//:Ignore
// CSplitPath : header file
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
//:End Ignore

#if !defined(__SPLITPATH_H__)
#define __SPLITPATH_H__

//:Ignore
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//:End Ignore

/////////////////////////////////////////////////////////////////////////////
// CSplitPath is a standalone class that wraps the _splitpath API to allow 
// easy access to a path's components.
//
class CSplitPath
{
public:
    
    // Constructs a CSplitPath object. If lpszPathBuffer is defined, the path will
    // be split.
    //
    CSplitPath(
        // Fully qualified path.
        LPCTSTR lpszPathBuffer=NULL,
        // 'true' if the path represents a directory.
        bool bIsDirectory=FALSE);
    
    // Destroys a CSplitPath object, handles cleanup and de-allocation.
    //
    virtual ~CSplitPath();
    
protected:

    // Drive letter, followed by a colon (:)
    TCHAR m_szDrive[_MAX_DRIVE];
    // Directory path, including trailing slash. Forward slashes ( / ), backslashes ( \ ), or both may be used.
    TCHAR m_szDir[_MAX_DIR];
    // Base filename (no extension)
    TCHAR m_szFName[_MAX_FNAME];
    // Filename extension, including leading period (.)
    TCHAR m_szExt[_MAX_EXT];
    // 'true' if the path is a directory.
    bool m_bIsDirectory;
    
public:

    // This member function is called to split the path specified by lpszPathBuffer.
    //
    void SplitPath(
        // Fully qualified path.
        LPCTSTR lpszPathBuffer=NULL,
        // 'true' if the path represents a directory.
        bool bIsDirectory=FALSE);
    
    // This member function retrieves the drive letter for the path, followed by a colon (:).
    // Returns a CString object.
    //
    CString GetDrive() const;

    // This member function retrieves the directory for the path, including trailing slash. 
    // Forward slashes ( / ), backslashes ( \ ), or both may be used.
    // Returns a CString object.
    //
    CString GetDir() const;

    // This member function retrieves the base filename (no extension).
    // Returns a CString object.
    //
    CString GetFName() const;

    // This member function retrieves the filename extension, including leading period (.).
    // Returns a CString object.
    //
    CString GetExt() const;

    // This member function retrieves the drive letter + the directory.
    // Returns a CString object.
    //
    CString GetFullPath() const;

    // This member function retrieves the file name + the extension.
    // Returns a CString object.
    //
    CString GetFullName() const;

    // This member function retrieves the parent directory.
    // Returns a CString object.
    //
    CString GetParentDir() const;
};

//:Ignore
//////////////////////////////////////////////////////////////////////

AFX_INLINE CString CSplitPath::GetDrive() const {
    return CString(m_szDrive);
}
AFX_INLINE CString CSplitPath::GetDir() const {
    return CString(m_szDir);
}
AFX_INLINE CString CSplitPath::GetFName() const {
    return CString(m_szFName);
}
AFX_INLINE CString CSplitPath::GetExt() const {
    return CString(m_szExt);
}
AFX_INLINE CString CSplitPath::GetFullPath() const {
    return GetDrive() + GetDir();
}
AFX_INLINE CString CSplitPath::GetFullName() const {
    return GetFName() + GetExt();
}

//////////////////////////////////////////////////////////////////////
//:End Ignore

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__SPLITPATH_H__)
