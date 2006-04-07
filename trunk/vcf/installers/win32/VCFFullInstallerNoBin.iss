[_ISTool]
EnableISX=true

[Components]
Name: Src; Description: VCF include files and source code; Types: full custom compact
Name: Examples; Description: VCF Example projects; Types: full custom
Name: VC6_Addins; Description: VCF Visual Studio 6 Addins; Types: full custom
Name: VC6_Wizards; Description: VCF Visual Studio 6 Application wizards; Types: full custom
Name: Help_Files; Description: VCF Help files; Types: full custom compact
Name: Help_Files/CHM_Help_Files; Description: Compiled HTML Help files; Types: custom compact full
Name: Help_Files/VC6_Help_Files; Description: Visual Studio 6/MSDN Help integration files (requires Compiled HTML Help files); Types: custom full; Flags: dontinheritcheck
Name: Help_Files/MSHelp2_Files; Description: MSHelp2 Help integration files for Visual Studio 7/8/2005 Express; Types: custom full; Flags: dontinheritcheck

[Dirs]
Name: {app}\bin
Name: {app}\lib
Name: {app}\src; Components: Src
Name: {app}\build; Components: Src
Name: {app}\examples; Components: Examples
Name: {app}\VC6-Addins; Components: VC6_Addins

[Files]
#include "vcfSrcFiles.iss"

; vc60 addins/wizards
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\Release\COMToVCFClassWizard.dll; DestDir: {app}\VC6-Addins; Components: VC6_Addins; Flags: regserver
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Release\vcfwizard.awx; DestDir: {app}\VC6-Addins; Components: VC6_Wizards; Flags: ignoreversion
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Release\VCFConsoleWiz.awx; DestDir: {app}\VC6-Addins; Components: VC6_Wizards; Flags: ignoreversion
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Release\VCFLibraryAppWizard.awx; DestDir: {app}\VC6-Addins; Components: VC6_Wizards; Flags: ignoreversion
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\Release\VCFNewClassWiz.dll; DestDir: {app}\VC6-Addins; Components: VC6_Addins; Flags: regserver
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Release\VPLAppWiz.awx; DestDir: {app}\VC6-Addins; Components: VC6_Wizards; Flags: ignoreversion
Source: C:\WINNT\system32\msvcp60.dll; DestDir: {app}\VC6-Addins

; various help files
Source: ..\..\docs\VCFDocs.VCF-VERSION.chm; DestDir: {app}\docs; Components: Help_Files/CHM_Help_Files  Help_Files/VC6_Help_Files
Source: ..\..\docs\VCFDocs.VCF-VERSION.chi; DestDir: {app}\docs; Components: Help_Files/CHM_Help_Files  Help_Files/VC6_Help_Files
Source: ..\..\docs\VCFSrcDocs.VCF-VERSION.chm; DestDir: {app}\docs; Components: Help_Files/CHM_Help_Files  Help_Files/VC6_Help_Files
Source: ..\..\docs\VCFSrcDocs.VCF-VERSION.chi; DestDir: {app}\docs; Components: Help_Files/CHM_Help_Files  Help_Files/VC6_Help_Files

;readme files
Source: ..\..\readme.txt; DestDir: {app}
Source: ..\..\readme.html; DestDir: {app}
Source: ..\..\quickbuild.txt; DestDir: {app}
Source: ..\..\quickbuild.html; DestDir: {app}

Source: ..\..\src\thirdparty\win32\MSDNIntegrator\MSDNIntegrator.exe; DestDir: {app}; Components: Help_Files/VC6_Help_Files

Source: ..\..\docs\VS7\H2Reg.exe; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\H2Reg.ini; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\H2Reg_cmd.ini; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\H2Reg_cmd_090.ini; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\VCFBook.0.9.0.HxS; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\VCFSrcDocs.0.9.0.HxS; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\VCFDocs.0.9.0.HxA; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\VCFDocs.0.9.0.HxC; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\VCFDocs.0.9.0_K.HxK; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\VCFDocs.0.9.0.HxT; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files
Source: ..\..\docs\VS7\VCFDocs.0.9.0_NamedUrlIndex.HxK; DestDir: {app}\docs; Components: Help_Files/MSHelp2_Files


Source: psvince.dll; Flags: dontcopy
Source: ..\..\build\resources\win32\vcf.ico; DestDir: {app}
Source: ..\..\src\thirdparty\win32\RegEnVar\RegEnVar.exe; DestDir: {app}

