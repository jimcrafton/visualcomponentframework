//TreeListControls.cpp


#include "ApplicationKit.h"
#include "ControlsKit.h"


using namespace VCF;


class CustomSubItem : public TreeItem::SubItem {
public:
	CustomSubItem( TreeItem* ownerItem ) : TreeItem::SubItem(ownerItem) {
	}

	virtual bool canPaint() {
		return true;
	}

	virtual void paint( GraphicsContext* context, Rect* paintRect ) {
		Color oldColor = *context->getColor();
		context->setColor( Color::getColor("blue") );

		Rect r = *paintRect;
		r.inflate( -2,-1 );
		context->rectangle( &r );
		context->strokePath();

		context->setColor( &oldColor );
	}
};


class TreeListControlsWindow : public Window {
public:

	void removeSelectedItem( MenuItemEvent* e ) {
		TreeItem* selected =  treeList->getSelectedItem();
		if ( NULL != selected ) {
			TreeModel* tm = treeList->getTreeModel();
			tm->deleteNodeItem( selected );
		}
	}

	void changeCaption( MenuItemEvent* e ) {
		TreeItem* selected =  treeList->getSelectedItem();
		if ( NULL != selected ) {
			selected->setCaption( "Oops, I did it again..." );
		}
	}

	void setMultiSelection( MenuItemEvent* e ) {
		treeList->setAllowsMultipleSelection( ! treeList->getAllowsMultipleSelection() );
	}


	void enumerateSelectedItems( MenuItemEvent* e ) {
		Enumerator<TreeItem*>* selectedItems = treeList->getSelectedItems();
		while ( true == selectedItems->hasMoreElements() ) {
			TreeItem* item = selectedItems->nextElement();
			StringUtils::trace( item->getCaption() + "\n" );
		}
	}

	void setFullRowSelect( MenuItemEvent* e ) {
		
		treeList->setDisplayOptions( TreeListControl::tdoShowHierarchyLines | 
										TreeListControl::tdoShowFullRowSelection | 
										TreeListControl::tdoShowColumnHeader ); 


	}

	void setFullRowSelectOff( MenuItemEvent* e ) {
		
		treeList->showFullRowSelection( false ); 

	}

	void doList( TreeItem* item ) {
		TreeItem* next = NULL;
		
		next = item->getChildren()->nextElement();

		while ( next ) {
			StringUtils::trace( "Name: " + next->getCaption() + "\n" );
			doList( next );
			next = next->getNextChildNodeItem();
		}
	}


