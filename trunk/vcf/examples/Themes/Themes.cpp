//Themes.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/GraphicsKit/DrawUIState.h"


using namespace VCF;


String SysColorToString( int i ) {
	String result;

	switch ( i ) {
		case SYSCOLOR_SHADOW : {
			result = "SYSCOLOR_SHADOW";
		}
		break;

		case SYSCOLOR_FACE : {
			result = "SYSCOLOR_FACE";
		}
		break;

		case SYSCOLOR_HIGHLIGHT : {
			result = "SYSCOLOR_HIGHLIGHT";
		}
		break;

		case SYSCOLOR_ACTIVE_CAPTION : {
			result = "SYSCOLOR_ACTIVE_CAPTION";
		}
		break;

		case SYSCOLOR_ACTIVE_BORDER : {
			result = "SYSCOLOR_ACTIVE_BORDER";
		}
		break;

		case SYSCOLOR_DESKTOP : {
			result = "SYSCOLOR_DESKTOP";
		}
		break;

		case SYSCOLOR_CAPTION_TEXT : {
			result = "SYSCOLOR_CAPTION_TEXT";
		}
		break;

		case SYSCOLOR_SELECTION : {
			result = "SYSCOLOR_SELECTION";
		}
		break;

		case SYSCOLOR_SELECTION_TEXT : {
			result = "SYSCOLOR_SELECTION_TEXT";
		}
		break;

		case SYSCOLOR_INACTIVE_BORDER : {
			result = "SYSCOLOR_INACTIVE_BORDER";
		}
		break;

		case SYSCOLOR_INACTIVE_CAPTION : {
			result = "SYSCOLOR_INACTIVE_CAPTION";
		}
		break;

		case SYSCOLOR_TOOLTIP : {
			result = "SYSCOLOR_TOOLTIP";
		}
		break;

		case SYSCOLOR_TOOLTIP_TEXT : {
			result = "SYSCOLOR_TOOLTIP_TEXT";
		}
		break;

		case SYSCOLOR_MENU : {
			result = "SYSCOLOR_MENU";
		}
		break;

		case SYSCOLOR_MENU_TEXT : {
			result = "SYSCOLOR_MENU_TEXT";
		}
		break;

		case SYSCOLOR_WINDOW : {
			result = "SYSCOLOR_WINDOW";
		}
		break;

		case SYSCOLOR_WINDOW_TEXT : {
			result = "SYSCOLOR_WINDOW_TEXT";
		}
		break;

		case SYSCOLOR_WINDOW_FRAME : {
			result = "SYSCOLOR_WINDOW_FRAME";
		}
		break;
	}

	return result;
}

class SysColorsPanel : public Panel {
public:
	SysColorsPanel() {
		setBorder( NULL );
	}
	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		Rect r = getClientBounds();
		r.inflate( -10, -10 );

		Light3DBorder bdr;

		uint32 colorIdx =  SYSCOLOR_SHADOW ;
		int cols = 4;	
		int width = r.getWidth() - (cols * 5);
		Rect colorCell;
		colorCell.setRect( r.left_, r.top_, 
							r.left_ + (width/cols),
							r.top_ + (width/cols) );

		Rect textRect;

		for (int i=1;i<=18;i++ ) {
			Color* color = GraphicsToolkit::getSystemColor( colorIdx );

			bdr.paint( &colorCell, ctx );

			Rect fill = bdr.getClientRect( &colorCell, NULL );

			ctx->rectangle( &fill );
			ctx->setColor( color );
			Color tmp = *color;

			ctx->fillPath();

			textRect = colorCell;
			textRect.inflate(-5, -5 );
			long options = GraphicsContext::tdoCenterHorzAlign | 
							GraphicsContext::tdoCenterVertAlign;

			tmp = tmp.invert();

			ctx->getCurrentFont()->setPointSize( 6 );
			ctx->getCurrentFont()->setColor( &tmp );

			ctx->textBoundedBy( &textRect, SysColorToString(colorIdx), options );

			if ( i % cols == 0 ) {
				colorCell.setRect( r.left_, colorCell.bottom_, 
							r.left_ + (width/cols),
							colorCell.bottom_ + (width/cols) );

				colorCell.offset( 0, 5 );
			}
			else {
				colorCell.offset( colorCell.getWidth() + 5, 0 );
			}

			colorIdx ++;
		}

	}
};	

