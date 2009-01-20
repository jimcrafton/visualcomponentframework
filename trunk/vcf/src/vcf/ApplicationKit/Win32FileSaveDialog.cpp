//Win32FileSaveDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32FileSaveDialog.h"

//Win32FileSaveDialog.cpp


using namespace VCF;

Win32FileSaveDialog::Win32FileSaveDialog( Control* owner )
{
	init();
	owner_ = owner;
}


Win32FileSaveDialog::~Win32FileSaveDialog()
{

}

void Win32FileSaveDialog::init()
{

	allowsMultiSelect_ = false;
	container_.initContainer( selectedFiles_ );
	owner_ = NULL;

}

void Win32FileSaveDialog::setTitle( const String& title )
{
	title_ = title;
}

bool Win32FileSaveDialog::executeW()
{

	OPENFILENAMEW ofn;
	memset( &ofn, 0, sizeof(OPENFILENAMEW) );
	ofn.lStructSize = sizeof(ofn);
	HWND ownerWnd = NULL;
	if ( NULL != owner_ ){
		ControlPeer* impl = owner_->getPeer();
		ownerWnd = (HWND)impl->getHandleID();
	}	
	else {
		ownerWnd = ::GetActiveWindow();
	}

	ofn.hwndOwner = ownerWnd;
	ofn.hInstance = NULL;



	WCHAR tmpFileName[_MAX_PATH];
	memset(tmpFileName, 0, sizeof(tmpFileName));

	if ( !FilePath::getBaseName(fileName_).empty() ) {
		String fileName = FilePath::transformToOSSpecific( fileName_ );
		fileName.copy( tmpFileName, fileName.size() );
	}

	WCHAR tmpDir[_MAX_PATH];
	memset(tmpDir, 0, sizeof(tmpDir));
	String directory = FilePath::transformToOSSpecific( directory_ );
	directory.copy( tmpDir, directory.size() );

	ofn.lpstrFile = tmpFileName;
	ofn.lpstrInitialDir = tmpDir;
	ofn.nMaxFile = _MAX_PATH;

	WCHAR* tmpTitle = NULL;

	size_t titleSz = title_.size();
	if ( titleSz > 0 ){
		tmpTitle = new WCHAR[titleSz+1];
		memset( tmpTitle, 0, (titleSz+1)*sizeof(WCHAR) );
		title_.copy( tmpTitle, titleSz );
	}

	ofn.lpstrTitle = tmpTitle;

	ofn.Flags = OFN_EXPLORER;

	if ( true == allowsMultiSelect_ ){
		ofn.Flags |= OFN_ALLOWMULTISELECT;
	}

	if ( filter_.size() == 0 ) {//then add a default filter
		filter_.push_back( "Any File" );
		filter_.push_back( "*.*" );
	}


	int selectedFilterIndex = 0;

	std::vector<String>::iterator filter = filter_.begin();

	if ( !selectedFilter_.empty() ) {
		std::vector<String>::iterator filter = filter_.begin();
		while ( filter != filter_.end() ){
			filter++;

			String s = *filter;
			if ( String::npos != s.find( selectedFilter_ ) ) {
				selectedFilterIndex = ((filter - filter_.begin())/2)+1;
				break;
			}

			filter++;
		}
	}


	int size = _MAX_PATH * filter_.size();
	WCHAR *tmpFilter = new WCHAR[size];
	memset( tmpFilter, 0, size*sizeof(WCHAR) );

	filter = filter_.begin();
	String tmp;
	while ( filter != filter_.end() ){
		String s = *filter;
		if ( ((filter - filter_.begin()) % 2) != 0 ) {
			if ( s.find( "*." ) == String::npos ) {
				s = "*." + s;
			}
		}

		tmp += s + '\0';
		filter++;		
	}
	tmp += '\0';
	tmp.copy( tmpFilter, tmp.size() );

	ofn.lpstrFilter = tmpFilter;
	ofn.nFilterIndex = selectedFilterIndex;

	bool result = false;

	selectedFiles_.clear();

	selectedFilter_ = "";

	if ( GetSaveFileNameW( &ofn ) ) {
		result = true;
		WCHAR* fileStart = (WCHAR*)(ofn.lpstrFile + (ofn.nFileOffset-1));
		if ( *fileStart == '\0' ){

			directory_ = ofn.lpstrFile; //this represents the dir path - everything after this will be the file names

			WCHAR* s = fileStart + 1;
			bool atTheEnd = false;
			if ( *(s+1) == '\0' ){//double null terminators end the string
				atTheEnd = true;
			}
			while ( !atTheEnd ){
				selectedFiles_.push_back( s );
				while ( *s != '\0' ){
					s++;
				}
				s++;//increment past the null seperator
				if ( *(s+1) == '\0' ){
					atTheEnd = true;
				}
			}
			fileName_ = "";
		}
		else {
			fileName_ = ofn.lpstrFile;
			FilePath fp = fileName_;
			directory_ = fp.getPathName(true);
		}

		if ( ofn.nFilterIndex > 0 ) {
			int index = ((ofn.nFilterIndex-1) * 2) + 1;

			selectedFilter_ = filter_[index];
		}

	}
	else {
		 uint32 err = CommDlgExtendedError();
		 if ( 0 != err ) {
			String msg = Format( "Unable to open the FileSaveDialog. Error code: %u\r\n" ) % err;
			StringUtils::trace( msg );
			Dialog::showMessage( msg );
		 }
	}


	delete [] tmpFilter;

	delete [] tmpTitle;

	return result;
}

