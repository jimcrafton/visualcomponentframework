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
#include "vcf/ApplicationKit/TreeControl.h"
#include "vcf/ApplicationKit/ColumnModel.h"
#include "vcf/ApplicationKit/ColumnItem.h"

#include "vcf/ApplicationKit/Win32Tree.h"
#include "vcf/GraphicsKit/DrawUIState.h"

/**
this is redifined here because the mingw version is WRONG! (or the MS iversion is
wrong, depends on how you look at it :) ).
*/




#ifdef VCF_CYGWIN		
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
	headerImageListCtrl_(NULL),
	internalTreeItemMod_(false),
	currentCtx_(NULL),
	headerWnd_(NULL),
	oldHeaderWndProc_(NULL),
	oldHeaderFont_(NULL),
	treeWnd_(NULL),
	oldTreeWndProc_(NULL),
	headerEnabled_(false),
	hasLines_(false),
	hasButtons_(false)
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

	if ( true != isRegistered() ){
		registerWin32Class( "Win32Tree", wndProc_  );
	}

	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();


	 



	CreateParams params = createParams();	


	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( 0, L"Win32Tree",
										 NULL,
										 WS_CHILD | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
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
		hwnd_ = ::CreateWindowExA( 0, "Win32Tree",
										 NULL,
										 WS_CHILD | WS_BORDER | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
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

		//subclassWindow();		

		registerForFontChanges();



		peerControl_->ControlModelChanged +=
			new ClassProcedure1<Event*,Win32Tree>( this, &Win32Tree::onControlModelChanged, "Win32Tree::onControlModelChanged" );

		treeControl_->ItemExpanded +=
			new ClassProcedure1<ItemEvent*,Win32Tree>( this, &Win32Tree::onItemExpanded, "Win32Tree::onItemExpanded" );

		treeControl_->ItemSelected +=
			new ClassProcedure1<ItemEvent*,Win32Tree>( this, &Win32Tree::onItemSelected, "Win32Tree::onItemSelected" );

		COLORREF backColor = treeControl_->getColor()->getColorRef32();

		



		if ( System::isUnicodeEnabled() ) {
			this->treeWnd_ = ::CreateWindowExW( params.second,
											 WC_TREEVIEWW,
											 NULL,
											 params.first | WS_VISIBLE,
											 0,
											 0,
											 1,
											 1,
											 hwnd_,
											 NULL,
											 ::GetModuleHandleW(NULL),
											 NULL );
		}
		else {
			treeWnd_ = ::CreateWindowExA( params.second,
											 WC_TREEVIEWA,
											 NULL,
											 params.first,
											 0,
											 0,
											 1,
											 1,
											 hwnd_,
											 NULL,
											 ::GetModuleHandleA(NULL),
											 NULL );
		}


		::SetWindowLongPtr( treeWnd_, GWLP_USERDATA, (LONG_PTR)this );
		oldTreeWndProc_ = (WNDPROC)(LONG_PTR) ::SetWindowLongPtr( treeWnd_, GWLP_WNDPROC, (LONG_PTR)Win32Tree::TreeWndProc );

		TreeView_SetBkColor( treeWnd_, backColor );
	}
	else {
		//throw exception
	}

	setCreated( true );
}

void Win32Tree::setFont( Font* font )
{
	VCF_ASSERT(NULL != hwnd_);
	if ( NULL != font ){
		Win32Font* win32FontPeer = NULL;
		FontPeer* fontPeer = font->getFontPeer();
		win32FontPeer = dynamic_cast<Win32Font*>(fontPeer );
		if ( NULL != win32FontPeer ){
			HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( win32FontPeer );
			if ( NULL != fontHandle ){
				::SendMessage( hwnd_, WM_SETFONT, (WPARAM)fontHandle, MAKELPARAM(TRUE, 0) );
				
				::SendMessage( treeWnd_, WM_SETFONT, (WPARAM)fontHandle, MAKELPARAM(TRUE, 0) );

				if ( NULL != headerWnd_ ) {
					::SendMessage( headerWnd_, WM_SETFONT, (WPARAM)fontHandle, MAKELPARAM(TRUE, 0) );
				}
			}
		}
	}
}

Win32Object::CreateParams Win32Tree::createParams()
{
	Win32Object::CreateParams result;


	result.first = BORDERED_VIEW | TVS_HASBUTTONS | 
			TVS_HASLINES | TVS_LINESATROOT | /*TVS_NOTOOLTIPS | */ TVS_SHOWSELALWAYS;

	result.first &= ~WS_BORDER;
	result.first &= ~WS_VISIBLE;

	result.first |= WS_HSCROLL | WS_VSCROLL;

	result.first |= TVS_DISABLEDRAGDROP;
	result.second = 0;


	return result;
}

double Win32Tree::getItemIndent()
{
	return TreeView_GetIndent( treeWnd_ );
}

void Win32Tree::setItemIndent( const double& indent )
{
	BOOL err = TreeView_SetIndent( treeWnd_, (int)indent );
}


