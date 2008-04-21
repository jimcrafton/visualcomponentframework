//DateTimeUI.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/TitledBorder.h"


using namespace VCF;


class Calendar : public CustomControl {
public:


	Calendar() {

		EventHandler* ev = (EventHandler*) new ClassProcedure1<KeyboardEvent*,Calendar>( this, &Calendar::onUpArrow, "Calendar::onUpArrow" );

		Application::getRunningInstance()->addAcceleratorKey( vkUpArrow, 0, ev );

		Application::getRunningInstance()->addAcceleratorKey( vkUpArrow, kmCtrl, ev );

		Application::getRunningInstance()->addAcceleratorKey( vkUpArrow, kmCtrl | kmShift, ev );

		ev = (EventHandler*) new ClassProcedure1<KeyboardEvent*,Calendar>( this, &Calendar::onDownArrow, "Calendar::onDownArrow" );

		Application::getRunningInstance()->addAcceleratorKey( vkDownArrow, 0, ev );

		Application::getRunningInstance()->addAcceleratorKey( vkDownArrow, kmCtrl, ev );

		Application::getRunningInstance()->addAcceleratorKey( vkDownArrow, kmCtrl | kmShift, ev );

		ev = (EventHandler*) new ClassProcedure1<KeyboardEvent*,Calendar>( this, &Calendar::onSpaceBar, "Calendar::onSpaceBar" );

		Application::getRunningInstance()->addAcceleratorKey( vkSpaceBar, 0, ev );


		setUseColorForBackground( true );
		setColor( Color::getColor( "white" ) );

		current = DateTime::now();
	}


	virtual void paint( GraphicsContext* ctx ) {
		CustomControl::paint( ctx );

		DateTime currentMonthDate( current.getYear(), current.getMonth(), 1 );
		DateTime::Iterator<ByDay> dayIter = currentMonthDate;

		VCF::Rect rect = getClientBounds();

		ctx->setColor( Color::getColor("black") );
		ctx->rectangle( &rect );
		ctx->strokePath();

		VCF::Rect textRect = rect;

		textRect.bottom_ = 150;
		textRect.inflate( -5, -5 );

		String s = Format( "%ls. %ls")
					%	StringUtils::format( currentMonthDate, "The current month starts on %A, %B %d, %Y" ).c_str()
					%	StringUtils::format( current, "Today is %A, %B %d, %Y week %#W" ).c_str();

		String s2 = Format("\nThe current month has %d days in it, and the current year has %d days in it, starts on week %d,\nand has %d total weeks in the year\n")
									%	currentMonthDate.getNumberOfDaysInMonth()
									%	currentMonthDate.getDaysInYear()
									%	currentMonthDate.getWeekOfYearStartingMon()
									%	currentMonthDate.getWeeksInYear();

		s += s2;
		s += StringUtils::format( current, "The current time is %#I:%M:%S" );

		s += current.isAM() ? " AM" : " PM";

		s += "\n\nHit the space bar to update the current time.";
		s += "\nTo increment/decrement the Day use the up/down arrow keys with Ctrl+Shift held down.";
		s += "\nTo increment/decrement the Month use the up/down arrow keys with Ctrl held down.";
		s += "\nTo increment/decrement the Year use the up/down arrow keys.";

		ctx->textBoundedBy( &textRect, s );

		rect.top_ += textRect.bottom_ + 5;


		VCF::Size sizeBorder = VCF::Size( 5, 2 );
		VCF::Size sz;
		sz.width_  = ( rect.getWidth()  - 2 * sizeBorder.width_  ) / 7;
		sz.height_ = ( rect.getHeight() - 2 * sizeBorder.height_ ) / 7;


		int x,y;
		x = sizeBorder.width_;
		y = rect.top_ + sizeBorder.height_;
		VCF::Rect cellRect;


		for ( int i=0;i<7;i++ ) {
			for ( int j=0;j<7;j++) {
				ctx->setColor( Color::getColor("black") );
				cellRect.setRect( x, y, x + sz.width_, y + sz.height_ );
				ctx->rectangle( &cellRect );
				ctx->strokePath();

				if ( 0 == i ) {
					cellRect.inflate( -1, -1 );

					ctx->setColor( &Color(0.8,0.8,0.8) );
					ctx->rectangle( &cellRect );
					ctx->fillPath();

					switch ( j ) {
						case 0 : {
							ctx->textBoundedBy( &cellRect, "Sun" );
						}
						break;

						case 1 : {
							ctx->textBoundedBy( &cellRect, "Mon" );
						}
						break;

						case 2 : {
							ctx->textBoundedBy( &cellRect, "Tues" );
						}
						break;

						case 3 : {
							ctx->textBoundedBy( &cellRect, "Wed" );
						}
						break;

						case 4 : {
							ctx->textBoundedBy( &cellRect, "Thurs" );
						}
						break;

						case 5 : {
							ctx->textBoundedBy( &cellRect, "Fri" );
						}
						break;

						case 6 : {
							ctx->textBoundedBy( &cellRect, "Sat" );
						}
						break;

					}
				}
				else {
					cellRect.inflate( -3, -3 );
					DateTime dt = *dayIter;
					bool drawText = false;
					if ( 1 == i ) {
						if ( j >= dt.getWeekDay() ) {
							drawText = true;
						}
					}
					else if (dt.getMonth() == currentMonthDate.getMonth()) {
						drawText = true;
					}

					if ( drawText == true ) {
						if ( dt.getDayOfYear() == current.getDayOfYear() ) {
							ctx->setColor( &Color(1.0,0.8,0.0) );
							ctx->rectangle( &cellRect );
							ctx->fillPath();
						}
						ctx->textBoundedBy( &cellRect, StringUtils::format( dt, "%#d") );

						++dayIter;
					}

				}


				x += sz.width_;
			}
			y += sz.height_;
			x = sizeBorder.width_;
		}

	}



