#ifndef _VCF_WIN32SYSTEMPEER_H__
#define _VCF_WIN32SYSTEMPEER_H__
//Win32SystemPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Win32SystemPeer.h: interface for the Win32SystemPeer class.





namespace VCF {
class Win32ResourceBundle;

class Win32SystemPeer : public SystemPeer {
public:
	Win32SystemPeer();
	virtual ~Win32SystemPeer();

	virtual unsigned long getTickCount();

	virtual void sleep( const uint32& milliseconds );

	virtual bool doesFileExist( const String& fileName );

	virtual String getEnvironmentVariable( const String& variableName );

	virtual String getCurrentWorkingDirectory();

	virtual void setEnvironmentVariable( const String& variableName, const String& newValue );

	virtual void addPathDirectory( const String& directory );

	virtual void setCurrentWorkingDirectory( const String& currentDirectory );

	virtual String getCommonDirectory( System::CommonDirectory directory );

	virtual String createTempFileName( const String& directory );

	virtual void setDateToSystemTime( DateTime* date );

	virtual void setDateToLocalTime( DateTime* date );

	virtual void setCurrentThreadLocale( Locale* locale );

	virtual bool isUnicodeEnabled();

	virtual DateTime convertUTCTimeToLocalTime( const DateTime& date );	

	virtual DateTime convertLocalTimeToUTCTime( const DateTime& date );
	
	virtual String getOSName();

	virtual String getOSVersion();

	virtual String getComputerName();

	virtual String getUserName();

	virtual ProgramInfo* getProgramInfoFromFileName( const String& fileName );
protected:
};

};


#endif // _VCF_WIN32SYSTEMPEER_H__

/**
$Id$
*/
