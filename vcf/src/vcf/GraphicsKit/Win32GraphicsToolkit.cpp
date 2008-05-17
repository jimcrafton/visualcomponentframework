//Win32GraphicsToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32GraphicsToolkit.h
#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

#include <commdlg.h>

#include "vcf/GraphicsKit/PrintSessionPeer.h"
#include "vcf/GraphicsKit/Win32PrintSession.h"
#include "vcf/FoundationKit/ResourceBundle.h"

#include "vcf/FoundationKit/ResourceBundlePeer.h"
#include "vcf/GraphicsKit/GraphicsResourceBundlePeer.h"
#include "vcf/GraphicsKit/Win32GraphicsResourceBundle.h"

#include "vcf/GraphicsKit/Win32VisualStylesWrapper.h"
#include "vcf/FoundationKit/VFFInputStream.h"


//init singleton
Win32VisualStylesWrapper Win32VisualStylesWrapper::Instance;




using namespace VCF;



#define CXGAP				1		// num pixels between button and text
#define CXTEXTMARGIN		2		// num pixels after hilite to start text
#define CXBUTTONMARGIN		2		// num pixels wider button is than bitmap
#define CYBUTTONMARGIN		2		// ditto for height

//UIMetricsManager implementation
class Win32UIMetricsManager : public UIMetricsManager {
public:

	static Point DLUToPixel( const Point& dlu, VCF::Font& font ) {
		Point result;
		HDC dc = GetDC( ::GetDesktopWindow() );

		int baseUnitY = 0;
		int cx = 0;

		HFONT hf = NULL;
		HFONT old = NULL;
		if ( System::isUnicodeEnabled() ) {
			LOGFONTW* lf = (LOGFONTW*) font.getFontPeer()->getFontHandleID();
			hf = ::CreateFontIndirectW( lf );


			old = (HFONT)SelectObject(dc, hf );

			TEXTMETRICW tm;
			GetTextMetricsW( dc, &tm );
			baseUnitY = tm.tmHeight;
			SIZE sz;
			::GetTextExtentPointW( dc,
								L"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
								52, &sz );

			cx = sz.cx;
		}
		else {
			LOGFONTA* lf = (LOGFONTA*) font.getFontPeer()->getFontHandleID();
			hf = ::CreateFontIndirectA( lf );

			old = (HFONT)SelectObject(dc, hf );

			TEXTMETRICA tm;
			GetTextMetricsA( dc, &tm );
			baseUnitY = tm.tmHeight;
			SIZE sz;
			::GetTextExtentPointA( dc,
								"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz",
								52, &sz );

			cx = sz.cx;
		}




		int baseUnitX = (cx / 26 + 1) / 2;
		result.x_ = MulDiv(dlu.x_, baseUnitX, 4);
		result.y_ = MulDiv(dlu.y_, baseUnitY, 8);

		//(dlu.x_ * baseUnitX) / 4;
		//result.y_  = (dlu.y_ * baseUnitY) / 8;

		SelectObject(dc, old );
		DeleteObject( hf );
		ReleaseDC( ::GetDesktopWindow(), dc );


		return result;
	}

