#ifndef _VCF_DATETIME_H__
#define _VCF_DATETIME_H__
//DateTime.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/FoundationKit/VCFulong64.h"



namespace VCF {


class InputStream;
class OutputStream;

/**
This exception is thrown when a bad date format is used. An example
of an invalid date might be Jan 32, 2003.
*/
class FOUNDATIONKIT_API BadDateFormat : public std::exception {
public:
	BadDateFormat( const String& err ):err_(err) {

	}

	virtual ~BadDateFormat() throw() {} ;

	virtual const char* what() const throw() {
		return err_.ansi_c_str();
	}

protected:
	String err_;
};


/**
This exception is thrown when a bad time format is used. An example
of an invalid time might be 26:65:03.
*/
class FOUNDATIONKIT_API BadTimeFormat : public std::exception {
public:
	BadTimeFormat( const String& err ):err_(err) {

	}

	virtual ~BadTimeFormat() throw() {} ;

	virtual const char* what() const throw() {
		return err_.ansi_c_str();
	}

protected:
	String err_;
};


class DateTime;

/**
The DateTimeSpan represents an absolute delta value between two date time
values. You can get the individual components of the span by calling the various
getYears(), getMonths(), etc methods, or you can get the total amount of time
this span covers in a praticular format, such the total minutes, or the total
seconds. An example of this might look like so:
<pre>
DateTime dt1(2003,2,10); //2003, Feb 10th
DateTime dt2(2003,2,23); //2003, Feb 23rd
DateTimeSpan span = dt1 - dt2;
int totalHours = span.getTotalHours();//returns 312 (or 24 * 13)
int totalMinutes = span.getTotalMinutes(); //returns 18,720 (or 60 * 24 * 13)

int days = span.getDays(); //returns 13
int months = span.getMonths(); //returns 0
int minutes = span.getMinutes(); //returns 0
</pre>

*/
class FOUNDATIONKIT_API DateTimeSpan {
public:
	DateTimeSpan() :years_(0), months_(0), days_(0) {

	}

	DateTimeSpan( const DateTimeSpan& rhs ) {
		*this = rhs;
	}

	DateTimeSpan& operator= ( const DateTimeSpan& rhs ) {
		delta_ = rhs.delta_;
		start_ = rhs.start_;
		end_ = rhs.end_;
		years_ = rhs.years_;
		months_ = rhs.months_;
		days_ = rhs.days_;

		return *this;
	}


	operator ulong64() const {
		return delta_;
	}

	/**
	returns the number of years in this span of time
	*/
	unsigned long getYears() const ;

	/**
	returns the number of months in this span of time
	*/
	unsigned long getMonths() const ;

	/**
	returns the number of days in this span of time
	*/
	unsigned long getDays() const ;

	/**
	returns the number of hours in this span of time
	*/
	unsigned long getHours() const ;

	/**
	returns the number of minutes in this span of time
	*/
	unsigned long getMinutes() const ;

	/**
	returns the number of seconds in this span of time
	*/
	unsigned long getSeconds() const ;

	/**
	returns the number of milliseconds in this span of time
	*/
	unsigned long getMilliseconds() const ;


	/**
	returns the total number of whole months if this span of time
	is evaluated in months as the unit of measurement
	*/
	unsigned long getTotalMonths() const ;

	/**
	returns the total number of whole days if this span of time
	is evaluated in days as the unit of measurement
	*/
	unsigned long getTotalDays() const ;

	/**
	returns the total number of whole hours if this span of time
	is evaluated in hours as the unit of measurement
	*/
	unsigned long getTotalHours() const ;

	/**
	returns the total number of whole minutes if this span of time
	is evaluated in minutes as the unit of measurement
	*/
	unsigned long getTotalMinutes() const ;

	/**
	returns the total number of whole seconds if this span of time
	is evaluated in seconds as the unit of measurement
	*/
	unsigned long getTotalSeconds() const ;

	/**
	returns the total number of whole milliseconds if this span of time
	is evaluated in milliseconds as the unit of measurement
	*/
	ulong64 getTotalMilliseconds() const ;

	friend class DateTime;
protected:

	void subtract( const DateTime& lhs, const DateTime& rhs );

	DateTimeSpan& operator=( const ulong64& rhs ) {
		delta_ = rhs;
		return *this;
	}
	ulong64 delta_;

