#ifndef _VCF_CURSORMANAGER_H__
#define _VCF_CURSORMANAGER_H__
//CursorManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

/**
\class CursorManager CursorManager.h "vcf/ApplicationKit/CursorManager.h"
*Class CursorManager documentation
*/
class APPLICATIONKIT_API CursorManager : public Object {
public:
	static CursorManager* create();

	enum {
		UNREGISTERED_ID=-1
	};

	CursorManager();

	virtual ~CursorManager();

	Cursor* getCursor( const long& cursorID );

	void registerCursor( Cursor* cursor );

	static CursorManager* getCursorManager();
protected:
	static CursorManager* cursorMgrInstance;
	std::map<long,Cursor*> cursorMap_;
	long cursorIDCount_;

};


}; //end of namespace VCF


#endif // _VCF_CURSORMANAGER_H__

/**
$Id$
*/
