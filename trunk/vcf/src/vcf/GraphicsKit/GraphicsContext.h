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

#ifndef AGG_SCANLINE_U_INCLUDED
#include "thirdparty/common/agg/include/agg_scanline_u.h"
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

class RenderArea;

class GraphicsContext;


template<typename SpanAllocT, typename SpanGenT>
void renderScanlines( GraphicsContext& gc,
										agg::rendering_buffer& renderingBuffer,
										agg::rasterizer_scanline_aa<>& rasterizer,
										SpanAllocT& spanAllocater,
										SpanGenT& spanGenerator );


void renderScanlinesSolid( GraphicsContext& gc,
							agg::rasterizer_scanline_aa<>& rasterizer,
							const agg::rgba& color );



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

	/**
	These are the set of standard compositing
	or "blend" modes that the GraphicsContext
	supports. The last mode, cmCustom, is for
	future use, and will allow some custom
	compositing function to be used. The blend/compositing
	modes below are the same as used in AGG and
	in the PDF specification.
	[todo]
	We should have some little pictures of what each blend
	mode looks like...
	[/todo]
	*/
	enum CompositingMode {
		cmNone = 0xFF,
		cmClear = 0,
		cmSource,
		cmDestination,
		cmSrcOver,
		cmDestOver,
		cmSrcIn,
		cmDestIn,
		cmSrcOut,
		cmDestOut,
		cmSrcATop,
		cmDestATop,
		cmXOR,
		cmPlus,
		cmMinus,
		cmMultiply,
		cmScreen,
		cmOverlay,
		cmDarken,
		cmLighten,
		cmColorDodge,
		cmColorBurn,
		cmHardLight,
		cmSoftLight,
		cmExclusion,
		cmDifference,
		cmContrast,
		cmCustom
	};

	/**
	The set of enum values define the
	standard line cap style. These are the same
	line cap styles that the PDF spec and Win32
	uses.
	*/
	enum LineCapStyle {
		lcsButtCap = 0,
		lcsRoundCap,
		lcsSquareCap
	};

	/**
	The set of enum values for defining the line
	join style. These values are the same as those
	found in the PDF spec and Win32.
	*/
	enum LineJoinStyle {
		ljsMiterJoin = 0,
		ljsRoundJoin,
		ljsBevelJoin
	};


	/**
	Describes the state of the alpha channel.
	The state is used to check whether or not
	the render area's alpha values have been
	accidentally overwritten by native GDI calls.
	If they have, we can then reset them back to
	255, which is the default value.

	The default state is rasDefault, which means
	that all the render area's alpha values
	are at 0xFF (255).

	When the graphics context's drawing routine's
	are called they may, depending on the platform,
	overwrite the render area's alpha values. If
	this happens then the state must be set to
	rasDirty, indicating that the graphics
	context needs to reset the alpha values
	back to the original state before any drawing
	gets done that depends on accurate alpha
	values being present in the render area's
	buffer.

	If the alpha values of the render area have been
	modified by the programmer and need to be retained,
	then the default state should be changed from
	rasDefault to rasNonDefaultAlphaVals.
	*/
	enum RenderAreaAlphaState {
		rasDefault = 0,
		rasNonDefaultAlphaVals,
		rasDirty
	};

	typedef std::vector<GraphicsState*> GraphicsStateCollection;
	typedef GraphicsStateCollection::iterator GraphicsStateIterator;
	typedef GraphicsStateCollection::const_iterator GraphicsStateConstIterator;