void Win32Tree::setImageList( ImageList* imageList )
{

	if ( NULL != imageListCtrl_ ) {
		BOOL err = ImageList_Destroy( imageListCtrl_ );
	}
	imageListCtrl_ = NULL;
	TreeView_SetImageList( treeWnd_, imageListCtrl_, TVSIL_NORMAL );

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


		TreeView_SetImageList( treeWnd_, imageListCtrl_, TVSIL_NORMAL );


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
			

			wndProcResult = 0;
			result = false;
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

			wndProcResult = 0;
			result = true;
		}
		break;
		
		case WM_LBUTTONDOWN : {


			if ( NULL != headerWnd_ ) {
				if ( ::IsWindowVisible(headerWnd_) ) {
					RECT r;
					GetWindowRect(headerWnd_,&r);

					int xPos = LOWORD(lParam); 
					int yPos = HIWORD(lParam);				
					yPos -= (r.bottom - r.top); 

					lParam = MAKELPARAM(xPos,yPos);
				}
			}

			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );



			

			result = true;
			wndProcResult = defaultWndProcedure( message, wParam, lParam );	

		}
		break;

		case WM_CREATE:{
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

/*		
		case WM_LBUTTONDBLCLK: case WM_MBUTTONDBLCLK: case WM_RBUTTONDBLCLK:{
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			
			Win32MSG msg( hwnd_, message, wParam, lParam, peerControl_ );
			Event* event = UIToolkit::createEventFromNativeOSEventData( &msg );


			if ( NULL != event && (peerControl_->getComponentState() != Component::csDestroying) ) {
				peerControl_->handleEvent( event );

				event->free();
			}
			

			//DO NOT, REPEAT: DO NOT allow the DefaultWndProc to get called!
			//wndProcResult = 1;
			//result = true;
		}
		break;
		*/


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
				TreeView_Expand (treeWnd_,
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
				::ScreenToClient( treeWnd_, &tmpPt );
				ItemEvent event( treeControl_, TREEITEM_EXPANDED );

				event.setUserData( (void*)item );

				Point pt( tmpPt.x, tmpPt.y );
				event.point =pt;

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
				TreeView_Expand (treeWnd_,
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

						if ( prevItem )
						{
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
								
									TreeView_SetItem( treeWnd_, &tvItem );
								}
							}
						}

						item->setSelected( true );
					}
				}
			}

			internalTreeItemMod_ = false;
			
			if ( !(treeview->itemOld.state & TVIS_SELECTED) && (NULL != treeview->itemOld.hItem) ) {
				internalTreeItemMod_ = true;
				TreeItem* item = treeControl_->getItemFromKey( treeview->itemOld.lParam );
				if ( NULL != item ) {
					item->setSelected( false );
				}
				internalTreeItemMod_ = false;
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
								
								TreeView_SetItem( treeWnd_, &tvItem );
							}
						}


						item->setSelected( true );
					}
				}
			}

			internalTreeItemMod_ = false;
			
			if ( !(treeview->itemOld.state & TVIS_SELECTED) && (NULL != treeview->itemOld.hItem) ) {
				internalTreeItemMod_ = true;
				TreeItem* item = treeControl_->getItemFromKey( treeview->itemOld.lParam );
				if ( NULL != item ) {
					item->setSelected( false );
				}
				internalTreeItemMod_ = false;
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
		
		case NM_RCLICK :{
			POINT pt = {0,0};
			GetCursorPos( &pt );
			ScreenToClient( treeWnd_, &pt );
			Point tmpPt( pt.x, pt.y );

			uint32 keyMask = kmUndefined;
			if ( (::GetKeyState(VK_CONTROL) & 0x8000) != 0 ) {
				keyMask |= kmCtrl;
			}

			if ( (::GetKeyState(VK_SHIFT) & 0x8000) != 0 ) {
				keyMask |= kmShift;
			}

			if ( (::GetKeyState(VK_MENU) & 0x8000) != 0 ) {
				keyMask |= kmAlt;
			}

			VCF::MouseEvent event( getControl(), Control::MOUSE_CLICK,
						mbmRightButton, keyMask, &tmpPt );
			if ( peerControl_ ) {
					peerControl_->handleEvent( &event );
			}
		}
		break;

/*
JC
Do we need these? What advantage does processing these events have for us???
		

		case NM_CLICK :{
			POINT pt = {0,0};
			GetCursorPos( &pt );
			ScreenToClient( treeWnd_, &pt );
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
			NMHDR* notificationHdr = (LPNMHDR)lParam;
			if ( notificationHdr->hwndFrom == headerWnd_ ) {
				wndProcResult = headerCustomDraw( (NMCUSTOMDRAW*)lParam );
			}
			else {
				wndProcResult = treeCustomDraw( (NMTVCUSTOMDRAW*)lParam );
			}
			result = true;	
		}
		break;

		case WM_SIZE : {
			result = true;
			AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			
			int hdrHeight = 0;
			if ( NULL != headerWnd_ ) {
				RECT r = {0};
				GetWindowRect( headerWnd_, &r );

				WINDOWPOS wp = {0};
				HDLAYOUT layout = {0};
				layout.prc = &r;
				layout.pwpos = &wp;		

				::SendMessage( headerWnd_, HDM_LAYOUT, 0, (LPARAM)&layout );

				hdrHeight = headerEnabled_ ? wp.cy : 0;
				
				MoveWindow( headerWnd_, 0, 0, LOWORD(lParam), hdrHeight, TRUE );
			}

			if ( NULL != this->treeWnd_ ) {
				MoveWindow( treeWnd_, 0, hdrHeight, LOWORD(lParam), HIWORD(lParam) - hdrHeight, TRUE );
			}



			

			wndProcResult = defaultWndProcedure( message, wParam, lParam );

			
			if ( NULL != headerWnd_ ) {
				if ( ::IsWindowVisible(headerWnd_) ) {
					/*
					SCROLLINFO si = {0};
					si.cbSize = sizeof(SCROLLINFO);
					si.fMask = SIF_PAGE | SIF_RANGE;
					GetScrollInfo( treeWnd_, SB_VERT, &si );
					si.nMax += hdrHeight;
					::SetScrollInfo( treeWnd_, SB_VERT, &si, TRUE );

					int hdrWidth = 0;
					int count = SendMessage(headerWnd_,HDM_GETITEMCOUNT,0,0);
					for (size_t i=0;i<count;i++ ) {
						RECT r = {0};
						SendMessage( headerWnd_,	HDM_GETITEMRECT, i, (LPARAM)&r );
						hdrWidth += (r.right - r.left);
					}

					si.fMask = SIF_PAGE | SIF_RANGE;
					GetScrollInfo( treeWnd_, SB_HORZ, &si );
					si.nMax = hdrWidth;
					::SetScrollInfo( treeWnd_, SB_HORZ, &si, TRUE );
					*/
				}
			}
			
		}
		break;

		case HDN_TRACKW:  case HDN_ENDTRACKW : {
			InvalidateRect( treeWnd_, NULL, TRUE );
		}
		break;

		case HDN_GETDISPINFOW : {
			NMHDDISPINFOW* dispInfo = (NMHDDISPINFOW*)lParam;
			
			ColumnModel* cm = treeControl_->getColumnModel();
			
			
			if ( NULL != cm ) {
				if ( dispInfo->mask & HDI_IMAGE ) {
					ColumnItem* item = treeControl_->getColumnItem( (uint32)dispInfo->lParam );
					dispInfo->iImage = item->getImageIndex();
				}
				
				if ( dispInfo->mask & HDI_TEXT ) {								
					
					String caption = cm->getAsString( dispInfo->lParam ) ;
					
					unsigned int size = VCF::minVal<unsigned int>( caption.size(), dispInfo->cchTextMax );
					caption.copy( dispInfo->pszText, size );
					if ( size < dispInfo->cchTextMax ) {
						dispInfo->pszText[size] = '\0';
					}
				}
			}
		}
		break;

		case WM_NOTIFY: {
			result = true;			
			if ( !peerControl_->isDestroying() ) {
				NMHDR* notificationHdr = (LPNMHDR)lParam;
				handleEventMessages( notificationHdr->code, wParam, lParam, wndProcResult );

				if ( notificationHdr->hwndFrom == headerWnd_ && notificationHdr->code == NM_CUSTOMDRAW ) {
				//	wndProcResult = headerCustomDraw( (NMCUSTOMDRAW*)lParam );
				}
				else {
					
				}
				
			}
		}
		break;


