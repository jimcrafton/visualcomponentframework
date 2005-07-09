//Directories.cpp

#include "vcf/FoundationKit/FoundationKit.h"


using namespace VCF;






Directory::Finder::DisplayMode g_displayMode = Directory::Finder::dmAny;
Directory::Finder::DisplayMode g_displayOrder = Directory::Finder::dmAny;

bool g_showFilenames = false;
bool g_showDirnames = false;
bool g_testingFileAttributes = false;
bool g_testingTimeStamps = false;


class FinderTest {
public:
	virtual void loopTest(  const String& filepath, const bool& recurse = false ) {
		return;
	}

public:
	int countFiles_;
	int countDirectories_;
};



class FinderTest1 : public FinderTest {
public:
	virtual void loopTest(  const String& filepath, const bool& recurse = false ) {
		loop(  filepath, recurse, true );
	}

	void loop( const String& filepath, const bool& recurse = false, const bool& start = true ) {
		if ( start ) {
			countFiles_ = 0;
			countDirectories_   = 0;
		}

		String filename, path;
		File* file = NULL;

		Directory dir( FilePath::getExpandedRelativePathName( filepath ) );

		Directory::Finder* finder = dir.findFiles();

		while ( finder->nextElement() ) {
			file = finder->getCurrentElement();

			filename = file->getName();
			path = filepath + filename;

			if ( file->isDirectory() ) {
				VCF_ASSERT( !( filename == L"." || filename == L".." ) );

				countDirectories_ ++;
				if ( g_showDirnames ) System::print ( Format("[%s]\n") % path.ansi_c_str() );
				if ( recurse ) {
					this->loop( path + L"/", recurse, false );
				}
			} else {
				countFiles_ ++;
				if ( g_showFilenames ) System::print ( Format("%s\n") % path.ansi_c_str() );
			}
		}
		finder->free();

	}

};



FileSearchFilterStandard filterFilesObj2( L"*.h" );

class FinderTest2 : public FinderTest {
public:
	virtual void loopTest(  const String& filepath, const bool& recurse = false ) {
		loop(  filepath, recurse, true );
	}

	void loop( const String& filepath, const bool& recurse = false, const bool& start = true ) {
		if ( start ) {
			countFiles_ = 0;
			countDirectories_   = 0;
		}

		String filename, path;

		File* file = NULL;

		Directory dir( FilePath::getExpandedRelativePathName( filepath ) );

		Directory::Finder* finder = dir.findFiles( &filterFilesObj2 );
		finder->setStatMask( File::smAttributes );
		while ( finder->nextElement() ) {
			file = finder->getCurrentElement();
			filename = file->getName();
			path = filepath + filename;

			if ( file->isDirectory() ) {
				VCF_ASSERT( !( filename == L"." || filename == L".." ) );

				countDirectories_ ++;
				if ( g_showDirnames ) System::print ( Format("[%s]\n") % path.ansi_c_str() );
				if ( recurse ) {
					this->loop( path + L"/", recurse, false );
				}
			} else {
				countFiles_ ++;
				if ( g_showFilenames ) System::print ( Format("%s\n") % path.ansi_c_str() );
			}
		}
		finder->free();
	}

};

String formatDirectoryInfos( File* file, const Directory::Finder* finder )
{
	String filename = file->getName();
	DateTime dt = file->getDateModified().toLocal();

	String st = StringUtils::format( dt, L"%d/%m/%Y %H:%M:%S" );

	String text = Format(L"[%d] %s %10s %5s [%s]\n") 
					% finder->getRecursionLevel() % st.c_str() 
					% L"" % L"" % filename.c_str();

	return text;
}

String formatFileInfos( File* file, const Directory::Finder* finder )
{
	String filename = file->getName();
	DateTime dt = file->getDateModified().toLocal();

	String st = StringUtils::format( dt, L"%d/%m/%Y %H:%M:%S" );
	String sz = StringUtils::toString( file->getSize() );
	String sa = Format("%c%c%c%c%c")% (file->isArchive()?'a':' ')
				% (file->isReadOnly()?'r':' ') % (file->isHidden()?'h':' ')
                % (file->isSystem()?'s':' ') % (file->isExecutable()?'x':' ') ;

	String text = Format(L"[%d] %s %10s %s  %s\n") 
					% finder->getRecursionLevel() % st.c_str() % sz.c_str()
					% sa.c_str() % filename.c_str();

	return text;
}

