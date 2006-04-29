#ifndef _VCF_OSXSYSTEMPEER_H__
#define _VCF_OSXSYSTEMPEER_H__
//OSXSystemPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF
{

class OSXSystemPeer : public SystemPeer {
public:
	OSXSystemPeer();
	virtual ~OSXSystemPeer();

	virtual unsigned long getTickCount();

	virtual void sleep( const uint32& milliseconds );

	virtual bool doesFileExist( const String& fileName );

	virtual String getCurrentWorkingDirectory();

	virtual String getEnvironmentVariable( const String& variableName );
	
	virtual void setEnvironmentVariable( const String& variableName, const String& newValue );

	virtual void addPathDirectory( const String& directory );
	
	virtual void setCurrentWorkingDirectory( const String& currentDirectory );

	virtual String getCommonDirectory( System::CommonDirectory directory );

    virtual void setDateToSystemTime( DateTime* date );

	virtual void setDateToLocalTime( DateTime* date );

	virtual void setCurrentThreadLocale( Locale* locale );

    virtual bool isUnicodeEnabled() {
        return true;
    }
	
	virtual DateTime convertUTCTimeToLocalTime( const DateTime& date );	

	virtual DateTime convertLocalTimeToUTCTime( const DateTime& date );
	
	virtual String getOSName();
	virtual String getOSVersion();

	virtual String getComputerName();
	virtual String getUserName();
	
	virtual ProgramInfo* getProgramInfoFromFileName( const String& fileName );
	
	virtual String createTempFileName( const String& directory ) ;
protected:
	struct timezone timeZone_;
	struct timeval time_;
};

};


#endif // _VCF_OSXSYSTEMPEER_H__

/**
$Id$
*/
