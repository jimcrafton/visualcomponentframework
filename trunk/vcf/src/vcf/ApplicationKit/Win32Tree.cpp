//Win32Tree.cpp

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
#include "vcf/ApplicationKit/Win32Tree.h"
#include "vcf/ApplicationKit/TreeControl.h"


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



#ifdef VCF_CYGWIN

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


#ifdef VCF_UNICODE
	#define TVN_GETINFOTIP          TVN_GETINFOTIPW
	#define NMTVGETINFOTIP          NMTVGETINFOTIPW
	#define LPNMTVGETINFOTIP        LPNMTVGETINFOTIPW
#else
	#define TVN_GETINFOTIP          TVN_GETINFOTIPA
	#define NMTVGETINFOTIP          NMTVGETINFOTIPA
	#define LPNMTVGETINFOTIP        LPNMTVGETINFOTIPA
#endif

#endif //_WIN32_IE


#endif //VCF_CYGWIN





using namespace VCFWin32;
using namespace VCF;

Win32Tree::Win32Tree( TreeControl* tree ):
	AbstractWin32Component( tree ),
	treeControl_( tree ),
	imageListCtrl_(NULL),
	stateImageListCtrl_(NULL),
	internalTreeItemMod_(false)
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
		treeControl_ = (TreeControl*)owningControl;
		peerControl_ = owningControl;

		Win32Object::registerWin32Object( this );

		subclassWindow();		

		registerForFontChanges();

		peerControl_->ControlModelChanged +=
			new ClassProcedure1<Event*,Win32Tree>( this, &Win32Tree::onControlModelChanged, "Win32Tree::onControlModelChanged" );

		treeControl_->ItemExpanded +=
			new ClassProcedure1<ItemEvent*,Win32Tree>( this, &Win32Tree::onItemExpanded, "Win32Tree::onItemExpanded" );

		treeControl_->ItemSelected +=
			new ClassProcedure1<ItemEvent*,Win32Tree>( this, &Win32Tree::onItemSelected, "Win32Tree::onItemSelected" );

		COLORREF backColor = treeControl_->getColor()->getColorRef32();

		TreeView_SetBkColor( hwnd_, backColor );
	}
	else {
		//throw exception
	}

	setCreated( true );
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

		COLORREF transparentColor = imageList->getTransparentColor()->getColorRef32();		

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
			bits[sz].a = oldAlpaVals[sz];
		} while( sz > 0 );

		delete [] oldAlpaVals;


		TreeView_SetImageList( hwnd_, imageListCtrl_, TVSIL_NORMAL );


		CallBack* imgListHandler = getCallback( "Win32Tree::onImageListImageChanged" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ClassProcedure1<ImageListEvent*, Win32Tree>(this, &Win32Tree::onImageListImageChanged, "Win32Tree::onImageListImageChanged" );

		}
		imageList->SizeChanged += imgListHandler;
		imageList->ImageAdded += imgListHandler;
		imageList->ImageDeleted += imgListHandler;
	}
}

