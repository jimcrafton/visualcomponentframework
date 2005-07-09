#ifndef _VCF_DEFAULTPROPERTYEDITORS_H__
#define _VCF_DEFAULTPROPERTYEDITORS_H__
//DefaultPropertyEditors.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

namespace VCF {



class APPLICATIONKIT_API IntegerPropertyEditor : public AbstractPropertyEditor {
public:
	IntegerPropertyEditor(){};

	virtual ~IntegerPropertyEditor(){};

private:

};


class APPLICATIONKIT_API DoublePropertyEditor : public AbstractPropertyEditor {
public:
	DoublePropertyEditor(){};

	virtual ~DoublePropertyEditor(){};

private:

};

class APPLICATIONKIT_API StringPropertyEditor : public AbstractPropertyEditor {
public:
	StringPropertyEditor(){};

	virtual ~StringPropertyEditor(){};

private:

};


class APPLICATIONKIT_API BoolPropertyEditor : public AbstractPropertyEditor {
public:
	BoolPropertyEditor();

	virtual ~BoolPropertyEditor();

	virtual std::vector<String> getStringValues();
};

class APPLICATIONKIT_API EnumPropertyEditor : public AbstractPropertyEditor{
public:
	EnumPropertyEditor();

	virtual ~EnumPropertyEditor();	

	virtual std::vector<String> getStringValues();
};



class APPLICATIONKIT_API ColorPropertyEditor : public AbstractPropertyEditor {
public:
	ColorPropertyEditor();

	virtual ~ColorPropertyEditor();

	virtual void paintValue( VariantData* value, GraphicsContext* context, const Rect& bounds, const DrawUIState& state );

	virtual std::vector<String> getStringValues();

	virtual void edit();

	virtual bool sort( const String& strVal1, const String& strVal2 );

	//takes a value as text - try and look up the text color value
	//in our color list
	virtual void setValueAsText( const String& textValue );	
};

class APPLICATIONKIT_API FontPropertyEditor : public AbstractPropertyEditor {
public:
	FontPropertyEditor();

	virtual ~FontPropertyEditor();

	virtual void paintValue( VariantData* value, GraphicsContext* context, const Rect& bounds, const DrawUIState& state );

	virtual void edit();

	virtual std::vector<PropertyEditor*> getSubProperties();

};


class APPLICATIONKIT_API DefaultMenuItemPropertyEditor : public AbstractPropertyEditor {
public:
	DefaultMenuItemPropertyEditor();

	virtual ~DefaultMenuItemPropertyEditor();

};

class APPLICATIONKIT_API DefaultListModelPropertyEditor : public AbstractPropertyEditor {
public:
	DefaultListModelPropertyEditor();

	virtual ~DefaultListModelPropertyEditor();
};








};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/03/09 05:11:19  ddiego
*fixed property editor class.
*
*Revision 1.2.4.2  2005/02/21 16:20:01  ddiego
*minor changes to various things, property editors, and tree list control.
*
*Revision 1.2.4.1  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.17.4.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.17  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.16.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.16.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.16  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.15.2.1  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.15  2003/05/17 20:37:02  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.14.2.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.14.2.1  2003/03/12 03:09:31  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.14  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.13.14.2  2002/12/25 22:37:59  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.13.14.1  2002/12/25 22:06:19  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.13  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.2  2002/04/27 15:42:07  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.12.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.12  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTPROPERTYEDITORS_H__


