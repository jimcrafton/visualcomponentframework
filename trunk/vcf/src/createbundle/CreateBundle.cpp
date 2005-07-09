//CreateBundle.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
createbundle is a little utility that creates a bundle diredtory
tree. It takes a source directory, a destination directory, and a bundle name. 
From this it creates the proper bundle directory hierarchy like so:
 <destination dir>/
	Desktop.ini (created only for Win32)
	Contents/
		Info.plist (copied from <source dir>/Info.plist)
		<OSName>/
			<CompilerName>/
		Resources/
			<bundle name>.ico (copied from the <source dir>/<bundle name>.ico)

The <destination dir> gets marked as a system folder so that the entries in the Desktop.ini
file will show the correct icon for the folder.

If you were to execute createbundle -src MyApp -dest release/MyApp.exe -name MyApp
the following would be created (assuming this is run from Win32, with a VC6 build)
release/MyApp.exe/
	Desktop.ini 
	Contents/
		Info.plist
		WindowsNT/
			VC6/
		Resources/
			MyApp.ico 


If you are going to use this to "bundle-ize" your executable, you should be 
sure to have a "Resources" right under the src directory. This directory will
be copied over into the new <destination dir>/Contents/Resources dir that 
gets created.
*/
#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;


#define USAGE	"createbundle usage.\n"\
				"Proper arguments to send to me are:\n"\
				"\t-src <source dir>\n"\
				"\t-dest <destination dir>\n"\
				"\t-bundle <bundle name>"


