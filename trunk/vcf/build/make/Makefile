#########################################################
#
#CVS Log info
#$Log$
#Revision 1.4  2003/12/18 05:15:47  ddiego
#merge from devmain-0-6-2 branch into the stable branch
#
#Revision 1.3.4.11  2003/12/13 19:17:10  ddiego
#*** empty log message ***
#
#Revision 1.3.4.10  2003/12/13 18:19:00  ddiego
#*** empty log message ***
#
#Revision 1.3.4.9  2003/11/11 17:43:42  ddiego
#updated the makefile and foundationKit object to make a VariantData.obj
#file
#
#Revision 1.3.4.8  2003/11/01 20:41:00  ddiego
#updated makefil to add the gtk toolbar class
#
#Revision 1.3.4.7  2003/10/22 03:56:43  ddiego
#added two more tutorials for advanced alignment and another for anchors
#also finished off the alignment tutorial. yay :)
#
#Revision 1.3.4.6  2003/10/04 20:13:45  ddiego
#updated the Makefiles - everything works now, including compiling
#building on GCC 3.3.1
#
#Revision 1.3.4.5  2003/10/03 04:33:03  ddiego
#add precompiled header target - doesn't seem to really work though
#
#Revision 1.3.4.4  2003/10/03 01:07:48  ddiego
#added/fixed problems to get it to compile under linux
#
#Revision 1.3.4.3  2003/10/02 04:50:34  ddiego
#changes to ensure the code compiles on linux. made a bunch of updates to
#the makefiles
#
#Revision 1.3.4.2  2003/09/27 16:19:10  ddiego
#further mods to bring it up to synch with the current win32 rev
#
#Revision 1.3.4.1  2003/09/27 16:11:30  ddiego
#fixed some minor glitches in the makefile due to changes made on the Win32
#side.
#
#Revision 1.3  2003/05/17 20:36:20  ddiego
#this is the checkin for the 0.6.1 release - represents the merge over from
#the devmain-0-6-0 branch plus a few minor bug fixes
#
#Revision 1.2.2.1  2003/04/19 22:21:43  ddiego
#tested the code developed in windows using gtk in linux. Seems to work ok except for a
#few minor compiler glitches. Had to comment out the partial specialization for
#floating point image bits in include/graphics/ImageBits.h. Also made some
#adjustments in the makefiles for building the GraphicsKit and ApplicationKit
#from the build/make/Makefile.
#
#Revision 1.2  2003/02/26 04:30:25  ddiego
#merge of code in the devmain-0-5-9 branch into the current tree.
#most additions are in the area of the current linux port, but the major
#addition to this release is the addition of a Condition class (currently
#still under development) and the change over to using the Delegate class
#exclusively from the older event handler macros.
#
#Revision 1.1.2.9  2003/02/18 19:59:56  catwallader
#Added Condition classes. Also added comments to Thread and Mutex class
#headers.
#
#Revision 1.1.2.8  2003/02/12 19:33:45  catwallader
#Added PosixMutex class.
#
#Revision 1.1.2.7  2003/02/08 17:55:44  ddiego
#modified the makefiles to have cvs Log entries, so we can keepo track of
#whats going on :)
#
#
#makefile for foundation kit
#
#
#INCLUDES sections
#
#this is where we pull stuff in from a set of 
#one or more shared files. The files can be named 
#anything you want
#the "include" keyword is used to tell make to 
#include the file - works just like the C/C++ #include 
#statement
#
#########################################################

include common.mak




#debug target
FOUNDATION_KIT_SO_D=$(BIN_OUT)/libFoundationKit_d.so
GRAPHICS_KIT_SO_D=$(BIN_OUT)/libGraphicsKit_d.so
LIBAGG_LIB_D=$(LIB_OUT)/libAGG_d.a
APPLICATION_KIT_SO_D=$(BIN_OUT)/libApplicationKit_d.so
NETWORK_KIT_SO_D=$(BIN_OUT)/libNetworkKit_d.so

#release target
FOUNDATION_KIT_SO=$(BIN_OUT)/libFoundationKit.so
GRAPHICS_KIT_SO=$(BIN_OUT)/libGraphicsKit.so
LIBAGG_LIB=$(LIB_OUT)/libAGG.a
APPLICATION_KIT_SO=$(BIN_OUT)/libApplicationKit.so
NETWORK_KIT_SO=$(BIN_OUT)/libNetworkKit.so



FK_PRECOMP=$(INC)/FoundationKit.h.gch


#toolchain definitions
CXX_FLAGS_D=-ggdb -D VCF_GCC -DVCF_POSIX -D_DEBUG -I $(CXX_INC) -c

GTK_CXX_FLAGS = `pkg-config gtk+-2.0 --cflags`

GK_CXX_FLAGS_D=$(GTK_CXX_FLAGS) -DVCF_GTK $(CXX_FLAGS_D)

AK_CXX_FLAGS_D=$(GK_CXX_FLAGS_D)

NK_CXX_FLAGS_D=$(CXX_FLAGS_D)

CXX_FLAGS=-DNDEBUG -DVCF_GCC -DVCF_POSIX -I $(CXX_INC) -Os -c
GK_CXX_FLAGS=$(GTK_CXX_FLAGS) -DVCF_GTK $(CXX_FLAGS)

AK_CXX_FLAGS=$(GK_CXX_FLAGS)

NK_CXX_FLAGS=$(CXX_FLAGS)


LINKER_FLAGS_D=-ldl -shared -ggdb -o
GTK_LINKER_FLAGS = `pkg-config gtk+-2.0 --libs`
GK_LINKER_FLAGS_D=-L $(BIN_OUT) $(GTK_LINKER_FLAGS) -lFoundationKit_d $(LINKER_FLAGS_D)
AK_LINKER_FLAGS_D=-L $(BIN_OUT) $(GTK_LINKER_FLAGS) -lFoundationKit_d -lGraphicsKit_d $(LINKER_FLAGS_D)
NK_LINKER_FLAGS_D=-L $(BIN_OUT) -lFoundationKit_d $(LINKER_FLAGS_D)

