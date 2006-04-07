/** \file
  * Wrappers for DATE.
  */

/* Copyright � 2001 Michael Geddes
 *
 * This class was originally based on ATL/MFC code, however the original
 * implementations have almost entirely been replaced with more efficient code.
 * The core date algorithms are from boost.
 *
 * This material is provided "as is", with absolutely no warranty
 * expressed or implied. Any use is at your own risk. Permission to
 * use or copy this software for any purpose is hereby granted without
 * fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is
 * granted, provided the above notices are retained, and a notice that
 * the code was modified is included with the above copyright notice.
 *
 * This header is part of comet.
 * http://www.lambdasoft.dk/comet
 */
#ifndef COMET_DATETIME_H
#define COMET_DATETIME_H

#include <comet/error_fwd.h>
#include <comet/bstr.h>
#include <comet/auto_buffer.h>

#include <math.h>
#include <time.h>

// The Platform SDK does not define VAR_FOURDIGITYEARS
#ifndef VAR_FOURDIGITYEARS
#define VAR_FOURDIGITYEARS	((DWORD)0x00000040)
#endif

namespace comet
{

#define COMET_DIVMOD_( quot,rem, val1, val2) quot = (val1)/(val2); rem = (val1)%(val2);


/*! \addtogroup ErrorHandling
 */
//@{
//! Exception for datetimes.
class datetime_exception : public std::exception
{
public:
	datetime_exception( const char *desc) : desc_(desc)
	{}

	~datetime_exception() throw()
	{}

	const char* what() const throw()
	{
		return desc_.c_str();
	}

private:
	std::string desc_;
};

//@}

/*! \addtogroup COMType
 */
//@{
/// Initialise date/time value as invalid.
static struct dt_invalid_t {} dt_invalid;
/// Initialise date/time value as null.
static struct dt_null_t {} dt_null;
/// Initialise date/time value as zero.
static struct dt_zero_t {
	operator double() const { return 0.;}
	operator long() const { return 0;}
} dt_zero;

// timeperiod_t
/////////////////

/** \class timeperiod_t datetime.h comet/datetime.h
  * Time-period.  Used with datetime_t math.
  */
class timeperiod_t
{
	enum {
		dt_invalid_ = 2147483647L,
	};
	/// Days.
	double pd_;
	public:
		/// Default Constructor.
		timeperiod_t() : pd_(0.){}

		/// Construct invalid
		timeperiod_t( dt_invalid_t )  : pd_(dt_invalid_) {}
		/// Construct zero
		timeperiod_t( dt_zero_t) : pd_(0.) {}

		timeperiod_t( double period) :pd_(period){}
		timeperiod_t( float period) :pd_(period){}
		timeperiod_t( long period) :pd_(period){}
		timeperiod_t( int period) :pd_(period){}
		timeperiod_t( short period) :pd_(period){}
		timeperiod_t( unsigned long period) :pd_(period){}
		timeperiod_t( unsigned int period) :pd_(period){}
		timeperiod_t( unsigned short period) :pd_(period){}

		timeperiod_t( long days, long hours)
			: pd_(days + hours/24){}
		timeperiod_t( long days, long hours, long minutes)
			: pd_(days + (hours*60+minutes)/(24.*60.)){}
		timeperiod_t( long days, long hours, long minutes, long seconds, long milliseconds=0 )
			: pd_(days + ((hours*3600000L) + (minutes*60000L)+ (seconds*1000L)+ milliseconds)/86400000.){}

		/// \name Assignment operators
		//@{
		timeperiod_t &operator =( const double &period){pd_=period; return *this;}
		timeperiod_t &operator =( float period){pd_=period; return *this;}
		timeperiod_t &operator =( long period){pd_=period; return *this;}
		timeperiod_t &operator =( int period){pd_=period; return *this;}
		timeperiod_t &operator =( short period){pd_=period; return *this;}
		//@}

		/// Return time-period as a double (days).
		operator double() const{return pd_;}

		/// \name Comparison operators.
		//@{
		bool operator ==(const timeperiod_t &prd) const { return pd_ == prd.pd_; }
		bool operator !=(const timeperiod_t &prd) const { return pd_ != prd.pd_; }
		bool operator < (const timeperiod_t &prd) const { return pd_ <  prd.pd_; }
		bool operator > (const timeperiod_t &prd) const { return pd_ >  prd.pd_; }
		bool operator <=(const timeperiod_t &prd) const { return pd_ <= prd.pd_; }
		bool operator >=(const timeperiod_t &prd) const { return pd_ >= prd.pd_; }
		bool operator ==(dt_invalid_t) const { return pd_ == dt_invalid_; }
		bool operator !=(dt_invalid_t) const { return pd_ != dt_invalid_; }

		// These shouldn't be needed.
		template<typename T> bool operator < (T prd) const { return pd_ < double(prd); }
		template<typename T> bool operator <= (T prd) const { return pd_ <= double(prd); }
		template<typename T> bool operator > (T prd) const { return pd_ > double(prd); }
		template<typename T> bool operator >= (T prd) const { return pd_ >= double(prd); }
		template<typename T> bool operator == (T prd) const { return pd_ == double(prd); }
		template<typename T> bool operator != (T prd) const { return pd_ != double(prd); }

		//@}
		/// \name Simple math operators.
		//@{
		timeperiod_t operator+(const timeperiod_t &prd) const { return pd_ + prd.pd_; }
		timeperiod_t operator-(const timeperiod_t &prd) const { return pd_ - prd.pd_; }
		timeperiod_t &operator+=(const timeperiod_t &prd) { pd_ += prd.pd_; return *this; }
		timeperiod_t &operator-=(const timeperiod_t &prd) { pd_ -= prd.pd_; return *this; }
		timeperiod_t operator-() const { return -pd_; }
		//@}

		/// \name Conversion functions
		//@{
		double as_days() { return pd_; }
		void as_days(double prd) { pd_=prd; }
		double as_hours() { return pd_*24; }
		void as_hours(double prd) { pd_= prd/24; }
		double as_minutes() { return pd_*24*60; }
		void as_minutes(double prd) { pd_= prd/(24*60); }
		double as_seconds() { return pd_*24*60*60; }
		void as_seconds(double prd) { pd_= prd/(24*60*60); }
		//@}

		/// Split up the time period into days/hours/minutes/seconds.
		/** Backwards compatible.
		 * \deprecated
		 */
		void split( long& days, long& hours, long& minutes, long& seconds )
		{
			split(&days,&hours,&minutes,&seconds);
		}
		/// Split up the time period into days/hours/minutes/seconds.
		void split( long *days, long *hours, long *minutes, long *seconds, long *milliseconds = 0)
		{
			// Split into days and milliseconds.
			double int_part;
			long mspart = long(modf(pd_, &int_part) * 86400000);
			*days = long(int_part);
			// Optimise for integer.
			if (mspart == 0 )
			{
				*days = *hours = *minutes = *seconds =  0;
				if (milliseconds!=NULL) *milliseconds =0;
				return;
			}
			// Split up parts.
			long ms, quot, quot2;
			COMET_DIVMOD_(quot, ms, mspart, 1000);
			COMET_DIVMOD_(quot2, *seconds, quot, 60);
			COMET_DIVMOD_( *hours, *minutes, quot2, 60);
			if( milliseconds != NULL)
				*milliseconds = ms;
		}

