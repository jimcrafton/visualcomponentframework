#include "xmake.h"
#include "FilePath.h"

using namespace xmake;



int main(int argc, char* argv[])
{
	
	XMLMake make;	
	
	try {
		if ( make.initFromCommandLine( argc, argv ) ) {	
			make.initMakefile( make.getMakeFile() );
			make.executeMakefile();	
		}
		else {
			printf( XMLMake::usage().c_str() );
		}
	}
	catch ( RuntimeException& e ) {
		FilePath fp = make.getMakeFile();
		printf( "Exception: %s\nMakefile: %s\n", e.err_.c_str(), 
			fp.expandRelativePathName(make.getCurrentDirectory()).c_str() );
	}
	catch ( ... ) {
		printf( "Exception: uknown, exiting...\n" );
		return -1;
	}


	return make.getReturnCode();
}


