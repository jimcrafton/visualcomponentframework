//:Ignore
// MSDNIntegration.h: interface for the CMSDNIntegration class.
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

#if !defined(__MSDNINTEGRATION_H__)
#define __MSDNINTEGRATION_H__

//:Ignore
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//:End Ignore

//////////////////////////////////////////////////////////////////////
// CMSDNIntegration is a standalone class used to integrate HTML help 
// files with the MSDN collection.
//
class CMSDNIntegration
{
    // Constructs a CMSDNIntegration object.
    //
	CMSDNIntegration();

public:
	
    // Destroys a CMSDNIntegration object, handles cleanup and de-allocation.
    //
	virtual ~CMSDNIntegration();

protected:

    // Full path to hhcolreg.dat
    CString m_strMSDNDat;
    // Full path to the MSDN collection file
    CString m_strMSDNCol;
    // Full path of the Windows directory.
    CString m_strWinDir;
    // Current collection number
    CString m_strColNum;
    // Current collection language id
    CString m_strLangId;
    // Unique identifier of the help to be added.
    CString m_strUniqueID;
    // Title to be displayed in the contents tab of the MSDN collection.
    CString m_strTitleString;
    // Full path to the .chm file to be added.
    CString m_strChmFile;
    // Full path to the .chi file to be added.
    CString m_strChiFile;
    // Current version of the help to be added.
    CString m_strHelpVer;
    // Contains path information for col file.
    CSplitPath m_spMSDNCol;
    // Buffer that holds col file data.
    CStringArray m_sarMSDNCol;
    // Buffer that holds dat file data.
    CStringArray m_sarMSDNDat;
    // Control to display the integration progress, can be NULL.
   // CProgressCtrl* m_pProgress;

public:
	
	// This member function is used to query the system registry and retrieve
	// the value for the specified key.
	// Returns 'true' if successful, otherwise 'false'.
    //
	bool GetRegKeyValue(
        // handle to an open key
        HKEY hKey,
        // Pointer to a null-terminated string specifying the registry subkey to get the value for.
        const CString strKey,
        // Pointer to a null-terminated string containing the name of the value to query. 
        const CString strName,
        // Pointer to a buffer that receives the value's data.
        CString& strValue);

	// This member function will initialize the language id and collection 
	// collection number data.
	// Returns 'true' if successful, otherwise 'false'.
    //
	bool GetMSDNColData();

	// This member function querys the system registry for the name
	// and file location of the MSDN collection.
	// Returns 'true' if successful, otherwise 'false'.
    //
	bool GetMSDNColPath();

	// This member function determines the correct location of the
	// hhcolreg.dat file that is used by the MSDN collection.
	// Returns 'true' if successful, otherwise 'false'.
    //
	bool GetMSDNDatPath();

	// This member function is called to verify that all strings
	// have been initialized.
	// Returns 'true' if successful, otherwise 'false'.
	//
	bool IsInitialized(
        // 'true' to verify all input data has been initialized.
        bool bCheckData=true,
        // 'true' to disable error message.
		bool bSilent=false);

	// This member function is used to determine if all of the
	// input data has been initialized, and if the new title can
	// be safely added to the collection. Will return false if the
	// title is already found.
	// Returns 'true' if successful, otherwise 'false'.
    //
	bool CanIntegrate(
        // 'true' to verify all input data has been initialized.
        bool bCheckData=true,
        // 'true' to disable error message.
		bool bSilent=false);

	// This member function will integrate the initialized data into 
	// the MSDN collection file.
	// Returns 'true' if successful, otherwise 'false'.
    //
	bool IntegrateMSDNCol();

	// This member function will integrate the initialized data into 
	// the hhcolreg.dat file.
	// Returns 'true' if successful, otherwise 'false'.
    //
	bool IntegrateMSDNDat();

	// This member function will restore the MSDN collection file to the original
    // state prior to integration.  It uses a backup file that was created when the
    // integration originally took place.  If no backup files are found, a message will
    // be displayed to the user.
	// Returns 'true' if successful, otherwise 'false'.
    //
	bool RestoreMSDNCol(
        // 'true' to disable message if no backup files were found.
        bool bSilent=false);

	// This member function will restore the MSDN data file to the original
    // state prior to integration.  It uses a backup file that was created when the
    // integration originally took place.  If no backup files are found, a message will
    // be displayed to the user.
	// Returns 'true' if successful, otherwise 'false'.
    //
	bool RestoreMSDNDat(
        // 'true' to disable message if no backup files were found.
        bool bSilent=false);
	
	// This member function will create a new GUID and initialize the
	// unique identifier for this object.
	// Returns a CString object that represents the newly created GUID if successful.
	CString GenerateGUID();

	// This member function determines the correct location of the
	// hhcolreg.dat file that is used by the MSDN collection.
	// Returns 'true' if successful, otherwise 'false'.
    //
	CString GetDatPath() const;

	// This member function querys the system registry for the name
	// and file location of the MSDN collection.
	// Returns 'true' if successful, otherwise 'false'.
    //
	CString GetColPath() const;

	// This member function will return the current MSDN collection name
	// minus the path.
	// Returns a CString object that represents the MSDN collection file name.
    //
	CString GetColName() const;

	// This member function will return the current MSDN collection number.
	// Returns a CString object that represents the MSDN collection number.
    //
	CString GetColNum() const;

	// This member function will return the current language ID settings
	// for the MSDN collection.
	// Returns a CString object that represents the current language ID settings.
    //
	CString GetLangID() const;

