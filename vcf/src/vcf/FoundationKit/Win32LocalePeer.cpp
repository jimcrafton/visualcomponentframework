//Win32LocalePeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/LocalePeer.h"
#include "vcf/FoundationKit/Win32LocalePeer.h"
#include "vcf/FoundationKit/DateTime.h"

#include <locale.h>

using namespace VCF;


class CalendarData {
public:

	CalendarData() :calType(0), shortDays(7), longDays(7),shortMonths(13),longMonths(13) {}

	DWORD calType;
	std::vector<String> shortDays;
	std::vector<String> longDays;

	std::vector<String> shortMonths;
	std::vector<String> longMonths;
};

class DateTimeParser {
public:

	DateTimeParser( LocalePeer* val ) {
		locale_ = val;
		lcID_ = (LCID)locale_->getHandleID();
		init();
	}

	enum FormatParseState {
		fpsSeparators = 0,
		fpsStartTag, //% char found
		fpsFormatter, 
		fpsDone
	};

	DateTime parse( const String& dateString, const String& formatting ) {
		DateTime result;

		if ( formatting.size() < 2 ) {
			throw RuntimeException( "Invalid formatting string for datetime parsing." );
		}


		const VCFChar* fmtPtr = formatting.c_str();
		const VCFChar* fmtStart = fmtPtr;
		const VCFChar* fmtDelimS = fmtPtr;
		int fmtSize = formatting.size();


		const VCFChar* dsPtr = dateString.c_str();
		const VCFChar* dsStart = dsPtr;
		const VCFChar* dsCurrent = dsPtr;
		int dsSize = dateString.size();
		size_t lastDelimPos = 0;
		int currentFmtChar = -1;

		size_t day, month, year, hour, minute, second, millis;
		day = month = year = -1;
		hour = minute = second = millis = 0;

		int state = fpsSeparators;

		bool using365Day = false;
		bool hashCharFound = false;

		do {	

			while ( dsPtr-dsStart < dsSize ) {
				switch ( *dsPtr ) {
					case '\n': case '\r': case ' ': case '\t': {
						dsPtr ++;
					}
					break;
				}

				dsCurrent = dsPtr;
				break;
			}

			switch ( *fmtPtr ) {
				case '%' : {
					state = fpsStartTag;
					hashCharFound = false;
				}
				break;
			}


			switch ( state ) {
				case fpsSeparators : {
					fmtPtr++;
				}
				break;

				case fpsStartTag : {					
					fmtPtr++;
					state = fpsFormatter;
				}
				break;

				case fpsFormatter : {
					if ( '#' == *fmtPtr ) {
						fmtPtr ++;
						hashCharFound = true;
					}
					currentFmtChar = *fmtPtr;
					state = fpsDone;
				}
				break;

				case fpsDone : {
					fmtDelimS = fmtPtr + 1;				

					String val;
					size_t extraIncr = 0;
					switch ( currentFmtChar ) {
						case 'B' : case 'b' : {
							while ( dsCurrent-dsStart < dsSize ) {
								if ( *dsCurrent == *fmtDelimS ) {
									break;
								}
								dsCurrent++;
							}
							
							val = val.append( dsPtr, dsCurrent - dsPtr );

							//short month

							if ( currentFmtChar == 'B' ) {
								for (size_t i=0;i<data_->longMonths.size();i++) {
									if ( 0 == StringUtils::noCaseCompare( this->data_->longMonths[i], val ) ) {
										month = i+1;
										break;
									}
								}
							}
							else {
								for (size_t i=0;i<data_->shortMonths.size();i++) {
									if ( 0 == StringUtils::noCaseCompare( this->data_->shortMonths[i], val ) ) {
										month = i+1;
										break;
									}
								}
							}

							extraIncr = 1;
						}
						break;

						case 'A' : case 'a' : {
							while ( dsCurrent-dsStart < dsSize ) {
								if ( *dsCurrent == *fmtDelimS ) {
									break;
								}
								dsCurrent++;
							}
							
							val = val.append( dsPtr, dsCurrent - dsPtr );

							//short month

							if ( currentFmtChar == 'A' ) {
								for (size_t i=0;i<data_->longDays.size();i++) {
									if ( 0 == StringUtils::noCaseCompare( this->data_->longDays[i], val ) ) {
										day = i+1;
										break;
									}
								}
							}
							else {
								for (size_t i=0;i<data_->shortDays.size();i++) {
									if ( 0 == StringUtils::noCaseCompare( this->data_->shortDays[i], val ) ) {
										day = i+1;
										break;
									}
								}
							}

							extraIncr = 1;
						}
						break;

						case 'd' : {

							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 2 ) );
							}
							else {
								if ( ((dsPtr+2)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//day 01-31
								val = val.append( dsPtr, 2 );
							}

							

							day = locale_->toUInt( val );
							
						}
						break;

						case 'Y' : {
							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 4 ) );
								extraIncr = 1;
							}
							else {
								if ( ((dsPtr+4)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//year with century
								val = val.append( dsPtr, 4 );
							}

							year = locale_->toUInt( val );
							
						}
						break;

						case 'y' : {
							//year without century
							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 2 ) );
								extraIncr = 1;
							}
							else {
								if ( ((dsPtr+2)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//year with century
								val = val.append( dsPtr, 2 );
							}

							year = locale_->toUInt( val );
							
						}
						break;


						case 'H' : {
							//%H - Hour in 24-hour format (00  23)
							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 2 ) );
								extraIncr = 1;
							}
							else {
								if ( ((dsPtr+2)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//year with century
								val = val.append( dsPtr, 2 );
							}

							hour = locale_->toUInt( val );
							
						}
						break;

						case 'I' : {
							//%I - Hour in 12-hour format (01  12)
							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 2 ) );
								extraIncr = 1;
							}
							else {
								if ( ((dsPtr+2)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//year with century
								val = val.append( dsPtr, 2 );
							}

							hour = locale_->toUInt( val );
							
						}
						break;

						case 'm' : {
							//%m - Month as decimal number (01  12)
							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 2 ) );
								extraIncr = 1;
							}
							else {
								if ( ((dsPtr+2)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//year with century
								val = val.append( dsPtr, 2 );
							}

							month = locale_->toUInt( val );
							
						}
						break;

						case 'M' : {
							//%M - Minute as decimal number (00  59)
							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 2 ) );
								extraIncr = 1;
							}
							else {
								if ( ((dsPtr+2)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//year with century
								val = val.append( dsPtr, 2 );
							}

							minute = locale_->toUInt( val );
							
						}
						break;

						case 'P' : {
							//%P - Current locale's A.M./P.M. indicator for 12-hour clock
							
							while ( dsCurrent-dsStart < dsSize ) {
								if ( *dsCurrent == *fmtDelimS ) {
									break;
								}
								dsCurrent++;
							}
								
							val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 2 ) );
							extraIncr = 1;
							
							//minute = locale_->toUInt( val );
							
						}
						break;

						case 's' : {
							//%s - millisecond part
							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 3 ) );
								extraIncr = 1;
							}
							else {
								if ( ((dsPtr+3)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//year with century
								val = val.append( dsPtr, 3 );
							}

							millis = locale_->toUInt( val );
							
						}
						break;

						case 'S' : {
							//%S - Second as decimal number (00  59)
							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 2 ) );
								extraIncr = 1;
							}
							else {
								if ( ((dsPtr+2)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//year with century
								val = val.append( dsPtr, 2 );
							}

							second = locale_->toUInt( val );
							
						}
						break;

						case 'w' : {
							//%w - Weekday as decimal number (0  6; Sunday is 0)
							
							while ( dsCurrent-dsStart < dsSize ) {
								if ( *dsCurrent == *fmtDelimS ) {
									break;
								}
								dsCurrent++;
							}
							
							val = val.append( dsPtr, dsCurrent - dsPtr );
							extraIncr = 1;
						}
						break;

						case 'W' : {
							//%W - Week of year as decimal number, with Monday as first day of week (00  53)
							
							if ( hashCharFound ) {
								while ( dsCurrent-dsStart < dsSize ) {
									if ( *dsCurrent == *fmtDelimS ) {
										break;
									}
									dsCurrent++;
								}
								
								val = val.append( dsPtr, minVal<size_t>( dsCurrent - dsPtr, 2 ) );
								extraIncr = 1;
							}
							else {
								if ( ((dsPtr+2)-dsStart) > dsSize ) {
									throw RuntimeException( "Date string too small" );
								}
								//year with century
								val = val.append( dsPtr, 2 );
							}


						}
						break;

						case 'D' : case 'j' : {
							using365Day = true;

							while ( dsCurrent-dsStart < dsSize ) {
								if ( *dsCurrent == *fmtDelimS ) {
									break;
								}
								dsCurrent++;
							}
							
							val = val.append( dsPtr, dsCurrent - dsPtr );

							day = locale_->toUInt( val );

							extraIncr = 1;
							
						}
						break;
					}

					

					dsPtr += val.size() + extraIncr;
					while ( dsPtr-dsStart < dsSize ) {
						if ( *dsPtr == *fmtDelimS ) {
							dsPtr++;
						}
						else {
							break;
						}
					}


					fmtPtr++;
					state = fpsSeparators;
					
				}
				break;
			}

		} while ( ((dsPtr-dsStart) < dsSize) && ((fmtPtr-fmtStart) < fmtSize) );


		if ( year == -1 ) {
			throw RuntimeException( "The data and/or format string(s) probably invalid, no year was specified");
		}

		if ( using365Day ) {
			if ( day == -1 ) {
				throw RuntimeException( "The data and/or format string(s) probably invalid, no day was specified");
			}
		}
		else {
			if ( month == -1 ) {
				throw RuntimeException( "The data and/or format string(s) probably invalid, no month was specified");
			}
			
			if ( day == -1 ) {
				throw RuntimeException( "The data and/or format string(s) probably invalid, no day was specified");
			}
		}
		
		if ( using365Day ) {
			result.setDate( year, day );
			result.setTime( hour, minute, second );
			result.incrMilliSecond( millis );
		}
		else {
			result.set( year, month, day, hour, minute, second, millis );
		}

		return result;
	}

protected:
	LocalePeer* locale_;
	LCID lcID_;
	CalendarData* data_;
	void init() {
		std::map<LCID,CalendarData*>::iterator found = 
			DateTimeParser::calendarMap.find( this->lcID_ );
		if ( found == DateTimeParser::calendarMap.end() ) {
			CalendarData* data = new CalendarData();


			if ( !GetLocaleInfoW( lcID_, LOCALE_ICALENDARTYPE | LOCALE_RETURN_NUMBER, (LPWSTR)&data->calType, sizeof(data->calType) ) ) {
				throw RuntimeException( "Failed to determine calendar type" );
			}

			WCHAR tmp[256];
			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVDAYNAME1, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortDays[0] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVDAYNAME2, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortDays[1] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVDAYNAME3, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortDays[2] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVDAYNAME4, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortDays[3] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVDAYNAME5, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortDays[4] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVDAYNAME6, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortDays[5] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVDAYNAME7, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortDays[6] = tmp;


			GetCalendarInfoW( lcID_, data->calType, CAL_SDAYNAME1, &tmp[0], sizeof(tmp)-1, NULL );
			data->longDays[0] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SDAYNAME2, &tmp[0], sizeof(tmp)-1, NULL );
			data->longDays[1] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SDAYNAME3, &tmp[0], sizeof(tmp)-1, NULL );
			data->longDays[2] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SDAYNAME4, &tmp[0], sizeof(tmp)-1, NULL );
			data->longDays[3] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SDAYNAME5, &tmp[0], sizeof(tmp)-1, NULL );
			data->longDays[4] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SDAYNAME6, &tmp[0], sizeof(tmp)-1, NULL );
			data->longDays[5] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SDAYNAME7, &tmp[0], sizeof(tmp)-1, NULL );
			data->longDays[6] = tmp;


			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME1, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[0] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME2, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[1] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME3, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[2] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME4, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[3] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME5, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[4] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME6, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[5] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME7, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[6] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME8, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[7] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME9, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[8] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME10, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[9] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME11, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[10] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME12, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[11] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SABBREVMONTHNAME13, &tmp[0], sizeof(tmp)-1, NULL );
			data->shortMonths[12] = tmp;



			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME1, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[0] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME2, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[1] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME3, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[2] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME4, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[3] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME5, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[4] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME6, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[5] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME7, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[6] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME8, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[7] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME9, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[8] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME10, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[9] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME11, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[10] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME12, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[11] = tmp;

			GetCalendarInfoW( lcID_, data->calType, CAL_SMONTHNAME13, &tmp[0], sizeof(tmp)-1, NULL );
			data->longMonths[12] = tmp;

			DateTimeParser::calendarMap[this->lcID_] = data;

			data_ = data;
		}
		else {
			data_ = found->second;
		}
	}

	static std::map<LCID,CalendarData*> calendarMap; 
};

std::map<LCID,CalendarData*> DateTimeParser::calendarMap;






