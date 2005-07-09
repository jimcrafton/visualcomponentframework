//Win32FolderBrowseDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32FolderBrowseDialog.h"

using namespace VCF;

Win32FolderBrowseDialog::Win32FolderBrowseDialog()
{

}

Win32FolderBrowseDialog::~Win32FolderBrowseDialog()
{

}

void Win32FolderBrowseDialog::setTitle( const String& title )
{
	title_ = title;
}

HTREEITEM Win32FolderBrowseDialog::getDriveRoot( HWND treeCtrl, HTREEITEM desktop, const String& driveName, std::vector<String>& pathComponents )
{
	HTREEITEM result = NULL;

	bool found = false;

	if ( !pathComponents.empty() ) {
		HTREEITEM parent = TreeView_GetChild( treeCtrl, desktop );
		while ( (parent != NULL) && (!found) ) {
			HTREEITEM child = TreeView_GetChild( treeCtrl, parent );
			while ( (child != NULL) && (!found) ) {
				if ( System::isUnicodeEnabled() ) {
					TVITEMW item;
					memset( &item, 0, sizeof(item) );
					VCFChar text[256];
					item.mask = TVIF_TEXT;
					item.hItem = child;
					item.pszText = text;
					item.cchTextMax = 255;
					if ( SendMessage( treeCtrl, TVM_GETITEMW, 0, (LPARAM)&item ) ) {
						String tmp = StringUtils::lowerCase( item.pszText );
						//tmp.append( item.pszText, item.cchTextMax );

						int pos = tmp.find( driveName );
						if ( pos != String::npos ) {
							result = child;
							found = true;
							break;
						}
					}
					else {
						break;//quit the loop
					}
				}
				else {
					TVITEMA item;
					memset( &item, 0, sizeof(item) );
					char text[256];
					item.mask = TVIF_TEXT;
					item.hItem = child;
					item.pszText = text;
					item.cchTextMax = 255;
					if ( SendMessage( treeCtrl, TVM_GETITEMA, 0, (LPARAM)&item ) ) {
						AnsiString tmp = StringUtils::lowerCase( String(item.pszText) );

						int pos = tmp.find( driveName );
						if ( pos != String::npos ) {
							result = child;
							found = true;
							break;
						}
					}
					else {
						break;//quit the loop
					}
				}


				child = TreeView_GetNextSibling( treeCtrl, child );
			}
			parent = TreeView_GetNextSibling( treeCtrl, parent );
		}

	}

	return result;
}

HTREEITEM Win32FolderBrowseDialog::getFinalItem( HWND treeCtrl, HTREEITEM driveRoot, std::vector<String>& pathComponents )
{
	HTREEITEM result = NULL;

	TreeView_Expand( treeCtrl, driveRoot, TVE_EXPAND );

	std::vector<String>::iterator it = pathComponents.begin();
	bool directorySet = false;
	while ( it != pathComponents.end() ) {
		String compareTo = StringUtils::lowerCase( *it );
		if ( compareTo[compareTo.size()-1] == '/' ) {
			compareTo.erase( compareTo.size()-1, 1 );
		}
		if ( !compareTo.empty() ) {
			HTREEITEM child = TreeView_GetChild( treeCtrl, driveRoot );
			while ( child != NULL ) {
				if ( System::isUnicodeEnabled() ) {
					TVITEMW item;
					memset( &item, 0, sizeof(item) );
					VCFChar text[256];
					item.mask = TVIF_TEXT;
					item.hItem = child;
					item.pszText = text;
					item.cchTextMax = 255;

					if ( SendMessage( treeCtrl, TVM_GETITEMW, 0, (LPARAM)&item ) ) {
						String tmp = StringUtils::lowerCase( item.pszText );

						if ( tmp == compareTo ) {
							driveRoot = child;
							directorySet = true;
							TreeView_Expand( treeCtrl, driveRoot, TVE_EXPAND );
							result = driveRoot;
							break;
						}
					}
					else {
						break;//quit the loop
					}
				}
				else {
					TVITEMA item;
					memset( &item, 0, sizeof(item) );
					char text[256];
					item.mask = TVIF_TEXT;
					item.hItem = child;
					item.pszText = text;
					item.cchTextMax = 255;

					if ( SendMessage( treeCtrl, TVM_GETITEMA, 0, (LPARAM)&item ) ) {
						String tmp = StringUtils::lowerCase( item.pszText );

						if ( tmp == compareTo ) {
							driveRoot = child;
							directorySet = true;
							TreeView_Expand( treeCtrl, driveRoot, TVE_EXPAND );
							result = driveRoot;
							break;
						}
					}
					else {
						break;//quit the loop
					}
				}


				child = TreeView_GetNextSibling( treeCtrl, child );
			}
			if ( !directorySet ) {
				break;
			}
		}
		it ++;
	}

	return result;
}


