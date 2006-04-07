#ifndef _VCF_APPLICATIONKIT_H__
#define _VCF_APPLICATIONKIT_H__
//ApplicationKit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/ApplicationKitSelectLib.h"

#include "vcf/GraphicsKit/GraphicsKit.h"

#include "vcf/ApplicationKit/KeyboardEvent.h"
#include "vcf/ApplicationKit/ScrollEvent.h"
#include "vcf/ApplicationKit/ValidationEvent.h"

#include "vcf/FoundationKit/InvalidStateException.h"
#include "vcf/ApplicationKit/ApplicationException.h"
#include "vcf/ApplicationKit/BadComponentStateException.h"
#include "vcf/ApplicationKit/BadModelStateException.h"

#include "vcf/ApplicationKit/ItemEditorEvent.h"


#include "vcf/ApplicationKit/ComponentEvent.h"
#include "vcf/ApplicationKit/Component.h"

/**
Action classes
*/
#include "vcf/ApplicationKit/Action.h"
#include "vcf/ApplicationKit/ActionEvent.h"


/**
*Core model classes fopr the application kit
*/


#include "vcf/ApplicationKit/ModelEvent.h"
#include "vcf/ApplicationKit/Model.h"

#include "vcf/ApplicationKit/ItemEvent.h"
#include "vcf/ApplicationKit/Item.h"


/**
*Menus and menu items
*/
#include "vcf/ApplicationKit/MenuItem.h"
#include "vcf/ApplicationKit/MenuItemEvent.h"
#include "vcf/ApplicationKit/DefaultMenuItem.h"


#include "vcf/ApplicationKit/Menu.h"
#include "vcf/ApplicationKit/MenuBar.h"
#include "vcf/ApplicationKit/PopupMenu.h"



/**
*Clipboard
*/
#include "vcf/ApplicationKit/DataTypeNotSupportedException.h"
#include "vcf/ApplicationKit/DataObject.h"
#include "vcf/ApplicationKit/ClipboardEvent.h"
#include "vcf/ApplicationKit/Clipboard.h"

/**
*Drag Drop
*/
#include "vcf/ApplicationKit/DragSource.h"
#include "vcf/ApplicationKit/DragEvent.h"
#include "vcf/ApplicationKit/DragScrollEvent.h"

#include "vcf/ApplicationKit/DropEvent.h"


#include "vcf/ApplicationKit/DropTarget.h"


/**
*Application services
*/
#include "vcf/ApplicationKit/AbstractApplication.h"
#include "vcf/ApplicationKit/LibraryApplication.h"
#include "vcf/ApplicationKit/Application.h"



#include "vcf/ApplicationKit/Border.h"

#include "vcf/ApplicationKit/Cursor.h"

/**
*Control events
*/
#include "vcf/ApplicationKit/MouseEvent.h"
#include "vcf/ApplicationKit/FocusEvent.h"
#include "vcf/ApplicationKit/ToolTipEvent.h"
#include "vcf/ApplicationKit/WhatsThisHelpEvent.h"
#include "vcf/ApplicationKit/HelpEvent.h"

#include "vcf/ApplicationKit/ControlGraphicsContext.h"

/**
*Views
*/
#include "vcf/ApplicationKit/View.h"
#include "vcf/ApplicationKit/AbstractView.h"

/**
*Keyboard accelerators
*/
#include "vcf/ApplicationKit/AcceleratorKey.h"

/**
*Toolkit stuff
*/
#include "vcf/FoundationKit/NoToolKitFoundException.h"
#include "vcf/ApplicationKit/UIMetricsManager.h"
#include "vcf/ApplicationKit/UIPolicyManager.h"
#include "vcf/ApplicationKit/UIToolkit.h"



#include "vcf/ApplicationKit/Control.h"
#include "vcf/ApplicationKit/ControlEvent.h"


#include "vcf/ApplicationKit/CustomControl.h"
#include "vcf/ApplicationKit/Container.h"
#include "vcf/ApplicationKit/ControlContainer.h"
#include "vcf/ApplicationKit/Containers.h"

#include "vcf/ApplicationKit/FrameEvent.h"
#include "vcf/ApplicationKit/WindowEvent.h"

