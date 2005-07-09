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

		setFont( control->getFont() );

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
		new ModelEventHandler<Win32Toolbar>( this, &Win32Toolbar::onModelChanged, "Win32Toolbar::onModelChanged" ) );

}

void Win32Toolbar::setEnableAutoResize( const bool& val )
{
	int style = GetWindowLong( hwnd_, GWL_STYLE );

	if( val ) {
		style &= ~CCS_NORESIZE;
	}
	else {
		style |= CCS_NORESIZE;
	}
	SetWindowLong( hwnd_, GWL_STYLE, style );
	::SetWindowPos( hwnd_, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED | SWP_NOACTIVATE );
	::UpdateWindow( hwnd_ );
}

bool Win32Toolbar::isAutoResizeEnabled()
{
	int style = GetWindowLong( hwnd_, GWL_STYLE );

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
			//check to see if the font needs updating
			checkForFontChange();


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

		case WM_SIZE : {


			AbstractWin32Component::handleEventMessages( message, wParam, lParam, wndProcResult );

			DWORD style = ::GetWindowLong( hwnd_, GWL_STYLE );

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

				TBBUTTONINFOW info = {0};
				info.dwMask = TBIF_STATE | TBIF_LPARAM ;
				info.cbSize = sizeof(info);

				if ( SendMessage( hwnd_, TB_GETBUTTONINFOW, tbn->iItem, (LPARAM)&info ) >= 0 ) {

					ToolbarItem* item = (ToolbarItem*)info.lParam;
					long state = item->getState();

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

				TBBUTTONINFOA info = {0};
				info.dwMask = TBIF_STATE | TBIF_LPARAM ;
				info.cbSize = sizeof(info);

				if ( SendMessage( hwnd_, TB_GETBUTTONINFOA, tbn->iItem, (LPARAM)&info ) >= 0 ) {

					ToolbarItem* item = (ToolbarItem*)info.lParam;
					long state = item->getState();

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
				TBBUTTONINFOW info = {0};
				info.cbSize = sizeof(info);
				info.dwMask |= TBIF_LPARAM | TBIF_STATE;
				SendMessage( hwnd_, TB_GETBUTTONINFOW, wID, (LPARAM)&info );
				ToolbarItem* item = (ToolbarItem*)info.lParam;
				if ( NULL != item ) {


					long state = item->getState();

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
				TBBUTTONINFOA info = {0};
				info.cbSize = sizeof(info);
				info.dwMask |= TBIF_LPARAM | TBIF_STATE;
				SendMessage( hwnd_, TB_GETBUTTONINFOA, wID, (LPARAM)&info );
				ToolbarItem* item = (ToolbarItem*)info.lParam;
				if ( NULL != item ) {


					long state = item->getState();

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
						TBBUTTONINFOW info = {0};
						info.cbSize = sizeof(info);
						info.dwMask |= TBIF_STATE;
						if ( SendMessage( hwnd_, TB_GETBUTTONINFOW, lpNMCustomDraw->nmcd.dwItemSpec, (LPARAM)&info ) >= 0 ) {
							long state = item->getState();
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
						TBBUTTONINFOA info = {0};
						info.cbSize = sizeof(info);
						info.dwMask |= TBIF_STATE;
						if ( SendMessage( hwnd_, TB_GETBUTTONINFOA, lpNMCustomDraw->nmcd.dwItemSpec, (LPARAM)&info ) >= 0 ) {
							long state = item->getState();
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
				TBBUTTONINFOW info = {0};
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
				TBBUTTONINFOA info = {0};
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
				TBBUTTONINFOW info = {0};
				info.dwMask = TBIF_IMAGE  ;
				info.cbSize = sizeof(info);

				index = tme->getItem()->getIndex();
				SendMessage( hwnd_, TB_GETBUTTONINFOW, index, (LPARAM)&info );

				info.iImage = tme->getItem()->getImageIndex();

				SendMessage( hwnd_, TB_SETBUTTONINFOW, index, (LPARAM)&info );
			}
			else {
				TBBUTTONINFOA info = {0};
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
				TBBUTTONINFOW info = {0};
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
				TBBUTTONINFOA info = {0};
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
				TBBUTTONINFOW info = {0};
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
				TBBUTTONINFOA info = {0};
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
				TBBUTTONINFOW info = {0};
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
				TBBUTTONINFOA info = {0};
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


			RECT tbRect = {0};
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
				TBBUTTONINFOW info = {0};
				info.dwMask = TBIF_SIZE ;
				info.cbSize = sizeof(info);
				Rect r = *tme->getItem()->getBounds();

				info.cx = r.getWidth();

				SendMessage( hwnd_, TB_SETBUTTONINFOW, tme->getItem()->getIndex(), (LPARAM)&info );
			}
			else {
				TBBUTTONINFOA info = {0};
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
			long state = tme->getItem()->getState();

			if ( System::isUnicodeEnabled() ) {
				TBBUTTONINFOW info = {0};
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
				TBBUTTONINFOA info = {0};
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
		RECT tbRect = {0};
		if ( SendMessage( hwnd_, TB_GETITEMRECT, index, (LPARAM)&tbRect ) ) {

			TBBUTTONINFO info = {0};
			info.cbSize = sizeof(info);
			info.dwMask |= TBIF_LPARAM;
			SendMessage( hwnd_, TB_GETBUTTONINFO, index, (LPARAM)&info );
			ToolbarItem* item = (ToolbarItem*)info.lParam;
			item->internal_setBounds( Rect(tbRect.left,tbRect.top,tbRect.right,tbRect.bottom) );
		}
	}
}

void Win32Toolbar::insertToolbarButton( const ulong32& index, ToolbarItem* item, bool showCaption )
{
	currentlyModifyingItem_ = true;


	TBBUTTON btn = {0};

	if ( System::isUnicodeEnabled() ) {

		btn.dwData = (DWORD)item;
		btn.iBitmap = item->getImageIndex();

		String caption = item->getCaption();
		if ( item->getUseLocaleStrings() ) {
			caption = System::getCurrentThreadLocale()->translate( caption );
		}

		VCFChar* tmp = new VCFChar[caption.size()+1];

		caption.copy( tmp, caption.size() );
		tmp[caption.size()] = 0;

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

		TBBUTTONINFOW info = {0};
		//info.dwMask = TBIF_IMAGE;
		info.cbSize = sizeof(info);


		if ( !SendMessage( hwnd_, TB_GETBUTTONINFOW, 0, (LPARAM)&info ) ) {
			int err = GetLastError();
		}

		info.dwMask |= TBIF_LPARAM;
		info.lParam = (LPARAM)item;

		long state = item->getState();

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
		btn.dwData = (DWORD)item;
		btn.iBitmap = item->getImageIndex();


		String caption = item->getCaption();
		if ( item->getUseLocaleStrings() ) {
			caption = System::getCurrentThreadLocale()->translate( caption );
		}

		AnsiString ansiCaption = caption;
		char* tmp = new char[ansiCaption.size()+1];

		ansiCaption.copy( tmp, ansiCaption.size() );
		tmp[ansiCaption.size()] = 0;

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

		TBBUTTONINFOA info = {0};
		//info.dwMask = TBIF_IMAGE;
		info.cbSize = sizeof(info);


		if ( !SendMessage( hwnd_, TB_GETBUTTONINFOA, 0, (LPARAM)&info ) ) {
			int err = GetLastError();
		}

		info.dwMask |= TBIF_LPARAM;
		info.lParam = (LPARAM)item;

		long state = item->getState();

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

	long state = 0;

	ToolbarItem* item = NULL;

	for (index=0;index<buttonCount;index++ ) {
		if ( unicodeEnabled ) {

			TBBUTTONINFOW info = {0};
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
			TBBUTTONINFOA info = {0};
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

	DWORD style = GetWindowLong( hwnd_, GWL_STYLE );

	if ( val ) {
		style |= TBSTYLE_LIST;
	}
	else {
		style &= ~TBSTYLE_LIST;
	}

	SetWindowLong( hwnd_, GWL_STYLE, style );

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

	DWORD style = GetWindowLong( hwnd_, GWL_STYLE );


	SetWindowLong( hwnd_, GWL_STYLE, style|TBSTYLE_TRANSPARENT|TBSTYLE_FLAT );

	::SetWindowPos(hwnd_, NULL, 0, 0, 0, 0,
			SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	SendMessage( hwnd_, TB_SETBUTTONSIZE, 0, (LPARAM) MAKELONG((short)buttonSize.width_, (short)buttonSize.height_) );


	SetWindowLong( hwnd_, GWL_STYLE, style );


	SendMessage( hwnd_, TB_SETIMAGELIST, 0, (LPARAM)imageListCtrl_ );



	bool val = ((Toolbar*)peerControl_)->getShowButtonCaptions();

	for (index=0;index<items.size();index++ ) {
		insertToolbarButton( index, items[index], val );
	}

	SetWindowLong( hwnd_, GWL_STYLE, style );

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
				pix[sz].a = oldAlpaVals[sz];
			} while( sz > 0 );

			delete [] oldAlpaVals;
		}
		break;

		case IMAGELIST_EVENT_ITEM_ADDED : {

			Win32Image* win32Img = (Win32Image*)e->getImage();
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

		EventHandler* imgListHandler = getEventHandler( "Win32Toolbar::onImageListImageChanged" );

		imageListCtrl_ = ImageList_Create( imageList->getImageWidth(), imageList->getImageHeight(),
											ILC_COLOR24  | ILC_MASK, imageList->getImageCount(), 4 );

		if ( imageList->getImageCount() > 0 ) {
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
				new ImageListEventHandler<Win32Toolbar>(this, &Win32Toolbar::onImageListImageChanged, "Win32Toolbar::onImageListImageChanged" );
		}

		imageList->SizeChanged.addHandler( imgListHandler );
		imageList->ImageAdded.addHandler( imgListHandler );
		imageList->ImageDeleted.addHandler( imgListHandler );


		bool val = ((Toolbar*)peerControl_)->getShowButtonCaptions();

		for (index=0;index<items.size();index++ ) {
			insertToolbarButton( index, items[index], val );
		}


		SendMessage(hwnd_, TB_AUTOSIZE, 0, 0 );


		peerControl_->setVisible( true );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.6  2005/06/26 01:31:20  marcelloptr
*improvements to the Color class. The default, when packing the components into a single integer, is now cpsARGB instead than cpsABGR.
*
*Revision 1.3.2.5  2005/06/09 06:13:08  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.3.2.4  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.3.2.3  2005/04/26 02:29:40  ddiego
*fixes font setting bug brought up by scott and glen_f
*
*Revision 1.3.2.2  2005/04/20 02:26:01  ddiego
*fixes for single line text and formatting problems in text window creation.
*
*Revision 1.3.2.1  2005/02/16 05:09:32  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/11/18 06:45:44  ddiego
*updated toolbar btn bug, and added text edit sample.
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
*Revision 1.1.2.11  2004/07/30 17:27:14  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.10  2004/07/21 03:35:49  ddiego
*some minor updates to the QTPlayer example
*
*Revision 1.1.2.9  2004/07/15 14:55:11  ddiego
*borders fixed
*
*Revision 1.1.2.8  2004/07/14 18:18:14  ddiego
*fixed problem with edit control. Turns out we were using the wrong
*subclassed wndproc. This is now fixed.
*
*Revision 1.1.2.7  2004/07/14 04:56:02  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.6  2004/07/13 04:34:32  ddiego
*little changes
*
*Revision 1.1.2.5  2004/07/11 18:45:34  ddiego
*some toolbar fixes, plus some other minor glithches fixed
*
*Revision 1.1.2.4  2004/07/09 18:48:05  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.3  2004/06/26 15:49:36  ddiego
*miscellaneous Unicode changes
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.2.4.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.2  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.4  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.1.2.3  2003/12/02 22:11:31  ddiego
*some minor changes to support Actions. Still not done yet.
*
*Revision 1.1.2.2  2003/12/01 03:44:13  ddiego
*added some fixes to the Win32Toolbar impl. A few minor changes to the
*toolbar example (which also got added). Some minor changes to docs
*as well.
*
*Revision 1.1.2.1  2003/10/31 05:06:38  ddiego
*added toolbar impl
*
*/


