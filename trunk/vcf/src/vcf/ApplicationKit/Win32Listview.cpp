//Win32Listview.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#ifdef __GNUWIN32__
#define _WIN32_IE   0x0400  //this may be a bogus thing to do !
#endif//__GNUWIN32__



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/Win32Listview.h"



#ifdef __GNUWIN32__

//add some stupid defines here since they seem to be missing from the mingw Win32 API headers
#if (_WIN32_IE >= 0x0400)
typedef struct tagNMLVGETINFOTIPA
{
    NMHDR hdr;
    DWORD dwFlags;
    LPSTR pszText;
    int cchTextMax;
    int iItem;
    int iSubItem;
    LPARAM lParam;
} NMLVGETINFOTIPA, *LPNMLVGETINFOTIPA;

typedef struct tagNMLVGETINFOTIPW
{
    NMHDR hdr;
    DWORD dwFlags;
    LPWSTR pszText;
    int cchTextMax;
    int iItem;
    int iSubItem;
    LPARAM lParam;
} NMLVGETINFOTIPW, *LPNMLVGETINFOTIPW;

// NMLVGETINFOTIPA.dwFlag values

#define LVGIT_UNFOLDED  0x0001

#define LVN_GETINFOTIPA          (LVN_FIRST-57)
#define LVN_GETINFOTIPW          (LVN_FIRST-58)

#ifdef UNICODE
    #define LVN_GETINFOTIP          LVN_GETINFOTIPW
    #define NMLVGETINFOTIP          NMLVGETINFOTIPW
    #define LPNMLVGETINFOTIP        LPNMLVGETINFOTIPW
#else
    #define LVN_GETINFOTIP          LVN_GETINFOTIPA
    #define NMLVGETINFOTIP          NMLVGETINFOTIPA
    #define LPNMLVGETINFOTIP        LPNMLVGETINFOTIPA
#endif


#endif      // _WIN32_IE >= 0x0400


#if (_WIN32_IE >= 0x0400)
#define LVN_HOTTRACK            (LVN_FIRST-21)
#endif

#if (_WIN32_IE >= 0x0300)

#define LVN_ODCACHEHINT         (LVN_FIRST-13)
#define LVN_ODFINDITEMA         (LVN_FIRST-52)
#define LVN_ODFINDITEMW         (LVN_FIRST-79)

#define LVN_ITEMACTIVATE        (LVN_FIRST-14)
#define LVN_ODSTATECHANGED      (LVN_FIRST-15)

    #ifdef UNICODE
        #define LVN_ODFINDITEM          LVN_ODFINDITEMW
    #else
        #define LVN_ODFINDITEM          LVN_ODFINDITEMA
    #endif
#endif      // _WIN32_IE >= 0x0300



#if (_WIN32_IE >= 0x0300)
#define LVN_MARQUEEBEGIN        (LVN_FIRST-56)
#endif

#if (_WIN32_IE >= 0x0300)
//==================== CUSTOM DRAW ==========================================


// custom draw return flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
/*
#define CDRF_NOTIFYITEMDRAW     0x00000020
#if (_WIN32_IE >= 0x0400)
#define CDRF_NOTIFYSUBITEMDRAW  0x00000020  // flags are the same, we can distinguish by context
#endif

#define CDRF_NOTIFYPOSTERASE    0x00000040

// drawstage flags
// values under 0x00010000 are reserved for global custom draw values.
// above that are for specific controls
#define CDDS_PREPAINT           0x00000001
#define CDDS_POSTPAINT          0x00000002
#define CDDS_PREERASE           0x00000003
#define CDDS_POSTERASE          0x00000004
// the 0x000010000 bit means it's individual item specific
#define CDDS_ITEM               0x00010000
#define CDDS_ITEMPREPAINT       (CDDS_ITEM | CDDS_PREPAINT)
#define CDDS_ITEMPOSTPAINT      (CDDS_ITEM | CDDS_POSTPAINT)
#define CDDS_ITEMPREERASE       (CDDS_ITEM | CDDS_PREERASE)
#define CDDS_ITEMPOSTERASE      (CDDS_ITEM | CDDS_POSTERASE)
#if (_WIN32_IE >= 0x0400)
#define CDDS_SUBITEM            0x00020000
#endif


// itemState flags
#define CDIS_SELECTED       0x0001
#define CDIS_GRAYED         0x0002
#define CDIS_DISABLED       0x0004
#define CDIS_CHECKED        0x0008
#define CDIS_FOCUS          0x0010
#define CDIS_DEFAULT        0x0020
#define CDIS_HOT            0x0040
#define CDIS_MARKED         0x0080
#define CDIS_INDETERMINATE  0x0100


typedef struct tagNMCUSTOMDRAWINFO
{
    NMHDR hdr;
    DWORD dwDrawStage;
    HDC hdc;
    RECT rc;
    DWORD dwItemSpec;  // this is control specific, but it's how to specify an item.  valid only with CDDS_ITEM bit set
    UINT  uItemState;
    LPARAM lItemlParam;
} NMCUSTOMDRAW, FAR * LPNMCUSTOMDRAW;



typedef struct tagNMTTCUSTOMDRAW
{
    NMCUSTOMDRAW nmcd;
    UINT uDrawFlags;
} NMTTCUSTOMDRAW, FAR * LPNMTTCUSTOMDRAW;
*/
#endif      // _WIN32_IE >= 0x0300

/*
#if (_WIN32_IE >= 0x0400)
#define ListView_SetExtendedListViewStyleEx(hwndLV, dwMask, dw)\
        (DWORD)SNDMSG((hwndLV), LVM_SETEXTENDEDLISTVIEWSTYLE, dwMask, dw)
#endif

#define LVM_GETEXTENDEDLISTVIEWSTYLE (LVM_FIRST + 55)
#define ListView_GetExtendedListViewStyle(hwndLV)\
        (DWORD)SNDMSG((hwndLV), LVM_GETEXTENDEDLISTVIEWSTYLE, 0, 0)

#define LVS_EX_GRIDLINES        0x00000001
#define LVS_EX_SUBITEMIMAGES    0x00000002
#define LVS_EX_CHECKBOXES       0x00000004
#define LVS_EX_TRACKSELECT      0x00000008
#define LVS_EX_HEADERDRAGDROP   0x00000010
#define LVS_EX_FULLROWSELECT    0x00000020 // applies to report mode only
#define LVS_EX_ONECLICKACTIVATE 0x00000040
#define LVS_EX_TWOCLICKACTIVATE 0x00000080
#if (_WIN32_IE >= 0x0400)
#define LVS_EX_FLATSB           0x00000100
#define LVS_EX_REGIONAL         0x00000200
#define LVS_EX_INFOTIP          0x00000400 // listview does InfoTips for you
#define LVS_EX_UNDERLINEHOT     0x00000800
#define LVS_EX_UNDERLINECOLD    0x00001000
#define LVS_EX_MULTIWORKAREAS   0x00002000
#endif
*/

#endif //__GNUWIN32__

using namespace VCFWin32;
using namespace VCF;


Win32Listview::Win32Listview( ListViewControl* listviewControl ):
	AbstractWin32Component( listviewControl ),
	listviewControl_( listviewControl ),
	oldHeaderWndProc_(NULL),
	largeImageListCtrl_(NULL),
	smallImageListCtrl_(NULL)
{

}

Win32Listview::~Win32Listview()
{
	if ( NULL != largeImageListCtrl_ ) {
		ImageList_Destroy( largeImageListCtrl_ );
	}

	if ( NULL != smallImageListCtrl_ ) {
		ImageList_Destroy( smallImageListCtrl_ );
	}
}


void Win32Listview::create( Control* owningControl )
{


	itemAddedHandler_ =
		new ItemEventHandler<Win32Listview>( this, &Win32Listview::onItemAdded, "Win32Listview::onItemAdded" );

	itemDeletedHandler_ =
		new ItemEventHandler<Win32Listview>( this, &Win32Listview::onItemDeleted, "Win32Listview::onItemDeleted" );

	itemChangedHandler_ =
		new ItemEventHandler<Win32Listview>( this, &Win32Listview::onItemChanged, "Win32Listview::onItemChanged" );

	itemSelectedHandler_ =
		new ItemEventHandler<Win32Listview>( this, &Win32Listview::onItemSelected, "Win32Listview::onItemSelected" );

	itemPaintedHandler_ =
		new ItemEventHandler<Win32Listview>( this, &Win32Listview::onItemPaint, "Win32Listview::onItemPaint" );

	subItemAddedHandler_ =
		new ItemEventHandler<Win32Listview>( this, &Win32Listview::onSubItemAdded, "Win32Listview::onSubItemAdded" );

	subItemDeletedHandler_ =
		new ItemEventHandler<Win32Listview>( this, &Win32Listview::onSubItemDeleted, "Win32Listview::onSubItemDeleted" );

	subItemChangedHandler_ =
		new ItemEventHandler<Win32Listview>( this, &Win32Listview::onSubItemChanged, "Win32Listview::onSubItemChanged" );


	createParams();
	backColor_.copy( owningControl->getColor() );
	/*
	if ( true != isRegistered() ){
		registerWin32Class( getClassName(), wndProc_  );
	}
	*/

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	String className = getClassName();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( exStyleMask_,
		                             WC_LISTVIEWW,
									 NULL,
									 styleMask_,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}
	else {
		hwnd_ = ::CreateWindowExA( exStyleMask_,
		                             WC_LISTVIEWA,//"SysListView32",//className.c_str(),
									 NULL,
									 styleMask_,
		                             0,
									 0,
									 1,
									 1,
									 parent,
									 NULL,
									 ::GetModuleHandle(NULL),
									 NULL );
	}
	


	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );

		subclassWindow();
		
		COLORREF backColor = RGB(backColor_.getRed() * 255.0,
									backColor_.getGreen() * 255.0,
									backColor_.getBlue() * 255.0 );
		ListView_SetBkColor( hwnd_, backColor );
	}
	else {
		//throw exception
	}

	setCreated( true );

	headerControlIsTracking_ = false;
}

