#include "ApplicationKit.h"
#include "SketchWindow.h"
#include "ModelViewKit.h"

using namespace VCF;


SketchWindow::SketchWindow()
{
	DocumentManager* docMgr = DocumentManager::getDocumentManager();
	docMgr->DocumentInitialized += new GenericEventHandler<SketchWindow>( this, 
																			&SketchWindow::onDocInitialized,
																			"SketchWindow::onDocInitialized" );

	//setUsingRenderBuffer( true );	
}

SketchWindow::~SketchWindow()
{

}

void SketchWindow::onDocInitialized( Event* e ) 
{
	Document* doc = (Document*)e->getSource();
	
	

	
}

