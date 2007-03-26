
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






extern "C" {

#include <xcb/xcb.h>
#include <xcb/shm.h>
#include <xcb/xcb_aux.h>
#include <xcb/xcb_image.h>
#include <xcb/xcb_icccm.h>

}




using namespace VCF;

XCBWindowPeer::XIDWindowPeerMap XCBWindowPeer::XIDWindowPeerMap_;

XCBWindowPeer::XCBWindowPeer( Control* control, Control* owner ) :
    XCBAbstractControl(control),
    image_(NULL)
{

}

Rect XCBWindowPeer::getClientBounds()
{
	return clientBounds_;
}

void  XCBWindowPeer::setClientBounds( Rect* bounds )
{
	clientBounds_ = *bounds;

	xcb_connection_t* connection = XCBGraphicsToolkit::getConnection();
	destroyImage(*connection);
	createImage(*connection, (uint32)clientBounds_.getWidth(), (uint32)clientBounds_.getHeight());
}

void XCBWindowPeer::close()
{
	XIDWindowPeerMap_.erase(drawable_);
	xcb_connection_t* connection = XCBGraphicsToolkit::getConnection();
	destroyImage(*connection);

	xcb_void_cookie_t voidCookie = xcb_destroy_window(connection, drawable_);
	VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
				   uiToolkit->internal_addVoidCookie(voidCookie, "xcb_destroy_window");)

	xcb_flush(connection);
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
	xcb_connection_t* connection = XCBGraphicsToolkit::getConnection();
	xcb_screen_t*     screen     = XCBGraphicsToolkit::getScreen();

	if(connection != NULL)
	{
		drawable_ = xcb_generate_id(connection);
		uint32           mask = 0;
		uint32           values[1];

		mask = XCB_CW_EVENT_MASK ;
		values[0] = XCB_EVENT_MASK_EXPOSURE |
					XCB_EVENT_MASK_STRUCTURE_NOTIFY;

		xcb_window_t parentWindow = screen->root;
/*		if ( NULL != owner_ ) {
			XCBDRAWABLE* parentDrawable = reinterpret_cast<XCBDRAWABLE*>(owner_->getPeer()->getHandleID());
			if(parentDrawable != NULL)
			{
				parentWindow = parentDrawable->window;
			}
		}
*/
		xcb_void_cookie_t voidCookie =
		xcb_create_window (connection,       		// Connection
						 0,                     // depth
						 drawable_,      // window Id
						 parentWindow,          // parent window
						 0, 0,                  // x, y
						 150, 150,              // width, height
						 10,                    // border_width
						 XCB_WINDOW_CLASS_INPUT_OUTPUT,           // class
						 screen->root_visual,   // visual
						 mask,                  // values' masks
						 values);               // values
		// For debug purposes.
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
					   uiToolkit->internal_addVoidCookie(voidCookie, "XCBCreateWindow");)

		XIDWindowPeerMap_[drawable_] = this;

		{
			context_ = xcb_generate_id( connection );
			uint32 mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
			uint32 values[2];
			values[0] = screen->black_pixel;
			values[1] = 0;
			voidCookie = xcb_create_gc( connection, context_, drawable_, mask, values );
			VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
						   uiToolkit->internal_addVoidCookie(voidCookie, "XCBCreateGC");)
		}


		xcb_intern_atom_cookie_t atom  = xcb_intern_atom(connection, 0, sizeof("WM_DELETE_WINDOW")-1, "WM_DELETE_WINDOW");
		xcb_intern_atom_reply_t* atomrep = xcb_intern_atom_reply(connection, atom, 0);
		if(atomrep != NULL)
		{
			deleteWindowAtom_ = atomrep->atom;
			set_wm_protocols(connection, drawable_, 1, &deleteWindowAtom_);
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
	xcb_connection_t* connection = XCBGraphicsToolkit::getConnection();

	if(connection != NULL)
	{
		xcb_void_cookie_t voidCookie = xcb_change_property(connection, XCB_PROP_MODE_REPLACE, drawable_,
				  WM_NAME, STRING, 8,
				  text.length(), text.ansi_c_str());
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
					   uiToolkit->internal_addVoidCookie(voidCookie, "XCBChangeProperty:WM_NAME");)

		voidCookie = xcb_change_property(connection, XCB_PROP_MODE_REPLACE, drawable_,
				  WM_ICON_NAME, STRING, 8,
				  text.length(), text.ansi_c_str());
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
					   uiToolkit->internal_addVoidCookie(voidCookie, "XCBChangeProperty:WM_ICON_NAME");)
    }
}

