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

    pthread_cond_t     cond_;
    pthread_mutex_t*   mutex_;

};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/26 21:58:43  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.6.1  2004/03/30 01:48:16  ddiego
*updated linux code
*
*Revision 1.3  2003/05/17 20:37:12  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.2.1  2003/03/23 03:23:50  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.1  2003/02/18 20:03:29  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
**/


#endif // _VCF_POSIXCONDITION_H__