LINKER_FLAGS=-ldl -lpthread -shared -o
GK_LINKER_FLAGS=-L $(BIN_OUT) $(GTK_LINKER_FLAGS) -lFoundationKit $(LINKER_FLAGS)
AK_LINKER_FLAGS=-L $(BIN_OUT) $(GTK_LINKER_FLAGS)  -lFoundationKit -lGraphicsKit $(LINKER_FLAGS)
NK_LINKER_FLAGS=-L $(BIN_OUT) -lFoundationKit $(LINKER_FLAGS)


STATIC_LINKER_FLAGS=-cru




#debug object files.
#note that they are in a different directory
#from their physical source location
FK_OBJECT_FILES_D=$(OUTDIR_FK_D)/BasicException.o \
	$(OUTDIR_FK_D)/BasicInputStream.o \
	$(OUTDIR_FK_D)/BasicOutputStream.o \
	$(OUTDIR_FK_D)/Class.o \
	$(OUTDIR_FK_D)/ClassRegistry.o \
	$(OUTDIR_FK_D)/Directory.o \
	$(OUTDIR_FK_D)/ErrorLog.o \
	$(OUTDIR_FK_D)/Event.o \
	$(OUTDIR_FK_D)/EventHandler.o \
	$(OUTDIR_FK_D)/File.o \
	$(OUTDIR_FK_D)/FilePath.o \
	$(OUTDIR_FK_D)/FileStream.o \
	$(OUTDIR_FK_D)/FileUtils.o \
	$(OUTDIR_FK_D)/FoundationKit.o \
	$(OUTDIR_FK_D)/InterfaceClass.o \
	$(OUTDIR_FK_D)/Library.o \
	$(OUTDIR_FK_D)/Locales.o \
	$(OUTDIR_FK_D)/MemoryStream.o \
	$(OUTDIR_FK_D)/Mutex.o \
	$(OUTDIR_FK_D)/Condition.o \
	$(OUTDIR_FK_D)/Object.o \
	$(OUTDIR_FK_D)/ObjectWithEvents.o \
	$(OUTDIR_FK_D)/Parser.o \
	$(OUTDIR_FK_D)/PropertyChangeEvent.o \
	$(OUTDIR_FK_D)/Registry.o \
	$(OUTDIR_FK_D)/Stream.o \
	$(OUTDIR_FK_D)/StringUtils.o \
	$(OUTDIR_FK_D)/System.o \
	$(OUTDIR_FK_D)/SystemToolkit.o \
	$(OUTDIR_FK_D)/TextInputStream.o \
	$(OUTDIR_FK_D)/TextOutputStream.o \
	$(OUTDIR_FK_D)/Thread.o \
	$(OUTDIR_FK_D)/ThreadEvent.o \
	$(OUTDIR_FK_D)/VariantData.o \
	$(OUTDIR_FK_D)/VCFMath.o \
	$(OUTDIR_FK_D)/VCFProcess.o \
	$(OUTDIR_FK_D)/XMLParser.o \
	$(OUTDIR_FK_D)/CommandLine.o \
	$(OUTDIR_FK_D)/LinuxPeer.o \
	$(OUTDIR_FK_D)/LinuxFilePeer.o \
	$(OUTDIR_FK_D)/LinuxFileStream.o \
	$(OUTDIR_FK_D)/PosixThread.o \
	$(OUTDIR_FK_D)/LinuxLibraryPeer.o \
	$(OUTDIR_FK_D)/PosixMutex.o \
	$(OUTDIR_FK_D)/PosixCondition.o \
	$(OUTDIR_FK_D)/LinuxProcessPeer.o \
	$(OUTDIR_FK_D)/LinuxRegistry.o \
	$(OUTDIR_FK_D)/LinuxSemaphorePeer.o \
	$(OUTDIR_FK_D)/LinuxSystemPeer.o \
	$(OUTDIR_FK_D)/LinuxSystemToolkit.o \
	$(OUTDIR_FK_D)/LinuxProcessIORedirector.o 


#release object files.
#note that they are in a different directory
#from their physical source location
FK_OBJECT_FILES=$(OUTDIR_FK)/BasicException.o \
	$(OUTDIR_FK)/BasicInputStream.o \
	$(OUTDIR_FK)/BasicOutputStream.o \
	$(OUTDIR_FK)/Class.o \
	$(OUTDIR_FK)/CommandLine.o \
	$(OUTDIR_FK)/ClassRegistry.o \
	$(OUTDIR_FK)/Directory.o \
	$(OUTDIR_FK)/ErrorLog.o \
	$(OUTDIR_FK)/Event.o \
	$(OUTDIR_FK)/EventHandler.o \
	$(OUTDIR_FK)/File.o \
	$(OUTDIR_FK)/FilePath.o \
	$(OUTDIR_FK)/FileStream.o \
	$(OUTDIR_FK)/FileUtils.o \
	$(OUTDIR_FK)/FoundationKit.o \
	$(OUTDIR_FK)/InterfaceClass.o \
	$(OUTDIR_FK)/Library.o \
	$(OUTDIR_FK)/Locales.o \
	$(OUTDIR_FK)/MemoryStream.o \
	$(OUTDIR_FK)/Mutex.o \
	$(OUTDIR_FK)/Condition.o \
	$(OUTDIR_FK)/Object.o \
	$(OUTDIR_FK)/ObjectWithEvents.o \
	$(OUTDIR_FK)/Parser.o \
	$(OUTDIR_FK)/PropertyChangeEvent.o \
	$(OUTDIR_FK)/Registry.o \
	$(OUTDIR_FK)/Stream.o \
	$(OUTDIR_FK)/StringUtils.o \
	$(OUTDIR_FK)/System.o \
	$(OUTDIR_FK)/SystemToolkit.o \
	$(OUTDIR_FK)/TextInputStream.o \
	$(OUTDIR_FK)/TextOutputStream.o \
	$(OUTDIR_FK)/Thread.o \
	$(OUTDIR_FK)/ThreadEvent.o \
	$(OUTDIR_FK)/VariantData.o \
	$(OUTDIR_FK)/VCFMath.o \
	$(OUTDIR_FK)/VCFProcess.o \
	$(OUTDIR_FK)/XMLParser.o \
	$(OUTDIR_FK)/LinuxPeer.o \
	$(OUTDIR_FK)/LinuxFilePeer.o \
	$(OUTDIR_FK)/LinuxFileStream.o \
	$(OUTDIR_FK)/PosixThread.o \
	$(OUTDIR_FK)/LinuxLibraryPeer.o \
	$(OUTDIR_FK)/PosixMutex.o \
	$(OUTDIR_FK)/PosixCondition.o \
	$(OUTDIR_FK)/LinuxProcessPeer.o \
	$(OUTDIR_FK)/LinuxRegistry.o \
	$(OUTDIR_FK)/LinuxSemaphorePeer.o \
	$(OUTDIR_FK)/LinuxSystemPeer.o \
	$(OUTDIR_FK)/LinuxSystemToolkit.o \
	$(OUTDIR_FK)/LinuxProcessIORedirector.o 





