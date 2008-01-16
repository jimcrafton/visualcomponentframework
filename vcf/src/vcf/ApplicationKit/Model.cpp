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


Model::Model(): deleteVariantObjects_(false)
{
}

Model::~Model()
{

}

void Model::addView( View* view )
{
	view->setViewModel( this );
	std::vector<View*>::iterator found = std::find( views_.begin(), views_.end(), view );
	if ( found == views_.end() ) {
		views_.push_back( view );
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


/**
$Id$
*/

