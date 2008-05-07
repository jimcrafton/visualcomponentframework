
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "AggWindowPeer.h"





using namespace VCF;



AggWindowPeer::AggWindowPeer( Control* control, Control* owner ) :
    AggAbstractControl(control)
{

}

Rect AggWindowPeer::getClientBounds()
{
	return clientBounds_;
}

void  AggWindowPeer::setClientBounds( Rect* bounds )
{
	clientBounds_ = *bounds;

	
}

void AggWindowPeer::close()
{
	
}

void AggWindowPeer::setFrameStyle( const FrameStyleType& frameStyle )
{
	
}

void AggWindowPeer::setFrameTopmost( const bool& isTopmost )
{
	
}

bool AggWindowPeer::isMaximized()
{
	
	return false;
}

void AggWindowPeer::setMaximized( const bool maximised )
{
	
}

bool AggWindowPeer::isMinimized()
{
	return false;
}

void AggWindowPeer::setMinimized( const bool& minimized )
{
	
}

void AggWindowPeer::restore()
{
	
}

void AggWindowPeer::setIconImage( Image* icon )
{
	
}

bool AggWindowPeer::isActiveWindow()
{
	return false;
}

/////////////////////////////////////////////////////////////////////////////
void AggWindowPeer::create( Control* owningControl )
{
	

	owningWindow_ = this;
}

void AggWindowPeer::destroyControl()
{
	
}

OSHandleID AggWindowPeer::getHandleID()
{
	return reinterpret_cast<OSHandleID>(NULL);
}

String AggWindowPeer::getText()
{
	
	return "";
}

void AggWindowPeer::setText( const String& text )
{
	
}

void AggWindowPeer::setBounds( Rect* rect )
{
	VCF_ASSERT(rect != NULL);

	
}

bool AggWindowPeer::beginSetBounds( const uint32& numberOfChildren )
{	
	return true;
}

void AggWindowPeer::endSetBounds()
{
}

Rect AggWindowPeer::getBounds()
{
	return clientBounds_;
}

void AggWindowPeer::setVisible( const bool& visible )
{
	
}

bool AggWindowPeer::getVisible()
{

	return AggAbstractControl::getVisible();
}


void AggWindowPeer::setCursor( Cursor* cursor )
{
	
}


bool AggWindowPeer::isFocused()
{
	return AggAbstractControl::isFocused();
}

void AggWindowPeer::setFocused()
{
	AggAbstractControl::setFocused();
}

bool AggWindowPeer::isEnabled()
{
	return AggAbstractControl::isEnabled();
}

void AggWindowPeer::setEnabled( const bool& enabled )
{
	AggAbstractControl::setEnabled( enabled );
}

void AggWindowPeer::setFont( Font* font )
{
	AggAbstractControl::setFont( font );
}

void AggWindowPeer::repaint( Rect* repaintRect, const bool& immediately )
{
	
}

void AggWindowPeer::keepMouseEvents()
{
	AggAbstractControl::keepMouseEvents();
}

void AggWindowPeer::releaseMouseEvents()
{
	AggAbstractControl::releaseMouseEvents();
}

void AggWindowPeer::translateToScreenCoords( Point* pt )
{
	
}

void AggWindowPeer::translateFromScreenCoords( Point* pt )
{
	
}

void AggWindowPeer::setBorder( Border* border )
{
	
}

void AggWindowPeer::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{

}

void AggWindowPeer::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{

}


void AggWindowPeer::setBorderPath( Path* path )
{

}


/**
$Id$
*/


