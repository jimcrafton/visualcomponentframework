//LinuxProcessIORedirector.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ProcessWithRedirectedIO.h"
#include "vcf/FoundationKit/LinuxProcessIORedirector.h"

using namespace VCF;

LinuxProcessIORedirector::LinuxProcessIORedirector()
{}

LinuxProcessIORedirector::~LinuxProcessIORedirector()
{}

bool LinuxProcessIORedirector::createProcess( const String& processName,
                                              const String& arguments )
{
	bool result = false;
	return result;
}

uint32 LinuxProcessIORedirector::terminate()
{
	return 0;
}

Waitable::WaitResult LinuxProcessIORedirector::wait( uint32 milliseconds )
{
	Waitable::WaitResult result = Waitable::wrWaitFailed;
	return result;
}

Waitable::WaitResult LinuxProcessIORedirector::wait()
{
	Waitable::WaitResult result = Waitable::wrWaitFailed;
	return result;
}


/**
$Id$
*/
