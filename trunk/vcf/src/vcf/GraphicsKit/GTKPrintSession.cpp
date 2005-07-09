//GTKPrintSession.cpp

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/PrintSession.h"
#include "vcf/GraphicsKit/PrintSessionPeer.h"
#include "vcf/GraphicsKit/GTKPrintSession.h"
#include "vcf/GraphicsKit/PrintContext.h"

using namespace VCF;





GTKPrintSession::GTKPrintSession()	
{

}

GTKPrintSession::~GTKPrintSession()
{

}


String GTKPrintSession::getTitle()
{
	String result;
	return result;	
}

void GTKPrintSession::setTitle( const String& title )
{
	
}

void GTKPrintSession::setDefaultPageSettings()
{
	
}

Size GTKPrintSession::getPageSize()
{
	Size result;
	return result;
}

void GTKPrintSession::setPageSize( const Size& pageSize )
{

}

void GTKPrintSession::setStandardPageSize( const PrintSession::PageSize& pageSize )
{

}

void GTKPrintSession::setStartPage( const ulong32& startPage )
{	
	
}

ulong32 GTKPrintSession::getStartPage()
{	
	return 0;
}

void GTKPrintSession::setEndPage( const ulong32& endPage )
{
	
}

ulong32 GTKPrintSession::getEndPage()
{
	return 0;

}
Rect GTKPrintSession::getPageDrawingRect()
{	
	Rect result;
	return result;
}

void GTKPrintSession::setPageDrawingRect( const Rect& drawingRect )
{
	
}

PrintInfoHandle GTKPrintSession::getPrintInfoHandle()
{
	return (PrintInfoHandle)NULL;
}

void GTKPrintSession::setPrintInfoHandle( PrintInfoHandle info )
{
	
}

void GTKPrintSession::abort()
{
	
}

PrintContext* GTKPrintSession::beginPrintingDocument()
{

	PrintContext* result = NULL;//new PrintContext((OSHandleID)printerDC_);

	return result;
}

void GTKPrintSession::endPrintingDocument()
{
	
}

void GTKPrintSession::beginPage( PrintContext* context )
{	
	
}

double GTKPrintSession::getDPI()
{
	return 0;
}

void GTKPrintSession::endPage( PrintContext* context )
{
	
}

std::vector<ulong32> GTKPrintSession::getPrintablePages()
{
	std::vector<ulong32> result;
	return result;
}

void GTKPrintSession::setPrintablePages( const std::vector<ulong32>& printablePages )
{
	
}