/*
		case WM_NOTIFY: {
			
			if ( !peerControl_->isDestroying() ) {
				NMHDR* notificationHdr = (LPNMHDR)lParam;
				Win32Object* win32Obj = Win32Object::getWin32ObjectFromHWND( notificationHdr->hwndFrom );
				if ( NULL != win32Obj ){
					win32Obj->handleEventMessages( notificationHdr->code, wParam, lParam, wndProcResult );
				}
				else {
					NMHDR* notificationHdr = (LPNMHDR)lParam;
					
				}
			}
		}
		break;
*/
		default: {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
			//result = CallWindowProc( oldTreeWndProc_, hwnd_, message, wParam, lParam );

		}
		break;
	}
	return result;
}

LRESULT Win32Tree::treeCustomDraw( NMTVCUSTOMDRAW* drawInfo )
{
	LRESULT result = CDRF_DODEFAULT;
	if ( NULL == drawInfo )	{
		return result;
	}

	switch ( drawInfo->nmcd.dwDrawStage ) {					

		case CDDS_PREPAINT : {
			result = CDRF_NOTIFYITEMDRAW;// | CDRF_NOTIFYPOSTPAINT;
			if ( NULL != headerWnd_ ) {
				if ( ::IsWindowVisible(headerWnd_) ) {					
					int count = SendMessage(headerWnd_,HDM_GETITEMCOUNT,0,0);

					if ( headerRects_.size() != count ) {
						headerRects_.resize(count);
					}

					for ( int i=0;i<count;i++ ) {						
						SendMessage( headerWnd_, HDM_GETITEMRECT, i, (LPARAM)&headerRects_[i] );
					}
				}
			}
		}
		break;

		case CDDS_ITEMPREPAINT : {						

			result = CDRF_NOTIFYPOSTPAINT;

			if ( treeControl_->itemExists( drawInfo->nmcd.lItemlParam ) ) {
				TreeItem* item = treeControl_->getItemFromKey( drawInfo->nmcd.lItemlParam );
				if ( !item->isFontDefault() ) {
					Color* fc = item->getFont()->getColor();
					
					drawInfo->clrText = (COLORREF) fc->getColorRef32();
					

					Win32Font* fontPeer = dynamic_cast<Win32Font*>( item->getFont()->getFontPeer() );
					HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( fontPeer );
					if ( NULL != fontHandle ){
						::SelectObject( drawInfo->nmcd.hdc, fontHandle );
						result |= CDRF_NEWFONT;
					}
				}							
			}


			if ( headerEnabled_ ) {							
				result |= CDRF_SKIPDEFAULT;
				drawItem( drawInfo );				
			}
		}
		break;

		case CDDS_ITEMPOSTPAINT : {						
			result = CDRF_DODEFAULT;

			if ( headerEnabled_ ) {
				drawInfo->nmcd.rc.left = headerRects_[0].left;
				drawInfo->nmcd.rc.right = headerRects_[0].right;
			}

			if ( !headerEnabled_ ) {
				
				bool useItemPaint = false;
				Rect itemRect;
				itemRect.left_ = drawInfo->nmcd.rc.left;
				itemRect.top_ = drawInfo->nmcd.rc.top;
				itemRect.right_ = drawInfo->nmcd.rc.right;
				itemRect.bottom_ = drawInfo->nmcd.rc.bottom;
				
				if ( treeControl_->itemExists( drawInfo->nmcd.lItemlParam ) ) {
					TreeItem* item = treeControl_->getItemFromKey( drawInfo->nmcd.lItemlParam );
					if ( item->canPaint() ) {
						if ( NULL != currentCtx_ ) {
							item->paint( currentCtx_, &itemRect );
							useItemPaint = true;
						}								
					}
				}
				
				if ( !useItemPaint ) {
					TreeItemState itemState;
					treeControl_->paintItem( currentCtx_, itemRect, drawInfo->nmcd.lItemlParam, itemState );
				}
			}


		}
		break;

		default : {

			result = CDRF_DODEFAULT;
		}
		break;
	}
			
	return result;
}