#GraphicsKit Objects
LIBAGG_OBJECTFILES_D=$(OUTDIR_GK_D)/agg_affine_matrix.o \
			$(OUTDIR_GK_D)/agg_bspline.o \
			$(OUTDIR_GK_D)/agg_curves.o \
			$(OUTDIR_GK_D)/agg_gen_stroke.o \
			$(OUTDIR_GK_D)/agg_gsv_text.o \
			$(OUTDIR_GK_D)/agg_path_storage.o \
			$(OUTDIR_GK_D)/agg_rasterizer_scanline_aa.o \
			$(OUTDIR_GK_D)/agg_scanline_u8.o 

LIBAGG_OBJECTFILES=$(OUTDIR_GK)/agg_affine_matrix.o \
			$(OUTDIR_GK)/agg_bspline.o \
			$(OUTDIR_GK)/agg_curves.o \
			$(OUTDIR_GK)/agg_gen_stroke.o \
			$(OUTDIR_GK)/agg_gsv_text.o \
			$(OUTDIR_GK)/agg_path_storage.o \
			$(OUTDIR_GK)/agg_rasterizer_scanline_aa.o \
			$(OUTDIR_GK)/agg_scanline_u8.o 
			
GRAFKIT_OBJECT_FILES_D=$(OUTDIR_GK_D)/GraphicsKit.o \
			$(OUTDIR_GK_D)/AbstractImage.o \
			$(OUTDIR_GK_D)/BasicFill.o \
			$(OUTDIR_GK_D)/BasicStroke.o \
			$(OUTDIR_GK_D)/Color.o \
			$(OUTDIR_GK_D)/Font.o \
			$(OUTDIR_GK_D)/GlyphCollection.o \
			$(OUTDIR_GK_D)/GraphicsContext.o \
			$(OUTDIR_GK_D)/GraphicsToolKit.o \
			$(OUTDIR_GK_D)/ImageEvent.o \
			$(OUTDIR_GK_D)/Matrix2D.o \
			$(OUTDIR_GK_D)/BezierCurve.o \
			$(OUTDIR_GK_D)/Vector2D.o \
			$(OUTDIR_GK_D)/Point.o \
			$(OUTDIR_GK_D)/Rect.o \
			$(OUTDIR_GK_D)/GTKFont.o \
			$(OUTDIR_GK_D)/GTKImage.o \
			$(OUTDIR_GK_D)/GTKContext.o \
			$(OUTDIR_GK_D)/GTKGraphicsToolkit.o \
			$(OUTDIR_GK_D)/MgcBezierCurve2.o \
			$(OUTDIR_GK_D)/MgcCurve2.o \
			$(OUTDIR_GK_D)/MgcVector2.o \
			$(OUTDIR_GK_D)/MgcIntegrate.o \
			$(OUTDIR_GK_D)/MgcSingleCurve2.o \
			$(OUTDIR_GK_D)/MgcMath.o \
			$(LIBAGG_LIB_D) 
			


GRAFKIT_OBJECT_FILES=$(OUTDIR_GK)/GraphicsKit.o \
			$(OUTDIR_GK)/AbstractImage.o \
			$(OUTDIR_GK)/BasicFill.o \
			$(OUTDIR_GK)/BasicStroke.o \
			$(OUTDIR_GK)/Color.o \
			$(OUTDIR_GK)/Font.o \
			$(OUTDIR_GK)/GlyphCollection.o \
			$(OUTDIR_GK)/GraphicsContext.o \
			$(OUTDIR_GK)/GraphicsToolKit.o \
			$(OUTDIR_GK)/ImageEvent.o \
			$(OUTDIR_GK)/Matrix2D.o \
			$(OUTDIR_GK)/BezierCurve.o \
			$(OUTDIR_GK)/Point.o \
			$(OUTDIR_GK)/Rect.o \
			$(OUTDIR_GK)/Vector2D.o \
			$(OUTDIR_GK)/GTKFont.o \
			$(OUTDIR_GK)/GTKImage.o \
			$(OUTDIR_GK)/GTKContext.o \
			$(OUTDIR_GK)/GTKGraphicsToolkit.o \
			$(OUTDIR_GK)/MgcBezierCurve2.o \
			$(OUTDIR_GK)/MgcCurve2.o \
			$(OUTDIR_GK)/MgcVector2.o \
			$(OUTDIR_GK)/MgcIntegrate.o \
			$(OUTDIR_GK)/MgcSingleCurve2.o \
			$(OUTDIR_GK)/MgcMath.o \
			$(LIBAGG_LIB)


#ApplicationKit objects