void copyFiles( const String& src, const String& dest ) 
{
	Directory srcDir(src);
	
	if ( !File::exists( dest ) ) {
		//create
		Directory dir;
		dir.create( dest, File::ofRead | File::ofWrite );
	}

	Directory::Finder* finder = srcDir.findFiles( "*.*" );
	if ( NULL != finder ) {
		try {
			finder->setDisplayMode( Directory::Finder::dmAny );
			FilePath srcName;
			FilePath destName;
			while ( finder->nextElement() ) {
				File* srcFile = finder->getCurrentElement();
				srcName = srcFile->getName();
				
				destName = dest + srcName.getBaseName(true);

				if ( srcFile->isDirectory() ) {
					srcName = FilePath::makeDirectoryName( srcName );
					destName = FilePath::makeDirectoryName( destName );

					//ignore nested CVS folders!
					if ( String::npos == destName.getFileName().find( "CVS/" ) ) {
						copyFiles( srcName, destName ); 
					}
				}
				else {
					srcFile->copyTo( destName );
				}
			}
		}
		catch ( BasicException& e ) {
			System::errorPrint( &e );
		}				
		finder->free();
	}
}


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	CommandLine cmdLine = FoundationKit::getCommandLine();
	if ( !cmdLine.hasSwitch( "-src" ) ) {
		System::println( "Please supply a source directory!" );
		System::println( USAGE );
		return 1;	
	}
	
	if ( !cmdLine.hasSwitch( "-dest" ) ) {
		System::println( "Please supply a dest directory!" );
		System::println( USAGE );
		return 1;	
	}

	if ( !cmdLine.hasSwitch( "-bundle" ) ) {
		System::println( "Please supply a bundle name!" );
		System::println( USAGE );
		return 1;	
	}

	
	String bundleName = cmdLine.getArgument( "-bundle", 0 );
	FilePath srcDir = cmdLine.getArgument( "-src", 0 );
	FilePath destDir = cmdLine.getArgument( "-dest", 0 );

	if ( srcDir.isRelativePath() ) {
		//expand it completely using the current working dir
		srcDir = FilePath::makeDirectoryName( srcDir.expandRelativePathName( System::getCurrentWorkingDirectory() ) );
	}
	else {
		srcDir = FilePath::makeDirectoryName( srcDir ); 
	}

	if ( destDir.isRelativePath() ) {
		//expand it completely using the current working dir
		destDir = FilePath::makeDirectoryName( destDir.expandRelativePathName( System::getCurrentWorkingDirectory() ) );
	}
	else {
		destDir = FilePath::makeDirectoryName( destDir ); 
	}

	String contentDir = destDir + "Contents" + FilePath::getDirectorySeparator();


	if ( System::getOSName().find( "Windows" ) != String::npos ) {
		//Windows!
		String infoFileName = srcDir + "Info.plist";

		if ( !File::exists( infoFileName ) ) {
			infoFileName = srcDir + "Info.xml";
			if ( !File::exists( infoFileName ) ) {
				infoFileName = "";
			}
		}


		if ( !infoFileName.empty() ) {
			try { 

				if ( !File::exists( contentDir ) ) {
					//create the output dir!
					Directory dir;
					dir.create( contentDir, File::ofRead | File::ofWrite );
				}

				File infoFile( infoFileName, File::ofRead, File::shRead );
				
				FilePath fp = infoFileName;
				
				//special block
				try {
					infoFile.copyTo( contentDir + fp.getBaseName(true) );
				}
				catch ( BasicFileError& ) {
					//is it already there?
					if ( !File::exists( contentDir ) ) {
						//nope, throw the exception to our outer handler !
						throw; //we're done
					}
				}
				
				String resDir = contentDir + "Resources" + FilePath::getDirectorySeparator();
				if ( !File::exists( resDir ) ) {
					//create the output dir!
					Directory dir;
					dir.create( resDir, File::ofRead | File::ofWrite );
				}

				String binDir = contentDir + System::getOSName() + FilePath::getDirectorySeparator() +
								System::getCompiler() + FilePath::getDirectorySeparator();

				if ( !File::exists( binDir ) ) {
					//create the output dir!
					Directory dir;
					dir.create( binDir, File::ofRead | File::ofWrite );
				}


				//see if we can copy over the Resources dir from our source
				String srcResDir = srcDir + "Resources/";
				if ( File::exists( srcResDir ) ) {
					System::println( "Copying resource files from [" + srcDir );// + "] to [" + resDir + "]." );

					try {
						copyFiles( srcResDir, resDir );
					}
					catch ( BasicException& e ){
						System::println( "Copy failed: \n" + e.getMessage() );
					}

				}
				else{
					System::println( "No resource directory found in [" + srcDir + "]." );
				}



				String srcIcoFile = srcDir + bundleName + ".ico";
				String missingIcoFile;

				if ( File::exists( srcIcoFile ) ) {
					//copy it over!	
					File ico(srcIcoFile);
					try { 
						ico.copyTo( resDir + bundleName + ".ico" );
					}
					catch ( BasicException& ) {
						System::println( "Warning: failed to copy over bundle .ico file." );
					}
				}
				else {
					//warn about the lack of an ico file!
					missingIcoFile = ";Please put a valid ICO file in the Contents\\Resources\\ directory!\r\n";
				}

				//create Desktop.ini				
				String desktopIni = "[.ShellClassInfo]\r\n" + missingIcoFile + ""\
									"IconFile=\"Contents\\Resources\\" + bundleName + ".ico\"\r\n"\
									"IconIndex=0\r";

				//add extraneous info just to be cool!

				ProgramInfo* progInfo = System::getProgramInfoFromFileName( destDir );
				if ( NULL != progInfo ) {

					desktopIni +="\nInfoTip=";
					desktopIni += "Application bundle: " + bundleName + ". " + progInfo->getCopyright();
					
					desktopIni += "\r";
					delete progInfo;
				}



				FileOutputStream fs ( destDir + "Desktop.ini" );
				TextOutputStream ts(&fs);
				ts << desktopIni;
				fs.close();



				//last step - mark the top level directory as a system dir
				//so that it picks up the icon specified in the Desktop.ini
				//file
				Process proc;
				String dest = destDir;
				if ( dest[dest.size()-1] == FilePath::DirectorySeparator ) {
					//remove it, the attrib command doesn't like it???

					dest.erase( dest.size()-1, 1 );
				}
				proc.createProcess( "attrib", "+s " + FilePath::transformToOSSpecific(dest) );

			}
			catch ( BasicException& e ) {
				System::println( e.getMessage() );
				return 1;
			}
		}
		else {
			//bail!!!!
			System::println( "You don't have the right info - please create a valid Info.plist or Info.xml file in your source directory." );
			return 1;
		}
	}


	FoundationKit::terminate();
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:48  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.6  2005/02/16 05:09:30  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.1.2.5  2004/12/22 02:58:22  marcelloptr
*eliminated a warning for unreferenced variable
*
*/