void Win32Listview::updateItemSubItems( ListItem* item )
{
	if ( NULL == item ) {
		return;
	}

	Enumerator<ListItem::SubItem*>* subItems = item->getSubItems();
	int index = item->getIndex();
	int subItemIndex = 1;
	while ( true == subItems->hasMoreElements() ) {
		ListItem::SubItem* subItem = subItems->nextElement();

		

		if  (System::isUnicodeEnabled() ) {
			LVITEMW lvItem = {0};
			lvItem.iSubItem = subItemIndex;
			lvItem.pszText  = LPSTR_TEXTCALLBACKW;

			SendMessage( hwnd_, LVM_SETITEMTEXTW, index, (LPARAM)&lvItem );
		}
		else {
			LVITEMA lvItem = {0};
			lvItem.iSubItem = subItemIndex;
			lvItem.pszText  = LPSTR_TEXTCALLBACKA;
			SendMessage( hwnd_, LVM_SETITEMTEXTA, index, (LPARAM)&lvItem );
		}

		subItemIndex ++;
	}
}

void Win32Listview::onSubItemChanged( ItemEvent* event )
{
	ListItem* item = (ListItem*)event->getSource();
	updateItemSubItems( item );
}

void Win32Listview::onSubItemAdded( ItemEvent* event )
{
	onSubItemChanged( event );
}

void Win32Listview::onSubItemDeleted( ItemEvent* event )
{
	ListItem* item = (ListItem*)event->getSource();

	HWND header = ListView_GetHeader( hwnd_ );
	if ( NULL != header ) {
		int count = Header_GetItemCount( header );
		for ( int i=1;i<count;i++ ) {			
			if  (System::isUnicodeEnabled() ) {
				LVITEMW lvItem = {0};
				lvItem.iSubItem = i;
				lvItem.pszText  = L"";
				
				SendMessage( hwnd_, LVM_SETITEMTEXTW, item->getIndex(), (LPARAM)&lvItem );
			}
			else {
				LVITEMA lvItem = {0};
				lvItem.iSubItem = i;
				lvItem.pszText  = "";
				SendMessage( hwnd_, LVM_SETITEMTEXTA, item->getIndex(), (LPARAM)&lvItem );
			}

		}
	}

	onSubItemChanged( event );
}

void Win32Listview::registerHeaderWndProc()
{
	if ( NULL == oldHeaderWndProc_ ) {
		HWND headerWnd = ListView_GetHeader( hwnd_ );
		if ( NULL != headerWnd ) {
			SetWindowLong( headerWnd, GWL_USERDATA, (LONG)(LPARAM)this );
			oldHeaderWndProc_ = (WNDPROC) SetWindowLong( headerWnd, GWL_WNDPROC, (LONG)Win32Listview::Header_WndProc );
		}
	}
}

void Win32Listview::createParams()
{
	exStyleMask_ = 0;
	styleMask_ = BORDERED_VIEW | LVS_SINGLESEL | LVS_ALIGNLEFT | LVS_AUTOARRANGE | LVS_ICON | LVS_SHOWSELALWAYS;
	styleMask_ &= ~WS_BORDER;
}

LRESULT CALLBACK Win32Listview::Header_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	Win32Listview* win32ListView = (Win32Listview*) GetWindowLong( hWnd, GWL_USERDATA );

	switch ( message ) {
		case WM_ERASEBKGND : {
			result = 0;
		}
		break;


		case WM_PAINT:{
			//result = 

			PAINTSTRUCT ps;
			HDC dc = BeginPaint( hWnd, &ps );

			RECT r;
			GetClientRect( hWnd, &r );


			FillRect( dc, &r, (HBRUSH) (COLOR_3DFACE + 1) ); 
			

			if ( System::isUnicodeEnabled() ) {
				result = CallWindowProcW( win32ListView->oldHeaderWndProc_, hWnd, WM_PAINT, (WPARAM)dc, 0 );
			}
			else {
				result = CallWindowProcA( win32ListView->oldHeaderWndProc_, hWnd, WM_PAINT, (WPARAM)dc, 0 );
			}
			
			EndPaint( hWnd, &ps );
		}
		break;

		case WM_DRAWITEM : {
			StringUtils::trace( "Draw item for header\n" );
			if ( System::isUnicodeEnabled() ) {
				result = CallWindowProcW( win32ListView->oldHeaderWndProc_, hWnd, message, wParam, lParam );
			}
			else {
				result = CallWindowProcA( win32ListView->oldHeaderWndProc_, hWnd, message, wParam, lParam );
			}
			
		}
		break;

		case WM_LBUTTONDOWN : {
			win32ListView->headerControlIsTracking_ = true;
			if ( System::isUnicodeEnabled() ) {
				result = CallWindowProcW( win32ListView->oldHeaderWndProc_, hWnd, message, wParam, lParam );
			}
			else {
				result = CallWindowProcA( win32ListView->oldHeaderWndProc_, hWnd, message, wParam, lParam );
			}
			
		}
		break;

		default : {
			if ( System::isUnicodeEnabled() ) {
				result = CallWindowProcW( win32ListView->oldHeaderWndProc_, hWnd, message, wParam, lParam );
			}
			else {
				result = CallWindowProcA( win32ListView->oldHeaderWndProc_, hWnd, message, wParam, lParam );
			}
			
		}
		break;
	}

	return result;
}

void Win32Listview::postPaintItem( NMLVCUSTOMDRAW* drawItem )
{
	ListModel* model = listviewControl_->getListModel();
	ListItem* item = model->getItemFromIndex( (ulong32 )drawItem->nmcd.dwItemSpec );

	if ( NULL != item ) {
		
		//item->setSelected( isItemSelected( item ) );
		
		if ( true == item->canPaint() ) {
			RECT tmp = {0,0,0,0};
			GraphicsContext* ctx = NULL;
			
			ListView_GetItemRect( hwnd_, drawItem->nmcd.dwItemSpec,
				&tmp, LVIR_BOUNDS );


			Rect itemRect( tmp.left, tmp.top, tmp.right, tmp.bottom );
			ctx = peerControl_->getContext();

			item->paint( ctx, &itemRect );

			DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );
			if ( style & LVS_REPORT ) {
				ColumnModel* colModel = listviewControl_->getColumnModel();
				if ( NULL != colModel ) {
					ulong32 colIndex = 0;
					Enumerator<ColumnItem*>* columns = colModel->getItems();
					Enumerator<ListItem::SubItem*>* subItems = item->getSubItems();
					Rect subItemRect = itemRect;
					while ( (true == columns->hasMoreElements()) && (true == subItems->hasMoreElements()) ) {
						ColumnItem* column = columns->nextElement();
						subItemRect.right_ = subItemRect.left_ + column->getWidth();

						if ( colIndex > 0 ) {
							ListItem::SubItem* subItem = subItems->nextElement();
							subItem->paint( ctx, &subItemRect, colIndex );
						}

						subItemRect.left_ = subItemRect.right_;
						colIndex ++;
					}
				}
			}
		}
	}
}

