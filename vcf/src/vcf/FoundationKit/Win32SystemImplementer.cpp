//Win32SystemImplementer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "Win32SystemImplementer.h"
#include "Win32Implementer.h"

using namespace VCF;

Win32SystemImplementer::Win32SystemImplementer()
{

}

Win32SystemImplementer::~Win32SystemImplementer()
{

}

unsigned long Win32SystemImplementer::getTickCount()
{
	return ::GetTickCount();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.4  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.3.20.1  2003/01/08 00:19:54  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.3  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


