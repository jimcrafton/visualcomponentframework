#ifndef _STATUSBAR_H__
#define _STATUSBAR_H__
//StatusBar.h

/*
Copyright 2000-2008 The VCF Builder Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#define STATUSBAR_CLASSID			"fef64f70-d3f2-4cd3-885d-641c53ea503a"

namespace VCF {


class APPLICATIONKIT_API StatusBar : public VCF::CustomControl {
public:
	/**
	* constructor.
	* This creates the control container and adds to it a 
	* child status label control.
	*/
	StatusBar();



	enum {
		PrimaryPane = (uint32)-1
	};

	/**
	* te container internally used by this control. 
	* It is a minor variation of the VCF::StandardContainer
	* in the way it resizes its children.
	* IT creates a spacing of 2 pixels between them.
	*/
	class Container : public VCF::StandardContainer {
	public:
		virtual void resizeChildren( VCF::Control* control );
	};

	/**
	* adds a child status control to this control's container
	* and assignes to it a width and a text.
	* @param const double& width, the width to assign to the created child control.
	* The default is -1 to let this child control to have its preferred width.
	* @param const VCF::String& text, the text for this child control to display.
	* The default is an empty string.
	*/
	void addStatusPane( const double& width=-1.0, const String& text=""  );

	void insertStatusPaneWithWidth( const uint32& index, const String& text, const double& width );
	void insertStatusPane( const uint32& index, const String& text );

	/**
	* remove a child status control from this control's container.
	* @param ulong index, the index of the control to remove.
	*/
	void removeStatusPane( const uint32& index );

	uint32 getStatusPaneCount();
	
	String getStatusPaneText( const uint32& index );

	/**
	* writes the status text on the control indexed by index
	* @param int index, the index of the control in this control's container
	* @param const VCF::String& text, the text to write
	*/
	void setStatusPaneText( const uint32& index, const String& val );

	String getStatusText();
	void setStatusText( const String& val );
	

	/**
	* gets the pointer to the status control indexed by index
	* @param ulong index, the index of the control in this control's container.
	*/
	VCF::Control* getStatusPaneControl( const uint32& index );

	/**
	* paint this control and all its children status controls.
	* Overrides the default implementation for a Control.
	*/
	virtual void paint( VCF::GraphicsContext* ctx );
};

}; // namespace VCF




/**
$Id$
*/


#endif // _STATUSBAR_H__