bool Win32Listview::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;

	switch ( message ) {

		case WM_CONTEXTMENU : {
			//HACK ALERT !!!
			if ( Component::csNormal == listviewControl_->getComponentState() ) {
				PopupMenu* popup =  listviewControl_->getPopupMenu();
				if ( NULL != popup ) {
					POINT pt = {0,0};
					pt.x = LOWORD(lParam);
					pt.y = HIWORD(lParam);
					::ScreenToClient( hwnd_, &pt );
					popup->popup( &Point(pt.x, pt.y ) );
				}
			}
		}
		break;

		case WM_ERASEBKGND :{
			/*
			Color* color = listviewControl_->getColor();
			if ( (backColor_.getRed() != color->getRed()) || (backColor_.getGreen() != color->getGreen()) || (backColor_.getBlue() != color->getBlue()) ) {
				COLORREF backColor = RGB(color->getRed() * 255.0,
									color->getGreen() * 255.0,
									color->getBlue() * 255.0 );

				ListView_SetBkColor( hwnd_, backColor );

				backColor_.copy( color );
			}
			*/
			
			wndProcResult = 0;
			result= true;
		}
		break;

		case WM_NCCALCSIZE: {
			wndProcResult = handleNCCalcSize( wParam, lParam );
			result= true;
		}
		break;

		case WM_NCPAINT: {			
			wndProcResult = handleNCPaint( wParam, lParam );
			result= true;
		}
		break;
		

		case WM_DRAWITEM : {
			wndProcResult = TRUE;
			result = true;

			DRAWITEMSTRUCT* drawItem = (DRAWITEMSTRUCT*)lParam;
			if ( ODT_HEADER == drawItem->CtlType ) {

				ulong32 index = drawItem->itemID;
				ColumnItem* item = NULL;

				if ( listviewControl_->getColumnModel()->getCount() > 0 ) {
					HWND header = ListView_GetHeader( hwnd_ );
					if ( NULL != header ) {
						HDITEM headerItem;
						memset( &headerItem, 0, sizeof(HDITEM) );
						headerItem.mask = HDI_FORMAT | HDI_LPARAM;
						if ( Header_GetItem( header, index, &headerItem ) ) {
							item = (ColumnItem*)headerItem.lParam;
						}
					}
				}

				if ( NULL != item ) {
					String caption = item->getCaption();

					//::SelectObject( drawItem->hDC, ::GetStockObject(DEFAULT_GUI_FONT) );
					UINT format = 0;
					RECT textRect =  drawItem->rcItem;
					InflateRect( &textRect, -5, -2 );
					switch( item->getCaptionAlignment() ) {
						case taTextLeft: {
							format = DT_LEFT;
						}
						break;

						case taTextCenter: {
							format = DT_CENTER;
						}
						break;

						case taTextRight: {
							format = DT_RIGHT;
						}
						break;
					}

					format |= DT_SINGLELINE | DT_WORD_ELLIPSIS;

					if ( System::isUnicodeEnabled() ) {
						::DrawTextW(drawItem->hDC, caption.c_str(), caption.size(), &textRect, format);
					}
					else {
						AnsiString tmp = caption;
						::DrawTextA(drawItem->hDC, tmp.c_str(), tmp.size(), &textRect, format);
					}



					//::SelectObject( drawItem->hDC, ::GetStockObject(SYSTEM_FONT) );

					if ( true == item->canPaint() ) {
						if ( (drawItem->itemState & ODS_SELECTED) != 0 ) {

						}
						else {

						}

						GraphicsContext gc( (ulong32)drawItem->hDC );
						Rect rect( drawItem->rcItem.left, drawItem->rcItem.top, drawItem->rcItem.right, drawItem->rcItem.bottom );
						item->paint( &gc, &rect );
						gc.getPeer()->setContextID( 0 );
					}
				}
			}
		}
		break;

		case WM_PAINT:{
			//result = CallWindowProc( oldListviewWndProc_, hwnd_, message, wParam, lParam );

			PAINTSTRUCT ps;
			HDC dc = BeginPaint( hwnd_, &ps );

			RECT r;
			GetClientRect( hwnd_, &r );

			
			

			HWND header = GetDlgItem( hwnd_, 0 );
			RECT headerRect = {0};
			if ( NULL != header ) {				
				GetWindowRect( header, &headerRect );
				POINT pt;
				pt.x = headerRect.left;
				pt.y = headerRect.top;

				ScreenToClient( hwnd_, &pt );

				headerRect.left = pt.x;
				headerRect.top = pt.y;

				pt.x = headerRect.right;
				pt.y = headerRect.bottom;

				ScreenToClient( hwnd_, &pt );

				headerRect.right = pt.x;
				headerRect.bottom = pt.y;

				ExcludeClipRect( dc, headerRect.left, headerRect.top, headerRect.right, headerRect.bottom );

				r.top = headerRect.bottom;
			}


			if ( NULL == memDC_ ) {
				//create here
				HDC dc = ::GetDC(0);
				memDC_ = ::CreateCompatibleDC( dc );
				::ReleaseDC( 0,	dc );
			}
			memBMP_ = ::CreateCompatibleBitmap( dc,
					r.right - r.left,
					r.bottom - r.top );
			memDCState_ = ::SaveDC( memDC_ );

			originalMemBMP_ = (HBITMAP)::SelectObject( memDC_, memBMP_ );

			::SetViewportOrgEx( memDC_, -r.left, -r.top, NULL );

			Color* color = listviewControl_->getColor();
			
			COLORREF backColor = RGB(color->getRed() * 255.0,
									color->getGreen() * 255.0,
									color->getBlue() * 255.0 );
			HBRUSH bkBrush = CreateSolidBrush( backColor );
			FillRect( memDC_, &r, bkBrush );
			DeleteObject( bkBrush );

				

			::SetViewportOrgEx( memDC_, -r.left, -r.top, NULL );

			VCF::GraphicsContext* ctx = peerControl_->getContext();
		
			ctx->setViewableBounds( Rect(r.left, r.top,
											r.right, r.bottom ) );

			ctx->getPeer()->setContextID( (long)memDC_ );
			((ControlGraphicsContext*)ctx)->setOwningControl( NULL );				

			defaultWndProcedure( WM_PAINT, (WPARAM)memDC_, 0 );

			((ControlGraphicsContext*)ctx)->setOwningControl( peerControl_ );


			::BitBlt( dc, r.left, r.top,
					  r.right - r.left,
					  r.bottom - r.top,
					  memDC_, r.left, r.top, SRCCOPY );
			::RestoreDC ( memDC_, memDCState_ );
			
			::DeleteObject( memBMP_ );


			

			EndPaint( hwnd_, &ps );

			wndProcResult = 1;
			result = true;
		}
		break;

		case WM_CREATE:{
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case LVN_BEGINDRAG:{
			NMLISTVIEW* lvNotificationHdr = (LPNMLISTVIEW)lParam;

		}
		break;

		case LVN_BEGINLABELEDIT:{
			
		}
		break;

		case LVN_BEGINRDRAG:{
			
		}
		break;

		case NM_DBLCLK : {
			StringUtils::trace( "NM_DBLCLK\n" );
			
		}
		break;

		case LVN_COLUMNCLICK:{

			NMLISTVIEW* nmlistView = (NMLISTVIEW*)lParam;
			ColumnItem* item  = listviewControl_->getColumnModel()->getItemFromIndex( (ulong32)nmlistView->iSubItem );
			if ( NULL != item ) {
				POINT pt = {0,0};
				::GetCursorPos( &pt );
				::ScreenToClient( hwnd_, &pt );

				MouseEvent event( item, ListViewControl::COLUMN_MOUSE_EVENT_CLICK,
									Win32Utils::translateButtonMask( MK_LBUTTON ),
									Win32Utils::translateKeyMask( 0 ),
									&Point(pt.x, pt.y) );

				listviewControl_->handleEvent( &event );
			}
			result = true;
		}
		break;

		case HDN_BEGINTRACK : {
			headerControlIsTracking_ = true;
			
			wndProcResult = FALSE;
			result = true;
		}
		break;

		case HDN_ITEMCHANGINGW:  {
			if ( true == headerControlIsTracking_ ) {
				NMHEADERW* nmHeader = (NMHEADERW*)lParam;
				
				if ( nmHeader->pitem->mask & HDI_WIDTH ) {
					ColumnItem* item  = listviewControl_->getColumnModel()->getItemFromIndex( (ulong32)nmHeader->iItem );
					if ( NULL != item ) {
						item->setWidth( nmHeader->pitem->cxy );
						InvalidateRect( hwnd_, NULL, TRUE );
					}
				}
			}				
			
			wndProcResult = FALSE;
			result = true;
		}
		break;

		case HDN_ITEMCHANGINGA: {
			if ( true == headerControlIsTracking_ ) {				
				NMHEADERA* nmHeader = (NMHEADERA*)lParam;
				
				if ( nmHeader->pitem->mask & HDI_WIDTH ) {
					ColumnItem* item  = listviewControl_->getColumnModel()->getItemFromIndex( (ulong32)nmHeader->iItem );
					if ( NULL != item ) {
						item->setWidth( nmHeader->pitem->cxy );
						InvalidateRect( hwnd_, NULL, TRUE );
					}
				}
			}
			
			wndProcResult = FALSE;
			result = true;
		}
		break;

		case HDN_ENDTRACKW : {

			NMHEADERW* nmHeader = (NMHEADERW*)lParam;
			headerControlIsTracking_ = false;
			
			if ( (nmHeader->pitem->mask & HDI_WIDTH) && (listviewControl_->getColumnModel()->getCount() > 0) ) {
				ColumnItem* item  = listviewControl_->getColumnModel()->getItemFromIndex( (ulong32)nmHeader->iItem );
				if ( NULL != item ) {
					item->setWidth( nmHeader->pitem->cxy );
					InvalidateRect( hwnd_, NULL, TRUE );
				}
			}
			
			
			
			wndProcResult = FALSE;
			result = true;
		}
		break;
		
		case HDN_ENDTRACKA : {
			
			NMHEADERA* nmHeader = (NMHEADERA*)lParam;
			headerControlIsTracking_ = false;
			
			if ( (nmHeader->pitem->mask & HDI_WIDTH) && (listviewControl_->getColumnModel()->getCount() > 0) ) {
				ColumnItem* item  = listviewControl_->getColumnModel()->getItemFromIndex( (ulong32)nmHeader->iItem );
				if ( NULL != item ) {
					item->setWidth( nmHeader->pitem->cxy );
					InvalidateRect( hwnd_, NULL, TRUE );
				}
			}

			
			wndProcResult = FALSE;
			result = true;
		}
		break;

		case LVN_DELETEALLITEMS:{

		}
		break;

		case LVN_DELETEITEM:{

		}
		break;

		case LVN_ENDLABELEDITW:{
			NMLVDISPINFOW* displayInfo = (NMLVDISPINFOW*)lParam;
			
			wndProcResult = (NULL != displayInfo->item.pszText) ? TRUE : FALSE;;
			result = true;

			if ( NULL != displayInfo->item.pszText ){
				String newCaption = displayInfo->item.pszText;
				ListItem* item = (ListItem*)displayInfo->item.lParam;
				if ( NULL != item ){
					item->setCaption( newCaption );
					item->setSelected( true );
				}
			}
		}
		break;

		case LVN_ENDLABELEDITA:{
			NMLVDISPINFOA* displayInfo = (NMLVDISPINFOA*)lParam;
			
			wndProcResult = (NULL != displayInfo->item.pszText) ? TRUE : FALSE;;
			result = true;

			if ( NULL != displayInfo->item.pszText ){
				String newCaption = displayInfo->item.pszText;
				ListItem* item = (ListItem*)displayInfo->item.lParam;
				if ( NULL != item ){
					item->setCaption( newCaption );
					item->setSelected( true );
				}
			}
		}
		break;

		case LVN_GETDISPINFOW:{
			NMLVDISPINFOW* displayInfo = (NMLVDISPINFOW*)lParam;
			if ( displayInfo->hdr.hwndFrom == hwnd_ ) {

				if ( displayInfo->item.iSubItem > 0 ) {
					ListItem* item = (ListItem*)displayInfo->item.lParam;
					if ( NULL != item ) {
						if ( (displayInfo->item.iSubItem <= item->getSubItemCount()) && ( displayInfo->item.mask & LVIF_TEXT) ) {
							ListItem::SubItem* subItem = item->getSubItem( displayInfo->item.iSubItem - 1 );
							String caption = subItem->getCaption();
							int size = min( caption.size(), displayInfo->item.cchTextMax );
							caption.copy( displayInfo->item.pszText, size );
							if ( size < displayInfo->item.cchTextMax ) {
								displayInfo->item.pszText[size] = '\0';
							}
						}
					}
				}
			}
		}
		break;

		case LVN_GETDISPINFOA:{
			NMLVDISPINFOA* displayInfo = (NMLVDISPINFOA*)lParam;
			if ( displayInfo->hdr.hwndFrom == hwnd_ ) {

				if ( displayInfo->item.iSubItem > 0 ) {
					ListItem* item = (ListItem*)displayInfo->item.lParam;
					if ( NULL != item ) {
						if ( (displayInfo->item.iSubItem <= item->getSubItemCount()) && ( displayInfo->item.mask & LVIF_TEXT) ) {
							ListItem::SubItem* subItem = item->getSubItem( displayInfo->item.iSubItem - 1 );
							AnsiString caption = subItem->getCaption();
							int size = min( caption.size(), displayInfo->item.cchTextMax );
							caption.copy( displayInfo->item.pszText, size );
							if ( size < displayInfo->item.cchTextMax ) {
								displayInfo->item.pszText[size] = '\0';
							}
						}
					}
				}
			}
		}
		break;

		case LVN_GETINFOTIPW:{

		}
		break;

		case LVN_GETINFOTIPA:{

		}
		break;

		case LVN_HOTTRACK:{

		}
		break;

		case LVN_ITEMACTIVATE:{

		}
		break;

		case LVN_MARQUEEBEGIN:{

		}
		break;

		case LVN_ODCACHEHINT:{

		}
		break;

		case LVN_ODFINDITEM:{

		}
		break;

		case LVN_ODSTATECHANGED:{

		}
		break;

		case LVN_INSERTITEM:{

		}
		break;


		case LVN_ITEMCHANGED:{
			NMLISTVIEW* lvNotificationHdr = (LPNMLISTVIEW)lParam;

			if ( -1 != lvNotificationHdr->iItem ){

				ListItem* item = (ListItem*)lvNotificationHdr->lParam;
				if ( NULL != item ){
					if ( (lvNotificationHdr->uChanged & LVIF_STATE) != 0 ) {
						if ( (lvNotificationHdr->uNewState & LVIS_SELECTED) != 0 ){
							item->setSelected( true );

							POINT tmpPt = {0,0};
							GetCursorPos( &tmpPt );
							::ScreenToClient( hwnd_, &tmpPt );
							ItemEvent event( listviewControl_, ITEM_EVENT_SELECTED );
							Point pt( tmpPt.x, tmpPt.y );
							event.setPoint( &pt );

							listviewControl_->ItemSelectionChanged.fireEvent( &event );
						}
						else {
							item->setSelected( false );
						}
					}
				}
			}

		}
		break;

		case LVN_ITEMCHANGING:{

		}
		break;

		case LVN_KEYDOWN:{

		}
		break;



		case LVN_SETDISPINFO:{

		}
		break;

		case NM_CUSTOMDRAW:{

			NMLVCUSTOMDRAW* listViewCustomDraw = (NMLVCUSTOMDRAW*)lParam;
			ListModel* model = listviewControl_->getListModel();
			wndProcResult = CDRF_DODEFAULT;
			result = true;

			
			if ( NULL != model ) {
				/**
				*CDDS_PREPAINT is at the beginning of the paint cycle. You
				*implement custom draw by returning the proper value. In this
				*case, we're requesting item-specific notifications.
				*/
				switch ( listViewCustomDraw->nmcd.dwDrawStage ) {
					case CDDS_PREPAINT : {
						// Request prepaint notifications for each item.
						wndProcResult = CDRF_NOTIFYITEMDRAW;
					}
					break;

					case CDDS_ITEMPREPAINT : {
						// Request prepaint notifications for each item.
						
						wndProcResult = CDRF_NOTIFYPOSTPAINT;
					}
					break;

					case CDDS_ITEMPOSTPAINT : {
						// Request prepaint notifications for each item.
						postPaintItem( listViewCustomDraw );
						
						wndProcResult = CDRF_SKIPDEFAULT;
					}
					break;

					default : {						
						wndProcResult = CDRF_DODEFAULT;
					}
					break;
				}
			}
		}
		break;

		default: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;
	}
	return result;
}