class ButtonsPanel : public Panel {
public:
	ButtonsPanel() {
		setBorder( NULL );
	}
	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		Rect r = getClientBounds();

		r.inflate( -10, -10 );

		Rect btn = r;
		Rect textR = r;
		btn.right_ = btn.left_ + btn.getWidth()/2;
		btn.bottom_ = btn.top_ + 35;

		textR.left_ = btn.right_;
		textR.bottom_ = btn.bottom_;

		long options = GraphicsContext::tdoCenterHorzAlign | 
							GraphicsContext::tdoCenterVertAlign;

		ctx->textBoundedBy( &textR, "Button Focus Rect", options );

		
		ctx->drawThemeButtonFocusRect( &btn );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Button Rect", options );

		ButtonState state;
		state.setEnabled( true );
		state.setFocused( false );
		state.setActive( true );

		state.buttonCaption_ = "A Button";
		ctx->drawThemeButtonRect( &btn, state, &btn );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Button Rect Pressed", options );
		
		state.setPressed(true);		
		ctx->drawThemeButtonRect( &btn, state, &btn );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Button Rect Disabled", options );
		
		state.setPressed(false);		
		state.setEnabled( false );
		ctx->drawThemeButtonRect( &btn, state, &btn );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Check box Rect", options );
		
		ButtonState cbState;
		cbState.setEnabled( true );
		cbState.setFocused( false );
		cbState.setActive( true );
		cbState.buttonCaption_ = "A Checkbox";

		ctx->drawThemeCheckboxRect( &btn, cbState );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Check box Rect toggled", options );