public:
	void init( );

	ContextPeer* getPeer( );

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
	@see Fill
	*/
	void setCurrentFill(Fill * fill );

	/**
	sets the current stroke
	@see Stroke
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

	/**
	This method sets the image bounds for the drawing
	area image. This gets called by the framework to designate
	an image that should be used to draw on, essectially a
	"back buffer" that can be used to draw on, and then blitted
	back onto the GraphicsContext. This is used to draw on
	for anti-aliased graphics.
	*/
	void setRenderArea( Rect bounds );

	/**
	This deletes the drawing area, and frees any resources
	associated with it.
	*/
	void deleteRenderArea( );

	/**
	Draws the drawing area image on to the graphics context.
	*/
	void flushRenderArea( );

	void cacheRenderAreaAlpha();

	void resetRenderAreaAlpha();

	bool hasRenderArea();

	void renderAreaAlphaOverwritten();

	void setRenderAreaAlphaSize( bool usingNonDefaultAlpha );

	Image* getRenderArea();

	agg::rendering_buffer* getRenderingBuffer();

	void setRenderingBuffer( agg::rendering_buffer* buffer );

	agg::scanline_u8& internal_getRenderAreaScanline();

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
	Returns the current line cap style.
	*/
	LineCapStyle getLineCapStyle();

	/**
	Sets the line cap style.
	*/
	void setLineCapStyle( LineCapStyle val );

	LineJoinStyle getLineJoinStyle();
	void setLineJoinStyle( LineJoinStyle val );

	/**
	Returns the current miter limit. The default
	value for this is 1.0 (for now).
	*/
	double getMiterLimit();

	/**
	Sets the current miter limit. The miter limit is the amount to
	extend a miter join between two angled lines.
	*/
	void setMiterLimit( double val );


	/**
	Sets the current compositing mode. The default value
	for the compositing mode is cmSource. When drawing without
	anti-aliasing support, most of these modes will be ignored
	with the exception of cmXOR. Setting the composite mode to cmXOR
	takes the place of calling setXORModeOn(true), while setting
	the composite mode to cmSource is the same as setXORModeOn( false ).

	When anti-aliased drawing is used, then the compositing value is
	checked when drawing with a Stroke or Fill class.

	The composite value effects how colors for new graphic elements
	are blended with colors of existing graphic elements.
	*/
	void setCompositingMode( CompositingMode compositeMode );

	/**
	Returns the current composite mode.
	*/
	CompositingMode getCompositingMode();

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


	Image* getAlphaMask();

	void setAlphaMask( Image* alphaMask );


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
	@deprecated use getCompositingMode and check to see if
	the GraphicsContext::cmXOR is the current composite mode.
	*/
	bool isXORModeOn( );

	/**
	@deprecated use setCompositingMode and pass in
	GraphicsContext::cmXOR for the current composite mode.
	*/
	void setXORModeOn( const bool& XORModeOn );

	void setAlpha( const double& alpha );
	double getAlpha();


	void copyContext( const Rect& sourceRect, const Rect& destRect, GraphicsContext* context );

	/**
	*/
	void fillPath();

	/**
	*/
	void strokePath();

	/**
	draws a path. See Path for more info. Basically this simple enumerates all the
	path points and uses the current stroke and fill to render the shape
	*/
	void draw(Path * path );

	/**
	draws an image at the x,y, coordinates
	*/
	void drawImage( const double& x, const double& y, Image * image, const bool& renderImmediately=true );
	void drawImage( const Point & pt, Image * image, const bool& renderImmediately=true );


	/**
	"Blits" the image to the underlying graphics context. No attempt is
	made to transform the image. The image is blitted to the coordinates
	specified by the x and y arguments, and the image's width and height
	are used to determine the bounds.
	*/
	void bitBlit( const double& x, const double& y, Image* image );
	void bitBlit( const Point & pt, Image* image );

	void bitBlit( const double& x, const double& y, Rect* imageBounds, Image* image );
	void bitBlit( const Point & pt, Rect* imageBounds, Image* image );




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
	void drawImageWithState( const double& x, const double& y, Image * image, const bool& enabled, const bool& renderImmediately=true );
	void drawImageWithState( const Point & pt, Image * image, const bool& enabled, const bool& renderImmediately=true );

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
	void drawImageWithinBounds( Rect* bounds, Image* image, const bool& renderImmediately=true );

	/**
	draws a partial image at the x,y, coordinates specified
	@param double x - the x coordinate on the GraphicsContext
	@param double y - the y coordinate on the GraphicsContext
	@param Rect* imageBounds - a rectangle in the coordinate space
	of the image that specifies which rectangular portion of the
	image to draw
	@param Image image - the image to draw
	*/
	void drawPartialImage( const double& x, const double& y, Rect* imageBounds, Image* image, const bool& renderImmediately=true );
	void drawPartialImage( const Point & pt, Rect* imageBounds, Image* image, const bool& renderImmediately=true );


	void renderImages( bool freeImages = true );


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

	struct ImageOperation {
		ImageOperation():image(NULL),compositeMode(cmSource){}

		Image* image;
		Rect imgSrcRect;
		Rect imgXfrmdRect;
		Point pt;
		CompositingMode compositeMode;
		Matrix2D matrix;
		double ctxAlpha;
	};




	ContextPeer* contextPeer_;
	GraphicsDrawingState currentDrawingState_;
	std::vector<PointOperation> pathOperations_;
	std::vector<ImageOperation> imageOperations_;
	/*
	Image* renderArea_;
	Point drawingAreaTopLeft_;
	agg::rendering_buffer* renderBuffer_;
	uchar* renderAreaAlphaVal_;
	size_t renderAreaAlphaSize_;
	RenderAreaAlphaState renderAreaAlphaState_;
	*/
	Rect viewableBounds_;

	RenderArea* renderArea_;

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


	void renderImage( agg::rendering_buffer& destBuffer, Rect& destRect, ImageOperation& imgOp );

	Rect getRenderDestRect();
	Rect getTransformedImageRect( ImageOperation& imgOp );
	Point getTransformedImagePoint( ImageOperation& imgOp );

};


