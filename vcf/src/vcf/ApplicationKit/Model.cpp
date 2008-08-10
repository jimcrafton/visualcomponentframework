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

VariantData Model::validate( const VariantData& key, const VariantData& value ) 
{
	
	if ( updateMode_ == muOnValidation ) {

		VariantData tmpVal = value;
		try {
			if ( NULL != formatter_ ) {				
				tmpVal = formatter_->convertFrom( key, value );
			}
		}
		catch ( BasicException& e ) {
			throw ValidationException( "Invalid Formatting error: " + e.getMessage() );
		}


		if ( NULL != validator_ ) {
			if ( !validator_->isValid( key, tmpVal ) ) {
				throw ValidationException( "Data value is invalid.\nProblem: " + validator_->getValidationProblem() );
			}
		}


		ValidationEvent e( this, MODEL_VALIDATING, key, tmpVal );
		e.validationOK = ModelValidating.empty();
		ModelValidating( &e );
		if ( !e.validationOK ) {
			throw ValidationException( e.errorMessage );
		}


		Event e2(this, MODEL_VALIDATED);
		ModelValidated( &e2 );
	}

	return value;
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

