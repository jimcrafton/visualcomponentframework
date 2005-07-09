//Win32Tree.cpp

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
#include "vcf/ApplicationKit/Win32Tree.h"
#include "vcf/ApplicationKit/TreeControl.h"
#include "vcf/ApplicationKit/DefaultTreeItem.h"


/**
this is redifined here because the mingw version is WRONG! (or the MS iversion is
wrong, depends on how you look at it :) ).
*/

#if (_WIN32_IE >= 0x0400)
typedef struct tagNMCUSTOMDRAWINFO__ {
    NMHDR  hdr;
    DWORD  dwDrawStage;
    HDC    hdc;
    RECT   rc;
    DWORD  dwItemSpec;
    UINT   uItemState;
    LPARAM lItemlParam;
} NMCUSTOMDRAW__, FAR * LPNMCUSTOMDRAW__;

#endif


typedef struct tagNMTVCUSTOMDRAW__ {
    NMCUSTOMDRAW__ nmcd;
    COLORREF clrText;
    COLORREF clrTextBk;
#if (_WIN32_IE >= 0x0400)
    int iLevel;
#endif
} NMTVCUSTOMDRAW__, *LPNMTVCUSTOMDRAW__;



#ifdef __GNUWIN32__

#if (_WIN32_IE >= 0x0300)
#define LPTV_HITTESTINFO   LPTVHITTESTINFO
#define   TV_HITTESTINFO     TVHITTESTINFO
#else
#define tagTVHITTESTINFO    _TV_HITTESTINFO
#define    TVHITTESTINFO     TV_HITTESTINFO
#define  LPTVHITTESTINFO   LPTV_HITTESTINFO
#endif

typedef struct tagTVHITTESTINFO {
    POINT       pt;
    UINT        flags;
    HTREEITEM   hItem;
} TVHITTESTINFO, FAR *LPTVHITTESTINFO;


#if (_WIN32_IE >= 0x0400)
#define TVN_GETINFOTIPA         (TVN_FIRST-13)
#define TVN_GETINFOTIPW         (TVN_FIRST-14)
#define TVN_SINGLEEXPAND        (TVN_FIRST-15)
#endif // 0x400



#if (_WIN32_IE >= 0x0400)

// for tooltips

typedef struct tagNMTVGETINFOTIPA
{
    NMHDR hdr;
    LPSTR pszText;
    int cchTextMax;
    HTREEITEM hItem;
    LPARAM lParam;
} NMTVGETINFOTIPA, *LPNMTVGETINFOTIPA;

typedef struct tagNMTVGETINFOTIPW
{
    NMHDR hdr;
    LPWSTR pszText;
    int cchTextMax;
    HTREEITEM hItem;
    LPARAM lParam;
} NMTVGETINFOTIPW, *LPNMTVGETINFOTIPW;


#ifdef UNICODE
	#define TVN_GETINFOTIP          TVN_GETINFOTIPW
	#define NMTVGETINFOTIP          NMTVGETINFOTIPW
	#define LPNMTVGETINFOTIP        LPNMTVGETINFOTIPW
#else
	#define TVN_GETINFOTIP          TVN_GETINFOTIPA
	#define NMTVGETINFOTIP          NMTVGETINFOTIPA
	#define LPNMTVGETINFOTIP        LPNMTVGETINFOTIPA
#endif

#endif //_WIN32_IE


#endif //__GNUWIN32__





using namespace VCFWin32;
using namespace VCF;

Win32Tree::Win32Tree( TreeControl* tree ):
	AbstractWin32Component( tree ),
	treeControl_( tree ),
	imageListCtrl_(NULL),
	stateImageListCtrl_(NULL),
	internalTreeItemExpanded_(false)
{

}

Win32Tree::~Win32Tree()
{
	if ( NULL != imageListCtrl_ ) {
		BOOL err = ImageList_Destroy( imageListCtrl_ );
	}

	if ( NULL != stateImageListCtrl_ ) {
		BOOL err = ImageList_Destroy( stateImageListCtrl_ );
	}
}

void Win32Tree::create( Control* owningControl )
{
	init();

	CreateParams params = createParams();

	backColor_ = *treeControl_->getColor();

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();

	String className = getClassName();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
										 WC_TREEVIEWW,
										 NULL,
										 params.first,
										 0,
										 0,
										 1,
										 1,
										 parent,
										 NULL,
										 ::GetModuleHandleW(NULL),
										 NULL );
	}
	else {
		hwnd_ = ::CreateWindowExA( params.second,
										 WC_TREEVIEWA,
										 NULL,
										 params.first,
										 0,
										 0,
										 1,
										 1,
										 parent,
										 NULL,
										 ::GetModuleHandleA(NULL),
										 NULL );
	}


	if ( NULL != hwnd_ ){
		Win32Object::registerWin32Object( this );

		subclassWindow();

		setFont( owningControl->getFont() );

		treeControl_ = (TreeControl*)owningControl;
		peerControl_ = owningControl;

		peerControl_->ControlModelChanged +=
			new GenericEventHandler<Win32Tree>( this, &Win32Tree::onControlModelChanged, "Win32Tree::onControlModelChanged" );

		COLORREF backColor = backColor_.getColorRef32();

		TreeView_SetBkColor( hwnd_, backColor );
	}
	else {
		//throw exception
	}

	setCreated( true );
}

void Win32Tree::init()
{


	itemAddedHandler_ =
		new ItemEventHandler<Win32Tree>( this, &Win32Tree::onItemAdded, "Win32Tree::onItemAdded" );

	itemDeletedHandler_ =
		new ItemEventHandler<Win32Tree>( this, &Win32Tree::onItemDeleted, "Win32Tree::onItemDeleted" );

	itemChangedHandler_ =
		new ItemEventHandler<Win32Tree>( this, &Win32Tree::onItemChanged, "Win32Tree::onItemChanged" );

	itemSelectedHandler_ =
		new ItemEventHandler<Win32Tree>( this, &Win32Tree::onItemSelected, "Win32Tree::onItemSelected" );

	itemPaintedHandler_ =
		new ItemEventHandler<Win32Tree>( this, &Win32Tree::onItemPaint, "Win32Tree::onItemPaint" );

}

