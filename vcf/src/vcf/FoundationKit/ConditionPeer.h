#ifndef _VCF_CONDITIONPEER_H__
#define _VCF_CONDITIONPEER_H__
//ConditionPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

/**
\class ConditionPeer ConditionPeer.h "vcf/FoundationKit/ConditionPeer.h"
*Class ConditionPeer documentation
*/
class FOUNDATIONKIT_API ConditionPeer {
public:
	virtual ~ConditionPeer() {}

	virtual int wait() = 0;

	virtual int wait( uint32 milliseconds ) = 0;

	virtual void signal() = 0;

    virtual void broadcast() = 0;

	virtual OSHandleID getHandleID() = 0;
};


}; //end of namespace VCF


#endif // _VCF_CONDITIONPEER_H__

/**
$Id$
*/
