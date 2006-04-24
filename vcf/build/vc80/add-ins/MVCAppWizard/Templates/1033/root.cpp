//[!output PROJECT_NAME].cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "[!output PROJECT_NAME]Document.h"
#include "[!output PROJECT_NAME]View.h"
#include "[!output PROJECT_NAME]Window.h"

using namespace VCF;

class [!output PROJECT_NAME] : public SDIDocumentBasedApplication {
public:

	[!output PROJECT_NAME]( int argc, char *argv[] ) : SDIDocumentBasedApplication(argc,argv) {

	}

	virtual bool initRunningApplication(){

		REGISTER_CLASSINFO( [!output PROJECT_NAME]Document );
		REGISTER_CLASSINFO( [!output PROJECT_NAME]View );
		REGISTER_CLASSINFO( [!output PROJECT_NAME]Window );

		bool result = SDIDocumentBasedApplication::initRunningApplication();	
		
		newDefaultDocument( "" );

		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += new GenericEventHandler<[!output PROJECT_NAME]>( this, 
																			&[!output PROJECT_NAME]::onDocInitialized,
																			"[!output PROJECT_NAME]::onDocInitialized" );

		return result;
	}

	virtual void terminateRunningApplication() {
		SDIDocumentBasedApplication::terminateRunningApplication();

	}

	void onDocInitialized( Event* e ) {
		Document* doc = (Document*)e->getSource();		

	}
};


int main(int argc, char *argv[])
{
	Application* app = new [!output PROJECT_NAME]( argc, argv );

	Application::main();
	
	return 0;
}

