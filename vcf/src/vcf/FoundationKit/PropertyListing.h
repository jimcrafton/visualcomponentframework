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
	*The TextOutputStream is used for writing data from another stream as text.
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
	};
};

#endif //_VCF_PROPERTYLISTING_H__