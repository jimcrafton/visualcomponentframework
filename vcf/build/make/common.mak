##############################################################
#
#
#CVS Log info
#$Log$
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
#Revision 1.1.2.4  2003/02/08 17:55:44  ddiego
#modified the makefiles to have cvs Log entries, so we can keepo track of
#whats going on :)
#
#
#
#common definitions
#
#output directory for debug builds
#
#output base directories
#
#see the prep_dirs_XXX targets for auto creation
#of output directories
#
##############################################################

OUTPUT_BASE_FK=./FoundationKit
OUTPUT_BASE_AK=./ApplicationKit
OUTPUT_BASE_GK=./GraphicsKit
OUTPUT_BASE_NK=./NetworkKit
OUTPUT_BASE_RK=./RemoteObjectKit

OUTDIR_FK_D=$(OUTPUT_BASE_FK)/Debug
OUTDIR_FK=$(OUTPUT_BASE_FK)/Release

OUTDIR_GK_D=$(OUTPUT_BASE_GK)/Debug
OUTDIR_GK=$(OUTPUT_BASE_GK)/Release

OUTDIR_AK_D=$(OUTPUT_BASE_AK)/Debug
OUTDIR_AK=$(OUTPUT_BASE_AK)/Release

OUTDIR_NK_D=$(OUTPUT_BASE_NK)/Debug
OUTDIR_NK=$(OUTPUT_BASE_NK)/Release

#imlib2 include path, used by graphics kit
IMLIB2_INC=/usr/local/include/imlib2

#X11 include path and library, used by ApplicationKit and GraphicsKit
X11_INC=/usr/X11R6/include
X11_LIB=/usr/X11R6/lib


SRC=../../src


INC=../../include

#binary output directory
BIN_OUT=../../bin


#library output directory
LIB_OUT=../../lib


#source file short cut directories
SRC_COM=$(SRC)/COM
SRC_CORE=$(SRC)/core
SRC_DND=$(SRC)/DragDrop
SRC_EVENT=$(SRC)/Events
SRC_EXCPT=$(SRC)/Exceptions
SRC_GRF=$(SRC)/Graphics
SRC_IMPLKIT=$(SRC)/ImplementerKit
SRC_IO=$(SRC)/IO
SRC_NET=$(SRC)/net
SRC_REMOTE=$(SRC)/remote
SRC_UTILS=$(SRC)/Utils


#include short cuts
INC_COM=$(INC)/com
INC_CORE=$(INC)/core
INC_DND=$(INC)/dragdrop
INC_EVENT=$(INC)/events
INC_EXCPT=$(INC)/exceptions
INC_GRF=$(INC)/graphics
INC_IMPL=$(INC)/implementer
INC_IMPLKIT=$(INC)/implementerKit
INC_IO=$(INC)/io
INC_NET=$(INC)/net
INC_REMOTE=$(INC)/remote
INC_UTILS=$(INC)/utils



#toolchain definitions
CXX_INC=$(INC)


#we are using the g++ compiler for C++
CXX=g++

#we are using the g++ linker
LINKER=g++


###########################################################
#
#"make" is pretty stupid. So, unfortunately (AFAIK) to get
#it to understand that we MAY need to check on other headers,
#we have to explicitly tell it to look at these headers.
#Sigh...you'd think stuff like this would be build in...
#
#So this long list of headers is the set of VCF include
#files that each project uses (by and large), and would
#need to be checked for each file that gets compiled. If
#any of these files changes, then the file will need to 
#be compiled again.
#
###########################################################

###########################################################
#FoundationKit headers
###########################################################

