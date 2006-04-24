//QTPlayer.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "QTPlayerApplication.h"
#include "MainWindow.h"



using namespace VCF;



int main(int argc, char *argv[])
{
	QTPlayerApplication* app = new QTPlayerApplication( argc, argv );

	Application::main();
	
	return 0;
}


