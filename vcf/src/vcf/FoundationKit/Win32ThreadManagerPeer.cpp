//Win32ThreadManagerPeer.cpp


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/Win32ThreadManagerPeer.h"

using namespace VCF;


Win32ThreadManagerPeer::Win32ThreadManagerPeer()
{

}

Win32ThreadManagerPeer::~Win32ThreadManagerPeer()
{

}

Waitable::WaitResult Win32ThreadManagerPeer::wait( std::vector<Waitable*>& waitObjects, 
													std::vector<Waitable*>& signaledObjects )
{
	Waitable::WaitResult result = Waitable::wrWaitFailed;

	VCF_ASSERT( !waitObjects.empty() );
	
	signaledObjects.clear();

	HANDLE* handles = new HANDLE[ waitObjects.size() ];
	for ( int i=0;i<waitObjects.size();i++ ) {
		handles[i] = waitObjects[i]->getPeerHandleID();
	}
	
	DWORD res = WaitForMultipleObjects( waitObjects.size(), handles, FALSE, INFINITE );

	switch ( res ) {
		case WAIT_TIMEOUT : {
			result = Waitable::wrTimedOut;
		}
		break;

		case WAIT_FAILED : {
			result = Waitable::wrWaitFailed;
		}
		break;

		default : {
			if ( (res >= WAIT_OBJECT_0) && (res < WAIT_OBJECT_0+waitObjects.size()) ) {
				signaledObjects.push_back( waitObjects[res-WAIT_OBJECT_0] );
			}
		}
		break;
		
	}
	delete [] handles;
	return result;
}

Waitable::WaitResult Win32ThreadManagerPeer::wait( std::vector<Waitable*>& waitObjects, 
												  std::vector<Waitable*>& signaledObjects, 
												  uint32 timeoutInMilliseconds )
{
	Waitable::WaitResult result = Waitable::wrWaitFailed;

	VCF_ASSERT( !waitObjects.empty() );
	
	signaledObjects.clear();

	HANDLE* handles = new HANDLE[ waitObjects.size() ];
	for ( int i=0;i<waitObjects.size();i++ ) {
		handles[i] = waitObjects[i]->getPeerHandleID();
	}
	
	DWORD res = WaitForMultipleObjects( waitObjects.size(), handles, FALSE, timeoutInMilliseconds );

	switch ( res ) {
		case WAIT_TIMEOUT : {
			result = Waitable::wrTimedOut;
		}
		break;

		case WAIT_FAILED : {
			result = Waitable::wrWaitFailed;
		}
		break;

		default : {
			if ( (res >= WAIT_OBJECT_0) && (res < WAIT_OBJECT_0+waitObjects.size()) ) {
				signaledObjects.push_back( waitObjects[res-WAIT_OBJECT_0] );
			}
		}
		break;
		
	}
	delete [] handles;
	return result;
}


uint32 Win32ThreadManagerPeer::getCurrentThreadID()
{
	return GetCurrentThreadId();
}