std::map<AnsiString,int> Win32LocalePeer::langIDs;
std::map<AnsiString,int> Win32LocalePeer::countryIDs;
static std::map<AnsiString,AnsiString> countryToWin32Country;
static std::map<AnsiString,AnsiString> languageToWin32Language;

Win32LocalePeer::Win32LocalePeer():lcid_(0)
{
	lcid_ = GetUserDefaultLCID();



	if ( Win32LocalePeer::langIDs.empty() ) {
		Win32LocalePeer::langIDs["af"] = LANG_AFRIKAANS;
		Win32LocalePeer::langIDs["sq"] = LANG_ALBANIAN;
		Win32LocalePeer::langIDs["ar"] = LANG_ARABIC;
		Win32LocalePeer::langIDs["hy"] = LANG_ARMENIAN;
		Win32LocalePeer::langIDs["as"] = LANG_ASSAMESE;
		Win32LocalePeer::langIDs["az"] = LANG_AZERI;
		Win32LocalePeer::langIDs["eu"] = LANG_BASQUE;
		Win32LocalePeer::langIDs["be"] = LANG_BELARUSIAN;
		Win32LocalePeer::langIDs["bn"] = LANG_BENGALI;
		Win32LocalePeer::langIDs["bg"] = LANG_BULGARIAN;
		Win32LocalePeer::langIDs["ca"] = LANG_CATALAN;
		Win32LocalePeer::langIDs["zh"] = LANG_CHINESE;
		Win32LocalePeer::langIDs["hr"] = LANG_CROATIAN;
		Win32LocalePeer::langIDs["cs"] = LANG_CZECH;
		Win32LocalePeer::langIDs["da"] = LANG_DANISH;
		Win32LocalePeer::langIDs["nl"] = LANG_DUTCH;
		Win32LocalePeer::langIDs["en"] = LANG_ENGLISH;
		Win32LocalePeer::langIDs["et"] = LANG_ESTONIAN;
		Win32LocalePeer::langIDs["fo"] = LANG_FAEROESE;
		Win32LocalePeer::langIDs["fa"] = LANG_FARSI;
		Win32LocalePeer::langIDs["fi"] = LANG_FINNISH;
		Win32LocalePeer::langIDs["fr"] = LANG_FRENCH;
		Win32LocalePeer::langIDs["ka"] = LANG_GEORGIAN;
		Win32LocalePeer::langIDs["de"] = LANG_GERMAN;
		Win32LocalePeer::langIDs["el"] = LANG_GREEK;
		Win32LocalePeer::langIDs["gu"] = LANG_GUJARATI;
		Win32LocalePeer::langIDs["he"] = LANG_HEBREW;
		Win32LocalePeer::langIDs["hi"] = LANG_HINDI;
		Win32LocalePeer::langIDs["hu"] = LANG_HUNGARIAN;
		Win32LocalePeer::langIDs["is"] = LANG_ICELANDIC;
		Win32LocalePeer::langIDs["id"] = LANG_INDONESIAN;
		Win32LocalePeer::langIDs["it"] = LANG_ITALIAN;
		Win32LocalePeer::langIDs["ja"] = LANG_JAPANESE;
		Win32LocalePeer::langIDs["kn"] = LANG_KANNADA;
		Win32LocalePeer::langIDs["ks"] = LANG_KASHMIRI;
		Win32LocalePeer::langIDs["kk"] = LANG_KAZAK;
		Win32LocalePeer::langIDs["kok"] = LANG_KONKANI;
		Win32LocalePeer::langIDs["ko"] = LANG_KOREAN;
		Win32LocalePeer::langIDs["lv"] = LANG_LATVIAN;
		Win32LocalePeer::langIDs["lt"] = LANG_LITHUANIAN;
		Win32LocalePeer::langIDs["mk"] = LANG_MACEDONIAN;
		Win32LocalePeer::langIDs["ms"] = LANG_MALAY;
		Win32LocalePeer::langIDs["ml"] = LANG_MALAYALAM;
		Win32LocalePeer::langIDs["mni"] = LANG_MANIPURI;
		Win32LocalePeer::langIDs["mr"] = LANG_MARATHI;
		Win32LocalePeer::langIDs["ne"] = LANG_NEPALI;
		Win32LocalePeer::langIDs["no"] = LANG_NORWEGIAN;
		Win32LocalePeer::langIDs["or"] = LANG_ORIYA;
		Win32LocalePeer::langIDs["pl"] = LANG_POLISH;
		Win32LocalePeer::langIDs["pt"] = LANG_PORTUGUESE;
		Win32LocalePeer::langIDs["pa"] = LANG_PUNJABI;
		Win32LocalePeer::langIDs["ro"] = LANG_ROMANIAN;
		Win32LocalePeer::langIDs["ru"] = LANG_RUSSIAN;
		Win32LocalePeer::langIDs["sa"] = LANG_SANSKRIT;
		Win32LocalePeer::langIDs["sr"] = LANG_SERBIAN;
		Win32LocalePeer::langIDs["sd"] = LANG_SINDHI;
		Win32LocalePeer::langIDs["sk"] = LANG_SLOVAK;
		Win32LocalePeer::langIDs["sl"] = LANG_SLOVENIAN;
		Win32LocalePeer::langIDs["es"] = LANG_SPANISH;
		Win32LocalePeer::langIDs["sw"] = LANG_SWAHILI;
		Win32LocalePeer::langIDs["sv"] = LANG_SWEDISH;
		Win32LocalePeer::langIDs["ta"] = LANG_TAMIL;
		Win32LocalePeer::langIDs["tt"] = LANG_TATAR;
		Win32LocalePeer::langIDs["te"] = LANG_TELUGU;
		Win32LocalePeer::langIDs["th"] = LANG_THAI;
		Win32LocalePeer::langIDs["tr"] = LANG_TURKISH;
		Win32LocalePeer::langIDs["uk"] = LANG_UKRAINIAN;
		Win32LocalePeer::langIDs["ur"] = LANG_URDU;
		Win32LocalePeer::langIDs["uz"] = LANG_UZBEK;
		Win32LocalePeer::langIDs["vi"] = LANG_VIETNAMESE;
	}


	if ( countryToWin32Country.empty() ) {
		countryToWin32Country["AU"] = "aus";
		countryToWin32Country["AT"] = "aut";
		countryToWin32Country["BE"] = "bel";
		countryToWin32Country["BR"] = "bra";
		countryToWin32Country["CA"] = "can";
		countryToWin32Country["CZ"] = "cze";
		countryToWin32Country["DK"] = "dnk";
		countryToWin32Country["FI"] = "fin";
		countryToWin32Country["FR"] = "fra";
		countryToWin32Country["DE"] = "deu";
		countryToWin32Country["GR"] = "grc";
		countryToWin32Country["HK"] = "hkg";
		countryToWin32Country["HU"] = "hun";
		countryToWin32Country["IS"] = "isl";
		countryToWin32Country["IE"] = "irl";
		countryToWin32Country["IT"] = "ita";
		countryToWin32Country["JP"] = "jpn";
		countryToWin32Country["MX"] = "mex";
		countryToWin32Country["NL"] = "nld";
		countryToWin32Country["NZ"] = "nzl";
		countryToWin32Country["NO"] = "nor";
		countryToWin32Country["CN"] = "chn";
		countryToWin32Country["PL"] = "pol";
		countryToWin32Country["PT"] = "prt";
		countryToWin32Country["RU"] = "rus";
		countryToWin32Country["SG"] = "sgp";
		countryToWin32Country["SK"] = "svk";
		countryToWin32Country["KR"] = "kor";
		countryToWin32Country["ES"] = "esp";
		countryToWin32Country["SE"] = "swe";
		countryToWin32Country["CH"] = "che";
		countryToWin32Country["TW"] = "twn";
		countryToWin32Country["TR"] = "tur";
		countryToWin32Country["UK"] = "gbr";
		countryToWin32Country["US"] = "usa";
	}

	if ( languageToWin32Language.empty() ) {
		languageToWin32Language["en"] = "english";

		languageToWin32Language["zh_CN"] = "chinese";
		languageToWin32Language["zh_HK"] = "chinese";
		languageToWin32Language["zh_SG"] = "chinese";
		languageToWin32Language["zh_MO"] = "chinese";
		languageToWin32Language["nl_BK"] = "dutch";
		languageToWin32Language["nl_BE"] = "dutch-belgian";
		languageToWin32Language["en_US"] = "english-us";
		languageToWin32Language["en_UK"] = "english-uk";
		languageToWin32Language["en_GB"] = "english-uk";
		languageToWin32Language["en_AU"] = "english-aus";
		languageToWin32Language["en_CA"] = "english-can";
		languageToWin32Language["en_NZ"] = "english-nz";
		languageToWin32Language["fr_FR"] = "french";
		languageToWin32Language["fr_BE"] = "french-belgian";
		languageToWin32Language["fr_CA"] = "french-canadian";
		languageToWin32Language["fr_CH"] = "french-swiss";
		languageToWin32Language["de_DE"] = "german";
		languageToWin32Language["de_CH"] = "german-swiss";
		languageToWin32Language["de_AT"] = "german-austrian";

		languageToWin32Language["is_IS"] = "icelandic";

		languageToWin32Language["el_GR"] = "greek";

		languageToWin32Language["hu_HU"] = "hungarian";

		languageToWin32Language["it_IT"] = "italian";
		languageToWin32Language["it_CH"] = "italian-swiss";
		languageToWin32Language["ja_JP"] = "japanese";

		languageToWin32Language["ko_KR"] = "korean";
		languageToWin32Language["no_BK"] = "norwegian-bokmal";
		languageToWin32Language["no_NO"] = "norwegian-nynorsk";
		languageToWin32Language["pl_PL"] = "polish";
		languageToWin32Language["pt_PT"] = "portuguese";
		languageToWin32Language["pt_BR"] = "portuguese-brazilian";
		languageToWin32Language["es_ES"] = "spanish";
		languageToWin32Language["es_MX"] = "spanish-mexican";
		languageToWin32Language["es_GT"] = "spanish-modern";
		languageToWin32Language["es_CR"] = "spanish-modern";
		languageToWin32Language["es_PA"] = "spanish-modern";
		languageToWin32Language["es_DO"] = "spanish-modern";
		languageToWin32Language["es_VE"] = "spanish-modern";
		languageToWin32Language["es_CO"] = "spanish-modern";
		languageToWin32Language["es_PE"] = "spanish-modern";
		languageToWin32Language["es_AR"] = "spanish-modern";
		languageToWin32Language["es_EC"] = "spanish-modern";
		languageToWin32Language["es_CL"] = "spanish-modern";
		languageToWin32Language["es_UY"] = "spanish-modern";
		languageToWin32Language["es_PY"] = "spanish-modern";
		languageToWin32Language["es_BO"] = "spanish-modern";
		languageToWin32Language["es_SV"] = "spanish-modern";
		languageToWin32Language["es_HN"] = "spanish-modern";
		languageToWin32Language["es_NI"] = "spanish-modern";
		languageToWin32Language["es_PR"] = "spanish-modern";
		languageToWin32Language["sv_SE"] = "swedish";
		languageToWin32Language["tr_TR"] = "turkish";
	}

	if ( Win32LocalePeer::countryIDs.empty() ) {
		Win32LocalePeer::countryIDs["ar_SA"] = SUBLANG_ARABIC_SAUDI_ARABIA;
		Win32LocalePeer::countryIDs["ar_IQ"] = SUBLANG_ARABIC_IRAQ;
		Win32LocalePeer::countryIDs["ar_EG"] = SUBLANG_ARABIC_EGYPT;
		Win32LocalePeer::countryIDs["ar_LY"] = SUBLANG_ARABIC_LIBYA;
		Win32LocalePeer::countryIDs["ar_DZ"] = SUBLANG_ARABIC_ALGERIA;
		Win32LocalePeer::countryIDs["ar_MA"] = SUBLANG_ARABIC_MOROCCO;
		Win32LocalePeer::countryIDs["ar_TN"] = SUBLANG_ARABIC_TUNISIA;
		Win32LocalePeer::countryIDs["ar_OM"] = SUBLANG_ARABIC_OMAN;
		Win32LocalePeer::countryIDs["ar_YE"] = SUBLANG_ARABIC_YEMEN;
		Win32LocalePeer::countryIDs["ar_SY"] = SUBLANG_ARABIC_SYRIA;
		Win32LocalePeer::countryIDs["ar_JO"] = SUBLANG_ARABIC_JORDAN;
		Win32LocalePeer::countryIDs["ar_LB"] = SUBLANG_ARABIC_LEBANON;
		Win32LocalePeer::countryIDs["ar_KW"] = SUBLANG_ARABIC_KUWAIT;
		Win32LocalePeer::countryIDs["ar_AE"] = SUBLANG_ARABIC_UAE;
		Win32LocalePeer::countryIDs["ar_BH"] = SUBLANG_ARABIC_BAHRAIN;
		Win32LocalePeer::countryIDs["ar_QA"] = SUBLANG_ARABIC_QATAR;
		Win32LocalePeer::countryIDs["az_AZ"] = SUBLANG_AZERI_CYRILLIC;
		Win32LocalePeer::countryIDs["zh_CN"] = SUBLANG_CHINESE_TRADITIONAL;
		Win32LocalePeer::countryIDs["zh_HK"] = SUBLANG_CHINESE_HONGKONG;
		Win32LocalePeer::countryIDs["zh_SG"] = SUBLANG_CHINESE_SINGAPORE;
		Win32LocalePeer::countryIDs["zh_MO"] = SUBLANG_CHINESE_MACAU;
		Win32LocalePeer::countryIDs["nl_BK"] = SUBLANG_DUTCH;
		Win32LocalePeer::countryIDs["nl_BE"] = SUBLANG_DUTCH_BELGIAN;
		Win32LocalePeer::countryIDs["en_US"] = SUBLANG_ENGLISH_US;
		Win32LocalePeer::countryIDs["en_UK"] = SUBLANG_ENGLISH_UK;
		Win32LocalePeer::countryIDs["en_GB"] = SUBLANG_ENGLISH_UK;
		Win32LocalePeer::countryIDs["en_AU"] = SUBLANG_ENGLISH_AUS;
		Win32LocalePeer::countryIDs["en_CA"] = SUBLANG_ENGLISH_CAN;
		Win32LocalePeer::countryIDs["en_NZ"] = SUBLANG_ENGLISH_NZ;
		Win32LocalePeer::countryIDs["en_IE"] = SUBLANG_ENGLISH_EIRE;
		Win32LocalePeer::countryIDs["en_ZA"] = SUBLANG_ENGLISH_SOUTH_AFRICA;
		Win32LocalePeer::countryIDs["en_JM"] = SUBLANG_ENGLISH_JAMAICA;
		Win32LocalePeer::countryIDs["en_BZ"] = SUBLANG_ENGLISH_BELIZE;
		Win32LocalePeer::countryIDs["en_TT"] = SUBLANG_ENGLISH_TRINIDAD;
		Win32LocalePeer::countryIDs["en_PH"] = SUBLANG_ENGLISH_PHILIPPINES;
		Win32LocalePeer::countryIDs["en_ZW"] = SUBLANG_ENGLISH_ZIMBABWE;
		Win32LocalePeer::countryIDs["fr_FR"] = SUBLANG_FRENCH;

		Win32LocalePeer::countryIDs["fr_BE"] = SUBLANG_FRENCH_BELGIAN;

		Win32LocalePeer::countryIDs["fr_CA"] = SUBLANG_FRENCH_CANADIAN;
		Win32LocalePeer::countryIDs["fr_CH"] = SUBLANG_FRENCH_SWISS;
		Win32LocalePeer::countryIDs["fr_LU"] = SUBLANG_FRENCH_LUXEMBOURG;
		Win32LocalePeer::countryIDs["fr_MC"] = SUBLANG_FRENCH_MONACO;
		Win32LocalePeer::countryIDs["de_DE"] = SUBLANG_GERMAN;
		Win32LocalePeer::countryIDs["de_CH"] = SUBLANG_GERMAN_SWISS;
		Win32LocalePeer::countryIDs["de_AT"] = SUBLANG_GERMAN_AUSTRIAN;
		Win32LocalePeer::countryIDs["de_LU"] = SUBLANG_GERMAN_LUXEMBOURG;
		Win32LocalePeer::countryIDs["de_LI"] = SUBLANG_GERMAN_LIECHTENSTEIN;
		Win32LocalePeer::countryIDs["it_IT"] = SUBLANG_ITALIAN;
		Win32LocalePeer::countryIDs["it_CH"] = SUBLANG_ITALIAN_SWISS;
		Win32LocalePeer::countryIDs["ks_IN"] = SUBLANG_KASHMIRI_INDIA;
		Win32LocalePeer::countryIDs["ko_KR"] = SUBLANG_KOREAN;
		Win32LocalePeer::countryIDs["lt_LT"] = SUBLANG_LITHUANIAN;
		Win32LocalePeer::countryIDs["ms_BN"] = SUBLANG_MALAY_BRUNEI_DARUSSALAM;
		Win32LocalePeer::countryIDs["ne_IN"] = SUBLANG_NEPALI_INDIA;
		Win32LocalePeer::countryIDs["no_BK"] = SUBLANG_NORWEGIAN_BOKMAL;
		Win32LocalePeer::countryIDs["no_NO"] = SUBLANG_NORWEGIAN_NYNORSK;
		Win32LocalePeer::countryIDs["pt_PT"] = SUBLANG_PORTUGUESE;
		Win32LocalePeer::countryIDs["pt_BR"] = SUBLANG_PORTUGUESE_BRAZILIAN;
		Win32LocalePeer::countryIDs["sr_CS"] = SUBLANG_SERBIAN_LATIN;
		Win32LocalePeer::countryIDs["sr_CS"] = SUBLANG_SERBIAN_CYRILLIC;
		Win32LocalePeer::countryIDs["es_ES"] = SUBLANG_SPANISH;
		Win32LocalePeer::countryIDs["es_MX"] = SUBLANG_SPANISH_MEXICAN;
		Win32LocalePeer::countryIDs["es_GT"] = SUBLANG_SPANISH_GUATEMALA;
		Win32LocalePeer::countryIDs["es_CR"] = SUBLANG_SPANISH_COSTA_RICA;
		Win32LocalePeer::countryIDs["es_PA"] = SUBLANG_SPANISH_PANAMA;
		Win32LocalePeer::countryIDs["es_DO"] = SUBLANG_SPANISH_DOMINICAN_REPUBLIC;
		Win32LocalePeer::countryIDs["es_VE"] = SUBLANG_SPANISH_VENEZUELA;
		Win32LocalePeer::countryIDs["es_CO"] = SUBLANG_SPANISH_COLOMBIA;
		Win32LocalePeer::countryIDs["es_PE"] = SUBLANG_SPANISH_PERU;
		Win32LocalePeer::countryIDs["es_AR"] = SUBLANG_SPANISH_ARGENTINA;
		Win32LocalePeer::countryIDs["es_EC"] = SUBLANG_SPANISH_ECUADOR;
		Win32LocalePeer::countryIDs["es_CL"] = SUBLANG_SPANISH_CHILE;
		Win32LocalePeer::countryIDs["es_UY"] = SUBLANG_SPANISH_URUGUAY;
		Win32LocalePeer::countryIDs["es_PY"] = SUBLANG_SPANISH_PARAGUAY;
		Win32LocalePeer::countryIDs["es_BO"] = SUBLANG_SPANISH_BOLIVIA;
		Win32LocalePeer::countryIDs["es_SV"] = SUBLANG_SPANISH_EL_SALVADOR;
		Win32LocalePeer::countryIDs["es_HN"] = SUBLANG_SPANISH_HONDURAS;
		Win32LocalePeer::countryIDs["es_NI"] = SUBLANG_SPANISH_NICARAGUA;
		Win32LocalePeer::countryIDs["es_PR"] = SUBLANG_SPANISH_PUERTO_RICO;
		Win32LocalePeer::countryIDs["sv_SE"] = SUBLANG_SWEDISH;
		Win32LocalePeer::countryIDs["sv_FI"] = SUBLANG_SWEDISH_FINLAND;
		Win32LocalePeer::countryIDs["ur_IN"] = SUBLANG_URDU_INDIA;
		Win32LocalePeer::countryIDs["ur_PK"] = SUBLANG_URDU_PAKISTAN;
		Win32LocalePeer::countryIDs["uz_UZ"] = SUBLANG_UZBEK_CYRILLIC;
	}
}

