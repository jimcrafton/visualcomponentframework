#ifndef _VCF_THREADMANAGER_H__
#define _VCF_THREADMANAGER_H__
//Win32SystemToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {
class ThreadManagerPeer;

/**
*/
class FOUNDATIONKIT_API ThreadManager {
public:
	/**
	This creates the singleton instance of the ThreadManager
	*/
	static void create();

	/**
	This destroys the singleton instance of the ThreadManager
	*/
	static void terminate();

	/**
	\par
	Returns the current Thread object associated with the calling thread. 
	Depending on the platform, this gets the calling thread's ID and
	looks up the associated Thread object that is registered with the 
	ThreadManager.
	\par
	For Win32  - see GetCurrentThreadId()
	For Unix/Posix systems - see pthread_self
	For Mac OSX - see MPCurrentTaskID
	*/
	static Thread* getCurrentThread();

	/**
	\par
	Convenience function for retrieving the current thread's run loop.
	Equivalent to calling 
	\code
	RunLoop* runLoop = ThreadManager::getCurrentThread()->getRunLoop();
	\endcode

	@return RunLoop - the run loop instance of the current thread. 
	@see Thread::getRunLoop
	*/
	static RunLoop* getCurrentRunLoop();

	/**
	\par
	Allows you to wait on 1 or more wait objects till one of them
	becomes signaled. The duration of the wait is specified in milliseconds.
	\par
	When the function returns, the signaledObjects will contain a 
	list of signaled objects

	@param std::vector<Waitable*> a vector of Waitable* objects to 
	@param std::vector<Waitable*>
	@param uint32 the duration to wait before returning from the call. If the
	duration is exceeded the return value will be Waitable::wrTimedOut
	@return Waitable::WaitResult
	*/
	static Waitable::WaitResult wait( std::vector<Waitable*>& waitObjects, 
										std::vector<Waitable*>& signaledObjects, 
										uint32 timeoutInMilliseconds );

	/**
	*/
	static Waitable::WaitResult wait( std::vector<Waitable*>& waitObjects, 
										std::vector<Waitable*>& signaledObjects );

	/**
	*/
	static void addThread( Thread* thread );

	/**
	*/
	static void removeThread( Thread* thread );
protected:
	static ThreadManager* threadManagerInstance;

	std::map<uint32, Thread*> threads_;
	Mutex mtx_;
	ThreadManagerPeer* peer_;

	void internal_addThread( Thread* thread );

	void internal_removeThread( Thread* thread );
private:
	ThreadManager();
	~ThreadManager();
};

};

#endif //_VCF_THREADMANAGER_H__