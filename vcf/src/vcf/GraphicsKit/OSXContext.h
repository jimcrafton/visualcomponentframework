#ifndef _VCF_OSXCONTEXT_H__
#define _VCF_OSXCONTEXT_H__
//OSXContext.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

class GraphicsContext;


class OSXContext  : public ContextPeer, public Object {
public:

	
	enum LastPrimitive{
		lpNone, 
		lpMove, 
		lpLine
	};


	OSXContext();
	/**
	*Creates a new HDC from scratch
	*/
	OSXContext( const unsigned long& width, const unsigned long& height );

	OSXContext( const unsigned long& contextID );

	virtual ~OSXContext();

	virtual void setContext( GraphicsContext* context );

	virtual GraphicsContext* getContext();

	virtual unsigned long getContextID();

	virtual void setContextID( const unsigned long& handle );

	virtual void textAt( const Rect& bounds, const String & text, const long& drawOptions=0 );

	virtual double getTextWidth( const String& text );

	virtual double getTextHeight( const String& text );

    virtual void rectangle(const double & x1, const double & y1, const double & x2, const double & y2);

	virtual void roundRect(const double & x1, const double & y1, const double & x2, const double & y2,
							 const double & xc, const double & yc);

    virtual void ellipse(const double & x1, const double & y1, const double & x2, const double & y2 );

	virtual void arc(const double & x1, const double & y1, const double & x2, const double & y2, const double & x3,
						 const double & y3, const double & x4, const double & y4);

    virtual void polyline(const std::vector<Point>& pts);

    virtual void curve(const double & x1, const double & y1, const double & x2, const double & y2,
                         const double & x3, const double & y3, const double & x4, const double & y4);

    virtual void lineTo(const double & x, const double & y);

    virtual void moveTo(const double & x, const double & y);

	void init();

	virtual void setOrigin( const double& x, const double& y );

	virtual Point getOrigin();

	virtual void copyContext( const Rect& sourceRect,
								const Rect& destRect,
								ContextPeer* sourceContext );

	virtual bool isMemoryContext();

	virtual bool prepareForDrawing( long drawingOperation );

	virtual void finishedDrawing( long drawingOperation );

	virtual void drawImage( const double& x, const double& y, Rect* imageBounds, Image* image );

	virtual void checkHandle();

	virtual void releaseHandle();

	virtual bool isXORModeOn();

	virtual void setXORModeOn( const bool& XORModeOn );

	virtual bool isAntiAliasingOn() {
		return antialiasingOn_;
	}
	
	virtual void setAntiAliasingOn( bool antiAliasingOn );
	
	virtual void setTextAlignment( const bool& alignTobaseline );

	virtual bool isTextAlignedToBaseline();

	virtual void setClippingPath( Path* clippingPath );

	virtual void setClippingRect( Rect* clipRect );
	
	
	
	virtual void drawThemeSelectionRect( Rect* rect, DrawUIState& state );
	
	virtual void drawThemeFocusRect( Rect* rect, DrawUIState& state );

	virtual void drawThemeButtonRect( Rect* rect, ButtonState& state );

	virtual void drawThemeCheckboxRect( Rect* rect, ButtonState& state );

	virtual void drawThemeRadioButtonRect( Rect* rect, ButtonState& state );
	
	virtual void drawThemeComboboxRect( Rect* rect, ButtonState& state );

	virtual void drawThemeScrollButtonRect( Rect* rect, ScrollBarState& state );

	virtual void drawThemeDisclosureButton( Rect* rect, DisclosureButtonState& state );

	virtual void drawThemeTab( Rect* rect, TabState& state );

	virtual void drawThemeTabPage( Rect* rect, DrawUIState& state );

	virtual void drawThemeTickMarks( Rect* rect, SliderState& state );

	virtual void drawThemeSlider( Rect* rect, SliderState& state );
	
	virtual void drawThemeProgress( Rect* rect, ProgressState& state );	
	
	virtual void drawThemeImage( Rect* rect, Image* image, DrawUIState& state );

	virtual void drawThemeHeader( Rect* rect, ButtonState& state );

	virtual void drawThemeEdge( Rect* rect, DrawUIState& state, const long& edgeSides, const long& edgeStyle );

	virtual void drawThemeSizeGripper( Rect* rect, DrawUIState& state );

	virtual void drawThemeBackground( Rect* rect, BackgroundState& state );

	virtual void drawThemeMenuItem( Rect* rect, MenuState& state );

	virtual void drawThemeText( Rect* rect, TextState& state );
	
	
	void setCGContext( CGContextRef cgRef, GrafPtr port, const Rect& ownerRect  );
	void setPortFromImage( GrafPtr port, uint32 width, uint32 height );
protected:
	CGContextRef contextID_;
    GrafPtr grafPort_;
	unsigned char* inMemoryImage_;
    ulong32 imgWidth_;
    ulong32 imgHeight_;
	GraphicsContext* context_;
	long currentDrawingOperation_;
	ATSUTextLayout textLayout_;
	VCF::Point origin_;
    bool xorModeOn_;
    Rect ownerRect_;
	LastPrimitive lastPrimitive_;
	VCF::Point lastPrimitiveP1_;
	VCF::Point lastPrimitiveV1_;
	bool antialiasingOn_;




	void atsuDrawTextInBox(	const VCF::Rect& rect, const long& drawOptions );

	double getLayoutWidth( ATSUTextLayout layout );

	void setLayoutWidth( ATSUTextLayout layout, double width );
	VCF::Size getLayoutDimensions( const String& text );
	
	void endLastPrimitive();
	void finishLastPrimitive(const double & x, const double & y);
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/27 03:12:18  ddiego
*integrated chrisk changes
*
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.8  2004/07/27 04:26:05  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.7.2.5  2004/07/06 03:27:13  ddiego
*more osx updates that add proper support
*for lightweight controls, some fixes to text layout, and some window painting issues. Also a fix
*so that controls and windows paint either their default theme background or their background
*color.
*
*Revision 1.1.2.7.2.4  2004/06/27 18:19:16  ddiego
*more osx updates
*
*Revision 1.1.2.7.2.3  2004/06/20 00:36:11  ddiego
*finished the new theme API updates
*
*Revision 1.1.2.7.2.2  2004/06/16 05:18:56  ddiego
*further updates to OSX theme compliant drawing code
*
*Revision 1.1.2.7.2.1  2004/06/15 04:04:38  ddiego
*revamped osx theme drawing API
*
*Revision 1.1.2.7  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.6  2004/05/31 13:20:58  ddiego
*more osx updates
*
*Revision 1.1.2.5  2004/05/23 14:12:18  ddiego
*osx updates
*
*Revision 1.1.2.4  2004/05/16 02:39:10  ddiego
*OSX code updates
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.3  2004/02/23 05:51:42  ddiego
*basic GraphicsKit implementation done for OSX
*
*Revision 1.1.2.2  2004/02/22 06:50:12  ddiego
*more progress with the OSX GraphicsKit - almost done!
*
*Revision 1.1.2.1  2004/02/21 03:27:06  ddiego
*updates for OSX porting
*
*/


#endif // _VCF_OSXCONTEXT_H__


