//Win32Listview.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#ifdef VCF_CYGWIN
#define _WIN32_IE   0x0400  //this may be a bogus thing to do !
#endif//VCF_CYGWIN



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/ListViewControl.h"
#include "vcf/ApplicationKit/Win32Listview.h"
#include "vcf/GraphicsKit/DrawUIState.h"


#if defined(VCF_CYGWIN) || defined(VCF_MINGW)
/*
//add some stupid defines here since they seem to be missing from the mingw Win32 API headers
#if (_WIN32_IE >= 0x0400)

#if !defined(VCF_MINGW)
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
#endif

// NMLVGETINFOTIPA.dwFlag values

#define LVGIT_UNFOLDED  0x0001

#define LVN_GETINFOTIPA          (LVN_FIRST-57)
#define LVN_GETINFOTIPW          (LVN_FIRST-58)

#ifdef VCF_UNICODE
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

    #ifdef VCF_UNICODE
        #define LVN_ODFINDITEM          LVN_ODFINDITEMW
    #else
        #define LVN_ODFINDITEM          LVN_ODFINDITEMA
    #endif
#endif      // _WIN32_IE >= 0x0300



#if (_WIN32_IE >= 0x0300)
#define LVN_MARQUEEBEGIN        (LVN_FIRST-56)
#endif
*/


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

#endif //VCF_CYGWIN

using namespace VCFWin32;
using namespace VCF;


Win32Listview::Win32Listview( ListViewControl* listviewControl ):
	AbstractWin32Component( listviewControl ),
	listviewControl_( listviewControl ),
	oldHeaderWndProc_(NULL),
	largeImageListCtrl_(NULL),
	smallImageListCtrl_(NULL),
	internalMessage_(false),
	oldHeaderFont_(NULL),
	currentCtx_(NULL)
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

	CreateParams params = createParams();

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
		hwnd_ = ::CreateWindowExW( params.second,
		                             WC_LISTVIEWW,
									 NULL,
									 params.first,
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
		hwnd_ = ::CreateWindowExA( params.second,
		                             WC_LISTVIEWA,//"SysListView32",//className.c_str(),
									 NULL,
									 params.first,
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
		registerForFontChanges();

		COLORREF backColor = backColor_.getColorRef32();
		ListView_SetBkColor( hwnd_, backColor );

		CallBack* cb = 
			new ClassProcedure1<Event*,Win32Listview>( this, &Win32Listview::onColumnModelAdded, "Win32Listview::onColumnModelAdded" );

		cb = 
			new ClassProcedure1<Event*,Win32Listview>( this, &Win32Listview::onColumnModelRemoved, "Win32Listview::onColumnModelRemoved" );

		cb = 
			new ClassProcedure1<Event*,Win32Listview>( this, &Win32Listview::onCtrlModelChanged, "Win32Listview::onCtrlModelChanged" );

		owningControl->ControlModelChanged += cb;

		cb = 
			new ClassProcedure1<Event*,Win32Listview>( this, &Win32Listview::onListModelChanged, "Win32Listview::onListModelChanged" );
		
		cb = 
			new ClassProcedure1<Event*,Win32Listview>( this, &Win32Listview::onColumnModelChanged, "Win32Listview::onColumnModelChanged" );
			

		
	}
	else {
		//throw exception
	}

	setCreated( true );

	headerControlIsTracking_ = false;
}

void Win32Listview::registerHeaderWndProc()
{
	if ( NULL == oldHeaderWndProc_ ) {
		HWND headerWnd = ListView_GetHeader( hwnd_ );
		if ( NULL != headerWnd ) {
			::SetWindowLongPtr( headerWnd, GWLP_USERDATA, (LONG_PTR)this );
			oldHeaderWndProc_ = (WNDPROC)(LONG_PTR) ::SetWindowLongPtr( headerWnd, GWLP_WNDPROC, (LONG_PTR)Win32Listview::Header_WndProc );

			::SetWindowLong(headerWnd, GWL_ID, (LONG)'vcfH');
		}
	}
}

Win32Object::CreateParams Win32Listview::createParams()
{
	Win32Object::CreateParams result;
	result.first = BORDERED_VIEW | LVS_SINGLESEL | LVS_ALIGNLEFT | LVS_AUTOARRANGE | LVS_ICON | LVS_SHOWSELALWAYS | LVS_OWNERDATA;
	result.first &= ~WS_BORDER;

	result.second = 0;

	return result;
}

