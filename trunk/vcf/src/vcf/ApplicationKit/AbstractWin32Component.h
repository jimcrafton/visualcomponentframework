#ifndef _VCF_ABSTRACTWIN32COMPONENT_H__
#define _VCF_ABSTRACTWIN32COMPONENT_H__
//AbstractWin32Component.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class Control;

class Font;

/**
*This is the core Win32 control class peer, does most of the handling
*of WM_XXX messages.
*/
class APPLICATIONKIT_API AbstractWin32Component : public Win32Object, public ControlPeer  {
public:
	/**
	* identifiers to specify what to paint
	*@see AbstractWin32Component::doControlPaint()
	*/
	enum {
		cpBorderOnly = 0,
		cpControlOnly,
		cpBorderAndControl
	};

	AbstractWin32Component();

	AbstractWin32Component( Control* component );

	virtual ~AbstractWin32Component();

public:
	virtual void create( Control* owningControl );

	virtual void destroyControl();

	virtual OSHandleID getHandleID();

	virtual VCF::String getText();

	virtual void setText( const VCF::String& text );

	virtual void setBounds( VCF::Rect* rect );

	virtual VCF::Rect getBounds();

	virtual void setVisible( const bool& visible );

	virtual bool getVisible();

	virtual VCF::Control* getControl();

	virtual void setControl( VCF::Control* component );

	virtual void setParent( VCF::Control* parent );

	virtual VCF::Control* getParent();

	virtual bool isFocused();

	virtual void setFocused();

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual void setFont( Font* font );


	virtual void repaint( Rect* repaintRect, const bool& immediately );

	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);

	virtual String toString();

	virtual void setCursor( Cursor* cursor );

	virtual bool beginSetBounds( const uint32& numberOfChildren );

	virtual void endSetBounds();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );

	virtual void setBorder( Border* border );

	virtual void preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect );
	
	virtual void postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect );
	
	/**
	* manages a paint message for a control.
	* it prepares the Graphics context for the control so the correct device context handle is used.
	* It garantees that the state of the Graphics context doesn't change during tha paint operation.
	* 
	*@param HDC paintDC, the HDC given by the system with the paint message.
	*@see GraphicsContext::saveState()
	*/
	HDC doControlPaint( HDC paintDC, RECT paintRect, RECT* exclusionRect, int whatToPaint );

	void updatePaintDC( HDC paintDC, RECT paintRect, RECT* exclusionRect );

protected:
	/**
	*
	*
	*/
	LRESULT handleNCPaint( WPARAM wParam, LPARAM lParam );

	/**
	*
	*
	*/
	LRESULT handleNCCalcSize( WPARAM wParam, LPARAM lParam );

protected:
	void init();
	HDC memDC_;
	HBITMAP originalMemBMP_;
	HBITMAP memBMP_;
	bool mouseEnteredControl_;	
	int memDCState_;
	bool destroyed_;

	//this starts off false - the control just ignores messages UNTIL 
	//it recv's a VCF_CONTROL_CREATE message - at that point it's
	//set to true
	bool canProcessMessages_;

	std::vector<MSG>* cachedMessages_;

	void registerForFontChanges();
	void onControlFontChanged( Event* event );

};


}; // namespace VCF


#endif // _VCF_ABSTRACTWIN32COMPONENT_H__

/**
$Id$
*/
