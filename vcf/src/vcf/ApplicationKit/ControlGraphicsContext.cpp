//ControlGraphicsContext.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;


ControlGraphicsContext::ControlGraphicsContext( Control* control )
{
	init();
	contextPeer_ = UIToolkit::createContextPeer( control );
	if ( NULL == contextPeer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit unable to create an instance of a Context Peer for ControlGraphicsContext - this is probably due to an improperly implemented UIToolkit") );
	}
	contextPeer_->setContext( this );
	setOwningControl( control );	
	Font* font = this->getCurrentFont();
	font->setPointSize( font->getPointSize() );
}

ControlGraphicsContext::~ControlGraphicsContext()
{

}

void ControlGraphicsContext::init()
{

}

void ControlGraphicsContext::setOwningControl( Control* owningComponent )
{
	owningControl_ = owningComponent;
	if ( NULL != owningControl_ ) {
		Font * controlFont = owningControl_->getFont();
		if ( NULL != controlFont ) {
			setCurrentFont( controlFont );
		}
	}
}


/**
$Id$
*/