LRESULT Win32Tree::headerCustomDraw( NMCUSTOMDRAW* drawInfo )
{
	LRESULT result = 0;
	switch ( drawInfo->dwDrawStage ) {
		case CDDS_PREPAINT : {
			result = CDRF_NOTIFYITEMDRAW;
			
			RECT r;
			GetClientRect( headerWnd_, &r );
			
			RECT rLast;
			int index = -1;
			index = Header_GetItemCount(headerWnd_) - 1;
			if ( index >= 0 ) {
				Header_GetItemRect( headerWnd_, index, &rLast );				
				r.left = rLast.right;
			}
			FillRect( drawInfo->hdc, &r, (HBRUSH) (COLOR_3DFACE + 1) );
			InvalidateRect( treeWnd_, NULL, TRUE );
		}
		break;

		case CDDS_ITEMPREPAINT : {								
			result = CDRF_NOTIFYPOSTPAINT;

			uint32 index = drawInfo->dwItemSpec;
			ColumnItem* item = NULL;
			
			HDITEM headerItem;
			memset( &headerItem, 0, sizeof(HDITEM) );
			headerItem.mask = HDI_FORMAT | HDI_LPARAM;
			if ( Header_GetItem( headerWnd_, index, &headerItem ) ) {
				item = treeControl_->getColumnItem( (uint32)headerItem.lParam );
				if ( NULL != item ) {
					if ( !item->isFontDefault() ) {
						
						Color* fc = item->getFont()->getColor();
						
						SetTextColor( drawInfo->hdc, (COLORREF) fc->getColorRef32() );
						
						Win32Font* fontPeer = dynamic_cast<Win32Font*>( item->getFont()->getFontPeer() );
						HFONT fontHandle = Win32FontManager::getFontHandleFromFontPeer( fontPeer );
						if ( NULL != fontHandle ){
							
							oldHeaderFont_ = (HFONT)::SelectObject( drawInfo->hdc, fontHandle );
							
							result |= CDRF_NEWFONT;
						}
					}
				}
			}
			
		}
		break;

		case CDDS_ITEMPOSTPAINT : {
			
			uint32 index = drawInfo->dwItemSpec;
			ColumnItem* item = NULL;
			
			HDITEM headerItem;
			memset( &headerItem, 0, sizeof(HDITEM) );
			headerItem.mask = HDI_FORMAT | HDI_LPARAM;
			if ( Header_GetItem( headerWnd_, index, &headerItem ) ) {
				item = treeControl_->getColumnItem( (uint32)headerItem.lParam );
			}
			

			if ( NULL != item ) {
				if ( item->canPaint() ) {
					GraphicsContext gc( (OSHandleID)drawInfo->hdc );
					Rect rect( drawInfo->rc.left, drawInfo->rc.top, drawInfo->rc.right, drawInfo->rc.bottom );
					item->paint( &gc, &rect );
					gc.getPeer()->setContextID( 0 );
				}

			}

			if ( NULL != oldHeaderFont_ ) {
				::SelectObject( drawInfo->hdc, oldHeaderFont_ );
				oldHeaderFont_ = NULL;
			}
			result = CDRF_SKIPDEFAULT;										

		}
		break;

		default : {
			result = CDRF_DODEFAULT;
		}
		break;
	}
	return 0;
}

#define BUTTON_SIZE 9

