#ifndef _GTKPRINTSESSION_H__
#define _GTKPRINTSESSION_H__



namespace VCF {

	
	class  GTKPrintSession : public Object, public PrintSessionPeer {
	public:
		GTKPrintSession();
		virtual ~GTKPrintSession();

		virtual double getDPI();

		virtual String getTitle();
		virtual void setTitle( const String& title );

		virtual void setDefaultPageSettings();

		virtual Size getPageSize();
		virtual void setPageSize( const Size& pageSize );
		virtual void setStandardPageSize( const PrintSession::PageSize& pageSize );

		virtual void setStartPage( const uint32& startPage );
		virtual uint32 getStartPage();

		virtual void setEndPage( const uint32& endPage );
		virtual uint32 getEndPage();

		virtual Rect getPageDrawingRect();
		virtual void setPageDrawingRect( const Rect& drawingRect );


		virtual PrintInfoHandle getPrintInfoHandle();
		virtual void setPrintInfoHandle( PrintInfoHandle info );

		virtual void abort();

		virtual PrintContext* beginPrintingDocument();
		virtual void endPrintingDocument();

		virtual void beginPage( PrintContext* context );
		virtual void endPage( PrintContext* context );	
		
		virtual std::vector<uint32> getPrintablePages();
		virtual void setPrintablePages( const std::vector<uint32>& printablePages );
		
	};

};



#endif //_GTKPRINTSESSION_H__

/**
$Id$
*/
