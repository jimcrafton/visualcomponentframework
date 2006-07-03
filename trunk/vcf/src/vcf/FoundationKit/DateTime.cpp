//DateTime.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/DateTime.h"


using namespace VCF;

#define TOSTRING_FORMAT		"%#d %b %Y %H:%M:%S.%s"

#if defined(VCF_GCC) || defined(VCF_BCC8)
	#define BASIC_GREGORIAN_TIME_IN_MS	198647424000000LL
#else
	#define BASIC_GREGORIAN_TIME_IN_MS	198647424000000
#endif




///////////////////////////////////////////////////////////////////////////////
// DateTime implementation

DateTime::DateTime( time_t newTime ):
	time_(0)
{
	tm gm = *localtime( &newTime );

	set( gm.tm_year + 1900, gm.tm_mon+1, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec );
}

DateTime::DateTime( uint32 year, uint32 month, uint32 day ):
	time_(0)
{
	set( year, month, day );
}

DateTime::DateTime( uint32 year, uint32 month, uint32 day,
				uint32 hour, uint32 minute, uint32 second )
{
	set( year, month, day, hour, minute, second );
}

bool DateTime::isGregorianCalendarDate( const DateTime& dt )
{
	bool result = false;

	uint64 gd = BASIC_GREGORIAN_TIME_IN_MS + (DateTime::ONEDAY-1);

	result = gd < dt.time_;

	return result;
}

bool DateTime::isGregorianCalendarDate( const uint32& year,
				const uint32& month,
				const uint32& day )
{
	/**
	this is the default determination. The correct determination of this
	is dependant on the country that the date is being considered for.
	For more info on the rules used for this, please see:
	http://www.tondering.dk/claus/cal/node3.html#SECTION00324000000000000000
	Final implementation of this will use either :
		the current Locale from the System
		or
		the Locale of the DateTime object, if it is not NULL
	*/
	bool result = false;
	if ( (year == 1582)  ) {
		if ( month == 10 ) {
			if ( day >= 5 ) {
				result = true;
			}
		}
		else if ( month > 10 ) {
			result = true;
		}
	}
	else if ( year > 1582 ) {
		result = true;
	}
	return result;
}

void DateTime::setDate( const uint32& year,
					const uint32& month,
					const uint32& day )
{
	uint32 h;
	uint32 m;
	uint32 s;
	uint32 ms;
	getHourMinuteSecond( *this, &h, &m, &s, &ms );

	set( year, month, day, h, m, s, ms ) ;
}

void DateTime::setTime( const uint32& hour,
					const uint32& minutes,
					const uint32& seconds )
{
	uint32 y;
	uint32 m;
	uint32 d;
	getYearMonthDay( *this, &y, &m, &d );

	uint32 ms = getMillisecond();

	set( y, m, d, hour, minutes, seconds, ms );
}

void DateTime::set( const uint32& year,
				const uint32& month,
				const uint32& day,
				const uint32& hour,
				const uint32& minutes,
				const uint32& seconds,
				const uint32& milliseconds )
{
	/**
	see
	http://www.tondering.dk/claus/cal/node3.html#SECTION003151000000000000000
	for julian day algorithm
	*/

	if ( (month > 12) || (month < 1) ) {
		throw BadDateFormat( BAD_MONTH_VALUE );
	}

	unsigned int maxDayVal = DateTime::getNumberOfDaysInMonth( year, (DateTime::Months)month );
	if ( (day > maxDayVal) || (day < 1) ) {
		throw BadDateFormat( BAD_DAY_VALUE );
	}

	if ( (hour > 59) || (hour < 0) ) {
		throw BadTimeFormat( BAD_HOUR_VALUE );
	}

	if ( (minutes > 59) || (minutes < 0) ) {
		throw BadTimeFormat( BAD_MIN_VALUE );
	}

	if ( (seconds > 59) || (seconds < 0) ) {
		throw BadTimeFormat( BAD_SEC_VALUE );
	}

	if ( (milliseconds > 999) || (milliseconds < 0) ) {
		throw BadTimeFormat( BAD_MILLISEC_VALUE );
	}


	time_ = 0;

	int a = (14 - month)/12;
	int y = year + 4800 - a;
	int m = month + (12 * a ) - 3;

	if ( isGregorianCalendarDate( year, month, day ) ) {
		//use formula for gregorian dates
		time_ = (day + ((153*m + 2)/5) + (365*y) + (y/4) - (y/100) + (y/400) - 32045);
		time_ = time_ * DateTime::ONEDAY;
		time_ += (hour*60*60*1000) + (minutes*60*1000) + (seconds*1000) + milliseconds;
	}
	else {
		//use formula for Julian Calendar dates
		time_ = (day + ((153*m + 2)/5) + (365*y) + (y/4) - 32083);
		time_ = time_ * DateTime::ONEDAY;
		time_ += (hour*60*60*1000) + (minutes*60*1000) + (seconds*1000) + milliseconds;
	}
}

