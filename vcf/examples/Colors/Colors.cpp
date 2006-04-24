//Colors.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"


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


class StandardColorsPanel : public Panel {
public:
	enum {
		NumColorColumns = 10
	};

	ScrollbarManager* scrollBarMgr;

	StandardColorsPanel() {
		setBorder( NULL );

		scrollBarMgr = new ScrollbarManager(this);
		scrollBarMgr->setTarget( this );
		scrollBarMgr->setHasHorizontalScrollbar( true );
		scrollBarMgr->setHasVerticalScrollbar( true );
		scrollBarMgr->setKeepScrollbarsVisible( true, true );
		
		ToolTipRequested += 
			new ToolTipEventHandler<StandardColorsPanel>(this,&StandardColorsPanel::onToolTipRequested, "StandardColorsPanel::onToolTipRequested" );

	}

	virtual void paint( GraphicsContext* ctx ) {
		Panel::paint( ctx );

		Rect r = getClientBounds();

		int cols = NumColorColumns;	
		int width = r.getWidth();
		Rect colorCell;
		colorCell.setRect( r.left_, r.top_, 
							r.left_ + (width/cols),
							r.top_ + (width/cols) );

		for (int i=ColorNames::uniqueColorFirst;i<=ColorNames::numUniqueColorNames;i++ ) {
			Color* color = Color::getColor( ColorNames::at( (ColorNames::ColorID) i ) );
			

			ctx->rectangle( &colorCell );
			ctx->setColor( color );
			ctx->fillPath();

			if ( ((i+1) % cols == 0) ) {
				colorCell.setRect( r.left_, colorCell.bottom_, 
							r.left_ + (width/cols),
							colorCell.bottom_ + (width/cols) );

				//colorCell.offset( 0, 5 );
			}
			else {
				colorCell.offset( colorCell.getWidth(), 0 );
			}

		}
	}

	virtual void sizeChange( ControlEvent* event ) {
		
		Rect r = getBounds();

		int cols = NumColorColumns;	
		int width = r.getWidth();
		Rect colorCell;
		colorCell.setRect( r.left_, r.top_, 
							r.left_ + (width/cols),
							r.top_ + (width/cols) );

		double totalVirtHeight  =  
			((ColorNames::numUniqueColorNames+2) / cols) *  colorCell.getHeight();

		scrollBarMgr->setVirtualViewSize(  colorCell.getWidth() * cols, totalVirtHeight ); 
		
	}

	void onToolTipRequested( ToolTipEvent* e ) {
		e->setToolTipString( "Unknown color" );
		Point pt = Desktop::getDesktop()->getCurrentMousePosition();
		
		translateFromScreenCoords( &pt );


		pt.x_ += scrollBarMgr->getHorizontalPosition();
		pt.y_ += scrollBarMgr->getVerticalPosition();

		Rect r = getClientBounds();

		int cols = NumColorColumns;	
		int width = r.getWidth();
		Rect colorCell;
		colorCell.setRect( r.left_, r.top_, 
							r.left_ + (width/cols),
							r.top_ + (width/cols) );

		for (int i=ColorNames::uniqueColorFirst;i<=ColorNames::numUniqueColorNames;i++ ) {
			

			if ( colorCell.containsPt( &pt ) ) {
				String colorName = ColorNames::at( (ColorNames::ColorID) i );
				Color* color = Color::getColor( colorName );
				int r = color->getRed() * 255.0;
				int g = color->getGreen() * 255.0;
				int b = color->getBlue() * 255.0;

				e->setToolTipString( Format("Color name: %s, #%02X%02X%02X") % 
										colorName % r % g % b ) ;
				break;
			}

			if ( ((i+1) % cols == 0) && (i > ColorNames::uniqueColorFirst) ) {
				colorCell.setRect( r.left_, colorCell.bottom_, 
							r.left_ + (width/cols),
							colorCell.bottom_ + (width/cols) );
			}
			else {
				colorCell.offset( colorCell.getWidth(), 0 );
			}

		}
	}
};



