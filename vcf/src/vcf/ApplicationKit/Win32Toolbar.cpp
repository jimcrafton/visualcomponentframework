//Win32Toolbar.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32Toolbar.h"
#include "vcf/ApplicationKit/Toolbar.h"


using namespace VCF;


Win32Toolbar::Win32Toolbar(Control* control):
	AbstractWin32Component(control),
	imageListCtrl_(NULL),
	currentlyModifyingItem_(false)
{

}

Win32Object::CreateParams Win32Toolbar::createParams()
{
	Win32Object::CreateParams result;
	result.first = WS_CHILD | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | TBSTYLE_TOOLTIPS | TBSTYLE_FLAT | CCS_NODIVIDER;// | CCS_NORESIZE;;
	result.second = 0;

	return result;
}


void Win32Toolbar::create( Control* control )
{
	Win32ToolKit* toolkit = (Win32ToolKit*)UIToolkit::internal_getDefaultUIToolkit();
	HWND parent = toolkit->getDummyParent();


	CreateParams params = createParams();

	if ( System::isUnicodeEnabled() ) {
		hwnd_ = ::CreateWindowExW( params.second,
		                             TOOLBARCLASSNAMEW,
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
		                             TOOLBARCLASSNAMEA,
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


	if ( NULL != hwnd_ ) {
		Win32Object::registerWin32Object( this );

		subclassWindow();

		registerForFontChanges();

		SendMessage(hwnd_, TB_BUTTONSTRUCTSIZE, (WPARAM) sizeof(TBBUTTON), 0);

		DWORD btnSize = SendMessage(hwnd_, TB_GETBUTTONSIZE, 0, 0 );


		SendMessage(hwnd_, TB_SETIMAGELIST, 0, 0 );


		currentlyModifyingItem_ = true;
		Size sz;
		sz.width_ = LOWORD(btnSize);
		sz.height_ = HIWORD(btnSize);

		((Toolbar*)peerControl_)->setButtonSize(sz);
		currentlyModifyingItem_ = false;

		SendMessage(hwnd_, TB_AUTOSIZE, 0, 0 );
	}

	control->getViewModel()->addModelHandler(
		new ClassProcedure1<ModelEvent*,Win32Toolbar>( this, &Win32Toolbar::onModelChanged, "Win32Toolbar::onModelChanged" ) );

}

void Win32Toolbar::setEnableAutoResize( const bool& val )
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );

	if( val ) {
		style &= ~CCS_NORESIZE;
	}
	else {
		style |= CCS_NORESIZE;
	}
	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );
	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );
	::UpdateWindow( hwnd_ );
}

bool Win32Toolbar::isAutoResizeEnabled()
{
	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );

	return (style & CCS_NORESIZE) ? false : true;
}

