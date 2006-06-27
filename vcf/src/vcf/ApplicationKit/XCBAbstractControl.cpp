
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBAbstractControl.h"
//#include "vcf/ApplicationKit/XCBControlContextPeer.h"

//#include <sys/shm.h>

using namespace VCF;
/*
class XCBAbstractControl::XCBControlMapImpl
{
public:
	typedef std::map<CARD32, XCBAbstractControl*> XCBDrawableControlMap;

	void registerControl( XCBWINDOW& window, XCBAbstractControl* control ) {
		map_[window.xid] = control;
	}
	void unRegisterControl( XCBWINDOW& window )
	{
		XCBDrawableControlMap::iterator it = map_.find(window.xid);
		map_.erase(it);
	}
	XCBAbstractControl* getControl(XCBWINDOW& window)
	{
		XCBAbstractControl* control = NULL;
		XCBDrawableControlMap::iterator it = map_.find(window.xid);
		if( it != map_.end() ) {
			control = it->second;	
		}
		return control;
	}

protected:
	XCBDrawableControlMap map_;
};

VCF::SmartPtr<XCBAbstractControl::XCBControlMapImpl>::Scoped XCBAbstractControl::controlMap_;
*/

XCBAbstractControl::XCBAbstractControl( Control* control ) :
control_(control)
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

XCBAbstractControl::~XCBAbstractControl()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::create( Control* owningControl )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::destroyControl()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

OSHandleID XCBAbstractControl::getHandleID()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0;
}

String XCBAbstractControl::getText()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return "";
}

void XCBAbstractControl::setText( const String& text )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::setBounds( Rect* rect )
{
	bounds_ = *rect;
}

bool XCBAbstractControl::beginSetBounds( const uint32& numberOfChildren )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return true;
}

void XCBAbstractControl::endSetBounds()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

Rect XCBAbstractControl::getBounds()
{
	return bounds_;
}

void XCBAbstractControl::setVisible( const bool& visible )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBAbstractControl::getVisible()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

Control* XCBAbstractControl::getControl()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

void XCBAbstractControl::setControl( Control* component )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::setCursor( Cursor* cursor )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::setParent( Control* parent )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

Control* XCBAbstractControl::getParent()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

bool XCBAbstractControl::isFocused()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBAbstractControl::setFocused()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBAbstractControl::isEnabled()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBAbstractControl::setEnabled( const bool& enabled )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::setFont( Font* font )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::repaint( Rect* repaintRect, const bool& immediately )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::keepMouseEvents()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::releaseMouseEvents()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::translateToScreenCoords( Point* pt )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::translateFromScreenCoords( Point* pt )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::setBorder( Border* border )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

/**
$Id$
*/

