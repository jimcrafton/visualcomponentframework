# Microsoft Developer Studio Generated NMAKE File, Based on ApplicationKit.dsp
!IF "$(CFG)" == ""
CFG=ApplicationKit - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ApplicationKit - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ApplicationKit - Win32 Release" && "$(CFG)" != "ApplicationKit - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "ApplicationKit - Win32 Release"

OUTDIR=.\..\..\..\lib
INTDIR=.\ReleaseS\obj
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ApplicationKit_s.lib"

!ELSE 

ALL : "GraphicsKit - Win32 Release" "FoundationKit - Win32 Release" "$(OUTDIR)\ApplicationKit_s.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKit - Win32 ReleaseCLEAN" "GraphicsKit - Win32 ReleaseCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AbstractCommand.obj"
	-@erase "$(INTDIR)\AbstractContainer.obj"
	-@erase "$(INTDIR)\AbstractListModel.obj"
	-@erase "$(INTDIR)\AbstractTableModel.obj"
	-@erase "$(INTDIR)\AbstractTextModel.obj"
	-@erase "$(INTDIR)\AbstractTreeModel.obj"
	-@erase "$(INTDIR)\AbstractWin32Component.obj"
	-@erase "$(INTDIR)\Application.obj"
	-@erase "$(INTDIR)\ApplicationKit.obj"
	-@erase "$(INTDIR)\ApplicationKit.pch"
	-@erase "$(INTDIR)\Basic3DBorder.obj"
	-@erase "$(INTDIR)\BasicTableItemEditor.obj"
	-@erase "$(INTDIR)\ButtonEvent.obj"
	-@erase "$(INTDIR)\CheckBoxControl.obj"
	-@erase "$(INTDIR)\Clipboard.obj"
	-@erase "$(INTDIR)\ClipboardDataObject.obj"
	-@erase "$(INTDIR)\ClipboardEvent.obj"
	-@erase "$(INTDIR)\ComboBoxControl.obj"
	-@erase "$(INTDIR)\COMDataObject.obj"
	-@erase "$(INTDIR)\COMDropTarget.obj"
	-@erase "$(INTDIR)\CommandButton.obj"
	-@erase "$(INTDIR)\CommandGroup.obj"
	-@erase "$(INTDIR)\CommonColor.obj"
	-@erase "$(INTDIR)\CommonFileBrowse.obj"
	-@erase "$(INTDIR)\CommonFileDialog.obj"
	-@erase "$(INTDIR)\CommonFileOpen.obj"
	-@erase "$(INTDIR)\CommonFileSave.obj"
	-@erase "$(INTDIR)\CommonFont.obj"
	-@erase "$(INTDIR)\CommonPrint.obj"
	-@erase "$(INTDIR)\COMObject.obj"
	-@erase "$(INTDIR)\Component.obj"
	-@erase "$(INTDIR)\ComponentInfo.obj"
	-@erase "$(INTDIR)\COMUtils.obj"
	-@erase "$(INTDIR)\Control.obj"
	-@erase "$(INTDIR)\ControlContainer.obj"
	-@erase "$(INTDIR)\ControlEvent.obj"
	-@erase "$(INTDIR)\ControlGraphicsContext.obj"
	-@erase "$(INTDIR)\CustomControl.obj"
	-@erase "$(INTDIR)\DataType.obj"
	-@erase "$(INTDIR)\DefaultListItem.obj"
	-@erase "$(INTDIR)\DefaultListModel.obj"
	-@erase "$(INTDIR)\DefaultMenuItem.obj"
	-@erase "$(INTDIR)\DefaultPropertyEditors.obj"
	-@erase "$(INTDIR)\DefaultTableCellItem.obj"
	-@erase "$(INTDIR)\DefaultTableModel.obj"
	-@erase "$(INTDIR)\DefaultTabModel.obj"
	-@erase "$(INTDIR)\DefaultTabPage.obj"
	-@erase "$(INTDIR)\DefaultTextModel.obj"
	-@erase "$(INTDIR)\DefaultTreeItem.obj"
	-@erase "$(INTDIR)\DefaultTreeModel.obj"
	-@erase "$(INTDIR)\Desktop.obj"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\DragEvent.obj"
	-@erase "$(INTDIR)\DragSource.obj"
	-@erase "$(INTDIR)\DropEvent.obj"
	-@erase "$(INTDIR)\DropTarget.obj"
	-@erase "$(INTDIR)\Frame.obj"
	-@erase "$(INTDIR)\ImageList.obj"
	-@erase "$(INTDIR)\ImageListEvent.obj"
	-@erase "$(INTDIR)\ItemEvent.obj"
	-@erase "$(INTDIR)\KeyboardEvent.obj"
	-@erase "$(INTDIR)\Label.obj"
	-@erase "$(INTDIR)\Light3DBorder.obj"
	-@erase "$(INTDIR)\LightweightComponent.obj"
	-@erase "$(INTDIR)\ListBoxControl.obj"
	-@erase "$(INTDIR)\ListModelEvent.obj"
	-@erase "$(INTDIR)\ListViewControl.obj"
	-@erase "$(INTDIR)\Menu.obj"
	-@erase "$(INTDIR)\MenuBar.obj"
	-@erase "$(INTDIR)\MenuItemEvent.obj"
	-@erase "$(INTDIR)\MenuItemShortcut.obj"
	-@erase "$(INTDIR)\Model.obj"
	-@erase "$(INTDIR)\MouseEvent.obj"
	-@erase "$(INTDIR)\MultilineTextControl.obj"
	-@erase "$(INTDIR)\OpenGLControl.obj"
	-@erase "$(INTDIR)\OpenGLControlContext.obj"
	-@erase "$(INTDIR)\Panel.obj"
	-@erase "$(INTDIR)\PopupMenu.obj"
	-@erase "$(INTDIR)\PropertyEditorManager.obj"
	-@erase "$(INTDIR)\Resource.obj"
	-@erase "$(INTDIR)\ResourceStream.obj"
	-@erase "$(INTDIR)\Splitter.obj"
	-@erase "$(INTDIR)\TabbedPages.obj"
	-@erase "$(INTDIR)\TableControl.obj"
	-@erase "$(INTDIR)\TableModelEvent.obj"
	-@erase "$(INTDIR)\TabModelEvent.obj"
	-@erase "$(INTDIR)\TextControl.obj"
	-@erase "$(INTDIR)\TextEvent.obj"
	-@erase "$(INTDIR)\Toolbar.obj"
	-@erase "$(INTDIR)\ToolbarButton.obj"
	-@erase "$(INTDIR)\ToolbarDock.obj"
	-@erase "$(INTDIR)\ToolbarSeparator.obj"
	-@erase "$(INTDIR)\TreeControl.obj"
	-@erase "$(INTDIR)\TreeListControl.obj"
	-@erase "$(INTDIR)\TreeModelEvent.obj"
	-@erase "$(INTDIR)\UIToolkit.obj"
	-@erase "$(INTDIR)\UndoRedoEvent.obj"
	-@erase "$(INTDIR)\UndoRedoStack.obj"
	-@erase "$(INTDIR)\ValidationEvent.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\VFFInputStream.obj"
	-@erase "$(INTDIR)\VFFOutputStream.obj"
	-@erase "$(INTDIR)\Win32Application.obj"
	-@erase "$(INTDIR)\Win32Button.obj"
	-@erase "$(INTDIR)\Win32ColorDialog.obj"
	-@erase "$(INTDIR)\Win32ComboBox.obj"
	-@erase "$(INTDIR)\Win32Component.obj"
	-@erase "$(INTDIR)\Win32ControlContext.obj"
	-@erase "$(INTDIR)\Win32CustomControl.obj"
	-@erase "$(INTDIR)\Win32Desktop.obj"
	-@erase "$(INTDIR)\Win32Dialog.obj"
	-@erase "$(INTDIR)\Win32DropTargetPeer.obj"
	-@erase "$(INTDIR)\Win32Edit.obj"
	-@erase "$(INTDIR)\Win32FileOpenDialog.obj"
	-@erase "$(INTDIR)\Win32FileSaveDialog.obj"
	-@erase "$(INTDIR)\Win32FolderBrowseDialog.obj"
	-@erase "$(INTDIR)\Win32FontDialog.obj"
	-@erase "$(INTDIR)\Win32ListBox.obj"
	-@erase "$(INTDIR)\Win32Listview.obj"
	-@erase "$(INTDIR)\Win32MenuBar.obj"
	-@erase "$(INTDIR)\Win32MenuItem.obj"
	-@erase "$(INTDIR)\Win32Object.obj"
	-@erase "$(INTDIR)\Win32PopupMenu.obj"
	-@erase "$(INTDIR)\Win32ResourceBundle.obj"
	-@erase "$(INTDIR)\Win32ResourceStream.obj"
	-@erase "$(INTDIR)\Win32ToolKit.obj"
	-@erase "$(INTDIR)\Win32Tree.obj"
	-@erase "$(INTDIR)\Win32Window.obj"
	-@erase "$(INTDIR)\Window.obj"
	-@erase "$(INTDIR)\WindowEvent.obj"
	-@erase "$(OUTDIR)\ApplicationKit_s.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\COM" /I "..\..\..\include\Core" /I "..\..\..\include\Graphics" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\Implementer" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\DragDrop" /I "..\..\..\xml\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\ApplicationKit.pch" /Yu"ApplicationKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ApplicationKit.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ApplicationKit_s.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AbstractCommand.obj" \
	"$(INTDIR)\AbstractContainer.obj" \
	"$(INTDIR)\AbstractListModel.obj" \
	"$(INTDIR)\AbstractTableModel.obj" \
	"$(INTDIR)\AbstractTextModel.obj" \
	"$(INTDIR)\AbstractTreeModel.obj" \
	"$(INTDIR)\AbstractWin32Component.obj" \
	"$(INTDIR)\Application.obj" \
	"$(INTDIR)\ApplicationKit.obj" \
	"$(INTDIR)\Basic3DBorder.obj" \
	"$(INTDIR)\BasicTableItemEditor.obj" \
	"$(INTDIR)\ButtonEvent.obj" \
	"$(INTDIR)\CheckBoxControl.obj" \
	"$(INTDIR)\Clipboard.obj" \
	"$(INTDIR)\ClipboardDataObject.obj" \
	"$(INTDIR)\ClipboardEvent.obj" \
	"$(INTDIR)\ComboBoxControl.obj" \
	"$(INTDIR)\COMDataObject.obj" \
	"$(INTDIR)\COMDropTarget.obj" \
	"$(INTDIR)\CommandButton.obj" \
	"$(INTDIR)\CommandGroup.obj" \
	"$(INTDIR)\CommonColor.obj" \
	"$(INTDIR)\CommonFileBrowse.obj" \
	"$(INTDIR)\CommonFileDialog.obj" \
	"$(INTDIR)\CommonFileOpen.obj" \
	"$(INTDIR)\CommonFileSave.obj" \
	"$(INTDIR)\CommonFont.obj" \
	"$(INTDIR)\CommonPrint.obj" \
	"$(INTDIR)\COMObject.obj" \
	"$(INTDIR)\Component.obj" \
	"$(INTDIR)\ComponentInfo.obj" \
	"$(INTDIR)\COMUtils.obj" \
	"$(INTDIR)\Control.obj" \
	"$(INTDIR)\ControlContainer.obj" \
	"$(INTDIR)\ControlEvent.obj" \
	"$(INTDIR)\ControlGraphicsContext.obj" \
	"$(INTDIR)\CustomControl.obj" \
	"$(INTDIR)\DataType.obj" \
	"$(INTDIR)\DefaultListItem.obj" \
	"$(INTDIR)\DefaultListModel.obj" \
	"$(INTDIR)\DefaultMenuItem.obj" \
	"$(INTDIR)\DefaultPropertyEditors.obj" \
	"$(INTDIR)\DefaultTableCellItem.obj" \
	"$(INTDIR)\DefaultTableModel.obj" \
	"$(INTDIR)\DefaultTabModel.obj" \
	"$(INTDIR)\DefaultTabPage.obj" \
	"$(INTDIR)\DefaultTextModel.obj" \
	"$(INTDIR)\DefaultTreeItem.obj" \
	"$(INTDIR)\DefaultTreeModel.obj" \
	"$(INTDIR)\Desktop.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\DragEvent.obj" \
	"$(INTDIR)\DragSource.obj" \
	"$(INTDIR)\DropEvent.obj" \
	"$(INTDIR)\DropTarget.obj" \
	"$(INTDIR)\Frame.obj" \
	"$(INTDIR)\ImageList.obj" \
	"$(INTDIR)\ImageListEvent.obj" \
	"$(INTDIR)\ItemEvent.obj" \
	"$(INTDIR)\KeyboardEvent.obj" \
	"$(INTDIR)\Label.obj" \
	"$(INTDIR)\Light3DBorder.obj" \
	"$(INTDIR)\LightweightComponent.obj" \
	"$(INTDIR)\ListBoxControl.obj" \
	"$(INTDIR)\ListModelEvent.obj" \
	"$(INTDIR)\ListViewControl.obj" \
	"$(INTDIR)\Menu.obj" \
	"$(INTDIR)\MenuBar.obj" \
	"$(INTDIR)\MenuItemEvent.obj" \
	"$(INTDIR)\MenuItemShortcut.obj" \
	"$(INTDIR)\Model.obj" \
	"$(INTDIR)\MouseEvent.obj" \
	"$(INTDIR)\MultilineTextControl.obj" \
	"$(INTDIR)\OpenGLControl.obj" \
	"$(INTDIR)\OpenGLControlContext.obj" \
	"$(INTDIR)\Panel.obj" \
	"$(INTDIR)\PopupMenu.obj" \
	"$(INTDIR)\PropertyEditorManager.obj" \
	"$(INTDIR)\Resource.obj" \
	"$(INTDIR)\ResourceStream.obj" \
	"$(INTDIR)\Splitter.obj" \
	"$(INTDIR)\TabbedPages.obj" \
	"$(INTDIR)\TableControl.obj" \
	"$(INTDIR)\TableModelEvent.obj" \
	"$(INTDIR)\TabModelEvent.obj" \
	"$(INTDIR)\TextControl.obj" \
	"$(INTDIR)\TextEvent.obj" \
	"$(INTDIR)\Toolbar.obj" \
	"$(INTDIR)\ToolbarButton.obj" \
	"$(INTDIR)\ToolbarDock.obj" \
	"$(INTDIR)\ToolbarSeparator.obj" \
	"$(INTDIR)\TreeControl.obj" \
	"$(INTDIR)\TreeListControl.obj" \
	"$(INTDIR)\TreeModelEvent.obj" \
	"$(INTDIR)\UIToolkit.obj" \
	"$(INTDIR)\UndoRedoEvent.obj" \
	"$(INTDIR)\UndoRedoStack.obj" \
	"$(INTDIR)\ValidationEvent.obj" \
	"$(INTDIR)\VFFInputStream.obj" \
	"$(INTDIR)\VFFOutputStream.obj" \
	"$(INTDIR)\Win32Application.obj" \
	"$(INTDIR)\Win32Button.obj" \
	"$(INTDIR)\Win32ColorDialog.obj" \
	"$(INTDIR)\Win32ComboBox.obj" \
	"$(INTDIR)\Win32Component.obj" \
	"$(INTDIR)\Win32ControlContext.obj" \
	"$(INTDIR)\Win32CustomControl.obj" \
	"$(INTDIR)\Win32Desktop.obj" \
	"$(INTDIR)\Win32Dialog.obj" \
	"$(INTDIR)\Win32DropTargetPeer.obj" \
	"$(INTDIR)\Win32Edit.obj" \
	"$(INTDIR)\Win32FileOpenDialog.obj" \
	"$(INTDIR)\Win32FileSaveDialog.obj" \
	"$(INTDIR)\Win32FolderBrowseDialog.obj" \
	"$(INTDIR)\Win32FontDialog.obj" \
	"$(INTDIR)\Win32ListBox.obj" \
	"$(INTDIR)\Win32Listview.obj" \
	"$(INTDIR)\Win32MenuBar.obj" \
	"$(INTDIR)\Win32MenuItem.obj" \
	"$(INTDIR)\Win32Object.obj" \
	"$(INTDIR)\Win32PopupMenu.obj" \
	"$(INTDIR)\Win32ResourceBundle.obj" \
	"$(INTDIR)\Win32ResourceStream.obj" \
	"$(INTDIR)\Win32ToolKit.obj" \
	"$(INTDIR)\Win32Tree.obj" \
	"$(INTDIR)\Win32Window.obj" \
	"$(INTDIR)\Window.obj" \
	"$(INTDIR)\WindowEvent.obj" \
	"$(OUTDIR)\FoundationKit_s.lib" \
	"$(OUTDIR)\GraphicsKit_s.lib"