	virtual VCF::Font getDefaultFontFor( const UIMetricsManager::FontType& type ) {
		VCF::Font result;

		NONCLIENTMETRICSA ncm;
		memset( &ncm, 0, sizeof(ncm) );

		ncm.cbSize = sizeof(ncm);

		switch ( type ) {
			case UIMetricsManager::ftMenuItemFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfMenuFont.lfFaceName ) ;
					result.setBold( ncm.lfMenuFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_MENUTEXT ) ) );
					result.setItalic( ncm.lfMenuFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfMenuFont.lfHeight );
					result.setStrikeOut( ncm.lfMenuFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfMenuFont.lfUnderline ? true : false );
				}
				//
			}
			break;

			case UIMetricsManager::ftSelectedMenuItemFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfMenuFont.lfFaceName ) ;
					result.setBold( ncm.lfMenuFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_HIGHLIGHTTEXT ) ) );
					result.setItalic( ncm.lfMenuFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfMenuFont.lfHeight );
					result.setStrikeOut( ncm.lfMenuFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfMenuFont.lfUnderline ? true : false );
				}
			}
			break;

			case UIMetricsManager::ftControlFont :  case UIMetricsManager::ftSystemFont : {
				//do nothing the Win32Font already is initialized ot this by default
				result.setColor( &Color( ::GetSysColor( COLOR_WINDOWTEXT ) ) );
			}
			break;

			case UIMetricsManager::ftMessageFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfMessageFont.lfFaceName ) ;
					result.setBold( ncm.lfMessageFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_WINDOWTEXT ) ) );
					result.setItalic( ncm.lfMessageFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfMessageFont.lfHeight );
					result.setStrikeOut( ncm.lfMessageFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfMessageFont.lfUnderline ? true : false );
				}
			}
			break;

			case UIMetricsManager::ftToolTipFont : {
				if ( SystemParametersInfoA( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 ) ) {
					result.setName( ncm.lfStatusFont.lfFaceName ) ;
					result.setBold( ncm.lfStatusFont.lfWeight >= FW_BOLD );
					result.setColor( &Color( ::GetSysColor( COLOR_INFOTEXT ) ) );
					result.setItalic( ncm.lfStatusFont.lfItalic ? true : false );
					result.setPixelSize( ncm.lfStatusFont.lfHeight );
					result.setStrikeOut( ncm.lfStatusFont.lfStrikeOut ? true : false );
					result.setUnderlined( ncm.lfStatusFont.lfUnderline ? true : false );
				}
			}
			break;
		}

		return result;
	}

