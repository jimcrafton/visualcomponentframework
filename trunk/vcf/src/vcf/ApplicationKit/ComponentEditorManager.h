#ifndef _VCF_COMPONENTEDITORMANAGER_H__
#define _VCF_COMPONENTEDITORMANAGER_H__
//ComponentEditorManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class ComponentEditor;


#define REGISTER_FOR_ALL_COMPONENTS		"*"

/**
\class ComponentEditorManager ComponentEditorManager.h "vcf/ApplicationKit/ComponentEditorManager.h"
*The ComponentEditorManager is used
*to regulate the different component editors that are available
*/
class APPLICATIONKIT_API ComponentEditorManager : public VCF::Object {
public:
	ComponentEditorManager();

	virtual ~ComponentEditorManager();

	/**
	*find a suitable Component editor for a given
	*classname.
	*/
	static ComponentEditor* findComponentEditor( const String& className );

	static void registerComponentEditor( ComponentEditor* componentEditor, const String& className );

	/**
	Removes a ComponentEditor with a given class/type name from the
	list of registered component editors.
	*/
	static void removeComponentEditor( const String& className );

	/**
	*initializes the Component editor manager for use - must be called at start up
	*/
	static void initComponentEditorManager();

	/**
	*frees any memory used by initComponentEditorManager(). Must be called before the
	*runtime shuts down
	*/
	static void closeComponentEditorManager();
protected:
	static ComponentEditorManager* componentEditorMgr;

	std::map<String,ComponentEditor*> componentEditorMap_;
};


}; //end of namespace VCF


#endif // _VCF_COMPONENTEDITORMANAGER_H__

/**
$Id$
*/
