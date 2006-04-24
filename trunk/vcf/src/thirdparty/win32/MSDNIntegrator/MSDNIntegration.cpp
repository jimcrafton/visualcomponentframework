// MSDNIntegration.cpp: implementation of the CMSDNIntegration class.
//
// ©2001-2003 Codejock.com Software, All Rights Reserved.
//
// You are free to use this source code unconditionally as long as this
// notice is not removed. If you have questions, comments suggestions or
// fixes, please feel free to drop me a line.
//
// Kirk Stowell <kstowell@codejock.com>
// http://www.codejock.com
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "Resource.h"
#include "SplitPath.h"
#include "LoadLibrary.h"
#include "MSDNIntegration.h"

#include <io.h>

const TCHAR KEY_LANG[] = _T("Language");
const TCHAR KEY_PREF[] = _T("Preferred");
const TCHAR KEY_FILE[] = _T("Filename");

#ifndef VERSION_SH471
#define VERSION_SH471           MAKELONG(71,4)
#endif // VERSION_SH471

#ifndef CSIDL_COMMON_APPDATA
#define CSIDL_COMMON_APPDATA    0x0023      // All Users\Application Data
#endif // CSIDL_COMMON_APPDATA

/////////////////////////////////////////////////////////////////////////////
// CMSDNIntegration

CMSDNIntegration::CMSDNIntegration()
//: m_pProgress(0)
{
	Init();
}

CMSDNIntegration::~CMSDNIntegration()
{
	// TODO: add destruction code here.

}

/////////////////////////////////////////////////////////////////////////////

bool CMSDNIntegration::DisplayMessage(UINT nMessage, bool bError/*=true*/)
{
	CString strMessage;
	strMessage.LoadString(nMessage);

	CString strTitle;
	strTitle.LoadString(bError ? IDS_ERR_TITLE : IDS_SUCCESS_CAPTION);

	::MessageBox(NULL, strMessage, strTitle, MB_OK | bError ? 
		MB_ICONERROR : MB_ICONINFORMATION );

	return !bError;
}

bool CMSDNIntegration::DisplayMessage(LPCTSTR lpszMessage, bool bError/*=true*/)
{
	CString strTitle;
	strTitle.LoadString(bError ? IDS_ERR_TITLE : IDS_SUCCESS_CAPTION);

	::MessageBox(NULL, lpszMessage, strTitle, MB_OK | bError ? 
		MB_ICONERROR : MB_ICONINFORMATION );

	return !bError;
}

CMSDNIntegration& CMSDNIntegration::Get()
{
	static CMSDNIntegration theIntegrator;
	return theIntegrator;
}

bool CMSDNIntegration::GetRegKeyValue(HKEY hKey, const CString strKey, const CString strName, CString& strValue)
{
	HKEY hkKey = NULL;
	DWORD dwDisposition;

	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof( SECURITY_ATTRIBUTES );
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;

	// check results
	if ( ::RegCreateKeyEx( hKey, strKey,
		NULL, "", REG_OPTION_NON_VOLATILE, KEY_QUERY_VALUE,
		&sa, &hkKey, &dwDisposition ) != ERROR_SUCCESS )
	{
		return false;
	}

	if ( dwDisposition == REG_OPENED_EXISTING_KEY )
	{
		TCHAR szValue[256];
		DWORD dwValueType;
		DWORD dwBufferLength = _MAX_PATH;
		
		if ( ::RegQueryValueEx( hkKey, strName, ( LPDWORD )NULL, &dwValueType,
			( LPBYTE )szValue, &dwBufferLength ) != ERROR_SUCCESS )
		{
			::RegCloseKey( hkKey );
			return false;
		}

		strValue = szValue;
	}

	::RegCloseKey( hkKey );

	return true;
}

