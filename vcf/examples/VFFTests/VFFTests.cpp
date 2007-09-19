//VFFTests.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/VFFOutputStream.h"
#include "vcf/FoundationKit/VFFInputStream.h"


using namespace VCF;


class VFFTestsWindow : public Window {
public:
	VFFTestsWindow() {
		setCaption( "VFFTests" );		
	}

	virtual ~VFFTestsWindow(){};

};




class VFFTestsApplication : public Application {
public:

	VFFTestsApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new VFFTestsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();
		
		{
			Window* w2 = new Window();
			w2->setName( "Window1" );
			w2->setCaption( w2->getName() );
			
			
			FileOutputStream fs("test1.vff");
			TextOutputStream tos(&fs);
			VFFOutputStream vos(&tos);
			//vos.setWriteComponentClassID(false);
			
			vos.writeComponent( w2 );
			
			w2->free();
		}


		{
			FileInputStream fs2("test1.vff");
			VFFInputStream vis(&fs2);
			
			Window* w3 = (Window*) vis.readNewComponent();
			w3->show();
			System::sleep(1000);
			w3->free();
		}

		{
#define	TEST_FORM1 "object Window2 : VCF::Window  top=500 left=400 width=300 height=400 end"

			VFFInputStream vis( TEST_FORM1 );
			
			Window* w4 = (Window*) vis.readNewComponent();
			w4->show();
			System::sleep(1000);
			w4->free();
		}


		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new VFFTestsApplication( argc, argv );

	Application::main();
	
	return 0;
}