		cbState.setToggled( true );
		ctx->drawThemeCheckboxRect( &btn, cbState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Check box Rect Disabled and toggled", options );

		cbState.setEnabled( false );
		ctx->drawThemeCheckboxRect( &btn, cbState );


		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Radio button Rect", options );

		ButtonState rbState;
		rbState.setEnabled( true );
		rbState.setFocused( false );
		rbState.setActive( true );
		rbState.buttonCaption_ = "A Radio button";

		ctx->drawThemeRadioButtonRect( &btn, rbState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Radio box Rect toggled", options );

		rbState.setToggled( true );
		ctx->drawThemeRadioButtonRect( &btn, rbState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Radio box Rect Disabled and toggled", options );

		rbState.setEnabled( false );
		ctx->drawThemeRadioButtonRect( &btn, rbState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ButtonState cmboState;
		cmboState.setEnabled( true );
		cmboState.setFocused( false );
		cmboState.setActive( true );
		cmboState.buttonCaption_ = "A Combo Box";

		ctx->textBoundedBy( &textR, "Combo box Rect", options );
		ctx->drawThemeComboboxRect( &btn, cmboState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Combo box Rect Disabled", options );

		cmboState.setEnabled( false );
		ctx->drawThemeComboboxRect( &btn, cmboState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ctx->textBoundedBy( &textR, "Combo box Rect Focused", options );

		cmboState.setEnabled( true );
		cmboState.setFocused( true );
		ctx->drawThemeComboboxRect( &btn, cmboState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		ScrollBarState scrollState;
		scrollState.setEnabled( true );
		scrollState.setFocused( false );
		scrollState.setActive( true );		
		scrollState.setButtonType( ScrollBarState::sbUpOrLeftBtn );

		ctx->textBoundedBy( &textR, "Scroll bar btn Rect", options );
		ctx->drawThemeScrollButtonRect( &btn, scrollState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		scrollState.setScrollBarIncrArrowPressed( true );
		ctx->textBoundedBy( &textR, "Scroll bar btn pressed Rect", options );
		ctx->drawThemeScrollButtonRect( &btn, scrollState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		scrollState.setEnabled( false );
		ctx->textBoundedBy( &textR, "Scroll bar btn disabled Rect", options );
		ctx->drawThemeScrollButtonRect( &btn, scrollState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );


		DisclosureButtonState disclState;
		disclState.setEnabled( true );
		disclState.setFocused( false );
		disclState.setActive( true );
		disclState.setClosed( true );
		disclState.setOpened( false );

		ctx->textBoundedBy( &textR, "Disclosure btn Rect - closed", options );
		ctx->drawThemeDisclosureButton( &btn, disclState );

		btn.offset( 0, 40 );
		textR.offset( 0, 40 );

		disclState.setClosed( false );
		disclState.setOpened( true );
		ctx->textBoundedBy( &textR, "Disclosure btn Rect - open", options );
		ctx->drawThemeDisclosureButton( &btn, disclState );
	}
};	



class EdgesPanel : public Panel {
public:
	EdgesPanel() {
		setBorder( NULL );
	}
	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		Rect r = getClientBounds();

		r.inflate( -10, -10 );

		int height = 70;

		Rect edgeR = r;
		Rect textR = r;
		edgeR.right_ = edgeR.left_ + edgeR.getWidth()/2;
		edgeR.bottom_ = edgeR.top_ + height;

		textR.left_ = edgeR.right_;
		textR.bottom_ = edgeR.bottom_;

		long options = GraphicsContext::tdoCenterHorzAlign | 
							GraphicsContext::tdoCenterVertAlign;

		ctx->textBoundedBy( &textR, "Button Focus Rect", options );

		
		ctx->drawThemeButtonFocusRect( &edgeR );

		edgeR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );


		ctx->textBoundedBy( &textR, "Selection Rect", options );

		DrawUIState state;
		ctx->drawThemeSelectionRect( &edgeR, state );

		edgeR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );



		ctx->textBoundedBy( &textR, "Focus Rect", options );
		ctx->drawThemeFocusRect( &edgeR, state );


		edgeR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );
		
		long sides = GraphicsContext::etAllSides;
		long style = GraphicsContext::etRecessed;
		ctx->textBoundedBy( &textR, "Edge Rect - Recessed", options );
		ctx->drawThemeEdge( &edgeR, state, sides, style );

		edgeR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );

		style = GraphicsContext::etEtched;
		ctx->textBoundedBy( &textR, "Edge Rect - Etched", options );
		ctx->drawThemeEdge( &edgeR, state, sides, style );

		edgeR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );

		style = GraphicsContext::etRaised;
		ctx->textBoundedBy( &textR, "Edge Rect - Raised", options );
		ctx->drawThemeEdge( &edgeR, state, sides, style );

		edgeR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );

		style = GraphicsContext::etSunken;
		ctx->textBoundedBy( &textR, "Edge Rect - Sunken", options );
		ctx->drawThemeEdge( &edgeR, state, sides, style );
		

	}
};	


class TabsPanel : public Panel {
public:
	TabsPanel() {
		setBorder( NULL );
	}
	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		Rect r = getClientBounds();

		r.inflate( -10, -10 );

		int height = 70;

		Rect tabsR = r;
		Rect textR = r;
		tabsR.right_ = tabsR.left_ + tabsR.getWidth()/2;
		tabsR.bottom_ = tabsR.top_ + height;

		textR.left_ = tabsR.right_;
		textR.bottom_ = tabsR.bottom_;

		long options = GraphicsContext::tdoCenterHorzAlign | 
							GraphicsContext::tdoCenterVertAlign;

		ctx->textBoundedBy( &textR, "Tab Rect", options );

		DrawUIState state;
		ctx->drawThemeTabPage( &tabsR, state );

		tabsR.offset( 0, tabsR.getHeight() + 10 );
		textR.offset( 0, textR.getHeight() + 10 );
		
		tabsR.bottom_ += 100;
		textR.bottom_ = tabsR.bottom_;

		ctx->textBoundedBy( &textR, "Complete Tabs Rect", options );

		TabState tab;
		TabState selectedTab;
		state.setEnabled(true);
		std::vector<String> tabs;
		tabs.push_back( "Page 1" );
		tabs.push_back( "Page 2" );
		tabs.push_back( "Page 3" );
		tabs.push_back( "Page 4" );