///////////////////////////////////////////////////////////////////////////////
// inlines

inline void GraphicsContext::drawImage( const Point & pt, Image * image, const bool& renderImmediately) {
	drawImage( pt.x_, pt.y_, image, renderImmediately );
}

inline void GraphicsContext::bitBlit( const Point & pt, Image* image )
{
	bitBlit( pt.x_, pt.y_, image );
}

inline void GraphicsContext::bitBlit( const Point & pt, Rect* imageBounds, Image* image )
{
	bitBlit( pt.x_, pt.y_, imageBounds, image );
}

inline void GraphicsContext::drawImageWithState( const Point & pt, Image * image, const bool& enabled, const bool& renderImmediately ) {
	drawImageWithState( pt.x_, pt.y_, image, enabled, renderImmediately );
}

inline void GraphicsContext::drawPartialImage( const Point & pt, Rect* imageBounds, Image* image, const bool& renderImmediately ) {
	drawPartialImage( pt.x_, pt.y_, imageBounds, image, renderImmediately );
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


template<typename SpanAllocT, typename SpanGenT>
void renderScanlines( GraphicsContext& gc,
										agg::rendering_buffer& renderingBuffer,
										agg::rasterizer_scanline_aa<>& rasterizer,
										SpanAllocT& spanAllocater,
										SpanGenT& spanGenerator )
{
	typedef agg::renderer_base<pixfmt> RendererBase;

	typedef agg::comp_op_adaptor_rgba<color_type, component_order> blender_type;
	typedef agg::pixfmt_custom_blend_rgba<blender_type, agg::rendering_buffer> pixfmt_type;
	typedef agg::renderer_base<pixfmt_type> comp_renderer_type;

	agg::scanline_u8& scanline = gc.internal_getRenderAreaScanline();


	if ( GraphicsContext::cmSource == gc.getCompositingMode() ) {
		pixfmt pix(renderingBuffer);
		RendererBase rb(pix);
		agg::render_scanlines_aa( rasterizer, scanline, rb, spanAllocater, spanGenerator );
	}
	else {
		pixfmt_type pix(renderingBuffer);
		pix.comp_op( gc.getCompositingMode() );

		comp_renderer_type crb(pix);
		agg::render_scanlines_aa( rasterizer, scanline, crb, spanAllocater, spanGenerator );
	}
}

inline void renderScanlinesSolid( GraphicsContext& gc,
										agg::rasterizer_scanline_aa<>& rasterizer,
										const agg::rgba& color )
{
	typedef agg::renderer_base<pixfmt> RendererBase;
	typedef agg::renderer_scanline_aa_solid<RendererBase> RendererSolid;

	typedef agg::comp_op_adaptor_rgba<color_type, component_order> blender_type;
	typedef agg::pixfmt_custom_blend_rgba<blender_type, agg::rendering_buffer> pixfmt_type;
	typedef agg::renderer_base<pixfmt_type> comp_renderer_type;

	agg::rendering_buffer& renderingBuffer = *gc.getRenderingBuffer();

	agg::scanline_u8& scanline = gc.internal_getRenderAreaScanline();

	if ( GraphicsContext::cmSource == gc.getCompositingMode() ) {
		pixfmt pixf(renderingBuffer);
		RendererBase renb(pixf);
		RendererSolid renderer( renb );

		renderer.color(color);


		agg::render_scanlines(rasterizer, scanline, renderer);
	}
	else {
		pixfmt_type pixf(renderingBuffer);
		pixf.comp_op( gc.getCompositingMode() );
		comp_renderer_type renb(pixf);

		agg::render_scanlines_aa_solid(rasterizer, scanline, renb, color);
	}
}


};


#endif // _VCF_GRAPHICSCONTEXT_H__

/**
$Id$
*/
