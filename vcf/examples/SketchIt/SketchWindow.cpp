//SketchWindow.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "../examples/SketchIt/SketchWindow.h"
#include "vcf/ApplicationKit/ModelViewKit.h"

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


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:37  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.6.4  2004/04/29 03:40:56  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


