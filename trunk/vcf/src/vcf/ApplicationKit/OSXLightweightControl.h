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
*Revision 1.5  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.2  2006/01/09 02:22:31  ddiego
*more osx code
*
*Revision 1.4.2.1  2005/11/10 04:43:27  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.4  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.2  2005/06/29 05:15:41  marcelloptr
*fixed some white spaces
*
*Revision 1.2.4.1  2005/05/08 19:55:31  ddiego
*osx updates, not yet functional.
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



