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
PROJECT=$(PROJECT2)
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
SRC=
OBJ=.\$(OBJDIR)
BIN=.\$(OUTDIR)
RESFILE=$(OBJ)\ApplicationKit.res
SYSDEFINES=STRICT;_MBCS;WIN32;NO_MFC;BUILD_APPLICATIONKIT_LIB;$(SYSDEFINES)

################################
# Target
################################
PROJECT1=$(BIN)\$(LIBNAME)
PROJECT2=$(BIN)\$(DLLNAME)
OBJFILES=$(OBJ)\AbstractApplication.obj  \
	$(OBJ)\AbstractCommand.obj  \
	$(OBJ)\AbstractComponentEditor.obj  \
	$(OBJ)\AbstractContainer.obj  \
	$(OBJ)\AbstractPropertyEditor.obj  \
	$(OBJ)\AbstractScrollable.obj  \
	$(OBJ)\AcceleratorKey.obj  \
	$(OBJ)\Action.obj  \
	$(OBJ)\Application.obj  \
	$(OBJ)\ApplicationKit.obj  \
	$(OBJ)\Basic3DBorder.obj  \
	$(OBJ)\BasicTableItemEditor.obj  \
	$(OBJ)\Clipboard.obj  \
	$(OBJ)\ColorEtchedBorder.obj  \
	$(OBJ)\CommandGroup.obj  \
	$(OBJ)\CommonColor.obj  \
	$(OBJ)\CommonFileBrowse.obj  \
	$(OBJ)\CommonFileDialog.obj  \
	$(OBJ)\CommonFileOpen.obj  \
	$(OBJ)\CommonFileSave.obj  \
	$(OBJ)\CommonFont.obj  \
	$(OBJ)\CommonPrint.obj  \
	$(OBJ)\Component.obj  \
	$(OBJ)\ComponentEditorManager.obj  \
	$(OBJ)\ComponentInfo.obj  \
	$(OBJ)\Containers.obj  \
	$(OBJ)\Control.obj  \
	$(OBJ)\ControlGraphicsContext.obj  \
	$(OBJ)\Cursor.obj  \
	$(OBJ)\CursorManager.obj  \
	$(OBJ)\DataObject.obj  \
	$(OBJ)\DefaultPropertyEditors.obj  \
	$(OBJ)\Desktop.obj  \
	$(OBJ)\Dialog.obj  \
	$(OBJ)\DragSource.obj  \
	$(OBJ)\DropTarget.obj  \
	$(OBJ)\EtchedBorder.obj  \
	$(OBJ)\Frame.obj  \
	$(OBJ)\ImageList.obj  \
	$(OBJ)\ImageListEvent.obj  \
	$(OBJ)\KeyboardEvent.obj  \
	$(OBJ)\LibraryApplication.obj  \
	$(OBJ)\Light3DBorder.obj  \
	$(OBJ)\LightweightComponent.obj
	
