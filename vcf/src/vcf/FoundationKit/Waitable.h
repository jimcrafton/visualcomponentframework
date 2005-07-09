#ifndef _VCF_WAITABLE_H__
#define _VCF_WAITABLE_H__
//Waitable.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Waitable {
public:
	virtual ~Waitable(){}


	enum WaitResult{
		wrTimedOut,
		wrWaitFinished,
		wrWaitFailed
	};

	virtual WaitResult wait() = 0;

	virtual WaitResult wait( uint32 milliseconds ) = 0;

	virtual OSHandleID getPeerHandleID() = 0; 
};


};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:06  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/05/05 12:42:27  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.2.2.1  2004/04/26 21:58:49  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.2  2004/03/29 14:52:39  ddiego
*added newlines to end of file
*
*Revision 1.1.2.1  2004/03/11 22:20:00  ddiego
*added condition implementation to FoundationKit.
*added a Conditions example to the examples directory.
*
*/


#endif // _VCF_WAITABLE_H__


