
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBWindowPeer.h"
#include "vcf/ApplicationKit/XCBControlContextPeer.h"

#include <sys/shm.h>

extern "C"
{
	#include <X11/XCB/xcb_icccm.h>
}

using namespace VCF;

XCBWindowPeer::XIDWindowPeerMap XCBWindowPeer::XIDWindowPeerMap_;

XCBWindowPeer::XCBWindowPeer( Control* component, Control* owner ) :
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
}

void XCBWindowPeer::close()
{
	XIDWindowPeerMap_.erase(drawable_.window.xid);
	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	XCBDestroyWindow(connection, drawable_.window);
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

		XIDWindowPeerMap_[drawable_.window.xid] = this;

		{
			context_ = XCBGCONTEXTNew( connection );
			CARD32 mask = XCBGCForeground | XCBGCGraphicsExposures;
			CARD32 values[2];
			values[0] = screen->black_pixel;
			values[1] = 0;
			XCBCreateGC( connection, context_, drawable_, mask, values );
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
		XCBChangeProperty(connection, PropModeReplace, drawable_.window,
				  WM_NAME, STRING, 8,
				  text.length(), text.ansi_c_str());
	
		XCBChangeProperty(connection, PropModeReplace, drawable_.window,
				  WM_ICON_NAME, STRING, 8,
				  text.length(), text.ansi_c_str());
    }
}

void XCBWindowPeer::setBounds( Rect* rect )
{
	VCF_ASSERT(rect != NULL);

	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	if(connection != NULL)
	{
		const CARD32 values[] = { rect->getLeft(), rect->getTop(), rect->getWidth(), rect->getHeight() };
		XCBConfigureWindow(connection, drawable_.window, CWX | CWY | CWWidth | CWHeight, values);
    }
	setClientBounds(rect);
}

bool XCBWindowPeer::beginSetBounds( const ulong32& numberOfChildren )
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
			XCBMapWindow(connection, drawable_.window);
		}
		else {
			XCBUnmapWindow(connection, drawable_.window);
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
void XCBWindowPeer::internal_handleClientMessageEvent(const XCBClientMessageEvent& event)
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

void XCBWindowPeer::internal_handleConfigureNotifyEvent(const XCBConfigureNotifyEvent& event)
{
	XIDWindowPeerMap::iterator it = XIDWindowPeerMap_.find(event.window.xid);
	if(it != XIDWindowPeerMap_.end()) {
		XCBWindowPeer *peer = it->second;
		Rect newClientBounds(0, 0, event.width, event.height);
		peer->setClientBounds(&newClientBounds);
	}
}

void XCBWindowPeer::internal_handleExposeEvent(const XCBExposeEvent& event)
{
	XIDWindowPeerMap::iterator it = XIDWindowPeerMap_.find(event.window.xid);
	if(it != XIDWindowPeerMap_.end()) {
		XCBWindowPeer *peer = it->second;
		peer->paint();
	}
}

void XCBWindowPeer::internal_handleDestroyNotify(const XCBDestroyNotifyEvent& event)
{
}

void XCBWindowPeer::paint()
{
	Rect bounds = getClientBounds();
	int width  = bounds.getWidth();
	int height = bounds.getHeight();

	if(width >0 && height > 0)
	{
		XCBConnection* connection = XCBGraphicsToolkit::getConnection();
		XCBSCREEN*     screen     = XCBGraphicsToolkit::getScreen();

		XCBFlush(connection);

		CARD8 bpp = 32; 
		CARD8 depth = XCBAuxGetDepth( connection, screen );
		XCBImage *image = XCBImageSHMCreate( connection, depth, XCBImageFormatZPixmap, NULL, width, height );

		XCBShmSegmentInfo shminfo;
		shminfo.shmseg = XCBShmSEGNew( connection );
		shminfo.shmid = shmget(IPC_PRIVATE, image->bytes_per_line * image->height, IPC_CREAT | 0777);
		shminfo.shmaddr = (BYTE*)shmat(shminfo.shmid, 0, 0);
		image->data = (BYTE*) shminfo.shmaddr;
		XCBShmAttach(connection, shminfo.shmseg, shminfo.shmid, 0);

		memset(image->data, 127, width * height * (bpp / 8));

		GraphicsContext* gc = control_->getContext();
		XCBContextPeer *contextPeer = dynamic_cast<XCBContextPeer*>(gc->getPeer());
		if(contextPeer != NULL) {
			contextPeer->internal_setImage(image);
			control_->paint(gc);
		}

		XCBImageSHMPut( connection, 
						drawable_, 
						context_, 
						image, 
						shminfo, 
						0, 
						0, 
						0, 
						0, 
						width, 
						height, 
						0);

		XCBFlush(connection);
		XCBShmDetach(connection, shminfo.shmseg);
		XCBImageSHMDestroy(image);
		shmdt(shminfo.shmaddr);
		shmctl(shminfo.shmid, IPC_RMID, 0);

		XCBFlush(connection);
	}

}

/**
$Id$
*/

