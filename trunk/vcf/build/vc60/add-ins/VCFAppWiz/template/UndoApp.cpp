//$$Root$$.cpp


#include "ApplicationKit.h"
#include "$$Root$$Application.h"

#include "$$MainWindow$$.h"



using namespace VCF;



int main(int argc, char *argv[])
{
	Application* app = new $$Root$$Application(argc,argv);

	Application::main();
	
	return 0;
}


