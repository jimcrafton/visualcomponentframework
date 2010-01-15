//Win32UIShell.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Win32UIShell.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32UIShell.h"
#include <shellapi.h>
#include <shlwapi.h>

#include "thirdparty/win32/comet/interface.h"
#include "thirdparty/win32/comet/threading.h"

using namespace VCF;
using namespace comet;

Win32UIShell::Win32UIShell( UIShell* shell )
{
	shell_ = shell;
	if ( NULL == shell_ ) {
		//throw exception
	}

}

Win32UIShell::~Win32UIShell()
{

}

void Win32UIShell::shellBeginPainting( Rect* clippingRect )
{
	hClipRgn_ = NULL;
	DWORD flags = DCX_WINDOW|DCX_CACHE;

	if ( NULL != clippingRect ) {
		hClipRgn_ = ::CreateRectRgn( (int32)clippingRect->left_, (int32)clippingRect->top_, (int32)clippingRect->right_, (int32)clippingRect->bottom_ );
		flags |= DCX_INTERSECTRGN;
	}

	HDC dc = NULL;


	if ( LockWindowUpdate( ::GetDesktopWindow() ) ) {
		flags |= DCX_LOCKWINDOWUPDATE;
	}

	dc = ::GetDCEx( ::GetDesktopWindow(), hClipRgn_, flags );

	if ( NULL == dc ) {
		//throw exception !!
	}
	shell_->getContext()->getPeer()->setContextID( (OSHandleID)dc );
}

void Win32UIShell::shellEndPainting()
{
	::LockWindowUpdate( NULL );//unlocks the window update
	HDC dc = (HDC)shell_->getContext()->getPeer()->getContextID();
	shell_->getContext()->getPeer()->setContextID( (OSHandleID)0 );
	ReleaseDC( ::GetDesktopWindow(), dc );
	if ( NULL != hClipRgn_ ) {
		DeleteObject( hClipRgn_ );
	}
	InvalidateRect( ::GetDesktopWindow(), NULL, TRUE );
}

bool Win32UIShell::shellSupportsVirtualDirectories()
{
	return true;
}

bool Win32UIShell::shellHasFileSystemDirectory()
{
	return true;
}

String Win32UIShell::shellGetDirectory()
{
	String result = "";

	IMalloc* mallocObj = NULL;
	HRESULT hr = SHGetMalloc(&mallocObj);
	if ( SUCCEEDED(hr) ) {
		if ( System::isUnicodeEnabled() ) {
			VCFChar shellPath[MAX_PATH];
			memset( shellPath, 0, MAX_PATH*sizeof(VCFChar) );
			LPITEMIDLIST pidl;

			hr = ::SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
			if ( SUCCEEDED(hr) ) {
				BOOL err = SHGetPathFromIDListW(pidl, shellPath);

				if ( FALSE != err ) {
					result = shellPath;
				}

				mallocObj->Free( pidl );
			}
		}
		else {
			char shellPath[MAX_PATH];
			memset( shellPath, 0, MAX_PATH*sizeof(char) );
			LPITEMIDLIST pidl;

			hr = ::SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl);
			if ( SUCCEEDED(hr) ) {
				BOOL err = SHGetPathFromIDListA(pidl, shellPath);

				if ( FALSE != err ) {
					result = shellPath;
				}

				mallocObj->Free( pidl );
			}
		}

		mallocObj->Release();
	}

	return result;
}

OSHandleID Win32UIShell::shellGetHandleID()
{
	return (OSHandleID)GetDesktopWindow();
}

OSHandleID Win32UIShell::shellGetGraphicsContextHandleID()
{
	return 0;
}

void Win32UIShell::shellSetUIShell( UIShell* shell )
{
	shell_ = shell;
}

void Win32UIShell::shellTranslateToScreenCoords( Control* control, Point* pt )
{
	POINT win32Point = { (int32)pt->x_, (int32)pt->y_ };
	::ClientToScreen( (HWND)control->getPeer()->getHandleID(), &win32Point );
	pt->x_ = win32Point.x;
	pt->y_ = win32Point.y;
}

