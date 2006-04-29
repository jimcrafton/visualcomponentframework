#ifndef _VCF_POSIXCONDITION_H__
#define _VCF_POSIXCONDITION_H__
//PosixCondition.h

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
*Class PosixCondition documentation
*/
class FOUNDATIONKIT_API PosixCondition : public ConditionPeer {
public:
    /* Every condtion must be associated with a mutex */
    PosixCondition( Condition* condition );

	virtual ~PosixCondition();

    virtual int wait();

	virtual int wait( uint32 milliseconds );

	virtual void signal();

    virtual void broadcast();

    /* Return "handle" that must be cast to a pthread_cond_t pointer */
	virtual OSHandleID getHandleID() {
		return (OSHandleID)&cond_;
	}

protected:

    pthread_cond_t   cond_;
    pthread_mutex_t* mutex_;

};

}; //end of namespace VCF


#endif // _VCF_POSIXCONDITION_H__

/**
$Id$
*/
