//Win32PrintSession.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include <commdlg.h>
#include "vcf/GraphicsKit/PrintSession.h"
#include "vcf/GraphicsKit/PrintSessionPeer.h"
#include "vcf/GraphicsKit/Win32PrintSession.h"
#include "vcf/GraphicsKit/PrintContext.h"

using namespace VCF;





Win32PrintSession::Win32PrintSession():
	printerDC_(0)
{
	if ( System::isUnicodeEnabled() ) {
		printInfo_.getPrintDlgW().Flags |= PD_RETURNDEFAULT;
	}
	else{
		printInfo_.getPrintDlgA().Flags |= PD_RETURNDEFAULT;
	}
}

Win32PrintSession::~Win32PrintSession()
{

}


String Win32PrintSession::getTitle()
{
	return title_;	
}

void Win32PrintSession::setTitle( const String& title )
{
	title_ = title;
}

BOOL CALLBACK Win32PrintSession::AbortProc( HDC hdc, int iError )
{
	return TRUE;
}

void Win32PrintSession::setDefaultPageSettings()
{
	HDC hDC = NULL;
	
	if ( System::isUnicodeEnabled() ) {
		PRINTDLGW& printDlg =  printInfo_.getPrintDlgW();


		printDlg.Flags |= PD_RETURNDEFAULT;
		
		::PrintDlgW( &printDlg );
		
		LPDEVNAMES devNamesPtr = (LPDEVNAMES)::GlobalLock(printDlg.hDevNames);
		LPDEVMODEW  devModePtr = NULL;
		if ( NULL != printDlg.hDevMode ) {
			devModePtr = (LPDEVMODEW)::GlobalLock(printDlg.hDevMode);
		}
		
		
		if ( NULL == devNamesPtr ) {
			
			//error!
		}
		
		
		
		hDC = ::CreateDCW((WideChar*)devNamesPtr + devNamesPtr->wDriverOffset,
			(WideChar*)devNamesPtr + devNamesPtr->wDeviceOffset,
			(WideChar*)devNamesPtr + devNamesPtr->wOutputOffset,
			devModePtr);
		
		::GlobalUnlock(printDlg.hDevNames);
		
		if ( NULL != printDlg.hDevMode ) {
			
			::GlobalUnlock(printDlg.hDevMode);
		}


		static WideChar DefaultDocumentName[] = L"Untitled";


		// [bugfix 1227570] do not assign this to a temporary
		printInfo_.getDocInfoW().lpszDocName = DefaultDocumentName;
	}
	else {
		PRINTDLGA& printDlg =  printInfo_.getPrintDlgA();


		printDlg.Flags |= PD_RETURNDEFAULT;
		
		::PrintDlgA( &printDlg );
		
		LPDEVNAMES devNamesPtr = (LPDEVNAMES)::GlobalLock(printDlg.hDevNames);
		LPDEVMODEA  devModePtr = NULL;
		if ( NULL != printDlg.hDevMode ) {
			devModePtr = (LPDEVMODEA)::GlobalLock(printDlg.hDevMode);
		}
		
		
		if ( NULL == devNamesPtr ) {
			
			//error!
		}
		
		
		
		hDC = ::CreateDCA((char*)devNamesPtr + devNamesPtr->wDriverOffset,
			(char*)devNamesPtr + devNamesPtr->wDeviceOffset,
			(char*)devNamesPtr + devNamesPtr->wOutputOffset,
			devModePtr);
		
		::GlobalUnlock(printDlg.hDevNames);
		
		if ( NULL != printDlg.hDevMode ) {
			
			::GlobalUnlock(printDlg.hDevMode);
		}


		static char DefaultDocumentName[] = "Untitled";


		// [bugfix 1227570] do not assign this to a temporary
		printInfo_.getDocInfoA().lpszDocName = DefaultDocumentName;
	}
	

	printerDC_ = hDC;

	::SetAbortProc( printerDC_, Win32PrintSession::AbortProc );

	RECT r;
	r.left = 0;
	r.top = 0;
	r.right = ::GetDeviceCaps( printerDC_, HORZRES );
	r.bottom = ::GetDeviceCaps( printerDC_, VERTRES );

	DPtoLP( printerDC_, (LPPOINT)&r, 2 );

	printInfo_.pageSize_.width_ = r.right - r.left;
	printInfo_.pageSize_.height_ = r.bottom - r.top;

	printInfo_.pages_[0] = 1;

	printInfo_.pageDrawingRect_.setRect( 0, 0, printInfo_.pageSize_.width_, printInfo_.pageSize_.height_ );

}