void Win32LocalePeer::setToCurrentThread()
{
	lcid_ = GetThreadLocale();

#ifndef VCF_WIN32CE
	char* tmp = setlocale( LC_ALL, NULL );
	if ( NULL != tmp ) {
		crtLocaleStr_ = tmp;
	}
	else {
		crtLocaleStr_.clear();
	}
#endif
}

void Win32LocalePeer::setLocale( const UnicodeString& language, const UnicodeString& country, const UnicodeString& variant )
{
	if ( !language.empty() || !country.empty() ) {

		WORD langID = 0;
		USHORT primaryLanguage = 0;
		USHORT subLanguage = 0;
		std::map<AnsiString,int>::iterator found = Win32LocalePeer::langIDs.find( language );
		if ( found != Win32LocalePeer::langIDs.end() ) {
			primaryLanguage = found->second;
		}
		else {
			primaryLanguage = LANG_NEUTRAL;
		}

		found = Win32LocalePeer::countryIDs.find( language + "_" + country );
		if ( found != Win32LocalePeer::countryIDs.end() ) {
			subLanguage = found->second;
		}
		else {
			subLanguage = SUBLANG_DEFAULT;
		}

		lcid_ = MAKELCID( MAKELANGID(primaryLanguage,subLanguage), SORT_DEFAULT );

		crtLocaleStr_ = "";

		std::map<AnsiString,AnsiString>::iterator found2 = languageToWin32Language.find( language + "_" + country );
		if ( found2 != languageToWin32Language.end() ) {
			crtLocaleStr_ = found2->second;
		}

		found2 = countryToWin32Country.find( country );
		if ( found2 != countryToWin32Country.end() ) {
			crtLocaleStr_ += "_" + found2->second;
		}
	}


}

int Win32LocalePeer::collate( const UnicodeString& s1, const UnicodeString& s2 )
{
	int result = 0;
	int cmpRes = CSTR_EQUAL;
#ifdef VCF_WIN32CE
	cmpRes = ::CompareStringW( lcid_, 0, s1.c_str(), s1.size(), s2.c_str(), s2.size() );
#else
	if ( System::isUnicodeEnabled() ) {
		cmpRes = ::CompareStringW( lcid_, 0, s1.c_str(), s1.size(), s2.c_str(), s2.size() );
	}
	else {
		AnsiString tmp1 = s1;
		AnsiString tmp2 = s2;

		cmpRes = ::CompareStringA( lcid_, 0, tmp1.c_str(), tmp1.size(), tmp2.c_str(), tmp2.size() );
	}
#endif

	switch ( cmpRes ) {
		case CSTR_LESS_THAN : {
			result = -1;
		}
		break;

		case CSTR_EQUAL : {
			result = 0;
		}
		break;

		case CSTR_GREATER_THAN : {
			result = 1;
		}
		break;
	}

	return result;
}

int Win32LocalePeer::collateCaseInsensitive( const UnicodeString& s1, const UnicodeString& s2 )
{
	int result = 0;
#ifdef VCF_WIN32CE
	result = ::CompareStringW( lcid_, NORM_IGNORECASE, s1.c_str(), s1.size(), s2.c_str(), s2.size() );
#else
	if ( System::isUnicodeEnabled() ) {
		result = ::CompareStringW( lcid_, NORM_IGNORECASE, s1.c_str(), s1.size(), s2.c_str(), s2.size() );
	}
	else {
		AnsiString tmp1 = s1;
		AnsiString tmp2 = s2;

		result = ::CompareStringA( lcid_, NORM_IGNORECASE, tmp1.c_str(), tmp1.size(), tmp2.c_str(), tmp2.size() );
	}
#endif
	return result;
}

void Win32LocalePeer::initNumberFormatForIntW( NUMBERFMTW& fmt )
{
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_IDIGITS, tmp, 255 );
	fmt.NumDigits = 0;//atoi( tmp );
	fmt.LeadingZero = 0;
	fmt.lpDecimalSep = new VCFChar[255];
	GetLocaleInfoW( lcid_, LOCALE_SDECIMAL, fmt.lpDecimalSep, 255 );

	fmt.lpThousandSep = new VCFChar[255];
	GetLocaleInfoW( lcid_, LOCALE_STHOUSAND, fmt.lpThousandSep, 255 );

	GetLocaleInfoW( lcid_, LOCALE_INEGNUMBER, tmp, 255 );
	fmt.NegativeOrder = _wtoi( tmp );

	GetLocaleInfoW( lcid_, LOCALE_SGROUPING, tmp, 255 );

	UnicodeString s = tmp;
	size_t pos = s.find( ";" );
	if ( pos != UnicodeString::npos ) {
		//take the first group number
		UnicodeString num = s.substr( 0, pos );

		fmt.Grouping = _wtoi( num.c_str() );
	}
}

void Win32LocalePeer::initNumberFormatForIntA( NUMBERFMTA& fmt )
{
#ifndef VCF_WIN32CE
	char tmp[256];
	GetLocaleInfoA( lcid_, LOCALE_IDIGITS, tmp, 255 );
	fmt.NumDigits = 0;//atoi( tmp );
	fmt.LeadingZero = 0;
	fmt.lpDecimalSep = new char[255];
	GetLocaleInfoA( lcid_, LOCALE_SDECIMAL, fmt.lpDecimalSep, 255 );

	fmt.lpThousandSep = new char[255];
	GetLocaleInfoA( lcid_, LOCALE_STHOUSAND, fmt.lpThousandSep, 255 );

	GetLocaleInfoA( lcid_, LOCALE_INEGNUMBER, tmp, 255 );
	fmt.NegativeOrder = atoi( tmp );

	GetLocaleInfoA( lcid_, LOCALE_SGROUPING, tmp, 255 );

	AnsiString s = tmp;
	size_t pos = s.find( ";" );
	if ( pos != AnsiString::npos ) {
		//take the first group number
		AnsiString num = s.substr( 0, pos );

		fmt.Grouping = atoi( num.c_str() );
	}
#endif
}

