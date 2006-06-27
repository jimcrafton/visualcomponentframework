#ifndef _VCF_LIGHTWEIGHTCOMPONENT_H__
#define _VCF_LIGHTWEIGHTCOMPONENT_H__
//LightweightComponent.h

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

/**
\class LightweightComponent LightweightComponent.h "vcf/ApplicationKit/LightweightComponent.h"
*/
class APPLICATIONKIT_API LightweightComponent : public Object, public ControlPeer {
public:
	LightweightComponent( Control* component );

	virtual ~LightweightComponent();

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

	void repaint( Rect* repaintRect, const bool& immediately );

	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();

	virtual void setCursor( Cursor* cursor );

	virtual bool beginSetBounds( const uint32& numberOfChildren );

	virtual void endSetBounds();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );

	virtual void preChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* childClipRect );

	virtual void postChildPaint( GraphicsContext* graphicsContext, Control* child, Rect* oldClipRect );
	/**
	* sets the control's border.
	* Called by the control when it's border object changes.
	* This implementation is a no-op because 
	* a lightweight component only needs to set border_
	* but it doesn't need an indipendent peer.
	*@param Border* border, the border object to assign.
	*/
	virtual void setBorder( Border* border ) {} //no-op

private:
	VCF::Control* getHeavyWeightParent();
	VCF::Control* component_;
	VCF::Rect bounds_;
	bool visible_;
	bool enabled_;
	bool focused_;
	std::vector<bool> hiddenControls_;
};


}; // namespace VCF


#endif // _VCF_LIGHTWEIGHTCOMPONENT_H__

/**
$Id$
*/