void XCBWindowPeer::setBounds( Rect* rect )
{
	VCF_ASSERT(rect != NULL);

	xcb_connection_t* connection = XCBGraphicsToolkit::getConnection();
	if(connection != NULL)
	{
		if(clientBounds_.getWidth() != rect->getWidth() ||
		   clientBounds_.getHeight() != rect->getHeight() ) {
			uint32 values[] = { (uint32)rect->getLeft(),
				                      (uint32)rect->getTop(),
									  (uint32)rect->getWidth(),
									  (uint32)rect->getHeight()
									};
			if(values[2] <=1 ) {
				values[2] = 1;
			}
			if(values[3] <=1 ) {
				values[3] = 1;
			}

			xcb_void_cookie_t voidCookie = xcb_configure_window(connection,
														  drawable_,
														  XCB_CONFIG_WINDOW_X | XCB_CONFIG_WINDOW_Y |
														  XCB_CONFIG_WINDOW_WIDTH | XCB_CONFIG_WINDOW_HEIGHT,
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
	xcb_connection_t* connection = XCBGraphicsToolkit::getConnection();
	if(connection != NULL) {
		if(visible) {
			xcb_void_cookie_t voidCookie = xcb_map_window(connection, drawable_);
			VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
				           uiToolkit->internal_addVoidCookie(voidCookie, Format("XCBMapWindow"));)
		}
		else {
			xcb_void_cookie_t voidCookie = xcb_unmap_window(connection, drawable_);
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

}

void XCBWindowPeer::postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect )
{

}

////
void XCBWindowPeer::internal_handleClientMessageEvent(xcb_connection_t &connection, const xcb_client_message_event_t& event)
{
	XIDWindowPeerMap::iterator it = XIDWindowPeerMap_.find(event.window);
	if(it != XIDWindowPeerMap_.end()) {
		XCBWindowPeer *peer = it->second;
		if(event.data.data32[0] == peer->deleteWindowAtom_) {
			Window *window = dynamic_cast<Window*>(peer->control_);
			if(window != NULL)
			{
				window->close();
			}
		}
	}
}

void XCBWindowPeer::internal_handleConfigureNotifyEvent(xcb_connection_t &connection, const xcb_configure_notify_event_t& event)
{
	XIDWindowPeerMap::iterator it = XIDWindowPeerMap_.find(event.window);
	if(it != XIDWindowPeerMap_.end()) {
		XCBWindowPeer *peer = it->second;
		Rect oldClientBounds = peer->getClientBounds();
		if(event.width != oldClientBounds.getWidth() || event.height != oldClientBounds.getHeight() ) {
			Rect newClientBounds(0, 0, event.width, event.height);
			peer->setClientBounds(&newClientBounds);
		}
	}
}

void XCBWindowPeer::internal_handleExposeEvent(xcb_connection_t &connection, const xcb_expose_event_t& event)
{
	XIDWindowPeerMap::iterator it = XIDWindowPeerMap_.find(event.window);
	if(it != XIDWindowPeerMap_.end()) {
		XCBWindowPeer *peer = it->second;
		peer->paint(connection,event);
	}
}

void XCBWindowPeer::internal_handleDestroyNotify(xcb_connection_t &connection, const xcb_destroy_notify_event_t& event)
{
}

void XCBWindowPeer::createImage (xcb_connection_t &connection, int width, int height)
{
	image_ = NULL;
	if(width >0 && height > 0)
	{
        //! \note perhaps screen should be passed to this function as well?
		xcb_screen_t* screen = XCBGraphicsToolkit::getScreen();

		xcb_flush(&connection);

        static unsigned char format = 0;
        if ( format == 0 ) {
            xcb_shm_query_version_reply_t *rep;
            rep = xcb_shm_query_version_reply( &connection, xcb_shm_query_version (&connection), NULL );
            if ( NULL == rep ) {
                format = XCB_IMAGE_FORMAT_Z_PIXMAP;
            }
            else {
                if ( rep->shared_pixmaps && (rep->major_version > 1 || rep->minor_version > 0) ) {
                    format = rep->pixmap_format;
                }
                else {
                    format = XCB_IMAGE_FORMAT_Z_PIXMAP;
                }
            }
        }

		unsigned char depth = xcb_aux_get_depth( &connection, screen );
		image_ = xcb_image_shm_create( &connection, depth, format, NULL, width, height );
		shminfo_.shmseg = xcb_generate_id( &connection );
		shminfo_.shmid = shmget(IPC_PRIVATE, image_->bytes_per_line * image_->height, IPC_CREAT | 0777);
		shminfo_.shmaddr = (unsigned char*)shmat(shminfo_.shmid, 0, 0);
		image_->data = (unsigned char*) shminfo_.shmaddr;
		xcb_void_cookie_t voidCookie = xcb_shm_attach(&connection, shminfo_.shmseg, shminfo_.shmid, 0);
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
					   uiToolkit->internal_addVoidCookie(voidCookie,
														 Format("XCBShmAttach %i, %i") % width % height);)
		xcb_flush(&connection);
	}
}

void XCBWindowPeer::destroyImage(xcb_connection_t &connection)
{
	if(image_ != NULL) {
		xcb_void_cookie_t voidCookie = xcb_shm_detach(&connection, shminfo_.shmseg);
		VCF_DEBUG_CODE(XCBUIToolkit *uiToolkit = (XCBUIToolkit*)UIToolkit::internal_getDefaultUIToolkit();
			           uiToolkit->internal_addVoidCookie(voidCookie, "XCBShmDetach");)

		xcb_image_shm_destroy(image_);

		shmctl(shminfo_.shmid, IPC_RMID, 0);
		shmdt(shminfo_.shmaddr);
		xcb_flush(&connection);
		image_ = NULL;
	}
}

void XCBWindowPeer::setBorderPath( Path* path )
{

}

void XCBWindowPeer::paint(xcb_connection_t &connection, const xcb_expose_event_t& event )
{
    GraphicsContext* gc = control_->getContext();
	XCBContextPeer *contextPeer = dynamic_cast<XCBContextPeer*>(gc->getPeer());
	if(contextPeer != NULL) {
		VCF::XCBSurface surf;
		surf.context = &context_;
		surf.drawable = &drawable_;
		surf.drawableImage = image_;

		contextPeer->setContextID( (VCF::OSHandleID)&surf );



		control_->paint(gc);
	}


	xcb_image_shm_put( &connection,
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

	xcb_flush(&connection);
}

/**
$Id$
*/

