//UndoAppApplication.h

#ifndef _QTPLAYERAPPAPPLICATION_H__
#define _QTPLAYERAPPAPPLICATION_H__


#include "QuickTimeMovie.h"


class MainQTWindow;

/**
*Class QTPlayerApplication documentation
*
* This application *only* works under Win32 at the moment.
* Eventually it will work under both Mac and Win32.
* Not linux though, as the QuickTime SDK does not support Linux yet.
* For the QuickTime SDK, please go: 
*   http://developer.apple.com/quicktime/
* and look for 'QuickTime 6 SDK Windows'
* which is located at:
*   ftp://ftp.apple.com/developer/Development_Kits/QT6SDK_Win.hqx
*
*/
class QTPlayerApplication : public VCF::Application { 
public:
	QTPlayerApplication( int argc, char** argv );

	virtual ~QTPlayerApplication();

	virtual bool initRunningApplication();

	virtual void terminateRunningApplication();
	
	
	static QTPlayerApplication* getQTPlayerApplication() {
		return (QTPlayerApplication*)Application::getRunningInstance();
	}

protected:
	
	MainQTWindow* m_mainQTWindow;
private:
};


#endif //_QTPLAYERAPPAPPLICATION_H__


