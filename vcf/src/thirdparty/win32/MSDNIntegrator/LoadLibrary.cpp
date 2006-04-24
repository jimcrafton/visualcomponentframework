// CLoadLibrary : implementation file
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
#include "LoadLibrary.h"

#include <shlwapi.h>  // used for DLLVERSIONINFO

/////////////////////////////////////////////////////////////////////////////
// CLoadLibrary

CLoadLibrary::CLoadLibrary(LPCTSTR lpszModule/*=NULL*/)
{
	m_hInstance = NULL;

	if (lpszModule != NULL) {
		m_hInstance = ::LoadLibrary(lpszModule); 
	}
}

CLoadLibrary::~CLoadLibrary()
{
	if (m_hInstance != NULL) {
		::FreeLibrary(m_hInstance);  
	}
}

/////////////////////////////////////////////////////////////////////////////

void CLoadLibrary::LoadLibrary(LPCTSTR lpszModule)
{
	if (m_hInstance != NULL) {
		::FreeLibrary(m_hInstance);  
		m_hInstance = NULL;
	}
	if (lpszModule != NULL) {
		m_hInstance = ::LoadLibrary(lpszModule); 
	}
}

DWORD CLoadLibrary::GetModuleVersion()
{
	typedef HRESULT ( CALLBACK* DLLGETVERSIONPROC )( DLLVERSIONINFO* );

	DLLGETVERSIONPROC pDllGetVersion =
		( DLLGETVERSIONPROC )::GetProcAddress( m_hInstance, "DllGetVersion" );

	DWORD dwVersion = 0L;
	if ( pDllGetVersion != NULL )
	{
		DLLVERSIONINFO dvi;
		::ZeroMemory( &dvi, sizeof( dvi ) );
		dvi.cbSize = sizeof( dvi );
		
		HRESULT hr = ( *pDllGetVersion )( &dvi );
		if ( SUCCEEDED( hr ) )
		{
			ASSERT( dvi.dwMajorVersion <= 0xFFFF );
			ASSERT( dvi.dwMinorVersion <= 0xFFFF );
			dwVersion = MAKELONG( dvi.dwMinorVersion, dvi.dwMajorVersion );
		}
	}
	
	return dwVersion;
}
