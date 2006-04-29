#ifndef _VCF_LINUXSEMAPHOREPEER_H__
#define _VCF_LINUXSEMAPHOREPEER_H__ 
//LinuxSemaphorePeer.h



/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

// LinuxSemaphorePeer.h: interface for the LinuxSemaphorePeer class.

namespace VCF
{

/**
*Class LinuxSemaphorePeer documentation
Implements the base SemaphorePeer class
used for synchronizing access to threaded
resources
*/ 
/**
*Class LinuxSemaphorePeer
*@author Jim Crafton, May 26 2002
*/
class LinuxSemaphorePeer : public VCF::Object, public VCF::SemaphorePeer
{
public:
	LinuxSemaphorePeer( long initialCount , long maxCount );

	virtual ~LinuxSemaphorePeer();

	virtual bool lock();

    virtual bool lock( uint32 timeoutInMilliseconds );

	virtual bool unlock();

	virtual OSHandleID getHandleID() {
		return (OSHandleID)&semaphore_;
	}
	
protected:
	sem_t semaphore_;

};

} // end of namespace VCF


#endif // _VCF_LINUXSEMAPHOREPEER_H__

/**
$Id$
*/