	// This member function will return unique identifier for the
	// help file that is to be added to the MSDN collection.
	// Returns a CString object that represents the current identifier for the
	// newly added help file.
    //
	CString GetUniqueID() const;

    
	// This member function will set the value of the unique identifier
	// for the help file that is to be added to the MSDN collection.
    //
	void SetUniqueID(
        // A NULL terminated string that represents the new value for the help file unique identifier.
        LPCTSTR lpszUniqueID=NULL);

	// This member function will return the title string for the help
	// file that is to be added to the MSDN collection.
	// Returns a CString object that represents the title string for the help file.
    //
	CString GetTitleString() const;
	
    
	// This member function will set the title string for the help file that
	// is to be added to the MSDN collection.
    //
	void SetTitleString(
        // A NULL terminated string that represents the title string for the help file
        LPCTSTR lpszTitleString);

	// This member function will return the full path to the .chm file that
	// is to be added to the MSDN collection.
	// Returns a CString object that represents the full path to the .chm help file.
    //
	CString GetChmFile() const;

	// This member function will set the value for the .chm help file that
	// is to be added to the MSDN collection.
    //
	void SetChmFile(
        // A NULL terminated string that represents the full path to the .chm help file.
        LPCTSTR lpszChmFile);

	// This member function will return the full path to the .chi index file that
	// is to be added to the MSDN collection.
	// Returns a CString object that represents the full path to the .chi help index file.
    //
	CString GetChiFile() const;

	// This member function will set the value for the .chi help index file that
	// is to be added to the MSDN collection.
    //
	void SetChiFile(
        // A NULL terminated string that represents the full path to the .chi help index file.
        LPCTSTR lpszChiFile);

	// This member function will return the version number of the help file that
	// is to be added to the MSDN collection.
	// Returns a CString object that represents the version number of the help file.
    //
	CString GetHelpVer() const;

	// This member function will return the version number of the help file that
	// is to be added to the MSDN collection.
	// Returns a CString object that represents the version number of the help file.
    //
	void SetHelpVer(LPCTSTR lpszHelpVer);
	
	// This member function will return a pointer to the progress control
	// that is to be used during the integration process.
	// Returns a pointer to the progress control to be used during integration.
    //
	//CProgressCtrl* GetProgressCtrl() const;

	// This member function will set the progress control object that is to
	// be used during the integration progress. If set the progress control
	// will be initialized and updated during the integration process.
    //
	//void SetProgressCtrl(
      //  // A pointer to a CProgressCtrl object.
        //CProgressCtrl* pProgress);

	// This member function will activate a file open dialog to search for
	// a .chm file to be used when integrating with the MSDN collection.
	// Returns a CString object that represents the currently selected .chm file.
    //


	//CString FindChmFile(
      //  // A pointer to the file open dialog-box object’s parent or owner window.
        //CWnd* pWnd);

	// Returns a CString object that represents the currently selected .chi file.
	// This member function will activate a file open dialog to search for
	// a .chi file to be used when integrating with the MSDN collection.
    //
	//CString FindChiFile(
      //  // A pointer to the file open dialog-box object’s parent or owner window.
       // CWnd* pWnd);

	// This member function displays an error message to be used during integration.
	// Returns 'false' if the message displayed is an error, otherwise true.
    //
	bool DisplayMessage(
        // A string resource id that represents the message to display.
        UINT nMessage,
        // 'true' if this is an error message.
        bool bError=true);

	// This member function displays an error message to be used during integration.
	// Returns false if the message displayed is an error, otherwise true.
    //
	bool DisplayMessage(
        // A NULL terminated string that represents the message to display.
        LPCTSTR lpszMessage,
        // true if this is an error message.
        bool bError=true);

	// This member function will reset all of the data used for integration.
    //
	void ResetData();

	// This static member function will retrieve a reference to the one
	// and only CXTAccelManager object.  You can use this function to access
	// data members for the CXTAccelManager class.
	//
	// Example:
	// CMSDNIntegration::Get().Init( );
	// Returns a reference to the one and only CXTAccelManager object.
    //
	static CMSDNIntegration& Get();
	
	// This member function initializes the msdn integrator object.
    // Returns 'true' if successful, otherwise returns 'false'.
	//
	void Init();

    // This member function retrieves a safe backup file name for the file
    // specified by strFile.  The backup file name is used to backup the MSDN
    // collection and data files prior to integration.
    // Returns 'true' if successful, otherwise returns 'false'.
    //
	bool GetBackupName(
        // The name and path of the file to backup.
        const CString strFile,
        // Receives the backup name if successful.
        CString& strBackupName);

    // This member function is called to backup the MSDN collection file.
    // Returns 'true' if successful, otherwise returns 'false'.
	//
	bool BackupColFile();

    // This member function is called to backup the MSDN data file.
    // Returns 'true' if successful, otherwise returns 'false'.
	//
	bool BackupDatFile();

	// Retrieves the path of a special folder, identified by its CSIDL (nFolder).
    // Returns 'TRUE' if successful, otherwise returns 'FALSE'.
	//
	BOOL GetSpecialFolderPath(
		// Handle to the owner window the client should specify if it displays a 
		// dialog box or message box.
		HWND hwndOwner,
		// Pointer to a null-terminated string that receives the drive and path 
		// of the specified folder. This buffer must be at least MAX_PATH characters in size.
		LPTSTR lpszPath,
		// A CSIDL that identifies the folder of interest. If a virtual folder is specified, 
		// this function will fail.
		int nFolder,
		// Indicates if the folder should be created if it does not already exist. If this 
		// value is nonzero, the folder will be created. If this value is zero, the folder 
		// will not be created.
		BOOL fCreate);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // #if !defined(__MSDNINTEGRATION_H__)