[Setup]
OutputDir=..\..\uploadToSF
OutputBaseFilename=VCFSrcOnlyInstaller-VCF-VERSION
AppCopyright=2000-2006 Jim Crafton
AppName=Visual Component Framework VCF-LONG-VERSION
AppVerName=Visual Component Framework VCF-LONG-VERSION
LicenseFile=..\..\license.txt
DefaultDirName={pf}\VCF-VCF-VERSION
DefaultGroupName=Visual Component Framework VCF-VERSION
AppPublisher=VCF
AppPublisherURL=http://vcf.sf.net
AppSupportURL=http://vcf-online.org
AppUpdatesURL=http://vcf.sf.net
AppVersion=VCF-VERSION
UninstallDisplayIcon={app}\vcf.ico
UninstallDisplayName=Visual Component Framework VCF-VERSION
WizardImageFile=wizimage.bmp
WizardImageBackColor=clBlack
WizardSmallImageFile=wizsmall.bmp
WizardImageStretch=false

[Registry]
;Root: HKCU; Subkey: Environment; ValueType: string; ValueName: VCF_INCLUDE; ValueData: {app}\include; Flags: uninsdeletevalue dontcreatekey; Components: Src Binaries
;Root: HKCU; Subkey: Environment; ValueType: string; ValueName: VCF_BIN; ValueData: {app}\bin; Components: Src Binaries
;Root: HKCU; Subkey: Environment; ValueType: string; ValueName: VCF_LIB; ValueData: {app}\lib; Components: Src Binaries
;Root: HKCU; Subkey: Environment; ValueType: string; ValueName: path; ValueData: "%VCF_BIN%;{olddata}"; Components: Src Binaries
Root: HKCU; Subkey: Software\Microsoft\Devstudio\6.0\Build System\Components\Platforms\Win32 (x86)\Directories; ValueType: string; ValueName: Include Dirs; ValueData: "{olddata};{app}\include"; Tasks: addvc6dirs
Root: HKCU; Subkey: Software\Microsoft\Devstudio\6.0\Build System\Components\Platforms\Win32 (x86)\Directories; ValueType: string; ValueName: Library Dirs; ValueData: "{olddata};{app}\lib"; Tasks: addvc6dirs
Root: HKCU; Subkey: Software\Microsoft\Devstudio\6.0\Build System\Components\Platforms\Win32 (x86)\Directories; ValueType: string; ValueName: Path Dirs; ValueData: "{olddata};{app}\bin"; Tasks: addvc6dirs

[Icons]
Name: {group}\Uninstall VCF; Filename: {uninstallexe}
Name: {group}\Submit Bug; Filename: http://sourceforge.net/tracker/?group_id=6796&atid=106796; IconFilename: {app}\vcf.ico; IconIndex: 0
Name: {group}\Online Documentation; Filename: http://vcf-online.org/docs/ref_manual/; IconFilename: {app}\vcf.ico; IconIndex: 0
Name: {group}\Online Source Documentation; Filename: http://vcf-online.org/docs/src_manual/; IconFilename: {app}\vcf.ico; IconIndex: 0
Name: {group}\VCF Documentation; Filename: {app}\docs\VCFDocs.VCF-VERSION.chm; Components: Help_Files/CHM_Help_Files
Name: {group}\VCF Source Documentation; Filename: {app}\docs\VCFSrcDocs.VCF-VERSION.chm; Components: Help_Files/CHM_Help_Files
Name: {group}\VCF Website; Filename: http://vcf-online.org; IconFilename: {app}\vcf.ico; IconIndex: 0

[Tasks]
Name: addenvpaths; Description: Add VCF environment variables, and update your Path
Name: addvc6dirs; Description: Add VCF Include and Library path to Microsoft's Visual C++ 6

Name: msdnintegrate; Description: Visual Studio 6; GroupDescription: Integrate VCF Help with Visual Studio/MSDN Help; Flags: unchecked; Components: Help_Files/VC6_Help_Files  Help_Files/CHM_Help_Files
Name: MSHelp2_msdnintegrate; Description: Visual Studio 7, 8, 2005 Express; GroupDescription: Integrate VCF Help with Visual Studio/MSDN Help; Flags: unchecked; Components: Help_Files/MSHelp2_Files

Name: installwizards; Description: Visual Studio 6; GroupDescription: Install Visual Studio Addins/Wizards; Flags: unchecked
;we are not supporting VC70 for wizards at the moment
;Name: VC70_installwizards; Description: Visual Studio 7.0 (.NET 2002); GroupDescription: Install Visual Studio Addins/Wizards; Components: Src; Flags: unchecked

