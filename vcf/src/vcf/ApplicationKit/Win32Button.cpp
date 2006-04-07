//Win32Button.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Button.h"
#include "vcf/ApplicationKit/CommandButton.h"

using namespace VCF;


Win32Button::Win32Button( CommandButton* component ):
	AbstractWin32Component( component ),
	commandButton_(component)
{

}

Win32Button::~Win32Button()
{

}

void Win32Button::create( Control* owningControl )
{
	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	String className = getClassName();

	CreateParams params = createParams();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
		                             L"BUTTON",
									 windowCaption_.c_str(),
									 params.first,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}
	else {
		hwnd_ = ::CreateWindowExA( params.second,
		                             "BUTTON",
									 windowCaption_.ansi_c_str(),
									 params.first,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandleA(NULL),
									 NULL );
	}



	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );
		subclassWindow();
		registerForFontChanges();
	}
	else {
		//throw exception
	}

	setCreated( true );
}

Win32Object::CreateParams Win32Button::createParams()
{
	Win32Object::CreateParams result;
	result.first = WS_VISIBLE | WS_CHILD | BS_OWNERDRAW;
	result.second = 0;

	return result;
}

Image* Win32Button::getImage()
{
	return NULL;
}


void Win32Button::setImage( Image* image )
{

}

ButtonState Win32Button::getState()
{
	return state_;
}


bool Win32Button::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;

	switch ( message ) {
		
		case WM_PAINT:{
			//check to see if the font needs updating
		}
		break;

		case WM_ERASEBKGND:{
			wndProcResult = TRUE;
			result = true;
		}
		break;

		case WM_DRAWITEM:{
			DRAWITEMSTRUCT* drawItem = (DRAWITEMSTRUCT*)lParam;

			state_.setFocused( (drawItem->itemState & ODS_FOCUS) || peerControl_->isFocused() );
			state_.setEnabled( !(drawItem->itemState & ODS_DISABLED) );
			state_.setPressed( drawItem->itemState & ODS_SELECTED );

			CommandButton* button = (CommandButton*)peerControl_;
			button->setIsPressed( drawItem->itemState & ODS_SELECTED ? true : false );

			if ( peerControl_->isDoubleBuffered() ){

				if ( NULL == memDC_ ) {
						//create here
					HDC dc = ::GetDC(0);
					memDC_ = ::CreateCompatibleDC( dc );
					::ReleaseDC( 0,	dc );
				}

				VCF::GraphicsContext* ctx = peerControl_->getContext();

				int dcState = ::SaveDC( drawItem->hDC );
				Rect tmp(drawItem->rcItem.left, drawItem->rcItem.top, drawItem->rcItem.right, drawItem->rcItem.bottom);

				HBITMAP memBitmap =
					::CreateCompatibleBitmap( drawItem->hDC,
												drawItem->rcItem.right - drawItem->rcItem.left,
												drawItem->rcItem.bottom - drawItem->rcItem.top );

				HBITMAP oldBMP = (HBITMAP)::SelectObject( memDC_, memBitmap );

				//clear the memdc
				Control* parent = peerControl_->getParent();
				Color* bkColor = parent->getColor();
				HBRUSH bkBr = CreateSolidBrush( RGB( bkColor->getRed()*255.0, bkColor->getGreen()*255.0, bkColor->getBlue()*255.0 ) );
				FillRect( memDC_, &drawItem->rcItem, bkBr );
				DeleteObject( bkBr );


				::SetViewportOrgEx( memDC_, -drawItem->rcItem.left, -drawItem->rcItem.top, NULL );

				//::BitBlt( memDC_, 0, 0,
				//					drawItem->rcItem.right - drawItem->rcItem.left,
				//					drawItem->rcItem.bottom - drawItem->rcItem.top,
				//					drawItem->hDC, drawItem->rcItem.left, drawItem->rcItem.top, SRCCOPY );

				


				ctx->getPeer()->setContextID( (OSHandleID)memDC_ );

				((ControlGraphicsContext*)ctx)->setOwningControl( NULL );

				peerControl_->internal_beforePaint( ctx );

				peerControl_->paint( ctx );

				peerControl_->internal_afterPaint( ctx );


				((ControlGraphicsContext*)ctx)->setOwningControl( peerControl_ );

				::SetViewportOrgEx( memDC_, -drawItem->rcItem.left, -drawItem->rcItem.top, NULL );

				int err = ::BitBlt( drawItem->hDC, drawItem->rcItem.left, drawItem->rcItem.top,
									drawItem->rcItem.right - drawItem->rcItem.left,
									drawItem->rcItem.bottom - drawItem->rcItem.top,
									memDC_, drawItem->rcItem.left, drawItem->rcItem.top, SRCCOPY );

				::SelectObject( memDC_, oldBMP );

				::DeleteObject( memBitmap );

				::RestoreDC ( memDC_, dcState );

				if ( err == FALSE ) {
					err = GetLastError();
					StringUtils::traceWithArgs( Format("error in BitBlt during drawing of double buffered Comp: error code=%d\n") %
						err );
				}
			}
			else {
				VCF::GraphicsContext* ctx = peerControl_->getContext();

				ctx->getPeer()->setContextID( (OSHandleID)drawItem->hDC );

				peerControl_->internal_beforePaint( ctx );

				peerControl_->paint( ctx );

				peerControl_->internal_afterPaint( ctx );
			}
			wndProcResult = TRUE;
			result = true;
		}
		break;

		case WM_NCCALCSIZE: {
			wndProcResult = handleNCCalcSize( wParam, lParam );
			result = true;
		}
		break;

		case WM_NCPAINT: {	

			wndProcResult = handleNCPaint( wParam, lParam );
			return true;
		}
		break;

		case BN_CLICKED :{

			if ( peerControl_->isDesigning() ) {
				wndProcResult = 0;
				result = true;
			}
			else {
				commandButton_->click();
			}
		}
		break;
		

		case WM_COMMAND: {			
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );			
		}

		default: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

		}
	}
	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.6  2006/03/18 19:04:56  ddiego