Win32Object::CreateParams Win32Tree::createParams()
{
	Win32Object::CreateParams result;


	result.first = BORDERED_VIEW | TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT | /*TVS_NOTOOLTIPS | */ TVS_SHOWSELALWAYS;

	result.first &= ~WS_BORDER;
	result.first &= ~WS_VISIBLE;

	result.first |= WS_HSCROLL | WS_VSCROLL;

	result.first |= TVS_DISABLEDRAGDROP;
	result.second = 0;


	return result;
}

TreeModel* Win32Tree::getTreeModel()
{
	return NULL;
}

void Win32Tree::setTreeModel( TreeModel* model )
{

}

double Win32Tree::getItemIndent()
{
	return TreeView_GetIndent( hwnd_ );
}

void Win32Tree::setItemIndent( const double& indent )
{
	BOOL err = TreeView_SetIndent( hwnd_, (int)indent );
}

ImageList* Win32Tree::getImageList()
{
	return NULL;
}

void Win32Tree::setImageList( ImageList* imageList )
{

	if ( NULL != imageListCtrl_ ) {
		BOOL err = ImageList_Destroy( imageListCtrl_ );
	}
	imageListCtrl_ = NULL;
	TreeView_SetImageList( hwnd_, imageListCtrl_, TVSIL_NORMAL );

	if ( imageList != NULL ) {
		imageListCtrl_ = ImageList_Create( imageList->getImageWidth(), imageList->getImageHeight(),
										ILC_COLOR24|ILC_MASK, imageList->getImageCount(), 4 );

		Image* masterImage = imageList->getMasterImage();
		Win32Image* win32Img = (Win32Image*)masterImage;

		/*
		JC added this cause it appears that for 32bit images the alpa val
		matters! If it's not set back to 0 then the transparency affect doesn't
		work? Bizarre
		*/
		SysPixelType* pix = win32Img->getImageBits()->pixels_;
		int sz = win32Img->getWidth() * win32Img->getHeight();
		unsigned char* oldAlpaVals = new unsigned char[sz];
		do {
			sz --;
			oldAlpaVals[sz] = pix[sz].a;
			pix[sz].a = 0;
		} while( sz > 0 );

		HBITMAP hbmImage = win32Img->getBitmap();

		COLORREF transparentColor = RGB(0,0,0);
		if ( masterImage->isTransparent() ) {
			Color* c = masterImage->getTransparencyColor();
			transparentColor = RGB( c->getRed() * 255, c->getGreen() * 255, c->getBlue() * 255 );
		}
		else {
			transparentColor = ::GetPixel( win32Img->getDC(), 0, 0 );
		}

		//JEC 11/05/2002 currently on NT4 this call seems to fail, returning the same
		//HBITMAP value as hbmImage. This is running on NT4 in VMWare perhaps this is
		//some weird bug within VMWare? Need to test this on a "real" NT4 install
		HBITMAP hBMPcopy = (HBITMAP)CopyImage( hbmImage, IMAGE_BITMAP,
												0,
												0,
												NULL );

		int err = ImageList_AddMasked( imageListCtrl_, hBMPcopy, transparentColor );
		if ( err < 0 ) {
			//error condition !
		}

		DeleteObject( hBMPcopy );
		sz = win32Img->getWidth() * win32Img->getHeight();
		do {
			sz --;
			pix[sz].a = oldAlpaVals[sz];
		} while( sz > 0 );

		delete [] oldAlpaVals;


		TreeView_SetImageList( hwnd_, imageListCtrl_, TVSIL_NORMAL );


		EventHandler* imgListHandler = getEventHandler( "Win32Tree::onImageListImageChanged" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ImageListEventHandler<Win32Tree>(this, &Win32Tree::onImageListImageChanged, "Win32Tree::onImageListImageChanged" );

		}
		imageList->SizeChanged.addHandler( imgListHandler );
		imageList->ImageAdded.addHandler( imgListHandler );
		imageList->ImageDeleted.addHandler( imgListHandler );
	}
}

