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

/**
*PropertyEditor
*/
class APPLICATIONKIT_API PropertyEditor{
public:
	virtual ~PropertyEditor(){};

	/**
	*returns a new instance of the custom editor. The caller
	*is resposible for deleting the editor when it is finished
	*with it.
	*Implementer of this interface should always make a new instance
	*each time this is called.
	*/
	virtual Control* getCustomEditor() = 0;

	virtual void paintValue( GraphicsContext* context, const Rect& bounds ) = 0;

	/**
	*Sets the source for the Property editor
	*/
	virtual void setSource( Object* source ) = 0;

	/**
	*Sets the property of the Property editor
	*/
	virtual void setProperty( Property* property ) = 0;

	virtual VariantData* getValue() = 0;

	virtual void setValue( VariantData* value ) = 0;

	/**
	*is it OK to call getCustomEditor ?
	*/
	virtual bool hasCustomEditor() = 0;

	/**
	*is OK to call paintValue ?
	*/
	virtual bool canPaintValue() = 0;

	virtual String getValueAsText() = 0;

	virtual void setValueAsText( const String& textValue ) = 0;

	/**
	*called by an IDE to get the C++ string representation of
	the property to insert into C++ code.
	*/
	virtual String getCodeString() = 0;

};




};


/**
*CVS Log info
*$Log$
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


