#ifndef _VCF_OSXLIGHTWEIGHTCONTROL_H__
#define _VCF_OSXLIGHTWEIGHTCONTROL_H__
//OSXLightweightControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



namespace VCF
{

class OSXLightweightControl : public ControlPeer {
public:
	OSXLightweightControl( Control* component );

	virtual ~OSXLightweightControl();

	virtual void create( Control* owningControl );

	virtual void destroyControl();

	virtual OSHandleID getHandleID();

	virtual String getText();

	virtual void setText( const String& text );

	virtual void setBounds( Rect* rect );

	virtual bool beginSetBounds( const uint32& numberOfChildren );

	virtual void endSetBounds();

	virtual Rect getBounds();

	virtual void setVisible( const bool& visible );

	virtual bool getVisible();

	virtual Control* getControl();

	virtual void setControl( Control* component );

	virtual void setCursor( Cursor* cursor );

	virtual void setParent( Control* parent );

	virtual Control* getParent();

	virtual bool isFocused();

	virtual void setFocused();

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual void setFont( Font* font );

	virtual void repaint( Rect* repaintRect, const bool& immediately );

	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );

	virtual void setBorder( Border* border );
	
	virtual void preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect );
	
	virtual void postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect );	
protected:
	Control* getHeavyWeightParent();
	Control* component_;
	Rect bounds_;
	bool visible_;
	bool enabled_;
	bool focused_;
	std::vector<bool> hiddenControls_;
};

};


#endif // _VCF_OSXLIGHTWEIGHTCONTROL_H__

/**
$Id$
*/

