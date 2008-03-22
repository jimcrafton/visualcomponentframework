#ifndef _VCF_XMLDICTOUTPUTSTREAM_H__
#define _VCF_XMLDICTOUTPUTSTREAM_H__
//XMLDictOutputStream.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/FoundationKit/Base64Codec.h"


namespace VCF {


/**
\class XMLDictOutputStream XMLDictOutputStream.h "vcf/FoundationKit/XMLDictOutputStream.h"
*/
class XMLDictOutputStream : public BasicOutputStream {
public:
	XMLDictOutputStream( OutputStream* outStream ): outStream_(outStream),tabCount_(0) {

	}

	virtual void seek(const uint64& offset, const SeekType& offsetFrom){
		outStream_->seek( offset, offsetFrom );
	}

	virtual uint64 getSize(){
		return outStream_->getSize();
	}

	virtual uchar* getBuffer() {
		return outStream_->getBuffer();
	}

	virtual uint64 getCurrentSeekPos() {
		return outStream_->getCurrentSeekPos();
	}

	virtual uint32 write( const unsigned char* bytesToRead, uint32 sizeOfBytes ) {
		return outStream_->write( bytesToRead, sizeOfBytes );
	}

	virtual void write( Persistable* persistableObject ) {
		Dictionary* dict = dynamic_cast<Dictionary*>(persistableObject);
		if ( NULL != dict ) {
			writeDict( *dict, true );
		}
		else {
			OutputStream::write( persistableObject );
		}
	}

	virtual void write( const short& val ) {
		writeInteger( val );
	}

	virtual void write( const long& val ) {
		writeInteger( val );
	}

	virtual void write( const int& val ) {
		writeInteger( val );
	}

	virtual void write( const bool& val ) {
		writeBool( val );
	}

	virtual void write( const float& val ) {
		writeReal( val );
	}

	virtual void write( const double& val ){
		writeReal( val );
	}

	virtual void write( const String& val ) {
		String s;
		s = "<string>" + val + "</string>\n";
		AnsiString tmp = getTabs() + s;
		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}


	OutputStream* outStream_;
	int tabCount_;

	AnsiString getTabs() {
		AnsiString result;
		result.append( tabCount_, '\t' );		
		return result;
	}

	void writeBool( bool val ) {
		String s;
		s = val ? "<true/>" : "<false/>\n";
		AnsiString tmp = getTabs() + s;
		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}

	void writeInteger( int val ) {
		String s;
		s = "<integer>" + StringUtils::toString(val) + "</integer>\n";
		AnsiString tmp = getTabs() + s;
		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}

	void writeReal( double val ) {
		String s;
		s = "<real>" + StringUtils::toString(val) + "</real>\n";
		AnsiString tmp = getTabs() + s;
		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}

	void writeData( const unsigned char* buffer, uint32 bufferSize ) {
		AnsiString output;
		Base64Codec::encode( buffer, bufferSize, output, true );
		AnsiString tmp;
		tmp = getTabs() + "<data>\n" + output + "/n</data>\n";

		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}

	void writeDate( const DateTime& dt ) {
		String s;
		s = "<date>";
		s += StringUtils::format( dt, "%Y-%m-%dT%H:%M:%SZ" ) ;
		s += "</date>\n";
		AnsiString tmp = getTabs() + s;
		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}

	void writeArray( VariantArray* data ) {
		AnsiString s;
		s = getTabs() + "<array>\n";
		write( (const unsigned char*)s.c_str(), s.length() );

		tabCount_++;

		std::vector<VariantData>::iterator it =
			data->data.begin();
		while ( it != data->data.end() ) {
			writeVariantData( &(*it) );
			++it;
		}
		
		tabCount_--;

		s = getTabs() + "</array>\n";
		write( (const unsigned char*)s.c_str(), s.length() );
	}
	
	void writeVariantData( VariantData* data ) {
		switch ( data->type ) {
			case pdShort : case pdULong : case pdLong : case pdInt : {				
				write( (int)(*data) );
			}
			break;

			case pdChar : {
				String s;
				s += (char)(*data);
				write( s );
			}
			break;

			case pdFloat : case pdDouble : {
				write( (double)(*data) );
			}
			break;

			case pdBool : {
				write( (bool)(*data) );
			}
			break;

			case pdString : {				
				write( (String)(*data) );
			}
			break;

			case pdDateTime : {				
				writeDate( *data );
			}
			break;

			

			case pdObject : {
				Object* obj = *data;				
				if ( NULL != obj ) {
					Dictionary* dict = dynamic_cast<Dictionary*>(obj);

					if ( NULL != dict ) {
						writeDict( *dict, false );	
					}
					else {
						VariantArray* va = dynamic_cast<VariantArray*>(obj);
						if ( NULL != va ) {
							writeArray( va );	
						}
						else {							
							Persistable* persistentObj = dynamic_cast<Persistable*>(obj);
							if ( NULL != persistentObj ) {
								BasicOutputStream bos;
								OutputStream* os = &bos;
								os->write( persistentObj );
								
								const unsigned char* buffer = (const unsigned char*)bos.getBuffer();
								
								writeData( buffer, bos.getSize() );
								
							}
							else {
								throw TypeCastException("Error attempting to write to stream.\nObject doesn't support Persistable interface!");
							}
						}
					}					
				}
				else {
					throw InvalidPointerException();
				}
			}
			break;
		}
	}

	void writeDict( Dictionary& dict ) {
		writeDict( dict, true );		
	}

	void writeDict( Dictionary& dict, bool isRootDictionary ) {

		AnsiString s;
		if ( isRootDictionary ) {
			s = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<plist>\n";
			write( (const unsigned char*)s.c_str(), s.length() );
			tabCount_ = 1;
		}

		s = getTabs() + "<dict>\n";
		write( (const unsigned char*)s.c_str(), s.length() );

		tabCount_++;

		Dictionary::Enumerator* items = dict.getEnumerator();
		while ( items->hasMoreElements() ) {
			Dictionary::pair item = items->nextElement();
			s = getTabs() + "<key>" + item.first + "</key>\n";
			write( (const unsigned char*)s.c_str(), s.length() );

			writeVariantData( &item.second );
		}

		tabCount_--;

		s = getTabs() + "</dict>\n";
		write( (const unsigned char*)s.c_str(), s.length() );

		if ( isRootDictionary ) {
			s = "</plist>\n";
			write( (const unsigned char*)s.c_str(), s.length() );	
			tabCount_ = 0;
		}
	}
};

};


#endif //_VCF_XMLDICTOUTPUTSTREAM_H__