	TreeListControlsWindow() {
		setCaption( "TreeList" );

		MenuBar* menuBar = new MenuBar();
		setMenuBar( menuBar );
		addComponent( menuBar );

		MenuItem* root = menuBar->getRootMenuItem();
		MenuItem* test = new DefaultMenuItem( "Test", root, menuBar );
		MenuItem* menuItem = new DefaultMenuItem( "Remove Selected Item", test, menuBar );
		menuItem->addMenuItemClickedHandler( 
			new MenuItemEventHandler<TreeListControlsWindow>( this, TreeListControlsWindow::removeSelectedItem, "TreeListControlsWindow::removeSelectedItem" ) );


		menuItem = new DefaultMenuItem( "Set Multi select", test, menuBar );
		menuItem->addMenuItemClickedHandler( 
			new MenuItemEventHandler<TreeListControlsWindow>( this, TreeListControlsWindow::setMultiSelection, "TreeListControlsWindow::setMultiSelection" ) );


		menuItem = new DefaultMenuItem( "Full Row Selection", test, menuBar );
		menuItem->addMenuItemClickedHandler( 
			new MenuItemEventHandler<TreeListControlsWindow>( this, TreeListControlsWindow::setFullRowSelect, "TreeListControlsWindow::setFullRowSelect" ) );


		menuItem = new DefaultMenuItem( "Full Row Selection Off", test, menuBar );
		menuItem->addMenuItemClickedHandler( 
			new MenuItemEventHandler<TreeListControlsWindow>( this, TreeListControlsWindow::setFullRowSelectOff, "TreeListControlsWindow::setFullRowSelectOff" ) );

		menuItem = new DefaultMenuItem( "Change Caption", test, menuBar );
		menuItem->addMenuItemClickedHandler( 
			new MenuItemEventHandler<TreeListControlsWindow>( this, TreeListControlsWindow::changeCaption, "TreeListControlsWindow::changeCaption" ) );
		
		
		ImageList* listIL = new ImageList();
		Image* img = Application::getRunningInstance()->getResourceBundle()->getImage( "MainIcon" );
		listIL->setImageHeight( img->getHeight() );
		listIL->setImageWidth( img->getWidth() );
		listIL->setTransparentColor( &Color(0.0,1.0,0.0) );

		listIL->addImage( img );
		delete img;
		

		img = Application::getRunningInstance()->getResourceBundle()->getImage( "Open" );
		listIL->addImage( img );
		delete img;
		
		img = Application::getRunningInstance()->getResourceBundle()->getImage( "img3" );
		listIL->addImage( img );
		delete img;

		img = Application::getRunningInstance()->getResourceBundle()->getImage( "img4" );
		listIL->addImage( img );
		delete img;

		img = Application::getRunningInstance()->getResourceBundle()->getImage( "img5" );
		listIL->addImage( img );
		delete img;



		popup = new PopupMenu();
		addComponent( popup );

		popup->setRootMenuItem( new DefaultMenuItem() );

		root = popup->getRootMenuItem();

		menuItem = new DefaultMenuItem( "Enumerate Selected items", root, popup );
		menuItem->addMenuItemClickedHandler( 
			new MenuItemEventHandler<TreeListControlsWindow>( this, TreeListControlsWindow::enumerateSelectedItems, "TreeListControlsWindow::enumerateSelectedItems" ) );


		treeList = new TreeListControl();
		treeList->setDefaultItemHeight( 18 );

		treeList->setPopupMenu( popup );

		treeList->setImageList( listIL );

		treeList->showRowLines( true );
		treeList->showColumnLines( true );
		treeList->showFullRowSelection( true );

		addComponent( listIL );

		add( treeList, AlignClient );

		Light3DBorder* border = new Light3DBorder();
		border->setInverted( true ) ;
		treeList->setBorder( border );

		TreeItem* item = treeList->addItem( NULL, "foo 1" );
		
		TreeItem* firstItem = item;

		item->setExpandedImageIndex( 1 );
		item->setState( Item::idsChecked );

		item->addSubItem( "Sub item 1", NULL );
		item->addSubItem( "Sub item 2", NULL );

		CustomSubItem* subItem = new CustomSubItem(item);
		subItem->setCaption( "Sub item 3" );
		item->addSubItem( subItem );
		item->addSubItem( "Sub item 4", NULL );

		TreeItem* child = treeList->addItem( item, "foo 1a" );
		child = treeList->addItem( item, "foo 1b" );

		child->addSubItem( "Sub item 1", NULL );
		
		child = treeList->addItem( item, "foo 1c" );
		child = treeList->addItem( item, "foo 1d" );
		child = treeList->addItem( item, "foo 1e" );
		child = treeList->addItem( item, "foo 1f" );
		child = treeList->addItem( item, "foo 1g" );
		child = treeList->addItem( item, "foo 1h" );
		child = treeList->addItem( item, "foo 1i" );
		child = treeList->addItem( item, "foo 1j" );
		child = treeList->addItem( item, "foo 1k" );

		child->setImageIndex( 2 );

		item = treeList->addItem( NULL, "foo 2" );
		child = treeList->addItem( item, "foo 2a" );
		child = treeList->addItem( item, "foo 2b" );
		child = treeList->addItem( item, "foo 2c" );
		child = treeList->addItem( item, "foo 2d" );
		child = treeList->addItem( item, "foo 2e" );
		child = treeList->addItem( item, "foo 2f" );
		child = treeList->addItem( item, "foo 2g" );
		child = treeList->addItem( item, "foo 2h" );
		child = treeList->addItem( item, "foo 2i" );
		child = treeList->addItem( item, "foo 2j" );
		child = treeList->addItem( item, "foo 2k" );
		child = treeList->addItem( item, "foo 2l" );
		child = treeList->addItem( item, "foo 2m" );
		child = treeList->addItem( item, "foo 2n" );
		child = treeList->addItem( item, "foo 2o" );
		child = treeList->addItem( item, "foo 2p" );
		child = treeList->addItem( item, "foo 2q" );
		child = treeList->addItem( item, "foo 2r" );
		child = treeList->addItem( item, "foo 2s" );
		child = treeList->addItem( item, "foo 2t" );
		child = treeList->addItem( item, "foo 2u" );

		item = child;
		child = treeList->addItem( item, "foo 2ba" );
		child = treeList->addItem( item, "foo 2bb" );
		child = treeList->addItem( item, "foo 2bc" );
		child = treeList->addItem( item, "foo 2bd" );
		child = treeList->addItem( item, "foo 2be" );
		child = treeList->addItem( item, "foo 2bf" );
		child = treeList->addItem( item, "foo 2bg" );
		child = treeList->addItem( item, "foo 2bh" );
		child = treeList->addItem( item, "foo 2bi" );
		child = treeList->addItem( item, "foo 2bj" );
		child = treeList->addItem( item, "foo 2bk" );
		child = treeList->addItem( item, "foo 2bl" );
		child = treeList->addItem( item, "foo 2bm" );
		child = treeList->addItem( item, "foo 2bn" );
		child = treeList->addItem( item, "foo 2bo" );
		child = treeList->addItem( item, "foo 2bp" );
		child = treeList->addItem( item, "foo 2bq" );
		child = treeList->addItem( item, "foo 2br" );
		child = treeList->addItem( item, "foo 2bs" );
		child = treeList->addItem( item, "foo 2bt" );
		child = treeList->addItem( item, "foo 2bu" );
		child = treeList->addItem( item, "foo 2bv" );
		child = treeList->addItem( item, "foo 2bw" );
		child = treeList->addItem( item, "foo 2bx" );
		child = treeList->addItem( item, "foo 2by" );
		child = treeList->addItem( item, "foo 2bz" );
		child = treeList->addItem( item, "foo 2b1" );
		child = treeList->addItem( item, "foo 2b2" );




		treeList->getHeader()->setImageList( listIL );

		ColumnItem* col = treeList->getHeader()->addColumn( "Column 1" );
		col->setImageIndex( 0 );

		col = treeList->getHeader()->addColumn( "Column 2" );
		col->setImageIndex( 3 );

		col = treeList->getHeader()->addColumn( "Column 3" );
		col->setImageIndex( 4 );

		treeList->getHeader()->addColumn( "Column 4" );
		treeList->getHeader()->addColumn( "Column 5" );

		ScrollbarManager* scrollbarManager = new ScrollbarManager();
		addComponent( scrollbarManager );

		scrollbarManager->setHasVerticalScrollbar( true );
		scrollbarManager->setTarget( treeList );

		treeList->showColumnHeader( true );

		treeList->showHierarchyLines( true );

		treeList->ItemSelected.addHandler( new ItemEventHandler<TreeListControlsWindow>( this, TreeListControlsWindow::onTreeItemSelected, "TreeListControlsWindow::onTreeItemSelected" ) );

		treeList->ItemStateChangeRequested.addHandler(
											new ItemEventHandler<TreeListControlsWindow>( this, TreeListControlsWindow::onTreeItemState, "TreeListControlsWindow::onTreeItemState" ) );

		Panel* panel = new Panel();
		panel->setTransparent( true );

		treeList->setTransparent( true );

		panel->setHeight( 35 );
		add( panel, AlignBottom );
		
		status = new Label();
		panel->add( status, AlignClient );
		status->setCaption( "status: " );

		setVisible( true );

		HeaderControl* header = treeList->getHeader();
		header->ColumnItemClicked.addHandler( 
			new MouseEventHandler<TreeListControlsWindow>( this, TreeListControlsWindow::headerColumnClicked, "TreeListControlsWindow::headerColumnClicked" ) );

	}