		/// Set as days/hours/minutes/seconds.
		void set_period( long days, long hours, long minutes, long seconds, long milliseconds=0 )
		{
			pd_ = days + ((hours*3600000L) + (minutes*60000L)+ (seconds*1000L)+ milliseconds)/86400000.;
		}

		/// Return true if the period is invalid.
		bool invalid() const
		{
			return pd_ == (double)(dt_invalid_);
		}
		/// Return true if the period is not invalid.
		bool good() const
		{
			return !invalid();
		}
		/** return true if the period is valid.
		 * \deprecated
		 */
		bool valid() const { return !invalid(); }

		/// Return an invalid period.
		static timeperiod_t invalid_period() { return timeperiod_t( (double)(dt_invalid_)); }

};


/// A wrapper for choosing strftime/wcsftime based on char type.
template< typename CHAR >
inline size_t str_formattime( CHAR *strDest, size_t maxsize, const CHAR *format, const struct tm *timeptr )
{
	return -1;
}
/// @if Internal
template<>
inline size_t str_formattime<char>( char *strDest, size_t maxsize, const char *format, const struct tm *timeptr )
{
	return  strftime( strDest, maxsize, format, timeptr );
}

template<>
inline size_t str_formattime<wchar_t>( wchar_t *strDest, size_t maxsize, const wchar_t *format, const struct tm *timeptr )
{
	return  wcsftime( strDest, maxsize, format, timeptr );
}

namespace impl {
// Internally used to group div/mod so optimiser is likely to pick it up.
#ifdef __MINGW32__
	const double half_millisecond = 1.0/172800000.0;
#endif
	template<typename T>
		struct datetime_base
		{
			T dt_;

			enum convert_mode {
				cmBoth,
				cmOnlyTime,
				cmOnlyDate
			};


			/*! Convert absolute date to date-parts.
			*/
			static bool date_from_absdate_( long daysAbsolute, int *tm_year, int *tm_mon, int *tm_mday );

			/*! Convert absolute date to day-of-week.
			 */
			static bool dow_from_absdate_( long daysAbsolute, int *tm_wday)
			{
				// Calculate the day of week (sun=0, mon=1...)
				//   -1 because 1/1/0 is Sat.
				*tm_wday = (int)((daysAbsolute + 1) % 7L);
				return true;
			}

			/*! Convert date parts to absolute date.
			*/
			static bool absdate_from_date_( long *daysAbsolute, int tm_year, int tm_mon, int tm_mday);

			/*! Convert time in milliseconds to time of day parts.
			*/
			static bool time_from_milliseconds_( long milliseconds, int *tm_hour, int *tm_min, int *tm_sec, int *tm_ms);
			/*! Convert  time-of-day parts to milliseconds.
			*/
			static bool milliseconds_from_time_( long *milliseconds, unsigned short tm_hour, unsigned short tm_min, unsigned short tm_sec, unsigned short tm_ms);

			/*! Convert ole date to datetime-parts.
			*/
			static bool datetime_from_oledate_( DATE date, int *tm_year,  int *tm_mon, int *tm_mday,  int *tm_dow, int *tm_hour, int *tm_min, int *tm_sec, int *tm_ms,  convert_mode mode);

			/*! Get date part of oledate.
			*/
			static inline long split_oledate_as_absdate_( DATE date )
			{
				double val = to_double(date)+ (693959 + 1721060) + half_millisecond; // Add days from 1/1/0 to 12/30/1899
				return long(floor(val));
			}
			/*! Split oledate into date/milliseconds.
			*/
			static inline long split_oledate_as_absdate_( DATE date, long *ms_part,bool need_ms_part )
			{
				double val = to_double(date)+ (693959 + 1721060) + half_millisecond; // Add days from 1/1/0 to 12/30/1899
				if (!need_ms_part) return long(floor(val));
				*ms_part = long(modf(val, &val) * 86400000);
				return long(val);
			}

			/*! Join oledate.
			*/
			static inline DATE join_absdate_as_oledate_( long absDate, long ms_part)
			{
				return to_date( (double(absDate) + (ms_part / 86400000.)) - 693959 - 1721060 );
			}


			/*! Convert datetime-parts to ole date.
			*/
			static bool oledate_from_datetime_( DATE *date, unsigned short tm_year, unsigned short tm_mon, unsigned short tm_mday,  unsigned short tm_hour, unsigned short tm_min, unsigned short tm_sec, unsigned short tm_ms, convert_mode mode);

			/*! Convert TM to OLE date.
			 * Sets the date to invalid if unsuccessful.
			 * \retval true Successful conversion.
			 */
			static bool from_tm_( const struct tm &src, DATE *dt, convert_mode mode);

			/*! Convert OLE date to TM.
			 * \retval true Successful conversion.
			 */
			static bool to_tm_( DATE dt, struct tm *dest, int *ms);

			void set_invalid_() { dt_ = ((T) dt_invalid_); }
			void set_null_()  { dt_ = ((T) dt_null_); }

			/// Convert offset from 0 to DATE type.
			static DATE to_date( double dbl)
			{
				if(dbl>0) return dbl;
				double t=floor(dbl);
				return t+(t-dbl);
			}
			/// Convert DATE type to offset from 0.
			static double to_double( DATE dt)
			{
				if(dt>=0) return dt;
				double t = ceil(dt);
				return t-(dt-t);
			}

			/// Set to value \a dt and check the range.
			bool set_check_range_( T dt)
			{
				bool result = (dt <= dt_max && dt >= dt_min);
				if (result)
					dt_ = dt;
				return result;
			}
			/// Set the value to \a dt and set 'invalid' if out of range.
			void set_invalid_check_range_(T dt)
			{
				if (!set_check_range_(dt) )
					set_invalid_();
			}

			/// Return true if \a year is a leap-year.
			static bool is_leap_year( long year)
			{
				if ((year & 0x3) != 0) return false;
				// && ((year % 100) != 0 || (year % 400) == 0);
				long quot,rem;
				COMET_DIVMOD_(quot,rem, year, 100);
				if (rem != 0) return true;
				return ((quot & 0x3) == 0);
			}

			enum {
				dt_max = 2958465L, // about year 9999
				dt_null_ = 2147483648L,
				dt_invalid_ = 2147483647L,
				dt_min = (-657434L)  // about year 100
			};


