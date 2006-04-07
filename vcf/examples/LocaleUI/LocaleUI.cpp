//LocaleUI.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TitledBorder.h"

using namespace VCF;



class DateTimeLabel : public CustomControl {
protected:
	TimerComponent* timer;
	String extraTxt;
	Locale* locale;
	void onTimer( Event* e ) {
		repaint();
	}
public:
	DateTimeLabel() : CustomControl(false),locale(NULL){

		setBorder( new TitledBorder() );

		timer = new TimerComponent(this);
		timer->setTimeoutInterval ( 1000 );
		timer->TimerPulse += 
			new GenericEventHandler<DateTimeLabel>(this, &DateTimeLabel::onTimer, "DateTimeLabel::onTimer" );
	}

	virtual ~DateTimeLabel() {
		delete locale;
	}
	
	void setLocale( Locale* loc ) {
		if ( NULL != locale ) {
			delete locale;
		}

		locale = new Locale( loc->getLanguageCode(), loc->getCountryCode() );

		TitledBorder* border = (TitledBorder*)getBorder();
		border->setCaption( locale->getLanguageName() );
		border->getFont()->setLocale( locale );
	}

	void setLocale( const String& lang, const String& country ) {
		if ( NULL != locale ) {
			delete locale;
		}

		locale = new Locale( lang, country );

		TitledBorder* border = (TitledBorder*)getBorder();
		border->setCaption( locale->getLanguageName() );
		border->getFont()->setLocale( locale );
	}

	void start() {
		timer->setActivated ( true );
	}
	
	void stop() {
		timer->setActivated ( false );
	}
	
	void setExtraTxt( const String& val ) {
		extraTxt = val;
		repaint();
	}
	
	String getExtraTxt() {
		return extraTxt;
	}
	
	virtual void paint( GraphicsContext* ctx ) {
		CustomControl::paint( ctx );

		//get the current locale
		Locale* currentLocale = System::getCurrentThreadLocale();

		if ( NULL != locale ) {
			currentLocale = locale;
		}	


		
		String localizedExtra = extraTxt;

		ctx->getCurrentFont()->setName( "Times New Roman" );
		ctx->getCurrentFont()->setPointSize( 16 );

		
		
		
		//check if we can localize the string
		if ( getUseLocaleStrings() ) {
			//Yep! Let's get the localized version. Worst case scenario is that
			//no translation exists, which means localizedExtra will be the same
			//as extraTxt
			localizedExtra =   currentLocale->translate( extraTxt );
		}
		
		DateTime dt = DateTime::now();
		//localize the date/time value into a string
		String dateStr = currentLocale->toStringFromDate( dt, "dddd, MMM d yyyy" );
		String timeStr = currentLocale->toStringFromTime ( dt );
		
		Rect r = getClientBounds();
		
		Rect xtraRect = r;
		xtraRect.bottom_ = xtraRect.top_ + ctx->getTextHeight( localizedExtra );
		
		long textDrawOptions = GraphicsContext::tdoCenterHorzAlign;
		
		ctx->textBoundedBy( &xtraRect, localizedExtra, textDrawOptions );

		Rect textRect = r;

		textRect.inflate( -10, -10 );
		textRect.top_ = xtraRect.bottom_;

		
		ctx->getCurrentFont()->setBold( true );

		textDrawOptions = GraphicsContext::tdoWordWrap | GraphicsContext::tdoCenterHorzAlign;
		ctx->textBoundedBy( &textRect, dateStr + "\n" + timeStr, textDrawOptions );
	}
};

class LocaleUIWindow : public Window {
public:
	LocaleUIWindow() {
		setCaption( "LocaleUI" );
		
		DateTimeLabel* label;
		
		label = new DateTimeLabel();

		label->setLocale( "en", "US" );

		label->setExtraTxt( "Hello it's:" );

		label->setHeight( 100 );

		add( label, AlignTop );

		label->start();


		label = new DateTimeLabel();

		label->setLocale( "it", "IT" );

		label->setExtraTxt( "Hello it's:" );

		label->setHeight( 100 );

		add( label, AlignTop );

		label->start();


		label = new DateTimeLabel();

		label->setLocale( "pl", "PL" );

		label->setExtraTxt( "Hello it's:" );

		label->setHeight( 100 );

		add( label, AlignTop );

		label->start();


		label = new DateTimeLabel();

		label->setLocale( "de", "DE" );

		label->setExtraTxt( "Hello it's:" );

		label->setHeight( 100 );

		add( label, AlignTop );

		label->start();


		label = new DateTimeLabel();

		Locale loc( Locale::lcJapanese, Locale::ccJapan );
		label->setLocale( &loc );

		label->setExtraTxt( "Hello it's:" );

		label->setHeight( 100 );

		add( label, AlignTop );

		label->start();

		label = new DateTimeLabel();

		Locale loc2( Locale::lcRussian, Locale::ccRussianFederation );
		label->setLocale( &loc2 );

		label->setExtraTxt( "Hello it's:" );

		label->setHeight( 100 );

		add( label, AlignTop );

		label->start();
	}

	virtual ~LocaleUIWindow(){};

};




class LocaleUIApplication : public Application {
public:

	LocaleUIApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new LocaleUIWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 350.0, 620.0 );
		mainWindow->show();
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new LocaleUIApplication( argc, argv );

	Application::main();
	
	return 0;
}


