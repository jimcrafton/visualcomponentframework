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
# PROP Scc_ProjName "ApplicationKit"
# PROP Scc_LocalPath "."
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
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "vc7/ReleaseS\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /I "$(VCF_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "USE_FRAMEWORK_LIB" /D "USE_GRAPHICSKIT_LIB" /D "USE_WIN32HTMLBROWSER_LIB" /Yu"ApplicationKit.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\..\..\Lib\ApplicationKit_vc7_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\Lib\ApplicationKit_vc7_s.lib"

!ELSEIF  "$(CFG)" == "ApplicationKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib"
# PROP Intermediate_Dir "vc7/DebugS\obj"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "USE_FRAMEWORK_LIB" /D "USE_GRAPHICSKIT_LIB" /D "USE_WIN32HTMLBROWSER_LIB" /FR /Yu"ApplicationKit.h" /Fd"..\..\..\Lib/ApplicationKit_vc7_sd.pdb" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"..\..\..\Lib\ApplicationKit_vc7_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\..\..\Lib\ApplicationKit_vc7_sd.lib"

!ENDIF 

# Begin Target

# Name "ApplicationKit - Win32 Release"
# Name "ApplicationKit - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\core\AbstractApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractCommand.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractComponentEditor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractListModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractPropertyEditor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractScrollable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractTableModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractTextModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractTreeModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AbstractView.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\AbstractWin32Component.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\AcceleratorKey.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Application.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ApplicationKit.cpp
# ADD CPP /Yc"ApplicationKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Graphics\Basic3DBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\BasicTableItemEditor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ButtonEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CheckBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ClipboardDataObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ClipboardEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Graphics\ColorEtchedBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ColumnItemEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ColumnModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ComboBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\COM\COMDataObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\COM\COMDragSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\COM\COMDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CommandButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CommandGroup.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CommonColor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CommonFileBrowse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CommonFileDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CommonFileOpen.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CommonFileSave.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CommonFont.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CommonPrint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\COM\COMObject.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Component.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ComponentEditorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ComponentInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\COM\COMUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Control.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ControlContainer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ControlEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Graphics\ControlGraphicsContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Cursor.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CursorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\CustomControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DataType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultColumnItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultColumnModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultListItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultListModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultMenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultPropertyEditors.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultTableCellItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultTableModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultTabModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultTabPage.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultTextModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultTreeItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\DefaultTreeModel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Desktop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\DragEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\DragDrop\DragSource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\DropEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\DragDrop\DropTarget.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Graphics\EtchedBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\FocusEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Frame.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\HeaderControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\HelpEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\HTMLBrowserControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ImageControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Graphics\ImageList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ImageListEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ItemEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\KeyboardEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Label.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\LibraryApplication.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Graphics\Light3DBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\LightweightComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ListBoxControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ListModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ListViewControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Menu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\MenuItemEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\MessageDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Model.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\MouseEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\MultilineTextControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Panel.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\PropertyEditorManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\PushButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\RadioButtonControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Utils\Resource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\IO\ResourceStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ScrollbarManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Splitter.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\StatusBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\TabbedPages.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\TableControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\TableModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\TabModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\TextControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\TextEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\TimerComponent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\TimerEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Graphics\TitledBorder.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ToggledButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Toolbar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ToolbarButton.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ToolbarDock.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\ToolbarSeparator.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ToolTipEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\TreeControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\TreeListControl.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\TreeModelEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Utils\UIToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\UndoRedoEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\UndoRedoStack.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\ValidationEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\IO\VFFInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\IO\VFFOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\WhatsThisHelpEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Application.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Button.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Clipboard.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32ColorDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Component.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32ControlContext.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32CursorPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Desktop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Dialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32DragDropPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32DropTargetPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Edit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32FileOpenDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32FileSaveDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32FolderBrowseDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32FontDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Listview.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32MenuBar.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32MenuItem.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32PopupMenu.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32ResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32ResourceStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32ScrollPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32ToolKit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Tree.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\ImplementerKit\Win32Window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\core\Window.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\Events\WindowEvent.cpp
# End Source File
# End Group
# Begin Group "Res"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\resources\win32\ApplicationKit.rc
# End Source File
# Begin Source File

SOURCE=..\..\resources\win32\inform.bmp
# End Source File
# Begin Source File

SOURCE=..\..\resources\win32\vcf.ico
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\core\AbstractApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AbstractCommand.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AbstractComponentEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AbstractListModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AbstractPropertyEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AbstractScrollable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AbstractTableModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AbstractTextModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AbstractTreeModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AbstractView.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\AbstractWin32Component.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\AcceleratorKey.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\AppKitPeerConfig.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Application.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\exceptions\ApplicationException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\ApplicationKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\ApplicationKitPrivate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ApplicationPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\exceptions\BadComponentStateException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\exceptions\BadModelStateException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\BasicTableItemEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Button.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ButtonEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ButtonListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\ButtonPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CheckBoxControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ColumnItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ColumnItemEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ColumnModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ColumnModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ColumnModelEventHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ComboBoxControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ComboBoxListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\com\COMDataObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\com\COMDropTarget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Command.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommandButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommandGroup.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommonColor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommonDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\CommonDialogPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommonFileBrowse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommonFileDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommonFileOpen.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommonFileSave.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommonFont.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CommonPrint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\com\COMObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Component.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ComponentEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ComponentEditorManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ComponentEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ComponentInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ComponentListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\com\COMUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Container.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\Contextpeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Control.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ControlContainer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ControlEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\graphics\ControlGraphicsContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Controller.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ControlListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\ControlPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\ControlsKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Cursor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CursorManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\CursorPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\CustomControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\CustomControlPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\dragdrop\DataObjectPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\dragdrop\DataType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\exceptions\DataTypeNotSupportedException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultColumnItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultColumnModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultListItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultListModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultMenuItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultPropertyEditors.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultTableCellItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultTableModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultTabModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultTabPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultTextModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultTreeItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\DefaultTreeModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Desktop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\DesktopPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Dialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\DialogPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\dragdrop\DragSource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\dragdrop\DropTarget.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\FillState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\FocusEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\FocusListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\FontState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Frame.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\FrameEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\HeaderControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\HeaderPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\HelpEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\HelpListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\HTMLBrowserControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\HTMLBrowserPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ImageControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\graphics\ImageList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ImageListEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ImageListListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\exceptions\InvalidStateException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Item.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ItemEditorEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ItemEditorListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ItemEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ItemListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\KeyboardEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\KeyboardListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Label.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\LibraryApplication.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\graphics\Light3DBorder.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\LightweightComponent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ListBoxControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\ListBoxPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ListItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ListModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ListModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ListModelListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ListViewControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\ListviewPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Menu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\MenuBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\MenuBarPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\MenuItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\MenuItemEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\MenuItemListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\MenuItemPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\MenuListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Model.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ModelListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ModelValidationListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\ModelViewKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\MouseEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\MouseListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\MultilineTextControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\NotifyEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\NotifyListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\exceptions\NoToolKitFoundException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\OpenGLControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\graphics\OpenGLControlContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Panel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\PopupMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\PopupMenuPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\PrintContextPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\PrintPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\PropertyEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\PropertyEditorManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\PushButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\RadioButtonControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\utils\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\utils\ResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\exceptions\ResourceException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\io\ResourceStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Scrollable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ScrollBarControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ScrollbarManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ScrollEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ScrollPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Selectable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Splitter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\StatusBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\StrokeState.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TabbedPages.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TableCellItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TableControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TableItemEditor.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TableModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\TableModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\TableModelListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TabModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\TabModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\TabModelListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TabPage.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TextControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\TextEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TextModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\TextModelListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\TextPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TimerComponent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\TimerEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ToggledButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Toolbar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ToolbarButton.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ToolbarDock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\ToolbarSeparator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ToolTipEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ToolTipListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TreeControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TreeItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TreeListControl.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\TreeModel.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\TreeModelEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\TreeModelListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\TreePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\utils\UIToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\UndoRedoEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\UndoRedoListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\UndoRedoStack.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\ValidationEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\com\VCFCOM.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\io\VFFInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\io\VFFOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\View.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\WhatsThisHelpEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\WhatsThisHelpListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Application.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Button.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Clipboard.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32ColorDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Component.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerkit\Win32ControlContext.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32CursorPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Desktop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Dialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32DragDropPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32DropTargetPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Edit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32FileOpenDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32FileSaveDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32FolderBrowseDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32FontDialog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\ImplementerKit\Win32FontManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Listview.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32MenuBar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32MenuItem.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Object.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Peer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32PopupMenu.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32ResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32ResourceStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32ScrollPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32SystemPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32ToolKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Tree.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementerKit\Win32Window.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\core\Window.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\WindowEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\events\WindowListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\implementer\WindowPeer.h
# End Source File
# End Group
# End Target
# End Project
