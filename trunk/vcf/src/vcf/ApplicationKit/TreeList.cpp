//TreeList.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Window.h"
#include "vcf/GraphicsKit/Rect.h"
#include "vcf/ApplicationKit/TreeListControl.h"

using namespace VCF;


class TreeListApplication : public Application {
public:

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();

		Window* helloWorldWindow = new Window();
		setMainWindow(helloWorldWindow);
		helloWorldWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		helloWorldWindow->setCaption( "Hello World !!!!" );

		TreeListControl* tlc = new TreeListControl();
		tlc->setBounds( &Rect(25, 25, 300, 300 ) );
		tlc->setVisible( true );
		DefaultColumnHeaderItem* dci = new DefaultColumnHeaderItem();
		dci->setCaption( "Column2" );
		tlc->addColumnHeaderItem( dci );
		helloWorldWindow->add( tlc );

		helloWorldWindow->setVisible( true );
		return result;
	}

};


int main(int argc, char *argv[])
{
	TreeListApplication app;

	Application::appMain( argc, argv );

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.3  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.22.1  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