void Win32LocalePeer::initNumberFormatForFloatW( NUMBERFMTW& fmt )
{
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_IDIGITS, tmp, 255 );
	fmt.NumDigits = _wtoi( tmp );

	GetLocaleInfoW( lcid_, LOCALE_ILZERO, tmp, 255 );
	fmt.LeadingZero = _wtoi( tmp );

	fmt.lpDecimalSep = new VCFChar[255];
	GetLocaleInfoW( lcid_, LOCALE_SDECIMAL, fmt.lpDecimalSep, 255 );

	fmt.lpThousandSep = new VCFChar[255];
	GetLocaleInfoW( lcid_, LOCALE_STHOUSAND, fmt.lpThousandSep, 255 );

	GetLocaleInfoW( lcid_, LOCALE_INEGNUMBER, tmp, 255 );
	fmt.NegativeOrder = _wtoi( tmp );

	GetLocaleInfoW( lcid_, LOCALE_SGROUPING, tmp, 255 );

	UnicodeString s = tmp;
	size_t pos = s.find( L";" );
	if ( pos != UnicodeString::npos ) {
		//take the first group number
		UnicodeString num = s.substr( 0, pos );

		fmt.Grouping = _wtoi( num.c_str() );
	}
}

void Win32LocalePeer::initNumberFormatForFloatA( NUMBERFMTA& fmt )
{
#ifndef VCF_WIN32CE
	char tmp[256];
	GetLocaleInfoA( lcid_, LOCALE_IDIGITS, tmp, 255 );
	fmt.NumDigits = atoi( tmp );

	GetLocaleInfoA( lcid_, LOCALE_ILZERO, tmp, 255 );
	fmt.LeadingZero = atoi( tmp );

	fmt.lpDecimalSep = new char[255];
	GetLocaleInfoA( lcid_, LOCALE_SDECIMAL, fmt.lpDecimalSep, 255 );

	fmt.lpThousandSep = new char[255];
	GetLocaleInfoA( lcid_, LOCALE_STHOUSAND, fmt.lpThousandSep, 255 );

	GetLocaleInfoA( lcid_, LOCALE_INEGNUMBER, tmp, 255 );
	fmt.NegativeOrder = atoi( tmp );

	GetLocaleInfoA( lcid_, LOCALE_SGROUPING, tmp, 255 );

	AnsiString s = tmp;
	size_t pos = s.find( ";" );
	if ( pos != AnsiString::npos ) {
		//take the first group number
		AnsiString num = s.substr( 0, pos );

		fmt.Grouping = atoi( num.c_str() );
	}
#endif
}