"$(OUTDIR)\ApplicationKit_s.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ApplicationKit - Win32 Debug"

OUTDIR=.\..\..\..\lib
INTDIR=.\DebugS\obj
# Begin Custom Macros
OutDir=.\..\..\..\lib
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ApplicationKit_sd.lib"

!ELSE 

ALL : "GraphicsKit - Win32 Debug" "FoundationKit - Win32 Debug" "$(OUTDIR)\ApplicationKit_sd.lib"

!ENDIF 

!IF "$(RECURSE)" == "1" 
CLEAN :"FoundationKit - Win32 DebugCLEAN" "GraphicsKit - Win32 DebugCLEAN" 
!ELSE 
CLEAN :
!ENDIF 
	-@erase "$(INTDIR)\AbstractCommand.obj"
	-@erase "$(INTDIR)\AbstractContainer.obj"
	-@erase "$(INTDIR)\AbstractListModel.obj"
	-@erase "$(INTDIR)\AbstractTableModel.obj"
	-@erase "$(INTDIR)\AbstractTextModel.obj"
	-@erase "$(INTDIR)\AbstractTreeModel.obj"
	-@erase "$(INTDIR)\AbstractWin32Component.obj"
	-@erase "$(INTDIR)\Application.obj"
	-@erase "$(INTDIR)\ApplicationKit.obj"
	-@erase "$(INTDIR)\ApplicationKit.pch"
	-@erase "$(INTDIR)\Basic3DBorder.obj"
	-@erase "$(INTDIR)\BasicTableItemEditor.obj"
	-@erase "$(INTDIR)\ButtonEvent.obj"
	-@erase "$(INTDIR)\CheckBoxControl.obj"
	-@erase "$(INTDIR)\Clipboard.obj"
	-@erase "$(INTDIR)\ClipboardDataObject.obj"
	-@erase "$(INTDIR)\ClipboardEvent.obj"
	-@erase "$(INTDIR)\ComboBoxControl.obj"
	-@erase "$(INTDIR)\COMDataObject.obj"
	-@erase "$(INTDIR)\COMDropTarget.obj"
	-@erase "$(INTDIR)\CommandButton.obj"
	-@erase "$(INTDIR)\CommandGroup.obj"
	-@erase "$(INTDIR)\CommonColor.obj"
	-@erase "$(INTDIR)\CommonFileBrowse.obj"
	-@erase "$(INTDIR)\CommonFileDialog.obj"
	-@erase "$(INTDIR)\CommonFileOpen.obj"
	-@erase "$(INTDIR)\CommonFileSave.obj"
	-@erase "$(INTDIR)\CommonFont.obj"
	-@erase "$(INTDIR)\CommonPrint.obj"
	-@erase "$(INTDIR)\COMObject.obj"
	-@erase "$(INTDIR)\Component.obj"
	-@erase "$(INTDIR)\ComponentInfo.obj"
	-@erase "$(INTDIR)\COMUtils.obj"
	-@erase "$(INTDIR)\Control.obj"
	-@erase "$(INTDIR)\ControlContainer.obj"
	-@erase "$(INTDIR)\ControlEvent.obj"
	-@erase "$(INTDIR)\ControlGraphicsContext.obj"
	-@erase "$(INTDIR)\CustomControl.obj"
	-@erase "$(INTDIR)\DataType.obj"
	-@erase "$(INTDIR)\DefaultListItem.obj"
	-@erase "$(INTDIR)\DefaultListModel.obj"
	-@erase "$(INTDIR)\DefaultMenuItem.obj"
	-@erase "$(INTDIR)\DefaultPropertyEditors.obj"
	-@erase "$(INTDIR)\DefaultTableCellItem.obj"
	-@erase "$(INTDIR)\DefaultTableModel.obj"
	-@erase "$(INTDIR)\DefaultTabModel.obj"
	-@erase "$(INTDIR)\DefaultTabPage.obj"
	-@erase "$(INTDIR)\DefaultTextModel.obj"
	-@erase "$(INTDIR)\DefaultTreeItem.obj"
	-@erase "$(INTDIR)\DefaultTreeModel.obj"
	-@erase "$(INTDIR)\Desktop.obj"
	-@erase "$(INTDIR)\Dialog.obj"
	-@erase "$(INTDIR)\DragEvent.obj"
	-@erase "$(INTDIR)\DragSource.obj"
	-@erase "$(INTDIR)\DropEvent.obj"
	-@erase "$(INTDIR)\DropTarget.obj"
	-@erase "$(INTDIR)\Frame.obj"
	-@erase "$(INTDIR)\ImageList.obj"
	-@erase "$(INTDIR)\ImageListEvent.obj"
	-@erase "$(INTDIR)\ItemEvent.obj"
	-@erase "$(INTDIR)\KeyboardEvent.obj"
	-@erase "$(INTDIR)\Label.obj"
	-@erase "$(INTDIR)\Light3DBorder.obj"
	-@erase "$(INTDIR)\LightweightComponent.obj"
	-@erase "$(INTDIR)\ListBoxControl.obj"
	-@erase "$(INTDIR)\ListModelEvent.obj"
	-@erase "$(INTDIR)\ListViewControl.obj"
	-@erase "$(INTDIR)\Menu.obj"
	-@erase "$(INTDIR)\MenuBar.obj"
	-@erase "$(INTDIR)\MenuItemEvent.obj"
	-@erase "$(INTDIR)\MenuItemShortcut.obj"
	-@erase "$(INTDIR)\Model.obj"
	-@erase "$(INTDIR)\MouseEvent.obj"
	-@erase "$(INTDIR)\MultilineTextControl.obj"
	-@erase "$(INTDIR)\OpenGLControl.obj"
	-@erase "$(INTDIR)\OpenGLControlContext.obj"
	-@erase "$(INTDIR)\Panel.obj"
	-@erase "$(INTDIR)\PopupMenu.obj"
	-@erase "$(INTDIR)\PropertyEditorManager.obj"
	-@erase "$(INTDIR)\Resource.obj"
	-@erase "$(INTDIR)\ResourceStream.obj"
	-@erase "$(INTDIR)\Splitter.obj"
	-@erase "$(INTDIR)\TabbedPages.obj"
	-@erase "$(INTDIR)\TableControl.obj"
	-@erase "$(INTDIR)\TableModelEvent.obj"
	-@erase "$(INTDIR)\TabModelEvent.obj"
	-@erase "$(INTDIR)\TextControl.obj"
	-@erase "$(INTDIR)\TextEvent.obj"
	-@erase "$(INTDIR)\Toolbar.obj"
	-@erase "$(INTDIR)\ToolbarButton.obj"
	-@erase "$(INTDIR)\ToolbarDock.obj"
	-@erase "$(INTDIR)\ToolbarSeparator.obj"
	-@erase "$(INTDIR)\TreeControl.obj"
	-@erase "$(INTDIR)\TreeListControl.obj"
	-@erase "$(INTDIR)\TreeModelEvent.obj"
	-@erase "$(INTDIR)\UIToolkit.obj"
	-@erase "$(INTDIR)\UndoRedoEvent.obj"
	-@erase "$(INTDIR)\UndoRedoStack.obj"
	-@erase "$(INTDIR)\ValidationEvent.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\VFFInputStream.obj"
	-@erase "$(INTDIR)\VFFOutputStream.obj"
	-@erase "$(INTDIR)\Win32Application.obj"
	-@erase "$(INTDIR)\Win32Button.obj"
	-@erase "$(INTDIR)\Win32ColorDialog.obj"
	-@erase "$(INTDIR)\Win32ComboBox.obj"
	-@erase "$(INTDIR)\Win32Component.obj"
	-@erase "$(INTDIR)\Win32ControlContext.obj"
	-@erase "$(INTDIR)\Win32CustomControl.obj"
	-@erase "$(INTDIR)\Win32Desktop.obj"
	-@erase "$(INTDIR)\Win32Dialog.obj"
	-@erase "$(INTDIR)\Win32DropTargetPeer.obj"
	-@erase "$(INTDIR)\Win32Edit.obj"
	-@erase "$(INTDIR)\Win32FileOpenDialog.obj"
	-@erase "$(INTDIR)\Win32FileSaveDialog.obj"
	-@erase "$(INTDIR)\Win32FolderBrowseDialog.obj"
	-@erase "$(INTDIR)\Win32FontDialog.obj"
	-@erase "$(INTDIR)\Win32ListBox.obj"
	-@erase "$(INTDIR)\Win32Listview.obj"
	-@erase "$(INTDIR)\Win32MenuBar.obj"
	-@erase "$(INTDIR)\Win32MenuItem.obj"
	-@erase "$(INTDIR)\Win32Object.obj"
	-@erase "$(INTDIR)\Win32PopupMenu.obj"
	-@erase "$(INTDIR)\Win32ResourceBundle.obj"
	-@erase "$(INTDIR)\Win32ResourceStream.obj"
	-@erase "$(INTDIR)\Win32ToolKit.obj"
	-@erase "$(INTDIR)\Win32Tree.obj"
	-@erase "$(INTDIR)\Win32Window.obj"
	-@erase "$(INTDIR)\Window.obj"
	-@erase "$(INTDIR)\WindowEvent.obj"
	-@erase "$(OUTDIR)\ApplicationKit_sd.lib"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\COM" /I "..\..\..\include\Core" /I "..\..\..\include\Graphics" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\Implementer" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\DragDrop" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\ApplicationKit.pch" /Yu"ApplicationKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

