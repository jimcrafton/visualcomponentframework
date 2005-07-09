//OSXThreadManagerPeer.cpp


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/OSXThreadManagerPeer.h"

using namespace VCF;


OSXThreadManagerPeer::OSXThreadManagerPeer()
{

}

OSXThreadManagerPeer::~OSXThreadManagerPeer()
{

}

Waitable::WaitResult OSXThreadManagerPeer::wait( std::vector<Waitable*>& waitObjects, 
													std::vector<Waitable*>& signaledObjects )
{
	Waitable::WaitResult result = Waitable::wrWaitFailed;

	VCF_ASSERT( !waitObjects.empty() );
	
	signaledObjects.clear();

	return result;
}

Waitable::WaitResult OSXThreadManagerPeer::wait( std::vector<Waitable*>& waitObjects, 
												  std::vector<Waitable*>& signaledObjects, 
												  uint32 timeoutInMilliseconds )
{
	Waitable::WaitResult result = Waitable::wrWaitFailed;

	VCF_ASSERT( !waitObjects.empty() );
	
	signaledObjects.clear();

	return result;
}


uint32 OSXThreadManagerPeer::getCurrentThreadID()
{
	return (uint32) MPCurrentTaskID();
}