//QTPlayerApplication.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "QTPlayerApplication.h"
#include "MainWindow.h"



using namespace VCF;



QTPlayerApplication::QTPlayerApplication( int argc, char** argv ): 
	Application(argc, argv),
	m_mainQTWindow( NULL )
{
	
}

QTPlayerApplication::~QTPlayerApplication()
{
	
}

bool QTPlayerApplication::initRunningApplication(){
	bool result = Application::initRunningApplication();

	// Initialize QuickTime Media Layer
	InitializeQTML(0);

	// Initialize QuickTime
	EnterMovies();

	setName( L"QuickTime Media Player" );

	m_mainQTWindow = new MainQTWindow();
	
	setMainWindow(m_mainQTWindow);
	m_mainQTWindow->setBounds( 100.0, 100.0, 700.0, 500.0 );
	m_mainQTWindow->setVisible( true );
	m_mainQTWindow->setCaption( getName() );
	
	return result;
}

void QTPlayerApplication::terminateRunningApplication() {	

	Application::terminateRunningApplication();
	// Deinitialize QuickTime Media Layer
	ExitMovies();

	// Deinitialize QuickTime Media Layer
	TerminateQTML();
}