	void onUpArrow( KeyboardEvent* e ) {

		if ( e->hasShiftKey() && e->hasControlKey() ) {
			current.incrDay();
		}
		else if ( e->hasControlKey() ) {
			current.incrMonth();
		}
		else {
			current.incrYear();
		}

		repaint();
	}

	void onDownArrow( KeyboardEvent* e ) {

		if ( e->hasShiftKey() && e->hasControlKey() ) {
			current.decrDay();
		}
		else if ( e->hasControlKey() ) {
			current.decrMonth();
		}
		else {
			current.decrYear();
		}

		repaint();
	}

	void onSpaceBar( KeyboardEvent* e ) {

		current = DateTime::now();

		repaint();
	}

	DateTime current;
};



class DigitalClock : public CustomControl {
public:
	DigitalClock()	{

		current = DateTime::now();

		getFont()->setName( "Tahoma" );
		getFont()->setPointSize( 15 );
		getFont()->setBold( true );

		EventHandler* ev =
			new ClassProcedure1<Event*,DigitalClock>( this, &DigitalClock::onTimer, "DigitalClock::onTimer" );

		TimerComponent* timer = new TimerComponent();
		addComponent( timer );

		timer->TimerPulse += ev;

		timer->setTimeoutInterval( 1000 );
		timer->setActivated( true );

		TitledBorder* bdr = new TitledBorder();

		bdr->setCaption( "Digital Clock" );

		setBorder( bdr );
	}


	virtual void paint( GraphicsContext* ctx ) {

		CustomControl::paint( ctx );

		VCF::Rect rect = getClientBounds();

		rect.inflate( -5, -5 );
		ctx->setCurrentFont( getFont() );

		String s = StringUtils::format( current, "%#I:%M:%S");
		s += current.isAM() ? " AM" : " PM";

		int32 options = GraphicsContext::tdoCenterVertAlign | GraphicsContext::tdoCenterHorzAlign;
		ctx->textBoundedBy( &rect, s, options );

	}

	void onTimer( Event* e ) {
		current = DateTime::now();
		repaint();
	}

	DateTime current;
};


class AnalogClock : public CustomControl {
public:
	AnalogClock()	{

		current = DateTime::now();

		EventHandler* ev =
			new ClassProcedure1<Event*,AnalogClock>( this, &AnalogClock::onTimer, "AnalogClock::onTimer" );

		TimerComponent* timer = new TimerComponent();
		addComponent( timer );

		timer->TimerPulse += ev;

		timer->setTimeoutInterval( 1000 );
		timer->setActivated( true );

		TitledBorder* bdr = new TitledBorder();

		bdr->setCaption( "Analog Clock" );

		setBorder( bdr );
	}


