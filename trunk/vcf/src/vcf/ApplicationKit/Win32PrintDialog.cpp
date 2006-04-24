//Win32PrintDialog.cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/GraphicsKit/PrintSession.h"
#include "vcf/GraphicsKit/PrintSessionPeer.h"
#include "vcf/GraphicsKit/Win32PrintSession.h"
#include "vcf/ApplicationKit/Win32PrintDialog.h"



using namespace VCF;



Win32PrintDialog::Win32PrintDialog( Control* owner ):
	owner_(owner)
{	
	
}

Win32PrintDialog::~Win32PrintDialog()
{

}

UINT CALLBACK Win32PrintDialog::PrintHookProc( HWND hdlg, UINT uiMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uiMsg ) {
		case WM_INITDIALOG : {
			PRINTDLG* printInfo = (PRINTDLG*)lParam;
			Win32PrintDialog* thisPtr = (Win32PrintDialog*)printInfo->lCustData;
			
			if ( !thisPtr->title_.empty() ) {
				if ( System::isUnicodeEnabled() ) {
					SetWindowTextW( hdlg, thisPtr->title_.c_str() );
				}
				else {
					SetWindowTextA( hdlg, thisPtr->title_.ansi_c_str() );
				}
			}

			return TRUE;
		}
		break;
	}
	
	return 0;//The default dialog proc will handle the rest
}

void Win32PrintDialog::setTitle( const String& title )
{
	this->title_ = title;
}

bool Win32PrintDialog::execute()
{
	bool result = false;

	HDC printDC = NULL;

	if ( System::isUnicodeEnabled() ) {
		PRINTDLGW& printDlg =  printInfo_.getPrintDlgW();

		printDlg.Flags |= PD_ENABLEPRINTHOOK | PD_RETURNDC;
		
		printDlg.hDC = NULL;
		printDlg.lCustData = (DWORD) this;
		if ( NULL != owner_ ) {
			printDlg.hwndOwner = (HWND)owner_->getPeer()->getHandleID();
		}
		else {
			printDlg.hwndOwner = NULL;
		}
		
		printDlg.nFromPage = printInfo_.getStartPage();
		printDlg.nToPage = printInfo_.getEndPage();
		
		printDlg.lpfnPrintHook = Win32PrintDialog::PrintHookProc;
		printDlg.nMinPage = printDlg.nFromPage;
		printDlg.nMaxPage = printDlg.nToPage;
		
		if ( PrintDlgW( &printDlg ) ) {
			result = true;
			
			
			if ( NULL != printDlg.hDevMode ) {
				LPDEVMODE  devModePtr = NULL;
				devModePtr = (LPDEVMODE)::GlobalLock(printDlg.hDevMode);
				
				printDlg.nCopies = devModePtr->dmCopies;
				
				::GlobalUnlock(printDlg.hDevMode);
			}

			printDC = printDlg.hDC;
			printInfo_.setStartPage( printDlg.nFromPage );
			printInfo_.setEndPage( printDlg.nToPage );
		}
	}
	else {
		PRINTDLGA& printDlg =  printInfo_.getPrintDlgA();

		printDlg.Flags |= PD_ENABLEPRINTHOOK | PD_RETURNDC;
		
		printDlg.hDC = NULL;
		printDlg.lCustData = (DWORD) this;
		if ( NULL != owner_ ) {
			printDlg.hwndOwner = (HWND)owner_->getPeer()->getHandleID();
		}
		else {
			printDlg.hwndOwner = NULL;
		}
		
		printDlg.nFromPage = printInfo_.getStartPage();
		printDlg.nToPage = printInfo_.getEndPage();
		
		printDlg.lpfnPrintHook = Win32PrintDialog::PrintHookProc;
		printDlg.nMinPage = printDlg.nFromPage;
		printDlg.nMaxPage = printDlg.nToPage;
		
		if ( PrintDlgA( &printDlg ) ) {
			result = true;
			
			
			if ( NULL != printDlg.hDevMode ) {
				LPDEVMODE  devModePtr = NULL;
				devModePtr = (LPDEVMODE)::GlobalLock(printDlg.hDevMode);
				
				printDlg.nCopies = devModePtr->dmCopies;
				
				::GlobalUnlock(printDlg.hDevMode);
			}

			printDC = printDlg.hDC;
			printInfo_.setStartPage( printDlg.nFromPage );
			printInfo_.setEndPage( printDlg.nToPage );
		}
	}
	

	if ( result == true ) {
		RECT r;
		r.left = 0;
		r.top = 0;
		r.right = ::GetDeviceCaps( printDC, HORZRES );
		r.bottom = ::GetDeviceCaps( printDC, VERTRES );
		
		DPtoLP( printDC, (LPPOINT)&r, 2 );
		
		printInfo_.pageSize_.width_ = r.right - r.left;
		printInfo_.pageSize_.height_ = r.bottom - r.top;
		
		printInfo_.pageDrawingRect_.setRect( 0, 0, printInfo_.pageSize_.width_, printInfo_.pageSize_.height_ );
	}

	return result;
}