APPKIT_OBJECT_FILES_D=$(OUTDIR_AK_D)/ApplicationKit.o \
			$(OUTDIR_AK_D)/AbstractApplication.o \
			$(OUTDIR_AK_D)/AbstractCommand.o \
			$(OUTDIR_AK_D)/AbstractComponentEditor.o \
			$(OUTDIR_AK_D)/AbstractContainer.o \
			$(OUTDIR_AK_D)/AbstractListModel.o \
			$(OUTDIR_AK_D)/AbstractPropertyEditor.o \
			$(OUTDIR_AK_D)/AbstractScrollable.o \
			$(OUTDIR_AK_D)/AbstractTableModel.o \
			$(OUTDIR_AK_D)/AbstractTextModel.o \
			$(OUTDIR_AK_D)/AbstractTreeModel.o \
			$(OUTDIR_AK_D)/AbstractView.o \
			$(OUTDIR_AK_D)/AcceleratorKey.o \
			$(OUTDIR_AK_D)/Application.o \
			$(OUTDIR_AK_D)/Basic3DBorder.o \
			$(OUTDIR_AK_D)/BasicTableItemEditor.o \
			$(OUTDIR_AK_D)/ButtonEvent.o \
			$(OUTDIR_AK_D)/CheckBoxControl.o \
			$(OUTDIR_AK_D)/Clipboard.o \
			$(OUTDIR_AK_D)/DataObject.o \
			$(OUTDIR_AK_D)/ClipboardEvent.o \
			$(OUTDIR_AK_D)/ColumnItemEvent.o \
			$(OUTDIR_AK_D)/ColumnModelEvent.o \
			$(OUTDIR_AK_D)/ComboBoxControl.o \
			$(OUTDIR_AK_D)/CommandButton.o \
			$(OUTDIR_AK_D)/CommandGroup.o \
			$(OUTDIR_AK_D)/CommonColor.o \
			$(OUTDIR_AK_D)/CommonFileBrowse.o \
			$(OUTDIR_AK_D)/CommonFileDialog.o \
			$(OUTDIR_AK_D)/CommonFileOpen.o \
			$(OUTDIR_AK_D)/CommonFileSave.o \
			$(OUTDIR_AK_D)/CommonFont.o \
			$(OUTDIR_AK_D)/CommonPrint.o \
			$(OUTDIR_AK_D)/Component.o \
			$(OUTDIR_AK_D)/ComponentEditorManager.o \
			$(OUTDIR_AK_D)/ComponentInfo.o \
			$(OUTDIR_AK_D)/Action.o \
			$(OUTDIR_AK_D)/Control.o \
			$(OUTDIR_AK_D)/ControlContainer.o \
			$(OUTDIR_AK_D)/ControlEvent.o \
			$(OUTDIR_AK_D)/ControlGraphicsContext.o \
			$(OUTDIR_AK_D)/Cursor.o \
			$(OUTDIR_AK_D)/CursorManager.o \
			$(OUTDIR_AK_D)/CustomControl.o \
			$(OUTDIR_AK_D)/DefaultColumnItem.o \
			$(OUTDIR_AK_D)/DefaultColumnModel.o \
			$(OUTDIR_AK_D)/DefaultListItem.o \
			$(OUTDIR_AK_D)/DefaultListModel.o \
			$(OUTDIR_AK_D)/DefaultMenuItem.o \
			$(OUTDIR_AK_D)/DefaultPropertyEditors.o \
			$(OUTDIR_AK_D)/DefaultTableCellItem.o \
			$(OUTDIR_AK_D)/DefaultTableModel.o \
			$(OUTDIR_AK_D)/DefaultTabModel.o \
			$(OUTDIR_AK_D)/DefaultTabPage.o \
			$(OUTDIR_AK_D)/DefaultTextModel.o \
			$(OUTDIR_AK_D)/DefaultTreeItem.o \
			$(OUTDIR_AK_D)/DefaultTreeModel.o \
			$(OUTDIR_AK_D)/Desktop.o \
			$(OUTDIR_AK_D)/Dialog.o \
			$(OUTDIR_AK_D)/DragSource.o \
			$(OUTDIR_AK_D)/DropTarget.o \
			$(OUTDIR_AK_D)/FocusEvent.o \
			$(OUTDIR_AK_D)/Frame.o \
			$(OUTDIR_AK_D)/HeaderControl.o \
			$(OUTDIR_AK_D)/HelpEvent.o \
			$(OUTDIR_AK_D)/HTMLBrowserControl.o \
			$(OUTDIR_AK_D)/ImageControl.o \
			$(OUTDIR_AK_D)/ImageList.o \
			$(OUTDIR_AK_D)/ImageListEvent.o \
			$(OUTDIR_AK_D)/ItemEvent.o \
			$(OUTDIR_AK_D)/KeyboardEvent.o \
			$(OUTDIR_AK_D)/Label.o \
			$(OUTDIR_AK_D)/LibraryApplication.o \
			$(OUTDIR_AK_D)/Light3DBorder.o \
			$(OUTDIR_AK_D)/LightweightComponent.o \
			$(OUTDIR_AK_D)/ListBoxControl.o \
			$(OUTDIR_AK_D)/ListModelEvent.o \
			$(OUTDIR_AK_D)/ListViewControl.o \
			$(OUTDIR_AK_D)/Menu.o \
			$(OUTDIR_AK_D)/MenuBar.o \
			$(OUTDIR_AK_D)/MenuItemEvent.o \
			$(OUTDIR_AK_D)/Model.o \
			$(OUTDIR_AK_D)/MouseEvent.o \
			$(OUTDIR_AK_D)/MultilineTextControl.o \
			$(OUTDIR_AK_D)/Panel.o \
			$(OUTDIR_AK_D)/PopupMenu.o \
			$(OUTDIR_AK_D)/PropertyEditorManager.o \
			$(OUTDIR_AK_D)/PushButton.o \
			$(OUTDIR_AK_D)/RadioButtonControl.o \
			$(OUTDIR_AK_D)/Resource.o \
			$(OUTDIR_AK_D)/ResourceStream.o \
			$(OUTDIR_AK_D)/ScrollbarManager.o \
			$(OUTDIR_AK_D)/Splitter.o \
			$(OUTDIR_AK_D)/StatusBar.o \
			$(OUTDIR_AK_D)/TabbedPages.o \
			$(OUTDIR_AK_D)/TableControl.o \
			$(OUTDIR_AK_D)/TableModelEvent.o \
			$(OUTDIR_AK_D)/TabModelEvent.o \
			$(OUTDIR_AK_D)/TextControl.o \
			$(OUTDIR_AK_D)/TextEvent.o \
			$(OUTDIR_AK_D)/TimerComponent.o \
			$(OUTDIR_AK_D)/TimerEvent.o \
			$(OUTDIR_AK_D)/ToggledButton.o \
			$(OUTDIR_AK_D)/Toolbar.o \
			$(OUTDIR_AK_D)/ToolbarDock.o \
			$(OUTDIR_AK_D)/ToolTipEvent.o \
			$(OUTDIR_AK_D)/TreeControl.o \
			$(OUTDIR_AK_D)/TreeListControl.o \
			$(OUTDIR_AK_D)/TreeModelEvent.o \
			$(OUTDIR_AK_D)/UIToolkit.o \
			$(OUTDIR_AK_D)/UndoRedoEvent.o \
			$(OUTDIR_AK_D)/UndoRedoStack.o \
			$(OUTDIR_AK_D)/ValidationEvent.o \
			$(OUTDIR_AK_D)/VFFInputStream.o \
			$(OUTDIR_AK_D)/VFFOutputStream.o \
			$(OUTDIR_AK_D)/WhatsThisHelpEvent.o \
			$(OUTDIR_AK_D)/Window.o \
			$(OUTDIR_AK_D)/WindowEvent.o \
			$(OUTDIR_AK_D)/Containers.o \
			$(OUTDIR_AK_D)/PackageInfo.o \
			$(OUTDIR_AK_D)/DocumentManager.o \
			$(OUTDIR_AK_D)/MessageDialog.o \
			$(OUTDIR_AK_D)/GTKUIToolkit.o \
			$(OUTDIR_AK_D)/GTKDesktop.o \
			$(OUTDIR_AK_D)/GTKApplication.o \
			$(OUTDIR_AK_D)/AbstractGTKControl.o \
			$(OUTDIR_AK_D)/GTKControl.o \
			$(OUTDIR_AK_D)/GTKWindow.o \
			$(OUTDIR_AK_D)/GTKControlContext.o \
			$(OUTDIR_AK_D)/GTKCursor.o \
			$(OUTDIR_AK_D)/GTKTextControl.o \
			$(OUTDIR_AK_D)/GTKFileOpenDialog.o \
			$(OUTDIR_AK_D)/GTKDialog.o \
			$(OUTDIR_AK_D)/GTKCommandButton.o \
			$(OUTDIR_AK_D)/GTKToolbar.o 


