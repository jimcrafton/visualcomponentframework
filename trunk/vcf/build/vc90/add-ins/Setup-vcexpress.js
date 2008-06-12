// VCF Application Wizards
// Copyright (C) 2004 the VCF team
//
// This file is a part of the Visual Component Framework.
// The code and information is provided "as-is" without
// warranty of any kind, either expressed or implied.

// Setup program for the VCF Application Wizards

main();

function hello()
{
	WScript.Echo( "hello!" );
}


function isVC90Express()
{
	var result = false;
	var WSShell = WScript.CreateObject("WScript.Shell");
	var FileSys = WScript.CreateObject("Scripting.FileSystemObject");
	
	var strVC8Key = "HKLM\\Software\\Microsoft\\VCExpress\\9.0\\Setup\\VC\\ProductDir";
	try
	{
		if ( FileSys.FolderExists( WSShell.RegRead(strVC8Key) ) ) {
			result = true;
		}
	}
	catch(e)
	{		
		try {
			strVC8Key = "HKLM\\SOFTWARE\\Microsoft\\VisualStudio\\9.0\\Setup\\VC\\ProductDir";
			if ( FileSys.FolderExists( WSShell.RegRead(strVC8Key) ) ) {
				result = false;
			}
		}
		catch(e)
		{
			WScript.Echo("ERROR: Cannot find where Visual Studio 9.0 is installed.");
		}
	}
	
	return result;
}

function getVC90ProductDir()
{
	var result = "Unknown";
	var WSShell = WScript.CreateObject("WScript.Shell");
	
	var strVC8Key = "HKLM\\Software\\Microsoft\\VCExpress\\9.0\\Setup\\VC\\ProductDir";
	try
	{
		result = WSShell.RegRead(strVC8Key);
	}
	catch(e)
	{		
		try {
			strVC8Key = "HKLM\\SOFTWARE\\Microsoft\\VisualStudio\\9.0\\Setup\\VC\\ProductDir";
			result = WSShell.RegRead(strVC8Key);
		}
		catch(e)
		{
			WScript.Echo("ERROR: Cannot find where Visual Studio 9.0 is installed.");
		}
	}
	
	return result;
}

function getInstallDestFolder( rootDir )
{
	var result;
	var FileSys = WScript.CreateObject("Scripting.FileSystemObject");
	
	result = FileSys.BuildPath( rootDir, "Express\\vcprojects" );
	if ( !isVC90Express() ) {
		result = FileSys.BuildPath( rootDir, "vcprojects" );
	}
	
	return result;
}