void Win32Listview::addItem( ListItem * item )
{
	//LVM_INSERTITEM
	if ( NULL != item ){

		int index = ListView_GetItemCount(hwnd_);

		insertItem( index, item );
	}
}

void Win32Listview::insertItem( const unsigned long& index, ListItem * item )
{
	if ( NULL != item ){
		int itemIndex = index;

		if ( System::isUnicodeEnabled() ) {
			LVITEMW lvItem;
			memset( &lvItem, 0, sizeof(lvItem) );
			lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
			lvItem.iItem = itemIndex;
			String caption = item->getCaption();

			VCFChar* tmp = new VCFChar[ caption.size()+1 ];
			memset( tmp, 0, sizeof(VCFChar)*(caption.size()+1) );
			caption.copy( tmp, caption.size() );


			lvItem.pszText = tmp;
			lvItem.cchTextMax = caption.size();
			lvItem.lParam = (LPARAM)item;
			lvItem.iImage = item->getImageIndex();
			itemIndex = SendMessage( hwnd_, LVM_INSERTITEMW, 0, (LPARAM) &lvItem );

		}
		else {
			LVITEMA lvItem;
			memset( &lvItem, 0, sizeof(lvItem) );
			lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_IMAGE;
			lvItem.iItem = itemIndex;
			AnsiString caption = item->getCaption();

			char* tmp = new char[ caption.size()+1 ];
			memset( tmp, 0, sizeof(char)*(caption.size()+1) );
			caption.copy( tmp, caption.size() );


			lvItem.pszText = tmp;
			lvItem.cchTextMax = caption.size();
			lvItem.lParam = (LPARAM)item;
			lvItem.iImage = item->getImageIndex();
			itemIndex = SendMessage( hwnd_, LVM_INSERTITEMA, 0, (LPARAM) &lvItem );
		}

		if ( itemIndex != -1 ) {
			item->setIndex( itemIndex );
			updateItemSubItems( item );
		}
		else{
			//throw exception
		}

		item->addItemAddedHandler( itemAddedHandler_ );
		item->addItemDeletedHandler( itemDeletedHandler_ );
		item->addItemChangedHandler( itemChangedHandler_ );
		item->addItemSelectedHandler( itemSelectedHandler_ );
		item->addItemPaintHandler( itemPaintedHandler_ );

		item->addSubItemAddedHandler( subItemAddedHandler_ );
		item->addSubItemDeletedHandler( subItemDeletedHandler_ );
		item->addSubItemChangedHandler( subItemChangedHandler_ );
	}
}

void Win32Listview::clear()
{
	ListView_DeleteAllItems( hwnd_ );
}

void Win32Listview::deleteItem( ListItem* item )
{
	if ( NULL != item ){

		if ( System::isUnicodeEnabled() ) {
			LVFINDINFOW findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOW) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			int index = SendMessage( hwnd_, LVM_FINDITEMW, -1, (LPARAM)&findInfo );

			if ( index > -1 ) {
				ListView_DeleteItem( hwnd_, index );
			}
		}
		else {
			LVFINDINFOA findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOA) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			int index = SendMessage( hwnd_, LVM_FINDITEMA, -1, (LPARAM)&findInfo );
			if ( index > -1 ) {
				ListView_DeleteItem( hwnd_, index );
			}
		}

		
	}
}

bool Win32Listview::ensureVisible(ListItem * item, bool partialOK )
{
	//LVM_ENSUREVISIBLE
	bool result = false;
	if ( NULL != item ){

		if ( System::isUnicodeEnabled() ) {
			LVFINDINFOW findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOW) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			
			int index = SendMessage( hwnd_, LVM_FINDITEMW, -1, (LPARAM)&findInfo );
			if ( index > -1 ) {
				result = ( 0 !=
					ListView_EnsureVisible( hwnd_, index, partialOK ) );
			}
			
		}
		else {
			LVFINDINFOA findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOA) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			int index = SendMessage( hwnd_, LVM_FINDITEMA, -1, (LPARAM)&findInfo );
			if ( index > -1 ) {
				result = ( 0 !=
					ListView_EnsureVisible( hwnd_, index, partialOK ) );
			}
		}

		
	}
	return result;
}

