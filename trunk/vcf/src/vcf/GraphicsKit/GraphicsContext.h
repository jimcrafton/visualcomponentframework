#ifndef _VCF_GRAPHICSCONTEXT_H__
#define _VCF_GRAPHICSCONTEXT_H__
//GraphicsContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef AGG_RENDERING_BUFFER_INCLUDED
#include "thirdparty/common/agg/include/agg_rendering_buffer.h"
#endif



namespace VCF{


class ContextPeer;
class Image;
class Fill;
class Path;
class Stroke;
class Font;
class DrawUIState;
class MenuState;
class ButtonState;
class DisclosureButtonState;
class ProgressState ;
class SliderState;
class ScrollBarState;
class TabState;
class BackgroundState;
class TextState;

class GraphicsState;




/**
\class GraphicsContext GraphicsContext.h "vcf/GraphicsKit/GraphicsContext.h"
A GraphicsContext provides the lowest level graphics interface to the
native systems 2D drawing operations. Based loosely on PostScript,
a Context takes a series of of drawing operations, or commands
*(lineTo, moveTo, etc), and then executes them by either filling or
strokeing the path(s) that result from the commands. Thus calling
ellipse() will not draw anything till the strokePath() or fillPath()
methods have been called. All path commands should add their information
to a stack of some sort that is then looped through and executed
using the appropriate native graphics calls. At each path command
a test should be made as to whether the buffer should be cleared.
The buffer should be cleared only after the stroke of fill methods
have been  called. For example:


\code
	ellipse(23,23,45,67) //added to buffer
	moveTo(89,100) //add to buffer
	lineTo(300,40) //add to buffer
	strokePath()
	fillPath()
	rectangle(200,300,400,400)//buffer cleared, then add to buffer
\endcode

@version 1.0
@author Jim Crafton

*/
class GRAPHICSKIT_API GraphicsContext : public Object {
public:
	GraphicsContext( );

	/**
	Creates a new blank graphics context of the specified width and height
	*/
	GraphicsContext( const unsigned long& width, const unsigned long& height );

	/**
	Create a new context based on a context ID. See ContextPeer getContextID()
	Doing this should caryy over any of the current settings of the context that the contextID represents.
	*/
	GraphicsContext( OSHandleID contextID );

	virtual ~GraphicsContext( );

	/**
	represents what kind of high level drawing operation we
	are performing. We can stroke a path, fill a path,
	draw an image, or draw text. This is used by the
	ConextPeer's prepareForDrawing() so it know's how
	best to prepare the low level graphics resources. For example
	strokePath() would call the ConextPeer's prepareForDrawing() and
	pass in GraphicsContext::doStroke, indicating that any upcoming
	calls to moveTo, lineTo, rectangle, etc will be drawn using the
	attributes of the GraphicsContext's stroke.
	*/
	enum DrawingOperation {
		doStroke,
		doFill,
		doText,
		doImage
	};

	enum GraphicsDrawingState {
		gsNone = 0,
		gsAddingGraphicsOps,
		gsExecutingGraphicsOps
	};

	/**
	text drawing options
	*/
	enum TextDrawingOptions{
		tdoNone=0,
		tdoWordWrap=1,
		tdoLeftAlign=2,
		tdoCenterHorzAlign=4,
		tdoRightAlign=8,
		tdoBottomAlign=16,
		tdoCenterVertAlign=32,
		tdoTopAlign=64
	};

	enum EdgeType{
		etNoSides = 0x000,
		etLeftSide = 0x001,
		etRightSide = 0x002,
		etTopSide = 0x004,
		etBottomSide = 0x008,
		etAllSides = 0x00F,
		etRecessed = 0x010,
		etEtched = 0x020,
		etRaised = 0x030,
		etSunken = 0x040,
	};

	enum ThemeTextType {
		ttMenuItemFont = 0,
		ttSelectedMenuItemFont,
		ttSystemFont,
		ttSystemSmallFont,
		ttControlFont,
		ttMessageFont,
		ttToolTipFont
	};

