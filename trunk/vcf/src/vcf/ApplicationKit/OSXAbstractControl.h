#ifndef _VCF_OSXABSTRACTCONTROL_H__
#define _VCF_OSXABSTRACTCONTROL_H__
//OSXAbstractControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/*


namespace VCF {

class OSXAbstractControl : public Object, public ControlPeer {
public:

	OSXAbstractControl();

	virtual ~OSXAbstractControl();

	virtual long getHandleID() {
		return (long)controlRef_;
	}

	virtual void create( Control* owningControl );

	virtual void destroyControl();

	virtual String getText();

	virtual void setText( const String& text );

	virtual void setBounds( Rect* rect );

	virtual bool beginSetBounds( const ulong32& numberOfChildren );

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

	virtual void repaint( Rect* repaintRect=NULL );

	virtual void keepMouseEvents();

	virtual void releaseMouseEvents();

	virtual void translateToScreenCoords( Point* pt );

	virtual void translateFromScreenCoords( Point* pt );

	static OSXAbstractControl* getOSXControlFromControlRef( ControlRef controlRef );

	Rect internal_getBounds() {
		return bounds_;
	}

	void internal_setBounds( const Rect& bounds ) {
		bounds_ = bounds;
	}
protected:

	typedef std::map<ControlRef,OSXAbstractControl*> OSXControlMap;

	static void registerOSXControl( OSXAbstractControl* gtkControl );
	static void unRegisterOSXControl( OSXAbstractControl* gtkControl );

	static OSXControlMap gtkControlMap;

	OSXAbstractControl* parent_;
	bool enabled_;

	ControlRef controlRef_;
	Control* control_;

	Rect bounds_;

	bool repainted_;

};


}; //end of namespace VCF
*/


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/06/29 05:15:41  marcelloptr
*fixed some white spaces
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/04/30 05:44:33  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.1  2004/02/24 01:42:43  ddiego
*initial OSX ApplicationKit port checkin
*
*/


#endif // _VCF_OSXABSTRACTCONTROL_H__


