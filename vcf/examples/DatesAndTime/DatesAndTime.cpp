//DatesAndTime.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

/**
include the DateTime header - this must come *after* your include
of the FoundationKit.
*/
#include "vcf/FoundationKit/DateTime.h"



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

    String timeStr = currentTime.toString();
	System::println( Format("currentTime: %ls") % timeStr.c_str() );


	/**
	Modify the date
	*/

	currentTime.setDate( 2012, 11, 23 );

	/**
	Output the date time instance using the StringUtils::format() method
	*/

	System::println( Format("currentTime from StringUtils::format():\n\t%ls")
					% StringUtils::format( currentTime, "Day %#j in the year %Y, week %#U, %A day %#d of %B month %#m" ).c_str() );

	/**
	Output the time portion of the date time instance using the StringUtils::format() method
	*/

	System::println( Format("currentTime from StringUtils::format():\n\t%ls")
					% StringUtils::format( currentTime, "%H:%M:%S.%s" ).c_str() );

	/**
	Modify the time, hours, minutes and seconds
	*/
	currentTime.setTime( 9, 45, 12 );

	System::println( Format("currentTime from StringUtils::format():\n\t%ls")
					% StringUtils::format( currentTime, "%H:%M:%S.%s" ).c_str() );


	/**
	Modify the date and time in one call - this allows for milliseconds resolutions
	*/
	currentTime.set( 1982, 5, 21, 18, 23, 10, 456 );

	System::println( Format("currentTime from StringUtils::format():\n\t%ls")
					% StringUtils::format( currentTime, "%Y/%m/%d-%H:%M:%S.%s" ).c_str() );


	/**
	Demonstrate what happens when setting the date/time with bad data
	*/
	try {
		currentTime.setDate( 2003, 45, 12 );
	}
	catch ( std::exception& e ) {
		System::println( Format("Setting the date/time failed due to : %s") % e.what() );
	}

	try {
		currentTime.setTime( 2003, 45, 12 );
	}
	catch ( std::exception& e ) {
		System::println( Format("Setting the date/time failed due to : %s") % e.what() );
	}

	DateTime dt1(2003,12,23);
	DateTime dt2(2003,12,23);

	/**
	Compare a date
	*/

	if ( dt1 == dt2 ) {
		System::println( Format("Date {%ls} equals date {%ls}")
						% dt1.toString().c_str() % dt2.toString().c_str() );
	}

	/**
	increment the dates value
	*/
	dt2.incrHour( 10 );

	if ( dt1 < dt2 ) {
		System::println( Format("Date {%ls} is earlier than date {%ls}")
						% dt1.toString().c_str() % dt2.toString().c_str() );
	}

	/**
	decrement the dates value
	*/
	dt2.decrYear( 10 );

	if ( dt1 > dt2 ) {
		System::println( Format("Date {%ls} is later than date {%ls}")
						% dt1.toString().c_str() % dt2.toString().c_str() );
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


	System::println( Format("Holy cow! I've been married for: \n\t%d years, %d months, %d days, %d hours, and %d minutes,\n or for a total of: \n\t %s seconds!")
					%	howLong.getYears()
					%	howLong.getMonths()
					%	howLong.getDays()
					%	howLong.getHours()
					%	howLong.getMinutes()
                    %	System::getCurrentThreadLocale()->toString( howLong.getTotalSeconds() ) );


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

		System::println( Format("storeMe (%ls) saved!")%  storeMe.toString().c_str() );
	}

	DateTime loadMe;
	System::println( Format("loadMe is equal to %s") % loadMe.toString() );

	{
		FileInputStream fs( "datetime.out" );

		fs >> static_cast<VCF::Persistable*>(&loadMe);

		System::println( Format("loadMe (%s) loaded!") % loadMe.toString() );
	}


	FoundationKit::terminate();
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:34:21  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/03/19 00:03:39  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.5.2.1  2005/07/23 21:45:34  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.5  2005/07/09 23:14:35  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.4.2.1  2005/04/17 15:11:42  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.4.2.4  2005/07/14 03:45:15  marcelloptr
*fixed all deprecated traceWithArgs(...) and format(...) calls
*
*Revision 1.4.2.1  2005/04/17 15:11:42  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.4  2004/12/01 04:15:01  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3.2.1  2004/10/07 13:15:27  kiklop74
*Fixed building issues with bcb
*
*Revision 1.3  2004/08/07 02:46:58  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.2.7  2004/07/09 03:39:28  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.2.2.6.2.1  2004/06/27 18:19:14  ddiego
*more osx updates
*
*Revision 1.2.2.6  2004/05/15 17:59:36  marcelloptr
*minor project changes
*
*Revision 1.2.2.5  2004/05/03 03:44:52  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.2.2.4  2004/04/29 03:40:52  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