UnicodeString Win32LocalePeer::toString( const int& val )
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	memset(tmp,0,sizeof(tmp));
	swprintf( tmp, L"%d", val );
	NUMBERFMTW fmt;
	memset(&fmt,0,sizeof(fmt));

	initNumberFormatForIntW( fmt );

	int size = ::GetNumberFormatW( lcid_, 0, tmp, &fmt, NULL, 0 );
	VCFChar* numStr = new VCFChar[size+1];
	memset(numStr,0,(size+1)*sizeof(VCFChar));
	::GetNumberFormatW( lcid_, 0, tmp, &fmt, numStr, size );


	delete [] fmt.lpDecimalSep;
	delete [] fmt.lpThousandSep;

	result = numStr;

	delete [] numStr;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		memset(tmp,0,sizeof(tmp));
	#if defined(VCF_CW) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)-1, L"%d", val);
	#else
		swprintf( tmp, L"%d", val );
	#endif
		NUMBERFMTW fmt;
		memset(&fmt,0,sizeof(fmt));

		initNumberFormatForIntW( fmt );

		int size = ::GetNumberFormatW( lcid_, 0, tmp, &fmt, NULL, 0 );
		VCFChar* numStr = new VCFChar[size+1];
		memset(numStr,0,(size+1)*sizeof(VCFChar));
		::GetNumberFormatW( lcid_, 0, tmp, &fmt, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
	else {
		char tmp[256];
		memset(tmp,0,sizeof(tmp));
		sprintf( tmp, "%d", val );

		NUMBERFMTA fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForIntA( fmt );

		int size = ::GetNumberFormatA( lcid_, 0, tmp, &fmt, NULL, 0 );
		char* numStr = new char[size+1];
		memset(numStr,0,(size+1)*sizeof(char));
		::GetNumberFormatA( lcid_, 0, tmp, &fmt, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::toString( const unsigned int& val )
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	memset(tmp,0,sizeof(tmp));
	swprintf( tmp, L"%d", val );

	NUMBERFMTW fmt;
	memset(&fmt,0,sizeof(fmt));
	initNumberFormatForIntW( fmt );

	int size = ::GetNumberFormatW( lcid_, 0, tmp, &fmt, NULL, 0 );
	VCFChar* numStr = new VCFChar[size+1];
	memset(numStr,0,(size+1)*sizeof(VCFChar));
	::GetNumberFormatW( lcid_, 0, tmp, &fmt, numStr, size );


	delete [] fmt.lpDecimalSep;
	delete [] fmt.lpThousandSep;

	result = numStr;

	delete [] numStr;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		memset(tmp,0,sizeof(tmp));
	#if defined(VCF_CW) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)-1, L"%d", val);
	#else
		swprintf( tmp, L"%d", val );
	#endif
		NUMBERFMTW fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForIntW( fmt );

		int size = ::GetNumberFormatW( lcid_, 0, tmp, &fmt, NULL, 0 );
		VCFChar* numStr = new VCFChar[size+1];
		memset(numStr,0,(size+1)*sizeof(VCFChar));
		::GetNumberFormatW( lcid_, 0, tmp, &fmt, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
	else {
		char tmp[256];
		memset(tmp,0,sizeof(tmp));
		sprintf( tmp, "%d", val );

		NUMBERFMTA fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForIntA( fmt );

		int size = ::GetNumberFormatA( lcid_, 0, tmp, &fmt, NULL, 0 );
		char* numStr = new char[size+1];
		memset(numStr,0,(size+1)*sizeof(char));
		::GetNumberFormatA( lcid_, 0, tmp, &fmt, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::toString( const long& val )
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];;
	memset(tmp,0,sizeof(tmp));
	swprintf( tmp, L"%d", val );
	NUMBERFMTW fmt;
	memset(&fmt,0,sizeof(fmt));
	initNumberFormatForIntW( fmt );

	int size = ::GetNumberFormatW( lcid_, 0, tmp, &fmt, NULL, 0 );
	VCFChar* numStr = new VCFChar[size+1];
	memset(numStr,0,(size+1)*sizeof(VCFChar));
	::GetNumberFormatW( lcid_, 0, tmp, &fmt, numStr, size );


	delete [] fmt.lpDecimalSep;
	delete [] fmt.lpThousandSep;

	result = numStr;

	delete [] numStr;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];;
		memset(tmp,0,sizeof(tmp));
	#if defined(VCF_CW) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)-1, L"%d", val);
	#else
		swprintf( tmp, L"%d", val );
	#endif
		NUMBERFMTW fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForIntW( fmt );

		int size = ::GetNumberFormatW( lcid_, 0, tmp, &fmt, NULL, 0 );
		VCFChar* numStr = new VCFChar[size+1];
		memset(numStr,0,(size+1)*sizeof(VCFChar));
		::GetNumberFormatW( lcid_, 0, tmp, &fmt, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
	else {
		char tmp[256];;
		memset(tmp,0,sizeof(tmp));
		sprintf( tmp, "%d", val );

		NUMBERFMTA fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForIntA( fmt );

		int size = ::GetNumberFormatA( lcid_, 0, tmp, &fmt, NULL, 0 );
		char* numStr = new char[size+1];
		memset(numStr,0,(size+1)*sizeof(char));
		::GetNumberFormatA( lcid_, 0, tmp, &fmt, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::toString( const unsigned long& val )
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];;
	memset(tmp,0,sizeof(tmp));
	swprintf( tmp, L"%d", val );
	NUMBERFMTW fmt;
	memset(&fmt,0,sizeof(fmt));
	initNumberFormatForIntW( fmt );

	int size = ::GetNumberFormatW( lcid_, 0, tmp, &fmt, NULL, 0 );
	VCFChar* numStr = new VCFChar[size+1];
	memset(numStr,0,(size+1)*sizeof(VCFChar));
	::GetNumberFormatW( lcid_, 0, tmp, &fmt, numStr, size );


	delete [] fmt.lpDecimalSep;
	delete [] fmt.lpThousandSep;

	result = numStr;

	delete [] numStr;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];;
		memset(tmp,0,sizeof(tmp));
	#if defined(VCF_CW) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)-1, L"%d", val);
	#else
		swprintf( tmp, L"%d", val );
	#endif
		NUMBERFMTW fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForIntW( fmt );

		int size = ::GetNumberFormatW( lcid_, 0, tmp, &fmt, NULL, 0 );
		VCFChar* numStr = new VCFChar[size+1];
		memset(numStr,0,(size+1)*sizeof(VCFChar));
		::GetNumberFormatW( lcid_, 0, tmp, &fmt, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
	else {
		char tmp[256];;
		memset(tmp,0,sizeof(tmp));
		sprintf( tmp, "%d", val );

		NUMBERFMTA fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForIntA( fmt );

		int size = ::GetNumberFormatA( lcid_, 0, tmp, &fmt, NULL, 0 );
		char* numStr = new char[size+1];
		memset(numStr,0,(size+1)*sizeof(char));
		::GetNumberFormatA( lcid_, 0, tmp, &fmt, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
#endif

	return result;
}

UnicodeString Win32LocalePeer::toString( const double& val )
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	memset(tmp,0,sizeof(tmp));
	swprintf( tmp, L"%.08f", val );

	NUMBERFMTW fmt;
	memset(&fmt,0,sizeof(fmt));
	initNumberFormatForFloatW( fmt );

	int size = ::GetNumberFormatW( lcid_, 0, tmp, NULL, NULL, 0 );
	VCFChar* numStr = new VCFChar[size+1];
	memset(numStr,0,(size+1)*sizeof(VCFChar));
	::GetNumberFormatW( lcid_, 0, tmp, NULL, numStr, size );


	delete [] fmt.lpDecimalSep;
	delete [] fmt.lpThousandSep;

	result = numStr;

	delete [] numStr;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		memset(tmp,0,sizeof(tmp));
	#if defined(VCF_CW) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)-1, L"%.08f", val );
	#else
		swprintf( tmp, L"%.08f", val );
	#endif
		NUMBERFMTW fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForFloatW( fmt );

		int size = ::GetNumberFormatW( lcid_, 0, tmp, NULL, NULL, 0 );
		VCFChar* numStr = new VCFChar[size+1];
		memset(numStr,0,(size+1)*sizeof(VCFChar));
		::GetNumberFormatW( lcid_, 0, tmp, NULL, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
	else {
		char tmp[256];
		memset(tmp,0,sizeof(tmp));
		sprintf( tmp, "%.08f", val );

		NUMBERFMTA fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForFloatA( fmt );

		int size = ::GetNumberFormatA( lcid_, 0, tmp, NULL, NULL, 0 );
		char* numStr = new char[size+1];
		memset(numStr,0,(size+1)*sizeof(char));
		::GetNumberFormatA( lcid_, 0, tmp, NULL, numStr, size );


		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;

		result = numStr;

		delete [] numStr;
	}
#endif
	return result;
}


UnicodeString Win32LocalePeer::toString( const float& val )
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	memset(tmp,0,sizeof(tmp));
	swprintf( tmp, L"%.08f", val );
	NUMBERFMTW fmt;
	memset(&fmt,0,sizeof(fmt));
	initNumberFormatForFloatW( fmt );

	int size = ::GetNumberFormatW( lcid_, 0, tmp, NULL, NULL, 0 );
	VCFChar* numStr = new VCFChar[size+1];
	memset(numStr,0,(size+1)*sizeof(VCFChar));
	::GetNumberFormatW( lcid_, 0, tmp, NULL, numStr, size );

	delete [] fmt.lpDecimalSep;
	delete [] fmt.lpThousandSep;


	result = numStr;

	delete [] numStr;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		memset(tmp,0,sizeof(tmp));
	#if defined(VCF_CW) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)-1, L"%.08f", val );
	#else
		swprintf( tmp, L"%.08f", val );
	#endif
		NUMBERFMTW fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForFloatW( fmt );

		int size = ::GetNumberFormatW( lcid_, 0, tmp, NULL, NULL, 0 );
		VCFChar* numStr = new VCFChar[size+1];
		memset(numStr,0,(size+1)*sizeof(VCFChar));
		::GetNumberFormatW( lcid_, 0, tmp, NULL, numStr, size );

		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;


		result = numStr;

		delete [] numStr;
	}
	else {
		char tmp[256];
		memset(tmp,0,sizeof(tmp));
		sprintf( tmp, "%.08f", val );

		NUMBERFMTA fmt;
		memset(&fmt,0,sizeof(fmt));
		initNumberFormatForFloatA( fmt );

		int size = ::GetNumberFormatA( lcid_, 0, tmp, NULL, NULL, 0 );
		char* numStr = new char[size+1];
		memset(numStr,0,(size+1)*sizeof(char));
		::GetNumberFormatA( lcid_, 0, tmp, NULL, numStr, size );

		delete [] fmt.lpDecimalSep;
		delete [] fmt.lpThousandSep;


		result = numStr;

		delete [] numStr;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::toStringFromCurrency( const double& val )
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	memset(tmp,0,sizeof(tmp));
	swprintf( tmp, L"%.08f", val );
	int size = ::GetCurrencyFormatW( lcid_, 0, tmp, NULL, NULL, 0 );
	VCFChar* numStr = new VCFChar[size+1];
	memset(numStr,0,(size+1)*sizeof(VCFChar));
	::GetCurrencyFormatW( lcid_, 0, tmp, NULL, numStr, size );

	result = numStr;

	delete [] numStr;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		memset(tmp,0,sizeof(tmp));
	#if defined(VCF_CW) || defined(VCF_DMC)
		swprintf( tmp, sizeof(tmp)-1, L"%.08f", val );
	#else
		swprintf( tmp, L"%.08f", val );
	#endif
		int size = ::GetCurrencyFormatW( lcid_, 0, tmp, NULL, NULL, 0 );
		VCFChar* numStr = new VCFChar[size+1];
		memset(numStr,0,(size+1)*sizeof(VCFChar));
		::GetCurrencyFormatW( lcid_, 0, tmp, NULL, numStr, size );

		result = numStr;

		delete [] numStr;
	}
	else {
		char tmp[256];
		memset(tmp,0,sizeof(tmp));
		sprintf( tmp, "%.08f", val );

		int size = ::GetCurrencyFormatA( lcid_, 0, tmp, NULL, NULL, 0 );
		char* numStr = new char[size+1];
		memset(numStr,0,(size+1)*sizeof(char));
		::GetCurrencyFormatA( lcid_, 0, tmp, NULL, numStr, size );


		result = numStr;

		delete [] numStr;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::changeToGenericNumberString( const UnicodeString& str )
{
	UnicodeString result = str;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	int err = GetLocaleInfoW( lcid_, LOCALE_SDECIMAL, tmp, 255 );
	UnicodeString s = tmp;


	size_t pos = result.find( s );
	if ( pos != UnicodeString::npos ) {
		result = result.erase( pos, s.size() );
		result = result.insert( pos, L"." );
	}

	err = GetLocaleInfoW( lcid_, LOCALE_STHOUSAND, tmp, 255 );



	if ( 0 == err ) {
		err = GetLastError();
	}
	s = tmp;
	pos = result.find( s );
	while ( pos != UnicodeString::npos ) {
		result = result.erase( pos, s.size() );
		pos = result.find( s );
	}
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		int err = GetLocaleInfoW( lcid_, LOCALE_SDECIMAL, tmp, 255 );
		UnicodeString s = tmp;


		size_t pos = result.find( s );
		if ( pos != UnicodeString::npos ) {
			result = result.erase( pos, s.size() );
			result = result.insert( pos, L"." );
		}

		err = GetLocaleInfoW( lcid_, LOCALE_STHOUSAND, tmp, 255 );



		if ( 0 == err ) {
			err = GetLastError();
		}
		s = tmp;
		pos = result.find( s );
		while ( pos != UnicodeString::npos ) {
			result = result.erase( pos, s.size() );
			pos = result.find( s );
		}
	}
	else {
		char tmp[256];
		int err = GetLocaleInfoA( lcid_, LOCALE_SDECIMAL, tmp, 255 );
		AnsiString s = tmp;

		AnsiString tmpRes = result;
		size_t pos = tmpRes.find( s );
		if ( pos != AnsiString::npos ) {
			tmpRes = tmpRes.erase( pos, s.size() );
			tmpRes = tmpRes.insert( pos, "." );
		}

		err = GetLocaleInfoA( lcid_, LOCALE_STHOUSAND, tmp, 255 );



		if ( 0 == err ) {
			err = GetLastError();
		}
		s = tmp;
		pos = tmpRes.find( s );
		while ( pos != AnsiString::npos ) {
			tmpRes = tmpRes.erase( pos, s.size() );
			pos = tmpRes.find( s );
		}

		result = tmpRes;
	}
#endif


	return result;
}


int Win32LocalePeer::toInt( const UnicodeString& str )
{
	int result;

	if ( System::isUnicodeEnabled() ) {
		float f = 0.0f;
		swscanf( changeToGenericNumberString(str).c_str(), L"%f", &f );
		result = f;
	}
	else {
		double tmpRes = 0.0;
		tmpRes = atof( changeToGenericNumberString(str).ansi_c_str() );
		result = tmpRes;
	}

	return result;
}

unsigned int Win32LocalePeer::toUInt( const UnicodeString& str )
{
	unsigned int result;

	if ( System::isUnicodeEnabled() ) {
		float f = 0.0f;
		swscanf( changeToGenericNumberString(str).c_str(), L"%f", &f );
		result = f;
	}
	else {
		double tmpRes = 0.0;
		tmpRes = atof( changeToGenericNumberString(str).ansi_c_str() );
		result = tmpRes;
	}

	return result;
}

double Win32LocalePeer::toDouble( const UnicodeString& str )
{
	double result;

	if ( System::isUnicodeEnabled() ) {
		result = wcstod( changeToGenericNumberString(str).c_str(), NULL );
	}
	else {
		result = atof( changeToGenericNumberString(str).ansi_c_str() );
	}

	return result;
}

float Win32LocalePeer::toFloat( const UnicodeString& str )
{
	float result;

	if ( System::isUnicodeEnabled() ) {
		result = (float)wcstod( changeToGenericNumberString(str).c_str(), NULL );
		//swscanf( changeToGenericNumberString(str).c_str(), L"%f", &result );
	}
	else {
		result = atof( changeToGenericNumberString(str).ansi_c_str() );
	}


	return result;
}

double Win32LocalePeer::toDoubleAsCurrency( const UnicodeString& str )
{
	double result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_SMONDECIMALSEP, tmp, 255 );
	UnicodeString s = tmp;

	UnicodeString s2 = str;
	size_t pos = s2.find( s );
	if ( pos != UnicodeString::npos ) {
		s2 = s2.erase( pos, s.size() );
		s2 = s2.insert( pos, L"." );
	}

	GetLocaleInfoW( lcid_, LOCALE_SMONTHOUSANDSEP, tmp, 255 );
	s = tmp;
	pos = s2.find( s );
	while ( pos != UnicodeString::npos ) {
		s2 = s2.erase( pos, s.size() );
		pos = s2.find( s );
	}


	GetLocaleInfoW( lcid_, LOCALE_SCURRENCY, tmp, 255 );
	s = tmp;
	pos = s2.find( s );
	while ( pos != UnicodeString::npos ) {
		s2 = s2.erase( pos, s.size() );
		pos = s2.find( s );
	}

	float f = 0.0f;
	swscanf( s2.c_str(), L"%f", &f );
	result = f;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_SMONDECIMALSEP, tmp, 255 );
		UnicodeString s = tmp;

		UnicodeString s2 = str;
		size_t pos = s2.find( s );
		if ( pos != UnicodeString::npos ) {
			s2 = s2.erase( pos, s.size() );
			s2 = s2.insert( pos, L"." );
		}

		GetLocaleInfoW( lcid_, LOCALE_SMONTHOUSANDSEP, tmp, 255 );
		s = tmp;
		pos = s2.find( s );
		while ( pos != UnicodeString::npos ) {
			s2 = s2.erase( pos, s.size() );
			pos = s2.find( s );
		}


		GetLocaleInfoW( lcid_, LOCALE_SCURRENCY, tmp, 255 );
		s = tmp;
		pos = s2.find( s );
		while ( pos != UnicodeString::npos ) {
			s2 = s2.erase( pos, s.size() );
			pos = s2.find( s );
		}

		float f = 0.0f;
		swscanf( s2.c_str(), L"%f", &f );
		result = f;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_SMONDECIMALSEP, tmp, 255 );
		AnsiString s = tmp;

		AnsiString s2 = str;
		size_t pos = s2.find( s );
		if ( pos != AnsiString::npos ) {
			s2 = s2.erase( pos, s.size() );
			s2 = s2.insert( pos, "." );
		}

		GetLocaleInfoA( lcid_, LOCALE_SMONTHOUSANDSEP, tmp, 255 );
		s = tmp;
		pos = s2.find( s );
		while ( pos != AnsiString::npos ) {
			s2 = s2.erase( pos, s.size() );
			pos = s2.find( s );
		}


		GetLocaleInfoA( lcid_, LOCALE_SCURRENCY, tmp, 255 );
		s = tmp;
		pos = s2.find( s );
		while ( pos != AnsiString::npos ) {
			s2 = s2.erase( pos, s.size() );
			pos = s2.find( s );
		}


		result = atof( s2.c_str() );
	}
#endif
	return result;
}



UnicodeString Win32LocalePeer::toLowerCase( const UnicodeString& s )
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	int size = LCMapStringW( lcid_, LCMAP_LOWERCASE, s.c_str(), s.size(), NULL, 0 );

	VCFChar* tmp = new VCFChar[size+1];
	memset( tmp, 0, (size+1) * sizeof(VCFChar));

	LCMapStringW( lcid_, LCMAP_LOWERCASE, s.c_str(), s.size(), tmp, size );

	result = tmp;

	delete [] tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		int size = LCMapStringW( lcid_, LCMAP_LOWERCASE, s.c_str(), s.size(), NULL, 0 );

		VCFChar* tmp = new VCFChar[size+1];
		memset( tmp, 0, (size+1) * sizeof(VCFChar));

		LCMapStringW( lcid_, LCMAP_LOWERCASE, s.c_str(), s.size(), tmp, size );

		result = tmp;

		delete [] tmp;
	}
	else {

		const char* ansiStr = s.ansi_c_str();
		int ansiSize = strlen(ansiStr);

		int size = LCMapStringA( lcid_, LCMAP_LOWERCASE, ansiStr, ansiSize, NULL, 0 );

		char* tmp = new char[size+1];
		memset( tmp, 0, (size+1)*sizeof(char));

		LCMapStringA( lcid_, LCMAP_LOWERCASE, ansiStr, ansiSize, tmp, size );

		result = tmp;

		delete [] tmp;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::toUpperCase( const UnicodeString& s )
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	int size = LCMapStringW( lcid_, LCMAP_UPPERCASE, s.c_str(), s.size(), NULL, 0 );

	VCFChar* tmp = new VCFChar[size+1];
	memset( tmp, 0, (size+1) * sizeof(VCFChar));

	LCMapStringW( lcid_, LCMAP_UPPERCASE, s.c_str(), s.size(), tmp, size );

	result = tmp;

	delete [] tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		int size = LCMapStringW( lcid_, LCMAP_UPPERCASE, s.c_str(), s.size(), NULL, 0 );

		VCFChar* tmp = new VCFChar[size+1];
		memset( tmp, 0, (size+1) * sizeof(VCFChar));

		LCMapStringW( lcid_, LCMAP_UPPERCASE, s.c_str(), s.size(), tmp, size );

		result = tmp;

		delete [] tmp;
	}
	else {

		const char* ansiStr = s.ansi_c_str();
		int ansiSize = strlen(ansiStr);

		int size = LCMapStringA( lcid_, LCMAP_UPPERCASE, ansiStr, ansiSize, NULL, 0 );

		char* tmp = new char[size+1];
		memset( tmp, 0, (size+1)*sizeof(char));

		LCMapStringA( lcid_, LCMAP_UPPERCASE, ansiStr, ansiSize, tmp, size );

		result = tmp;

		delete [] tmp;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::getNumberThousandsSeparator()
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_STHOUSAND, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_STHOUSAND, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_STHOUSAND, tmp, 255 );
		result = tmp;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::getNumberDecimalPoint()
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_SDECIMAL, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_SDECIMAL, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_SDECIMAL, tmp, 255 );
		result = tmp;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::getNumberGrouping()
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_SGROUPING, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_SGROUPING, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_SGROUPING, tmp, 255 );
		result = tmp;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::getCurrencyDecimalPoint()
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_SMONDECIMALSEP, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_SMONDECIMALSEP, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_SMONDECIMALSEP, tmp, 255 );
		result = tmp;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::getCurrencyThousandsSeparator()
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_SMONTHOUSANDSEP, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_SMONTHOUSANDSEP, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_SMONTHOUSANDSEP, tmp, 255 );
		result = tmp;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::getCurrencySymbol()
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_SCURRENCY, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_SCURRENCY, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_SCURRENCY, tmp, 255 );
		result = tmp;
	}
#endif
	return result;
}