void Win32PrintDialog::setPrintInfo( PrintInfoHandle info )
{
	Win32PrintInfo* infoPtr = (Win32PrintInfo*)info;

	if ( NULL != infoPtr ) {
		printInfo_ = *infoPtr;
	}
}

PrintInfoHandle Win32PrintDialog::getPrintInfo()
{
	return (PrintInfoHandle)&printInfo_;
}

void Win32PrintDialog::setNumberOfCopies( const ulong32& val )
{
	if ( System::isUnicodeEnabled() ) {
		printInfo_.getPrintDlgW().nCopies = val;
	}
	else {
		printInfo_.getPrintDlgA().nCopies = val;
	}	
}

ulong32 Win32PrintDialog::getNumberOfCopies()
{
	if ( System::isUnicodeEnabled() ) {
		return printInfo_.getPrintDlgW().nCopies;
	}
	else {
		return printInfo_.getPrintDlgA().nCopies;
	}	

	return 0;
}

void Win32PrintDialog::setStartPage( const ulong32& val )
{
	if ( System::isUnicodeEnabled() ) {
		printInfo_.getPrintDlgW().nFromPage = val;
	}
	else {
		printInfo_.getPrintDlgA().nFromPage = val;
	}	

	printInfo_.setStartPage( val );
}

ulong32 Win32PrintDialog::getStartPage()
{
	if ( System::isUnicodeEnabled() ) {
		return printInfo_.getPrintDlgW().nFromPage;
	}
	else {
		return printInfo_.getPrintDlgA().nFromPage;
	}	

	return 0;
}

void Win32PrintDialog::setEndPage( const ulong32& val )
{
	if ( System::isUnicodeEnabled() ) {
		printInfo_.getPrintDlgW().nToPage = val;
	}
	else {
		printInfo_.getPrintDlgA().nToPage = val;
	}	

	printInfo_.setEndPage( val );
}

ulong32 Win32PrintDialog::getEndPage()
{
	if ( System::isUnicodeEnabled() ) {
		return printInfo_.getPrintDlgW().nToPage;
	}
	else {
		return printInfo_.getPrintDlgA().nToPage;
	}	

	return 0;
}

void Win32PrintDialog::setPrintJobType( PrintSession::PrintJob val )
{
	DWORD flags = 0;

	if ( System::isUnicodeEnabled() ) {
		flags = printInfo_.getPrintDlgW().Flags;
	}
	else {
		flags = printInfo_.getPrintDlgA().Flags;
	}


	switch ( val ) {
		case PrintSession::pjPrintAll :  {
			flags &= ~PD_SELECTION;
			flags &= ~PD_PAGENUMS;
			flags |= PD_ALLPAGES;			
		}
		break;

		case PrintSession::pjPrintSelectedPage : {
			flags &= ~PD_PAGENUMS;
			flags &= ~PD_ALLPAGES;
			flags |= PD_SELECTION;
		}
		break;

		case PrintSession::pjPrintRange : {
			flags &= ~PD_ALLPAGES;
			flags &= ~PD_SELECTION;
			flags |= PD_PAGENUMS;			

		}
		break;
	}

	if ( System::isUnicodeEnabled() ) {
		printInfo_.getPrintDlgW().Flags = flags;
	}
	else {
		printInfo_.getPrintDlgA().Flags = flags;
	}
}

PrintSession::PrintJob Win32PrintDialog::getPrintJobType()
{
	DWORD flags = 0;

	if ( System::isUnicodeEnabled() ) {
		flags = printInfo_.getPrintDlgW().Flags;
	}
	else {
		flags = printInfo_.getPrintDlgA().Flags;
	}

	PrintSession::PrintJob result;
	if ( flags & PD_ALLPAGES ) {
		result = PrintSession::pjPrintAll;
	}
	else if ( flags & PD_SELECTION ) {
		result = PrintSession::pjPrintSelectedPage;
	}
	else if ( flags & PD_PAGENUMS ) {
		result = PrintSession::pjPrintRange;
	}
	return result;
}











/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2005/11/04 17:56:17  ddiego
*fixed bugs in some win32 code to better handle unicode - ansi functionality.
*
*Revision 1.3  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.2.1  2005/04/13 00:57:02  iamfraggle
*Enable Unicode in CodeWarrior
*
*Revision 1.2  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/11/21 00:19:10  ddiego
*fixed a few more res loading bugs, and added yet another resource example.
*
*Revision 1.1.2.1  2004/08/31 04:12:12  ddiego
*cleaned up the GraphicsContext class - made more pervasive use
*of transformation matrix. Added common print dialog class. Fleshed out
*printing example more.
*
*/