FOUNDATIONKIT_HDRS=$(INC)/utils/VCFChar.h \
	$(INC)/utils/VCFProcess.h \
	$(INC)/utils/VCFString.h \
	$(INC)/utils/XMLParser.h \
	$(INC)/utils/Runnable.h \
	$(INC)/utils/Semaphore.h \
	$(INC)/utils/SemaphorePeer.h \
	$(INC)/utils/StringUtils.h \
	$(INC)/utils/SynchObject.h \
	$(INC)/utils/System.h \
	$(INC)/utils/SystemPeer.h \
	$(INC)/utils/SystemToolkit.h \
	$(INC)/utils/Thread.h \
	$(INC)/utils/Mutex.h \
	$(INC)/utils/Parser.h \
	$(INC)/utils/pcre.h \
	$(INC)/utils/pcreposix.h \
	$(INC)/utils/ProcessWithRedirectedIO.h \
	$(INC)/utils/References.h \
	$(INC)/utils/regexx.h \
	$(INC)/utils/Registry.h \
	$(INC)/utils/internal.h \
	$(INC)/utils/Library.h \
	$(INC)/utils/Lock.h \
	$(INC)/utils/Enum.h \
	$(INC)/utils/Enumerator.h \
	$(INC)/utils/ErrorLog.h \
	$(INC)/utils/FilePath.h \
	$(INC)/io/Stream.h \
	$(INC)/io/TextInputStream.h \
	$(INC)/io/TextOutputStream.h \
	$(INC)/io/VariantDataStream.h \
	$(INC)/io/Directory.h \
	$(INC)/io/File.h \
	$(INC)/io/FileIOError.h \
	$(INC)/io/FileNotFound.h \
	$(INC)/io/FileStream.h \
	$(INC)/io/FileStreamPeer.h \
	$(INC)/io/FileUtils.h \
	$(INC)/io/MemoryStream.h \
	$(INC)/io/MemStreamUtils.h \
	$(INC)/io/Persistable.h \
	$(INC)/io/BasicFileError.h \
	$(INC)/io/BasicInputStream.h \
	$(INC)/io/BasicOutputStream.h \
	$(INC)/implementer/ThreadPeer.h \
	$(INC)/implementer/ProcessIORedirectionPeer.h \
	$(INC)/implementer/ProcessPeer.h \
	$(INC)/implementer/RegistryPeer.h \
	$(INC)/implementer/MutexPeer.h \
	$(INC)/implementer/LibraryPeer.h \
	$(INC)/implementer/FilePeer.h \
	$(INC)/exceptions/RuntimeException.h \
	$(INC)/exceptions/ThreadException.h \
	$(INC)/exceptions/TypeCastException.h \
	$(INC)/FoundationKit.h \
	$(INC)/FoundationKitPrivate.h \
	$(INC)/exceptions/OutOfBoundsException.h \
	$(INC)/exceptions/ProcessException.h \
	$(INC)/exceptions/PropertyChangeException.h \
	$(INC)/exceptions/NoImplementerFoundException.h \
	$(INC)/exceptions/NoPeerFoundException.h \
	$(INC)/exceptions/NoSuchElementException.h \
	$(INC)/exceptions/InvalidImplementer.h \
	$(INC)/exceptions/InvalidPeer.h \
	$(INC)/exceptions/InvalidPointerException.h \
	$(INC)/exceptions/NoFreeMemException.h \
	$(INC)/exceptions/BasicException.h \
	$(INC)/exceptions/CantCreateObjectException.h \
	$(INC)/exceptions/ClassNotFound.h \
	$(INC)/exceptions/ErrorStrings.h \
	$(INC)/events/NotifyEvent.h \
	$(INC)/events/NotifyListener.h \
	$(INC)/events/OutputReadyEvent.h \
	$(INC)/events/PropertyChangeEvent.h \
	$(INC)/events/PropertyListener.h \
	$(INC)/core/Class.h \
	$(INC)/core/ClassInfo.h \
	$(INC)/core/ClassRegistry.h \
	$(INC)/core/CommonDefines.h \
	$(INC)/core/FoundationKitSelectLib.h \
	$(INC)/core/FrameworkConfig.h \
	$(INC)/core/Interface.h \
	$(INC)/core/InterfaceClass.h \
	$(INC)/core/Locales.h \
	$(INC)/core/Method.h \
	$(INC)/core/Object.h \
	$(INC)/core/ObjectWithEvents.h \
	$(INC)/core/Point.h \
	$(INC)/core/Property.h \
	$(INC)/core/Rect.h \
	$(INC)/core/Size.h \
	$(INC)/core/VCF.h \
	$(INC)/core/VCFMath.h \
	$(INC)/core/WarningsOffVc.h \
	$(INC)/events/Delegate.h \
	$(INC)/events/Event.h \
	$(INC)/events/EventHandler.h \
	$(INC)/implementerKit/LinuxFilePeer.h \
	$(INC)/implementerKit/LinuxFileStream.h \
	$(INC)/implementerKit/LinuxLibraryPeer.h \
	$(INC)/implementerKit/LinuxMutex.h \
	$(INC)/implementerKit/LinuxPeer.h \
	$(INC)/implementerKit/LinuxProcessIORedirector.h \
	$(INC)/implementerKit/LinuxProcessPeer.h \
	$(INC)/implementerKit/LinuxRegistry.h \
	$(INC)/implementerKit/LinuxSemaphorePeer.h \
	$(INC)/implementerKit/LinuxSystemPeer.h \
	$(INC)/implementerKit/LinuxSystemToolkit.h \
	$(INC)/implementerKit/LinuxThread.h