APPKIT_OBJECT_FILES=$(OUTDIR_AK)/ApplicationKit.o \
			$(OUTDIR_AK)/AbstractApplication.o \
			$(OUTDIR_AK)/AbstractCommand.o \
			$(OUTDIR_AK)/AbstractComponentEditor.o \
			$(OUTDIR_AK)/AbstractContainer.o \
			$(OUTDIR_AK)/AbstractListModel.o \
			$(OUTDIR_AK)/AbstractPropertyEditor.o \
			$(OUTDIR_AK)/AbstractScrollable.o \
			$(OUTDIR_AK)/AbstractTableModel.o \
			$(OUTDIR_AK)/AbstractTextModel.o \
			$(OUTDIR_AK)/AbstractTreeModel.o \
			$(OUTDIR_AK)/AbstractView.o \
			$(OUTDIR_AK)/AcceleratorKey.o \
			$(OUTDIR_AK)/Application.o \
			$(OUTDIR_AK)/Basic3DBorder.o \
			$(OUTDIR_AK)/BasicTableItemEditor.o \
			$(OUTDIR_AK)/ButtonEvent.o \
			$(OUTDIR_AK)/CheckBoxControl.o \
			$(OUTDIR_AK)/Clipboard.o \
			$(OUTDIR_AK)/DataObject.o \
			$(OUTDIR_AK)/ClipboardEvent.o \
			$(OUTDIR_AK)/ColumnItemEvent.o \
			$(OUTDIR_AK)/ColumnModelEvent.o \
			$(OUTDIR_AK)/ComboBoxControl.o \
			$(OUTDIR_AK)/CommandButton.o \
			$(OUTDIR_AK)/CommandGroup.o \
			$(OUTDIR_AK)/CommonColor.o \
			$(OUTDIR_AK)/CommonFileBrowse.o \
			$(OUTDIR_AK)/CommonFileDialog.o \
			$(OUTDIR_AK)/CommonFileOpen.o \
			$(OUTDIR_AK)/CommonFileSave.o \
			$(OUTDIR_AK)/CommonFont.o \
			$(OUTDIR_AK)/CommonPrint.o \
			$(OUTDIR_AK)/Component.o \
			$(OUTDIR_AK)/ComponentEditorManager.o \
			$(OUTDIR_AK)/ComponentInfo.o \
			$(OUTDIR_AK)/Action.o \
			$(OUTDIR_AK)/Control.o \
			$(OUTDIR_AK)/ControlContainer.o \
			$(OUTDIR_AK)/ControlEvent.o \
			$(OUTDIR_AK)/ControlGraphicsContext.o \
			$(OUTDIR_AK)/Cursor.o \
			$(OUTDIR_AK)/CursorManager.o \
			$(OUTDIR_AK)/CustomControl.o \
			$(OUTDIR_AK)/DefaultColumnItem.o \
			$(OUTDIR_AK)/DefaultColumnModel.o \
			$(OUTDIR_AK)/DefaultListItem.o \
			$(OUTDIR_AK)/DefaultListModel.o \
			$(OUTDIR_AK)/DefaultMenuItem.o \
			$(OUTDIR_AK)/DefaultPropertyEditors.o \
			$(OUTDIR_AK)/DefaultTableCellItem.o \
			$(OUTDIR_AK)/DefaultTableModel.o \
			$(OUTDIR_AK)/DefaultTabModel.o \
			$(OUTDIR_AK)/DefaultTabPage.o \
			$(OUTDIR_AK)/DefaultTextModel.o \
			$(OUTDIR_AK)/DefaultTreeItem.o \
			$(OUTDIR_AK)/DefaultTreeModel.o \
			$(OUTDIR_AK)/Desktop.o \
			$(OUTDIR_AK)/Dialog.o \
			$(OUTDIR_AK)/DragSource.o \
			$(OUTDIR_AK)/DropTarget.o \
			$(OUTDIR_AK)/FocusEvent.o \
			$(OUTDIR_AK)/Frame.o \
			$(OUTDIR_AK)/HeaderControl.o \
			$(OUTDIR_AK)/HelpEvent.o \
			$(OUTDIR_AK)/HTMLBrowserControl.o \
			$(OUTDIR_AK)/ImageControl.o \
			$(OUTDIR_AK)/ImageList.o \
			$(OUTDIR_AK)/ImageListEvent.o \
			$(OUTDIR_AK)/ItemEvent.o \
			$(OUTDIR_AK)/KeyboardEvent.o \
			$(OUTDIR_AK)/Label.o \
			$(OUTDIR_AK)/LibraryApplication.o \
			$(OUTDIR_AK)/Light3DBorder.o \
			$(OUTDIR_AK)/LightweightComponent.o \
			$(OUTDIR_AK)/ListBoxControl.o \
			$(OUTDIR_AK)/ListModelEvent.o \
			$(OUTDIR_AK)/ListViewControl.o \
			$(OUTDIR_AK)/Menu.o \
			$(OUTDIR_AK)/MenuBar.o \
			$(OUTDIR_AK)/MenuItemEvent.o \
			$(OUTDIR_AK)/Model.o \
			$(OUTDIR_AK)/MouseEvent.o \
			$(OUTDIR_AK)/MultilineTextControl.o \
			$(OUTDIR_AK)/Panel.o \
			$(OUTDIR_AK)/PopupMenu.o \
			$(OUTDIR_AK)/PropertyEditorManager.o \
			$(OUTDIR_AK)/PushButton.o \
			$(OUTDIR_AK)/RadioButtonControl.o \
			$(OUTDIR_AK)/Resource.o \
			$(OUTDIR_AK)/ResourceStream.o \
			$(OUTDIR_AK)/ScrollbarManager.o \
			$(OUTDIR_AK)/Splitter.o \
			$(OUTDIR_AK)/StatusBar.o \
			$(OUTDIR_AK)/TabbedPages.o \
			$(OUTDIR_AK)/TableControl.o \
			$(OUTDIR_AK)/TableModelEvent.o \
			$(OUTDIR_AK)/TabModelEvent.o \
			$(OUTDIR_AK)/TextControl.o \
			$(OUTDIR_AK)/TextEvent.o \
			$(OUTDIR_AK)/TimerComponent.o \
			$(OUTDIR_AK)/TimerEvent.o \
			$(OUTDIR_AK)/ToggledButton.o \
			$(OUTDIR_AK)/Toolbar.o \
			$(OUTDIR_AK)/ToolbarDock.o \
			$(OUTDIR_AK)/ToolTipEvent.o \
			$(OUTDIR_AK)/TreeControl.o \
			$(OUTDIR_AK)/TreeListControl.o \
			$(OUTDIR_AK)/TreeModelEvent.o \
			$(OUTDIR_AK)/UIToolkit.o \
			$(OUTDIR_AK)/UndoRedoEvent.o \
			$(OUTDIR_AK)/UndoRedoStack.o \
			$(OUTDIR_AK)/ValidationEvent.o \
			$(OUTDIR_AK)/VFFInputStream.o \
			$(OUTDIR_AK)/VFFOutputStream.o \
			$(OUTDIR_AK)/WhatsThisHelpEvent.o \
			$(OUTDIR_AK)/Window.o \
			$(OUTDIR_AK)/WindowEvent.o \
			$(OUTDIR_AK)/Containers.o \
			$(OUTDIR_AK)/PackageInfo.o \
			$(OUTDIR_AK)/DocumentManager.o \
			$(OUTDIR_AK)/MessageDialog.o \
			$(OUTDIR_AK)/GTKUIToolkit.o \
			$(OUTDIR_AK)/GTKDesktop.o \
			$(OUTDIR_AK)/GTKApplication.o \
			$(OUTDIR_AK)/AbstractGTKControl.o \
			$(OUTDIR_AK)/GTKControl.o \
			$(OUTDIR_AK)/GTKWindow.o \
			$(OUTDIR_AK)/GTKControlContext.o \
			$(OUTDIR_AK)/GTKCursor.o \
			$(OUTDIR_AK)/GTKTextControl.o \
			$(OUTDIR_AK)/GTKFileOpenDialog.o \
			$(OUTDIR_AK)/GTKDialog.o \
			$(OUTDIR_AK)/GTKCommandButton.o \
			$(OUTDIR_AK)/GTKToolbar.o 




