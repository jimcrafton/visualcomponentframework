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
$Id$
*/
