//Dictionaries.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/Dictionary.h"


using namespace VCF;


class Base64Data {
public:
	
	static void encode( const unsigned char* buffer, uint32 bufferSize, AnsiString& output, bool addLineBreak ) { 
		uint32 count = 0;
		uint32 o = 0;
		
		output = "";
		while (count < bufferSize) {
			uint32 remainingBytes = bufferSize - count;
			if ( addLineBreak && o && (o % 76 == 0) ) {
				output += "\n";
			}
			switch ( remainingBytes ) {
				case 1: {
					output += Base64Data::base64EncodingTable[ ((buffer[count] >> 2) & 0x3f) ];
					output += Base64Data::base64EncodingTable[ ((buffer[count] << 4) & 0x30) ];
					output += "==";
				}
				break; 
				case 2: {
					output += Base64Data::base64EncodingTable[ ((buffer[count] >> 2) & 0x3f) ];
					output += Base64Data::base64EncodingTable[ ((buffer[count] << 4) & 0x30) + ((buffer[count + 1] >> 4) & 0x0f) ];
					output += Base64Data::base64EncodingTable[ ((buffer[count + 1] << 2) & 0x3c) ];
					output += "=";
				}
				break;

				default: {
					output += Base64Data::base64EncodingTable[ ((buffer[count] >> 2) & 0x3f) ];
					output += Base64Data::base64EncodingTable[ ((buffer[count] << 4) & 0x30) + ((buffer[count + 1] >> 4) & 0x0f) ];
					output += Base64Data::base64EncodingTable[ ((buffer[count + 1] << 2) & 0x3c) + ((buffer[count + 2] >> 6) & 0x03) ];
					output += Base64Data::base64EncodingTable[ (buffer[count + 2] & 0x3f) ];
				}
				break;
			}
			o += 4;
			count += 3;
		}
	}

	//calling this with a NULL buffer means that the buffer size will be returned
	static void decode(const AnsiString& input, unsigned char *buffer, uint32& bufferSize )	{
		uint32 index = 0;
		uint32 count = input.size();
		uint32 bufferIndex = 0;
		
		

		while (index < count)
		{
			while (index < count && (input[index] == 13 || input[index] == 10)) {
				index++;
			}

			if (index < count) {
				unsigned char b1 = (unsigned char)((Base64Data::base64DecodingTable[(int)input[index]] << 2 & 0xfc) +
					(Base64Data::base64DecodingTable[(int)input[index + 1]] >> 4 & 0x03));
				
				if ( buffer ) {
					buffer[bufferIndex] = b1;
				}
				
				bufferIndex++;
				if (input[index + 2] != '=')  {
					unsigned char b2 = (unsigned char)((Base64Data::base64DecodingTable[(int)input[index + 1]] << 4 & 0xf0) +
						(Base64Data::base64DecodingTable[(int)input[index + 2]] >> 2 & 0x0f));
					
					if ( buffer ) {
						buffer[bufferIndex] = b2;
					}

					bufferIndex++;
				}

				if (input[index + 3] != '=') {
					unsigned char b3 = (unsigned char)((Base64Data::base64DecodingTable[(int)input[index + 2]] << 6 & 0xc0) +
						Base64Data::base64DecodingTable[(int)input[index + 3]]);
					
					if ( buffer ) {
						buffer[bufferIndex] = b3;
					}
					
					bufferIndex++;
				}
				index += 4;
			}
		}
		bufferSize = bufferIndex;
	}

	static char* base64EncodingTable;
	static char base64DecodingTable[];
};

char* Base64Data::base64EncodingTable = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
char Base64Data::base64DecodingTable[] = {
           0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
           0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 
           0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  62,   0,   0,   0,  63, 
          52,  53,  54,  55,  56,  57,  58,  59,  60,  61,   0,   0,   0,   0,   0,   0, 
           0,   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14, 
          15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,   0,   0,   0,   0,   0, 
           0,  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40, 
          41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,   0,   0,   0,   0,   0};