void Win32Listview::setFocusedItem(ListItem * item)
{
	if ( NULL != item ){

		if ( System::isUnicodeEnabled() ) {
			LVFINDINFOW findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOW) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			int index = SendMessage( hwnd_, LVM_FINDITEMW, -1, (LPARAM)&findInfo );

			if ( index > -1 ) {
				LV_ITEMW lvItem = {0};
				lvItem.stateMask = LVIS_FOCUSED;
				lvItem.state = LVIS_FOCUSED;


				SendMessage( hwnd_, LVM_SETITEMSTATE, index, (LPARAM)&lvItem );
			}
		}
		else {
			LVFINDINFOA findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOA) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			int index = SendMessage( hwnd_, LVM_FINDITEMA, -1, (LPARAM)&findInfo );

			if ( index > -1 ) {
				LV_ITEMA lvItem = {0};
				lvItem.stateMask = LVIS_FOCUSED;
				lvItem.state = LVIS_FOCUSED;


				SendMessage( hwnd_, LVM_SETITEMSTATE, index, (LPARAM)&lvItem );
			}
		}
	}
}

void Win32Listview::selectItem(ListItem * item)
{
	if ( NULL != item ){

		if ( System::isUnicodeEnabled() ) {
			LVFINDINFOW findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOW) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			int index = SendMessage( hwnd_, LVM_FINDITEMW, -1, (LPARAM)&findInfo );

			if ( index > -1 ) {
				LV_ITEMW lvItem = {0};
				lvItem.stateMask = LVIS_SELECTED;
				lvItem.state = LVIS_SELECTED;


				SendMessage( hwnd_, LVM_SETITEMSTATE, index, (LPARAM)&lvItem );
			}
		}
		else {
			LVFINDINFOA findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOA) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			int index = SendMessage( hwnd_, LVM_FINDITEMA, -1, (LPARAM)&findInfo );

			if ( index > -1 ) {
				LV_ITEMA lvItem = {0};
				lvItem.stateMask = LVIS_SELECTED;
				lvItem.state = LVIS_SELECTED;


				SendMessage( hwnd_, LVM_SETITEMSTATE, index, (LPARAM)&lvItem );
			}
		}
	}
}

Rect* Win32Listview::getItemRect( ListItem* item )
{
	RECT rect = {0,0,0,0};
	if ( NULL != item ){
		LVFINDINFO findInfo;
		memset( &findInfo, 0, sizeof(LVFINDINFO) );
		findInfo.flags = LVFI_PARAM;
		findInfo.lParam = (LPARAM)item;

		int index = ListView_FindItem( hwnd_, -1, &findInfo );
		if ( index > -1 ) {
			ListView_GetItemRect( hwnd_, index, &rect, LVIR_BOUNDS );
			itemRect_.setRect( rect.left, rect.top, rect.right, rect.bottom );
		}
	}
	else {
		return NULL;
	}
	return &itemRect_;
}

bool Win32Listview::isItemSelected(ListItem* item)
{
	bool result = false;
	if ( NULL != item ){
		if ( System::isUnicodeEnabled() ) {
			LVFINDINFOW findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOW) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			int index = SendMessage( hwnd_, LVM_FINDITEMW, -1, (LPARAM)&findInfo );

			if ( index > -1 ) {
				result = ( LVIS_SELECTED == 
					SendMessage( hwnd_, LVM_GETITEMSTATE, index, LVIS_SELECTED ) );
			}
		}
		else {
			LVFINDINFOA findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOA) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;
			
			int index = SendMessage( hwnd_, LVM_FINDITEMA, -1, (LPARAM)&findInfo );

			if ( index > -1 ) {
				result = ( LVIS_SELECTED == 
					SendMessage( hwnd_, LVM_GETITEMSTATE, index, LVIS_SELECTED ) );
			}
		}
	}
	return result;
}

ListItem* Win32Listview::isPtOverItem( Point* point )
{
	ListItem* result = NULL;

	LVHITTESTINFO hitTestInfo;
	memset( &hitTestInfo, 0, sizeof(LVHITTESTINFO) );
	hitTestInfo.pt.x = (long)point->x_;
	hitTestInfo.pt.y = (long)point->y_;

	int index = ListView_HitTest( hwnd_, &hitTestInfo );
	if ( index > -1 ) {
		ListModel* model = listviewControl_->getListModel();
		if ( NULL != model ){
			if ( System::isUnicodeEnabled() ) {
				LVITEMW lvItem;
				memset( &lvItem, 0, sizeof(LVITEMW) );
				
				lvItem.mask = LVIF_PARAM ;
				lvItem.iItem = index;
				if ( SendMessage( hwnd_, LVM_GETITEMW, 0, (LPARAM)&lvItem ) ) {
					result = (ListItem*)lvItem.lParam;
				}
			}
			else {
				LVITEMA lvItem;
				memset( &lvItem, 0, sizeof(LVITEMA) );
				
				lvItem.mask = LVIF_PARAM ;
				lvItem.iItem = index;
				if ( SendMessage( hwnd_, LVM_GETITEMA, 0, (LPARAM)&lvItem ) ) {				
					result = (ListItem*)lvItem.lParam;
				}
			}
			
		}
	}
	return result;
}

ListItem* Win32Listview::getFocusedItem()
{
	ListItem* result = NULL;

	int index = ListView_GetSelectionMark( hwnd_ );
	if ( index > -1 ){
		int i = 0;
		int count = ListView_GetSelectedCount( hwnd_ );
		while ( i < count ){
			if ( LVIS_FOCUSED  == ListView_GetItemState( hwnd_, index, LVIS_FOCUSED  ) ){

				if ( System::isUnicodeEnabled() ) {
					LVITEMW lvItem;
					memset( &lvItem, 0, sizeof(LVITEMW) );
					
					lvItem.mask = LVIF_PARAM ;
					lvItem.iItem = index;
					if ( SendMessage( hwnd_, LVM_GETITEMW, 0, (LPARAM)&lvItem ) ) {
						result = (ListItem*)lvItem.lParam;
					}
				}
				else {
					LVITEMA lvItem;
					memset( &lvItem, 0, sizeof(LVITEMA) );
					
					lvItem.mask = LVIF_PARAM ;
					lvItem.iItem = index;
					if ( SendMessage( hwnd_, LVM_GETITEMA, 0, (LPARAM)&lvItem ) ) {				
						result = (ListItem*)lvItem.lParam;

					}
				}

				if ( NULL != result ) {
					break;
				}
				
			}
			index++;
			i++;
		}
	}
	return result;
}

ListItem* Win32Listview::getSelectedItem()
{
	ListItem* result = NULL;

	int index = ListView_GetNextItem(hwnd_, -1, LVNI_SELECTED);
	if ( index >= 0 ) {
		if ( System::isUnicodeEnabled() ) {
			LVITEMW lvItem;
			memset( &lvItem, 0, sizeof(LVITEMW) );
			
			lvItem.mask = LVIF_PARAM ;
			lvItem.iItem = index;
			if ( SendMessage( hwnd_, LVM_GETITEMW, 0, (LPARAM)&lvItem ) ) {
				result = (ListItem*)lvItem.lParam;
			}
		}
		else {
			LVITEMA lvItem;
			memset( &lvItem, 0, sizeof(LVITEMA) );
			
			lvItem.mask = LVIF_PARAM ;
			lvItem.iItem = index;
			if ( SendMessage( hwnd_, LVM_GETITEMA, 0, (LPARAM)&lvItem ) ) {				
				result = (ListItem*)lvItem.lParam;				
			}
		}

	}
	return result;
}

Enumerator<ListItem*>* Win32Listview::getSelectedItems()
{
	//int index = ListView_GetSelectionMark( hwnd_ );

	ListItem* item = NULL;
	selectedItems_.clear();

	int index = ListView_GetNextItem(hwnd_, -1, LVNI_SELECTED);
	if ( index >= 0 ) {

		if ( System::isUnicodeEnabled() ) {
			LVITEMW lvItem;
			memset( &lvItem, 0, sizeof(LVITEMW) );
			
			lvItem.mask = LVIF_PARAM ;
			lvItem.iItem = index;
			if ( SendMessage( hwnd_, LVM_GETITEMW, 0, (LPARAM)&lvItem ) ) {
				item = (ListItem*)lvItem.lParam;
			}
		}
		else {
			LVITEMA lvItem;
			memset( &lvItem, 0, sizeof(LVITEMA) );
			
			lvItem.mask = LVIF_PARAM ;
			lvItem.iItem = index;
			if ( SendMessage( hwnd_, LVM_GETITEMA, 0, (LPARAM)&lvItem ) ) {				
				item = (ListItem*)lvItem.lParam;				
			}
		}

		selectedItems_.push_back( item );

		index = ListView_GetNextItem(hwnd_, index, LVNI_SELECTED);

		while ( index >= 0 ) {
			if ( System::isUnicodeEnabled() ) {
				LVITEMW lvItem;
				memset( &lvItem, 0, sizeof(LVITEMW) );
				
				lvItem.mask = LVIF_PARAM ;
				lvItem.iItem = index;
				if ( SendMessage( hwnd_, LVM_GETITEMW, 0, (LPARAM)&lvItem ) ) {
					item = (ListItem*)lvItem.lParam;
				}
			}
			else {
				LVITEMA lvItem;
				memset( &lvItem, 0, sizeof(LVITEMA) );
				
				lvItem.mask = LVIF_PARAM ;
				lvItem.iItem = index;
				if ( SendMessage( hwnd_, LVM_GETITEMA, 0, (LPARAM)&lvItem ) ) {				
					item = (ListItem*)lvItem.lParam;				
				}
			}

			selectedItems_.push_back( item );

			index = ListView_GetNextItem(hwnd_, index, LVNI_SELECTED);
		}
	}
	else {
		return NULL;
	}

	enumContainer_.initContainer( selectedItems_ );
	return enumContainer_.getEnumerator();
}

