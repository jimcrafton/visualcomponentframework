#ifndef _PRINTSESSION_H__
#define _PRINTSESSION_H__


namespace VCF {

	typedef void* PrintInfoHandle;
	
	class PrintSessionPeer;
	class PrintContext;


	/**
	\class PrintSession PrintSession.h "vcf/GraphicsKit/PrintSession.h"
	The PrintSession is the core printing class. You use it to 
	set things up with default attributes, to start printing, to
	end printing, to start a new page, and to end the page.
	@delegates	
		@del PrintSession::PageBegun
		@del PrintSession::PageDone
		@del PrintSession::PrintingBegun
		@del PrintSession::PrintingFinished
	*/
	class GRAPHICSKIT_API PrintSession : public Object {
	public:

		/**
		@delegate PageBegun	fired when the beginPage() method is called.
		@event PrintEvent
		@eventtype PrintSession::PageBegunEvent
		*/
		DELEGATE(PageBegun);

		/**
		@delegate PageDone	fired when the endPage() method is called.
		@event PrintEvent
		@eventtype PrintSession::PageDoneEvent
		*/
		DELEGATE(PageDone);

		/**
		@delegate PrintingBegun	fired when the beginPrintingDocument() method is called.
		@event PrintEvent
		@eventtype PrintSession::PrintingBegunEvent
		*/
		DELEGATE(PrintingBegun);

		/**
		@delegate PrintingFinished	fired when the endPrintingDocument() method is called.
		@event PrintEvent
		@eventtype PrintSession::PrintingFinishedEvent
		*/
		DELEGATE(PrintingFinished);

		enum {
			PageBegunEvent = 102231,
			PageDoneEvent,
			PrintingBegunEvent,
			PrintingFinishedEvent
		};

		enum {
			UnknownPage = -1
		};

		enum PrintJob {
			pjPrintAll = 0,
			pjPrintSelectedPage,
			pjPrintRange
		};

		/**
		An enumeration of different 
		standard page sizes
		*/
		enum PageSize { 
			psA4, 
			psB5,
			psLetter, 
			psLegal, 
			psExecutive, 
			psA0, 
			psA1, 
			psA2, 
			psA3, 
			psA5, 
			psA6, 
			psA7, 
			psA8, 
			psA9, 
			psB0, 
			psB1, 
			psB10, 
			psB2, 
			psB3, 
			psB4, 
			psB6, 
			psB7, 
			psB8, 
			psB9, 
			psC5E, 
			psComm10E, 
			psDLE, 
			psFolio, 
			psLedger, 
			psTabloid, 
			psCustom
		};


		/**
		The page units. 
		*/
		enum PageSizeUnits {
			/**
			This is the default page unit.
			*/
			psuPixels = 0,

			/**
			Points - where 72 points make 1 inch.
			*/
			psuPoints,

			/**
			Inches. To determine the number of pixels in an inch
			you need to get the Dots Per Inch (or DPI) from the GraphicsToolkit
			@see GraphicsToolkit::getDPI()
			*/
			psuInches,

			/**
			Millimeters. There are 25.4 millimeters in 1 inch.
			*/
			psuMillimeters,

			/**
			Twips. There are 1400 twips in 1 inch.
			*/
			psuTwips
		};


		PrintSession();
		virtual ~PrintSession();

		/**
		Returns the dots per inch (DPI) for this session. Note that the DPI 
		value for this maybe quite a bit higher than the value returned by 
		GraphicsToolkit::getDPI(NULL), which returns the screen based DPI, 
		whereas this returns the printing device DPI.
		@return double a value that represents the dots (pixels) per inch for the
		print session's printing device.
		*/
		double getDPI();

		/**
		returns the title for the print session. On some platform this may be displayed
		in the UI for displaying print progress.
		*/
		String getTitle();

		/**
		Set the title for the print session.
		*/
		void setTitle( const String& title );