class SysColorsPanel : public Panel {
public:
	ScrollbarManager* scrollBarMgr;
	SysColorsPanel() {
		setBorder( NULL );
		scrollBarMgr = new ScrollbarManager(this);
		scrollBarMgr->setTarget( this );
		scrollBarMgr->setHasHorizontalScrollbar( true );
		scrollBarMgr->setHasVerticalScrollbar( true );
		scrollBarMgr->setKeepScrollbarsVisible( true, true );

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

	virtual void sizeChange( ControlEvent* event ) {
		
		Rect r = getBounds();

		int cols = 4;	
		int width = r.getWidth();
		Rect colorCell;
		colorCell.setRect( r.left_, r.top_, 
							r.left_ + (width/cols),
							r.top_ + (width/cols) );

		double totalVirtHeight  =  
			(20 / cols) *  (colorCell.getHeight() + 5);

		scrollBarMgr->setVirtualViewSize(  (colorCell.getWidth() + 5) * cols, totalVirtHeight ); 
		
	}
};


class RGBPanel : public Panel {
public:

	Panel* colorWell;
	Label* redVal;
	Label* greenVal;
	Label* blueVal;

	RGBPanel() {
		setBorder( NULL );

		HorizontalLayoutContainer* hc = new HorizontalLayoutContainer();	
		hc->setNumberOfColumns( 3 );
		hc->setColumnWidth( 0, 100 );
		hc->setColumnWidth( 1, 100 );
		hc->setColumnWidth( 2, 100 );

		hc->setColumnTweenWidth( 0, UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) );
		hc->setColumnTweenWidth( 1, UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) );


		setContainer( hc );

		colorWell = new Panel();
		colorWell->setUseColorForBackground(true);

		Label* label = new Label();
		label->setCaption( "Red:" );
		add( label );

		SliderControl* slider = new SliderControl();			
		slider->setPosition( colorWell->getColor()->getRed() * 100.0 );
		slider->PositionChanged +=
			new GenericEventHandler<RGBPanel>( this, &RGBPanel::onRedChanged, "RGBPanel::onRedChanged" );

		slider->setTickFrequency(0);
		add( slider );

		redVal = new Label();
		redVal->setCaption( "???" );
		add( redVal );


		label = new Label();
		label->setCaption( "Green:" );
		add( label );

		slider = new SliderControl();	
		slider->setPosition( colorWell->getColor()->getGreen() * 100.0 );
		slider->PositionChanged +=
			new GenericEventHandler<RGBPanel>( this, &RGBPanel::onGreenChanged, "RGBPanel::onGreenChanged" );
		slider->setTickFrequency(0);
		add( slider );

		greenVal = new Label();
		greenVal->setCaption( "???" );
		add( greenVal );


		label = new Label();
		label->setCaption( "Blue:" );
		add( label );

		slider = new SliderControl();	
		slider->setPosition( colorWell->getColor()->getBlue() * 100.0 );
		slider->PositionChanged +=
			new GenericEventHandler<RGBPanel>( this, &RGBPanel::onBlueChanged, "RGBPanel::onBlueChanged" );

		slider->setTickFrequency(0);
		add( slider );

		blueVal = new Label();
		blueVal->setCaption( "???" );
		add( blueVal );

		

		add( colorWell );
	}

	void onRedChanged( Event* e ) {
		Color color = *colorWell->getColor();

		SliderControl* slider = (SliderControl*)e->getSource();
		color.setRed( slider->getPosition() / 100.0 );

		colorWell->setColor( &color );

		redVal->setCaption( Format("%.3f (#%02X)") % color.getRed() %
								(uchar)(color.getRed() * 255.0) );
	}

	void onGreenChanged( Event* e ) {
		Color color = *colorWell->getColor();

		SliderControl* slider = (SliderControl*)e->getSource();
		color.setGreen( slider->getPosition() / 100.0 );

		colorWell->setColor( &color );

		greenVal->setCaption( Format("%.3f (#%02X)") % color.getGreen() %
								(uchar)(color.getGreen() * 255.0) );
	}

	void onBlueChanged( Event* e ) {
		Color color = *colorWell->getColor();

		SliderControl* slider = (SliderControl*)e->getSource();
		color.setBlue( slider->getPosition() / 100.0 );

		colorWell->setColor( &color );

		blueVal->setCaption( Format("%.3f (#%02X)") % color.getBlue() %
								(uchar)(color.getBlue() * 255.0) );
	}
};





class HSLPanel : public Panel {
public:

	Panel* colorWell;
	Label* hueVal;
	Label* saturationVal;
	Label* luminanceVal;
	double hue;
	double saturation;
	double luminance;

