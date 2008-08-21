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







/**
\class ValidationEvent Model.h "vcf/ApplicationKit/Model.h"  
*/
class APPLICATIONKIT_API ValidationEvent : public VCF::Event {
public:

	ValidationEvent( Object* source, const uint32& type,
						const VariantData& k,
						const VariantData& v ): 
		Event(source,type),validationOK(false),key(k), value(v){}

	
	virtual ~ValidationEvent() {}
	
	virtual Object* clone( bool deep=false ) {
		return new ValidationEvent(*this);
	}


	const VariantData& key;

	const VariantData& value;


	bool validationOK;
	String errorMessage;
};



/**
\class ValidationEvent Model.h "vcf/ApplicationKit/Model.h"  
*/
class APPLICATIONKIT_API ValidationErrorEvent : public VCF::Event {
public:

	enum ValidationState {
		vsNone = 0,
		vsFormattingFailed,
		vsValidatorRulesFailed,
		vsValidatingFailed
	};

	ValidationErrorEvent( Object* source, const uint32& type,
						const VariantData& k,
						const VariantData& v ): 
		Event(source,type),key(k), value(v),state(vsNone){}

	
	virtual ~ValidationErrorEvent() {}
	
	virtual Object* clone( bool deep=false ) {
		return new ValidationErrorEvent(*this);
	}


	const VariantData& key;

	const VariantData& value;


	String errorMessage;
	ValidationState state;
};

/**
\class ValidationException Model.h "vcf/ApplicationKit/Model.h"
*/
class APPLICATIONKIT_API ValidationException : public BasicException{
public:

	ValidationException( const String & message ):
	  BasicException( message ){};

	ValidationException():
		BasicException( "Validation error occurred." ){};

	ValidationException( const String & message, const int lineNumber ):
		BasicException(message, lineNumber){};

	virtual ~ValidationException() throw() {};
}; 



/**
ModelValidationDelegate
handles the following:
\li onModelValidate
*/

typedef Delegate1<ValidationEvent*> ValidationDelegate; 
typedef ValidationDelegate::ProcedureType ValidationHandler;


typedef Delegate1<ValidationErrorEvent*> ValidationErrorDelegate; 





class APPLICATIONKIT_API ValidationFormatter : public Component {
public:
	virtual ~ValidationFormatter(){}

	/**
	Converts a model's raw value, based on it's key, to some other 
	format, typically a string. For example, if the 
	value was a double, 1.987023455 it might be converted to
	"1.99".

	Flow is from Model ==>> external value
	*/
	virtual VariantData convertFromModel( const VariantData& key, const VariantData& value ) = 0;

	/**
	Converts an value to a value used for the model. FOr example, a string
	might be converted to a double, so "1.99" might be converted to a 
	1.99000000.

	Flow is from external value ==>> Model
	*/
	virtual VariantData convertToModel( const VariantData& key, const VariantData& value ) = 0;

	VariantData getAppliesToKey() {
		return appliesToKey_;
	}

	void setAppliesToKey( const VariantData& val ) {
		appliesToKey_ = val;
	}
protected:
	VariantData appliesToKey_;
};


class APPLICATIONKIT_API NumericFormatter : public ValidationFormatter {
public:
	NumericFormatter(): ValidationFormatter(), numDecimalPlaces_(2){}

	virtual ~NumericFormatter(){}

	virtual VariantData convertFromModel( const VariantData& key, const VariantData& value );
	virtual VariantData convertToModel( const VariantData& key, const VariantData& value );

	uint32 getNumberOfDecimalPlaces() {
		return numDecimalPlaces_;
	}

	void setNumberOfDecimalPlaces( const uint32& val ) {
		numDecimalPlaces_ = val;
	}
protected:
	uint32 numDecimalPlaces_;
};






enum ValidationLogicOp{
	vlNone = 0,
	vlAND,
	vlOR
};


static String ValidationLogicOpNames[] = { "vlNone",
                                         "vlAND",
										 "vlOR",
										 "vlXOR" };

class ValidationResult;


class APPLICATIONKIT_API ValidationRule : public Component {
public:
	ValidationRule(): logicOp_(vlAND){}
	virtual ~ValidationRule(){}