/*
	virtual Size getDefaultSliderThumbDimensions()  {
		Size result;

		result.width_ = ::GetSystemMetrics( SM_CXHTHUMB )*0.85+1;
		result.height_ = ::GetSystemMetrics( SM_CYVTHUMB );

		return result;
	}

	virtual Size getDefaultMenuItemDimensions( const String& caption )  {
		Size result;

		NONCLIENTMETRICSA ncInfo;
		ncInfo.cbSize = sizeof(ncInfo);
		::SystemParametersInfoA (SPI_GETNONCLIENTMETRICS, sizeof(ncInfo), &ncInfo, 0);
		HFONT menuHFont = CreateFontIndirectA( &ncInfo.lfMenuFont );
		if ( NULL != menuHFont ) {
			HDC dc = ::CreateCompatibleDC( NULL );// screen DC--I won't actually draw on it
			HFONT oldFont = (HFONT)SelectObject( dc, menuHFont );
			RECT rcText = {0,0,0,0};
			if ( System::isUnicodeEnabled() ) {
				::DrawTextW( dc, caption.c_str(), caption.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
			}
			else {
				AnsiString tmp = caption;
				::DrawTextA( dc, tmp.c_str(), tmp.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
			}


			SelectObject( dc, oldFont );

			// height of item is just height of a standard menu item
			result.height_ = maxVal<double>( ::GetSystemMetrics(SM_CYMENU), abs(rcText.bottom - rcText.top) );

			const int CXGAP = 1;		// num pixels between button and text
			const int CXTEXTMARGIN = 2;		// num pixels after hilite to start text
			const int CXBUTTONMARGIN = 2;		// num pixels wider button is than bitmap
			const int CYBUTTONMARGIN = 2;		// ditto for height

			// width is width of text plus a bunch of stuff
			int cx = rcText.right - rcText.left;	// text width
			cx += CXTEXTMARGIN << 1;		// L/R margin for readability
			cx += CXGAP;					// space between button and menu text

			//cx += szButton_.cx<<1;		// button width (L=button; R=empty margin)

			// whatever value I return in lpms->itemWidth, Windows will add the
			// width of a menu checkmark, so I must subtract to defeat Windows. Argh.
			//
			cx += GetSystemMetrics(SM_CXMENUCHECK)-1;
			result.width_ = cx;		// done deal

			::DeleteObject( menuHFont );
			::DeleteDC( dc );
		}

		return result;
	}
*/
	virtual double getValue( const MetricType& type, const String& text, Font* alternateFont ) {		
		double result = 0;

		switch ( type ) {
			case mtLabelHeight : {				
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,8), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,8), f );
				}
				result = pt.y_;
			}
			break;

			case mtComboBoxHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,14), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,14), f );
				}
				result = pt.y_;
			}
			break;

			case mtListItemHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,10), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,10), f );
				}
				result = pt.y_;
			}
			break;

			case mtButtonHeight : {			
				
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"BUTTON" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					RECT r;
					memset(&r,0,sizeof(r));
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, BP_PUSHBUTTON, PBS_NORMAL, 
																&r, TS_TRUE, &sz);

					MARGINS m = {0};
					Win32VisualStylesWrapper::GetThemeMargins( theme, dc, BP_PUSHBUTTON, 0, TMT_CONTENTMARGINS, NULL, &m );

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					//sz.cy += m.cyTopHeight + m.cyBottomHeight;
					result = sz.cy;
				}
				else {
					Point pt;
					if ( NULL != alternateFont ) {
						pt = DLUToPixel( Point(0,14), *alternateFont );
					}
					else {
						VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
						pt = DLUToPixel( Point(0,14), f );
					}

					result = pt.y_;
				}
			}
			break;

			case mtRadioBoxHeight : {			
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,10), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,10), f );
				}
				
				result = pt.y_;				
			}
			break;

			case mtCheckBoxHeight : {				
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,10), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,10), f );
				}
				result = pt.y_;				
			}
			break;

			case mtToolTipHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,10), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,10), f );
				}
				result = pt.y_;
			}
			break;

			case mtSeparatorHeight : {
				result = 2.0;
			}
			break;

			case mtHeaderHeight : {
				HTHEME theme = NULL;
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"Header" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					RECT r;
					memset(&r,0,sizeof(r));
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, HP_HEADERITEM, HIS_NORMAL, 
																&r, TS_TRUE, &sz);

					MARGINS m = {0};
					Win32VisualStylesWrapper::GetThemeMargins( theme, dc, HP_HEADERITEM, 0, TMT_CONTENTMARGINS, NULL, &m );

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					sz.cy += m.cyTopHeight + m.cyBottomHeight;
					result = sz.cy;
				}
				else {
					Point pt;
					if ( NULL != alternateFont ) {
						pt = DLUToPixel( Point(0,10), *alternateFont );
					}
					else {
						VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
						pt = DLUToPixel( Point(0,10), f );
					}
					result = pt.y_;
				}
			}
			break;

			case mtTreeItemHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,9), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,9), f );
				}
				result = pt.y_;
			}
			break;

			case mtTextControlHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,12), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,12), f );
				}
				result = pt.y_;
			}
			break;

			case mtVerticalProgressWidth : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(14,14), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(14,14), f );
				}
				result = pt.x_;
			}
			break;

			case mtHorizontalProgressHeight : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,14), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,14), f );
				}
				result = pt.y_;
			}
			break;

			case mtInformationalControlHeight : {
				
				HTHEME theme = NULL;
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					//theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"STATUS" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					HRESULT hr = Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SP_PANE, 0, 
						NULL, TS_TRUE, &sz);
					
					MARGINS m = {0};
					hr = Win32VisualStylesWrapper::GetThemeMargins(theme, dc, SP_PANE,0,TMT_CONTENTMARGINS,
						NULL, &m );

					int h = 0;
					hr = Win32VisualStylesWrapper::GetThemeMetric(theme,dc,SP_GRIPPER,1,TMT_HEIGHT,&h);
					

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cy + 10;// + m.;
				}
				else {
					Point pt;
					if ( NULL != alternateFont ) {
						pt = DLUToPixel( Point(0,14), *alternateFont );
					}
					else {
						VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
						pt = DLUToPixel( Point(0,14), f );
					}
					result = pt.y_;
				}
				
			}
			break;

			case mtVerticalScrollbarThumbWidth : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"SCROLLBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SBP_THUMBBTNVERT, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cx;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					
					result = ncm.iScrollWidth;
				}
			}
			break;

			case mtHorizontalScrollbarThumbHeight : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"SCROLLBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SBP_THUMBBTNHORZ, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cy;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					
					result = ncm.iScrollHeight;
				}
			}
			break;

			case mtVerticalScrollbarWidth : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"SCROLLBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SBP_LOWERTRACKVERT, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cx;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					
					result = ncm.iScrollWidth;
				}
			}
			break;

			case mtHorizontalScrollbarHeight : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"SCROLLBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, SBP_LOWERTRACKHORZ, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);
					
					result = sz.cy;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					
					result = ncm.iScrollHeight;
				}
			}
			break;

			case mtMenuIndent : {

				result = (double) ::GetSystemMetrics( SM_CXMENUCHECK ) + CXGAP + CXTEXTMARGIN;
			}
			break;

			case mtMenuSeparatorHeight : {
				result = 2;//????? Guestimate????
			}
			break;

			case mtMenuBarHeight : {
				NONCLIENTMETRICS ncm;
				memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
				ncm.cbSize = sizeof(NONCLIENTMETRICS);
				
				SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
				
				result = ncm.iMenuHeight;
			}
			break;

			

			case mtWindowBorderDelta : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,7), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,7), f );
				}

				result = pt.y_;
			}
			break;

			case mtContainerBorderDelta : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,7), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,7), f );
				}
				result = pt.y_;
			}
			break;

			case mtControlVerticalSpacing : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,4), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,4), f );
				}
				result = pt.y_;
			}
			break;

			case mtControlHorizontalSpacing : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(4,4), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(4,4), f );
				}
				result = pt.x_;
			}
			break;

			case mtInformationControlTopSpacer : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,4), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,4), f );
				}
				result = pt.y_;
			}
			break;

			case mtInformationControlBottomSpacer : {
				Point pt;
				if ( NULL != alternateFont ) {
					pt = DLUToPixel( Point(0,4), *alternateFont );
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					pt = DLUToPixel( Point(0,4), f );
				}
				result = pt.y_;
			}
			break;

			default : {
				throw RuntimeException( MAKE_ERROR_MSG_2("Invalid metric type.") );
			}
			break;
		}

		return result;
	}

	virtual Size getSize( const MetricType& type, const String& text, Font* alternateFont ) {
		Size result;
		
		switch ( type ) {
			case mtMenuItemSize : {
				NONCLIENTMETRICSA ncInfo;
				ncInfo.cbSize = sizeof(ncInfo);
				::SystemParametersInfoA (SPI_GETNONCLIENTMETRICS, sizeof(ncInfo), &ncInfo, 0);
				HFONT menuHFont = CreateFontIndirectA( &ncInfo.lfMenuFont );
				if ( NULL != menuHFont ) {
					HDC dc = ::CreateCompatibleDC( NULL );// screen DC--I won't actually draw on it
					HFONT oldFont = (HFONT)SelectObject( dc, menuHFont );
					RECT rcText = {0,0,0,0};
					if ( System::isUnicodeEnabled() ) {
						::DrawTextW( dc, text.c_str(), text.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
					}
					else {
						AnsiString tmp = text;
						::DrawTextA( dc, tmp.c_str(), tmp.size(), &rcText, DT_SINGLELINE|DT_LEFT|DT_VCENTER|DT_CALCRECT);
					}
					
					
					SelectObject( dc, oldFont );
					
					// height of item is just height of a standard menu item
					result.height_ = maxVal<double>( ::GetSystemMetrics(SM_CYMENU), abs(rcText.bottom - rcText.top) );
					
					
					// width is width of text plus a bunch of stuff
					int cx = rcText.right - rcText.left;	// text width
					cx += CXTEXTMARGIN << 1;		// L/R margin for readability
					cx += CXGAP;					// space between button and menu text
					
					int cxButn = result.height_;				// width of button

					cx += cxButn;//<<1;		// button width (L=button; R=empty margin)
					
					// whatever value I return in lpms->itemWidth, Windows will add the
					// width of a menu checkmark, so I must subtract to defeat Windows. Argh.
					//
					cx += GetSystemMetrics(SM_CXMENUCHECK)-1;
					result.width_ = cx;		// done deal
					
					::DeleteObject( menuHFont );
					::DeleteDC( dc );
				}
			}
			break;

			case mtMenuItemSeparatorSize : {
				result.height_ = GetSystemMetrics(SM_CYMENU)>>1;
				result.width_  = 0;
			}
			break;

			case mtVerticalSliderThumbSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TRACKBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TKP_THUMBVERT, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					Point pt = DLUToPixel( Point(15,15), f );
					
					result.height_ = 11;
					result.width_ = pt.x_;
				}
			}
			break;

			case mtHorizontalSliderThumbSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TRACKBAR" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TKP_THUMB, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					Point pt = DLUToPixel( Point(0,15), f );
					
					result.height_ = pt.y_;
					result.width_ = 11;
				}
			}
			break;

			case mtTabSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TAB" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					int dcs = SaveDC(dc);
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					HFONT font = NULL;	
					SIZE textSz;
					memset(&textSz,0,sizeof(textSz));

					if ( System::isUnicodeEnabled() ) {
						LOGFONTW* lf = (LOGFONTW*) f.getFontPeer()->getFontHandleID();
						font = ::CreateFontIndirectW( lf );
						::SelectObject( dc, font );
						
						if ( text.empty() ) {
							::GetTextExtentPoint32W( dc, L"EM", 2, &textSz );
						}
						else {
							::GetTextExtentPoint32W( dc, text.c_str(), text.size(), &textSz );
						}
					}
					else {
						LOGFONTA* lf = (LOGFONTA*) f.getFontPeer()->getFontHandleID();
						AnsiString s = text;
						font = ::CreateFontIndirectA( lf );
						::SelectObject( dc, font );
						
						if ( s.empty() ) {
							::GetTextExtentPoint32A( dc, "EM", 2, &textSz );
						}
						else {
							::GetTextExtentPoint32A( dc, s.c_str(), s.size(), &textSz );
						}
					}

					RestoreDC(dc, dcs);
					DeleteObject( font );

					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TABP_TABITEM, 0, 
																NULL, TS_TRUE, &sz);					


					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx + textSz.cx;
					result.height_ = sz.cy;
				}
				else {
					HDC dc = ::GetDC( ::GetDesktopWindow() );
					int dcs = SaveDC(dc);
					SIZE textSz;
					memset(&textSz,0,sizeof(textSz));
					SIZE textSz2;
					memset(&textSz2,0,sizeof(textSz2));
					
					VCF::Font f = getDefaultFontFor( UIMetricsManager::ftControlFont );
					HFONT font = NULL;			
					if ( System::isUnicodeEnabled() ) {
						LOGFONTW* lf = (LOGFONTW*) f.getFontPeer()->getFontHandleID();
						font = ::CreateFontIndirectW( lf );
						::SelectObject( dc, font );
						::GetTextExtentPoint32W( dc, L"EM", 2, &textSz );
						if ( text.empty() ) {
							textSz2 = textSz;
						}
						else {
							::GetTextExtentPoint32W( dc, text.c_str(), text.size(), &textSz2 );
						}
					}
					else {
						LOGFONTA* lf = (LOGFONTA*) f.getFontPeer()->getFontHandleID();
						AnsiString s = text;
						font = ::CreateFontIndirectA( lf );
						::SelectObject( dc, font );
						::GetTextExtentPoint32A( dc, "EM", 2, &textSz );
						if ( s.empty() ) {
							textSz2 = textSz;
						}
						else {
							::GetTextExtentPoint32A( dc, s.c_str(), s.size(), &textSz2 );
						}
					}
					
					result.height_ = maxVal<int>( textSz.cy, 21 );
					result.width_ = textSz2.cx + result.height_ + 5.0;
					
					
					
					RestoreDC(dc, dcs);
					DeleteObject( font );
					::ReleaseDC( ::GetDesktopWindow(), dc );
				}
			}
			break;

			case mtRadioBoxBtnSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"BUTTON" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, BP_RADIOBUTTON, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					result.width_ = 13;
					result.height_ = 13;
				}
			}
			break;

			case mtCheckBoxBtnSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"BUTTON" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, BP_CHECKBOX, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					result.width_ = 13;
					result.height_ = 13;
				}
			}
			break;

			case mtComboBoxDropBtnSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"COMBOBOX" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, CP_DROPDOWNBUTTON, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {
					NONCLIENTMETRICS ncm;
					memset( &ncm, 0, sizeof(NONCLIENTMETRICS) );
					ncm.cbSize = sizeof(NONCLIENTMETRICS);
					
					SystemParametersInfo( SPI_GETNONCLIENTMETRICS, ncm.cbSize, &ncm, 0 );
					result.width_ = ncm.iScrollWidth;
					result.height_ = ncm.iScrollHeight;
				}
			}
			break;

			case mtDisclosureButtonSize : {
				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TREEVIEW" );
				}
				
				if ( theme ) {
					HDC dc = GetDC( ::GetDesktopWindow() );
					SIZE sz;
					
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TVP_GLYPH, 0, 
																NULL, TS_TRUE, &sz);

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.width_ = sz.cx;
					result.height_ = sz.cy;
				}
				else {

				}
			}
			break;

			default : {
				throw RuntimeException( MAKE_ERROR_MSG_2("Invalid metric type.") );
			}
			break;
		}

		return result;
	}

	virtual Rect getRect( const MetricType& type, Rect* rect, Font* alternateFont ) {
		Rect result;

		switch ( type ) {
			case mtTabPaneContentRect : {
				if ( NULL == rect ) {					
					throw RuntimeException( MAKE_ERROR_MSG_2("mtTabPaneContentRect needs a valid rect instance - you passed in a NULL one!") );
				}


				HTHEME theme = NULL;
				
				if ( Win32VisualStylesWrapper::IsThemeActive() ) {
					theme = Win32VisualStylesWrapper::OpenThemeData( NULL, L"TAB" );
				}
				
				if ( theme ) {					
					HDC dc = GetDC( ::GetDesktopWindow() );
					
					
					result = *rect;
					
					RECT r;
					r.left = result.left_;
					r.top = result.top_;
					r.right = result.right_;
					r.bottom = result.bottom_;
					RECT paneContent = r;
					RECT bodyContent = r;
					
					
					Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc, 
						TABP_PANE, 1, &r, &paneContent );
					
					Win32VisualStylesWrapper::GetThemeBackgroundContentRect(theme, dc, 
						TABP_BODY, 1, &r, &bodyContent );

					int dy = abs(bodyContent.top - paneContent.top);
					
					SIZE tabSz;
					memset(&tabSz,0,sizeof(tabSz));
					Win32VisualStylesWrapper::GetThemePartSize(theme, dc, TABP_TABITEM, TIS_NORMAL, 
																&r, TS_TRUE, &tabSz);

										
					paneContent.top += tabSz.cy + dy;
					

					Win32VisualStylesWrapper::CloseThemeData( theme );
					ReleaseDC(::GetDesktopWindow(),dc);

					result.left_ = paneContent.left;
					result.top_ = paneContent.top;
					result.right_ = paneContent.right;
					result.bottom_ = paneContent.bottom;
				}
				else {
					result = *rect;

					result.inflate( -5, -5 );

					Size sz = getSize(mtTabSize,"",NULL);
					result.top_ += sz.height_;
				}

			}
			break;

			default : {
				throw RuntimeException( MAKE_ERROR_MSG_2("Invalid metric type.") );
			}
			break;
		}

		return result;
	}
};







