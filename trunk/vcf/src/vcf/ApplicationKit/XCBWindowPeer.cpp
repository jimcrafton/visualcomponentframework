
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBWindowPeer.h"
#include "vcf/ApplicationKit/XCBControlContextPeer.h"

#include <sys/ipc.h>
#include <sys/shm.h>


#define X_H
#include <X11/XCB/xcb.h>




extern "C" {

#include <X11/XCB/shm.h>
#include <X11/XCB/xcb_aux.h>
#include <X11/XCB/xcb_image.h>
#include <X11/XCB/xcb_icccm.h>

}


using namespace VCF;

XCBWindowPeer::XIDWindowPeerMap XCBWindowPeer::XIDWindowPeerMap_;

XCBWindowPeer::XCBWindowPeer( Control* component, Control* owner ) :
image_(NULL),
control_(component)
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

Rect XCBWindowPeer::getClientBounds()
{
	return clientBounds_;
}

void  XCBWindowPeer::setClientBounds( Rect* bounds )
{
	clientBounds_ = *bounds;

	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	destroyImage(*connection);
	createImage(*connection, (CARD32)clientBounds_.getWidth(), (CARD32)clientBounds_.getHeight());
}

void XCBWindowPeer::close()
{
	XIDWindowPeerMap_.erase(drawable_.window.xid);
	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	destroyImage(*connection);

	XCBVoidCookie voidCookie = XCBDestroyWindow(connection, drawable_.window);
	VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
				   uiToolkit->internal_addVoidCookie(voidCookie, "XCBDestroyWindow");)

	XCBFlush(connection);
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

/////////////////////////////////////////////////////////////////////////////
void XCBWindowPeer::create( Control* owningControl )
{
	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	XCBSCREEN*     screen     = XCBGraphicsToolkit::getScreen();

	if(connection != NULL)
	{
		drawable_.window = XCBWINDOWNew(connection);
		CARD32           mask = 0;
		CARD32           values[1];

		mask = XCBCWEventMask ;
		values[0] = XCBEventMaskExposure | 
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
		XCBVoidCookie voidCookie = 
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
		// For debug purposes.
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
					   uiToolkit->internal_addVoidCookie(voidCookie, "XCBCreateWindow");)

		XIDWindowPeerMap_[drawable_.window.xid] = this;

		{
			context_ = XCBGCONTEXTNew( connection );
			CARD32 mask = XCBGCForeground | XCBGCGraphicsExposures;
			CARD32 values[2];
			values[0] = screen->black_pixel;
			values[1] = 0;
			voidCookie = XCBCreateGC( connection, context_, drawable_, mask, values );
			VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
						   uiToolkit->internal_addVoidCookie(voidCookie, "XCBCreateGC");)
		}


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

void XCBWindowPeer::destroyControl()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

OSHandleID XCBWindowPeer::getHandleID()
{
	return reinterpret_cast<OSHandleID>(&drawable_);
}

String XCBWindowPeer::getText()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return "";
}

void XCBWindowPeer::setText( const String& text )
{
	XCBConnection* connection = XCBGraphicsToolkit::getConnection();

	if(connection != NULL)
	{
		XCBVoidCookie voidCookie = XCBChangeProperty(connection, PropModeReplace, drawable_.window,
				  WM_NAME, STRING, 8,
				  text.length(), text.ansi_c_str());
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
					   uiToolkit->internal_addVoidCookie(voidCookie, "XCBChangeProperty:WM_NAME");)

		voidCookie = XCBChangeProperty(connection, PropModeReplace, drawable_.window,
				  WM_ICON_NAME, STRING, 8,
				  text.length(), text.ansi_c_str());
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
					   uiToolkit->internal_addVoidCookie(voidCookie, "XCBChangeProperty:WM_ICON_NAME");)
    }
}

void XCBWindowPeer::setBounds( Rect* rect )
{
	VCF_ASSERT(rect != NULL);

	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	if(connection != NULL)
	{
		if(clientBounds_.getWidth() != rect->getWidth() ||
		   clientBounds_.getHeight() != rect->getHeight() ) {
			CARD32 values[] = { (CARD32)rect->getLeft(), 
				                      (CARD32)rect->getTop(), 
									  (CARD32)rect->getWidth(), 
									  (CARD32)rect->getHeight() 
									};
			if(values[2] <=1 ) {
				values[2] = 1;
			}
			if(values[3] <=1 ) {
				values[3] = 1;
			}

			XCBVoidCookie voidCookie = XCBConfigureWindow(connection, 
														  drawable_.window, 
														  CWX | CWY | CWWidth | CWHeight, 
														  values);
			VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
				           uiToolkit->internal_addVoidCookie(voidCookie, 
															 Format("XCBConfigureWindow %i, %i, %i, %i") % values[0] %
																									       values[1] %
																										   values[2] %
																										   values[3]);)
			setClientBounds(rect);
		}
    }
}

bool XCBWindowPeer::beginSetBounds( const uint32& numberOfChildren )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return true;
}

void XCBWindowPeer::endSetBounds()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

Rect XCBWindowPeer::getBounds()
{
	return clientBounds_;
}

void XCBWindowPeer::setVisible( const bool& visible )
{
	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	if(connection != NULL) {
		if(visible) {
			XCBVoidCookie voidCookie = XCBMapWindow(connection, drawable_.window);
			VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
				           uiToolkit->internal_addVoidCookie(voidCookie, Format("XCBMapWindow"));)
		}
		else {
			XCBVoidCookie voidCookie = XCBUnmapWindow(connection, drawable_.window);
			VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
						   uiToolkit->internal_addVoidCookie(voidCookie, Format("XCBUnmapWindow"));)
		}
    }
}