LRESULT CALLBACK Win32Listview::Header_WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	Win32Listview* win32ListView = (Win32Listview*)(LONG_PTR) ::GetWindowLongPtr( hWnd, GWLP_USERDATA );

	switch ( message ) {
	
		case WM_ERASEBKGND : {

			result = 0;
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
	ListItem* item = listviewControl_->getItem( drawItem->nmcd.dwItemSpec );
	
	bool useItemPaint = false;
	
	RECT tmp = {0,0,0,0};
	ListView_GetItemRect( hwnd_, drawItem->nmcd.dwItemSpec, &tmp, LVIR_BOUNDS );
	Rect itemRect( tmp.left, tmp.top, tmp.right, tmp.bottom );
	

	if ( NULL != item ) {

		//item->setSelected( isItemSelected( item ) );

		if ( item->canPaint() ) {
			
			
			item->paint( currentCtx_, &itemRect );

			LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
			if ( style & LVS_REPORT ) {
				
				ColumnModel* colModel = listviewControl_->getColumnModel();
				if ( NULL != colModel ) {
					uint32 colIndex = 0;
					Enumerator<ColumnItem*>* columns = listviewControl_->getColumnItems();
					std::vector<ListSubItem*> subItems;
					std::vector<ListSubItem*>::iterator it = subItems.begin();

					item->getSubItems(subItems);
					Rect subItemRect = itemRect;
					while ( (true == columns->hasMoreElements()) && 
							(it != subItems.end()) ) {
						useItemPaint = false;
						ColumnItem* column = columns->nextElement();
						subItemRect.right_ = subItemRect.left_ + column->getWidth();

						if ( colIndex > 0 ) {
							ListSubItem* subItem = *it;
							if ( subItem->canPaint() ) {
								subItem->paint( currentCtx_, &subItemRect, colIndex );
								useItemPaint = true;
							}
							++it;
						}

						if ( !useItemPaint ) {
							ListItemState itemState;
							itemState.setAsSubItem(true);
							listviewControl_->paintSubItem( currentCtx_, subItemRect, drawItem->nmcd.dwItemSpec, colIndex-1, itemState );
						}
						
						subItemRect.left_ = subItemRect.right_;
						
						colIndex ++;
					}
				}
			}

			useItemPaint = true;
		}
	}

	if ( !useItemPaint ) {
		ListItemState itemState;
		listviewControl_->paintItem( currentCtx_, itemRect, drawItem->nmcd.dwItemSpec, itemState );
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

		case WM_NOTIFY:{
			result = true;
			wndProcResult = defaultWndProcedure( message, wParam, lParam );
			if ( !peerControl_->isDestroying() ) {
				NMHDR* notificationHdr = (LPNMHDR)lParam;
				Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( notificationHdr->hwndFrom );
				if ( NULL != win32Obj ){
					win32Obj->handleEventMessages( notificationHdr->code, wParam, lParam, wndProcResult );
				}
				else {
					NMHDR* notificationHdr = (LPNMHDR)lParam;
					if ( notificationHdr->idFrom == 'vcfH' ) {						
						switch ( notificationHdr->code ) {
							case HDN_GETDISPINFOW : {
								NMHDDISPINFOW* dispInfo = (NMHDDISPINFOW*)lParam;
								
								ColumnModel* cm = this->listviewControl_->getColumnModel();
								ColumnItem* item = listviewControl_->getColumnItem( (uint32)dispInfo->lParam );
								
								if ( NULL != cm ) {
									
									if ( NULL != item && dispInfo->mask & HDI_IMAGE ) {
										dispInfo->iImage = item->getImageIndex();
									}
									
									if ( dispInfo->mask & HDI_TEXT ) {
										
										String caption;
										if ( NULL != item ) {
											caption = item->getCaption();
										}
										else {
											caption = cm->getAsString((uint32)dispInfo->lParam);
										}
										
										unsigned int size = VCF::minVal<unsigned int>( caption.size(), dispInfo->cchTextMax );
										caption.copy( dispInfo->pszText, size );
										if ( size < dispInfo->cchTextMax ) {
											dispInfo->pszText[size] = '\0';
										}
									}
								}
							}
							break;

							case NM_CUSTOMDRAW : {
								NMCUSTOMDRAW* cd = (NMCUSTOMDRAW*)lParam;
								switch ( cd->dwDrawStage ) {
									case CDDS_PREPAINT : {
										wndProcResult = CDRF_NOTIFYITEMDRAW;
										
										RECT r;
										GetClientRect( notificationHdr->hwndFrom, &r );
										
										RECT rLast;
										int index = -1;
										index = Header_GetItemCount(notificationHdr->hwndFrom) - 1;
										if ( index >= 0 ) {
											Header_GetItemRect( notificationHdr->hwndFrom, index, &rLast );				
											r.left = rLast.right;
										}
										FillRect( cd->hdc, &r, (HBRUSH) (COLOR_3DFACE + 1) );
										
									}
									break;

									case CDDS_ITEMPREPAINT : {								
										wndProcResult = CDRF_NOTIFYPOSTPAINT;

										uint32 index = cd->dwItemSpec;
										ColumnItem* item = NULL;

										HWND header = ListView_GetHeader( hwnd_ );
										if ( NULL != header ) {
											HDITEM headerItem;
											memset( &headerItem, 0, sizeof(HDITEM) );
											headerItem.mask = HDI_FORMAT | HDI_LPARAM;
											if ( Header_GetItem( header, index, &headerItem ) ) {
												item = listviewControl_->getColumnItem( (uint32)headerItem.lParam );
												if ( NULL != item ) {
													if ( !item->isFontDefault() ) {
														
														Color* fc = item->getFont()->getColor();
														
														SetTextColor( cd->hdc, (COLORREF) fc->getColorRef32() );
														
														Win32Font* fontPeer = dynamic_cast<Win32Font*>( item->getFont()->getFontPeer() );
														HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( fontPeer );
														if ( NULL != fontHandle ){
															
															oldHeaderFont_ = (HFONT)::SelectObject( cd->hdc, fontHandle );
															
															wndProcResult |= CDRF_NEWFONT;
														}
													}
												}
											}
										}
									}
									break;

									case CDDS_ITEMPOSTPAINT : {
										
										uint32 index = cd->dwItemSpec;
										ColumnItem* item = NULL;

										HWND header = ListView_GetHeader( hwnd_ );
										if ( NULL != header ) {
											HDITEM headerItem;
											memset( &headerItem, 0, sizeof(HDITEM) );
											headerItem.mask = HDI_FORMAT | HDI_LPARAM;
											if ( Header_GetItem( header, index, &headerItem ) ) {
												item = listviewControl_->getColumnItem( (uint32)headerItem.lParam );
											}
										}

										if ( NULL != item ) {
											if ( item->canPaint() ) {
												GraphicsContext gc( (OSHandleID)cd->hdc );
												Rect rect( cd->rc.left, cd->rc.top, cd->rc.right, cd->rc.bottom );
												item->paint( &gc, &rect );
												gc.getPeer()->setContextID( 0 );
											}

										}

										if ( NULL != oldHeaderFont_ ) {
											::SelectObject( cd->hdc, oldHeaderFont_ );
											oldHeaderFont_ = NULL;
										}
										wndProcResult = CDRF_SKIPDEFAULT;
									}
									break;

									default : {
										wndProcResult = CDRF_DODEFAULT;
									}
									break;
								}

							}
							break;
						}
					}
				}
			}
		}
		break;


		case WM_PAINT:{

			PAINTSTRUCT ps;
			HDC dc = BeginPaint( hwnd_, &ps );

			RECT r;
			GetClientRect( hwnd_, &r );




			LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
			if ( style & LVS_REPORT ) {
				
				HWND header = GetDlgItem( hwnd_, 0 );
				RECT headerRect;
				memset(&headerRect,0,sizeof(headerRect));
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
			}


			Rect paintRect(r.left, r.top,r.right, r.bottom );

			this->prepForDoubleBufferPaint( dc, paintRect );

			HDC memDC = (HDC) memCtx_->getPeer()->getContextID();

			::SetViewportOrgEx( memDC, -r.left, -r.top, NULL );

			Color* color = listviewControl_->getColor();
			COLORREF backColor = color->getColorRef32();

			HBRUSH bkBrush = CreateSolidBrush( backColor );
			FillRect( memDC, &r, bkBrush );
			DeleteObject( bkBrush );



			::SetViewportOrgEx( memDC, -r.left, -r.top, NULL );

			currentCtx_ = memCtx_;

			//ControlGraphicsContext ctrlCtx(peerControl_);
			//currentCtx_ = &ctrlCtx;			

			//currentCtx_->setViewableBounds( Rect(r.left, r.top,
			//								r.right, r.bottom ) );

			//currentCtx_->getPeer()->setContextID( (OSHandleID)memDC_ );
			//((ControlGraphicsContext*)currentCtx_)->setOwningControl( NULL );


			defaultWndProcedure( WM_PAINT, (WPARAM)memDC, 0 );

			//((ControlGraphicsContext*)currentCtx_)->setOwningControl( peerControl_ );


			::BitBlt( dc, r.left, r.top,
					  r.right - r.left,
					  r.bottom - r.top,
					  memDC, r.left, r.top, SRCCOPY );
			//::RestoreDC ( memDC_, memDCState_ );

			//::DeleteObject( memBMP_ );


			currentCtx_ = NULL;

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
			ColumnItem* item  = listviewControl_->getColumnItem( (uint32)nmlistView->iSubItem );

			if ( NULL != item ) {
				POINT pt = {0,0};
				::GetCursorPos( &pt );
				::ScreenToClient( hwnd_, &pt );

				MouseEvent event( item, ListViewControl::COLUMN_MOUSE_EVENT_CLICK,
									Win32UIUtils::translateButtonMask( MK_LBUTTON ),
									Win32UIUtils::translateKeyMask( 0 ),
									&Point(pt.x, pt.y) );

				listviewControl_->handleEvent( &event );
			}
			else {
				POINT pt = {0,0};
				::GetCursorPos( &pt );
				::ScreenToClient( hwnd_, &pt );

				MouseEvent event( NULL, ListViewControl::COLUMN_MOUSE_EVENT_CLICK,
									Win32UIUtils::translateButtonMask( MK_LBUTTON ),
									Win32UIUtils::translateKeyMask( 0 ),
									&Point(pt.x, pt.y) );

				event.setUserData( (void*)nmlistView->iSubItem );

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
					ColumnItem* item  = listviewControl_->getColumnItem( (uint32)nmHeader->iItem );

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
					ColumnItem* item  = listviewControl_->getColumnItem( (uint32)nmHeader->iItem );
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
				ColumnItem* item  = listviewControl_->getColumnItem( (uint32)nmHeader->iItem );
				
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
				ColumnItem* item  = listviewControl_->getColumnItem( (uint32)nmHeader->iItem );
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

				ListModel* lm = (ListModel*) this->peerControl_->getViewModel();				
				if ( NULL != lm ) {

					if ( displayInfo->item.mask & LVIF_IMAGE ) {
						ListItem* item = listviewControl_->getItem( displayInfo->item.iItem );
						if ( NULL != item ) {
							displayInfo->item.iImage = item->getImageIndex();
						}
					}

					if ( displayInfo->item.mask & LVIF_PARAM ) {
						ListItem* item = listviewControl_->getItem( displayInfo->item.iItem );
						displayInfo->item.lParam  = (LPARAM)item;
					}

					if ( displayInfo->item.mask & LVIF_STATE ) {
						StringUtils::trace( "LVIF_STATE requested!" );
					}


					if ( displayInfo->item.mask & LVIF_TEXT ) {
						
						//StringUtils::trace( String("LVIF_TEXT index: ") + displayInfo->item.iItem + ", subi: " + displayInfo->item.iSubItem + "\n" );

						String caption;
						
						if ( displayInfo->item.iSubItem > 0 ) {						
							caption = lm->getSubItemAsString( displayInfo->item.iItem, displayInfo->item.iSubItem-1 );
						}
						else{
							caption = lm->getAsString( displayInfo->item.iItem );
						}
						
						// changed to unsigned ints after discussion with Jim,
						// but he seemed uncertain so it'd be worth checking - ACH
						unsigned int size = VCF::minVal<unsigned int>( caption.size(), displayInfo->item.cchTextMax );
						caption.copy( displayInfo->item.pszText, size );
						if ( size < displayInfo->item.cchTextMax ) {
							displayInfo->item.pszText[size] = '\0';
						}
					}
				}
			}
		}
		break;

		case LVN_GETDISPINFOA:{
			NMLVDISPINFOA* displayInfo = (NMLVDISPINFOA*)lParam;
			if ( displayInfo->hdr.hwndFrom == hwnd_ ) {
				ListItem* item = (ListItem*)displayInfo->item.lParam;
				if ( NULL != item ) {
					AnsiString caption;
					if ( displayInfo->item.iSubItem > 0 ) {
						ListSubItem* subItem = item->getSubItem( displayInfo->item.iSubItem - 1 );
						if ( NULL != subItem ) {
							caption = subItem->getCaption();
						}
					}
					else{
						caption = item->getCaption();
					}
					// changed to unsigned ints after discussion with Jim,
					// but he seemed uncertain so it'd be worth checking - ACH
					unsigned int size = VCF::minVal<unsigned int>( caption.size(), displayInfo->item.cchTextMax );
					caption.copy( displayInfo->item.pszText, size );
					if ( size < displayInfo->item.cchTextMax ) {
						displayInfo->item.pszText[size] = '\0';
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
			NMLVCACHEHINT* cacheHintPtr = (NMLVCACHEHINT *)lParam;
			StringUtils::trace( String("LVN_ODCACHEHINT from: ") + cacheHintPtr->iFrom + " to: " + cacheHintPtr->iTo + "\n" );

			ListModel* lm = listviewControl_->getListModel();
			if ( NULL != lm ) {
				lm->verifyRange( cacheHintPtr->iFrom, cacheHintPtr->iTo );
			}
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

				ListItem* item = listviewControl_->getItem( lvNotificationHdr->iItem );
				if ( NULL != item ){
					if ( (lvNotificationHdr->uChanged & LVIF_STATE) != 0 ) {
						internalMessage_ = true;

						if ( (lvNotificationHdr->uNewState & LVIS_SELECTED) != 0 ){
							item->setSelected( true );

							POINT tmpPt = {0,0};
							GetCursorPos( &tmpPt );
							::ScreenToClient( hwnd_, &tmpPt );
							ItemEvent event( listviewControl_, ItemEvent::Selected );
							Point pt( tmpPt.x, tmpPt.y );
							event.point = pt;
							event.index = lvNotificationHdr->iItem;
							event.itemSelected = true;

							listviewControl_->handleEvent( &event );
								//ItemSelectionChanged( &event );
						}
						else {
							item->setSelected( false );
						}

						internalMessage_ = false;
					}
				}
			}
			else {
				if ( (lvNotificationHdr->uChanged & LVIF_STATE) != 0 ) {
					if ( (lvNotificationHdr->uNewState & LVIS_SELECTED) == 0 ){
						internalMessage_ = true;

						POINT tmpPt = {0,0};
						GetCursorPos( &tmpPt );
						::ScreenToClient( hwnd_, &tmpPt );
						ItemEvent event( listviewControl_, ItemEvent::Selected );
						Point pt( tmpPt.x, tmpPt.y );
						event.point = pt;
						event.index = lvNotificationHdr->iItem;
						event.itemSelected = false;

						listviewControl_->handleEvent( &event );


						internalMessage_ = false;
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
						ListItem* item = listviewControl_->getItem( listViewCustomDraw->nmcd.dwItemSpec );
						if ( NULL != item ) {
							if ( !item->isFontDefault() ) {
								
								Color* fc = item->getFont()->getColor();
								listViewCustomDraw->clrText = (COLORREF) fc->getColorRef32();
								
								Win32Font* fontPeer = dynamic_cast<Win32Font*>( item->getFont()->getFontPeer() );
								HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( fontPeer );
								if ( NULL != fontHandle ){
									::SelectObject( listViewCustomDraw->nmcd.hdc, fontHandle );
									wndProcResult |= CDRF_NEWFONT;
								}
							}
						}

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
/*
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
*/

bool Win32Listview::ensureVisible( const uint32& index, bool partialOK )
{
	//LVM_ENSUREVISIBLE
	bool result = false;
	if ( ListModel::InvalidIndex != index ){

//		if ( System::isUnicodeEnabled() ) {
			
				result = ( 0 !=
					ListView_EnsureVisible( hwnd_, index, partialOK ) );
			
/*
		}
		else {
			LVFINDINFOA findInfo;
			memset( &findInfo, 0, sizeof(LVFINDINFOA) );
			findInfo.flags = LVFI_PARAM;
			findInfo.lParam = (LPARAM)item;

			int foundIndex = SendMessage( hwnd_, LVM_FINDITEMA, -1, (LPARAM)&findInfo );
			if ( foundIndex > -1 ) {
				result = ( 0 !=
					ListView_EnsureVisible( hwnd_, foundIndex, partialOK ) );
			}
		}

*/
	}
	return result;
}

void Win32Listview::setFocusedItem( const uint32& index )
{
	if ( ListModel::InvalidIndex != index ){

		if ( System::isUnicodeEnabled() ) {		
			LV_ITEMW lvItem;
			memset(&lvItem,0,sizeof(lvItem));
			lvItem.stateMask = LVIS_FOCUSED;
			lvItem.state = LVIS_FOCUSED;

			SendMessage( hwnd_, LVM_SETITEMSTATE, index, (LPARAM)&lvItem );			
		}
		else {			
			LV_ITEMA lvItem;
			memset(&lvItem,0,sizeof(lvItem));
			lvItem.stateMask = LVIS_FOCUSED;
			lvItem.state = LVIS_FOCUSED;

			SendMessage( hwnd_, LVM_SETITEMSTATE, index, (LPARAM)&lvItem );			
		}
	}
}

void Win32Listview::selectItem(const uint32& index)
{
	if ( ListModel::InvalidIndex != index ){

		internalMessage_ = true;

		if ( System::isUnicodeEnabled() ) {
			LV_ITEMW lvItem;
			memset(&lvItem,0,sizeof(lvItem));
			lvItem.stateMask = LVIS_SELECTED;
			lvItem.state = LVIS_SELECTED;


			SendMessage( hwnd_, LVM_SETITEMSTATE, index, (LPARAM)&lvItem );
			
		}
		else {			
			LV_ITEMA lvItem;
			memset(&lvItem,0,sizeof(lvItem));
			lvItem.stateMask = LVIS_SELECTED;
			lvItem.state = LVIS_SELECTED;


			SendMessage( hwnd_, LVM_SETITEMSTATE, index, (LPARAM)&lvItem );			
		}

		internalMessage_ = false;
	}
	else {
		LV_ITEMW lvItem;
		memset(&lvItem,0,sizeof(lvItem));
		lvItem.stateMask = LVIS_SELECTED;
		lvItem.state = 0;
		SendMessage( hwnd_, LVM_SETITEMSTATE, index, (LPARAM)&lvItem );
	}
}

Rect Win32Listview::getItemRect( const uint32& index )
{
	Rect result;

	RECT rect = {0,0,0,0};
	
	if ( index != ListModel::InvalidIndex ) {
		ListView_GetItemRect( hwnd_, index, &rect, LVIR_BOUNDS );
		result.setRect( rect.left, rect.top, rect.right, rect.bottom );
	}
	
	return result;
}

bool Win32Listview::isItemSelected( const uint32& index )
{
	bool result = false;
	if ( index != ListModel::InvalidIndex ){		
		result = ( LVIS_SELECTED ==
			SendMessage( hwnd_, LVM_GETITEMSTATE, index, LVIS_SELECTED ) );
	}
	return result;
}

uint32 Win32Listview::getFocusedItem()
{
	uint32 result = ListModel::InvalidIndex;

	int index = ListView_GetSelectionMark( hwnd_ );
	if ( index > -1 ){
		if ( LVIS_FOCUSED  == ListView_GetItemState( hwnd_, index, LVIS_FOCUSED  ) ){
			result = index;
		}
		else {
			
			int i = 0;
			int count = ListView_GetSelectedCount( hwnd_ );
			while ( i < count ){
				index = ListView_GetNextItem( hwnd_, index, LVNI_FOCUSED );
				if ( index != -1 ) {
					result = index;
					break;
				}
				//if ( LVIS_FOCUSED  == ListView_GetItemState( hwnd_, index, LVIS_FOCUSED  ) ){
					
					
					/*
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
							*/
					//		break;
				//}
				i++;
			}
		}
	}
	return result;
}

uint32 Win32Listview::getSelectedItem()
{
	uint32 result = ListModel::InvalidIndex;

	int index = ListView_GetNextItem(hwnd_, -1, LVNI_SELECTED);
	if ( index >= 0 ) {
		result = index;
		/*
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
*/
	}
	return result;
}

Enumerator<uint32>* Win32Listview::getSelectedItems()
{
	//int index = ListView_GetSelectionMark( hwnd_ );

	ListItem* item = NULL;
	selectedItems_.clear();

	int index = ListView_GetNextItem(hwnd_, -1, LVNI_SELECTED);
	if ( index >= 0 ) {
/*
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
		*/

		selectedItems_.push_back( index );

		index = ListView_GetNextItem(hwnd_, index, LVNI_SELECTED);

		while ( index >= 0 ) {
			/*
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
			*/

			selectedItems_.push_back( index );

			index = ListView_GetNextItem(hwnd_, index, LVNI_SELECTED);
		}
	}

	return selectedItems_.getEnumerator();
}

void Win32Listview::rangeSelect( const Rect& selectionRect )
{

}

IconStyleType Win32Listview::getIconStyle()
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	return translateStyleToIconStyle( style );
}

void Win32Listview::setIconStyle( const IconStyleType& iconStyle )
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );

	style &= ~LVS_ICON;
	style &= ~LVS_SMALLICON;
	style &= ~LVS_LIST;
	style &= ~LVS_REPORT;

	style |= translateIconStyleToStyleBit( iconStyle );

	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED );
	InvalidateRect( hwnd_, NULL, TRUE );
}

bool Win32Listview::allowsMultiSelect()
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	return ((style & LVS_SINGLESEL) == 0);
}

void Win32Listview::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	if ( true == allowsMultiSelect ){
		style &= ~LVS_SINGLESEL;
	}
	else {
		style |= LVS_SINGLESEL;
	}
	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
}

IconAlignType Win32Listview::getIconAlignment()
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	return translateStyleToIconAlignment( style );
}

void Win32Listview::setIconAlignment( const IconAlignType& iconAlignType )
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	style |= translateIconAlignmentToStyleBit( iconAlignType );
	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
}

bool Win32Listview::getAllowLabelEditing()
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	return ((style & LVS_EDITLABELS) == 0);
}

