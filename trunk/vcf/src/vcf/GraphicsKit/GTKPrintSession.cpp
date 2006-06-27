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
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	String result;
	return result;	
}

void GTKPrintSession::setTitle( const String& title )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKPrintSession::setDefaultPageSettings()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

Size GTKPrintSession::getPageSize()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	Size result;
	return result;
}

void GTKPrintSession::setPageSize( const Size& pageSize )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKPrintSession::setStandardPageSize( const PrintSession::PageSize& pageSize )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKPrintSession::setStartPage( const uint32& startPage )
{	
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

uint32 GTKPrintSession::getStartPage()
{	
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return 0;
}

void GTKPrintSession::setEndPage( const uint32& endPage )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

uint32 GTKPrintSession::getEndPage()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return 0;
}

Rect GTKPrintSession::getPageDrawingRect()
{	
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	Rect result;
	return result;
}

void GTKPrintSession::setPageDrawingRect( const Rect& drawingRect )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

PrintInfoHandle GTKPrintSession::getPrintInfoHandle()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return (PrintInfoHandle)NULL;
}

void GTKPrintSession::setPrintInfoHandle( PrintInfoHandle info )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKPrintSession::abort()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

PrintContext* GTKPrintSession::beginPrintingDocument()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	PrintContext* result = NULL;//new PrintContext((OSHandleID)printerDC_);
	return result;
}

void GTKPrintSession::endPrintingDocument()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");	
}

void GTKPrintSession::beginPage( PrintContext* context )
{	
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

double GTKPrintSession::getDPI()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	return 0;
}

void GTKPrintSession::endPage( PrintContext* context )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

std::vector<uint32> GTKPrintSession::getPrintablePages()
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
	std::vector<uint32> result;
	return result;
}

void GTKPrintSession::setPrintablePages( const std::vector<uint32>& printablePages )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}


/**
$Id$
*/