bool Win32FileSaveDialog::executeA()
{
	OPENFILENAMEA ofn;
	memset( &ofn, 0, sizeof(OPENFILENAMEA) );
	ofn.lStructSize = sizeof(ofn);
	HWND ownerWnd = NULL;
	if ( NULL != owner_ ){
		ControlPeer* impl = owner_->getPeer();
		ownerWnd = (HWND)impl->getHandleID();
	}	
	else {
		ownerWnd = ::GetActiveWindow();
	}

	ofn.hwndOwner = ownerWnd;
	ofn.hInstance = NULL;

	char tmpFileName[_MAX_PATH];
	memset(tmpFileName, 0, sizeof(tmpFileName));
	
	
	if ( !FilePath::getBaseName(fileName_).empty() ) {
		String fileName = FilePath::transformToOSSpecific( fileName_ );
		fileName.copy( tmpFileName, fileName.size() );
	}	

	char tmpDir[_MAX_PATH];
	memset(tmpDir, 0, sizeof(tmpDir));
	String directory = FilePath::transformToOSSpecific( directory_ );
	directory.copy( tmpDir, directory.size() );


	ofn.lpstrFile = tmpFileName;
	ofn.lpstrInitialDir = tmpDir;
	ofn.nMaxFile = _MAX_PATH;

	char* tmpTitle = NULL;
	size_t titleSz = title_.size();
	if ( titleSz > 0 ){
		tmpTitle = new char[titleSz+1];
		memset( tmpTitle, 0, (titleSz+1)*sizeof(char) );
		title_.copy( tmpTitle, titleSz );
	}

	ofn.lpstrTitle = tmpTitle;

	ofn.Flags = OFN_EXPLORER;

	if ( true == allowsMultiSelect_ ){
		ofn.Flags |= OFN_ALLOWMULTISELECT;
	}

	if ( filter_.size() == 0 ) {//then add a default filter
		filter_.push_back( "Any File" );
		filter_.push_back( "*.*" );
	}


	int selectedFilterIndex = 0;

	std::vector<String>::iterator filter = filter_.begin();

	if ( !selectedFilter_.empty() ) {
		std::vector<String>::iterator filter = filter_.begin();
		while ( filter != filter_.end() ){
			filter++;

			String s = *filter;
			if ( String::npos != s.find( selectedFilter_ ) ) {
				selectedFilterIndex = ((filter - filter_.begin())/2)+1;
				break;
			}

			filter++;
		}
	}


	int size = _MAX_PATH * filter_.size();
	char *tmpFilter = new char[size];
	memset( tmpFilter, 0, size*sizeof(char) );

	filter = filter_.begin();
	String tmp;
	while ( filter != filter_.end() ){
		String s = *filter;
		if ( ((filter - filter_.begin()) % 2) != 0 ) {
			if ( s.find( "*." ) == String::npos ) {
				s = "*." + s;
			}
		}

		tmp += s + '\0';
		filter++;		
	}
	tmp += '\0';
	tmp.copy( tmpFilter, tmp.size() );

	ofn.lpstrFilter = tmpFilter;
	ofn.nFilterIndex = selectedFilterIndex;

	bool result = false;

	selectedFiles_.clear();

	selectedFilter_ = "";

	if ( GetSaveFileNameA( &ofn ) ) {
		result = true;
		char* fileStart = (char*)(ofn.lpstrFile + (ofn.nFileOffset-1));
		if ( *fileStart == '\0' ){

			directory_ = ofn.lpstrFile; //this represents the dir path - everything after this will be the file names

			char* s = fileStart + 1;
			bool atTheEnd = false;
			if ( *(s+1) == '\0' ){//double null terminators end the string
				atTheEnd = true;
			}
			while ( !atTheEnd ){
				selectedFiles_.push_back( s );
				while ( *s != '\0' ){
					s++;
				}
				s++;//increment past the null seperator
				if ( *(s+1) == '\0' ){
					atTheEnd = true;
				}
			}
			fileName_ = "";
		}
		else {
			fileName_ = ofn.lpstrFile;
			FilePath fp = fileName_;
			directory_ = fp.getPathName(true);
		}

		if ( ofn.nFilterIndex > 0 ) {
			int index = ((ofn.nFilterIndex-1) * 2) + 1;

			selectedFilter_ = filter_[index];
		}

	}
	else {
		 uint32 err = CommDlgExtendedError();
		 if ( 0 != err ) {
			String msg = Format( "Unable to open the FileSaveDialog. Error code: %u\r\n" ) % err;
			StringUtils::trace( msg );
		 }
	}



	delete [] tmpFilter;

	delete [] tmpTitle;

	return result;
}

bool Win32FileSaveDialog::execute()
{
	bool result = false;
	if ( System::isUnicodeEnabled() ) {
		result = executeW();
	}
	else {
		result = executeA();
	}
	return result;

}

void Win32FileSaveDialog::addFilter( const String & description, const String & extension )
{
	filter_.push_back( description );
	filter_.push_back( extension );
}

void Win32FileSaveDialog::setDirectory( const String & directory )
{
	directory_ = directory;
}

void Win32FileSaveDialog::setFileName( const String & filename )
{
	fileName_ = filename;
}

String Win32FileSaveDialog::getFileName()
{
	return fileName_;
}

String Win32FileSaveDialog::getDirectory()
{
	return directory_;
}

String Win32FileSaveDialog::getFileExtension()
{
	return selectedFilter_;
}

uint32 Win32FileSaveDialog::getSelectedFileCount()
{
	return selectedFiles_.size();
}

Enumerator<String>* Win32FileSaveDialog::getSelectedFiles()
{
	return container_.getEnumerator();
}

void Win32FileSaveDialog::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	allowsMultiSelect_ = allowsMultiSelect;
}

void Win32FileSaveDialog::setSelectedFilter( const String& selectedFilter )
{
	selectedFilter_ = selectedFilter;
}


/**
$Id$
*/