class XMLDictOutputStream : public BasicOutputStream {
public:
	XMLDictOutputStream( OutputStream* outStream ): outStream_(outStream) {

	}

	virtual void seek(const uint64& offset, const SeekType& offsetFrom){
		outStream_->seek( offset, offsetFrom );
	}

	virtual uint64 getSize(){
		return outStream_->getSize();
	}

	virtual char* getBuffer() {
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
		AnsiString tmp = s;
		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}


	OutputStream* outStream_;

	void writeBool( bool val ) {
		String s;
		s = val ? "<true/>" : "<false/>\n";
		AnsiString tmp = s;
		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}

	void writeInteger( int val ) {
		String s;
		s = "<integer>" + StringUtils::toString(val) + "</integer>\n";
		AnsiString tmp = s;
		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}

	void writeReal( double val ) {
		String s;
		s = "<real>" + StringUtils::toString(val) + "</real>\n";
		AnsiString tmp = s;
		write( (const unsigned char*)tmp.c_str(), tmp.length() );
	}

	void writeData( const unsigned char* buffer, uint32 bufferSize ) {
		AnsiString output;
		Base64Data::encode( buffer, bufferSize, output, true );
		AnsiString tmp;
		tmp = "<data>\n" + output + "/n</data>\n";

		write( (const unsigned char*)tmp.c_str(), tmp.length() );
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

			case pdObject : {
				Object* obj = *data;				
				if ( NULL != obj ) {
					Dictionary* dict = dynamic_cast<Dictionary*>(obj);

					if ( NULL != dict ) {
						writeDict( *dict, false );	
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
		}

		s = "<dict>\n";
		write( (const unsigned char*)s.c_str(), s.length() );

		Dictionary::Enumerator* items = dict.getEnumerator();
		while ( items->hasMoreElements() ) {
			Dictionary::pair item = items->nextElement();
			s = "<key>" + item.first + "</key>\n";
			write( (const unsigned char*)s.c_str(), s.length() );

			writeVariantData( &item.second );
		}

		s = "</dict>\n";
		write( (const unsigned char*)s.c_str(), s.length() );

		if ( isRootDictionary ) {
			s = "</plist>\n";
			write( (const unsigned char*)s.c_str(), s.length() );	
		}
	}
};




class XMLDictInputStream : public BasicInputStream {
public:
	XMLDictInputStream( InputStream* stream ): inStream_(stream) {

	}

	virtual void seek(const uint64& offset, const SeekType& offsetFrom) {
		inStream_->seek( offset, offsetFrom );
	}

	virtual uint64 getSize() {
		return inStream_->getSize();
	}

	virtual char* getBuffer() {
		return inStream_->getBuffer();
	}

	virtual uint32 read( unsigned char* bytesToRead, uint32 sizeOfBytes ) {
		return inStream_->read( bytesToRead, sizeOfBytes );
	}

	virtual void read( Persistable* persistableObject ) {
		Dictionary* dict = dynamic_cast<Dictionary*>(persistableObject);
		if ( NULL != dict ) {
			readDict( *dict );
		}
		else {
			InputStream::read( persistableObject );
		}
	}

	virtual bool isEOS()
	{
		return inStream_->isEOS();
	}

	void readDict( Dictionary& dict ) {
		XMLParser parser;

		parser.parse( inStream_ );

		Enumerator<XMLNode*>* nodes = parser.getParsedNodes();
		XMLNode* plist = NULL;

		while ( nodes->hasMoreElements() ) {
			XMLNode* node = nodes->nextElement();
			if ( node->getName() == "plist" ) {
				plist = node;
				break;
			}
		}

		if ( NULL != plist ) {
			//get root dict

			XMLNode* rootDict = plist->getNodeByName( "dict" );

			readDict( rootDict, dict );
		}
	}

	void readDict( XMLNode* dictNode, Dictionary& dict ) {
		Enumerator<XMLNode*>* nodes = dictNode->getChildNodes();
		

		while ( nodes->hasMoreElements() ) {
			XMLNode* keyNode = nodes->nextElement();
			String key = StringUtils::lowerCase(keyNode->getName());
			StringUtils::trimWhiteSpaces( key );			
			
			if ( key != "key" ) {
				throw RuntimeException( "Invalid dictionary format!!! No key node!" );
			}

			if ( !nodes->hasMoreElements() ) {
				throw RuntimeException( "Invalid dictionary format!!! No value node found!" );
			}

			String keyName = keyNode->getCDATA();
			StringUtils::trimWhiteSpaces( keyName );

			XMLNode* valNode = nodes->nextElement();

			String name = StringUtils::lowerCase(valNode->getName());
			StringUtils::trimWhiteSpaces( name );

			String cdata = valNode->getCDATA();
			StringUtils::trimWhiteSpaces( cdata );
			if ( name == "integer" ) {
				int val = StringUtils::fromStringAsInt( cdata );
				dict[ keyName ] = val;
			}
			else if ( name == "string" ) {
				dict[ keyName ] = cdata;
			}
			else if ( name == "real" ) {
				double val = StringUtils::fromStringAsInt( cdata );
				dict[ keyName ] = val;
			}
			else if ( name == "data" ) {
				AnsiString s;
				uint32 bufferSize = 0;
				Base64Data::decode( s, NULL, bufferSize );
				if ( bufferSize > 0 ) {
					unsigned char* buffer = new unsigned char[bufferSize];
					
					Base64Data::decode( s, buffer, bufferSize );

					/**
					we need to be able to attach the data to an Object class
					so that we can assign it to a VariantData instance,
					We need to create a new class for this, something like:
					
					class BinaryData : public Object {
					public:
					protected:
						unsigned char* buffer_;
						uint32 bufSize_;
					};

					then we could do something like 
					Dictionary dict;
					BinaryData* data = new BinaryData( jpegPictData, jpegPictSize );
					dict["Picture"] = data;
					*/

					delete [] buffer;
				}
			}
			else if ( name == "true" ) {
				bool val = true;
				dict[ keyName ] = val;
			}
			else if ( name == "false" ) {
				bool val = false;
				dict[ keyName ] = val;
			}
			else if ( name == "dict" ) {
				
			}
		}	
	}

	virtual uint64 getCurrentSeekPos() {
		return inStream_->getCurrentSeekPos();
	}
protected:
	InputStream* inStream_;	
};


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );
	
