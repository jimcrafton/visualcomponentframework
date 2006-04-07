/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadManager.h"
#include "vcf/FoundationKit/ThreadManagerPeer.h"
#include "vcf/FoundationKit/Lock.h"

//ThreadManager.cpp


using namespace VCF;


ThreadManager* ThreadManager::threadManagerInstance = NULL;

ThreadManager::ThreadManager():
	peer_(NULL)
{
	peer_ = SystemToolkit::createThreadManagerPeer();
	if ( NULL == peer_ ) {
		throw NoPeerFoundException();
	}
}

ThreadManager::~ThreadManager()
{
	delete peer_;
	peer_ = NULL;
}

void ThreadManager::create()
{
	ThreadManager::threadManagerInstance = new ThreadManager();

	//create and add the "main" thread wrapper that wraps the
	//main executable thread.

	Thread* mainThread = Thread::getMainThread();

	ThreadManager::addThread( mainThread );
}

void ThreadManager::terminate()
{
	Thread* mainThread = Thread::getMainThread();
	delete mainThread;

	delete ThreadManager::threadManagerInstance;
}

Thread* ThreadManager::getCurrentThread()
{
	Thread* result = NULL;

	Lock l( ThreadManager::threadManagerInstance->mtx_ );

	uint32 id = ThreadManager::threadManagerInstance->peer_->getCurrentThreadID();

	std::map<uint32, Thread*>::iterator found =
		ThreadManager::threadManagerInstance->threads_.find( id );

	if ( found != ThreadManager::threadManagerInstance->threads_.end() ) {
		result = found->second;
	}

	return result;

}

RunLoop* ThreadManager::getCurrentRunLoop()
{
	return ThreadManager::getCurrentThread()->getRunLoop();
}

Waitable::WaitResult ThreadManager::wait( std::vector<Waitable*>& waitObjects, std::vector<Waitable*>& signaledObjects )
{
	return ThreadManager::threadManagerInstance->peer_->wait( waitObjects, signaledObjects );
}

Waitable::WaitResult ThreadManager::wait( std::vector<Waitable*>& waitObjects, std::vector<Waitable*>& signaledObjects, uint32 timeoutInMilliseconds )
{
	return ThreadManager::threadManagerInstance->peer_->wait( waitObjects, signaledObjects, timeoutInMilliseconds );
}

void ThreadManager::addThread( Thread* thread )
{
	ThreadManager::threadManagerInstance->internal_addThread( thread );
}

void ThreadManager::removeThread( Thread* thread )
{
	ThreadManager::threadManagerInstance->internal_removeThread( thread );
}

void ThreadManager::internal_addThread( Thread* thread )
{
	Lock l(mtx_);

	threads_[thread->getThreadID()] = thread;
}

void ThreadManager::internal_removeThread( Thread* thread )
{
	Lock l(mtx_);

	std::map<uint32, Thread*>::iterator found = threads_.find( thread->getThreadID() );
	if ( found != threads_.end() ) {
		threads_.erase( found );
	}
}
