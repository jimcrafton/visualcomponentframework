# Microsoft Developer Studio Project File - Name="AllIn1DLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=AllIn1DLL - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "AllIn1DLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "AllIn1DLL.mak" CFG="AllIn1DLL - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "AllIn1DLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "AllIn1DLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "AllIn1DLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\DebugDLL\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VCF_ALLIN1_DLL" /D "VCF_ALLIN1_EXPORTS" /Fd"..\..\..\bin\vcf_vc6_d.pdb" /Yu"vcf/ApplicationKit/ApplicationKit.h" /FD /GZ /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib comctl32.lib rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /out:"..\..\..\bin\vcf_vc6_d.dll" /pdbtype:sept /libpath:"..\..\..\lib" /incremental:no
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "AllIn1DLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\ReleaseDLL\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VCF_ALLIN1_DLL" /D "VCF_ALLIN1_EXPORTS" /Yu"vcf/ApplicationKit/ApplicationKit.h" /FD /GZ /Zm200 /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VCF_ALLIN1_DLL" /D "VCF_ALLIN1_EXPORTS" /Yu"vcf/ApplicationKit/ApplicationKit.h" /FD /Zm200 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 version.lib comctl32.lib rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"..\..\..\bin\vcf_d.dll" /implib:"..\..\..\lib\vcf_d.lib" /pdbtype:sept /libpath:"..\..\..\lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 version.lib comctl32.lib rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386 /out:"..\..\..\bin\vcf_vc6.dll" /libpath:"..\..\..\lib" /incremental:no
# SUBTRACT LINK32 /pdb:none /debug

!ENDIF 

# Begin Target

# Name "AllIn1DLL - Win32 Debug"
# Name "AllIn1DLL - Win32 Release"
# Begin Group "ApplicationKit"

# PROP Default_Filter ""
# Begin Group "Res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\resources\win32\ApplicationKit.rc
# End Source File
# Begin Source File

SOURCE=..\..\resources\win32\inform.bmp
# End Source File
# Begin Source File

SOURCE=..\..\resources\win32\question.bmp
# End Source File
# Begin Source File

SOURCE=..\..\resources\win32\stop.bmp
# End Source File
# Begin Source File

