#######################################################
# MAKEFILE for building ApplicationKit_bcc_s(d).lib   #
#                   and ApplicationKit_bcc_(d).dll    #
#                                                     #
# (c) 2004 by Darko Miletic                           #
# e-mail: kiklop@fibertel.com.ar                      # 
#######################################################
.autodepend

!ifndef BMODE
BMODE = RELEASE
!endif

!ifndef TARGET
TARGET = LIB
!endif

!if $(BMODE) != RELEASE && $(BMODE) != DEBUG
!  error Illegal value for BMODE option
!endif

!if $(TARGET) != LIB && $(TARGET) != DLL
!  error Illegal value for TARGET option
!endif

!include <..\defaultmake.inc>

!if $(TARGET) == LIB
PROJECT=$(PROJECT1)
TDIR=S
OUTDIR=..\..\..\lib
SYSDEFINES=_LIB;USE_FOUNDATIONKIT_LIB;USE_GRAPHICSKIT_LIB;USE_WIN32HTMLBROWSER_LIB
!else
PROJECT=$(RESFILE) $(PROJECT2)
TDIR=DLL
OUTDIR=..\..\..\bin
SYSDEFINES=_WINDOWS;_USRDLL;USE_FOUNDATIONKIT_DLL;USE_GRAPHICSKIT_DLL;APPLICATIONKIT_DLL;APPLICATIONKIT_EXPORTS
!endif

!if $(BMODE) == RELEASE
	USERDEFINES=NDEBUG
	OBJDIR=bcc\Release$(TDIR)
	LPARAM=/P2048
	!message Building release version of project
!else
	USERDEFINES=_DEBUG
	OBJDIR=bcc\Debug$(TDIR)
	LPARAM=/P4096
	!message Building debug version of project
!endif

      
LIBNAME=ApplicationKit_bcc_s$(DBG).lib
DLLNAME=ApplicationKit_bcc$(DBGDLL).dll
INCDIR=..\..\..\src
LIBDIR=..\..\..\lib;$(MAKEDIR)\..\Lib\PSDK
SRC=..\..\..\src\vcf\ApplicationKit
RESSRC=..\..\resources\win32
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
SYSDEFINES=STRICT;_MBCS;WIN32;NO_MFC;BUILD_APPLICATIONKIT_LIB;$(SYSDEFINES)
RFLAGS=$(RFLAGS) /l0x409 -d_DEBUG
.path.cpp=$(SRC)
.path.obj=$(OBJ)         
.path.res=$(OBJ)
.path.rc=$(RESSRC)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
RESSRCFILE=ApplicationKit.rc
CPPFILES=AbstractApplication.cpp \
	AbstractCommand.cpp \
	AbstractComponentEditor.cpp \
	AbstractContainer.cpp \
	AbstractPropertyEditor.cpp \
	AbstractScrollable.cpp \
	AcceleratorKey.cpp \
	Action.cpp \
	Application.cpp \
	ApplicationKit.cpp \
	Basic3DBorder.cpp \
	BasicTableItemEditor.cpp \
	Clipboard.cpp \
	ColorEtchedBorder.cpp \
	CommandGroup.cpp \
	CommonColor.cpp \
	CommonFileBrowse.cpp \
	CommonFileDialog.cpp \
	CommonFileOpen.cpp \
	CommonFileSave.cpp \
	CommonFont.cpp \
	CommonPrint.cpp \
	Component.cpp \
	ComponentEditorManager.cpp \
	ComponentInfo.cpp \
	Containers.cpp \
	Control.cpp \
	ControlGraphicsContext.cpp \
	Cursor.cpp \
	CursorManager.cpp \
	DataObject.cpp \
	DefaultPropertyEditors.cpp \
	Desktop.cpp \
	Dialog.cpp \
	DragSource.cpp \
	DropTarget.cpp \
	EtchedBorder.cpp \
	Frame.cpp \
	ImageList.cpp \
	ImageListEvent.cpp \
	KeyboardEvent.cpp \
	LibraryApplication.cpp \
	Light3DBorder.cpp \
	LightweightComponent.cpp \	
	Menu.cpp \
	MenuBar.cpp \
	MessageDialog.cpp \
	MultilineTextControl.cpp \
	PopupMenu.cpp \
	PropertyEditorManager.cpp \
	TitledBorder.cpp \
	UIToolkit.cpp \
	UndoRedoStack.cpp \
	VFFInputStream.cpp \
	VFFOutputStream.cpp \
	Win32PrintDialog.cpp \
	Window.cpp \
	WindowEvent.cpp \
	AbstractWin32Component.cpp \
	COMDataObject.cpp \
	COMUtils.cpp \
	Win32Application.cpp \
	Win32Button.cpp \
	Win32Clipboard.cpp \
	Win32ColorDialog.cpp \
	Win32Component.cpp \
	Win32ControlContext.cpp \
	Win32CursorPeer.cpp \
	Win32Desktop.cpp \
	Win32Dialog.cpp \
	Win32DragDropPeer.cpp \
	Win32DropTargetPeer.cpp \
	Win32Edit.cpp \
	Win32FileOpenDialog.cpp \
	Win32FileSaveDialog.cpp \
	Win32FolderBrowseDialog.cpp \
	Win32FontDialog.cpp \
	Win32Listview.cpp \
	Win32MenuBar.cpp \
	Win32MenuItem.cpp \
	Win32Object.cpp \
	Win32PopupMenu.cpp \
	Win32ScrollPeer.cpp \
	Win32SystemTrayPeer.cpp \
	Win32Toolbar.cpp \
	Win32ToolKit.cpp \
	Win32Tree.cpp \
	Win32Window.cpp \	
	ButtonEvent.cpp \
	ClipboardEvent.cpp \
	ColumnItemEvent.cpp \
	ColumnModelEvent.cpp \
	ControlEvent.cpp \
	FocusEvent.cpp \
	HelpEvent.cpp \
	ItemEvent.cpp \
	ListModelEvent.cpp \
	MenuItemEvent.cpp \
	MouseEvent.cpp \
	TabModelEvent.cpp \
	TextEvent.cpp \
	TimerEvent.cpp \
	ToolTipEvent.cpp \
	TreeModelEvent.cpp \
	UndoRedoEvent.cpp \
	ValidationEvent.cpp \
	WhatsThisHelpEvent.cpp \
	AbstractListModel.cpp \
	AbstractTextModel.cpp \
	AbstractTreeModel.cpp \
	AbstractView.cpp \
	DefaultColumnItem.cpp \
	DefaultColumnModel.cpp \
	DefaultListItem.cpp \
	DefaultListModel.cpp \
	DefaultMenuItem.cpp \
	DefaultTableCellItem.cpp \
	DefaultTableModel.cpp \
	DefaultTabModel.cpp \
	DefaultTabPage.cpp \
	DefaultTextModel.cpp \
	DefaultTreeItem.cpp \
	DefaultTreeModel.cpp \
	DocumentManager.cpp \
	Model.cpp \
	CheckBoxControl.cpp \
	ComboBoxControl.cpp \
	CommandButton.cpp \
	ControlContainer.cpp \
	CustomControl.cpp \
	HeaderControl.cpp \
	HTMLBrowserControl.cpp \
	ImageControl.cpp \
	Label.cpp \
	ListBoxControl.cpp \
	ListViewControl.cpp \
	Panel.cpp \
	ProgressControl.cpp \
	PushButton.cpp \
	RadioButtonControl.cpp \
	ScrollbarManager.cpp \
	SliderControl.cpp \
	Splitter.cpp \
	StatusBar.cpp \
	SystemTray.cpp \
	TabbedPages.cpp \
	TableControl.cpp \
	TextControl.cpp \
	TimerComponent.cpp \
	ToggledButton.cpp \
	Toolbar.cpp \
	ToolbarDock.cpp \
	TreeControl.cpp \
	TreeListControl.cpp

