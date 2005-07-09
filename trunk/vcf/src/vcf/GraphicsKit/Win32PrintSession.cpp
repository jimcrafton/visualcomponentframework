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



#if defined(VCF_CW) && defined(UNICODE)
	static wchar_t szDefaultDocName[] = L"Untitled";
#else
	static char szDefaultDocName[] = "Untitled";
#endif


Win32PrintSession::Win32PrintSession():
	printerDC_(0)
{
	

	printInfo_.docInfo_.cbSize = sizeof(printInfo_.docInfo_);

	
	printInfo_.printDlg_.lStructSize = sizeof(printInfo_.printDlg_);
	printInfo_.printDlg_.Flags |= PD_RETURNDEFAULT;
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
	printInfo_.printDlg_.Flags |= PD_RETURNDEFAULT;
	::PrintDlg( &printInfo_.printDlg_ );

	LPDEVNAMES devNamesPtr = (LPDEVNAMES)::GlobalLock(printInfo_.printDlg_.hDevNames);
	LPDEVMODE  devModePtr = NULL;
	if ( NULL != printInfo_.printDlg_.hDevMode ) {
		devModePtr = (LPDEVMODE)::GlobalLock(printInfo_.printDlg_.hDevMode);
	}


	if ( NULL == devNamesPtr ) {

		//error!
	}

	HDC hDC = NULL;
	
	hDC = ::CreateDC((LPCTSTR)devNamesPtr + devNamesPtr->wDriverOffset,
					  (LPCTSTR)devNamesPtr + devNamesPtr->wDeviceOffset,
					  (LPCTSTR)devNamesPtr + devNamesPtr->wOutputOffset,
					  devModePtr);

	::GlobalUnlock(printInfo_.printDlg_.hDevNames);

	if ( NULL != printInfo_.printDlg_.hDevMode ) {

		::GlobalUnlock(printInfo_.printDlg_.hDevMode);
	}
	

	// [bugfix 1227570] do not assign this to a temporary
	printInfo_.docInfo_.lpszDocName = szDefaultDocName;

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

		printerDC_ = printInfo_.printDlg_.hDC;
	}
}

void Win32PrintSession::abort()
{
	::AbortDoc( printerDC_ );
}

PrintContext* Win32PrintSession::beginPrintingDocument()
{
#if defined(VCF_CW) && defined(UNICODE)
	printInfo_.docInfo_.lpszDocName = title_.c_str();	
#else
	printInfo_.docInfo_.lpszDocName = title_.ansi_c_str();
#endif
	if ( !::StartDoc( printerDC_, &printInfo_.docInfo_ ) ) {
		//throw exception???		
		return NULL;
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