			static int days_in_month(int year, int month)
			{
				switch (month)
				{
				case 2: return (is_leap_year(year)?29:28);
				case 4: case 6: case 9: case 11:
						return 30;
				default:return 31;
				};
			}

		};
	//! @endif
#ifndef __MINGW32__
	const double half_millisecond = 1.0/172800000.0;
#endif
	// Convert TM to OLE date
	template<typename T>
		bool
		datetime_base<T>::from_tm_( const struct tm &src, DATE *dt, convert_mode mode)
		{
			return oledate_from_datetime_( dt, (unsigned short)(src.tm_year + 1900),(unsigned short)( src.tm_mon+1),(unsigned short)( src.tm_mday),(unsigned short)( src.tm_hour),(unsigned short)( src.tm_min),(unsigned short)( src.tm_sec), 0U, mode);
		}

	// Convert OLE date to TM. \retval true Successful conversion.
	template<typename T>
		bool
		datetime_base<T>::to_tm_( DATE dt, struct tm *dest, int *ms)
		{
			int y,m,d;
			if ( !datetime_from_oledate_( dt,  &y,  &m, &d, &dest->tm_wday, &dest->tm_hour, &dest->tm_min, &dest->tm_sec, NULL, cmBoth) )
				return false;
			dest->tm_year = y;
			dest->tm_mon = m;
			dest->tm_mday = d;


			if (dest->tm_year != 0)
			{
				long firstday, thisday;
				absdate_from_date_( &thisday, y,m,d);
				absdate_from_date_(&firstday, y, 1, 1);
				dest->tm_yday =  1+ ( thisday - firstday);
				// Convert afx internal tm to format expected by runtimes (_tcsftime, etc)
				dest->tm_year -= 1900;  // year is based on 1900
				dest->tm_mon -= 1;      // month of year is 0-based
				dest->tm_isdst = -1;    // Don't know DST status.
			}
			else
				dest->tm_yday = 0;
			return true;
		}

	// Convert OLE date to date-parts.
	template<typename T>
		bool
		datetime_base<T>::date_from_absdate_(long daysAbsolute , int *tm_year, int *tm_mon, int *tm_mday)
		{
			// These algorithms are taken from the gregorian_calendar
			// calculations in boost.
			typedef long date_int_type;
			typedef int year_type;
			date_int_type dayNumber = daysAbsolute;
			date_int_type a = dayNumber + 32044 ;
			date_int_type b = (4*a + 3)/146097;
			date_int_type c = a-((146097*b)/4);
			date_int_type d = (4*c + 3)/1461;
			date_int_type e = c - (1461*d)/4;
			date_int_type m = (5*e + 2)/153;
			*tm_mday = static_cast<unsigned short>(e - ((153*m + 2)/5) + 1);
			*tm_mon = static_cast<unsigned short>(m + 3 - 12 * (m/10));
			*tm_year = static_cast<unsigned short>(100*b + d - 4800 + (m/10));
			return true;
		}

	// Convert date parts to absolute date.
	template<typename T>
		bool
		datetime_base<T>::absdate_from_date_( long *daysAbsolute, int tm_year, int tm_month, int tm_mday)
		{
			// These algorithms are taken from the gregorian_calendar
			// calculations in boost.
			unsigned short a = static_cast<unsigned short>((14-tm_month)/12);
			unsigned short y = static_cast<unsigned short>(tm_year + 4800 - a);
			unsigned short m = static_cast<unsigned short>(tm_month + 12*a - 3);
			unsigned long  d = tm_mday + ((153*m + 2)/5) + 365*y + (y/4) - (y/100) + (y/400) - 32045;

			*daysAbsolute = d;

			return true;
		}

	// Convert OLE time to time of day parts.
	template<typename T>
		bool
		datetime_base<T>::time_from_milliseconds_( long milliseconds, int *tm_hour, int *tm_min, int *tm_sec, int *tm_ms)
		{
			if (milliseconds == 0 )
			{
				*tm_hour = *tm_min = *tm_sec = 0;
				if (tm_ms!=NULL) *tm_ms =0;
				return true;
			}
			long ms, quot, quot2;
			COMET_DIVMOD_(quot, ms, milliseconds, 1000);
			COMET_DIVMOD_(quot2, *tm_sec, quot, 60);
			COMET_DIVMOD_( *tm_hour, *tm_min, quot2, 60);
			if( tm_ms != NULL)
				*tm_ms =  ms;
			return true;
		}
	// Convert  time-of-day parts to milliseconds.
	template<typename T>
		bool
		datetime_base<T>::milliseconds_from_time_( long *milliseconds, unsigned short tm_hour, unsigned short tm_min, unsigned short tm_sec, unsigned short tm_ms)
		{
			if ( tm_hour > 23 || tm_min > 59 || tm_sec> 59) return false;

			*milliseconds = (tm_hour* 3600000L) + (tm_min*60000L)+ (tm_sec*1000)+ tm_ms;
			return true;
		}

	//
	template<typename T>
		bool
		datetime_base<T>::datetime_from_oledate_( DATE date, int *tm_year, int *tm_mon, int *tm_mday, int *tm_wday, int *tm_hour, int *tm_min, int *tm_sec, int *tm_ms, convert_mode mode)
		{
			long datePart, msPart;
			datePart = split_oledate_as_absdate_(date, &msPart, mode != cmOnlyDate);
			if ( mode != cmOnlyDate && !time_from_milliseconds_( msPart, tm_hour, tm_min, tm_sec, tm_ms))
				return false;
			return (mode == cmOnlyTime) || (date_from_absdate_( datePart, tm_year, tm_mon, tm_mday)) && ( (tm_wday==NULL) || dow_from_absdate_(datePart, tm_wday));
		}
	// Convert datetime-parts to ole date.
	template<typename T>
		bool
		datetime_base<T>::oledate_from_datetime_( DATE *date, unsigned short tm_year, unsigned short tm_mon, unsigned short tm_mday, unsigned short tm_hour, unsigned short tm_min, unsigned short tm_sec, unsigned short tm_ms, convert_mode mode)
		{
			long datePart = 0, timePart = 0;
			if (mode != cmOnlyDate && !milliseconds_from_time_( &timePart, tm_hour, tm_min, tm_sec, tm_ms))
				return false;
			if (mode != cmOnlyTime && !absdate_from_date_( &datePart, tm_year, tm_mon, tm_mday))
				return false;
			*date = join_absdate_as_oledate_(datePart, timePart);
			return true;
		}
};


/** \class datetime_t datetime.h comet\datetime.h
  * Wrapper for DATE.
  * DATE/TIME Represented as days + fraction of days.
  */
class datetime_t : private impl::datetime_base<DATE>
{
	public:

