
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/XCBContextPeer.h"

using namespace VCF;

XCBContextPeer::XCBContextPeer() :
context_(NULL),
image_(NULL)
{
	init();
}

XCBContextPeer::XCBContextPeer( const unsigned long& width, const unsigned long& height ) :
context_(NULL),
image_(NULL)
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	init();
}

XCBContextPeer::XCBContextPeer( OSHandleID contextID ) :
context_(NULL),
image_(NULL)
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	init();
}

void XCBContextPeer::init()
{
}

void XCBContextPeer::checkHandle()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::releaseHandle()
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::setContext( GraphicsContext* context ) 
{
	context_ = context;
}

GraphicsContext* XCBContextPeer::getContext() 
{
	return context_;
}

OSHandleID XCBContextPeer::getContextID() 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return NULL;
}

void XCBContextPeer::setContextID( OSHandleID contextID ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBContextPeer::prepareForDrawing( long drawingOperation ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return true;
}

void XCBContextPeer::finishedDrawing( long drawingOperation ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::setClippingPath( Path* clippingPath ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::setClippingRect( Rect* clipRect ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::setTextAlignment( const bool& alignTobaseline ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBContextPeer::isTextAlignedToBaseline() 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBContextPeer::textAt( const Rect& bounds, const String & text, const long& drawOptions ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

double XCBContextPeer::getTextWidth( const String& text ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0.0;
}

double XCBContextPeer::getTextHeight( const String& text ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return 0.0;
}

void XCBContextPeer::rectangle( const double & x1, const double & y1,
								const double & x2, const double & y2 ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__); 
}

void XCBContextPeer::roundRect( const double & x1, const double & y1,
								const double & x2, const double & y2,
								const double & xc, const double & yc ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__); 
}

void XCBContextPeer::ellipse( const double & x1, const double & y1,
							  const double & x2, const double & y2 ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__); 
}

void XCBContextPeer::arc( const double & x1, const double & y1,
						  const double & x2, const double & y2,
						  const double & x3, const double & y3,
						  const double & x4, const double & y4 ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__); 
}

void XCBContextPeer::polyline( const std::vector<Point>& pts ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::curve( const double & x1, const double & y1, const double & x2, const double & y2,
							const double & x3, const double & y3, const double & x4, const double & y4 ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__); 
}

void XCBContextPeer::moveTo( const double & x, const double & y ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::lineTo( const double & x, const double & y ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::setOrigin( const double& x, const double& y ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

Point XCBContextPeer::getOrigin() 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return Point();
}

void XCBContextPeer::copyContext( const Rect& sourceRect,
								  const Rect& destRect,
								  ContextPeer* sourceContext ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__); 
}

bool XCBContextPeer::isMemoryContext() 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

bool XCBContextPeer::isXORModeOn() 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBContextPeer::setXORModeOn( const bool& XORModeOn ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

bool XCBContextPeer::isAntiAliasingOn() 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
	return false;
}

void XCBContextPeer::setAntiAliasingOn( bool antiAliasingOn ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawImage( const double& x, const double& y, Rect* imageBounds, Image* image, int compositeMode )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeSelectionRect( Rect* rect, DrawUIState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeFocusRect( Rect* rect, DrawUIState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeButtonFocusRect( Rect* rect ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeCheckboxRect( Rect* rect, ButtonState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeRadioButtonRect( Rect* rect, ButtonState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeComboboxRect( Rect* rect, ButtonState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTab( Rect* rect, TabState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTabPage( Rect* rect, DrawUIState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTabContent( Rect* rect, DrawUIState& state )
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeTickMarks( Rect* rect, SliderState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeSlider( Rect* rect, SliderState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeProgress( Rect* rect, ProgressState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeImage( Rect* rect, Image* image, DrawUIState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeHeader( Rect* rect, ButtonState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeSizeGripper( Rect* rect, DrawUIState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeBackground( Rect* rect, BackgroundState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeMenuItem( Rect* rect, MenuState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeMenuItemText( Rect* rect, MenuState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::drawThemeText( Rect* rect, TextState& state ) 
{
	LinuxDebugUtils::FunctionNotImplemented(__FUNCTION__);
}

void XCBContextPeer::internal_setImage(XCBImage *image)
{
	image_ = image;
}

/**
$Id$
*/

