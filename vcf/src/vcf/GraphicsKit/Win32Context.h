#ifndef _VCF_WIN32CONTEXT_H__
#define _VCF_WIN32CONTEXT_H__
//Win32Context.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Win32Context.h: interface for the Win32Context class.



#include <deque>

#ifdef WINTHEMES
#include "Win32ThemeDLLWrapper.h"
#endif

namespace VCF
{


class GRAPHICSKIT_API Win32Image;
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
class GRAPHICSKIT_API Win32Context  : public Object, public ContextPeer {
public:
	Win32Context();

	/**
	* creates a new HDC from scratch
	*/
	Win32Context( const unsigned long& width, const unsigned long& height );

	Win32Context( OSHandleID contextID );

	virtual ~Win32Context();

public:
	/**
	* 
	* 
	*/
	virtual void setContext( GraphicsContext* context );

	/**
	* 
	* 
	*/
	virtual GraphicsContext* getContext();

	/**
	* 
	* 
	*/
	virtual OSHandleID getContextID();

	/**
	* 
	* 
	*/
	virtual void setContextID( OSHandleID handle );

	/**
	* 
	* 
	*/
	void init();

	/**
	* 
	* 
	*/
	virtual void setOrigin( const double& x, const double& y );

	/**
	* 
	* 
	*/
	virtual Point getOrigin();

	/**
	* 
	* 
	*/
	virtual bool isAntiAliasingOn(){
		return false;
	}
	
	/**
	* 
	* 
	*/
	virtual void setAntiAliasingOn( bool antiAliasingOn ) {} //no-op for now
	

	/**
	* 
	* 
	*/
	virtual bool prepareForDrawing( long drawingOperation );

	/**
	* 
	* 
	*/
	virtual void finishedDrawing( long drawingOperation );

	/**
	* 
	* 
	*/
	virtual bool isMemoryContext();

	/**
	* 
	* 
	*/
	virtual void copyContext( const Rect& sourceRect, const Rect& destRect,
	                          ContextPeer* sourceContext );


	/**
	* 
	* 
	*/
	virtual void textAt( const Rect& bounds, const String & text, const long& drawOptions=0 );

	/**
	* 
	*/
	virtual double getTextWidth( const String& text );

	/**
	* 
	*/
	virtual double getTextHeight( const String& text );


	/**
	* 
	*/
	virtual void lineTo( const double & x, const double & y );

	/**
	* 
	*/
	virtual void moveTo( const double & x, const double & y );

	/**
	* 
	*/
	virtual void rectangle( const double & x1, const double & y1, const double & x2, const double & y2 );

	/**
	* 
	*/
	virtual void roundRect( const double & x1, const double & y1, const double & x2, const double & y2,
	                        const double & xc, const double & yc );


	/**
	* 
	*/
	virtual void ellipse( const double & x1, const double & y1, const double & x2, const double & y2 );

	/**
	* 
	*/
	virtual void arc( const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
	                  const double & y3, const double & x4, const double & y4 );

/*
	virtual void pie( const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
	                  const double & y3, const double & x4, const double & y4 );

	virtual void chord( const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
	                    const double & y3, const double & x4, const double & y4 );
*/

	/**
	* 
	*/
	virtual void polyline( const std::vector<Point>& pts );

	/**
	* 
	*/
	virtual void curve( const double & x1, const double & y1, const double & x2, const double & y2,
	                    const double & x3, const double & y3, const double & x4, const double & y4 );

	/**
	* 
	* 
	*/
	virtual void drawImage( const double& x, const double& y, Rect* imageBounds, Image* image );


	/* utility functions */

	/**
	* 
	* 
	*/
	void copyToImage( Win32Image* image );

	/**
	* make sure we always have the HDC ( device context handle ) we need.
	* Normally the paint function already receives the correct handle
	* so this is a no-op (does nothing).
	* In the case of a control we may need to get a different HDC, for example when 
	* painting under a mouse move event or getting other informations depending
	* on the device context.
	* @see releaseHandle()
	*/
	virtual void checkHandle(){};