Size Win32PrintSession::getPageSize()
{
	Size result;
	return printInfo_.pageSize_;
}

void Win32PrintSession::setPageSize( const Size& pageSize )
{

}

void Win32PrintSession::setStandardPageSize( const PrintSession::PageSize& pageSize )
{

}

void Win32PrintSession::setStartPage( const ulong32& startPage )
{	
	printInfo_.setStartPage( startPage );
}

ulong32 Win32PrintSession::getStartPage()
{	
	return printInfo_.getStartPage();
}

void Win32PrintSession::setEndPage( const ulong32& endPage )
{
	printInfo_.setEndPage( endPage );
}

ulong32 Win32PrintSession::getEndPage()
{
	return printInfo_.getEndPage();

}
Rect Win32PrintSession::getPageDrawingRect()
{	
	return printInfo_.pageDrawingRect_;
}

void Win32PrintSession::setPageDrawingRect( const Rect& drawingRect )
{
	printInfo_.pageDrawingRect_ = drawingRect;
}

PrintInfoHandle Win32PrintSession::getPrintInfoHandle()
{
	return (PrintInfoHandle)&printInfo_;
}

void Win32PrintSession::setPrintInfoHandle( PrintInfoHandle info )
{
	Win32PrintInfo* infoPtr = (Win32PrintInfo*)info;

	if ( NULL != infoPtr ) {
		printInfo_ = *infoPtr;

		if ( System::isUnicodeEnabled() ) {
			printerDC_ = printInfo_.getPrintDlgW().hDC;
		}
		else {
			printerDC_ = printInfo_.getPrintDlgA().hDC;
		}		
	}
}

void Win32PrintSession::abort()
{
	::AbortDoc( printerDC_ );
}

PrintContext* Win32PrintSession::beginPrintingDocument()
{
	if ( System::isUnicodeEnabled() ) {
		printInfo_.getDocInfoW().lpszDocName = title_.c_str();
		if ( !::StartDocW( printerDC_, &printInfo_.getDocInfoW() ) ) {
			//throw exception???		
			return NULL;
		}
	}
	else{
		printInfo_.getDocInfoA().lpszDocName = title_.ansi_c_str();
		if ( !::StartDocA( printerDC_, &printInfo_.getDocInfoA() ) ) {
			//throw exception???		
			return NULL;
		}
	}

	

	PrintContext* result = new PrintContext((OSHandleID)printerDC_);

	return result;
}

void Win32PrintSession::endPrintingDocument()
{
	if ( !::EndDoc( printerDC_ ) ) {		
		//throw exception???
	}
}

void Win32PrintSession::beginPage( PrintContext* context )
{	
	VCF_ASSERT( (HDC) context->getPeer()->getContextID() == printerDC_ );

	if ( ! ::StartPage( (HDC) context->getPeer()->getContextID() ) ) {
		//throw exception???
	}
}

double Win32PrintSession::getDPI()
{
	return GetDeviceCaps( printerDC_, LOGPIXELSY );
}

void Win32PrintSession::endPage( PrintContext* context )
{
	VCF_ASSERT( (HDC) context->getPeer()->getContextID() == printerDC_ );

	if ( ! ::EndPage( (HDC) context->getPeer()->getContextID() ) ) {
		//throw exception???
	}
}

std::vector<ulong32> Win32PrintSession::getPrintablePages()
{
	return printInfo_.pages_;
}

void Win32PrintSession::setPrintablePages( const std::vector<ulong32>& printablePages )
{
	printInfo_.pages_ = printablePages;
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:42  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.1  2005/11/04 17:56:17  ddiego
*fixed bugs in some win32 code to better handle unicode - ansi functionality.
*
*Revision 1.4  2005/07/09 23:06:02  ddiego
*added missing gtk files
*
*Revision 1.2.2.5  2005/06/25 23:10:24  marcelloptr
*[bugfix 1227570] Win32PrintSession::setDefaultPageSettings assigns a pointer to a temporary
*
*Revision 1.2.2.3  2005/04/29 15:03:40  marcelloptr
*added cvs log section
*
*/