void Win32Listview::setAllowLabelEditing( const bool& allowLabelEditing )
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	if ( true == allowLabelEditing ){
		style |= LVS_EDITLABELS;
	}
	else {
		style &= ~LVS_EDITLABELS;
	}
	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
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

/*void Win32Listview::onItemPaint( ItemEvent* event )
{

}
*/

/*
void Win32Listview::onItemChanged( ItemEvent* event )
{
	//switch ( event->getType() ){
	//		case ITEM_EVENT_TEXT_CHANGED:{
	//			Object* source = event->getSource();
	//			if ( NULL != source ){
	//				ListItem* item = dynamic_cast<ListItem*>(source);
	//				if ( NULL != item ){
	//					LVITEM lvItem = {0};
	//					lvItem.mask = LVIF_TEXT;
	//					String caption = item->getCaption();
	//					lvItem.cchTextMax = caption.size();
	//					lvItem.iItem = item->getIndex();
	//					TCHAR* tmp = new TCHAR[lvItem.cchTextMax];
	//					memset( tmp, 0, lvItem.cchTextMax * sizeof(TCHAR) );
	//					caption.copy( tmp, lvItem.cchTextMax );
	//					lvItem.pszText = tmp;
	//					ListView_SetItem( hwnd_, &lvItem );
	//					delete [] tmp;
	//				}
	//			}
	//		}
	//		break;
//
//			default: {
//
//			}
//			break;
//		}
	

	Object* source = event->getSource();
	if ( NULL != source ){
		ListItem* item = dynamic_cast<ListItem*>(source);
		if ( NULL != item ){

			if ( System::isUnicodeEnabled() ) {
				LVITEMW lvItem;
				memset( &lvItem, 0, sizeof(lvItem) );
				lvItem.mask = LVIF_TEXT | LVIF_IMAGE ;
				lvItem.iImage = item->getImageIndex();
				//String caption = item->getCaption();
				//lvItem.cchTextMax = caption.size()+1;
				lvItem.iItem = item->getIndex();

				//VCFChar* tmp = new VCFChar[lvItem.cchTextMax];
				//memset( tmp, 0, lvItem.cchTextMax * sizeof(VCFChar) );

				//caption.copy( tmp, lvItem.cchTextMax-1 );
				lvItem.pszText = LPSTR_TEXTCALLBACKW;
				SendMessage( hwnd_, LVM_SETITEMW, 0, (LPARAM)&lvItem );

				//delete [] tmp;
			}
			else {
				LVITEMA lvItem;
				memset( &lvItem, 0, sizeof(lvItem) );
				lvItem.mask = LVIF_TEXT | LVIF_IMAGE ;
				lvItem.iImage = item->getImageIndex();

				//AnsiString caption = item->getCaption();

				//lvItem.cchTextMax = caption.size()+1;
				lvItem.iItem = item->getIndex();

				//char* tmp = new char[lvItem.cchTextMax];
				//memset( tmp, 0, lvItem.cchTextMax * sizeof(char) );
				//caption.copy( tmp, lvItem.cchTextMax-1 );
				lvItem.pszText = LPSTR_TEXTCALLBACKA;
				SendMessage( hwnd_, LVM_SETITEMA, 0, (LPARAM)&lvItem );
				//delete [] tmp;
			}


		}
	}
}
*/

