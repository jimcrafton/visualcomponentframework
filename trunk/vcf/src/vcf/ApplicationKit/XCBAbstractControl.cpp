
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
control_(control),
owningWindow_(NULL),
enabled_(false),
visible_(false),
focused_(false),
parent_(NULL),
mouseEventsCaptured_(false)
{

}

XCBAbstractControl::~XCBAbstractControl()
{

}

void XCBAbstractControl::create( Control* owningControl )
{

}

void XCBAbstractControl::destroyControl()
{

}

OSHandleID XCBAbstractControl::getHandleID()
{

	return (OSHandleID) this;
}

String XCBAbstractControl::getText()
{
	return "";
}

void XCBAbstractControl::setText( const String& text )
{

}

void XCBAbstractControl::setBounds( Rect* rect )
{
	bounds_ = *rect;
}

bool XCBAbstractControl::beginSetBounds( const uint32& numberOfChildren )
{
	return true;
}

void XCBAbstractControl::endSetBounds()
{

}

Rect XCBAbstractControl::getBounds()
{
	return bounds_;
}

void XCBAbstractControl::setVisible( const bool& visible )
{
    visible_ = visible;
}

bool XCBAbstractControl::getVisible()
{

	return visible_;
}

Control* XCBAbstractControl::getControl()
{
	return control_;
}

void XCBAbstractControl::setControl( Control* control )
{
	control_ = control;
}

void XCBAbstractControl::setCursor( Cursor* cursor )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBAbstractControl::setParent( Control* parent )
{
    if ( NULL == parent ) {
        parent_ = NULL;
    }
    else {
        XCBAbstractControl* parentPeer = (XCBAbstractControl*)parent->getPeer();
        if ( parent_ != parentPeer ) {
            if ( NULL != parent_ ) {
                parent_->removeChild( this );
            }

            parent_ = parentPeer;

            Frame* frame = parent->getParentFrame ();
            owningWindow_ = (XCBWindowPeer*) frame->getPeer();

            parent_->addChild( this );
        }
    }
}


void XCBAbstractControl::addChild( XCBAbstractControl* child )
{
    XCBControlArray::iterator found =
        std::find( childControls_.begin(), childControls_.end(), child );
    if ( found == childControls_.end() ) {
        childControls_.push_back( child );
    }
}

void XCBAbstractControl::removeChild( XCBAbstractControl* child )
{
    XCBControlArray::iterator found =
        std::find( childControls_.begin(), childControls_.end(), child );
    if ( found != childControls_.end() ) {
        childControls_.erase( found );
    }
}

Control* XCBAbstractControl::getParent()
{
    Control* result = NULL;
    if ( NULL != parent_ ) {
        result = parent_->getControl();
    }
	return result;
}

bool XCBAbstractControl::isFocused()
{
	return focused_;
}

void XCBAbstractControl::setFocused()
{
	focused_ = true;
}

bool XCBAbstractControl::isEnabled()
{
	return enabled_;
}

void XCBAbstractControl::setEnabled( const bool& enabled )
{
	enabled_ = enabled;
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
	mouseEventsCaptured_ = true;
}

void XCBAbstractControl::releaseMouseEvents()
{
	mouseEventsCaptured_ = false;
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
	repaint(NULL,true);
}

void XCBAbstractControl::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	//graphicsContext->setClippingRect( childClipRect );
}

void XCBAbstractControl::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	//graphicsContext->setClippingRect( oldClipRect );
}

void XCBAbstractControl::paintChildren( xcb_connection_t &connection, const xcb_expose_event_t& event, GraphicsContext* sharedCtx )
{
	XCBControlArray::iterator it = childControls_.begin();
	while ( it != childControls_.end() ) {
		XCBAbstractControl* child = *it;
		if ( child->getVisible() && (NULL != child->getOwnerWindow()) ) {
			Control* childControl =  child->getControl();
			childControl->paint( sharedCtx );
			
			paintChildren( connection, event, sharedCtx );			
		}
		++it;
	}
}

void XCBAbstractControl::handleMouseEvents(xcb_connection_t &connection, const xcb_generic_event_t& event)
{
	switch ( event.response_type ) {
		case XCB_BUTTON_PRESS : {
			const xcb_button_press_event_t* ev = (const xcb_button_press_event_t*)&event;
		}
		break;
		
		case XCB_BUTTON_RELEASE : {
			const xcb_button_release_event_t* ev = (const xcb_button_release_event_t*)&event;
		}
		break;
		
		case XCB_MOTION_NOTIFY : {
			const xcb_motion_notify_event_t* ev = (const xcb_motion_notify_event_t*)&event;
		}
		break;
		
		case XCB_ENTER_NOTIFY : {
			const xcb_enter_notify_event_t* ev = (const xcb_enter_notify_event_t*)&event;
		}
		break;
		
		case XCB_LEAVE_NOTIFY : {
			const xcb_leave_notify_event_t* ev = (const xcb_leave_notify_event_t*)&event;
		}
		break;
	}	
}

XCBAbstractControl* XCBAbstractControl::findControlForMouseEvent( Point pt )
{
	XCBAbstractControl* result = NULL;
	
	if ( mouseEventsCaptured() ) {
		result = this;
	}
	
	if ( NULL == result ) {
		XCBControlArray::iterator it = childControls_.begin();
		while ( it != childControls_.end() ) {
			XCBAbstractControl* child = *it;
			
			result = child->findControlForMouseEvent(pt);
			if ( NULL != result ) {
				break;
			}
			
			++it;
		}
		
		if ( NULL == result ) {
			if ( getVisible() && (NULL != getOwnerWindow()) && isEnabled() ) {
				
				if ( bounds_.containsPt( &pt ) ) {
					result = this;
				}
			}
		}
	}
	
	return result;
}
/**
$Id$
*/

