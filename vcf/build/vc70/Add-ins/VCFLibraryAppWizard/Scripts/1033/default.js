
function OnFinish(selProj, selObj)
{
	try
	{
		var strProjectPath = wizard.FindSymbol('PROJECT_PATH');
		var strProjectName = wizard.FindSymbol('PROJECT_NAME');

		selProj = CreateCustomProject(strProjectName, strProjectPath);
		AddConfig(selProj, strProjectName);
		AddFilters(selProj);

		var InfFile = CreateCustomInfFile();
		AddFilesToCustomProj(selProj, strProjectName, strProjectPath, InfFile);
		PchSettings(selProj);
		InfFile.Delete();

		selProj.Object.Save();
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
	}
	catch(e)
	{
		throw e;
	}
}

function AddConfig(proj, strProjectName)
{
	try
	{

///DEBUG/////////////////////////////////////////////////////////////////

		var config = proj.Object.Configurations('Debug');
		config.CharacterSet = charSetMBCS;
		config.ConfigurationType = typeDynamicLibrary;
		config.IntermediateDirectory = 'Debug';
		config.OutputDirectory = 'Debug';

		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.RuntimeLibrary = rtMultiThreadedDebugDLL;
		CLTool.WarningLevel = warningLevelOption.warningLevel_3;
		CLTool.BasicRuntimeChecks = basicRuntimeCheckOption.runtimeBasicCheckAll;
		
		var strDefines = GetPlatformDefine(config);
		strDefines += "_DEBUG";
		strDefines += ";_WINDOWS;_USRDLL;";
		var strExports = wizard.FindSymbol("UPPER_CASE_PROJECT_NAME") + "_EXPORTS";
		strDefines += strExports;
		strDefines += ";USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL";
		CLTool.PreprocessorDefinitions = strDefines;
		CLTool.DebugInformationFormat = debugEditAndContinue;
		CLTool.RuntimeTypeInfo = true;
		CLTool.AdditionalIncludeDirectories = "$(VCF_ROOT)/src";
		CLTool.Optimization = optimizeOption.optimizeDisabled;

		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.AdditionalLibraryDirectories = "$(VCF_ROOT)/lib";
		LinkTool.AdditionalDependencies = "odbc32.lib odbccp32.lib rpcrt4.lib";
		LinkTool.ProgramDatabaseFile = "$(OutDir)/" + strProjectName + ".pdb";
		LinkTool.GenerateDebugInformation = true;
		LinkTool.LinkIncremental = linkIncrementalYes;
		LinkTool.SubSystem = subSystemWindows;
		LinkTool.ImportLibrary = "$(OutDir)/" + strProjectName + ".lib";
		LinkTool.OutputFile = "$(OutDir)/" + strProjectName + ".dll";
		LinkTool.TargetMachine = machineTypeOption.machineX86;
		LinkTool.SuppressStartupBanner = true;
		LinkTool.LinkIncremental = linkIncrementalType.linkIncrementalNo;



///RELEASE///////////////////////////////////////////////////////////////

		config = proj.Object.Configurations('Release');
		config.CharacterSet = charSetMBCS;
		config.ConfigurationType = typeDynamicLibrary;
		config.IntermediateDirectory = 'Release';
		config.OutputDirectory = 'Release';

		var CLTool = config.Tools('VCCLCompilerTool');
		CLTool.RuntimeLibrary = rtMultiThreadedDLL;
		CLTool.WarningLevel = warningLevelOption.warningLevel_3;
		
		var strDefines = GetPlatformDefine(config);
		strDefines += "NDEBUG";
		CLTool.DebugInformationFormat = debugEnabled;
		strDefines += ";_WINDOWS;_USRDLL;";
		var strExports = wizard.FindSymbol("UPPER_CASE_PROJECT_NAME") + "_EXPORTS";
		strDefines += strExports;
		strDefines += ";USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;USE_APPLICATIONKIT_DLL";
		CLTool.PreprocessorDefinitions = strDefines;
		CLTool.RuntimeTypeInfo = true;
		CLTool.AdditionalIncludeDirectories = "$(VCF_ROOT)/src";
		CLTool.EnableFunctionLevelLinking = true;
		CLTool.InlineFunctionExpansion = inlineExpansionOption.expandOnlyInline;
		CLTool.Optimization = optimizeOption.optimizeMinSpace;
		CLTool.StringPooling = true;
		CLTool.BufferSecurityCheck = true

		var LinkTool = config.Tools('VCLinkerTool');
		LinkTool.AdditionalLibraryDirectories = "$(VCF_ROOT)/lib";
		LinkTool.AdditionalDependencies = "odbc32.lib odbccp32.lib rpcrt4.lib";
		LinkTool.GenerateDebugInformation = true;
		LinkTool.LinkIncremental = linkIncrementalNo;
		LinkTool.SubSystem = subSystemWindows;
		LinkTool.ImportLibrary = "$(OutDir)/" + strProjectName + ".lib";
		LinkTool.OutputFile = "$(OutDir)/" + strProjectName + ".dll";
		LinkTool.TargetMachine = machineTypeOption.machineX86;
		LinkTool.SuppressStartupBanner = true;
		LinkTool.LinkIncremental = linkIncrementalType.linkIncrementalNo;
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

		if (strName == 'LibMain.cpp')
			strTarget = strProjectName + '.cpp';

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
