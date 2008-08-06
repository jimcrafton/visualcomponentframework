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





Win32PrintSession::Win32PrintSession()
#ifndef VCF_WIN32CE
:
printerDC_(0)
#endif
{
#ifndef VCF_WIN32CE
	if ( System::isUnicodeEnabled() ) {
		printInfo_.getPrintDlgW().Flags |= PD_RETURNDEFAULT;
	}
	else{
		printInfo_.getPrintDlgA().Flags |= PD_RETURNDEFAULT;
	}
#endif
}

Win32PrintSession::~Win32PrintSession()
{

}


String Win32PrintSession::getTitle()
{
#ifdef VCF_WIN32CE
	return L"";	
#else
	return title_;	
#endif
}

void Win32PrintSession::setTitle( const String& title )
{
#ifdef VCF_WIN32CE
#else
	title_ = title;
#endif
}

#ifndef VCF_WIN32CE
BOOL CALLBACK Win32PrintSession::AbortProc( HDC hdc, int iError )
{
	return TRUE;
}
#endif

void Win32PrintSession::setDefaultPageSettings()
{
	#ifdef VCF_WIN32CE
#else
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
#endif
}

Size Win32PrintSession::getPageSize()
{
	Size result;
	#ifdef VCF_WIN32CE
	return result;
#else
	return printInfo_.pageSize_;
#endif
}

void Win32PrintSession::setPageSize( const Size& pageSize )
{

}

void Win32PrintSession::setStandardPageSize( const PrintSession::PageSize& pageSize )
{

}

void Win32PrintSession::setStartPage( const uint32& startPage )
{	
	#ifdef VCF_WIN32CE
#else
	printInfo_.setStartPage( startPage );
#endif
}

uint32 Win32PrintSession::getStartPage()
{	
	#ifdef VCF_WIN32CE
	return 0;
#else
	return printInfo_.getStartPage();
#endif
}

void Win32PrintSession::setEndPage( const uint32& endPage )
{
	#ifdef VCF_WIN32CE
#else
	printInfo_.setEndPage( endPage );
#endif
}

uint32 Win32PrintSession::getEndPage()
{
	#ifdef VCF_WIN32CE
	return 0;
#else
	return printInfo_.getEndPage();
#endif

}
Rect Win32PrintSession::getPageDrawingRect()
{	
#ifdef VCF_WIN32CE
	return Rect();
#else
	return printInfo_.pageDrawingRect_;
#endif
}

void Win32PrintSession::setPageDrawingRect( const Rect& drawingRect )
{
	#ifdef VCF_WIN32CE
#else
	printInfo_.pageDrawingRect_ = drawingRect;
#endif
}

PrintInfoHandle Win32PrintSession::getPrintInfoHandle()
{
	#ifdef VCF_WIN32CE
	return NULL;
#else
	return (PrintInfoHandle)&printInfo_;
#endif
}

void Win32PrintSession::setPrintInfoHandle( PrintInfoHandle info )
{
	#ifdef VCF_WIN32CE
#else
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
#endif
}

void Win32PrintSession::abort()
{
#ifndef VCF_WIN32CE
	::AbortDoc( printerDC_ );
#endif
}

PrintContext* Win32PrintSession::beginPrintingDocument()
{
	PrintContext* result = NULL;
	#ifdef VCF_WIN32CE
#else
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

	

	result = new PrintContext((OSHandleID)printerDC_);
#endif
	return result;
}

void Win32PrintSession::endPrintingDocument()
{
	#ifdef VCF_WIN32CE
#else
	if ( !::EndDoc( printerDC_ ) ) {		
		//throw exception???
	}
#endif
}

void Win32PrintSession::beginPage( PrintContext* context )
{	
#ifdef VCF_WIN32CE
#else
	VCF_ASSERT( (HDC) context->getPeer()->getContextID() == printerDC_ );

	if ( ! ::StartPage( (HDC) context->getPeer()->getContextID() ) ) {
		//throw exception???
	}
#endif
}

double Win32PrintSession::getDPI()
{
	#ifdef VCF_WIN32CE
return 0.0;
#else
	return GetDeviceCaps( printerDC_, LOGPIXELSY );
#endif
}

void Win32PrintSession::endPage( PrintContext* context )
{
	#ifdef VCF_WIN32CE
#else
	VCF_ASSERT( (HDC) context->getPeer()->getContextID() == printerDC_ );

	if ( ! ::EndPage( (HDC) context->getPeer()->getContextID() ) ) {
		//throw exception???
	}
#endif
}

std::vector<uint32> Win32PrintSession::getPrintablePages()
{
	#ifdef VCF_WIN32CE
	static std::vector<uint32> res;
	return res;
#else
	return printInfo_.pages_;
#endif
}

void Win32PrintSession::setPrintablePages( const std::vector<uint32>& printablePages )
{
	#ifdef VCF_WIN32CE
#else
	printInfo_.pages_ = printablePages;
#endif
}


/**
$Id$
*/
