// VCF Application Wizards
// Copyright (C) 2004 the VCF team
//
// This file is a part of the Visual Component Framework.
// The code and information is provided "as-is" without
// warranty of any kind, either expressed or implied.

// Setup program for the VCF Application Wizards

main();

function main()
{
	var bDebug = false;
	var Args = WScript.Arguments;
	if(Args.length > 0 && Args(0) == "/debug")
		bDebug = true;

	// Create shell object
	var WSShell = WScript.CreateObject("WScript.Shell");
	// Create file system object
	var FileSys = WScript.CreateObject("Scripting.FileSystemObject");



// VCFAppWizard

	var strValue = FileSys.GetAbsolutePathName(".");
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

	var strVC7Key = "HKLM\\Software\\Microsoft\\VisualStudio\\7.1\\Setup\\VC\\ProductDir";
	try
	{
		strValue = WSShell.RegRead(strVC7Key);
	}
	catch(e)
	{
		WScript.Echo("ERROR: Cannot find where Visual Studio 7.1 is installed.");
		return;
	}

	var strDestFolder = strValue + "\\vcprojects";
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

	var strValue = FileSys.GetAbsolutePathName(".");
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

	var strVC7Key = "HKLM\\Software\\Microsoft\\VisualStudio\\7.1\\Setup\\VC\\ProductDir";
	try
	{
		strValue = WSShell.RegRead(strVC7Key);
	}
	catch(e)
	{
		WScript.Echo("ERROR: Cannot find where Visual Studio 7.1 is installed.");
		return;
	}

	var strDestFolder = strValue + "\\vcprojects";
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




// VCFLibraryAppWizard

	var strValue = FileSys.GetAbsolutePathName(".");
	if(strValue == null || strValue == "")
		strValue = ".";

	var strSourceFolder = strValue + "/" + "VCFLibraryAppWizard";
	if(bDebug)
		WScript.Echo("Source: " + strSourceFolder);

	if(!FileSys.FolderExists(strSourceFolder))
	{
		WScript.Echo("ERROR: Cannot find Wizard folder (should be: " + strSourceFolder + ")");
		return;
	}

	var strVC7Key = "HKLM\\Software\\Microsoft\\VisualStudio\\7.1\\Setup\\VC\\ProductDir";
	try
	{
		strValue = WSShell.RegRead(strVC7Key);
	}
	catch(e)
	{
		WScript.Echo("ERROR: Cannot find where Visual Studio 7.1 is installed.");
		return;
	}

	var strDestFolder = strValue + "\\vcprojects";
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
		strSrc = strSourceFolder + "\\VCFLibraryAppWizard.ico";
		FileSys.CopyFile(strSrc, strDest);
		strSrc = strSourceFolder + "\\VCFLibraryAppWizard.vsdir";
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

	// Read and write VCFLibraryAppWizard.vsz, replace path when found
	try
	{
		strSrc = strSourceFolder + "\\VCFLibraryAppWizard.vsz";
		strDest = strDestFolder + "\\VCFLibraryAppWizard.vsz";

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
		WScript.Echo("ERROR: Cannot read and write VCFLibraryAppWizard.vsz (" + strError + ")");
		return;
	}

	// WScript.Echo("VCF Library Application Wizard successfully installed - enjoy!");



// MVCAppWizard

	var strValue = FileSys.GetAbsolutePathName(".");
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

	var strVC7Key = "HKLM\\Software\\Microsoft\\VisualStudio\\7.1\\Setup\\VC\\ProductDir";
	try
	{
		strValue = WSShell.RegRead(strVC7Key);
	}
	catch(e)
	{
		WScript.Echo("ERROR: Cannot find where Visual Studio 7.1 is installed.");
		return;
	}

	var strDestFolder = strValue + "\\vcprojects";
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



// VPLApplicationWizard

	var strValue = FileSys.GetAbsolutePathName(".");
	if(strValue == null || strValue == "")
		strValue = ".";

	var strSourceFolder = strValue + "/" + "VPLApplicationWizard";
	if(bDebug)
		WScript.Echo("Source: " + strSourceFolder);

	if(!FileSys.FolderExists(strSourceFolder))
	{
		WScript.Echo("ERROR: Cannot find Wizard folder (should be: " + strSourceFolder + ")");
		return;
	}

	var strVC7Key = "HKLM\\Software\\Microsoft\\VisualStudio\\7.1\\Setup\\VC\\ProductDir";
	try
	{
		strValue = WSShell.RegRead(strVC7Key);
	}
	catch(e)
	{
		WScript.Echo("ERROR: Cannot find where Visual Studio 7.1 is installed.");
		return;
	}

	var strDestFolder = strValue + "\\vcprojects";
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
		strSrc = strSourceFolder + "\\VPLApplicationWizard.ico";
		FileSys.CopyFile(strSrc, strDest);
		strSrc = strSourceFolder + "\\VPLApplicationWizard.vsdir";
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

	// Read and write VPLApplicationWizard.vsz, replace path when found
	try
	{
		strSrc = strSourceFolder + "\\VPLApplicationWizard.vsz";
		strDest = strDestFolder + "\\VPLApplicationWizard.vsz";

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
		WScript.Echo("ERROR: Cannot read and write VPLApplicationWizard.vsz (" + strError + ")");
		return;
	}

	// WScript.Echo("VCF VPL Wizard successfully installed - enjoy!");


	WScript.Echo("The VCF Application Wizards has been successfully installed!");
}