bool CMSDNIntegration::GetMSDNColPath()
{
	CString strKey;
	strKey.LoadString(IDS_MSDN_KEY);
	
	CString strValue;
	if (GetRegKeyValue(HKEY_LOCAL_MACHINE, strKey, KEY_LANG, strValue) == false)
		return DisplayMessage(IDS_ERR_REGNOTFOUND);

	strKey += _T('\\');
	strKey += strValue;

	if (GetRegKeyValue(HKEY_LOCAL_MACHINE, strKey, KEY_PREF, strValue) == false)
		return DisplayMessage(IDS_ERR_REGNOTFOUND);

	strKey += _T('\\');
	strKey += strValue;

	if (GetRegKeyValue(HKEY_LOCAL_MACHINE, strKey, KEY_FILE, m_strMSDNCol) == false)
		return DisplayMessage(IDS_ERR_REGNOTFOUND);

	// Make sure that the collection exists!
    if (_taccess(m_strMSDNCol, 0) == -1)
		return DisplayMessage(IDS_ERR_COLNOTFOUND);

	m_spMSDNCol.SplitPath( m_strMSDNCol, false );

	// open the .col file.
	CStdioFile stdRead( m_strMSDNCol, CFile::modeRead | CFile::typeText );

	// save its contents to our buffer array.
	CString strBuffer;
	while ( stdRead.ReadString( strBuffer ) )
	{
		strBuffer += _T( "\n" );
		m_sarMSDNCol.Add( strBuffer );
	}

	// close the file.
	stdRead.Close();

	return true;
}

#ifdef _UNICODE
static const TCHAR _szSpecialFolderPath[] = _T("SHGetSpecialFolderPathW");
#else
static const TCHAR _szSpecialFolderPath[] = _T("SHGetSpecialFolderPathA");
#endif

BOOL CMSDNIntegration::GetSpecialFolderPath(HWND hwndOwner, LPTSTR lpszPath, int nFolder, BOOL fCreate)
{
	typedef int (WINAPI* _SHGET)(HWND, LPTSTR, int, BOOL);

	// Get a function pointer to SHGetSpecialFolderPath(...) from
	// Shell32.dll, if this returns NULL then check ShFolder.dll...
	_SHGET pfn = (_SHGET)::GetProcAddress(
		CLoadLibrary(_T("Shell32.dll")), _szSpecialFolderPath);

	if (pfn == NULL)
	{
		// Try to get the function pointer from ShFolder.dll, if pfn is still
		// NULL then we have bigger problems...
		pfn = (_SHGET)::GetProcAddress(
			CLoadLibrary(_T("ShFolder.dll")), _szSpecialFolderPath);

		if (pfn == NULL) {
			return FALSE;
		}
	}

	return pfn(hwndOwner, lpszPath, nFolder, fCreate);
}

bool CMSDNIntegration::GetMSDNDatPath()
{
    // Verify that we have version 4.71 or later of Shell32.dll.
    // If so we can use SHGetSpecialFolderPath(...) to get the path
    // where hhcolreg.dat should be located, otherwise we will make
    // an educated guess.

    

	// Old MSDN collection? hhcolreg.dat is located in the
	// Windows\Help directory possibly.
	m_strMSDNDat.Format(IDS_OLD_DAT, m_strWinDir);

	if ( -1 == _taccess(m_strMSDNDat,0) ) {
		
		CLoadLibrary libModule(_T("Shell32.dll"));
		if (libModule.GetModuleVersion() < VERSION_SH471)
		{
			m_strMSDNDat.Format(IDS_NEW_DAT, m_spMSDNCol.GetDrive());
		}
		else
		{
			TCHAR lpszFolderPath[_MAX_PATH];
			::ZeroMemory(lpszFolderPath, sizeof(lpszFolderPath));
			
			if ( !GetSpecialFolderPath( NULL,
				lpszFolderPath, CSIDL_COMMON_APPDATA, FALSE ) )
			{
				return false;
			}
			
			m_strMSDNDat.Format(IDS_NEWER_DAT, lpszFolderPath);
		}
		
		
		// Check to see if the registry file was found.
		if (_taccess(m_strMSDNDat, 0) == -1)
		{			
			// Still not found, return error.		
			return DisplayMessage(IDS_ERR_DATNOTFOUND);
		}
		
	}



	// open the .dat file.
	CStdioFile stdRead( m_strMSDNDat, CFile::modeRead | CFile::typeText );

	// save its contents to our buffer array.
	CString strBuffer;
	while ( stdRead.ReadString( strBuffer ) )
	{
		strBuffer += _T( "\n" );
		m_sarMSDNDat.Add( strBuffer );
	}

	// close the file.
	stdRead.Close();

	return true;
}

