#ifndef _VCF_WIN32SEMAPHOREPEER_H__
#define _VCF_WIN32SEMAPHOREPEER_H__
//Win32SemaphorePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Win32SemaphorePeer.h: interface for the Win32SemaphorePeer class.


namespace VCF
{

/**
*Class Win32SemaphorePeer documentation
Implements the base SemaphorePeer class
used for synchronizing access to threaded
resources
*/
/**
*Class Win32SemaphorePeer
*@author Tiziano Franzoi, Nov 15, 2001
*/
class Win32SemaphorePeer : public VCF::SemaphorePeer
{
public:
	Win32SemaphorePeer(int32 initialCount , int32 maxCount);
	virtual ~Win32SemaphorePeer();

	virtual bool lock();

	virtual bool lock( uint32 timeoutInMilliseconds );

	virtual bool unlock();

	virtual OSHandleID getHandleID() {
		return (OSHandleID)hObject_;
	}
protected:
	HANDLE  hObject_;
};
} // end of namespace VCF


#endif // _VCF_WIN32SEMAPHOREPEER_H__

/**
$Id$
*/
