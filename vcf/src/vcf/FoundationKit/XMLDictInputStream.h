#ifndef _VCF_XMLDICTINPUTSTREAM_H__
#define _VCF_XMLDICTINPUTSTREAM_H__
//XMLDictInputStream.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


/**
\class XMLDictInputStream XMLDictInputStream.h "vcf/FoundationKit/XMLDictInputStream.h"
*/
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

	virtual uchar* getBuffer() {
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

	void readValue( XMLNode* valNode, VariantData& value ) {
		String name = StringUtils::lowerCase(valNode->getName());
		StringUtils::trimWhiteSpaces( name );

		String cdata = valNode->getCDATA();
		StringUtils::trimWhiteSpaces( cdata );
		if ( name == "integer" ) {
			int val = StringUtils::fromStringAsInt( cdata );
			value = val;
		}
		else if ( name == "string" ) {
			value = cdata;
		}
		else if ( name == "real" ) {
			double val = StringUtils::fromStringAsDouble( cdata );
			value = val;
		}
		else if ( name == "date" ) {
			size_t pos = cdata.find("T");

			VCF_ASSERT( pos != String::npos );
			
			if ( pos != String::npos ) {
				StringTokenizer dtPt(cdata.substr(0,pos),"-");
				std::vector<String> vals;
				dtPt.getElements(vals);
				cdata.erase( 0, pos+1 );
				pos = cdata.find("Z");
				
				VCF_ASSERT( pos != String::npos );
				
				if ( pos != String::npos ) {
					StringTokenizer tmPt(cdata.substr(0,pos),":");
					std::vector<String> vals2;
					tmPt.getElements(vals2);
					
					VCF_ASSERT( vals.size() == 3 );

					VCF_ASSERT( vals2.size() == 3 );

					if ( vals.size() == 3 && vals2.size() == 3 ) {
						DateTime dt;
						dt.set( StringUtils::fromStringAsUInt(vals[0]), 
								StringUtils::fromStringAsUInt(vals[1]), 
								StringUtils::fromStringAsUInt(vals[2]),
								StringUtils::fromStringAsUInt(vals2[0]), 
								StringUtils::fromStringAsUInt(vals2[1]), 
								StringUtils::fromStringAsUInt(vals2[2]) );
						
						
						value = dt;
					}
				}
				
			}
		}
		else if ( name == "data" ) {
			AnsiString s;
			uint32 bufferSize = 0;
			Base64Codec::decode( s, NULL, bufferSize );
			if ( bufferSize > 0 ) {
				unsigned char* buffer = new unsigned char[bufferSize];
				
				Base64Codec::decode( s, buffer, bufferSize );

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
			value = val;
		}
		else if ( name == "false" ) {
			bool val = false;
			value = val;
		}
		else if ( name == "array" ) {
			VariantArray* va = new VariantArray();
			
			readArray( valNode, va );

			value = va;
		}
		else if ( name == "dict" ) {
			Dictionary* subDict = new Dictionary();
			readDict( valNode, *subDict );
			value = subDict;
		}
	}

	void readArray( XMLNode* arrayNode, VariantArray* array ) {
		Enumerator<XMLNode*>* nodes = arrayNode->getChildNodes();
		array->setOwnsObjectValues( true );
		while ( nodes->hasMoreElements() ) {
			XMLNode* valNode = nodes->nextElement();
			VariantData v;
			readValue( valNode, v );

			array->data.push_back( v );
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

			VariantData v;
			readValue( valNode, v );

			dict[ keyName ] = v;

			if ( name == "dict" || name == "array" ) {
				dict.setOwnsObjectValues( true );
			}
		}	
	}

	virtual uint64 getCurrentSeekPos() {
		return inStream_->getCurrentSeekPos();
	}
protected:
	InputStream* inStream_;	
};


};

#endif //_VCF_XMLDICTINPUTSTREAM_H__

