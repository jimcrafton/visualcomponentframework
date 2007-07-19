#ifndef _VCF_MODEL_H__
#define _VCF_MODEL_H__
//Model.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF{

class View;

#define MODEL_CLASSID		"ED88C0AD-26AB-11d4-B539-00C04F0196DA"


/**
\class Model Model.h "vcf/ApplicationKit/Model.h"
A Model is the base class for storing data for a control or other visual elements.
*/
class APPLICATIONKIT_API Model : public Component {
public:


	Model();

	virtual ~Model();


	enum ModelEvents{
		MODEL_CHANGED = 2000,
		MODEL_VALIDATED,
		MODEL_EMPTIED,
		MODEL_LAST_EVENT
	};



	/**
	@delegate ModelChanged fired when the model's empty() method is
	called. Should be fired for any change to the model's content.
	@event ModelEvent
	@eventtype Model::MODEL_EMPTIED
	@see empty()
	*/
	DELEGATE(ModelDelegate,ModelChanged)

	/**
	@delegate ModelValidate fired when the model's validate() method is called
	@event ValidationEvent
	@see validate()
	*/
	DELEGATE(ValidationDelegate,ModelValidate)

    /**
     * Adds a validation listener to the model
     */
    void addModelValidationHandler( EventHandler* handler ){
		ModelValidate +=  handler;
	}

    /**
     * removes a validation listener from the model
     */
    void removeModelValidationHandler( EventHandler* handler ){
		ModelValidate.remove( handler );
	}

    /**
     * validate the model.
     * The implementation for this can vary widely, or even be nonexistant for model's that do not require validation.
     * The basic idea is to call all the listeners in the list , passing in a local variable to the
     * onModelValidate() methods of the listener's. The variable is initialized to true, and if it is
     * still true at the end of the listener iterations, then it is safe to apply the changes to the
     * model, other wise the changes are removed.
     */
    virtual void validate() {
		ValidationEvent e( this );
		ModelValidate( &e );
	}

    /**
     * Adds a model listener to the model
     */
    void addModelHandler( ModelHandler* handler ){
		ModelChanged +=  handler;
	}

    /**
     * removes a model listener from the model
     */
    void removeModelHandler( ModelHandler* handler ){
		ModelChanged.remove( handler );
	}

	

	

	/**
     * clears out the model's data
     */
	virtual void empty() {
		ModelEvent e( this, Model::MODEL_EMPTIED );
		changed( &e );
	}

	/**
	*adds a new view to the model
	*/
	virtual void addView( View* view );

	/**
	*removes a view from the model
	*/
	virtual void removeView( View* view );

	/**
	*notifies all the views the model has changed
	*calls View::updateView( ), passing itself
	*in as the updated Model
	*/
	virtual void updateAllViews();

	Enumerator<View*>* getViews() {
		return viewContainer_.getEnumerator();
	}

	void changed( ModelEvent* event ) {
		ModelChanged.invoke( event );
		updateAllViews();
	}
protected:
	std::vector<View*> views_;
	EnumeratorContainer<std::vector<View*>,View*> viewContainer_;
};

};


#endif // _VCF_MODEL_H__

/**
$Id$
*/