#NetworkKit objects

NETKIT_OBJECT_FILES_D=$(OUTDIR_NK_D)/DatagramSocket.o \
			$(OUTDIR_NK_D)/NetToolkit.o \
			$(OUTDIR_NK_D)/ServerSocketEvent.o \
			$(OUTDIR_NK_D)/Socket.o \
			$(OUTDIR_NK_D)/SocketEvent.o \
			$(OUTDIR_NK_D)/SocketListeningLoop.o \
			$(OUTDIR_NK_D)/URL.o 

NETKIT_OBJECT_FILES=$(OUTDIR_NK)/DatagramSocket.o \
			$(OUTDIR_NK)/NetToolkit.o \
			$(OUTDIR_NK)/ServerSocketEvent.o \
			$(OUTDIR_NK)/Socket.o \
			$(OUTDIR_NK)/SocketEvent.o \
			$(OUTDIR_NK)/SocketListeningLoop.o \
			$(OUTDIR_NK)/URL.o 


#define the target and it's dependencies
#<target> : <dependency1> <dependency2> ... <dependencyN>
#<tabchar><program to create target> <arguments, usually dependcies from above>

target : 
	echo please choose either "debug", "release" or "all" '(for both debug and release)'


#debug target

debug : FoundationKit_debug GraphicsKit_debug ApplicationKit_debug