	typedef std::vector<GraphicsState*> GraphicsStateCollection;
	typedef GraphicsStateCollection::iterator GraphicsStateIterator;
	typedef GraphicsStateCollection::const_iterator GraphicsStateConstIterator;

public:
	void init( );

	bool isAntiAliasingOn( );

	void setAntiAliasingOn( bool antiAliasingOn );

	/**
	sets the current font
	A copy of the Font is made when this is set
	@deprecated
	*/
	void setCurrentFont( Font * font );

	/**
	sets the current font
	A copy of the Font is made when this is set
	*/
	void setCurrentFont( const Font * font );

	/**
	returns the current Font
	*/
	Font* getCurrentFont( );

	/**
	sets the current fill
	*/
	void setCurrentFill(Fill * fill );

	/**
	sets the current stroke
	*/
	void setCurrentStroke(Stroke * stroke );

	void setClippingRect( Rect* rect );

	void setClippingPath( Path* clippingPath );

	Rect getClippingRect( );

	Path* getClippingPath( );

	Rect getViewableBounds() {
		return viewableBounds_;
	}

	void setViewableBounds( const Rect& bounds ) {
		viewableBounds_ = bounds;
	}

	void setDrawingArea( Rect bounds );

	void deleteDrawingArea( );

	void flushDrawingArea( );

	void markRenderAreaDirty() {
		renderAreaDirty_ = true;
	}

	bool isRenderAreaDirty() {
		if ( hasDrawingArea() ) {
			return renderAreaDirty_;
		}
		return false;
	}

	bool hasDrawingArea() {
		return NULL != drawingArea_;
	}

	Image* getDrawingArea() {
		return drawingArea_;
	}

	agg::rendering_buffer* getRenderingBuffer() {
		return renderBuffer_;
	}

	void setRenderingBuffer( agg::rendering_buffer* buffer ) {
		renderBuffer_ = buffer;
	}

	/**
	saves the state of a Graphics context after the
	paint operations are done.
	The save/restore idea idea is the same as for Win32 SaveDC and RestoreDC.
	It allows you to save the state of the DC (device context) at a given point in time,
	and then make a whole bunch of changes to it, and when you're all done
	just call RestoreDC() and everything is set back.
		
	This prevents all sorts of extra SelectObject() calls and is more efficent.
	
	Similarly this makes it easy to guarantee that the
	state of the GraphicsContext is reset correctly.
	@return int, the index of the newly saved graphics state.
	@see GraphicsContext::restoreState()
	*/
	int saveState( );

	/**
	Restores the state of a Graphics context after the
	paint operations are done.
	@param int state, the index of the graphics state we want to restore. All
	the graphics states saved after this index are lost as they have lost meaning,
	and the current graphics state index is set to the state just restored.
	@see GraphicsContext::saveState()
	*/
	void restoreState( int state );


	/**
	Sets the current color of the graphics context to use for filling
	or stroking paths.
	@deprecated
	*/
	void setColor( Color* color );

	/**
	Sets the current color of the graphics context to use for filling
	or stroking paths.
	*/
	void setColor( const Color* color );

	Color* getColor( );

	void fillPath( );

	void strokePath( );

	ContextPeer* getPeer( );

	void copyContext( const Rect& sourceRect, const Rect& destRect, GraphicsContext* context );

	/**
	Sets the context's origin for drawing. The default is 0,0 in the top, left of the corner of
	screen real estate the context represents
	*/
	void setOrigin( const double& x, const double& y );
	void setOrigin( const Point & pt );

	Point getOrigin( );

	/**
	sets the current rotation value of the transformation matrix. The
	theta argument is in degrees.
	*/
	void setRotation( const double& theta );

	/**
	Set the x and y translation values for the transformation matrix.
	*/
	void setTranslation( const double transX, const double& transY );

	/**
	Sets the x and y shear values, in degrees, for the transformation
	matrix
	*/
	void setShear( const double& shearX, const double& shearY );

	/**
	Sets the x and y scale values for the transformation matrix. To double the
	size of drawn elements use a scaleX value of 2.0 and a scaleY value of
	2.0. To flip the y coordinates use a scaleY of -1.0.
	*/
	void setScale( const double& scaleX, const double& scaleY );