	ulong64 start_;
	ulong64 end_;
	unsigned long years_;
	unsigned long months_;
	unsigned long days_;
};




/**
<p>
This class is used to represent a point in time. The internal structure is a
64bit unsigned long that counts the number of milliseconds from ~ 4700BC. The
calendar used is the Gregorian calendar. There is logic to support switching
to the Julian calendar for days before the Gregorian switch. At the moment
there is no time zone support. This will be coming next.
</p>
<p>
There are a wide number of functions for retrieving all sorts of handy date/time
info, such as :
<ul>
<li>getting the Month enumeration
<li>getting the day of the week
<li>getting the day of the year
<li>getting the week of the year (starting on either Sun or Mon)
<li>getting the number of days in a year
<li>getting the number of weeks in a year
<li>getting the number of weeks in a year
<li>getting AM or PM
<li>getting the time as C time(i.e. positive number of seconds since Jan 1, 1970)
</ul>
There is iteration support in the form of the DateTime::Iterator class which allows
templatized iterator logic and lets you:
<ul>
  <li>incrementing or decrementing dates by a single unit in millisecond, second,
  minute, hour, day, month, or year resolution. This is done with the
  operator++ or operator --.
  <li>incrementing or decrementing dates by a 1 or more units in millisecond, second,
  minute, hour, day, month, or year resolution. This is done with the
  operator+=(n) or operator -=(n).
</ul>
Since the iterator template type is customizable, you can create your own iteration logic classes
to perform custom iteration logic.
</p>
<p>
You can modify the date time object in a variety of ways, by specifying the year, month, day, or
set the time specifying hour, minute, second, or have more control by setting all fields
(year, month, day, hour, minute, second, millisecond).
</p>
<p>
Most of the algorithms that this class uses come from: <br>
http://www.tondering.dk/claus/cal/

*/
class FOUNDATIONKIT_API DateTime : public Object, public Persistable {
public:

	enum {
		ONEDAY = 24 * 60 * 60 * 1000,
		ONEHOUR = 60*60*1000,
		ONEMINUTE = 60*1000,
		ONESECOND = 1000
	};

	enum Months {
		Jan = 1,
		Feb,
		Mar,
		Apr,
		May,
		Jun,
		Jul,
		Aug,
		Sep,
		Oct,
		Nov,
		Dec
	};

	enum WeekDay {
		Sun = 0,
		Mon,
		Tue,
		Wed,
		Thu,
		Fri,
		Sat
	};

	enum DayTime {
		AM = 0,
		PM
	};

	/**
	Constructs a blank/empty date time object
	*/
	DateTime():time_(0) {

	}

	/**
	Constructs a date time object from a C time <code>time_t</code> value.
	*/
	DateTime( time_t newTime );

	/**
	Constructs a date time object given a year, month, and a day.
	The time will be set to 00:00:00. If the month or day is an
	invalid value, a BadDateFormat exception will be thrown. Valid ranges for months
	are between 1 and 12. Valid ranges for days are between 1 and the maximum day for the
	specified month and year (i.e. for Feb 2004 the range would be 1-29, while Feb 2003
	the range would be 1-28).
	An example:
	<pre>
	DateTime bobs31stBirthday(2004,2,24); //valid date - February 24, 2004 00:00:00

	DateTime bobs32stBirthday(2005,14,24); //invalid date! BadDateFormat will be thrown
	</pre>
	@throw BadDateFormat
	*/
	DateTime( unsigned long year, unsigned long month, unsigned long day );

	/**
	Constructs a date time object given a year, month, day, hour, minute,
	and second. If the month or day is an invalid value, a
	BadDateFormat exception will be thrown. If the hour, minute,
	or second is invalid a BadTimeFormat exception will be thrown. The Valid range for
	the hour value is between 0 and 23, and valid ranges for minutes, or seconds
	are between 0 and 59.
	An example:
	<pre>
	DateTime bobs31stBirthday(2004,2,24,10,32,12); //valid date - February 24, 2004 10:32:12

	DateTime bobs32stBirthday(2005,2,24,60,32,12); //invalid date! BadTimeFormat will be thrown
	</pre>
	@throw BadDateFormat
	@throw BadTimeFormat
	*/
	DateTime( unsigned long year, unsigned long month, unsigned long day,
				unsigned long hour, unsigned long minute, unsigned long second );

