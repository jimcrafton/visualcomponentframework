
#ifndef _$$ROOT$$DOCUMENT_H__
#define _$$ROOT$$DOCUMENT_H__

#include "ModelViewKit.h"

#define $$ROOT$$DOCUMENT_CLASSID		"$$DOCUUID$$"

/**
class $$Root$$Document documentation
*/
class $$Root$$Document : public VCF::Document {
public: 
	BEGIN_CLASSINFO( $$Root$$Document, "$$Root$$Document", "VCF::Document", $$ROOT$$DOCUMENT_CLASSID )
	END_CLASSINFO($$Root$$Document)

	$$Root$$Document();
	virtual ~$$Root$$Document();

	virtual void initNew();

	virtual void empty();

	virtual bool canCutFromDocument() {
		return true;
	}

	virtual bool canCopyFromDocument() {
		return true;
	}

	virtual bool canPasteToDocument() {
		return true;
	}

	virtual bool saveAsType( const VCF::String& fileType, VCF::OutputStream& stream );

	virtual bool openFromType( const VCF::String& fileType, VCF::InputStream& stream );
protected:

};



#endif //_$$ROOT$$DOCUMENT_H__