int Win32LocalePeer::getCurrencyFractionalDigits()
{
	int result = 0;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_ICURRDIGITS, tmp, 255 );
	result = _wtoi(tmp);
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_ICURRDIGITS, tmp, 255 );
		result = _wtoi(tmp);
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_ICURRDIGITS, tmp, 255 );
		result = atoi(tmp);
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::getCurrencyPositiveSign()
{
	UnicodeString result;
#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_SCURRENCY, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_SCURRENCY, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_SCURRENCY, tmp, 255 );
		result = tmp;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::getCurrencyNegativeSign()
{
	UnicodeString result;

	#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_SNEGATIVESIGN, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_SNEGATIVESIGN, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_SNEGATIVESIGN, tmp, 255 );
		result = tmp;
	}
#endif

	return result;
}

UnicodeString Win32LocalePeer::getAMSymbol()
{
	UnicodeString result;

#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_S1159, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_S1159, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_S1159, tmp, 255 );
		result = tmp;
	}
#endif

	return result;
}

UnicodeString Win32LocalePeer::getPMSymbol()
{
	UnicodeString result;

#ifdef VCF_WIN32CE
	VCFChar tmp[256];
	GetLocaleInfoW( lcid_, LOCALE_S2359, tmp, 255 );
	result = tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		VCFChar tmp[256];
		GetLocaleInfoW( lcid_, LOCALE_S2359, tmp, 255 );
		result = tmp;
	}
	else {
		char tmp[256];
		GetLocaleInfoA( lcid_, LOCALE_S2359, tmp, 255 );
		result = tmp;
	}
#endif

	return result;
}

bool Win32LocalePeer::isCharA( const int32& charTypeMask, const VCFChar& c )
{
	int32 mask = 0;

#ifdef VCF_WIN32CE
	if ( charTypeMask & ctSpace ) {
		if ( iswspace( c ) ) {
			mask |= ctSpace;
		}
	}

	if ( charTypeMask & ctPrint ) {
		if ( iswprint( c ) ) {
			mask |= ctPrint;
		}
	}

	if ( charTypeMask & ctCntrl ) {
		if ( iswprint( c ) ) {
			mask |= ctCntrl;
		}
	}

	if ( charTypeMask & ctCntrl ) {
		if ( iswcntrl( c ) ) {
			mask |= ctCntrl;
		}
	}

	if ( charTypeMask & ctUpper ) {
		if ( iswupper( c ) ) {
			mask |= ctUpper;
		}
	}

	if ( charTypeMask & ctLower ) {
		if ( iswlower( c ) ) {
			mask |= ctLower;
		}
	}

	if ( charTypeMask & ctDigit ) {
		if ( iswdigit( c ) ) {
			mask |= ctDigit;
		}
	}

	if ( charTypeMask & ctPunct ) {
		if ( iswpunct( c ) ) {
			mask |= ctPunct;
		}
	}

	if ( charTypeMask & ctHexDigit ) {
		if ( iswxdigit( c ) ) {
			mask |= ctHexDigit;
		}
	}

	if ( charTypeMask & ctAlpha ) {
		if ( iswalpha( c ) ) {
			mask |= ctAlpha;
		}
	}

	if ( charTypeMask & ctAlphaNumeric ) {
		if ( iswalnum( c ) ) {
			mask |= ctAlphaNumeric;
		}
	}

	if ( charTypeMask & ctGraph ) {
		if ( iswgraph( c ) ) {
			mask |= ctGraph;
		}
	}
#else

	UnicodeString oldLocaleStr;


	if ( System::isUnicodeEnabled() ) {

	#ifdef VCF_CW
		oldLocaleStr = setlocale( LC_CTYPE, NULL );

		setlocale( LC_CTYPE, crtLocaleStr_.ansi_c_str() );
	#else

		if ( crtLocaleStr_.empty() ) {
			crtLocaleStr_ = setlocale( LC_ALL, NULL );
		}

		oldLocaleStr = _wsetlocale( LC_CTYPE, NULL );

		UnicodeString tmp(crtLocaleStr_);
		_wsetlocale( LC_CTYPE, tmp.c_str() );
	#endif

		if ( charTypeMask & ctSpace ) {
			if ( iswspace( c ) ) {
				mask |= ctSpace;
			}
		}

		if ( charTypeMask & ctPrint ) {
			if ( iswprint( c ) ) {
				mask |= ctPrint;
			}
		}

		if ( charTypeMask & ctCntrl ) {
			if ( iswprint( c ) ) {
				mask |= ctCntrl;
			}
		}

		if ( charTypeMask & ctCntrl ) {
			if ( iswcntrl( c ) ) {
				mask |= ctCntrl;
			}
		}

		if ( charTypeMask & ctUpper ) {
			if ( iswupper( c ) ) {
				mask |= ctUpper;
			}
		}

		if ( charTypeMask & ctLower ) {
			if ( iswlower( c ) ) {
				mask |= ctLower;
			}
		}

		if ( charTypeMask & ctDigit ) {
			if ( iswdigit( c ) ) {
				mask |= ctDigit;
			}
		}

		if ( charTypeMask & ctPunct ) {
			if ( iswpunct( c ) ) {
				mask |= ctPunct;
			}
		}

		if ( charTypeMask & ctHexDigit ) {
			if ( iswxdigit( c ) ) {
				mask |= ctHexDigit;
			}
		}

		if ( charTypeMask & ctAlpha ) {
			if ( iswalpha( c ) ) {
				mask |= ctAlpha;
			}
		}

		if ( charTypeMask & ctAlphaNumeric ) {
			if ( iswalnum( c ) ) {
				mask |= ctAlphaNumeric;
			}
		}

		if ( charTypeMask & ctGraph ) {
			if ( iswgraph( c ) ) {
				mask |= ctGraph;
			}
		}

	#ifdef VCF_CW
		setlocale( LC_CTYPE, oldLocaleStr.ansi_c_str() );
	#else
		_wsetlocale( LC_CTYPE, oldLocaleStr.c_str() );
	#endif
	}
	else {
		oldLocaleStr = setlocale( LC_CTYPE, NULL );

		setlocale( LC_CTYPE, crtLocaleStr_.c_str() );

		if ( charTypeMask & ctSpace ) {
			if ( isspace( c ) ) {
				mask |= ctSpace;
			}
		}

		if ( charTypeMask & ctPrint ) {
			if ( isprint( c ) ) {
				mask |= ctPrint;
			}
		}

		if ( charTypeMask & ctCntrl ) {
			if ( isprint( c ) ) {
				mask |= ctCntrl;
			}
		}

		if ( charTypeMask & ctCntrl ) {
			if ( iscntrl( c ) ) {
				mask |= ctCntrl;
			}
		}

		if ( charTypeMask & ctUpper ) {
			if ( isupper( c ) ) {
				mask |= ctUpper;
			}
		}

		if ( charTypeMask & ctLower ) {
			if ( islower( c ) ) {
				mask |= ctLower;
			}
		}

		if ( charTypeMask & ctDigit ) {
			if ( isdigit( c ) ) {
				mask |= ctDigit;
			}
		}

		if ( charTypeMask & ctPunct ) {
			if ( ispunct( c ) ) {
				mask |= ctPunct;
			}
		}

		if ( charTypeMask & ctHexDigit ) {
			if ( isxdigit( c ) ) {
				mask |= ctHexDigit;
			}
		}

		if ( charTypeMask & ctAlpha ) {
			if ( isalpha( c ) ) {
				mask |= ctAlpha;
			}
		}

		if ( charTypeMask & ctAlphaNumeric ) {
			if ( isalnum( c ) ) {
				mask |= ctAlphaNumeric;
			}
		}

		if ( charTypeMask & ctGraph ) {
			if ( isgraph( c ) ) {
				mask |= ctGraph;
			}
		}

		setlocale( LC_CTYPE, oldLocaleStr.ansi_c_str() );
	}
#endif

	return (0 == mask) ? false : true;
}

UnicodeString Win32LocalePeer::translate( const UnicodeString& id )
{
	return "";
}


#include "vcf/FoundationKit/Win32_DTUtils.h"




DateTime Win32LocalePeer::toDateTime( const UnicodeString& str, const String& format )
{
	DateTimeParser parser(this);

	DateTime result = parser.parse( str, format );
/*
	OLECHAR* tmp = new OLECHAR[str.size()+1];
	memset( tmp, 0, sizeof(OLECHAR) * str.size()+1 );

	str.copy( tmp, str.size() );

	DATE d;
	VarDateFromStr( tmp, lcid_, 0, &d );

	delete [] tmp;


	DateTimeFromOleDate( d, result );
	*/


	return result;
}

UnicodeString Win32LocalePeer::toStringFromDate( const DateTime& val, const UnicodeString& format )
{
	UnicodeString result;

	uint32 y = val.getYear();
	if ( ( y < 1601 ) || ( 30827 < y ) ) {
		throw RuntimeException( "The SYSTEMTIME structure doesn't allow dates outside the range [1601,30827]" );
	}

	SYSTEMTIME timeVal;
	memset(&timeVal,0,sizeof(timeVal));

	timeVal.wYear = y;
	timeVal.wMonth = val.getMonth();
	timeVal.wDay = val.getDay();
	timeVal.wDayOfWeek = val.getWeekDay();

	int size = 0;
	DWORD flags = (!format.empty()) ? 0 : LOCALE_NOUSEROVERRIDE;

	#ifdef VCF_WIN32CE
	const VCFChar* formatStr = NULL;
	if ( !format.empty() ) {
		formatStr = format.c_str();
	}

	size = GetDateFormatW( lcid_, flags, &timeVal, formatStr, NULL, 0 );
	VCFChar* dateStr = new VCFChar[size+1];
	memset(dateStr,0,(size+1)*sizeof(VCFChar));


	GetDateFormatW( lcid_, flags, &timeVal, formatStr, dateStr, size );

	result = dateStr;

	delete [] dateStr;
#else
	if ( System::isUnicodeEnabled() ) {
		const VCFChar* formatStr = NULL;
		if ( !format.empty() ) {
			formatStr = format.c_str();
		}

		size = GetDateFormatW( lcid_, flags, &timeVal, formatStr, NULL, 0 );
		VCFChar* dateStr = new VCFChar[size+1];
		memset(dateStr,0,(size+1)*sizeof(VCFChar));


		GetDateFormatW( lcid_, flags, &timeVal, formatStr, dateStr, size );

		result = dateStr;

		delete [] dateStr;
	}
	else {
		const char* formatStr = NULL;
		if ( !format.empty() ) {
			formatStr = format.ansi_c_str();
		}

		size = GetDateFormatA( lcid_, flags, &timeVal, formatStr, NULL, 0 );
		char* dateStr = new char[size+1];
		memset(dateStr,0,(size+1)*sizeof(char));


		GetDateFormatA( lcid_, flags, &timeVal, formatStr, dateStr, size );

		result = dateStr;

		delete [] dateStr;
	}
#endif
	return result;
}

UnicodeString Win32LocalePeer::toStringFromTime( const DateTime& val, const UnicodeString& format )
{
	UnicodeString result;

	SYSTEMTIME timeVal;
	memset(&timeVal,0,sizeof(timeVal));

	uint32 y, m, d, h, min, s, ms;
	val.get( &y, &m, &d, &h, &min, &s, &ms );

	if ( ( y < 1601 ) || ( 30827 < y ) ) {
		throw BasicException( "The SYSTEMTIME structure doesn't allow dates outside the range [1601,30827]" );
	}

	timeVal.wYear   = y;
	timeVal.wMonth  = m;
	timeVal.wDayOfWeek = val.getWeekDay();
	timeVal.wDay    = d;
	timeVal.wHour   = h;
	timeVal.wMinute = min;
	timeVal.wSecond = s;
	timeVal.wMilliseconds = ms;


	DWORD flags = (!format.empty()) ? 0 : LOCALE_NOUSEROVERRIDE;
#ifdef VCF_WIN32CE
	const VCFChar* formatStr = NULL;
	if ( !format.empty() ) {
		formatStr = format.c_str();
	}

	int size = GetTimeFormatW( lcid_, flags, &timeVal, formatStr, NULL, 0 );
	VCFChar* dateStr = new VCFChar[size+1];
	memset(dateStr,0,(size+1)*sizeof(VCFChar));


	GetTimeFormatW( lcid_, flags, &timeVal, formatStr, dateStr, size );

	result = dateStr;

	delete [] dateStr;
#else
	if ( System::isUnicodeEnabled() ) {
		const VCFChar* formatStr = NULL;
		if ( !format.empty() ) {
			formatStr = format.c_str();
		}

		int size = GetTimeFormatW( lcid_, flags, &timeVal, formatStr, NULL, 0 );
		VCFChar* dateStr = new VCFChar[size+1];
		memset(dateStr,0,(size+1)*sizeof(VCFChar));


		GetTimeFormatW( lcid_, flags, &timeVal, formatStr, dateStr, size );

		result = dateStr;

		delete [] dateStr;
	}
	else {
		const char* formatStr = NULL;
		if ( !format.empty() ) {
			formatStr = format.ansi_c_str();
		}

		int size = GetTimeFormatA( lcid_, flags, &timeVal, formatStr, NULL, 0 );
		char* dateStr = new char[size+1];
		memset(dateStr,0,(size+1)*sizeof(char));


		GetTimeFormatA( lcid_, flags, &timeVal, formatStr, dateStr, size );

		result = dateStr;

		delete [] dateStr;
	}
#endif

	return result;
}