	/**
	* Does the opposite operation of checkHandle(), i.e. restores
	* the previous HDC if it has been changed by checkHandle().
	* Normally the paint function already receives the correct handle 
	* in checkHandle() so this one too is a no-op.
	* @see checkHandle()
	*/
	virtual void releaseHandle();

	/**
	* 
	* 
	*/
	virtual bool isXORModeOn();

	/**
	* 
	* 
	*/
	virtual void setXORModeOn( const bool& XORModeOn );

	/**
	* 
	* 
	*/
	virtual void setTextAlignment( const bool& alignTobaseline );

	/**
	* 
	* 
	*/
	virtual bool isTextAlignedToBaseline();

	/**
	* 
	* 
	*/
	virtual void setClippingPath( Path* clippingPath );

	/**
	* 
	* 
	*/
	virtual void setClippingRect( Rect* clipRect );


	/**
	* 
	*/
	virtual void drawThemeSelectionRect( Rect* rect, DrawUIState& state );

	/**
	* 
	*/
	virtual void drawThemeFocusRect( Rect* rect, DrawUIState& state );

	/**
	* 
	*/
	virtual void drawThemeButtonRect( Rect* rect, ButtonState& state );

	/**
	* 
	*/
	virtual void drawThemeCheckboxRect( Rect* rect, ButtonState& state );

	/**
	* 
	*/
	virtual void drawThemeRadioButtonRect( Rect* rect, ButtonState& state );

	/**
	* 
	*/
	virtual void drawThemeComboboxRect( Rect* rect, ButtonState& state );

	/**
	* 
	*/
	virtual void drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state );

	/**
	* Draws a button that is used to open up more details, for example
	* the button that opens up a tree node to reveal it's children, that is compliant
	* with the native windowing systems default look and feel.
	* On Win32 this is usually represented by the "+" and "-" look as found on
	* the tree controls, while on OSX it is the little triangles
	*/
	virtual void drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state );

	/**
	* Draws a tab, the part of the TabbedPages control that acts like a
	* little button to activate a page, that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeTab( Rect* rect, TabState& state );

	/**
	Draws a tab page - the page on which other controls for the page are
	parented to, that is compliant
	with the native windowing systems default look and feel
	*/
	virtual void drawThemeTabPage( Rect* rect, DrawUIState& state );

	/**
	* Draws a tick mark, like that used for a slider control, that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeTickMarks( Rect* rect, SliderState& state );
	
	/**
	* Draws a slider control, like that used for a slider control, that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeSlider( Rect* rect, SliderState& state );
	
	/**
	* Draws a progress bar control, that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeProgress( Rect* rect, ProgressState& state );	
	
	/**
	* 
	* 
	*/
	virtual void drawThemeImage( Rect* rect, Image* image, DrawUIState& state );

	/**
	* draws a header control that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeHeader( Rect* rect, ButtonState& state );

	/**
	* draws edges, useful for separators, that is compliant
	* with the native windowing systems default look and feel.
	* use a mask or 1 or more values of type ContextPeer::EdgeType
	* to indicate which sides of the rect to draw an edge on
	*/
	virtual void drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle );

	/**
	* Draws a size gripper for resizing a control/window that is compliant
	* with the native windowing systems default look and feel
	*/
	virtual void drawThemeSizeGripper( Rect* rect, DrawUIState& state );

	/**
	* Draws a them compliant background
	*/
	virtual void drawThemeBackground( Rect* rect, BackgroundState& state );

	/**
	* Draws the background appropriate for a menu item that is compliant
	* with the native windowing systems default look and feel.
	* This is typically called first by a menu item to give it a standard
	* look and feel in it's background before drawing any thing else
	*/
	virtual void drawThemeMenuItem( Rect* rect, MenuState& state );

	/**
	* 
	* 
	*/
	virtual void drawThemeText( Rect* rect, TextState& state );


