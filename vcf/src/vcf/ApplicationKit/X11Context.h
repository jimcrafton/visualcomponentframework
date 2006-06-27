#ifndef _VCF_X11CONTEXT_H__
#define _VCF_X11CONTEXT_H__
//X11Context.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// X11Context.h: interface for the X11Context class.



#include <deque>

namespace VCF
{

/*
#define MAX_WIN32_CTXT_CACHE_COUNT		4

enum ContextState {
	CTXS_NULL=0,
	CTXS_HANDLE_VALID=1
};
*/

enum PrimitiveType{
	PRIMITIVE_MOVE=0,
	PRIMITIVE_LINE,
	PRIMITIVE_POLYLINE,
	PRIMITIVE_BEZIER,
	PRIMITIVE_RECT,
	PRIMITIVE_ELLIPSE,
	PRIMITIVE_ARC,
	PRIMITIVE_CLOSE
};


struct PointOperation {
	PointOperation( const double& ax=0.0, const double& ay=0.0 ) {
		x = ax;
		y = ay;
		primitive = PRIMITIVE_MOVE;
	}

	double x;
	double y;
	PrimitiveType primitive;
};

struct TextOperation {
	TextOperation( const double& ax=0.0, const double& ay=0.0 ) {
		x = (int32)ax;
		y = (int32)ay;
	};

	int32 x;
	int32 y;
	String text;
};

class GRAPHICSKIT_API X11Image;
/**
*A Context provides the lowest level graphics interface to the
*native systems 2D drawing operations. Based loosely on PostScript,
*a Context takes a series of of drawing operations, or commands
*(lineTo, moveTo, etc), and then executes them by either filling or
*strokeing the path(s) that result from the commands. Thus calling
*ellipse() will not draw anything till the strokePath() or fillPath()
*methods have been called. All path commands should add their information
*to a stack of some sort that is then looped through and executed
*using the appropriate native graphics calls. At each path command
*a test should be made as to whether the buffer should be cleared.
*The buffer should be cleared only after the stroke of fill methods
*have been  called. For example:
*
*<p><pre>
*	ellipse(23,23,45,67) //added to buffer
*	moveTo(89,100) //add to buffer
*	lineTo(300,40) //add to buffer
*	strokePath()
*	fillPath()
*	rectangle(200,300,400,400)//buffer cleared, then add to buffer
*</pre></p>
*/
class X11Context  : public ContextPeer, public Object
{
public:
	X11Context();
	/**
	*Creates a new HDC from scratch
	*/
	X11Context( const uint32& width, const uint32& heigh );

	/**
	Thius will initialize the context from a X11GraphicsDevice object
	@param int32 the contextID is a pointer to a X11GraphicsDevice, which
	in turn holds the actual Visual and GC values
	*/

	X11Context( const int32& contextID );

	virtual ~X11Context();

	virtual void setContext( GraphicsContext* context );

	virtual GraphicsContext* getContext();

	virtual VCF::FontState* getCurrentFontState();

	/**
	Will return the contextID which represents the GC value for the
	Context
	@return int32 the contextID is the value of the GC for the Context
	*/
	virtual int32 getContextID();

	/**
	Sets the value of the interna X11GraphicsDevice object
	@param int32 the contextID is a pointer to a X11GraphicsDevice, which
	in turn holds the actual Visual and GC values
	@see X11GraphicsDevice
	*/
	virtual void setContextID( const int32& handle );

	virtual void setCurrentFontState(VCF::FontState * state);

	virtual void setClippingPath( Path* clippingPath );

	virtual void setClippingRect( Rect* clipRect );

	virtual void drawImage( const double & x, const double & y, Image* image );

	virtual void drawImageWithinBounds( Rect* bounds, Image* image );

	virtual void drawPartialImage( const double& x, const double& y, Rect* imageBounds, Image* image );

    virtual void textAt(const double & x, const double & y, const String & text, const int32& drawOptions );

	virtual void textBoundedBy( Rect* bounds, const String& text, const int32& drawOptions );

	virtual double getTextWidth( const String& text );

	virtual double getTextHeight( const String& text );

    virtual void rectangle(const double & x1, const double & y1, const double & x2, const double & y2);

    virtual void circle(const double & x, const double & y, const double & radius);

    virtual void ellipse(const double & x1, const double & y1, const double & x2, const double & y2, const double & angle=0.0);

	virtual void arc( const double & x1, const double & y1, const double & x2, const double & y2,
                      const double & x3, const double & y3, const double & x4, const double & y4 );

    virtual void setCurrentStrokeState( StrokeState * state );

