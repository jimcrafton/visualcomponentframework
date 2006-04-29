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


#endif // _VCF_OSXABSTRACTCONTROL_H__

/**
$Id$
*/
