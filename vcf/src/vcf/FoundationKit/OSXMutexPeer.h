#ifndef _VCF_OSXMUTEXPEER_H__
#define _VCF_OSXMUTEXPEER_H__
//OSXMutexPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF
{

/**
*Class ConditionalPeer documentation
*/
class OSXMutex : public MutexPeer
{
public:
	OSXMutex();

    virtual ~OSXMutex();

    virtual bool lock();
	
	virtual bool lock( uint32 timeoutInMilliseconds );

    virtual bool unlock();

    /**
    On OSX this returns a value that is a MPCriticalRegionID
    */
	virtual OSHandleID getHandleID() {
        return (OSHandleID)&mutex_;
    }

protected:
	MPCriticalRegionID mutex_;
};

};


#endif // _VCF_OSXMUTEXPEER_H__

/**
$Id$
*/