#include "vcf/ApplicationKit/Frame.h"

#include "vcf/ApplicationKit/Dialog.h"

/**
*Common dialogs, file open, file save, etc
*/
#include "vcf/ApplicationKit/CommonDialog.h"

#include "vcf/ApplicationKit/CommonFileDialog.h"
#include "vcf/ApplicationKit/CommonFileOpenDialog.h"
#include "vcf/ApplicationKit/CommonFileSaveDialog.h"
#include "vcf/ApplicationKit/CommonFontDialog.h"
#include "vcf/ApplicationKit/CommonPrintDialog.h"
#include "vcf/ApplicationKit/CommonColorDialog.h"
#include "vcf/ApplicationKit/CommonFileBrowseDialog.h"

/**
*Button classes
*/
#include "vcf/ApplicationKit/Button.h"
#include "vcf/ApplicationKit/ButtonEvent.h"


#include "vcf/ApplicationKit/Window.h"
#include "vcf/ApplicationKit/Scrollable.h"


#include "vcf/ApplicationKit/CursorManager.h"

#include "vcf/ApplicationKit/ImageListEvent.h"
#include "vcf/ApplicationKit/ImageList.h"


/**
*Borders
*/
#include "vcf/ApplicationKit/Basic3DBorder.h"
#include "vcf/ApplicationKit/Light3DBorder.h"


/**
*Desktop class
*/
#include "vcf/ApplicationKit/Desktop.h"



/**
*Application undo redo support - uses command pattern
*/
#include "vcf/ApplicationKit/Command.h"
#include "vcf/ApplicationKit/CommandGroup.h"
#include "vcf/ApplicationKit/UndoRedoEvent.h"
#include "vcf/ApplicationKit/AbstractCommand.h"
#include "vcf/ApplicationKit/UndoRedoStack.h"


/**
*Scrolling support
*/
#include "vcf/ApplicationKit/AbstractScrollable.h"
#include "vcf/ApplicationKit/ScrollbarManager.h"

#include "vcf/ApplicationKit/ComponentInfo.h"


/**
*Timers
*/
#include "vcf/ApplicationKit/TimerEvent.h"
#include "vcf/ApplicationKit/TimerComponent.h"


/**
*peer classes
*/

#include "vcf/ApplicationKit/CursorPeer.h"
#include "vcf/ApplicationKit/ApplicationPeer.h"
#include "vcf/ApplicationKit/ClipboardPeer.h"
#include "vcf/ApplicationKit/DataObjectPeer.h"
#include "vcf/ApplicationKit/DragDropPeer.h"
#include "vcf/ApplicationKit/DropTargetPeer.h"
#include "vcf/ApplicationKit/CommonDialogPeer.h"
#include "vcf/ApplicationKit/ControlPeer.h"


/**
\class ApplicationKit ApplicationKit.h "vcf/ApplicationKit/ApplicationKit.h"
*/
namespace VCF {
	class APPLICATIONKIT_API ApplicationKit {
	public:
		/**
		*initializes the Application Kit runtime.
		*This includes registering the basic classes in the runtime system
		*This MUST be called first off in the main() function of the app
		*This will automatically call
			FoundationKit::init();
		and
			GraphicsKit::init();
		*/
		static void init( int argc, char** argv );