bool Win32Toolbar::handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc )
{
	bool result = false;
	wndProcResult = 0;

	switch ( message ) {
		case WM_ERASEBKGND :{
			//result = CallWindowProc( oldToolbarWndProc_, hwnd_, message, wParam, lParam );
			wndProcResult = 0;
			result = true;
		}
		break;

		case WM_PAINT :{
			PAINTSTRUCT ps;
			HDC dc = BeginPaint( hwnd_, &ps );

			RECT r;
			GetClientRect( hwnd_, &r );

			////FillRect( dc, &r, (HBRUSH) (COLOR_3DFACE + 1) );

			HDC memDC = doControlPaint( dc, r, NULL, cpControlOnly );

			defaultWndProcedure( WM_PAINT, (WPARAM)memDC, 0 );

			updatePaintDC( dc, r, NULL );

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
			return true;
		}
		break;

		case WM_DESTROY : {
			if ( NULL != imageListCtrl_ ) {
				//destroy the old one
				int err = ImageList_Destroy( imageListCtrl_ );
				imageListCtrl_ = NULL;
			}
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;

		case WM_SIZE : {


			AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );

			resizeToolbarItems();
		}
		break;

		case TBN_GETDISPINFOW : {
			NMTBDISPINFOW* dispInfo = (NMTBDISPINFOW*)lParam;
			ToolbarItem* item = (ToolbarItem*)dispInfo->lParam;
			dispInfo->iImage = item->getImageIndex();
		}
		break;

		case TBN_GETDISPINFOA : {
			NMTBDISPINFOA* dispInfo = (NMTBDISPINFOA*)lParam;
			ToolbarItem* item = (ToolbarItem*)dispInfo->lParam;
			dispInfo->iImage = item->getImageIndex();

		}
		break;

		case TBN_GETINFOTIPW : {
			NMTBGETINFOTIPW * dispInfo = (NMTBGETINFOTIPW *)lParam;
			ToolbarItem* item = (ToolbarItem*)dispInfo->lParam;
			String tooltip = item->getTooltip();
			int size = minVal<int>(tooltip.size(),dispInfo->cchTextMax);
			tooltip.copy( dispInfo->pszText, size );
			dispInfo->pszText[size] = 0;
		}
		break;

		case TBN_GETINFOTIPA : {
			NMTBGETINFOTIPA * dispInfo = (NMTBGETINFOTIPA *)lParam;
			ToolbarItem* item = (ToolbarItem*)dispInfo->lParam;
			AnsiString tooltip = item->getTooltip();
			int size = minVal<int>(tooltip.size(),dispInfo->cchTextMax);
			tooltip.copy( dispInfo->pszText, size );
			dispInfo->pszText[size] = 0;
		}
		break;

		case NM_CLICK : {
			if ( System::isUnicodeEnabled() ) {
				TBNOTIFYW* tbn = (TBNOTIFYW*)lParam;

				TBBUTTONINFOW info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_STATE | TBIF_LPARAM ;
				info.cbSize = sizeof(info);

				if ( SendMessage( hwnd_, TB_GETBUTTONINFOW, tbn->iItem, (LPARAM)&info ) >= 0 ) {

					ToolbarItem* item = (ToolbarItem*)info.lParam;
					int32 state = item->getState();

					if ( (TBSTATE_CHECKED  & info.fsState) && ( state & ToolbarItem::tisChecked ) ) {
						state |= ToolbarItem::tisPressed;
					}
					else {
						state &= ~ToolbarItem::tisPressed;
					}
					currentlyModifyingItem_ = true;
					item->setState( state );
					currentlyModifyingItem_ = false;
				}
			}
			else {
				TBNOTIFYA* tbn = (TBNOTIFYA*)lParam;

				TBBUTTONINFOA info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_STATE | TBIF_LPARAM ;
				info.cbSize = sizeof(info);

				if ( SendMessage( hwnd_, TB_GETBUTTONINFOA, tbn->iItem, (LPARAM)&info ) >= 0 ) {

					ToolbarItem* item = (ToolbarItem*)info.lParam;
					int32 state = item->getState();

					if ( (TBSTATE_CHECKED  & info.fsState) && ( state & ToolbarItem::tisChecked ) ) {
						state |= ToolbarItem::tisPressed;
					}
					else {
						state &= ~ToolbarItem::tisPressed;
					}
					currentlyModifyingItem_ = true;
					item->setState( state );
					currentlyModifyingItem_ = false;
				}
			}
		}
		break;

		case WM_COMMAND : {
			WORD wNotifyCode = HIWORD(wParam); // notification code
			WORD wID = LOWORD(wParam);         // item, control, or accelerator identifier
			HWND hwndCtl = (HWND) lParam;

			if ( System::isUnicodeEnabled() ) {
				TBBUTTONINFOW info;
				memset(&info,0,sizeof(info));
				info.cbSize = sizeof(info);
				info.dwMask |= TBIF_LPARAM | TBIF_STATE;
				SendMessage( hwnd_, TB_GETBUTTONINFOW, wID, (LPARAM)&info );
				ToolbarItem* item = (ToolbarItem*)info.lParam;
				if ( NULL != item ) {


					int32 state = item->getState();

					if ( (TBSTATE_CHECKED  & info.fsState) && ( state & ToolbarItem::tisChecked ) ) {
						state |= ToolbarItem::tisPressed;
					}
					else {
						state &= ~ToolbarItem::tisPressed;
					}
					currentlyModifyingItem_ = true;
					item->setState( state );
					currentlyModifyingItem_ = false;



					item->click();
				}
			}
			else {
				TBBUTTONINFOA info;
				memset(&info,0,sizeof(info));
				info.cbSize = sizeof(info);
				info.dwMask |= TBIF_LPARAM | TBIF_STATE;
				SendMessage( hwnd_, TB_GETBUTTONINFOA, wID, (LPARAM)&info );
				ToolbarItem* item = (ToolbarItem*)info.lParam;
				if ( NULL != item ) {


					int32 state = item->getState();

					if ( (TBSTATE_CHECKED  & info.fsState) && ( state & ToolbarItem::tisChecked ) ) {
						state |= ToolbarItem::tisPressed;
					}
					else {
						state &= ~ToolbarItem::tisPressed;
					}
					currentlyModifyingItem_ = true;
					item->setState( state );
					currentlyModifyingItem_ = false;



					item->click();
				}
			}


		}
		break;

		case NM_CUSTOMDRAW : {
			NMTBCUSTOMDRAW* lpNMCustomDraw = (NMTBCUSTOMDRAW*) lParam;
			switch ( lpNMCustomDraw->nmcd.dwDrawStage ) {
				case CDDS_PREPAINT : {
					wndProcResult = CDRF_NOTIFYITEMDRAW;
					result = true;
				}
				break;

				case CDDS_ITEMPREPAINT : {

					ToolbarItem* item = (ToolbarItem*)lpNMCustomDraw->nmcd.lItemlParam;
					if ( NULL != item ) {

					}

					if ( System::isUnicodeEnabled() ) {
						TBBUTTONINFOW info;
						memset(&info,0,sizeof(info));
						info.cbSize = sizeof(info);
						info.dwMask |= TBIF_STATE;
						if ( SendMessage( hwnd_, TB_GETBUTTONINFOW, lpNMCustomDraw->nmcd.dwItemSpec, (LPARAM)&info ) >= 0 ) {
							int32 state = item->getState();
							if ( (TBSTATE_CHECKED  & info.fsState) && ( state & ToolbarItem::tisChecked ) ) {
								state |= ToolbarItem::tisPressed;
							}
							else {
								state &= ~ToolbarItem::tisPressed;
							}

							currentlyModifyingItem_ = true;
							item->setState( state );
							currentlyModifyingItem_ = false;
						}

					}
					else {
						TBBUTTONINFOA info;
						memset(&info,0,sizeof(info));
						info.cbSize = sizeof(info);
						info.dwMask |= TBIF_STATE;
						if ( SendMessage( hwnd_, TB_GETBUTTONINFOA, lpNMCustomDraw->nmcd.dwItemSpec, (LPARAM)&info ) >= 0 ) {
							int32 state = item->getState();
							if ( (TBSTATE_CHECKED  & info.fsState) && ( state & ToolbarItem::tisChecked ) ) {
								state |= ToolbarItem::tisPressed;
							}
							else {
								state &= ~ToolbarItem::tisPressed;
							}

							currentlyModifyingItem_ = true;
							item->setState( state );
							currentlyModifyingItem_ = false;
						}
					}


					wndProcResult = CDRF_DODEFAULT;
					result = true;
				}
				break;
			}
		}
		break;



		default : {
			result = AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );
		}
		break;
	}


	return result;
}

