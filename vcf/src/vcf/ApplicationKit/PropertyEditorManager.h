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
\class PropertyEditorManager PropertyEditorManager.h "vcf/ApplicationKit/PropertyEditorManager.h"
This is the class for managing the current list of
property editors available for use in editing a property.
Some of the default editors are provided by the framework
itself, while other will be added by 3rd parties.

This is a singleton class, and it's lifetime is managed by
the UIToolkit, not by any other direct means or by developers
using the framework. 

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
	static void removePropertyEditor( const String& editorClassName, const String& className );	

private:
	PropertyEditorManager();
	virtual ~PropertyEditorManager();

	PropertyEditorManager( const PropertyEditorManager& ); //no copy
	PropertyEditorManager& operator=( const PropertyEditorManager& ); //no assignment


	static PropertyEditorManager* propertyEditorMgr;
	std::map<String,Class*> propertEditorMap_;

};


};


#endif // _VCF_PROPERTYEDITORMANAGER_H__

/**
$Id$
*/
