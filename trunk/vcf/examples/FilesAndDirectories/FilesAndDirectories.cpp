////FilesAndDirectories.cpp

#include "FoundationKit.h"

using namespace VCF;



/**
This example will demonstrate using the various file and directory classes for
working with the underlying filesystem.
*/

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	/**
	use a FilePath object to store the file name
	*/
	FilePath fileName = "tmp-output.txt";

	/**
	Is this a relative file name?
	If so, let's expand the relative and change it to an
	absolute filename using the current directory as our 
	reference point
	*/
	if ( fileName.isRelativePath() ) {		
		fileName = fileName.expandRelativePathName( System::getCurrentWorkingDirectory() );
	}


	/**
	Lets look at the various file name components
	*/

	String drive = fileName.getDriveName();
	String directoryPath = fileName.getPathName();
	String name = fileName.getName();
	String extension = fileName.getExtension();
	String nativeOSFilePath = fileName.transformToOSSpecific();

	System::println( "The filename %s has the following components:\n"\
						"\tdrive: %s\n"\
						"\tdirectoryPath: %s\n"\
						"\tname: %s\n"\
						"\textension: %s\n"\
						"\tnativeOSFilePath: %s",
						fileName.getFileName().c_str(),
						drive.c_str(),
						directoryPath.c_str(),
						name.c_str(),
						extension.c_str(),
						nativeOSFilePath.c_str() );


	/**
	You can also enumerate the path components
	*/
	std::vector<String> pathComponents = fileName.getPathComponents();
	std::vector<String>::iterator it = pathComponents.begin();
	while ( it != pathComponents.end() ) {
		System::println( *it );
		it ++;
	}



	/**
	Create a file and write some text to it
	*/
	FileOutputStream fs(fileName);
	String text = "here's some text to put in the file";
	fs << text;
	System::println( "FileOutputStream current size: %d", fs.getSize() );
	fs.close();


	{
		
	/**
	Use the file object to access the file
		*/
		File file( fileName ); 
		System::println( "The file %s's size: %d", fileName.getFileName().c_str(), file.getSize() );
		
		
		/**
		Make a copy of the file
		*/
		file.copyTo( fileName.getPathName(true) + 
			FilePath::getDirectorySeparator() + 
			fileName.getName() + "-copy" + fileName.getExtension() );
		
	}

	

	/**
	Enumerate all files ending with a .txt extension
	*/

	Directory dir( fileName.getPathName(true) );
	Directory::Finder* finder = dir.findFiles( "*.txt" );
	if ( NULL != finder ) {
		while ( finder->hasMoreElements() ) {
			fileName = finder->nextElement();
			System::println( fileName );

			File f(fileName);
			f.remove();
		}
		finder->free();
	}



	/**
	File chaining - 
	*/

	{
		FileOutputStream textFile( "text-file.txt" );
		TextOutputStream tos(&textFile);
		
		tos.write( 100 );
		tos.write( 200 );
		tos.write( true );
		tos.write( 12.433 );
		tos.write( String("Hello World") );

		textFile.close();
		
		int i1;
		int i2;
		bool b1;
		double d1;
		String s;
		
		FileInputStream fis( "text-file.txt" );
		TextInputStream tis(&fis);
		tis.read( i1 );
		tis.read( i2 );
		tis.read( b1 );
		tis.read( d1 );
		tis.read( s );


	}

	FoundationKit::terminate();
	return 0;
}