void Win32Toolbar::onModelChanged( ModelEvent* e )
{
	if ( currentlyModifyingItem_ ) {
		return;
	}

	int index = 0;

	switch( e->getType() ) {

		case ToolbarItem::tbCaptionChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

			if ( System::isUnicodeEnabled() ) {
				TBBUTTONINFOW info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_TEXT ;
				info.cbSize = sizeof(info);
				VCFChar tmp[256];
				String caption = tme->getItem()->getCaption();
				if ( tme->getItem()->getUseLocaleStrings() ) {
					caption = System::getCurrentThreadLocale()->translate( caption );
				}

				int size = minVal<int>(caption.size(), 255);
				caption.copy( tmp, size );
				tmp[size] = 0;

				info.cchText = size;
				info.pszText = tmp;

				SendMessage( hwnd_, TB_SETBUTTONINFOW, tme->getItem()->getIndex(), (LPARAM)&info );
			}
			else {
				TBBUTTONINFOA info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_TEXT ;
				info.cbSize = sizeof(info);
				char tmp[256];

				String caption = tme->getItem()->getCaption();
				if ( tme->getItem()->getUseLocaleStrings() ) {
					caption = System::getCurrentThreadLocale()->translate( caption );
				}

				AnsiString ansiCaption = caption;
				int size = minVal<int>(ansiCaption.size(), 255);
				ansiCaption.copy( tmp, size );
				tmp[size] = 0;

				info.cchText = size;
				info.pszText = tmp;

				SendMessage( hwnd_, TB_SETBUTTONINFOA, tme->getItem()->getIndex(), (LPARAM)&info );
			}


			resizeToolbarItems();
		}
		break;


		case ToolbarItem::tbImageIndexChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

			if ( System::isUnicodeEnabled() ) {
				TBBUTTONINFOW info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_IMAGE  ;
				info.cbSize = sizeof(info);

				index = tme->getItem()->getIndex();
				SendMessage( hwnd_, TB_GETBUTTONINFOW, index, (LPARAM)&info );

				info.iImage = tme->getItem()->getImageIndex();

				SendMessage( hwnd_, TB_SETBUTTONINFOW, index, (LPARAM)&info );
			}
			else {
				TBBUTTONINFOA info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_IMAGE  ;
				info.cbSize = sizeof(info);

				index = tme->getItem()->getIndex();
				SendMessage( hwnd_, TB_GETBUTTONINFOA, index, (LPARAM)&info );

				info.iImage = tme->getItem()->getImageIndex();

				SendMessage( hwnd_, TB_SETBUTTONINFOA, index, (LPARAM)&info );
			}

		}
		break;


		case ToolbarItem::tbSelected : {

		}
		break;

		case ToolbarItem::tbGroupChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

			if (System::isUnicodeEnabled() ) {
				TBBUTTONINFOW info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_STYLE  ;
				info.cbSize = sizeof(info);

				SendMessage( hwnd_, TB_GETBUTTONINFOW, tme->getItem()->getIndex(), (LPARAM)&info );

				if ( tme->getItem()->isGrouped() ) {
					info.fsStyle |= TBSTYLE_GROUP;
				}
				else {
					info.fsStyle &= ~TBSTYLE_GROUP;
				}

				SendMessage( hwnd_, TB_SETBUTTONINFOW, tme->getItem()->getIndex(), (LPARAM)&info );
			}
			else {
				TBBUTTONINFOA info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_STYLE  ;
				info.cbSize = sizeof(info);

				SendMessage( hwnd_, TB_GETBUTTONINFOA, tme->getItem()->getIndex(), (LPARAM)&info );

				if ( tme->getItem()->isGrouped() ) {
					info.fsStyle |= TBSTYLE_GROUP;
				}
				else {
					info.fsStyle &= ~TBSTYLE_GROUP;
				}

				SendMessage( hwnd_, TB_SETBUTTONINFOA, tme->getItem()->getIndex(), (LPARAM)&info );
			}

		}
		break;

		case ToolbarItem::tbCheckChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

			if ( System::isUnicodeEnabled() ) {
				TBBUTTONINFOW info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_STYLE  ;
				info.cbSize = sizeof(info);

				if ( SendMessage( hwnd_, TB_GETBUTTONINFOW, tme->getItem()->getIndex(), (LPARAM)&info ) >= 0 ) {

					if ( tme->getItem()->isChecked() ) {
						info.fsStyle |= TBSTYLE_CHECK;
					}
					else {
						info.fsStyle &= ~TBSTYLE_CHECK;
					}

					int i = SendMessage( hwnd_, TB_SETBUTTONINFOW, tme->getItem()->getIndex(), (LPARAM)&info );
				}
				else {
					int err = GetLastError();
				}
			}
			else {
				TBBUTTONINFOA info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_STYLE  ;
				info.cbSize = sizeof(info);

				if ( SendMessage( hwnd_, TB_GETBUTTONINFOA, tme->getItem()->getIndex(), (LPARAM)&info ) >= 0 ) {

					if ( tme->getItem()->isChecked() ) {
						info.fsStyle |= TBSTYLE_CHECK;
					}
					else {
						info.fsStyle &= ~TBSTYLE_CHECK;
					}

					int i = SendMessage( hwnd_, TB_SETBUTTONINFOA, tme->getItem()->getIndex(), (LPARAM)&info );
				}
				else {
					int err = GetLastError();
				}
			}

		}
		break;

		case ToolbarItem::tbItemControlAdded : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
			Control* addedControl = NULL;

			if ( System::isUnicodeEnabled() ) {
				TBBUTTONINFOW info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_STYLE;
				info.fsStyle = TBSTYLE_SEP ;
				info.cbSize = sizeof(info);

				index = tme->getItem()->getIndex();

				SendMessage( hwnd_, TB_SETBUTTONINFOW, index, (LPARAM)&info );


				addedControl = tme->getItem()->getItemControl();
				Rect r = addedControl->getBounds();


				memset( &info, 0, sizeof(info) );
				info.dwMask = TBIF_SIZE;
				info.cbSize = sizeof(info);
				info.cx = r.getWidth();

				SendMessage( hwnd_, TB_SETBUTTONINFOW, index, (LPARAM)&info );
			}
			else {
				TBBUTTONINFOA info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_STYLE;
				info.fsStyle = TBSTYLE_SEP ;
				info.cbSize = sizeof(info);

				index = tme->getItem()->getIndex();

				SendMessage( hwnd_, TB_SETBUTTONINFOA, index, (LPARAM)&info );


				addedControl = tme->getItem()->getItemControl();
				Rect r = addedControl->getBounds();


				memset( &info, 0, sizeof(info) );
				info.dwMask = TBIF_SIZE;
				info.cbSize = sizeof(info);
				info.cx = r.getWidth();

				SendMessage( hwnd_, TB_SETBUTTONINFOA, index, (LPARAM)&info );

			}



			resizeToolbarItems();

			currentlyModifyingItem_ = true;


			RECT tbRect;
			memset(&tbRect,0,sizeof(tbRect));
			if ( SendMessage( hwnd_, TB_GETITEMRECT, index, (LPARAM)&tbRect ) ) {
				tme->getItem()->internal_setBounds( Rect(tbRect.left,tbRect.top,tbRect.right,tbRect.bottom) );

				Container* container = this->peerControl_->getContainer();
				if ( NULL != container ) {
					container->add( addedControl );
					addedControl->setBounds( &Rect(tbRect.left,tbRect.top,tbRect.right,tbRect.bottom) );
					addedControl->setVisible( true );
				}
				else {
					throw RuntimeException( MAKE_ERROR_MSG_2("No container found - unable to add control to toolbar") );
				}

			}


			currentlyModifyingItem_ = false;
		}
		break;


		case ToolbarItem::tbDimensionsChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

			if ( System::isUnicodeEnabled() ) {
				TBBUTTONINFOW info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_SIZE ;
				info.cbSize = sizeof(info);
				Rect r = *tme->getItem()->getBounds();

				info.cx = r.getWidth();

				SendMessage( hwnd_, TB_SETBUTTONINFOW, tme->getItem()->getIndex(), (LPARAM)&info );
			}
			else {
				TBBUTTONINFOA info;
				memset(&info,0,sizeof(info));
				info.dwMask = TBIF_SIZE ;
				info.cbSize = sizeof(info);
				Rect r = *tme->getItem()->getBounds();

				info.cx = r.getWidth();

				SendMessage( hwnd_, TB_SETBUTTONINFOA, tme->getItem()->getIndex(), (LPARAM)&info );
			}

			resizeToolbarItems();
		}
		break;

		case ToolbarItem::tbAdded : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;

			bool val = ((Toolbar*)peerControl_)->getShowButtonCaptions();

			insertToolbarButton( tme->getItem()->getIndex(), tme->getItem(), val );
		}
		break;

		case ToolbarItem::tbRemoved : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
			SendMessage( hwnd_, TB_DELETEBUTTON, tme->getItem()->getIndex(), 0 );
			resizeToolbarItems();
		}
		break;

		case ToolbarItem::tbStateChanged : {
			ToolbarModelEvent* tme = (ToolbarModelEvent*)e;
			int32 state = tme->getItem()->getState();

			if ( System::isUnicodeEnabled() ) {
				TBBUTTONINFOW info;
				memset(&info,0,sizeof(info));
				info.cbSize = sizeof(info);

				if ( state == ToolbarItem::tisSeparator ) {
					info.dwMask = TBIF_STYLE | TBIF_SIZE;
					info.fsStyle = TBSTYLE_SEP ;
					info.cx = 5;
				}
				else {
					if ( state & ToolbarItem::tisPressed ) {
						if ( state & ToolbarItem::tisChecked ) {
							info.dwMask |= TBIF_STATE ;
							info.fsState |= TBSTATE_CHECKED  ;
						}
					}

					if ( state & ToolbarItem::tisGrouped ) {
						info.dwMask |= TBIF_STYLE ;
						info.fsStyle |= TBSTYLE_GROUP  ;
					}

					if ( state & ToolbarItem::tisChecked ) {
						info.dwMask |= TBIF_STYLE ;
						info.fsStyle |= TBSTYLE_CHECK  ;
					}

					if ( state & ToolbarItem::tisEnabled ) {
						info.dwMask |= TBIF_STATE ;
						info.fsState |= TBSTATE_ENABLED  ;
					}
					else {
						info.dwMask |= TBIF_STATE ;
						info.fsState &= ~TBSTATE_ENABLED  ;
					}
				}

				SendMessage( hwnd_, TB_SETBUTTONINFOW, tme->getItem()->getIndex(), (LPARAM)&info );
			}
			else {
				TBBUTTONINFOA info;
				memset(&info,0,sizeof(info));
				info.cbSize = sizeof(info);

				if ( state == ToolbarItem::tisSeparator ) {
					info.dwMask = TBIF_STYLE | TBIF_SIZE;
					info.fsStyle = TBSTYLE_SEP ;
					info.cx = 5;
				}
				else {
					if ( state & ToolbarItem::tisPressed ) {
						if ( state & ToolbarItem::tisChecked ) {
							info.dwMask |= TBIF_STATE ;
							info.fsState |= TBSTATE_CHECKED  ;
						}
					}

					if ( state & ToolbarItem::tisGrouped ) {
						info.dwMask |= TBIF_STYLE ;
						info.fsStyle |= TBSTYLE_GROUP  ;
					}

					if ( state & ToolbarItem::tisChecked ) {
						info.dwMask |= TBIF_STYLE ;
						info.fsStyle |= TBSTYLE_CHECK  ;
					}

					if ( state & ToolbarItem::tisEnabled ) {
						info.dwMask |= TBIF_STATE ;
						info.fsState |= TBSTATE_ENABLED  ;
					}
					else {
						info.dwMask |= TBIF_STATE ;
						info.fsState &= ~TBSTATE_ENABLED  ;
					}
				}

				SendMessage( hwnd_, TB_SETBUTTONINFOA, tme->getItem()->getIndex(), (LPARAM)&info );
			}


		}
		break;

		case ToolbarItem::tbIndexChanged  : {

		}
		break;

		default : {

		}
		break;
	}
}

