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
	docMgr->DocumentInitialized += new ClassProcedure1<Event*,SketchWindow>( this,
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
$Id$
*/