void Win32UIShell::shellTranslateFromScreenCoords( Control* control, Point* pt )
{
	POINT win32Point = { (int32)pt->x_, (int32)pt->y_ };
	::ScreenToClient( (HWND)control->getPeer()->getHandleID(), &win32Point );
	pt->x_ = win32Point.x;
	pt->y_ = win32Point.y;
}

uint32 Win32UIShell::shellGetWidth()
{
	return (uint32)GetSystemMetrics( SM_CXSCREEN );
}

uint32 Win32UIShell::shellGetHeight()
{
	return (uint32)GetSystemMetrics( SM_CYSCREEN );
}

Rect Win32UIShell::shellGetUsableBounds()
{
	Rect result;

	RECT r;
	SystemParametersInfo( SPI_GETWORKAREA, 0, &r, 0 );
	result.left_ = r.left;
	result.top_ = r.top;
	result.right_ = r.right;
	result.bottom_ = r.bottom;

	return result;
}

Point Win32UIShell::getCurrentMousePosition()
{
	::POINT pt;
	::GetCursorPos(&pt);
	return Point( pt.x, pt.y );
}

void Win32UIShell::performFileOp( int operationType, const std::vector<String>& srcFiles, const std::vector<String>& destFiles )
{
	if ( System::isUnicodeEnabled() ) {

		SHFILEOPSTRUCTW fileOp = {0};

		if ( Frame::getActiveFrame() != NULL ) {
			fileOp.hwnd = (HWND)Frame::getActiveFrame()->getPeer()->getHandleID();
		}

		switch ( operationType ) {
			case UIShell::foCopy : {
				fileOp.wFunc = FO_COPY;
			}
			break;

			case UIShell::foMove : {
				fileOp.wFunc = FO_MOVE;
			}
			break;

			case UIShell::foDelete : {
				fileOp.wFunc = FO_DELETE ;
			}
			break;

			case UIShell::foRename : {
				fileOp.wFunc = FO_RENAME;
			}
			break;
		}


		VCFChar* srcBuf = NULL;
		VCFChar* tmp;
		size_t sz = 0;
		std::vector<String>::const_iterator it = srcFiles.begin();
		while ( it != srcFiles.end() ) {
			const String& s = *it;
			sz += s.length() + 1;
			++it;
		}

		sz += 1;

		srcBuf = new VCFChar[sz];
		tmp = srcBuf;
		it = srcFiles.begin();
		while ( it != srcFiles.end() ) {
			const String& s = *it;
			s.copy( tmp, s.length() );
			tmp += s.length();
			*tmp = 0;
			tmp ++;
			++it;
		}
		*tmp = 0;

		VCFChar* destBuf = NULL;

		if ( !destFiles.empty() ) {
			sz = 0;
			it = destFiles.begin();
			while ( it != destFiles.end() ) {
				const String& s = *it;
				sz += s.length() + 1;
				++it;
			}

			sz += 1;

			destBuf = new VCFChar[sz];
			tmp = destBuf;
			it = destFiles.begin();
			while ( it != destFiles.end() ) {
				const String& s = *it;
				s.copy( tmp, s.length() );
				tmp += s.length();
				*tmp = 0;
				tmp ++;
				++it;
			}
			*tmp = 0;
		}


		fileOp.pFrom = srcBuf;
		fileOp.pTo = destBuf;

		if ( destFiles.size() > 1 ) {
			fileOp.fFlags |= FOF_MULTIDESTFILES;
		}

		fileOp.fFlags |= FOF_ALLOWUNDO;

		if ( SHFileOperationW( &fileOp ) != 0 ) {
			//error
		}

		if ( fileOp.fAnyOperationsAborted ) {

		}

		delete [] srcBuf;
		delete [] destBuf;
	}
	else {

	}
}

