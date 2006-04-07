#ifndef _VCF_URL_H__
#define _VCF_URL_H__


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

namespace VCF {

	/**
	\class URL URL.h "vcf/InternetKit/URL.h"
	The URL class wraps a string that points to 
	some resource, either on the local filesystem
	or over the internet. The URL also has delegates
	that fire events as data is received, when status 
	changes during the download, and when authentication
	is requested in the form of a username and password.
	\par
	The URL can also break the string representation into
	it's component parts. See http://www.faqs.org/rfcs/rfc1738.html
	for more information about the exact parts of a 
	URL string.
	*/
	class INTERNETKIT_API URL : public Object {
	public:

		/**
		An enum compreising the various component
		parts of the URL.
		*/
		enum UrlParts{
			/**
			The scheme of the URL. These can
			include things like "http", "ftp",
			and so on.
			\par
			Required
			*/
			upScheme = 0,

			/**
			The user name for the resource. Used for
			authentication purposes. Unless you're using 
			an SSL connection there's a good chance this is 
			being sent in the clear.
			\par
			Optional
			*/
			upUser,

			/**
			The password for the resource. Used for
			authentication purposes. Unless you're using 
			an SSL connection there's a good chance this is 
			being sent in the clear.
			\par
			Optional
			*/
			upPassword,

			/**
			The host name for the resource. This would be things like
			"www.google.com", or "vcf-online.org", or even an 
			IP address like "192.45.66.121".
			\par
			Required
			*/
			upHost,
			/**
			The port to use to make a connection to the
			host.
			\par
			Optional
			*/
			upPort,
			/**
			The path to the resource.
			\par
			Required
			*/
			upUrlPath,
			/**
			The total number of possible URL components.
			*/
			upTotalCount
		};

		/**
		The possible event types that can be fired 
		by the URL when downloading a file.
		*/
		enum Events {
			/**
			The URL is about to receive some data. 
			*/
			evDataReceiving = 0x23123,
			/**
			The URL has received a chunk of data and written to 
			a the output stream.
			*/
			evDataReceived,
			/**
			The status of the URL download has changed.
			*/
			evStatusChanged,

			/**
			The URL requires authentication. The handler will
			need to supply a valid user name and password.
			*/
			evAuthenticationRequested
		};


		DELEGATE( DataReceiving );
		DELEGATE( DataReceived );
		DELEGATE( StatusChanged );
		DELEGATE( AuthenticationRequested );

		URL(){}

		URL(const String& urlString ):data_(urlString){
			parse();
		}

		/**
		Assign a string to the URL.
		*/
		URL& operator=( const String& rhs ) {
			data_ = rhs;
			
			parse();

			return *this;
		}

		operator String() const {
			return data_;
		}

		String getURLString() const {
			return data_;
		}

		/**
		Start downloading the URL into the OutputStream. The InternetToolKit 
		will extract the data and write it to the output stream. During this 
		process various events may get fired.
		\par
		If the URL was not able to access the data, a URLException
		may be thrown.
		*/
		void download( OutputStream& stream ) {
			InternetToolkit::getDataFromURL( this, &stream );
		}

		/**
		Download the URL to the specific filename. The InternetToolKit 
		will extract the data and write it to the file. During this 
		process various events may get fired.
		\par
		If the URL was not able to access the data, a URLException
		may be thrown.
		*/
		void downloadToFile( const String& fileName ) {
			FileOutputStream fos(fileName);
			download( fos );
		}

		/**
		Returns the scheme component of the URL
		*/
		String getScheme() const {
			std::vector<String> parts;
			parse( &parts );

			return parts[URL::upScheme];
		}

		/**
		Returns the user component of the URL
		*/
		String getUser() const {
			std::vector<String> parts;
			parse( &parts );

			return parts[URL::upUser];
		}

		/**
		Returns the password component of the URL
		*/
		String getPassword() const {
			std::vector<String> parts;
			parse( &parts );

			return parts[URL::upPassword];
		}

		/**
		Returns the host component of the URL
		*/
		String getHost() const {
			std::vector<String> parts;
			parse( &parts );

			return parts[URL::upHost];
		}

		/**
		Returns the port component of the URL
		*/
		String getPort() const {
			std::vector<String> parts;
			parse( &parts );

			return parts[URL::upPort];
		}

		/**
		Returns the url path component of the URL
		*/
		String getUrlPath() const {
			std::vector<String> parts;
			parse( &parts );

			return parts[URL::upUrlPath];
		}


		/**
		Returns all the components of the URL in a vector.
		*/
		std::vector<String> getParts() const {
			std::vector<String> result;
			
			parse( &result );

			return result;
		}