	void concatRotation( const double& theta );

	void concatTranslation( const double transX, const double& transY );

	void concatShear( const double& shearX, const double& shearY );

	void concatScale( const double& scaleX, const double& scaleY );


	/**
	This test to see if the current rotation
	translation, scale, and shear values are all
	at their default values.
	*/
	bool isDefaultTransform( );

	/**
	This (re)sets the current values for rotation,
	shear, scale, and translation to their default values.
	*/
	void makeDefaultTransform( );

	double getRotation( );

	double getTranslationX( );

	double getTranslationY( );

	double getShearX( );

	double getShearY( );

	double getScaleX( );

	double getScaleY( );

	/**
	returns whether or not the XOR Mode is turned on.
	@return bool if the return is true then the
	XOR mode is on, which means that colors are alternated
	at the pixel level. Thus a line drawn once, and then
	a second time at the same coordinates will erase itself
	*/
	bool isXORModeOn( );

	/**
	Turns the XOR mode on or off.
	@param bool XORModeOn, if true then turns the XORMode on
	otherwise if it's false it turns it off.
	*/
	void setXORModeOn( const bool& XORModeOn );


	/**
	draws a path. See Path for more info. Basically this simple enumerates all the
	path points and uses the current stroke and fill to render the shape
	*/
	void draw(Path * path );

	/**
	draws an image at the x,y, coordinates
	*/
	void drawImage( const double& x, const double& y, Image * image );
	void drawImage( const Point & pt, Image * image );



	/**
	draws an image at the x,y, coordinates, with
	state
	@param double x coordinate
	@param double y coordinate
	@param Image the image to draw
	@param bool the state of the image, if true then draws the
	image normally, if false draws a grayed out and embossed
	version
	Note: as of 8/4/2001 not implemented yet
	*/
	void drawImageWithState( const double& x, const double& y, Image * image, const bool& enabled );
	void drawImageWithState( const Point & pt, Image * image, const bool& enabled );

	/**
	draws a portion of the image.
	@param Rect boudns - the left_, top_ members of the bounds rect describe
	where on the GraphicsContext the image will be drawn, while the height
	and width of the bounds tells how much of the image to draw. A height or width
	greater than the Image is ignored, and the whole image is draw. A height
	or width less than the image results in only a portion of the image getting
	drawn, or the top, left of the image to the specified height and width.
	@param Image the image to draw
	*/
	void drawImageWithinBounds( Rect* bounds, Image* image );

	/**
	draws a partial image at the x,y, coordinates specified
	@param double x - the x coordinate on the GraphicsContext
	@param double y - the y coordinate on the GraphicsContext
	@param Rect* imageBounds - a rectangle in the coordinate space
	of the image that specifies which rectangular portion of the
	image to draw
	@param Image image - the image to draw
	*/
	void drawPartialImage( const double& x, const double& y, Rect* imageBounds, Image* image );
	void drawPartialImage( const Point & pt, Rect* imageBounds, Image* image );



	void setCurrentTransform( const Matrix2D& transform );

	Matrix2D* getCurrentTransform( );

	/**
	End of high level gaphics functions. The funtions below are lower level
	See ContextPeer for more information on the functions below
	*/

	void setStrokeWidth( const double& width );

	double getStrokeWidth( );


	void textAt( const double & x, const double & y, const String & text );
	void textAt( const Point & pt, const String & text );

	void textAt( const double & x, const double & y, const String& text, const long drawOptions );
	void textAt( const Point & pt, const String& text, const long drawOptions );

	void textWithStateAt( const double& x, const double& y, const String& text, const bool& enabled );
	void textWithStateAt( const Point & pt, const String& text, const bool& enabled );

	/**
	draws text within the bounds specified. If specified the
	text will be word wrapped within the bounds.
	@param Rect bounds - the left, top, right, and bottom of the
	rectangle to draw the text within
	@param String the text to draw
	@param bool wordWrap whether or not wrap the text to
	bounds specified. If wordWrap is false, then the text is
	treated as a single line, and any text extending past the
	right coordinate value will be clipped using an ellipsis.
	So if "Hello World" is passed in and the bounds only fits
	*"Hello W", then the string will be drawn as "Hello..."
	*/
	void textBoundedBy( Rect* bounds, const String& text, const bool& wordWrap=true );