bool XCBWindowPeer::getVisible()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

Control* XCBWindowPeer::getControl()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

void XCBWindowPeer::setControl( Control* component )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::setCursor( Cursor* cursor )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::setParent( Control* parent )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

Control* XCBWindowPeer::getParent()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

bool XCBWindowPeer::isFocused()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBWindowPeer::setFocused()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBWindowPeer::isEnabled()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBWindowPeer::setEnabled( const bool& enabled )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::setFont( Font* font )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::repaint( Rect* repaintRect, const bool& immediately )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::keepMouseEvents()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::releaseMouseEvents()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::translateToScreenCoords( Point* pt )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::translateFromScreenCoords( Point* pt )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::setBorder( Border* border )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBWindowPeer::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

////
void XCBWindowPeer::internal_handleClientMessageEvent(XCBConnection &connection, const XCBClientMessageEvent& event)
{
	XIDWindowPeerMap::iterator it = XIDWindowPeerMap_.find(event.window.xid);
	if(it != XIDWindowPeerMap_.end()) {
		XCBWindowPeer *peer = it->second;
		if(event.data.data32[0] == peer->deleteWindowAtom_.xid) {
			Window *window = dynamic_cast<Window*>(peer->control_);
			if(window != NULL)
			{
				window->close();
			}
		}
	}
}

void XCBWindowPeer::internal_handleConfigureNotifyEvent(XCBConnection &connection, const XCBConfigureNotifyEvent& event)
{
	XIDWindowPeerMap::iterator it = XIDWindowPeerMap_.find(event.window.xid);
	if(it != XIDWindowPeerMap_.end()) {
		XCBWindowPeer *peer = it->second;
		Rect oldClientBounds = peer->getClientBounds();
		if(event.width != oldClientBounds.getWidth() || event.height != oldClientBounds.getHeight() ) {
			Rect newClientBounds(0, 0, event.width, event.height);
			peer->setClientBounds(&newClientBounds);
		}
	}
}

void XCBWindowPeer::internal_handleExposeEvent(XCBConnection &connection, const XCBExposeEvent& event)
{
	XIDWindowPeerMap::iterator it = XIDWindowPeerMap_.find(event.window.xid);
	if(it != XIDWindowPeerMap_.end()) {
		XCBWindowPeer *peer = it->second;
		peer->paint(connection);
	}
}

void XCBWindowPeer::internal_handleDestroyNotify(XCBConnection &connection, const XCBDestroyNotifyEvent& event)
{
}

void XCBWindowPeer::createImage (XCBConnection &connection, int width, int height)
{
	image_ = NULL;
	if(width >0 && height > 0)
	{
        //! \note perhaps screen should be passed to this function as well?
		XCBSCREEN* screen = XCBGraphicsToolkit::getScreen();

		XCBFlush(&connection);

		CARD8 depth = XCBAuxGetDepth( &connection, screen );
		image_ = XCBImageSHMCreate( &connection, depth, XCBImageFormatZPixmap, NULL, width, height );
		shminfo_.shmseg = XCBShmSEGNew( &connection );
		shminfo_.shmid = shmget(IPC_PRIVATE, image_->bytes_per_line * image_->height, IPC_CREAT | 0777);
		shminfo_.shmaddr = (BYTE*)shmat(shminfo_.shmid, 0, 0);
		image_->data = (BYTE*) shminfo_.shmaddr;
		XCBVoidCookie voidCookie = XCBShmAttach(&connection, shminfo_.shmseg, shminfo_.shmid, 0);
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
					   uiToolkit->internal_addVoidCookie(voidCookie, 
														 Format("XCBShmAttach %i, %i") % width % height);)
		XCBFlush(&connection);
	}
}

void XCBWindowPeer::destroyImage(XCBConnection &connection)
{
	if(image_ != NULL) {
		XCBVoidCookie voidCookie = XCBShmDetach(&connection, shminfo_.shmseg);
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
			           uiToolkit->internal_addVoidCookie(voidCookie, "XCBShmDetach");)

		XCBImageSHMDestroy(image_);

		shmctl(shminfo_.shmid, IPC_RMID, 0);
		shmdt(shminfo_.shmaddr);
		XCBFlush(&connection);
		image_ = NULL;
	}
}

void XCBWindowPeer::paint(XCBConnection &connection)
{
	GraphicsContext* gc = control_->getContext();
	XCBContextPeer *contextPeer = dynamic_cast<XCBContextPeer*>(gc->getPeer());
	if(contextPeer != NULL) {
		memset(image_->data, 127, image_->bytes_per_line * image_->height);

		contextPeer->internal_setImage(image_);
		control_->paint(gc);
	}

	/////////////////////////////////////////////////////////////////////
    agg::rendering_buffer rbuf(image_->data, 
                               image_->width, 
                               image_->height, 
                               image_->bytes_per_line);
    pixfmt pixf(rbuf);
    unsigned i;
    for(i = 0; i < pixf.height()/2; ++i)
    {
        pixf.copy_pixel(i, i, agg::rgba8(127, 200, 98));
    }
	/////////////////////////////////////////////////////////////////////

	XCBImageSHMPut( &connection, 
					drawable_, 
					context_, 
					image_, 
					shminfo_, 
					0, 
					0, 
					0, 
					0, 
					image_->width, 
					image_->height, 
					0 );

	XCBFlush(&connection);
}

/**
$Id$
*/

