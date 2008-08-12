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
	updateMode_(muNone),
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
	try {
		VariantData v = validate( key, value );		
		setValue( v, key );
	}
	catch ( ValidationException& e ) {
		Application::showErrorMessage( e.getMessage(), "Validation Error" );
	}

}


VariantData Model::validate( const VariantData& key, const VariantData& value ) 
{
	VariantData result = value;
	if ( updateMode_ == muOnValidation ) {

		VariantData tmpVal = value;
		try {
			if ( NULL != formatter_ ) {				
				tmpVal = formatter_->convertFrom( key, value );
			}
		}
		catch ( BasicException& e ) {

			ValidationErrorEvent errEv(this, MODEL_VALIDATIONFAILED, key, value );
			errEv.errorMessage = e.getMessage();
			errEv.state = ValidationErrorEvent::vsFormattingFailed;

			ModelValidationFailed(&errEv);
			if ( errEv.throwException ) {
				throw ValidationException( "Invalid Formatting error: " + errEv.errorMessage );
			}
			else {
				return value;
			}
		}


		if ( NULL != validator_ ) {
			if ( !validator_->isValid( key, tmpVal ) ) {

				ValidationErrorEvent errEv(this, MODEL_VALIDATIONFAILED, key, value );
				errEv.errorMessage = validator_->getValidationProblem();
				errEv.state = ValidationErrorEvent::vsValidatorRulesFailed;

				ModelValidationFailed(&errEv);
				if ( errEv.throwException ) {
					throw ValidationException( "Data value is invalid.\nProblem: " + errEv.errorMessage );
				}
				else {
					return value;
				}
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
			
			if ( errEv.throwException ) {
				throw ValidationException( errEv.errorMessage );
			}
			else {
				return value;
			}
		}


		ValidationEvent e2(this, MODEL_VALIDATED, key, tmpVal);
		ModelValidated( &e2 );
		result = tmpVal;
	}

	return result;
}


bool ValidationRuleCollection::exec( const VariantData& key, const VariantData& value )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	bool result = true;
	Array<ValidationRule*>::iterator it = rules_.begin();		

	ValidationRule* prevRule = NULL;
	while ( it != rules_.end() ) {
		ValidationRule* rule = *it;
		
		VariantData oldKey = rule->getAppliesToKey();
		rule->setAppliesToKey( appliesToKey_ );

		bool ruleRes = rule->exec( key, value );
		
		if ( it == rules_.begin() ) {
			result = ruleRes;			
		}
		else {
			switch ( prevRule->getLogicOp() ) {
				case vlAND : {
					result = result && ruleRes;
				}
				break;

				case vlOR : {
					result = result || ruleRes;
				}
				break;
			}


			if ( !result ) {
				problem_ = 	rule->getErrorMessage();	
				break;
			}
		}

		rule->setAppliesToKey( oldKey );

		prevRule = rule;
		++it;
	}

	return result;
}

bool ValidationRuleCollection::isValid( const VariantData& key, const VariantData& value ) 
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	return exec( key, value );
}


bool NullRule::exec( const VariantData& key, const VariantData& value )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	if ( !allowsNull_ && value.isNull() ) {
		return false;
	}

	return true;
}


bool MinRule::exec( const VariantData& key, const VariantData& value )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	if ( value.isInteger() ) {
		int x = value;
		int y = data_;

		return x < y;
	}
	else if ( value.isReal() ) {
		double x = value;
		double y = data_;

		return x < y;
	}

	return false;
}

bool MaxRule::exec( const VariantData& key, const VariantData& value )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	if ( value.isInteger() ) {
		int x = value;
		int y = data_;

		return x > y;
	}
	else if ( value.isReal() ) {
		double x = value;
		double y = data_;

		return x > y;
	}
	return false;
}

bool EqualsRule::exec( const VariantData& key, const VariantData& value )
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

bool SimilarToRule::exec( const VariantData& key, const VariantData& value )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return true;
	}

	return false;
}


VariantData NumericFormatter::convertTo( const VariantData& key, const VariantData& value )
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


VariantData NumericFormatter::convertFrom( const VariantData& key, const VariantData& value )
{
	if ( !appliesToKey_.isNull() && (appliesToKey_ != key) ) {
		return value;
	}


	VariantData result;

	if ( value.isString() ) {
		String s = value;
		double d = 0;
		swscanf( s.c_str(), L"%lf", &d );
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