void Win32Listview::rangeSelect( Rect* selectionRect )
{

}

void Win32Listview::addHeaderColumn( const String& columnName, const double& width )
{
	HWND header = ListView_GetHeader( hwnd_ );
	int index = 0;
	if ( NULL != header ) {
		index = Header_GetItemCount( header );
	}

	insertHeaderColumn( index, columnName, width );
}

void Win32Listview::insertHeaderColumn( const unsigned long& index, const String& columnName, const double& width )
{
	if ( System::isUnicodeEnabled() ) {
		LVCOLUMNW column;
		memset( &column, 0, sizeof(column) );
		column.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH;
		column.cx = (long)width;
		column.fmt = LVCFMT_LEFT;

		VCFChar* tmp = new VCFChar[columnName.size()+1];
		memset( tmp, 0, sizeof(VCFChar)*(columnName.size()+1) );

		columnName.copy( tmp, columnName.size() );

		column.pszText = tmp;
		column.cchTextMax = columnName.size();

		if ( SendMessage( hwnd_, LVM_INSERTCOLUMNW, (WPARAM)index, (LPARAM)&column ) >= 0 ) {
			HWND header = ListView_GetHeader( hwnd_ );

			if ( NULL != header ) {
				HDITEMW headerItem;
				memset( &headerItem, 0, sizeof(headerItem) );
				headerItem.mask = HDI_FORMAT | HDI_LPARAM;
				Header_GetItem( header, index, &headerItem );
				headerItem.fmt |= HDF_OWNERDRAW;
				ColumnItem* item = listviewControl_->getColumnModel()->getItemFromIndex( index );

				headerItem.lParam = (LPARAM)item;

				int err = SendMessage( header, HDM_SETITEMW, (WPARAM)index, (LPARAM)&headerItem );
			}


			registerHeaderWndProc();
		}

		delete tmp;

	}
	else {
		LVCOLUMNA column;

		AnsiString tmpColName = columnName;

		memset( &column, 0, sizeof(column) );
		column.mask = LVCF_TEXT | LVCF_FMT | LVCF_WIDTH;
		column.cx = (long)width;
		column.fmt = LVCFMT_LEFT;

		char* tmp = new char[tmpColName.size()+1];
		memset( tmp, 0, sizeof(char)*(tmpColName.size()+1) );

		tmpColName.copy( tmp, tmpColName.size() );

		column.pszText = tmp;
		column.cchTextMax = tmpColName.size();

		if ( SendMessage( hwnd_, LVM_INSERTCOLUMNA, (WPARAM)index, (LPARAM)&column ) >= 0 ) {
			HWND header = ListView_GetHeader( hwnd_ );

			if ( NULL != header ) {
				HDITEMA headerItem;
				memset( &headerItem, 0, sizeof(headerItem) );
				headerItem.mask = HDI_FORMAT | HDI_LPARAM;
				Header_GetItem( header, index, &headerItem );
				headerItem.fmt |= HDF_OWNERDRAW;
				ColumnItem* item = listviewControl_->getColumnModel()->getItemFromIndex( index );

				headerItem.lParam = (LPARAM)item;

				int err = SendMessage( header, HDM_SETITEMA, (WPARAM)index, (LPARAM)&headerItem );
			}


			registerHeaderWndProc();
		}

		delete tmp;
	}

}

void Win32Listview::deleteHeaderColumn( const unsigned long& index )
{
	int err = ListView_DeleteColumn( hwnd_, index );

}

IconStyleType Win32Listview::getIconStyle()
{
	DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );
	return translateStyleToIconStyle( style );
}

void Win32Listview::setIconStyle( const IconStyleType& iconStyle )
{
	DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );

	style &= ~LVS_ICON;
	style &= ~LVS_SMALLICON;
	style &= ~LVS_LIST;
	style &= ~LVS_REPORT;

	style |= translateIconStyleToStyleBit( iconStyle );

	::SetWindowLong( hwnd_, GWL_STYLE, style );
	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
}

bool Win32Listview::getAllowsMultiSelect()
{
	DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );
	return ((style & LVS_SINGLESEL) == 0);
}

void Win32Listview::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );
	if ( true == allowsMultiSelect ){
		style &= ~LVS_SINGLESEL;
	}
	else {
		style |= LVS_SINGLESEL;
	}
	::SetWindowLong( hwnd_, GWL_STYLE, style );
}

IconAlignType Win32Listview::getIconAlignment()
{
	DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );
	return translateStyleToIconAlignment( style );
}

void Win32Listview::setIconAlignment( const IconAlignType& iconAlignType )
{
	DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );
	style |= translateIconAlignmentToStyleBit( iconAlignType );
	::SetWindowLong( hwnd_, GWL_STYLE, style );
}

bool Win32Listview::getAllowLabelEditing()
{
	DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );
	return ((style & LVS_EDITLABELS) == 0);
}

void Win32Listview::setAllowLabelEditing( const bool& allowLabelEditing )
{
	DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );
	if ( true == allowLabelEditing ){
		style |= LVS_EDITLABELS;
	}
	else {
		style &= ~LVS_EDITLABELS;
	}
	::SetWindowLong( hwnd_, GWL_STYLE, style );
}

IconStyleType Win32Listview::translateStyleToIconStyle( const DWORD& wsStyle )
{
	IconStyleType result;
	if ( (wsStyle & LVS_ICON) != 0 ){
		result = isLargeIcon;
	}
	else if ( (wsStyle & LVS_LIST) != 0 ){
		result = isList;
	}
	else if ( (wsStyle & LVS_SMALLICON) != 0 ){
		result = isSmallIcon;
	}
	else if ( (wsStyle & LVS_REPORT) != 0 ){
		result = isDetails;
	}
	return result;
}

DWORD Win32Listview::translateIconStyleToStyleBit( const IconStyleType& iconStyle )
{
	DWORD result = 0;
	switch ( iconStyle ){
		case isLargeIcon:{
			result = LVS_ICON;
		}
		break;

		case isSmallIcon:{
			result = LVS_SMALLICON;
		}
		break;

		case isList:{
			result = LVS_LIST;
		}
		break;

		case isDetails:{
			result = LVS_REPORT;
		}
		break;
	}
	return result;
}

IconAlignType Win32Listview::translateStyleToIconAlignment( const DWORD& wsStyle )
{
	IconAlignType result;
	if ( (wsStyle & LVS_ALIGNTOP) != 0 ){
		result = iaTop;
	}
	else if ( (wsStyle & LVS_ALIGNLEFT) != 0 ){
		result = iaLeft;
	}
	else if ( (wsStyle & LVS_AUTOARRANGE) != 0 ){
		result = iaAutoArrange;
	}
	else {
		result = iaNone;
	}
	return result;
}

DWORD Win32Listview::translateIconAlignmentToStyleBit( const IconAlignType& iconAlignment )
{
	DWORD result = 0;
	switch ( iconAlignment ){
		case iaTop:{
			result = LVS_ALIGNTOP;
		}
		break;

		case iaLeft:{
			result = LVS_ALIGNLEFT;
		}
		break;

		case iaAutoArrange:{
			result = LVS_AUTOARRANGE;
		}
		break;
		case iaNone:{
			result = 0;
		}
		break;
	}
	return result;
}

void Win32Listview::onItemPaint( ItemEvent* event )
{

}

void Win32Listview::onItemChanged( ItemEvent* event )
{
	/*switch ( event->getType() ){
			case ITEM_EVENT_TEXT_CHANGED:{
				Object* source = event->getSource();
				if ( NULL != source ){
					ListItem* item = dynamic_cast<ListItem*>(source);
					if ( NULL != item ){
						LVITEM lvItem = {0};
						lvItem.mask = LVIF_TEXT;
						String caption = item->getCaption();
						lvItem.cchTextMax = caption.size();
						lvItem.iItem = item->getIndex();
						char* tmp = new char[lvItem.cchTextMax];
						memset( tmp, 0, lvItem.cchTextMax );
						caption.copy( tmp, lvItem.cchTextMax );
						lvItem.pszText = tmp;
						ListView_SetItem( hwnd_, &lvItem );
						delete [] tmp;
					}
				}
			}
			break;

			default: {

			}
			break;
		}
	*/

	Object* source = event->getSource();
	if ( NULL != source ){
		ListItem* item = dynamic_cast<ListItem*>(source);
		if ( NULL != item ){

			if ( System::isUnicodeEnabled() ) {
				LVITEMW lvItem;
				memset( &lvItem, 0, sizeof(lvItem) );
				lvItem.mask = LVIF_TEXT | LVIF_IMAGE ;
				lvItem.iImage = item->getImageIndex();
				String caption = item->getCaption();
				lvItem.cchTextMax = caption.size()+1;
				lvItem.iItem = item->getIndex();

				VCFChar* tmp = new VCFChar[lvItem.cchTextMax];
				memset( tmp, 0, lvItem.cchTextMax * sizeof(VCFChar) );

				caption.copy( tmp, lvItem.cchTextMax-1 );
				lvItem.pszText = tmp;
				SendMessage( hwnd_, LVM_SETITEMW, 0, (LPARAM)&lvItem );

				delete [] tmp;
			}
			else {
				LVITEMA lvItem;
				memset( &lvItem, 0, sizeof(lvItem) );
				lvItem.mask = LVIF_TEXT | LVIF_IMAGE ;
				lvItem.iImage = item->getImageIndex();

				AnsiString caption = item->getCaption();

				lvItem.cchTextMax = caption.size()+1;
				lvItem.iItem = item->getIndex();

				char* tmp = new char[lvItem.cchTextMax];
				memset( tmp, 0, lvItem.cchTextMax );
				caption.copy( tmp, lvItem.cchTextMax-1 );
				lvItem.pszText = tmp;
				SendMessage( hwnd_, LVM_SETITEMA, 0, (LPARAM)&lvItem );
				delete [] tmp;
			}


		}
	}
}

