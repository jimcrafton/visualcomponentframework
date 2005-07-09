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

		virtual void setStartPage( const ulong32& startPage );
		virtual ulong32 getStartPage();

		virtual void setEndPage( const ulong32& endPage );
		virtual ulong32 getEndPage();

		virtual Rect getPageDrawingRect();
		virtual void setPageDrawingRect( const Rect& drawingRect );


		virtual PrintInfoHandle getPrintInfoHandle();
		virtual void setPrintInfoHandle( PrintInfoHandle info );

		virtual void abort();

		virtual PrintContext* beginPrintingDocument();
		virtual void endPrintingDocument();

		virtual void beginPage( PrintContext* context );
		virtual void endPage( PrintContext* context );	
		
		virtual std::vector<ulong32> getPrintablePages();
		virtual void setPrintablePages( const std::vector<ulong32>& printablePages );
		
	};

};



#endif //_GTKPRINTSESSION_H__



