#ifndef _VCF_GTKCONTEXT_H__
#define _VCF_GTKCONTEXT_H__
//GTKContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class GTKImage;


/**

*/
class GRAPHICSKIT_API GTKContext  : public Object, public ContextPeer  {
public:

	GTKContext();

	GTKContext( const unsigned long& width, const unsigned long& height );

	GTKContext( const unsigned long& contextID );

	virtual ~GTKContext();

	void init();

	virtual void setContext( GraphicsContext* context );

	virtual GraphicsContext* getContext();

	virtual unsigned long getContextID();

	virtual void setContextID( const unsigned long& handle );

	virtual void setClippingPath( Path* clippingPath );

	virtual void setClippingRect( Rect* clipRect );

	virtual bool prepareForDrawing( long drawingOperation );

	virtual void finishedDrawing( long drawingOperation );


	virtual void drawImage( const double& x, const double& y, Rect* imageBounds, Image* image );

    virtual void textAt( const Rect& bounds, const String & text, const long& drawOptions=0 );

	virtual double getTextWidth( const String& text );

	virtual double getTextHeight( const String& text );

    virtual void rectangle(const double & x1, const double & y1, const double & x2, const double & y2);

    virtual void ellipse(const double & x1, const double & y1, const double & x2, const double & y2 );

	virtual void arc( const double & x1, const double & y1, const double & x2, const double & y2,
                      const double & x3, const double & y3, const double & x4, const double & y4 );


    virtual void polyline( const std::vector<Point>& pts);

    virtual void curve(const double & x1, const double & y1, const double & x2, const double & y2,
                         const double & x3, const double & y3, const double & x4, const double & y4);

    virtual void lineTo(const double & x, const double & y);

    virtual void moveTo(const double & x, const double & y);

	virtual void setOrigin( const double& x, const double& y );

	virtual Point getOrigin();

	virtual void copyContext( const Rect& sourceRect,
											const Rect& destRect,
											ContextPeer* sourceContext );

	virtual bool isMemoryContext();

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

	virtual void drawTickMarks( Rect* rect, const SliderInfo& sliderInfo  );

	virtual void drawSliderThumb( Rect* rect, const SliderInfo& sliderInfo );

	virtual void drawSlider( Rect* rect, const SliderInfo& sliderInfo );

	virtual void drawHeader( Rect* rect );

	virtual void drawEdge( Rect* rect, const long& edgeSides, const long& edgeStyle );

	virtual void drawSizeGripper( Rect* rect );

	virtual void drawControlBackground( Rect* rect );

	virtual void drawWindowBackground( Rect* rect );

	virtual void drawMenuItemBackground( Rect* rect, const bool& selected );

	void setParentImage( GTKImage* image ) {
		parentImage_ = image;
	}

	GdkDrawable* getDrawable() {
		return drawable_;
	}

	GdkGC* getGC() {
		return gdkGC_;
	}

protected:

	GdkDrawable* drawable_;
	GdkGC* gdkGC_;
	PangoContext* pangoCtx_;
	PangoLayout* pangoLayout_;

	unsigned long pixmapWidth_;
	unsigned long pixmapHeight_;


	//std::vector<PointOperation*> pathOperations_;
	//std::vector<TextOperation*> textOperations_;

	Point currentMoveTo_;
	Point oldOrigin_;
	Point origin_;

	bool inFillPath_;
	bool isMemoryCtx_;
	//bool pathStarted_;
	bool isXORModeOn_;
	bool alignToBaseline_;


	GraphicsContext* context_;

	GTKImage* parentImage_;

	GtkStyle* getGTKStyle( GtkWidget* widget );
	GtkStateType getGTKState( GtkWidget* widget );

	//void clearBuffer();
	//void clearPathBuffer();
	//void clearTextBuffer();
	//void testBuffer();

	//void execPathOperations();
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.2.1  2003/11/01 20:39:35  ddiego
*added gtk toolbar - no implementation yet
*
*Revision 1.4  2003/08/09 02:56:44  ddiego
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
*Revision 1.3.2.2  2003/06/01 16:43:58  ddiego
*further GTK support added
*
*Revision 1.3.2.1  2003/05/30 04:13:10  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.3  2003/05/17 20:37:11  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.2  2003/04/17 04:29:48  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.2.2.1  2003/03/12 03:10:53  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.2  2003/02/23 05:08:14  ddiego
*finished up the GTKImage class. Now putting in text rendering with pango support
*
*Revision 1.1.2.1  2003/02/20 02:46:02  ddiego
*added in the base files for supporting a GTK peer implementation. Core parts
*of the GTKContext work (basic line primitives), and working on the GTKImage
*class.
*
*Auto generated header for class GTKContext
*/


#endif // _VCF_GTKCONTEXT_H__


