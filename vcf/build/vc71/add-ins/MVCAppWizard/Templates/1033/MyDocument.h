#ifndef _[!output UPPER_CASE_PROJECT_NAME]DOCUMENT_H__
#define _[!output UPPER_CASE_PROJECT_NAME]DOCUMENT_H__

#include "vcf/ApplicationKit/ModelViewKit.h"

#define [!output UPPER_CASE_PROJECT_NAME]DOCUMENT_CLASSID		"[!output DOC_UUID]"

/**
class [!output PROJECT_NAME]Document documentation
*/
class [!output PROJECT_NAME]Document : public VCF::Document {
public: 
	BEGIN_CLASSINFO( [!output PROJECT_NAME]Document, "[!output PROJECT_NAME]Document", "VCF::Document", [!output UPPER_CASE_PROJECT_NAME]DOCUMENT_CLASSID )
	END_CLASSINFO([!output PROJECT_NAME]Document)

	[!output PROJECT_NAME]Document();
	virtual ~[!output PROJECT_NAME]Document();

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



#endif //_[!output UPPER_CASE_PROJECT_NAME]DOCUMENT_H__