	virtual bool exec( const VariantData& key, const VariantData& value, ValidationResult& result ) = 0;


	ValidationLogicOp getLogicOp() {
		return logicOp_;
	}

	void setLogicOp( const ValidationLogicOp& val ) {
		logicOp_ = val;
	}

	String getErrorMessage() {
		return errorMessage_;
	}

	void setErrorMessage( const String& val ) {
		errorMessage_ = val;
	}

	VariantData getAppliesToKey() {
		return appliesToKey_;
	}

	void setAppliesToKey( const VariantData& val ) {
		appliesToKey_ = val;
	}
protected:	
	ValidationLogicOp logicOp_;
	String errorMessage_;
	VariantData appliesToKey_;

};




class APPLICATIONKIT_API ValidationResult {
public:

	ValidationResult(): key(VariantData::null()),value(VariantData::null()),valid(false){}


	operator bool () const {
		return valid;
	}

	ValidationResult& operator=( const bool& rhs ) {
		valid = rhs;
		return *this;
	}


	ValidationResult& operator=( const ValidationException& rhs ) {
		valid = false;
		error = rhs.getMessage();

		return *this;
	}



	VariantData key;
	VariantData value;

	String error;

	bool valid;

	void addFailedRule( ValidationRule* rule ) {
		std::vector<ValidationRule*>::iterator found =
			std::find( failedRules.begin(), failedRules.end(), rule );
		if ( found == failedRules.end() ) {
			failedRules.push_back( rule );
		}
	}

	const std::vector<ValidationRule*>& getFailedRules() const {
		return failedRules;
	}

	void addFailedRules( const std::vector<ValidationRule*>& val ) {
		failedRules.insert( failedRules.end(), val.begin(), val.end() );
	}
protected:
	std::vector<ValidationRule*> failedRules;
};








class APPLICATIONKIT_API NullRule : public ValidationRule {
public:
	NullRule():allowsNull_(true){}
	virtual ~NullRule(){}	
	virtual bool exec( const VariantData& key, const VariantData& value, ValidationResult& result );

	bool allowsNull() {
		return allowsNull_;
	}

	void setAllowsNull( const bool& val ) {
		allowsNull_ = val;
	}
protected:
	bool allowsNull_;
};


class APPLICATIONKIT_API DataRule : public ValidationRule {
public:
	virtual ~DataRule(){}

	VariantData getData() {
		return data_;
	}

	void setData( const VariantData& val ) {
		data_ = val;
	}
protected:
	VariantData data_;
};

class APPLICATIONKIT_API MinRule : public DataRule {
public:
	virtual ~MinRule(){}	
	virtual bool exec( const VariantData& key, const VariantData& value, ValidationResult& result );
};

class APPLICATIONKIT_API MaxRule : public DataRule {
public:
	virtual ~MaxRule(){}	
	virtual bool exec( const VariantData& key, const VariantData& value, ValidationResult& result );
};


class APPLICATIONKIT_API EqualsRule : public DataRule {
public:
	virtual ~EqualsRule(){}	
	virtual bool exec( const VariantData& key, const VariantData& value, ValidationResult& result );
};


class APPLICATIONKIT_API SimilarToRule : public DataRule {
public:
	virtual ~SimilarToRule(){}	
	virtual bool exec( const VariantData& key, const VariantData& value, ValidationResult& result );
};



class APPLICATIONKIT_API ValidationRuleCollection : public ValidationRule {
public:
	virtual ~ValidationRuleCollection(){}

	ValidationRule* getRule( const uint32& i ) {
		if ( i < rules_.size() ) {
			return rules_[i];
		}
		return NULL;
	}

	void setRule( const uint32& index, ValidationRule* rule ) {
		size_t missing = (index+1) - rules_.size();
		if ( missing > 0 ) {
			rules_.resize( missing + rules_.size() );
		}
		
		Array<ValidationRule*>::iterator found = 
			std::find( rules_.begin(), rules_.end(), rule );
		//don't allow duplicate entries
		if ( found == rules_.end() ) {
			rules_[index] = rule;
		}
	}

