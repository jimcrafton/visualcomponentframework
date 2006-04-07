
function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		var bEmptyProject = wizard.FindSymbol("EMPTY_PROJECT");

		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddCommonConfig(selProj, strProjectName);
		AddSpecificConfig(selProj, strProjectName,bEmptyProject);
		AddFilters(selProj);

		if (!bEmptyProject)
		{
			var InfFile = CreateInfFile();
			AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
			PchSettings(selProj);
			InfFile.Delete();

			selProj.Object.Save();
		}
		
	}
	catch(e)
	{
		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}

function CreateCustomProject(strProjectName, strProjectPath)
{
	try
	{
		var strProjTemplatePath = wizard.FindSymbol('PROJECT_TEMPLATE_PATH');
		var strProjTemplate = '';
		strProjTemplate = strProjTemplatePath + '\\default.vcproj';

		var Solution = dte.Solution;
		var strSolutionName = "";
		if (wizard.FindSymbol("CLOSE_SOLUTION"))
		{
			Solution.Close();
			strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
			if (strSolutionName.length)
			{
				var strSolutionPath = strProjectPath.substr(0, strProjectPath.length - strProjectName.length);
				Solution.Create(strSolutionPath, strSolutionName);
			}
		}

		var strProjectNameWithExt = '';
		strProjectNameWithExt = strProjectName + '.vcproj';

		var oTarget = wizard.FindSymbol("TARGET");
		var prj;
		if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject)  // vsWizardAddSubProject
		{
			var prjItem = oTarget.AddFromTemplate(strProjTemplate, strProjectNameWithExt);
			prj = prjItem.SubProject;
		}
		else
		{
			prj = oTarget.AddFromTemplate(strProjTemplate, strProjectPath, strProjectNameWithExt);
		}
		return prj;
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilters(proj)
{
	try
	{
		// Add the folders to your project
		var group = proj.Object.AddFilter('Source Files');
		group.Filter = "cpp;c;cxx;def;odl;idl;hpj;bat;asm";
		
		var group = proj.Object.AddFilter('Header Files');
		group.Filter = "h;hpp;hxx;hm;inl;inc";
		
		var group = proj.Object.AddFilter('Resource files');
		group.Filter = "rc;ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe";		
	}
	catch(e)
	{
		throw e;
	}
}

function AddSpecificConfig(proj, strProjectName, bEmptyProject)
{
	try
	{
		var bLibDynamic = wizard.FindSymbol('LIB_DYNAMIC');
		var bLibStatic = wizard.FindSymbol('LIB_STATIC');
		var bLibNet = wizard.FindSymbol('LIB_NET');
		var bLibRemote = wizard.FindSymbol('LIB_REMOTE');

//DEBUG//////////////////////////////////////////////////////////////
		var config = proj.Object.Configurations('Debug|Win32');
		
		config.IntermediateDirectory = '$(ConfigurationName)';
		config.OutputDirectory = '$(ConfigurationName)';
		config.CharacterSet = charSetMBCS;

	var debugSettings = config.DebugSettings;
	
		debugSettings.WorkingDirectory = "$(ConfigurationName)";
		debugSettings.Command = "$(ConfigurationName)\\$(ProjectName).exe";
	
	
		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.RuntimeLibrary = rtMultiThreadedDebugDLL;
		CLTool.UsePrecompiledHeader = pchNone;
		

		CLTool.MinimalRebuild = false;
		CLTool.DebugInformationFormat = debugEditAndContinue;
		CLTool.BasicRuntimeChecks = runtimeBasicCheckAll;
		
		CLTool.Optimization = optimizeDisabled;
		
		CLTool.ExceptionHandling = cppExceptionHandlingYes;
		CLTool.AdditionalIncludeDirectories = "$(VCF_INCLUDE)";
		CLTool.WarningLevel = WarningLevel_3;
		
	
		if(bLibDynamic)
		{
			if(bLibRemote)
			{
				CLTool.PreprocessorDefinitions = "WIN32;_DEBUG;USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL;USE_NETKIT_DLL;USE_REMOTEKIT_DLL";
			}
			else if(bLibNet)
			{
				CLTool.PreprocessorDefinitions = "WIN32;_DEBUG;USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL;USE_NETKIT_DLL";
			}
			else
			{
				CLTool.PreprocessorDefinitions = "WIN32;_DEBUG;USE_APPLICATIONKIT_DLL";
			}
		}
		else if(bLibStatic)
		{
			if(bLibRemote)
			{
				CLTool.PreprocessorDefinitions = "WIN32;_DEBUG;USE_FOUNDATIONKIT_LIB;USE_GRAPHICSKIT_LIB;USE_APPLICATIONKIT_LIB;USE_NETKIT_LIB;USE_REMOTEKIT_LIB";
			}
			else if(bLibNet)
			{
				CLTool.PreprocessorDefinitions = "WIN32;_DEBUG;USE_FOUNDATIONKIT_LIB;USE_GRAPHICSKIT_LIB;USE_APPLICATIONKIT_LIB;USE_NETKIT_LIB";
			}
			else
			{
				CLTool.PreprocessorDefinitions = "WIN32;_DEBUG;USE_APPLICATIONKIT_LIB";
			}
		}
		CLTool.RuntimeTypeInfo = true;
		CLTool.SuppressStartupBanner = true;

		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.AdditionalLibraryDirectories = "$(VCF_LIB)";
		
		if(bLibDynamic)
		{
			LinkTool.AdditionalDependencies = "odbc32.lib odbccp32.lib rpcrt4.lib";
		}
		else if(bLibStatic)
		{
			LinkTool.AdditionalDependencies = "comctl32.lib odbc32.lib odbccp32.lib rpcrt4.lib";
		}
			
		LinkTool.EntryPointSymbol = 'mainCRTStartup';
		LinkTool.SubSystem = subSystemWindows;
		LinkTool.GenerateDebugInformation = true;
		LinkTool.ProgramDatabaseFile = "$(OutDir)/" + strProjectName + ".pdb";
		LinkTool.TargetMachine = machineX86;
		


//RELEASE////////////////////////////////////////////////////////////
		config = proj.Object.Configurations('Release|Win32');
		config.IntermediateDirectory = '$(ConfigurationName)';
		config.OutputDirectory = '$(ConfigurationName)';
		config.CharacterSet = charSetMBCS;

		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.UsePrecompiledHeader = pchNone;
		CLTool.RuntimeLibrary = rtMultiThreadedDLL;
		CLTool.ExceptionHandling = cppExceptionHandlingYes;
		CLTool.BufferSecurityCheck = true
		CLTool.DebugInformationFormat = debugDisabled;
		CLTool.AdditionalIncludeDirectories = "$(VCF_INCLUDE)";
		CLTool.WarningLevel = WarningLevel_3;
		CLTool.EnableFunctionLevelLinking = true;
		CLTool.InlineFunctionExpansion = expandOnlyInline;
		CLTool.Optimization = optimizeMinSpace;
		CLTool.StringPooling = true;
		if(bLibDynamic)
		{
			if(bLibRemote)
			{
				CLTool.PreprocessorDefinitions = "WIN32;NDEBUG;USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL;USE_REMOTEKIT_DLL;USE_NETKIT_DLL";
			}
			else if(bLibNet)
			{
				CLTool.PreprocessorDefinitions = "WIN32;NDEBUG;USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL;USE_NETKIT_DLL";
			}
			else
			{
				CLTool.PreprocessorDefinitions = "WIN32;NDEBUG;USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL";
			}
		}
		else if(bLibStatic)
		{
			if(bLibRemote)
			{
				CLTool.PreprocessorDefinitions = "WIN32;NDEBUG;USE_FOUNDATIONKIT_LIB;USE_GRAPHICSKIT_LIB;USE_APPLICATIONKIT_LIB;USE_NETKIT_LIB;USE_REMOTEKIT_LIB";
			}
			else if(bLibNet)
			{
				CLTool.PreprocessorDefinitions = "WIN32;NDEBUG;USE_FOUNDATIONKIT_LIB;USE_GRAPHICSKIT_LIB;USE_APPLICATIONKIT_LIB;USE_NETKIT_LIB";
			}
			else
			{
				CLTool.PreprocessorDefinitions = "WIN32;NDEBUG;USE_FOUNDATIONKIT_LIB;USE_GRAPHICSKIT_LIB;USE_APPLICATIONKIT_LIB";
			}
		}
		CLTool.RuntimeTypeInfo = true;
		CLTool.SuppressStartupBanner = true;

		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.AdditionalOptions = "/MACHINE:I386";
		LinkTool.AdditionalLibraryDirectories = "$(VCF_LIB)";
		if(bLibDynamic)
		{
			LinkTool.AdditionalDependencies = "odbc32.lib odbccp32.lib rpcrt4.lib";
		}
		else if(bLibStatic)
		{
			LinkTool.AdditionalDependencies = "comctl32.lib odbc32.lib odbccp32.lib rpcrt4.lib";
		}
		LinkTool.EntryPointSymbol = 'mainCRTStartup';
		LinkTool.SubSystem = subSystemWindows;

	}
	catch(e)
	{
		throw e;
	}
}

function PchSettings(proj)
{
	// TODO: specify pch settings
}

function DelFile(fso, strWizTempFile)
{
	try
	{
		if (fso.FileExists(strWizTempFile))
		{
			var tmpFile = fso.GetFile(strWizTempFile);
			tmpFile.Delete();
		}
	}
	catch(e)
	{
		throw e;
	}
}

function CreateCustomInfFile()
{
	try
	{
		var fso, TemplatesFolder, TemplateFiles, strTemplate;
		fso = new ActiveXObject('Scripting.FileSystemObject');

		var TemporaryFolder = 2;
		var tfolder = fso.GetSpecialFolder(TemporaryFolder);
		var strTempFolder = tfolder.Drive + '\\' + tfolder.Name;

		var strWizTempFile = strTempFolder + "\\" + fso.GetTempName();

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');
		var strInfFile = strTemplatePath + '\\Templates.inf';
		wizard.RenderTemplate(strInfFile, strWizTempFile);

		var WizTempFile = fso.GetFile(strWizTempFile);
		return WizTempFile;
	}
	catch(e)
	{
		throw e;
	}
}

function GetTargetName(strName, strProjectName)
{
	try
	{
		// TODO: set the name of the rendered file based on the template filename
		var strTarget = strName;

		if (strName == 'readme.txt')
			strTarget = 'ReadMe.txt';

		if (strName == 'res\\app.rc')
			strTarget = 'res\\' + strProjectName + '.rc'

		if (strName == 'UndoAppAbout.h')
			strTarget = strProjectName + 'About.h'

		if (strName == 'UndoAppAbout.cpp')
			strTarget = strProjectName + 'About.cpp'

		if (strName == 'UndoApp.h')
			strTarget = strProjectName + '.h'

		if (strName == 'UndoApp.cpp')
			strTarget = strProjectName + '.cpp'

		if (strName == 'UndoAppApplication.h')
			strTarget = strProjectName + 'Application.h'

		if (strName == 'UndoAppApplication.cpp')
			strTarget = strProjectName + 'Application.cpp'

		return strTarget; 
	}
	catch(e)
	{
		throw e;
	}
}

function AddFilesToCustomProj(proj, strProjectName, strProjectPath, InfFile)
{
	try
	{
		var projItems = proj.ProjectItems

		var strTemplatePath = wizard.FindSymbol('TEMPLATES_PATH');

		var strTpl = '';
		var strName = '';

		var strTextStream = InfFile.OpenAsTextStream(1, -2);
		while (!strTextStream.AtEndOfStream)
		{
			strTpl = strTextStream.ReadLine();
			if (strTpl != '')
			{
				strName = strTpl;
				var strTarget = GetTargetName(strName, strProjectName);
				var strTemplate = strTemplatePath + '\\' + strTpl;
				var strFile = strProjectPath + '\\' + strTarget;

				var bCopyOnly = false;  //"true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
				var strExt = strName.substr(strName.lastIndexOf("."));
				if(strExt==".bmp" || strExt==".ico" || strExt==".gif" || strExt==".rtf" || strExt==".css")
					bCopyOnly = true;
				wizard.RenderTemplate(strTemplate, strFile, bCopyOnly);
				proj.Object.AddFile(strFile);
			}
		}
		strTextStream.Close();
	}
	catch(e)
	{
		throw e;
	}
}
