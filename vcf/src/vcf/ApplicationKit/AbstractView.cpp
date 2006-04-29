//AbstractView.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;


AbstractView::~AbstractView()
{
	
}

void AbstractView::updateView( Model* updatedModel )
{
	if ( NULL != viewControl_ ) {
		viewControl_->repaint();
	}
}

void AbstractView::paintView( GraphicsContext* context )
{
	//do nothing for now
}

void AbstractView::setViewModel( Model* viewModel ){
	if ( viewModel_ == viewModel ) {
		return;
	}

	viewModel_ = viewModel;
}


/**
$Id$
*/
