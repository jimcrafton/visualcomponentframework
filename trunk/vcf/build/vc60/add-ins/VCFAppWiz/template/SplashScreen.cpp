//SplashScreen.h
#include "ApplicationKit.h"
#include "SplashScreen.h"
#include "Color.h"

using namespace VCF;



SplashScreen::SplashScreen()
{
	setVisible( true );
	setTop( 400 );
	setLeft( 300 );
	setHeight( 250 );
	setHeight( 300 );

	setFrameStyle( FST_NOBORDER_FIXED );
	setFrameTopmost( true );
	setColor( Color::getColor( "white" ) );
	m_thread = new ThreadLooper( this );
	m_thread->start();
}


SplashScreen::~SplashScreen()
{
	
}


void SplashScreen::paint( GraphicsContext* context )
{
	Window::paint( context );
	Rect bounds(0,0,getWidth(), getHeight() );
	context->rectangle( &bounds );
	context->fillPath();
	context->drawString( bounds.getWidth()/2-50, bounds.getHeight()/2.0, "Welcome to the $$Root$$..." );
}

static int sleepCount = 0;

bool SplashScreen::run()
{	
	repaint();
	m_thread->sleep( 500 );
	sleepCount ++;
	if ( sleepCount == 6 ) {
		setVisible( false );
		close();
		delete this;
		return false;
	}
	
	return true;
}