void Win32Toolbar::resizeToolbarItems( int startAt )
{

	int buttonCount = SendMessage( hwnd_, TB_BUTTONCOUNT, 0, 0 );
	int index = (startAt >= 0) ? startAt : 0;

	for (index=0;index<buttonCount;index++ ) {
		RECT tbRect;
		memset(&tbRect,0,sizeof(tbRect));
		if ( SendMessage( hwnd_, TB_GETITEMRECT, index, (LPARAM)&tbRect ) ) {

			TBBUTTONINFO info;
			memset(&info,0,sizeof(info));
			info.cbSize = sizeof(info);
			info.dwMask |= TBIF_LPARAM;
			SendMessage( hwnd_, TB_GETBUTTONINFO, index, (LPARAM)&info );
			ToolbarItem* item = (ToolbarItem*)info.lParam;
			item->internal_setBounds( Rect(tbRect.left,tbRect.top,tbRect.right,tbRect.bottom) );
		}
	}
}



void Win32Toolbar::insertToolbarButton( const uint32& index, ToolbarItem* item, bool showCaption )
{
	currentlyModifyingItem_ = true;


	TBBUTTON btn;
	memset(&btn,0,sizeof(btn));

	if ( System::isUnicodeEnabled() ) {

		btn.dwData = (DWORD_PTR)item;
		btn.iBitmap = item->getImageIndex();

		String caption = item->getCaption();
		if ( item->getUseLocaleStrings() ) {
			caption = System::getCurrentThreadLocale()->translate( caption );
		}

		VCFChar* tmp = new VCFChar[caption.size()+2];

		caption.copy( tmp, caption.size() );
		tmp[caption.size()] = 0;
		tmp[caption.size()+1] = 0;
		
		btn.iString = SendMessage( hwnd_, TB_ADDSTRINGW, (WPARAM) 0, (LPARAM) (LPSTR) tmp);		

		buttonCaptionsMap_[caption] = btn.iString;

		if ( buttonCaptionsMap_.size() == 1 ) {
			SendMessage(hwnd_, TB_AUTOSIZE, 0, 0 );
		}

		if ( !showCaption ) {
			btn.iString = -1;
		}

		btn.fsState = TBSTATE_ENABLED;
		btn.fsStyle = TBSTYLE_BUTTON /*| TBSTYLE_AUTOSIZE */;
		btn.idCommand = index;

		if ( !SendMessage( hwnd_, TB_INSERTBUTTONW, (WPARAM) index, (LPARAM)&btn ) ) {
			int err = GetLastError();
		}

		TBBUTTONINFOW info;
		memset(&info,0,sizeof(info));
		//info.dwMask = TBIF_IMAGE;
		info.cbSize = sizeof(info);


		if ( !SendMessage( hwnd_, TB_GETBUTTONINFOW, 0, (LPARAM)&info ) ) {
			int err = GetLastError();
		}

		info.dwMask |= TBIF_LPARAM;
		info.lParam = (LPARAM)item;

		int32 state = item->getState();

		if ( state == ToolbarItem::tisSeparator ) {
			info.dwMask = TBIF_STYLE | TBIF_SIZE;
			info.fsStyle = TBSTYLE_SEP ;
			info.cx = 5;
		}
		else {
			if ( state & ToolbarItem::tisPressed ) {
				//info.dwMask |= TBIF_STATE ;
				//info.fsState |= TBSTATE_PRESSED  ;
				if ( state & ToolbarItem::tisChecked ) {
					info.dwMask |= TBIF_STATE ;
					info.fsState |= TBSTATE_CHECKED ;
				}
			}

			if ( state & ToolbarItem::tisGrouped ) {
				info.dwMask |= TBIF_STYLE ;
				info.fsStyle |= TBSTYLE_GROUP  ;
			}

			if ( state & ToolbarItem::tisChecked ) {
				info.dwMask |= TBIF_STYLE ;
				info.fsStyle |= TBSTYLE_CHECK  ;
			}

			if ( state & ToolbarItem::tisEnabled ) {
				info.dwMask |= TBIF_STATE ;
				info.fsState |= TBSTATE_ENABLED  ;
			}
			else {
				info.dwMask |= TBIF_STATE ;
				info.fsState &= ~TBSTATE_ENABLED  ;
			}
		}

		if ( NULL != item->getItemControl() ) {
			Rect bounds = item->getItemControl()->getBounds();
			info.cx = bounds.getWidth();
			info.dwMask = TBIF_STYLE | TBIF_SIZE;
			info.fsStyle = TBSTYLE_SEP ;
		}

		//info.iImage = I_IMAGECALLBACK;
		SendMessage( hwnd_, TB_SETBUTTONINFOW, index, (LPARAM)&info );
		delete [] tmp;
	}
	else {
		btn.dwData = (DWORD_PTR)item;
		btn.iBitmap = item->getImageIndex();


		String caption = item->getCaption();
		if ( item->getUseLocaleStrings() ) {
			caption = System::getCurrentThreadLocale()->translate( caption );
		}

		AnsiString ansiCaption = caption;
		char* tmp = new char[ansiCaption.size()+2];

		ansiCaption.copy( tmp, ansiCaption.size() );
		tmp[ansiCaption.size()] = 0;
		tmp[ansiCaption.size()+1] = 0;

		btn.iString = SendMessage( hwnd_, TB_ADDSTRINGA, (WPARAM) 0, (LPARAM) (LPSTR) tmp);
		buttonCaptionsMap_[ansiCaption] = btn.iString;

		if ( buttonCaptionsMap_.size() == 1 ) {
			SendMessage(hwnd_, TB_AUTOSIZE, 0, 0 );
		}

		if ( !showCaption ) {
			btn.iString = -1;
		}

		btn.fsState = TBSTATE_ENABLED;
		btn.fsStyle = TBSTYLE_BUTTON | TBSTYLE_AUTOSIZE ;
		btn.idCommand = index;

		if ( !SendMessage( hwnd_, TB_INSERTBUTTONA, (WPARAM) index, (LPARAM)&btn ) ) {
			int err = GetLastError();
		}

		TBBUTTONINFOA info;
		memset(&info,0,sizeof(info));
		//info.dwMask = TBIF_IMAGE;
		info.cbSize = sizeof(info);


		if ( !SendMessage( hwnd_, TB_GETBUTTONINFOA, 0, (LPARAM)&info ) ) {
			int err = GetLastError();
		}

		info.dwMask |= TBIF_LPARAM;
		info.lParam = (LPARAM)item;

		int32 state = item->getState();

		if ( state == ToolbarItem::tisSeparator ) {
			info.dwMask = TBIF_STYLE | TBIF_SIZE;
			info.fsStyle = TBSTYLE_SEP ;
			info.cx = 5;
		}
		else {
			if ( state & ToolbarItem::tisPressed ) {
				//info.dwMask |= TBIF_STATE ;
				//info.fsState |= TBSTATE_PRESSED  ;
				if ( state & ToolbarItem::tisChecked ) {
					info.dwMask |= TBIF_STATE ;
					info.fsState |= TBSTATE_CHECKED ;
				}
			}

			if ( state & ToolbarItem::tisGrouped ) {
				info.dwMask |= TBIF_STYLE ;
				info.fsStyle |= TBSTYLE_GROUP  ;
			}

			if ( state & ToolbarItem::tisChecked ) {
				info.dwMask |= TBIF_STYLE ;
				info.fsStyle |= TBSTYLE_CHECK  ;
			}

			if ( state & ToolbarItem::tisEnabled ) {
				info.dwMask |= TBIF_STATE ;
				info.fsState |= TBSTATE_ENABLED  ;
			}
			else {
				info.dwMask |= TBIF_STATE ;
				info.fsState &= ~TBSTATE_ENABLED  ;
			}
		}

		if ( NULL != item->getItemControl() ) {
			Rect bounds = item->getItemControl()->getBounds();
			info.cx = bounds.getWidth();
			info.dwMask = TBIF_STYLE | TBIF_SIZE;
			info.fsStyle = TBSTYLE_SEP ;
		}

		//info.iImage = I_IMAGECALLBACK;
		SendMessage( hwnd_, TB_SETBUTTONINFOA, index, (LPARAM)&info );
		delete [] tmp;
	}




	resizeToolbarItems();

	currentlyModifyingItem_ = false;




}