RSC=rc.exe
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ApplicationKit.bsc" 
BSC32_SBRS= \
	
LIB32=link.exe -lib
LIB32_FLAGS=/nologo /out:"$(OUTDIR)\ApplicationKit_sd.lib" 
LIB32_OBJS= \
	"$(INTDIR)\AbstractCommand.obj" \
	"$(INTDIR)\AbstractContainer.obj" \
	"$(INTDIR)\AbstractListModel.obj" \
	"$(INTDIR)\AbstractTableModel.obj" \
	"$(INTDIR)\AbstractTextModel.obj" \
	"$(INTDIR)\AbstractTreeModel.obj" \
	"$(INTDIR)\AbstractWin32Component.obj" \
	"$(INTDIR)\Application.obj" \
	"$(INTDIR)\ApplicationKit.obj" \
	"$(INTDIR)\Basic3DBorder.obj" \
	"$(INTDIR)\BasicTableItemEditor.obj" \
	"$(INTDIR)\ButtonEvent.obj" \
	"$(INTDIR)\CheckBoxControl.obj" \
	"$(INTDIR)\Clipboard.obj" \
	"$(INTDIR)\ClipboardDataObject.obj" \
	"$(INTDIR)\ClipboardEvent.obj" \
	"$(INTDIR)\ComboBoxControl.obj" \
	"$(INTDIR)\COMDataObject.obj" \
	"$(INTDIR)\COMDropTarget.obj" \
	"$(INTDIR)\CommandButton.obj" \
	"$(INTDIR)\CommandGroup.obj" \
	"$(INTDIR)\CommonColor.obj" \
	"$(INTDIR)\CommonFileBrowse.obj" \
	"$(INTDIR)\CommonFileDialog.obj" \
	"$(INTDIR)\CommonFileOpen.obj" \
	"$(INTDIR)\CommonFileSave.obj" \
	"$(INTDIR)\CommonFont.obj" \
	"$(INTDIR)\CommonPrint.obj" \
	"$(INTDIR)\COMObject.obj" \
	"$(INTDIR)\Component.obj" \
	"$(INTDIR)\ComponentInfo.obj" \
	"$(INTDIR)\COMUtils.obj" \
	"$(INTDIR)\Control.obj" \
	"$(INTDIR)\ControlContainer.obj" \
	"$(INTDIR)\ControlEvent.obj" \
	"$(INTDIR)\ControlGraphicsContext.obj" \
	"$(INTDIR)\CustomControl.obj" \
	"$(INTDIR)\DataType.obj" \
	"$(INTDIR)\DefaultListItem.obj" \
	"$(INTDIR)\DefaultListModel.obj" \
	"$(INTDIR)\DefaultMenuItem.obj" \
	"$(INTDIR)\DefaultPropertyEditors.obj" \
	"$(INTDIR)\DefaultTableCellItem.obj" \
	"$(INTDIR)\DefaultTableModel.obj" \
	"$(INTDIR)\DefaultTabModel.obj" \
	"$(INTDIR)\DefaultTabPage.obj" \
	"$(INTDIR)\DefaultTextModel.obj" \
	"$(INTDIR)\DefaultTreeItem.obj" \
	"$(INTDIR)\DefaultTreeModel.obj" \
	"$(INTDIR)\Desktop.obj" \
	"$(INTDIR)\Dialog.obj" \
	"$(INTDIR)\DragEvent.obj" \
	"$(INTDIR)\DragSource.obj" \
	"$(INTDIR)\DropEvent.obj" \
	"$(INTDIR)\DropTarget.obj" \
	"$(INTDIR)\Frame.obj" \
	"$(INTDIR)\ImageList.obj" \
	"$(INTDIR)\ImageListEvent.obj" \
	"$(INTDIR)\ItemEvent.obj" \
	"$(INTDIR)\KeyboardEvent.obj" \
	"$(INTDIR)\Label.obj" \
	"$(INTDIR)\Light3DBorder.obj" \
	"$(INTDIR)\LightweightComponent.obj" \
	"$(INTDIR)\ListBoxControl.obj" \
	"$(INTDIR)\ListModelEvent.obj" \
	"$(INTDIR)\ListViewControl.obj" \
	"$(INTDIR)\Menu.obj" \
	"$(INTDIR)\MenuBar.obj" \
	"$(INTDIR)\MenuItemEvent.obj" \
	"$(INTDIR)\MenuItemShortcut.obj" \
	"$(INTDIR)\Model.obj" \
	"$(INTDIR)\MouseEvent.obj" \
	"$(INTDIR)\MultilineTextControl.obj" \
	"$(INTDIR)\OpenGLControl.obj" \
	"$(INTDIR)\OpenGLControlContext.obj" \
	"$(INTDIR)\Panel.obj" \
	"$(INTDIR)\PopupMenu.obj" \
	"$(INTDIR)\PropertyEditorManager.obj" \
	"$(INTDIR)\Resource.obj" \
	"$(INTDIR)\ResourceStream.obj" \
	"$(INTDIR)\Splitter.obj" \
	"$(INTDIR)\TabbedPages.obj" \
	"$(INTDIR)\TableControl.obj" \
	"$(INTDIR)\TableModelEvent.obj" \
	"$(INTDIR)\TabModelEvent.obj" \
	"$(INTDIR)\TextControl.obj" \
	"$(INTDIR)\TextEvent.obj" \
	"$(INTDIR)\Toolbar.obj" \
	"$(INTDIR)\ToolbarButton.obj" \
	"$(INTDIR)\ToolbarDock.obj" \
	"$(INTDIR)\ToolbarSeparator.obj" \
	"$(INTDIR)\TreeControl.obj" \
	"$(INTDIR)\TreeListControl.obj" \
	"$(INTDIR)\TreeModelEvent.obj" \
	"$(INTDIR)\UIToolkit.obj" \
	"$(INTDIR)\UndoRedoEvent.obj" \
	"$(INTDIR)\UndoRedoStack.obj" \
	"$(INTDIR)\ValidationEvent.obj" \
	"$(INTDIR)\VFFInputStream.obj" \
	"$(INTDIR)\VFFOutputStream.obj" \
	"$(INTDIR)\Win32Application.obj" \
	"$(INTDIR)\Win32Button.obj" \
	"$(INTDIR)\Win32ColorDialog.obj" \
	"$(INTDIR)\Win32ComboBox.obj" \
	"$(INTDIR)\Win32Component.obj" \
	"$(INTDIR)\Win32ControlContext.obj" \
	"$(INTDIR)\Win32CustomControl.obj" \
	"$(INTDIR)\Win32Desktop.obj" \
	"$(INTDIR)\Win32Dialog.obj" \
	"$(INTDIR)\Win32DropTargetPeer.obj" \
	"$(INTDIR)\Win32Edit.obj" \
	"$(INTDIR)\Win32FileOpenDialog.obj" \
	"$(INTDIR)\Win32FileSaveDialog.obj" \
	"$(INTDIR)\Win32FolderBrowseDialog.obj" \
	"$(INTDIR)\Win32FontDialog.obj" \
	"$(INTDIR)\Win32ListBox.obj" \
	"$(INTDIR)\Win32Listview.obj" \
	"$(INTDIR)\Win32MenuBar.obj" \
	"$(INTDIR)\Win32MenuItem.obj" \
	"$(INTDIR)\Win32Object.obj" \
	"$(INTDIR)\Win32PopupMenu.obj" \
	"$(INTDIR)\Win32ResourceBundle.obj" \
	"$(INTDIR)\Win32ResourceStream.obj" \
	"$(INTDIR)\Win32ToolKit.obj" \
	"$(INTDIR)\Win32Tree.obj" \
	"$(INTDIR)\Win32Window.obj" \
	"$(INTDIR)\Window.obj" \
	"$(INTDIR)\WindowEvent.obj" \
	"$(OUTDIR)\FoundationKit_sd.lib" \
	"$(OUTDIR)\GraphicsKit_sd.lib"