bool Win32Tree::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = 0;
	wndProcResult = 0;


	switch ( message ) {
		case WM_PAINT:{
			//check to see if the font needs updating
			checkForFontChange();

			PAINTSTRUCT ps;

			HDC dc = BeginPaint( hwnd_, &ps );

			RECT paintRect;
			GetClientRect( hwnd_, &paintRect );

			if ( NULL == memDC_ ) {
				//create here
				HDC tmpDC = ::GetDC(0);
				memDC_ = ::CreateCompatibleDC( tmpDC );
				::ReleaseDC( 0,	tmpDC );
			}


			VCF::GraphicsContext* ctx = peerControl_->getContext();

			ctx->setViewableBounds( Rect(paintRect.left, paintRect.top,
									paintRect.right, paintRect.bottom ) );

			memBMP_ = ::CreateCompatibleBitmap( dc,
					paintRect.right - paintRect.left,
					paintRect.bottom - paintRect.top );


			memDCState_ = ::SaveDC( memDC_ );
			originalMemBMP_ = (HBITMAP)::SelectObject( memDC_, memBMP_ );

			POINT oldOrg = {0};
			::SetViewportOrgEx( memDC_, -paintRect.left, -paintRect.top, &oldOrg );

			Color* color = peerControl_->getColor();
			COLORREF backColor = color->getColorRef32();

			HBRUSH bkBrush = CreateSolidBrush( backColor );
			FillRect( memDC_, &paintRect, bkBrush );
			DeleteObject( bkBrush );


			ctx->getPeer()->setContextID( (OSHandleID)memDC_ );


			((ControlGraphicsContext*)ctx)->setOwningControl( NULL );

			int gcs = ctx->saveState();

			//paint the control here - double buffered
			peerControl_->paint( ctx );


			ctx->restoreState( gcs );


			//reset back to original origin
			::SetViewportOrgEx( memDC_, -paintRect.left, -paintRect.top, &oldOrg );

			//let the tree control's DefWndProc do windwos painting

			defaultWndProcedure( WM_PAINT, (WPARAM)memDC_, 0 );


			//NOW reset the owning control of teh graphics context here
			((ControlGraphicsContext*)ctx)->setOwningControl( peerControl_ );

			::BitBlt( dc, paintRect.left, paintRect.top,
					  paintRect.right - paintRect.left,
					  paintRect.bottom - paintRect.top,
					  memDC_, paintRect.left, paintRect.top, SRCCOPY );

			::RestoreDC ( memDC_, memDCState_ );

			::DeleteObject( memBMP_ );

			memBMP_ = NULL;
			originalMemBMP_ = NULL;
			memDCState_ = 0;




			EndPaint( hwnd_, &ps );

			wndProcResult = 1;
			result = true;
		}
		break;

		case WM_NCCALCSIZE: {
			wndProcResult = handleNCCalcSize( wParam, lParam );
			result = true;
		}
		break;

		case WM_NCPAINT: {
			wndProcResult = handleNCPaint( wParam, lParam );
			result = true;
		}
		break;

		case WM_ERASEBKGND :{
			Color* color = treeControl_->getColor();
			if ( backColor_ != *color ) {
				COLORREF backColor = color->getColorRef32();
				TreeView_SetBkColor( hwnd_, backColor );

				backColor_ = *color;
			}


			wndProcResult = 0;
			result = true;
		}
		break;

		case WM_LBUTTONDOWN : {


			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );



			TVHITTESTINFO hitTestInfo;
			memset( &hitTestInfo, 0, sizeof(TVHITTESTINFO) );

			hitTestInfo.pt.x = Win32Utils::getXFromLParam( lParam );
			hitTestInfo.pt.y = Win32Utils::getYFromLParam( lParam );
			HTREEITEM hItem = TreeView_HitTest( hwnd_, &hitTestInfo );
			if ( NULL != hItem ) {
				if( hitTestInfo.flags & TVHT_ONITEMSTATEICON ) {
					TVITEM tvItem;
					memset( &tvItem, 0, sizeof(TVITEM) );
					tvItem.mask = TVIF_PARAM | TVIF_HANDLE ;
					tvItem.hItem = hItem;
					if ( TreeView_GetItem( hwnd_, &tvItem ) ) {
						TreeItem* item = (TreeItem*)tvItem.lParam;

						ItemEvent event( item, TreeControl::ITEM_STATECHANGE_REQUESTED );

						treeControl_->handleEvent( &event );
					}
				}
			}

		}
		break;

		case WM_CREATE:{
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_LBUTTONDBLCLK: case WM_MBUTTONDBLCLK: case WM_RBUTTONDBLCLK:{
			Win32MSG msg( hwnd_, message, wParam, lParam, peerControl_ );
			Event* event = UIToolkit::createEventFromNativeOSEventData( &msg );


			if ( NULL != event && (peerControl_->getComponentState() != Component::csDestroying) ) {
				peerControl_->handleEvent( event );

				event->free();
			}

			//DO NOT, REPEAT: DO NOT allow the DefaultWndProc to get called!
			wndProcResult = 1;
			result = true;
		}
		break;


		case TVN_BEGINDRAGW:{
			NMTREEVIEWW* treeview = (NMTREEVIEWW*)lParam ;
			TreeItem* item = (TreeItem*)treeview->itemNew.lParam;

			if ( NULL != item ) {
				Point pt( treeview->ptDrag.x, treeview->ptDrag.y );

				TreeItem* oldItem = treeControl_->getSelectedItem();
				if ( item != oldItem ) {
					//hmm, we haven't selected this item before, so
					//let's go ahead and make it selected now
					//we do this because the TVN_SELECTIONCHANGED
					//won't get called at this point

					item->setSelected( true );

					ItemEvent event( treeControl_, TREEITEM_SELECTED );

					event.setUserData( (void*)item );

					event.setPoint( &pt );

					treeControl_->handleEvent( &event );

					if ( NULL != oldItem ) {
						oldItem->setSelected( false );
					}
				}

				SHORT keyState = GetKeyState( VK_SHIFT );
				ulong32 keyMask = kmUndefined;
				if ( (keyState >> 15) ) {
					keyMask |= kmShift;
				}
				keyState = GetKeyState( VK_CONTROL );
				if ( (keyState >> 15) ) {
					keyMask |= kmCtrl;
				}

				keyState = GetKeyState( VK_MENU );
				if ( (keyState >> 15) ) {
					keyMask |= kmAlt;
				}

				VCF::MouseEvent event( treeControl_, Control::MOUSE_MOVE,
										mbmLeftButton, keyMask, &pt );

				treeControl_->beginDragDrop( &event );
			}
		}
		break;

		case TVN_BEGINDRAGA:{
			NMTREEVIEWA* treeview = (NMTREEVIEWA*)lParam ;
			TreeItem* item = (TreeItem*)treeview->itemNew.lParam;

			if ( NULL != item ) {
				Point pt( treeview->ptDrag.x, treeview->ptDrag.y );

				TreeItem* oldItem = treeControl_->getSelectedItem();
				if ( item != oldItem ) {
					//hmm, we haven't selected this item before, so
					//let's go ahead and make it selected now
					//we do this because the TVN_SELECTIONCHANGED
					//won't get called at this point

					item->setSelected( true );

					ItemEvent event( treeControl_, TREEITEM_SELECTED );

					event.setUserData( (void*)item );

					event.setPoint( &pt );

					treeControl_->handleEvent( &event );

					if ( NULL != oldItem ) {
						oldItem->setSelected( false );
					}
				}

				SHORT keyState = GetKeyState( VK_SHIFT );
				ulong32 keyMask = kmUndefined;
				if ( (keyState >> 15) ) {
					keyMask |= kmShift;
				}
				keyState = GetKeyState( VK_CONTROL );
				if ( (keyState >> 15) ) {
					keyMask |= kmCtrl;
				}

				keyState = GetKeyState( VK_MENU );
				if ( (keyState >> 15) ) {
					keyMask |= kmAlt;
				}

				VCF::MouseEvent event( treeControl_, Control::MOUSE_MOVE,
										mbmLeftButton, keyMask, &pt );

				treeControl_->beginDragDrop( &event );

			}
		}
		break;

		case TVN_BEGINLABELEDIT:{

		}
		break;

		case TVN_BEGINRDRAG:{			

		}
		break;

		case TVN_DELETEITEM:{

		}
		break;


		case TVN_ENDLABELEDITW:{
			LPNMTVDISPINFOW lptvdi = (LPNMTVDISPINFOW) lParam ;
			if ( lptvdi->item.pszText ) {
				String text = lptvdi->item.pszText;
				TreeItem* item = (TreeItem*)lptvdi->item.lParam;
				item->setCaption( text );

				wndProcResult = 1;
				result = true;
			}
			return false;
		}
		break;

		case TVN_ENDLABELEDITA:{
			LPNMTVDISPINFOA lptvdi = (LPNMTVDISPINFOA) lParam ;
			if ( lptvdi->item.pszText ) {
				AnsiString text = lptvdi->item.pszText;
				TreeItem* item = (TreeItem*)lptvdi->item.lParam;
				item->setCaption( text );
				wndProcResult = 1;
				result = true;
			}
			return false;
		}
		break;

		case TVN_GETDISPINFOW: {
			LPNMTVDISPINFOW lptvdi = (LPNMTVDISPINFOW) lParam ;
			if ( lptvdi->item.mask & TVIF_TEXT ) {
				static String text;
				TreeItem* item = (TreeItem*)lptvdi->item.lParam;
				if ( NULL != item ) {
					text = item->getCaption();
					text.copy( lptvdi->item.pszText, text.size() );
					lptvdi->item.pszText[text.size()] = 0;
				}
			}
		}
		break;

		case TVN_GETDISPINFOA: {
			LPNMTVDISPINFOA lptvdi = (LPNMTVDISPINFOA) lParam ;
			if ( lptvdi->item.mask & TVIF_TEXT ) {
				static AnsiString text;
				TreeItem* item = (TreeItem*)lptvdi->item.lParam;
				if ( NULL != item ) {
					text = item->getCaption();

					text.copy( lptvdi->item.pszText, text.size() );
					lptvdi->item.pszText[text.size()] = 0;
				}
			}
		}
		break;

		case TVN_GETINFOTIP:{

		}
		break;

		case TVN_ITEMEXPANDEDA:{
			internalTreeItemExpanded_ = true;
			NMTREEVIEWA* treeview = (NMTREEVIEWA*)lParam;
			TreeItem* item = (TreeItem*)treeview->itemNew.lParam;
			if ( NULL != item ) {

				if ( treeview->action & TVE_EXPAND ) {
					item->expand( true );
				}
				else if ( treeview->action & TVE_COLLAPSE ) {
					item->expand( false );
				}

				POINT tmpPt = {0,0};
				GetCursorPos( &tmpPt );
				::ScreenToClient( hwnd_, &tmpPt );
				ItemEvent event( treeControl_, TREEITEM_EXPANDED );

				event.setUserData( (void*)item );

				Point pt( tmpPt.x, tmpPt.y );
				event.setPoint( &pt );

				treeControl_->handleEvent( &event );
			}
			internalTreeItemExpanded_ = false;
		}
		break;

		case TVN_ITEMEXPANDEDW:{
			internalTreeItemExpanded_ = true;
			NMTREEVIEWW* treeview = (NMTREEVIEWW*)lParam;
			TreeItem* item = (TreeItem*)treeview->itemNew.lParam;

			if ( NULL != item ) {

				if ( treeview->action & TVE_EXPAND ) {
					item->expand( true );
				}
				else if ( treeview->action & TVE_COLLAPSE ) {
					item->expand( false );
				}

				POINT tmpPt = {0,0};
				GetCursorPos( &tmpPt );
				::ScreenToClient( hwnd_, &tmpPt );
				ItemEvent event( treeControl_, TREEITEM_EXPANDED );

				event.setUserData( (void*)item );

				Point pt( tmpPt.x, tmpPt.y );
				event.setPoint( &pt );

				treeControl_->handleEvent( &event );
			}
			internalTreeItemExpanded_ = false;
		}
		break;

		case TVN_ITEMEXPANDING:{

		}
		break;

		case TVN_KEYDOWN:{

		}
		break;

		case TVN_SELCHANGEDW:{
			NMTREEVIEWW* treeview = (NMTREEVIEWW*)lParam;
			TreeItem* item = (TreeItem*)treeview->itemNew.lParam;

			if ( NULL != item ) {

				item->setSelected( true );

				POINT tmpPt = {0,0};
				GetCursorPos( &tmpPt );
				::ScreenToClient( hwnd_, &tmpPt );
				ItemEvent event( treeControl_, TREEITEM_SELECTED );

				event.setUserData( (void*)item );

				Point pt( tmpPt.x, tmpPt.y );
				event.setPoint( &pt );

				treeControl_->handleEvent( &event );
			}

			item = (TreeItem*)treeview->itemOld.lParam;
			if ( NULL != item ) {
				item->setSelected( false );
			}
		}
		break;

		case TVN_SELCHANGEDA:{
			NMTREEVIEWA* treeview = (NMTREEVIEWA*)lParam;
			TreeItem* item = (TreeItem*)treeview->itemNew.lParam;
			if ( NULL != item ) {
				item->setSelected( true );
				POINT tmpPt = {0,0};
				GetCursorPos( &tmpPt );
				::ScreenToClient( hwnd_, &tmpPt );
				ItemEvent event( treeControl_, TREEITEM_SELECTED );

				event.setUserData( (void*)item );

				Point pt( tmpPt.x, tmpPt.y );
				event.setPoint( &pt );

				treeControl_->handleEvent( &event );
			}

			item = (TreeItem*)treeview->itemOld.lParam;
			if ( NULL != item ) {
				item->setSelected( false );
			}
		}
		break;

		case TVN_SELCHANGING:{

		}
		break;

		case TVN_SETDISPINFO:{

		}
		break;

		case TVN_SINGLEEXPAND:{

		}
		break;
/*
JC
Do we need these? What advantage does processing these events have for us???
		case NM_RCLICK :{
			POINT pt = {0,0};
			GetCursorPos( &pt );
			ScreenToClient( hwnd_, &pt );
			Point tmpPt( pt.x, pt.y );
			VCF::MouseEvent event( getControl(), Control::MOUSE_CLICK,
						mbmRightButton, kmUndefined, &tmpPt );
			if ( peerControl_ ) {
					peerControl_->handleEvent( &event );
			}
		}
		break;

		case NM_CLICK :{
			POINT pt = {0,0};
			GetCursorPos( &pt );
			ScreenToClient( hwnd_, &pt );
			Point tmpPt( pt.x, pt.y );
			VCF::MouseEvent event( getControl(), Control::MOUSE_CLICK,
						mbmLeftButton, kmUndefined, &tmpPt );
			if ( peerControl_ ) {
					peerControl_->handleEvent( &event );
			}
		}
		break;
		*/

		case NM_CUSTOMDRAW:{
			static Rect itemRect;

			wndProcResult = CDRF_DODEFAULT;
			result = true;

			NMTVCUSTOMDRAW__* treeViewDraw = (NMTVCUSTOMDRAW__*)lParam;
			if ( NULL != treeViewDraw )	{
				switch ( treeViewDraw->nmcd.dwDrawStage ) {
					case CDDS_PREPAINT : {
						wndProcResult = CDRF_NOTIFYITEMDRAW | CDRF_NOTIFYPOSTPAINT;
					}
					break;

					case CDDS_ITEMPREPAINT : {
						RECT r;
						TreeView_GetItemRect( hwnd_,
											(HTREEITEM) treeViewDraw->nmcd.dwItemSpec,
											&r, TRUE );

						itemRect.left_ = r.left;
						itemRect.top_ = r.top;
						itemRect.right_ = r.right;
						itemRect.bottom_ = r.bottom;

						wndProcResult = CDRF_NOTIFYPOSTPAINT;
					}
					break;

					case CDDS_ITEMPOSTPAINT : {


						wndProcResult = CDRF_DODEFAULT;

						if ( NULL != treeViewDraw->nmcd.lItemlParam ) {
							TreeItem* item = (TreeItem*)treeViewDraw->nmcd.lItemlParam;

							if ( item->canPaint() ) {
								item->paint( peerControl_->getContext(), &itemRect );
							}
						}
					}
					break;

					default : {

						wndProcResult = 0;
					}
					break;
				}
			}
		}
		break;

		default: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			//result = CallWindowProc( oldTreeWndProc_, hwnd_, message, wParam, lParam );

		}
		break;
	}
	return result;
}

