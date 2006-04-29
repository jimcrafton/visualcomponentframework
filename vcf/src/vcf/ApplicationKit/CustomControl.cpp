//CustomControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/GraphicsKit/DrawUIState.h"


using namespace VCF;

	
CustomControl::CustomControl():
	Control(),
	isLightweight_(false),
	isTransparent_(false),
	useColorForBackground_(false)
{
	peer_ =	UIToolkit::createControlPeer( this );
	peer_->create( this );

	init();
}

CustomControl::CustomControl( const bool& useHeavyweightPeer ):
	Control(),
	isLightweight_(!useHeavyweightPeer),
	isTransparent_(false),
	useColorForBackground_(false)
{
	if ( isLightweight_ ){
		peer_ = UIToolkit::createControlPeer( this, CT_LIGHTWEIGHT );
	}
	else{
		peer_ = UIToolkit::createControlPeer( this, CT_HEAVYWEIGHT );
	}

	peer_->create( this );
	init();
}

CustomControl::~CustomControl()
{
}

void CustomControl::paint(GraphicsContext * context)
{
	if ( NULL != getView() ) {
		getView()->paintView( context );
		return;
	}


	

	Rect innerBounds = getClientBounds( true );//we DO need to account for the border here

	

	if ( (!isTransparent_) || (!isLightWeight()) ){
		if ( useColorForBackground_ ) {
			context->setColor( getColor() );
			
			context->rectangle( &innerBounds );
			
			context->fillPath();		
		}
		else {	
			BackgroundState bkg;
			bkg.setEnabled( isEnabled() );
			bkg.setActive( isActive() );
			bkg.colorType_ = SYSCOLOR_FACE;	
			
			context->drawThemeBackground( &innerBounds, bkg );
		}
	}

	context->setCurrentFont( getFont() );

	Scrollable* scrollable = getScrollable();
	if ( scrollable ) {
		Rect viewBounds = context->getViewableBounds();

		Point origin = context->getOrigin();

		adjustViewableBoundsAndOriginForScrollable( context, viewBounds, origin );

		context->setOrigin( origin );

		context->setViewableBounds( viewBounds );
	}
}

void CustomControl::init()
{
	setEnabled( true );
	setVisible( true );
	setFocused();
}

bool CustomControl::isLightWeight()
{
	return isLightweight_;
}

bool CustomControl::isTransparent()
{
	return isTransparent_;
}

void CustomControl::setTransparent( const bool& transparent )
{
	isTransparent_ = transparent;
}


/**
$Id$
*/
