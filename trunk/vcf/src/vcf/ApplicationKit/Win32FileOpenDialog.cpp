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
		tmp += *filter + '\0';
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
		tmp += *filter + '\0';
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
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:57  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/04/09 17:20:36  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.2.4.2  2005/03/28 18:16:50  marcelloptr
*minor fixes: TCHAR removed
*
*Revision 1.2.4.1  2005/02/28 04:51:56  ddiego
*fixed issue in handling componenent state and events when in design mode
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/18 14:45:18  ddiego
*integrated Marcello's new File/Directory API changes into both
*the FoundationKit and the ApplicationKit. Many, many thanks go out
*to Marcello for a great job with this. This adds much better file searching
*capabilities, with many options for how to use it and extend it in the
*future.
*
*Revision 1.1.2.5  2004/07/09 18:48:05  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.4  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/05/04 17:16:07  ddiego
*updated some win32 stuff for unicode compliance
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.15  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.14.2.4  2003/09/17 03:27:56  ddiego
*added a fix for bug [ 807416 ] CommonFileDialog needs setFileExtension
*added methods for getting data from the open and save dialogs in the
*DocumentManager
*
*Revision 1.14.2.3  2003/08/23 02:01:29  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.14.2.2  2003/08/20 22:55:18  ddiego
*got rid of some older methods for StringUtils, should be using the FilePath
*class instead
*
*Revision 1.14.2.1  2003/08/17 18:18:05  ddiego
*added some of Marcellos fixes, notably the one to fix CRLF problems in teh
*edit control
*
*Revision 1.14  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.13.2.1  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.13  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.12.2.1  2003/03/12 03:12:33  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:50  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.2.3  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.11.2.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.11.2.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.11  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.10.4.1  2002/11/09 05:30:19  ddiego
*this fixes bug [ 634795 ] Open Workspace on non-existent file
*causes VCF Builder to crash. All that needed doing was to add
*the OFN_FILEMUSTEXIST flag to the GetFileName API call. Too bad
*all the bugs aren't this easy.... !
*
*Revision 1.10  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.9.6.2  2002/08/15 03:27:45  ddiego
*small mod to parser
*
*Revision 1.9.6.1  2002/08/15 01:12:58  ddiego
*changes to the xmake makefiles adding preliminary support for MinGW
*WARJNING: doesn't yet compile, or at least not on my machine
*
*Revision 1.9  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.2  2002/04/27 15:52:30  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.8.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.8  2002/01/28 05:07:42  ddiego
*removed wim32implementer - old file
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