###########################################################
#GraphicsKit headers, which also pulls in 
#FoundationKit headers
###########################################################

GRAPHICSKIT_HDRS=$(FOUNDATIONKIT_HDRS) $(INC)/events/ImageEvent.h \
	$(INC)/events/ImageListener.h \
	$(INC)/graphics/AbstractImage.h \
	$(INC)/graphics/AlphaGamma.h \
	$(INC)/graphics/Basic3DBorder.h \
	$(INC)/graphics/BasicFill.h \
	$(INC)/graphics/BasicRectangle.h \
	$(INC)/graphics/BasicStroke.h \
	$(INC)/graphics/Border.h \
	$(INC)/graphics/Circle.h \
	$(INC)/graphics/ClippingRegion.h \
	$(INC)/graphics/Color.h \
	$(INC)/graphics/ColorEtchedBorder.h \
	$(INC)/graphics/Composition.h \
	$(INC)/graphics/ControlGraphicsContext.h \
	$(INC)/graphics/Curve.h \
	$(INC)/graphics/DrawToolkit.h \
	$(INC)/graphics/Ellipse.h \
	$(INC)/graphics/EtchedBorder.h \
	$(INC)/graphics/Fill.h \
	$(INC)/graphics/Filter.h \
	$(INC)/graphics/Font.h \
	$(INC)/graphics/FontPeer.h \
	$(INC)/graphics/Glyph.h \
	$(INC)/graphics/GlyphCollection.h \
	$(INC)/graphics/GraphicsContext.h \
	$(INC)/graphics/GraphicsKitSelectLib.h \
	$(INC)/graphics/GraphicsObject.h \
	$(INC)/graphics/GraphicsResourceMgr.h \
	$(INC)/graphics/Image.h \
	$(INC)/graphics/ImageBits.h \
	$(INC)/graphics/ImageList.h \
	$(INC)/graphics/ImageLoader.h \
	$(INC)/graphics/ImageTile.h \
	$(INC)/graphics/Kernel.h \
	$(INC)/graphics/Layer.h \
	$(INC)/graphics/Light3DBorder.h \
	$(INC)/graphics/MagicFMLibType.h \
	$(INC)/graphics/Matrix2D.h \
	$(INC)/graphics/MatrixFunction.h \
	$(INC)/graphics/MgcBezierCurve2.h \
	$(INC)/graphics/MgcCurve2.h \
	$(INC)/graphics/MgcIntegrate.h \
	$(INC)/graphics/MgcMath.h \
	$(INC)/graphics/MgcRTLib.h \
	$(INC)/graphics/MgcSingleCurve2.h \
	$(INC)/graphics/MgcVector2.h \
	$(INC)/graphics/MicroTiles.h \
	$(INC)/graphics/OpenGLContext.h \
	$(INC)/graphics/OpenGLControlContext.h \
	$(INC)/graphics/Path.h \
	$(INC)/graphics/PathEnumerator.h \
	$(INC)/graphics/PixelBuffer.h \
	$(INC)/graphics/Polygon.h \
	$(INC)/graphics/Printable.h \
	$(INC)/graphics/PrintContext.h \
	$(INC)/graphics/RenderableArea.h \
	$(INC)/graphics/RenderPaths.h \
	$(INC)/graphics/Stroke.h \
	$(INC)/graphics/TileManager.h \
	$(INC)/graphics/TitledBorder.h \
	$(INC)/graphics/UVMap.h \
	$(INC)/graphics/VCFOpenGL.h \
	$(INC)/graphics/Vector2D.h \
	$(INC)/GraphicsKit.h \
	$(INC)/GraphicsKitPrivate.h \
	$(INC)/exceptions/NoGraphicsToolkitFoundException.h \
	$(INC)/exceptions/ImageLoaderException.h \
	$(INC)/exceptions/InvalidImage.h \
	$(INC)/implementerKit/GTKContext.h \
	$(INC)/implementerKit/GTKFont.h \
	$(INC)/implementerKit/GTKGraphicsToolkit.h \
	$(INC)/implementerKit/GTKImage.h \
	$(INC)/utils/GraphicsToolKit.h