	void textBoundedBy( Rect* bounds, const String& text, const long drawOptions );

	double getTextWidth( const String& text );

	double getTextHeight( const String& text );

	void rectangle( const double & x1, const double & y1, const double & x2, const double & y2 );
	void rectangle( const Rect & rc );
	void rectangle( const Point & pt1, const Point & pt2 );

	void rectangle( Rect* r ){
		if ( NULL != r ) {
			this->rectangle( r->left_, r->top_, r->right_, r->bottom_ );
		}
	};

	void lineTo( const double& x, const double& y );
	void lineTo( const Point & pt );

	void moveTo( const double& x, const double& y );
	void moveTo( const Point & pt );

	void roundRect( const double & x1, const double & y1, const double & x2, const double & y2, const double & xc, const double & yc );
	void roundRect( const Rect & rc, const Point & ptc );
	void roundRect( const Point & pt1, const Point & pt2, const Point & ptc );

	void roundRect( Rect* r, Point * p ){
		if ( NULL != r && NULL != p ) {
			this->roundRect( r->left_, r->top_, r->right_, r->bottom_, p->x_, p->y_ );
		}
	};

	void circle( const double & x, const double & y, const double & radius );
	void circle( const Point & pt, const double & radius );

	void ellipse( const double & x1, const double & y1, const double & x2, const double & y2 );
	void ellipse( const Point & pt1, const Point & pt2 );

	void arc( const double& centerX,  const double& centerY,
	          const double& radiusWidth, const double& radiusHeight,
	          const double& startAngle, const double& endAngle );

	void arc( const Point & centerPt, const Size& radius,
	          const double& startAngle, const double& endAngle );


	void pie( const double & x1, const double & y1, const double & x2, const double & y2, const double & x3, const double & y3, const double & x4, const double & y4 );
	void pie( const Point & pt1, const Point & pt2, const Point & pt3, const Point & pt4 );

	void chord( const double & x1, const double & y1, const double & x2, const double & y2, const double & x3, const double & y3, const double & x4, const double & y4 );
	void chord( const Point & pt1, const Point & pt2, const Point & pt3, const Point & pt4 );

	void polyline( const std::vector<Point> & pts );

	void curve( const double& x1, const double& y1, const double& x2, const double& y2,
	            const double& x3, const double& y3, const double& x4, const double& y4 );
	void curve( const Point & pt1, const Point & pt2, const Point & pt3, const Point & pt4 );




	/**
	The following functions are related to theme compliant drawing.
	These allow the VCF to properly draw various "parts" of the
	windowing system that are compliant with the windowing system's
	"theme" or visual style.
	*/
	void drawThemeSelectionRect( Rect* rect, DrawUIState& state );

	void drawThemeFocusRect( Rect* rect, DrawUIState& state );

	void drawThemeButtonRect( Rect* rect, ButtonState& state, Rect* captionRect=NULL );

	void drawThemeButtonFocusRect( Rect* rect );

	void drawThemeCheckboxRect( Rect* rect, ButtonState& state );

	void drawThemeRadioButtonRect( Rect* rect, ButtonState& state );

	void drawThemeComboboxRect( Rect* rect, ButtonState& state );

	void drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state );

