////DatesAndTime.cpp

#include "FoundationKit.h"

/**
include the DateTime header - this must come *after* your include 
of the FoundationKit.
*/
#include "utils/DateTime.h"


using namespace VCF;

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	/**
	retrieve the current time
	*/
	DateTime currentTime = DateTime::now();

	/**
	Output the date time instance using the Object::toString method
	*/

	System::println( "currentTime: %s", currentTime.toString().c_str() );


	/**
	Modify the date
	*/

	currentTime.setDate( 2012, 11, 23 );

	/**
	Output the date time instance using the StringUtils::format() method
	*/
	System::println( "currentTime from StringUtils::format():\n\t%s",
					StringUtils::format( currentTime, "Day %#j in the year %Y, week %#U, %A day %#d of %B month %#m" ).c_str() );

	/**
	Output the time portion of the date time instance using the StringUtils::format() method
	*/
	System::println( "currentTime from StringUtils::format():\n\t%s",
					StringUtils::format( currentTime, "%H:%M:%S.%s" ).c_str() );

	/**
	Modify the time, hours, minutes and seconds
	*/
	currentTime.setTime( 9, 45, 12 );
	System::println( "currentTime from StringUtils::format():\n\t%s",
					StringUtils::format( currentTime, "%H:%M:%S.%s" ).c_str() );


	/**
	Modify the date and time in one call - this allows for milliseconds resolutions
	*/
	currentTime.set( 1982, 5, 21, 18, 23, 10, 456 );

	System::println( "currentTime from StringUtils::format():\n\t%s",
					StringUtils::format( currentTime, "%Y/%m/%d-%H:%M:%S.%s" ).c_str() );


	/**
	Demonstrate what happens when setting the date/time with bad data
	*/
	try {
		currentTime.setDate( 2003, 45, 12 );
	}
	catch ( std::exception& e ) {
		System::println( "Setting the date/time failed due to : %s", e.what() );
	}

	try {
		currentTime.setTime( 2003, 45, 12 );
	}
	catch ( std::exception& e ) {
		System::println( "Setting the date/time failed due to : %s", e.what() );
	}

	DateTime dt1(2003,12,23);
	DateTime dt2(2003,12,23);

	/**
	Compare a date
	*/

	if ( dt1 == dt2 ) {
		System::println( "Date {%s} equals date {%s}",
							dt1.toString().c_str(), dt2.toString().c_str() );
	}

	/**
	increment the dates value
	*/
	dt2.incrHour( 10 );

	if ( dt1 < dt2 ) {
		System::println( "Date {%s} is earlier than date {%s}",
							dt1.toString().c_str(), dt2.toString().c_str() );
	}

	/**
	decrement the dates value
	*/
	dt2.decrYear( 10 );

	if ( dt1 > dt2 ) {
		System::println( "Date {%s} is after than date {%s}",
							dt1.toString().c_str(), dt2.toString().c_str() );
	}


	/**
	Iterate dates given a starting point
	*/
	DateTime xmas2002(2002, 12, 25);
	DateTime::Iterator<ByYear> iterator = xmas2002;
	while ( *iterator != DateTime(2012, 12, 25) ) {
		System::println( StringUtils::format( *iterator, "Christmas is on a %A in %Y" ) );
		iterator ++;
	}

	DateTime dt3(1998, 8, 1, 16, 30, 0 );
	DateTime dt4 = DateTime::now();

	DateTimeSpan howLong = dt3 - dt4;

	System::println( "Holy cow! I've been married for: \n\t%d years, %d months, %d days, %d hours, and %d minutes,\n or for a total of: \n\t %s seconds!",
						howLong.getYears(),
						howLong.getMonths(),
						howLong.getDays(),
						howLong.getHours(),
						howLong.getMinutes(),
						System::getCurrentThreadLocale()->toString( howLong.getTotalSeconds() ).ansi_c_str() );


	/**
	The following demonstrates how to save a date to a output stream
	and how to read it back in from an input stream. These
	show how to read/write the date time as an object, obviously
	there are alternate ways of store it.
	*/

	DateTime storeMe( 1977, 10, 3, 19, 23, 12 );

	
	{
		FileOutputStream fs( "datetime.out" );

		fs << &storeMe;

		System::println( "storeMe (%s) saved!", storeMe.toString().c_str() );
	}

	DateTime loadMe;
	System::println( "loadMe is equal to %s", loadMe.toString().c_str() );
	{
		FileInputStream fs( "datetime.out" );

		fs >> &loadMe;

		System::println( "loadMe (%s) loaded!", loadMe.toString().c_str() );
	}


	FoundationKit::terminate();
	return 0;
}