OBJFILES2=$(OBJ)\Menu.obj  \
	$(OBJ)\MenuBar.obj  \
	$(OBJ)\MessageDialog.obj  \
	$(OBJ)\MultilineTextControl.obj  \
	$(OBJ)\PopupMenu.obj  \
	$(OBJ)\PropertyEditorManager.obj  \
	$(OBJ)\Resource.obj  \
	$(OBJ)\ResourceStream.obj  \
	$(OBJ)\TitledBorder.obj  \
	$(OBJ)\UIToolkit.obj  \
	$(OBJ)\UndoRedoStack.obj  \
	$(OBJ)\VFFInputStream.obj  \
	$(OBJ)\VFFOutputStream.obj  \
	$(OBJ)\Window.obj  \
	$(OBJ)\WindowEvent.obj  \
	$(OBJ)\AbstractWin32Component.obj  \
	$(OBJ)\COMDataObject.obj  \
	$(OBJ)\COMUtils.obj  \
	$(OBJ)\Win32Application.obj  \
	$(OBJ)\Win32Button.obj  \
	$(OBJ)\Win32Clipboard.obj  \
	$(OBJ)\Win32ColorDialog.obj  \
	$(OBJ)\Win32Component.obj  \
	$(OBJ)\Win32ControlContext.obj  \
	$(OBJ)\Win32CursorPeer.obj  \
	$(OBJ)\Win32Desktop.obj  \
	$(OBJ)\Win32Dialog.obj  \
	$(OBJ)\Win32DragDropPeer.obj  \
	$(OBJ)\Win32DropTargetPeer.obj  \
	$(OBJ)\Win32Edit.obj  \
	$(OBJ)\Win32FileOpenDialog.obj  \
	$(OBJ)\Win32FileSaveDialog.obj  \
	$(OBJ)\Win32FolderBrowseDialog.obj  \
	$(OBJ)\Win32FontDialog.obj  \
	$(OBJ)\Win32Listview.obj  \
	$(OBJ)\Win32MenuBar.obj  \
	$(OBJ)\Win32MenuItem.obj  \
	$(OBJ)\Win32Object.obj  \
	$(OBJ)\Win32PopupMenu.obj  \
	$(OBJ)\Win32ResourceBundle.obj  \
	$(OBJ)\Win32ResourceStream.obj  \
	$(OBJ)\Win32ScrollPeer.obj  \
	$(OBJ)\Win32Toolbar.obj  \
	$(OBJ)\Win32ToolKit.obj  \
	$(OBJ)\Win32Tree.obj  \
	$(OBJ)\Win32Window.obj
	
OBJFILES3=$(OBJ)\ButtonEvent.obj  \
	$(OBJ)\ClipboardEvent.obj  \
	$(OBJ)\ColumnItemEvent.obj  \
	$(OBJ)\ColumnModelEvent.obj  \
	$(OBJ)\ControlEvent.obj  \
	$(OBJ)\FocusEvent.obj  \
	$(OBJ)\HelpEvent.obj  \
	$(OBJ)\ItemEvent.obj  \
	$(OBJ)\ListModelEvent.obj  \
	$(OBJ)\MenuItemEvent.obj  \
	$(OBJ)\MouseEvent.obj  \
	$(OBJ)\TabModelEvent.obj  \
	$(OBJ)\TextEvent.obj  \
	$(OBJ)\TimerEvent.obj  \
	$(OBJ)\ToolTipEvent.obj  \
	$(OBJ)\TreeModelEvent.obj  \
	$(OBJ)\UndoRedoEvent.obj  \
	$(OBJ)\ValidationEvent.obj  \
	$(OBJ)\WhatsThisHelpEvent.obj  \
	$(OBJ)\AbstractListModel.obj  \
	$(OBJ)\AbstractTextModel.obj  \
	$(OBJ)\AbstractTreeModel.obj  \
	$(OBJ)\AbstractView.obj  \
	$(OBJ)\DefaultColumnItem.obj  \
	$(OBJ)\DefaultColumnModel.obj  \
	$(OBJ)\DefaultListItem.obj  \
	$(OBJ)\DefaultListModel.obj  \
	$(OBJ)\DefaultMenuItem.obj  \
	$(OBJ)\DefaultTableCellItem.obj  \
	$(OBJ)\DefaultTableModel.obj  \
	$(OBJ)\DefaultTabModel.obj  \
	$(OBJ)\DefaultTabPage.obj  \
	$(OBJ)\DefaultTextModel.obj  \
	$(OBJ)\DefaultTreeItem.obj  \
	$(OBJ)\DefaultTreeModel.obj  \
	$(OBJ)\DocumentManager.obj  \
	$(OBJ)\Model.obj  \
	$(OBJ)\CheckBoxControl.obj  \
	$(OBJ)\ComboBoxControl.obj  \
	$(OBJ)\CommandButton.obj  \
	$(OBJ)\ControlContainer.obj  \
	$(OBJ)\CustomControl.obj  \
	$(OBJ)\HeaderControl.obj  \
	$(OBJ)\HTMLBrowserControl.obj  \
	$(OBJ)\ImageControl.obj  \
	$(OBJ)\Label.obj  \
	$(OBJ)\ListBoxControl.obj  \
	$(OBJ)\ListViewControl.obj  \
	$(OBJ)\Panel.obj  \
	$(OBJ)\ProgressControl.obj  \
	$(OBJ)\PushButton.obj  \
	$(OBJ)\RadioButtonControl.obj  \
	$(OBJ)\ScrollbarManager.obj  \
	$(OBJ)\SliderControl.obj  \
	$(OBJ)\Splitter.obj  \
	$(OBJ)\StatusBar.obj  \
	$(OBJ)\TabbedPages.obj  \
	$(OBJ)\TableControl.obj  \
	$(OBJ)\TextControl.obj  \
	$(OBJ)\TimerComponent.obj  \
	$(OBJ)\ToggledButton.obj  \
	$(OBJ)\Toolbar.obj  \
	$(OBJ)\ToolbarDock.obj  \
	$(OBJ)\TreeControl.obj  \
	$(OBJ)\TreeListControl.obj 
         