		ctx->drawThemeTabs( &tabsR, state, selectedTab, tab, tabs, 2 );


		tabsR.offset( 0, tabsR.getHeight() + 10 );
		textR.offset( 0, textR.getHeight() + 10 );

		ctx->textBoundedBy( &textR, "Complete Tabs Rect disabled", options );

		state.setEnabled(false);			

		ctx->drawThemeTabs( &tabsR, state, selectedTab, tab, tabs, 1 );

	}
};	



class SlidersPanel : public Panel {
public:
	SlidersPanel() {
		setBorder( NULL );
	}
	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		Rect r = getClientBounds();

		r.inflate( -10, -10 );

		int height = 40;

		Rect sliderR = r;
		Rect textR = r;
		sliderR.right_ = sliderR.left_ + sliderR.getWidth()/2;
		sliderR.bottom_ = sliderR.top_ + height;

		textR.left_ = sliderR.right_;
		textR.bottom_ = sliderR.bottom_;

		long options = GraphicsContext::tdoCenterHorzAlign | 
							GraphicsContext::tdoCenterVertAlign;

		ctx->textBoundedBy( &textR, "Horizontal Slider Rect", options );

		SliderState horzState;
		horzState.setEnabled( true );
		horzState.setTickMarkingOnTopLeft( true );
		horzState.setTickMarkingOnBottomRight( false );
		horzState.setVertical( false );
		horzState.min_ = 0;
		horzState.max_ = 100;
		horzState.position_ = 23;
		
		ctx->drawThemeSlider( &sliderR, horzState );
		

		sliderR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );


		horzState.setEnabled( false );
		horzState.position_ = 65;
		horzState.setTickMarkingOnBottomRight(true);
		horzState.setTickMarkingOnTopLeft( false );
		

		ctx->textBoundedBy( &textR, "Horizontal Slider disabled Rect", options );
		ctx->drawThemeSlider( &sliderR, horzState );

		sliderR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );


		horzState.setEnabled( true );
		horzState.position_ = 37;
		horzState.setTickMarkingOnBottomRight(false);
		horzState.setTickMarkingOnTopLeft( false );
		horzState.setPressed( true );

		ctx->textBoundedBy( &textR, "Horizontal Slider pressed Rect", options );
		ctx->drawThemeSlider( &sliderR, horzState );

		sliderR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );

		sliderR.bottom_ += 40;
		textR.bottom_ += 40;


		ctx->textBoundedBy( &textR, "Vertical Slider Rect", options );

		SliderState vertState;
		vertState.setEnabled( true );
		vertState.setTickMarkingOnTopLeft( true );
		vertState.setTickMarkingOnBottomRight( false );
		vertState.setVertical( true );
		vertState.min_ = 0;
		vertState.max_ = 100;
		vertState.position_ = 23;
		
		ctx->drawThemeSlider( &sliderR, vertState );

		sliderR.offset( 0, sliderR.getHeight() + 10 );
		textR.offset( 0, textR.getHeight() + 10 );

		ctx->textBoundedBy( &textR, "Vertical Slider Rect disabled", options );
		vertState.setEnabled( false );
		vertState.position_ = 65;
		vertState.setTickMarkingOnBottomRight(true);
		vertState.setTickMarkingOnTopLeft( false );
		ctx->drawThemeSlider( &sliderR, vertState );

		sliderR.offset( 0, sliderR.getHeight() + 10 );
		textR.offset( 0, textR.getHeight() + 10 );


		vertState.setEnabled( true );
		vertState.position_ = 37;
		vertState.setTickMarkingOnBottomRight(false);
		vertState.setTickMarkingOnTopLeft( false );
		vertState.setPressed( true );

		ctx->textBoundedBy( &textR, "Vertical Slider pressed Rect", options );
		ctx->drawThemeSlider( &sliderR, vertState );
	}
};	


class ProgressPanel : public Panel {
public:
	ProgressPanel() {
		setBorder( NULL );
	}
	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		Rect r = getClientBounds();

		r.inflate( -10, -10 );

		int height = 40;