void Win32Toolbar::resetItems( std::vector<ToolbarItem*>& items )
{
	int buttonCount = SendMessage( hwnd_, TB_BUTTONCOUNT, 0, 0 );
	int index = 0;

	items.resize(buttonCount);


	bool unicodeEnabled = System::isUnicodeEnabled() ;

	int32 state = 0;

	ToolbarItem* item = NULL;

	for (index=0;index<buttonCount;index++ ) {
		if ( unicodeEnabled ) {

			TBBUTTONINFOW info;
			memset(&info,0,sizeof(info));
			info.cbSize = sizeof(info);
			info.dwMask |= TBIF_LPARAM | TBIF_STYLE | TBIF_STATE;
			SendMessage( hwnd_, TB_GETBUTTONINFOW, index, (LPARAM)&info );
			item = (ToolbarItem*)info.lParam;
			items[index] = item;

			state = item->getState();

			if ( (TBSTATE_CHECKED  & info.fsState) && ( state & ToolbarItem::tisChecked ) ) {
				state |= ToolbarItem::tisPressed;
			}
			else {
				state &= ~ToolbarItem::tisPressed;
			}

		}
		else {
			TBBUTTONINFOA info;
			memset(&info,0,sizeof(info));
			info.cbSize = sizeof(info);
			info.dwMask |= TBIF_LPARAM | TBIF_STYLE | TBIF_STATE;
			SendMessage( hwnd_, TB_GETBUTTONINFOA, index, (LPARAM)&info );
			item = (ToolbarItem*)info.lParam;
			items[index] = item;

			state = item->getState();

			if ( (TBSTATE_CHECKED  & info.fsState) && ( state & ToolbarItem::tisChecked ) ) {
				state |= ToolbarItem::tisPressed;
			}
			else {
				state &= ~ToolbarItem::tisPressed;
			}
		}



		currentlyModifyingItem_ = true;
		item->setState( state );
		currentlyModifyingItem_ = false;


		SendMessage( hwnd_, TB_DELETEBUTTON, 0, 0 );
	}


}

