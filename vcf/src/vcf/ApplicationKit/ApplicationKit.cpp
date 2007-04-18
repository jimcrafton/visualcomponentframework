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

#include "vcf/ApplicationKit/AbstractPropertyEditor.h"
#include "vcf/ApplicationKit/PropertyEditorManager.h"

#include "vcf/ApplicationKit/ComponentEditorManager.h"


using namespace VCF;

static bool ApplicationKitIsInitialized = false;

static int ApplicationKitRefCount = 0;




PropertyEditorManager* PropertyEditorManager::propertyEditorMgr = NULL;

std::map<String,VCF::LibraryApplication*>* VCF::LibraryApplication::namedLibraryAppMap = NULL;

EnumeratorMapContainer<std::map<String,VCF::LibraryApplication*>, VCF::LibraryApplication*>* LibraryApplication::namedLibAppContainer = NULL;

CursorManager* CursorManager::cursorMgrInstance = NULL;

UIShell* UIShell::shellInstance = NULL;

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
		REGISTER_CLASSINFO_EXTERNAL( EnumSetPropertyEditor );
		REGISTER_CLASSINFO_EXTERNAL( CursorPropertyEditor );


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

		UIShell::create();

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

		UIShell::getUIShell()->free();

		CursorManager::getCursorManager()->free();

		ComponentEditorManager::closeComponentEditorManager();

		PropertyEditorManager::closePropertyEditorManager();

		UIToolkit::closeToolkit();

		GraphicsKit::terminate();
	}
}


/**
$Id$
*/
