//PosixThreadManagerPeer.cpp


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include "vcf/FoundationKit/PosixThreadManagerPeer.h"

using namespace VCF;


PosixThreadManagerPeer::PosixThreadManagerPeer()
{

}

PosixThreadManagerPeer::~PosixThreadManagerPeer()
{

}

Waitable::WaitResult PosixThreadManagerPeer::wait( std::vector<Waitable*>& waitObjects,
                                                    std::vector<Waitable*>& signaledObjects )
{
    Waitable::WaitResult result = Waitable::wrWaitFailed;
    return result;
}

Waitable::WaitResult PosixThreadManagerPeer::wait( std::vector<Waitable*>& waitObjects,
                                                  std::vector<Waitable*>& signaledObjects, 
                                                  uint32 timeoutInMilliseconds )
{
    Waitable::WaitResult result = Waitable::wrWaitFailed;
    return result;
}

uint32 PosixThreadManagerPeer::getCurrentThreadID()
{
    return pthread_self();
}