bool Win32Tree::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = 0;
	wndProcResult = 0;


	switch ( message ) {
		case WM_PAINT:{
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

			POINT oldOrg;
			memset(&oldOrg,0,sizeof(oldOrg));
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
			
			peerControl_->internal_beforePaint( ctx );

			peerControl_->paint( ctx );

			peerControl_->internal_afterPaint( ctx );


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
			COLORREF clrRef = color->getColorRef32();
			COLORREF currentClr = TreeView_GetBkColor( hwnd_ );

			if ( currentClr != clrRef ) {
				TreeView_SetBkColor( hwnd_, clrRef );
			}


			wndProcResult = 0;
			result = true;
		}
		break;

		case WM_LBUTTONDOWN : {


			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );



			TVHITTESTINFO hitTestInfo;
			memset( &hitTestInfo, 0, sizeof(TVHITTESTINFO) );

			hitTestInfo.pt.x = Win32UIUtils::getXFromLParam( lParam );
			hitTestInfo.pt.y = Win32UIUtils::getYFromLParam( lParam );
			HTREEITEM hItem = TreeView_HitTest( hwnd_, &hitTestInfo );
			if ( NULL != hItem ) {
				if( hitTestInfo.flags & TVHT_ONITEMSTATEICON ) {
					TVITEM tvItem;
					memset( &tvItem, 0, sizeof(TVITEM) );
					tvItem.mask = TVIF_PARAM | TVIF_HANDLE ;
					tvItem.hItem = hItem;
					if ( TreeView_GetItem( hwnd_, &tvItem ) ) {
						TreeItem* item = treeControl_->getItemFromKey( tvItem.lParam );
						if ( NULL != item ) {
							
							ItemEvent event( item, TreeControl::ITEM_STATECHANGE_REQUESTED );
							
							treeControl_->handleEvent( &event );
						}
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
			//result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			
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

			TreeItem* item = treeControl_->getItemFromKey( treeview->itemNew.lParam );

			if ( NULL != item ) {
				Point pt( treeview->ptDrag.x, treeview->ptDrag.y );

				TreeItem* oldItem = treeControl_->getSelectedItem();
				if ( item != oldItem ) {
					//hmm, we haven't selected this item before, so
					//let's go ahead and make it selected now
					//we do this because the TVN_SELECTIONCHANGED
					//won't get called at this point

					item->setSelected( true );

					if ( NULL != oldItem ) {
						oldItem->setSelected( false );
					}
				}

				SHORT keyState = GetKeyState( VK_SHIFT );
				uint32 keyMask = kmUndefined;
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
			TreeItem* item = treeControl_->getItemFromKey( treeview->itemNew.lParam );

			if ( NULL != item ) {
				Point pt( treeview->ptDrag.x, treeview->ptDrag.y );

				TreeItem* oldItem = treeControl_->getSelectedItem();
				if ( item != oldItem ) {
					//hmm, we haven't selected this item before, so
					//let's go ahead and make it selected now
					//we do this because the TVN_SELECTIONCHANGED
					//won't get called at this point

					item->setSelected( true );					

					if ( NULL != oldItem ) {
						oldItem->setSelected( false );
					}
				}

				SHORT keyState = GetKeyState( VK_SHIFT );
				uint32 keyMask = kmUndefined;
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
				TreeItem* item = treeControl_->getItemFromKey( lptvdi->item.lParam );
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
				TreeItem* item = treeControl_->getItemFromKey( lptvdi->item.lParam );
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
				TreeModel* tm = treeControl_->getTreeModel();
				TreeModel::Key key = (TreeModel::Key)lptvdi->item.lParam;

				String s = tm->getAsString( key );

				if ( !s.empty() ) {
					s.copy( lptvdi->item.pszText, s.size() );
					lptvdi->item.pszText[s.size()] = 0;
				}
			}


			if ( lptvdi->item.mask & TVIF_CHILDREN ) {
				TreeModel* tm = treeControl_->getTreeModel();
				TreeModel::Key key = (TreeModel::Key)lptvdi->item.lParam;
				lptvdi->item.cChildren = tm->isLeaf( key ) ? 0 : 1;
			}

			if ( lptvdi->item.mask & TVIF_IMAGE ) {
				if ( treeControl_->itemExists( lptvdi->item.lParam ) ) {
					TreeItem* item = treeControl_->getItemFromKey( lptvdi->item.lParam );
					lptvdi->item.iImage = item->getImageIndex();
				}
				else {
					lptvdi->item.iImage = -1;
				}
			}

			if ( lptvdi->item.mask & TVIF_SELECTEDIMAGE ) {
				if ( treeControl_->itemExists( lptvdi->item.lParam ) ) {
					TreeItem* item = treeControl_->getItemFromKey( lptvdi->item.lParam );
					lptvdi->item.iSelectedImage = item->getSelectedImageIndex();
					if ( lptvdi->item.iSelectedImage == -1 && item->getImageIndex() != -1 ) {
						lptvdi->item.iSelectedImage = item->getImageIndex();
					}
				}
				else {
					lptvdi->item.iSelectedImage = -1;
				}
			}

		}
		break;

		case TVN_GETDISPINFOA: {
			LPNMTVDISPINFOA lptvdi = (LPNMTVDISPINFOA) lParam ;
			if ( lptvdi->item.mask & TVIF_TEXT ) {
				
				TreeModel* tm = treeControl_->getTreeModel();
				TreeModel::Key key = (TreeModel::Key)lptvdi->item.lParam;

				AnsiString s = tm->getAsString( key );

				if ( !s.empty() ) {					
					s.copy( lptvdi->item.pszText, s.size() );
					lptvdi->item.pszText[s.size()] = 0;
				}
			}


			if ( lptvdi->item.mask & TVIF_CHILDREN ) {
				TreeModel* tm = treeControl_->getTreeModel();
				TreeModel::Key key = (TreeModel::Key)lptvdi->item.lParam;
				lptvdi->item.cChildren = tm->isLeaf( key ) ? 0 : 1;
			}

			if ( lptvdi->item.mask & TVIF_IMAGE ) {
				if ( treeControl_->itemExists( lptvdi->item.lParam ) ) {
					TreeItem* item = treeControl_->getItemFromKey( lptvdi->item.lParam );
					lptvdi->item.iImage = item->getImageIndex();
				}
				else {
					lptvdi->item.iImage = -1;
				}
			}

			if ( lptvdi->item.mask & TVIF_SELECTEDIMAGE ) {
				if ( treeControl_->itemExists( lptvdi->item.lParam ) ) {
					TreeItem* item = treeControl_->getItemFromKey( lptvdi->item.lParam );
					lptvdi->item.iSelectedImage = item->getSelectedImageIndex();
				}
				else {
					lptvdi->item.iSelectedImage = -1;
				}
			}
		}
		break;

		case TVN_GETINFOTIP:{

		}
		break;

		case TVN_ITEMEXPANDEDA:{
			internalTreeItemMod_ = true;
			NMTREEVIEWA* treeview = (NMTREEVIEWA*)lParam;

			if ( treeview->action == TVE_EXPAND ) {
			}
			else if ( treeview->action == TVE_COLLAPSE ) {
				TreeView_Expand (hwnd_,
                                 treeview->itemNew.hItem,
                                 TVE_COLLAPSE | TVE_COLLAPSERESET);	
			}

			TreeItem* item = treeControl_->getItemFromKey( treeview->itemNew.lParam );


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

			internalTreeItemMod_ = false;
		}
		break;

		case TVN_ITEMEXPANDEDW:{
			internalTreeItemMod_ = true;
			NMTREEVIEWW* treeview = (NMTREEVIEWW*)lParam;

			if ( treeview->action == TVE_EXPAND ) {
			}
			else if ( treeview->action == TVE_COLLAPSE ) {
				TreeView_Expand (hwnd_,
                                 treeview->itemNew.hItem,
                                 TVE_COLLAPSE | TVE_COLLAPSERESET);	
			}

			TreeItem* item = treeControl_->getItemFromKey( treeview->itemNew.lParam );


			if ( NULL != item ) {

				if ( treeview->action & TVE_EXPAND ) {
					item->expand( true );
				}
				else if ( treeview->action & TVE_COLLAPSE ) {
					item->expand( false );
				}
/*
				POINT tmpPt = {0,0};
				GetCursorPos( &tmpPt );
				::ScreenToClient( hwnd_, &tmpPt );
				ItemEvent event( item, TREEITEM_EXPANDED );

				Point pt( tmpPt.x, tmpPt.y );
				event.setPoint( &pt );

				treeControl_->handleEvent( &event );
				*/
			}

			internalTreeItemMod_ = false;
		}
		break;

		case TVN_ITEMEXPANDINGW:{
			NMTREEVIEWW* treeview = (NMTREEVIEWW*)lParam;
			if ( TVE_EXPAND == treeview->action ) {
				TreeModel* tm = treeControl_->getTreeModel();
				TreeModel::Key key = (TreeModel::Key)treeview->itemNew.lParam;
				
				std::vector<TreeModel::Key> children;
				tm->getChildren(key,children);
				std::vector<TreeModel::Key>::iterator it = children.begin();
				while ( it != children.end() ) {
					addTreeItem( *it, treeview->itemNew.hItem );
					++it;
				}
			}
		}
		break;

		case TVN_ITEMEXPANDINGA:{
			NMTREEVIEWA* treeview = (NMTREEVIEWA*)lParam;
			if ( TVE_EXPAND == treeview->action ) {
				TreeModel* tm = treeControl_->getTreeModel();
				TreeModel::Key key = (TreeModel::Key)treeview->itemNew.lParam;
				
				std::vector<TreeModel::Key> children;
				tm->getChildren(key,children);
				std::vector<TreeModel::Key>::iterator it = children.begin();
				while ( it != children.end() ) {
					addTreeItem( *it, treeview->itemNew.hItem );
					++it;
				}
			}
		}
		break;

		case TVN_KEYDOWN:{

		}
		break;

		case TVN_SELCHANGEDW:{
			NMTREEVIEWW* treeview = (NMTREEVIEWW*)lParam;		

			internalTreeItemMod_ = true;
			if ( treeview->itemNew.state & TVIS_SELECTED ) {
				TreeItem* item = treeControl_->getItemFromKey( treeview->itemNew.lParam );
				if ( NULL != item ) {
					if ( !item->isSelected() ) {

						//get old selected item from tree control

						TreeItem* prevItem = treeControl_->getSelectedItem();
						TreeModel::Key key = prevItem->getKey();
						std::map<TreeModel::Key,HTREEITEM>::iterator found =
							treeItems_.find( key );
						
						if ( found != treeItems_.end() ){
							HTREEITEM hItem = found->second;

							if ( hItem != treeview->itemOld.hItem ) {
								
								TVITEM tvItem = {0};
								tvItem.hItem = hItem;
								tvItem.mask = TVIF_STATE ;
								tvItem.stateMask = TVIS_SELECTED;
								
								tvItem.state = tvItem.state &= ~TVIS_SELECTED;
								
								TreeView_SetItem( hwnd_, &tvItem );
							}
						}


						item->setSelected( true );
					}
				}
			}

			internalTreeItemMod_ = false;
			
			if ( !(treeview->itemOld.state & TVIS_SELECTED) && (NULL != treeview->itemOld.hItem) ) {
				TreeItem* item = treeControl_->getItemFromKey( treeview->itemOld.lParam );
				if ( NULL != item ) {
					item->setSelected( false );
				}
			}

			
		}
		break;

		case TVN_SELCHANGEDA:{
			NMTREEVIEWA* treeview = (NMTREEVIEWA*)lParam;		

			internalTreeItemMod_ = true;
			if ( treeview->itemNew.state & TVIS_SELECTED ) {
				TreeItem* item = treeControl_->getItemFromKey( treeview->itemNew.lParam );
				if ( NULL != item ) {
					if ( !item->isSelected() ) {

						//get old selected item from tree control

						TreeItem* prevItem = treeControl_->getSelectedItem();
						TreeModel::Key key = prevItem->getKey();
						std::map<TreeModel::Key,HTREEITEM>::iterator found =
							treeItems_.find( key );
						
						if ( found != treeItems_.end() ){
							HTREEITEM hItem = found->second;

							if ( hItem != treeview->itemOld.hItem ) {
								
								TVITEM tvItem = {0};
								tvItem.hItem = hItem;
								tvItem.mask = TVIF_STATE ;
								tvItem.stateMask = TVIS_SELECTED;
								
								tvItem.state = tvItem.state &= ~TVIS_SELECTED;
								
								TreeView_SetItem( hwnd_, &tvItem );
							}
						}


						item->setSelected( true );
					}
				}
			}

			internalTreeItemMod_ = false;
			
			if ( !(treeview->itemOld.state & TVIS_SELECTED) && (NULL != treeview->itemOld.hItem) ) {
				TreeItem* item = treeControl_->getItemFromKey( treeview->itemOld.lParam );
				if ( NULL != item ) {
					item->setSelected( false );
				}
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

						wndProcResult = CDRF_NOTIFYPOSTPAINT;

						if ( treeControl_->itemExists( treeViewDraw->nmcd.lItemlParam ) ) {
							TreeItem* item = treeControl_->getItemFromKey( treeViewDraw->nmcd.lItemlParam );
							if ( !item->isFontDefault() ) {
								Color* fc = item->getFont()->getColor();
								
								treeViewDraw->clrText = (COLORREF) fc->getColorRef32();
								

								Win32Font* fontPeer = dynamic_cast<Win32Font*>( item->getFont()->getFontPeer() );
								HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( fontPeer );
								if ( NULL != fontHandle ){
									::SelectObject( treeViewDraw->nmcd.hdc, fontHandle );
									wndProcResult |= CDRF_NEWFONT;
								}
							}							
						}
					}
					break;

					case CDDS_ITEMPOSTPAINT : {


						wndProcResult = CDRF_DODEFAULT;

						if ( treeControl_->itemExists( treeViewDraw->nmcd.lItemlParam ) ) {
							TreeItem* item = treeControl_->getItemFromKey( treeViewDraw->nmcd.lItemlParam );
							if ( item->canPaint() ) {
								Rect itemRect;
								itemRect.left_ = treeViewDraw->nmcd.rc.left;
								itemRect.top_ = treeViewDraw->nmcd.rc.top;
								itemRect.right_ = treeViewDraw->nmcd.rc.right;
								itemRect.bottom_ = treeViewDraw->nmcd.rc.bottom;

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

void Win32Tree::addTreeItem( TreeModel::Key key, HTREEITEM parent )
{
	HTREEITEM hItem = NULL;

	if ( System::isUnicodeEnabled() ) {
		TVINSERTSTRUCTW insert;
		memset( &insert, 0, sizeof(TVINSERTSTRUCTW) );
		TVITEMW tvItem;
		memset( &tvItem, 0, sizeof(TVITEMW) );
		
		
		
		tvItem.mask = TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN | 
			TVIF_SELECTEDIMAGE | TVIF_IMAGE;
		
		tvItem.cChildren = I_CHILDRENCALLBACK;
		tvItem.iImage = I_IMAGECALLBACK;
		tvItem.iSelectedImage = I_IMAGECALLBACK;
		
		/*
		if ( item->getStateImageIndex() >= 0 ) {
		tvItem.mask |= TVIF_STATE;
		//INDEXTOSTATEIMAGEMASK is one based, but Item::getStateImageIndex() is zero based
		tvItem.state = INDEXTOSTATEIMAGEMASK( item->getStateImageIndex() );
		tvItem.stateMask = TVIS_STATEIMAGEMASK;
		}
		*/
		
		
		tvItem.cchTextMax = 0;					
		tvItem.pszText = LPSTR_TEXTCALLBACKW;
		tvItem.lParam = (LPARAM)key;
		
		insert.hParent = parent;
		insert.hInsertAfter = TVI_LAST;
		insert.item = tvItem;
		
		hItem = (HTREEITEM) ::SendMessage( hwnd_, TVM_INSERTITEMW, 0, (LPARAM)&insert );
	}
	else {
		TVINSERTSTRUCTA insert;
		memset( &insert, 0, sizeof(TVINSERTSTRUCTA) );
		TVITEMA tvItem;
		memset( &tvItem, 0, sizeof(TVITEMA) );
		
		
		
		tvItem.mask = TVIF_TEXT | TVIF_PARAM | TVIF_CHILDREN | 
			TVIF_SELECTEDIMAGE | TVIF_IMAGE;
		
		tvItem.cChildren = I_CHILDRENCALLBACK;
		tvItem.iImage = I_IMAGECALLBACK;
		tvItem.iSelectedImage = I_IMAGECALLBACK;
		
		
		tvItem.cchTextMax = 0;					
		tvItem.pszText = LPSTR_TEXTCALLBACKA;
		tvItem.lParam = (LPARAM)key;
		
		insert.hParent = parent;
		insert.hInsertAfter = TVI_LAST;
		insert.item = tvItem;
		
		hItem = (HTREEITEM) ::SendMessage( hwnd_, TVM_INSERTITEMA, 0, (LPARAM)&insert );
	}

	if ( NULL != hItem ) {
		treeItems_[key] = hItem;
	}	
}

void Win32Tree::onImageListImageChanged( ImageListEvent* event )
{
	uint32 index = event->getIndexOfImage();
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

Rect Win32Tree::getItemRect( TreeItem* item )
{
	Rect result;
	
	if ( NULL != item ){
		std::map<TreeModel::Key,HTREEITEM>::iterator it = treeItems_.find( item->getKey() );
		if ( it != treeItems_.end() ){
			if ( item->isSelected() ) {
				RECT r;
				memset(&r,0,sizeof(r));
				TreeView_GetItemRect( hwnd_, it->second, &r, TRUE );				

				result.left_ = r.left;
				result.top_ = r.top;
				result.right_ = r.right;
				result.bottom_ = r.bottom;
			}
		}
	}

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
		ColorPixels pix(win32Img);
		SysPixelType* bits = pix;
		int sz = win32Img->getWidth() * win32Img->getHeight();
		unsigned char* oldAlpaVals = new unsigned char[sz];
		do {
			sz --;
			oldAlpaVals[sz] = bits[sz].a;
			bits[sz].a = 0;
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
			bits[sz].a = oldAlpaVals[sz];
		} while( sz > 0 );

		delete [] oldAlpaVals;

		TreeView_SetImageList( hwnd_, stateImageListCtrl_, TVSIL_STATE );


		CallBack* imgListHandler = getCallback( "Win32Tree::onStateImageListImageChanged" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ClassProcedure1<ImageListEvent*,Win32Tree>(this, &Win32Tree::onStateImageListImageChanged, "Win32Tree::onStateImageListImageChanged" );

		}
		imageList->SizeChanged += imgListHandler;
		imageList->ImageAdded += imgListHandler;
		imageList->ImageDeleted += imgListHandler;
	}
}

bool Win32Tree::getAllowLabelEditing()
{
	return ( TVS_EDITLABELS & ::GetWindowLongPtr( hwnd_, GWL_STYLE ) ) ? true : false;
}

void Win32Tree::setAllowLabelEditing( const bool& allowLabelEditing )
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );
	if ( allowLabelEditing ) {
		style |= TVS_EDITLABELS;
	}
	else {
		style &= ~TVS_EDITLABELS;
	}
	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );

	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );

	::UpdateWindow( hwnd_ );
}

void Win32Tree::onControlModelChanged( Event* e )
{
	CallBack* ev = getCallback( "Win32Tree::onTreeModelChanged" );

	if ( NULL == ev ) {
		ev = new ClassProcedure1<ModelEvent*,Win32Tree>( this,
													&Win32Tree::onTreeModelChanged,
													"Win32Tree::onTreeModelChanged" );
	}
	treeControl_->getTreeModel()->ModelChanged += ev;
}

void Win32Tree::onTreeModelChanged( ModelEvent* event )
{
	switch ( event->getType() ) {
		case TreeModel::ItemAdded : {
			TreeModelEvent* te = (TreeModelEvent*)event;
			if ( TreeModel::RootKey ==  te->parentKey ) {
				//only add root items - the rest will be added 
				//as needed
				addTreeItem( te->key, NULL );
			}
			else {
				std::map<TreeModel::Key,HTREEITEM>::iterator found =
					treeItems_.find( te->parentKey );

				if ( found != treeItems_.end() ){
					HTREEITEM hItem = found->second;

					TVITEM tvItem = {0};
					tvItem.hItem = hItem;
					tvItem.mask = TVIF_STATE ;
					tvItem.stateMask = TVIS_EXPANDED;

					TreeView_GetItem( hwnd_, &tvItem );

					if ( tvItem.state & TVIS_EXPANDED ) {
						//need to add the item
						addTreeItem( te->key, hItem );
					}
				}
			}
		}
		break;

		case TreeModel::ItemRemoved : {
			TreeModelEvent* te = (TreeModelEvent*)event;
			std::map<TreeModel::Key,HTREEITEM>::iterator found =
			treeItems_.find( te->key );
			if ( found != treeItems_.end() ){
				HTREEITEM hItem = found->second;
				treeItems_.erase( found );
				TreeView_DeleteItem( hwnd_, hItem );
			}
		}
		break;

		case TreeModel::ContentsDeleted : {
			treeItems_.clear();
			
			TreeView_DeleteAllItems( hwnd_ );
		}
		break;
	}
}

void Win32Tree::onItemExpanded( ItemEvent* e )
{
	if ( !internalTreeItemMod_ ) {
		TreeItem* item = (TreeItem*)e->getSource();
		TreeModel::Key key = item->getKey();
		std::map<TreeModel::Key,HTREEITEM>::iterator found =
			treeItems_.find( key );

		if ( found != treeItems_.end() ){
			if ( item->isExpanded() ) {
				TreeView_Expand( hwnd_, found->second, TVE_EXPAND );
			}
			else {
				TreeView_Expand( hwnd_, found->second, TVE_COLLAPSE | TVE_COLLAPSERESET );
			}
		}
	}
}

void Win32Tree::onItemSelected( ItemEvent* e )
{
	if ( !internalTreeItemMod_ ) {
		TreeItem* item = (TreeItem*)e->getSource();
		TreeModel::Key key = item->getKey();
		std::map<TreeModel::Key,HTREEITEM>::iterator found =
			treeItems_.find( key );

		if ( found != treeItems_.end() ){
			HTREEITEM hItem = found->second;
			
			TVITEM tvItem = {0};
			tvItem.hItem = hItem;
			tvItem.mask = TVIF_STATE ;
			tvItem.stateMask = TVIS_SELECTED;
			
			tvItem.state = item->isSelected() ? tvItem.state |= TVIS_SELECTED : tvItem.state &= ~TVIS_SELECTED;

			TreeView_SetItem( hwnd_, &tvItem );			
		}
	}
}


/**
$Id$
*/