###########################################################
#ApplicationKit headers, which also pulls in 
#GraphicsKit headers (and by definition FoundationKit headers
###########################################################

APPKIT_HDRS=$(GRAPHICSKIT_HDRS) $(INC)/ApplicationKit.h \
	$(INC)/ApplicationKitPrivate.h \
	$(INC)/com/ClassFactory.h \
	$(INC)/com/COMDataObject.h \
	$(INC)/com/COMDragSource.h \
	$(INC)/com/COMDropTarget.h \
	$(INC)/com/COMObject.h \
	$(INC)/com/COMUtils.h \
	$(INC)/com/ConnectionPoint.h \
	$(INC)/com/ConnectionPointContainer.h \
	$(INC)/com/DataObject.h \
	$(INC)/com/DispatchObject.h \
	$(INC)/com/EnumObject.h \
	$(INC)/com/MemoryAllocator.h \
	$(INC)/com/VCFCOM.h \
	$(INC)/com/ViewableObject.h \
	$(INC)/core/AbstractApplication.h \
	$(INC)/core/AbstractCommand.h \
	$(INC)/core/AbstractComponentEditor.h \
	$(INC)/core/AbstractListModel.h \
	$(INC)/core/AbstractPropertyEditor.h \
	$(INC)/core/AbstractScrollable.h \
	$(INC)/core/AbstractTableModel.h \
	$(INC)/core/AbstractTextModel.h \
	$(INC)/core/AbstractTreeModel.h \
	$(INC)/core/AbstractView.h \
	$(INC)/core/AcceleratorKey.h \
	$(INC)/core/ActiveXControlHost.h \
	$(INC)/core/Application.h \
	$(INC)/core/ApplicationKitSelectLib.h \
	$(INC)/core/ApplicationPeer.h \
	$(INC)/core/BasicTableItemEditor.h \
	$(INC)/core/Button.h \
	$(INC)/core/CheckBoxControl.h \
	$(INC)/core/Clipboard.h \
	$(INC)/core/ClipboardDataObject.h \
	$(INC)/core/ColumnItem.h \
	$(INC)/core/ColumnModel.h \
	$(INC)/core/ComboBoxControl.h \
	$(INC)/core/Command.h \
	$(INC)/core/CommandButton.h \
	$(INC)/core/CommandGroup.h \
	$(INC)/core/CommonColor.h \
	$(INC)/core/CommonDialog.h \
	$(INC)/core/CommonFileBrowse.h \
	$(INC)/core/CommonFileDialog.h \
	$(INC)/core/CommonFileOpen.h \
	$(INC)/core/CommonFileSave.h \
	$(INC)/core/CommonFont.h \
	$(INC)/core/CommonPrint.h \
	$(INC)/core/Component.h \
	$(INC)/core/ComponentEditor.h \
	$(INC)/core/ComponentEditorManager.h \
	$(INC)/core/ComponentInfo.h \
	$(INC)/core/Container.h \
	$(INC)/core/Control.h \
	$(INC)/core/ControlContainer.h \
	$(INC)/core/Controller.h \
	$(INC)/core/Cursor.h \
	$(INC)/core/CursorManager.h \
	$(INC)/core/CustomControl.h \
	$(INC)/core/DataType.h \
	$(INC)/core/DefaultColumnItem.h \
	$(INC)/core/DefaultColumnModel.h \
	$(INC)/core/DefaultListItem.h \
	$(INC)/core/DefaultListModel.h \
	$(INC)/core/DefaultMenuItem.h \
	$(INC)/core/DefaultPropertyEditors.h \
	$(INC)/core/DefaultTableCellItem.h \
	$(INC)/core/DefaultTableModel.h \
	$(INC)/core/DefaultTabModel.h \
	$(INC)/core/DefaultTabPage.h \
	$(INC)/core/DefaultTextModel.h \
	$(INC)/core/DefaultTreeItem.h \
	$(INC)/core/DefaultTreeModel.h \
	$(INC)/core/Desktop.h \
	$(INC)/core/Dialog.h \
	$(INC)/core/Frame.h \
	$(INC)/core/HeaderControl.h \
	$(INC)/core/HTMLBrowserControl.h \
	$(INC)/core/ImageControl.h \
	$(INC)/core/Item.h \
	$(INC)/core/Label.h \
	$(INC)/core/LibraryApplication.h \
	$(INC)/core/ListBoxControl.h \
	$(INC)/core/ListItem.h \
	$(INC)/core/ListModel.h \
	$(INC)/core/ListViewControl.h \
	$(INC)/core/Menu.h \
	$(INC)/core/MenuBar.h \
	$(INC)/core/MenuItem.h \
	$(INC)/core/MenuItemShortcut.h \
	$(INC)/core/MessageDialog.h \
	$(INC)/core/Model.h \
	$(INC)/core/MultilineTextControl.h \
	$(INC)/core/OpenGLControl.h \
	$(INC)/core/Panel.h \
	$(INC)/core/PopupMenu.h \
	$(INC)/core/PropertyEditor.h \
	$(INC)/core/PropertyEditorManager.h \
	$(INC)/core/PushButton.h \
	$(INC)/core/RadioButtonControl.h \
	$(INC)/core/Scrollable.h \
	$(INC)/core/ScrollBarControl.h \
	$(INC)/core/ScrollbarManager.h \
	$(INC)/core/ScrollPeer.h \
	$(INC)/core/Selectable.h \
	$(INC)/core/SelectionListener.h \
	$(INC)/core/Splitter.h \
	$(INC)/core/StatusBar.h \
	$(INC)/core/TabbedPages.h \
	$(INC)/core/TableCellItem.h \
	$(INC)/core/TableControl.h \
	$(INC)/core/TableItemEditor.h \
	$(INC)/core/TableModel.h \
	$(INC)/core/TabModel.h \
	$(INC)/core/TabPage.h \
	$(INC)/core/TextControl.h \
	$(INC)/core/TextModel.h \
	$(INC)/core/TimerComponent.h \
	$(INC)/core/ToggledButton.h \
	$(INC)/core/Toolbar.h \
	$(INC)/core/ToolbarButton.h \
	$(INC)/core/ToolbarDock.h \
	$(INC)/core/ToolbarSeparator.h \
	$(INC)/core/TreeControl.h \
	$(INC)/core/TreeItem.h \
	$(INC)/core/TreeListControl.h \
	$(INC)/core/TreeModel.h \
	$(INC)/core/UIApplication.h \
	$(INC)/core/UndoRedoStack.h \
	$(INC)/core/View.h \
	$(INC)/core/Window.h \
	$(INC)/core/Wizard.h \
	$(INC)/dragdrop/DragSource.h \
	$(INC)/dragdrop/DropTarget.h \
	$(INC)/events/ButtonEvent.h \
	$(INC)/events/ButtonListener.h \
	$(INC)/events/ClipboardEvent.h \
	$(INC)/events/ClipboardListener.h \
	$(INC)/events/ColumnItemEvent.h \
	$(INC)/events/ColumnModelEvent.h \
	$(INC)/events/ColumnModelEventHandler.h \
	$(INC)/events/ComboBoxListener.h \
	$(INC)/events/ComponentEvent.h \
	$(INC)/events/ComponentListener.h \
	$(INC)/events/ControlEvent.h \
	$(INC)/events/ControlListener.h \
	$(INC)/events/DragEvent.h \
	$(INC)/events/DragScrollEvent.h \
	$(INC)/events/DragSourceListener.h \
	$(INC)/events/DropEvent.h \
	$(INC)/events/DropTargetListener.h \
	$(INC)/events/FocusEvent.h \
	$(INC)/events/FocusListener.h \
	$(INC)/events/FrameEvent.h \
	$(INC)/events/HelpEvent.h \
	$(INC)/events/HelpListener.h \
	$(INC)/events/ImageListEvent.h \
	$(INC)/events/ImageListListener.h \
	$(INC)/events/ItemEditorEvent.h \
	$(INC)/events/ItemEditorListener.h \
	$(INC)/events/ItemEvent.h \
	$(INC)/events/ItemListener.h \
	$(INC)/events/KeyboardEvent.h \
	$(INC)/events/KeyboardListener.h \
	$(INC)/events/Listener.h \
	$(INC)/events/ListModelEvent.h \
	$(INC)/events/ListModelListener.h \
	$(INC)/events/MenuItemEvent.h \
	$(INC)/events/MenuItemListener.h \
	$(INC)/events/MenuListener.h \
	$(INC)/events/ModelEvent.h \
	$(INC)/events/ModelListener.h \
	$(INC)/events/ModelValidationListener.h \
	$(INC)/events/MouseEvent.h \
	$(INC)/events/MouseListener.h \
	$(INC)/events/ScrollEvent.h \
	$(INC)/events/ScrollListener.h \
	$(INC)/events/SelectionListener.h \
	$(INC)/events/TableModelEvent.h \
	$(INC)/events/TableModelListener.h \
	$(INC)/events/TabModelEvent.h \
	$(INC)/events/TabModelListener.h \
	$(INC)/events/TextEvent.h \
	$(INC)/events/TextModelListener.h \
	$(INC)/events/ThreadEvent.h \
	$(INC)/events/TimerEvent.h \
	$(INC)/events/TimerListener.h \
	$(INC)/events/ToolTipEvent.h \
	$(INC)/events/ToolTipListener.h \
	$(INC)/events/TreeModelEvent.h \
	$(INC)/events/TreeModelListener.h \
	$(INC)/events/UndoRedoEvent.h \
	$(INC)/events/UndoRedoListener.h \
	$(INC)/events/ValidationEvent.h \
	$(INC)/events/WhatsThisHelpEvent.h \
	$(INC)/events/WhatsThisHelpListener.h \
	$(INC)/events/WindowEvent.h \
	$(INC)/events/WindowListener.h \
	$(INC)/exceptions/ApplicationException.h \
	$(INC)/exceptions/BadComponentStateException.h \
	$(INC)/exceptions/BadImageBitsException.h \
	$(INC)/exceptions/BadModelStateException.h \
	$(INC)/exceptions/COMException.h \
	$(INC)/exceptions/DataTypeNotSupportedException.h \
	$(INC)/exceptions/InvalidStateException.h \
	$(INC)/exceptions/NoToolKitFoundException.h \
	$(INC)/exceptions/ResourceException.h \
	$(INC)/implementer/AppKitPeerConfig.h \
	$(INC)/implementer/ApplicationPeer.h \
	$(INC)/implementer/ButtonPeer.h \
	$(INC)/implementer/ClipboardPeer.h \
	$(INC)/implementer/CommonDialogPeer.h \
	$(INC)/implementer/ContextPeer.h \
	$(INC)/implementer/ControlPeer.h \
	$(INC)/implementer/CursorPeer.h \
	$(INC)/implementer/CustomControlPeer.h \
	$(INC)/implementer/DataObjectPeer.h \
	$(INC)/implementer/DesktopPeer.h \
	$(INC)/implementer/DialogPeer.h \
	$(INC)/implementer/DragDropPeer.h \
	$(INC)/implementer/DropTargetPeer.h \
	$(INC)/implementer/HeaderPeer.h \
	$(INC)/implementer/HTMLBrowserPeer.h \
	$(INC)/implementer/ListviewPeer.h \
	$(INC)/implementer/MenuBarPeer.h \
	$(INC)/implementer/MenuItemPeer.h \
	$(INC)/implementer/OpenGLPeer.h \
	$(INC)/implementer/PopupMenuPeer.h \
	$(INC)/implementer/PrintContextPeer.h \
	$(INC)/implementer/PrintPeer.h \
	$(INC)/implementer/ResourceStreamPeer.h \
	$(INC)/implementer/ScrollbarPeer.h \
	$(INC)/implementer/ScrollPeer.h \
	$(INC)/implementer/TextPeer.h \
	$(INC)/implementer/TreePeer.h \
	$(INC)/implementer/WindowPeer.h \
	$(INC)/implementerKit/HTMLBrowserPeer.h \
	$(INC)/io/ComponentInputStream.h \
	$(INC)/io/ComponentOutputStream.h \
	$(INC)/io/ResourceStream.h \
	$(INC)/io/ResourceStreamPeer.h \
	$(INC)/io/VFFInputStream.h \
	$(INC)/io/VFFOutputStream.h \
	$(INC)/ModelViewKit.h \
	$(INC)/utils/Resource.h \
	$(INC)/utils/ResourceBundle.h \
	$(INC)/utils/UIMetricsManager.h \
	$(INC)/utils/UIToolkit.h




