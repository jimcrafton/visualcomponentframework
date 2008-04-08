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



namespace VCF  {

	
/**
\class ModelEvent Model.h "vcf/ApplicationKit/Model.h"
*/
class APPLICATIONKIT_API ModelEvent : public Event {
public:
	ModelEvent( Object* source, const uint32& type ) :
	  Event( source, type ) {

	  }

	ModelEvent( Object* source ) : Event(source){}

	virtual ~ModelEvent(){};

	virtual Object* clone( bool deep=false ) {
		return new ModelEvent(*this);
	}
};


typedef Delegate1<ModelEvent*> ModelDelegate; 
typedef ModelDelegate::ProcedureType ModelHandler;





class View;

#define MODEL_CLASSID		"ED88C0AD-26AB-11d4-B539-00C04F0196DA"


/**
\class Model Model.h "vcf/ApplicationKit/Model.h"
A model is the base class for storing data that can then 
be presented to the user by controls and/or views. 
The model maintains zero or more views. It can update
the views in one shot by the updateAllViews(). 

The exact kind of data store in the model is up to the implementor
but all models has some basic common characteristics.
 \li They can be emptied or cleared out by calling the empty() method.
 \li You can determine is the model has any data at all by calling
 the isEmpty() method. 
 \li A model's data can be "validated", in other words you can 
 call validate() to determine if the data in the model is in a 
 correct state, or has meaningful values. Again, the exact implementation
 is up to the programmer, but if the model is not considered "valid" 
 then the validate() method \em must throw an exception.
 \li A model can notify interested parties that it's state or data 
 has changed through it's ModelChanged delegate. Any time the data 
 for the model is modified some sort of ModelEvent should be
 passed to the ModelChanged delegate to notify any of the associated 
 callbacks.
 \li a generic method for retrieving data is provided (it may not be the 
 best or most effient way to retreive data) via the getValue() method
 \li a generic method for setting/modifying data is provided (it may not be the 
 best or most effient way to retreive data) via the setValue() method

@delegates
	@del Model::ModelChanged
	@del Model::ModelValidate
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
	called. Should also be fired for any change to the model's content.
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
	Validate the model.
	 */
    virtual void validate() {
		ValidationEvent e( this );
		ModelValidate( &e );
	}
	

	/**
	Returns whether or not the model has an data. The default is true, since 
	in it's abstract form the model doesn't (yet) have any data associated
	it. It is up to implementers to return something meaningful here.
	*/
	virtual bool isEmpty() {
		VCF_ASSERT( false ); //we shouldn't get here
		return true;
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
		return views_.getEnumerator();
	}

	void changed( ModelEvent* event ) {
		ModelChanged.invoke( event );
		updateAllViews();
	}

	/**
	Returns the value for the model. A key may be specified with a 
	VariantData object. The exact meaning of the key is up to the
	specific implementation Model based sub class. For example, a ListModel
	would expect a key that represents an integer based index. Another
	kind of model might use a string that represent's coordinates, or 
	perhaps even an object instance that has relevant data for the key.
	Some models might ignore the key altogether, for example a TextModel
	might ignore the key and simply return the text of the model.
	*/
	virtual VariantData getValue( const VariantData& key=VariantData::null() ) 	{
		return VariantData::null();
	}

	/**
	Returns the data for the model as a string.
	@see getValue
	*/
	virtual String getValueAsString( const VariantData& key=VariantData::null() ) {
		return getValue().toString();
	}

	/**
	Sets the value of the model. The data is stored in a VariantData object. The 
	key may be used if it's relevant to the specific kind of model. See the 
	getValue documentation for more information about the key parameter.
	@see getValue

	*/
	virtual void setValue( const VariantData& value, const VariantData& key=VariantData::null() ) { }

	/**
	Sets the value of the model using a string to specify the data. 
	@see setValue()
	*/
	virtual void setValueAsString( const String& value, const VariantData& key=VariantData::null() ) {
		Variant v;
		v.setFromString(value);
		setValue( v, key );
	}

	/**
	Indicates whether or not the model will be responsible for deleting objects that may be held 
	in a collection of VariantData instances. For example, if the model stored it's data 
	using an array of VariantData objects, and each item in the array was a pointer
	to some Object based instance, then if the method returns true, the model will be responsible 
	for freeing all the object instances stored in the array. If it returns false then the
	programmer would be responsible for freeing up the instances.
	*/
	bool shouldDeleteVarObjects() {
		return deleteVariantObjects_;
	}

protected:
	/**
	Indicates whether the model deletes the variant objects. If you need to 
	set this, you should do so in your models constructor by accessing this 
	variable directly. If you set it to true, the model should delete any 
	object's it stores.
	@see shouldDeleteVarObjects
	*/
	bool deleteVariantObjects_;
	Array<View*> views_;

	/**
	A virtual method that deletes the object stored by the model. You may choose 
	to override this with an alternate implementation.
	*/
	virtual void deleteVariantObject( Object* obj ) {
		Component* c = dynamic_cast<Component*>(obj);
		if (c) {
			c->free();
		}
		else {
			delete obj;
		}
	}
};

};


#endif // _VCF_MODEL_H__

/**
$Id$
*/