Name: VC71_installwizards; Description: Visual Studio 7.1 (.NET 2003); GroupDescription: Install Visual Studio Addins/Wizards; Components: Src; Flags: unchecked
Name: VC80_installwizards; Description: Visual C++ 8.0 (Express 2005); GroupDescription: Install Visual Studio Addins/Wizards; Components: Src; Flags: unchecked


[Run]
Filename: {app}\MSDNIntegrator.exe; Parameters: "-guid ""{{858cf701-5e04-48ba-968e-46569c787d5f}"" -chi ""{app}\docs\VCFDocs.VCF-VERSION.chi""    -chm ""{app}\docs\VCFDocs.VCF-VERSION.chm""    -add -title ""VCF Documentation"""; StatusMsg: Registering VCF Documentation with MSDN...; Tasks: msdnintegrate; Components: Help_Files/VC6_Help_Files
Filename: {app}\MSDNIntegrator.exe; Parameters: "-guid ""{{cf54ec6b-a508-4b05-b04d-794bf0cb2757}"" -chi ""{app}\docs\VCFSrcDocs.VCF-VERSION.chi"" -chm ""{app}\docs\VCFSrcDocs.VCF-VERSION.chm"" -add -title ""VCF Source Documentation"""; StatusMsg: Registering VCF Documentation with MSDN...; Tasks: msdnintegrate; Components: Help_Files/VC6_Help_Files

Filename: {app}\RegEnVar.exe; Parameters: "--add-user-var VCF_BIN ""{app}\bin"""; Components: Src; Tasks: addenvpaths; Flags: runhidden
Filename: {app}\RegEnVar.exe; Parameters: "--add-user-var VCF_LIB ""{app}\lib"""; Components: Src; Tasks: addenvpaths; Flags: runhidden
Filename: {app}\RegEnVar.exe; Parameters: "--add-user-var VCF_INCLUDE ""{app}\src"""; Components: Src; Tasks: addenvpaths; Flags: runhidden
Filename: {app}\RegEnVar.exe; Parameters: --add-to-user-path %VCF_BIN%; Components: Src; Tasks: addenvpaths; Flags: runhidden

Filename: {app}\docs\H2Reg.exe; Parameters: "-R ""cmdfile=H2Reg_cmd_090.ini"""; Tasks: MSHelp2_msdnintegrate; Components: Help_Files/MSHelp2_Files

;run the quick build instructions!
Filename: {app}\quickbuild.html; Description: Read Quick build Instructions; Flags: shellexec nowait postinstall skipifsilent

;we are not supporting VC70 for wizards at the moment
;Filename: {app}\build\vc70\Add-Ins\Setup.js; Tasks: VC70_installwizards; Components: Src;  Flags: shellexec waituntilterminated
Filename: {app}\build\vc71\Add-Ins\Setup.js; Components: Src; Flags: shellexec waituntilterminated; Tasks: VC80_installwizards
Filename: {app}\build\vc80\Add-Ins\Setup-vcexpress.js; Components: Src; Flags: shellexec waituntilterminated; Tasks: VC80_installwizards

[UninstallRun]
Filename: {app}\MSDNIntegrator.exe; Parameters: "-guid ""{{858cf701-5e04-48ba-968e-46569c787d5f}"" -chi ""{app}\docs\VCFDocs.VCF-VERSION.chi"" -chm ""{app}\docs\VCFDocs.VCF-VERSION.chm"" -remove -title ""VCF Documentation"""; StatusMsg: Removing VCF Documentation with MSDN...; Components: Help_Files; Tasks: msdnintegrate
Filename: {app}\MSDNIntegrator.exe; Parameters: "-guid ""{{cf54ec6b-a508-4b05-b04d-794bf0cb2757}"" -chi ""{app}\docs\VCFSrcDocs.VCF-VERSION.chi"" -chm ""{app}\docs\VCFSrcDocs.VCF-VERSION.chm"" -remove -title ""VCF Source Documentation"""; StatusMsg: Removing VCF Documentation with MSDN...; Components: Help_Files; Tasks: msdnintegrate
Filename: {app}\RegEnVar.exe; Parameters: --del-from-user-path %VCF_BIN%; Tasks: addenvpaths; Components: Src; Flags: runhidden
Filename: {app}\RegEnVar.exe; Parameters: --del-user-var VCF_BIN; Tasks: addenvpaths; Components: Src; Flags: runhidden
Filename: {app}\RegEnVar.exe; Parameters: --del-user-var VCF_LIB; Tasks: addenvpaths; Components: Src; Flags: runhidden
Filename: {app}\RegEnVar.exe; Parameters: --del-user-var VCF_INCLUDE; Tasks: addenvpaths; Components: Src; Flags: runhidden


