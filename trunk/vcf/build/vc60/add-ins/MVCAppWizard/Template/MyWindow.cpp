
#include "ApplicationKit.h"
#include "$$Root$$Window.h"
#include "$$Root$$Document.h"

using namespace VCF;


$$Root$$Window::$$Root$$Window()
{
	DocumentManager* docMgr = DocumentManager::getDocumentManager();
	docMgr->DocumentInitialized += new GenericEventHandler<$$Root$$Window>( this, 
																			&$$Root$$Window::onDocInitialized,
																			"$$Root$$Window::onDocInitialized" );
}

$$Root$$Window::~$$Root$$Window()
{

}

void $$Root$$Window::onDocInitialized( VCF::Event* e )
{	
	//initialization code can go here
}


