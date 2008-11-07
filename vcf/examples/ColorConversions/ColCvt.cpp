//ColCvt.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/SliderControl.h"
#include "vcf/ApplicationKit/Label.h"

#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;



class ColCvtWindow : public Window {
public:
	ColCvtWindow() {}
	virtual ~ColCvtWindow(){};
};

_class_rtti_(ColCvtWindow, "VCF::Window", "ColCvtWindow")
_class_rtti_end_





class ColCvtApp : public Application {
public:

	ColCvtApp( int argc, char** argv ) : Application(argc, argv) {
		addCallback( new ClassProcedure1<Event*,ColCvtApp>(this, &ColCvtApp::onRed), "ColCvtApp::onRed" );
		addCallback( new ClassProcedure1<Event*,ColCvtApp>(this, &ColCvtApp::onGreen), "ColCvtApp::onGreen" );
		addCallback( new ClassProcedure1<Event*,ColCvtApp>(this, &ColCvtApp::onBlue), "ColCvtApp::onBlue" );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(ColCvtWindow);

		Window* mainWindow = Frame::createWindow( classid(ColCvtWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

	void onRed(Event* e) {
		SliderControl* slider = (SliderControl*)e->getSource();
		Control* ctrl = (Control*)findComponent("col",true);
		Color c = *ctrl->getColor();

		c.setRed( slider->getPosition()/slider->getMaxValue() );

		ctrl->setColor( &c );
		updateRGB();
	}


	void onGreen(Event* e) {
		SliderControl* slider = (SliderControl*)e->getSource();
		Control* ctrl = (Control*)findComponent("col",true);
		Color c = *ctrl->getColor();

		c.setGreen( slider->getPosition()/slider->getMaxValue() );

		ctrl->setColor( &c );
		updateRGB();
	}

	void onBlue(Event* e) {
		SliderControl* slider = (SliderControl*)e->getSource();
		Control* ctrl = (Control*)findComponent("col",true);
		Color c = *ctrl->getColor();

		c.setBlue( slider->getPosition()/slider->getMaxValue() );

		ctrl->setColor( &c );
		updateRGB();
	}

	void updateRGB() {
		Control* ctrl = (Control*)findComponent("col",true);
		Color c = *ctrl->getColor();

		Label* label = (Label*)findComponent("rgbVals",true);
		label->setCaption( Format( "R: %0.3f G: %0.3f B: %0.3f hex: %s" ) % c.getRed() % c.getGreen() % c.getBlue() % c.toHexCode8() );

		label = (Label*)findComponent("hlsVals",true);
		double h,s,l;
		c.getHSL(h,l,s);
		label->setCaption( Format( "H: %0.3f L: %0.3f S: %0.3f" ) % h % l % s );


		label = (Label*)findComponent("hsvVals",true);
		double v;
		c.getHSV(h,s,v);
		label->setCaption( Format( "H: %0.3f S: %0.3f V: %0.3f" ) % h % s % v );


		label = (Label*)findComponent("cmyVals",true);
		
		double r = c.getRed();
		double g = c.getGreen();
		double b = c.getBlue();

		double c2,m,y;
		c.getCMY(c2,m,y);

		label->setCaption( Format( "C: %0.3f M: %0.3f Y: %0.3f" ) % c2 % m % y );


		label = (Label*)findComponent("cmykVals",true);

		double k;

		c.getCMYK(c2,m,y,k);

		label->setCaption( Format( "C: %0.3f M: %0.3f Y: %0.3f K: %0.3f" ) % c2 % m % y % k );
	
		

		label = (Label*)findComponent("xyzVals",true);

		double X,Y,Z;
		c.getXYZ(X,Y,Z);
		label->setCaption( Format( "X: %0.3f Y: %0.3f Z: %0.3f" ) % X % Y % Z );
		double L,a;
		c.getLab(L,a,b);

		label = (Label*)findComponent("labVals",true);

		label->setCaption( Format( "CIE-L*: %0.3f CIE-a*: %0.3f CIE-b*: %0.3f" ) % L % a % b );



		double u;
		c.getYUV(y,u,v);


		label = (Label*)findComponent("yuvVals",true);

		label->setCaption( Format( "Y: %0.6f u: %0.6f v: %0.6f" ) % y % u % v );

		label = (Label*)findComponent("yuv8Vals",true);

		uchar y8,u8,v8;
		c.getYUV8Bit( y8,u8,v8 );

		label->setCaption( Format( "Y: 0x%0X u: 0x%0X v: 0x%0X" ) % y8 % u8 % v8 );
	}
};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<ColCvtApp>(argc,argv);
}


