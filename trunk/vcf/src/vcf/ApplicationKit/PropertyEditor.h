#ifndef _VCF_PROPERTYEDITOR_H__
#define _VCF_PROPERTYEDITOR_H__
//PropertyEditor.h

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

class Property;
class Control;
class GraphicsContext;
class DrawUIState;


/**
\class PropertyEditor PropertyEditor.h "vcf/ApplicationKit/PropertyEditor.h"
This is the common base class for any editor that is specific
of any property.
@see VCF::Property

Any property, and in general any kind of data, can be changed 
through an appropriate GUI interface called editor. A text 
editor is good for many kind of data, but some of them are
more easily chaged through more specific editors. For example 
a ComboBox control can be considered an appropriate editor for
any boolean value, or for any enumerated value.
The VCF library makes readily available some of them.

the editor is used by the host in order to display the 
property content, retrieve possible values, and to 
provide a possible UI for performing the editing. The
steps are something like this:
\li the host selects a source object
\li the host retrieves a list of all properties for the source objects
\li for each property the 
@see Object::getClass
@see Class
@see Property
*/
class APPLICATIONKIT_API PropertyEditor  {
public:

	/**
	Defines a set of different attributes that the 
	getAttributes() can return. 
	*/
	enum PropertyAttributes {
		/**
		Indicates that the property editor can return a
		vector of string values that represent possible
		values for the property. For example, a color 
		property editor might return a list of color
		names. A Font editor might return a list of 
		system fonts.
		*/
		paHasValues = 0x01,
		/**
		Indicates that the values returned by the editor need
		to be sorted. The sort process should call the 
		sort() method while iterating through the list.
		*/
		paSortValues = 0x0100,

		/**
		Indicates that the source object's property itself
		has sub properties. Things like a font or color property
		may use this to indicate separate elements that can be set.
		*/
		paHasSubProperties = 0x02,

		/**
		Indicates whether or not the editor allows multiple selection.
		If is does then the implementor needs to implement setSources
		*/
		paAllowsMultiSelect = 0x04,

		/**
		Indicates that the editor is read only - the value cannot be changed
		is only for display.
		*/
		paReadOnly = 0x08,

		/**
		Indicates that the editor can paint it's representation when not active
		*/
		paNeedsCustomPaint = 0x010,

		/**
		This indicates that the implementor will popup a modal dialog when the 
		edit() method is called
		*/
		paUsesModalDialogForEditing = 0x020,

		/**
		This indicates that the property value needs to be cloned. It implies that
		the property is an Object of some type (if this is not the case 
		this indicates an error condition). The object should be cloned by a 
		call to the original object's Object::clone() method.
		*/
		paValueNeedsDuplicating = 0x040,

		paEditorRequestsProperty = 0x080,

		/**
		This indicates that the proeprty editor's value
		is part of a set of values, such as a bit mask.
		*/
		paCompositeValue = 0x0100,

		/**
		This indicates to the host that the property editor's 
		string description of the property should be used over
		the value that is retreived from calling Property::getDescription().
		*/
		paOverridePropertyDescription = 0x010000,

		/**
		This indicates to the host that the property editor's 
		string name of the property should be used over
		the value that is retreived from calling Property::getName().
		*/
		paOverridePropertyName = 0x020000

	};

	virtual ~PropertyEditor(){};


	/**
	This sets the current property instance for
	the property editor. This should \em only 
	get called if the property editor has the 
	paEditorRequestsProperty attribute set.
	*/
	virtual void setProperty( Property* property ) = 0;

	/**
	This method needs to be oveeriden so to specify when two PropertyEditor(s)
	can be considered equal.
	*/
	virtual bool equalTo( PropertyEditor* editor ) = 0;

	/**
	This method returns a mask of potential attributes. 
	*/
	virtual int getAttributes() = 0;

	/**
	Don't call this - this is used strictly by the framework.
	*/
	virtual void internal_setPropertyType( const String& type ) = 0;

	/**
	Returns the property type that this editor instance is associated with.
	*/
	virtual String getPropertyType() = 0;


	/**
	returns the root component that is being edited in a 
	form designer. This may or may not be a control.
	*/
	virtual Component* getRootDesignerComponent() = 0;

	/**
	Sets the root component that is being edited in a 
	form designer. This may or may not be a control.
	This root component is then used by some property editor's 
	to enumerator choices for assign values to properties. For example
	a component proeprty editor might try and find all sub components
	of the root component whose class name matches a certain criteria
	and disply these as possible choices to assign a value to the
	property editor.
	*/
	virtual void setRootDesignerComponent( Component* rootDesigner )  = 0;

	/**
	
	Returns a control instance that belongs to this editor. This control
	instance is managed by the tool using this property editor so
	you just need to create it. This may be called multiple times, it is the
	callers responsibility to delete the control, the editor implementor does 
	not need to worry about this. For simple editors this may return null
	which will mean the implementation of the UI conntrol is up to the
	host environment. Typically editors for things like numbers, text, 
	etc, will by default use an edit control or, if the property editor
	support a list of values, a combo box.
	@return Control a new instance of the control for this editor
	or NULL if the editor doesn't support this.
	*/
	virtual Control* createEditingControl() = 0;