#release target

release : FoundationKit_release GraphicsKit_release ApplicationKit_release


#all target, builds release and debug builds
all : debug release


FoundationKit_debug : prep_dirs_FK_D $(FOUNDATION_KIT_SO_D)

FoundationKit_release : prep_dirs_FK $(FOUNDATION_KIT_SO)


GraphicsKit_debug : prep_dirs_GK_D FoundationKit_debug $(GRAPHICS_KIT_SO_D)

GraphicsKit_release : prep_dirs_GK FoundationKit_release $(GRAPHICS_KIT_SO)

ApplicationKit_debug : prep_dirs_AK_D GraphicsKit_debug $(APPLICATION_KIT_SO_D)

ApplicationKit_release : prep_dirs_AK GraphicsKit_release $(APPLICATION_KIT_SO)


NetworkKit_debug : prep_dirs_NK_D FoundationKit_debug $(NETWORK_KIT_SO_D)

NetworkKit_release : prep_dirs_NK FoundationKit_release $(NETWORK_KIT_SO)








#creates the foundationkit output directories for a debug build
#this works by using the test command to test if the OUTPUT_BASE_FK
#or OUTDIR_FK_D directories exist. the -d teslls test that we are
#testing for the existance of the specified directory. the command
#needs to be in `` backward single quotes so that it executes correctly.
#if the directory does not exist then we call mkdir to create it.
prep_dirs_FK_D: 
	if ! `test -d $(OUTPUT_BASE_FK)`;then mkdir $(OUTPUT_BASE_FK);fi;\
	if ! `test -d $(OUTDIR_FK_D)`;then mkdir $(OUTDIR_FK_D);fi;\
	if ! `test -d $(BIN_OUT)`;then mkdir $(BIN_OUT);fi;\
	if ! `test -d $(LIB_OUT)`;then mkdir $(LIB_OUT);fi;

#creates the foundationkit output directories for a release build
prep_dirs_FK: 
	if ! `test -d $(OUTPUT_BASE_FK)`;then mkdir $(OUTPUT_BASE_FK);fi;\
	if ! `test -d $(OUTDIR_FK)`;then mkdir $(OUTDIR_FK);fi;\
	if ! `test -d $(BIN_OUT)`;then mkdir $(BIN_OUT);fi;\
	if ! `test -d $(LIB_OUT)`;then mkdir $(LIB_OUT);fi;

#creates the GraphicsKit output directories for a debug build
prep_dirs_GK_D: 
	if ! `test -d $(OUTPUT_BASE_GK)`;then mkdir $(OUTPUT_BASE_GK);fi;\
	if ! `test -d $(OUTDIR_GK_D)`;then mkdir $(OUTDIR_GK_D);fi;\
	if ! `test -d $(BIN_OUT)`;then mkdir $(BIN_OUT);fi;\
	if ! `test -d $(LIB_OUT)`;then mkdir $(LIB_OUT);fi;

#creates the GraphicsKit output directories for a release build
prep_dirs_GK: 
	if ! `test -d $(OUTPUT_BASE_GK)`;then mkdir $(OUTPUT_BASE_GK);fi;\
	if ! `test -d $(OUTDIR_GK)`;then mkdir $(OUTDIR_GK);fi;\
	if ! `test -d $(BIN_OUT)`;then mkdir $(BIN_OUT);fi;\
	if ! `test -d $(LIB_OUT)`;then mkdir $(LIB_OUT);fi;


#creates the ApplicationKit output directories for a debug build
prep_dirs_AK_D: 
	if ! `test -d $(OUTPUT_BASE_AK)`;then mkdir $(OUTPUT_BASE_AK);fi;\
	if ! `test -d $(OUTDIR_AK_D)`;then mkdir $(OUTDIR_AK_D);fi;\
	if ! `test -d $(BIN_OUT)`;then mkdir $(BIN_OUT);fi;\
	if ! `test -d $(LIB_OUT)`;then mkdir $(LIB_OUT);fi;

#creates the ApplicationKit output directories for a release build
prep_dirs_AK: 
	if ! `test -d $(OUTPUT_BASE_AK)`;then mkdir $(OUTPUT_BASE_AK);fi;\
	if ! `test -d $(OUTDIR_AK)`;then mkdir $(OUTDIR_AK);fi;\
	if ! `test -d $(BIN_OUT)`;then mkdir $(BIN_OUT);fi;\
	if ! `test -d $(LIB_OUT)`;then mkdir $(LIB_OUT);fi;

#creates the NetworkKit output directories for a debug build
prep_dirs_NK_D: 
	if ! `test -d $(OUTPUT_BASE_NK)`;then mkdir $(OUTPUT_BASE_NK);fi;\
	if ! `test -d $(OUTDIR_NK_D)`;then mkdir $(OUTDIR_NK_D);fi;\
	if ! `test -d $(BIN_OUT)`;then mkdir $(BIN_OUT);fi;\
	if ! `test -d $(LIB_OUT)`;then mkdir $(LIB_OUT);fi;

#creates the NetworkKit output directories for a release build
prep_dirs_NK: 
	if ! `test -d $(OUTPUT_BASE_NK)`;then mkdir $(OUTPUT_BASE_NK);fi;\
	if ! `test -d $(OUTDIR_NK)`;then mkdir $(OUTDIR_NK);fi;\
	if ! `test -d $(BIN_OUT)`;then mkdir $(BIN_OUT);fi;\
	if ! `test -d $(LIB_OUT)`;then mkdir $(LIB_OUT);fi;



#so to build the FoundationKit debug shared object library
#i.e. FOUNDATION_KIT_SO_D, we need all the objects (or .o files) 
#specified in OBJECT_FILES_D. If we have those, then to produce the 
#file FOUNDATION_KIT_SO_D, we execute the LINKER executable, passing
#in LINKER_FLAGS, outputting the FOUNDATION_KIT_SO_D file, by linking
#all the OBJECT_FILES_D together