	virtual void paint( GraphicsContext* ctx ) {
		CustomControl::paint( ctx );

		VCF::Rect rect = getClientBounds();

		rect.inflate( -5, -5 );

		VCF::Point center = rect.getCenter();
		double radius = minVal<>( rect.getHeight()/2.0, rect.getWidth()/2.0);

		ctx->setColor( Color::getColor("black") );
		ctx->circle( center, radius );
		ctx->strokePath();

		double tickLength = 5.0;

		for ( int i=0;i<12;i++ ) {
			 double theta = (i/12.0) * (2*M_PI);

			 double s = sin( theta );
			 double c = cos( theta );

			 ctx->moveTo( center.x_ + c*(radius-tickLength),
							center.y_ - s*(radius-tickLength) );
			 ctx->lineTo( center.x_ + c*radius,
							center.y_ - s*radius );
		}
		ctx->strokePath();

		tickLength = 2.5;

		for ( int j=0;j<60;j++ ) {
			 double theta = (j/60.0) * (2*M_PI);

			 double s = sin( theta );
			 double c = cos( theta );

			 ctx->moveTo( center.x_ + c*(radius-tickLength),
							center.y_ - s*(radius-tickLength) );
			 ctx->lineTo( center.x_ + c*radius,
							center.y_ - s*radius );
		}
		ctx->setColor( Color::getColor("gray128") );
		ctx->strokePath();

		ctx->setColor( Color::getColor("black") );

		double hourLength = radius * 0.40;
		double minLength = radius * 0.35;
		double secLength = radius * 0.05;

		double theta = (((current.getHour()%12))/12.0) * (2*M_PI);
		double c = sin( theta );
		double s = cos( theta );

		ctx->setColor( Color::getColor("midnightblue") );
		ctx->setStrokeWidth( 2 );
		ctx->moveTo( center );
		ctx->lineTo( center.x_ + c*(radius-hourLength),
							center.y_ - s*(radius-hourLength) );

		ctx->strokePath();


		theta = (current.getMinute()/60.0) * (2*M_PI);
		c = sin( theta );
		s = cos( theta );

		ctx->setColor( Color::getColor("red") );
		ctx->setStrokeWidth( 1 );
		ctx->moveTo( center );
		ctx->lineTo( center.x_ + c*(radius-minLength),
							center.y_ - s*(radius-minLength) );

		ctx->strokePath();

		theta = (current.getSecond()/60.0) * (2*M_PI);
		c = sin( theta );
		s = cos( theta );

		ctx->setColor( Color::getColor("forestgreen") );

		ctx->moveTo( center );
		ctx->lineTo( center.x_ + c*(radius-secLength),
							center.y_ - s*(radius-secLength) );

		ctx->strokePath();


		ctx->setStrokeWidth( 1 );

	}

	void onTimer( Event* e ) {
		current = DateTime::now();
		repaint();
		String s = StringUtils::format( current, "%#I:%M:%S");
		s += current.isAM() ? " AM" : " PM";

		setToolTipText( s );
	}

	DateTime current;
};


class DateTimeUIWindow : public Window {
public:
	DateTimeUIWindow() {
		setCaption( "DateTimeUI" );


		Panel* panel = new Panel();
		panel->setHeight( 250 );
		panel->setBorderSize( 5 );
		add( panel, AlignTop );

		DigitalClock* clock1 = new DigitalClock();
		panel->add( clock1, AlignClient );

		AnalogClock* clock2 = new AnalogClock();
		clock2->setWidth( 200 );
		panel->add( clock2, AlignLeft );

		Calendar* calendar = new Calendar();
		add( calendar, AlignClient );
	}

	virtual ~DateTimeUIWindow(){};

};




class DateTimeUIApplication : public Application {
public:

	DateTimeUIApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new DateTimeUIWindow();
		setMainWindow(mainWindow);
        mainWindow->setBounds( 100.0, 100.0, 500, 600 );
        mainWindow->show();

		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new DateTimeUIApplication( argc, argv );

	Application::main();

	return 0;
}


/**
$Id$
*/
