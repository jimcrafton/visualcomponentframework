//Win32Object.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"


using namespace VCF;

std::vector< String > Win32Object::registeredWindowClasses_;

std::map<HWND, Win32Object*> Win32Object::windowMap_;


LRESULT CALLBACK Win32Object_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){

	Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( hWnd );

	if ( NULL != win32Obj ){
		LRESULT result = 0;
		if ( !win32Obj->handleEventMessages( message, wParam, lParam, result ) ) {
			result = win32Obj->defaultWndProcedure( message, wParam, lParam );
		}

		return result;
	}
	else {
		if ( System::isUnicodeEnabled() ) {
			return DefWindowProcW(hWnd, message, wParam, lParam);
		}
		else {
			return DefWindowProcA(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}


Win32Object::Win32Object():
	wndProc_(NULL),
	defaultWndProc_(NULL),
	hwnd_(NULL),
	created_(false),
	peerControl_(NULL)
{
	init();
	wndProc_ = Win32Object_WndProc;
	if ( System::isUnicodeEnabled() ) {
		defaultWndProc_ = ::DefWindowProcW;
	}
	else {
		defaultWndProc_ = ::DefWindowProcA;
	}

}

Win32Object::~Win32Object()
{

}

void Win32Object::destroyWindowHandle()
{
	if ( Win32Object::windowMap_.empty() ) {
		return;
	}

	std::map<HWND, Win32Object*>::iterator found =  Win32Object::windowMap_.find( hwnd_ );
	if ( found != Win32Object::windowMap_.end() ){
		Win32Object::windowMap_.erase( found );
	}
}

void Win32Object::subclassWindow()
{
	if ( System::isUnicodeEnabled() ) {
		defaultWndProc_ = (WNDPROC)::SetWindowLongW( hwnd_, GWL_WNDPROC, (LONG)wndProc_ );
	}
	else {
		defaultWndProc_ = (WNDPROC)::SetWindowLongA( hwnd_, GWL_WNDPROC, (LONG)wndProc_ );
	}
}

void Win32Object::addRegisterWin32Class( const String& className )
{
	Win32Object::registeredWindowClasses_.push_back( className );
}

void Win32Object::registerWin32Class( const String& className, WNDPROC wndProc )
{
	BOOL registered = FALSE;

	if ( System::isUnicodeEnabled() ) {
		WNDCLASSEXW wcex;

		wcex.cbSize = sizeof(wcex);

		wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc	= (WNDPROC)wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= (HINSTANCE)::GetModuleHandle(NULL);
		
		//This is taken care of in the Win32Window::create class, via
		//sending a WM_SETICON message
		wcex.hIcon			= NULL;

		wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= className.c_str();
		wcex.hIconSm		= NULL;

		registered = RegisterClassExW(&wcex);
	}
	else {
		WNDCLASSEXA wcex;

		wcex.cbSize = sizeof(wcex);

		wcex.style			= CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
		wcex.lpfnWndProc	= (WNDPROC)wndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= (HINSTANCE)::GetModuleHandle(NULL);
		wcex.hIcon			= NULL;
		wcex.hCursor		= NULL;//LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= NULL;//(HBRUSH)(COLOR_WINDOW+1);
		wcex.lpszMenuName	= NULL;
		wcex.lpszClassName	= className.ansi_c_str();
		wcex.hIconSm		= NULL;

		registered = RegisterClassExA(&wcex);
	}

	if ( registered ){
		addRegisterWin32Class( className );
	}
}

bool Win32Object::isRegistered()
{
	bool result = false;

	std::vector<String>::iterator it = std::find( Win32Object::registeredWindowClasses_.begin(),
													     Win32Object::registeredWindowClasses_.end(),
					                					 getClassName() );

	result = ( it != Win32Object::registeredWindowClasses_.end() );
	return result;
}

void Win32Object::init()
{
	hwnd_ = NULL;

	wndProc_ = NULL;
	defaultWndProc_ = NULL;

	created_ = false;

	peerControl_ = NULL;
}

Win32Object::CreateParams Win32Object::createParams()
{
	Win32Object::CreateParams result;
	result.first = SIMPLE_VIEW;
	result.second = 0;

	return result;
}

bool Win32Object::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	wndProcResult = 0;	
	return false;
}

Win32Object* Win32Object::getWin32ObjectFromHWND( HWND hwnd )
{
	Win32Object* result = NULL;

	if ( !Win32Object::windowMap_.empty() ) {

		std::map<HWND,Win32Object*>::iterator found =
			Win32Object::windowMap_.find( hwnd );

		if ( found != Win32Object::windowMap_.end() ){
			result = found->second;
		}
	}
	//result = (Win32Object*)::GetWindowLong( hwnd, GWL_USERDATA );

	return 	result;
}

HWND Win32Object::getHwnd()
{
	return hwnd_;
}

void Win32Object::registerWin32Object( Win32Object* wndObj )
{
	Win32Object::windowMap_[ wndObj->getHwnd() ] = wndObj;
	//::SetWindowLong( wndObj->getHwnd(), GWL_USERDATA, (LPARAM)wndObj );

	::PostMessage( wndObj->getHwnd(), VCF_CONTROL_CREATE, 0, 0 );
}

LRESULT Win32Object::defaultWndProcedure( UINT message, WPARAM wParam, LPARAM lParam )
{
	LRESULT result = 0;
	
	if ( System::isUnicodeEnabled() ) {
		if ( NULL != defaultWndProc_ ){
			result = CallWindowProcW( defaultWndProc_, hwnd_, message, wParam, lParam );
		}
		else {
			result = DefWindowProcW( hwnd_, message, wParam, lParam );
		}
	}
	else{
		
		if ( NULL != defaultWndProc_ ){
			result = CallWindowProcA( defaultWndProc_, hwnd_, message, wParam, lParam );
		}
		else {
			result = DefWindowProcA( hwnd_, message, wParam, lParam );
		}
	}
	

	return result;
}

void Win32Object::setCreated( const bool& creationComplete )
{
	created_ = creationComplete;
}

bool Win32Object::isCreated()
{
	return created_;
}

void Win32Object::setPeerControl( Control* control )
{
	peerControl_ = control;
}

Control* Win32Object::getPeerControl()
{
	return peerControl_;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*

*Revision 1.4  2005/01/02 03:04:22  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.2  2005/02/16 05:09:32  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.1  2004/12/10 21:14:00  ddiego
*fixed bug 1082362 App Icons do not appear.

*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/14 18:18:14  ddiego
*fixed problem with edit control. Turns out we were using the wrong
*subclassed wndproc. This is now fixed.
*
*Revision 1.1.2.5  2004/07/14 04:56:02  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.4  2004/07/12 02:05:45  ddiego
*fixed a subtle bug (that only showed up when using a lightweight
*control) that happened with MouseClick events being handled twice.
*
*Revision 1.1.2.3  2004/07/01 04:02:17  ddiego
*minor stuff
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.15.6.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.15  2003/08/09 02:56:46  ddiego
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
*Revision 1.14.2.2  2003/07/21 03:08:30  ddiego
*added bezier curve editing to Sketchit, fixed a bug in not saving
*bitmaps, added PackageInfo to the ApplicationKit
*
*Revision 1.14.2.1  2003/05/27 04:45:37  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.14  2003/05/17 20:37:37  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.13.2.1  2003/03/12 03:12:40  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.13  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.12.14.1  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.12  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.11.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.11  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


