//HelpEvent.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//HelpEvent.h
#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;


HelpEvent::HelpEvent( Object* source ):
	Event( source, HELP_EVENT_TYPE )
{

}

HelpEvent::~HelpEvent()
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/05/17 20:37:18  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.22.2  2003/03/23 06:46:01  marcelloptr
*minor fixes
*
*Revision 1.2.22.1  2003/03/23 03:23:54  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


