//PosixMutex.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;

PosixMutex::PosixMutex()
{
    pthread_mutex_init(&mutex_, NULL);
}

PosixMutex::~PosixMutex()
{
    pthread_mutex_destroy(&mutex_);
}

bool PosixMutex::lock()
{
    if ( pthread_mutex_lock(&mutex_) == 0 ) return true;
    return false;
}

bool PosixMutex::unlock()
{
    if ( pthread_mutex_unlock(&mutex_) == 0 ) return true;
    return false;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.2  2003/02/18 20:05:40  catwallader
*Added Condition classes. Also added comments to Thread and Mutex class
*headers.
*
*Revision 1.1.2.1  2003/02/12 19:35:55  catwallader
*Added PosixMutex class.
*
*/


