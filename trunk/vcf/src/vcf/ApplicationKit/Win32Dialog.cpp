//Win32Dialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Dialog.h"


using namespace VCFWin32;

using namespace VCF;


Win32Dialog::Win32Dialog():
	Win32Window()
{
	owner_ = NULL;
	dialogComponent_ = NULL;
}


Win32Dialog::Win32Dialog( Control* owner, Dialog* component ):
	Win32Window( component, owner )
{
	owner_ = owner;
	dialogComponent_ = component;
}


Win32Dialog::~Win32Dialog()
{

}

void Win32Dialog::init()
{
	createParams();
}

void Win32Dialog::create( Control* owningControl )
{
	String className = getClassName();
	if ( className.empty() ) {
		className = "VCF::Win32Dialog";
	}
	if ( true != isRegistered() ){
		registerWin32Class( className, wndProc_  );
	}
	init();

	HWND parent = NULL;
	if ( NULL != owner_ ){

		parent = (HWND)owner_->getPeer()->getHandleID();
	}

	if ( styleMask_ & WS_VISIBLE ) {
		styleMask_ &= ~WS_VISIBLE;
	}


	String caption = dialogComponent_->getCaption();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( exStyleMask_,
		                             className.c_str(),
									 caption.c_str(),
									 styleMask_,
		                             0,//bounds_.left_,
									 0,//bounds_.top_,
									 0,//bounds_.getWidth(),
									 0,//bounds_.getHeight(),
									 parent,
									 NULL,
									 ::GetModuleHandleW(NULL),
									 NULL );
	}
	else {
		hwnd_ = ::CreateWindowExA( exStyleMask_,
		                             className.ansi_c_str(),
									 caption.ansi_c_str(),
									 styleMask_,
		                             0,//bounds_.left_,
									 0,//bounds_.top_,
									 0,//bounds_.getWidth(),
									 0,//bounds_.getHeight(),
									 parent,
									 NULL,
									 ::GetModuleHandleA(NULL),
									 NULL );
	}


	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );
		HMENU sysMenu = ::GetSystemMenu( hwnd_, FALSE );
		if ( NULL != sysMenu ) 	{
			::RemoveMenu ( sysMenu, SC_MAXIMIZE, MF_BYCOMMAND );
			::RemoveMenu ( sysMenu, SC_MINIMIZE, MF_BYCOMMAND );
			::RemoveMenu ( sysMenu, SC_RESTORE, MF_BYCOMMAND );
			//::RemoveMenu ( sysMenu, SC_SIZE, MF_BYCOMMAND );

		}


		DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );


			if ( style & WS_MINIMIZEBOX ) {
				style &= ~WS_MINIMIZEBOX;
			}

			if ( style & WS_MAXIMIZEBOX ) {
				style &= ~WS_MAXIMIZEBOX;
			}
			::SetWindowLong( hwnd_, GWL_STYLE, style );
			::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );

	}
	setCreated( true );
}

void Win32Dialog::createParams()
{
	//WS_CLIPCHILDREN was added to fix bug 585239: Painting weirdness in a modal dialog
	styleMask_ = WS_POPUPWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | /*WS_OVERLAPPED | *//*WS_DLGFRAME |*/ DS_MODALFRAME | DS_3DLOOK;
	exStyleMask_ = WS_EX_RIGHTSCROLLBAR | WS_EX_WINDOWEDGE | WS_EX_DLGMODALFRAME | WS_EX_CONTEXTHELP;

	styleMask_ &= ~WS_MINIMIZEBOX;
	styleMask_ &= ~WS_MAXIMIZEBOX;
}

bool Win32Dialog::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;

	switch ( message ) {

		case WM_SHOWWINDOW :  {

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );
			DWORD tmp = style;
			if ( style & WS_MINIMIZEBOX ) {
				style &= ~WS_MINIMIZEBOX;
			}

			if ( style & WS_MAXIMIZEBOX ) {
				style &= ~WS_MAXIMIZEBOX;
			}

			if ( tmp != style ) {
				::SetWindowLong( hwnd_, GWL_STYLE, style );
				::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );
			}
		}
		break;
