//SplashScreen.h

#ifndef _SPLASHSCREEN_H__
#define _SPLASHSCREEN_H__


using namespace VCF;


/**
*Class SplashScreen documentation
*/
class SplashScreen : public VCF::Window, public VCF::Runnable  { 
public:
	SplashScreen();

	virtual ~SplashScreen();

	virtual bool run();

	virtual void paint( VCF::GraphicsContext* context );
protected:
	VCF::Image* m_splashImage;
private:

	VCF::ThreadLooper* m_thread;
};


#endif //_SPLASHSCREEN_H__