	HSLPanel() {
		setBorder( NULL );

		HorizontalLayoutContainer* hc = new HorizontalLayoutContainer();	
		hc->setNumberOfColumns( 3 );
		hc->setColumnWidth( 0, 100 );
		hc->setColumnWidth( 1, 100 );
		hc->setColumnWidth( 2, 100 );

		hc->setColumnTweenWidth( 0, UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) );
		hc->setColumnTweenWidth( 1, UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) );


		setContainer( hc );

		colorWell = new Panel();
		colorWell->setUseColorForBackground(true);

		Label* label = new Label();
		label->setCaption( "Hue:" );
		add( label );


		colorWell->getColor()->getHSL( hue,saturation,luminance );

		SliderControl* slider = new SliderControl();			
		slider->setPosition( hue * 100.0 );
		slider->PositionChanged +=
			new GenericEventHandler<HSLPanel>( this, &HSLPanel::onRedChanged, "HSLPanel::onRedChanged" );

		slider->setTickFrequency(0);
		add( slider );

		hueVal = new Label();
		hueVal->setCaption( "???" );
		add( hueVal );


		label = new Label();
		label->setCaption( "Saturation:" );
		add( label );

		slider = new SliderControl();	
		slider->setPosition( saturation * 100.0 );
		slider->setTickFrequency(0);
		slider->PositionChanged +=
			new GenericEventHandler<HSLPanel>( this, &HSLPanel::onGreenChanged, "HSLPanel::onGreenChanged" );
		add( slider );

		saturationVal = new Label();
		saturationVal->setCaption( "???" );
		add( saturationVal );


		label = new Label();
		label->setCaption( "Luminance:" );
		add( label );

		slider = new SliderControl();	
		slider->setPosition( luminance * 100.0 );
		slider->setTickFrequency(0);
		slider->PositionChanged +=
			new GenericEventHandler<HSLPanel>( this, &HSLPanel::onBlueChanged, "HSLPanel::onBlueChanged" );

		add( slider );

		luminanceVal = new Label();
		luminanceVal->setCaption( "???" );
		add( luminanceVal );

		

		add( colorWell );
	}

	void onRedChanged( Event* e ) {
		SliderControl* slider = (SliderControl*)e->getSource();
		hue = (slider->getPosition() / 100.0) * 6.0;

		Color color( hue,saturation,luminance, Color::ctHSV );		

		colorWell->setColor( &color );		

		hueVal->setCaption( Format("%.3f") % hue  );
	}

	void onGreenChanged( Event* e ) {
		SliderControl* slider = (SliderControl*)e->getSource();
		saturation = slider->getPosition() / 100.0;

		Color color( hue,saturation,luminance, Color::ctHSV );		

		colorWell->setColor( &color );		

		saturationVal->setCaption( Format("%.3f") % saturation  );
	}

	void onBlueChanged( Event* e ) {		
		SliderControl* slider = (SliderControl*)e->getSource();
		luminance = slider->getPosition() / 100.0;

		Color color( hue,saturation,luminance, Color::ctHSV );		

		colorWell->setColor( &color );		

		luminanceVal->setCaption( Format("%.3f") % luminance  );
	}
};


class ColorsApplication : public Application {
public:

	ColorsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new Window();

		mainWindow->setCaption( "Colors Example" );

		TabbedPages* tabs = new TabbedPages();

		tabs->addNewPage( "System Colors" )->getPageComponent()->getContainer()->add( new SysColorsPanel(), AlignClient );
		tabs->addNewPage( "Standard Colors" )->getPageComponent()->getContainer()->add( new StandardColorsPanel(), AlignClient );
		tabs->addNewPage( "RGB Colors" )->getPageComponent()->getContainer()->add( new RGBPanel(), AlignClient );
		tabs->addNewPage( "HSL Colors" )->getPageComponent()->getContainer()->add( new HSLPanel(), AlignClient );

		
		
		mainWindow->add( tabs, AlignClient );


		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();

		return result;
	}

};

int main(int argc, char *argv[])
{
	Application* app = new ColorsApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:34:16  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.4.3  2006/03/18 23:04:41  ddiego
*updated the colors example per fraggles request.
*
*Revision 1.2.4.2  2006/03/12 22:01:39  ddiego
*doc updates.
*
*Revision 1.2.4.1  2006/03/10 21:49:31  ddiego
*updates to color example and some documentation.
*
*Revision 1.2  2004/12/01 04:14:59  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.1  2004/08/27 22:27:50  marcelloptr
*added Colors example. It will be improved.
*
*/


