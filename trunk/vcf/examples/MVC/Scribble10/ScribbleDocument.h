#ifndef SCRIBBLEDOCUMENT_H__
#define SCRIBBLEDOCUMENT_H__

using VCF::Document;
using VCF::DataObject;
using VCF::BasicInputStream;


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

	virtual bool paste( DataObject* data ) {
		ScribbleModel* model = (ScribbleModel*)getModel();
		VCF_ASSERT( NULL != model );
		
		if ( NULL == model ) {
			return false;
		}

		String type;
		
		Enumerator<MIMEType>* types = getSupportedClipboardFormats();
		while ( types->hasMoreElements() ) {
			type = types->nextElement();
			if ( data->isTypeSupported( type ) )  {
				break;
			}
		}		

		BasicOutputStream bos;
		if ( !type.empty() ) {				
			data->saveToStream( type, &bos );
		}

		BasicInputStream bis( bos.getBuffer(), bos.getSize() );
		openFromType( type, bis );

		return true;

	}
};


#endif //SCRIBBLEDOCUMENT_H__

