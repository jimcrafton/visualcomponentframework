//ApplicationKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/DefaultPropertyEditors.h"

#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/ApplicationKitRTTI.inl"

#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"
#include "vcf/ApplicationKit/ColumnLayoutContainer.h"

using namespace VCF;

static bool ApplicationKitIsInitialized = false;

static int ApplicationKitRefCount = 0;



std::map<String,std::vector<Class*>*>* Component::registeredComponentMap = NULL;

EnumeratorContainer<std::vector<Class*>,Class*>* Component::registeredCompContainer = NULL;

EnumeratorContainer<std::vector<String>,String>* Component::registeredCategoryContainer = NULL;

std::vector<String>* Component::registeredCategory = NULL;

PropertyEditorManager* PropertyEditorManager::propertyEditorMgr = NULL;

std::map<String,VCF::LibraryApplication*>* VCF::LibraryApplication::namedLibraryAppMap = NULL;

EnumeratorMapContainer<std::map<String,VCF::LibraryApplication*>, VCF::LibraryApplication*>* LibraryApplication::namedLibAppContainer = NULL;

CursorManager* CursorManager::cursorMgrInstance = NULL;

Desktop* Desktop::desktopInstance = NULL;

DockManager* DockManager::dockManagerInstance = NULL;




void ApplicationKit::init( int argc, char** argv )
{
	ApplicationKitRefCount ++;
	if ( false == ApplicationKitIsInitialized ) {

		GraphicsKit::init( argc, argv );
		
		
		REGISTER_CLASSINFO_EXTERNAL( AbstractPropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( ImagePropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( ImageFilenamePropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( DefaultMenuItemPropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( FontPropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( ColorPropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( EnumPropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( StringPropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( BoolPropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( DoublePropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( IntegerPropertyEditor );


		REGISTER_CLASSINFO_EXTERNAL( Item );
		REGISTER_CLASSINFO_EXTERNAL( ListItem );
		REGISTER_CLASSINFO_EXTERNAL( Model );

		REGISTER_CLASSINFO_EXTERNAL(AbstractModel);
		REGISTER_CLASSINFO_EXTERNAL(Document);

//		REGISTER_CLASSINFO_EXTERNAL( ListModel );
		REGISTER_CLASSINFO_EXTERNAL( MenuItem );
//		REGISTER_CLASSINFO_EXTERNAL(TabModel);
		REGISTER_CLASSINFO_EXTERNAL(TabPage);
//		REGISTER_CLASSINFO_EXTERNAL( TextModel );
		REGISTER_CLASSINFO_EXTERNAL( TreeItem );
//		REGISTER_CLASSINFO_EXTERNAL( TreeModel );
		
//		REGISTER_CLASSINFO_EXTERNAL( AbstractListModel );
//		REGISTER_CLASSINFO_EXTERNAL( AbstractTextModel );
//		REGISTER_CLASSINFO_EXTERNAL( AbstractTreeModel );
		REGISTER_CLASSINFO_EXTERNAL( Component );
		
		REGISTER_CLASSINFO_EXTERNAL( Border );
		REGISTER_CLASSINFO_EXTERNAL( Basic3DBorder );
		REGISTER_CLASSINFO_EXTERNAL( EtchedBorder );
		REGISTER_CLASSINFO_EXTERNAL( ColorEtchedBorder );
		REGISTER_CLASSINFO_EXTERNAL( Light3DBorder );
		REGISTER_CLASSINFO_EXTERNAL( TitledBorder );

		REGISTER_CLASSINFO_EXTERNAL( Container );
		REGISTER_CLASSINFO_EXTERNAL( AbstractContainer );
		REGISTER_CLASSINFO_EXTERNAL( StandardContainer );
		REGISTER_CLASSINFO_EXTERNAL( ColumnLayoutContainer );
		REGISTER_CLASSINFO_EXTERNAL( HorizontalLayoutContainer );

		REGISTER_CLASSINFO_EXTERNAL( Control );
		REGISTER_CLASSINFO_EXTERNAL( CustomControl );
		REGISTER_CLASSINFO_EXTERNAL( ControlContainer );
		REGISTER_CLASSINFO_EXTERNAL( TabbedPages );
		REGISTER_CLASSINFO_EXTERNAL( DefaultListItem );
		REGISTER_CLASSINFO_EXTERNAL( DefaultMenuItem );
		REGISTER_CLASSINFO_EXTERNAL( DefaultListModel );
		REGISTER_CLASSINFO_EXTERNAL( DefaultTextModel );
		REGISTER_CLASSINFO_EXTERNAL( DefaultTreeItem );
		REGISTER_CLASSINFO_EXTERNAL( DefaultTreeModel );
		REGISTER_CLASSINFO_EXTERNAL( Frame );
		REGISTER_CLASSINFO_EXTERNAL( Dialog );
		REGISTER_CLASSINFO_EXTERNAL( Label );
		REGISTER_CLASSINFO_EXTERNAL( ListViewControl );
		REGISTER_CLASSINFO_EXTERNAL( Panel );
		REGISTER_CLASSINFO_EXTERNAL( TextControl );
		REGISTER_CLASSINFO_EXTERNAL( MultilineTextControl );
		REGISTER_CLASSINFO_EXTERNAL(TreeControl );
		REGISTER_CLASSINFO_EXTERNAL(Window );
		REGISTER_CLASSINFO_EXTERNAL( ToggledButton );
		REGISTER_CLASSINFO_EXTERNAL( CheckBoxControl );
		REGISTER_CLASSINFO_EXTERNAL( RadioButtonControl );
		REGISTER_CLASSINFO_EXTERNAL( Menu );
		REGISTER_CLASSINFO_EXTERNAL( MenuBar );
		REGISTER_CLASSINFO_EXTERNAL( PopupMenu );
		REGISTER_CLASSINFO_EXTERNAL( ListBoxControl );
		
		REGISTER_CLASSINFO_EXTERNAL( CommandButton );
		//REGISTER_CLASSINFO_EXTERNAL( OpenGLControl );
		REGISTER_CLASSINFO_EXTERNAL( ComboBoxControl );
		REGISTER_CLASSINFO_EXTERNAL( ImageControl );
//		REGISTER_CLASSINFO_EXTERNAL( ImageFilenameString );
		REGISTER_CLASSINFO_EXTERNAL( HTMLBrowserControl );
		REGISTER_CLASSINFO_EXTERNAL( TimerComponent );
		REGISTER_CLASSINFO_EXTERNAL( ScrollbarManager );
		REGISTER_CLASSINFO_EXTERNAL( SystemTray );
		REGISTER_CLASSINFO_EXTERNAL( PushButton );
		REGISTER_CLASSINFO_EXTERNAL( SliderControl );
		REGISTER_CLASSINFO_EXTERNAL( ProgressControl );
		REGISTER_CLASSINFO_EXTERNAL( TableControl );
		REGISTER_CLASSINFO_EXTERNAL( Splitter );
		REGISTER_CLASSINFO_EXTERNAL( TreeListControl );
		REGISTER_CLASSINFO_EXTERNAL( HeaderControl );
		//REGISTER_CLASSINFO_EXTERNAL( ToolbarDock );






		PropertyEditorManager::initPropertyEditorManager();

		ComponentEditorManager::initComponentEditorManager();

		UIToolkit::initToolKit();

		LibraryApplication::initLibraryRegistrar();

		DockManager::create();

		Desktop::create();

		CursorManager::create();

		//Component::registerComponent( "VCF::ToolbarDock", STANDARD_CATEGORY );
		/**
		*Register known classes here
		*/

	}
	ApplicationKitIsInitialized = true;
}

void ApplicationKit::terminate()
{
	if ( ApplicationKitRefCount > 0 ){
		ApplicationKitRefCount--;
	}

	if ( ApplicationKitRefCount == 0 ) {

		LibraryApplication::clearLibraryRegistrar();

		DockManager::getDockManager()->free();

		Desktop::getDesktop()->free();

		CursorManager::getCursorManager()->free();

		ComponentEditorManager::closeComponentEditorManager();

		PropertyEditorManager::closePropertyEditorManager();

		UIToolkit::closeToolkit();

		GraphicsKit::terminate();
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:51  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.3  2005/03/09 05:11:19  ddiego
*fixed property editor class.
*
*Revision 1.3.2.2  2005/03/06 22:50:58  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.3.2.1  2005/02/28 04:51:55  ddiego
*fixed issue in handling componenent state and events when in design mode
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.30.2.1  2004/04/21 02:17:24  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.30  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.27.2.2  2004/01/15 05:35:04  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.27.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.27  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.26.2.3  2003/10/23 04:24:52  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.26.2.2  2003/09/22 01:48:04  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.26.2.1  2003/09/12 00:09:18  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.26  2003/08/09 02:56:44  ddiego
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
*Revision 1.25.2.2  2003/07/06 01:20:29  ddiego
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
*Revision 1.25.2.1  2003/05/30 04:13:11  ddiego
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
*Revision 1.25  2003/05/17 20:37:46  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.24.2.1  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.24  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.23.8.4  2003/02/05 01:26:13  notandor
*Fixed a compilation error on VC6SP5
*
*Revision 1.23.8.3  2003/01/08 00:19:57  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.23.8.2  2002/12/27 23:04:58  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.23.8.1  2002/12/02 00:38:36  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.23  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.22.6.2  2002/08/12 02:56:25  ddiego
*changes to code parsing for C++
*
*Revision 1.22.6.1  2002/07/23 20:21:48  ddiego
*finished teh configuration editing, at least a prelim version
*can now read an write the config(s) from a .vcp file and edit them
*successfully - need to do HEAVY debugging to make sure this is OK
*
*Revision 1.22  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.21.4.3  2002/04/27 15:52:39  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.21.4.2  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.21.4.1  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.21  2002/02/17 01:07:15  ddiego
*removed OpenGL stuff to minimize memory impact. It will be in it's own
*module. Also fixed bugs:
*[ #500694 ] Combo text over writing down arrow
*[ #498481 ] pasting into edit control
*
*Revision 1.20  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