class FinderTest3 : public FinderTest {
public:
	virtual void loopTest(  const String& filepath, const bool& recurse = false ) {

		countFiles_ = 0;
		countDirectories_   = 0;

		String filename;
		String text;

		File* file = NULL;
		Directory::Finder* finder = NULL;

		Directory dir( FilePath::getExpandedRelativePathName( filepath ) );

		FileSearchFilterStandard filterFilesObj3( L"*.cpp"/*, L"c/g"*/ );

		try {

			finder = dir.findFiles( &filterFilesObj3, false );
			finder->setDisplayMode( g_displayMode ); //Directory::Finder::dmAny );
			finder->setDisplayOrder( g_displayOrder ); //Directory::Finder::dmFiles );
			finder->setKeepOSSpecificFormat( true );
			finder->setMaskFilterFileAttribs ( File::faMaskAll );
			finder->ignoreStat( File::smMaskDateAll | File::smSize );
			finder->setRecursion( recurse, 10 );

			while ( finder->nextElement() ) {
				file = finder->getCurrentElement();
				filename = file->getName();

				if ( file->isDirectory() ) {
					countDirectories_ ++;

					if ( g_showDirnames ) {
						text = formatDirectoryInfos( file, finder );
						printf( text.ansi_c_str() );
						StringUtils::trace( text );
					}
				}
				else {
					countFiles_ ++;

					if ( g_showDirnames ) {
						text = formatFileInfos( file, finder );
						printf( text.ansi_c_str() );
						StringUtils::trace( text );
					}

					// setting file attributes
					if ( g_testingFileAttributes ) {
						File::FileAttributes fa = file->getFileAttributes();
						file->setFileAttributes( (File::FileAttributes) ( fa | File::faReadOnly ) );

						StringUtils::trace( formatFileInfos( file, finder ) );
					}


					// setting time stamp
					if ( g_testingTimeStamps ) {
						// this increase the timestamp of one day
						file->setDateModified( file->getDateModified().incrDay( 1 ) );

						StringUtils::trace( formatFileInfos( file, finder ) );

						// this set the time of the file to now
						// this function must be completed though !
						// see its implementation
						//file->updateTime();
						//
						//StringUtils::trace( formatFileInfos( file, finder ) );
					}

				}
			}

		}
		catch ( BasicException& e ) {
			System::errorPrint( &e );
		}

		Object::objectAllocationCount();

		//Object::dumpDebugInfo();

		finder->free();

		Object::objectAllocationCount();

		//Object::dumpDebugInfo();
	}

};




void test( FinderTest& finderTest, const String& name, const bool& recurse = false )
{
	printf( String( "\nTesting: " + name + "\n" ).ansi_c_str() );

	String vcfIncludes = System::getEnvironmentVariable( "VCF_INCLUDE" );

	if ( vcfIncludes.empty() ) {
		printf( "No \"VCF_INCLUDE\" environment variable found!\n" );
		return;
	}

	DateTime startTime = DateTime::now();

	int countTot = 0;

	finderTest.loopTest( vcfIncludes, recurse );

	DateTime stopTime = DateTime::now();
	DateTimeSpan deltaTime = stopTime - startTime;
	double td = (1.0 * (double)deltaTime.getTotalMilliseconds())/1000;
	System::println( Format("[%s] files: %d, subdirs: %d  Total time: %.3f seconds\n")
					% name.ansi_c_str() % finderTest.countFiles_
					% finderTest.countDirectories_ % td );
}

void test()
{
	g_showDirnames = true;
	g_showFilenames = true;

	//FinderTest1 finderTest0 = FinderTest1();
	//test( finderTest0, L"t0 (*)", false );

	//FinderTest1 finderTest1 = FinderTest1();
	//test( finderTest1, L"t1 (*)", true );

	//FinderTest2 finderTest2 = FinderTest2();
	//test( finderTest2, L"t2 (*.h)", true );

	FinderTest3 finderTest3 = FinderTest3();
	test( finderTest3, L"t3 (*.cpp)", true );
}

void getArguments()
{
	CommandLine cmdLine = FoundationKit::getCommandLine();

	if ( cmdLine.hasSwitch( "a" ) ){
		g_displayMode = Directory::Finder::dmAny;
	}
	if ( cmdLine.hasSwitch( "f" ) ){
		g_displayMode = Directory::Finder::dmFiles;
	}

	if ( cmdLine.hasSwitch( "d" ) ){
		g_displayMode = Directory::Finder::dmDirs;
	}	
}

int main(int argc, char *argv[])
{
	FoundationKit::init( argc, argv );

	getArguments();

	try {
		test();
		printf( "\n" );
	}
	catch ( BasicException& /*be*/ ) {
		// the error message is already shown !
		//printf( "%s", be.getMessage().ansi_c_str() );
	}

	FoundationKit::terminate();

	return 0;
}





