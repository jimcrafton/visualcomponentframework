#ifndef _VCF_PROPERTYLISTING_H__
#define _VCF_PROPERTYLISTING_H__
//PropertyListing.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/XMLDictOutputStream.h"
#include "vcf/FoundationKit/XMLDictInputStream.h"
#include "vcf/FoundationKit/TextOutputStream.h"


namespace VCF {
	
	

	/**
	\class PropertyListing PropertyListing.h "vcf/FoundationKit/PropertyListing.h"
	A PropertyListing is just a Dictionary with some extra functions that
	make it easy to deal with sub dictionaries and arrays. Also supports
	reading and writing itself using the property list xml format. 
	*/
	class PropertyListing : public Dictionary {
	public:

		virtual String toString() const {
			TextOutputStream tos;
			XMLDictOutputStream xos(&tos);
			PropertyListing* pl = (PropertyListing*)this;
			xos << pl;

			return tos.getTextBuffer();
		}

		virtual void loadFromStream( InputStream* stream, const MIMEType& type=MIMEType() ) {
			XMLDictInputStream xis(stream);			
			//dump the dictionary to the stream
			xis >> this;
		}

		virtual void saveToStream( OutputStream* stream, const MIMEType& type=MIMEType() ) {
			XMLDictOutputStream xos(stream);			
			//dump the dictionary to the stream
			xos << this;
		}

		Dictionary& getDict( const String& name ) {
			if ( !keyExists( name ) ) {
				throw RuntimeException( "No dictionary exists with the name " + name );
			}
		
			VariantData v = get( name );

			if ( v.type != pdObject ) {
				throw RuntimeException( "Invalid data type named " + name + ". Expecting a dictionary object."  );
			}
			Object* o = v;
			if ( o == NULL ) {
				throw RuntimeException( "NULL Dictionary with name " + name );
			}

			return (Dictionary&) (*o);
		}

		const Dictionary& getDict( const String& name ) const {
			if ( !keyExists( name ) ) {
				throw RuntimeException( "No dictionary exists with the name " + name );
			}
		
			VariantData v = get( name );

			if ( v.type != pdObject ) {
				throw RuntimeException( "Invalid data type named " + name + ". Expecting a dictionary object."  );
			}
			Object* o = v;
			if ( o == NULL ) {
				throw RuntimeException( "NULL Dictionary with name " + name );
			}

			return (const Dictionary&) (*o);
		}


		VariantArray& getArray( const String& name ) {
			if ( !keyExists( name ) ) {
				throw RuntimeException( "No array exists with the name " + name );
			}
		
			VariantData v = get( name );

			if ( v.type != pdObject ) {
				throw RuntimeException( "Invalid data type named " + name + ". Expecting an array object."  );
			}
			Object* o = v;
			if ( o == NULL ) {
				throw RuntimeException( "NULL VariantArray with name " + name );
			}

			return (VariantArray&) (*o);
		}

		const VariantArray& getArray( const String& name ) const {
			if ( !keyExists( name ) ) {
				throw RuntimeException( "No array exists with the name " + name );
			}
		
			VariantData v = get( name );

			if ( v.type != pdObject ) {
				throw RuntimeException( "Invalid data type named " + name + ". Expecting an array object."  );
			}
			Object* o = v;
			if ( o == NULL ) {
				throw RuntimeException( "NULL VariantArray with name " + name );
			}

			return (const VariantArray&) (*o);
		}

		VariantData& getByPath(const String& path ) {
			String tmp = path;
			size_t pos = tmp.find( "/" );
			VariantData dictVal;
			Dictionary* currentDict = this;
			while ( pos != String::npos ) {
				dictVal = currentDict->get( tmp.substr(0,pos) );
				tmp.erase( 0, pos+1);
				pos = tmp.find( "/" );

				currentDict = (Dictionary*) (Object*)dictVal;
			}

			VCF_ASSERT( NULL != currentDict );

			if ( NULL == currentDict ) {
				throw RuntimeException( "NULL Dictionary in path name " + path );
			}
		
			return currentDict->get( tmp );
		}

		VariantData getByPath(const String& path ) const {
			String tmp = path;
			size_t pos = tmp.find( "/" );
			VariantData dictVal;
			const Dictionary* currentDict = this;
			while ( pos != String::npos ) {
				dictVal = currentDict->get( tmp.substr(0,pos) );
				tmp.erase( 0, pos+1);
				pos = tmp.find( "/" );

				currentDict = (const Dictionary*) (Object*)dictVal;
			}

			VCF_ASSERT( NULL != currentDict );

			if ( NULL == currentDict ) {
				throw RuntimeException( "NULL Dictionary in path name " + path );
			}
		
			return currentDict->get( tmp );
		}
	};
};

#endif //_VCF_PROPERTYLISTING_H__