		/** UTC/Local conversion mode.
		 */
		enum utc_convert_mode
		{
			ucm_none, //!< No conversion
			ucm_local_to_utc, //!< Convert from local to utc.
			ucm_utc_to_local, //!< Convert from utc to local.
		};
		/// Describe how to get the timezone bias.
		enum tz_bias_mode
		{
			tbm_use_local_date, ///< Use 'asOfDate' as a local date/time.
			tbm_use_utc_date,   ///< Use 'asOfDate' as a utc date/time.
			tbm_force_standard, ///< Use standard-timezone offset
			tbm_force_summer    ///< Use summer-timezone offset
		};
		/** \name Constructors.
		 * Attach to various system date/time types.
		 */
		//@{
		/// Constructor
		datetime_t()  { dt_ = 0.;}

		/// Constructor from raw DATE type.
		explicit datetime_t(DATE date)
		{
			dt_ = date;
		}
		//! Construct from date/time components.
		/** If conversion fails, an valid() will return false.
		 */
		explicit datetime_t(int year, int month, int day, int hours=-1, int minutes=0, int seconds=0, int milliseconds=0)
		{
			if (!oledate_from_datetime_( &dt_, (unsigned short)year, (unsigned short)month,
						(unsigned short)day, (unsigned short)hours, (unsigned short)minutes, (unsigned short)seconds, (unsigned short) milliseconds,
						(hours < 0)?cmOnlyDate:cmBoth ))
				set_invalid_();
		}

		/// Initialise as invalid.
		datetime_t( dt_invalid_t) { dt_ = dt_invalid_; }
		/// Initialise as null.
		datetime_t( dt_null_t) { dt_ = dt_null_; }
		/// Initialise as zero.
		datetime_t( dt_zero_t) { dt_ = 0.; }

		/// Get a 'NULL' datetime.
		static datetime_t get_null() { return datetime_t( DATE(dt_null_) ); }
		/// Get a 'zero' datetime.
		static datetime_t get_zero() { return datetime_t( DATE(0) ); }


		//! Construct from a SYSTEMTIME.
		/** Defaults to no conversion!
		 * \sa from_systemtime to_systemtime
		  */
		explicit datetime_t(const SYSTEMTIME& systimeSrc)
		{
			if (!from_systemtime(systimeSrc))
				set_invalid_();
		}

		//! Construct from a SYSTEMTIME.
		/**
		 * \param systimeSrc System time being converted.
		 * \param utcMode Timezone conversion mode.
		 * \param biasMode Specify how to calculate whether the local time is
		 * daylight/standard time.
		 * \param conversionTime Override the date to use for calculating
		 * daylight/standard time.
		 */
		explicit datetime_t(const SYSTEMTIME& systimeSrc, utc_convert_mode utcMode, tz_bias_mode biasMode = tbm_use_local_date, const datetime_t &conversionTime = datetime_t())
		{
			if (!from_systemtime(systimeSrc, utcMode, biasMode, conversionTime))
				set_invalid_();
		}

		//! Construct from a FILETIME.
		/** Defaults to no conversion. FILETIME values are a tricky beast.
		 * FILETIMEs on FAT are local, as are ZIP files (mostly). On shares and
		 * NTFS, they are UTC.
		 * \param filetimeSrc FileTime being converted.
		 * \param utcMode Timezone conversion mode.
		 * \param biasMode Specify how to calculate whether the local time is
		 * daylight/standard time.
		 * \param conversionTime Override the date to use for calculating
		 * daylight/standard time.
		 *
		 * \sa from_filetime to_filetime
		 */
		explicit datetime_t(const FILETIME& filetimeSrc, utc_convert_mode utcMode =ucm_none, tz_bias_mode biasMode = tbm_use_local_date, const datetime_t &conversionTime = datetime_t())
		{
			if (!from_filetime(filetimeSrc, utcMode, biasMode, conversionTime))
				set_invalid_();
		}

		//! Construct from time_t.
		/** \sa from_unixtime to_unixtime
		 * Defaults to conversion from utc to local time as time_t is in UTC.
		 * \param timeSrc time_t being converted.
		 * \param utcMode Timezone conversion mode.
		 * \param biasMode Specify how to calculate whether the local time is
		 * daylight/standard time.
		 * \param conversionTime Override the date to use for calculating
		 * daylight/standard time.
		 */
		explicit datetime_t(time_t timeSrc, utc_convert_mode utcMode = ucm_utc_to_local, tz_bias_mode biasMode = tbm_use_local_date, const datetime_t &conversionTime = datetime_t())
		{
			if (!from_unixtime(timeSrc, utcMode, biasMode, conversionTime))
				set_invalid_();
		}

		//! Copy constructor.
		datetime_t(const datetime_t& date)
		{
			dt_ = date.dt_;
		}

		//@}

		/// Create a const reference.
		static const datetime_t& create_const_reference(const DATE& s) throw()
		{ return *reinterpret_cast<const datetime_t*>(&s); }
		/// Create a non-const reference.
		static datetime_t& create_reference(DATE& s) throw()
		{ return *reinterpret_cast<datetime_t*>(&s); }

		/// Day-of-week enumeration.
		enum day_of_week {
			dow_sun=0, dow_mon, dow_tue, dow_wed, dow_thu, dow_fri, dow_sat
		};

		/// Return the current time.
		static datetime_t now()
		{
			SYSTEMTIME lt;
			::GetLocalTime(&lt);
			return datetime_t(lt);
		}
		/// Return the current utc time.
		static datetime_t now_utc()
		{
			SYSTEMTIME lt;
			::GetSystemTime(&lt);
			return datetime_t(lt);
		}

		/** Add specified number of months.
		 *  If the day is not valid (ie 1 month from 31 December)
		 *  an exception will be thrown.
		 *  \todo Add an enum to be more smart about this.
		 */
		datetime_t &add_months(int inc_months)
		{
			int year,month,day;

			split_date(&year,&month,&day);
			long months = (month-1)+(year*12)+inc_months;

			long quot,rem;
			COMET_DIVMOD_(quot, rem, months, 12);
			if(!set_date( quot, rem+1, day))
				throw datetime_exception("Invalid Date");

			return *this;
		}

		/// Add specified number of years.
		datetime_t &add_years(int inc_years)
		{
			int year,month,day;
			split_date(&year,&month,&day);
			if(!set_date( year+inc_years, month, day))
				throw datetime_exception("Invalid Date");
			return *this;
		}

		/// Return year/month/day values.
		void split_date(int *year, int *month, int *day) const
		{
			if (good())
			{
				long datePart = split_oledate_as_absdate_(dt_);
				if (date_from_absdate_( datePart, year, month, day) )
					return;
			}
			throw datetime_exception("Invalid Date");
		}