*minor update to remove dead code for checkFontUpdate function.
*
*Revision 1.5.2.5  2006/03/16 03:23:09  ddiego
*fixes some font change notification issues in win32 peers.
*
*Revision 1.5.2.4  2006/03/10 05:35:57  ddiego
*fixed repaint for win32window when first made visible.
*
*Revision 1.5.2.3  2006/02/20 20:42:08  ddiego
*comitting current state of theme code.
*
*Revision 1.5.2.2  2005/09/16 01:12:01  ddiego
*fixed bug in component loaded function.
*
*Revision 1.5.2.1  2005/09/05 14:38:31  ddiego
*added pre and post paint delegates to the control class.
*
*Revision 1.5  2005/07/09 23:14:57  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:21  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3.2.5  2005/04/26 02:29:39  ddiego
*fixes font setting bug brought up by scott and glen_f
*
*Revision 1.3.2.4  2005/04/20 02:26:00  ddiego
*fixes for single line text and formatting problems in text window creation.
*
*Revision 1.3.2.3  2005/03/15 01:51:50  ddiego
*added support for Format class to take the place of the
*previously used var arg funtions in string utils and system. Also replaced
*existing code in the framework that made use of the old style var arg
*functions.
*
*Revision 1.3.2.2  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.1  2004/12/19 04:04:59  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/09/06 23:05:55  ddiego
*fixed border in button class
*
*Revision 1.2.2.2  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2.2.1  2004/08/22 19:01:34  dougtinkham
*drawBasicButton painted 1 too many pixels. fixed.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/14 18:18:14  ddiego
*fixed problem with edit control. Turns out we were using the wrong
*subclassed wndproc. This is now fixed.
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.24.2.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.24  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.23.4.1  2004/03/23 05:04:28  ddiego
*minor nigglies
*
*Revision 1.23  2003/08/09 02:56:46  ddiego
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
*Revision 1.22.2.2  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.22.2.1  2003/05/27 04:45:33  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.22  2003/05/17 20:37:34  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.21.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.21.2.1  2003/03/12 03:12:19  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.21  2003/02/26 04:30:49  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.20.14.3  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.20.14.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.20.14.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.20  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.19.4.2  2002/04/27 15:52:24  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.19.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.19  2002/01/30 22:12:47  ddiego
*fixed the internals of default CommandButton::click() method
*closes the dialog without relying on the WM_COMMAND message,
*and responds to  vkEnter keyboards events more correctly, i.e.
*the Doalog will automatically close now when you hit the enter key
*and the button wil set the modal result of the dialogd
*
*Revision 1.18  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.17  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


