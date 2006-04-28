#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/OpenGLKit/OpenGLKit.h"

#include "ParticleEditor.h"

class ParticleEditorApplication:public VCF::Application{
public:
	ParticleEditorApplication(int argc,char **argv):VCF::Application(argc,argv){};

	virtual ~ParticleEditorApplication(){};

	virtual bool initRunningApplication(){
		bool result=Application::initRunningApplication();

		VCF::Window *window=new ParticleEditor();

 		setMainWindow(window);
		window->setVisible(true);

		return result;
	}
};

int main(int argc, char **argv){
	ParticleEditorApplication *app=new ParticleEditorApplication(argc,argv);

	Application::main();

	return 0;
}

/**
$Id$
*/
