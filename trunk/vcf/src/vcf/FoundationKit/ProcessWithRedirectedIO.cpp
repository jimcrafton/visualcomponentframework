//ProcessWithRedirectedIO.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ProcessWithRedirectedIO.h"


using namespace VCF;


ProcessWithRedirectedIO::ProcessWithRedirectedIO():
	processPeer_(NULL)
{
	processPeer_ = SystemToolkit::createProcessIORedirectionPeer( this );
	if ( NULL == processPeer_ ) {
		throw NoPeerFoundException(MAKE_ERROR_MSG_2(NO_PEER));
	}
}

ProcessWithRedirectedIO::ProcessWithRedirectedIO( const String& processName, const String& arguments ):
	processPeer_(NULL)
{
	processPeer_ = SystemToolkit::createProcessIORedirectionPeer( this );
	if ( NULL == processPeer_ ) {
		throw NoPeerFoundException(MAKE_ERROR_MSG_2(NO_PEER));
	}

	if ( !createProcess( processName, arguments ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "" ) );
	}
}

ProcessWithRedirectedIO::~ProcessWithRedirectedIO()
{
	delete processPeer_;
}

int ProcessWithRedirectedIO::getID()
{
	return processPeer_->getProcessID();
}

int ProcessWithRedirectedIO::getThreadID()
{
	return processPeer_->getProcessThreadID();
}

bool ProcessWithRedirectedIO::createProcess( const String& processName, const String& arguments )
{
	return processPeer_->createProcess( processName, arguments );
}

String ProcessWithRedirectedIO::getName()
{
	return processPeer_->getProcessFileName();
}

ulong32 ProcessWithRedirectedIO::terminate()
{
	return processPeer_->terminate();
}


/**
$Id$
*/