class Win32UnitTransformer : public UnitTransformer {
public:
	virtual String transform( const String& s ) {

		const VCFChar* P = s.c_str();
		const VCFChar* start = P;

		String val,unit;

		while ( P-start < s.length() ) {
			if ( *P == '$' ) {
				P++;
				while ( ((*P >= '0') && (*P <= '9')) || ((*P >= 'A') && (*P <= 'F')) || ((*P >= 'a') && (*P <= 'f')) && (P-start < s.length()) ) {
					P++;
				}

				if ( P-start >= s.length() ) {
					return s;
				}

				val.assign( start, ( P - start ) );
				
				unit.assign( P, s.length() - val.length() );

				break;
			}
			else if ( (*P == '-') ||  ((*P >= '0') && (*P <= '9')) ) {
				P++;
				while ( ((*P >= '0') && (*P <= '9')) && (P-start < s.length()) ) {
					P++;
				}

				while ( ((*P >= '0') && (*P <= '9')) || (*P == '.') || (*P == 'e') || (*P == '+') || (*P == '-') && (P-start < s.length()) ) {
					P++;
				}

				if ( P-start >= s.length() ) {
					return s;
				}

				val.assign( start, ( P - start ) );

				unit.assign( P, s.length() - val.length() );

				break;
			}
			P++;
		}
		

		unit = StringUtils::lowerCase(unit);

		if (unit != "px" ) {
			HDC dc = GetDC( ::GetDesktopWindow() );
			
			double dpi = (double)GetDeviceCaps( dc, LOGPIXELSY);
			
			ReleaseDC(::GetDesktopWindow(),dc);
			
			double v = StringUtils::fromStringAsDouble(val);
			
			if (unit == "in" ) {
				val = StringUtils::toString( v * dpi );
			}
			else if (unit == "pt" ) {
				val = StringUtils::toString( (v / 72.0) * dpi );
			}
			else if (unit == "em" ) {
				
			}
			else if (unit == "cm" ) {
				val = StringUtils::toString( (v / 2.54 ) * dpi );
			}
		}

		return val;
	}
};

