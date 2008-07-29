//FilesAndDirectories.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

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
	FilePath fileName = String("tmp-output.txt");

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
	String name = fileName.getBaseName();
	String extension = fileName.getExtension();
	String nativeOSFilePath = FilePath::transformToOSSpecific( fileName );

	System::println( Format("The filename %s has the following components:\n"\
						"\tdrive: %s\n"\
						"\tdirectoryPath: %s\n"\
						"\tname: %s\n"\
						"\textension: %s\n"\
						"\tnativeOSFilePath: %s")
					%	fileName.getFileName()
					%	drive
					%	directoryPath
					%	name
					%	extension
					%	nativeOSFilePath );



	/**
	You can also enumerate the path components
	*/
	std::vector<String> pathComponents = fileName.getPathComponents();
	std::vector<String>::iterator it = pathComponents.begin();
	while ( it != pathComponents.end() ) {
		System::println( *it );
		it ++;
	}


	{
	/**
	Create a file and write some text to it
		*/
		FileOutputStream fs(fileName);
		String text = "here's some text to put in the file";
		fs << text;
		System::println( Format("FileOutputStream current size: %d") % fs.getSize() );
		fs.close();
	}


	/**
	Use the file object to access the file
	*/
	{
		File file( fileName );		
		System::println( Format("The file %s's size: %d") 
						% fileName.getFileName()
						% (uint32)file.getSize() );


		/**
		Make a copy of the file
		*/
		file.copyTo( fileName.getPathName(true) +
			FilePath::getDirectorySeparator() +
			fileName.getBaseName() + "-copy" + fileName.getExtension() );

	}


	{
		File newFile;
		newFile.create( "HelloWorld.txt", File::ofReadWrite );
		//newFile.open( "HelloWorld.txt" );//, File::ofReadWrite );
		//String text = "here's some text to put in the file";
		//FileOutputStream* fos = newFile.getOutputStream();
		//(*fos) << text;
		//fos->free();
	}



	/**
	Enumerate all files ending with a .txt extension
	and removes them from the file system.
	*/
	{
		
		Directory dir( fileName.getPathName(true) );
		
		Directory::Finder* finder = dir.findFiles( "*.txt" );
		
			if ( NULL != finder ) {
				try {
					finder->setDisplayMode( Directory::Finder::dmFiles );
					
					while ( finder->nextElement() ) {
						File* foundFile = finder->getCurrentElement();
		
						fileName = foundFile->getName();
						
						System::println( fileName );
						
						if ( !foundFile->isDirectory() ) {
							foundFile->remove();
						}
					}
				}
				catch ( BasicException& e ) {
					System::errorPrint( &e );
				}				
				delete finder;
			}
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

	{
		File f1("text-file.txt", File::ofRead | File::ofWrite, File::shNone );

		FileOutputStream* fos = f1.getOutputStream();

		TextOutputStream tos(fos);

		tos.write( 100 );
		tos.write( 200 );
		tos.write( true );
		tos.write( 12.433 );
		tos.write( String("Hello World") );

		delete fos;

		FileInputStream* fis = f1.getInputStream();

		TextInputStream tis(fis);
		String s;
		tis >> s;
		
		System::println( Format("File contents of \"%s\" :\n%s") % f1.getName() % s );

		delete fis;

		f1.remove();

	}

	FoundationKit::terminate();
	return 0;
}


/**
$Id$
*/