		Rect progressR = r;
		Rect textR = r;
		progressR.right_ = progressR.left_ + progressR.getWidth()/2;
		progressR.bottom_ = progressR.top_ + height;

		textR.left_ = progressR.right_;
		textR.bottom_ = progressR.bottom_;

		long options = GraphicsContext::tdoCenterHorzAlign | 
							GraphicsContext::tdoCenterVertAlign;

		ctx->textBoundedBy( &textR, "Horizontal Progress bar Rect", options );

		ProgressState horzState;
		horzState.setEnabled( true );
		horzState.setVertical( false );
		horzState.min_ = 0;
		horzState.max_ = 100;
		horzState.position_ = 23;
		
		ctx->drawThemeProgress( &progressR, horzState );
		

		progressR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );


		horzState.setEnabled( false );
		horzState.position_ = 65;
		

		ctx->textBoundedBy( &textR, "Horizontal Progress bar disabled Rect", options );
		ctx->drawThemeProgress( &progressR, horzState );

		progressR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );


		horzState.setEnabled( true );
		horzState.position_ = 37;
		horzState.progressCaption_ = "Progress...";

		ctx->textBoundedBy( &textR, "Horizontal Progress bar pressed Rect", options );
		ctx->drawThemeProgress( &progressR, horzState );

		progressR.offset( 0, height + 10 );
		textR.offset( 0, height + 10 );

		progressR.bottom_ += 40;
		textR.bottom_ += 40;


		ctx->textBoundedBy( &textR, "Vertical Progress bar Rect", options );

		ProgressState vertState;
		vertState.setEnabled( true );
		vertState.setVertical( true );
		vertState.min_ = 0;
		vertState.max_ = 100;
		vertState.position_ = 23;
		
		ctx->drawThemeProgress( &progressR, vertState );

		progressR.offset( 0, progressR.getHeight() + 10 );
		textR.offset( 0, textR.getHeight() + 10 );

		ctx->textBoundedBy( &textR, "Vertical Progress bar Rect disabled", options );
		vertState.setEnabled( false );
		vertState.position_ = 65;
		ctx->drawThemeProgress( &progressR, vertState );

		progressR.offset( 0, progressR.getHeight() + 10 );
		textR.offset( 0, textR.getHeight() + 10 );


		vertState.setEnabled( true );
		vertState.position_ = 37;

		vertState.progressCaption_ = "Progress...";
		ctx->textBoundedBy( &textR, "Vertical Progress bar pressed Rect", options );
		ctx->drawThemeProgress( &progressR, vertState );
	}
};	



