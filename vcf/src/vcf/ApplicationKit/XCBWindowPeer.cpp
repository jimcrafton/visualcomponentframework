
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBWindowPeer.h"

extern "C"
{
	#include <X11/XCB/xcb_icccm.h>
}

using namespace VCF;

XCBWindowPeer::XCBWindowPeer( Control* component, Control* owner ) :
XCBAbstractControl(component)
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

Rect XCBWindowPeer::getClientBounds()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Rect();
}

void  XCBWindowPeer::setClientBounds( Rect* bounds )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::close()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::setFrameStyle( const FrameStyleType& frameStyle )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::setFrameTopmost( const bool& isTopmost )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBWindowPeer::isMaximized()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBWindowPeer::setMaximized( const bool maximised )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBWindowPeer::isMinimized()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBWindowPeer::setMinimized( const bool& minimized )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::restore()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::setIconImage( Image* icon )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBWindowPeer::isActiveWindow()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBWindowPeer::createImpl( XCBConnection* connection, XCBSCREEN* screen )
{
	if(connection != NULL)
	{
		drawable_.window = XCBWINDOWNew(connection);
		CARD32           mask = 0;
		CARD32           values[2];

		mask = XCBCWBackPixel | XCBCWEventMask ;
		values[0] = screen->white_pixel;
		values[1] = XCBEventMaskExposure | 
			        XCBEventMaskStructureNotify;


		XCBWINDOW parentWindow = screen->root;
/*		if ( NULL != owner_ ) {
			XCBDRAWABLE* parentDrawable = reinterpret_cast<XCBDRAWABLE*>(owner_->getPeer()->getHandleID());
			if(parentDrawable != NULL)
			{
				parentWindow = parentDrawable->window;
			}
		}
*/
		XCBCreateWindow (connection,       		// Connection          
						 0,                     // depth               
						 drawable_.window,      // window Id           
						 parentWindow,          // parent window       
						 0, 0,                  // x, y                
						 150, 150,              // width, height       
						 10,                    // border_width        
    					 InputOutput,           // class               
						 screen->root_visual,   // visual              
						 mask,                  // values' masks
						 values);               // values 

		XCBInternAtomCookie atom  = XCBInternAtom(connection, 0, sizeof("WM_DELETE_WINDOW")-1, "WM_DELETE_WINDOW");
		XCBInternAtomRep* atomrep = XCBInternAtomReply(connection, atom, 0);
		if(atomrep != NULL)
		{
			deleteWindowAtom_ = atomrep->atom;
			SetWMProtocols(connection, drawable_.window, 1, &deleteWindowAtom_);
		}
		::free(atomrep);
	}
}

/**
$Id$
*/

