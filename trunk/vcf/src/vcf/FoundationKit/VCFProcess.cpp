//VCFProcess.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

Process::Process():
	processPeer_(NULL)
{
	processPeer_ = SystemToolkit::createProcessPeer( this );
	if ( NULL == processPeer_ ) {		
		throw NoPeerFoundException( MAKE_ERROR_MSG_2("The SystemToolkit was unable to create a process peer!") );	
	}
}

Process::~Process()
{
	delete processPeer_;
}

int Process::getID()
{
	return processPeer_->getProcessID();
}

int Process::getThreadID()
{
	return processPeer_->getProcessThreadID();
}

bool Process::createProcess( const String& processName, const String& arguments )
{
	String fullProcessName = processName;

	

	{
		File processFile(processName);
		//JC
		//maybe we should attempt to expand out the file name here?
		//if so we would get the PATH env var, and loop through all the
		//dir names, try each one until we get a hit, or they all fail
		//is this too expensive??
		try {
			if ( processFile.isDirectory() ) {
				fullProcessName = System::getExecutableNameFromBundlePath( processName );				
			}
		}
		catch ( BasicException& ) {
			//definitely NOT a dir, or if it is, we can't find it
			//so replace the name back to the original one passed in
			fullProcessName = processName;
		}

		//if it's empty, then throw an exception!
		if ( fullProcessName.empty() ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("Invalid file name. Points to a directory with no program information available.") );
		}
	}
	

	bool result = false;

	if ( !fullProcessName.empty() ) {
		result = processPeer_->createProcess( fullProcessName, arguments );
	}

	return result;
}

String Process::getName()
{
	
	return processPeer_->getProcessFileName();
}

ulong32 Process::terminate()
{
	return processPeer_->terminate();
}

Waitable::WaitResult Process::wait()
{
	return processPeer_->wait();
}

Waitable::WaitResult Process::wait( uint32 milliseconds )
{
	return processPeer_->wait(milliseconds);
}

OSHandleID Process::getPeerHandleID()
{
	return processPeer_->getHandleID();
}


/**
$Id$
*/