void Win32Tree::addItem( TreeItem* item )
{
	HTREEITEM addedItem = NULL;

	if ( System::isUnicodeEnabled() ) {
		TVINSERTSTRUCTW insert;
		memset( &insert, 0, sizeof(TVINSERTSTRUCTW) );
		TVITEMW tvItem;
		memset( &tvItem, 0, sizeof(TVITEMW) );

		TreeItem* parent = item->getParent();
		HTREEITEM itemParent = NULL;
		if ( NULL != parent ){
			std::map<TreeItem*,HTREEITEM>::iterator it =
				treeItems_.find( parent );
			if ( it != treeItems_.end() ){
				itemParent = it->second;
			}
			else{
				//throw exception;
			}
		}
		tvItem.mask = TVIF_TEXT | TVIF_PARAM;
		if ( imageListCtrl_ != NULL ) {
			tvItem.mask |= TVIF_IMAGE;
			tvItem.iImage = item->getImageIndex();
		}

		if ( item->getStateImageIndex() >= 0 ) {
			tvItem.mask |= TVIF_STATE;
			//INDEXTOSTATEIMAGEMASK is one based, but Item::getStateImageIndex() is zero based
			tvItem.state = INDEXTOSTATEIMAGEMASK( item->getStateImageIndex() );
			tvItem.stateMask = TVIS_STATEIMAGEMASK;
		}

		if ( item->getSelectedImageIndex() >= 0 ) {
			tvItem.mask |= TVIF_SELECTEDIMAGE ;
			tvItem.iSelectedImage = item->getSelectedImageIndex();
		}

		tvItem.cchTextMax = 0;//item->getCaption().size()+1;
		//VCFChar* tmpName = new VCFChar[tvItem.cchTextMax];
		//memset( tmpName, 0, tvItem.cchTextMax*sizeof(VCFChar) );
		//item->getCaption().copy( tmpName, tvItem.cchTextMax-1 );

		tvItem.pszText = LPSTR_TEXTCALLBACKW;//tmpName;
		tvItem.lParam = (LPARAM)item;
		insert.hParent = itemParent;
		insert.hInsertAfter = TVI_LAST;
		insert.item = tvItem;

		addedItem = (HTREEITEM)::SendMessage( hwnd_, TVM_INSERTITEMW, 0, (LPARAM)&insert );
	}
	else {
		TVINSERTSTRUCTA insert;
		memset( &insert, 0, sizeof(TVINSERTSTRUCTA) );
		TVITEMA tvItem;
		memset( &tvItem, 0, sizeof(TVITEMA) );

		TreeItem* parent = item->getParent();
		HTREEITEM itemParent = NULL;
		if ( NULL != parent ){
			std::map<TreeItem*,HTREEITEM>::iterator it =
				treeItems_.find( parent );
			if ( it != treeItems_.end() ){
				itemParent = it->second;
			}
			else{
				//throw exception;
			}
		}
		tvItem.mask = TVIF_TEXT | TVIF_PARAM;
		if ( imageListCtrl_ != NULL ) {
			tvItem.mask |= TVIF_IMAGE;
			tvItem.iImage = item->getImageIndex();
		}

		if ( item->getStateImageIndex() >= 0 ) {
			tvItem.mask |= TVIF_STATE;
			//INDEXTOSTATEIMAGEMASK is one based, but Item::getStateImageIndex() is zero based
			tvItem.state = INDEXTOSTATEIMAGEMASK( item->getStateImageIndex() );
			tvItem.stateMask = TVIS_STATEIMAGEMASK;
		}

		if ( item->getSelectedImageIndex() >= 0 ) {
			tvItem.mask |= TVIF_SELECTEDIMAGE ;
			tvItem.iSelectedImage = item->getSelectedImageIndex();
		}

		tvItem.cchTextMax = 0;//item->getCaption().size()+1;
		//VCFChar* tmpName = new VCFChar[tvItem.cchTextMax];
		//memset( tmpName, 0, tvItem.cchTextMax*sizeof(VCFChar) );
		//item->getCaption().copy( tmpName, tvItem.cchTextMax-1 );

		tvItem.pszText = LPSTR_TEXTCALLBACKA;//tmpName;
		tvItem.lParam = (LPARAM)item;
		insert.hParent = itemParent;
		insert.hInsertAfter = TVI_LAST;
		insert.item = tvItem;

		addedItem = (HTREEITEM)SendMessage( hwnd_, TVM_INSERTITEMA, 0, (LPARAM)&insert );
	}




	//delete [] tmpName;

	treeItems_[item] = addedItem;

	item->addItemAddedHandler( itemAddedHandler_ );
	item->addItemChangedHandler( itemChangedHandler_ );
	item->addItemDeletedHandler( itemDeletedHandler_ );
	item->addItemPaintHandler( itemPaintedHandler_ );
	item->addItemSelectedHandler( itemSelectedHandler_ );

	//now check the children

	Enumerator<TreeItem*>* children = item->getChildren();
	if ( NULL != children ){
		while ( children->hasMoreElements() ){
			TreeItem* child = children->nextElement();
			if ( NULL != child ){
				addItem( child );
			}
		}
	}
}

