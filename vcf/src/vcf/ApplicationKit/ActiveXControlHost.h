#ifndef _VCF_ACTIVEXCONTROLHOST_H__
#define _VCF_ACTIVEXCONTROLHOST_H__
//ActiveXControlHost.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/CustomControl.h"

namespace VCF
{

/**
 * This is a control that can host other ActiveX controls. This will have to implement whatever
 *functionality is neccesary on an ActiveX site container.
 *
 *@version 1.0
 *@author Jim Crafton
 */
class ActiveXControlHost :  public VCF::CustomControl{
public:
	virtual ~ActiveXControlHost(){};
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.4.8.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/05/17 20:37:00  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.1  2003/03/23 03:23:44  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3  2003/02/26 04:30:36  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.20.1  2003/01/08 00:19:42  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.2  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ACTIVEXCONTROLHOST_H__