	/**
	Draws a button that is used to open up more details, for example
	the button that opens up a tree node to reveal it's children, that is compliant
	with the native windowing systems default look and feel.
	On Win32 this is usually represented by the "+" and "-" look as found on
	the tree controls, while on OSX it is the little triangles
	*/
	void drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state );

	/**
	Draws a tab, the part of the TabbedPages control that acts like a
	little button to activate a page, that is compliant
	with the native windowing systems default look and feel
	*/
	void drawThemeTab( Rect* rect, TabState& state );

	/**
	Draws a tab page - the page on which other controls for the page are
	parented to, that is compliant
	with the native windowing systems default look and feel
	*/
	void drawThemeTabPage( Rect* rect, DrawUIState& state );

	void drawThemeTabContent( Rect* rect, DrawUIState& state );

	void drawThemeTabs( Rect* rect, DrawUIState& paneState, TabState& selectedTabState, TabState& otherTabs, const std::vector<String>& tabNames, int selectedTabIndex );

	/**
	Draws tick marks, like that used for a slider control, that is compliant
	with the native windowing systems default look and feel
	*/
	void drawThemeTickMarks( Rect* rect, SliderState& state );

	/**
	Draws a slider control, like that used for a slider control, that is compliant
	with the native windowing systems default look and feel
	*/
	void drawThemeSlider( Rect* rect, SliderState& state );

	/**
	Draws a progress bar control, that is compliant
	with the native windowing systems default look and feel
	*/
	void drawThemeProgress( Rect* rect, ProgressState& state );


	void drawThemeImage( Rect* rect, Image* image, DrawUIState& state );

	/**
	Draws a header control that is compliant
	with the native windowing systems default look and feel
	*/
	void drawThemeHeader( Rect* rect, ButtonState& state );

	/**
	draws edges, useful for separators, that is compliant
	with the native windowing systems default look and feel.
	use a mask or 1 or more values of type ContextPeer::EdgeType
	to indicate which sides of the rect to draw an edge on
	*/
	void drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle );

	/**
	Draws a size gripper for resizing a control/window that is compliant
	with the native windowing systems default look and feel
	*/
	void drawThemeSizeGripper( Rect* rect, DrawUIState& state );

	/**
	Draws a them compliant background
	*/
	void drawThemeBackground( Rect* rect, BackgroundState& state );

	/**
	Draws the background appropriate for a menu item that is compliant
	with the native windowing systems default look and feel.
	This is typically called first by a menu item to give it a standard
	look and feel in it's background before drawing any thing else
	*/
	void drawThemeMenuItem( Rect* rect, MenuState& state );

	/**
	Draws the menu items text such that it's compliant with the
	native windowing platform look and feel. This will take into
	consideration the accelerator values if present.
	*/
	void drawThemeMenuItemText( Rect* rect, MenuState& state );

	void drawThemeText( Rect* rect, TextState& state );

protected:

	void buildArc( double centerX,  double centerY,
	               double radiusWidth, double radiusHeight,
	               double startAngle, double endAngle,
	               std::vector<Point>& pts, const Matrix2D& transform );

	void buildRoundRect( double x1, double y1, double x2, double y2,
	                     double cornerArcWidth, double cornerArcHeight,
	                     std::vector<Point>& pts, const Matrix2D& transform );

	void buildEllipse( double x1, double y1, double x2, double y2,
	                   std::vector<Point>& pts, const Matrix2D& transform );


	void checkPathOperations( );

	void execPathOperations( );


protected:

	/**
	*
	*
	*/
	struct PointOperation {
		enum PrimitiveType{
			ptMoveTo=0,
			ptLineTo,
			ptPolyLine,
			ptBezier,
			ptRect,
			ptRoundRect,
			ptEllipse,
			ptArc,
			ptClose
		};

		PointOperation( const double& ax=0.0, const double& ay=0.0, PrimitiveType op=ptMoveTo ):
			x(ax), y(ay),primitive(op) {
		}

		double x;
		double y;
		PrimitiveType primitive;
	};

	ContextPeer* contextPeer_;
	GraphicsDrawingState currentDrawingState_;
	std::vector<PointOperation> pathOperations_;
	Image* drawingArea_;
	Point drawingAreaTopLeft_;
	agg::rendering_buffer* renderBuffer_;
	bool renderAreaDirty_;
	Rect viewableBounds_;

	/**
	the collection of all the saved Graphics states.
	@see GraphicsContext::saveState()
	*/
	GraphicsStateCollection stateCollection_;

	/**
	the index of the current state in the collection of
	all the saved Graphics states.
	@see GraphicsContext::saveState()
	*/
	int graphicsStateIndex_;

	/**
	the current Graphics state that has been saved.
	@see GraphicsContext::saveState()
	*/
	GraphicsState* currentGraphicsState_;

};