		/**
		Verify the URL is actually valid. If the URL is 
		invalid the function returns false, otherwise it 
		returns true.
		*/
		bool validate() const {
			bool result = true;

			try {
				parse( NULL, true );
			}
			catch ( BasicException& e ) {
				StringUtils::trace( e.getMessage() + "\n" );
			}
			return result;
		}
	protected:
		String data_;

		virtual String parseScheme( String& data, bool validate=false ) const {
			String result ;
			int pos = data.find( "://" );
			if ( pos != String::npos ) {
				result = data.substr( 0, pos );
				data.erase( 0, pos + 3 );
			}

			return result;
		}

		void parse( std::vector<String>* parts=NULL, bool validate=false ) const {


			//based on the spec at RFC 1738
			//http://www.faqs.org/rfcs/rfc1738.html
			String scheme;
			String schemePart;
			String user;
			String pwd;
			String host;
			String port;
			String urlPath = "/";

			schemePart = data_;
			
			//strip out scheme
			scheme = parseScheme(schemePart);


			//strip out url path
			int pos = schemePart.find( "/" );
			if ( pos != String::npos ) {
				urlPath = schemePart.substr(pos,schemePart.size()-(pos));
				schemePart.erase( pos,schemePart.size()-pos);
			}


			pos = schemePart.find( "@" );

			if ( pos != String::npos ) {
				user = schemePart.substr(0,pos);
				schemePart.erase( 0, pos+1);

				pos = user.find( ":" );
				if ( pos != String::npos ) {
					pwd = user.substr(pos+1,user.size()-(pos+1));
					user.erase( pos+1,user.size()-(pos+1));
				}

				if ( validate ) {
					if ( String::npos != schemePart.find( "@" ) ) {
						//oops bad string! you've probable got a '@' in your password
						throw RuntimeException( "Bad URL string! You've probably got a '@' in your password" );
					}
				}
			}
			
			

			pos = schemePart.find( ":" );

			if ( pos != String::npos ) {				
				port = schemePart.substr(pos+1,schemePart.size()-(pos+1));
				schemePart.erase( pos,schemePart.size()-(pos));				
			}

			host = schemePart;

			if ( NULL != parts ) {
				std::vector<String>& tmp = *parts;

				parts->resize(URL::upTotalCount);

				tmp[URL::upScheme] = scheme;
				tmp[URL::upUser] = user;
				tmp[URL::upPassword] = pwd;
				tmp[URL::upHost] = host;
				tmp[URL::upPort] = port;
				tmp[URL::upUrlPath] = urlPath;
			}
		}
	};


	

	class URLAuthenticationEvent : public Event {
	public:
		URLAuthenticationEvent( URL* source ) : Event(source, URL::evAuthenticationRequested){}

		virtual Object* clone( bool deep=false ) {
			return new URLAuthenticationEvent(*this);
		}

		String getUserName() {
			return userName;
		}

		void setUserName( const String& val ) {
			userName = val;
		}

		String getPassword() {
			return password;
		}

		void setPassword( const String& val ) {
			password = val;
		}
	protected:
		String userName;
		String password;

	};

	class URLEvent : public Event {
	public:
		URLEvent( URL* source, ulong32 eventType ): 
		  Event(source,eventType),
			  bytesRecvd_(0),
			  cancelDataTransfer_(false){}

		URLEvent( const URLEvent& rhs ):
			Event(rhs),
			statusText_(rhs.statusText_), 
			bytesRecvd_(rhs.bytesRecvd_), 
			cancelDataTransfer_(rhs.cancelDataTransfer_){}
			
		
		virtual Object* clone( bool deep=false ) {
			return new URLEvent(*this);
		}

		String getStatusText() {
			return statusText_;
		}

		void setStatusText( const String& val ) {
			statusText_ = val;
		}

		uint32 getBytesReceived() {
			return bytesRecvd_;
		}

		void setBytesReceived( const uint32& val ) {
			bytesRecvd_ = val;
		}

		bool shouldCancelDataTransfer() {
			return cancelDataTransfer_;
		}

		void cancelDataTransfer() {
			cancelDataTransfer_ = true;
		}
	protected:
		String statusText_;
		uint32 bytesRecvd_;
		bool cancelDataTransfer_;
	};

	
	
	class URLException : public BasicException{
	public:
		URLException( const String & message ):
		  BasicException( message ){};
		  
		URLException( const String & message, const int lineNumber ):
		  BasicException(message, lineNumber){};
		  
		  virtual ~URLException() throw() {};
	};

};

#endif //_VCF_URL_H__