static Win32UnitTransformer win32Tfrm;


Win32FontManager* Win32FontManager::win32FontMgr = NULL;


Win32GraphicsToolkit::Win32GraphicsToolkit():
	systemFont_(NULL)
{
	Win32FontManager::create();


	loadSystemColors();
	registerImageLoader( "image/bmp", new BMPLoader() );

	initSystemFont();	

	VFFInputStream::setTransformer( &win32Tfrm );

	metricsMgr_ = new Win32UIMetricsManager();
}

Win32GraphicsToolkit::~Win32GraphicsToolkit()
{
	delete systemFont_;
	delete Win32FontManager::getFontManager();
}

void Win32GraphicsToolkit::internal_systemSettingsChanged()
{
	StringUtils::trace( "Win32GraphicsToolkit::internal_systemSettingsChanged()\n" );

	if ( System::isUnicodeEnabled() ) {
		HFONT defGUIFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
		LOGFONTW lf = {0};
		GetObjectW( defGUIFont, sizeof(LOGFONTW), &lf );

		systemFont_->setBold( (lf.lfWeight == FW_BOLD) ? true : false );
		systemFont_->setItalic( lf.lfItalic == TRUE );
		systemFont_->setUnderlined( lf.lfUnderline == TRUE );
		systemFont_->setStrikeOut( lf.lfStrikeOut == TRUE );
		systemFont_->setPixelSize( lf.lfHeight );
		systemFont_->setName( String(lf.lfFaceName) );
	}
	else {
		HFONT defGUIFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
		LOGFONTA lf = {0};
		GetObjectA( defGUIFont, sizeof(LOGFONTA), &lf );

		systemFont_->setBold( (lf.lfWeight == FW_BOLD) ? true : false );
		systemFont_->setItalic( lf.lfItalic == TRUE );
		systemFont_->setUnderlined( lf.lfUnderline == TRUE );
		systemFont_->setStrikeOut( lf.lfStrikeOut == TRUE );
		systemFont_->setPixelSize( lf.lfHeight );
		systemFont_->setName( String(lf.lfFaceName) );
	}

	
	systemColorNameMap_->clear();

	std::map<uint32,Color*>::iterator it = systemColors_.begin();
	while ( it != systemColors_.end() ){
		delete it->second;
		it++;
	}
	systemColors_.clear();

	loadSystemColors();
}

