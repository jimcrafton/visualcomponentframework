[_ISTool]
EnableISX=true

[Components]
Name: VC_Addins; Description: VCF Visual Studio 6 Addins; Types: full custom
Name: Help_Files; Description: VCF Help files; Types: full custom compact
Name: Binaries; Description: Precompiled VCF Exe's, DLL's, and .Libs (VC6 binaries); Types: full custom compact
Name: VC_Wizards; Description: MS Visual C++ 6 Appwizards; Types: full custom
Name: Src; Description: VCF include files and source code; Types: full custom compact
Name: Tutorials; Description: VCF Tutorials and test projects; Types: full custom

[Dirs]
Name: {app}\bin; Components: Binaries
Name: {app}\lib; Components: Binaries
Name: {app}\include; Components: Src
Name: {app}\src; Components: Src
Name: {app}\build; Components: Src
Name: {app}\test; Components: Src
Name: {app}\examples; Components: Src
Name: {app}\VC6-Addins; Components: VC_Addins




[Files]
#include "vcfSrcFiles.iss"
Source: ..\..\bin\GraphicsKit_vc6.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\ApplicationKit_vc6_d.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\FoundationKit_vc6.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\FoundationKit_vc6_d.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\ApplicationKit_vc6.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\GraphicsKit_vc6_d.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\ImageFormats_vc6.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\ImageFormats_vc6_d.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\NetworkKit_vc6.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\NetworkKit_vc6_d.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\RemoteObjectKit_vc6.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\RemoteObjectKit_vc6_d.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\Win32HTMLBrowser_vc6.dll; DestDir: {app}\bin; Components: Binaries
Source: ..\..\bin\Win32HTMLBrowser_vc6_d.dll; DestDir: {app}\bin; Components: Binaries

Source: ..\..\lib\FreeImage_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\ApplicationKit_vc6_d.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\ApplicationKit_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\ApplicationKit_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\FoundationKit_vc6.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\FoundationKit_vc6_d.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\FoundationKit_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\FoundationKit_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\ApplicationKit_vc6.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\FreeImage_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\GraphicsKit_vc6.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\GraphicsKit_vc6_d.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\GraphicsKit_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\GraphicsKit_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\LibJPEG_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\LibJPEG_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\LibMNG_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\LibMNG_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\LibPNG_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\LibPNG_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\LibTIFF_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\LibTIFF_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\NetworkKit_vc6.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\NetworkKit_vc6_d.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\NetworkKit_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\NetworkKit_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\RemoteObjectKit_vc6.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\RemoteObjectKit_vc6_d.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\RemoteObjectKit_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\RemoteObjectKit_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\Win32HTMLBrowser_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\Win32HTMLBrowser_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\ZLib_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\ZLib_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\libAGG_vc6_s.lib; DestDir: {app}\lib; Components: Binaries
Source: ..\..\lib\libAGG_vc6_sd.lib; DestDir: {app}\lib; Components: Binaries

Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\Release\COMToVCFClassWizard.dll; DestDir: {app}\VC6-Addins; Components: VC_Addins; Flags: regserver
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Release\vcfwizard.awx; DestDir: {app}\VC6-Addins; Components: VC_Wizards; Flags: ignoreversion
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Release\VCFConsoleWiz.awx; DestDir: {app}\VC6-Addins; Components: VC_Wizards; Flags: ignoreversion
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Release\VCFLibraryAppWizard.awx; DestDir: {app}\VC6-Addins; Components: VC_Wizards; Flags: ignoreversion
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\Release\VCFNewClassWiz.dll; DestDir: {app}\VC6-Addins; Components: VC_Addins; Flags: regserver
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Release\VPLAppWiz.awx; DestDir: {app}\VC6-Addins; Components: VC_Wizards; Flags: ignoreversion

Source: C:\WINNT\system32\msvcp60.dll; DestDir: {app}\VC6-Addins
Source: ..\..\docs\VCFDocs.0.6.4.chm; DestDir: {app}\docs; Components: Help_Files
Source: ..\..\docs\VCFDocs.0.6.4.chi; DestDir: {app}\docs; Components: Help_Files
Source: ..\..\docs\VCFSrcDocs.0.6.4.chm; DestDir: {app}\docs; Components: Help_Files
Source: ..\..\docs\VCFSrcDocs.0.6.4.chi; DestDir: {app}\docs; Components: Help_Files
Source: ..\..\thirdparty\win32\MSDNIntegrator\MSDNIntegrator.exe; DestDir: {app}
Source: D:\Program Files\ISTool 4\psvince.dll; Flags: dontcopy
Source: ..\..\build\resources\win32\vcf.ico; DestDir: {app}
Source: ..\..\..\..\RegEnVar.exe; DestDir: {app}