		static void terminate();
	};
};


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:21  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.4.4  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.3.4.3  2006/02/17 05:23:05  ddiego
*fixed some bugs, and added support for minmax in window resizing, as well as some fancier control over tooltips.
*
*Revision 1.3.4.2  2005/09/02 01:01:20  ddiego
*changed some of the common dialogs around, was using a less clear class name.
*
*Revision 1.3.4.1  2005/08/28 05:14:17  ddiego
*small changes to component editor class.
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/08/21 21:06:52  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/04/29 21:13:58  ddiego
*made a few changes to the new OpenGLKit files, adjusting where the
*CVS log was put, and changed a few cases for the export-import definition
*was used. Also added the two projects to the vcfAllProject workspace
*and added the script generated VC7 and VC71 projects as well.
*
*Revision 1.1.2.3  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:25  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.8.4.2  2004/04/26 21:58:14  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8.4.1  2004/04/21 02:17:07  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.8  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.2.5  2003/12/08 05:05:27  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.7.2.4  2003/09/21 04:15:15  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.7.2.3  2003/09/12 00:09:31  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.7.2.2  2003/09/02 02:11:14  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.7.2.1  2003/08/23 19:09:43  marcelloptr
*minor fixes + automatic library selection of with vc6, vc70 and vc71
*
*Revision 1.7  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.6.2.5  2003/07/06 01:20:28  ddiego
*added basic Document/View classes. These are based on the existing MVC
*architecture already present in the framework already, and exapnd on the
*existing functionality. Many of the ideas were influenced by the NeXT/Cocoa's
*Document/View architecture. Some of the new features are:
*  automatic creation and connection of the various parts including the
*  Document, view and Window.
*  Automatic default menu items, to ensure standard UI conformance. The menu
*  items are merged with an existing ones.
*  Automatic clipboard support in the form of cut/copy/paste and connecting this
*  directly to the current document
*  Support for Undo/Redo item as well, including default menu item validation
*  Default support for opening and saving documents, including presenting the
*  correct Dialogs to the User, and properly filling the default data, based
*  on the documents data.
*  Support for multiple document types
*  Support for differnt Document Interface policies. Currently we support
*  SDI (Single Document Interface) and MDI (Multiple Document Interface)
*
*Revision 1.6.2.4  2003/06/28 04:43:19  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.6.2.3  2003/06/27 03:10:58  ddiego
*got rid of some redundant junk in the Clipboard and DataObject
*classes. Instead of a rather dippy use of the DataType calss, we now simply
*use pure mime-types to identify the various "flavours" of data.
*
*Revision 1.6.2.2  2003/05/30 04:13:10  ddiego
*added the commandLine class
*changed the intialization functions for teh FoundationKit, GraphicsKit, and
*ApplicationKit to take command line parameters
*FoundationKit now allows you to retreive the commandline (it's stored)
*start up has changed from appMain() to main()
*added a custom GTK widget class for use in the various GTK peers - this will
*allow us to specify absolute positioning and let the VCF handle layout
*issues
*Miscellaneous clean in various interfaces
*removed the Rect, Point, and Size classes from the FoundationKit
*and moved them to the GraphicsKit
*
*Revision 1.6.2.1  2003/05/25 19:07:08  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.6  2003/05/17 20:36:57  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.1  2003/03/23 03:23:42  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.2.4  2003/01/08 00:19:41  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4.2.3  2002/12/27 23:04:28  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.4.2.2  2002/12/25 22:06:11  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.4.2.1  2002/12/02 00:38:34  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.4  2002/11/18 00:46:07  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.3.4.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.3  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.2.6.3  2002/08/13 04:28:22  ddiego
*bugs fixed:
*[ 585085 ] Can't get at multi selected filenames - this was just a matter of exposing a function that was already available in the
*peer class
*
*features:
*58839 Add a method to query closing a Frame, this required a change that included added a new event (FrameEvent and the corresponding
*FrameEventHandler) and a method, bool Frame::allowClose()
*
*Also made fixes in the VCF Builder to now take advantage of this, so the MainWindow class will now register an event
*handler to handler the FrameClosing event, and attempt to set the current workspace to NULL. If this does not happen then
*the closing event will fail and prevent the widnow from being shutdown. Woo hoo !
*
*Revision 1.2.6.2  2002/07/03 07:13:00  marcelloptr
*minor fixes
*
*Revision 1.2.6.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.2  2002/04/27 15:52:15  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.1.2.1  2002/04/08 21:08:51  zzack
*created
*
*Revision 1.18  2002/03/20 02:46:54  ddiego
*fixes an issue with with changes to an items state not correctly being reflected in the
*TreeListControl
*Also makes another adjustment to the scroll positioning when collapsing nodes
*
*Revision 1.17.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.17  2002/02/17 01:07:14  ddiego
*removed OpenGL stuff to minimize memory impact. It will be in it's own
*module. Also fixed bugs:
*[ #500694 ] Combo text over writing down arrow
*[ #498481 ] pasting into edit control
*
*Revision 1.16  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_APPLICATIONKIT_H__