		/// Return hours/minutes/second values.
		void split_time( int *hours, int *minutes, int *seconds, int *milliseconds=NULL) const
		{
			if(!good() || !datetime_from_oledate_(dt_, NULL,  NULL, NULL, NULL, hours, minutes, seconds, milliseconds, cmOnlyTime))
				throw datetime_exception("Invalid DateTime");
		}
		/// Return date/time split up.
		void split(int *year, int *month, int *day, int *hours, int *minutes, int *seconds, int *milliseconds=NULL)
		{
			if(!good() || !datetime_from_oledate_(dt_, year, month, day, NULL, hours, minutes, seconds, milliseconds, cmBoth))
				throw datetime_exception("Invalid DateTime");
		}


		/// \name Access date/time parts.
		//@{
		/// Year.
		int year() const
		{
			int year,month,day;
			split_date(&year,&month,&day);
			return year;
		}
		/// Month of year (1-based)
		int month() const
		{
			int year,month,day;
			split_date(&year,&month,&day);
			return month;
		}
		/// Day of month (1-based)
		int day() const
		{
			int year,month,day;
			split_date(&year,&month,&day);
			return day;
		}
		/// Hour part of time (0-based) ???
		int hour() const
		{
			int hours,minutes,seconds;
			split_time(&hours,&minutes,&seconds);
			return hours;
		}
		/// Minute part of time (0-based)
		int minute() const
		{
			int hours,minutes,seconds;
			split_time(&hours,&minutes,&seconds);
			return minutes;
		}
		/// Second
		int second() const
		{
			int hours,minutes,seconds;
			split_time(&hours,&minutes,&seconds);
			return seconds;
		}
		/// Milliseconds
		int millisecond() const
		{
			int hours,minutes,seconds,ms;
			split_time(&hours,&minutes,&seconds,&ms);
			return ms;
		}

		/// The day of week.
		day_of_week dow() const
		{
			long datePart;
			datePart = split_oledate_as_absdate_(dt_);
			int wday;
			if(!good() || !dow_from_absdate_(datePart, &wday))
				throw datetime_exception("Invalid Date");
			return day_of_week(wday);
		}
		/// Day of the year (0 -based)
		int year_day() const
		{
			if (good())
			{
				long datepart = split_oledate_as_absdate_(dt_);
				int y,m,d;
				date_from_absdate_(datepart, &y,&m,&d);
				long firstday;
				if ( absdate_from_date_(&firstday, y, 1, 1))
					return 1+ ( datepart - firstday);
			}
			throw datetime_exception("Invalid Date");
		}
		/// Days in the month;
		int days_in_month()
		{
			int year,month,day;
			split_date(&year,&month,&day);
			return impl::datetime_base<DATE>::days_in_month(year,month);
		}
		//@}
		static inline int days_in_month(int year, int month)
		{
			return impl::datetime_base<DATE>::days_in_month(year,month);
		}

		/// \name Assignment operators
		//@{

		datetime_t &operator=( const datetime_t& date)
		{
			dt_ = date.dt_;
			return *this;
		}

		datetime_t &operator=( DATE date )
		{
			set_invalid_check_range_(date);
			return *this;
		}
		//@}

		///\name Comparison operators
		//@{
		bool operator==(const datetime_t& date) const{ return date.dt_==dt_; }
		bool operator!=(const datetime_t& date) const{ return date.dt_!=dt_; }
		bool operator<(const datetime_t& date) const { return to_double(dt_)<to_double(date.dt_); }
		bool operator>(const datetime_t& date) const{ return to_double(dt_)>to_double(date.dt_); }
		bool operator<=(const datetime_t& date) const{ return to_double(dt_)<=to_double(date.dt_); }
		bool operator>=(const datetime_t& date) const{ return to_double(dt_)>=to_double(date.dt_); }
		bool operator==(dt_invalid_t) const { return invalid(); }
		bool operator!=(dt_invalid_t) const { return !invalid(); }
		bool operator==(dt_zero_t) const { return dt_==0.; }
		bool operator!=(dt_zero_t) const { return dt_!=0.; }
		bool operator==(dt_null_t) const { return null(); }
		bool operator!=(dt_null_t) const { return !null(); }
		//@}

		///\name Arithmetic operators
		//@{
		datetime_t operator+(const timeperiod_t& dateSpan) const
		{
			datetime_t dt(*this);
			dt+=dateSpan;
			return dt;
		}
		datetime_t operator-(const timeperiod_t& dateSpan) const
		{
			datetime_t dt(*this);
			dt-=dateSpan;
			return dt;
		}
		datetime_t& operator+=(const timeperiod_t &dateSpan)
		{
			COMET_ASSERT( good() );
			if(!good())
				set_invalid_();
			else
				set_invalid_check_range_(to_date( to_double(dt_) + (double)dateSpan ));

			return *this;
		}
		datetime_t& operator-=(const timeperiod_t &dateSpan)
		{
			COMET_ASSERT( good() );
			if(!good())
				set_invalid_();
			else
				set_invalid_check_range_(to_date( to_double(dt_) - (double)dateSpan ));
			return *this;
		}
		timeperiod_t operator-(const datetime_t& date) const
		{
			COMET_ASSERT( good() && date.good() );
			if( !good() || ! date.good())
				return timeperiod_t::invalid_period();
			return to_double(dt_) - to_double(date.dt_);
		}
		datetime_t &operator++()
		{
			(*this)+=1;
			return *this;
		}
		datetime_t operator++(int)
		{
			datetime_t t(*this); (*this)+=1; return t;
		}
		datetime_t &operator--()
		{
			(*this)-=1; return *this;
		}

		datetime_t operator--(int)
		{
			datetime_t t(*this); (*this)-=1; return t;
		}
		//@}

		/// return true if the date is marked 'invalid'.
		inline bool invalid() const { return dt_ == ((double) dt_invalid_); }
		/// return true if the date is marked 'null'
		inline bool null()  const { return dt_ == ((double) dt_null_); }

		/// return true if date is zero
		inline bool zero() const { return dt_ == 0; }

		/** return true if the date is not marked 'invalid'.
		 * \deprecated
		 */
		inline bool valid() const { return !invalid(); }

		/// Return true if the date is usable.
		inline bool good() const
		{
			switch ((long)dt_)
			{
				case dt_invalid_: case dt_null_: return false;
				default: return true;
			}
		}

		///\name Accessor methods
		//@{
		DATE get() const { if(invalid()) throw("Invalid Date"); return null()?0:dt_;}
		DATE in() const { return get(); }
		DATE *in_ptr() const { return const_cast<DATE *>(&dt_);}
		DATE *out() { return &dt_;}
		DATE *inout() { return &dt_;}
		//@}
		/** Set date part as year/month/day.
		 * \param year Year (from year 0 - as in 2000).
		 * \param month Month of year (1-based).
		 * \param day Day of month (1-based).
		 * \retval true Successfully set date.
		 * \retval false Conversion unsuccessful - date not set.
		 */
		bool set_date( int year, int month, int day)
		{
			long datePart, timePart;
			datePart = split_oledate_as_absdate_(dt_, &timePart, true);
			if (!absdate_from_date_(&datePart, year,month, day))
				return false;
			dt_ = join_absdate_as_oledate_( datePart, timePart);
			return true;
		}

