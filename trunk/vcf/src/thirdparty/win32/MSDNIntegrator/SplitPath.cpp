// CSplitPath : implementation file
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
#include "SplitPath.h"

/////////////////////////////////////////////////////////////////////////////
// CSplitPath

CSplitPath::CSplitPath(LPCTSTR lpszPathBuffer/*=NULL*/, bool bIsDirectory/*=FALSE*/)
{
	if (lpszPathBuffer != NULL)
        SplitPath(lpszPathBuffer, bIsDirectory);
}

CSplitPath::~CSplitPath()
{
	// TODO: add destruction code here.

}

/////////////////////////////////////////////////////////////////////////////

void CSplitPath::SplitPath(LPCTSTR lpszPathBuffer, bool bIsDirectory)
{
    ASSERT(lpszPathBuffer != NULL);
    ::_tsplitpath(lpszPathBuffer, m_szDrive, m_szDir, m_szFName, m_szExt);

    m_bIsDirectory = bIsDirectory;
}

CString CSplitPath::GetParentDir() const
{
    CString strFullPath = GetFullPath();

    if (m_bIsDirectory)
        strFullPath += m_szFName;

    // Build the base directory name;
    int iCount = strFullPath.ReverseFind(_T('\\'));
    CString strParentDir = strFullPath.Left(iCount);

    int iLength = strFullPath.GetLength();
    if (iCount == iLength-1)
    {
        iCount = strParentDir.ReverseFind(_T('\\'));
        strParentDir = strParentDir.Left(iCount);
    }
    
    return strParentDir;
}
