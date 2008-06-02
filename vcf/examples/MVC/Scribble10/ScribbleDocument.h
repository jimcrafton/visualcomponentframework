#ifndef SCRIBBLEDOCUMENT_H__
#define SCRIBBLEDOCUMENT_H__

using VCF::Document;
using VCF::DataObject;


class ScribbleDocument : public Document {
public:

	virtual bool canCopyFromDocument() {
		ScribbleModel* model = (ScribbleModel*)getModel();

		VCF_ASSERT( NULL != model );
		
		if ( NULL == model ) {
			return false;
		}


		return NULL != model->getActiveShape();
	}


	virtual bool canCutFromDocument() {
		return canCopyFromDocument();
	}


	virtual DataObject* cut() {
		ScribbleModel* model = (ScribbleModel*)getModel();
		VCF_ASSERT( NULL != model );
		
		if ( NULL == model ) {
			return NULL;
		}

		DataObject* result = copy();

		VariantData v = model->getActiveShape();
		model->remove( model->getIndexOf(v) );

		return result;
	}
};


#endif //SCRIBBLEDOCUMENT_H__