uint32 Win32LocalePeer::getLanguageCode()
{
	UINT languageID = PRIMARYLANGID(LANGIDFROMLCID(lcid_));
	UINT subLangID = SUBLANGID(LANGIDFROMLCID(lcid_));

	switch ( languageID ) {

		case LANG_AFRIKAANS : {
			return Locale::lcAfrikaans;
		}
		break;

		case LANG_ALBANIAN : {
			return Locale::lcAlbanian;
		}
		break;


		case LANG_ARABIC : {
			return Locale::lcArabic;
		}
		break;

		case LANG_ASSAMESE : {
			return Locale::lcAssamese;
		}
		break;

		case LANG_ARMENIAN : {
			return Locale::lcArmenian;
		}
		break;

		case LANG_AZERI : {
			return Locale::lcAzerbaijani;
		}
		break;

		case LANG_BASQUE : {
			return Locale::lcBasque;
		}
		break;


		case LANG_BELARUSIAN : {
			return Locale::lcBelarusian;
		}
		break;

		case LANG_BENGALI : {
			return Locale::lcBengali;
		}
		break;


		case LANG_BULGARIAN : {
			return Locale::lcBulgarian;
		}
		break;

		case LANG_CATALAN : {
			return Locale::lcCatalan;
		}
		break;

		case LANG_CHINESE : {
			return Locale::lcChinese;
		}
		break;

		case LANG_CROATIAN : { // equivalent to LANG_SERBIAN in winnt.h
			return Locale::lcSerbian; //??? Is this right???
		}
		break;

		case LANG_CZECH : {
			return Locale::lcCzech;
		}
		break;

		case LANG_DANISH : {
			return Locale::lcDanish;
		}
		break;

		case LANG_DUTCH : {
			return Locale::lcDutch;
		}
		break;


		case LANG_ENGLISH : {
			return Locale::lcEnglish;
		}
		break;

		case LANG_ESTONIAN : {
			return Locale::lcEstonian;
		}
		break;

		case LANG_FAEROESE : {
			return Locale::lcFaroese;
		}
		break;

		case LANG_FARSI : {
			return Locale::lcPersian; //?? do we need others ? Afghanistan??
		}
		break;

		case LANG_FINNISH : {
			return Locale::lcFinnish;
		}
		break;

		case LANG_FRENCH : {
			return Locale::lcFrench;
		}
		break;

		case LANG_GEORGIAN : {
			return Locale::lcGeorgian;
		}
		break;

		case LANG_GERMAN : {
			return Locale::lcGerman;
		}
		break;

		case LANG_GREEK : {
			return Locale::lcGreek;
		}
		break;

		case LANG_GUJARATI : {
			return Locale::lcGujarati;
		}
		break;

		case LANG_HEBREW : {
			return Locale::lcHebrew;
		}
		break;

		case LANG_HINDI : {
			return Locale::lcHindi;
		}
		break;

		case LANG_HUNGARIAN : {
			return Locale::lcHungarian;
		}
		break;

		case LANG_ICELANDIC : {
			return Locale::lcIcelandic;
		}
		break;

		case LANG_INDONESIAN : {
			return Locale::lcIndonesian;
		}
		break;

		case LANG_ITALIAN : {
			return Locale::lcItalian;
		}
		break;

		case LANG_JAPANESE : {
			return Locale::lcJapanese;
		}
		break;

		case LANG_KANNADA : {
			return Locale::lcKannada;
		}
		break;

		case LANG_KASHMIRI : {
			return Locale::lcKashmiri;
		}
		break;

		case LANG_KAZAK : {
			return Locale::lcKazakh;
		}
		break;

		case LANG_KOREAN : {
			return Locale::lcKorean;
		}
		break;




		case LANG_LATVIAN : {
			return Locale::lcLatvian;
		}
		break;

		case LANG_LITHUANIAN : {
			return Locale::lcLithuanian;
		}
		break;

		case LANG_MACEDONIAN : {
			return Locale::lcMacedonian;
		}
		break;

		case LANG_MALAY : {
			return Locale::lcMalay;
		}
		break;

		case LANG_MALAYALAM : {
			return Locale::lcMalayalam;
		}
		break;



		case LANG_MARATHI : {
			return Locale::lcMarathi;
		}
		break;

		case LANG_NEPALI : {
			return Locale::lcNepali;
		}
		break;

		case LANG_NORWEGIAN : {
			switch ( subLangID ) {
				case SUBLANG_NORWEGIAN_BOKMAL : {
					return Locale::lcNorwegianBokmal;
				}
				break;

				case SUBLANG_NORWEGIAN_NYNORSK : {
					return Locale::lcNorwegianNynorsk;
				}
				break;

				default : {
					return Locale::lcNorwegian;
				}
				break;
			}

		}
		break;

		case LANG_ORIYA : {
			return Locale::lcOriya;
		}
		break;

		case LANG_POLISH : {
			return Locale::lcPolish;
		}
		break;

		case LANG_PORTUGUESE : {
			return Locale::lcPortuguese;
		}
		break;

		case LANG_PUNJABI : {
			return Locale::lcPunjabi;
		}
		break;

		case LANG_ROMANIAN : {
			return Locale::lcRomanian;
		}
		break;

		case LANG_RUSSIAN : {
			return Locale::lcRussian;
		}
		break;

		case LANG_SANSKRIT : {
			return Locale::lcSanskrit;
		}
		break;

		case LANG_SINDHI : {
			return Locale::lcSindhi;
		}
		break;

		case LANG_SLOVAK : {
			return Locale::lcSlovak;
		}
		break;

		case LANG_SLOVENIAN : {
			return Locale::lcSlovenian;
		}
		break;

		case LANG_SPANISH : {
			return Locale::lcSpanish;
		}
		break;

		case LANG_SWAHILI : {
			return Locale::lcSwahili;
		}
		break;

		case LANG_SWEDISH : {
			return Locale::lcSwahili;
		}
		break;

		case LANG_TAMIL : {
			return Locale::lcSwedish;
		}
		break;

		case LANG_TATAR : {
			return Locale::lcTatar;
		}
		break;

		case LANG_TELUGU : {
			return Locale::lcTelugu;
		}
		break;

		case LANG_THAI : {
			return Locale::lcThai;
		}
		break;

		case LANG_TURKISH : {
			return Locale::lcTurkish;
		}
		break;

		case LANG_UKRAINIAN : {
			return Locale::lcUkrainian;
		}
		break;

		case LANG_URDU : {
			return Locale::lcUrdu;
		}
		break;

		case LANG_UZBEK : {
			return Locale::lcUzbek;
		}
		break;

		case LANG_VIETNAMESE : {
			return Locale::lcVietnamese;
		}
		break;

	}

		/*
		WARNING !!!! No support for LANG_MANIPURI because there is NO ISO639 code for it
		case LANG_MANIPURI : {
			return Locale::ccIndia;
		}
		break;
		*/
		/*
		WARNING!  No ISO 2 letter code for LANG_KONKANI41
		case LANG_KONKANI : {
			return Locale::ccIndia;
		}
		break;
		*/


	return 0;

}

String Win32LocalePeer::getLanguage()
{
	String result;
#ifdef VCF_WIN32CE
	int size = ::GetLocaleInfoW( lcid_, LOCALE_SLANGUAGE, NULL, 0 );
	VCFChar* tmp = new VCFChar[size+1];
	memset( tmp, 0, (size+1)*sizeof(VCFChar) );
	::GetLocaleInfoW( lcid_, LOCALE_SLANGUAGE, tmp, size );
	result = tmp;
	delete [] tmp;
#else
	if ( System::isUnicodeEnabled() ) {
		int size = ::GetLocaleInfoW( lcid_, LOCALE_SLANGUAGE, NULL, 0 );
		VCFChar* tmp = new VCFChar[size+1];
		memset( tmp, 0, (size+1)*sizeof(VCFChar) );
		::GetLocaleInfoW( lcid_, LOCALE_SLANGUAGE, tmp, size );
		result = tmp;
		delete [] tmp;
	}
	else {
		int size = ::GetLocaleInfoA( lcid_, LOCALE_SLANGUAGE, NULL, 0 );
		char* tmp = new char[size+1];
		memset( tmp, 0, (size+1) );
		::GetLocaleInfoA( lcid_, LOCALE_SLANGUAGE, tmp, size );
		result = tmp;
		delete [] tmp;
	}
#endif
	return result;
}