LIBFILES=comsupp.lib comctl32.lib
DEFFILE=
ALLOBJS=$(OBJFILES) $(OBJFILES2) $(OBJFILES3)
BCC32STARTUP=c0d32.obj
ALLOBJS2=$(BCC32STARTUP) $(ALLOBJS)
ALLLIBS2=$(LIBFILES) import32.lib $(BCC32RTLIB)

all: dirs $(RESFILE) $(PROJECT)

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
	-@if exist $(PROJECT) del $(PROJECT)

clean: cleanobj cleantgt

dirs::
	-@echo Creating output directory
	-@md bcc
	-@md $(OBJ)
	-@md $(BIN)
	
##################################
# Output
##################################
$(PROJECT1):: $(OBJFILES) $(OBJFILES2) $(OBJFILES3)
  @$(LB) $(LPARAM) $(BIN)\$(LIBNAME) /a$(OBJFILES)
  @$(LB) $(LPARAM) $(BIN)\$(LIBNAME) /a$(OBJFILES2)
  @$(LB) $(LPARAM) $(BIN)\$(LIBNAME) /a$(OBJFILES3)

$(PROJECT2):: $(ALLOBJS)
    $(ILINK32) @&&|
    $(LINKFLAGS) $(ALLOBJS2) 
    $<,$*
    $(ALLLIBS2)
    $(DEFFILE)
    $(RESFILE)

|
    @if exist ..\..\..\lib\ApplicationKit_bcc$(DBGDLL).lib del ..\..\..\lib\ApplicationKit_bcc$(DBGDLL).lib
    @if exist $(BIN)\ApplicationKit_bcc$(DBGDLL).lib move $(BIN)\ApplicationKit_bcc$(DBGDLL).lib ..\..\..\lib