/*
void Win32Listview::onItemSelected( ItemEvent* event )
{

	if ( !internalMessage_ ) {
		ListItem* item = (ListItem*)event->getSource();
		if ( true == item->isSelected() ) {
			ListView_SetItemState( hwnd_, item->getIndex(),
				LVIS_SELECTED, LVIS_SELECTED );
		}
		else {
			ListView_SetItemState( hwnd_, item->getIndex(), 0, LVIS_SELECTED );
		}
	}

}

void Win32Listview::onItemAdded( ItemEvent* event )
{

}

void Win32Listview::onItemDeleted( ItemEvent* event )
{

}
*/

void Win32Listview::setColumnWidth( const uint32& index, const double& width, ColumnAutosizeType type )
{
	//don't do this if we are tracking
	if ( false == headerControlIsTracking_ ) {
		/* autoresizing added by Marcello */
		int err = 0;
		switch ( type ) {
		case casAutoSizeNone:
			err = ListView_SetColumnWidth( hwnd_, index, (int32)width );
			break;
		case casAutoSizeColumns:
			err = ListView_SetColumnWidth( hwnd_, index, (int32)LVSCW_AUTOSIZE );
			break;
		case casAutoSizeHeaders:
			err = ListView_SetColumnWidth( hwnd_, index, (int32)LVSCW_AUTOSIZE_USEHEADER  );
			break;
		case casAutoSizeColumnsAndHeaders:
			err = ListView_SetColumnWidth( hwnd_, index, (int32)LVSCW_AUTOSIZE_USEHEADER );
			break;
		default:
			err = ListView_SetColumnWidth( hwnd_, index, (int32)LVSCW_AUTOSIZE_USEHEADER );
			break;
		}
	}
}