void Win32UIShell::launch( const String& fileName, const String& parameters )
{
	if ( System::isUnicodeEnabled() ) {
		SHELLEXECUTEINFOW info = {0};
		info.cbSize = sizeof(info);
		info.fMask = SEE_MASK_FLAG_DDEWAIT;

		info.lpVerb = L"Open";
		info.lpFile = fileName.c_str();
		info.lpParameters = parameters.c_str();

		if ( !ShellExecuteExW( &info ) ) {
			//int err = GetLastError();
		}
	}
	else {
		SHELLEXECUTEINFOA info = {0};
		info.cbSize = sizeof(info);
		info.fMask = SEE_MASK_FLAG_DDEWAIT;

		info.lpVerb = "Open";
		info.lpFile = fileName.ansi_c_str();
		info.lpParameters = parameters.ansi_c_str();

		if ( !ShellExecuteExA( &info ) ) {
			//int err = GetLastError();
		}
	}
}

void Win32UIShell::openTrash()
{
	if ( System::isUnicodeEnabled() ) {

		LPITEMIDLIST  idList = NULL;
		HRESULT hr = SHGetSpecialFolderLocation( NULL, CSIDL_BITBUCKET, &idList );

		if ( SUCCEEDED(hr) ) {

			SHELLEXECUTEINFOW info = {0};
			info.cbSize = sizeof(info);
			info.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_IDLIST;
			info.nShow = SW_SHOWNORMAL;
			info.lpIDList = idList;


			ShellExecuteExW( &info );

			CoTaskMemFree( idList );
		}
	}
	else {
		LPITEMIDLIST  idList = NULL;
		HRESULT hr = SHGetSpecialFolderLocation( NULL, CSIDL_BITBUCKET, &idList );

		if ( SUCCEEDED(hr) ) {

			SHELLEXECUTEINFOA info = {0};
			info.cbSize = sizeof(info);
			info.fMask = SEE_MASK_FLAG_DDEWAIT | SEE_MASK_IDLIST;
			info.nShow = SW_SHOWNORMAL;
			info.lpIDList = idList;


			ShellExecuteExA( &info );

			CoTaskMemFree( idList );
		}
	}
}

void Win32UIShell::emptyTrash()
{
	HWND hwnd = NULL;
	if ( Frame::getActiveFrame() != NULL ) {
		hwnd = (HWND)Frame::getActiveFrame()->getPeer()->getHandleID();
	}

	if ( System::isUnicodeEnabled() ) {
		HRESULT hr = SHEmptyRecycleBinW( hwnd, L"", 0 );
		if ( FAILED(hr) ) {

		}
	}
	else {
		HRESULT hr = SHEmptyRecycleBinA( hwnd, "", 0 );
		if ( FAILED(hr) ) {

		}
	}

}



#define COM_PTR(ifc) \
namespace comet { \
template<> struct comtype<ifc> { \
	static const IID& uuid() { \
        static const IID iid = IID_##ifc; \
        return iid; \
	} \
    typedef nil base;\
};\
};\
typedef comet::com_ptr<ifc> ifc##Ptr;\
\

 
#ifndef USE_STRINGPOOL
COM_PTR(IShellLinkW)
typedef comet::com_ptr<IPersistFile> IPersistFilePtr;
#endif





void Win32UIShell::createFileShortcut( const String& originalFileName, const String& shortcutFileName )
{
	IShellLinkWPtr shellLink(CLSID_ShellLink);

	shellLink->SetPath( originalFileName.c_str() );  // Path to the object we are referring to

	
	IPersistFilePtr persistFile;
#ifndef USE_STRINGPOOL
	persistFile = com_cast(shellLink);
#else
	persistFile = shellLink;
#endif
	persistFile->Save( shortcutFileName.c_str(), TRUE );
}

#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "shlwapi.lib")

