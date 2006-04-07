//ControlsApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "ControlsApplication.h"
#include "MainWindow.h"



using namespace VCF;



ControlsApplication::ControlsApplication( int argc, char** argv ):
	Application( argc, argv )

{

}

ControlsApplication::~ControlsApplication()
{

}

bool ControlsApplication::initRunningApplication(){
	bool result = Application::initRunningApplication();
	MainWindow* mainWindow = new MainWindow();

	setMainWindow(mainWindow);
	mainWindow->setBounds( &Rect( 50.0, 50.0, 650.0, 700.0 ) );
	mainWindow->setVisible( true );
	mainWindow->setCaption( "Controls" );

	return result;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:34:19  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2005/07/23 21:45:34  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.2.2.2  2005/06/27 23:58:03  marcelloptr
*added images to a PushButton
*
*Revision 1.2  2004/12/01 04:15:00  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.1.2.2  2004/08/30 03:50:47  dougtinkham
*added copyright
*
*/


