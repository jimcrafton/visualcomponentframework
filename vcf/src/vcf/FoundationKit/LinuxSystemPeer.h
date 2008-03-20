#ifndef _VCF_LINUXSYSTEMPEER_H__
#define _VCF_LINUXSYSTEMPEER_H__
//LinuxSystemPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

// LinuxSystemPeer.h: interface for the LinuxSystemPeer class.

#include <sys/time.h>

namespace VCF
{

class LinuxSystemPeer : public SystemPeer
{
public:
	LinuxSystemPeer();
	virtual ~LinuxSystemPeer();

	virtual uint32 getTickCount();

	virtual void sleep( const uint32& milliseconds );

	virtual bool doesFileExist( const String& fileName );

	virtual void addPathDirectory( const String& directory );

	virtual ProgramInfo* getProgramInfoFromFileName( const String& fileName );

	virtual String getCurrentWorkingDirectory();

	virtual String getEnvironmentVariable( const String& variableName );

    virtual void setEnvironmentVariable( const String& variableName, const String& newValue );

	virtual void setCurrentWorkingDirectory( const String& currentDirectory );

	virtual String getCommonDirectory( System::CommonDirectory directory );

    virtual String createTempFileName( const String& directory );

	virtual void setDateToSystemTime( DateTime* date );

	virtual void setDateToLocalTime( DateTime* date );

	virtual void setCurrentThreadLocale( Locale* locale );

	virtual bool isUnicodeEnabled()
	{
		return false;
	}

	virtual DateTime convertUTCTimeToLocalTime( const DateTime& date );

	virtual DateTime convertLocalTimeToUTCTime( const DateTime& date );

	virtual void setTimeZoneToLocal( const DateTime& currentDate, TimeZone& tz );


    virtual String getOSName();
    virtual String getOSVersion();

	virtual String getComputerName();
	virtual String getUserName();

protected:
	struct timezone timeZone_;
	struct timeval time_;
};

};


#endif // _VCF_LINUXSYSTEMPEER_H__

/**
$Id$
*/