[Setup]
OutputDir=..\..\uploadToSF
OutputBaseFilename=VCFFullInstaller-VCF-VERSION
AppCopyright=2000-2003 Jim Crafton
AppName=Visual Component Framework VCF-LONG-VERSION
AppVerName=Visual Component Framework VCF-LONG-VERSION
LicenseFile=..\..\license.txt
DefaultDirName={pf}\VCF-VCF-VERSION
DefaultGroupName=Visual Component Framework VCF-VERSION
AppPublisher=VCF
AppPublisherURL=http://vcf.sf.net
AppSupportURL=http://vcf.sf.net
AppUpdatesURL=http://vcf.sf.net
AppVersion=VCF-VERSION
UninstallDisplayIcon={app}\vcf.ico
UninstallDisplayName=Visual Component Framework VCF-VERSION

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
Name: {group}\Online Documentation; Filename: http://vcf.sourceforge.net/docs/ref_manual/; IconFilename: {app}\vcf.ico; IconIndex: 0
Name: {group}\VCF Documentation; Filename: {app}\docs\VCFDocs.0.6.4.chm; Components: Help_Files
Name: {group}\VCF Source Documentation; Filename: {app}\docs\VCFSrcDocs.0.6.4.chm; Components: Help_Files
Name: {group}\VCF Website; Filename: http://vcf.sf.net; IconFilename: {app}\vcf.ico; IconIndex: 0

[Tasks]
Name: msdnintegrate; Description: Integrate VCF Documentation with Visual C++ 6 MSDN; Components: Help_Files
Name: addvc6dirs; Description: Add VCF Include and Library path to Microsoft's Visual C++
Name: addenvpaths; Description: Add VCF environment variables, and update your Path
Name: installwizards; Description: Install Visual C++ 6 Project Wizards

[Run]
Filename: {app}\MSDNIntegrator.exe; Parameters: "-guid ""{{858cf701-5e04-48ba-968e-46569c787d5f}"" -chi ""{app}\docs\VCFDocs.0.6.4.chi"" -chm ""{app}\docs\VCFDocs.0.6.4.chm"" -add -title ""VCF Documentation"""; StatusMsg: Registering VCF Documentation with MSDN...; Tasks: msdnintegrate; Components: Help_Files
Filename: {app}\MSDNIntegrator.exe; Parameters: "-guid ""{{cf54ec6b-a508-4b05-b04d-794bf0cb2757}"" -chi ""{app}\docs\VCFSrcDocs.0.6.4.chi"" -chm ""{app}\docs\VCFSrcDocs.0.6.4.chm"" -add -title ""VCF Source Documentation"""; StatusMsg: Registering VCF Documentation with MSDN...; Tasks: msdnintegrate; Components: Help_Files

Filename: {app}\RegEnVar.exe; Parameters: "--add-user-var VCF_BIN ""{app}\bin"""; Components: Src Binaries; Tasks: addenvpaths
Filename: {app}\RegEnVar.exe; Parameters: "--add-user-var VCF_LIB ""{app}\lib"""; Components: Src Binaries; Tasks: addenvpaths
Filename: {app}\RegEnVar.exe; Parameters: "--add-user-var VCF_INCLUDE ""{app}\include"""; Components: Src Binaries; Tasks: addenvpaths
Filename: {app}\RegEnVar.exe; Parameters: --add-to-user-path %VCF_BIN%; Components: Src Binaries; Tasks: addenvpaths

[UninstallRun]
Filename: {app}\MSDNIntegrator.exe; Parameters: "-guid ""{{858cf701-5e04-48ba-968e-46569c787d5f}"" -chi ""{app}\docs\VCFDocs.0.6.4.chi"" -chm ""{app}\docs\VCFDocs.0.6.4.chm"" -remove -title ""VCF Documentation"""; StatusMsg: Removing VCF Documentation with MSDN...; Components: Help_Files; Tasks: msdnintegrate
Filename: {app}\MSDNIntegrator.exe; Parameters: "-guid ""{{cf54ec6b-a508-4b05-b04d-794bf0cb2757}"" -chi ""{app}\docs\VCFSrcDocs.0.6.4.chi"" -chm ""{app}\docs\VCFSrcDocs.0.6.4.chm"" -remove -title ""VCF Source Documentation"""; StatusMsg: Removing VCF Documentation with MSDN...; Components: Help_Files; Tasks: msdnintegrate
Filename: {app}\RegEnVar.exe; Parameters: --del-from-user-path %VCF_BIN%; Tasks: addenvpaths; Components: Src Binaries
Filename: {app}\RegEnVar.exe; Parameters: --del-user-var VCF_BIN; Tasks: addenvpaths; Components: Src Binaries
Filename: {app}\RegEnVar.exe; Parameters: --del-user-var VCF_LIB; Tasks: addenvpaths; Components: Src Binaries
Filename: {app}\RegEnVar.exe; Parameters: --del-user-var VCF_INCLUDE; Tasks: addenvpaths; Components: Src Binaries

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
    if ( (Pos( 'installwizards', tasks ) > 0) and (Pos( 'vc_wizards', components ) > 0) ) then begin

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
