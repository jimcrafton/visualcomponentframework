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

bool Win32FileSaveDialog::execute()
{

	OPENFILENAME ofn;
	memset( &ofn, 0, sizeof(OPENFILENAME) );
	ofn.lStructSize = sizeof(ofn);
	HWND ownerWnd = NULL;
	if ( NULL != owner_ ){
		ControlPeer* impl = owner_->getPeer();
		ownerWnd = (HWND)impl->getHandleID();
	}

	ofn.hwndOwner = ownerWnd;
	ofn.hInstance = NULL;
	TCHAR tmpFileName[_MAX_PATH];
	memset(tmpFileName, 0, _MAX_PATH);
	TCHAR tmpDir[_MAX_PATH];
	memset(tmpDir, 0, _MAX_PATH);
	directory_.copy( tmpDir, directory_.size() );

	fileName_.copy( tmpFileName, fileName_.size() );

	ofn.lpstrFile = tmpFileName;
	ofn.lpstrInitialDir = tmpDir;
	ofn.nMaxFile = _MAX_PATH;

	TCHAR* tmpTitle = NULL;
	if ( title_.size() > 0 ){
		tmpTitle = new TCHAR[title_.size()+1];
		memset( tmpTitle, 0, title_.size()+1 );
		title_.copy( tmpTitle, title_.size() );
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
				selectedFilterIndex = (filter - filter_.begin())+1;
				break;
			}

			filter++;
		}
	}


	int size = _MAX_PATH * filter_.size();
	TCHAR *tmpFilter = new TCHAR[size];
	memset( tmpFilter, 0, size );

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

	if ( GetSaveFileName( &ofn ) ){
		result = true;
		TCHAR* fileStart = (char*)(ofn.lpstrFile + (ofn.nFileOffset-1));
		if ( *fileStart == '\0' ){

			directory_ = ofn.lpstrFile; //this represents the dir path - everything after this will be the file names

			TCHAR* s = fileStart + 1;
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



	delete [] tmpFilter;

	delete [] tmpTitle;

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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.9  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.2.3  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.8.2.2  2003/09/17 03:27:56  ddiego
*added a fix for bug [ 807416 ] CommonFileDialog needs setFileExtension
*added methods for getting data from the open and save dialogs in the
*DocumentManager
*
*Revision 1.8.2.1  2003/08/20 22:55:18  ddiego
*got rid of some older methods for StringUtils, should be using the FilePath
*class instead
*
*Revision 1.8  2003/08/09 02:56:46  ddiego
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
*Revision 1.7.2.1  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.7  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.2.1  2003/03/12 03:12:35  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:50  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.14.3  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5.14.2  2002/12/27 23:04:52  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.5.14.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.5  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.2  2002/04/27 15:52:30  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.4.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.4  2002/01/28 05:07:42  ddiego
*removed wim32implementer - old file
*
*Revision 1.3  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