	void insertRule( const uint32& index, ValidationRule* rule ) {
		Array<ValidationRule*>::iterator found = std::find( rules_.begin(), rules_.end(), rule );
		//don't allow duplicate entries
		if ( found == rules_.end() ) {
			rules_.insert( rules_.begin() + index, rule );
		}
	}

	void removeRule( const uint32& index )	{
		if ( index < rules_.size() ) {
			rules_.erase( rules_.begin() + index );
		}
	}

	uint32 getRuleCount() {
		return rules_.size();
	}


	virtual bool exec( const VariantData& key, const VariantData& value, ValidationResult& result );

	bool isValid( const VariantData& key, const VariantData& value, ValidationResult& result );

	String getValidationProblem() {
		return problem_;
	}

	virtual void handleEvent( Event* e );
protected:
	Array<ValidationRule*> rules_;
	String problem_;
};



enum ModelUpdate {
	muNone = 0,
	muOnValidation
};


static String ModelUpdateNames[] = { "muNone",
                                         "muOnValidation" };



class View;

#define MODEL_CLASSID		"ED88C0AD-26AB-11d4-B539-00C04F0196DA"


/**
\class Model Model.h "vcf/ApplicationKit/Model.h"
A model is the base class for storing data that can then 
be presented to the user by controls and/or views. 
The model maintains zero or more views. It can update
the views in one shot by the updateAllViews(). 

The exact kind of data store in the model is up to the implementor
but all models have some basic common characteristics.
 \li They can be emptied or cleared out by calling the empty() method.
 \li You can determine if the model has any data at all by calling
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
	@del Model::ModelValidating
	@del Model::ModelValidationFailed
	@del Model::ModelValidated
*/
class APPLICATIONKIT_API Model : public Component {
public:


	Model();

	virtual ~Model();


	enum ModelEvents{
		MODEL_CHANGED = 2000,
		MODEL_VALIDATING,
		MODEL_VALIDATIONFAILED,
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
	@delegate ModelValidating fired when the model's validate() method is called
	@event ValidationEvent
	@see validate()
	*/
	DELEGATE(ValidationDelegate,ModelValidating)


	DELEGATE(ValidationErrorDelegate,ModelValidationFailed)
	

	/**
	@delegate ModelValidating fired when the model's validate() method is called
	@event ValidationEvent
	@see validate()
	*/
	DELEGATE(EventDelegate,ModelValidated)
    
    /**
	Validate the model.
	 */
    virtual ValidationResult validate() {
		VariantData key = VariantData::null();
		VariantData value = VariantData::null();
		return validate(key,value);
	}

	/**
	Throws an exception if the validation fails.
	Call with a value and optional key for the value. If there's
	a formatter present the value may be coerced into something 
	else using the rules (if any) of the formatter. For example,
	the value passed in might be a string that represents a number.
	The string may be limited to 3 decimal places and converted to
	a double.
  
	*/
	virtual ValidationResult validate( const VariantData& key, const VariantData& value );
	
	ValidationResult validate( const VariantData& key, const String& value ) {
		VariantData v;
		v.setFromString(value);
		return validate( key, v );
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
		try {
			if ( NULL != formatter_ ) {				
				return formatter_->convertFromModel( key, getValue(key) ).toString();
			}
		}
		catch ( BasicException& e ) {
			throw ValidationException( "Invalid Formatting error: " + e.getMessage() );
		}

		return getValue(key).toString();
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
	virtual void setValueAsString( const String& value, const VariantData& key=VariantData::null() );

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

	ModelUpdate getUpdateMode() {
		return updateMode_;
	}

	void setUpdateMode( const ModelUpdate& val ) {
		updateMode_ = val;
	}

	ValidationFormatter* getFormatter() {
		return formatter_;
	}

	void setFormatter( ValidationFormatter* val ) {
		formatter_ = val;
	}


	ValidationRuleCollection* getValidator() {
		return validator_;
	}

	void setValidator( ValidationRuleCollection* val ) {
		validator_ = val;
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
	ModelUpdate updateMode_;
	ValidationFormatter* formatter_;
	ValidationRuleCollection* validator_;

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