    virtual void setCurrentFillState( FillState * state );

	virtual StrokeState* getCurrentStrokeState();

    virtual FillState* getCurrentFillState();

    virtual void polyline(std::vector<Point*>& pts);

    virtual void curve(const double & x1, const double & y1, const double & x2, const double & y2,
                         const double & x3, const double & y3, const double & x4, const double & y4);

    virtual void lineTo(const double & x, const double & y);

    virtual void moveTo(const double & x, const double & y);

    virtual void fillPath();

    virtual void strokePath();

	void init();

	virtual void setOrigin( const double& x, const double& y );

	virtual Point* getOrigin();

	virtual void copyContext( const double& x, const double& y, ContextPeer* context );

	virtual bool isMemoryContext();

	//utility functions
	void copyToImage( X11Image* image );

	virtual void checkHandle();

	virtual void releaseHandle();

	virtual bool isXORModeOn();

	virtual void setXORModeOn( const bool& XORModeOn );

	virtual void setTextAlignment( const bool& alignTobaseline );

	virtual bool isTextAlignedToBaseline();

	virtual void drawSelectionRect( Rect* rect );

	virtual void drawButtonRect( Rect* rect, const bool& isPressed );

	virtual void drawCheckboxRect( Rect* rect, const bool& isPressed );

	virtual void drawRadioButtonRect( Rect* rect, const bool& isPressed );

	virtual void drawVerticalScrollButtonRect( Rect* rect, const bool& topButton, const bool& isPressed );

	virtual void drawDisclosureButton( Rect* rect, const int32& state );

	virtual void drawHorizontalScrollButtonRect( Rect* rect, const bool& leftButton, const bool& isPressed );

	virtual void drawTab( Rect* rect, const bool& selected, const String& caption );

	virtual void drawTabPage( Rect* rect );

	virtual void drawTickMark( Rect* rect );

	virtual void drawSliderThumb( Rect* rect, const bool& pressed );

	virtual void drawSlider( Rect* rect );

	virtual void drawHeader( Rect* rect );

	virtual void drawEdge( Rect* rect, const int32& edgeSides, const int32& edgeStyle );

	virtual void drawSizeGripper( Rect* rect );

	virtual void drawControlBackground( Rect* rect );

	virtual void drawWindowBackground( Rect* rect );

	virtual void drawMenuItemBackground( Rect* rect, const bool& selected );

	void setParentImage( X11Image* image ) {
		parentImage_ = image;
	}

	/**
	this method attachs an X11Image* to the context peer.
	when the peer's releaseHandle() is called it in turn
	calls the X11Image::updateBitsFromPixmap
	*/
	void attachToXImage( X11Image* image );
protected:

	GC x11GC_;
	Drawable x11Drawable_;
	Display* X11Display_;
	X11Image* parentImage_;

	Imlib_Image memoryImage_;
	Pixmap memoryImageAlpha_;

	//this serves as the image to use when drawing on
	//a control with a clip area set
	Rect clipRect_;


	bool isMemoryCtx_;
	uint32 pixmapHeight_;
	uint32 pixmapWidth_;


	bool pathStarted_;

	std::vector<PointOperation*> pathOperations_;
	std::vector<TextOperation*> textOperations_;

	Point currentMoveTo_;
	Point oldOrigin_;
	Point origin_;
	bool inFillPath_;


	FillState currentFill_;
	StrokeState currentStroke_;
	FontState currentFontState_;

	GraphicsContext* context_;

	bool isXORModeOn_;

	bool alignToBaseline_;

	void clearBuffer();
	void clearPathBuffer();
	void clearTextBuffer();
	void testBuffer();

	int32 translateFillStyle( const FillStyle& fillState );
	int32 translateStrokeStyle( const StrokeStyle& strokeStyle );
	int32 translateHatch( const FillStyle& fillState );
	void execPathOperations();

	/**
	*Utility function to draw a transparent bitmap
	*/
	static void drawTransparentBitmap(int hdc, int hBitmap, int32 xStart,
                           int32 yStart, uint32 cTransparentColor);



	void createDefaultGC();

	void xDrawLine( double x1, double y1, double x2, double y2 );
	void xDrawRectangle( double x1, double y1, double x2, double y2 );
	void xDrawEllipse( double x1, double y1, double x2, double y2, double angle );
	void xDrawLines( ImlibPolygon poly, XPoint* points, int numberOfPoints );

	void simpleLineBreak( const String& text, std::vector<String>& lines );
};

};


#endif // _VCF_X11CONTEXT_H__

/**
$Id$
*/