///////////////////////////////////////////////////////////////////////////////
// inlines

inline void GraphicsContext::drawImage( const Point & pt, Image * image) {
	drawImage( pt.x_, pt.y_, image );
}

inline void GraphicsContext::drawImageWithState( const Point & pt, Image * image, const bool& enabled ) {
	drawImageWithState( pt.x_, pt.y_, image, enabled );
}

inline void GraphicsContext::drawPartialImage( const Point & pt, Rect* imageBounds, Image* image ) {
	drawPartialImage( pt.x_, pt.y_, imageBounds, image );
}


inline void GraphicsContext::textWithStateAt( const Point & pt, const String& text, const bool& enabled ) {
	textWithStateAt( pt.x_, pt.y_, text, enabled );
}


inline void GraphicsContext::textAt( const Point & pt, const String & text) {
	textAt( pt.x_, pt.y_, text );
}

inline void GraphicsContext::textAt( const Point & pt, const String& text, const long drawOptions ) {
	textAt( pt.x_, pt.y_, text, drawOptions );
}

inline void GraphicsContext::rectangle( const Point & pt1, const Point & pt2) {
	rectangle( pt1.x_, pt1.y_, pt2.x_, pt2.y_ );
}

inline void GraphicsContext::rectangle( const Rect & rc) {
	rectangle( rc.left_, rc.top_, rc.right_, rc.bottom_ );
}

inline void GraphicsContext::roundRect( const Point & pt1, const Point & pt2, const Point & ptc) {
	roundRect( pt1.x_, pt1.y_, pt2.x_, pt2.y_, ptc.x_, ptc.y_ );
}

inline void GraphicsContext::roundRect( const Rect & rc, const Point & ptc) {
	roundRect( rc.left_, rc.top_, rc.right_, rc.bottom_, ptc.x_, ptc.y_ );
}

inline void GraphicsContext::circle( const Point & pt, const double & radius) {
	circle( pt.x_, pt.y_, radius );
}

inline void GraphicsContext::ellipse( const Point & pt1, const Point & pt2 ) {
	ellipse( pt1.x_, pt1.y_, pt2.x_, pt2.y_ );
}


inline void GraphicsContext::arc( const Point & centerPt, const Size& radius,
								 const double& startAngle, const double& endAngle) {
	arc( centerPt.x_, centerPt.y_, radius.width_, radius.height_, startAngle, endAngle );
}


inline void GraphicsContext::pie( const Point & pt1, const Point & pt2, const Point & pt3, const Point & pt4) {
	pie( pt1.x_, pt1.y_, pt2.x_, pt2.y_, pt3.x_, pt3.y_, pt4.x_, pt4.y_ );
}

inline void GraphicsContext::chord( const Point & pt1, const Point & pt2, const Point & pt3, const Point & pt4) {
	chord( pt1.x_, pt1.y_, pt2.x_, pt2.y_, pt3.x_, pt3.y_, pt4.x_, pt4.y_ );
}

inline void GraphicsContext::curve( const Point & pt1, const Point & pt2, const Point & pt3, const Point & pt4) {
	curve( pt1.x_, pt1.y_, pt2.x_, pt2.y_, pt3.x_, pt3.y_, pt4.x_, pt4.y_ );
}

inline void GraphicsContext::lineTo( const Point & pt)
{
	lineTo( pt.x_, pt.y_ );
}

inline void GraphicsContext::moveTo( const Point & pt)
{
	moveTo( pt.x_, pt.y_ );
}

inline void GraphicsContext::setOrigin( const Point & pt ) {
	setOrigin( pt.x_, pt.y_ );
}




};


