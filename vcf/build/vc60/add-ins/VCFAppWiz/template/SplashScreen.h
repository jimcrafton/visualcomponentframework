//SplashScreen.h

#ifndef _SPLASHSCREEN_H__
#define _SPLASHSCREEN_H__



/**
*Class SplashScreen documentation
*/
class SplashScreen : public VCF::Window  { 
public:
	SplashScreen();

	virtual ~SplashScreen();

	virtual void paint( VCF::GraphicsContext* context );
protected:
	VCF::Image* m_splashImage;


	void onTimer( VCF::Event* e );

	VCF::String m_splashText;
};


#endif //_SPLASHSCREEN_H__