DateTime DateTime::toLocal() const
{
	return System::convertUTCTimeToLocalTime( *this );
}

DateTime DateTime::toUTC() const
{
	return System::convertLocalTimeToUTCTime( *this );
}


void DateTime::getYearMonthDay( const DateTime& dt, uint32* year, uint32* month, uint32* day )
{
	//need to know if the date is gregorian or not
	bool gregorianDay = isGregorianCalendarDate( dt );

	int currentDay = dt.time_ / DateTime::ONEDAY;


	unsigned int a = currentDay + 32044;
	unsigned int b = 0;
	unsigned int c = 0;

	if ( gregorianDay ) {
		b = (4*a + 3)/146097;
		c = a - (b * 146097)/4;
	}
	else {
		c = currentDay + 32082;
	}

	int d = (4*c + 3)/1461;
	int e = c - (1461*d)/4;
	int m = (5*e + 2)/153;
	int tmp = 0;
	if ( NULL != year ) {
		tmp = (100 * b) + d - 4800 + m/10;
		*year = (tmp > 0) ? tmp : 0;
	}

	if ( NULL != month ) {
		tmp = m + 3 - (12 * (m/10));
		*month = tmp > 0 ? tmp : 0;
	}

	if ( NULL != day ) {
		tmp = e - ((153*m) + 2)/5 + 1;
		*day = tmp > 0 ? tmp : 0;
	}
}

void DateTime::getHourMinuteSecond( const DateTime& dt, uint32* hour, uint32* minute, uint32* second, uint32* millsecond/*=NULL*/ )
{
	if ( NULL != hour ) {
		*hour = ((dt.time_ % DateTime::ONEDAY) / DateTime::ONEHOUR );
	}

	if ( NULL != minute ) {
		*minute = ((dt.time_ % DateTime::ONEHOUR) / DateTime::ONEMINUTE );
	}

	if ( NULL != second ) {
		*second = ((dt.time_ % DateTime::ONEMINUTE) / DateTime::ONESECOND );
	}

	if ( NULL != millsecond ) {
		*millsecond = ((dt.time_ % DateTime::ONESECOND));
	}
}

uint32 DateTime::getYear() const
{
	uint32 result = 0;

	getYearMonthDay( *this, &result, NULL, NULL );

	return result;
}

uint32 DateTime::getMonth() const
{
	uint32 result = 0;

	getYearMonthDay( *this, NULL, &result, NULL );

	return result;
}

uint32 DateTime::getDay() const
{
	uint32 result = 0;

	getYearMonthDay( *this, NULL, NULL, &result );

	return result;
}

uint32 DateTime::getHour() const
{
	uint32 result = 0;

	result = ((time_ % DateTime::ONEDAY) / DateTime::ONEHOUR );

	return result;
}

uint32 DateTime::getMinute() const
{
	uint32 result = 0;

	result = ((time_ % DateTime::ONEHOUR) / DateTime::ONEMINUTE );

	return result;
}