uint32 Win32LocalePeer::getCountryCode()
{

	UINT languageID = PRIMARYLANGID(LANGIDFROMLCID(lcid_));
	UINT countryID = SUBLANGID(LANGIDFROMLCID(lcid_));

	switch ( languageID ) {
		case LANG_AFRIKAANS : {
			return Locale::ccSouthAfrica;
		}
		break;

		case LANG_ALBANIAN : {
			return Locale::ccAlbania;
		}
		break;


		case LANG_ARABIC : {
			switch ( countryID ) {
				case SUBLANG_ARABIC_SAUDI_ARABIA : {
					return Locale::ccSaudiArabia;
				}
				break;
				case SUBLANG_ARABIC_IRAQ : { //Win32LocalePeer::countryIDs["ar_IQ"]
					return Locale::ccIraq;
				}
				break;

				case SUBLANG_ARABIC_EGYPT : { //Win32LocalePeer::countryIDs["ar_EG"] = SUBLANG_ARABIC_EGYPT;
					return Locale::ccEgypt;
				}
				break;

				case SUBLANG_ARABIC_LIBYA : { //Win32LocalePeer::countryIDs["ar_LY"] =
					return Locale::ccLibyanArabJamahiriya;
				}
				break;

				case SUBLANG_ARABIC_ALGERIA : { //Win32LocalePeer::countryIDs["ar_DZ"] = SUBLANG_ARABIC_ALGERIA;
					return Locale::ccAlgeria;
				}
				break;

				case SUBLANG_ARABIC_MOROCCO : { //Win32LocalePeer::countryIDs["ar_MA"] = SUBLANG_ARABIC_MOROCCO;
					return Locale::ccMorocco;
				}
				break;

				case SUBLANG_ARABIC_TUNISIA : { //Win32LocalePeer::countryIDs["ar_TN"] = SUBLANG_ARABIC_TUNISIA;
					return Locale::ccTunisia;
				}
				break;

				case SUBLANG_ARABIC_OMAN : { //Win32LocalePeer::countryIDs["ar_OM"] = SUBLANG_ARABIC_OMAN;
					return Locale::ccOman;
				}
				break;

				case SUBLANG_ARABIC_YEMEN : { //Win32LocalePeer::countryIDs["ar_YE"] = SUBLANG_ARABIC_YEMEN;
					return Locale::ccYemen;
				}
				break;

				case SUBLANG_ARABIC_SYRIA : { //Win32LocalePeer::countryIDs["ar_SY"] = SUBLANG_ARABIC_SYRIA;
					return Locale::ccSyrianArabRepublic;
				}
				break;

				case SUBLANG_ARABIC_JORDAN : { //Win32LocalePeer::countryIDs["ar_JO"] = SUBLANG_ARABIC_JORDAN;
					return Locale::ccJordan;
				}
				break;

				case SUBLANG_ARABIC_LEBANON : { //Win32LocalePeer::countryIDs["ar_LB"] = SUBLANG_ARABIC_LEBANON;
					return Locale::ccLebanon;
				}
				break;

				case SUBLANG_ARABIC_KUWAIT : { //Win32LocalePeer::countryIDs["ar_KW"] = SUBLANG_ARABIC_KUWAIT;
					return Locale::ccKuwait;
				}
				break;

				case SUBLANG_ARABIC_UAE : { //Win32LocalePeer::countryIDs["ar_AE"] = SUBLANG_ARABIC_UAE;
					return Locale::ccUnitedArabEmirates;
				}
				break;

				case SUBLANG_ARABIC_BAHRAIN : { //Win32LocalePeer::countryIDs["ar_BH"] = SUBLANG_ARABIC_BAHRAIN;
					return Locale::ccBahrain;
				}
				break;

				case SUBLANG_ARABIC_QATAR : { //Win32LocalePeer::countryIDs["ar_QA"] = SUBLANG_ARABIC_QATAR;
					return Locale::ccQatar;
				}
				break;
			}
		}
		break;

		case LANG_ASSAMESE : {
			return Locale::ccIndia;
		}
		break;

		case LANG_ARMENIAN : {
			return Locale::ccArmenia;
		}
		break;

		case LANG_AZERI : {
			return Locale::ccAzerbaijan;
		}
		break;

		case LANG_BASQUE : {
			return Locale::ccSpain;
		}
		break;


		case LANG_BELARUSIAN : {
			return Locale::ccSpain;
		}
		break;

		case LANG_BENGALI : {
			return Locale::ccIndia;
		}
		break;


		case LANG_BULGARIAN : {
			return Locale::ccBulgaria;
		}
		break;

		case LANG_CATALAN : {
			return Locale::ccSpain;
		}
		break;

		case LANG_CHINESE : {
			switch ( countryID ) {
				case SUBLANG_CHINESE_HONGKONG : {
					return Locale::ccHongKong;
				}
				break;

				case SUBLANG_CHINESE_SINGAPORE : {
					return Locale::ccSingapore;
				}
				break;

				case SUBLANG_CHINESE_MACAU : {
					return Locale::ccMacao;
				}
				break;

				default : {
					return Locale::ccChina;
				}
				break;
			}
		}
		break;

		case LANG_CROATIAN : { // equivalent to LANG_SERBIAN in winnt.h

			switch ( countryID ) {
				case SUBLANG_SERBIAN_CYRILLIC : {
					return Locale::ccSerbia;
				}
				break;

				case SUBLANG_SERBIAN_LATIN : {
					return Locale::ccSerbia;
				}
				break;

				default : {
					return Locale::ccCroatia;
				}
				break;
			}
		}
		break;

		case LANG_CZECH : {
			return Locale::ccCzechRepublic;
		}
		break;

		case LANG_DANISH : {
			return Locale::ccDenmark;
		}
		break;

		case LANG_DUTCH : {
			switch ( countryID ) {
				case SUBLANG_DUTCH : {
					return Locale::ccNetherlands;
				}
				break;

				case SUBLANG_DUTCH_BELGIAN : {
					return Locale::ccBelgium;
				}
				break;
			}
		}
		break;


		case LANG_ENGLISH : {
			switch ( countryID ) {
				case SUBLANG_ENGLISH_US : {
					return Locale::ccUnitedStates;
				}
				break;

				case SUBLANG_ENGLISH_UK : {
					return Locale::ccUnitedKingdom;
				}
				break;

				case SUBLANG_ENGLISH_AUS : {
					return Locale::ccAustralia;
				}
				break;

				case SUBLANG_ENGLISH_CAN : {
					return Locale::ccCanada;
				}
				break;

				case SUBLANG_ENGLISH_NZ : {
					return Locale::ccNewZealand;
				}
				break;

				case SUBLANG_ENGLISH_EIRE : {
					return Locale::ccIreland;
				}
				break;

				case SUBLANG_ENGLISH_SOUTH_AFRICA : {
					return Locale::ccSouthAfrica;
				}
				break;

				case SUBLANG_ENGLISH_JAMAICA : {
					return Locale::ccJamaica;
				}
				break;

				case SUBLANG_ENGLISH_CARIBBEAN : {
					return Locale::ccJamaica;
				}
				break;

				case SUBLANG_ENGLISH_BELIZE : {
					return Locale::ccBelize;
				}
				break;

				case SUBLANG_ENGLISH_TRINIDAD : {
					return Locale::ccTrinidad;
				}
				break;

				case SUBLANG_ENGLISH_PHILIPPINES : {
					return Locale::ccPhilippines;
				}
				break;

				case SUBLANG_ENGLISH_ZIMBABWE : {
					return Locale::ccZimbabwe;
				}
				break;
			}
		}
		break;

		case LANG_ESTONIAN : {
			return Locale::ccEstonia;
		}
		break;

		case LANG_FAEROESE : {
			return Locale::ccFaroIslands;
		}
		break;

		case LANG_FARSI : {
			return Locale::ccIraq; //?? do we need others ? Afghanistan??
		}
		break;

		case LANG_FINNISH : {
			return Locale::ccFinland;
		}
		break;

		case LANG_FRENCH : {
			switch ( countryID ) {
				case SUBLANG_FRENCH : {
					return Locale::ccFrance;
				}
				break;

				case SUBLANG_FRENCH_BELGIAN : {
					return Locale::ccBelgium;
				}
				break;

				case SUBLANG_FRENCH_CANADIAN : {
					return Locale::ccCanada;
				}
				break;

				case SUBLANG_FRENCH_SWISS : {
					return Locale::ccSwitzerland;
				}
				break;

				case SUBLANG_FRENCH_LUXEMBOURG : {
					return Locale::ccLuxembourg;
				}
				break;

				case SUBLANG_FRENCH_MONACO : {
					return Locale::ccMonaco;
				}
				break;
			}
		}
		break;

		case LANG_GEORGIAN : {
			return Locale::ccGeorgia;
		}
		break;

		case LANG_GERMAN : {
			switch ( countryID ) {
				case SUBLANG_GERMAN : {
					return Locale::ccGermany;
				}
				break;

				case SUBLANG_GERMAN_SWISS : {
					return Locale::ccSwitzerland;
				}
				break;

				case SUBLANG_GERMAN_AUSTRIAN : {
					return Locale::ccAustria;
				}
				break;

				case SUBLANG_GERMAN_LUXEMBOURG : {
					return Locale::ccLuxembourg;
				}
				break;

				case SUBLANG_GERMAN_LIECHTENSTEIN : {
					return Locale::ccLiechtenstein;
				}
				break;
			}
		}
		break;

		case LANG_GREEK : {
			return Locale::ccGreece;
		}
		break;

		case LANG_GUJARATI : {
			return Locale::ccIndia;
		}
		break;

		case LANG_HEBREW : {
			return Locale::ccIsrael;
		}
		break;

		case LANG_HINDI : {
			return Locale::ccIndia;
		}
		break;

		case LANG_HUNGARIAN : {
			return Locale::ccHungary;
		}
		break;

		case LANG_ICELANDIC : {
			return Locale::ccIceland;
		}
		break;

		case LANG_INDONESIAN : {
			return Locale::ccIndonesia;
		}
		break;

		case LANG_ITALIAN : {
			switch ( countryID ) {
				case SUBLANG_ITALIAN : {
					return Locale::ccItaly;
				}
				break;

				case SUBLANG_ITALIAN_SWISS : {
					return Locale::ccSwitzerland;
				}
				break;
			}
		}
		break;

		case LANG_JAPANESE : {
			return Locale::ccJapan;
		}
		break;

		case LANG_KANNADA : {
			return Locale::ccIndia;
		}
		break;

		case LANG_KASHMIRI : {
			switch ( countryID ) {
				case SUBLANG_DEFAULT : {
					return Locale::ccPakistan;  //??? is this right ?
				}
				break;

				case SUBLANG_KASHMIRI_INDIA : {
					return Locale::ccIndia;
				}
				break;
			}
		}
		break;

		case LANG_KAZAK : {
			return Locale::ccKazakhstan;
		}
		break;

		case LANG_KOREAN : {
			switch ( countryID ) {
				case SUBLANG_KOREAN : {
					return Locale::ccSouthKorea;
				}
				break;
			}
		}
		break;

		case LANG_KONKANI : {
			return Locale::ccIndia;
		}
		break;

		case LANG_LATVIAN : {
			return Locale::ccLatvia;
		}
		break;

		case LANG_LITHUANIAN : {
			return Locale::ccLithuania;
		}
		break;

		case LANG_MACEDONIAN : {
			return Locale::ccMacedonia;
		}
		break;

		case LANG_MALAY : {

			switch ( countryID ) {
				case SUBLANG_MALAY_BRUNEI_DARUSSALAM : {
					return Locale::ccBrunei;
				}
				break;

				case SUBLANG_MALAY_MALAYSIA : {
					return Locale::ccMalaysia;
				}
				break;

				default : {
					return Locale::ccMalaysia;
				}
				break;
			}
		}
		break;

		case LANG_MALAYALAM : {
			return Locale::ccIndia;
		}
		break;

		case LANG_MANIPURI : {
			return Locale::ccIndia;
		}
		break;

		case LANG_MARATHI : {
			return Locale::ccIndia;
		}
		break;

		case LANG_NEPALI : {

			switch ( countryID ) {
				case SUBLANG_NEPALI_INDIA : {
					return Locale::ccIndia;
				}
				break;

				default : {
					return Locale::ccNepal;
				}
				break;
			}
		}
		break;

		case LANG_NORWEGIAN : {
			switch ( countryID ) {
				case SUBLANG_NORWEGIAN_BOKMAL : {
					return Locale::ccNorway;
				}
				break;

				case SUBLANG_NORWEGIAN_NYNORSK : {
					return Locale::ccNorway;
				}
				break;

				default : {
					return Locale::ccNorway;
				}
				break;
			}
		}
		break;

		case LANG_ORIYA : {
			return Locale::ccIndia;
		}
		break;

		case LANG_POLISH : {
			return Locale::ccPoland;
		}
		break;

		case LANG_PORTUGUESE : {
			switch ( countryID ) {
				case SUBLANG_PORTUGUESE : {
					return Locale::ccPortugal;
				}
				break;

				case SUBLANG_PORTUGUESE_BRAZILIAN : {
					return Locale::ccBrazil;
				}
				break;

				default : {
					return Locale::ccPortugal;
				}
				break;

			}
		}
		break;

		case LANG_PUNJABI : {
			return Locale::ccIndia;
		}
		break;

		case LANG_ROMANIAN : {
			return Locale::ccRomania;
		}
		break;

		case LANG_RUSSIAN : {
			return Locale::ccRussianFederation;
		}
		break;

		case LANG_SANSKRIT : {
			return Locale::ccIndia;
		}
		break;

		case LANG_SINDHI : {
			return Locale::ccIndia;
		}
		break;

		case LANG_SLOVAK : {
			return Locale::ccSlovakia;
		}
		break;

		case LANG_SLOVENIAN : {
			return Locale::ccSlovenia;
		}
		break;

		case LANG_SPANISH : {
			switch ( countryID ) {
				case SUBLANG_SPANISH_MEXICAN : {
					return Locale::ccMexico;
				}
				break;

				case SUBLANG_SPANISH_GUATEMALA : {
					return Locale::ccGuatemala;
				}
				break;

				case SUBLANG_SPANISH_COSTA_RICA : {
					return Locale::ccCostaRica;
				}
				break;

				case SUBLANG_SPANISH_PANAMA : {
					return Locale::ccPanama;
				}
				break;

				case SUBLANG_SPANISH_DOMINICAN_REPUBLIC : {
					return Locale::ccDominicanRepublic;
				}
				break;

				case SUBLANG_SPANISH_VENEZUELA : {
					return Locale::ccVenezuela;
				}
				break;

				case SUBLANG_SPANISH_COLOMBIA : {
					return Locale::ccColombia;
				}
				break;

				case SUBLANG_SPANISH_PERU : {
					return Locale::ccPeru;
				}
				break;

				case SUBLANG_SPANISH_ARGENTINA : {
					return Locale::ccArgentina;
				}
				break;

				case SUBLANG_SPANISH_ECUADOR : {
					return Locale::ccEcuador;
				}
				break;

				case SUBLANG_SPANISH_CHILE : {
					return Locale::ccChile;
				}
				break;

				case SUBLANG_SPANISH_URUGUAY : {
					return Locale::ccUruguay;
				}
				break;

				case SUBLANG_SPANISH_PARAGUAY : {
					return Locale::ccParaguay;
				}
				break;

				case SUBLANG_SPANISH_BOLIVIA : {
					return Locale::ccBolivia;
				}
				break;

				case SUBLANG_SPANISH_EL_SALVADOR : {
					return Locale::ccElSalvador;
				}
				break;

				case SUBLANG_SPANISH_HONDURAS : {
					return Locale::ccHonduras;
				}
				break;

				case SUBLANG_SPANISH_NICARAGUA : {
					return Locale::ccNicaragua;
				}
				break;

				case SUBLANG_SPANISH_PUERTO_RICO : {
					return Locale::ccPuertoRico;
				}
				break;

				default : {
					return Locale::ccSpain;
				}
				break;
			}
		}
		break;

		case LANG_SWAHILI : {
			/*
			Countries where Swahili is spoken

Tanzania
Swahili is an official language, alongside with English

Kenya
Swahili is a national language, alongside with other major African languages

Uganda
Swahili is widely used as a language of interethnic communication

Democratic    Republic of Congo
Swahili is one of four national languages

Other countries
Swahili is also used in Rwanda, in Burundi (for commercial purposes), and by a significant number of people in the southern part of Somalia and in northern Moçambique. It is also encountered in the larger cities of Southern Ethiopia
*/
		}
		break;

		case LANG_SWEDISH : {
			switch ( countryID ) {
				case SUBLANG_SWEDISH_FINLAND : {
					return Locale::ccFinland;
				}
				break;

				default : {
					return Locale::ccSweden;
				}
				break;
			}
		}
		break;

		case LANG_TAMIL : {
			return Locale::ccSriLanka;
		}
		break;

		case LANG_TATAR : {
			return Locale::ccUkraine;
		}
		break;

		case LANG_TELUGU : {
			return Locale::ccIndia;
		}
		break;

		case LANG_THAI : {
			return Locale::ccThailand;
		}
		break;

		case LANG_TURKISH : {
			return Locale::ccTurkey;
		}
		break;

		case LANG_UKRAINIAN : {
			return Locale::ccUkraine;
		}
		break;

		case LANG_URDU : {
			switch ( countryID ) {
				case SUBLANG_URDU_INDIA : {
					return Locale::ccIndia;
				}
				break;

				case SUBLANG_URDU_PAKISTAN : {
					return Locale::ccPakistan;
				}
				break;
			}
		}
		break;

		case LANG_UZBEK : {
			return Locale::ccUzbekistan;
		}
		break;

		case LANG_VIETNAMESE : {
			return Locale::ccVietNam;
		}
		break;
	}

	return 0;
}


/**
$Id$
*/
