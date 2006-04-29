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
/**
\class Waitable Waitable.h "vcf/FoundationKit/Waitable.h"
*/
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


#endif // _VCF_WAITABLE_H__

/**
$Id$
*/