int CALLBACK Win32FolderBrowseDialog::BrowseDlgCallbackProc( HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData )
{
	if ( BFFM_INITIALIZED  == uMsg ) {
		Win32FolderBrowseDialog* thisPtr = (Win32FolderBrowseDialog*)lpData;

		String directory = thisPtr->getDirectory();

		HWND treeCtrl = ::GetDlgItem( hwnd, Win32FolderBrowseDialog::TreeControlID );
		if ( (NULL != treeCtrl) && (!directory.empty()) ) {
			//get the desktop or root item
			HTREEITEM desktop = TreeView_GetRoot( treeCtrl );
			//get the first level, then open up the first child for each one
			//amd look for the ":" in hte name if it is there we have "found"
			//the "My Computer" parent (can't rely on using "My Computer" since the
			//user is free to rename it

			
			FilePath dirPath = directory;
			directory = dirPath;

			if ( directory[directory.size()-1] != '/' ) {
				directory += FilePath::getDirectorySeparator();
			}
			dirPath = directory;

			std::vector<String> pathComponents = dirPath.getPathComponents();
			String driveName = StringUtils::lowerCase( dirPath.getDriveName() );

			HTREEITEM driveRoot = Win32FolderBrowseDialog::getDriveRoot( treeCtrl, desktop, driveName, pathComponents );

			if ( NULL != driveRoot ) {
				//OK we're in business now

				HTREEITEM finalItem = Win32FolderBrowseDialog::getFinalItem( treeCtrl, driveRoot, pathComponents );

				if ( NULL == finalItem ) {
					thisPtr->setDirectory("");
				}

				if ( NULL != finalItem ) {
					TreeView_SelectItem( treeCtrl, finalItem );
				}
			}

		}
	}
	return 0;
}

bool Win32FolderBrowseDialog::execute()
{
	bool result = false;
	BROWSEINFO info;
	memset( &info, 0, sizeof(BROWSEINFO) );
	TCHAR displayName[MAX_PATH];
	memset(displayName,0,sizeof(displayName));

	int sz = title_.size() + 1;
	TCHAR* title = new TCHAR[sz];
	memset( title, 0, sz*sizeof(TCHAR) );
	title_.copy( title, title_.size() );

	info.hwndOwner = ::GetActiveWindow();
	info.pidlRoot = NULL;
	info.pszDisplayName = displayName;
	info.lpszTitle = title;
	info.ulFlags = 0;
	info.lpfn = Win32FolderBrowseDialog::BrowseDlgCallbackProc;
	info.lParam = (LPARAM)this;

	LPITEMIDLIST itemIDList = SHBrowseForFolder( &info );
	if ( NULL != itemIDList ){
		TCHAR path[MAX_PATH];
		memset(path,0,sizeof(path));
		if ( SHGetPathFromIDList( itemIDList, path ) ){
			directory_ = path;
			result = true;
		}
	}

	return result;

}

void Win32FolderBrowseDialog::setDirectory( const String & directory )
{
	directory_ = directory;
}

String Win32FolderBrowseDialog::getDirectory()
{
	return directory_;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:58  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/04/09 17:20:36  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/11/21 00:19:10  ddiego
*fixed a few more res loading bugs, and added yet another resource example.
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.13.2.1  2004/04/21 02:17:25  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.13  2004/04/03 15:48:47  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.12.6.1  2004/03/26 01:00:02  ddiego
*fixed a C++ bug in the implementation of the
*Win32FolderBrowseDialog class. This was showing up when compiling
*for VC7.1.
*
*Revision 1.12  2003/05/17 20:37:36  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.2  2003/03/23 03:23:57  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.2.1  2003/03/12 03:12:37  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:51  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.2.3  2003/01/08 00:19:53  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.10.2.2  2002/12/27 23:04:54  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.10.2.1  2002/12/02 00:38:35  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.10  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.9.10.1  2002/10/28 05:40:00  ddiego
*finished basics for adding new forms, adding interface for dealing with resources
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