void Win32Tree::clear()
{
	treeItems_.clear();
	StringUtils::trace( "tree items cleared\n" );
	TreeView_DeleteAllItems( hwnd_ );
}

void Win32Tree::onItemPaint( ItemEvent* event )
{

}

void Win32Tree::onItemChanged( ItemEvent* event )
{
	if ( (NULL != event) && (peerControl_->getComponentState() != Component::csDestroying) ){

		Object* source = event->getSource();
		if ( NULL != source ){
			TreeItem* item = dynamic_cast<TreeItem*>(source);
			if ( NULL != item ){
				std::map<TreeItem*,HTREEITEM>::iterator it =
					treeItems_.find( item );
				if ( it != treeItems_.end() ){

					if ( event->getType() == DefaultTreeItem::teItemExpanded ) {
						if ( !internalTreeItemExpanded_ ){
							if ( item->isExpanded() ) {
								TreeView_Expand( hwnd_, it->second, TVE_EXPAND );
							}
							else {
								TreeView_Expand( hwnd_, it->second, TVE_COLLAPSE );
							}
						}
					}
					else {
						if ( System::isUnicodeEnabled() ) {
							TVITEMW tvItem;
							memset( &tvItem, 0, sizeof(TVITEMW) );

							tvItem.mask = TVIF_HANDLE | TVIF_IMAGE ;
							tvItem.iImage = item->getImageIndex();

							tvItem.mask |= TVIF_STATE;

							if ( item->getTextBold() ) {
								tvItem.state |= TVIS_BOLD;
							}

							tvItem.stateMask |= TVIS_BOLD;


							if ( item->getStateImageIndex() >= 0 ) {
								tvItem.mask |= TVIF_STATE;
								tvItem.state |= INDEXTOSTATEIMAGEMASK( item->getStateImageIndex() );
								tvItem.stateMask |= TVIS_STATEIMAGEMASK;
							}

							if ( item->getSelectedImageIndex() >= 0 ) {
								tvItem.mask |= TVIF_SELECTEDIMAGE ;
								tvItem.iSelectedImage = item->getSelectedImageIndex();
							}

							tvItem.hItem = it->second;


							SendMessage( hwnd_, TVM_SETITEMW, 0, (LPARAM)&tvItem );
						}
						else {
							TVITEMA tvItem;
							memset( &tvItem, 0, sizeof(TVITEMA) );

							tvItem.mask = TVIF_HANDLE | TVIF_IMAGE ;
							tvItem.iImage = item->getImageIndex();

							tvItem.mask |= TVIF_STATE;

							if ( item->getTextBold() ) {
								tvItem.state |= TVIS_BOLD;
							}

							tvItem.stateMask |= TVIS_BOLD;


							if ( item->getStateImageIndex() >= 0 ) {
								tvItem.mask |= TVIF_STATE;
								tvItem.state |= INDEXTOSTATEIMAGEMASK( item->getStateImageIndex() );
								tvItem.stateMask |= TVIS_STATEIMAGEMASK;
							}

							if ( item->getSelectedImageIndex() >= 0 ) {
								tvItem.mask |= TVIF_SELECTEDIMAGE ;
								tvItem.iSelectedImage = item->getSelectedImageIndex();
							}

							tvItem.hItem = it->second;

							SendMessage( hwnd_, TVM_SETITEMA, 0, (LPARAM)&tvItem );
						}
					}
				}
			}
		}
	}
}

