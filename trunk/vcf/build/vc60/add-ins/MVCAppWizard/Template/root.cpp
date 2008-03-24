//$$root$$.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "$$Root$$Document.h"
#include "$$Root$$View.h"
#include "$$Root$$Window.h"

using namespace VCF;





class $$Root$$ : public SDIDocumentBasedApplication {
public:

	$$Root$$( int argc, char *argv[] ) : SDIDocumentBasedApplication(argc,argv) {

	}

	virtual bool initRunningApplication(){

		REGISTER_CLASSINFO( $$Root$$Document );
		REGISTER_CLASSINFO( $$Root$$View );
		REGISTER_CLASSINFO( $$Root$$Window );

		bool result = SDIDocumentBasedApplication::initRunningApplication();	
		
		newDefaultDocument();

		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += new GenericEventHandler<$$Root$$>( this, 
																			&$$Root$$::onDocInitialized,
																			"$$Root$$::onDocInitialized" );

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
	return ApplicationKitMain<$$Root$$>(argc,argv);
}