bool CMSDNIntegration::GetMSDNColData()
{
	m_strLangId.Empty();
	m_strColNum.Empty();
	
	CString strYear = _T("");
	
	int i;
	for (i = 0; i < m_sarMSDNCol.GetSize(); ++i)
	{
		CString strBuffer = m_sarMSDNCol.GetAt( i );
		
		if (strBuffer.Find(_T("<TitleString value=\"MSDN Library")) != -1)
		{
			int iIndex  = strBuffer.ReverseFind(_T(' '));
			int iLength = strBuffer.GetLength();
			
			strYear = strBuffer.Right(iLength - (iIndex+1));
			strYear = strYear.Left(4);
			
			if (atoi(strYear) > 2001)
				return DisplayMessage(IDS_ERR_WRONG_VER);
		}
		
		else if (strBuffer.Find(_T("masterlangid")) != -1)
		{
			int nStart = strBuffer.Find(_T('='))+1;
			int nEnd   = strBuffer.Find(_T('/'));
			m_strLangId = strBuffer.Mid(nStart, (nEnd-nStart));
		}
		
		else if (strBuffer.Find(_T("collectionnum")) != -1)
		{
			int nStart = strBuffer.Find(_T('='))+1;
			int nEnd   = strBuffer.Find(_T('/'));
			m_strColNum = strBuffer.Mid(nStart, (nEnd-nStart));
		}
		
		else if (!m_strLangId.IsEmpty() && !m_strColNum.IsEmpty() && !strYear.IsEmpty())
		{
			break;
		}
	}
	
	return true;
}

CString CMSDNIntegration::GetDatPath() const
{
	return m_strMSDNDat;
}

CString CMSDNIntegration::GetColPath() const
{
	return m_strMSDNCol;
}

CString CMSDNIntegration::GetColNum() const
{
	return m_strColNum;
}

CString CMSDNIntegration::GetLangID() const
{
	return m_strLangId;
}

CString CMSDNIntegration::GetUniqueID() const
{
	return m_strUniqueID;
}

void CMSDNIntegration::SetUniqueID(LPCTSTR lpszUniqueID/*=NULL*/)
{
	if ( lpszUniqueID == NULL )
	{
		m_strUniqueID = GenerateGUID( );
	}
	else
	{
		m_strUniqueID = lpszUniqueID;
	}
}

CString CMSDNIntegration::GetTitleString() const
{
	return m_strTitleString;
}

void CMSDNIntegration::SetTitleString(LPCTSTR lpszTitleString)
{
	m_strTitleString = lpszTitleString;
}

CString CMSDNIntegration::GetChmFile() const
{
	return m_strChmFile;
}

void CMSDNIntegration::SetChmFile(LPCTSTR lpszChmFile)
{
	m_strChmFile = lpszChmFile;
}

CString CMSDNIntegration::GetChiFile() const
{
	return m_strChiFile;
}

void CMSDNIntegration::SetChiFile(LPCTSTR lpszChiFile)
{
	m_strChiFile = lpszChiFile;
}

CString CMSDNIntegration::GetHelpVer() const
{
	return m_strHelpVer;
}

void CMSDNIntegration::SetHelpVer(LPCTSTR lpszHelpVer)
{
	m_strHelpVer = lpszHelpVer;
}

CString CMSDNIntegration::GetColName() const
{
	return m_spMSDNCol.GetFullName();
}

