//PropertyEditorManager.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
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

void PropertyEditorManager::removePropertyEditor( const String& className )
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
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/03/11 04:28:22  ddiego
*added some minor modifications to the PropertyEditor interface.
*
*Revision 1.2.4.2  2005/03/09 05:11:19  ddiego
*fixed property editor class.
*
*Revision 1.2.4.1  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.11  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.1  2003/03/12 03:13:18  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.14.1  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.8  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


