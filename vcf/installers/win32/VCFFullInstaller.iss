[_ISTool]
EnableISX=false

[Components]
Name: VC_Addins; Description: VCF Visual Studio Addins; Types: full custom
Name: Help_Files; Description: VCF Help files; Types: full custom compact
Name: Binaries; Description: Precompiled VCF Exe's, DLL's, and .Libs; Types: full custom compact
Name: VC_Wizards; Description: MS Visual C++ Appwizards; Types: full custom
Name: SSH; Description: Secure SHell binaries; Types: full custom
Name: CVS; Description: CVS version control executable; Types: full custom
Name: Src; Description: VCF include files and source code; Types: full custom compact
Name: Tutorials; Description: VCF Tutorials and test projects; Types: full custom

[Dirs]
Name: {app}\BlackBox; Components: Src
Name: {app}\AppServer; Components: Src
Name: {app}\build; Components: Src
Name: {app}\ClassServer; Components: Src
Name: {app}\ImageFormats; Components: Src
Name: {app}\docs
Name: {app}\Components; Components: Tutorials
Name: {app}\bin; Components: Binaries
Name: {app}\lib
Name: {app}\VC6-Addins; Components: VC_Addins
Name: {app}\src
Name: {app}\include

[Files]
Source: ..\..\BlackBox\include\ImageHlp.h; DestDir: {app}\BlackBox\include; Components: Src
Source: ..\..\BlackBox\include\TlHelp32.h; DestDir: {app}\BlackBox\include; Components: Src
Source: ..\..\BlackBox\lib\dbghelp.dll; DestDir: {app}\BlackBox\lib; Components: Src
Source: ..\..\BlackBox\lib\DbgHelp.Lib; DestDir: {app}\BlackBox\lib; Components: Src
Source: ..\..\BlackBox\lib\psapi.dll; DestDir: {app}\BlackBox\lib; Components: Src
Source: ..\..\BlackBox\lib\Psapi.Lib; DestDir: {app}\BlackBox\lib; Components: Src
Source: ..\..\BlackBox\AllocAndFillProcessModuleList.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BlackBox.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BlackBox.dll; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BlackBox.dsp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BlackBox.dsw; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BlackBox.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BlackBox.rc; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BlackBox.vcproj; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BlackBoxUI.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BlackBoxUI.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BSUFunctions.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\BugslayerUtil.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\CrashHandler.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\CrashHandler.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\CriticalSection.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\CRTDBG_Internals.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\DiagAssert.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\DiagAssert.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\GetLoadedModules.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\HookImportedFunctionByName.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\HookOrdinalExport.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\Internal.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\IsNT.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\MemDumperValidator.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\MemDumperValidator.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\MemStress.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\MemStress.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\MemStressConstants.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\MSJDBG.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\NT4ProcessInfo.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\PSAPI.H; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\ReadMe.txt; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\resource.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\StdAfx.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\StdAfx.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\SymbolEngine.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\tarBlackBox; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\TLHELPProcessInfo.cpp; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\WarningsOff.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\BlackBox\WarningsOn.h; DestDir: {app}\BlackBox\; Components: Src
Source: ..\..\AppServer\AppServer.cpp; DestDir: {app}\AppServer\; Components: Src
Source: ..\..\AppServer\AppServer.dsp; DestDir: {app}\AppServer\; Components: Src
Source: ..\..\AppServer\AppServer.vcproj; DestDir: {app}\AppServer\; Components: Src
Source: ..\..\build\resources\win32\ApplicationKit.rc; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\checkBox.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\ComboBox.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\commandButton.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\components.rc; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\defaultComponent.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\groupPanel.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\inform.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\label.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\listBox.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\menu.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\panel.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\popup.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\question.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\radioButton.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\resource.h; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\richTextControl.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\stop.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\textControl.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\vcf.ico; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\resources\win32\warning.bmp; DestDir: {app}\build\resources\win32; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\bitmap1.bmp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\bitmap2.bmp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\bitmap3.bmp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\bitmap4.bmp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\bmp00001.bmp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\bmp00002.bmp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\bmp00003.bmp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\COMToVCFClassWizard.rc2; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\TBarLrge.bmp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\res\TBarMedm.bmp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\Commands.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\Commands.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\Commands.rgs; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.def; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.dsp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.dsw; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMTOVCFCLASSWIZARD.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.idl; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.rc; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizardAddin.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizardAddin.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\COMToVCFClassWizardAddin.rgs; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\ConversionOptionsDlg.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\ConversionOptionsDlg.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\ConvertActiveXCtrlDlg.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\convertactivexctrldlg.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\ConvertTypeDlg.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\ConvertTypeDlg.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\MSRDC.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\MSRDC.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\MSRDCInterfaces.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\resource.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\shadow.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\shadow.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\SourceFormattingOptionsPage.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\SourceFormattingOptionsPage.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\StdAfx.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\StdAfx.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\Test.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\Test.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TreeItem.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TreeItem.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypeConversionOptionsPage.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypeConversionOptionsPage.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypeLibContents.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypeLibContents.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypelibDump.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypeLibDump.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypeLibraryConverterDlg.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypeLibraryConverterDlg.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypeLibTreeView.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\TypeLibTreeView.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\util.cpp; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\util.h; DestDir: {app}\build\vc60\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\res\bitmap1.bmp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\res\bitmap2.bmp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\res\bitmap3.bmp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\res\bitmap4.bmp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\res\splash1.bmp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\res\VCFAppWiz.ico; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\res\vcfwizard.ico; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\About.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\About.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\app.rc; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\confirm.inf; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\main.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\MainWindow.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\MainWindow.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\newproj.inf; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\splash.bmp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\SplashScreen.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\SplashScreen.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\test.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\UndoApp.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\UndoAppAbout.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\UndoAppAbout.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\UndoAppApplication.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\template\UndoAppApplication.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Chooser.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Chooser.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Debug.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Debug.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\FileExtensionPropDlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\FileExtensionPropDlg.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\FileExtsDlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\FileExtsDlg.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Page1Dlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Page1Dlg.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Page2Dlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Page2Dlg.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Page3Dlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Page3Dlg.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Page4Dlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Page4Dlg.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Resource.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\StdAfx.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\StdAfx.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\vcfwizard.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\vcfwizard.dsp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\vcfwizard.dsw; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\vcfwizard.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\vcfwizard.rc; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\vcfwizardAw.cpp; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFAppWiz\vcfwizardAw.h; DestDir: {app}\build\vc60\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\res\icon1.ico; DestDir: {app}\build\vc60\add-ins\VCFBuilder\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\res\TBarLrge.bmp; DestDir: {app}\build\vc60\add-ins\VCFBuilder\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\res\TBarMedm.bmp; DestDir: {app}\build\vc60\add-ins\VCFBuilder\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\res\VCFBuilder.rc2; DestDir: {app}\build\vc60\add-ins\VCFBuilder\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\Commands.cpp; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\Commands.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\DevStudioMainWnd.cpp; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\DevStudioMainWnd.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\DSAddIn.cpp; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\DSAddIn.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\resource.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\StdAfx.cpp; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\StdAfx.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\SubClassWnd.cpp; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\SubClassWnd.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilder.cpp; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilder.dsp; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilder.dsw; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilder.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilder.odl; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilder.rc; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilderHostView.cpp; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilderHostView.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilderMDIChild.cpp; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilderMDIChild.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFBuilder\VCFBuilderTypes.h; DestDir: {app}\build\vc60\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\res\bitmap1.bmp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\res\tmp.bmp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\res\VCFConsoleWiz.ico; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Template\confirm.inf; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Template\consoleMain.cpp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Template\newproj.inf; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Chooser.cpp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Chooser.h; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Debug.cpp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Debug.h; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Page1Dlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Page1Dlg.h; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Resource.h; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\StdAfx.cpp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\StdAfx.h; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\VCFConsoleWiz.cpp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\VCFConsoleWiz.dsp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\VCFConsoleWiz.dsw; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\VCFConsoleWiz.h; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\VCFConsoleWiz.rc; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\VCFConsoleWizAw.cpp; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\VCFConsoleWizAw.h; DestDir: {app}\build\vc60\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\res\bitmap1.bmp; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\res\VCFLibraryAppWizard.ico; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Template\confirm.inf; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Template\LibMain.cpp; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Template\newproj.inf; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Chooser.cpp; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Chooser.h; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\cstm1dlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\cstm1dlg.h; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Debug.cpp; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Debug.h; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\resource.h; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\StdAfx.cpp; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\StdAfx.h; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.cpp; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.dsp; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.dsw; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.h; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.rc; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizardAw.cpp; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizardAw.h; DestDir: {app}\build\vc60\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\res\TBarLrge.bmp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\res\TBarMedm.bmp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\res\VCFNewClassWiz.rc2; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\Commands.cpp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\Commands.h; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\Commands.rgs; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\NewClassDlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\NewClassDlg.h; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\PostHeaderDlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\PostHeaderDlg.h; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\PreHeaderDlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\PreHeaderDlg.h; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\PropertyInfoDlg.cpp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\PropertyInfoDlg.h; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\resource.h; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\StdAfx.cpp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\StdAfx.h; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNewClassWiz.cpp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNewClassWiz.def; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNewClassWiz.dsp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNewClassWiz.dsw; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNEWCLASSWIZ.h; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNewClassWiz.idl; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNewClassWiz.rc; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNewClassWizAddin.cpp; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNewClassWizAddin.h; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\VCFNewClassWizAddin.rgs; DestDir: {app}\build\vc60\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\res\bitmap1.bmp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\res\VPLAppWiz.ico; DestDir: {app}\build\vc60\add-ins\VPLAppWiz\res; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Template\confirm.inf; DestDir: {app}\build\vc60\add-ins\VPLAppWiz\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Template\newproj.inf; DestDir: {app}\build\vc60\add-ins\VPLAppWiz\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Template\root.cpp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Template\root.h; DestDir: {app}\build\vc60\add-ins\VPLAppWiz\Template; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Chooser.cpp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Chooser.h; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Debug.cpp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Debug.h; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\devshl.cpp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\devshl.h; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Page1Dlg.cpp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Page1Dlg.h; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Resource.h; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\StdAfx.cpp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\StdAfx.h; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\VPLAppWiz.cpp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\VPLAppWiz.dsp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\VPLAppWiz.dsw; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\VPLAppWiz.h; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\VPLAppWiz.rc; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\VPLAppWizAw.cpp; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\VPLAppWiz\VPLAppWizAw.h; DestDir: {app}\build\vc60\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc60\add-ins\all.dsp; DestDir: {app}\build\vc60\add-ins; Components: Src
Source: ..\..\build\vc60\add-ins\all.dsw; DestDir: {app}\build\vc60\add-ins; Components: Src
Source: ..\..\build\vc60\ApplicationKit\ApplicationKit.dep; DestDir: {app}\build\vc60\ApplicationKit; Components: Src
Source: ..\..\build\vc60\ApplicationKit\ApplicationKit.dsp; DestDir: {app}\build\vc60\ApplicationKit; Components: Src
Source: ..\..\build\vc60\ApplicationKit\ApplicationKit.mak; DestDir: {app}\build\vc60\ApplicationKit; Components: Src
Source: ..\..\build\vc60\ApplicationKit\ApplicationKitDLL.dep; DestDir: {app}\build\vc60\ApplicationKit; Components: Src
Source: ..\..\build\vc60\ApplicationKit\ApplicationKitDLL.dsp; DestDir: {app}\build\vc60\ApplicationKit; Components: Src
Source: ..\..\build\vc60\ApplicationKit\ApplicationKitDLL.mak; DestDir: {app}\build\vc60\ApplicationKit; Components: Src
Source: ..\..\build\vc60\FoundationKit\FoundationKit.dep; DestDir: {app}\build\vc60\FoundationKit; Components: Src
Source: ..\..\build\vc60\FoundationKit\FoundationKit.dsp; DestDir: {app}\build\vc60\FoundationKit; Components: Src
Source: ..\..\build\vc60\FoundationKit\FoundationKit.mak; DestDir: {app}\build\vc60\FoundationKit; Components: Src
Source: ..\..\build\vc60\FoundationKit\FoundationKitDLL.dep; DestDir: {app}\build\vc60\FoundationKit; Components: Src
Source: ..\..\build\vc60\FoundationKit\FoundationKitDLL.dsp; DestDir: {app}\build\vc60\FoundationKit; Components: Src
Source: ..\..\build\vc60\FoundationKit\FoundationKitDLL.mak; DestDir: {app}\build\vc60\FoundationKit; Components: Src
Source: ..\..\build\vc60\FoundationKit\RegExx.dsp; DestDir: {app}\build\vc60\FoundationKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\GraphicsKit.dep; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\GraphicsKit.dsp; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\GraphicsKit.mak; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\GraphicsKitDLL.dep; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\GraphicsKitDLL.dsp; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\GraphicsKitDLL.mak; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\ImageFormats.dsp; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\libart.dep; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\libart.dsp; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\GraphicsKit\libart.mak; DestDir: {app}\build\vc60\GraphicsKit; Components: Src
Source: ..\..\build\vc60\NetworkKit\NetworkKit.dsp; DestDir: {app}\build\vc60\NetworkKit; Components: Src
Source: ..\..\build\vc60\NetworkKit\NetworkKit.mak; DestDir: {app}\build\vc60\NetworkKit; Components: Src
Source: ..\..\build\vc60\NetworkKit\NetworkKitDLL.dsp; DestDir: {app}\build\vc60\NetworkKit; Components: Src
Source: ..\..\build\vc60\NetworkKit\NetworkKitDLL.mak; DestDir: {app}\build\vc60\NetworkKit; Components: Src
Source: ..\..\build\vc60\RemoteObjectKit\RemoteObjectKit.dsp; DestDir: {app}\build\vc60\RemoteObjectKit; Components: Src
Source: ..\..\build\vc60\RemoteObjectKit\RemoteObjectKit.mak; DestDir: {app}\build\vc60\RemoteObjectKit; Components: Src
Source: ..\..\build\vc60\RemoteObjectKit\RemoteObjectKitStatic.dsp; DestDir: {app}\build\vc60\RemoteObjectKit; Components: Src
Source: ..\..\build\vc60\RemoteObjectKit\RemoteObjectKitStatic.mak; DestDir: {app}\build\vc60\RemoteObjectKit; Components: Src
Source: ..\..\build\vc60\Tests\AllTests\AllTests.dsp; DestDir: {app}\build\vc60\Tests\AllTests; Components: Src
Source: ..\..\build\vc60\Tests\Tests.dsw; DestDir: {app}\build\vc60\Tests; Components: Src
Source: ..\..\build\vc60\Win32HTMLBrowser\Win32HTMLBrowser.dsp; DestDir: {app}\build\vc60\Win32HTMLBrowser; Components: Src
Source: ..\..\build\vc60\Win32HTMLBrowser\Win32HTMLBrowser_StaticLib.dsp; DestDir: {app}\build\vc60\Win32HTMLBrowser; Components: Src
Source: ..\..\build\vc60\makeAll; DestDir: {app}\build\vc60; Components: Src
Source: ..\..\build\vc60\vcfAll.dsp; DestDir: {app}\build\vc60; Components: Src
Source: ..\..\build\vc60\vcfAll.dsw; DestDir: {app}\build\vc60; Components: Src
Source: ..\..\build\vc60\vcfAll.mak; DestDir: {app}\build\vc60; Components: Src
Source: ..\..\build\vc60\vcfAllProjs.dsw; DestDir: {app}\build\vc60; Components: Src
Source: ..\..\build\vc60\vcfAllStaticLibs.dsp; DestDir: {app}\build\vc60; Components: Src
Source: ..\..\build\vc60\vcfAllStaticLibs.mak; DestDir: {app}\build\vc60; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\bitmap1.bmp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\bitmap2.bmp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\bitmap3.bmp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\bitmap4.bmp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\bmp00001.bmp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\bmp00002.bmp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\bmp00003.bmp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\COMToVCFClassWizard.rc2; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\TBarLrge.bmp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\res\TBarMedm.bmp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\Commands.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\Commands.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\Commands.rgs; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.def; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.dsp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.dsw; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMTOVCFCLASSWIZARD.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.idl; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.rc; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizard.vcproj; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizardAddin.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizardAddin.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\COMToVCFClassWizardAddin.rgs; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\ConversionOptionsDlg.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\ConversionOptionsDlg.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\ConvertActiveXCtrlDlg.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\convertactivexctrldlg.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\ConvertTypeDlg.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\ConvertTypeDlg.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\MSRDC.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\MSRDC.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\MSRDCInterfaces.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\resource.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\shadow.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\shadow.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\SourceFormattingOptionsPage.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\SourceFormattingOptionsPage.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\StdAfx.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\StdAfx.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\Test.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\Test.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TreeItem.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TreeItem.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypeConversionOptionsPage.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypeConversionOptionsPage.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypeLibContents.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypeLibContents.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypelibDump.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypeLibDump.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypeLibraryConverterDlg.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypeLibraryConverterDlg.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypeLibTreeView.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\TypeLibTreeView.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\util.cpp; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\COMToVCFClassWizard\util.h; DestDir: {app}\build\vc70\add-ins\COMToVCFClassWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\res\bitmap1.bmp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\res\bitmap2.bmp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\res\bitmap3.bmp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\res\bitmap4.bmp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\res\splash1.bmp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\res\VCFAppWiz.ico; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\res\vcfwizard.ico; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\About.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\About.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\app.rc; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\confirm.inf; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\main.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\MainWindow.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\MainWindow.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\newproj.inf; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\splash.bmp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\SplashScreen.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\SplashScreen.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\test.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\UndoApp.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\UndoAppAbout.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\UndoAppAbout.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\UndoAppApplication.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\template\UndoAppApplication.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz\template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Chooser.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Chooser.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Debug.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Debug.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\FileExtensionPropDlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\FileExtensionPropDlg.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\FileExtsDlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\FileExtsDlg.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Page1Dlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Page1Dlg.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Page2Dlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Page2Dlg.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Page3Dlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Page3Dlg.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Page4Dlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Page4Dlg.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\Resource.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\StdAfx.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\StdAfx.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\vcfwizard.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\vcfwizard.dsp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\vcfwizard.dsw; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\vcfwizard.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\vcfwizard.rc; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\vcfwizard.vcproj; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\vcfwizardAw.cpp; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFAppWiz\vcfwizardAw.h; DestDir: {app}\build\vc70\add-ins\VCFAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\res\icon1.ico; DestDir: {app}\build\vc70\add-ins\VCFBuilder\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\res\TBarLrge.bmp; DestDir: {app}\build\vc70\add-ins\VCFBuilder\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\res\TBarMedm.bmp; DestDir: {app}\build\vc70\add-ins\VCFBuilder\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\res\VCFBuilder.rc2; DestDir: {app}\build\vc70\add-ins\VCFBuilder\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\Commands.cpp; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\Commands.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\DevStudioMainWnd.cpp; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\DevStudioMainWnd.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\DSAddIn.cpp; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\DSAddIn.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\resource.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\StdAfx.cpp; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\StdAfx.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\SubClassWnd.cpp; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\SubClassWnd.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilder.cpp; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilder.dsp; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilder.dsw; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilder.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilder.odl; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilder.rc; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilder.vcproj; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilderHostView.cpp; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilderHostView.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilderMDIChild.cpp; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilderMDIChild.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFBuilder\VCFBuilderTypes.h; DestDir: {app}\build\vc70\add-ins\VCFBuilder; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\res\bitmap1.bmp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\res\tmp.bmp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\res\VCFConsoleWiz.ico; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Template\confirm.inf; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Template\consoleMain.cpp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Template\newproj.inf; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Chooser.cpp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Chooser.h; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Debug.cpp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Debug.h; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Page1Dlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Page1Dlg.h; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\Resource.h; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\StdAfx.cpp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\StdAfx.h; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\VCFConsoleWiz.cpp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\VCFConsoleWiz.dsp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\VCFConsoleWiz.dsw; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\VCFConsoleWiz.h; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\VCFConsoleWiz.rc; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\VCFConsoleWiz.vcproj; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\VCFConsoleWizAw.cpp; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFConsoleWiz\VCFConsoleWizAw.h; DestDir: {app}\build\vc70\add-ins\VCFConsoleWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\res\bitmap1.bmp; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\res\VCFLibraryAppWizard.ico; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\Template\confirm.inf; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\Template\LibMain.cpp; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\Template\newproj.inf; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\Chooser.cpp; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\Chooser.h; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\cstm1dlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\cstm1dlg.h; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\Debug.cpp; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\Debug.h; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\resource.h; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\StdAfx.cpp; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\StdAfx.h; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.cpp; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.dsp; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.dsw; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.h; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.rc; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizard.vcproj; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizardAw.cpp; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFLibraryAppWizard\VCFLibraryAppWizardAw.h; DestDir: {app}\build\vc70\add-ins\VCFLibraryAppWizard; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\res\TBarLrge.bmp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\res\TBarMedm.bmp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\res\VCFNewClassWiz.rc2; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\Commands.cpp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\Commands.h; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\Commands.rgs; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\NewClassDlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\NewClassDlg.h; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\PostHeaderDlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\PostHeaderDlg.h; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\PreHeaderDlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\PreHeaderDlg.h; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\PropertyInfoDlg.cpp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\PropertyInfoDlg.h; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\resource.h; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\StdAfx.cpp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\StdAfx.h; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWiz.cpp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWiz.def; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWiz.dsp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWiz.dsw; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNEWCLASSWIZ.h; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWiz.idl; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWiz.rc; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWiz.vcproj; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWizAddin.cpp; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWizAddin.h; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VCFNewClassWiz\VCFNewClassWizAddin.rgs; DestDir: {app}\build\vc70\add-ins\VCFNewClassWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\res\bitmap1.bmp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\res\VPLAppWiz.ico; DestDir: {app}\build\vc70\add-ins\VPLAppWiz\res; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Template\confirm.inf; DestDir: {app}\build\vc70\add-ins\VPLAppWiz\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Template\newproj.inf; DestDir: {app}\build\vc70\add-ins\VPLAppWiz\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Template\root.cpp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Template\root.h; DestDir: {app}\build\vc70\add-ins\VPLAppWiz\Template; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Chooser.cpp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Chooser.h; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Debug.cpp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Debug.h; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\devshl.cpp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\devshl.h; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Page1Dlg.cpp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Page1Dlg.h; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\Resource.h; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\StdAfx.cpp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\StdAfx.h; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\VPLAppWiz.cpp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\VPLAppWiz.dsp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\VPLAppWiz.dsw; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\VPLAppWiz.h; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\VPLAppWiz.rc; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\VPLAppWiz.vcproj; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\VPLAppWizAw.cpp; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\VPLAppWiz\VPLAppWizAw.h; DestDir: {app}\build\vc70\add-ins\VPLAppWiz; Components: Src
Source: ..\..\build\vc70\add-ins\all.dsp; DestDir: {app}\build\vc70\add-ins; Components: Src
Source: ..\..\build\vc70\add-ins\all.dsw; DestDir: {app}\build\vc70\add-ins; Components: Src
Source: ..\..\build\vc70\ApplicationKit\ApplicationKit.dep; DestDir: {app}\build\vc70\ApplicationKit; Components: Src
Source: ..\..\build\vc70\ApplicationKit\ApplicationKit.dsp; DestDir: {app}\build\vc70\ApplicationKit; Components: Src
Source: ..\..\build\vc70\ApplicationKit\ApplicationKit.vcproj; DestDir: {app}\build\vc70\ApplicationKit; Components: Src
Source: ..\..\build\vc70\ApplicationKit\ApplicationKitDLL.dep; DestDir: {app}\build\vc70\ApplicationKit; Components: Src
Source: ..\..\build\vc70\ApplicationKit\ApplicationKitDLL.dsp; DestDir: {app}\build\vc70\ApplicationKit; Components: Src
Source: ..\..\build\vc70\ApplicationKit\ApplicationKitDLL.vcproj; DestDir: {app}\build\vc70\ApplicationKit; Components: Src
Source: ..\..\build\vc70\FoundationKit\FoundationKit.dep; DestDir: {app}\build\vc70\FoundationKit; Components: Src
Source: ..\..\build\vc70\FoundationKit\FoundationKit.dsp; DestDir: {app}\build\vc70\FoundationKit; Components: Src
Source: ..\..\build\vc70\FoundationKit\FoundationKit.vcproj; DestDir: {app}\build\vc70\FoundationKit; Components: Src
Source: ..\..\build\vc70\FoundationKit\FoundationKitDLL.dep; DestDir: {app}\build\vc70\FoundationKit; Components: Src
Source: ..\..\build\vc70\FoundationKit\FoundationKitDLL.dsp; DestDir: {app}\build\vc70\FoundationKit; Components: Src
Source: ..\..\build\vc70\FoundationKit\FoundationKitDLL.vcproj; DestDir: {app}\build\vc70\FoundationKit; Components: Src
Source: ..\..\build\vc70\FoundationKit\RegExx.dsp; DestDir: {app}\build\vc70\FoundationKit; Components: Src
Source: ..\..\build\vc70\FoundationKit\RegExx.vcproj; DestDir: {app}\build\vc70\FoundationKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\GraphicsKit.dep; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\GraphicsKit.dsp; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\GraphicsKit.vcproj; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\GraphicsKitDLL.dep; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\GraphicsKitDLL.dsp; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\GraphicsKitDLL.vcproj; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\ImageFormats.dsp; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\ImageFormats.vcproj; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\libart.dep; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\libart.dsp; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\GraphicsKit\libart.vcproj; DestDir: {app}\build\vc70\GraphicsKit; Components: Src
Source: ..\..\build\vc70\NetworkKit\NetworkKit.dsp; DestDir: {app}\build\vc70\NetworkKit; Components: Src
Source: ..\..\build\vc70\NetworkKit\NetworkKit.vcproj; DestDir: {app}\build\vc70\NetworkKit; Components: Src
Source: ..\..\build\vc70\NetworkKit\NetworkKitDLL.dsp; DestDir: {app}\build\vc70\NetworkKit; Components: Src
Source: ..\..\build\vc70\NetworkKit\NetworkKitDLL.vcproj; DestDir: {app}\build\vc70\NetworkKit; Components: Src
Source: ..\..\build\vc70\RemoteObjectKit\RemoteObjectKit.dsp; DestDir: {app}\build\vc70\RemoteObjectKit; Components: Src
Source: ..\..\build\vc70\RemoteObjectKit\RemoteObjectKit.vcproj; DestDir: {app}\build\vc70\RemoteObjectKit; Components: Src
Source: ..\..\build\vc70\RemoteObjectKit\RemoteObjectKitStatic.dsp; DestDir: {app}\build\vc70\RemoteObjectKit; Components: Src
Source: ..\..\build\vc70\RemoteObjectKit\RemoteObjectKitStatic.vcproj; DestDir: {app}\build\vc70\RemoteObjectKit; Components: Src
Source: ..\..\build\vc70\Tests\AllTests\AllTests.dsp; DestDir: {app}\build\vc70\Tests\AllTests; Components: Src
Source: ..\..\build\vc70\Tests\Tests.dsw; DestDir: {app}\build\vc70\Tests; Components: Src
Source: ..\..\build\vc70\Win32HTMLBrowser\Win32HTMLBrowser.dsp; DestDir: {app}\build\vc70\Win32HTMLBrowser; Components: Src
Source: ..\..\build\vc70\Win32HTMLBrowser\Win32HTMLBrowser.vcproj; DestDir: {app}\build\vc70\Win32HTMLBrowser; Components: Src
Source: ..\..\build\vc70\Win32HTMLBrowser\Win32HTMLBrowser_StaticLib.dsp; DestDir: {app}\build\vc70\Win32HTMLBrowser; Components: Src
Source: ..\..\build\vc70\Win32HTMLBrowser\Win32HTMLBrowser_StaticLib.vcproj; DestDir: {app}\build\vc70\Win32HTMLBrowser; Components: Src
Source: ..\..\build\vc70\makeAll; DestDir: {app}\build\vc70; Components: Src
Source: ..\..\build\vc70\vcfAll.dsp; DestDir: {app}\build\vc70; Components: Src
Source: ..\..\build\vc70\vcfAll.dsw; DestDir: {app}\build\vc70; Components: Src
Source: ..\..\build\vc70\vcfAll.mak; DestDir: {app}\build\vc70; Components: Src
Source: ..\..\build\vc70\vcfAllProjs.dsw; DestDir: {app}\build\vc70; Components: Src
Source: ..\..\build\vc70\vcfAllProjs.sln; DestDir: {app}\build\vc70; Components: Src
Source: ..\..\build\vc70\vcfAllStaticLibs.dsp; DestDir: {app}\build\vc70; Components: Src
Source: ..\..\build\vc70\vcfAllStaticLibs.mak; DestDir: {app}\build\vc70; Components: Src
Source: ..\..\build\xmake\ApplicationKit\makefile.xml; DestDir: {app}\build\xmake\ApplicationKit; Components: Src
Source: ..\..\build\xmake\FoundationKit\makefile.xml; DestDir: {app}\build\xmake\FoundationKit; Components: Src
Source: ..\..\build\xmake\FoundationKit\regexx.xml; DestDir: {app}\build\xmake\FoundationKit; Components: Src
Source: ..\..\build\xmake\GraphicsKit\makefile.xml; DestDir: {app}\build\xmake\GraphicsKit; Components: Src
Source: ..\..\ClassServer\ClassServer.cpp; DestDir: {app}\ClassServer\; Components: Src
Source: ..\..\ClassServer\ClassServer.dsp; DestDir: {app}\ClassServer\; Components: Src
Source: ..\..\ClassServer\ClassServer.vcproj; DestDir: {app}\ClassServer\; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\BitmapAccess.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\Conversion.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\Conversion16_555.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\Conversion16_565.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\Conversion24.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\Conversion32.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\Conversion8.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\FreeImage.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\FreeImageIO.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\GetType.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\LoadFunctions.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\Makefile; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\NNQuantizer.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\Plugin.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginBMP.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginICO.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginIFF.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginJPEG.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginKOALA.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginMNG.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginPCD.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginPCX.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginPNG.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginPNM.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginPSD.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginRAS.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginTARGA.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginTIFF.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\PluginWBMP.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage\WuQuantizer.cpp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImageLib\FreeImageLib.dsp; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImageLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImageLib\FreeImageLib.vcproj; DestDir: {app}\ImageFormats\FreeImage\Source\FreeImageLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\ansi2knr.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\cderror.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\cdjpeg.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\cdjpeg.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\change.log; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\cjpeg.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\ckconfig.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\djpeg.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\example.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcapimin.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcapistd.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jccoefct.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jccolor.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcdctmgr.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jchuff.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jchuff.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcinit.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcmainct.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcmarker.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcmaster.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcomapi.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jconfig.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcparam.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcphuff.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcprepct.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jcsample.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jctrans.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdapimin.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdapistd.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdatadst.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdatasrc.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdcoefct.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdcolor.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdct.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jddctmgr.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdhuff.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdhuff.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdinput.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdmainct.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdmarker.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdmaster.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdmerge.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdphuff.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdpostct.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdsample.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jdtrans.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jerror.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jerror.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jfdctflt.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jfdctfst.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jfdctint.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jidctflt.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jidctfst.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jidctint.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jidctred.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jinclude.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jmemansi.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jmemdos.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jmemmac.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jmemmgr.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jmemname.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jmemnobs.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jmemsys.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jmorecfg.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jpegint.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jpeglib.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jpegtran.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jquant1.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jquant2.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jutils.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\jversion.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\LibJPEG.dsp; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\LibJPEG.vcproj; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\rdbmp.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\rdcolmap.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\rdgif.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\rdjpgcom.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\rdppm.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\rdrle.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\rdswitch.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\rdtarga.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\transupp.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\transupp.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\wrbmp.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\wrgif.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\wrjpgcom.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\wrppm.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\wrrle.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibJPEG\wrtarga.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibJPEG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\autogen.sh; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\Changes; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\LibMNG.dsp; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\LibMNG.vcproj; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_callback_xs.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_chunks.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_chunk_io.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_chunk_io.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_chunk_prc.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_chunk_prc.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_chunk_xs.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_cms.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_cms.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_conf.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_data.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_display.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_display.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_dither.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_dither.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_error.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_error.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_filter.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_filter.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_hlapi.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_jpeg.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_jpeg.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_memory.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_objects.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_object_prc.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_object_prc.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_pixels.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_pixels.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_prop_xs.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_read.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_read.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_trace.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_trace.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_types.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_write.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_write.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_zlib.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\libmng_zlib.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\LICENSE; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\README; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\README.config; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\README.contrib; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\README.examples; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibMNG\README.packaging; DestDir: {app}\ImageFormats\FreeImage\Source\LibMNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\ANNOUNCE; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\CHANGES; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\configure; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\example.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\INSTALL; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\KNOWNBUG; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\LibPNG.dsp; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\libpng.txt; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\LibPNG.vcproj; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\LICENSE; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\png.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\png.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngasmrd.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngconf.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngerror.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pnggccrd.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngget.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngmem.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngpread.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngread.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngrio.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngrtran.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngrutil.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngset.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngtest.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngtrans.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngvcrd.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngwio.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngwrite.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngwtran.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\pngwutil.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\README; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\TODO; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibPNG\Y2KINFO; DestDir: {app}\ImageFormats\FreeImage\Source\LibPNG; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\fax3sm_winnt.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\libtiff.def; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\LibTIFF.dsp; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\LibTIFF.vcproj; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\Makefile.in; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\Makefile.lcc; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\t4.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tiff.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tiffcomp.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tiffconf.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tiffio.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tiffiop.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_acorn.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_apple.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_atari.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_aux.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_close.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_codec.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_compress.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_dir.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_dir.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_dirinfo.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_dirread.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_dirwrite.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_dumpmode.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_error.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_fax3.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_fax3.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_flush.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_getimage.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_jpeg.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_luv.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_lzw.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_msdos.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_next.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_open.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_packbits.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_pixarlog.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_predict.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_predict.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_print.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_read.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_strip.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_swab.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_thunder.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_tile.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_unix.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_version.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_vms.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_warning.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_win3.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_win32.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_write.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\tif_zip.c; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\LibTIFF\uvcode.h; DestDir: {app}\ImageFormats\FreeImage\Source\LibTIFF; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\adler32.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\compress.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\crc32.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\deflate.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\deflate.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\gzio.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\infblock.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\infblock.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\infcodes.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\infcodes.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\inffast.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\inffast.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\inffixed.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\inflate.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\inftrees.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\inftrees.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\infutil.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\infutil.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\maketree.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\minigzip.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\trees.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\trees.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\uncompr.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\zconf.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\ZLib.dsp; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\zlib.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\ZLib.vcproj; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\zutil.c; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\ZLib\zutil.h; DestDir: {app}\ImageFormats\FreeImage\Source\ZLib; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImage.h; DestDir: {app}\ImageFormats\FreeImage\Source; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImageIO.h; DestDir: {app}\ImageFormats\FreeImage\Source; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\FreeImageSelectLib.h; DestDir: {app}\ImageFormats\FreeImage\Source; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\Plugin.h; DestDir: {app}\ImageFormats\FreeImage\Source; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\Quantizers.h; DestDir: {app}\ImageFormats\FreeImage\Source; Components: Src
Source: ..\..\ImageFormats\FreeImage\Source\Utilities.h; DestDir: {app}\ImageFormats\FreeImage\Source; Components: Src
Source: ..\..\ImageFormats\FreeImage\KnownBugs.txt; DestDir: {app}\ImageFormats\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\license-fi.txt; DestDir: {app}\ImageFormats\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\license-gpl.txt; DestDir: {app}\ImageFormats\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Makefile; DestDir: {app}\ImageFormats\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Makefile.cfg; DestDir: {app}\ImageFormats\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Todo.txt; DestDir: {app}\ImageFormats\FreeImage; Components: Src
Source: ..\..\ImageFormats\FreeImage\Whatsnew.txt; DestDir: {app}\ImageFormats\FreeImage; Components: Src
Source: ..\..\ImageFormats\ImageFormats.cpp; DestDir: {app}\ImageFormats\; Components: Src
Source: ..\..\ImageFormats\ImageFormats.h; DestDir: {app}\ImageFormats\; Components: Src
Source: ..\..\ImageFormats\ImageFormatsSelectLib.h; DestDir: {app}\ImageFormats\; Components: Src
Source: ..\..\docs\images\addins_verify.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\drag_drop_op1.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\drag_drop_op2.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\hello_world1.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\new_vcf_project.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\new_vcf_project_finish.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\old_style_event_handling.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\shared_event_handlers.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\vcf diagrams2.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\vcf_drag_drop1.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\vcf_drag_drop1_thm.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\vcf_drag_drop2.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\vcf_drag_drop2_thm.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\vcf_event_handling.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\vcf_peers.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\images\vcf_peers_lg.png; DestDir: {app}\docs\images; Components: Help_Files
Source: ..\..\docs\accelerator_keys.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\applicationkit_exceptions.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\applicationkit_faq.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\applicationkit_library.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\applicationkit_peer_classes.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\applications.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\borders.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\bugs.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\building_the_microsoft_vc.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\building_the_vcf.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\colors.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\components.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\component_authoring.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\component_authoring_faq.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\component_editing.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\contributing_to_the_vcf_project.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\controls.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\controls_and_containers.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\control_activation.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\control_dims.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\core_libraries.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\documentation_standards.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\downloading.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\drag_and_drop.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\dynamic_libraries.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\events.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\event_loops.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\features.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\files.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\fills.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\forums.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\foundationkit_exceptions.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\foundationkit_faq.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\foundationkit_library.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\foundationKit_peer_classes.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\frames_dialogs_and_windows.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\frame_dialog.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\frame_dims.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\frame_toolbar.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\frame_window.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\general_faq.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\graphicskit_faq.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\graphicskit_library.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\graphicskit_peer_classes.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\graphics_contexts.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\graphics_exceptions.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\graphics_toolkit.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\images.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\image_loading.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\installing_the_vcf.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\introduction.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\introTop.jpg; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\introTop2.jpg; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\items.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\layout.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\left_sidebar.jpg; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\left_sidebar_strip.jpg; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\logo.jpg; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\mailing_lists.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\main.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\models.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\naming_standards.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\object__the_vcf_base_class.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\old_docs.tar; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\paths.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\printing.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\processes.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\property_editing.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\reference_counting.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\registering_as_a_user_at_sf.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\registering_components.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\required_tools.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\rtti.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\saving_and_loading_component_state.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\setting_up_cvs.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\simple_vcf_application.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\streams.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\strokes.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\system_toolkit.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\threads.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\top-background.jpg; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\transforms.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\ui_toolkit.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\understanding_the_vcf_src_tree.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\undoredo_and_commands.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf diagrams.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf diagrams.ppt; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf diagrams2.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\VCFDocFooter.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\VCFDocHeader.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf_2.css; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf_drag_drop1.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf_drag_drop1_thm.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf_drag_drop2.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf_drag_drop2_thm.png; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf_events_comparison.htm; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\vcf_tools.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\views.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\VisualStudio_files.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\working_with_cvs.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\xmake.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\docs\xml_parsing.html; DestDir: {app}\docs\; Components: Help_Files
Source: ..\..\tests\Components\Components.cpp; DestDir: {app}\Components\; Components: Tutorials
Source: ..\..\tests\Components\Components.dsp; DestDir: {app}\Components\; Components: Tutorials
Source: ..\..\tests\Components\components.html; DestDir: {app}\Components\; Components: Tutorials
Source: ..\..\tests\Components\Components.rc; DestDir: {app}\Components\; Components: Tutorials
Source: ..\..\tests\Components\Components.vcproj; DestDir: {app}\Components\; Components: Tutorials
Source: ..\..\tests\Components\icon1.bmp; DestDir: {app}\Components\; Components: Tutorials
Source: ..\..\tests\Components\OldVCFEnums.h; DestDir: {app}\Components\; Components: Tutorials
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
Source: ..\..\build\vc60\add-ins\COMToVCFClassWizard\vc6\Release\COMToVCFClassWizard_vc6.dll; DestDir: {app}\VC6-Addins; Components: VC_Addins; Flags: regserver
Source: ..\..\build\vc60\add-ins\VCFAppWiz\Release\vcfwizard.awx; DestDir: {app}\VC6-Addins; Components: VC_Wizards
Source: ..\..\build\vc60\add-ins\VCFConsoleWiz\Release\VCFConsoleWiz.awx; DestDir: {app}\VC6-Addins; Components: VC_Wizards
Source: ..\..\build\vc60\add-ins\VCFLibraryAppWizard\Release\VCFLibraryAppWizard.awx; DestDir: {app}\VC6-Addins; Components: VC_Wizards
Source: ..\..\build\vc60\add-ins\VCFNewClassWiz\Release\VCFNewClassWiz.dll; DestDir: {app}\VC6-Addins; Components: VC_Addins; Flags: regserver
Source: ..\..\build\vc60\add-ins\VPLAppWiz\Release\VPLAppWiz.awx; DestDir: {app}\VC6-Addins; Components: VC_Wizards
Source: ..\..\src\COM\COMDataObject.cpp; DestDir: {app}\src\COM
Source: ..\..\src\COM\COMDragSource.cpp; DestDir: {app}\src\COM
Source: ..\..\src\COM\COMDropTarget.cpp; DestDir: {app}\src\COM
Source: ..\..\src\COM\COMObject.cpp; DestDir: {app}\src\COM
Source: ..\..\src\COM\COMUtils.cpp; DestDir: {app}\src\COM
Source: ..\..\src\COM\DataObject.cpp; DestDir: {app}\src\COM
Source: ..\..\src\core\AbstractApplication.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractCommand.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractComponentEditor.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractContainer.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractListModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractPropertyEditor.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractScrollable.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractTableModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractTextModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractTreeModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AbstractView.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\AcceleratorKey.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Application.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ApplicationKit.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\BasicTableItemEditor.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CheckBoxControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Class.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ClassRegistry.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Clipboard.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ClipboardDataObject.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ComboBoxControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CommandButton.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CommandGroup.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CommonColor.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CommonFileBrowse.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CommonFileDialog.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CommonFileOpen.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CommonFileSave.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CommonFont.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CommonPrint.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Component.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ComponentEditorManager.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ComponentInfo.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Control.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ControlContainer.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Cursor.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CursorManager.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\CustomControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DataType.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultColumnItem.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultColumnModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultListItem.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultListModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultMenuItem.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultPropertyEditors.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultTableCellItem.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultTableModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultTabModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultTabPage.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultTextModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultTreeItem.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\DefaultTreeModel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Desktop.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Dialog.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\FoundationKit.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Frame.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\HeaderControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\HTMLBrowserControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ImageControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\InterfaceClass.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Label.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\LibraryApplication.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ListBoxControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ListViewControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Locales.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Menu.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\MenuBar.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\MenuItemShortcut.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\MessageDialog.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Model.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\MultilineTextControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Object.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ObjectWithEvents.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\OpenGLControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Panel.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Point.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\PopupMenu.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\PropertyEditorManager.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\PushButton.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\RadioButtonControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Rect.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ScrollbarManager.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Splitter.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\StatusBar.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\TabbedPages.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\TableControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\TextControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\TimerComponent.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ToggledButton.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Toolbar.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ToolbarButton.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ToolbarDock.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\ToolbarSeparator.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\TreeControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\TreeList.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\TreeListControl.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\UIApplication.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\UndoRedoStack.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\VCFMath.cpp; DestDir: {app}\src\core
Source: ..\..\src\core\Window.cpp; DestDir: {app}\src\core
Source: ..\..\src\DragDrop\DragSource.cpp; DestDir: {app}\src\DragDrop
Source: ..\..\src\DragDrop\DropTarget.cpp; DestDir: {app}\src\DragDrop
Source: ..\..\src\Events\ButtonEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ClipboardEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ColumnItemEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ColumnModelEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ControlEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\DragEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\DropEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\Event.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\EventHandler.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\FocusEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\HelpEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ImageEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ImageListEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ItemEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\KeyboardEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ListModelEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\MenuItemEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\MouseEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\PropertyChangeEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\TableModelEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\TabModelEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\TextEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ThreadEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\TimerEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ToolTipEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\TreeModelEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\UndoRedoEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\ValidationEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\WhatsThisHelpEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Events\WindowEvent.cpp; DestDir: {app}\src\Events
Source: ..\..\src\Exceptions\BasicException.cpp; DestDir: {app}\src\Exceptions
Source: ..\..\src\Graphics\AbstractImage.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\AlphaGamma.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\ArtStroke.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_affine.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_alphagamma.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_bpath.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_gray_svp.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_misc.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_pixbuf.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rect.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rect_svp.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rect_uta.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_render.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_render_gradient.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_render_svp.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rgb.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rgba.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rgb_affine.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rgb_affine_private.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rgb_bitmap_affine.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rgb_pixbuf_affine.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rgb_rgba_affine.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_rgb_svp.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_svp.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_svp_ops.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_svp_point.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_svp_render_aa.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_svp_vpath.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_svp_vpath_stroke.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_svp_wind.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_uta.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_uta_ops.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_uta_rect.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_uta_svp.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_uta_vpath.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_vpath.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_vpath_bpath.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_vpath_dash.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\art_vpath_svp.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\Basic3DBorder.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\BasicFill.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\BasicStroke.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\Color.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\ColorEtchedBorder.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\ControlGraphicsContext.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\DrawToolkit.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\EtchedBorder.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\Font.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\FontState.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\gen_art_config.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\GlyphCollection.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\GraphicsContext.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\GraphicsKit.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\GraphicsObject.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\ImageList.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\libart-features.c; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\Light3DBorder.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\Matrix2D.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\MgcBezierCurve2.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\MgcCurve2.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\MgcIntegrate.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\MgcMath.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\MgcSingleCurve2.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\MgcVector2.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\MicroTiles.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\OpenGLContext.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\OpenGLControlContext.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\PixelBuffer.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\Polygon.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\RenderPaths.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\TitledBorder.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\Graphics\Vector2D.cpp; DestDir: {app}\src\Graphics
Source: ..\..\src\ImplementerKit\AbstractWin32Component.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LightweightComponent.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxFilePeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxFileStream.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxLibraryPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxMutex.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxProcessIORedirector.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxProcessPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxRegistry.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxSemaphorePeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxSystemPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxSystemToolkit.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\LinuxThread.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Application.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Button.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Clipboard.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32ColorDialog.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32ComboBox.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Component.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Context.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32ControlContext.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32CursorPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32CustomControl.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32DatagramSocketPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Desktop.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Dialog.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32DragDropPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32DropTargetPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Edit.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32FileOpenDialog.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32FilePeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32FileSaveDialog.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32FileStream.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32FolderBrowseDialog.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Font.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32FontDialog.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32FontManager.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32GraphicsToolkit.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32HTMLBrowser.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32HTMLBrowserApplication.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Image.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32LibraryPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Listview.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32MenuBar.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32MenuItem.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Mutex.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Object.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32OpenGLPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Peer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32PopupMenu.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32ProcessIORedirector.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32ProcessPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Registry.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32ResourceBundle.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32ResourceStream.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32ScrollPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32SemaphorePeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32SocketPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32SocketPeer.cppold; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32SystemImplementer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32SystemPeer.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32SystemToolkit.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Thread.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32ToolKit.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Tree.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\Win32Window.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\X11Context.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\X11Font.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\X11GraphicsToolkit.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\ImplementerKit\X11Image.cpp; DestDir: {app}\src\ImplementerKit
Source: ..\..\src\IO\BasicInputStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\BasicOutputStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\ComponentInputStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\ComponentOutputStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\Directory.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\File.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\FileStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\FileUtils.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\MemoryStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\ResourceStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\Stream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\TextInputStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\TextOutputStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\VFFInputStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\IO\VFFOutputStream.cpp; DestDir: {app}\src\IO
Source: ..\..\src\net\DatagramSocket.cpp; DestDir: {app}\src\net
Source: ..\..\src\net\NetToolkit.cpp; DestDir: {app}\src\net
Source: ..\..\src\net\ServerSocketEvent.cpp; DestDir: {app}\src\net
Source: ..\..\src\net\Socket.cpp; DestDir: {app}\src\net
Source: ..\..\src\net\SocketEvent.cpp; DestDir: {app}\src\net
Source: ..\..\src\net\SocketListeningLoop.cpp; DestDir: {app}\src\net
Source: ..\..\src\net\URL.cpp; DestDir: {app}\src\net
Source: ..\..\src\remote\AbstractDistributedApplication.cpp; DestDir: {app}\src\remote
Source: ..\..\src\remote\ClassRegistryEntry.cpp; DestDir: {app}\src\remote
Source: ..\..\src\remote\ClassServerInstance.cpp; DestDir: {app}\src\remote
Source: ..\..\src\remote\DistributedClassRegistry.cpp; DestDir: {app}\src\remote
Source: ..\..\src\remote\DistributedException.cpp; DestDir: {app}\src\remote
Source: ..\..\src\remote\InstanceID.cpp; DestDir: {app}\src\remote
Source: ..\..\src\remote\Proxy.cpp; DestDir: {app}\src\remote
Source: ..\..\src\remote\RemoteObjectKit.cpp; DestDir: {app}\src\remote
Source: ..\..\src\Utils\chartables.c; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\CPPParser.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\ErrorLog.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\FilePath.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\get.c; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\GraphicsToolKit.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\Library.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\maketables.c; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\Mutex.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\Parser.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\pcre.c; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\pcreposix.c; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\ProcessWithRedirectedIO.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\regexx.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\Registry.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\Resource.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\ResourceBundle.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\Semaphore.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\StringUtils.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\study.c; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\System.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\SystemToolkit.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\Thread.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\UIToolkit.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\VCFProcess.cpp; DestDir: {app}\src\Utils
Source: ..\..\src\Utils\XMLParser.cpp; DestDir: {app}\src\Utils
Source: ..\..\include\com\ClassFactory.h; DestDir: {app}\include\com
Source: ..\..\include\com\COMDataObject.h; DestDir: {app}\include\com
Source: ..\..\include\com\COMDragSource.h; DestDir: {app}\include\com
Source: ..\..\include\com\COMDropTarget.h; DestDir: {app}\include\com
Source: ..\..\include\com\COMObject.h; DestDir: {app}\include\com
Source: ..\..\include\com\COMUtils.h; DestDir: {app}\include\com
Source: ..\..\include\com\ConnectionPoint.h; DestDir: {app}\include\com
Source: ..\..\include\com\ConnectionPointContainer.h; DestDir: {app}\include\com
Source: ..\..\include\com\DataObject.h; DestDir: {app}\include\com
Source: ..\..\include\com\DispatchObject.h; DestDir: {app}\include\com
Source: ..\..\include\com\EnumObject.h; DestDir: {app}\include\com
Source: ..\..\include\com\MemoryAllocator.h; DestDir: {app}\include\com
Source: ..\..\include\com\VCFCOM.h; DestDir: {app}\include\com
Source: ..\..\include\com\ViewableObject.h; DestDir: {app}\include\com
Source: ..\..\include\core\AbstractApplication.h; DestDir: {app}\include\core
Source: ..\..\include\core\AbstractCommand.h; DestDir: {app}\include\core
Source: ..\..\include\core\AbstractComponentEditor.h; DestDir: {app}\include\core
Source: ..\..\include\core\AbstractListModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\AbstractPropertyEditor.h; DestDir: {app}\include\core
Source: ..\..\include\core\AbstractScrollable.h; DestDir: {app}\include\core
Source: ..\..\include\core\AbstractTableModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\AbstractTextModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\AbstractTreeModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\AbstractView.h; DestDir: {app}\include\core
Source: ..\..\include\core\AcceleratorKey.h; DestDir: {app}\include\core
Source: ..\..\include\core\ActiveXControlHost.h; DestDir: {app}\include\core
Source: ..\..\include\core\Application.h; DestDir: {app}\include\core
Source: ..\..\include\core\ApplicationKitSelectLib.h; DestDir: {app}\include\core
Source: ..\..\include\core\ApplicationPeer.h; DestDir: {app}\include\core
Source: ..\..\include\core\BasicTableItemEditor.h; DestDir: {app}\include\core
Source: ..\..\include\core\Button.h; DestDir: {app}\include\core
Source: ..\..\include\core\CheckBoxControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\Class.h; DestDir: {app}\include\core
Source: ..\..\include\core\ClassInfo.h; DestDir: {app}\include\core
Source: ..\..\include\core\ClassRegistry.h; DestDir: {app}\include\core
Source: ..\..\include\core\Clipboard.h; DestDir: {app}\include\core
Source: ..\..\include\core\ClipboardDataObject.h; DestDir: {app}\include\core
Source: ..\..\include\core\ColumnItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\ColumnModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\ComboBoxControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\Command.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommandButton.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommandGroup.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommonColor.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommonDefines.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommonDialog.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommonFileBrowse.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommonFileDialog.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommonFileOpen.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommonFileSave.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommonFont.h; DestDir: {app}\include\core
Source: ..\..\include\core\CommonPrint.h; DestDir: {app}\include\core
Source: ..\..\include\core\Component.h; DestDir: {app}\include\core
Source: ..\..\include\core\ComponentEditor.h; DestDir: {app}\include\core
Source: ..\..\include\core\ComponentEditorManager.h; DestDir: {app}\include\core
Source: ..\..\include\core\ComponentInfo.h; DestDir: {app}\include\core
Source: ..\..\include\core\Container.h; DestDir: {app}\include\core
Source: ..\..\include\core\Control.h; DestDir: {app}\include\core
Source: ..\..\include\core\ControlContainer.h; DestDir: {app}\include\core
Source: ..\..\include\core\Controller.h; DestDir: {app}\include\core
Source: ..\..\include\core\ControlsKit.h; DestDir: {app}\include\core
Source: ..\..\include\core\Cursor.h; DestDir: {app}\include\core
Source: ..\..\include\core\CursorManager.h; DestDir: {app}\include\core
Source: ..\..\include\core\CustomControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\DataType.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultColumnItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultColumnModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultListItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultListModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultMenuItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultPropertyEditors.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultTableCellItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultTableModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultTabModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultTabPage.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultTextModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultTreeItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\DefaultTreeModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\Desktop.h; DestDir: {app}\include\core
Source: ..\..\include\core\Dialog.h; DestDir: {app}\include\core
Source: ..\..\include\core\FoundationKitSelectLib.h; DestDir: {app}\include\core
Source: ..\..\include\core\Frame.h; DestDir: {app}\include\core
Source: ..\..\include\core\FrameworkConfig.h; DestDir: {app}\include\core
Source: ..\..\include\core\HeaderControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\HTMLBrowserControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\ImageControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\Interface.h; DestDir: {app}\include\core
Source: ..\..\include\core\InterfaceClass.h; DestDir: {app}\include\core
Source: ..\..\include\core\Item.h; DestDir: {app}\include\core
Source: ..\..\include\core\Label.h; DestDir: {app}\include\core
Source: ..\..\include\core\LibraryApplication.h; DestDir: {app}\include\core
Source: ..\..\include\core\ListBoxControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\ListItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\ListModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\ListViewControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\Locales.h; DestDir: {app}\include\core
Source: ..\..\include\core\Menu.h; DestDir: {app}\include\core
Source: ..\..\include\core\MenuBar.h; DestDir: {app}\include\core
Source: ..\..\include\core\MenuItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\MenuItemShortcut.h; DestDir: {app}\include\core
Source: ..\..\include\core\MessageDialog.h; DestDir: {app}\include\core
Source: ..\..\include\core\Method.h; DestDir: {app}\include\core
Source: ..\..\include\core\Model.h; DestDir: {app}\include\core
Source: ..\..\include\core\MultilineTextControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\Object.h; DestDir: {app}\include\core
Source: ..\..\include\core\ObjectWithEvents.h; DestDir: {app}\include\core
Source: ..\..\include\core\OpenGLControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\Panel.h; DestDir: {app}\include\core
Source: ..\..\include\core\Point.h; DestDir: {app}\include\core
Source: ..\..\include\core\PopupMenu.h; DestDir: {app}\include\core
Source: ..\..\include\core\Property.h; DestDir: {app}\include\core
Source: ..\..\include\core\PropertyEditor.h; DestDir: {app}\include\core
Source: ..\..\include\core\PropertyEditorManager.h; DestDir: {app}\include\core
Source: ..\..\include\core\PushButton.h; DestDir: {app}\include\core
Source: ..\..\include\core\RadioButtonControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\Rect.h; DestDir: {app}\include\core
Source: ..\..\include\core\Scrollable.h; DestDir: {app}\include\core
Source: ..\..\include\core\ScrollBarControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\ScrollbarManager.h; DestDir: {app}\include\core
Source: ..\..\include\core\ScrollPeer.h; DestDir: {app}\include\core
Source: ..\..\include\core\Selectable.h; DestDir: {app}\include\core
Source: ..\..\include\core\SelectionListener.h; DestDir: {app}\include\core
Source: ..\..\include\core\Size.h; DestDir: {app}\include\core
Source: ..\..\include\core\Splitter.h; DestDir: {app}\include\core
Source: ..\..\include\core\StatusBar.h; DestDir: {app}\include\core
Source: ..\..\include\core\TabbedPages.h; DestDir: {app}\include\core
Source: ..\..\include\core\TableCellItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\TableControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\TableItemEditor.h; DestDir: {app}\include\core
Source: ..\..\include\core\TableModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\TabModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\TabPage.h; DestDir: {app}\include\core
Source: ..\..\include\core\TextControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\TextModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\TimerComponent.h; DestDir: {app}\include\core
Source: ..\..\include\core\ToggledButton.h; DestDir: {app}\include\core
Source: ..\..\include\core\Toolbar.h; DestDir: {app}\include\core
Source: ..\..\include\core\ToolbarButton.h; DestDir: {app}\include\core
Source: ..\..\include\core\ToolbarDock.h; DestDir: {app}\include\core
Source: ..\..\include\core\ToolbarSeparator.h; DestDir: {app}\include\core
Source: ..\..\include\core\TreeControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\TreeItem.h; DestDir: {app}\include\core
Source: ..\..\include\core\TreeListControl.h; DestDir: {app}\include\core
Source: ..\..\include\core\TreeModel.h; DestDir: {app}\include\core
Source: ..\..\include\core\UIApplication.h; DestDir: {app}\include\core
Source: ..\..\include\core\UndoRedoStack.h; DestDir: {app}\include\core
Source: ..\..\include\core\VCF.h; DestDir: {app}\include\core
Source: ..\..\include\core\VCFMath.h; DestDir: {app}\include\core
Source: ..\..\include\core\View.h; DestDir: {app}\include\core
Source: ..\..\include\core\WarningsOffVc.h; DestDir: {app}\include\core
Source: ..\..\include\core\Window.h; DestDir: {app}\include\core
Source: ..\..\include\core\Wizard.h; DestDir: {app}\include\core
Source: ..\..\include\dragdrop\DragSource.h; DestDir: {app}\include\dragdrop
Source: ..\..\include\dragdrop\DropTarget.h; DestDir: {app}\include\dragdrop
Source: ..\..\include\events\ButtonEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ButtonListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ClipboardEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ClipboardListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ColumnItemEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ColumnModelEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ColumnModelEventHandler.h; DestDir: {app}\include\events
Source: ..\..\include\events\ComboBoxListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ComponentEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ComponentListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ControlEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ControlListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\Delegate.h; DestDir: {app}\include\events
Source: ..\..\include\events\DragEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\DragScrollEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\DragSourceListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\DropEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\DropTargetListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\Event.h; DestDir: {app}\include\events
Source: ..\..\include\events\EventHandler.h; DestDir: {app}\include\events
Source: ..\..\include\events\FocusEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\FocusListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\FrameEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\HelpEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\HelpListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ImageEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ImageListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ImageListEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ImageListListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ItemEditorEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ItemEditorListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ItemEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ItemListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\KeyboardEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\KeyboardListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\Listener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ListModelEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ListModelListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\MenuItemEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\MenuItemListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\MenuListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ModelEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ModelListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ModelValidationListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\MouseEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\MouseListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\NotifyEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\NotifyListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\OutputReadyEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\PropertyChangeEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\PropertyListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ScrollEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ScrollListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\SelectionListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\TableModelEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\TableModelListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\TabModelEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\TabModelListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\TextEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\TextModelListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ThreadEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\TimerEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\TimerListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ToolTipEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\ToolTipListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\TreeModelEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\TreeModelListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\UndoRedoEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\UndoRedoListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\ValidationEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\WhatsThisHelpEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\WhatsThisHelpListener.h; DestDir: {app}\include\events
Source: ..\..\include\events\WindowEvent.h; DestDir: {app}\include\events
Source: ..\..\include\events\WindowListener.h; DestDir: {app}\include\events
Source: ..\..\include\exceptions\ApplicationException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\BadComponentStateException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\BadImageBitsException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\BadModelStateException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\BasicException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\CantCreateObjectException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\ClassNotFound.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\COMException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\DataTypeNotSupportedException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\ErrorStrings.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\ImageLoaderException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\InvalidImage.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\InvalidImplementer.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\InvalidPeer.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\InvalidPointerException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\InvalidStateException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\NoFreeMemException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\NoGraphicsToolkitFoundException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\NoImplementerFoundException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\NoPeerFoundException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\NoSuchElementException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\NoToolKitFoundException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\OutOfBoundsException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\ProcessException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\PropertyChangeException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\ResourceException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\RuntimeException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\ThreadException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\exceptions\TypeCastException.h; DestDir: {app}\include\exceptions
Source: ..\..\include\graphics\AbstractImage.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\acconfig.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\AlphaGamma.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\ArtStroke.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_affine.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_alphagamma.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_bpath.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_config.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_filterlevel.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_gray_svp.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_misc.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_pathcode.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_pixbuf.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_point.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rect.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rect_svp.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rect_uta.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_render.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_render_gradient.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_render_svp.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rgb.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rgba.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rgb_affine.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rgb_affine_private.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rgb_bitmap_affine.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rgb_pixbuf_affine.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rgb_rgba_affine.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_rgb_svp.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_svp.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_svp_ops.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_svp_point.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_svp_render_aa.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_svp_vpath.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_svp_vpath_stroke.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_svp_wind.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_uta.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_uta_ops.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_uta_rect.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_uta_svp.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_uta_vpath.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_vpath.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_vpath_bpath.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_vpath_dash.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\art_vpath_svp.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Basic3DBorder.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\BasicFill.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\BasicRectangle.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\BasicStroke.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Border.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Circle.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\ClippingRegion.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Color.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\ColorEtchedBorder.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Composition.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\confdefs.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\ControlGraphicsContext.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Curve.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\DrawToolkit.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Ellipse.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\EtchedBorder.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Fill.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Filter.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Font.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\FontPeer.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Glyph.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\GlyphCollection.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\GraphicsContext.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\GraphicsKit.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\GraphicsKitSelectLib.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\GraphicsObject.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\GraphicsResourceMgr.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Image.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\ImageBits.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\ImageList.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\ImageLoader.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\ImageTile.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Kernel.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Layer.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\libart-features.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\libart.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\LibArtDLL.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\LibartSelectLib.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Light3DBorder.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MagicFMLibType.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Matrix.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Matrix2D.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MatrixFunction.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcBezierCurve2.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcBezierCurve2.inl; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcCurve2.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcCurve2.inl; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcIntegrate.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcMath.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcMath.inl; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcRTLib.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcSingleCurve2.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcVector2.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MgcVector2.inl; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\MicroTiles.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\OpenGLContext.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\OpenGLControlContext.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Path.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\PathEnumerator.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\PixelBuffer.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Polygon.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Printable.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\PrintContext.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\RenderableArea.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\RenderPaths.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Stroke.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\TileManager.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\TitledBorder.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\UVMap.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\VCFOpenGL.h; DestDir: {app}\include\graphics
Source: ..\..\include\graphics\Vector2D.h; DestDir: {app}\include\graphics
Source: ..\..\include\implementer\AppKitPeerConfig.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ApplicationPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ButtonPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ClipboardPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\CommonDialogPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ContextPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ControlPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\CursorPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\CustomControlPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\DataObjectPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\DesktopPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\DialogPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\DragDropPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\DropTargetPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\FilePeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\FillState.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\FontState.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\HeaderPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\HTMLBrowserPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\LibraryPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ListviewPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\MenuBarPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\MenuItemPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\MutexPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\OpenGLPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\PopupMenuPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\PrintContextPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\PrintPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ProcessIORedirectionPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ProcessPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\RegistryPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ResourceStreamPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ScrollbarPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ScrollPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\StrokeState.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\TextPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\ThreadPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\TreePeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementer\WindowPeer.h; DestDir: {app}\include\implementer
Source: ..\..\include\implementerKit\AbstractWin32Component.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\HTMLBrowserPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LightweightComponent.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxFilePeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxFileStream.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxLibraryPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxMutex.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxProcessIORedirector.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxProcessPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxRegistry.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxSemaphorePeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxSystemPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxSystemToolkit.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\LinuxThread.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Application.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Button.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Clipboard.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ColorDialog.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ComboBox.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Component.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Context.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ControlContext.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32CursorPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32CustomControl.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32DatagramSocketPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Desktop.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Dialog.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32DragDropPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32DropTargetPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Edit.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32FileOpenDialog.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32FilePeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32FileSaveDialog.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32FileStream.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32FolderBrowseDialog.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Font.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32FontDialog.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32FontManager.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32GraphicsToolkit.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32HTMLBrowser.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32HTMLBrowserApplication.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32HTMLBrowserSelectLib.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Image.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32LibraryPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ListBox.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Listview.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32MenuBar.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32MenuItem.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Mutex.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Object.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32OpenGLPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Peer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32PopupMenu.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ProcessIORedirector.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ProcessPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Registry.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ResourceBundle.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ResourceStream.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ScrollPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32SemaphorePeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32SocketPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32SystemPeer.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32SystemToolkit.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Thread.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32ToolKit.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Tree.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\Win32Window.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\X11Context.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\X11Font.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\X11GraphicsToolkit.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\X11Image.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\implementerKit\X11VCFUtils.h; DestDir: {app}\include\implementerKit
Source: ..\..\include\io\BasicFileError.h; DestDir: {app}\include\io
Source: ..\..\include\io\BasicInputStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\BasicOutputStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\ComponentInputStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\ComponentOutputStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\Directory.h; DestDir: {app}\include\io
Source: ..\..\include\io\File.h; DestDir: {app}\include\io
Source: ..\..\include\io\FileIOError.h; DestDir: {app}\include\io
Source: ..\..\include\io\FileNotFound.h; DestDir: {app}\include\io
Source: ..\..\include\io\FileStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\FileStreamPeer.h; DestDir: {app}\include\io
Source: ..\..\include\io\FileUtils.h; DestDir: {app}\include\io
Source: ..\..\include\io\MemoryStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\MemStreamUtils.h; DestDir: {app}\include\io
Source: ..\..\include\io\Persistable.h; DestDir: {app}\include\io
Source: ..\..\include\io\ResourceStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\ResourceStreamPeer.h; DestDir: {app}\include\io
Source: ..\..\include\io\Stream.h; DestDir: {app}\include\io
Source: ..\..\include\io\TextInputStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\TextOutputStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\VariantDataStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\VFFInputStream.h; DestDir: {app}\include\io
Source: ..\..\include\io\VFFOutputStream.h; DestDir: {app}\include\io
Source: ..\..\include\net\DatagramSocket.h; DestDir: {app}\include\net
Source: ..\..\include\net\NetToolkit.h; DestDir: {app}\include\net
Source: ..\..\include\net\NetworkKitSelectLib.h; DestDir: {app}\include\net
Source: ..\..\include\net\ServerSocketEvent.h; DestDir: {app}\include\net
Source: ..\..\include\net\Socket.h; DestDir: {app}\include\net
Source: ..\..\include\net\SocketEvent.h; DestDir: {app}\include\net
Source: ..\..\include\net\SocketException.h; DestDir: {app}\include\net
Source: ..\..\include\net\SocketListener.h; DestDir: {app}\include\net
Source: ..\..\include\net\SocketListeningLoop.h; DestDir: {app}\include\net
Source: ..\..\include\net\SocketPeer.h; DestDir: {app}\include\net
Source: ..\..\include\net\URL.h; DestDir: {app}\include\net
Source: ..\..\include\remote\AbstractDistributedApplication.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\ClassRegistryEntry.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\ClassServerInstance.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\DistributedClassRegistry.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\DistributedException.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\InstanceID.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\Proxy.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\RemoteCommon.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\RemoteConfig.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\RemoteObjectKit.h; DestDir: {app}\include\remote
Source: ..\..\include\remote\RemoteObjectKitSelectLib.h; DestDir: {app}\include\remote
Source: ..\..\include\utils\CPPParser.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\CPPParserSelectLib.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Enum.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Enumerator.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\ErrorLog.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\FilePath.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\GraphicsToolKit.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\internal.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Library.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Lock.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\markup.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Mutex.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Parser.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\pcre.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\pcreposix.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\ProcessWithRedirectedIO.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\References.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\regexx.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Registry.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Resource.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\ResourceBundle.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Runnable.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Semaphore.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\SemaphorePeer.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\StringUtils.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\SynchObject.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\System.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\SystemPeer.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\SystemToolkit.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\Thread.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\UIMetricsManager.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\UIToolkit.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\VCFChar.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\VCFProcess.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\VCFString.h; DestDir: {app}\include\utils
Source: ..\..\include\utils\XMLParser.h; DestDir: {app}\include\utils
Source: ..\..\include\ApplicationKit.h; DestDir: {app}\include\
Source: ..\..\include\ApplicationKitPrivate.h; DestDir: {app}\include\
Source: ..\..\include\ControlsKit.h; DestDir: {app}\include\
Source: ..\..\include\FoundationKit.h; DestDir: {app}\include\
Source: ..\..\include\FoundationKitPrivate.h; DestDir: {app}\include\
Source: ..\..\include\GraphicsKit.h; DestDir: {app}\include\
Source: ..\..\include\GraphicsKitPrivate.h; DestDir: {app}\include\
Source: ..\..\include\ModelViewKit.h; DestDir: {app}\include\
Source: ..\..\include\NetworkKit.h; DestDir: {app}\include\
Source: ..\..\include\NetworkKitPrivate.h; DestDir: {app}\include\
Source: ..\..\include\RemoteObjectKit.h; DestDir: {app}\include\
Source: C:\WINNT\system32\msvcp60.dll; DestDir: {app}\VC6-Addins

[Setup]
OutputDir=E:\code\vcfdev\stable\vcf\uploadToSF
OutputBaseFilename=VCFFullInstaller.0.5.9
AppCopyright=2000-2002 Jim Crafton
AppName=Visual Component Framework 0.5.9 beta
AppVerName=Visual Component Framework 0.5.9 beta
LicenseFile=E:\code\vcfdev\stable\vcf\vcfLicense.txt
DefaultDirName={pf}\VCF

[Registry]
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: VCF_INCLUDE; ValueData: {app}\include; Flags: uninsdeletevalue dontcreatekey
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: VCF_BIN; ValueData: {app}\bin
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: VCF_LIB; ValueData: {app}\lib
Root: HKCU; Subkey: Environment; ValueType: string; ValueName: path; ValueData: "%VCF_BIN%;{olddata}"

[Icons]
Name: {group}\Uninstall VCF; Filename: {uninstallexe}