void Win32GraphicsToolkit::initSystemFont()
{
	systemFont_ = new Font();

	if ( System::isUnicodeEnabled() ) {
		HFONT defGUIFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
		LOGFONTW lf = {0};
		GetObjectW( defGUIFont, sizeof(LOGFONTW), &lf );

		systemFont_->setBold( (lf.lfWeight == FW_BOLD) ? true : false );
		systemFont_->setItalic( lf.lfItalic == TRUE );
		systemFont_->setUnderlined( lf.lfUnderline == TRUE );
		systemFont_->setStrikeOut( lf.lfStrikeOut == TRUE );
		systemFont_->setPixelSize( lf.lfHeight );
		systemFont_->setName( String(lf.lfFaceName) );
	}
	else {
		HFONT defGUIFont = (HFONT)GetStockObject( DEFAULT_GUI_FONT );
		LOGFONTA lf = {0};
		GetObjectA( defGUIFont, sizeof(LOGFONTA), &lf );

		systemFont_->setBold( (lf.lfWeight == FW_BOLD) ? true : false );
		systemFont_->setItalic( lf.lfItalic == TRUE );
		systemFont_->setUnderlined( lf.lfUnderline == TRUE );
		systemFont_->setStrikeOut( lf.lfStrikeOut == TRUE );
		systemFont_->setPixelSize( lf.lfHeight );
		systemFont_->setName( String(lf.lfFaceName) );
	}


}

