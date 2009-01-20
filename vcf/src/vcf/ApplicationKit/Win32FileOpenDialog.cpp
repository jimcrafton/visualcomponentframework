//Win32FileOpenDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32FileOpenDialog.h"

using namespace VCF;

Win32FileOpenDialog::Win32FileOpenDialog( Control* owner )
{
	init();
	owner_ = owner;
}


Win32FileOpenDialog::~Win32FileOpenDialog()
{

}

void Win32FileOpenDialog::init()
{

	allowsMultiSelect_ = false;
	fileMustExist_ = true;
	container_.initContainer( selectedFiles_ );
	owner_ = NULL;

}

void Win32FileOpenDialog::setTitle( const String& title )
{
	title_ = title;
}

bool Win32FileOpenDialog::executeW()
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


	//allocate enough for 255 long file names
	WCHAR* tmpFileName = NULL;

	if ( true == allowsMultiSelect_ ) {
		tmpFileName = new WCHAR[MAX_PATH * MAX_PATH];
		memset(tmpFileName, 0, (MAX_PATH * MAX_PATH)*sizeof(WCHAR));
		ofn.nMaxFile = MAX_PATH * MAX_PATH;
	}
	else {
		tmpFileName = new WCHAR[MAX_PATH];
		memset(tmpFileName, 0, MAX_PATH*sizeof(WCHAR));
		ofn.nMaxFile = MAX_PATH;
	}

	WCHAR tmpDir[MAX_PATH];
	memset(tmpDir, 0, MAX_PATH*sizeof(WCHAR));
	directory_.copy( tmpDir, directory_.size() );

	fileName_.copy( tmpFileName, fileName_.size() );


	ofn.lpstrFile = tmpFileName;
	ofn.lpstrInitialDir = tmpDir;


	WCHAR* tmpTitle = NULL;
	int titleSz = title_.size();
	if ( titleSz > 0 ){
		tmpTitle = new WCHAR[titleSz+1];
		memset( tmpTitle, 0, (titleSz+1)*sizeof(WCHAR) );
		title_.copy( tmpTitle, titleSz );
		tmpTitle[titleSz] = 0;
	}

	ofn.lpstrTitle = tmpTitle;

	ofn.Flags = OFN_EXPLORER;

	if ( true == allowsMultiSelect_ ){
		ofn.Flags |= OFN_ALLOWMULTISELECT;
	}

	if ( true == fileMustExist_ ){
		ofn.Flags |= OFN_FILEMUSTEXIST;
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
				selectedFilterIndex = ((filter - filter_.begin())/2 )+1;
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

	ofn.lpstrFilter = 	tmpFilter;

	ofn.nFilterIndex = selectedFilterIndex;

	bool result = false;

	selectedFiles_.clear();

	selectedFilter_ = "";

	if ( GetOpenFileNameW( &ofn ) ){
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
			selectedFiles_.push_back( fp.getBaseName( true ) );
			directory_ = fp.getPathName(true);
		}

		if ( ofn.nFilterIndex > 0 ) {
			int index = ((ofn.nFilterIndex-1) * 2) + 1;

			selectedFilter_ = filter_[index];
		}
	}


	delete [] tmpFileName;

	delete [] tmpTitle;

	delete [] tmpFilter;

	return result;
}

bool Win32FileOpenDialog::executeA()
{
	OPENFILENAMEA ofn;
	memset( &ofn, 0, sizeof(OPENFILENAMEA) );
	ofn.lStructSize = sizeof(ofn);
	HWND ownerWnd = NULL;
	if ( NULL != owner_ ){
		ControlPeer* impl = owner_->getPeer();
		ownerWnd = (HWND)impl->getHandleID();
	}

	ofn.hwndOwner = ownerWnd;
	ofn.hInstance = NULL;


	//allocate enough for 255 long file names
	char* tmpFileName = NULL;

	if ( true == allowsMultiSelect_ ) {
		tmpFileName = new char[MAX_PATH * MAX_PATH];
		memset(tmpFileName, 0, (MAX_PATH * MAX_PATH)*sizeof(char) );
		ofn.nMaxFile = MAX_PATH * MAX_PATH;
	}
	else {
		tmpFileName = new char[MAX_PATH];
		memset(tmpFileName, 0, MAX_PATH*sizeof(char));
		ofn.nMaxFile = MAX_PATH;
	}

	char tmpDir[MAX_PATH];
	memset(tmpDir, 0, MAX_PATH*sizeof(char));
	directory_.copy( tmpDir, directory_.size() );

	fileName_.copy( tmpFileName, fileName_.size() );


	ofn.lpstrFile = tmpFileName;
	ofn.lpstrInitialDir = tmpDir;


	char* tmpTitle = NULL;
	int titleSz = title_.size();
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

	if ( true == fileMustExist_ ){
		ofn.Flags |= OFN_FILEMUSTEXIST;
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
				selectedFilterIndex = ((filter - filter_.begin())/2 )+1;
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

	ofn.lpstrFilter = 	tmpFilter;

	ofn.nFilterIndex = selectedFilterIndex;

	bool result = false;

	selectedFiles_.clear();

	selectedFilter_ = "";

	if ( GetOpenFileNameA( &ofn ) ){
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
			selectedFiles_.push_back( fp.getBaseName( true ) );
			directory_ = fp.getPathName(true);
		}

		if ( ofn.nFilterIndex > 0 ) {
			int index = ((ofn.nFilterIndex-1) * 2) + 1;

			selectedFilter_ = filter_[index];
		}
	}


	delete [] tmpFileName;

	delete [] tmpTitle;

	delete [] tmpFilter;

	return result;
}

bool Win32FileOpenDialog::execute()
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

void Win32FileOpenDialog::addFilter( const String & description, const String & extension )
{
	filter_.push_back( description );
	filter_.push_back( extension );
}

void Win32FileOpenDialog::setDirectory( const String & directory )
{
	directory_ = directory;
}

void Win32FileOpenDialog::setFileName( const String & filename )
{
	fileName_ = filename;
}

String Win32FileOpenDialog::getFileName()
{
	return fileName_;
}

String Win32FileOpenDialog::getDirectory()
{
	return directory_;
}

String Win32FileOpenDialog::getFileExtension()
{
	return selectedFilter_;
}

uint32 Win32FileOpenDialog::getSelectedFileCount()
{
	return selectedFiles_.size();
}

Enumerator<String>* Win32FileOpenDialog::getSelectedFiles()
{
	return container_.getEnumerator();
}

void Win32FileOpenDialog::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	allowsMultiSelect_ = allowsMultiSelect;
}

void Win32FileOpenDialog::setFileMustExist( const bool& fileMustExist )
{
	fileMustExist_ = fileMustExist;
}

void Win32FileOpenDialog::setSelectedFilter( const String& selectedFilter )
{
	selectedFilter_ = selectedFilter;
}


/**
$Id$
*/
