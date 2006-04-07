//LinuxProcessIORedirector.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ProcessWithRedirectedIO.h"
#include "vcf/FoundationKit/LinuxProcessIORedirector.h"

using namespace VCF;

LinuxProcessIORedirector::LinuxProcessIORedirector()
{}

LinuxProcessIORedirector::~LinuxProcessIORedirector()
{}

bool LinuxProcessIORedirector::createProcess( const String& processName,
                                              const String& arguments )
{
	bool result = false;
	return result;
}

ulong32 LinuxProcessIORedirector::terminate()
{
	return 0;
}

Waitable::WaitResult LinuxProcessIORedirector::wait( uint32 milliseconds )
{
	Waitable::WaitResult result = Waitable::wrWaitFailed;
	return result;
}

Waitable::WaitResult LinuxProcessIORedirector::wait()
{
	Waitable::WaitResult result = Waitable::wrWaitFailed;
	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:34  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.2  2006/03/19 00:04:16  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.3.2.1  2005/11/28 21:01:06  ddiego
*added wait function to process class. added stubs for linux.
*
*Revision 1.3  2005/04/05 23:44:22  jabelardo
*a lot of fixes to compile on linux, it does not run but at least it compile
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.5  2004/04/03 15:48:46  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.4.2.1  2004/02/16 05:34:05  ddiego
*updated linux makefiles as a result of new locale support - pushed in stubs for locale peer impl, but no functionality at this point
*
*Revision 1.4  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.3.6.1  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.3  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.2  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.2.2.1  2002/12/27 23:04:51  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.1  2002/09/27 01:54:58  ddiego
*added support for bezier curves - remeber to change over to using teh MgcBeziers in Win32 too
*
*Revision 1.1.2.3  2002/09/20 21:28:44  ddiego
*added mods to support building from the VCF Builder and display the
*console build process. Also allows for double clicking in the output
*area and being able to read the output in a generic manner
*
*Revision 1.1.2.2  2002/09/18 21:50:57  ddiego
*added more support for building a project and displaying results in gui
*
*Revision 1.1.2.1  2002/09/17 18:48:36  ddiego
*added support in the VCF FoundationKit for redirecting io in a process
*
*/


