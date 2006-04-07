

#ifndef _PRINTSESSIONPEER_H__
#define _PRINTSESSIONPEER_H__

namespace VCF {

class PrintContext;

/**
\class PrintSessionPeer PrintSessionPeer.h "vcf/GraphicsKit/PrintSessionPeer.h"
*/
class GRAPHICSKIT_API PrintSessionPeer {
public: 	
	virtual ~PrintSessionPeer(){};
	
	virtual double getDPI() = 0;
	
	virtual String getTitle() = 0;
	virtual void setTitle( const String& title ) = 0;
	
	virtual void setDefaultPageSettings() = 0;
	
	virtual Size getPageSize() = 0;
	virtual void setPageSize( const Size& pageSize ) = 0;
	virtual void setStandardPageSize( const PrintSession::PageSize& pageSizeType ) = 0;
	
	virtual void setStartPage( const ulong32& startPage ) = 0;
	virtual ulong32 getStartPage() = 0;
	
	virtual void setEndPage( const ulong32& endPage ) = 0;
	virtual ulong32 getEndPage() = 0;
	
	virtual std::vector<ulong32> getPrintablePages() = 0;
	virtual void setPrintablePages( const std::vector<ulong32>& printablePages ) = 0;

	virtual Rect getPageDrawingRect() = 0;
	virtual void setPageDrawingRect( const Rect& drawingRect ) = 0;
	
	
	virtual PrintInfoHandle getPrintInfoHandle() = 0;
	virtual void setPrintInfoHandle( PrintInfoHandle info ) = 0;
	
	virtual void abort() = 0;
	
	virtual PrintContext* beginPrintingDocument() = 0;
	virtual void endPrintingDocument() = 0;
	
	virtual void beginPage( PrintContext* context ) = 0;
	virtual void endPage( PrintContext* context ) = 0;	

};




};



#endif //_PRINTSESSIONPEER_H__



