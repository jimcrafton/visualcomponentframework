#ifndef _VCF_X11CONTROL_H__
#define _VCF_X11CONTROL_H__
//X11Control.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_ABSTRACTX11CONTROL_H__
#	include "vcf/ApplicationKit/AbstractX11Control.h"
#endif // _VCF_ABSTRACTX11CONTROL_H__



/**
For unusual looking typedefs please see the vcf/ApplicationKit/X11Peer.h
*/

namespace VCF {


/**

*/
class X11Control : public Object, public AbstractX11Control {
public:

	X11Control( Control* control );

	virtual ~X11Control();

protected:

};



};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/05 01:55:20  marcelloptr
*moved some files to the directory where they logically belong
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.2.10.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2003/02/26 04:30:41  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.1.2.2  2002/12/30 03:59:25  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
*Revision 1.1.2.1  2002/12/27 06:44:45  ddiego
*added initial control peer for X11 controls
*
*Auto generated header for class X11Control
*/


#endif // _VCF_X11CONTROL_H__


