//Tables.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"


using namespace VCF;




class TablesWindow : public Window {
public:
	TablesWindow() {
		setCaption( "Tables" );
		setVisible( true );

		TableControl* table = new TableControl();

		add( table, AlignClient );

		TableModel* model = table->getTableModel();

		model->empty();

		model->addColumns( 12 );
		model->addRows(80);
		model->setFixedRowsCount( 1 );
		model->setFixedColumnsCount( 1 );

		for (int y=0;y<model->getRowCount();y++ ){
			for ( int x=0;x<model->getColumnCount();x++ ) {
				model->getItem( y, x )->setCaption( StringUtils::format( "Cell [%d,%d]", y, x ) );
			}
		}



		table->setAllowFixedRowSelection( false );

	}

	virtual ~TablesWindow(){};

};




class TablesApplication : public Application {
public:

	TablesApplication( int argc, char** argv ) : Application(argc, argv) {

	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* mainWindow = new TablesWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );

		return result;
	}

};



int main(int argc, char *argv[])
{
	Application* app = new TablesApplication( argc, argv );

	Application::main();


	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:39  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.2.4  2004/04/29 03:40:57  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


