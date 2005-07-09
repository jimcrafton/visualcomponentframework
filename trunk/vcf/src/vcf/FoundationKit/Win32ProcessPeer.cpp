//Win32ProcessPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"


using namespace VCF;

Win32ProcessPeer::Win32ProcessPeer()
{
	memset( &win32ProcessInfo_, 0, sizeof( win32ProcessInfo_ ) );
	win32ProcessInfo_.dwProcessId = ::GetCurrentProcessId();
	win32ProcessInfo_.dwThreadId = ::GetCurrentThreadId();
	win32ProcessInfo_.hProcess = ::GetCurrentProcess();
	win32ProcessInfo_.hThread = ::GetCurrentThread();

	TCHAR moduleFileName[MAX_PATH];
	memset( moduleFileName, 0, sizeof(moduleFileName) );
	//retreive the current running file name
	::GetModuleFileName( NULL, moduleFileName, MAX_PATH );
	processFileName_ = moduleFileName;
}

Win32ProcessPeer::~Win32ProcessPeer()
{

}

int Win32ProcessPeer::getProcessID()
{
	return win32ProcessInfo_.dwProcessId;
}

int Win32ProcessPeer::getProcessThreadID()
{
	return win32ProcessInfo_.dwThreadId;
}

bool Win32ProcessPeer::createProcess( const String& processName, const String& arguments )
{
	bool result = false;
	processFileName_ = "";

	String commandLine = "";
	BOOL bInheritHandles = FALSE;
	DWORD dwCreationFlags = 0;

	memset( &win32ProcessInfo_, 0, sizeof( win32ProcessInfo_ ) );

	String cmdLine = processName + " " + arguments;



	if ( System::isUnicodeEnabled() ) {
		STARTUPINFOW si;
		memset(&si,0,sizeof(si) );
		si.cb = sizeof(STARTUPINFOW);

		VCFChar* tmp = new VCFChar[cmdLine.size()+1];
		cmdLine.copy( tmp, cmdLine.size() );
		tmp[cmdLine.size()] = 0;

		result = ::CreateProcessW( NULL, tmp, NULL, NULL,
										bInheritHandles, dwCreationFlags,
										NULL, NULL, &si, &win32ProcessInfo_ ) ? true : false;

		delete [] tmp;
	}
	else {
		STARTUPINFOA si;
		memset(&si,0,sizeof(si) );
		si.cb = sizeof(STARTUPINFOA);

		AnsiString tmpCmdLine = cmdLine;
		char* tmp = new char[tmpCmdLine.size()+1];
		tmpCmdLine.copy( tmp, tmpCmdLine.size() );
		tmp[tmpCmdLine.size()] = 0;
		result = ::CreateProcessA( NULL, tmp, NULL, NULL,
										bInheritHandles, dwCreationFlags,
										NULL, NULL, &si, &win32ProcessInfo_ ) ? true : false;

		delete [] tmp;
	}



	if ( true == result ) {
		processFileName_ = processName;
	}
	else {
		int err = GetLastError();
	}

	return result;
}

String Win32ProcessPeer::getProcessFileName()
{
	return processFileName_;
}

OSHandleID Win32ProcessPeer::getHandleID()
{
	return (OSHandleID)win32ProcessInfo_.hProcess;
}

ulong32 Win32ProcessPeer::terminate()
{
	TerminateProcess( win32ProcessInfo_.hProcess, -1 );
	return -1;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:07  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/01/02 03:04:24  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.2  2005/04/09 17:21:34  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.2.4.1  2004/12/19 04:05:02  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.12.2.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.12  2004/04/03 15:48:48  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.11.2.1  2004/01/20 19:18:28  ddiego
*mod to Process class to allow it to be terminated
*
*Revision 1.11  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.2.1  2003/11/18 01:38:12  ddiego
**** empty log message ***
*
*Revision 1.10  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.9.2.1  2003/06/24 02:45:26  ddiego
*mods to the Process class and the Win32 peers
*
*Revision 1.9  2003/05/17 20:37:38  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8.2.1  2003/03/12 03:12:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.2.2  2002/12/27 23:04:55  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.7.2.1  2002/11/28 05:12:05  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.7  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.6.10.1  2002/09/17 18:48:36  ddiego
*added support in the VCF FoundationKit for redirecting io in a process
*
*Revision 1.6  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.5  2002/01/31 05:46:17  ddiego
*fixed resource leak with GraphicsContexts used as memory GC's
*Works fine in 98 with no drop of GDI resources.
*
*Revision 1.4  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.3  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