void Win32Toolbar::showButtonCaptions( const bool& val )
{
	peerControl_->setVisible( false );

	int index = 0;

	std::vector<ToolbarItem*> items;

	resetItems( items );

	for (index=0;index<items.size();index++ ) {
		insertToolbarButton( index, items[index], val );
	}

	SendMessage(hwnd_, TB_AUTOSIZE, 0, 0 );

	peerControl_->setVisible( true );
}

void Win32Toolbar::setButtonCaptionPlacementHorizontal( const bool& val )
{
	if ( currentlyModifyingItem_ ) {
		return;
	}

	currentlyModifyingItem_ = true;

	peerControl_->setVisible( false );

	int index = 0;

	std::vector<ToolbarItem*> items;

	resetItems( items );

	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );

	if ( val ) {
		style |= TBSTYLE_LIST;
	}
	else {
		style &= ~TBSTYLE_LIST;
	}

	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );

	::SetWindowPos(hwnd_, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);



	bool showCaptions = ((Toolbar*)peerControl_)->getShowButtonCaptions();

	for (index=0;index<items.size();index++ ) {
		insertToolbarButton( index, items[index], showCaptions );
	}

	SendMessage(hwnd_, TB_AUTOSIZE, 0, 0 );

	peerControl_->setVisible( true );

	currentlyModifyingItem_ = false;
}