void Win32Listview::onItemSelected( ItemEvent* event )
{
/*
	Item* item = (Item*)event->getSource();
	if ( true == item->isSelected() ) {
		ListView_SetItemState( hwnd_, item->getIndex(),
			                   LVIS_SELECTED, LVIS_SELECTED );
	}
	else {
		ListView_SetItemState( hwnd_, item->getIndex(), 0, LVIS_SELECTED );
	}
*/
}

void Win32Listview::onItemAdded( ItemEvent* event )
{

}

void Win32Listview::onItemDeleted( ItemEvent* event )
{

}

void Win32Listview::setColumnWidth( const unsigned long& index, const double& width, ListViewControl::AutoSizeType type )
{
	//don't do this if we are tracking
	if ( false == headerControlIsTracking_ ) {
		/* autoresizing added by Marcello */
		int err = 0;
		switch ( type ) {
		case ListViewControl::lcatAutoSizeNone:
			err = ListView_SetColumnWidth( hwnd_, index, (long)width );
			break;
		case ListViewControl::lcatAutoSizeColumns:
			err = ListView_SetColumnWidth( hwnd_, index, (long)LVSCW_AUTOSIZE );
			break;
		case ListViewControl::lcatAutoSizeHeaders:
			err = ListView_SetColumnWidth( hwnd_, index, (long)LVSCW_AUTOSIZE_USEHEADER  );
			break;
		case ListViewControl::lcatAutoSizeColumnsAndHeaders:
			err = ListView_SetColumnWidth( hwnd_, index, (long)LVSCW_AUTOSIZE_USEHEADER );
			break;
		default:
			err = ListView_SetColumnWidth( hwnd_, index, (long)LVSCW_AUTOSIZE_USEHEADER );
			break;
		}
	}
}

double Win32Listview::getColumnWidth( const unsigned long& index )
{
	double result = 0.0;
	
	if ( System::isUnicodeEnabled() ) {
		LVCOLUMNW columnInfo;
		memset( &columnInfo, 0, sizeof(LVCOLUMNW) );
		columnInfo.mask = LVCF_WIDTH ;
		
		SendMessage( hwnd_, LVM_GETCOLUMNW, index, (LPARAM)&columnInfo );
		result = columnInfo.cx;
	}
	else {
		LVCOLUMNA columnInfo;
		memset( &columnInfo, 0, sizeof(LVCOLUMNA) );
		columnInfo.mask = LVCF_WIDTH ;
		
		SendMessage( hwnd_, LVM_GETCOLUMNA, index, (LPARAM)&columnInfo );
		result = columnInfo.cx;
	}
	
	return result;
}

void Win32Listview::setColumnName( const unsigned long& index, const String& columnName )
{
	if ( System::isUnicodeEnabled() ) {
		LVCOLUMNW columnInfo;
		memset( &columnInfo, 0, sizeof(columnInfo) );

		columnInfo.mask = LVCF_TEXT;
		columnInfo.cchTextMax = columnName.size();

		VCFChar* tmp = new VCFChar[columnInfo.cchTextMax+1];
		memset(tmp,0,(columnInfo.cchTextMax+1)*sizeof(VCFChar));
		columnName.copy( tmp, columnInfo.cchTextMax );

		columnInfo.pszText = tmp;



		SendMessage( hwnd_, LVM_SETCOLUMNW, (WPARAM)index, (LPARAM)&columnInfo );

		delete [] tmp;
	}
	else {
		LVCOLUMNA columnInfo;
		memset( &columnInfo, 0, sizeof(columnInfo) );

		AnsiString tmpColName = columnName;

		columnInfo.mask = LVCF_TEXT;
		columnInfo.cchTextMax = tmpColName.size();

		char* tmp = new char[columnInfo.cchTextMax+1];
		memset(tmp,0,columnInfo.cchTextMax+1);
		tmpColName.copy( tmp, columnInfo.cchTextMax );

		columnInfo.pszText = tmp;


		SendMessage( hwnd_, LVM_SETCOLUMNA, (WPARAM)index, (LPARAM)&columnInfo );

		delete [] tmp;
	}




}

String Win32Listview::getColumnName( const unsigned long& index )
{
	String result;	

	if ( System::isUnicodeEnabled() ) {
		LVCOLUMNW columnInfo;
		memset( &columnInfo, 0, sizeof(LVCOLUMNW) );
		columnInfo.mask = LVCF_TEXT ;
		
		SendMessage( hwnd_, LVM_GETCOLUMNW, index, (LPARAM)&columnInfo );
		result = columnInfo.pszText;
	}
	else {
		LVCOLUMNA columnInfo;
		memset( &columnInfo, 0, sizeof(LVCOLUMNA) );
		columnInfo.mask = LVCF_TEXT ;
		
		SendMessage( hwnd_, LVM_GETCOLUMNA, index, (LPARAM)&columnInfo );
		result = columnInfo.pszText;
	}

	return result;
}

int CALLBACK Win32Listview::sortFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
	int result = 0;
	ItemSort* itemSortFunctor = (ItemSort*)lParamSort;
	ListItem* item1 = (ListItem*)lParam1;
	ListItem* item2 = (ListItem*)lParam2;

	bool compareResult = itemSortFunctor->compare( item1, item2 );
	result = compareResult ? -1 : 1 ;
	return result;
}

void Win32Listview::sort( ItemSort* itemSortFunctor )
{
	int err = ListView_SortItems( hwnd_, Win32Listview::sortFunc, (LPARAM)itemSortFunctor );
}

void Win32Listview::onLargeImageListImageChanged( ImageListEvent* event )
{
	ImageList* imageList = (ImageList*)event->getSource();

	switch ( event->getType() ) {
		case IMAGELIST_EVENT_WIDTH_CHANGED : case IMAGELIST_EVENT_HEIGHT_CHANGED :{
			int cx = imageList->getImageWidth();
			int cy = imageList->getImageHeight();
			int err = ImageList_SetIconSize( largeImageListCtrl_, cx, cy );

			//reset the contents
			Win32Image* win32Img = (Win32Image*)imageList->getMasterImage();
			SysPixelType* pix = win32Img->getImageBits()->pixels_;
			int sz = win32Img->getWidth() * win32Img->getHeight();
			unsigned char* oldAlpaVals = new unsigned char[sz];
			do {
				sz --;
				oldAlpaVals[sz] = pix[sz].a;
				pix[sz].a = 0;
			} while( sz > 0 );

			HBITMAP hbmImage = win32Img->getBitmap();

			HBITMAP hCopyImg = (HBITMAP)CopyImage( hbmImage, IMAGE_BITMAP, 0, 0, NULL );

			err = ImageList_AddMasked( largeImageListCtrl_, hCopyImg, RGB(0,255,0) );
			if ( err < 0 ) {
				//error condition !
			}
			DeleteObject( hCopyImg );
			sz = win32Img->getWidth() * win32Img->getHeight();
			do {
				sz --;
				pix[sz].a = oldAlpaVals[sz];
			} while( sz > 0 );
			
			delete [] oldAlpaVals;

		}
		break;

		case IMAGELIST_EVENT_ITEM_ADDED : {
			Win32Image* win32Img = (Win32Image*)event->getImage();
			SysPixelType* pix = win32Img->getImageBits()->pixels_;
			int sz = win32Img->getWidth() * win32Img->getHeight();
			unsigned char* oldAlpaVals = new unsigned char[sz];
			do {
				sz --;
				oldAlpaVals[sz] = pix[sz].a;
				pix[sz].a = 0;
			} while( sz > 0 );

			HBITMAP hbmImage = win32Img->getBitmap();
			HBITMAP hCopyImg = (HBITMAP)CopyImage( hbmImage, IMAGE_BITMAP, 0, 0, NULL );

			int err = ImageList_Add( largeImageListCtrl_, hCopyImg, NULL );
			if ( err < 0 ) {
				//error condition !
			}
			DeleteObject( hCopyImg );
			sz = win32Img->getWidth() * win32Img->getHeight();
			do {
				sz --;
				pix[sz].a = oldAlpaVals[sz];
			} while( sz > 0 );
			
			delete [] oldAlpaVals;
		}
		break;

		case IMAGELIST_EVENT_ITEM_DELETED : {

		}
		break;
	}
}