		/** Set time part as hours/minutes/seconds.
		 * \param hours As in a 24-hour clock.
		 * \param minutes Minutes past the hour.
		 * \param seconds Seconds past the minute.
		 * \param milliseconds Milliseconds past the second.
		 * \retval true Successfully set time.
		 * \retval false Conversion unsuccessful - time not set.
		 */
		bool set_time( int hours, int minutes, int seconds, int milliseconds =0)
		{
			long datePart, timePart;
			datePart = split_oledate_as_absdate_(dt_, &timePart, true);
			if (!milliseconds_from_time_(&timePart, (unsigned short)hours, (unsigned short)minutes, (unsigned short)seconds, (unsigned short)milliseconds))
				return false;
			dt_ = join_absdate_as_oledate_( datePart, timePart);
			return true;
		}
		/** Set both date and time.
		 * \param year Year (from year 0 - as in 2000).
		 * \param month Month of year (1-based).
		 * \param day Day of month (1-based).
		 * \param hours As in a 24-hour clock.
		 * \param minutes Minutes past the hour.
		 * \param seconds Seconds past the minute.
		 * \param milliseconds Milliseconds past the second.
		 * \retval true Successfully set date/time.
		 * \retval false Conversion unsuccessful - date/time not set.
		 */
		bool set_date_time(int year, int month, int day, int hours, int minutes, int seconds, int milliseconds = 0 )
		{
			return oledate_from_datetime_(&dt_, (unsigned short)year, (unsigned short)month, (unsigned short)day, (unsigned short)hours, (unsigned short)minutes, (unsigned short)seconds, (unsigned short)milliseconds, cmBoth);
		}

		/// Flags for formatting.
		enum format_flags{
			ff_default = 0,                                 ///< Default formatting.
			ff_system_locale = LOCALE_NOUSEROVERRIDE,       ///< Use system locale
			ff_hijri = VAR_CALENDAR_HIJRI,                  ///< Use HIJRI calendar.
			ff_thai =  0x10, /* VAR_CALENDAR_THAI, */       ///< Use thai calendar.
			ff_gregorian = 0x20, /*VAR_CALENDAR_GREGORIAN*/ ///< Use gregorian calendar.
			ff_four_digits = VAR_FOURDIGITYEARS,            ///< Four digits for years
			ff_time_only = VAR_TIMEVALUEONLY,               ///< Only output time.
			ff_date_only = VAR_DATEVALUEONLY                ///< Only output date.
		};
		/** Parse bstring to a datetime_t.
		 * \param val String to parse.
		 * \param flags valid format_flags are: ff_default, ff_system_locale, ff_hijri, ff_time_only, ff_date_only
		 * \param locale Locale to use.  Default \p locale is the user default.
		 */
		datetime_t &parse( const bstr_t &val, format_flags flags = ff_default, LCID locale = LOCALE_USER_DEFAULT)
		{
			VarDateFromStr( val.in(), locale, flags, &dt_) | raise_exception;
			return *this;
		}

		/** Return a double that is sortable / can be subtracted.
		 * Dates before 12/30/1899 will not sort propperly.
		 */
		double as_sortable_double() const { COMET_ASSERT( good() ); return to_double(dt_); }
	public:


		/**  Convert a local time to UTC.
		  *  Takes a local time (like that inside a ZIP file, or on a FAT file system)
		  *  and converts it to UTC, using the timezone rules in effect as of the date
		  *  specified.  Typically the "as of" date is specified as the modification or
		  *  creation date of the ZIP file, or left missing to default to the given local
		  *  date. It is also possible to specify if the "as of" date is in UTC or not.
		  *  If missing, it defaults to false.
		  */
		datetime_t local_to_utc( tz_bias_mode biasMode = tbm_use_local_date, datetime_t asOfDate = datetime_t() )
		{
			if (asOfDate.invalid())
				switch( biasMode)
				{
					case tbm_use_utc_date:      biasMode = tbm_use_local_date; // no break
					case tbm_use_local_date:    asOfDate = *this;
				}
			//  if they didn't specify if the AS OF date is UTC, use the current date
			return datetime_t(to_date(to_double(dt_)+local_timezone_bias(asOfDate,biasMode))/(24.*60.));
		}

		/** Convert a UTC time to a local time.
		 * Takes a UTC time (like that on and NTFS file system) and converts it to local
		 * time, using the timezone rules in effect as of the date specified.
		 * Typically the "as of" date is specified as the current time or possibly the
		 * modification or creation date of an enclosing ZIP file, or left missing to
		 * default to the given UTC date. It is also possible to specify if the "as
		 * of" date is in UTC or not.  If missing, if the "as of" date is not
		 * specified, it defaults to TRUE (since the "as of" date IS UTC), otherwise
		 * it defaults to false.
		 */
		datetime_t utc_to_local( tz_bias_mode biasMode = tbm_use_local_date,datetime_t asOfDate = datetime_t() )
		{
			if ( asOfDate.invalid())
				switch( biasMode)
				{
					case tbm_use_local_date: biasMode = tbm_use_utc_date; // no break!
					case tbm_use_utc_date:   asOfDate = *this;
				}
			return datetime_t(to_date(to_double(dt_)-local_timezone_bias(asOfDate,biasMode))/(24.*60.));
		}

		/** Convert to SYSTEMTIME struct.
		 */
		bool to_systemtime( SYSTEMTIME *sysTime)
		{
			int year,month,day,dow,hour,minute,second,ms;
			if (!datetime_from_oledate_( dt_, &year,  &month, &day, &dow, &hour, &minute, &second, &ms, cmBoth))
				return false;
			sysTime->wYear = (short)year;
			sysTime->wMonth = (short)month;
			sysTime->wDay = (short)day;
			sysTime->wDayOfWeek = (short)dow; // Sunday=0
			sysTime->wHour = (short)hour;
			sysTime->wMinute = (short)minute;
			sysTime->wSecond = (short)second;
			sysTime->wMilliseconds = (short)ms;
			return true;
		}

