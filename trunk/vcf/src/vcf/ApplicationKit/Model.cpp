//Model.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Model.h
#include "vcf/ApplicationKit/ApplicationKit.h"

#include <algorithm>

using namespace VCF;


Model::Model(): 
	deleteVariantObjects_(false),
	updateFlags_(muDisplayErrorIfInvalid),
	formatter_(NULL),
	validator_(NULL)
{
}

Model::~Model()
{

}

void Model::addView( View* view )
{	
	std::vector<View*>::iterator found = std::find( views_.begin(), views_.end(), view );
	if ( found == views_.end() ) {		
		views_.push_back( view );
		view->setViewModel( this );
	}
}

void Model::removeView( View* view )
{
	std::vector<View*>::iterator found = std::find( views_.begin(), views_.end(), view );
	if ( found != views_.end() ) {
		views_.erase( found );
		view->setViewModel( NULL );
	}
}

void Model::updateAllViews()
{
	std::vector<View*>::iterator it = views_.begin();
	while ( it != views_.end() ) {
		View* view = *it;
		view->updateView( this );
		it++;
	}
}

void Model::setValueAsString( const String& value, const VariantData& key )
{
	
	ValidationResult v = validate( key, value );
	if ( v || (updateFlags_ & muAllowsInvalidData) ) {
		setValue( v.value, key );
	}
	
	if ( !v && (updateFlags_ & muUsesValidation) && (updateFlags_ & muDisplayErrorIfInvalid) ) {	
		Application::showErrorMessage( v.error, "Validation Error" );
	}
}


ValidationResult Model::validate( const VariantData& key, const VariantData& value ) 
{
	ValidationResult result;

	result.value = value;
	result.key = key;

	if ( updateFlags_ & muUsesValidation ) {

		VariantData tmpVal = value;
		if ( NULL != formatter_ ) {
			try {				
				tmpVal = formatter_->convertToModel( key, value );				
			}
			catch ( BasicException& e ) {

				ValidationErrorEvent errEv(this, MODEL_VALIDATIONFAILED, key, value );
				errEv.errorMessage = e.getMessage();
				errEv.state = ValidationErrorEvent::vsFormattingFailed;

				ModelValidationFailed(&errEv);
				
				result.error = errEv.errorMessage;

				return result;			
			}
		}


		if ( NULL != validator_ ) {
			if ( !validator_->isValid( key, tmpVal, result ) ) {

				ValidationErrorEvent errEv(this, MODEL_VALIDATIONFAILED, key, value );
				errEv.errorMessage = validator_->getValidationProblem();
				errEv.state = ValidationErrorEvent::vsValidatorRulesFailed;

				ModelValidationFailed(&errEv);

				result.error = errEv.errorMessage;
				
				return result;				
			}
		}


		ValidationEvent e( this, MODEL_VALIDATING, key, tmpVal );
		e.validationOK = ModelValidating.empty();
		ModelValidating( &e );
		if ( !e.validationOK ) {

			ValidationErrorEvent errEv(this, MODEL_VALIDATIONFAILED, key, value );
			errEv.errorMessage = e.errorMessage;
			errEv.state = ValidationErrorEvent::vsValidatingFailed;

			ModelValidationFailed(&errEv);
			
			result.error = errEv.errorMessage;

			return result;			
		}


		ValidationEvent e2(this, MODEL_VALIDATED, key, tmpVal);		
		ModelValidated( &e2 );
		result.value = tmpVal;
		result.valid = true;
	}
	else {
		result.valid = true;
	}

	return result;
}