ContextPeer* Win32GraphicsToolkit::internal_createContextPeer( OSHandleID contextID )
{
	ContextPeer* result = NULL;

	result = new Win32Context( contextID );

	return result;
}

ContextPeer* Win32GraphicsToolkit::internal_createContextPeer( const uint32& width, const uint32& height )
{
	return new Win32Context( width, height );
}

FontPeer* Win32GraphicsToolkit::internal_createFontPeer( const String& fontName )
{
	return new Win32Font( fontName );
}

FontPeer* Win32GraphicsToolkit::internal_createFontPeer( const String& fontName, const double& pointSize )
{
	return new Win32Font( fontName, pointSize );
}


Image* Win32GraphicsToolkit::internal_createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType )
{
	Image* result = NULL;

	if ( Image::itColor == imageType ) {
		result = new Win32Image( width, height );
	}
	else if ( Image::itGrayscale == imageType ) {
		result = new Win32GrayScaleImage( width, height );
	}

	return result;
}

Image* Win32GraphicsToolkit::internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType )
{
	if ( NULL != context ){
		if ( Image::itColor == imageType ) {
			return new Win32Image( context, rect );
		}
		else if ( Image::itGrayscale == imageType ) {
			return new Win32GrayScaleImage( context, rect );
		}
	}

	return NULL;
}