	virtual ~TreeListControlsWindow(){
		
	};

	void headerColumnClicked( MouseEvent* e ) {
		Dialog::showMessage( "headerColumnClicked" );
	}

	void onTreeItemSelected( ItemEvent* e ) {
		TreeListControl* tlc = (TreeListControl*)e->getSource();

		TreeItem* item = tlc->getSelectedItem();
		if ( item ) {
			String s = "Selected item: " + item->getCaption();
			s += " column width: " + StringUtils::toString( tlc->getColumnWidth( 2 ) );
			status->setCaption( s );
			if ( item->getCaption() == "foo 2b" ) {
				tlc->setColumnWidth( 2, 300 );
			}
		}
	}

	void onTreeItemState( ItemEvent* e ) {
		TreeItem* item = (TreeItem*)e->getSource();
		String s;
		s = StringUtils::format( "State item: %s, state: %d", item->getCaption().c_str(), item->getState() );	
		
		if ( item->getState() == Item::idsChecked ) {
			s += ", Item is Checked!";
		}
		status->setCaption( s );
	}

	Label* status;
	TreeListControl* treeList;
	PopupMenu* popup;
};




class TreeListControlsApplication : public Application {
public:
	TreeListControlsApplication(int argc, char *argv[]): Application(argc,argv){

	}

	virtual bool initRunningApplication(){
		this->setAutoLoadSaveAppState( true );
		bool result = Application::initRunningApplication();
		
		Window* mainWindow = new TreeListControlsWindow();
		setMainWindow(mainWindow);
		//mainWindow->setBounds( &Rect( 100.0, 100.0, 500.0, 500.0 ) );
		
		return result;
	}

};


int main(int argc, char *argv[])
{
	TreeListControlsApplication app(argc,argv);

	Application::main();
	
	return 0;
}

