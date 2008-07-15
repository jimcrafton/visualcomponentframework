
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "AggAbstractControl.h"
#include "AggWindowPeer.h"


using namespace VCF;

AggAbstractControl::AggAbstractControl( Control* control ) :
	control_(control),
	owningWindow_(NULL),
	enabled_(true),
	visible_(false),
	focused_(false),
	parent_(NULL),
	mouseEventsCaptured_(false)
{

}

AggAbstractControl::~AggAbstractControl()
{

}

void AggAbstractControl::create( Control* owningControl )
{
     control_ = owningControl;
}

void AggAbstractControl::destroyControl()
{

}

OSHandleID AggAbstractControl::getHandleID()
{

	return (OSHandleID) this;
}

String AggAbstractControl::getText()
{
	return "";
}

void AggAbstractControl::setText( const String& text )
{

}

void AggAbstractControl::setBounds( Rect* rect )
{
	bounds_ = *rect;
}

bool AggAbstractControl::beginSetBounds( const uint32& numberOfChildren )
{
	return true;
}

void AggAbstractControl::endSetBounds()
{

}

Rect AggAbstractControl::getBounds()
{
	return bounds_;
}

void AggAbstractControl::setVisible( const bool& visible )
{
    visible_ = visible;
}

bool AggAbstractControl::getVisible()
{

	return visible_;
}

Control* AggAbstractControl::getControl()
{
	return control_;
}

void AggAbstractControl::setControl( Control* control )
{
	control_ = control;
}

void AggAbstractControl::setCursor( Cursor* cursor )
{

}

void AggAbstractControl::setParent( Control* parent )
{
    if ( NULL == parent ) {
        parent_ = NULL;
    }
    else {
        AggAbstractControl* parentPeer = (AggAbstractControl*)parent->getPeer();
        if ( parent_ != parentPeer ) {
            if ( NULL != parent_ ) {
                parent_->removeChild( this );
            }

            parent_ = parentPeer;

            Frame* frame = parent->getParentFrame ();
            owningWindow_ = (AggWindowPeer*) frame->getPeer();

            parent_->addChild( this );
        }
    }
}


void AggAbstractControl::addChild( AggAbstractControl* child )
{
    AggControlArray::iterator found =
        std::find( childControls_.begin(), childControls_.end(), child );
    if ( found == childControls_.end() ) {
        childControls_.push_back( child );
    }
}

void AggAbstractControl::removeChild( AggAbstractControl* child )
{
    AggControlArray::iterator found =
        std::find( childControls_.begin(), childControls_.end(), child );
    if ( found != childControls_.end() ) {
        childControls_.erase( found );
    }
}

Control* AggAbstractControl::getParent()
{
    Control* result = NULL;
    if ( NULL != parent_ ) {
        result = parent_->getControl();
    }
	return result;
}

bool AggAbstractControl::isFocused()
{
	return focused_;
}

void AggAbstractControl::setFocused()
{
	focused_ = true;
}

bool AggAbstractControl::isEnabled()
{
	return enabled_;
}

void AggAbstractControl::setEnabled( const bool& enabled )
{
	enabled_ = enabled;
}

void AggAbstractControl::setFont( Font* font )
{

}

void AggAbstractControl::repaint( Rect* repaintRect, const bool& immediately )
{

}

void AggAbstractControl::keepMouseEvents()
{
	mouseEventsCaptured_ = true;
}

void AggAbstractControl::releaseMouseEvents()
{
	mouseEventsCaptured_ = false;
}

void AggAbstractControl::translateToScreenCoords( Point* pt )
{

}

void AggAbstractControl::translateFromScreenCoords( Point* pt )
{

}

void AggAbstractControl::setBorder( Border* border )
{
	repaint(NULL,true);
}

void AggAbstractControl::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	//graphicsContext->setClippingRect( childClipRect );
}

void AggAbstractControl::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	//graphicsContext->setClippingRect( oldClipRect );
}


void AggAbstractControl::paintChildren( GraphicsContext* sharedCtx )
{
    if ( childControls_.empty() ) {
        return;
    }


    //Control* control =  getControl();

    VCF_ASSERT( NULL != control_  );

    Scrollable* scrollable = control_->getScrollable();

    Rect mainBounds;

    if ( control_->getParent() ) {
		mainBounds = control_->getBounds();
		mainBounds.offset( -control_->getLeft(), -control_->getTop() );
	}
	else {
		mainBounds = control_->getClientBounds();
	}

    Rect childClipRect;
	Rect bounds;

    double originX = 0.0;
	double originY = 0.0;

	AggControlArray::iterator it = childControls_.begin();
	while ( it != childControls_.end() ) {
		AggAbstractControl* child = *it;
		if ( child->getVisible() && (NULL != child->getOwnerWindow()) ) {
		    bounds = child->getBounds();
		    childClipRect.left_ = maxVal<>(bounds.left_,mainBounds.left_);
			childClipRect.top_ = maxVal<>(bounds.top_,mainBounds.top_);
			childClipRect.right_ = minVal<>(bounds.right_,mainBounds.right_);
			childClipRect.bottom_ = minVal<>(bounds.bottom_,mainBounds.bottom_);

			childClipRect.offset( -bounds.left_, -bounds.top_ );

            Point oldOrigin = sharedCtx->getOrigin();
			originX = bounds.left_ + oldOrigin.x_;
			originY = bounds.top_ + oldOrigin.y_;
			if ( NULL != scrollable ) {
				originX += 	scrollable->getHorizontalPosition();
				originY += 	scrollable->getVerticalPosition();
			}

			sharedCtx->setOrigin( originX, originY );

            Matrix2D xfrm;
			int gcs = sharedCtx->saveState();
			sharedCtx->setCurrentTransform( xfrm );


		    child->paintPeer( sharedCtx );

		    sharedCtx->restoreState( gcs );
			sharedCtx->setOrigin( oldOrigin.x_, oldOrigin.y_ );
		}
		++it;
	}
}

void AggAbstractControl::paintPeer( GraphicsContext* sharedCtx )
{
    Control* control =  getControl();


    paintPeerControl( sharedCtx );

    control->paintBorder( sharedCtx );

    control->paint( sharedCtx );

    paintChildren( sharedCtx );


}


void AggAbstractControl::paintPeerControl( GraphicsContext* sharedCtx )
{

}

/*
void AggAbstractControl::handleMouseEvents(xcb_connection_t &connection, const xcb_generic_event_t& event)
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
*/

AggAbstractControl* AggAbstractControl::findControlForMouseEvent( Point pt )
{
	AggAbstractControl* result = NULL;
    printf( "AggAbstractControl::findControlForMouseEvent() %p\n", this );

	if ( mouseEventsCaptured() ) {
		result = this;
	}

	if ( NULL == result ) {
		AggControlArray::iterator it = childControls_.begin();
		while ( it != childControls_.end() ) {
			AggAbstractControl* child = *it;

			result = child->findControlForMouseEvent(pt);
			if ( NULL != result ) {
				break;
			}

			++it;
		}

		if ( NULL == result ) {
		    printf( "visible: %d, owner window: %p, enabled: %d\n",
                        getVisible(), getOwnerWindow(), isEnabled() );

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

