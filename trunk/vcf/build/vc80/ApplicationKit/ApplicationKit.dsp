# Microsoft Developer Studio Project File - Name="ApplicationKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ApplicationKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ApplicationKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ApplicationKit.mak" CFG="ApplicationKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ApplicationKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ApplicationKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ApplicationKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\ReleaseS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "USE_GRAPHICSKIT_LIB" /Yu"vcf/ApplicationKit/ApplicationKit.h" /FD /Zm120 /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../Lib/ApplicationKit_vc6_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../Lib/ApplicationKit_vc6_s.lib" /MACHINE:I386

!ELSEIF  "$(CFG)" == "ApplicationKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\DebugS\"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "USE_GRAPHICSKIT_LIB" /Fd"..\..\..\Lib\ApplicationKit_vc6_sd.pdb" /Yu"vcf/ApplicationKit/ApplicationKit.h" /FD /GZ /Zm150 /c
# SUBTRACT CPP /FR
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../Lib/ApplicationKit_vc6_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../Lib/ApplicationKit_vc6_sd.lib" /MACHINE:I386

!ENDIF 

# Begin Target

# Name "ApplicationKit - Win32 Release"
# Name "ApplicationKit - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AppKitPeerConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Application.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKitPrivate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonColorDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileBrowseDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileOpenDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileSaveDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFontDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonPrintDialog.h
# End Source File
# End Group
# Begin Group "Res"

# PROP Default_Filter "*.rc;*.bmp;*.ico"
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
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractPropertyEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractScrollable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractScrollable.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\Application.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKit.cpp
# ADD CPP /Yc"vcf/ApplicationKit/ApplicationKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKitRTTI.inl
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

SOURCE=..\..\..\src\vcf\ApplicationKit\Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Clipboard.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColorEtchedBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColorEtchedBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnLayoutContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Command.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonColorDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileBrowseDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileOpenDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileSaveDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFontDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonPrintDialog.cpp
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

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentInfo.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlGraphicsContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlGraphicsContext.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\DataObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DataObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DataTypeNotSupportedException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultPropertyEditors.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultPropertyEditors.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Desktop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Desktop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Dialog.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\EtchedBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\EtchedBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Frame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Frame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HorizontalLayoutContainer.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\Item.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\KeyboardEvent.cpp
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

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MessageDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MessageDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PopupMenu.h
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

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceBundlePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Scrollable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Selectable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableItemEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TitledBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TitledBorder.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\UndoRedoStack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UndoRedoStack.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\Window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Window.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\WindowEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Wizard.h
# End Source File
# End Group
# Begin Group "Peers"

# PROP Default_Filter "*.h;*.cpp"
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractWin32Component.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractWin32Component.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\COMDataObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\COMDataObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\COMUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\COMUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\EnumObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\LightweightComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\LightweightComponent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SystemTray.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\VCFCOM.h
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
# End Group
# Begin Group "Events"

# PROP Default_Filter "*.h;*.cpp"
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ButtonEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ButtonEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ClipboardEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ClipboardEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnItemEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnItemEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\FocusEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\FocusEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\FrameEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HelpEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HelpEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageListEvent.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\KeyboardEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuItemEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MouseEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MouseEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TimerEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TimerEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToolTipEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToolTipEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UndoRedoEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UndoRedoEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ValidationEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ValidationEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\WhatsThisHelpEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\WindowEvent.h
# End Source File
# End Group
# Begin Group "MVC"

# PROP Default_Filter "*.h;*.cpp"
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

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnModel.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\ListItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Model.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Model.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ModelViewKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableCellItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeModel.h
# End Source File
# End Group
# Begin Group "Controls"

# PROP Default_Filter "*.h;*.cpp"
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Button.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CheckBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CheckBoxControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComboBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComboBoxControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlsKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CustomControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CustomControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HeaderControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HeaderControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HTMLBrowserControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HTMLBrowserControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Label.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Label.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListBoxControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListViewControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListViewControl.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\ProgressControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ProgressControl.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollBarControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollbarManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollbarManager.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\TabbedPages.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabbedPages.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TimerComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TimerComponent.h
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

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeListControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeListControl.h
# End Source File
# End Group
# Begin Group "Peer Interfaces"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ButtonPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ClipboardPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonDialogPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CursorPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DataObjectPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DesktopPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DialogPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DragDropPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DropTargetPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HTMLBrowserPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListviewPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuBarPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuItemPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuManagerPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PopupMenuPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SystemTrayPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\WindowPeer.h
# End Source File
# End Group
# End Target
# End Project