double Win32GraphicsToolkit::internal_getDPI( GraphicsContext* context )
{
	double result = 0.0;
	if ( NULL == context ) {
		HDC dc = GetDC( ::GetDesktopWindow() );
		result = (double)GetDeviceCaps( dc, LOGPIXELSY);
		ReleaseDC( ::GetDesktopWindow(), dc );
	}
	else {
		result = (double) GetDeviceCaps( (HDC)context->getPeer()->getContextID(), LOGPIXELSY );
	}
	return result;
}

PrintSessionPeer* Win32GraphicsToolkit::internal_createPrintSessionPeer()
{
	return new Win32PrintSession();
}

void Win32GraphicsToolkit::loadSystemColors()
{
	Color* sysColor = NULL;
	sysColor = new Color( ::GetSysColor( COLOR_BTNSHADOW ), Color::cpsABGR );
	systemColors_[SYSCOLOR_SHADOW] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SHADOW";

	sysColor = new Color( ::GetSysColor( COLOR_3DFACE ), Color::cpsABGR );
	systemColors_[SYSCOLOR_FACE] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_FACE";

	sysColor = new Color( ::GetSysColor( COLOR_3DHILIGHT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_HIGHLIGHT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_HIGHLIGHT";

	sysColor = new Color( ::GetSysColor( COLOR_ACTIVECAPTION ), Color::cpsABGR );
	systemColors_[SYSCOLOR_ACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_CAPTION";

	sysColor = new Color( ::GetSysColor( COLOR_ACTIVEBORDER ), Color::cpsABGR );
	systemColors_[SYSCOLOR_ACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_ACTIVE_BORDER";

	sysColor = new Color( ::GetSysColor( COLOR_DESKTOP ), Color::cpsABGR );
	systemColors_[SYSCOLOR_DESKTOP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_DESKTOP";

	sysColor = new Color( ::GetSysColor( COLOR_CAPTIONTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_CAPTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_CAPTION_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_HIGHLIGHT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_SELECTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION";

	sysColor = new Color( ::GetSysColor( COLOR_HIGHLIGHTTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_SELECTION_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_SELECTION_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_INACTIVEBORDER ), Color::cpsABGR );
	systemColors_[SYSCOLOR_INACTIVE_BORDER] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_BORDER";

	sysColor = new Color( ::GetSysColor( COLOR_INACTIVECAPTION ), Color::cpsABGR );
	systemColors_[SYSCOLOR_INACTIVE_CAPTION] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_INACTIVE_CAPTION";

	sysColor = new Color( ::GetSysColor( COLOR_INFOBK ), Color::cpsABGR );
	systemColors_[SYSCOLOR_TOOLTIP] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP";

	sysColor = new Color( ::GetSysColor( COLOR_INFOTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_TOOLTIP_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_TOOLTIP_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_MENU ), Color::cpsABGR );
	systemColors_[SYSCOLOR_MENU] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU";

	sysColor = new Color( ::GetSysColor( COLOR_MENUTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_MENU_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_MENU_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_WINDOW ), Color::cpsABGR );
	systemColors_[SYSCOLOR_WINDOW] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW";

	sysColor = new Color( ::GetSysColor( COLOR_WINDOWTEXT ), Color::cpsABGR );
	systemColors_[SYSCOLOR_WINDOW_TEXT] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_TEXT";

	sysColor = new Color( ::GetSysColor( COLOR_WINDOWFRAME ), Color::cpsABGR );
	systemColors_[SYSCOLOR_WINDOW_FRAME] = sysColor;
	(*systemColorNameMap_)[*sysColor] = "SYSCOLOR_WINDOW_FRAME";

}

GraphicsResourceBundlePeer* Win32GraphicsToolkit::internal_createGraphicsResourceBundlePeer()
{
	return new Win32GraphicsResourceBundle();
}


/**
$Id$
*/