MIMEType Win32UIShell::getMIMEType( const String& fileName )
{
	MIMEType result;
	if ( System::isUnicodeEnabled() ) {
		SHFILEINFOW shInfo = {0};
		SHGetFileInfoW( fileName.c_str(), 0, &shInfo, sizeof(shInfo),
						SHGFI_ATTRIBUTES  | SHGFI_DISPLAYNAME  | SHGFI_EXETYPE | SHGFI_TYPENAME );

		VCFChar* tmp2;
#ifdef VCF_MINGW
// mingw does not provide urlmon.h so we have to go walkabout
        HINSTANCE hinst = LoadLibrary(TEXT("urlmon.dll"));
        HRESULT hr = NULL;
        typedef HRESULT (*Call) (LPBC, LPCWSTR, LPVOID, DWORD, LPCWSTR, DWORD, LPWSTR*, DWORD);
        if (hinst) {
            Call FindMimeFromData = (Call) GetProcAddress(hinst, "FindMimeFromData");
            if (FindMimeFromData) {
                hr = (*FindMimeFromData)( NULL, fileName.c_str(), NULL, 0, NULL, 0, &tmp2, 0 );
            }
            else {
                BasicException("GetProcAddress for FindMimeFromData failed");
            }
        }
        else {
            BasicException("LoadLibrary for urlmon.dll failed");
        }
#else
		HRESULT hr = FindMimeFromData( NULL, fileName.c_str(), NULL, 0, NULL, 0, &tmp2, 0 );
#endif
		if ( SUCCEEDED(hr) ) {
			result = MIMEType(tmp2);
		}
	}


	return result;
}

void Win32UIShell::createFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{
	String ext = info.extension;
	if ( ext[0] != '.' ) {
		ext = ext.insert( 0, "." );
	}

	Registry reg;


	String key = "";
	if ( forAllUsers ) {
		key += ext;
		reg.setRoot( RKT_ROOT );
		reg.openKey( key, true );
		reg.setValue( info.documentClass, "" );
		reg.setValue( info.mimeType, "Content Type" );

		key = "";
		key += info.documentClass;
		reg.setRoot( RKT_ROOT );
		reg.openKey( key, true );
		reg.setValue( info.documentDescription, "" );

		if ( !info.documentIconPath.empty() ) {
			reg.setRoot( RKT_ROOT );
			reg.openKey( key + "\\DefaultIcon", true );
			reg.setValue( String("\"") + info.documentIconPath + "\"", "" );
		}

		reg.setRoot( RKT_ROOT );
		reg.openKey( key + "\\shell\\open\\command", true );
		String launchStr = "\"";
		launchStr += info.launchingProgram + "\" \"%1\"";

		reg.setValue( launchStr, "" );
	}
	else {
		key = "Software\\Classes\\";
		key += ext;
		reg.setRoot( RKT_CURRENT_USER );
		reg.openKey( key, true );
		reg.setValue( info.documentClass, "" );
		reg.setValue( info.mimeType, "Content Type" );

		key = "Software\\Classes\\";
		key += info.documentClass;
		reg.setRoot( RKT_CURRENT_USER );
		reg.openKey( key, true );
		reg.setValue( info.documentDescription, "" );

		if ( !info.documentIconPath.empty() ) {
			reg.setRoot( RKT_CURRENT_USER );
			reg.openKey( key + "\\DefaultIcon", true );
			reg.setValue( String("\"") + info.documentIconPath + "\"", "" );
		}

		reg.setRoot( RKT_CURRENT_USER );
		reg.openKey( key + "\\shell\\open\\command", true );
		String launchStr = "\"";
		launchStr += info.launchingProgram + "\" \"%1\"";

		reg.setValue( launchStr, "" );
	}


	SHChangeNotify( SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL );
}

void Win32UIShell::removeFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{
	String ext = info.extension;
	if ( ext[0] != '.' ) {
		ext = ext.insert( 0, "." );
	}

	Registry reg;
	String key = "";

	if ( forAllUsers ) {
		key += ext;
		reg.setRoot( RKT_ROOT );
		reg.removeKey( key );
		key = "";
		key += info.documentClass;
		reg.removeKey( key );
	}
	else {
		key = "Software\\Classes\\";
		key += ext;
		reg.setRoot( RKT_CURRENT_USER );
		reg.removeKey( key );
		key = "Software\\Classes\\";
		key += info.documentClass;
		reg.removeKey( key );
	}

	SHChangeNotify( SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL );
}

/**
$Id: Win32UIShell.cpp 2807 2006-06-27 20:25:49Z kdmix $
*/
