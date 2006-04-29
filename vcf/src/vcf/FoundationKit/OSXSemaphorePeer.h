#ifndef _VCF_OSXSEMAPHOREPEER_H__
#define _VCF_OSXSEMAPHOREPEER_H__
//OSXSemaphorePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF  {

/**
*Class MutexPeer documentation
*/
class OSXSemaphore : public SemaphorePeer {
public:

    OSXSemaphore( long initialCount, long maxCount );
	virtual ~OSXSemaphore();

	virtual bool lock();
	
	virtual bool lock( uint32 timeoutInMilliseconds );

	virtual bool unlock();

    /**
    on OSX this returns a MPSemaphoreID
    */
	virtual OSHandleID getHandleID() {
        return (OSHandleID) semaphoreID_;
    }

protected:
    MPSemaphoreID semaphoreID_;

};


}; // end of namespace VCF


#endif // _VCF_OSXSEMAPHOREPEER_H__

/**
$Id$
*/