SOURCE=..\..\resources\win32\vcf.ico
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractCommand.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractCommand.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractComponentEditor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractComponentEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractListModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractListModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractPropertyEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractScrollable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractScrollable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractTreeModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractTreeModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractView.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractWin32Component.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractWin32Component.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AcceleratorKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AcceleratorKey.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Action.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Action.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AppKitPeerConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Application.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Application.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKit.cpp
# ADD CPP /Yc"vcf/ApplicationKit/ApplicationKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKitPrivate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKitRTTI.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\BadComponentStateException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\BadModelStateException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Basic3DBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Basic3DBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\BasicTableItemEditor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\BasicTableItemEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Border.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Button.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ButtonEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ButtonEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ButtonPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CheckBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CheckBoxControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Clipboard.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ClipboardEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ClipboardEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ClipboardPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColorEtchedBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColorEtchedBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnItemEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnItemEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnLayoutContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComboBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComboBoxControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\COMDataObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\COMDataObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Command.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonColor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonColor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonDialogPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileBrowse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileBrowse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileOpen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileOpen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileSave.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileSave.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFont.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFont.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonPrint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonPrint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Component.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Component.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentEditorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentEditorManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\COMUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\COMUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Container.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Containers.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Containers.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Control.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Control.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlGraphicsContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlGraphicsContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlsKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Cursor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Cursor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CursorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CursorManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CursorPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CustomControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CustomControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DataObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DataObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DataObjectPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DataTypeNotSupportedException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultColumnItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultColumnItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultColumnModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultColumnModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultListItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultListItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultListModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultListModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultMenuItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultPropertyEditors.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultPropertyEditors.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTableCellItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTableCellItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTableModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTableModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTabModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTabModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTabPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTabPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTextModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTextModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTreeItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTreeModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTreeModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Desktop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Desktop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DesktopPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Dialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DialogPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DocManagerPolicy.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Document.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DocumentBasedApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DocumentManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DocumentManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DragDropPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DragEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DragSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DragSource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DropEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DropTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DropTarget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DropTargetPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\EnumObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\EtchedBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\EtchedBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\FocusEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\FocusEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Frame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Frame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\FrameEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HeaderControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HeaderControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HelpEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HelpEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HorizontalLayoutContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HTMLBrowserControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HTMLBrowserControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HTMLBrowserPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageListEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageListEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Item.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ItemEditorEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ItemEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ItemEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\KeyboardEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\KeyboardEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Label.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Label.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\LibraryApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\LibraryApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Light3DBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Light3DBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\LightweightComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\LightweightComponent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListBoxControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListViewControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListViewControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListviewPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Menu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Menu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuBarPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuItemEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuItemPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuManagerPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MessageDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MessageDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Model.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Model.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ModelViewKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MouseEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MouseEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MultilineTextControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MultilineTextControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Panel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Panel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PopupMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PopupMenuPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ProgressControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ProgressControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PropertyEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PropertyEditorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PropertyEditorManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PushButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PushButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\RadioButtonControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\RadioButtonControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceBundlePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Scrollable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollBarControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollbarManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollbarManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Selectable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SliderControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SliderControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Splitter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Splitter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\StatusBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\StatusBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SystemTray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SystemTray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SystemTrayPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabbedPages.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabbedPages.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableCellItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableItemEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TimerComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TimerComponent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TimerEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TimerEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TitledBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TitledBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToggledButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToggledButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Toolbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Toolbar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToolbarDock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToolbarDock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToolTipEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToolTipEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeListControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeListControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UIMetricsManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UIPolicyManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UIToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UIToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UndoRedoEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UndoRedoEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UndoRedoStack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UndoRedoStack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ValidationEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ValidationEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\VCFCOM.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\VFFInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\VFFInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\VFFOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\VFFOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\View.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\WhatsThisHelpEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\WhatsThisHelpEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Application.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Application.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32AppResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32AppResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Button.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Clipboard.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ColorDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ColorDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Component.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Component.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ControlContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ControlContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32CursorPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32CursorPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Desktop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Desktop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Dialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32DragDropPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32DragDropPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32DropTargetPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32DropTargetPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Edit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Edit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FileOpenDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FileOpenDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FileSaveDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FileSaveDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FolderBrowseDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FolderBrowseDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FontDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FontDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Listview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Listview.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32MenuBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32MenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32MenuItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32MenuManagerPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32MenuManagerPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Object.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32PopupMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32PrintDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32PrintDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ScrollPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ScrollPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32SystemTrayPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32SystemTrayPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32TextPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32TextPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Toolbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Toolbar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ToolKit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ToolKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Tree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Tree.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Window.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Window.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\WindowEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\WindowEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\WindowPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Wizard.h
# End Source File
# End Group
# Begin Group "GraphicsKit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\AbstractImage.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\AbstractImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\AggCommon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicFill.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicFill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicRectangle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicStroke.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BasicStroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BezierCurve.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\BezierCurve.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Circle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Color.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Color.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Contextpeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\DrawUIState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Ellipse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Fill.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Filter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Font.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Font.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\FontPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsContext.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKitRTTI.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsResourceBundle.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsResourceBundlePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsToolKit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GraphicsToolKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageBits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageEvent.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageLoaderException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Matrix2D.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Matrix2D.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\MatrixFunction.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Path.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PixelFormats.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Point.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Point.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Printable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintSession.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintSession.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PrintSessionPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Rect.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Rect.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Size.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Stroke.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Context.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Context.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Font.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Font.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32FontManager.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32FontManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsResourceBundle.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsToolkit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32GraphicsToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Image.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32PrintSession.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Win32PrintSession.h
# End Source File
# End Group
# Begin Group "FoundationKit"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicException.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicFileError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicInputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicOutputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\CantCreateObjectException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Class.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Class.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ClassInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ClassNotFound.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ClassRegistry.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ClassRegistry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\CommandLine.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\CommandLine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\CommonDefines.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Condition.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Condition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ConditionPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\DateTime.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\DateTime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Delegate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Dictionary.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Dictionary.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Directory.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Directory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Enum.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Enumerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ErrorLog.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ErrorLog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ErrorStrings.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Event.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Event.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\EventHandler.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\EventHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Field.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\File.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\File.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileIOError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileNotFound.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FilePath.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FilePath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FilePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileStreamPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Format.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKitPrivate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKitRTTI.inl
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FrameworkConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Interface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InterfaceClass.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InterfaceClass.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InvalidPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InvalidPointerException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InvalidStateException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Library.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Library.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\LibraryPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\LocalePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Locales.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Locales.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Lock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MemoryStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MemoryStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MemStreamUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MessageLoader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MessageLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Method.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MIMEType.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MIMEType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Mutex.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Mutex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MutexPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NoFreeMemException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NoPeerFoundException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NoSuchElementException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NotifyEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NotImplementedException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NoToolKitFoundException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Object.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Object.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ObjectWithEvents.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ObjectWithEvents.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\OutOfBoundsException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\OutputReadyEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PackageInfo.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PackageInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Parser.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Parser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Persistable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessIORedirectionPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessWithRedirectedIO.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessWithRedirectedIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProgramInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Property.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PropertyChangeEvent.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PropertyChangeEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PropertyChangeException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Registry.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Registry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RegistryPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Resource.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceBundle.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RTTIMacros.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoop.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoopPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoopSource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Runnable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RuntimeException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Semaphore.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Semaphore.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SemaphorePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Stream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Stream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringsMessageLoader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringsMessageLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringTokenizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringUtils.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SynchObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\System.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\System.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SystemPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SystemToolkit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SystemToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextCodec.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextCodec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextInputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextOutputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Thread.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Thread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadEvent.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadManager.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadManagerPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TypeCastException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VariantData.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VariantData.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VariantDataStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFChar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFMath.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFMath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFProcess.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFProcess.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFRTTIImpl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFString.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFString.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFulong64.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Waitable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\WarningsOffVc.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Condition.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Condition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FilePeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FilePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FileStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FileStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LibraryPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LibraryPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LocalePeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LocalePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Mutex.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Mutex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Peer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Peer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessIORedirector.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessIORedirector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Registry.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Registry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ResourceBundle.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32RunLoopPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32RunLoopPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SemaphorePeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SemaphorePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemToolkit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Thread.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Thread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ThreadManagerPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ThreadManagerPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\XMLParser.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\XMLParser.h
# End Source File
# End Group
# End Target
# End Project
