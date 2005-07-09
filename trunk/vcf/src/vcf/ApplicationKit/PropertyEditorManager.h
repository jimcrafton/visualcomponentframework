#ifndef _VCF_PROPERTYEDITORMANAGER_H__
#define _VCF_PROPERTYEDITORMANAGER_H__
//PropertyEditorManager.h

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

class PropertyEditor;

/**
\par
This is the class for managing the current list of
property editors available for use in editing a property.
Some of the default editors are provided by the framework
itself, while other will be added by 3rd parties.
\par
This is a singleton class, and it's lifetime is managed by
the UIToolkit, not by any other direct means or by developers
using the framework. 
\par
The class allows the registration of property editor's at 
run time. The usage is something like this:
\code
//define you cool PropertyEditor derived class
class MyCoolEditor : public PropertyEditor {
//rest of code ommitted
};

//in some initialization function:
PropertyEditorManager::registerPropertyEditor( new MyCoolEditor(), "Foo" );
\endcode
This will register an instance of the MyCoolEditor class with any object
that is of type "Foo". Type names for a given property are usually retrieved
by calling the property's getTypeClassName() method.
@see UIToolkit::init()
@see PropertyEditor
@see Property::getTypeClassName
*/
class APPLICATIONKIT_API PropertyEditorManager : public Object
{
public:
	/**
	Called by the UIToolkit to create the singleton instance
	for the framework.
	*/
	static PropertyEditorManager* create();

	/**
	initializes the Property editor for use - must be called at start up
	*/
	static void initPropertyEditorManager();
	
	/**
	Frees any memory used by initPropertyEditorManager(). Must be called before the
	runtime shuts down.
	*/
	static void closePropertyEditorManager();

	/**
	create a suitable property editor for a given classname.
	@param String the class name of the property type - this is the same
	name that should have been used in the call to registerPropertyEditor()
	to register the property editor Class with the PropertyEditorManager.
	@return PropertyEditor returns a new intance of a property editor. If 
	no match is found with the className parameter, then the return value is NULL.
	*/
	static PropertyEditor* createEditor( const String& className );

	/**
	Registers a property editor for a given class name. If an existing property
	editor already exists with the same name type name, then the function returns
	false.
	@param Class the class instance that represents the property editor
	@param String the name of the type associated with this property editor
	@return bool 
	*/
	static bool registerPropertyEditor( Class* editorClass, const String& className );	

	/**
	Registers a property editor for a given class/type name. If an existing property
	editor already exists with the same name type name, then the function returns
	false.
	@param String the class name that represents the property editor
	@param String the name of the type associated with this property editor
	@return bool 
	*/
	static bool registerPropertyEditor( const String& editorClassName, const String& className );	

	/**
	Removes a PropertyEditor with a given class/type name from the
	list of registered propertyEditors.
	*/
	static void removePropertyEditor( const String& className );	

private:
	PropertyEditorManager();
	virtual ~PropertyEditorManager();

	PropertyEditorManager( const PropertyEditorManager& ); //no copy
	PropertyEditorManager& operator=( const PropertyEditorManager& ); //no assignment


	static PropertyEditorManager* propertyEditorMgr;
	std::map<String,Class*> propertEditorMap_;

};


};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.6  2005/03/10 03:19:54  marcelloptr
*more comments
*
*Revision 1.2.4.3  2005/03/09 05:11:19  ddiego
*fixed property editor class.
*
*Revision 1.2.4.2  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2.4.1  2005/01/24 18:11:59  marcelloptr
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
*Revision 1.9.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.8.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.8  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.22.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.22.1  2003/03/12 03:09:42  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PROPERTYEDITORMANAGER_H__


