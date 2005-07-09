//Win32CustomControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


// Win32CustomControl.cpp:

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Win32CustomControl.h"


using namespace VCF;


bool Win32CustomControl::windowClassRegistered_ = false;


LRESULT CALLBACK Win32CustomControl_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
		default: {
			if ( System::isUnicodeEnabled() ) {
				return DefWindowProcW(hWnd, message, wParam, lParam);
			}
			else {
				return DefWindowProcA(hWnd, message, wParam, lParam);
			}
		}
		break;

	}

	return 0;
}

Win32CustomControl::Win32CustomControl( Control* component )
{
	this->registerWndClass();
}

Win32CustomControl::~Win32CustomControl()
{

}

void Win32CustomControl::registerWndClass()
{
	if ( false == Win32CustomControl::windowClassRegistered_ ){
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style			= CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc	= (WNDPROC)Win32CustomControl_WndProc;
		wcex.cbClsExtra		= 0;
		wcex.cbWndExtra		= 0;
		wcex.hInstance		= 0;//?????
		wcex.hIcon			= NULL;
		wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground	= NULL;//(HBRUSH)(COLOR_BTNFACE+1);
		wcex.lpszMenuName	= NULL;
#if defined(VCF_CW) && !defined(UNICODE)
		wcex.lpszClassName  = this->getClassName().ansi_c_str();
#else
		wcex.lpszClassName	= this->getClassName().c_str();
#endif
		wcex.hIconSm		= NULL;

		if ( 0 != RegisterClassEx(&wcex) ){
			Win32CustomControl::windowClassRegistered_ = true;
		}
	}
}

long Win32CustomControl::getHandleID()
{
	long result = 0;
	result = (long)this->wndHandle_;
	return result;
}

String Win32CustomControl::getText()
{
	String result = "";

	return result;
}

void Win32CustomControl::setText( const String& text )
{

}

void Win32CustomControl::setBounds( Rect* rect )
{
	::SetWindowPos( this->wndHandle_, NULL,
	                rect->left_, rect->top_,
	                rect->getWidth(), rect->getHeight(),
	                SWP_NOACTIVATE );
}

Rect* Win32CustomControl::getBounds()
{
	Rect* result = NULL;
	RECT r = {0};
	::GetWindowRect( this->wndHandle_, &r );

	HWND parentHandle = ::GetParent( this->wndHandle_ );

	if ( NULL != parentHandle ){
		POINT pt = {0};
		pt.x = r.left;
		pt.y = r.top;
		ScreenToClient( parentHandle, &pt );
		r.left = pt.x;
		r.top = pt.y;

		pt.x = r.right;
		pt.y = r.bottom;
		ScreenToClient( parentHandle, &pt );
		r.right = pt.x;
		r.bottom = pt.y;

		bounds_.setRect( r.left, r.top, r.right, r.bottom );
		result = &bounds_;
	}
	return result;
}

void Win32CustomControl::setVisible( const bool& visible )
{
	if ( true == visible ){
		::ShowWindow( this->wndHandle_, SW_SHOW );
	}
	else{
		::ShowWindow( this->wndHandle_, SW_HIDE );
	}
}

bool Win32CustomControl::getVisible()
{
	bool result = false;
	DWORD style = GetWindowLong( this->wndHandle_, GWL_STYLE );
	result =  (style & WS_VISIBLE ) != 0;
	return result;
}

unsigned long Win32CustomControl::getStyleMask()
{
	unsigned long result = 0;
	result = GetWindowLong( this->wndHandle_, GWL_STYLE );
	return result;
}

void Win32CustomControl::setStyleMask( const unsigned long& styleMask )
{

}

Control* Win32CustomControl::getControl()
{
	return component_;
}

void Win32CustomControl::setControl( Control* component )
{
	this->component_ = component;
}

/* Removed as they are not declared in the header and CodeWarrior complains - ACH
void Win32CustomControl::getCursor()
{

}

void Win32CustomControl::setCursor()
{

}
*/
void Win32CustomControl::setParent( Control* parent )
{
	ControlPeer* Peer = parent->getPeer();
	HWND parentHandle = (HWND)Peer->getHandleID();

	if ( NULL == parentHandle ){
		//throw exception !!!
	}

	::SetParent( this->wndHandle_, parentHandle );
}

Control* Win32CustomControl::getParent()
{
	return NULL;
}

bool Win32CustomControl::isFocused()
{
	HWND focusedHandle = ::GetFocus();
	bool result = (NULL != focusedHandle) && (focusedHandle == this->wndHandle_);
	return result;
}

void Win32CustomControl::setFocus( const bool& focused )
{
	::SetFocus( this->wndHandle_ );
}

bool Win32CustomControl::isEnabled()
{
	return (::IsWindowEnabled( this->wndHandle_ ) != 0);
}

void Win32CustomControl::setEnabled( const bool& enabled )
{
	::EnableWindow( this->wndHandle_, enabled );
}

void Win32CustomControl::repaint( Rect* repaintRect )
{
	if ( NULL == repaintRect ){
		::InvalidateRect( this->wndHandle_, NULL, TRUE );
	}
	else {
		RECT rect = {0};
		rect.left = repaintRect->left_;
		rect.top = repaintRect->top_;
		rect.right = repaintRect->right_;
		rect.bottom = repaintRect->bottom_;
		::InvalidateRect( this->wndHandle_, &rect, TRUE );
	}
}

void Win32CustomControl::keepMouseEvents()
{
	::SetCapture( this->wndHandle_ );
}

void Win32CustomControl::releaseMouseEvents()
{
	::ReleaseCapture();
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:57  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.4  2005/06/29 05:00:03  marcelloptr
*some white spaces
*
*Revision 1.2.4.3  2005/04/17 06:10:54  iamfraggle
*UNICODE fix for CW
*
*Revision 1.2.4.2  2005/04/13 00:57:02  iamfraggle
*Enable Unicode in CodeWarrior
*
*Revision 1.2.4.1  2005/04/11 17:04:51  iamfraggle
*Changes allowing compilation of Win32 port under CodeWarrior
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.8.8.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.8  2003/05/17 20:37:35  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.1  2003/03/12 03:12:25  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:50  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.20.1  2003/01/08 00:19:52  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


