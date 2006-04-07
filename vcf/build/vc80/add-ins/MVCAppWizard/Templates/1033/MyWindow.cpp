#include "vcf/ApplicationKit/ApplicationKit.h"
#include "[!output PROJECT_NAME]Window.h"
#include "[!output PROJECT_NAME]Document.h"

using namespace VCF;


[!output PROJECT_NAME]Window::[!output PROJECT_NAME]Window()
{
	DocumentManager* docMgr = DocumentManager::getDocumentManager();
	docMgr->DocumentInitialized += new GenericEventHandler<[!output PROJECT_NAME]Window>( this, 
																			&[!output PROJECT_NAME]Window::onDocInitialized,
																			"[!output PROJECT_NAME]Window::onDocInitialized" );
}

[!output PROJECT_NAME]Window::~[!output PROJECT_NAME]Window()
{

}

void [!output PROJECT_NAME]Window::onDocInitialized( VCF::Event* e )
{	
	//initialization code can go here
}


