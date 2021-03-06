#ifndef _VCF_SYSTEMPEER_H__
#define _VCF_SYSTEMPEER_H__
//SystemPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class DateTime;
class ResourceBundle;

/**
\class SystemPeer SystemPeer.h "vcf/FoundationKit/SystemPeer.h"
*Defines the SystemPeer interface
*/
class FOUNDATIONKIT_API SystemPeer {
public:
	virtual ~SystemPeer(){};
	/**
	*tries to return a uint32 representing the current tick count of the system
	*/
	virtual uint32 getTickCount()=0;

	/**
	*causes the calling thread to pause for the
	*specified number of milliseconds
	*@param uint32 the number of milliseconds to pause the thread
	*/
	virtual void sleep( const uint32& milliseconds ) = 0;

	virtual bool doesFileExist( const String& fileName ) = 0;

	virtual String getEnvironmentVariable( const String& variableName ) = 0;

	virtual void setEnvironmentVariable( const String& variableName, const String& newValue ) = 0;

	virtual void addPathDirectory( const String& directory ) = 0;

	virtual String getCurrentWorkingDirectory() = 0;

	virtual void setCurrentWorkingDirectory( const String& currentDirectory ) = 0;

	virtual String getCommonDirectory( System::CommonDirectory directory ) = 0;

	virtual String createTempFileName( const String& directory ) = 0;

	virtual void setDateToSystemTime( DateTime* date ) = 0;

	virtual void setDateToLocalTime( DateTime* date ) = 0;

	virtual void setCurrentThreadLocale( Locale* locale ) = 0;

	virtual bool isUnicodeEnabled() = 0;

	virtual DateTime convertUTCTimeToLocalTime( const DateTime& date ) = 0;	

	virtual DateTime convertLocalTimeToUTCTime( const DateTime& date ) = 0;	

	virtual void setTimeZoneToLocal( const DateTime& currentDate, TimeZone& tz ) = 0;

	virtual String getOSName() = 0;
	virtual String getOSVersion() = 0;

	virtual String getComputerName() = 0;
	virtual String getUserName() = 0;

	virtual ProgramInfo* getProgramInfoFromFileName( const String& fileName ) = 0;

	virtual uint32 getCurrentThreadID() = 0;
	virtual uint32 getProcessID() = 0;
};

};


#endif // _VCF_SYSTEMPEER_H__

/**
$Id$
*/
