//InputValidation.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/AdapterModels.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/InputValidation.h"


using namespace VCF;




class InputValidationWindow : public Window {
public:
	InputValidationWindow() {}
	virtual ~InputValidationWindow(){};
};

_class_rtti_(InputValidationWindow, "VCF::Window", "InputValidationWindow")
_class_rtti_end_





class InputValidationApp : public Application {
public:

	InputValidationApp( int argc, char** argv ) : Application(argc, argv) {
		addCallback( new ClassProcedure1<Event*,InputValidationApp>(this, &InputValidationApp::updateNumericValAsDouble), "InputValidationApp::updateNumericValAsDouble" );
		addCallback( new ClassProcedure1<Event*,InputValidationApp>(this, &InputValidationApp::updateCurrencyValAsDouble), "InputValidationApp::updateCurrencyValAsDouble" );


	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(InputValidationWindow);		
		

		Window* mainWindow = Frame::createWindow( classid(InputValidationWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

	void updateNumericValAsDouble( Event* ) {
		TextControl* tc = (TextControl*)findComponent( "edt3", true );

		NumericValidator* numInput = (NumericValidator*)findComponent( "numericValidator", true );
		tc->setText( StringUtils::toString(numInput->getDouble()) );

	}

	void updateCurrencyValAsDouble( Event* ) {
		TextControl* tc = (TextControl*)findComponent( "edt4", true );

		CurrencyValidator* currencyValidator = (CurrencyValidator*)findComponent( "currencyValidator", true );
		tc->setText( StringUtils::toString(currencyValidator->getDouble()) );
	}

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<InputValidationApp>(argc,argv);
}