$(FOUNDATION_KIT_SO_D) : $(FK_OBJECT_FILES_D)
	$(LINKER) $(LINKER_FLAGS_D) $(FOUNDATION_KIT_SO_D) $(FK_OBJECT_FILES_D)





$(FK_PRECOMP): $(INC)/FoundationKit.h
	$(CXX) $(CXX_FLAGS_D) -x c++ $(INC)/FoundationKit.h -o $(FK_PRECOMP)
	
#this is the release build target for the 
#FoundationKit shared object library
$(FOUNDATION_KIT_SO) :  $(FK_OBJECT_FILES)
	$(LINKER) $(LINKER_FLAGS) $(FOUNDATION_KIT_SO) $(FK_OBJECT_FILES)



$(LIBAGG_LIB_D) : $(LIBAGG_OBJECTFILES_D)
	$(STATIC_LINKER) $(STATIC_LINKER_FLAGS) $(LIBAGG_LIB_D) $(LIBAGG_OBJECTFILES_D)

$(LIBAGG_LIB) : $(LIBAGG_OBJECTFILES)
	$(STATIC_LINKER) $(STATIC_LINKER_FLAGS) $(LIBAGG_LIB) $(LIBAGG_OBJECTFILES)
	
#this is the debug build target for the 
#GraphicsKit shared object library
$(GRAPHICS_KIT_SO_D) : $(LIBAGG_LIB_D) $(GRAFKIT_OBJECT_FILES_D)
	$(LINKER) $(GK_LINKER_FLAGS_D) $(GRAPHICS_KIT_SO_D) $(GRAFKIT_OBJECT_FILES_D)


#this is the release build target for the 
#GraphicsKit shared object library
$(GRAPHICS_KIT_SO) : $(LIBAGG_LIB) $(GRAFKIT_OBJECT_FILES)
	$(LINKER) $(GK_LINKER_FLAGS) $(GRAPHICS_KIT_SO) $(GRAFKIT_OBJECT_FILES)

#this is the debug build target for the 
#ApplicationKit shared object library
$(APPLICATION_KIT_SO_D) : $(APPKIT_OBJECT_FILES_D)
	$(LINKER) $(AK_LINKER_FLAGS_D) $(APPLICATION_KIT_SO_D) $(APPKIT_OBJECT_FILES_D)


#this is the release build target for the 
#ApplicationKit shared object library
$(APPLICATION_KIT_SO) : $(APPKIT_OBJECT_FILES)
	$(LINKER) $(AK_LINKER_FLAGS) $(APPLICATION_KIT_SO) $(APPKIT_OBJECT_FILES)	

#this is the debug build target for the 
#ApplicationKit shared object library
$(NETWORK_KIT_SO_D) : $(NETKIT_OBJECT_FILES_D)
	$(LINKER) $(NK_LINKER_FLAGS_D) $(NETWORK_KIT_SO_D) $(NETKIT_OBJECT_FILES_D)


#this is the release build target for the 
#ApplicationKit shared object library
$(NETWORK_KIT_SO) : $(NETKIT_OBJECT_FILES)
	$(LINKER) $(NK_LINKER_FLAGS) $(NETWORK_KIT_SO) $(NETKIT_OBJECT_FILES)	




###########################################################
#
#DEBUG and RELEASE FILES
#now for the Debug and Release source definitions 
#
###########################################################

include FoundationKitObjects.mak

include LibAGGObjects.mak

include GraphicsKitObjects.mak

include ApplicationKitObjects.mak


include NetworkKitObjects.mak




#to clean just run "make clean-debug" 
#note that clean does not depend on anything else
clean-FoundationKit-debug :
	rm $(FK_OBJECT_FILES_D)
	rm $(FOUNDATION_KIT_SO_D)

clean-FoundationKit-release :
	rm $(FK_OBJECT_FILES)
	rm $(FOUNDATION_KIT_SO)

clean-GraphicsKit-debug : clean-FoundationKit-debug
	rm $(GRAFKIT_OBJECT_FILES_D)
	rm $(GRAPHICS_KIT_SO_D)

clean-GraphicsKit-release : clean-FoundationKit-release
	rm $(GRAFKIT_OBJECT_FILES)
	rm $(GRAPHICS_KIT_SO)

clean-ApplicationKit-debug : clean-GraphicsKit-debug
	rm $(APPKIT_OBJECT_FILES_D)
	rm $(APPLICATION_KIT_SO_D)

clean-ApplicationKit-release : clean-GraphicsKit-release
	rm $(APPKIT_OBJECT_FILES)
	rm $(APPLICATION_KIT_SO)	


clean-NetworkKit-debug : clean-FoundationKit-debug
	rm $(NETKIT_OBJECT_FILES_D)
	rm $(NETWORK_KIT_SO_D)

clean-NetworkKit-release : clean-FoundationKit-release
	rm $(NETKIT_OBJECT_FILES)
	rm $(NETWORK_KIT_SO)

clean-debug : 
	rm $(FK_OBJECT_FILES_D)
	rm $(GRAFKIT_OBJECT_FILES_D)
	rm $(APPKIT_OBJECT_FILES_D)
	rm $(NETKIT_OBJECT_FILES_D)
	rm $(FOUNDATION_KIT_SO_D)
	rm $(GRAPHICS_KIT_SO_D)
	rm $(APPLICATION_KIT_SO_D)
	rm $(NETWORK_KIT_SO_D)


clean-release : 
	rm $(FK_OBJECT_FILES)
	rm $(GRAFKIT_OBJECT_FILES)
	rm $(APPKIT_OBJECT_FILES)
	rm $(NETKIT_OBJECT_FILES)
	rm $(FOUNDATION_KIT_SO)
	rm $(GRAPHICS_KIT_SO)
	rm $(APPLICATION_KIT_SO)
	rm $(NETWORK_KIT_SO)

clean : clean-debug clean-release

