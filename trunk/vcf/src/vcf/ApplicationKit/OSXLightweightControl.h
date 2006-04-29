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

class OSXLightweightControl : public Object, public ControlPeer {
public:
	OSXLightweightControl( Control* component );

	virtual ~OSXLightweightControl();

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

	virtual void setCursor( Cursor* cursor );

	virtual bool beginSetBounds( const ulong32& numberOfChildren );

	virtual void endSetBounds();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );
	
	VCF::Control* getHeavyWeightParent();
	
	virtual void setBorder( Border* border ){}
	
	virtual void preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect );
	
	virtual void postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect );
	
protected:
	
	VCF::Control* component_;
	VCF::Rect bounds_;
	bool visible_;
	bool enabled_;
	bool focused_;
};

};


#endif // _VCF_OSXLIGHTWEIGHTCONTROL_H__

/**
$Id$
*/

