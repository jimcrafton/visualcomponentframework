//:Ignore
// CLoadLibrary : header file
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

#if !defined(__LOADLIBRARY_H__)
#define __LOADLIBRARY_H__

//:Ignore
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//:End Ignore

//////////////////////////////////////////////////////////////////////
// CLoadLibrary is a stand alone utility class.  It is used to load a
// module (DLL) and free the instance handle upon destruction.  It wraps
// the LoadLibrary and the FreeLibrary API's.
//
class CLoadLibrary
{
public:
    
    // Constructs a CLoadLibrary object.
    //
    CLoadLibrary(        
		// Pointer to a null-terminated string that names the .DLL file. The
		// name specified is the filename of the module and is not related to
		// the name stored in the library module itself, as specified by the
		// LIBRARY keyword in the module-definition (.DEF) file. 
        //
        // If the string specifies a path but the file does not exist in
		// the specified directory, the function fails.  When specifying a path,
		// be sure to use backslashes (\), not forward slashes (/). 
        LPCTSTR lpszModule=NULL);

    // Destroys a CLoadLibrary object, handles cleanup and de-allocation.
    //
    virtual ~CLoadLibrary();

protected:

    // A handle to the module indicates success.
	HINSTANCE m_hInstance; 
    
public:

    // This member function is called to load the library specified by
	// 'lpszModule'.  Once the library is loaded, you can retrieve the instance
	// handle by using the HINSTANCE operator.
	//
	void LoadLibrary(
		// Pointer to a null-terminated string that names the .DLL file. The
		// name specified is the filename of the module and is not related to
		// the name stored in the library module itself, as specified by the
		// LIBRARY keyword in the module-definition (.DEF) file. 
        //
        // If the module does not exist in the specified directory, the
		// function will fail.  When specifying a path, be sure to use backslashes
		// (\), not forward slashes (/). 
        LPCTSTR lpszModule);

    // This overloaded operator returns a handle to the module indicating
	// success. NULL indicates failure.
    //
    operator HINSTANCE() const;

	// Use this member function to return the version number of the
	// module attached to this CLoadLibrary object. The high-order
	// word of the return value represents the major version number and
	// the low-order word of the returned value represents the minor
	// version number.  Returns a DWORD value if successful, otherwise 0L.
	DWORD GetModuleVersion();
};

//:Ignore
//////////////////////////////////////////////////////////////////////

AFX_INLINE CLoadLibrary::operator HINSTANCE() const {
	return m_hInstance;
};

//////////////////////////////////////////////////////////////////////
//:End Ignore

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__LOADLIBRARY_H__)
