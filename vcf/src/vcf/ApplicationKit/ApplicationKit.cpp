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
#include "vcf/ApplicationKit/SimpleListModel.h"
#include "vcf/ApplicationKit/InputValidation.h"
#include "vcf/ApplicationKit/FlowLayoutContainer.h"

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

//std::map<String,VCF::LibraryApplication*>* VCF::LibraryApplication::namedLibraryAppMap = NULL;

CursorManager* CursorManager::cursorMgrInstance = NULL;

UIShell* UIShell::shellInstance = NULL;

DockManager* DockManager::dockManagerInstance = NULL;




void ApplicationKit::init( int argc, char** argv )
{
	FoundationKit::internal_resetCommandLineArgs( argc, argv );

	ApplicationKitRefCount ++;
	if ( false == ApplicationKitIsInitialized ) {

		GraphicsKit::init( argc, argv );
		
		REGISTER_CLASSINFO_EXTERNAL( UIComponent );

		REGISTER_CLASSINFO_EXTERNAL( AbstractApplication );
		REGISTER_CLASSINFO_EXTERNAL( Application );

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
		REGISTER_CLASSINFO_EXTERNAL( ListSubItem );
		REGISTER_CLASSINFO_EXTERNAL( ColumnItem );
		
		
		REGISTER_CLASSINFO_EXTERNAL( Model );


		REGISTER_CLASSINFO_EXTERNAL(Document);

		REGISTER_CLASSINFO_EXTERNAL( ListModel );
		REGISTER_CLASSINFO_EXTERNAL( SimpleListModel );		

		REGISTER_CLASSINFO_EXTERNAL( MenuItem );
		REGISTER_CLASSINFO_EXTERNAL(TabModel);
		REGISTER_CLASSINFO_EXTERNAL(TabPage);
		REGISTER_CLASSINFO_EXTERNAL( TextModel );
		REGISTER_CLASSINFO_EXTERNAL( TreeItem );
		REGISTER_CLASSINFO_EXTERNAL( TreeSubItem );
		REGISTER_CLASSINFO_EXTERNAL( ColumnModel );
		REGISTER_CLASSINFO_EXTERNAL( TreeModel );

		

		REGISTER_CLASSINFO_EXTERNAL( TableModel );
		
		
		
		REGISTER_CLASSINFO_EXTERNAL( Border );
		REGISTER_CLASSINFO_EXTERNAL( Basic3DBorder );
		REGISTER_CLASSINFO_EXTERNAL( EtchedBorder );
		REGISTER_CLASSINFO_EXTERNAL( ColorEtchedBorder );
		REGISTER_CLASSINFO_EXTERNAL( Light3DBorder );
		REGISTER_CLASSINFO_EXTERNAL( TitledBorder );

		REGISTER_CLASSINFO_EXTERNAL( Action );
		REGISTER_CLASSINFO_EXTERNAL( AcceleratorKey );



		REGISTER_CLASSINFO_EXTERNAL( Container );
		REGISTER_CLASSINFO_EXTERNAL( AbstractContainer );
		REGISTER_CLASSINFO_EXTERNAL( StandardContainer );
		REGISTER_CLASSINFO_EXTERNAL( ColumnLayoutContainer );
		REGISTER_CLASSINFO_EXTERNAL( PagedContainer );
		
		REGISTER_CLASSINFO_EXTERNAL( HorizontalLayoutContainer );
		REGISTER_CLASSINFO_EXTERNAL( FlowLayoutContainer );

		REGISTER_CLASSINFO_EXTERNAL( Control );
		REGISTER_CLASSINFO_EXTERNAL( CustomControl );
		REGISTER_CLASSINFO_EXTERNAL( ControlContainer );
		REGISTER_CLASSINFO_EXTERNAL( DefaultMenuItem );
		REGISTER_CLASSINFO_EXTERNAL( SeparatorMenuItem );
		REGISTER_CLASSINFO_EXTERNAL( DefaultListModel );
		REGISTER_CLASSINFO_EXTERNAL( DefaultTextModel );
		REGISTER_CLASSINFO_EXTERNAL( DefaultTreeModel );
		REGISTER_CLASSINFO_EXTERNAL( TreeListModel );
		
		REGISTER_CLASSINFO_EXTERNAL( DefaultTableModel );

		REGISTER_CLASSINFO_EXTERNAL( Frame );
		REGISTER_CLASSINFO_EXTERNAL( Dialog );
		REGISTER_CLASSINFO_EXTERNAL( Label );
		REGISTER_CLASSINFO_EXTERNAL( ListControl );
		REGISTER_CLASSINFO_EXTERNAL( DropDownControl );
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
		REGISTER_CLASSINFO_EXTERNAL( TabbedPages );
		REGISTER_CLASSINFO_EXTERNAL( TabSheet );
		
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
		REGISTER_CLASSINFO_EXTERNAL( Toolbar );
		REGISTER_CLASSINFO_EXTERNAL( ToolbarItem );		
		REGISTER_CLASSINFO_EXTERNAL( ToolbarSeparator );
		REGISTER_CLASSINFO_EXTERNAL( StatusBar );
		REGISTER_CLASSINFO_EXTERNAL( ImageComponent );
		REGISTER_CLASSINFO_EXTERNAL( ImageList );
		

		REGISTER_CLASSINFO_EXTERNAL( DropTarget );


		REGISTER_CLASSINFO_EXTERNAL(ObjectModel);
		REGISTER_CLASSINFO_EXTERNAL(ObjectListModel);		
		REGISTER_CLASSINFO_EXTERNAL(ObjectColumnModel);		
		REGISTER_CLASSINFO_EXTERNAL(DictionaryModel);
		REGISTER_CLASSINFO_EXTERNAL(DictionaryListModel);		
		REGISTER_CLASSINFO_EXTERNAL(DictionaryColumnModel);
		REGISTER_CLASSINFO_EXTERNAL(ValueModel);
		REGISTER_CLASSINFO_EXTERNAL(BoolModel);
		REGISTER_CLASSINFO_EXTERNAL(IntModel);
		REGISTER_CLASSINFO_EXTERNAL(DoubleModel);
		REGISTER_CLASSINFO_EXTERNAL(StringModel);
		REGISTER_CLASSINFO_EXTERNAL( StringListModel );



		REGISTER_CLASSINFO_EXTERNAL(ValidationFormatter);
		REGISTER_CLASSINFO_EXTERNAL(NumericFormatter);

		REGISTER_CLASSINFO_EXTERNAL(ValidationRule);
		REGISTER_CLASSINFO_EXTERNAL(NullRule);
		REGISTER_CLASSINFO_EXTERNAL(DataRule);

		REGISTER_CLASSINFO_EXTERNAL(MinRule);
		REGISTER_CLASSINFO_EXTERNAL(MaxRule);
		REGISTER_CLASSINFO_EXTERNAL(EqualsRule);
		REGISTER_CLASSINFO_EXTERNAL(SimilarToRule);

		REGISTER_CLASSINFO_EXTERNAL(ValidationRuleCollection);

		REGISTER_CLASSINFO_EXTERNAL(InputValidator);
		REGISTER_CLASSINFO_EXTERNAL(AlphaNumericValidator);
		REGISTER_CLASSINFO_EXTERNAL(MaskedValidator);
		REGISTER_CLASSINFO_EXTERNAL(NumericValidator);
		REGISTER_CLASSINFO_EXTERNAL(CurrencyValidator);
		

		REGISTER_CLASSINFO_EXTERNAL(DateTimePickerControl);



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

		delete DockManager::getDockManager();

		delete UIShell::getUIShell();

		delete CursorManager::getCursorManager();

		ComponentEditorManager::closeComponentEditorManager();

		PropertyEditorManager::closePropertyEditorManager();

		UIToolkit::closeToolkit();

		GraphicsKit::terminate();
		ApplicationKitRefCount = 0;
	}
}


/**
$Id$
*/
