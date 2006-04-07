#ifndef _VCF_WIN32PRINTSESSION_H__
#define _VCF_WIN32PRINTSESSION_H__
//Win32PrintSession.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF {

	struct GRAPHICSKIT_API  Win32PrintInfo {
		Win32PrintInfo():docInfoPtr_(NULL),printDlgPtr_(NULL) {

			if ( System::isUnicodeEnabled() ) {
				docInfoPtr_ = malloc( sizeof(DOCINFOW) );
				memset( docInfoPtr_, 0, sizeof(DOCINFOW) );

				getDocInfoW().cbSize = sizeof(DOCINFOW);

				printDlgPtr_ = malloc( sizeof(PRINTDLGW) );
				memset( printDlgPtr_, 0, sizeof(PRINTDLGW) );
				getPrintDlgW().lStructSize = sizeof(PRINTDLGW);
			}
			else{
				docInfoPtr_ = malloc( sizeof(DOCINFOA) );
				memset( docInfoPtr_, 0, sizeof(DOCINFOA) );
				getDocInfoA().cbSize = sizeof(DOCINFOA);

				printDlgPtr_ = malloc( sizeof(PRINTDLGA) );
				memset( printDlgPtr_, 0, sizeof(PRINTDLGA) );
				getPrintDlgA().lStructSize = sizeof(PRINTDLGA);
			}
			
			//assume a start page of 1
			setStartPage(1);
		}

		Win32PrintInfo( const Win32PrintInfo& rhs ):docInfoPtr_(NULL),printDlgPtr_(NULL) {
			if ( System::isUnicodeEnabled() ) {
				docInfoPtr_ = malloc( sizeof(DOCINFOW) );
				memset( docInfoPtr_, 0, sizeof(DOCINFOW) );

				getDocInfoW().cbSize = sizeof(DOCINFOW);

				printDlgPtr_ = malloc( sizeof(PRINTDLGW) );
				memset( printDlgPtr_, 0, sizeof(PRINTDLGW) );
				getPrintDlgW().lStructSize = sizeof(PRINTDLGW);
			}
			else{
				docInfoPtr_ = malloc( sizeof(DOCINFOA) );
				memset( docInfoPtr_, 0, sizeof(DOCINFOA) );
				getDocInfoA().cbSize = sizeof(DOCINFOA);

				printDlgPtr_ = malloc( sizeof(PRINTDLGA) );
				memset( printDlgPtr_, 0, sizeof(PRINTDLGA) );
				getPrintDlgA().lStructSize = sizeof(PRINTDLGA);
			}

			*this = rhs;
		}

		~Win32PrintInfo(){
			::free(docInfoPtr_);
			::free(printDlgPtr_);
		}

		Win32PrintInfo& operator=( const Win32PrintInfo& rhs ) {
			if ( System::isUnicodeEnabled() ) {
				memcpy( docInfoPtr_, rhs.docInfoPtr_, sizeof(DOCINFOW) );
				memcpy( printDlgPtr_, rhs.printDlgPtr_, sizeof(PRINTDLGW) );
			}
			else{
				memcpy( docInfoPtr_, rhs.docInfoPtr_, sizeof(DOCINFOA) );
				memcpy( printDlgPtr_, rhs.printDlgPtr_, sizeof(PRINTDLGA) );
			}

			pageSize_ = rhs.pageSize_;
			pageDrawingRect_ = rhs.pageDrawingRect_;
			pages_ = rhs.pages_;

			return *this;
		}

		void setStartPage( const ulong32& startPage ) {
			if ( pages_.empty() ) {
				pages_.push_back( 0 );
			}
			pages_[0] = startPage;
		}

		void setEndPage( const ulong32& endPage ) {
			ulong32 start = pages_[0];
			if ( endPage - start > 1 ) {
				pages_.resize( (endPage - start)+1 );
				for ( ulong32 i=0;i<=(endPage - start);i++ ) {
					pages_[i] = start + i;
				}
			}
			else if ( pages_.size() > 1 ) {
				//get rid of the rest
				pages_.erase( pages_.begin()+1, pages_.end() );
			}
			else {
				pages_[0] = endPage;
			}
			VCF_ASSERT( pages_.back() == endPage );
		}

		ulong32 getStartPage() const {
			return pages_.front();
		}

		ulong32 getEndPage() const {
			return pages_.back();
		}


		DOCINFOW& getDocInfoW() {
			return *((DOCINFOW*)docInfoPtr_);
		}

		DOCINFOA& getDocInfoA() {
			return *((DOCINFOA*)docInfoPtr_);
		}

		PRINTDLGW& getPrintDlgW() {
			return *((PRINTDLGW*)printDlgPtr_);
		}

		PRINTDLGA& getPrintDlgA() {
			return *((PRINTDLGA*)printDlgPtr_);
		}

		
		Size pageSize_;
		Rect pageDrawingRect_;
		std::vector<ulong32> pages_;

		protected:
			void* docInfoPtr_;
			void* printDlgPtr_;
	};

	class GRAPHICSKIT_API Win32PrintSession : public Object, public PrintSessionPeer {
	public:
		Win32PrintSession();
		virtual ~Win32PrintSession();

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

		static BOOL CALLBACK AbortProc( HDC hdc, int iError );

		String title_;
		Win32PrintInfo printInfo_;
		HDC printerDC_;	
	};

};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:42  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2005/11/04 17:56:17  ddiego
*fixed bugs in some win32 code to better handle unicode - ansi functionality.
*
*Revision 1.3  2005/07/09 23:06:02  ddiego
*added missing gtk files
*
*Revision 1.2.2.1  2005/05/05 13:46:00  marcelloptr
*added standard VCF formatting
*
*/


#endif //_VCF_WIN32PRINTSESSION_H__