	/**
	Static utility function to get the current local date on the computer
	the framework is running on. Resolution will be in milliseconds.
	*/
	static DateTime now() {
		DateTime result;
		DateTime::setCurrent( result );
		return result;
	}

	/**
	Returns a 64 bit unsigned integer that contains the total number
	of milliseconds in this object.
	*/
	ulong64 getMilliseconds() const;

	/**
	Sets the total number of milliseconds
	*/
	void setMilliseconds( const ulong64& milliseconds );

	/**
	Allows you to modify the date/time of this object.
	@param unsigned long the year

	@param unsigned long the month. This must be a value between 1 and 12. Values
	outside of this range will cause a BadDateFormat exception to be thrown.

	@param unsigned long the day. This must be a value between 1 and the maximum day
	for the specified month and year. Values
	outside of this range will cause a BadDateFormat exception to be thrown.

	@param unsigned long the hour. This must be a value between 0 and 59. Values
	outside of this range will cause a BadTimeFormat exception to be thrown.

	@param unsigned long the minutes. This must be a value between 0 and 59. Values
	outside of this range will cause a BadTimeFormat exception to be thrown.

	@param unsigned long the seconds. This must be a value between 0 and 59. Values
	outside of this range will cause a BadTimeFormat exception to be thrown.

	@param unsigned long the milliseconds. This must be a value between 0 and 999. Values
	outside of this range will cause a BadTimeFormat exception to be thrown.

	@throw BadDateFormat
    @throw BadTimeFormat
	*/
	void set( const unsigned long& year,
				const unsigned long& month,
				const unsigned long& day,
				const unsigned long& hour=0,
				const unsigned long& minutes=0,
				const unsigned long& seconds=0,
				const unsigned long& milliseconds=0 );

	/**
	Setting the date causes the current time to reset to 0:0:0.
	So if you have a DateTime object that is set to Jan 23, 2123 12:23:22, and
	you call setDate( 2003, 6, 12 ), the result will be a DateTime object set
	to June 12, 2003 00:00:00.

	@param unsigned long the year

	@param unsigned long the month. This must be a value between 1 and 12. Values
	outside of this range will cause a BadDateFormat exception to be thrown.

	@param unsigned long the day. This must be a value between 1 and the maximum day
	for the specified month and year. Values
	outside of this range will cause a BadDateFormat exception to be thrown.
	@throw BadDateFormat
	*/
	void setDate( const unsigned long& year,
					const unsigned long& month,
					const unsigned long& day );

	/**
	Setting the time via this function keeps the current date. So
	if you have a DateTime object that is set to Jan 23, 2123 12:23:22, and
	you call setTime( 16, 2, 45 ) , the result will be a DateTime object set
	to Jan 23, 2123 16:02:45.

	@param unsigned long the hour. This must be a value between 0 and 23. Values
	outside of this range will cause a BadTimeFormat exception to be thrown.

	@param unsigned long the minutes. This must be a value between 0 and 59. Values
	outside of this range will cause a BadTimeFormat exception to be thrown.

	@param unsigned long the seconds. This must be a value between 0 and 59. Values
	outside of this range will cause a BadTimeFormat exception to be thrown.

	@throw BadTimeFormat
	*/
	void setTime( const unsigned long& hour,
					const unsigned long& minutes,
					const unsigned long& seconds );

	/**
	Gets all the components of date/time.
	@param pointer to unsigned long accepting the year.
	@param pointer to unsigned long accepting the month.
	@param pointer to unsigned long accepting the day.
	@param pointer to unsigned long accepting the hour.
	@param pointer to unsigned long accepting the minute.
	@param pointer to unsigned long accepting the second.
	@param pointer to unsigned long accepting the millisecond.
	Any pointer that is NULL does not accept any value.
	*/
	void get( unsigned long* year, unsigned long* month, unsigned long* day, unsigned long* hour, unsigned long* minute, unsigned long* second, unsigned long* millsecond=NULL ) const;

	/**
	Gets all the components of the date.
	@param pointer to unsigned long accepting the year.
	@param pointer to unsigned long accepting the month.
	@param pointer to unsigned long accepting the day.
	Any pointer that is NULL does not accept any value.
	*/
	void getDate( unsigned long* year, unsigned long* month, unsigned long* day ) const;