"$(OUTDIR)\ApplicationKit_sd.lib" : "$(OUTDIR)" $(DEF_FILE) $(LIB32_OBJS)
    $(LIB32) @<<
  $(LIB32_FLAGS) $(DEF_FLAGS) $(LIB32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("ApplicationKit.dep")
!INCLUDE "ApplicationKit.dep"
!ELSE 
!MESSAGE Warning: cannot find "ApplicationKit.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "ApplicationKit - Win32 Release" || "$(CFG)" == "ApplicationKit - Win32 Debug"
SOURCE=..\..\..\src\core\AbstractCommand.cpp

"$(INTDIR)\AbstractCommand.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\AbstractContainer.cpp

"$(INTDIR)\AbstractContainer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\AbstractListModel.cpp

"$(INTDIR)\AbstractListModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\AbstractTableModel.cpp

"$(INTDIR)\AbstractTableModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\AbstractTextModel.cpp

"$(INTDIR)\AbstractTextModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\AbstractTreeModel.cpp

"$(INTDIR)\AbstractTreeModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\AbstractWin32Component.cpp

"$(INTDIR)\AbstractWin32Component.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Application.cpp

"$(INTDIR)\Application.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ApplicationKit.cpp

!IF  "$(CFG)" == "ApplicationKit - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GR /GX /O2 /I "..\..\..\include\COM" /I "..\..\..\include\Core" /I "..\..\..\include\Graphics" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\Implementer" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\DragDrop" /I "..\..\..\xml\include" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\ApplicationKit.pch" /Yc"ApplicationKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\ApplicationKit.obj"	"$(INTDIR)\ApplicationKit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ApplicationKit - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "..\..\..\include\COM" /I "..\..\..\include\Core" /I "..\..\..\include\Graphics" /I "..\..\..\include\Events" /I "..\..\..\include\Exceptions" /I "..\..\..\include\io" /I "..\..\..\include\Utils" /I "..\..\..\include\Implementer" /I "..\..\..\include\ImplementerKit" /I "..\..\..\include\DragDrop" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /Fp"$(INTDIR)\ApplicationKit.pch" /Yc"ApplicationKit.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ /c 

"$(INTDIR)\ApplicationKit.obj"	"$(INTDIR)\ApplicationKit.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=..\..\..\src\Graphics\Basic3DBorder.cpp

"$(INTDIR)\Basic3DBorder.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\BasicTableItemEditor.cpp

"$(INTDIR)\BasicTableItemEditor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ButtonEvent.cpp

"$(INTDIR)\ButtonEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CheckBoxControl.cpp

"$(INTDIR)\CheckBoxControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\DragDrop\Clipboard.cpp

"$(INTDIR)\Clipboard.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\DragDrop\ClipboardDataObject.cpp

"$(INTDIR)\ClipboardDataObject.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\DragDrop\ClipboardEvent.cpp

"$(INTDIR)\ClipboardEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ComboBoxControl.cpp

"$(INTDIR)\ComboBoxControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\COM\COMDataObject.cpp

"$(INTDIR)\COMDataObject.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\COM\COMDropTarget.cpp

"$(INTDIR)\COMDropTarget.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CommandButton.cpp

"$(INTDIR)\CommandButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CommandGroup.cpp

"$(INTDIR)\CommandGroup.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CommonColor.cpp

"$(INTDIR)\CommonColor.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CommonFileBrowse.cpp

"$(INTDIR)\CommonFileBrowse.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CommonFileDialog.cpp

"$(INTDIR)\CommonFileDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CommonFileOpen.cpp

"$(INTDIR)\CommonFileOpen.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CommonFileSave.cpp

"$(INTDIR)\CommonFileSave.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CommonFont.cpp

"$(INTDIR)\CommonFont.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CommonPrint.cpp

"$(INTDIR)\CommonPrint.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\COM\COMObject.cpp

"$(INTDIR)\COMObject.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Component.cpp

"$(INTDIR)\Component.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ComponentInfo.cpp

"$(INTDIR)\ComponentInfo.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\COM\COMUtils.cpp

"$(INTDIR)\COMUtils.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Control.cpp

"$(INTDIR)\Control.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ControlContainer.cpp

"$(INTDIR)\ControlContainer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ControlEvent.cpp

"$(INTDIR)\ControlEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\ControlGraphicsContext.cpp

"$(INTDIR)\ControlGraphicsContext.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\CustomControl.cpp

"$(INTDIR)\CustomControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\DragDrop\DataType.cpp

"$(INTDIR)\DataType.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultListItem.cpp

"$(INTDIR)\DefaultListItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultListModel.cpp

"$(INTDIR)\DefaultListModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultMenuItem.cpp

"$(INTDIR)\DefaultMenuItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultPropertyEditors.cpp

"$(INTDIR)\DefaultPropertyEditors.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultTableCellItem.cpp

"$(INTDIR)\DefaultTableCellItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultTableModel.cpp

"$(INTDIR)\DefaultTableModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultTabModel.cpp

"$(INTDIR)\DefaultTabModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultTabPage.cpp

"$(INTDIR)\DefaultTabPage.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultTextModel.cpp

"$(INTDIR)\DefaultTextModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultTreeItem.cpp

"$(INTDIR)\DefaultTreeItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\DefaultTreeModel.cpp

"$(INTDIR)\DefaultTreeModel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Desktop.cpp

"$(INTDIR)\Desktop.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Dialog.cpp

"$(INTDIR)\Dialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\DragDrop\DragEvent.cpp

"$(INTDIR)\DragEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\DragDrop\DragSource.cpp

"$(INTDIR)\DragSource.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\DragDrop\DropEvent.cpp

"$(INTDIR)\DropEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\DragDrop\DropTarget.cpp

"$(INTDIR)\DropTarget.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Frame.cpp

"$(INTDIR)\Frame.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\ImageList.cpp

"$(INTDIR)\ImageList.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ImageListEvent.cpp

"$(INTDIR)\ImageListEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ItemEvent.cpp

"$(INTDIR)\ItemEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\KeyboardEvent.cpp

"$(INTDIR)\KeyboardEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Label.cpp

"$(INTDIR)\Label.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\Light3DBorder.cpp

"$(INTDIR)\Light3DBorder.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\LightweightComponent.cpp

"$(INTDIR)\LightweightComponent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ListBoxControl.cpp

"$(INTDIR)\ListBoxControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ListModelEvent.cpp

"$(INTDIR)\ListModelEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ListViewControl.cpp

"$(INTDIR)\ListViewControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Menu.cpp

"$(INTDIR)\Menu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\MenuBar.cpp

"$(INTDIR)\MenuBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\MenuItemEvent.cpp

"$(INTDIR)\MenuItemEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\MenuItemShortcut.cpp

"$(INTDIR)\MenuItemShortcut.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Model.cpp

"$(INTDIR)\Model.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\MouseEvent.cpp

"$(INTDIR)\MouseEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\MultilineTextControl.cpp

"$(INTDIR)\MultilineTextControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\OpenGLControl.cpp

"$(INTDIR)\OpenGLControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Graphics\OpenGLControlContext.cpp

"$(INTDIR)\OpenGLControlContext.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Panel.cpp

"$(INTDIR)\Panel.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\PopupMenu.cpp

"$(INTDIR)\PopupMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\PropertyEditorManager.cpp

"$(INTDIR)\PropertyEditorManager.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\Resource.cpp

"$(INTDIR)\Resource.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\ResourceStream.cpp

"$(INTDIR)\ResourceStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Splitter.cpp

"$(INTDIR)\Splitter.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\TabbedPages.cpp

"$(INTDIR)\TabbedPages.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\TableControl.cpp

"$(INTDIR)\TableControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\TableModelEvent.cpp

"$(INTDIR)\TableModelEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\TabModelEvent.cpp

"$(INTDIR)\TabModelEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\TextControl.cpp

"$(INTDIR)\TextControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\TextEvent.cpp

"$(INTDIR)\TextEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Toolbar.cpp

"$(INTDIR)\Toolbar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ToolbarButton.cpp

"$(INTDIR)\ToolbarButton.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ToolbarDock.cpp

"$(INTDIR)\ToolbarDock.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\ToolbarSeparator.cpp

"$(INTDIR)\ToolbarSeparator.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\TreeControl.cpp

"$(INTDIR)\TreeControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\TreeListControl.cpp

"$(INTDIR)\TreeListControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\TreeModelEvent.cpp

"$(INTDIR)\TreeModelEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Utils\UIToolkit.cpp

"$(INTDIR)\UIToolkit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\UndoRedoEvent.cpp

"$(INTDIR)\UndoRedoEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\UndoRedoStack.cpp

"$(INTDIR)\UndoRedoStack.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\ValidationEvent.cpp

"$(INTDIR)\ValidationEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\VFFInputStream.cpp

"$(INTDIR)\VFFInputStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\IO\VFFOutputStream.cpp

"$(INTDIR)\VFFOutputStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Application.cpp

"$(INTDIR)\Win32Application.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Button.cpp

"$(INTDIR)\Win32Button.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32ColorDialog.cpp

"$(INTDIR)\Win32ColorDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32ComboBox.cpp

"$(INTDIR)\Win32ComboBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Component.cpp

"$(INTDIR)\Win32Component.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32ControlContext.cpp

"$(INTDIR)\Win32ControlContext.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32CustomControl.cpp

"$(INTDIR)\Win32CustomControl.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Desktop.cpp

"$(INTDIR)\Win32Desktop.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Dialog.cpp

"$(INTDIR)\Win32Dialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32DropTargetPeer.cpp

"$(INTDIR)\Win32DropTargetPeer.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Edit.cpp

"$(INTDIR)\Win32Edit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32FileOpenDialog.cpp

"$(INTDIR)\Win32FileOpenDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32FileSaveDialog.cpp

"$(INTDIR)\Win32FileSaveDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32FolderBrowseDialog.cpp

"$(INTDIR)\Win32FolderBrowseDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32FontDialog.cpp

"$(INTDIR)\Win32FontDialog.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32ListBox.cpp

"$(INTDIR)\Win32ListBox.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Listview.cpp

"$(INTDIR)\Win32Listview.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32MenuBar.cpp

"$(INTDIR)\Win32MenuBar.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32MenuItem.cpp

"$(INTDIR)\Win32MenuItem.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Object.cpp

"$(INTDIR)\Win32Object.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32PopupMenu.cpp

"$(INTDIR)\Win32PopupMenu.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32ResourceBundle.cpp

"$(INTDIR)\Win32ResourceBundle.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32ResourceStream.cpp

"$(INTDIR)\Win32ResourceStream.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32ToolKit.cpp

"$(INTDIR)\Win32ToolKit.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Tree.cpp

"$(INTDIR)\Win32Tree.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\ImplementerKit\Win32Window.cpp

"$(INTDIR)\Win32Window.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\core\Window.cpp

"$(INTDIR)\Window.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=..\..\..\src\Events\WindowEvent.cpp

"$(INTDIR)\WindowEvent.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\ApplicationKit.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


!IF  "$(CFG)" == "ApplicationKit - Win32 Release"

"FoundationKit - Win32 Release" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" 
   cd "..\ApplicationKit"

"FoundationKit - Win32 ReleaseCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Release" RECURSE=1 CLEAN 
   cd "..\ApplicationKit"

!ELSEIF  "$(CFG)" == "ApplicationKit - Win32 Debug"

"FoundationKit - Win32 Debug" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" 
   cd "..\ApplicationKit"

"FoundationKit - Win32 DebugCLEAN" : 
   cd "\code\vcf\build\vc60\FoundationKit"
   $(MAKE) /$(MAKEFLAGS) /F .\FoundationKit.mak CFG="FoundationKit - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\ApplicationKit"

!ENDIF 

!IF  "$(CFG)" == "ApplicationKit - Win32 Release"

"GraphicsKit - Win32 Release" : 
   cd "\code\vcf\build\vc60\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKit.mak CFG="GraphicsKit - Win32 Release" 
   cd "..\ApplicationKit"

"GraphicsKit - Win32 ReleaseCLEAN" : 
   cd "\code\vcf\build\vc60\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKit.mak CFG="GraphicsKit - Win32 Release" RECURSE=1 CLEAN 
   cd "..\ApplicationKit"

!ELSEIF  "$(CFG)" == "ApplicationKit - Win32 Debug"

"GraphicsKit - Win32 Debug" : 
   cd "\code\vcf\build\vc60\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKit.mak CFG="GraphicsKit - Win32 Debug" 
   cd "..\ApplicationKit"

"GraphicsKit - Win32 DebugCLEAN" : 
   cd "\code\vcf\build\vc60\GraphicsKit"
   $(MAKE) /$(MAKEFLAGS) /F .\GraphicsKit.mak CFG="GraphicsKit - Win32 Debug" RECURSE=1 CLEAN 
   cd "..\ApplicationKit"

!ENDIF 


!ENDIF 

