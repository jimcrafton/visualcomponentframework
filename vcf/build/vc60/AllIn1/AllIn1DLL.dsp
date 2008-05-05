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
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
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
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VCF_ALLIN1_DLL" /D "VCF_ALLIN1_EXPORTS" /Yu"vcf/ApplicationKit/ApplicationKit.h" /Fd"..\..\..\bin\vcf_vc6_d.pdb" /FD /GZ /Zm300 /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 version.lib comctl32.lib rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /debug /machine:I386 /out:"..\..\..\bin\vcf_vc6_d.dll" /pdbtype:sept /libpath:"..\..\..\lib"
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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_ROOT)/src" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VCF_ALLIN1_DLL" /D "VCF_ALLIN1_EXPORTS" /Yu"vcf/ApplicationKit/ApplicationKit.h" /FD /GZ /Zm200 /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_ROOT)/src" /I "$(VCF_ROOT)/src/thirdparty/win32" /D "WIN32" /D "_NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "VCF_ALLIN1_DLL" /D "VCF_ALLIN1_EXPORTS" /Yu"vcf/ApplicationKit/ApplicationKit.h" /FD /Zm300 /c
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
# ADD LINK32 version.lib comctl32.lib rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /incremental:no /machine:I386 /out:"..\..\..\bin\vcf_vc6.dll" /libpath:"..\..\..\lib"
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

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractCommand.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractComponentEditor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractScrollable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AbstractWin32Component.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\AcceleratorKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Action.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Application.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationKit.cpp
# ADD CPP /Yc"vcf/ApplicationKit/ApplicationKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ApplicationResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Basic3DBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\BasicTableItemEditor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CheckBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColorEtchedBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ColumnItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ComboBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommandGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonColorDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileBrowseDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CommonFileDialog.cpp
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

SOURCE=..\..\..\src\vcf\ApplicationKit\ComponentEditorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Containers.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Control.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ControlGraphicsContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Cursor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CursorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\CustomControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DataObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultListModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultPropertyEditors.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTableCellItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTableModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTabPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTextModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DefaultTreeModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Document.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DocumentManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DragSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DropDownControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\DropTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\EtchedBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Frame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\HeaderControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ImageList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Label.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\LibraryApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Light3DBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\LightweightComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ListViewControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Menu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MenuManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MessageDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Model.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\MultilineTextControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Panel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PopupWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ProgressControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PropertyEditorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\PushButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\RadioButtonControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ScrollbarManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SimpleListModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SliderControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Splitter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\StatusBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\SystemTray.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabbedPages.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TableControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TabModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TextControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TimerComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TitledBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToggledButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Toolbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\ToolbarDock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TransparentWindow.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeListControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeListModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\TreeModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UIComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UIShell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UIToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\UndoRedoStack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Application.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32AppResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ColorDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32COMDataObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Component.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32COMUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ControlContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32CursorPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32DragDropPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32DropDownPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32DropTargetPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Edit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FileOpenDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FileSaveDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FolderBrowseDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32FontDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Listview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32MenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32MenuManagerPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32PopupWindowPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32PrintDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ScrollPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32SystemTrayPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32TextPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Toolbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32ToolKit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32TransparentWindowPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Tree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32UIShell.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Win32Window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\ApplicationKit\Window.cpp
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

SOURCE=..\..\..\src\vcf\GraphicsKit\GrayScaleImage.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\GrayScaleImage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\Image.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageBits.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\ImageLoaderException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\JPEGLoader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\JPEGLoader.h
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

SOURCE=..\..\..\src\vcf\GraphicsKit\PNGLoader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\GraphicsKit\PNGLoader.h
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

SOURCE=..\..\..\src\vcf\FoundationKit\Base64Codec.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicException.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicInputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicOutputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Class.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ClassRegistry.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\CommandLine.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Component.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ComponentInfo.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Condition.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\DateTime.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Delegates.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Dictionary.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Directory.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ErrorLog.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\File.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FilePath.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\IniFini.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InterfaceClass.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Library.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Locales.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MessageLoader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MIMEType.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Mutex.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Object.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PackageInfo.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessWithRedirectedIO.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Registry.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Resource.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceBundle.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoop.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoopSource.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoopSourcePeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoopTimer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Semaphore.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Stream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringsMessageLoader.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringUtils.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\System.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SystemToolkit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextCodec.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextInputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextOutputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Thread.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadManager.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VariantData.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFMath.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFProcess.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFString.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VFFInputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VFFOutputStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VFFParser.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Condition.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FilePeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FileStream.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LibraryPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LocalePeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Mutex.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Peer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessIORedirector.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Registry.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ResourceBundle.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32RunLoopPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32RunLoopSourcePeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32RunLoopTimerPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SemaphorePeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemToolkit.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Thread.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ThreadManagerPeer.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\XMLParser.cpp
# SUBTRACT CPP /YX /Yc /Yu
# End Source File
# End Group
# End Target
# End Project