	/**
	Gets all the components of the time.
	@param pointer to unsigned long accepting the minute.
	@param pointer to unsigned long accepting the second.
	@param pointer to unsigned long accepting the millisecond.
	Any pointer that is NULL does not accept any value.
	*/
	void getTime( unsigned long* hour, unsigned long* minute, unsigned long* second, unsigned long* millsecond=NULL ) const;

	/**
	Converts the time to the system's local time
	*/
	DateTime toLocal() const;

	/**
	Converts the time to UTC time
	*/
	DateTime toUTC() const;


	/**
	increments the year of this date object.
	@param unsigned long the amount to increment the year by
	*/
	DateTime& incrYear(const unsigned long& by=1);

	/**
	increments the month of this date object. This takes into
	account increments greater than 12 (which would then also increment the
	year).  It also treats the end of the month as follows: if the day of
	the object falls on the very last day of the month prior to the increment
	then the algorithm will "pin" the day, shortening or lengthening it depending
	on the newly incremented months value. For example, if the current date instance
	is set to Jan 31, 2003, and you increment the month by 1 unit, then the
	new value will be set to Feb 28, 2003.
	@param unsigned long the amount to increment the month by
	*/
	DateTime& incrMonth(const unsigned long& by=1);

	/**
	increments the day of this date object.
	@param unsigned long the amount to increment the day by
	*/
	DateTime& incrDay(const unsigned long& by=1);

	/**
	increments the hour of this date object.
	@param unsigned long the amount to increment the hour by
	*/
	DateTime& incrHour(const unsigned long& by=1);

	/**
	increments the minute of this date object.
	@param unsigned long the amount to increment the minute by
	*/
	DateTime& incrMinute(const unsigned long& by=1);

	/**
	increments the second of this date object.
	@param unsigned long the amount to increment the second by
	*/
	DateTime& incrSecond(const unsigned long& by=1);

	/**
	increments the millisecond of this date object.
	@param unsigned long the amount to increment the millisecond by
	*/
	DateTime& incrMilliSecond(const unsigned long& by=1);

	/**
	decrements the year of this date object
	@param unsigned long the amount to decrement the millisecond by
	*/
	DateTime& decrYear(const unsigned long& by=1);

	/**
	decrements the month of this date object. See the incrMonth()
	method for more details on the behaviour of this function.
	@param unsigned long the amount to decrement the month by
	@see incrMonth()
	*/
	DateTime& decrMonth(const unsigned long& by=1);

	/**
	decrements the day of this date object
	@param unsigned long the amount to decrement the day by
	*/
	DateTime& decrDay(const unsigned long& by=1);

	/**
	decrements the hour of this date object
	@param unsigned long the amount to decrement the hour by
	*/
	DateTime& decrHour(const unsigned long& by=1);

	/**
	decrements the minute of this date object
	@param unsigned long the amount to decrement the minute by
	*/
	DateTime& decrMinute(const unsigned long& by=1);

	/**
	decrements the second of this date object
	@param unsigned long the amount to decrement the second by
	*/
	DateTime& decrSecond(const unsigned long& by=1);

	/**
	decrements the millisecond of this date object
	@param unsigned long the amount to decrement the millisecond by
	*/
	DateTime& decrMilliSecond(const unsigned long& by=1);

	/**
	allows for assignment between this date time object and
	another.
	*/
	DateTime& operator =( const DateTime& rhs ) {
		time_ = rhs.time_;
		return *this;
	}

	/**
	Allows for assignment of C time values to this
	date time object. For example:
	<pre>
	time_t ctime = 0;
	time( &amp;ctime );

	DateTime dt;
	dt = ctime;
	</pre>
	*/
	DateTime& operator =( const time_t& rhs );

	/**
	Allows you to add a time span to the value of this date object
	and return the new date object
	*/
	DateTime operator+( const DateTimeSpan& rhs ) const;

	/**
	Allows you to subtract a time span from the value of this date object
	and return the new date object
	*/
	DateTime operator-( const DateTimeSpan& rhs ) const;

	/**
	Allows you to subtract one date time object from another and returns
	the date time span between them.
	*/
	DateTimeSpan operator-( const DateTime& rhs ) const;

	bool operator> ( const DateTime& rhs ) const ;
	bool operator>= ( const DateTime& rhs ) const ;
	bool operator< ( const DateTime& rhs ) const ;
	bool operator<= ( const DateTime& rhs ) const ;
	bool operator== ( const DateTime& rhs ) const ;
	bool operator!= ( const DateTime& rhs ) const ;


