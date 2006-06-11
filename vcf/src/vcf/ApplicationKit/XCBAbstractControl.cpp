
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/XCBAbstractControl.h"

using namespace VCF;

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

	XCBDrawableControlMap map_;
};

VCF::SmartPtr<XCBAbstractControl::XCBControlMapImpl>::Scoped XCBAbstractControl::controlMap_;

XCBAbstractControl::XCBAbstractControl( Control* control ) :
control_(control)
{
	if( controlMap_ == NULL ) {
		controlMap_.reset(new XCBControlMapImpl);
	}
}

XCBAbstractControl::~XCBAbstractControl()
{
	controlMap_->unRegisterControl( drawable_.window );
}

void XCBAbstractControl::create( Control* owningControl )
{
	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	XCBSCREEN*     screen     = XCBGraphicsToolkit::getScreen();

	createImpl( connection, screen );

	controlMap_->registerControl( drawable_.window, this );
}

void XCBAbstractControl::destroyControl()
{
	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	XCBDestroyWindow(connection, drawable_.window);
}

OSHandleID XCBAbstractControl::getHandleID()
{
	return reinterpret_cast<OSHandleID>(&drawable_);
}

String XCBAbstractControl::getText()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return "";
}

void XCBAbstractControl::setText( const String& text )
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

void XCBAbstractControl::setBounds( Rect* rect )
{
	VCF_ASSERT(rect != NULL);

	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	if(connection != NULL)
	{
		const CARD32 values[] = { rect->getLeft(), rect->getTop(), rect->getWidth(), rect->getHeight() };
		XCBConfigureWindow(connection, drawable_.window, CWX | CWY | CWWidth | CWHeight, values);
	}
}

bool XCBAbstractControl::beginSetBounds( const ulong32& numberOfChildren )
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
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Rect();
}

void XCBAbstractControl::setVisible( const bool& visible )
{
	XCBConnection* connection = XCBGraphicsToolkit::getConnection();
	if(connection != NULL)
	{
		if(visible)
		{
			XCBMapWindow(connection, drawable_.window);
		}
		else
		{
			XCBUnmapWindow(connection, drawable_.window);
		}
	}
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

void XCBAbstractControl::handlePaintEventFor(XCBWINDOW& window)
{
	XCBAbstractControl* control = controlMap_->getControl(window);
	if(control != NULL) {
		GraphicsContext* gc = control->control_->getContext();
		control->control_->paint(gc);
	}
}

/**
$Id$
*/