void Win32Tree::onItemSelected( ItemEvent* event )
{
	if ( (NULL != event) && (peerControl_->getComponentState() != Component::csDestroying) ){

		Object* source = event->getSource();
		if ( NULL != source ){
			TreeItem* item = dynamic_cast<TreeItem*>(source);
			if ( NULL != item ){
				std::map<TreeItem*,HTREEITEM>::iterator it =
					treeItems_.find( item );
				if ( it != treeItems_.end() ){
					if ( item->isSelected() ) {
						TreeView_SelectItem( hwnd_, it->second );
					}
				}
			}
		}
	}
}

void Win32Tree::onItemAdded( ItemEvent* event )
{

}


void Win32Tree::onItemDeleted( ItemEvent* event )
{
	Object* source = event->getSource();
	if ( NULL != source ){
		TreeItem* item = dynamic_cast<TreeItem*>(source);
		if ( NULL != item ){
			std::map<TreeItem*,HTREEITEM>::iterator found =
				treeItems_.find( item );
			if ( found != treeItems_.end() ){
				HTREEITEM hItem = found->second;
				treeItems_.erase( found );
				TreeView_DeleteItem( hwnd_, hItem );
			}
		}
	}
}

void Win32Tree::onImageListImageChanged( ImageListEvent* event )
{
	ulong32 index = event->getIndexOfImage();
	ImageList* imageList = (ImageList*)event->getSource();
	setImageList( imageList );

	//hacky way for now
	/*
	switch ( event->getType() ) {
		case IMAGELIST_EVENT_WIDTH_CHANGED : {

		}
		break;

		case IMAGELIST_EVENT_HEIGHT_CHANGED : {

		}
		break;

		case IMAGELIST_EVENT_ITEM_ADDED : {
			Win32Image* win32Img = (Win32Image*)event->getImage();
			HBITMAP hbmImage = win32Img->getBitmap();
			int err = ImageList_Add( imageListCtrl_, hbmImage, NULL );
			if ( err < 0 ) {
				//error condition !
			}
		}
		break;

		case IMAGELIST_EVENT_ITEM_DELETED : {

		}
		break;
	}
	*/
}