/*
		case WM_KEYDOWN : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam );
			Dialog* dlg = (Dialog*)peerControl_;
			if ( true == dlg->isModal() ) {
				KeyboardData keyData = Win32Utils::translateKeyData( hwnd_, lParam );
				VirtualKeyCode vkCode = (VirtualKeyCode)Win32Utils::translateVKCode( keyData.VKeyCode );

				if ( vkCode == vkEscape ) {

					PostMessage( hwnd_, WM_CLOSE, 0, 0 );
				}
			}
		}
		break;*/

		case WM_CLOSE:{
			Dialog* dlg = (Dialog*)peerControl_;

			if ( dlg->allowClose() ) {

				VCF::WindowEvent event( dlg, WINDOW_EVENT_CLOSE );


				dlg->FrameClose.fireEvent( &event );

				if ( dlg->isModal() ) {
					if ( NULL != dlg->getOwner() ) {
						dlg->getOwner()->setEnabled( true );
					}
					else if ( NULL != Application::getRunningInstance() ){
						Application::getRunningInstance()->getMainWindow()->setEnabled( true );
					}
					else {
						//thorw exception????
					}
				}

				result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			}
			else {
				//result = true, don't handle further
				wndProcResult = 0;
				result = true;
			}

		}
		break;

		case WM_DESTROY:{
			Dialog* dlg = (Dialog*)peerControl_;
			Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
			if ( true == dlg->isModal() ) {
				PostQuitMessage(0);
			}
		}
		break;

		default: result = Win32Window::handleEventMessages( message, wParam, lParam, wndProcResult );
	}
	return result;
}


void Win32Dialog::showMessage( const String& message, const String& caption )
{
	HWND activeWnd = GetActiveWindow();

	String tmp = caption;

	if ( tmp == "" ){
		TCHAR modFilename[MAX_PATH];
		memset(modFilename, 0, MAX_PATH );
		GetModuleFileName( GetModuleHandle(NULL), modFilename, MAX_PATH );
		tmp = modFilename;
		FilePath fp = tmp;
		tmp = fp.getBaseName(true);
	}

	if ( System::isUnicodeEnabled() ) {
		MessageBoxW( activeWnd, message.c_str(), tmp.c_str(), MB_OK );
	}
	else {
		MessageBoxA( activeWnd, message.ansi_c_str(), tmp.ansi_c_str(), MB_OK );
	}

}