void Win32Listview::onSmallImageListImageChanged( ImageListEvent* event )
{
	ImageList* imageList = (ImageList*)event->getSource();

	switch ( event->getType() ) {
		case IMAGELIST_EVENT_WIDTH_CHANGED : case IMAGELIST_EVENT_HEIGHT_CHANGED :{
			int cx = imageList->getImageWidth();
			int cy = imageList->getImageHeight();
			int err = ImageList_SetIconSize( smallImageListCtrl_, cx, cy );

			//reset the contents
			Win32Image* win32Img = (Win32Image*)imageList->getMasterImage();
			HBITMAP hbmImage = win32Img->getBitmap();
			SysPixelType* pix = win32Img->getImageBits()->pixels_;
			int sz = win32Img->getWidth() * win32Img->getHeight();
			unsigned char* oldAlpaVals = new unsigned char[sz];
			do {
				sz --;
				oldAlpaVals[sz] = pix[sz].a;
				pix[sz].a = 0;
			} while( sz > 0 );

			HBITMAP hCopyImg = (HBITMAP)CopyImage( hbmImage, IMAGE_BITMAP, 0, 0, NULL );

			err = ImageList_AddMasked( smallImageListCtrl_, hCopyImg, RGB(0,255,0) );
			if ( err < 0 ) {
				//error condition !
			}

			::DeleteObject( hCopyImg );
			sz = win32Img->getWidth() * win32Img->getHeight();
			do {
				sz --;
				pix[sz].a = oldAlpaVals[sz];
			} while( sz > 0 );
			
			delete [] oldAlpaVals;

		}
		break;
	}
}

void Win32Listview::setLargeImageList( ImageList* imageList )
{
	if ( NULL != largeImageListCtrl_ ) {
		//destroy the old one
		int err = ImageList_Destroy( largeImageListCtrl_ );
		largeImageListCtrl_ = NULL;
	}

	if ( NULL != imageList ) {
		largeImageListCtrl_ = ImageList_Create( imageList->getImageWidth(), imageList->getImageHeight(),
										ILC_COLOR32, imageList->getImageCount(), 4 );

		Win32Image* win32Img = (Win32Image*)imageList->getMasterImage();
		SysPixelType* pix = win32Img->getImageBits()->pixels_;
		int sz = win32Img->getWidth() * win32Img->getHeight();
		unsigned char* oldAlpaVals = new unsigned char[sz];
		do {
			sz --;
			oldAlpaVals[sz] = pix[sz].a;
			pix[sz].a = 0;
		} while( sz > 0 );


		HBITMAP hbmImage = win32Img->getBitmap();

		HBITMAP hCopyImg = (HBITMAP)CopyImage( hbmImage, IMAGE_BITMAP, 0, 0, NULL );

		if ( NULL == hCopyImg ) {
			//error - throw exception
		}

		int err = ImageList_Add( largeImageListCtrl_, hCopyImg, NULL );//RGB(98,94,94) );
		if ( err < 0 ) {
			//error condition !
		}

		::DeleteObject( hCopyImg );
		sz = win32Img->getWidth() * win32Img->getHeight();
		do {
			sz --;
			pix[sz].a = oldAlpaVals[sz];
		} while( sz > 0 );
		
		delete [] oldAlpaVals;


		ListView_SetImageList( hwnd_, largeImageListCtrl_, LVSIL_NORMAL );

		EventHandler* imgListHandler = getEventHandler( "LargeImageListHandler" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ImageListEventHandler<Win32Listview>(this, &Win32Listview::onLargeImageListImageChanged, "LargeImageListHandler" );

		}

		imageList->SizeChanged.addHandler( imgListHandler );
		imageList->ImageAdded.addHandler( imgListHandler );
		imageList->ImageDeleted.addHandler( imgListHandler );

	}
}

void Win32Listview::setSmallImageList( ImageList* imageList )
{
	if ( NULL != smallImageListCtrl_ ) {
		//destroy the old one
		int err = ImageList_Destroy( largeImageListCtrl_ );
		smallImageListCtrl_ = NULL;
	}

	if ( NULL != imageList ) {
		smallImageListCtrl_ = ImageList_Create( imageList->getImageWidth(), imageList->getImageHeight(),
										ILC_COLOR24|ILC_MASK, imageList->getImageCount(), 4 );

		Win32Image* win32Img = (Win32Image*)imageList->getMasterImage();
		SysPixelType* pix = win32Img->getImageBits()->pixels_;
		int sz = win32Img->getWidth() * win32Img->getHeight();
		unsigned char* oldAlpaVals = new unsigned char[sz];
		do {
			sz --;
			oldAlpaVals[sz] = pix[sz].a;
			pix[sz].a = 0;
		} while( sz > 0 );

		HBITMAP hbmImage = win32Img->getBitmap();

		HBITMAP hCopyImg = (HBITMAP)CopyImage( hbmImage, IMAGE_BITMAP, 0, 0, NULL );

		int err = ImageList_AddMasked( smallImageListCtrl_, hCopyImg, RGB(0,255,0) );
		if ( err < 0 ) {
			//error condition !
		}


		::DeleteObject( hCopyImg );
		sz = win32Img->getWidth() * win32Img->getHeight();
		do {
			sz --;
			pix[sz].a = oldAlpaVals[sz];
		} while( sz > 0 );
		
		delete [] oldAlpaVals;

		ListView_SetImageList( hwnd_, smallImageListCtrl_, LVSIL_SMALL );

		EventHandler* imgListHandler = getEventHandler( "SmallImageListHandler" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ImageListEventHandler<Win32Listview>(this, &Win32Listview::onSmallImageListImageChanged, "SmallImageListHandler" );

		}

		imageList->SizeChanged.addHandler( imgListHandler );
	}
}

Rect Win32Listview::getItemImageRect( ListItem* item )
{
	Rect result;

	return result;
}

long Win32Listview::getDisplayOptions()
{
	long result = lvdoDefault;
	DWORD style = ListView_GetExtendedListViewStyle( hwnd_ );
	if ( style & LVS_EX_FULLROWSELECT ) {
		result |= lvdoFullRowSelect;
	}

	if ( style & LVS_EX_GRIDLINES  ) {
		result |= lvdoGridLines;
	}

	if ( style & LVS_EX_TRACKSELECT  ) {
		result |= lvdoHotTracking;
	}

	return result;
}

void Win32Listview::setDisplayOptions( const long& displayOptions )
{
	DWORD style = 0;

	if ( displayOptions & lvdoFullRowSelect ) {
		style |= LVS_EX_FULLROWSELECT;
	}

	if ( displayOptions & lvdoGridLines  ) {
		style |= LVS_EX_GRIDLINES;
	}

	if ( displayOptions & lvdoHotTracking  ) {
		style |= LVS_EX_TRACKSELECT;
	}

	ListView_SetExtendedListViewStyleEx( hwnd_, 0, style );
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/09/09 04:42:04  ddiego
*fixed some custom draw bugs in win32 tree control. updated
*advanced ui example.
*
*Revision 1.2.2.2  2004/09/06 21:30:20  ddiego
*added a separate paintBorder call to Control class
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.10  2004/07/30 17:27:14  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.9  2004/07/21 03:35:49  ddiego
*some minor updates to the QTPlayer example
*
*Revision 1.1.2.8  2004/07/16 04:01:46  ddiego
*fixed the last of border redraw issues, I hope.
*
*Revision 1.1.2.7  2004/07/15 18:53:00  ddiego
*more updates
*
*Revision 1.1.2.6  2004/07/15 14:55:11  ddiego
*borders fixed
*
*Revision 1.1.2.5  2004/07/14 18:18:14  ddiego
*fixed problem with edit control. Turns out we were using the wrong
*subclassed wndproc. This is now fixed.
*
*Revision 1.1.2.4  2004/07/14 04:56:02  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.3  2004/07/13 04:34:32  ddiego
*little changes
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.40.2.2  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.40.2.1  2004/04/09 06:09:06  ddiego
*nybbles and bytes
*
*Revision 1.40  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.38.2.2  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.38.2.1  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.38  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.37.2.4  2003/10/07 21:26:04  ddiego
*minor adj to listview to get selected item correctly
*
*Revision 1.37.2.3  2003/09/09 19:32:03  marcelloptr
*minor changes and autoresizing of listbox columns
*
*Revision 1.37.2.2  2003/09/09 04:22:59  ddiego
*added a readonly method to the text peer interface
*patched in Marcellos changes to the ListViewControl for autosizing
*column headers
*made adjustment to default height calculations in UIMEtricManager impl
*
*Revision 1.37.2.1  2003/08/17 19:46:33  ddiego
*added a bug fix for bug #788533 to the Win32ListView impl
*
*Revision 1.37  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.36.2.2  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.36.2.1  2003/05/27 04:45:34  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.36  2003/05/17 20:37:37  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.35.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.35.2.1  2003/03/12 03:12:39  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.35  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.34.2.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.34.2.3  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.34.2.2  2002/12/27 23:04:54  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.34.2.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.34  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.33.4.1  2002/11/17 01:20:38  cesarmello
*Removed the LR_COPYRETURNORG flag from CopyImage due to inconsistent Win32 behavior under Windows NT 4
*
*Revision 1.33  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.32.6.1  2002/07/03 07:13:01  marcelloptr
*minor fixes
*
*Revision 1.32  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.31.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.31.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.31  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.30  2002/02/13 03:32:13  ddiego
*fixed bug [ #516363 ] emtying column model causes exception
*removed some redundant/incorrect code from Win32ListView.cpp
*
*Revision 1.29  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.28  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