Rect Win32Tree::getItemImageRect( TreeItem* item )
{
	Rect result;

	return result;
}

void Win32Tree::onStateImageListImageChanged( ImageListEvent* event )
{
	ImageList* imageList = (ImageList*)event->getSource();
	setStateImageList( imageList );
}

void Win32Tree::setStateImageList( ImageList* imageList )
{
	if ( NULL != stateImageListCtrl_ ) {
		BOOL err = ImageList_Destroy( stateImageListCtrl_ );
	}
	stateImageListCtrl_ = NULL;
	TreeView_SetImageList( hwnd_, imageListCtrl_, TVSIL_STATE );

	if ( imageList != NULL ) {
		stateImageListCtrl_ = ImageList_Create( imageList->getImageWidth(), imageList->getImageHeight(),
										ILC_COLOR24|ILC_MASK, imageList->getImageCount(), 4 );

		Image* masterImage = imageList->getMasterImage();
		Win32Image* win32Img = (Win32Image*)masterImage;
		SysPixelType* pix = win32Img->getImageBits()->pixels_;
		int sz = win32Img->getWidth() * win32Img->getHeight();
		unsigned char* oldAlpaVals = new unsigned char[sz];
		do {
			sz --;
			oldAlpaVals[sz] = pix[sz].a;
			pix[sz].a = 0;
		} while( sz > 0 );


		Color* transparentColor = imageList->getTransparentColor();

		HBITMAP hBMPcopy = (HBITMAP)CopyImage( win32Img->getBitmap(), IMAGE_BITMAP, 0, 0, NULL );
		//flip the bits

		int err = ImageList_AddMasked( stateImageListCtrl_, hBMPcopy, transparentColor->getColorRef32() );

		if ( err < 0 ) {
			//error condition !
		}
		DeleteObject( hBMPcopy );

		sz = win32Img->getWidth() * win32Img->getHeight();
		do {
			sz --;
			pix[sz].a = oldAlpaVals[sz];
		} while( sz > 0 );

		delete [] oldAlpaVals;

		TreeView_SetImageList( hwnd_, stateImageListCtrl_, TVSIL_STATE );


		EventHandler* imgListHandler = getEventHandler( "Win32Tree::onStateImageListImageChanged" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ImageListEventHandler<Win32Tree>(this, &Win32Tree::onStateImageListImageChanged, "Win32Tree::onStateImageListImageChanged" );

		}
		imageList->SizeChanged.addHandler( imgListHandler );
		imageList->ImageAdded.addHandler( imgListHandler );
		imageList->ImageDeleted.addHandler( imgListHandler );
	}
}

bool Win32Tree::getAllowLabelEditing()
{
	return ( TVS_EDITLABELS & GetWindowLong( hwnd_, GWL_STYLE ) ) ? true : false;
}

void Win32Tree::setAllowLabelEditing( const bool& allowLabelEditing )
{
	int style = GetWindowLong( hwnd_, GWL_STYLE );
	if ( allowLabelEditing ) {
		style |= TVS_EDITLABELS;
	}
	else {
		style &= ~TVS_EDITLABELS;
	}
	SetWindowLong( hwnd_, GWL_STYLE, style );

	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );

	::UpdateWindow( hwnd_ );
}

void Win32Tree::onControlModelChanged( Event* e )
{
	EventHandler* ev = getEventHandler( "Win32Tree::onTreeNodeDeleted" );

	if ( NULL == ev ) {
		ev = new TreeModelEventHandler<Win32Tree>( this,
													&Win32Tree::onTreeNodeDeleted,
													"Win32Tree::onTreeNodeDeleted" );
	}
	treeControl_->getTreeModel()->addTreeNodeDeletedHandler( ev );
}

