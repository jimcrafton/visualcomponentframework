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
		x = (long)ax;
		y = (long)ay;
	};

	long x;
	long y;
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
	X11Context( const unsigned long& width, const unsigned long& heigh );

	/**
	Thius will initialize the context from a X11GraphicsDevice object
	@param long the contextID is a pointer to a X11GraphicsDevice, which
	in turn holds the actual Visual and GC values
	*/

	X11Context( const long& contextID );

	virtual ~X11Context();

	virtual void setContext( GraphicsContext* context );

	virtual GraphicsContext* getContext();

	virtual VCF::FontState* getCurrentFontState();

	/**
	Will return the contextID which represents the GC value for the
	Context
	@return long the contextID is the value of the GC for the Context
	*/
	virtual long getContextID();

	/**
	Sets the value of the interna X11GraphicsDevice object
	@param long the contextID is a pointer to a X11GraphicsDevice, which
	in turn holds the actual Visual and GC values
	@see X11GraphicsDevice
	*/
	virtual void setContextID( const long& handle );

	virtual void setCurrentFontState(VCF::FontState * state);

	virtual void setClippingPath( Path* clippingPath );

	virtual void setClippingRect( Rect* clipRect );

	virtual void drawImage( const double & x, const double & y, Image* image );

	virtual void drawImageWithinBounds( Rect* bounds, Image* image );

	virtual void drawPartialImage( const double& x, const double& y, Rect* imageBounds, Image* image );

    virtual void textAt(const double & x, const double & y, const String & text, const long& drawOptions );

	virtual void textBoundedBy( Rect* bounds, const String& text, const long& drawOptions );

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

	virtual void drawDisclosureButton( Rect* rect, const long& state );

	virtual void drawHorizontalScrollButtonRect( Rect* rect, const bool& leftButton, const bool& isPressed );

	virtual void drawTab( Rect* rect, const bool& selected, const String& caption );

	virtual void drawTabPage( Rect* rect );

	virtual void drawTickMark( Rect* rect );

	virtual void drawSliderThumb( Rect* rect, const bool& pressed );

	virtual void drawSlider( Rect* rect );

	virtual void drawHeader( Rect* rect );

	virtual void drawEdge( Rect* rect, const long& edgeSides, const long& edgeStyle );

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
	unsigned long pixmapHeight_;
	unsigned long pixmapWidth_;


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

	long translateFillStyle( const FillStyle& fillState );
	long translateStrokeStyle( const StrokeStyle& strokeStyle );
	long translateHatch( const FillStyle& fillState );
	void execPathOperations();

	/**
	*Utility function to draw a transparent bitmap
	*/
	static void drawTransparentBitmap(int hdc, int hBitmap, long xStart,
                           long yStart, ulong32 cTransparentColor);



	void createDefaultGC();

	void xDrawLine( double x1, double y1, double x2, double y2 );
	void xDrawRectangle( double x1, double y1, double x2, double y2 );
	void xDrawEllipse( double x1, double y1, double x2, double y2, double angle );
	void xDrawLines( ImlibPolygon poly, XPoint* points, int numberOfPoints );

	void simpleLineBreak( const String& text, std::vector<String>& lines );
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.5.8.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.2.2  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.4.2.1  2003/03/12 03:11:38  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2003/02/26 04:30:41  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.3.2.12  2003/02/20 02:46:02  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
*Revision 1.3.2.11  2003/02/08 18:49:06  ddiego
*added some fixes to handle multiple lines of text. Also made a minor change to
*PosixThread so everything links OK.
*
*Revision 1.3.2.10  2003/01/27 05:04:01  ddiego
*more X11 work fixed up some stuff for modal event loop and added X11Dialog
*class. not ready to work yet
*
*Revision 1.3.2.9  2002/12/31 07:02:16  ddiego
*trying to track issues with parenting in X. Made some fixes in the Color class
*and the ContextPeer class to work in gcc/X
*
*Revision 1.3.2.8  2002/12/27 23:04:42  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.3.2.7  2002/12/22 04:47:59  ddiego
*basic integration of imlib2 is done for X11Context and X11Image, now
*starting on adding font support
*
*Revision 1.3.2.6  2002/12/20 03:29:32  ddiego
*continued more work in integrating imlib2 into the X11Image class. getting
*a little better hand of how to debug with CLI gdb ! Close to having this
*work, and tehn we can work on Fonts !
*
*Revision 1.3.2.5  2002/12/19 05:32:30  ddiego
*initial integration of imlib2 into the GraphicsKit.
*
*Revision 1.3.2.4  2002/12/14 01:50:37  ddiego
*more code in X11Image
*
*Revision 1.3.2.3  2002/12/10 05:33:55  ddiego
*more drawing support, now partial support for copying contexts, and more
*drawXXX methods implemented
*
*Revision 1.3.2.2  2002/12/08 04:48:29  ddiego
*more code to X11Context - uses a Drawable handle directly now
*fleshing out more functions
*
*Revision 1.3.2.1  2002/12/06 04:59:49  ddiego
*fixes to xmake to make it work correctly. Fixed a bug in FilePath that was screwing up
*path separation. fixed up auto generating directories for moveFile(). xmake now
*correctly handles multiple external files and moves output filels correctly
*
*Revision 1.3  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.2.4.1  2002/09/28 22:22:46  ddiego
*added some support for font info and determinging the names on the system
*
*Revision 1.2  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.2.3  2002/08/10 05:48:23  ddiego
*added basic support to the X11COntext for drawing lines, rectangles, and ellipses
*Bezier curves are more complex and will have to be done by hand as X has no
*convenient way to do this
*
*Revision 1.1.2.2  2002/08/08 05:02:59  ddiego
*added a test for X11 GraphicsKit testing
*fixed bug in initializing the graphicsKit, actually I just
*realized this will cause another but - take out automatice initialization of
*FoundationKit from GraphicsKit
*
*Revision 1.1.2.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*
*/


#endif // _VCF_X11CONTEXT_H__