Filename: {app}\docs\H2Reg.exe; Parameters: "-U ""cmdfile=H2Reg_cmd_090.ini"""; Tasks: MSHelp2_msdnintegrate; Components: Help_Files/MSHelp2_Files
; Must uninstall VS addins/wizards through IDE, I guess.



[Code]
function IsModuleLoaded(modulename: String ):  Boolean;
external 'IsModuleLoaded@files:psvince.dll stdcall';



function ScriptDlgPages(CurPage: Integer; BackClicked: Boolean): Boolean;
var
	Next, isloaded: Boolean; module,msg: String;
	mbRes,msdnWnd:Integer;
begin
	Result := true;
	if (CurPage = wpReady) and (not BackClicked) then begin
		msg := 'Setup has detected that Microsoft''s Visual Studio is running.'#13#10 +
			'You should shut it down first before continuing.'#13#10 +
			'To continue with the installation anyways, click "Yes".'#13#10 +
			'To wait and retry again (Setup will attempt to verify that Visual Studio is not running), click "No".';

		module := 'msdev.exe';
		isloaded := IsModuleLoaded( module );
		if isloaded then begin
			mbRes := MsgBox(msg, mbError, MB_YESNO);
			if ( mbRes = mrNo ) then begin
				result := false;
			end
		end

		module := 'devenv.exe';
		isloaded := IsModuleLoaded( module );
		if isloaded then begin
			mbRes := MsgBox(msg, mbError, MB_YESNO);
			if ( mbRes = mrNo ) then begin
				result := false;
			end
		end

		msg := 'Setup has detected that Microsoft''s MSDN for Visual Studio 6.0 is running.'#13#10 +
			'You should shut it down first before continuing.'#13#10 +
			'To continue with the installation anyways, click "Yes".'#13#10 +
			'To wait and retry again (Setup will attempt to verify that MSDN is not running), click "No".';

		msdnWnd := FindWindowByWindowName( 'MSDN Library Visual Studio 6.0' );
		if ( msdnWnd > 0 ) then begin
			mbRes := MsgBox(msg, mbError, MB_YESNO);
			if ( mbRes = mrNo ) then begin
				result := false;
			end
		end

		msg := 'Setup has detected that Microsoft''s Visual Studio Document '#13#10 +
			'Explorer is running (dexplore.exe). You should shut it down first before continuing.'#13#10 +
			'To continue with the installation anyways, click "Yes".'#13#10 +
			'To wait and retry again (Setup will attempt to verify that Visual Studio is not running), click "No".';

		module := 'dexplore.exe';
		isloaded := IsModuleLoaded( module );
		if isloaded then begin
			mbRes := MsgBox(msg, mbError, MB_YESNO);
			if ( mbRes = mrNo ) then begin
				result := false;
			end
		end


	end
end;

function NextButtonClick(CurPage: Integer): Boolean;
begin
  Result := ScriptDlgPages(CurPage, False);
end;

function BackButtonClick(CurPage: Integer): Boolean;
begin
  Result := ScriptDlgPages(CurPage, True);
end;


procedure CurPageChanged(CurPage: Integer);
var
  vc6Key:String;
  VsCommonDir:String;
  templatesDir:String;
  tasks:String;
  components:String;
begin
  if ( CurPage = wpFinished ) then begin
    components := WizardSelectedComponents( false );

	tasks := WizardSelectedTasks( false );

	if ( (Pos( 'installwizards', tasks ) > 0) and (Pos( 'vc6_wizards', components ) > 0) ) then begin

      vc6Key := 'SOFTWARE\Microsoft\VisualStudio\6.0\Setup';
	  if ( RegValueExists( HKEY_LOCAL_MACHINE, vc6Key, 'VsCommonDir' ) )then begin

		RegQueryStringValue( HKEY_LOCAL_MACHINE, vc6Key, 'VsCommonDir', VsCommonDir );
	    templatesDir := VsCommonDir + '\MSDev98\Template\';

	    FileCopy( ExpandConstant('{app}\VC6-Addins') + '\VPLAppWiz.awx', templatesDir + 'VPLAppWiz.awx', true );
        FileCopy( ExpandConstant('{app}\VC6-Addins') + '\VCFLibraryAppWizard.awx', templatesDir + 'VCFLibraryAppWizard.awx', true );
        FileCopy( ExpandConstant('{app}\VC6-Addins') + '\VCFConsoleWiz.awx', templatesDir + 'VCFConsoleWiz.awx', true );
        FileCopy( ExpandConstant('{app}\VC6-Addins') + '\vcfwizard.awx', templatesDir + 'vcfwizard.awx', true );
	  end
    end
  end
end;
