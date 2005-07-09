//Win32SemaphorePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


// Win32SemaphorePeer.cpp: implementation of the Win32SemaphorePeer class.
// Win32SemaphorePeer.h: interface for the Win32SemaphorePeer class.


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Win32SemaphorePeer::Win32SemaphorePeer(long initialCount/* = 1*/, long maxCount /*= 1*/)
{
	hObject_ = ::CreateSemaphore(NULL, initialCount, maxCount,NULL);
	if (hObject_ == NULL)
	{
		// here we should throw something!
	}
}

Win32SemaphorePeer::~Win32SemaphorePeer()
{
	if(hObject_ != NULL)
	{
		::CloseHandle(hObject_);
		hObject_ = NULL;
	}
}

bool Win32SemaphorePeer::unlock()
{
	BOOL flag = ::ReleaseSemaphore(hObject_, 1, NULL);

	return flag == FALSE? false:true;
}

bool Win32SemaphorePeer::lock()
{
	if (::WaitForSingleObject(hObject_, INFINITE) == WAIT_OBJECT_0)
		return true;
	else
		return false;
}

bool Win32SemaphorePeer::lock( uint32 timeoutInMilliseconds )
{
	if (::WaitForSingleObject(hObject_, timeoutInMilliseconds) == WAIT_OBJECT_0)
		return true;
	else
		return false;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:07  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/05/05 12:42:27  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.5  2003/05/17 20:37:39  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.16.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.4.16.1  2003/03/12 03:12:42  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.3  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