	//create a dictionary

	Dictionary dict;

	//add 2 elements to the dictionary.

	dict.insert( "size", 200 );

	dict["width"] = 150;

	dict["Name"] = "Bob";


	Dictionary::Enumerator* items = dict.getEnumerator();
	while ( items->hasMoreElements() ) {
		Dictionary::pair item = items->nextElement();

		System::println( Format("dict[\"%s\"] = %s") % item.first % item.second.toString() );
	}



	System::println( "Saving dictionary..." );

	{
		//store the dictionary
		FileOutputStream fs("test.dict.xml");

		//note: The use of the TextOutputStream is not neccessary, it's
		//just for demonstration purposes.
		//TextOutputStream tos(&fs);
		XMLDictOutputStream xos(&fs);

		//xos.writeDict( dict );
		//dump the dictionary to the stream
		xos << &dict;

	}

	System::println( "Loading dictionary..." );

	{
		//read in the dictionary from a file
		FileInputStream fs("test.dict.xml");

		//note: The use of the TextInputStream is not neccessary, it's
		//just for demonstration purposes.
		XMLDictInputStream xis(&fs);

		//clear the dictionary - this will remove all elements in the dictionary
		dict.clear();

		//read in the dictionary from the stream
		xis >> static_cast<VCF::Persistable*>(&dict);
	}


	items = dict.getEnumerator();
	while ( items->hasMoreElements() ) {
		Dictionary::pair item = items->nextElement();

		System::println( Format("dict[\"%s\"] = %s") % item.first % item.second.toString() );
	}



	FoundationKit::terminate();
	return 0;
}


/**
$Id$
*/