class ThemeSizesPanel : public Panel {
public:
	ScrollbarManager* scrollBarMgr;
	std::map<int,String> metricsToStringMap;
	ThemeSizesPanel() {
		setBorder( NULL );

		scrollBarMgr = new ScrollbarManager(this);
		scrollBarMgr->setTarget( this );
		scrollBarMgr->setHasHorizontalScrollbar( true );
		scrollBarMgr->setHasVerticalScrollbar( true );
		scrollBarMgr->setKeepScrollbarsVisible( true, true );

		metricsToStringMap[UIMetricsManager::mtLabelHeight] = "UIMetricsManager::mtLabelHeight";
		metricsToStringMap[UIMetricsManager::mtComboBoxHeight] = "UIMetricsManager::mtComboBoxHeight";
		metricsToStringMap[UIMetricsManager::mtListItemHeight] = "UIMetricsManager::mtListItemHeight";
		metricsToStringMap[UIMetricsManager::mtButtonHeight] = "UIMetricsManager::mtButtonHeight";
		metricsToStringMap[UIMetricsManager::mtRadioBoxHeight] = "UIMetricsManager::mtRadioBoxHeight";
		metricsToStringMap[UIMetricsManager::mtCheckBoxHeight] = "UIMetricsManager::mtCheckBoxHeight";
		metricsToStringMap[UIMetricsManager::mtToolTipHeight] = "UIMetricsManager::mtToolTipHeight";
		metricsToStringMap[UIMetricsManager::mtSeparatorHeight] = "UIMetricsManager::mtSeparatorHeight";
		metricsToStringMap[UIMetricsManager::mtHeaderHeight] = "UIMetricsManager::mtHeaderHeight";
		metricsToStringMap[UIMetricsManager::mtTreeItemHeight] = "UIMetricsManager::mtTreeItemHeight";
		metricsToStringMap[UIMetricsManager::mtTextControlHeight] = "UIMetricsManager::mtTextControlHeight";
		metricsToStringMap[UIMetricsManager::mtVerticalProgressWidth] = "UIMetricsManager::mtVerticalProgressWidth";
		metricsToStringMap[UIMetricsManager::mtHorizontalProgressHeight] = "UIMetricsManager::mtHorizontalProgressHeight";
		metricsToStringMap[UIMetricsManager::mtInformationalControlHeight] = "UIMetricsManager::mtInformationalControlHeight";
		metricsToStringMap[UIMetricsManager::mtVerticalScrollbarThumbWidth] = "UIMetricsManager::mtVerticalScrollbarThumbWidth";
		metricsToStringMap[UIMetricsManager::mtHorizontalScrollbarThumbHeight] = "UIMetricsManager::mtHorizontalScrollbarThumbHeight";
		metricsToStringMap[UIMetricsManager::mtVerticalScrollbarWidth] = "UIMetricsManager::mtVerticalScrollbarWidth";
		metricsToStringMap[UIMetricsManager::mtHorizontalScrollbarHeight] = "UIMetricsManager::mtHorizontalScrollbarHeight";
		metricsToStringMap[UIMetricsManager::mtMenuIndent] = "UIMetricsManager::mtMenuIndent";
		metricsToStringMap[UIMetricsManager::mtWindowBorderDelta] = "UIMetricsManager::mtWindowBorderDelta";
		metricsToStringMap[UIMetricsManager::mtContainerBorderDelta] = "UIMetricsManager::mtContainerBorderDelta";
		metricsToStringMap[UIMetricsManager::mtControlVerticalSpacing] = "UIMetricsManager::mtControlVerticalSpacing";
		metricsToStringMap[UIMetricsManager::mtControlHorizontalSpacing] = "UIMetricsManager::mtControlHorizontalSpacing";
		metricsToStringMap[UIMetricsManager::mtInformationControlTopSpacer] = "UIMetricsManager::mtInformationControlTopSpacer";
		metricsToStringMap[UIMetricsManager::mtInformationControlBottomSpacer] = "UIMetricsManager::mtInformationControlBottomSpacer";

		metricsToStringMap[UIMetricsManager::mtMenuSize] = "UIMetricsManager::mtMenuSize";
		metricsToStringMap[UIMetricsManager::mtVerticalSliderThumbSize] = "UIMetricsManager::mtVerticalSliderThumbSize";
		metricsToStringMap[UIMetricsManager::mtHorizontalSliderThumbSize] = "UIMetricsManager::mtHorizontalSliderThumbSize";
		metricsToStringMap[UIMetricsManager::mtTabSize] = "UIMetricsManager::mtTabSize";
		metricsToStringMap[UIMetricsManager::mtRadioBoxBtnSize] = "UIMetricsManager::mtRadioBoxBtnSize";
		metricsToStringMap[UIMetricsManager::mtCheckBoxBtnSize] = "UIMetricsManager::mtCheckBoxBtnSize";
		metricsToStringMap[UIMetricsManager::mtComboBoxDropBtnSize] = "UIMetricsManager::mtComboBoxDropBtnSize";
		metricsToStringMap[UIMetricsManager::mtDisclosureButtonSize] = "UIMetricsManager::mtDisclosureButtonSize";

		
	}
	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		Rect r = getClientBounds();

		r.inflate( -10, -10 );

		
		double height = 40;

		Rect metricsR = r;
		Rect textR = r;
		metricsR.right_ = metricsR.left_ + metricsR.getWidth()/2;
		metricsR.bottom_ = metricsR.top_ + height;

		textR.left_ = metricsR.right_;
		textR.bottom_ = metricsR.bottom_;

		Rect valRect;

		long options = GraphicsContext::tdoCenterHorzAlign | 
							GraphicsContext::tdoCenterVertAlign;

