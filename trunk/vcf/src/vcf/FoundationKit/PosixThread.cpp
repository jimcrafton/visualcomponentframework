//PosixThread.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"
#include <sys/types.h>
#include <unistd.h>

using namespace VCF;

void* threadProc( void* arg )
{
    Thread* threadPtr = (Thread*)arg;
 	threadPtr->run();
    return NULL;
}

PosixThread::PosixThread( Thread* thread ) :
	threadID_(0),
    processID_(getpid()),
	thread_(thread),
    isActive_(false),
    isDetached_(false)
{
}

PosixThread::~PosixThread()
{
    stop();
}

bool PosixThread::start()
{
    if ( isActive_ ) return true;
    if ( pthread_create(&threadID_, NULL, threadProc, this) != 0 )
    {
        isActive_ = true;
        return true;
    }
    else return false;
}

void PosixThread::stop()
{
    if ( isActive_ )
    {
        pthread_cancel(threadID_);
        //detach(); JC - commented this out to compile on linux
        isActive_ = false;
    }
}

void PosixThread::sleep( uint32 milliseconds )
{
    if ( !isActive_ ) return;
}

/*
void PosixThread::detach()
{
    if ( !isDetached_ )
    {
        pthread_detach(threadID_);
        isDetached_ = true;
    }
}

void PosixThread::join()
{
    if ( isActive_ && !isDetached_ && !inThreadProc() )
    {
        pthread_join(threadID_, NULL);
        isActive_ = false;
    }
}

void PosixThread::yield()
{
    if ( isActive_ && inThreadProc() ) sched_yield();
}


void PosixThread::exit()
{
    if ( isActive_ && inThreadProc() ) pthread_exit(NULL);
}
*/


int PosixThread::wait()
{
	return -1;
}

int PosixThread::wait( uint32 milliseconds )
{
	return -1;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.4  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.6.1  2004/03/30 01:48:26  ddiego
*updated linux code
*
*Revision 1.3  2003/05/17 20:37:34  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.2  2003/02/06 00:22:04  catwallader
*Added thread methods: isActive(), isDetached(), join(), exit(), yield() and detach().  Fleshed out PosixThread::stop().
*
*Revision 1.1.2.1  2003/01/30 22:32:22  catwallader
*Added the PosixThread class.  Modified Makefiles and toolkit files to accomodate it.
*
*/


