//LinuxProcessPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

#include <sys/wait.h>

using namespace VCF;

LinuxProcessPeer::LinuxProcessPeer()
		: processHandle_( -1 )
		, processFileName_()
{}

LinuxProcessPeer::~LinuxProcessPeer()
{}

int LinuxProcessPeer::getProcessID()
{
	return getpid();
}

int LinuxProcessPeer::getProcessThreadID()
{
	return pthread_self();
}

bool LinuxProcessPeer::createProcess( const String& processName, const String& arguments )
{
	bool result = false;
    processFileName_ = "";
    if( (processHandle_ = vfork()) == 0)
    {
        // child
        char* pn  = strdup(processName.ansi_c_str());
        CommandLine cmdLine;
        cmdLine.splitLine(arguments);
        const std::vector<String>& args = cmdLine.getOriginalCommandLine();
        char **argv = new char*[args.size()+2];
        argv[0] = strdup(pn);
        for(size_t i=0; i<args.size(); ++i)
        {
            argv[i+1] = strdup(args[i].ansi_c_str());
        }
        argv[args.size()+1] = NULL;

        if(execvp(pn, argv) == -1)
        {
            for(size_t i=0; i<args.size()+2; ++i)
            {
                free(argv[i]);
            }
            delete argv;
            free(pn);
            exit(-1);
        }
    }
    else if(processHandle_ == -1)
    {
        // parent failed
        result = false;
    }
    else
    {
        processFileName_ = processName;
        // parent success
        result = true;
    }

	return result;
}

String LinuxProcessPeer::getProcessFileName()
{
	return processFileName_;
}

OSHandleID LinuxProcessPeer::getHandleID()
{
	return reinterpret_cast<OSHandleID>( processHandle_ );
}

ulong32 LinuxProcessPeer::terminate()
{
	return kill(processHandle_, SIGKILL);
}

Waitable::WaitResult LinuxProcessPeer::wait( uint32 milliseconds )
{
	return wait();
}

Waitable::WaitResult LinuxProcessPeer::wait()
{
	Waitable::WaitResult result;
    int stat_loc = 0;
    if(waitpid(processHandle_, &stat_loc, 0) == -1)
    {
        result = Waitable::wrWaitFailed;
    }
    else
    {
        result = Waitable::wrWaitFinished;
    }
	return result;
}


/**
$Id$
*/