void Win32Toolbar::setButtonSize( const Size& buttonSize )
{
	if ( currentlyModifyingItem_ ) {
		return;
	}

	currentlyModifyingItem_ = true;

	peerControl_->setVisible( false );

	int buttonCount = SendMessage( hwnd_, TB_BUTTONCOUNT, 0, 0 );
	int index = 0;

	std::vector<ToolbarItem*> items;

	resetItems( items );

	SendMessage( hwnd_, TB_SETIMAGELIST, 0, 0 );

	LONG_PTR style = ::GetWindowLongPtr( hwnd_, GWL_STYLE );


	::SetWindowLongPtr( hwnd_, GWL_STYLE, style|TBSTYLE_TRANSPARENT|TBSTYLE_FLAT );

	::SetWindowPos(hwnd_, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	SendMessage( hwnd_, TB_SETBUTTONSIZE, 0, (LPARAM) MAKELONG((short)buttonSize.width_, (short)buttonSize.height_) );


	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );


	SendMessage( hwnd_, TB_SETIMAGELIST, 0, (LPARAM)imageListCtrl_ );



	bool val = ((Toolbar*)peerControl_)->getShowButtonCaptions();

	for (index=0;index<items.size();index++ ) {
		insertToolbarButton( index, items[index], val );
	}

	::SetWindowLongPtr( hwnd_, GWL_STYLE, style );

	SendMessage(hwnd_, TB_AUTOSIZE, 0, 0 );

	peerControl_->setVisible( true );
/*
	Container* container = peerControl_->getParent()->getContainer();
	if ( NULL != container ) {
		container->resizeChildren(NULL);
	}
*/
	currentlyModifyingItem_ = false;

}