	/*
	Gets the day time value.
	@return DayTime either AM or PM
	*/
	DayTime getDayTime() const ;

	/**
	Is the current time in the AM or not.
	@return bool true if the current time is less than 12 hours
	*/
	bool isAM() const ;

	/**
	Is the current time in the PM or not.
	@return bool true if the current time is greater than or equal to 12 hours
	*/
	bool isPM() const ;

	bool firstDayOfTheWeek() const;
	bool lastDayOfTheWeek() const;

	bool firstDayOfTheMonth() const;
	bool lastDayOfTheMonth() const;

	bool firstDayOfTheYear() const;
	bool lastDayOfTheYear() const;

	bool isLeapYear() const ;

	time_t getCTime() const ;

	unsigned long getYear() const;
	unsigned long getMonth() const;
	unsigned long getDay() const;

	unsigned long getHour() const;
	unsigned long getMinute() const;
	unsigned long getSecond() const;
	unsigned long getMilliSecond() const;

	/*
	* Gets the day of the week. Sunday is 0, Monday is 1, and so on. 
	*/
	WeekDay getWeekDay() const ;

	unsigned long getDayOfYear() const ;

	unsigned long getDaysInYear() const ;

	unsigned long getNumberOfDaysInMonth() const ;

	unsigned long getWeekOfYearStartingSun() const ;
	unsigned long getWeekOfYearStartingMon() const ;

	unsigned long getWeeksInYear() const ;

	virtual void loadFromStream( InputStream* stream );

	virtual void saveToStream( OutputStream* stream );

	/**
	templatized class for iterating a date, either forward
	or backard in time, where the template type DateLogic
	is a class with the following static methods:
	<pre>
	class SomeDateLogic {
	public:
		static void incr( DateTime& dt, unsigned long offset );
		static void decr( DateTime& dt, unsigned long offset );
    };
	</pre>
	*/
	template <typename DateLogic>
	class Iterator 
	#ifdef VCF_BCC
	;
	#else	
	{
	public:

		Iterator()  {

		}

		Iterator( const DateTime& dt ) : dt_(dt){

		}

		Iterator& operator=( const DateTime& dt ) {
			dt_ = dt;
			return *this;
		}

		DateTime& operator* () {
			return dt_;
		}

		bool operator==( const Iterator& rhs ) const {
			return dt_ == rhs.dt_;
		}

		bool operator!=( const Iterator& rhs ) const {
			return dt_ != rhs.dt_;
		}

		Iterator& operator++() {
			DateLogic::incr( dt_, 1 );
			return *this;
		}

		Iterator& operator+=( const unsigned long& rhs ) {
			DateLogic::incr( dt_, rhs );

			return *this;
		}

		Iterator& operator--() {
			DateLogic::decr( dt_, 1 );
			return *this;
		}

		Iterator& operator-=( const unsigned long& rhs ) {
			DateLogic::decr( dt_, rhs );

			return *this;
		}
	protected:
		DateTime dt_;
	};
        #endif //VCF__BCC

	virtual String toString();

	static bool isLeapYear( unsigned long year );

	static unsigned long getNumberOfDaysInMonth( unsigned long year, Months month );

	static bool isGregorianCalendarDate( const unsigned long& year,
											const unsigned long& month,
											const unsigned long& day );

	static bool isGregorianCalendarDate( const DateTime& dt );

	static void getYearMonthDay( const DateTime& dt, unsigned long* year, unsigned long* month, unsigned long* day );

	static void getHourMinuteSecond( const DateTime& dt, unsigned long* hour, unsigned long* minute, unsigned long* second, unsigned long* millsecond=NULL );


	friend class DateTimeSpan;
protected:


	void setAndAdjustForGregorianDay( const unsigned long& year,
				const unsigned long& month,
				const unsigned long& day,
				const unsigned long& hour,
				const unsigned long& minutes,
				const unsigned long& seconds,
				const unsigned long& milliseconds );

	static void setCurrent( DateTime& dt );
	/**
	time is stored as the number of milliseconds since
	1 January 4713 BC. This is also known as the Julian Day
	used by astronomers
	*/
	ulong64 time_;
};

#ifdef VCF_BCC
	template <typename DateLogic>
	class DateTime::Iterator {
	public:

		Iterator()  {

		}

