//CursorManager.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//CursorManager.h

#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;



CursorManager* CursorManager::create()
{
	if ( NULL == CursorManager::cursorMgrInstance ) {
		CursorManager::cursorMgrInstance = new CursorManager();
		CursorManager::cursorMgrInstance->init();
	}

	return CursorManager::cursorMgrInstance;
}


CursorManager* CursorManager::getCursorManager()
{
	return CursorManager::cursorMgrInstance;
}

CursorManager::CursorManager()
{
	cursorIDCount_ = (long)(Cursor::SCT_WAIT) + 1;
}

CursorManager::~CursorManager()
{
	std::map<long,Cursor*>::iterator it = cursorMap_.begin();
	while ( it != cursorMap_.end() ) {
		Cursor* cursor = it->second;
		delete cursor;
		cursor = NULL;
		it ++;
	}
	cursorMap_.clear();
}

Cursor* CursorManager::getCursor( const long& cursorID )
{
	Cursor* result = NULL;
	std::map<long,Cursor*>::iterator found = cursorMap_.find( cursorID );
	if ( found != cursorMap_.end() ) {
		result = found->second;
	}
	else {

		if ( (cursorID >= (long)Cursor::SCT_DEFAULT) && (cursorID <= (long)Cursor::SCT_WAIT) ) {
			result = new Cursor( (Cursor::SystemCursorType)cursorID );
		}
	}

	return result;
}

void CursorManager::registerCursor( Cursor* cursor )
{
	long cursorID = cursor->getCursorID();
	std::map<long,Cursor*>::iterator found = cursorMap_.find( cursorID );
	if ( found == cursorMap_.end() ) {
		//only add the cursor to the map if it isn't already there
		if ( (cursorID == CursorManager::UNREGISTERED_ID) ||
			((cursorID >= Cursor::SCT_DEFAULT) && (cursorID <= Cursor::SCT_WAIT)) ) {
			if ( cursorID == CursorManager::UNREGISTERED_ID ) {
				cursorID = cursorIDCount_;
				cursor->getPeer()->setCursorID( cursorID );
				cursorIDCount_ ++;
			}
			cursorMap_[cursorID] = cursor;
		}
		else {
			//this is bad - somehow the cursor has an ID but is not present in the
			//map - possibly throw an exception ?
		}
	}
}


/**
$Id$
*/