/*
void CMSDNIntegration::SetProgressCtrl(CProgressCtrl* pProgress)
{
	ASSERT(pProgress != NULL && ::IsWindow(pProgress->GetSafeHwnd()));
	m_pProgress = pProgress;

	m_pProgress->SetRange(0, m_sarMSDNCol.GetSize()+m_sarMSDNDat.GetSize());
	m_pProgress->SetStep(1);
	m_pProgress->SetPos(0);
}


CProgressCtrl* CMSDNIntegration::GetProgressCtrl() const
{
	return m_pProgress;
}
*/

CString CMSDNIntegration::GenerateGUID()
{
	// create random GUID
	GUID guid = GUID_NULL;
	::CoCreateGuid(&guid);
	
	if (guid != GUID_NULL)
	{
		m_strUniqueID.Empty();

		// use the formatting string to format into destination.
		m_strUniqueID.Format(IDS_GUID,
			guid.Data1,    guid.Data2,    guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
		
		return m_strUniqueID;
	}

	return _T("");
}


/*
CString CMSDNIntegration::FindChmFile(CWnd* pWnd)
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	strFilter.LoadString(IDS_CHM_FILTER);
 
	//CFileDialog dlg( TRUE, NULL, NULL, OFN_EXPLORER|
	//	OFN_ENABLESIZING|OFN_FILEMUSTEXIST, strFilter, pWnd );
	
	// Check to see if this is Windows 2000...if so use the
	// Windows 2000 version of OPENFILENAME.

	DWORD dwWinMajor = ( DWORD )( LOBYTE( LOWORD( ::GetVersion( ) ) ) );
	if ( ( BYTE )dwWinMajor >= 5 && sizeof( OPENFILENAME ) < 88 )
	{
		// Windows 2000 version of OPENFILENAME has three extra members,
		// this was copied from newer version of commdlg.h...
		
		struct OPENFILENAMEEX
		{ 
			void*  pvReserved; // 4 bytes
			DWORD  dwReserved; // 4 bytes
			DWORD  FlagsEx;    // 4 bytes
		};
		
		dlg.m_ofn.lStructSize += sizeof( OPENFILENAMEEX ); // should equal an additional 12 bytes;
	}
	
	if( dlg.DoModal() == IDOK )
	{
		SetChmFile(dlg.GetPathName());
		return GetChmFile();
	}


	return _T("");
}
*/


/*
CString CMSDNIntegration::FindChiFile(CWnd* pWnd)
{
	// TODO: Add your control notification handler code here
	CString strFilter;
	strFilter.LoadString(IDS_CHI_FILTER);
 
	CFileDialog dlg( TRUE, NULL, NULL, OFN_EXPLORER|
		OFN_ENABLESIZING|OFN_FILEMUSTEXIST, strFilter, pWnd );

	// Check to see if this is Windows 2000...if so use the
	// Windows 2000 version of OPENFILENAME.
	DWORD dwWinMajor = ( DWORD )( LOBYTE( LOWORD( ::GetVersion( ) ) ) );
	if ( ( BYTE )dwWinMajor >= 5 && sizeof( OPENFILENAME ) < 88 )
	{
		// Windows 2000 version of OPENFILENAME has three extra members,
		// this was copied from newer version of commdlg.h...
		
		struct OPENFILENAMEEX
		{ 
			void*  pvReserved; // 4 bytes
			DWORD  dwReserved; // 4 bytes
			DWORD  FlagsEx;    // 4 bytes
		};
		
		dlg.m_ofn.lStructSize += sizeof( OPENFILENAMEEX ); // should equal an additional 12 bytes;
	}
	
	if( dlg.DoModal() == IDOK )
	{
		SetChiFile(dlg.GetPathName());
		return GetChiFile();
	}

	return _T("");
}
*/


void CMSDNIntegration::ResetData()
{
	// flush all strings.
	m_strChmFile.Empty();
	m_strChiFile.Empty();
	m_strUniqueID.Empty();
	m_strTitleString.Empty();
}

void CMSDNIntegration::Init()
{
	// get the current windows directory.
	TCHAR szWinDir[ _MAX_PATH ];
	::GetWindowsDirectory( szWinDir, _MAX_PATH );
	m_strWinDir = szWinDir;

	// construct the path to the MSDN collection.
	GetMSDNColPath( );

	// construct the path to the MSDN collection registry.
	GetMSDNDatPath( );

	// extract the collection data.
	GetMSDNColData();
}

const int _MAX_COUNT = 1000;

bool CMSDNIntegration::GetBackupName(const CString strFile, CString& strBackupName)
{
	bool bBackupFile = false;

	// figure out where to write backup
    CSplitPath sp( strFile );
	
	int i;
	for ( i = 0; i < _MAX_COUNT && !bBackupFile; i++ )
	{
		strBackupName.Format(_T("%s%s%s.%03.3d"), sp.GetDrive(), sp.GetDir(), sp.GetFName(), i);
		bBackupFile = (_taccess(strBackupName, 0) == -1);
	}
	
	return bBackupFile;
};

bool CMSDNIntegration::BackupColFile()
{
	CString strBakName;
	GetBackupName( m_strMSDNCol, strBakName );
	if ( _taccess( m_strMSDNCol, 0 ) != -1 )
	{
		if ( ::CopyFile( m_strMSDNCol, strBakName, FALSE ) )
		{
			return true;
		}
	}

	return false;
}

bool CMSDNIntegration::BackupDatFile()
{
	CString strBakName;
	GetBackupName( m_strMSDNDat, strBakName );
	if ( _taccess( m_strMSDNDat, 0 ) != -1 )
	{
		if ( ::CopyFile( m_strMSDNDat, strBakName, FALSE ) )
		{
			return true;
		}
	}

	return false;
}

bool CMSDNIntegration::IsInitialized(bool bCheckData/*=true*/, bool bSilent/*=false*/)
{
	if (m_strUniqueID.IsEmpty())
		return bSilent ? false : DisplayMessage(IDS_ERR_INIT_ID);
	
	if (bCheckData)
	{
		if (m_strHelpVer.IsEmpty())
			return bSilent ? false : DisplayMessage(IDS_ERR_INIT_VER);

		if (m_strChmFile.IsEmpty())
			return bSilent ? false : DisplayMessage(IDS_ERR_INIT_CHM);
		
		if (m_strChiFile.IsEmpty())
			return bSilent ? false : DisplayMessage(IDS_ERR_INIT_CHI);
		
		if (m_strTitleString.IsEmpty())
			return bSilent ? false : DisplayMessage(IDS_ERR_INIT_TITLE);
		
		if (m_strMSDNDat.IsEmpty())
			return bSilent ? false : DisplayMessage(IDS_ERR_INIT_DAT);
		
		if (m_strMSDNCol.IsEmpty())
			return bSilent ? false : DisplayMessage(IDS_ERR_INIT_COL);
	}

	return true;
}

bool CMSDNIntegration::CanIntegrate(bool bCheckData/*=true*/, bool bSilent/*=false*/)
{
	CString strTitle;
	strTitle.LoadString(IDS_ERR_TITLE);
	
	// All data must be completely initialized first...
	if ( !IsInitialized( bCheckData, bSilent ) )
	{
		return false;
	}

	// see if there is an entry in the MSDN collection...
	int i;
	for (i = 0; i < m_sarMSDNCol.GetSize(); ++i)
	{
		CString strBuffer = m_sarMSDNCol.GetAt( i );
		if (strBuffer.Find(m_strUniqueID) != -1)
		{
			return false; // already integrated.
		}
	}
	
	// if not check the MSDN Registry.
	for (i = 0; i < m_sarMSDNDat.GetSize(); ++i)
	{
		CString strBuffer = m_sarMSDNDat.GetAt( i );
		if (strBuffer.Find(m_strUniqueID) != -1)
		{
			return false; // already integrated.
		}
	}

	return true;
}

bool CMSDNIntegration::IntegrateMSDNDat()
{
	if ( !CanIntegrate( ) )
	{
		return false;
	}

	// backup the original file incase of a fatal error!
	BackupDatFile( );

	// insert our additions.
	CStdioFile stdWrite( m_strMSDNDat,
		CFile::modeWrite | CFile::modeCreate | CFile::typeText );

	int i;
	for ( i = 0; i < m_sarMSDNDat.GetSize( ); ++i )
	{
		CString strBuffer = m_sarMSDNDat.GetAt( i );

		if ( strBuffer.Find( _T( "</DocCompilations>" ) ) != -1 )
		{
			strBuffer.Format( IDS_DAT, m_strUniqueID, m_strLangId,
				m_strColNum, m_strChmFile, m_strChiFile, m_strHelpVer );
		}

		stdWrite.WriteString( strBuffer );
		//m_pProgress->StepIt();
	}

	stdWrite.Close();

	return true;
}

bool CMSDNIntegration::IntegrateMSDNCol()
{
	if ( !CanIntegrate( ) )
	{
		return false;
	}

	// backup the original file incase of a fatal error!
	BackupColFile( );

	// insert our additions.
	CStdioFile stdWrite( m_strMSDNCol,
		CFile::modeWrite | CFile::modeCreate | CFile::typeText );

	int i;
	for ( i = 0; i < m_sarMSDNCol.GetSize( ); ++i )
	{
		CString strBuffer = m_sarMSDNCol.GetAt( i );

		if ( strBuffer.Find( _T( "</Folders>" ) ) != -1 )
		{
			strBuffer.Format( IDS_COL,
				m_strTitleString, m_strUniqueID, m_strLangId );
		}

		stdWrite.WriteString( strBuffer );
		//m_pProgress->StepIt();
	}

	stdWrite.Close();

	return true;
}

bool CMSDNIntegration::RestoreMSDNDat(bool bSilent/*=false*/)
{
	CString strBackupName;

	if ( CanIntegrate( ) )
		return true;

    CSplitPath sp( m_strMSDNDat );
	int i;
	for ( i = 0; i < _MAX_COUNT; i++ )
	{
		strBackupName.Format( _T( "%s%s%s.%03.3d" ), sp.GetDrive( ), sp.GetDir( ), sp.GetFName( ), i );

		if ( _taccess( strBackupName, 0 ) != -1 )
		{
			break;
		}
	}

	if ( i == _MAX_COUNT )
	{
		if ( !bSilent )
		{
			CString strBuffer;
			strBuffer.Format( IDS_BACKUPNOTFOUND, m_strMSDNDat );
			AfxMessageBox( strBuffer, MB_OK|MB_ICONWARNING );
		}
		
		return false;
	}

	else
	{
		if ( _taccess( m_strMSDNDat, 0 ) != -1 )
		{
			if ( ::CopyFile( strBackupName, m_strMSDNDat, FALSE ) )
			{
				try
				{
					CFile::Remove( strBackupName );
				}
				catch ( CFileException& )
				{
					return false;
				}

				return true;
			}
		}
	}

	return false;
}

bool CMSDNIntegration::RestoreMSDNCol(bool bSilent/*=false*/)
{
	CString strBackupName;

	if ( CanIntegrate( ) )
		return true;

    CSplitPath sp( m_strMSDNCol );
	int i;
	for ( i = 0; i < _MAX_COUNT; i++ )
	{
		strBackupName.Format( _T( "%s%s%s.%03.3d" ), sp.GetDrive( ), sp.GetDir( ), sp.GetFName( ), i );

		if ( _taccess( strBackupName, 0 ) != -1 )
		{
			break;
		}
	}

	if ( i == _MAX_COUNT )
	{
		if ( !bSilent )
		{
			CString strBuffer;
			strBuffer.Format( IDS_BACKUPNOTFOUND, m_strMSDNCol );
			AfxMessageBox( strBuffer, MB_OK|MB_ICONWARNING );
		}
		
		return false;
	}

	else
	{
		if ( _taccess( m_strMSDNCol, 0 ) != -1 )
		{
			if ( ::CopyFile( strBackupName, m_strMSDNCol, FALSE ) )
			{
				try
				{
					CFile::Remove( strBackupName );
				}
				catch ( CFileException& )
				{
					return false;
				}

				return true;
			}
		}
	}

	return false;
}
