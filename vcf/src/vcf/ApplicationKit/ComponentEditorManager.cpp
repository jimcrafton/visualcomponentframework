//ComponentEditorManager.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ComponentEditorManager.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ComponentEditor.h"
#include "vcf/ApplicationKit/ComponentEditorManager.h"

using namespace VCF;

ComponentEditorManager* ComponentEditorManager::componentEditorMgr = NULL;


ComponentEditorManager::ComponentEditorManager()
{

}

ComponentEditorManager::~ComponentEditorManager()
{
	std::map<String,ComponentEditor*>::iterator it = componentEditorMap_.begin();
	while ( it != componentEditorMap_.end() ) {
		delete it->second;
		it->second = NULL;
		it ++;
	}

	componentEditorMap_.clear();
}

ComponentEditor* ComponentEditorManager::findComponentEditor( const String& className )
{
	ComponentEditor* result = NULL;
	std::map<String,ComponentEditor*>::iterator found =
		ComponentEditorManager::componentEditorMgr->componentEditorMap_.find( className );
	if ( found != ComponentEditorManager::componentEditorMgr->componentEditorMap_.end() ) {
		result = found->second;
	}

	return result;
}

void ComponentEditorManager::registerComponentEditor( ComponentEditor* componentEditor, const String& className )
{
	ComponentEditorManager::componentEditorMgr->componentEditorMap_[className] = componentEditor;
}

void ComponentEditorManager::removeComponentEditor( const String& className )
{
	ComponentEditor* result = NULL;
	std::map<String,ComponentEditor*>::iterator found =
		ComponentEditorManager::componentEditorMgr->componentEditorMap_.find( className );
	if ( found != ComponentEditorManager::componentEditorMgr->componentEditorMap_.end() ) {
		delete found->second;
		ComponentEditorManager::componentEditorMgr->componentEditorMap_.erase( found );
	}
}

void ComponentEditorManager::initComponentEditorManager()
{
	ComponentEditorManager::componentEditorMgr = new ComponentEditorManager();
	ComponentEditorManager::componentEditorMgr->init();
}

void ComponentEditorManager::closeComponentEditorManager()
{

	if ( NULL != ComponentEditorManager::componentEditorMgr ) {
		delete ComponentEditorManager::componentEditorMgr;
	}
	ComponentEditorManager::componentEditorMgr = NULL;

}


/**
$Id$
*/
