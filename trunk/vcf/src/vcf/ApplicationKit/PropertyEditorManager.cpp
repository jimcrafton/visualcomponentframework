//PropertyEditorManager.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/PropertyEditor.h"
#include "vcf/ApplicationKit/PropertyEditorManager.h"

using namespace VCF;


PropertyEditorManager::PropertyEditorManager()
{

}

PropertyEditorManager::~PropertyEditorManager()
{
	propertEditorMap_.clear();
}

PropertyEditor* PropertyEditorManager::createEditor( const String& className )
{
	PropertyEditor* result = NULL;

	std::map<String,Class*>::iterator found =
		PropertyEditorManager::propertyEditorMgr->propertEditorMap_.find( className );
	
	if ( found != PropertyEditorManager::propertyEditorMgr->propertEditorMap_.end() ){
		Class* editorClass = found->second;

		Object* instance = editorClass->createInstance();
		if ( NULL != instance ) {
			result = dynamic_cast<PropertyEditor*>(instance);
			if ( NULL != result ) {
				result->internal_setPropertyType( className );
			}
			else {
				instance->free();
			}
		}
	}
	return result;
}

bool PropertyEditorManager::registerPropertyEditor( Class* editorClass, const String& className )
{
	bool result = true;
	if ( PropertyEditorManager::propertyEditorMgr->propertEditorMap_.find(className) !=
			PropertyEditorManager::propertyEditorMgr->propertEditorMap_.end() ) {
		result = false;
	}
	else {
		PropertyEditorManager::propertyEditorMgr->propertEditorMap_[className] = editorClass;
	}
	
	return result;
}

bool PropertyEditorManager::registerPropertyEditor( const String& editorClassName, const String& className )
{
	Class* editorClass = ClassRegistry::getClass( editorClassName );
	if ( NULL != editorClass ) {
		return PropertyEditorManager::registerPropertyEditor( editorClass, className );
	}

	return false;
}

void PropertyEditorManager::removePropertyEditor( const String& editorClassName, const String& className )
{
	Class* editorClass = NULL;

	std::map<String,Class*>::iterator found =
		PropertyEditorManager::propertyEditorMgr->propertEditorMap_.find( className );
	PropertyEditor* result = NULL;
	if ( found != PropertyEditorManager::propertyEditorMgr->propertEditorMap_.end() ){
		editorClass = found->second;
	}
	else {
		return; //nothing to do
	}

	if ( (editorClass->getClassName() == editorClassName) || (editorClass->getID() == editorClassName) ) {
		//prep to remove dupes if neccessary
		std::map<String,Class*>::iterator it =
			PropertyEditorManager::propertyEditorMgr->propertEditorMap_.begin();
		
		std::vector<std::map<String,Class*>::iterator> removeList;
		while ( it != PropertyEditorManager::propertyEditorMgr->propertEditorMap_.end() ) {
			if ( it->second == editorClass ) {
				removeList.push_back( it );			
			}
			it ++;
		}
		
		std::vector<std::map<String,Class*>::iterator>::iterator it2 = 
			removeList.begin();
		while ( it2 != removeList.end() ) {
			PropertyEditorManager::propertyEditorMgr->propertEditorMap_.erase( *it2 );
			it2 ++;
		}
	}
}

void PropertyEditorManager::initPropertyEditorManager()
{
	PropertyEditorManager::propertyEditorMgr = new PropertyEditorManager();
	PropertyEditorManager::propertyEditorMgr->init();
}

void PropertyEditorManager::closePropertyEditorManager()
{

	try{
		if ( NULL != PropertyEditorManager::propertyEditorMgr ){
			delete PropertyEditorManager::propertyEditorMgr;
		}
		PropertyEditorManager::propertyEditorMgr = NULL;
	}
	catch(...) {

	}

}


/**
$Id$
*/