		/** Convert from a \e SYSTIME struct.
		 */
		bool from_systemtime(const SYSTEMTIME& src)
		{
			return oledate_from_datetime_( &dt_, src.wYear, src.wMonth, src.wDay, src.wHour, src.wMinute, src.wSecond, src.wMilliseconds, cmBoth);
		}
		/** Convert from a \e SYSTIME struct.
		 * \param src SYSTEMTIME being converted.
		 * \param utcMode Timezone conversion mode.
		 * \param biasMode Specify how to calculate whether the local time is
		 * daylight/standard time.
		 * \param conversionTime Override the date to use for calculating
		 * daylight/standard time.
		 */
		bool from_systemtime(const SYSTEMTIME& src, utc_convert_mode utcMode, tz_bias_mode biasMode = tbm_use_local_date , const datetime_t &conversionTime = datetime_t())
		{
			if (! from_systemtime( src))
				return false;
			switch( utcMode)
			{
				case ucm_none: break;
				case ucm_local_to_utc: *this = local_to_utc( biasMode, conversionTime ); break;
				case ucm_utc_to_local: *this = utc_to_local( biasMode, conversionTime); break;
			}
			return true;
		}
		/** Convert from a \e FILETIME struct.
		 */
		bool from_filetime(const FILETIME& src)
		{
			double ftd = ((((__int64)(src.dwHighDateTime) << 32 | src.dwLowDateTime)/(36000000000.)) - 2620920.)/24;
			return  set_check_range_( to_date(ftd));
		}
		/** Convert from a \e FILETIME struct.
		 * \param src FILETIME being converted.
		 * \param utcMode Timezone conversion mode.
		 * \param biasMode Specify how to calculate whether the local time is
		 * daylight/standard time.
		 * \param conversionTime Override the date to use for calculating
		 * daylight/standard time.
		 */
		bool from_filetime(const FILETIME& src, utc_convert_mode utcMode, tz_bias_mode biasMode = tbm_use_local_date, const datetime_t &conversionTime = datetime_t())
		{
			if (! from_filetime(src))
				return false;
			switch( utcMode)
			{
				case ucm_none: break;
				case ucm_local_to_utc: *this = local_to_utc( biasMode, conversionTime ); break;
				case ucm_utc_to_local: *this = utc_to_local( biasMode, conversionTime); break;
			}
			return true;
		}


		/** Convert to a \e FILETIME struct.
		 */
		bool to_filetime( FILETIME *filetime)
		{
			double val = ((to_double(dt_)  * 24.) + 2620920.)*(36000000000.) ;

			__int64 llval = (__int64)(val);
			filetime->dwHighDateTime = long (llval >> 32);
			filetime->dwLowDateTime = long (llval);
			return val > 0;
		}

		/** Convert from a \e tm struct.
		 */
		bool from_tm(const struct tm &tm_time)
		{
			return from_tm_( tm_time, &dt_, cmBoth);
		}
		/** Convert from a \e tm struct.
		 * \param tm_time 'tm' struct being converted.
		 * \param utcMode Timezone conversion mode.
		 * \param biasMode Specify how to calculate whether the local time is
		 * daylight/standard time.
		 * \param conversionTime Override the date to use for calculating
		 * daylight/standard time.
		 */
		bool from_tm(const struct tm &tm_time, utc_convert_mode utcMode, tz_bias_mode biasMode = tbm_use_local_date, datetime_t conversionTime = datetime_t())
		{
			if(!from_tm(tm_time))
				return false;
			switch( utcMode)
			{
				case ucm_none:
					break;
				case ucm_local_to_utc:
					// Take advantage of tm_isdst to work out dst mode!
					if( tm_time.tm_isdst >= 0)
						biasMode = (( tm_time.tm_isdst ==0)? tbm_force_standard: tbm_force_summer );
					*this = local_to_utc( biasMode, conversionTime );
					break;
				case ucm_utc_to_local:
					*this = utc_to_local( biasMode, conversionTime);
					break;
			}
			return true;
		}

		/** Convert from a \e time_t value.
		 */
		bool from_unixtime( time_t val)
		{
			FILETIME ft;
#if !defined(__MINGW32__) && !defined(VCF_BCC8)
			__int64 ll =(__int64(val) * 10000000L) + 116444736000000000L;
#else
			__int64 ll =((__int64)(val) * 10000000L) + 116444736000000000LL;
#endif
			ft.dwLowDateTime = (DWORD) ll;
			ft.dwHighDateTime = (DWORD)(ll >>32);
			return from_filetime(ft);
		}
		/** Convert from a \e time_t value.
		 * \param val Value to convert.
		 * \param utcMode Timezone conversion mode.
		 * \param biasMode Specify how to calculate whether the local time is
		 * daylight/standard time.
		 * \param conversionTime Override the date to use for calculating
		 * daylight/standard time.
		 */
		bool from_unixtime( time_t val, utc_convert_mode utcMode = ucm_utc_to_local, tz_bias_mode biasMode = tbm_use_local_date, const datetime_t &conversionTime = datetime_t())
		{
			FILETIME ft;
#if !defined(__MINGW32__) && !defined(VCF_BCC8)
			__int64 ll =(__int64(val) * 10000000L) + 116444736000000000L;
#else
			__int64 ll =((__int64)(val) * 10000000L) + 116444736000000000LL;
#endif
			ft.dwLowDateTime = (DWORD) ll;
			ft.dwHighDateTime = (DWORD)(ll >>32);
			return from_filetime( ft, utcMode, biasMode, conversionTime);
		}

		/** Convert to a \e time_t value.
		 * \param val time-t value output.
		 * \param utcMode Timezone conversion mode.
		 * \param biasMode Specify how to calculate whether the local time is
		 * daylight/standard time.
		 * \param conversionTime Override the date to use for calculating
		 * daylight/standard time.
		 */
		bool to_unixtime( time_t *val, utc_convert_mode utcMode = ucm_local_to_utc, tz_bias_mode biasMode = tbm_use_local_date, const datetime_t &conversionTime = datetime_t())
		{
			datetime_t dtval;
			switch( utcMode)
			{
				case ucm_none:          dtval = *this; break;
				case ucm_local_to_utc:  dtval = local_to_utc( biasMode, conversionTime ); break;
				case ucm_utc_to_local:  dtval = utc_to_local( biasMode, conversionTime); break;
			}
			FILETIME ft;
			if( !dtval.to_filetime(&ft) )
				return false;
#if !defined(__MINGW32__) && !defined(VCF_BCC8)
			*val = time_t(((__int64(ft.dwHighDateTime) << 32 | ft.dwLowDateTime) - 116444736000000000L)/10000000L);
#else
			*val = time_t((((__int64)(ft.dwHighDateTime) << 32 | ft.dwLowDateTime) - 116444736000000000LL)/10000000L);
#endif
			return true;
		}