uint32 DateTime::getSecond() const
{
	uint32 result = 0;

	result = ((time_ % DateTime::ONEMINUTE) / DateTime::ONESECOND );

	return result;
}

uint32 DateTime::getMillisecond() const
{
	uint32 result = 0;

	result = ((time_ % DateTime::ONESECOND));

	return result;
}


void DateTime::setCurrent( DateTime& dt )
{
	System::setDateToLocalTime( &dt );
}



DateTime& DateTime::incrYear(const uint32& by)
{
	DateTime::Iterator<ByYear> it = *this;

	it+=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::incrMonth(const uint32& by)
{

	DateTime::Iterator<ByMonth> it = *this;

	it+=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::incrDay(const uint32& by)
{
	DateTime::Iterator<ByDay> it = *this;

	it+=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::incrHour(const uint32& by)
{
	DateTime::Iterator<ByHour> it = *this;

	it+=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::incrMinute(const uint32& by)
{
	DateTime::Iterator<ByMinute> it = *this;

	it+=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::incrSecond(const uint32& by)
{
	DateTime::Iterator<BySecond> it = *this;

	it+=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::incrMilliSecond(const uint32& by)
{
	DateTime::Iterator<ByMillisecond> it = *this;

	it+=(by);

	*this = *it;
	return *this;
}


DateTime& DateTime::decrYear(const uint32& by)
{
	DateTime::Iterator<ByYear> it = *this;

	it-=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::decrMonth(const uint32& by)
{
	DateTime::Iterator<ByMonth> it = *this;

	it-=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::decrDay(const uint32& by)
{
	DateTime::Iterator<ByDay> it = *this;

	it-=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::decrHour(const uint32& by)
{
	DateTime::Iterator<ByHour> it = *this;

	it-=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::decrMinute(const uint32& by)
{
	DateTime::Iterator<ByMinute> it = *this;

	it-=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::decrSecond(const uint32& by)
{
	DateTime::Iterator<BySecond> it = *this;

	it-=(by);

	*this = *it;
	return *this;
}

DateTime& DateTime::decrMilliSecond(const uint32& by)
{
	DateTime::Iterator<ByMillisecond> it = *this;

	it-=(by);

	*this = *it;
	return *this;
}


void DateTime::setAndAdjustForGregorianDay( const uint32& year,
				const uint32& month,
				const uint32& day,
				const uint32& hour,
				const uint32& minutes,
				const uint32& seconds,
				const uint32& milliseconds )
{
	bool gregorianDate = DateTime::isGregorianCalendarDate( *this );

	set( year, month, day, hour, minutes, seconds, milliseconds );

	bool newGregorianDate = DateTime::isGregorianCalendarDate( *this );

	if ( gregorianDate != newGregorianDate ) {
		if ( !gregorianDate ) {
			set( getYear(), getMonth(), getDay()+10, getHour(), getMinute(), getSecond(), getMillisecond() );
		}
	}
}



DateTime::WeekDay DateTime::getWeekDay() const
{
	uint32 year = 0;
	uint32 month = 0;
	uint32 day = 0;

	getYearMonthDay( *this, &year, &month, &day );

	uint32 a = (uint32) floor( static_cast<float>( (14.0f - month) / 12.0f) );
	uint32 y = year -a ;
	uint32 m = month + (12 * a) - 2;

	uint32 d = (uint32) (day + y +
		floor(static_cast<float>(y / 4.0f)) -
		floor(static_cast<float>(y/100)) +
		floor(static_cast<float>(y/400)) +
		floor(static_cast<float>((31 * m)/12)));

	return (DateTime::WeekDay)(d % 7);
}

uint32 DateTime::getNumberOfDaysInMonth() const{

	uint32 year = 0;
	uint32 month = 0;

	getYearMonthDay( *this, &year, &month, NULL );



	return getNumberOfDaysInMonth( year, (DateTime::Months)month );
}

bool DateTime::isLeapYear( uint32 year )
{
	bool result = (year % 4) == 0;

	if ( result ) {
		if ( ((year % 100) == 0) && !((year % 400) == 0) ) {
			result = false;
		}
	}
	return result;
}

bool DateTime::isLeapYear() const
{
	return DateTime::isLeapYear( getYear() );
}

uint32 DateTime::getNumberOfDaysInMonth( uint32 year, DateTime::Months month )
{
	uint32 result = 0;

	switch( month ) {
		case DateTime::Feb : {

			result = DateTime::isLeapYear( year ) ? 29 : 28;
		}
		break;

		case DateTime::Apr : case DateTime::Jun : case DateTime::Sep : case DateTime::Nov : {
			result = 30;
		}
		break;

		case DateTime::Jan : case DateTime::Mar : case DateTime::May :
		case DateTime::Jul : case DateTime::Aug :  case DateTime::Oct : case DateTime::Dec : {
			result = 31;
		}
		break;
	}

	return result;
}


uint32 DateTime::getDayOfYear() const
{
	uint32 result = 0;

	DateTime startOfYear;
	startOfYear.set( getYear(), 1, 1, getHour(), getMinute(), getSecond(), getMillisecond() );

	uint64 diff = time_ - startOfYear.time_;
	//+1 is added so we get a 1 based result - otherwise it'd be zero based
	result = (diff / DateTime::ONEDAY) + 1;

	return result;
}

uint32 DateTime::getDaysInYear() const
{
	uint32 result = 365;
	
	if ( isGregorianCalendarDate( *this ) ) {
		if ( isLeapYear() ) {
			result ++;
		}
	}

	return result;
}

bool DateTime::operator> ( const DateTime& rhs ) const
{
	return time_ > rhs.time_;
}

bool DateTime::operator>= ( const DateTime& rhs ) const
{
	return time_ >= rhs.time_;
}

bool DateTime::operator< ( const DateTime& rhs ) const
{
	return time_ < rhs.time_;
}

bool DateTime::operator<= ( const DateTime& rhs ) const
{
	return time_ <= rhs.time_;
}

bool DateTime::operator== ( const DateTime& rhs ) const
{
	return time_ == rhs.time_;
}

bool DateTime::operator!= ( const DateTime& rhs ) const
{
	return time_ != rhs.time_;
}

DateTime& DateTime::operator =( const time_t& rhs )
{
	tm gm = *localtime( &rhs );

	set( gm.tm_year + 1900, gm.tm_mon+1, gm.tm_mday, gm.tm_hour, gm.tm_min, gm.tm_sec );

	return *this;
}

time_t DateTime::getCTime() const
{
	time_t result = 0;

	DateTime unixCtime( 1970, 1, 1 ) ;

	result = ((time_ - unixCtime.time_) / 1000);

	return result;
}

DateTime::DayTime DateTime::getDayTime() const
{
	DayTime result = DateTime::AM;
	result = getHour() >= 12 ? DateTime::PM : DateTime::AM;
	return result;
}

bool DateTime::isAM() const
{
	return getHour() < 12;
}

bool DateTime::isPM() const
{
	return getHour() >= 12;
}

bool DateTime::firstDayOfTheWeek() const
{
	return getWeekDay() == DateTime::Sun;
}

bool DateTime::lastDayOfTheWeek() const
{
	return getWeekDay() == DateTime::Sat;
}

bool DateTime::firstDayOfTheMonth() const
{
	return getDay() == 1;
}

bool DateTime::lastDayOfTheMonth() const
{
	return getDay() == getNumberOfDaysInMonth();
}

bool DateTime::firstDayOfTheYear() const
{
	return 1 == getDayOfYear();
}

bool DateTime::lastDayOfTheYear() const
{
	return getDayOfYear() == getDaysInYear();
}


DateTime DateTime::operator+( const DateTimeSpan& rhs ) const
{
	DateTime result = *this;

	result.time_ += rhs;

	return result;
}

DateTime DateTime::operator-( const DateTimeSpan& rhs ) const
{
	DateTime result = *this;

	result.time_ -= rhs;

	return result;
}

DateTimeSpan DateTime::operator-( const DateTime& rhs ) const
{
	DateTimeSpan result;

	if ( time_ > rhs.time_ ) {
		result.subtract( *this , rhs );
	}
	else {
		result.subtract( rhs, *this );
	}

	return result;
}

uint64 DateTime::getMilliseconds() const
{
	return time_;
}


void DateTime::setMilliseconds( const uint64& milliseconds )
{
	time_ = milliseconds;
}

uint32 DateTime::getWeekOfYearStartingMon() const
{
	//based on ISO 8601
	//code shamelessly swiped from http://www.merlyn.demon.co.uk/weekinfo.htm
	// J R Stockton, any problems are my fault
	uint32 result = 0;

	DateTime dt(*this);

	int day = dt.getWeekDay();
	if ( day == 0 ) {
		day = 7;
	}
	int month = dt.getMonth();

	int d = dt.getDay() + (4 - day);

	int maxDays = dt.getNumberOfDaysInMonth();

	if ( (d < 1) && (month==1) ) {
		//use week of prev year
		dt.decrYear();
		result = dt.getWeeksInYear();
	}
	else {
		dt.set( dt.getYear(), month, maxVal<>(1, minVal<>(maxDays,d)) ) ;//max( 1, dt.getDay() + 4 - day ) );

		result = (uint32) floor(static_cast<float>((dt.getDayOfYear()-1) / 7 )) + 1;
	}

	return result;
}

uint32 DateTime::getWeekOfYearStartingSun() const
{
	//based on ISO 8601
	//code shamelessly swiped from http://www.merlyn.demon.co.uk/weekinfo.htm
	// J R Stockton, any problems are my fault
	uint32 result = 0;

	DateTime dt(*this);

	int day = dt.getWeekDay() + 1;
	int month = dt.getMonth();

	int d = dt.getDay() + (4 - day);

	int maxDays = dt.getNumberOfDaysInMonth();

	if ( (d < 1) && (month==1) ) {
		//use week of prev year
		dt.decrYear();
		result = dt.getWeeksInYear();
	}
	else {
		dt.set( dt.getYear(), month, maxVal<>(1, minVal<>(maxDays,d)) ) ;//max( 1, dt.getDay() + 4 - day ) );

		result = (uint32) floor(static_cast<float>((dt.getDayOfYear()-1) / 7 )) + 1;
	}

	return result;
}

uint32 DateTime::getWeeksInYear() const
{
	return (uint32) floor(static_cast<float>(getDaysInYear() / 7) ) + 1;
}

String DateTime::toString()
{
	return StringUtils::format( *this, TOSTRING_FORMAT );
}

void DateTime::loadFromStream( InputStream* stream )
{
	int32 hi = 0;
	int32 lo = 0;

	stream->read( hi );
	stream->read( lo );

	time_ = makeULong64(hi,lo);
}

void DateTime::saveToStream( OutputStream* stream )
{
	int32 hi = getHi32(time_);
	int32 lo = (uint32)getLo32(time_);

	stream->write( hi );
	stream->write( lo );
}



void ByMillisecond::incr( DateTime& dt, uint32 offset )
{
	dt.setMilliseconds( dt.getMilliseconds() + offset );
}

void ByMillisecond::decr( DateTime& dt, uint32 offset )
{
	dt.setMilliseconds( dt.getMilliseconds() - offset );
}

void BySecond::incr( DateTime& dt, uint32 offset )
{
	dt.setMilliseconds( dt.getMilliseconds() + (offset * DateTime::ONESECOND) );
}

void BySecond::decr( DateTime& dt, uint32 offset )
{
	dt.setMilliseconds( dt.getMilliseconds() - (offset * DateTime::ONESECOND) );
}

void ByMinute::incr( DateTime& dt, uint32 offset )
{
	dt.setMilliseconds( dt.getMilliseconds() + (offset * DateTime::ONEMINUTE) );
}

void ByMinute::decr( DateTime& dt, uint32 offset )
{
	dt.setMilliseconds( dt.getMilliseconds() - (offset * DateTime::ONEMINUTE) );
}

void ByHour::incr( DateTime& dt, uint32 offset )
{
	dt.setMilliseconds( dt.getMilliseconds() + (offset * DateTime::ONEHOUR) );
}

void ByHour::decr( DateTime& dt, uint32 offset )
{
	dt.setMilliseconds( dt.getMilliseconds() - (offset * DateTime::ONEHOUR) );
}

void ByDay::incr( DateTime& dt, uint32 offset )
{
	uint64 offset64 = offset * DateTime::ONEDAY;
	dt.setMilliseconds( dt.getMilliseconds() + offset64 );
}

void ByDay::decr( DateTime& dt, uint32 offset )
{
	dt.setMilliseconds( dt.getMilliseconds() - (offset * DateTime::ONEDAY) );
}

void ByMonth::incr( DateTime& dt, uint32 offset )
{
	uint32 y = dt.getYear();
	uint32 m = dt.getMonth();
	uint32 d = dt.getDay();

	int origMaxDaysInMon = DateTime::getNumberOfDaysInMonth( y, (DateTime::Months)m );

	if ( (m + offset) > 12 ) {
		y += (m + offset) / 12;

		m = (m + offset) % 12;
	}
	else {
		m += offset;
	}

	int newMaxDaysInMon = DateTime::getNumberOfDaysInMonth( y, (DateTime::Months)m );

	if ( newMaxDaysInMon != origMaxDaysInMon ) {
		//check to see if we need to move the day around
		if ( d == origMaxDaysInMon ) {
			//last day of the month
			d = newMaxDaysInMon;
		}
		else if ( d > 28 ) {
			//make it smaller
			d = minVal<int>( d, newMaxDaysInMon );
		}
	}



	dt.set( y, m, d, dt.getHour(), dt.getMinute(), dt.getSecond(), dt.getMillisecond() );
}

void ByMonth::decr( DateTime& dt, uint32 offset )
{
	uint32 y = dt.getYear();
	uint32 m = dt.getMonth();
	uint32 d = dt.getDay();

	int origMaxDaysInMon = DateTime::getNumberOfDaysInMonth( y, (DateTime::Months)m );

	if ( (m - offset) < 1 ) {

		y -= ( abs((int32)static_cast<float>( m - offset ) ) / 12) + 1;

		m = 12 - ((m - offset) % 12);
	}
	else {
		m -= offset;
	}

	int newMaxDaysInMon = DateTime::getNumberOfDaysInMonth( y, (DateTime::Months)m );

	if ( newMaxDaysInMon != origMaxDaysInMon ) {
		//check to see if we need to move the day around
		if ( d == origMaxDaysInMon ) {
			//last day of the month
			d = newMaxDaysInMon;
		}
		else if ( d > 28 ) {
			//make it smaller
			d = minVal<int>( d, newMaxDaysInMon );
		}
	}

	dt.set( y, m, d, dt.getHour(), dt.getMinute(), dt.getSecond(), dt.getMillisecond() );
}

void ByYear::incr( DateTime& dt, uint32 offset )
{
	uint32 y = dt.getYear();
	uint32 m = dt.getMonth();
	uint32 d = dt.getDay();

	int origMaxDaysInMon = DateTime::getNumberOfDaysInMonth( y, (DateTime::Months)m );

	y += offset;

	int newMaxDaysInMon = DateTime::getNumberOfDaysInMonth( y, (DateTime::Months)m );

	if ( newMaxDaysInMon != origMaxDaysInMon ) {
		//check to see if we need to move the day around
		if ( d == origMaxDaysInMon ) {
			//last day of the month
			d = newMaxDaysInMon;
		}
		else if ( d > 28 ) {
			//make it smaller
			d = minVal<int>( d, newMaxDaysInMon );
		}
	}

	dt.set( y, m, d, dt.getHour(), dt.getMinute(), dt.getSecond(), dt.getMillisecond() );
}

void ByYear::decr( DateTime& dt, uint32 offset )
{
	uint32 y = dt.getYear();
	uint32 m = dt.getMonth();
	uint32 d = dt.getDay();

	int origMaxDaysInMon = DateTime::getNumberOfDaysInMonth( y, (DateTime::Months)m );

	y -= offset;

	int newMaxDaysInMon = DateTime::getNumberOfDaysInMonth( y, (DateTime::Months)m );

	if ( newMaxDaysInMon != origMaxDaysInMon ) {
		//check to see if we need to move the day around
		if ( d == origMaxDaysInMon ) {
			//last day of the month
			d = newMaxDaysInMon;
		}
		else if ( d > 28 ) {
			//make it smaller
			d = minVal<int>( d, newMaxDaysInMon );
		}
	}

	dt.set( y, m, d, dt.getHour(), dt.getMinute(), dt.getSecond(), dt.getMillisecond() );
}



///////////////////////////////////////////////////////////////////////////////
// DateTimeSpan implementation


void DateTimeSpan::subtract( const DateTime& lhs, const DateTime& rhs )
{
	start_ = rhs.time_;
	end_ = lhs.time_;
	delta_ = end_ - start_;

	DateTime::Iterator<ByMonth> monthIt = rhs;
	unsigned int ey = lhs.getYear();
	unsigned int em = lhs.getMonth();
	unsigned int sy = rhs.getYear();
	
	months_ = 0;
	while ( true ) {
		if ( (*monthIt).getYear() == ey ) {
			if ( (*monthIt).getMonth() == em ) {
				break;
			}
		}
		++months_;

		++monthIt;
	}

	years_ = abs(static_cast<int>(ey-sy));

	if ( years_ > 0 ) {
		if ( lhs > rhs ) {
			if ( lhs.getMonth() < rhs.getMonth() ) {
				years_ --;
			}
		}
		else {
			if ( rhs.getMonth() < lhs.getMonth() ) {
				years_ --;
			}
		}
	}

	days_ = delta_ / DateTime::ONEDAY;
}

uint32 DateTimeSpan::getYears() const
{
	return years_;
}

uint32 DateTimeSpan::getMonths() const
{
	return months_ % 12;
}

uint32 DateTimeSpan::getDays() const
{

	uint32 result = 0;


	DateTime end;
	end.time_ = end_;

	DateTime start;
	start.time_ = start_;

	result = abs((int32)static_cast<float>(end.getDay() - start.getDay()));

	return result;
}

uint32 DateTimeSpan::getHours() const
{
	DateTime dt;
	dt.time_ = delta_;

	return dt.getHour();
}

uint32 DateTimeSpan::getMinutes() const
{
	DateTime dt;
	dt.time_ = delta_;

	return dt.getMinute();
}

uint32 DateTimeSpan::getSeconds() const
{
	DateTime dt;
	dt.time_ = delta_;

	return dt.getSecond();
}

uint32 DateTimeSpan::getMilliseconds() const
{
	DateTime dt;
	dt.time_ = delta_;

	return dt.getMillisecond();
}

uint32 DateTimeSpan::getTotalMonths() const
{
	return months_;
}

uint32 DateTimeSpan::getTotalDays() const
{
	return days_;
}

uint32 DateTimeSpan::getTotalHours() const
{
	return delta_ / DateTime::ONEHOUR;
}

uint32 DateTimeSpan::getTotalMinutes() const
{
	return delta_ / DateTime::ONEMINUTE;
}

uint32 DateTimeSpan::getTotalSeconds() const
{
	return delta_ / DateTime::ONESECOND;
}

uint64 DateTimeSpan::getTotalMilliseconds() const
{
	return delta_;
}


/**
$Id$
*/