void Win32Tree::onTreeNodeDeleted( TreeModelEvent* event )
{
	TreeItem* item = event->getTreeItem();
	if ( NULL != item ){
		std::map<TreeItem*,HTREEITEM>::iterator found =
			treeItems_.find( item );
		if ( found != treeItems_.end() ){
			HTREEITEM hItem = found->second;
			treeItems_.erase( found );
			TreeView_DeleteItem( hwnd_, hItem );
		}
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:14:59  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4  2005/01/02 03:04:22  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.13  2005/06/26 01:31:20  marcelloptr
*improvements to the Color class. The default, when packing the components into a single integer, is now cpsARGB instead than cpsABGR.
*
*Revision 1.3.2.12  2005/06/09 06:13:08  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.3.2.11  2005/05/02 02:31:42  ddiego
*minor text updates.
*
*Revision 1.3.2.10  2005/04/26 02:29:40  ddiego
*fixes font setting bug brought up by scott and glen_f
*
*Revision 1.3.2.9  2005/04/20 02:26:01  ddiego
*fixes for single line text and formatting problems in text window creation.
*
*Revision 1.3.2.8  2005/04/09 17:20:36  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3.2.7  2005/02/16 05:09:32  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3.2.6  2005/01/28 02:49:02  ddiego
*fixed bug 1111096 where the text control was properly handlind
*input from the numbpad keys.
*
*Revision 1.3.2.5  2005/01/07 01:13:59  ddiego
*fixed a foundation kit but that was cause a crash by releasing the system instance and then making use of a member variable for it. The member variable is now static, which is more appropriate.
*
*Revision 1.3.2.4  2005/01/01 20:31:08  ddiego
*made an adjustment to quitting and event loop, and added some changes to the DefaultTabModel.
*
*Revision 1.3.2.3  2004/12/31 17:41:23  ddiego
*fixes a drag-drop bug, initially listed under the vcfbuilders
*bug list
*
*Revision 1.3.2.2  2004/12/31 17:39:47  ddiego
*fixes a drag-drop bug, initially listed under the vcfbuilders
*bug list
*
*Revision 1.3.2.1  2004/12/19 04:05:00  ddiego
*made modifications to methods that return a handle type. Introduced
*a new typedef for handles, that is a pointer, as opposed to a 32bit int,
*which was causing a problem for 64bit compiles.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/09/09 04:42:04  ddiego
*fixed some custom draw bugs in win32 tree control. updated
*advanced ui example.
*
*Revision 1.2.2.3  2004/09/08 03:49:05  ddiego
*minor win32 tree mods
*
*Revision 1.2.2.2  2004/09/07 03:57:04  ddiego
*misc tree control update
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.13  2004/07/30 17:27:14  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.12  2004/07/26 03:40:31  ddiego
*minor changes
*
*Revision 1.1.2.11  2004/07/23 04:20:56  ddiego
*more checkins
*
*Revision 1.1.2.10  2004/07/16 05:07:18  ddiego
*added support for editing labels on a tree control
*
*Revision 1.1.2.9  2004/07/16 04:01:46  ddiego
*fixed the last of border redraw issues, I hope.
*
*Revision 1.1.2.8  2004/07/15 18:53:00  ddiego
*more updates
*
*Revision 1.1.2.7  2004/07/14 18:18:14  ddiego
*fixed problem with edit control. Turns out we were using the wrong
*subclassed wndproc. This is now fixed.
*
*Revision 1.1.2.6  2004/07/14 04:56:02  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.5  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/05/06 21:18:33  ddiego
*some more minor win32 unicode changes
*
*Revision 1.1.2.3  2004/05/04 17:16:07  ddiego
*updated some win32 stuff for unicode compliance
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.33  2004/04/03 15:48:48  ddiego
*Merged over code from the 0-6-3 branch.
*

*Revision 1.31.2.4  2004/03/28 00:46:22  ddiego
*added VisualFormFiles, fixed some code in the DocumentManager
*class, and changed code over to create an Application class on the
*heap instead of on the stack. This fixes a problem with static object
*destrcutor order when using VC71. Also updated the project wizards
*for vc6. Still need to update docs.
*
*Revision 1.31.2.3  2004/03/21 16:03:10  ddiego
*minor change to VCFString to properly allocate a buffer
*unicode xfrm
*
*Revision 1.31.2.2  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.31.2.1  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.32  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.31.2.1  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.31  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.30.2.2  2003/09/17 21:23:24  ddiego
*added adjustmnents to win32 tree peer and drop target
*
*Revision 1.30.2.1  2003/09/16 21:21:19  ddiego
*freed up the DataObject the com DO held onto
*added support for dynamically get the caption's of tree items
*
*Revision 1.30  2003/08/09 02:56:46  ddiego
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
*Revision 1.29.2.2  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.29.2.1  2003/05/27 04:45:38  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.29  2003/05/17 20:37:39  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.28.2.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.28.2.1  2003/03/12 03:12:43  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.28  2003/02/26 04:30:52  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.27.2.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.27.2.3  2003/01/08 00:19:54  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.27.2.2  2002/12/27 23:04:55  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.27.2.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.27  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.26.10.3  2002/11/17 01:20:38  cesarmello
*Removed the LR_COPYRETURNORG flag from CopyImage due to inconsistent Win32 behavior under Windows NT 4
*
*Revision 1.26.10.2  2002/11/06 04:27:26  ddiego
**** empty log message ***
*
*Revision 1.26.10.1  2002/09/12 21:35:53  ddiego
*mods to make double clicking on the form in the workspace tree open a
*form designer, and clicking on a component instance in the workspace tree
*will select the component in the form designer
*
*Revision 1.26  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.25.4.2  2002/04/27 15:52:31  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.25.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.25  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.24  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