#Dependencies - explicit rules
$(OBJ)\AbstractApplication.obj:          ..\..\..\src\vcf\ApplicationKit\AbstractApplication.cpp
$(OBJ)\AbstractCommand.obj:              ..\..\..\src\vcf\ApplicationKit\AbstractCommand.cpp                  
$(OBJ)\AbstractComponentEditor.obj:      ..\..\..\src\vcf\ApplicationKit\AbstractComponentEditor.cpp          
$(OBJ)\AbstractContainer.obj:            ..\..\..\src\vcf\ApplicationKit\AbstractContainer.cpp                
$(OBJ)\AbstractPropertyEditor.obj:       ..\..\..\src\vcf\ApplicationKit\AbstractPropertyEditor.cpp           
$(OBJ)\AbstractScrollable.obj:           ..\..\..\src\vcf\ApplicationKit\AbstractScrollable.cpp               
$(OBJ)\AcceleratorKey.obj:               ..\..\..\src\vcf\ApplicationKit\AcceleratorKey.cpp                   
$(OBJ)\Action.obj:                       ..\..\..\src\vcf\ApplicationKit\Action.cpp                           
$(OBJ)\Application.obj:                  ..\..\..\src\vcf\ApplicationKit\Application.cpp                      
$(OBJ)\ApplicationKit.obj:               ..\..\..\src\vcf\ApplicationKit\ApplicationKit.cpp                   
$(OBJ)\Basic3DBorder.obj:                ..\..\..\src\vcf\ApplicationKit\Basic3DBorder.cpp                
$(OBJ)\BasicTableItemEditor.obj:         ..\..\..\src\vcf\ApplicationKit\BasicTableItemEditor.cpp             
$(OBJ)\Clipboard.obj:                    ..\..\..\src\vcf\ApplicationKit\Clipboard.cpp                        
$(OBJ)\ColorEtchedBorder.obj:            ..\..\..\src\vcf\ApplicationKit\ColorEtchedBorder.cpp            
$(OBJ)\CommandGroup.obj:                 ..\..\..\src\vcf\ApplicationKit\CommandGroup.cpp                     
$(OBJ)\CommonColor.obj:                  ..\..\..\src\vcf\ApplicationKit\CommonColor.cpp                      
$(OBJ)\CommonFileBrowse.obj:             ..\..\..\src\vcf\ApplicationKit\CommonFileBrowse.cpp                 
$(OBJ)\CommonFileDialog.obj:             ..\..\..\src\vcf\ApplicationKit\CommonFileDialog.cpp                 
$(OBJ)\CommonFileOpen.obj:               ..\..\..\src\vcf\ApplicationKit\CommonFileOpen.cpp                   
$(OBJ)\CommonFileSave.obj:               ..\..\..\src\vcf\ApplicationKit\CommonFileSave.cpp                   
$(OBJ)\CommonFont.obj:                   ..\..\..\src\vcf\ApplicationKit\CommonFont.cpp                       
$(OBJ)\CommonPrint.obj:                  ..\..\..\src\vcf\ApplicationKit\CommonPrint.cpp                      
$(OBJ)\Component.obj:                    ..\..\..\src\vcf\ApplicationKit\Component.cpp                        
$(OBJ)\ComponentEditorManager.obj:       ..\..\..\src\vcf\ApplicationKit\ComponentEditorManager.cpp           
$(OBJ)\ComponentInfo.obj:                ..\..\..\src\vcf\ApplicationKit\ComponentInfo.cpp                    
$(OBJ)\Containers.obj:                   ..\..\..\src\vcf\ApplicationKit\Containers.cpp                       
$(OBJ)\Control.obj:                      ..\..\..\src\vcf\ApplicationKit\Control.cpp                          
$(OBJ)\ControlGraphicsContext.obj:       ..\..\..\src\vcf\ApplicationKit\ControlGraphicsContext.cpp       
$(OBJ)\Cursor.obj:                       ..\..\..\src\vcf\ApplicationKit\Cursor.cpp                           
$(OBJ)\CursorManager.obj:                ..\..\..\src\vcf\ApplicationKit\CursorManager.cpp                    
$(OBJ)\DataObject.obj:                   ..\..\..\src\vcf\ApplicationKit\DataObject.cpp                       
$(OBJ)\DefaultPropertyEditors.obj:       ..\..\..\src\vcf\ApplicationKit\DefaultPropertyEditors.cpp           
$(OBJ)\Desktop.obj:                      ..\..\..\src\vcf\ApplicationKit\Desktop.cpp                          
$(OBJ)\Dialog.obj:                       ..\..\..\src\vcf\ApplicationKit\Dialog.cpp                           
$(OBJ)\DragSource.obj:                   ..\..\..\src\vcf\ApplicationKit\DragSource.cpp                   
$(OBJ)\DropTarget.obj:                   ..\..\..\src\vcf\ApplicationKit\DropTarget.cpp                   
$(OBJ)\EtchedBorder.obj:                 ..\..\..\src\vcf\ApplicationKit\EtchedBorder.cpp                 
$(OBJ)\Frame.obj:                        ..\..\..\src\vcf\ApplicationKit\Frame.cpp                            
$(OBJ)\ImageList.obj:                    ..\..\..\src\vcf\ApplicationKit\ImageList.cpp                    
$(OBJ)\ImageListEvent.obj:               ..\..\..\src\vcf\ApplicationKit\ImageListEvent.cpp                 
$(OBJ)\KeyboardEvent.obj:                ..\..\..\src\vcf\ApplicationKit\KeyboardEvent.cpp                  
$(OBJ)\LibraryApplication.obj:           ..\..\..\src\vcf\ApplicationKit\LibraryApplication.cpp               
$(OBJ)\Light3DBorder.obj:                ..\..\..\src\vcf\ApplicationKit\Light3DBorder.cpp                
$(OBJ)\LightweightComponent.obj:         ..\..\..\src\vcf\ApplicationKit\LightweightComponent.cpp   
$(OBJ)\Menu.obj:                         ..\..\..\src\vcf\ApplicationKit\Menu.cpp                             
$(OBJ)\MenuBar.obj:                      ..\..\..\src\vcf\ApplicationKit\MenuBar.cpp                          
$(OBJ)\MessageDialog.obj:                ..\..\..\src\vcf\ApplicationKit\MessageDialog.cpp                    
$(OBJ)\MultilineTextControl.obj:         ..\..\..\src\vcf\ApplicationKit\MultilineTextControl.cpp             
$(OBJ)\PopupMenu.obj:                    ..\..\..\src\vcf\ApplicationKit\PopupMenu.cpp                        
$(OBJ)\PropertyEditorManager.obj:        ..\..\..\src\vcf\ApplicationKit\PropertyEditorManager.cpp            
$(OBJ)\Resource.obj:                     ..\..\..\src\vcf\ApplicationKit\Resource.cpp                        
$(OBJ)\ResourceStream.obj:               ..\..\..\src\vcf\ApplicationKit\ResourceStream.cpp                     
$(OBJ)\TitledBorder.obj:                 ..\..\..\src\vcf\ApplicationKit\TitledBorder.cpp                 
$(OBJ)\UIToolkit.obj:                    ..\..\..\src\vcf\ApplicationKit\UIToolkit.cpp                       
$(OBJ)\UndoRedoStack.obj:                ..\..\..\src\vcf\ApplicationKit\UndoRedoStack.cpp                    
$(OBJ)\VFFInputStream.obj:               ..\..\..\src\vcf\ApplicationKit\VFFInputStream.cpp                     
$(OBJ)\VFFOutputStream.obj:              ..\..\..\src\vcf\ApplicationKit\VFFOutputStream.cpp                    
$(OBJ)\Window.obj:                       ..\..\..\src\vcf\ApplicationKit\Window.cpp                           
$(OBJ)\WindowEvent.obj:                  ..\..\..\src\vcf\ApplicationKit\WindowEvent.cpp                    
$(OBJ)\AbstractWin32Component.obj:       ..\..\..\src\vcf\ApplicationKit\AbstractWin32Component.cpp 
$(OBJ)\COMDataObject.obj:                ..\..\..\src\vcf\ApplicationKit\COMDataObject.cpp          
$(OBJ)\COMUtils.obj:                     ..\..\..\src\vcf\ApplicationKit\COMUtils.cpp               
$(OBJ)\Win32Application.obj:             ..\..\..\src\vcf\ApplicationKit\Win32Application.cpp       
$(OBJ)\Win32Button.obj:                  ..\..\..\src\vcf\ApplicationKit\Win32Button.cpp            
$(OBJ)\Win32Clipboard.obj:               ..\..\..\src\vcf\ApplicationKit\Win32Clipboard.cpp         
$(OBJ)\Win32ColorDialog.obj:             ..\..\..\src\vcf\ApplicationKit\Win32ColorDialog.cpp       
$(OBJ)\Win32Component.obj:               ..\..\..\src\vcf\ApplicationKit\Win32Component.cpp         
$(OBJ)\Win32ControlContext.obj:          ..\..\..\src\vcf\ApplicationKit\Win32ControlContext.cpp    
$(OBJ)\Win32CursorPeer.obj:              ..\..\..\src\vcf\ApplicationKit\Win32CursorPeer.cpp        
$(OBJ)\Win32Desktop.obj:                 ..\..\..\src\vcf\ApplicationKit\Win32Desktop.cpp           
$(OBJ)\Win32Dialog.obj:                  ..\..\..\src\vcf\ApplicationKit\Win32Dialog.cpp            
$(OBJ)\Win32DragDropPeer.obj:            ..\..\..\src\vcf\ApplicationKit\Win32DragDropPeer.cpp      
$(OBJ)\Win32DropTargetPeer.obj:          ..\..\..\src\vcf\ApplicationKit\Win32DropTargetPeer.cpp    
$(OBJ)\Win32Edit.obj:                    ..\..\..\src\vcf\ApplicationKit\Win32Edit.cpp              
$(OBJ)\Win32FileOpenDialog.obj:          ..\..\..\src\vcf\ApplicationKit\Win32FileOpenDialog.cpp    
$(OBJ)\Win32FileSaveDialog.obj:          ..\..\..\src\vcf\ApplicationKit\Win32FileSaveDialog.cpp    
$(OBJ)\Win32FolderBrowseDialog.obj:      ..\..\..\src\vcf\ApplicationKit\Win32FolderBrowseDialog.cpp
$(OBJ)\Win32FontDialog.obj:              ..\..\..\src\vcf\ApplicationKit\Win32FontDialog.cpp        
$(OBJ)\Win32Listview.obj:                ..\..\..\src\vcf\ApplicationKit\Win32Listview.cpp          
$(OBJ)\Win32MenuBar.obj:                 ..\..\..\src\vcf\ApplicationKit\Win32MenuBar.cpp           
$(OBJ)\Win32MenuItem.obj:                ..\..\..\src\vcf\ApplicationKit\Win32MenuItem.cpp          
$(OBJ)\Win32Object.obj:                  ..\..\..\src\vcf\ApplicationKit\Win32Object.cpp            
$(OBJ)\Win32PopupMenu.obj:               ..\..\..\src\vcf\ApplicationKit\Win32PopupMenu.cpp         
$(OBJ)\Win32ResourceBundle.obj:          ..\..\..\src\vcf\ApplicationKit\Win32ResourceBundle.cpp    
$(OBJ)\Win32ResourceStream.obj:          ..\..\..\src\vcf\ApplicationKit\Win32ResourceStream.cpp    
$(OBJ)\Win32ScrollPeer.obj:              ..\..\..\src\vcf\ApplicationKit\Win32ScrollPeer.cpp        
$(OBJ)\Win32Toolbar.obj:                 ..\..\..\src\vcf\ApplicationKit\Win32Toolbar.cpp           
$(OBJ)\Win32ToolKit.obj:                 ..\..\..\src\vcf\ApplicationKit\Win32ToolKit.cpp           
$(OBJ)\Win32Tree.obj:                    ..\..\..\src\vcf\ApplicationKit\Win32Tree.cpp              
$(OBJ)\Win32Window.obj:                  ..\..\..\src\vcf\ApplicationKit\Win32Window.cpp            
$(OBJ)\ButtonEvent.obj:                  ..\..\..\src\vcf\ApplicationKit\ButtonEvent.cpp                    
$(OBJ)\ClipboardEvent.obj:               ..\..\..\src\vcf\ApplicationKit\ClipboardEvent.cpp                 
$(OBJ)\ColumnItemEvent.obj:              ..\..\..\src\vcf\ApplicationKit\ColumnItemEvent.cpp                
$(OBJ)\ColumnModelEvent.obj:             ..\..\..\src\vcf\ApplicationKit\ColumnModelEvent.cpp               
$(OBJ)\ControlEvent.obj:                 ..\..\..\src\vcf\ApplicationKit\ControlEvent.cpp                   
$(OBJ)\FocusEvent.obj:                   ..\..\..\src\vcf\ApplicationKit\FocusEvent.cpp                     
$(OBJ)\HelpEvent.obj:                    ..\..\..\src\vcf\ApplicationKit\HelpEvent.cpp                      
$(OBJ)\ItemEvent.obj:                    ..\..\..\src\vcf\ApplicationKit\ItemEvent.cpp                      
$(OBJ)\ListModelEvent.obj:               ..\..\..\src\vcf\ApplicationKit\ListModelEvent.cpp                 
$(OBJ)\MenuItemEvent.obj:                ..\..\..\src\vcf\ApplicationKit\MenuItemEvent.cpp                  
$(OBJ)\MouseEvent.obj:                   ..\..\..\src\vcf\ApplicationKit\MouseEvent.cpp                     
$(OBJ)\TabModelEvent.obj:                ..\..\..\src\vcf\ApplicationKit\TabModelEvent.cpp                  
$(OBJ)\TextEvent.obj:                    ..\..\..\src\vcf\ApplicationKit\TextEvent.cpp                      
$(OBJ)\TimerEvent.obj:                   ..\..\..\src\vcf\ApplicationKit\TimerEvent.cpp                     
$(OBJ)\ToolTipEvent.obj:                 ..\..\..\src\vcf\ApplicationKit\ToolTipEvent.cpp                   
$(OBJ)\TreeModelEvent.obj:               ..\..\..\src\vcf\ApplicationKit\TreeModelEvent.cpp                 
$(OBJ)\UndoRedoEvent.obj:                ..\..\..\src\vcf\ApplicationKit\UndoRedoEvent.cpp                  
$(OBJ)\ValidationEvent.obj:              ..\..\..\src\vcf\ApplicationKit\ValidationEvent.cpp                
$(OBJ)\WhatsThisHelpEvent.obj:           ..\..\..\src\vcf\ApplicationKit\WhatsThisHelpEvent.cpp             
$(OBJ)\AbstractListModel.obj:            ..\..\..\src\vcf\ApplicationKit\AbstractListModel.cpp                
$(OBJ)\AbstractTextModel.obj:            ..\..\..\src\vcf\ApplicationKit\AbstractTextModel.cpp                
$(OBJ)\AbstractTreeModel.obj:            ..\..\..\src\vcf\ApplicationKit\AbstractTreeModel.cpp                
$(OBJ)\AbstractView.obj:                 ..\..\..\src\vcf\ApplicationKit\AbstractView.cpp                     
$(OBJ)\DefaultColumnItem.obj:            ..\..\..\src\vcf\ApplicationKit\DefaultColumnItem.cpp                
$(OBJ)\DefaultColumnModel.obj:           ..\..\..\src\vcf\ApplicationKit\DefaultColumnModel.cpp               
$(OBJ)\DefaultListItem.obj:              ..\..\..\src\vcf\ApplicationKit\DefaultListItem.cpp                  
$(OBJ)\DefaultListModel.obj:             ..\..\..\src\vcf\ApplicationKit\DefaultListModel.cpp                 
$(OBJ)\DefaultMenuItem.obj:              ..\..\..\src\vcf\ApplicationKit\DefaultMenuItem.cpp                  
$(OBJ)\DefaultTableCellItem.obj:         ..\..\..\src\vcf\ApplicationKit\DefaultTableCellItem.cpp             
$(OBJ)\DefaultTableModel.obj:            ..\..\..\src\vcf\ApplicationKit\DefaultTableModel.cpp                
$(OBJ)\DefaultTabModel.obj:              ..\..\..\src\vcf\ApplicationKit\DefaultTabModel.cpp                  
$(OBJ)\DefaultTabPage.obj:               ..\..\..\src\vcf\ApplicationKit\DefaultTabPage.cpp                   
$(OBJ)\DefaultTextModel.obj:             ..\..\..\src\vcf\ApplicationKit\DefaultTextModel.cpp                 
$(OBJ)\DefaultTreeItem.obj:              ..\..\..\src\vcf\ApplicationKit\DefaultTreeItem.cpp                  
$(OBJ)\DefaultTreeModel.obj:             ..\..\..\src\vcf\ApplicationKit\DefaultTreeModel.cpp                 
$(OBJ)\DocumentManager.obj:              ..\..\..\src\vcf\ApplicationKit\DocumentManager.cpp                  
$(OBJ)\Model.obj:                        ..\..\..\src\vcf\ApplicationKit\Model.cpp                            
$(OBJ)\CheckBoxControl.obj:              ..\..\..\src\vcf\ApplicationKit\CheckBoxControl.cpp                  
$(OBJ)\ComboBoxControl.obj:              ..\..\..\src\vcf\ApplicationKit\ComboBoxControl.cpp                  
$(OBJ)\CommandButton.obj:                ..\..\..\src\vcf\ApplicationKit\CommandButton.cpp                    
$(OBJ)\ControlContainer.obj:             ..\..\..\src\vcf\ApplicationKit\ControlContainer.cpp                 
$(OBJ)\CustomControl.obj:                ..\..\..\src\vcf\ApplicationKit\CustomControl.cpp                    
$(OBJ)\HeaderControl.obj:                ..\..\..\src\vcf\ApplicationKit\HeaderControl.cpp                    
$(OBJ)\HTMLBrowserControl.obj:           ..\..\..\src\vcf\ApplicationKit\HTMLBrowserControl.cpp               
$(OBJ)\ImageControl.obj:                 ..\..\..\src\vcf\ApplicationKit\ImageControl.cpp                     
$(OBJ)\Label.obj:                        ..\..\..\src\vcf\ApplicationKit\Label.cpp                            
$(OBJ)\ListBoxControl.obj:               ..\..\..\src\vcf\ApplicationKit\ListBoxControl.cpp                   
$(OBJ)\ListViewControl.obj:              ..\..\..\src\vcf\ApplicationKit\ListViewControl.cpp                  
$(OBJ)\Panel.obj:                        ..\..\..\src\vcf\ApplicationKit\Panel.cpp                            
$(OBJ)\ProgressControl.obj:              ..\..\..\src\vcf\ApplicationKit\ProgressControl.cpp                  
$(OBJ)\PushButton.obj:                   ..\..\..\src\vcf\ApplicationKit\PushButton.cpp                       
$(OBJ)\RadioButtonControl.obj:           ..\..\..\src\vcf\ApplicationKit\RadioButtonControl.cpp               
$(OBJ)\ScrollbarManager.obj:             ..\..\..\src\vcf\ApplicationKit\ScrollbarManager.cpp                 
$(OBJ)\SliderControl.obj:                ..\..\..\src\vcf\ApplicationKit\SliderControl.cpp                    
$(OBJ)\Splitter.obj:                     ..\..\..\src\vcf\ApplicationKit\Splitter.cpp                         
$(OBJ)\StatusBar.obj:                    ..\..\..\src\vcf\ApplicationKit\StatusBar.cpp                        
$(OBJ)\TabbedPages.obj:                  ..\..\..\src\vcf\ApplicationKit\TabbedPages.cpp                      
$(OBJ)\TableControl.obj:                 ..\..\..\src\vcf\ApplicationKit\TableControl.cpp                     
$(OBJ)\TextControl.obj:                  ..\..\..\src\vcf\ApplicationKit\TextControl.cpp                      
$(OBJ)\TimerComponent.obj:               ..\..\..\src\vcf\ApplicationKit\TimerComponent.cpp                   
$(OBJ)\ToggledButton.obj:                ..\..\..\src\vcf\ApplicationKit\ToggledButton.cpp                    
$(OBJ)\Toolbar.obj:                      ..\..\..\src\vcf\ApplicationKit\Toolbar.cpp                          
$(OBJ)\ToolbarDock.obj:                  ..\..\..\src\vcf\ApplicationKit\ToolbarDock.cpp                      
$(OBJ)\TreeControl.obj:                  ..\..\..\src\vcf\ApplicationKit\TreeControl.cpp                      
$(OBJ)\TreeListControl.obj:              ..\..\..\src\vcf\ApplicationKit\TreeListControl.cpp                  

$(RESFILE)::
   @brcc32 /l0x409 -d_DEBUG ..\..\resources\win32\ApplicationKit.rc
   @move ..\..\resources\win32\ApplicationKit.res $(OBJ)

