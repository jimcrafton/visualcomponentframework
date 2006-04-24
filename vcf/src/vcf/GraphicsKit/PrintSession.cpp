//PrintSession.cpp

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/PrintSession.h"
#include "vcf/GraphicsKit/PrintSessionPeer.h"


using namespace VCF;

PrintSession::PrintSession():
	peer_(NULL),
	errorDuringPrinting_(false),
	currentPage_(PrintSession::UnknownPage)
{	
	peer_ = GraphicsToolkit::createPrintSessionPeer();
	if ( NULL == peer_ ) {

	}
}

PrintSession::~PrintSession()
{
	delete peer_;
}

double PrintSession::getDPI()
{
	return peer_->getDPI();
}

String PrintSession::getTitle()
{
	return title_;
}

void PrintSession::setTitle( const String& title )
{
	title_ = title;
	peer_->setTitle( title_ );
}

void PrintSession::setDefaultPageSettings()
{
	peer_->setDefaultPageSettings();
}

Size PrintSession::getPageSize()
{
	return peer_->getPageSize();
}

Size PrintSession::getPageSizeIn( PrintSession::PageSizeUnits units )
{	
	Size adjustedPageSize(peer_->getPageSize());

	double dpi = peer_->getDPI();

	switch( units ) {
		case psuPoints : {
			adjustedPageSize.width_ = (adjustedPageSize.width_/dpi) * 72.0;
			adjustedPageSize.height_ = (adjustedPageSize.height_/dpi) * 72.0;
		}
		break;

		case psuInches : {
			adjustedPageSize.width_ = adjustedPageSize.width_ / dpi;
			adjustedPageSize.height_ = adjustedPageSize.height_ / dpi;
		}
		break;

		case psuMillimeters : {
			adjustedPageSize.width_ = (adjustedPageSize.width_/dpi) * 25.40;
			adjustedPageSize.height_ = (adjustedPageSize.height_/dpi) * 25.40;
		}
		break;

		case psuTwips : {
			adjustedPageSize.width_ = (adjustedPageSize.width_/dpi) * 1400.0;
			adjustedPageSize.height_ = (adjustedPageSize.height_/dpi) * 1400;			
		}
		break;
	}

	return adjustedPageSize;
}

void PrintSession::setPageSize( const Size& pageSize )
{
	peer_->setPageSize(pageSize);
}

void PrintSession::setPageSizeIn( const Size& pageSize, PrintSession::PageSizeUnits units )
{
	Size adjustedPageSize(pageSize);

	double dpi = peer_->getDPI();

	switch( units ) {
		case psuPoints : {
			adjustedPageSize.width_ = (pageSize.width_/72.0) * dpi;
			adjustedPageSize.height_ = (pageSize.height_/72.0) * dpi;
		}
		break;

		case psuInches : {
			adjustedPageSize.width_ = pageSize.width_ * dpi;
			adjustedPageSize.height_ = pageSize.height_ * dpi;
		}
		break;

		case psuMillimeters : {
			adjustedPageSize.width_ = (pageSize.width_/25.40) * dpi;
			adjustedPageSize.height_ = (pageSize.height_/25.40) * dpi;
		}
		break;

		case psuTwips : {
			adjustedPageSize.width_ = (pageSize.width_/1400.0) * dpi;
			adjustedPageSize.height_ = (pageSize.height_/1400.0) * dpi;
		}
		break;
	}
	

	peer_->setPageSize(adjustedPageSize);
}

void PrintSession::setStandardPageSize( const PageSize& pageSize )
{
	peer_->setStandardPageSize(pageSize);
}

void PrintSession::setStartPage( const ulong32& startPage )
{
	peer_->setStartPage(startPage);
}

ulong32 PrintSession::getStartPage()
{
	return peer_->getStartPage();
}

void PrintSession::setEndPage( const ulong32& endPage )
{
	peer_->setEndPage(endPage);
}

ulong32 PrintSession::getEndPage()
{
	return peer_->getEndPage();
}

std::vector<ulong32> PrintSession::getPrintablePages()
{
	return peer_->getPrintablePages();
}

void PrintSession::setPrintablePages( const std::vector<ulong32>& printablePages )
{
	peer_->setPrintablePages( printablePages );
}

Rect PrintSession::getPageDrawingRect()
{
	return peer_->getPageDrawingRect();
}

void PrintSession::setPageDrawingRect( const Rect& drawingRect )
{
	peer_->setPageDrawingRect( drawingRect );
}


PrintInfoHandle PrintSession::getPrintInfoHandle()
{
	return peer_->getPrintInfoHandle();
}

void PrintSession::setPrintInfoHandle( PrintInfoHandle info )
{
	peer_->setPrintInfoHandle( info );
}

void PrintSession::abort()
{
	peer_->abort();
}

PrintContext* PrintSession::beginPrintingDocument()
{
	errorDuringPrinting_ = false;
	PrintContext* result = peer_->beginPrintingDocument();

	result->setViewableBounds( getPageDrawingRect() );

	PrintEvent event( this, result, PrintSession::UnknownPage, PrintingBegunEvent );
	PrintingBegun.fireEvent( &event );

	return result;
}

void PrintSession::endPrintingDocument()
{
	try {
		peer_->endPrintingDocument();

		PrintEvent event( this, NULL, PrintSession::UnknownPage, PrintingFinishedEvent );
		PrintingFinished.fireEvent( &event );
	}
	catch ( BasicException& ) {
		errorDuringPrinting_ = true;
	}
}

void PrintSession::beginPage( PrintContext* context )
{
	try {
		peer_->beginPage( context );
		PrintEvent event( this, context, currentPage_, PageBegunEvent );
		PageBegun.fireEvent( &event );
	}
	catch ( BasicException& ) {
		errorDuringPrinting_ = true;
	}
}

void PrintSession::endPage( PrintContext* context )
{
	try {
		peer_->endPage( context );
		PrintEvent event( this, context, currentPage_, PageDoneEvent );
		PageDone.fireEvent( &event );
	}
	catch ( BasicException& ) {
		errorDuringPrinting_ = true;
	}
}

void PrintSession::runDefaultPrintLoop() 
{
	errorDuringPrinting_ = false;

	currentPage_ = PrintSession::UnknownPage;

	int firstPage = this->getStartPage();
	int lastPage = this->getEndPage();


	PrintContext* printCtx = beginPrintingDocument();
	if ( NULL == printCtx ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Failed to create a Printer Context") );
	}

	int page = firstPage;
	while ( page <= lastPage ) {

		currentPage_ = page;

		beginPage( printCtx );

		endPage( printCtx );		
		
		page++;
	}


	endPrintingDocument();

	printCtx->free();
}



