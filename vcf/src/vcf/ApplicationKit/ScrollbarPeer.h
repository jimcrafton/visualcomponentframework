#ifndef _VCF_SCROLLBARPEER_H__
#define _VCF_SCROLLBARPEER_H__
//ScrollbarPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

class APPLICATIONKIT_API ScrollbarPeer : public VCF::Interface {
public:

    virtual double getPosition() = 0;

    virtual void setPosition(const double& position ) = 0;

    virtual void setMax(const double& max ) = 0;

    virtual double getMax() = 0;

    virtual double getMin() = 0;

    virtual void setMin( const double& min ) = 0;

    virtual void getPageSize() = 0;

    virtual void setPageSize() = 0;

    virtual void getOrientation() = 0;

    virtual void setOrientation() = 0;
};

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.7.10.1  2004/04/26 21:58:41  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2003/01/08 00:19:45  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_SCROLLBARPEER_H__


