//UndoAppApplication.h

#ifndef _QTPLAYERAPPAPPLICATION_H__
#define _QTPLAYERAPPAPPLICATION_H__


#include "QuickTimeMovie.h"


class MainQTWindow;

/**
*Class QTPlayerApplication documentation
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