void Win32Tree::drawItem( NMTVCUSTOMDRAW* drawInfo )
{
	if ( headerRects_.empty() ) {
		return;
	}

	int dcs = SaveDC( drawInfo->nmcd.hdc );
	
	TVITEM tvItem = {0};
	tvItem.mask = TVIF_STATE;
	tvItem.hItem = (HTREEITEM)drawInfo->nmcd.dwItemSpec;
	TreeView_GetItem( treeWnd_, &tvItem );

	int offsetX = 0;
	int offsetY = 0;
	

	SCROLLINFO si = {0};
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_POS;
	GetScrollInfo( treeWnd_, SB_HORZ, &si );
	offsetX -= si.nPos;
	

	//col 1
	int indent = SendMessage( treeWnd_, TVM_GETINDENT, 0, 0 );

	RECT bkRect = drawInfo->nmcd.rc;

	drawInfo->nmcd.rc.left = headerRects_[0].left + indent * drawInfo->iLevel;
	drawInfo->nmcd.rc.right = headerRects_[0].right;
	bkRect.right = headerRects_.back().right;
	
	int x = drawInfo->nmcd.rc.left;
	int y = drawInfo->nmcd.rc.top;
	
	
	::SetTextColor( drawInfo->nmcd.hdc, drawInfo->clrText );
	::SetBkColor( drawInfo->nmcd.hdc, drawInfo->clrTextBk );
	
	HBRUSH bk = CreateSolidBrush( drawInfo->clrTextBk );
	FillRect( drawInfo->nmcd.hdc, &bkRect, bk );

	DeleteObject( bk );

	TreeModel* tm = treeControl_->getTreeModel();
	TreeModel::Key key = (TreeModel::Key)drawInfo->nmcd.lItemlParam;

	bool hasChildren = !tm->isLeaf( key );


	String s = tm->getAsString( key );
	VCFChar tmp[255];
	size_t sz = minVal<size_t>(s.length(),254);
	s.copy(tmp,sz);
	tmp[sz] = 0;

	SIZE tmpSz = {0};
	::GetTextExtentPoint32W( drawInfo->nmcd.hdc, tmp, sz, &tmpSz );	
	
	RECT btn;
	btn.left = x+offsetX+ (indent )/2 - BUTTON_SIZE / 2; 
	btn.top = y+offsetY + (drawInfo->nmcd.rc.bottom-drawInfo->nmcd.rc.top) /2 - BUTTON_SIZE/2;
	btn.right = btn.left + BUTTON_SIZE;
	btn.bottom = btn.top + BUTTON_SIZE;
/*
	if ( hasLines_ && hasChildren && btn.right < drawInfo->nmcd.rc.right ) {
		HPEN p = CreatePen( PS_GEOMETRIC | PS_DOT, 0, RGB(120,120,120) );
		SelectObject( drawInfo->nmcd.hdc, p );

		int lx = x+offsetX+ (indent )/2;
		int ly = y+offsetY + tmpSz.cy/2;

		

		::MoveToEx( drawInfo->nmcd.hdc, 
						lx, ly, NULL);

		::LineTo( drawInfo->nmcd.hdc, 
						lx, drawInfo->nmcd.rc.bottom);


		HTREEITEM parent = TreeView_GetParent( hwnd_, tvItem.hItem );
		while ( parent ) {

			lx -= indent;
			::MoveToEx( drawInfo->nmcd.hdc, 
							lx, drawInfo->nmcd.rc.top, NULL);

			::LineTo( drawInfo->nmcd.hdc, 
							lx, drawInfo->nmcd.rc.bottom);
			

			parent = TreeView_GetParent( hwnd_, parent );
		}
		
		DeleteObject(p);
	}
*/
	
	if ( hasButtons_ && hasChildren && btn.right < drawInfo->nmcd.rc.right ) {	
		HPEN p = CreatePen( PS_SOLID, 1, RGB(120,120,120) );
		SelectObject( drawInfo->nmcd.hdc, p );
		

		::Rectangle(drawInfo->nmcd.hdc, btn.left,btn.top, btn.right,btn.bottom);

		DeleteObject(p);

		p = CreatePen( PS_SOLID, 1, RGB(0,0,0) );
		SelectObject( drawInfo->nmcd.hdc, p );

		::MoveToEx( drawInfo->nmcd.hdc, 
					btn.left + 2, 
					btn.top + BUTTON_SIZE / 2, NULL);

		::LineTo( drawInfo->nmcd.hdc,
					btn.right - 2, 
					btn.top + BUTTON_SIZE / 2);


		if ( (tvItem.state  & TVIS_EXPANDED) == 0 ) {
			::MoveToEx( drawInfo->nmcd.hdc, 
						btn.left + BUTTON_SIZE / 2, 
						btn.top + 2, NULL);

			::LineTo( drawInfo->nmcd.hdc,
						btn.left + BUTTON_SIZE / 2, 
						btn.bottom - 2);
		}
		DeleteObject(p);
	}
	
	

	RECT r = drawInfo->nmcd.rc;
	r.left += indent;

	r.left -= si.nPos;
	r.right -= si.nPos;	

	if ( r.right - r.left > 3 ) {
		r.left -= 2;
		if ( (drawInfo->nmcd.uItemState & CDIS_FOCUS ) ) {
			DrawFocusRect( drawInfo->nmcd.hdc, &r );
		}

		r.left += 2;

		DrawTextExW( drawInfo->nmcd.hdc, tmp, sz, &r, 
						DT_LEFT | DT_END_ELLIPSIS | DT_EXPANDTABS | DT_SINGLELINE | DT_VCENTER,
						NULL );
	}

	TreeItem* item = NULL;
	if ( treeControl_->itemExists(key) ) {
		item = treeControl_->getItemFromKey( key );
	}

	Rect itemRect;
	itemRect.left_ = r.left;
	itemRect.top_ = r.top;
	itemRect.right_ = r.right;
	itemRect.bottom_ = r.bottom;
	bool useItemPaint = false;
	if ( NULL != item ) {
		if ( item->canPaint() ) {			
			item->paint( currentCtx_, &itemRect );
			useItemPaint = true;
		}
	}

	if ( !useItemPaint ) {
		TreeItemState itemState;
		treeControl_->paintItem( currentCtx_, itemRect, key, itemState );
	}

	ColumnModel* cm = treeControl_->getColumnModel();
	int count = SendMessage(headerWnd_,HDM_GETITEMCOUNT,0,0);
	for (size_t i=1;i<count;i++ ) {
		s = tm->getSubItemAsString( key, i-1 );	
		
		if ( !s.empty() ) {
			r.left = headerRects_[i].left + 5;
			r.right = headerRects_[i].right;

			r.left -= si.nPos;
			r.right -= si.nPos;

			if ( r.right - r.left > 3 ) {
				size_t sz = minVal<size_t>(s.length(),254);
				s.copy(tmp,sz);
				tmp[sz] = 0;

				DrawTextExW( drawInfo->nmcd.hdc, tmp, sz, &r, 
						DT_LEFT | DT_END_ELLIPSIS | DT_EXPANDTABS | DT_SINGLELINE | DT_VCENTER,
						NULL );
			}
		}


		if ( NULL != item ) {
			uint32 siCount = item->getSubItemCount();
			if ( (i-1) < siCount ) {
				useItemPaint = false;

				if ( treeControl_->subItemExists( key, i-1 ) ) {					
					TreeSubItem* subItem = item->getSubItem( i-1 );
					if ( NULL != subItem ) {
						if ( subItem->canPaint() ) {
							Rect itemRect;
							itemRect.left_ = r.left;
							itemRect.top_ = r.top;
							itemRect.right_ = r.right;
							itemRect.bottom_ = r.bottom;
							subItem->paint( currentCtx_, &itemRect );
						}
					}
				}

				if ( !useItemPaint ) {
					TreeItemState itemState;
					itemState.setAsSubItem(true);
					treeControl_->paintSubItem( currentCtx_, itemRect, key, i-1, itemState );
				}
			}
		}
	}

	::RestoreDC( drawInfo->nmcd.hdc, dcs );
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
		tvItem.mask |= TVIF_STATE;
		
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
		
		tvItem.state = INDEXTOSTATEIMAGEMASK(1);
		tvItem.stateMask = TVIS_STATEIMAGEMASK;
		
		tvItem.cchTextMax = 0;					
		tvItem.pszText = LPSTR_TEXTCALLBACKW;
		tvItem.lParam = (LPARAM)key;
		
		insert.hParent = parent;
		insert.hInsertAfter = TVI_LAST;
		insert.item = tvItem;
		
		hItem = (HTREEITEM) ::SendMessage( treeWnd_, TVM_INSERTITEMW, 0, (LPARAM)&insert );
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
		
		hItem = (HTREEITEM) ::SendMessage( treeWnd_, TVM_INSERTITEMA, 0, (LPARAM)&insert );
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

Rect Win32Tree::getItemImageRect( const TreeModel::Key& itemKey )
{
	Rect result;

	
	return result;
}

Rect Win32Tree::getItemRect( const TreeModel::Key& itemKey )
{
	Rect result;
	
	std::map<TreeModel::Key,HTREEITEM>::iterator it = treeItems_.find( itemKey );
	if ( it != treeItems_.end() ){
		
			RECT r;
			memset(&r,0,sizeof(r));
			TreeView_GetItemRect( treeWnd_, it->second, &r, TRUE );				

			result.left_ = r.left;
			result.top_ = r.top;
			result.right_ = r.right;
			result.bottom_ = r.bottom;
		
	}	

	return result;
}

TreeModel::Key Win32Tree::hitTest( const Point& pt )
{
	TreeModel::Key result = TreeModel::InvalidKey;

	TVHITTESTINFO hitTestInfo;
	memset( &hitTestInfo, 0, sizeof(TVHITTESTINFO) );
	
	hitTestInfo.pt.x = pt.x_;
	hitTestInfo.pt.y = pt.y_;

	HTREEITEM hItem = TreeView_HitTest( treeWnd_, &hitTestInfo );
	if ( NULL != hItem ) {
		TVITEM tvItem;
		memset( &tvItem, 0, sizeof(TVITEM) );
		tvItem.mask = TVIF_PARAM | TVIF_HANDLE ;
		tvItem.hItem = hItem;
		if ( TreeView_GetItem( treeWnd_, &tvItem ) ) {
			result = (TreeModel::Key)tvItem.lParam;
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
	TreeView_SetImageList( treeWnd_, imageListCtrl_, TVSIL_STATE );

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

		TreeView_SetImageList( treeWnd_, stateImageListCtrl_, TVSIL_STATE );


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
	return ( TVS_EDITLABELS & ::GetWindowLongPtr( treeWnd_, GWL_STYLE ) ) ? true : false;
}

void Win32Tree::setAllowLabelEditing( const bool& allowLabelEditing )
{
	LONG_PTR style = ::GetWindowLongPtr( treeWnd_, GWL_STYLE );
	if ( allowLabelEditing ) {
		style |= TVS_EDITLABELS;
	}
	else {
		style &= ~TVS_EDITLABELS;
	}
	::SetWindowLongPtr( treeWnd_, GWL_STYLE, style );

	::SetWindowPos( treeWnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );

	::UpdateWindow( treeWnd_ );
}

void Win32Tree::onControlModelChanged( Event* e )
{
	CallBack* ev = getCallback( "Win32Tree::onTreeModelChanged" );

	if ( NULL == ev ) {
		ev = new ClassProcedure1<ModelEvent*,Win32Tree>( this,
													&Win32Tree::onTreeModelChanged,
													"Win32Tree::onTreeModelChanged" );
	}

	treeItems_.clear();			
	TreeView_DeleteAllItems( treeWnd_ );

	Model* model = treeControl_->getViewModel();
	if ( NULL != model ) {
		model->ModelChanged += ev;
		TreeModel* tm = treeControl_->getTreeModel();	
		
		std::vector<TreeModel::Key> children;
		tm->getChildren(TreeModel::RootKey,children);
		std::vector<TreeModel::Key>::iterator it = children.begin();
		while ( it != children.end() ) {
			addTreeItem( *it, NULL );
			++it;
		}
	}
}

void Win32Tree::onTreeModelChanged( ModelEvent* event )
{
	switch ( event->getType() ) {
		case TreeModel::ItemAdded : {
			TreeModelEvent* te = (TreeModelEvent*)event;
			if ( TreeModel::RootKey ==  te->parentKey ) {
				std::map<TreeModel::Key,HTREEITEM>::iterator found =
					treeItems_.find( te->key );
				if ( found == treeItems_.end() ){
					//only add root items - the rest will be added 
					//as needed
					addTreeItem( te->key, NULL );
				}
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

					TreeView_GetItem( treeWnd_, &tvItem );

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
				TreeView_DeleteItem( treeWnd_, hItem );
			}
		}
		break;

		case TreeModel::ContentsDeleted : {
			treeItems_.clear();
			
			TreeView_DeleteAllItems( treeWnd_ );
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
				TreeView_Expand( treeWnd_, found->second, TVE_EXPAND );
			}
			else {
				TreeView_Expand( treeWnd_, found->second, TVE_COLLAPSE | TVE_COLLAPSERESET );
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
			/*
			TVITEM tvItem = {0};
			tvItem.hItem = hItem;
			tvItem.mask = TVIF_STATE ;
			tvItem.stateMask = TVIS_SELECTED;
			
			tvItem.state = item->isSelected() ? tvItem.state |= TVIS_SELECTED : tvItem.state &= ~TVIS_SELECTED;

			

			TreeView_SetItem( treeWnd_, &tvItem );			
			*/

			TreeView_SelectItem( treeWnd_, hItem );
		}
	}
}

void Win32Tree::registerHeaderWndProc()
{
	if ( NULL == headerWnd_ ) {
		headerWnd_ = CreateWindowExW( 0, WC_HEADERW, NULL, WS_CHILD | WS_VISIBLE |  
										HDS_BUTTONS | HDS_HORZ | HDS_FULLDRAG,
										0, 0,
										0, CW_USEDEFAULT,
										hwnd_,NULL, NULL, NULL);


		::SetWindowLongPtr( headerWnd_, GWLP_USERDATA, (LONG_PTR)this );
		oldHeaderWndProc_ = (WNDPROC)(LONG_PTR) ::SetWindowLongPtr( headerWnd_, GWLP_WNDPROC, (LONG_PTR)Win32Tree::HeaderWndProc );

		HFONT f = (HFONT)SendMessage( hwnd_, WM_GETFONT, 0, 0 );

		SendMessage( headerWnd_, WM_SETFONT, (WPARAM)f, MAKELPARAM(TRUE,0) );

	}
}

void Win32Tree::enableHeader( const bool& val )
{
	if ( headerEnabled_ != val ) {
		headerEnabled_ = val;

		registerHeaderWndProc();
		
		int count = Header_GetItemCount( headerWnd_ );
		for (int i=0;i<count;i++ ) {
			Header_DeleteItem( headerWnd_, i );
		}
		
		if ( headerEnabled_ ) {
			
			ColumnModel* columnModel = treeControl_->getColumnModel();
			

			CallBack* cb = getCallback("Win32Tree::onColumnModelChanged");
			if ( NULL == cb ) {
				cb = new ClassProcedure1<ModelEvent*,Win32Tree>(this, &Win32Tree::onColumnModelChanged, "Win32Tree::onColumnModelChanged" );
			}

			columnModel->ModelChanged += cb;

			size_t colCount = columnModel->getCount();
			for (size_t j=0;j<colCount;j++ ) {
				HDITEMW headerItem;
				memset( &headerItem, 0, sizeof(headerItem) );
				headerItem.mask = HDI_LPARAM | HDI_WIDTH|HDI_FORMAT|HDI_TEXT;
				//HDI_LPARAM | | HDI_IMAGE | | ;
				if ( headerImageListCtrl_ != NULL ) {
					headerItem.mask |= HDI_IMAGE;
				}
				
				headerItem.lParam = (LPARAM)j;
				headerItem.iImage = I_IMAGECALLBACK;
				headerItem.pszText = LPSTR_TEXTCALLBACKW;
				headerItem.cxy = 80;
				headerItem.fmt = HDF_LEFT;	
				
				int err = SendMessage( headerWnd_, HDM_INSERTITEMW, (WPARAM)j, (LPARAM)&headerItem );
			}
			ShowWindow( headerWnd_, SW_NORMAL );		
		}
		else {
			ShowWindow( headerWnd_, SW_HIDE );
		}
	}
}

LRESULT Win32Tree::treeWndPaint(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;
	PAINTSTRUCT ps;			

	HDC dc = BeginPaint( hWnd, &ps );			
	
	DWORD style = GetWindowLong( hWnd, GWL_STYLE );
	hasLines_ = (style & TVS_HASLINES) ? true : false;
	hasButtons_ = (style & TVS_HASBUTTONS) ? true : false;	
	
	RECT paintRect;
	GetClientRect( hwnd_, &paintRect );
	
	//paintRect = ps.rcPaint;
	
	if ( NULL == memDC_ ) {
		//create here
		HDC tmpDC = ::GetDC(0);
		memDC_ = ::CreateCompatibleDC( tmpDC );
		::ReleaseDC( 0,	tmpDC );
	}
	
	
	ControlGraphicsContext ctrlCtx(peerControl_);
	currentCtx_ = &ctrlCtx;
	
	currentCtx_->setViewableBounds( Rect(paintRect.left, paintRect.top,
		paintRect.right, paintRect.bottom ) );
	
	memBMP_ = ::CreateCompatibleBitmap( dc,
		paintRect.right - paintRect.left,
		paintRect.bottom - paintRect.top );
	
	memDCState_ = ::SaveDC( memDC_ );
	originalMemBMP_ = (HBITMAP)::SelectObject( memDC_, memBMP_ );
	
	POINT oldOrg;
	memset(&oldOrg,0,sizeof(oldOrg));
	::SetViewportOrgEx( memDC_, -paintRect.left, -(paintRect.top), &oldOrg );			
	
	Color* color = peerControl_->getColor();
	COLORREF backColor = color->getColorRef32();
	
	HBRUSH bkBrush = CreateSolidBrush( backColor );
	FillRect( memDC_, &paintRect, bkBrush );
	DeleteObject( bkBrush );
	
	
	currentCtx_->getPeer()->setContextID( (OSHandleID)memDC_ );
	
	
	
	
	int gcs = currentCtx_->saveState();
	
	//paint the control here - double buffered
	
	peerControl_->internal_beforePaint( currentCtx_ );

	peerControl_->paint( currentCtx_ );

	peerControl_->internal_afterPaint( currentCtx_ );


	currentCtx_->restoreState( gcs );
				  
	
	
	//reset back to original origin
	::SetViewportOrgEx( memDC_, paintRect.left, paintRect.top, &oldOrg );
	
	//let the tree control's DefWndProc do windwos painting
	
	if ( System::isUnicodeEnabled() ) {
		result = CallWindowProcW( oldTreeWndProc_, hWnd, WM_PAINT, (WPARAM)memDC_, lParam );
	}
	else {
		result = CallWindowProcA( oldTreeWndProc_, hWnd, WM_PAINT, (WPARAM)memDC_, lParam );
	}
	
	
	::BitBlt( dc, paintRect.left, paintRect.top,
		paintRect.right - paintRect.left,
		paintRect.bottom - paintRect.top,
		memDC_, 0, 0, SRCCOPY );
	
	::RestoreDC ( memDC_, memDCState_ );
	
	::DeleteObject( memBMP_ );
	
	memBMP_ = NULL;
	originalMemBMP_ = NULL;
	memDCState_ = 0;
	
	
	
	currentCtx_ = NULL;
	
	
	EndPaint( hWnd, &ps );
	
	return result;
}

LRESULT CALLBACK Win32Tree::TreeWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	Win32Tree* tree = (Win32Tree*)(LONG_PTR) ::GetWindowLongPtr( hWnd, GWLP_USERDATA );
	switch ( message ) {
		case WM_LBUTTONUP :{
			tree->handleEventMessages( message, wParam, lParam, result );

			//wndProcResult = tree->defaultWndProcedure( message, wParam, lParam );	
			
			//hit test to see if we pressed a state icon
			if ( NULL != tree->stateImageListCtrl_ ) {
				TVHITTESTINFO hitTestInfo;
				memset( &hitTestInfo, 0, sizeof(TVHITTESTINFO) );
				
				hitTestInfo.pt.x = LOWORD( lParam );
				hitTestInfo.pt.y = HIWORD( lParam );
				HTREEITEM hItem = TreeView_HitTest( hWnd, &hitTestInfo );
				if ( NULL != hItem ) {
					if( hitTestInfo.flags & TVHT_ONITEMSTATEICON ) {
						TVITEM tvItem;
						memset( &tvItem, 0, sizeof(TVITEM) );
						tvItem.mask = TVIF_PARAM | TVIF_HANDLE ;
						tvItem.hItem = hItem;
						if ( TreeView_GetItem( hWnd, &tvItem ) ) {
							TreeItem* item = tree->treeControl_->getItemFromKey( tvItem.lParam );
							if ( NULL != item ) {
								
								ItemEvent event( item, TreeControl::ITEM_STATECHANGE_REQUESTED );
								
								tree->treeControl_->handleEvent( &event );


								
								tvItem.mask = TVIF_STATE | TVIF_HANDLE;
								tvItem.state = INDEXTOSTATEIMAGEMASK( item->getStateImageIndex()+1 );
								tvItem.stateMask = TVIS_STATEIMAGEMASK;
								TreeView_SetItem( hWnd, &tvItem );
								
							}
						}
					}
				}
			}			
		}
		break;

		case WM_ERASEBKGND : {

			Color* color = tree->treeControl_->getColor();
			COLORREF clrRef = color->getColorRef32();
			COLORREF currentClr = TreeView_GetBkColor( hWnd );

			if ( currentClr != clrRef ) {
				TreeView_SetBkColor( hWnd, clrRef );
			}


			result = 0;
		}
		break;

		case WM_PAINT:{
			result = tree->treeWndPaint( hWnd, message, wParam, lParam );		
		}
		break;

		default : {
			if ( System::isUnicodeEnabled() ) {
				result = CallWindowProcW( tree->oldTreeWndProc_, hWnd, message, wParam, lParam );
			}
			else {
				result = CallWindowProcA( tree->oldTreeWndProc_, hWnd, message, wParam, lParam );
			}
		}
		break;
	}

	return result;
}


LRESULT CALLBACK Win32Tree::HeaderWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	Win32Tree* tree = (Win32Tree*)(LONG_PTR) ::GetWindowLongPtr( hWnd, GWLP_USERDATA );

	switch ( message ) {
	
		case WM_ERASEBKGND : {

			result = 0;
		}
		break;
/*
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
		*/

		default : {
			if ( System::isUnicodeEnabled() ) {
				result = CallWindowProcW( tree->oldHeaderWndProc_, hWnd, message, wParam, lParam );
			}
			else {
				result = CallWindowProcA( tree->oldHeaderWndProc_, hWnd, message, wParam, lParam );
			}

		}
		break;
	}


	return result;
}

void Win32Tree::setColumnWidth( const uint32& index, const double& width, ColumnAutosizeType type )
{
	if ( NULL != headerWnd_ ) {
		HDITEMW item = {0};
		item.mask = HDI_WIDTH;
		item.cxy = width;
		SendMessage( headerWnd_, HDM_SETITEMW, index, (LPARAM)&item );
	}
}

double Win32Tree::getColumnWidth( const uint32& index )
{
	double result = 0.0;
	if ( NULL != headerWnd_ ) {
		HDITEMW item = {0};
		item.mask = HDI_WIDTH;
		SendMessage( headerWnd_, HDM_GETITEMW, index, (LPARAM)&item );

		result = item.cxy;
	}

	return result;
}

TextAlignmentType Win32Tree::getColumnTextAlignment( const uint32& index )
{
	TextAlignmentType result;

	if ( NULL != headerWnd_ ) {
		HDITEMW item = {0};
		item.mask = HDI_FORMAT;
		SendMessage( headerWnd_, HDM_GETITEMW, index, (LPARAM)&item );

		if ( item.fmt & HDF_LEFT ) {
			result = taTextLeft;
		}
		else if ( item.fmt & HDF_CENTER ) {
			result = taTextCenter;
		}
		else if ( item.fmt & HDF_RIGHT ) {
			result = taTextRight;
		}
	}

	return result;
}

void Win32Tree::setColumnTextAlignment( const uint32& index, const TextAlignmentType& val )
{
	if ( NULL != headerWnd_ ) {
		HDITEMW item = {0};
		item.mask = HDI_FORMAT;

		if ( val == taTextLeft ) {
			item.fmt = HDF_LEFT;
		}
		else if ( val == taTextCenter ) {
			item.fmt = HDF_CENTER;
		}
		else if ( val == taTextRight ) {
			item.fmt = HDF_RIGHT;
		}

		item.fmt |= HDF_STRING ;
		SendMessage( headerWnd_, HDM_SETITEMW, index, (LPARAM)&item );
	}
}

void Win32Tree::onColumnModelChanged( ModelEvent* event )
{
	switch ( event->getType() ) {
		case lmeItemAdded : {
			ListModelEvent* lme = (ListModelEvent*)event;
			 
			HDITEMW headerItem;
			memset( &headerItem, 0, sizeof(headerItem) );
			headerItem.mask = HDI_LPARAM | HDI_WIDTH|HDI_FORMAT|HDI_TEXT;//
			if ( headerImageListCtrl_ != NULL ) {
				headerItem.mask |= HDI_IMAGE;
			}
			//HDI_LPARAM | | HDI_IMAGE | | ;				
			
			headerItem.lParam = (LPARAM)lme->index;
			headerItem.iImage = I_IMAGECALLBACK;
			headerItem.pszText = LPSTR_TEXTCALLBACKW;
			headerItem.cxy = 80;
			headerItem.fmt = HDF_LEFT;	
			 
			SendMessage( headerWnd_, HDM_INSERTITEMW, (WPARAM)lme->index, (LPARAM)&headerItem );
		}
		break;

		case lmeItemRemoved : {
			ListModelEvent* lme = (ListModelEvent*)event;
			SendMessage( headerWnd_, HDM_DELETEITEM, (WPARAM)lme->index, 0 );
		}
		break;
	}
}

void Win32Tree::setDisplayOptions( uint32 displayOptions )
{
	bool showHeader = (displayOptions & tdoShowColumnHeader) ? true : false;

	enableHeader( showHeader );

	LONG_PTR style = ::GetWindowLongPtr( treeWnd_, GWL_STYLE );

	if ( displayOptions & tdoShowHierarchyLines ) {
		style |= TVS_HASLINES;
	}
	else {
		style &= ~TVS_HASLINES;
	}

	if ( displayOptions & tdoShowFullRowSelection ) {
		style |= TVS_FULLROWSELECT;
	}
	else {
		style &= ~TVS_FULLROWSELECT;
	}

	
	
	::SetWindowLongPtr( treeWnd_, GWL_STYLE, style );

	::SetWindowPos( treeWnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );

	::UpdateWindow( treeWnd_ );

}

void Win32Tree::setHeaderImageList( ImageList* imageList )
{
	if ( NULL != imageListCtrl_ ) {
		BOOL err = ImageList_Destroy( headerImageListCtrl_ );
	}
	headerImageListCtrl_ = NULL;

	if ( NULL != headerWnd_ ) {
		Header_SetImageList( headerWnd_, headerImageListCtrl_ );
	}

	if ( imageList != NULL ) {
		headerImageListCtrl_ = ImageList_Create( imageList->getImageWidth(), imageList->getImageHeight(),
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

		int err = ImageList_AddMasked( headerImageListCtrl_, hBMPcopy, transparentColor );
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


		if ( NULL != headerWnd_ ) {
			Header_SetImageList( headerWnd_, headerImageListCtrl_ );
		}


		CallBack* imgListHandler = getCallback( "Win32Tree::onHeaderImageListImageChanged" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ClassProcedure1<ImageListEvent*, Win32Tree>(this, &Win32Tree::onHeaderImageListImageChanged, "Win32Tree::onHeaderImageListImageChanged" );

		}
		imageList->SizeChanged += imgListHandler;
		imageList->ImageAdded += imgListHandler;
		imageList->ImageDeleted += imgListHandler;
	}


	//reset header item flags
	int count = SendMessage( headerWnd_, HDM_GETITEMCOUNT, 0, 0 );
	for (int i=0;i<count;i++ ) {
		HDITEM item = {0};
		item.mask = HDI_FORMAT | HDI_IMAGE;

		SendMessage( headerWnd_, HDM_GETITEM, i, (LPARAM)&item );

		if ( imageList == NULL ) {
			item.fmt &= ~HDF_IMAGE;
			item.iImage = -1;
		}
		else {
			item.fmt |= HDF_IMAGE;
			item.iImage = I_IMAGECALLBACK;
		}

		SendMessage( headerWnd_, HDM_SETITEM, i, (LPARAM)&item );
	}
}

void Win32Tree::onHeaderImageListImageChanged( ImageListEvent* event )
{
	ImageList* imageList = (ImageList*)event->getSource();
	setHeaderImageList( imageList );
}
/**
$Id$
*/

