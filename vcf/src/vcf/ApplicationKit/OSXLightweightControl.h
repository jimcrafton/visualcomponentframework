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

	void repaint( Rect* repaintRect=NULL );

	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();

	virtual void setCursor( Cursor* cursor );

	virtual bool beginSetBounds( const ulong32& numberOfChildren );

	virtual void endSetBounds();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );
	
	VCF::Control* getHeavyWeightParent();
	
	virtual void setBorder( Border* border ){}
protected:
	
	VCF::Control* component_;
	VCF::Rect bounds_;
	bool visible_;
	bool enabled_;
	bool focused_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/01/08 20:52:46  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.2  2004/08/07 17:15:07  ddiego
*added missing osx files and projects
*
*Revision 1.1.4.1  2004/08/07 16:32:50  ddiego
*added missing files
*
*Revision 1.1.2.1  2004/07/06 03:34:56  ddiego
*added new files for osx update, and added new
*project template files for creating VCF based projects with XCode.
*
*/


#endif // _VCF_OSXLIGHTWEIGHTCONTROL_H__