/**
*CVS Log info
*$Log$
*Revision 1.8  2006/04/07 02:35:41  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.7.2.6  2006/03/26 22:37:35  ddiego
*minor update to source docs.
*
*Revision 1.7.2.5  2006/03/12 22:42:08  ddiego
*more doc updates - specific to graphicskit.
*
*Revision 1.7.2.4  2006/03/12 22:01:45  ddiego
*doc updates.
*
*Revision 1.7.2.3  2006/03/01 04:34:57  ddiego
*fixed tab display to use themes api.
*
*Revision 1.7.2.2  2006/02/21 04:32:51  ddiego
*comitting moer changes to theme code, progress bars, sliders and tab pages.
*
*Revision 1.7.2.1  2005/09/03 14:03:53  ddiego
*added a package manager to support package info instances, and
*fixed feature request 1278069 - Background color of the TableControl cells.
*
*Revision 1.7  2005/07/18 03:54:19  ddiego
*documentation updates.
*
*Revision 1.6  2005/07/09 23:05:59  ddiego
*added missing gtk files
*
*Revision 1.5  2005/01/02 03:04:25  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.4.2.3  2005/06/26 01:27:54  marcelloptr
*added images to a PushButton
*
*Revision 1.4.2.2  2005/03/14 04:17:26  ddiego
*adds a fix plus better handling of accelerator keys, ands auto menu title for the accelerator key data.
*
*Revision 1.4.2.1  2004/12/19 04:05:03  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.4  2004/12/02 04:11:10  ddiego
*removed some old, extraneous files from graphics kit dir.
*
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.8  2004/11/07 19:32:20  marcelloptr
*more documentation
*
*Revision 1.2.2.7  2004/10/27 03:12:18  ddiego
*integrated chrisk changes
*
*Revision 1.2.2.6  2004/09/09 03:09:26  marcelloptr
*minor change for style
*
*Revision 1.2.2.5  2004/09/06 03:33:21  ddiego
*updated the graphic context code to support image transforms.
*
*Revision 1.2.2.4  2004/09/03 04:05:46  ddiego
*fixes to add matrix transform support for images.
*
*Revision 1.2.2.3  2004/09/01 03:50:39  ddiego
*fixed font drawing bug that tinkham pointed out.
*
*Revision 1.2.2.2  2004/08/31 21:12:07  ddiego
*graphice save and restore state
*
*Revision 1.2.2.1  2004/08/31 04:12:13  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 03:39:30  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.4  2004/06/27 18:19:16  ddiego
*more osx updates
*
*Revision 1.1.2.2.2.3  2004/06/20 00:36:11  ddiego
*finished the new theme API updates
*
*Revision 1.1.2.2.2.2  2004/06/16 05:18:56  ddiego
*further updates to OSX theme compliant drawing code
*
*Revision 1.1.2.2.2.1  2004/06/15 04:04:38  ddiego
*revamped osx theme drawing API
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.19.4.1  2004/04/26 21:58:39  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.19  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.18.2.1  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.18  2003/08/09 02:56:43  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.17.2.6  2003/08/08 03:21:35  ddiego
*got rid of some miscellaneous graphics files
*
*Revision 1.17.2.5  2003/07/28 23:49:58  ddiego
*check in of the weekend's work from July 25
*learned how to use agg image renedering, now have to integrate it into the
*GraphicsKit - alos enabled setting a viewable bounds that sets the agg cliprect
*as well, useful for later optimizations
*
*Revision 1.17.2.4  2003/06/20 04:41:04  ddiego
*more AGG integration
*
*Revision 1.17.2.3  2003/06/17 03:54:25  ddiego
*further agg integration - took out the getImage/putImage from GraphicsContext -
*this was too slow. now have an alternate solution that seems to work OK
*
*Revision 1.17.2.2  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.17.2.1  2003/06/05 03:48:53  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.17  2003/05/17 20:37:09  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.16.2.4  2003/05/13 03:57:12  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.16.2.3  2003/04/17 04:29:47  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.16.2.2  2003/03/23 03:23:48  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.16.2.1  2003/03/12 03:10:22  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.16  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.15.2.4  2003/02/20 02:46:01  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
*Revision 1.15.2.3  2002/12/31 07:01:28  ddiego
*trying to track issues with parenting in X. Made some fixes in the Color class
*and the ContextPeer class to work in gcc/X
*
*Revision 1.15.2.2  2002/12/28 21:51:18  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.15.2.1  2002/12/27 23:04:38  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.15  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.14.4.2  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.14.4.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.14  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.13.12.1  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.13  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_GRAPHICSCONTEXT_H__