void Win32Toolbar::removeToolbarButton( ToolbarItem* item )
{
	SendMessage( hwnd_, TB_DELETEBUTTON, item->getIndex(), 0 );
	resizeToolbarItems();
}


void Win32Toolbar::onImageListImageChanged( ImageListEvent* e )
{
	ImageList* imageList = (ImageList*)e->getSource();

	switch ( e->getType() ) {
		case IMAGELIST_EVENT_WIDTH_CHANGED : case IMAGELIST_EVENT_HEIGHT_CHANGED :{
			int cx = imageList->getImageWidth();
			int cy = imageList->getImageHeight();
			int err = ImageList_SetIconSize( imageListCtrl_, cx, cy );

			//reset the contents
			Win32Image* win32Img = (Win32Image*)imageList->getMasterImage();

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

			HBITMAP hCopyImg = (HBITMAP)CopyImage( hbmImage, IMAGE_BITMAP, 0, 0, NULL );


			Color* transparentColor = imageList->getTransparentColor();

			COLORREF color = transparentColor->getColorRef32();
			err = ImageList_AddMasked( imageListCtrl_, hCopyImg, color );
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

		case IMAGELIST_EVENT_ITEM_ADDED : {

			Win32Image* win32Img = (Win32Image*)e->getImage();
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

			Color* transparentColor = imageList->getTransparentColor();

			COLORREF color = transparentColor->getColorRef32();

			int err = ImageList_AddMasked( imageListCtrl_, hCopyImg, color );

			::DeleteObject( hCopyImg );

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

void Win32Toolbar::setImageList( ImageList* imageList )
{
	if ( NULL != imageListCtrl_ ) {
		//destroy the old one
		int err = ImageList_Destroy( imageListCtrl_ );
		imageListCtrl_ = NULL;
	}

	if ( NULL != imageList ) {

		peerControl_->setVisible( false );


		int buttonCount = SendMessage( hwnd_, TB_BUTTONCOUNT, 0, 0 );
		int index = 0;

		std::vector<ToolbarItem*> items;

		resetItems( items );




		SendMessage( hwnd_, TB_SETBITMAPSIZE, 0, (LPARAM) MAKELONG(imageList->getImageWidth(), imageList->getImageHeight()) );

		CallBack* imgListHandler = getEventHandler( "Win32Toolbar::onImageListImageChanged" );

		imageListCtrl_ = ImageList_Create( imageList->getImageWidth(), imageList->getImageHeight(),
											ILC_COLOR24  | ILC_MASK, imageList->getImageCount(), 4 );

		if ( imageList->getImageCount() > 0 ) {
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

			Color* transparentColor = imageList->getTransparentColor();
			COLORREF color = transparentColor->getColorRef32();

			int err = ImageList_AddMasked( imageListCtrl_, hCopyImg, color );

			::DeleteObject( hCopyImg );

			sz = win32Img->getWidth() * win32Img->getHeight();
			do {
				sz --;
				pix[sz].a = oldAlpaVals[sz];
			} while( sz > 0 );

			delete [] oldAlpaVals;
		}

		SendMessage( hwnd_, TB_SETIMAGELIST, 0, (LPARAM)imageListCtrl_ );

		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ClassProcedure1<ImageListEvent*,Win32Toolbar>(this, &Win32Toolbar::onImageListImageChanged, "Win32Toolbar::onImageListImageChanged" );
		}

		imageList->SizeChanged += imgListHandler;
		imageList->ImageAdded += imgListHandler;
		imageList->ImageDeleted +=  imgListHandler;


		bool val = ((Toolbar*)peerControl_)->getShowButtonCaptions();

		for (index=0;index<items.size();index++ ) {
			insertToolbarButton( index, items[index], val );
		}


		SendMessage(hwnd_, TB_AUTOSIZE, 0, 0 );


		peerControl_->setVisible( true );
	}
}


/**
$Id$
*/
