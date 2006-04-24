
#ifndef _VCF_THREADMANAGERPEER_H__
#define _VCF_THREADMANAGERPEER_H__

#if _MSC_VER > 1000
#   pragma once
#endif


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {
	/**
	\class ThreadManagerPeer ThreadManagerPeer.h "vcf/FoundationKit/ThreadManagerPeer.h"
	*/
	class FOUNDATIONKIT_API ThreadManagerPeer {
	public:
		virtual ~ThreadManagerPeer(){}

		virtual Waitable::WaitResult wait( std::vector<Waitable*>& waitObjects, std::vector<Waitable*>& signaledObjects ) = 0;

		virtual Waitable::WaitResult wait( std::vector<Waitable*>& waitObjects, std::vector<Waitable*>& signaledObjects, uint32 timeoutInMilliseconds ) = 0;

		virtual uint32 getCurrentThreadID() = 0;
	};



};


#endif //_VCF_THREADMANAGERPEER_H__

