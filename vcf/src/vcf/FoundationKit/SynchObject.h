#ifndef _VCF_SYNCHOBJECT_H__
#define _VCF_SYNCHOBJECT_H__
//SynchObject.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// SynchObject.h: interface for the SynchObject class.


namespace VCF
{

/**
\class SynchObject SynchObject.h "vcf/FoundationKit/SynchObject.h"
*Class SynchObject documentation
Defines an abstract base class for synchronisation classes
like mutexes and semaphores, to be used with the lock class
*/

class FOUNDATIONKIT_API SynchObject : public VCF::Interface
{
public:
	virtual ~SynchObject(){};
	
	/**
	Attempts tp lock the SynchObject and will block
	indefinitely till a lock is achieved.
	*/
	virtual bool lock() = 0;
	
	/**
	Attempts tp lock the SynchObject and will block
	for timeoutInMilliseconds till a lock is achieved.
	*/
	virtual bool lock( uint32 timeoutInMilliseconds ) = 0;

	virtual bool unlock() = 0;
};
}; // end of namespace VCF


#endif // _VCF_SYNCHOBJECT_H__

/**
$Id$
*/