double Win32Listview::getColumnWidth( const uint32& index )
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

/*
void Win32Listview::setColumnName( const uint32& index, const String& columnName )
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
		memset(tmp,0,(columnInfo.cchTextMax+1)*sizeof(char));
		tmpColName.copy( tmp, columnInfo.cchTextMax );

		columnInfo.pszText = tmp;


		SendMessage( hwnd_, LVM_SETCOLUMNA, (WPARAM)index, (LPARAM)&columnInfo );

		delete [] tmp;
	}




}

String Win32Listview::getColumnName( const uint32& index )
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
*/

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
/*
void Win32Listview::sort( ItemSort* itemSortFunctor )
{
	int err = ListView_SortItems( hwnd_, Win32Listview::sortFunc, (LPARAM)itemSortFunctor );
}
*/

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
			ColorPixels pix(imageList->getMasterImage());
			SysPixelType* bits = pix;
			int sz = win32Img->getWidth() * win32Img->getHeight();
			unsigned char* oldAlpaVals = new unsigned char[sz];
			do {
				sz --;
				oldAlpaVals[sz] = bits[sz].a;
				bits[sz].a = 0;
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

			ColorPixels pix(event->getImage());
			SysPixelType* bits = pix;
			int sz = win32Img->getWidth() * win32Img->getHeight();
			unsigned char* oldAlpaVals = new unsigned char[sz];
			do {
				sz --;
				oldAlpaVals[sz] = bits[sz].a;
				bits[sz].a = 0;
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
				bits[sz].a = oldAlpaVals[sz];
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
			ColorPixels pix(imageList->getMasterImage());
			SysPixelType* bits = pix;
			int sz = win32Img->getWidth() * win32Img->getHeight();
			unsigned char* oldAlpaVals = new unsigned char[sz];
			do {
				sz --;
				oldAlpaVals[sz] = bits[sz].a;
				bits[sz].a = 0;
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
				bits[sz].a = oldAlpaVals[sz];
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
										ILC_COLOR24|ILC_MASK, imageList->getImageCount(), 4 );

			//ImageList_Create( imageList->getImageWidth(), imageList->getImageHeight(),
								//		ILC_COLOR32, imageList->getImageCount(), 4 );

		Win32Image* win32Img = (Win32Image*)imageList->getMasterImage();
		ColorPixels pix(imageList->getMasterImage());
		SysPixelType* bits = pix;
		int sz = win32Img->getWidth() * win32Img->getHeight();
		unsigned char* oldAlpaVals = new unsigned char[sz];
		do {
			sz --;
			oldAlpaVals[sz] = bits[sz].a;
			bits[sz].a = 0;
		} while( sz > 0 );

		COLORREF transparentColor = RGB(0,0,0);
		if ( win32Img->isTransparent() ) {
			Color* c = win32Img->getTransparencyColor();
			transparentColor = RGB( c->getRed() * 255, c->getGreen() * 255, c->getBlue() * 255 );
		}
		else {
			transparentColor = ::GetPixel( win32Img->getDC(), 0, 0 );
		}


		HBITMAP hbmImage = win32Img->getBitmap();

		HBITMAP hCopyImg = (HBITMAP)CopyImage( hbmImage, IMAGE_BITMAP, 0, 0, NULL );

		if ( NULL == hCopyImg ) {
			//error - throw exception
		}

		int err = ImageList_AddMasked( largeImageListCtrl_, hCopyImg, transparentColor );
		if ( err < 0 ) {
			//error condition !
		}

		::DeleteObject( hCopyImg );
		sz = win32Img->getWidth() * win32Img->getHeight();
		do {
			sz --;
			bits[sz].a = oldAlpaVals[sz];
		} while( sz > 0 );

		delete [] oldAlpaVals;


		ListView_SetImageList( hwnd_, largeImageListCtrl_, LVSIL_NORMAL );

		CallBack* imgListHandler = getCallback( "LargeImageListHandler" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ClassProcedure1<ImageListEvent*,Win32Listview>(this, &Win32Listview::onLargeImageListImageChanged, "LargeImageListHandler" );

		}

		imageList->SizeChanged +=  imgListHandler;
		imageList->ImageAdded += imgListHandler;
		imageList->ImageDeleted += imgListHandler;

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
		ColorPixels pix(win32Img);
		SysPixelType* bits = pix;
		int sz = win32Img->getWidth() * win32Img->getHeight();
		unsigned char* oldAlpaVals = new unsigned char[sz];
		do {
			sz --;
			oldAlpaVals[sz] = bits[sz].a;
			bits[sz].a = 0;
		} while( sz > 0 );

		HBITMAP hbmImage = win32Img->getBitmap();

		HBITMAP hCopyImg = (HBITMAP)CopyImage( hbmImage, IMAGE_BITMAP, 0, 0, NULL );

		COLORREF transparentColor = RGB(0,0,0);
		if ( win32Img->isTransparent() ) {
			Color* c = win32Img->getTransparencyColor();
			transparentColor = RGB( c->getRed() * 255, c->getGreen() * 255, c->getBlue() * 255 );
		}
		else {
			transparentColor = ::GetPixel( win32Img->getDC(), 0, 0 );
		}

		int err = ImageList_AddMasked( smallImageListCtrl_, hCopyImg, transparentColor );
		if ( err < 0 ) {
			//error condition !
		}


		::DeleteObject( hCopyImg );
		sz = win32Img->getWidth() * win32Img->getHeight();
		do {
			sz --;
			bits[sz].a = oldAlpaVals[sz];
		} while( sz > 0 );

		delete [] oldAlpaVals;

		ListView_SetImageList( hwnd_, smallImageListCtrl_, LVSIL_SMALL );

		CallBack* imgListHandler = getCallback( "SmallImageListHandler" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ClassProcedure1<ImageListEvent*,Win32Listview>(this, &Win32Listview::onSmallImageListImageChanged, "SmallImageListHandler" );

		}

		imageList->SizeChanged+=  imgListHandler;
	}
}

