//[!output PROJECT_NAME].cpp

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "[!output PROJECT_NAME]Application.h"

#include "MainWindow.h"

using namespace VCF;

int main(int argc, char *argv[])
{
	return ApplicationKitMain< [!output PROJECT_NAME]Application >(argc,argv);
}
