
#ifndef _VCF_OSXTHREADMANAGERPEER_H__
#define _VCF_OSXTHREADMANAGERPEER_H__

//OSXThreadManagerPeer.h


#include "vcf/FoundationKit/ThreadManagerPeer.h"
/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

	class OSXThreadManagerPeer : public ThreadManagerPeer {
	public:
		OSXThreadManagerPeer();
		virtual ~OSXThreadManagerPeer();

		virtual Waitable::WaitResult wait( std::vector<Waitable*>& waitObjects, std::vector<Waitable*>& signaledObjects );

		virtual Waitable::WaitResult wait( std::vector<Waitable*>& waitObjects, std::vector<Waitable*>& signaledObjects, uint32 timeoutInMilliseconds );

		virtual uint32 getCurrentThreadID();
	};

};

#endif //_VCF_OSXTHREADMANAGERPEER_H__