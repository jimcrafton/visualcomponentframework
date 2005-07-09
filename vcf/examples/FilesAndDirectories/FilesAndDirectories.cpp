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

	System::println( Format("The filename %ls has the following components:\n"\
						"\tdrive: %ls\n"\
						"\tdirectoryPath: %ls\n"\
						"\tname: %ls\n"\
						"\textension: %ls\n"\
						"\tnativeOSFilePath: %ls")
					%	fileName.getFileName().c_str()
					%	drive.c_str()
					%	directoryPath.c_str()
					%	name.c_str()
					%	extension.c_str()
					%	nativeOSFilePath.c_str() );


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
	System::println( Format("FileOutputStream current size: %d") % fs.getSize() );
	fs.close();



	/**
	Use the file object to access the file
	*/
	{
		File file( fileName );		
		System::println( Format("The file %ls's size: %d") 
						% fileName.getFileName().c_str()
						% (ulong32)file.getSize() );


		/**
		Make a copy of the file
		*/
		file.copyTo( fileName.getPathName(true) +
			FilePath::getDirectorySeparator() +
			fileName.getBaseName() + "-copy" + fileName.getExtension() );

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
				finder->free();
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

		fos->free();

		FileInputStream* fis = f1.getInputStream();

		TextInputStream tis(fis);
		String s;
		tis >> s;
		
		System::println( Format("File contents of \"%ls\" :\n%ls") % f1.getName().c_str() % s.c_str() );

		fis->free();

		f1.remove();

	}

	FoundationKit::terminate();
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:37  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.4.2  2005/04/17 17:19:09  iamfraggle
*Small fixes
*
*Revision 1.3.4.1  2005/04/17 15:11:44  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.3  2004/08/07 02:47:02  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.4.10  2004/08/01 23:40:08  ddiego
*fixed a few osx bugs
*
*Revision 1.2.4.9  2004/07/29 02:39:13  ddiego
*fixed a bug with File::getINputStream and File::getOutputStream.
*
*Revision 1.2.4.8  2004/07/25 17:04:02  marcelloptr
*project changes
*
*Revision 1.2.4.7  2004/07/23 00:56:37  ddiego
*added the latest changes to the File and Directory finder classes.
*
*Revision 1.2.4.6  2004/07/19 04:08:52  ddiego
*more files and directories integration. Added Marcello's Directories example as well
*
*Revision 1.2.4.5  2004/05/03 03:44:52  ddiego
*This checks in a bunch of changes to the FoundationKit for OSX
*porting. The thread, mutex, semaphor, condition, and file peers
*have all been implemented and tested. The file peer could be improved
*and needs search functionality. The locale peer is only partially
*complete, but the functions will return values. The unicode transition
*is also finished and works OK now.
*
*Revision 1.2.4.4  2004/04/29 03:40:53  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