protected:

	/**
	* 
	* 
	*/
	void prepareDCWithContextFont( HFONT& fontHandle );

	/**
	* 
	* 
	*/
	HDC getDC();

	/**
	* Utility function to draw a transparent bitmap
	*/
	static void drawTransparentBitmap( HDC hdc, HBITMAP hBitmap, long xStart,
	                                   long yStart, COLORREF cTransparentColor );

#ifdef WINTHEMES
	/**
	* AutoPointer to a wrapper for the UxTheme.dll
	*/
	static std::auto_ptr<Win32ThemeDLLWrapper> pThemeDLL_;
#endif


private:
#ifdef WINTHEMES
	/**
	* Draw a themed button using the UxTheme.dll.
	* Remarks: In case of an error parts of the button may have been
	*          already drawn.
	*          This will only happen if the DLL is present but not
	*          fully implemented.
	*@return bool, false if themed drawing was not possible.
	*/
	bool drawThemeButtonRectDLL( Rect* rect, ButtonState& state );
#endif

protected:
	HRGN clipRGN_;

	bool pathStarted_;

	Point oldOrigin_;
	Point origin_;
	bool inFillPath_;
	HDC dc_;
	HBITMAP memBitmap_;
	HBITMAP originalBitmap_;

	HBRUSH currentHBrush_;
	HPEN currentHPen_;
	HFONT currentHFont_;

	int currentDCState_;

	bool isMemoryCtx_;
	GraphicsContext* context_;
	bool isXORModeOn_;
	double strokeWidth_;

	bool alignToBaseline_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/01/02 03:04:26  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/19 04:05:05  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.5  2004/11/10 02:08:41  marcelloptr
*minor change on a comment as for doxygen
*
*Revision 1.2.2.4  2004/11/09 18:47:20  chriskr
*changed class name VisualStylesXP to Win32ThemeDLLWrapper
*
*Revision 1.2.2.3  2004/11/08 18:17:23  marcelloptr
*more documentation
*
*Revision 1.2.2.2  2004/11/06 20:22:32  chriskr
*added dynamic linking to UxTheme.dll
*added example xp theme support for drawThemeButtonRect()
*
*Revision 1.2.2.1  2004/10/27 03:12:18  ddiego
*integrated chrisk changes
*
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/15 01:52:54  ddiego
*added drawThemeComboboxRect implementation so a combobox
*control draws itself correctly.
*
*Revision 1.1.2.3  2004/07/09 03:39:30  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2  2004/04/29 04:10:28  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.23.4.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.23  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.22.2.2  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.22.2.1  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.22  2003/08/09 02:56:44  ddiego
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
*Revision 1.21.2.2  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.21.2.1  2003/06/05 03:48:53  ddiego
*added a way to get part of a graphics context into an image - no
*implementation yet.
*
*Revision 1.21  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.20.2.3  2003/05/13 03:57:13  ddiego
*cleaned up the GraphicsKit, got rid of some old crap files, cleaned
*up the ContextPeer so that tehre are fewer methods to implement, and
*moved the repetitive fillPath and strokePath code that was copied into
*all the context peers back into the GraphicsContext where it belongs
*
*Revision 1.20.2.2  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.20.2.1  2003/03/12 03:11:09  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.20  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.19.2.4  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.19.2.3  2003/01/08 00:19:46  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.19.2.2  2002/12/28 21:51:18  marcelloptr
*Fixes and improvements for WM_COPYDATA, Point, Rect, Size, GraphicsContext and StringUtils
*
*Revision 1.19.2.1  2002/12/27 23:04:40  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.19  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.18.10.2  2002/09/30 21:08:18  ddiego
*piddling stuff
*
*Revision 1.18.10.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.18  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.17.4.1  2002/04/27 15:52:19  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.17  2002/01/31 05:46:14  ddiego
*fixed resource leak with GraphicsContexts used as memory GC's
*Works fine in 98 with no drop of GDI resources.
*
*Revision 1.16  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32CONTEXT_H__