bool ValidationRuleCollection::exec( const VariantData& key, const VariantData& value, ValidationResult& result )
{
	problem_ = "";	

	bool retVal = true;
	Array<ValidationRule*>::iterator it = rules_.begin();		

	ValidationRule* prevRule = NULL;
	while ( it != rules_.end() ) {
		ValidationRule* rule = *it;
		
		VariantData oldKey = rule->getAppliesToKey();

		if ( !appliesToKey_.isNull() && !appliesToKey_.isUndefined()  ) {
			rule->setAppliesToKey( appliesToKey_ );
		}

		

		bool ruleRes = false;
		try {
			ruleRes = rule->exec( key, value, result );
		}
		catch (...) {
			ruleRes = false;
		}
		
		if ( !ruleRes ) {
			result.addFailedRule( rule );
		}

		if ( it == rules_.begin() ) {
			retVal = ruleRes;			
		}
		else {
			switch ( prevRule->getLogicOp() ) {
				case vlAND : {
					retVal = retVal && ruleRes;
				}
				break;

				case vlOR : {
					retVal = retVal || ruleRes;
				}
				break;
			}
		}

		if ( !problem_.empty() ) {
			problem_ += "\n";
		}
		problem_ += rule->getErrorMessage();

		if ( !appliesToKey_.isNull() && !appliesToKey_.isUndefined()  ) {
			rule->setAppliesToKey( oldKey );
		}
			

		prevRule = rule;
		++it;
	}

	return retVal;
}

bool ValidationRuleCollection::isValid( const VariantData& key, const VariantData& value, ValidationResult& result ) 
{
	return exec( key, value, result );
}

void ValidationRuleCollection::handleEvent( Event* event )
{
	ValidationRule::handleEvent( event );
	switch ( event->getType() ){
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)event;
			Component* child = ev->getChildComponent();
			ValidationRule* item = dynamic_cast<ValidationRule*>(child);
			if ( NULL != item ) {
				insertRule( getRuleCount(), item );				
			}
		}
		break;
	}
}

bool NullRule::exec( const VariantData& key, const VariantData& value, ValidationResult& result )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	if ( !allowsNull_ && value.isNull() ) {
		return false;
	}

	if ( !allowsNull_ && value.isString() ) {
		String s = value;
		return !s.empty();
	}

	return true;
}


bool MinRule::exec( const VariantData& key, const VariantData& value, ValidationResult& result )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	if ( value.isReal() ) {
		double x = value;
		double y = data_;

		return x < y;
	}
	else {
		int x = value;
		int y = data_;

		return x < y; 
	}

	return false;
}

bool MaxRule::exec( const VariantData& key, const VariantData& value, ValidationResult& result )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}
	try {		
		if ( value.isReal() ) {
			double x = value;
			double y = data_;
			
			return x > y;
		}
		else {
			int x = value;
			int y = data_;
			
			return x > y;
		}
	}
	catch (...) {
		return false;
	}

	return false;
}

bool EqualsRule::exec( const VariantData& key, const VariantData& value, ValidationResult& result )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	if ( value.isInteger() ) {
		int x = value;
		int y = data_;

		return x == y;
	}
	else if ( value.isReal() ) {
		double x = value;
		double y = data_;

		return x == y;
	}

	return value == data_;
}

bool SimilarToRule::exec( const VariantData& key, const VariantData& value, ValidationResult& result )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	if ( data_.isString() && value.isString() ) {		
		String s1 = data_;
		String s2 = value;

		return s2.find( s1 ) != String::npos;
	}

	return false;
}


VariantData NumericFormatter::convertFromModel( const VariantData& key, const VariantData& value )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return value;
	}

	VariantData result;

	if ( value.isReal() ) {
		char tmp[256];
		sprintf( tmp, "%%0.%df", numDecimalPlaces_ );
		result = Format( String(tmp) ) %  value.DblVal;
	}
	else if ( value.isString() ) {
		double d = value;
		char tmp[256];
		sprintf( tmp, "%%0.%df", numDecimalPlaces_ );
		result = Format( String(tmp) ) %  d;
	}
	else {
		result = value;
	}

	return result;
}


VariantData NumericFormatter::convertToModel( const VariantData& key, const VariantData& value )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return value;
	}


	VariantData result;

	if ( value.isString() ) {
		//String s = value;
		double d = value;
		//swscanf( s.c_str(), L"%lf", &d );
		result = d;
	}
	else {
		result = value;
	}

	return result;
}


/**
$Id$
*/