UIToolkit::ModalReturnType Win32Dialog::showMessage( const String& message, const String& caption,
												 const long& messageButtons, const Dialog::MessageStyle& messageStyle )
{
	UIToolkit::ModalReturnType result = UIToolkit::mrNone;

	UINT mbStyle = 0;
	switch ( messageStyle ){
		case Dialog::msDefault: {

		}
		break;

		case Dialog::msError: {
			mbStyle = MB_ICONERROR;
		}
		break;

		case Dialog::msInfo: {
			mbStyle = MB_ICONINFORMATION;
		}
		break;

		case Dialog::msWarning: {
			mbStyle = MB_ICONWARNING;
		}
		break;
	}

	if ( messageButtons & Dialog::mbOK ) {
		mbStyle |= MB_OK;
	}
	else if ( messageButtons & Dialog::mbOKCancel ) {
		mbStyle |= MB_OKCANCEL;
	}
	else if ( messageButtons & Dialog::mbYesNo ) {
		mbStyle |= MB_YESNO;
	}
	else if ( messageButtons & Dialog::mbYesNoCancel ) {
		mbStyle |= MB_YESNOCANCEL;
	}
	else if ( messageButtons & Dialog::mbRetryCancel ) {
		mbStyle |= MB_RETRYCANCEL;
	}
	else if ( messageButtons & Dialog::mbAbortRetryIgnore ) {
		mbStyle |= MB_ABORTRETRYIGNORE;
	}

	if ( messageButtons & Dialog::mbHelp ) {
		mbStyle |= MB_HELP;
	}


	HWND activeWnd = GetActiveWindow();
	//if ( !IsWindow ( activeWnd ) ) {
		Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
		activeWnd = toolkit->getDummyParent();
	//}

	String tmp = caption;

	if ( tmp == "" ){
		TCHAR modFilename[MAX_PATH];
		memset(modFilename, 0, MAX_PATH );
		GetModuleFileName( GetModuleHandle(NULL), modFilename, MAX_PATH );
		tmp = modFilename;
		FilePath fp = tmp;
		tmp = fp.getBaseName(true);
	}

	int returnVal = 0;
	if ( System::isUnicodeEnabled() ) {
		returnVal = ::MessageBoxW( activeWnd, message.c_str(), tmp.c_str(), mbStyle );
	}
	else {
		returnVal = ::MessageBoxA( activeWnd, message.ansi_c_str(), tmp.ansi_c_str(), mbStyle );
	}


	switch ( returnVal ){
		case IDABORT:{
			result = UIToolkit::mrAbort;
		}
		break;

		case IDCANCEL:{
			result = UIToolkit::mrCancel;
		}
		break;
		/*
		case IDCONTINUE:{

		}
		break;
		*/
		case IDIGNORE:{
			result = UIToolkit::mrIgnore;
		}
		break;

		case IDNO:{
			result = UIToolkit::mrNo;
		}
		break;

		case IDOK:{
			result = UIToolkit::mrOK;
		}
		break;

		case IDRETRY:{
			result = UIToolkit::mrRetry;
		}
		break;
		/*
		case IDTRYAGAIN:{

		}
		break;
		*/
		case IDYES:{
			result = UIToolkit::mrYes;
		}
		break;
	}

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2004/12/05 21:11:55  ddiego
*dialog allowClose() fix in peer.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/12 22:34:21  ddiego
*fixed bug in handling window cleanup when exception thrown from constructor.
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/18 14:45:18  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.44.2.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.44  2004/04/03 16:09:31  ddiego
*Found some more merge issues that needing resolving.
*
*Revision 1.43  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.42.2.5  2003/10/13 21:28:41  ddiego
*fiddles with the containers a bit - didn't fix anything :(
*
*Revision 1.42.2.4  2003/09/03 22:52:49  marcelloptr
*minor fixes
*
*Revision 1.42.2.3  2003/09/03 01:42:05  ddiego
*some minor fixes
*
*Revision 1.42.2.2  2003/08/28 21:47:30  ddiego
*added escape reponse...
*
*Revision 1.42.2.1  2003/08/20 22:55:18  ddiego
*got rid of some older methods for StringUtils, should be using the FilePath
*class instead
*
*Revision 1.42  2003/08/09 02:56:46  ddiego
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
*Revision 1.41.2.5  2003/08/01 00:50:16  ddiego
*added a fix for popup windows that also fixed a problem with the
*ComboBoxControl drop down list disapearing.
*
*Revision 1.41.2.4  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.41.2.3  2003/06/13 03:05:32  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.41.2.2  2003/06/13 00:02:12  ddiego
*more xmake fixes for the new version
*bug fixes for bugs
*509004	Opening a modal Dialog causes flicker
*also have tooltips working again
*
*Revision 1.41.2.1  2003/05/27 04:45:33  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.41  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.40.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.40.2.1  2003/03/12 03:12:28  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.40  2003/02/26 04:30:50  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.39.2.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.39.2.3  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.39.2.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.39.2.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.39  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.38.10.2  2002/11/02 20:51:56  ddiego
*fixed NT4 menu bug 533453 Disapearing menu items on WinNT 4
*also added soem bug fixes for hte VCF Builder and some empty name
*error checking in the Win32FileStream class
*
*Revision 1.38.10.1  2002/10/08 04:16:57  ddiego
*fixed a bug in the getClientBounds() that caused a stack overflow! DOH!
*further additions to the TemplateNewClassDlg to sync the various file names
*in the dialog to the lcass name
*
*Revision 1.38  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.37  2002/03/21 04:01:01  ddiego
*fixed [ 532894 ] bug using the Frame::setClientBounds()
*
*Revision 1.36.4.2  2002/04/27 15:52:28  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.36.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.36  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.35  2002/01/30 22:12:47  ddiego
*fixed the internals of default CommandButton::click() method
*closes the dialog without relying on the WM_COMMAND message,
*and responds to  vkEnter keyboards events more correctly, i.e.
*the Doalog will automatically close now when you hit the enter key
*and the button wil set the modal result of the dialogd
*
*Revision 1.34  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


