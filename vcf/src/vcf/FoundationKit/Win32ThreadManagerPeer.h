
#ifndef _VCF_WIN32THREADMANAGERPEER_H__
#define _VCF_WIN32THREADMANAGERPEER_H__

//Win32ThreadManagerPeer.h



#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/ThreadManagerPeer.h"
/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

	class Win32ThreadManagerPeer : public ThreadManagerPeer {
	public:
		Win32ThreadManagerPeer();
		virtual ~Win32ThreadManagerPeer();

		virtual Waitable::WaitResult wait( std::vector<Waitable*>& waitObjects, std::vector<Waitable*>& signaledObjects );

		virtual Waitable::WaitResult wait( std::vector<Waitable*>& waitObjects, std::vector<Waitable*>& signaledObjects, uint32 timeoutInMilliseconds );

		virtual uint32 getCurrentThreadID();
	};

};

#endif //_VCF_WIN32THREADMANAGERPEER_H__