	/**
	
	This method is used to edit the property value. This is an optional method 
	to implement, and only needs to be done if createEditingControl() returns
	a non null value. If createEditingControl() is NULL then it's assumed that
	the actual editing process will be completely handled by the host of the
	property editor.
	
	If the implementor does edit this method, then it's up to the implemementor 
	to properly transfer the contents of the propert value to the control.
	*/
	virtual void edit() = 0;

	/**
	Paints a representation of the editor. This will only get called if
	needsCustomPaint() method returns true. This is for custom painting of 
	the property editor when it is \em not being edited.
	*/
	virtual void paintValue( VariantData* value, GraphicsContext* context, const Rect& bounds, const DrawUIState& state ) = 0;	

	/**
	Returns the value for the property. Note that this value is completely 
	independant of the actual value that may be crurently stored in the 
	source object's property. The assignment of this value to the source's
	property is up to the tool/IDE/etc that is using this interface.
	*/
	virtual VariantData* getValue() = 0;

	/**
	Set's the value on the property editor
	*/
	virtual void setValue( VariantData* value ) = 0;

	/**
	Like getValue(), but this returns the value in text format.
	This value is used for display purposes if the editor doesn't
	support custom painting.
	*/
	virtual String getValueAsText() = 0;

	/**
	Like setValue() but allows the value to be a string.
	*/
	virtual void setValueAsText( const String& textValue ) = 0;

	/**
	Returns an array of potential values for the property.
	Only usable if the PropertEditor::paHasValues bit is set.
	@see PropertEditor::paHasValues
	*/
	virtual std::vector<String> getStringValues() = 0;

	/**
	Returns a array of proeprty editors from the current value
	of this editor. The requirement, of course, is that the
	variant data that is returned by getValue() is a pdObject.
	This is not meaningful to call unless PropertEditor::paHasSubProperties
	is set.
	@see PropertEditor::paHasSubProperties
	*/
	virtual std::vector<PropertyEditor*> getSubProperties() = 0;

	/**
	only implement this if sortValues() returns true. If this is 
	the case, then return true if strVal1 is greater than strVal2.
	*/
	virtual bool sort( const String& strVal1, const String& strVal2 ) = 0;
	
	/**
	This returns a string that describes the property. A host that
	displays a UI should first try and call the property's 
	Property::getDescription() method. If this returns an empty string,
	then the host should call the property editor's getPropertyDescription().
	@see Property::getDescription()
	@see paOverridePropertyDescription
	*/
	virtual String getPropertyDescription() = 0;

	/**
	This returns a string that describes the property. A host that
	displays a UI should first try and call the property's 
	Property::getName() method. If this returns an empty string,
	then the host should call the property editor's getPropertyName().
	@see Property::getName()
	@see paOverridePropertyName
	*/
	virtual String getPropertyName() = 0;

	/*
	Useful shortcut methods for determining which attributes are set
	for a property editor
	*/
	bool hasValues() {
		return (getAttributes() & PropertyEditor::paHasValues) ? true : false;
	}

	bool sortValues() {
		return (getAttributes() & PropertyEditor::paSortValues) ? true : false;
	}

	bool hasSubProperties() {
		return (getAttributes() & PropertyEditor::paHasSubProperties) ? true : false;
	}

	bool allowsMultiSelect() {
		return (getAttributes() & PropertyEditor::paAllowsMultiSelect) ? true : false;
	}	

	bool isReadOnly() {
		return (getAttributes() & PropertyEditor::paReadOnly) ? true : false;
	}
	

	bool needsCustomPaint() {
		return (getAttributes() & PropertyEditor::paNeedsCustomPaint) ? true : false;
	}

	bool usesModalDialogForEditing() {
		return (getAttributes() & PropertyEditor::paUsesModalDialogForEditing) ? true : false;
	}

	bool valueNeedsDuplicating() { 
		return (getAttributes() & PropertyEditor::paValueNeedsDuplicating) ? true : false;		
	}
	
	bool overridesPropertyDescription() { 
		return (getAttributes() & PropertyEditor::paOverridePropertyDescription) ? true : false;		
	}
	
	bool overridesPropertyName() { 
		return (getAttributes() & PropertyEditor::paOverridePropertyName) ? true : false;		
	}

	bool editorRequestsProperty() { 
		return (getAttributes() & PropertyEditor::paEditorRequestsProperty) ? true : false;		
	}

	bool isCompositeValue() { 
		return (getAttributes() & PropertyEditor::paCompositeValue) ? true : false;		
	}

	
};




}; // namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:24  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.4  2006/03/18 22:17:42  ddiego
*removed par tag for doxygen comments as its not needed and
*screws up the doc formatting.
*
*Revision 1.3.2.3  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.3.2.2  2005/09/12 03:47:04  ddiego
*more prop editor updates.
*
*Revision 1.3.2.1  2005/09/01 03:56:57  ddiego
*doc updates and some minor mods to the property editor interface.
*
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.5  2005/03/11 04:28:21  ddiego
*added some minor modifications to the PropertyEditor interface.
*
*Revision 1.2.4.4  2005/03/09 23:16:17  marcelloptr
*more comments
*
*Revision 1.2.4.3  2005/03/09 05:11:19  ddiego
*fixed property editor class.
*
*Revision 1.2.4.2  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2.4.1  2005/01/24 18:09:18  marcelloptr
*documentation
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.9.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.14.1  2002/12/25 22:06:20  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.7  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/04/27 15:42:51  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PROPERTYEDITOR_H__


