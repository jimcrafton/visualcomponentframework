#ifndef _VCF_MIMETYPE_H__
#define _VCF_MIMETYPE_H__
//MIMEType.h

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
class MIMEType documentation
Specification for this MIME Types may be found at
RFC 2045 http://www.faqs.org/rfcs/rfc2045.html.
This is a simple class that makes it easy to deal with 
strings that signify mime-type information.
*/
class FOUNDATIONKIT_API MIMEType {
public:
	typedef std::pair<String,String> Parameter;

	MIMEType();

	MIMEType( const String& data );

	MIMEType( const String& type, const String& subType );

	MIMEType( const String& type, const String& subType, const std::vector<Parameter>& parameters );



	operator String () const {
		return data_;
	}

	MIMEType& operator=( const String& rhs ) {
		data_ = rhs;
		return *this;
	}

	MIMEType& operator=( const FilePath& rhs ) {
		setFromFileName( rhs );
		return *this;
	}

	bool operator==( const MIMEType& rhs ) const {
		return compare( rhs );
	}

	bool operator!=( const MIMEType& rhs ) const {
		return !compare( rhs );
	}

	void setFromFileName( const String& fileName ) {
		setFromFileName( FilePath(fileName) );
	}


	String getType() const;

	String getSubType() const;

	std::vector<Parameter> getParameters() const;


	bool isTextType() const;

	bool isImageType() const;

	bool isAudioType() const;

	bool isVideoType() const;

	bool isApplicationType() const;


	static void registerExtension( const String& extension, const String& mimeType );

protected:
	static std::map<String,String> registeredFileExtensions;

	void setFromFileName( const FilePath& fileName );
	String data_;

	bool compare( const MIMEType& rhs ) const;

	static String canonicalValue( const String& value );
};




};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_MIMETYPE_H__


