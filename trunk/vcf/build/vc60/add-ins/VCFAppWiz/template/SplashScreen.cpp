//SplashScreen.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "SplashScreen.h"


using namespace VCF;



SplashScreen::SplashScreen()
{
	setTop( 400 );
	setLeft( 300 );

	m_splashImage = Application::getRunningInstance()->getResourceBundle()->getImage( "SPLASH" );
	if ( NULL != m_splashImage ) {
		setHeight( m_splashImage->getHeight() );
		setWidth( m_splashImage->getWidth() );
	}
	else {
		setWidth( 250 );
		setHeight( 300 );
	}

	setVisible( true );	

	setFrameStyle( fstNoBorderFixed );
	setFrameTopmost( true );
	setColor( Color::getColor( "white" ) );


	TimerComponent* tc = new TimerComponent();
	addComponent( tc );

	tc->setTimeoutInterval( 1000 ); //set timeout interval in milliseconds

	tc->TimerPulse += new GenericEventHandler<SplashScreen>( this, &SplashScreen::onTimer, "SplashScreen::onTimer" );

	tc->setActivated( true );

	m_splashText = "Welcome to the $$Root$$...";
}


SplashScreen::~SplashScreen()
{
	if ( NULL != m_splashImage ) {
		delete m_splashImage;
		m_splashImage = NULL;
	}
}

void SplashScreen::onTimer( Event* e )
{
	static int count = 0;
	count ++;
	repaint();
	if ( count >= 6 ) {
		close();
	}
}


void SplashScreen::paint( GraphicsContext* context )
{
	Window::paint( context );
	Rect bounds(0,0,getWidth(), getHeight() );
	context->rectangle( &bounds );
	context->fillPath();

	if ( NULL != m_splashImage ) {
		context->drawImage( 0, 0, m_splashImage );
	}
	
	double w = context->getTextWidth( m_splashText );
	context->textAt( bounds.getWidth()/2-(w/2.0), bounds.getHeight()/2.0, m_splashText );
}

void SplashScreen::onTimer( Event* e )
{
	static int count = 0;
	count ++;

	if ( count <= 5 ) {
		m_splashText += ", going";
	}
	else {
		m_splashText += "...Gone!";
	}

	repaint();
	if ( count >= 6 ) {
		close();
	}
}