		/**
		Sets the print sessions settings to default values appropriate 
		for the platform.
		*/
		void setDefaultPageSettings();

		/**
		returns the page size in pixels, adjusted for the 
		DPI of the printing device.
		*/
		Size getPageSize();

		/**
		Returns the page size in the scale of the units requested.
		@param units the units to use when returning the page size
		@return Size the width and height of the page in the units requested.
		*/
		Size getPageSizeIn( PageSizeUnits units );

		/**
		Sets the page size. Assumes the width and height are in pixels.
		*/
		void setPageSize( const Size& pageSize );

		/**
		Sets the page size using the requested units.
		*/
		void setPageSizeIn( const Size& pageSize, PageSizeUnits units );

		/**
		Sets the page size in one of the standard page size enumerations.
		*/
		void setStandardPageSize( const PageSize& pageSize );

		/**
		Sets the page number to start printing with
		*/
		void setStartPage( const ulong32& startPage );

		/**
		returns the page this session wil use to start printing
		*/
		ulong32 getStartPage();

		/**
		Sets the last page to print.
		*/
		void setEndPage( const ulong32& endPage );

		/**
		Returns the last page to print for this session.
		*/
		ulong32 getEndPage();

		/**
		Returns a vector of printable pages. The default, assuming the 
		start page was set to 1, and the end page to 10, might look like:
		\code
		element		page
			0		1
			1		2
			2		3
			3		4
			4		5
			5		6
			6		7
			7		8
			8		9
			9		10
		\endcode
		However, if the user only selected page 2, 4, 5, and 9, then it would look like:
		\code
		element		page
			0		2
			1		4
			2		5
			3		9
		\endcode
		*/
		std::vector<ulong32> getPrintablePages();

		void setPrintablePages( const std::vector<ulong32>& printablePages );

		/**
		Returns the page rect in pixel units.
		*/
		Rect getPageDrawingRect();

		/**
		Sets the page drawing rect
		*/
		void setPageDrawingRect( const Rect& drawingRect );

		/**
		returns the print info handle. This is an opaque handle to 
		a platform specific struct, and you cannot manipulate it other
		than to pass it to other printing classes.
		*/
		PrintInfoHandle getPrintInfoHandle();
		void setPrintInfoHandle( PrintInfoHandle info );

		/**
		Aborts the current printing session
		*/
		void abort();

		/**
		Starts printing the document. This will return a new instance of a 
		PrintContext for which the caller is responsible for.
		*/
		PrintContext* beginPrintingDocument();

		/**
		This ends the printing for the document. 
		*/
		void endPrintingDocument();

		/**
		This should be called for each page of the "document" that you want to print.
		@see endPage()
		*/
		void beginPage( PrintContext* context );


		/**
		This should be called for each page of the "document" once you are finished
		with that page. For example, this will print a single page:

		\code
		PrintSession session;
		
		PrintContext* ctx = session.beginPrintingDocument();
		session.beginPage( ctx );

		//your code here that draws in the ctx

		session.endPage( ctx );

		session.endPrintingDocument();

		\endcode
		*/
		void endPage( PrintContext* context );

		/**
		This is a high level function that can attempt to run a print loop through all
		the pages of the printing document, starting with the first page, and ending with
		the last page.
		\code

		PrintSession session;
		session.setStartPage( 1 );
		session.setEndPage( 10 );

		session.runDefaultPrintLoop(); //this will print 10 pages. 
		\endcode

		This will call beginPrintingDocument(), endPrintingDocument(), beginPage(), and
		endPage(), as appropriate. You can handle the actual drawing by add an event handler
		to the PageBegun delegate, which will get fired for each page. See the example in 
		vcf/examples/Printing for a more complete example of this.
		*/
		void runDefaultPrintLoop();

	protected:
		String title_;
		PrintSessionPeer* peer_;		
		bool errorDuringPrinting_;
		int currentPage_;
	};

};


#endif //_PRINTSESSION_H__