		/** Calculates the local time Bias (to subtract from UTC), using the timezone
		  * rules for this date.  This "as of" date may be the
		  * current time or possibly the modification or creation date of an enclosing
		  * ZIP file.  It must be specified if this "as of" date is in UTC or not.
		  */
		static long local_timezone_bias( datetime_t dt, tz_bias_mode biasMode)
		{
			TIME_ZONE_INFORMATION tzi;
			::GetTimeZoneInformation(&tzi);

			long baseBias= tzi.Bias;
			bool isUTC = false;
			switch ( biasMode )
			{
				case tbm_force_standard: return baseBias + tzi.StandardBias;
				case tbm_force_summer:   return baseBias + tzi.DaylightBias;
				case tbm_use_local_date: break;
				case tbm_use_utc_date:   isUTC = true; break;
			}
			// if we've even got both time zones set, we have to choose which is active...
			if ((tzi.DaylightDate.wMonth != 0) && (tzi.StandardDate.wMonth != 0) )
			{
				// all local standard time/daylight savings time rules are based on
				// local-time, so add the base bias FIRST
				if (isUTC)
					dt -= (baseBias/(24.*60.));

				SYSTEMTIME sysTime;
				if (!dt.to_systemtime(&sysTime))
					throw datetime_exception("Invalid Date");

				bool DSTbeforeLST =  tzi.DaylightDate.wMonth < tzi.StandardDate.wMonth;

				bool afterDaylightStarts =  tz_on_or_after_in_year(sysTime, tzi.DaylightDate);
				bool afterStandardStarts =  tz_on_or_after_in_year(sysTime, tzi.StandardDate);

				if( ((afterDaylightStarts== afterStandardStarts)!= DSTbeforeLST) )
					return baseBias + tzi.DaylightBias;
			}
			return baseBias + tzi.StandardBias;
		}

	protected:
		/** Compares two SYSTEMTIME values to decide if the second is after (or on) the
		 * first.
		 * If the year is supplied, the two dates are assumed static, otherwise it
		 * computes the proper day-of-week instance (like last Sunday in October) for
		 * the specified test year.  See the encoding rules documented with
		 * TIME_ZONE_INFORMATION
		 */

		static bool tz_on_or_after_in_year(SYSTEMTIME testST, SYSTEMTIME tziST)
		{
			// assume month check first...
			long cmp = testST.wMonth - tziST.wMonth;
			if (cmp!=0)
				return cmp > 0;

			SYSTEMTIME absST;

			// if year is given, then the specified date is already exact...
			if (tziST.wYear != 0)
			{
				// first test the year...
				cmp = testST.wYear - tziST.wYear;
				if (cmp !=0)
					return cmp > 0;
				// carry on with the exact day known
				absST = tziST;
			}
			else
			{
				// compute the appropriate day from the specified instance of the set day-of-week
				// use the testST's year for the year in the calculation
				tz_convert_relative_dow_to_absolute(testST, tziST, &absST);
			}

			// month same... check day/hour/minute/second/millisecond
			if ((cmp = testST.wDay  - absST.wDay)==0)
				if ((cmp = testST.wHour - absST.wHour)==0)
					if ((cmp = testST.wMinute - absST.wMinute)==0)
						if ((cmp = testST.wSecond - absST.wSecond)==0)
							cmp = testST.wMilliseconds - absST.wMilliseconds;
			return cmp >= 0;
		}

		// Computes the proper day-of-week instance (like last Sunday in October) for the
		// specified test year.   See the encoding rules documented with TIME_ZONE_INFORMATION.
		// This ASSUMES that testST.wMonth == tziST.wMonth
		static void tz_convert_relative_dow_to_absolute(const SYSTEMTIME &testST , const SYSTEMTIME &tziST, SYSTEMTIME *absST)
		{
			COMET_ASSERT(testST.wMonth == tziST.wMonth);

			// Set up the absolute date except for wDay, which we must find
			absST->wYear = testST.wYear;          // year is only valid in the testST
			int month = absST->wMonth = tziST.wMonth;
			absST->wDayOfWeek = tziST.wDayOfWeek;

			absST->wHour = tziST.wHour;
			absST->wMinute = tziST.wMinute;
			absST->wSecond = tziST.wSecond;
			absST->wMilliseconds = tziST.wMilliseconds;

			// Find a day of the month that falls on the same day of the week as
			// the transition.

			// If test day is the 29th of the month (testST.wDay = 29) and today
			// is a Tuesday (testST.wDayOfWeek = 2) and the transition occurs on
			// Sunday (testST.wDayOfWeek = 0) we compute absDay = 29 + 0 + 7 -
			// 2, giving the 34th

			// then adjust that to a day of month adjustment
			long absDay = ((testST.wDay + tziST.wDayOfWeek + (7-1) - testST.wDayOfWeek) % 7) +1;

			// now multiply this time the "which DOW" setting from the TZI
			// (1 = first, 5 = last)
			// add the requisite number of weeks to the base point
			absDay += (7 * (tziST.wDay - 1));

			// and if we exceeded the number of days in the month, back up by a
			// week (this handles the 5=last situation)

			int daysInMonth = days_in_month( absST->wYear,  month);

			if (absDay > daysInMonth)
				absDay -= 7;

			absST->wDay = (unsigned short)absDay;
		}
	public:

		/** Format datetime_t as bstr.
		 * \param flags Format (can be or-ed). All format_flags are valid.
		 * \param locale Locale ID (default to User Default.
		 */
		bstr_t format( format_flags flags = ff_default , LCID locale = LOCALE_USER_DEFAULT) const
		{
			bstr_t strDate;
			if (!good())
			{
				return strDate;
			}
			VarBstrFromDate(dt_, locale, flags, strDate.out()) | raise_exception;
			return strDate;
		}

		/** Format datetime_t as basic_string.
		 * \param fmt See system documentation for strftime for details.
		 */
		template<typename CHAR>
			std::basic_string<CHAR> format( const std::basic_string<CHAR> &fmt ) const
			{
				return format(fmt.c_str());
			}

		/** Format datetime_t as basic_string.
		 * \param fmt See system documentation for strftime for details.
		 */
		template<typename CHAR>
			std::basic_string<CHAR> format( const CHAR *fmt ) const
			{
				if (!good())
				{
					return std::basic_string<CHAR>();
				}
				struct tm src;
				if(!to_tm_( dt_, &src, NULL))
					throw datetime_exception("Invalid Date");

				COMET_STRICT_TYPENAME auto_buffer_t<CHAR>::size_type capacity = 50;
				auto_buffer_t<CHAR> buf(capacity);
				size_t ret;
				while( (ret = str_formattime( buf.get() , capacity, fmt, &src ))==0 && capacity < 1024)
				{
					capacity += 50;
					buf.resize(capacity);
				}
				if(ret == 0)
					buf.at(0)='\0';

				return std::basic_string<CHAR>(buf.get(), ret);
			}

		/// Detach the raw date from the class.
		DATE detach()
		{
			DATE val = dt_;
			dt_ = 0.;
			return val;
		}

		/// Detach the raw date from the class.
		static DATE detach( datetime_t &dt)
		{
			return dt.detach();
		}

		/// Stream operator.
		friend
			std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const datetime_t &val)
			{
				os << val.format();
				return os;
			}

		/// Stream operator.
		friend
			std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &os, const datetime_t &val)
			{
				os << val.format();
				return os;
			}

	private:
};
#undef COMET_DIVMOD_
//@}

};
#endif