###########################################################
#NetworkKit headers, which also pulls in 
#FoundationKit headers
###########################################################

NETWORKKIT_HDRS=$(FOUNDATIONKIT_HDRS) $(INC)/net/DatagramSocket.h \
	$(INC)/net/NetToolkit.h \
	$(INC)/net/NetworkKitSelectLib.h \
	$(INC)/net/ServerSocketEvent.h \
	$(INC)/net/Socket.h \
	$(INC)/net/SocketEvent.h \
	$(INC)/net/SocketException.h \
	$(INC)/net/SocketListener.h \
	$(INC)/net/SocketListeningLoop.h \
	$(INC)/net/SocketPeer.h \
	$(INC)/net/URL.h \
	$(INC)/NetworkKit.h \
	$(INC)/NetworkKitPrivate.h



###########################################################
#RemoteObjectKit headers, which also pulls in 
#NetworkKit headers and FoundationKit headers
###########################################################

REMOTEOBJECTKIT_HDRS=$(NETWORKKIT_HDRS) $(INC)/remote/AbstractDistributedApplication.h \
	$(INC)/remote/ClassRegistryEntry.h \
	$(INC)/remote/ClassServerInstance.h \
	$(INC)/remote/DistributedClassRegistry.h \
	$(INC)/remote/DistributedException.h \
	$(INC)/remote/InstanceID.h \
	$(INC)/remote/Proxy.h \
	$(INC)/remote/RemoteCommon.h \
	$(INC)/remote/RemoteConfig.h \
	$(INC)/remote/RemoteObjectKit.h \
	$(INC)/remote/RemoteObjectKitSelectLib.h \
	$(INC)/RemoteObjectKit.h



