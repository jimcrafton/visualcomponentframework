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





bool NullRule::exec( const VariantData& value )
{
	if ( !allowsNull_ && value.isNull() ) {
		return false;
	}

	return true;
}


bool MinRule::exec( const VariantData& value )
{
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

bool MaxRule::exec( const VariantData& value )
{
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

bool EqualsRule::exec( const VariantData& value )
{
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

bool SimilarToRule::exec( const VariantData& value )
{
	return false;
}


VariantData NumericFormatter::convertTo( const VariantData& value )
{
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


VariantData NumericFormatter::convertFrom( const VariantData& value )
{
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