		Iterator( const DateTime& dt ) : dt_(dt){

		}

		Iterator& operator=( const DateTime& dt ) {
			dt_ = dt;
			return *this;
		}

		DateTime& operator* () {
			return dt_;
		}

		bool operator==( const Iterator& rhs ) const {
			return dt_ == rhs.dt_;
		}

		bool operator!=( const Iterator& rhs ) const {
			return dt_ != rhs.dt_;
		}

		Iterator& operator++() {
			DateLogic::incr( dt_, 1 );
			return *this;
		}

		Iterator& operator+=( const unsigned long& rhs ) {
			DateLogic::incr( dt_, rhs );

			return *this;
		}

		Iterator& operator--() {
			DateLogic::decr( dt_, 1 );
			return *this;
		}

		Iterator& operator-=( const unsigned long& rhs ) {
			DateLogic::decr( dt_, rhs );

			return *this;
		}
	protected:
		DateTime dt_;
	};
#endif

class FOUNDATIONKIT_API ByMillisecond {
public :
	static void incr( DateTime& dt, unsigned long offset );
	static void decr( DateTime& dt, unsigned long offset );
};

class FOUNDATIONKIT_API BySecond {
public :
	static void incr( DateTime& dt, unsigned long offset );
	static void decr( DateTime& dt, unsigned long offset );
};

class FOUNDATIONKIT_API ByMinute {
public :
	static void incr( DateTime& dt, unsigned long offset );
	static void decr( DateTime& dt, unsigned long offset );
};

class FOUNDATIONKIT_API ByHour {
public :
	static void incr( DateTime& dt, unsigned long offset );
	static void decr( DateTime& dt, unsigned long offset );
};

class FOUNDATIONKIT_API ByDay {
public :
	static void incr( DateTime& dt, unsigned long offset );
	static void decr( DateTime& dt, unsigned long offset );
};

class FOUNDATIONKIT_API ByMonth {
public :
	static void incr( DateTime& dt, unsigned long offset );
	static void decr( DateTime& dt, unsigned long offset );
};

class FOUNDATIONKIT_API ByYear {
public :
	static void incr( DateTime& dt, unsigned long offset );
	static void decr( DateTime& dt, unsigned long offset );
};



inline void DateTime::getDate( unsigned long* year, unsigned long* month, unsigned long* day ) const {
	getYearMonthDay( *this, year, month, day );
}

inline void DateTime::getTime( unsigned long* hour, unsigned long* minute, unsigned long* second, unsigned long* millsecond/*=NULL*/ ) const {
	getHourMinuteSecond( *this, hour, minute, second, millsecond );
}

inline void DateTime::get( unsigned long* year, unsigned long* month, unsigned long* day, unsigned long* hour, unsigned long* minute, unsigned long* second, unsigned long* millsecond/*=NULL*/ ) const {
	getYearMonthDay( *this, year, month, day );

	getHourMinuteSecond( *this, hour, minute, second, millsecond );
}



};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.9  2004/08/06 01:45:04  ddiego
*updated and added Marcellos DateTime changes.
*
*Revision 1.1.2.8  2004/08/03 20:57:22  marcelloptr
*minor change on name DateTime:getSecond DateTime:getMillisecond
*
*Revision 1.1.2.7  2004/07/30 17:28:40  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.6  2004/07/24 01:40:42  ddiego
*committed changes requested by Marcello. Got rid of the remaining
*date time members on the File class - now the dat time function call the
*FilePeer directly each time. Also added 2 functions to DateTime to convert
*directly to UTC or Local time.
*
*Revision 1.1.2.5  2004/07/13 16:16:23  marcelloptr
*added a comment
*
*Revision 1.1.2.4  2004/06/25 20:02:14  marcelloptr
*minor fix
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.2.2.3  2004/04/26 21:58:48  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2.2.2  2004/04/21 02:17:23  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.2.2.1  2004/04/06 17:19:15  ddiego
*minor header changes to better facilitate compiling with
*mingw. Also some minor changes to the devcpp FoundationKit project.
*
*Revision 1.2  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.1.2.3  2004/01/17 18:47:30  ddiego
*added a new example for DateTime calss and some other minor fixes to it
*
*Revision 1.1.2.2  2004/01/17 06:09:50  ddiego
*integrated the DateTime class into the VCF FoundationKit.
*
*/


#endif // _VCF_DATETIME_H__