Rect Win32Listview::getItemImageRect( const uint32& index )
{
	Rect result;

	return result;
}

uint32 Win32Listview::hitTest( const Point& point )
{
	uint32 result = ListModel::InvalidIndex;

	LVHITTESTINFO hitTestInfo;
	memset( &hitTestInfo, 0, sizeof(LVHITTESTINFO) );
	hitTestInfo.pt.x = (int32)point.x_;
	hitTestInfo.pt.y = (int32)point.y_;

	int index = ListView_HitTest( hwnd_, &hitTestInfo );
	if ( index > -1 ) {
		/*
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
		*/

		result = index;
	}

	return result;
}

int32 Win32Listview::getDisplayOptions()
{
	int32 result = lvdoDefault;
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

void Win32Listview::setDisplayOptions( const int32& displayOptions )
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

void Win32Listview::onCtrlModelChanged( Event* e )
{
 	Model* model = listviewControl_->getViewModel();
	if ( NULL != model ) {
		model->ModelChanged += getCallback( "Win32Listview::onListModelChanged" );

		ListModel* lm = (ListModel*)model;		
		ListView_SetItemCountEx( hwnd_, lm->getCount(), LVSICF_NOINVALIDATEALL );				
		StringUtils::trace( Format("Win32Listview::onCtrlModelChanged(): Added %d items to hwnd: %p\n") % lm->getCount() % hwnd_ );
		InvalidateRect( hwnd_, NULL, TRUE );


		model =  listviewControl_->getColumnModel();
		model->ModelChanged += getCallback( "Win32Listview::onColumnModelChanged" );

		ColumnModel* cm = (ColumnModel*)model;
		cm->ItemAdded += 
			getCallback( "Win32Listview::onColumnModelAdded" );

		cm->ItemRemoved += 
			getCallback( "Win32Listview::onColumnModelRemoved" );


		HWND header = ListView_GetHeader(hwnd_);
		int cc = Header_GetItemCount(header);		

		for (int i=cc-1;i>=0;i-- ) {
			//can't delete column 0
			SendMessage( hwnd_, LVM_DELETECOLUMN, i, 0 );
			//Weird - don't use the code below! It causes 
			//the items in the column to have 0 width! Despite 
			//being assigned a width value when the column is assigned.
			//Header_DeleteItem(header,i);
		}

		cc = Header_GetItemCount(header);

		

		//build up colums
		if ( !cm->isEmpty() ) {
			uint32 count = cm->getCount();
			ListModelEvent lme(cm);

			for (uint32 i=0;i<count;i++ ) {

				if ( cc == 1 && i == 0 ) {
					if ( NULL != header ) {
						double width = 100;
						HDITEMW headerItem;
						memset( &headerItem, 0, sizeof(headerItem) );
						headerItem.mask = HDI_LPARAM | HDI_TEXT | HDI_IMAGE | HDI_WIDTH | HDI_FORMAT;				

						headerItem.lParam = (LPARAM)lme.index;
						headerItem.iImage = I_IMAGECALLBACK;
						headerItem.pszText = LPSTR_TEXTCALLBACKW;	
						headerItem.cxy = width;
						headerItem.fmt = HDF_LEFT | HDF_STRING;	

						int err = SendMessage( header, HDM_SETITEMW, (WPARAM)lme.index, (LPARAM)&headerItem );
					}

				}
				else {
					lme.index = i;
					onColumnModelAdded(&lme);
				}
			}
		}
	}
	
}

void Win32Listview::onListModelChanged( Event* e )
{
	ListModel* lm = (ListModel*)e->getSource();

	int count = ListView_GetItemCount( hwnd_ );
	

	if ( count != lm->getCount() ) {
		ListView_SetItemCountEx( hwnd_, lm->getCount(), LVSICF_NOINVALIDATEALL );

	}

	InvalidateRect( hwnd_, NULL, TRUE );
}

void Win32Listview::onColumnModelAdded( Event* e )
{
	double width = 100;

	ListModelEvent* lme = (ListModelEvent*)e;
	
	if ( System::isUnicodeEnabled() ) {
		LVCOLUMNW column;
		memset( &column, 0, sizeof(column) );
		column.mask = LVCF_FMT | LVCF_WIDTH;
		column.cx = (int32)width;
		column.fmt = LVCFMT_LEFT;
		int res = SendMessage( hwnd_, LVM_INSERTCOLUMNW, (WPARAM)lme->index, (LPARAM)&column );
		if ( res >= 0 ) {
			HWND header = ListView_GetHeader( hwnd_ );
			
			registerHeaderWndProc();
			
			if ( NULL != header ) {
				HDITEMW headerItem;
				memset( &headerItem, 0, sizeof(headerItem) );
				headerItem.mask = HDI_LPARAM | HDI_TEXT | HDI_IMAGE | HDI_WIDTH | HDI_FORMAT;				
				
				headerItem.lParam = (LPARAM)lme->index;
				headerItem.iImage = I_IMAGECALLBACK;
				headerItem.pszText = LPSTR_TEXTCALLBACKW;	
				headerItem.cxy = width;
				headerItem.fmt = HDF_LEFT | HDF_STRING;	
				
				int err = SendMessage( header, HDM_SETITEMW, (WPARAM)lme->index, (LPARAM)&headerItem );
			}
		}
	}
	else {
		LVCOLUMNA column;
		memset( &column, 0, sizeof(column) );
		column.mask = LVCF_FMT | LVCF_WIDTH;
		column.cx = (int32)width;
		column.fmt = LVCFMT_LEFT;
		
		if ( SendMessage( hwnd_, LVM_INSERTCOLUMNA, (WPARAM)lme->index, (LPARAM)&column ) >= 0 ) {
			HWND header = ListView_GetHeader( hwnd_ );
			
			registerHeaderWndProc();
			
			if ( NULL != header ) {
				HDITEMA headerItem;
				memset( &headerItem, 0, sizeof(headerItem) );
				headerItem.mask = HDI_LPARAM | HDI_TEXT | HDI_IMAGE | HDI_WIDTH | HDI_FORMAT;
				
				headerItem.lParam = (LPARAM)lme->index;
				headerItem.iImage = I_IMAGECALLBACK;
				headerItem.pszText = LPSTR_TEXTCALLBACKA;	
				headerItem.cxy = width;
				headerItem.fmt = HDF_LEFT | HDF_STRING;	
				
				int err = SendMessage( header, HDM_SETITEMA, (WPARAM)lme->index, (LPARAM)&headerItem );
			}
		}
	}
}

void Win32Listview::onColumnModelRemoved( Event* e )
{
	ListModelEvent* lme = (ListModelEvent*)e;
	int err = ListView_DeleteColumn( hwnd_, lme->index );
}

void Win32Listview::onColumnModelChanged( Event* e )
{
	HWND header = ListView_GetHeader(hwnd_);

	if ( NULL != header ) {
		InvalidateRect( header, NULL, TRUE );
	}
}

TextAlignmentType Win32Listview::getColumnTextAlignment( const uint32& index )
{
	TextAlignmentType result = TextAlignmentType();

	HWND header = ListView_GetHeader( hwnd_ );
	if ( NULL != header ) {
		HDITEM headerItem;
		memset( &headerItem, 0, sizeof(HDITEM) );
		headerItem.mask = HDI_FORMAT;

		if ( Header_GetItem( header, index, &headerItem ) ) {
			if ( headerItem.fmt & HDF_LEFT ) {
				result = taTextLeft;
			}
			else if ( headerItem.fmt & HDF_CENTER ) {
				result = taTextCenter;
			}
			else if ( headerItem.fmt & HDF_RIGHT ) {
				result = taTextRight;
			}
		}
	}

	return result;
}

void Win32Listview::setColumnTextAlignment( const uint32& index, const TextAlignmentType& val )
{
	HWND header = ListView_GetHeader( hwnd_ );
	if ( NULL != header ) {
		HDITEM headerItem;
		memset( &headerItem, 0, sizeof(HDITEM) );
		headerItem.mask = HDI_FORMAT;

		if ( val == taTextLeft ) {
			headerItem.fmt |= HDF_LEFT;
		}
		else if ( val == taTextCenter ) {
			headerItem.fmt |= HDF_CENTER;				
		}
		else if ( val == taTextRight ) {
			headerItem.fmt |= HDF_RIGHT;
		}

		Header_SetItem( header, index, &headerItem );
	}
}

/**
$Id$
*/
