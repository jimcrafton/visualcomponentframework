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
*CVS Log info
*$Log$
*Revision 1.2  2004/12/01 04:15:10  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.5  2004/11/07 20:44:51  marcelloptr
*common sintax inside main
*
*Revision 1.1.2.3  2004/11/01 20:44:22  kiklop74
*Added support for building ParticleEditor in BCB. Fixed some issues in header and cpp files
*
*Revision 1.1.2.2  2004/11/01 17:19:00  marcelloptr
*just added few lines at the end of file
*
*Revision 1.1.2.1  2004/11/01 14:38:59  pallindo
*Initial checkin of the particle editor example.  Just shows off a more complex opengl application using the VCF.
*
*/