RESFILE=$(RESSRCFILE:.rc=.res^ )
OBJFILES=$(CPPFILES:.cpp=.obj^ )

LIBFILES=comsupp.lib comctl32.lib
DEFFILE=
BCC32STARTUP=c0d32.obj
ALLOBJS=$(BCC32STARTUP) $(OBJFILES)
ALLLIBS=$(LIBFILES) import32.lib $(BCC32RTLIB)

all: dirs $(PROJECT)

cleanobj:: 
	-@echo Deleting intermediate files for project
	-@if exist $(OBJ)\*.obj del $(OBJ)\*.obj
	-@if exist $(OBJ)\*.res del $(OBJ)\*.res
	-@if exist $(OBJ)\. rd $(OBJ)
!if $(BMODE) == RELEASE
	-@if exist $(BIN)\*.tds del $(BIN)\*.tds
	-@if exist $(BIN)\*.map del $(BIN)\*.map
!endif

cleantgt::
	-@echo Deleting output files for project
	-@if exist $(PROJECT1) del $(PROJECT1)
	-@if exist $(PROJECT2) del $(PROJECT2)
	-@if exist ..\..\..\lib\ApplicationKit_bcc$(DBGDLL).lib del ..\..\..\lib\ApplicationKit_bcc$(DBGDLL).lib

clean: cleanobj cleantgt

dirs::
	-@echo Creating output directory
	-@if not exist .\bcc md bcc
	-@if not exist $(OBJ) md $(OBJ)
	-@if not exist $(BIN) md $(BIN)
	

##################################
# Output
##################################
$(PROJECT1):: $(OBJFILES)
   @echo Linking $(<F) static library
   @$(LB) @&&|
   $< $(LPARAM) &
   -+$(?: = &^
   -+)
   
| > NUL:

$(PROJECT2):: $(OBJFILES)
    @echo Linking $(<F) dynamic library
    @$(ILINK32) @&&|
    $(LINKFLAGS) $(ALLOBJS) 
    $<,$*
    $(ALLLIBS)
    $(DEFFILE)
    $(RESFILE)

|
    @if exist ..\..\..\lib\ApplicationKit_bcc$(DBGDLL).lib del ..\..\..\lib\ApplicationKit_bcc$(DBGDLL).lib
    @if exist $(BIN)\ApplicationKit_bcc$(DBGDLL).lib move $(BIN)\ApplicationKit_bcc$(DBGDLL).lib ..\..\..\lib