function main()
{	
	var bDebug = false;
	var expressVer = isVC90Express();
	
	var Args = WScript.Arguments;
	if(Args.length > 0 && Args(0) == "/debug")
		bDebug = true;

	// Create shell object
	var WSShell = WScript.CreateObject("WScript.Shell");
	// Create file system object
	var FileSys = WScript.CreateObject("Scripting.FileSystemObject");


	var WshSysEnv = WSShell.Environment("USER");
	var addinsDir = WshSysEnv("VCF_ROOT") + "/build/vc90/add-ins";
	

// VCFAppWizard

	var strValue = FileSys.GetAbsolutePathName(addinsDir);
	if(strValue == null || strValue == "")
		strValue = ".";

	var strSourceFolder = strValue + "/" + "VCFAppWizard";
	if(bDebug)
		WScript.Echo("Source: " + strSourceFolder);

	if(!FileSys.FolderExists(strSourceFolder))
	{
		WScript.Echo("ERROR: Cannot find Wizard folder (should be: " + strSourceFolder + ")");
		return;
	}

	
	strValue = getVC90ProductDir();

	var strDestFolder = getInstallDestFolder(strValue);
	
	WScript.Echo("Destination: " + strDestFolder);
	
	if(bDebug)
		WScript.Echo("Destination: " + strDestFolder);
	if(!FileSys.FolderExists(strDestFolder))
	{
		WScript.Echo("ERROR: Cannot find destination folder (should be: " + strDestFolder + ")");
		return;
	}

	var strDest = strDestFolder + "\\";
	var strSrc = "";

	// Copy files
	try
	{
		strSrc = strSourceFolder + "\\VCFAppWizard.ico";
		FileSys.CopyFile(strSrc, strDest);
		strSrc = strSourceFolder + "\\VCFAppWizard.vsdir";
		FileSys.CopyFile(strSrc, strDest);
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot copy file (" + strError + ")");
		return;
	}

	// Read and write VCFAppWizard.vsz, replace path when found
	try
	{
		strSrc = strSourceFolder + "\\VCFAppWizard.vsz";
		strDest = strDestFolder + "\\VCFAppWizard.vsz";

		var ForReading = 1;
		var fileSrc = FileSys.OpenTextFile(strSrc, ForReading);
		if(fileSrc == null)
		{
			WScript.Echo("ERROR: Cannot open source file " + strSrc);
			return;
		}

		var ForWriting = 2;
		var fileDest = FileSys.OpenTextFile(strDest, ForWriting, true);
		if(fileDest == null)
		{
			WScript.Echo("ERROR: Cannot open destination file" + strDest);
			return;
		}

		while(!fileSrc.AtEndOfStream)
		{
			var strLine = fileSrc.ReadLine();
			if(strLine.indexOf("ABSOLUTE_PATH") != -1)
				strLine = "Param=\"ABSOLUTE_PATH = " + strSourceFolder + "\"";
			fileDest.WriteLine(strLine);
		}

		fileSrc.Close();
		fileDest.Close();
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot read and write VCFAppWizard.vsz (" + strError + ")");
		return;
	}

	//WScript.Echo("VCF Application Wizard successfully installed - enjoy!");



// VCFConsoleWizard

	var strValue = FileSys.GetAbsolutePathName(addinsDir);
	if(strValue == null || strValue == "")
		strValue = ".";

	var strSourceFolder = strValue + "/" + "VCFConsoleWizard";
	if(bDebug)
		WScript.Echo("Source: " + strSourceFolder);

	if(!FileSys.FolderExists(strSourceFolder))
	{
		WScript.Echo("ERROR: Cannot find Wizard folder (should be: " + strSourceFolder + ")");
		return;
	}

	strValue = getVC90ProductDir();
	var strDestFolder = getInstallDestFolder(strValue);	
	
	if(bDebug)
		WScript.Echo("Destination: " + strDestFolder);
	if(!FileSys.FolderExists(strDestFolder))
	{
		WScript.Echo("ERROR: Cannot find destination folder (should be: " + strDestFolder + ")");
		return;
	}

	var strDest = strDestFolder + "\\";
	var strSrc = "";

	// Copy files
	try
	{
		strSrc = strSourceFolder + "\\VCFConsoleWizard.ico";
		FileSys.CopyFile(strSrc, strDest);
		strSrc = strSourceFolder + "\\VCFConsoleWizard.vsdir";
		FileSys.CopyFile(strSrc, strDest);
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot copy file (" + strError + ")");
		return;
	}

	// Read and write VCFConsoleWizard.vsz, replace path when found
	try
	{
		strSrc = strSourceFolder + "\\VCFConsoleWizard.vsz";
		strDest = strDestFolder + "\\VCFConsoleWizard.vsz";

		var ForReading = 1;
		var fileSrc = FileSys.OpenTextFile(strSrc, ForReading);
		if(fileSrc == null)
		{
			WScript.Echo("ERROR: Cannot open source file " + strSrc);
			return;
		}

		var ForWriting = 2;
		var fileDest = FileSys.OpenTextFile(strDest, ForWriting, true);
		if(fileDest == null)
		{
			WScript.Echo("ERROR: Cannot open destination file" + strDest);
			return;
		}

		while(!fileSrc.AtEndOfStream)
		{
			var strLine = fileSrc.ReadLine();
			if(strLine.indexOf("ABSOLUTE_PATH") != -1)
				strLine = "Param=\"ABSOLUTE_PATH = " + strSourceFolder + "\"";
			fileDest.WriteLine(strLine);
		}

		fileSrc.Close();
		fileDest.Close();
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot read and write VCFConsoleWizard.vsz (" + strError + ")");
		return;
	}

	// WScript.Echo("VCF Console Application Wizard successfully installed - enjoy!");


// MVCAppWizard

	var strValue = FileSys.GetAbsolutePathName(addinsDir);
	if(strValue == null || strValue == "")
		strValue = ".";

	var strSourceFolder = strValue + "/" + "MVCAppWizard";
	if(bDebug)
		WScript.Echo("Source: " + strSourceFolder);

	if(!FileSys.FolderExists(strSourceFolder))
	{
		WScript.Echo("ERROR: Cannot find Wizard folder (should be: " + strSourceFolder + ")");
		return;
	}

	strValue = getVC90ProductDir();
	var strDestFolder = getInstallDestFolder(strValue);	
	
	if(bDebug)
		WScript.Echo("Destination: " + strDestFolder);
	if(!FileSys.FolderExists(strDestFolder))
	{
		WScript.Echo("ERROR: Cannot find destination folder (should be: " + strDestFolder + ")");
		return;
	}

	var strDest = strDestFolder + "\\";
	var strSrc = "";

	// Copy files
	try
	{
		strSrc = strSourceFolder + "\\MVCAppWizard.ico";
		FileSys.CopyFile(strSrc, strDest);
		strSrc = strSourceFolder + "\\MVCAppWizard.vsdir";
		FileSys.CopyFile(strSrc, strDest);
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot copy file (" + strError + ")");
		return;
	}

	// Read and write MVCAppWizard.vsz, replace path when found
	try
	{
		strSrc = strSourceFolder + "\\MVCAppWizard.vsz";
		strDest = strDestFolder + "\\MVCAppWizard.vsz";

		var ForReading = 1;
		var fileSrc = FileSys.OpenTextFile(strSrc, ForReading);
		if(fileSrc == null)
		{
			WScript.Echo("ERROR: Cannot open source file " + strSrc);
			return;
		}

		var ForWriting = 2;
		var fileDest = FileSys.OpenTextFile(strDest, ForWriting, true);
		if(fileDest == null)
		{
			WScript.Echo("ERROR: Cannot open destination file" + strDest);
			return;
		}

		while(!fileSrc.AtEndOfStream)
		{
			var strLine = fileSrc.ReadLine();
			if(strLine.indexOf("ABSOLUTE_PATH") != -1)
				strLine = "Param=\"ABSOLUTE_PATH = " + strSourceFolder + "\"";
			fileDest.WriteLine(strLine);
		}

		fileSrc.Close();
		fileDest.Close();
	}
	catch(e)
	{
		var strError = "no info";
		if(e.description.length != 0)
			strError = e.description;
		WScript.Echo("ERROR: Cannot read and write MVCAppWizard.vsz (" + strError + ")");
		return;
	}

	// WScript.Echo("VCF MVC Application Wizard successfully installed - enjoy!");



	WScript.Echo("The VCF Application Wizards has been successfully installed!");
}
