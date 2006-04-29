#ifndef _VCF_LOCK_H__
#define _VCF_LOCK_H__
//Lock.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

/**
\class Lock Lock.h "vcf/FoundationKit/Lock.h"
The Lock class represents a way to automatically lock or unlock a 
syncronizeable primitive, like a thread, mutex, or semaphore, by 
having the lifetime of the Lock stack based. This frees the 
developer from having to remember to call lock or unlock on the
sync object. For example:
\code
Mutex* mutex = //get a mutex
Lock l( *mutex );
//do some operations on a shared resource
\endcode
When the lock instance falls off of the stack, and it's destructor is called,
and the sync object's unlock method will be called.
@see SynchObject
@author Tiziano Franzoi, Nov 15, 2001
*/
class FOUNDATIONKIT_API Lock :public VCF::Object
{
public:
	Lock( VCF::SynchObject& synchObject ):synchObject_(synchObject)
	{
		validSynchObject_ = synchObject_.lock();
	}


	virtual ~Lock()
	{
		if( true == validSynchObject_ )
		{
			synchObject_.unlock();
		}
	}
protected:
	bool validSynchObject_;
	VCF::SynchObject& synchObject_;

private:
	/**
	* we forbid to copy a lock, as it would probably
	* cause some trouble.
	* Plus it would be impossible to define an explicit 
	* assignment operator with a reference. With this
	* the CodeWarrior doesn't complain anymore.
	*/
	Lock& operator = ( const Lock& lock ) { return *this; };

};
} // namespace VCF


#endif // _VCF_LOCK_H__

/**
$Id$
*/