		double value = 0;
		Size size;

		double defWidth = minVal<>( metricsR.getWidth()-10.0, 100.0 );


		double totalVirtHeight  = 0;
		static bool setVirtHeight = true;

		for ( int i=UIMetricsManager::mtLabelHeight;i<UIMetricsManager::mtMenuSize;i++ ) {
			value = UIToolkit::getUIMetricValue( (UIMetricsManager::MetricType) i, "Test" );
			
			ctx->textBoundedBy( &textR, (Format("%s: %.2f pixels") % metricsToStringMap[i] % value), options );
			
			valRect.left_ = metricsR.left_ + (metricsR.getWidth()/2) - (defWidth/2);
			valRect.right_ = valRect.left_ + defWidth;
			valRect.top_ = metricsR.top_ + (metricsR.getHeight()/2) - (value/2);
			valRect.bottom_ = valRect.top_ + value;
			
			ctx->setColor( Color::getColor("black") );
			ctx->rectangle( &valRect );
			ctx->strokePath();
			
			totalVirtHeight += metricsR.getHeight() + 10;
			
			metricsR.offset( 0, metricsR.getHeight() + 10 );
			textR.offset( 0, textR.getHeight() + 10 );
		}


		for ( int ii=UIMetricsManager::mtMenuSize;ii<=UIMetricsManager::mtDisclosureButtonSize;ii++ ) {
			size = UIToolkit::getUIMetricSize( (UIMetricsManager::MetricType) ii, "Test" );
			
			metricsR.bottom_ = metricsR.top_ + maxVal<>( size.height_ + 10, metricsR.getHeight() );
			textR.bottom_  = metricsR.bottom_;

			ctx->textBoundedBy( &textR, (Format("%s: %.2f X %.2f pixels") % metricsToStringMap[ii] % size.width_ % size.height_), options );
			
			

			valRect.left_ = metricsR.left_ + (metricsR.getWidth()/2) - (size.width_/2);
			valRect.right_ = valRect.left_ + size.width_;
			valRect.top_ = metricsR.top_ + (metricsR.getHeight()/2) - (size.height_/2);
			valRect.bottom_ = valRect.top_ + size.height_;
			
			ctx->setColor( Color::getColor("black") );
			ctx->rectangle( &valRect );
			ctx->strokePath();
			
			totalVirtHeight += metricsR.getHeight() + 10;
			
			metricsR.offset( 0, metricsR.getHeight() + 10 );
			textR.offset( 0, textR.getHeight() + 10 );
		}
 
		if ( setVirtHeight ) {
			scrollBarMgr->setVirtualViewSize(  r.getWidth(), totalVirtHeight ); 
		}

		setVirtHeight = false;
	}
};	

class ThemesWindow : public Window {
public:
	ThemesWindow() {
		setCaption( "Themes" );	
		

		TabbedPages* pages = new TabbedPages();
		add( pages, AlignClient );

		pages->addNewPage( "System Colors" )->getPageComponent()->getContainer()->add( new SysColorsPanel(), AlignClient );

		pages->addNewPage( "Buttons" )->getPageComponent()->getContainer()->add( new ButtonsPanel(), AlignClient );

		pages->addNewPage( "Edges and Stuff" )->getPageComponent()->getContainer()->add( new EdgesPanel(), AlignClient );

		pages->addNewPage( "Tabs" )->getPageComponent()->getContainer()->add( new TabsPanel(), AlignClient );

		pages->addNewPage( "Sliders" )->getPageComponent()->getContainer()->add( new SlidersPanel(), AlignClient );

		pages->addNewPage( "Progress Bars" )->getPageComponent()->getContainer()->add( new ProgressPanel(), AlignClient );		

		pages->addNewPage( "Theme Metrics" )->getPageComponent()->getContainer()->add( new ThemeSizesPanel(), AlignClient );
	}

	virtual ~ThemesWindow(){
		
	};
};




class ThemesApplication : public Application {
public:

	ThemesApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new ThemesWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();

		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new ThemesApplication( argc, argv );

	Application::main();
	
	return 0;
}


