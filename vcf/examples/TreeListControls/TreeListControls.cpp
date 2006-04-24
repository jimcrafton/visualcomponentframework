//TreeListControls.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"


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
		menuItem->MenuItemClicked +=
			new MenuItemEventHandler<TreeListControlsWindow>( this, &TreeListControlsWindow::removeSelectedItem, "TreeListControlsWindow::removeSelectedItem" );


		menuItem = new DefaultMenuItem( "Set Multi select", test, menuBar );
		menuItem->MenuItemClicked +=
			new MenuItemEventHandler<TreeListControlsWindow>( this, &TreeListControlsWindow::setMultiSelection, "TreeListControlsWindow::setMultiSelection" );


		menuItem = new DefaultMenuItem( "Full Row Selection", test, menuBar );
		menuItem->MenuItemClicked +=
			new MenuItemEventHandler<TreeListControlsWindow>( this, &TreeListControlsWindow::setFullRowSelect, "TreeListControlsWindow::setFullRowSelect" );


		menuItem = new DefaultMenuItem( "Full Row Selection Off", test, menuBar );
		menuItem->MenuItemClicked +=
			new MenuItemEventHandler<TreeListControlsWindow>( this, &TreeListControlsWindow::setFullRowSelectOff, "TreeListControlsWindow::setFullRowSelectOff" );

		menuItem = new DefaultMenuItem( "Change Caption", test, menuBar );
		menuItem->MenuItemClicked +=
			new MenuItemEventHandler<TreeListControlsWindow>( this, &TreeListControlsWindow::changeCaption, "TreeListControlsWindow::changeCaption" );


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

		root = popup->getRootMenuItem();

		menuItem = new DefaultMenuItem( "Enumerate Selected items", root, popup );
		menuItem->MenuItemClicked +=
			new MenuItemEventHandler<TreeListControlsWindow>( this, &TreeListControlsWindow::enumerateSelectedItems, "TreeListControlsWindow::enumerateSelectedItems" );


		ScrollbarManager* scrollbarManager = new ScrollbarManager();
		addComponent( scrollbarManager );
		scrollbarManager->setHasVerticalScrollbar( true );
		

		treeList = new TreeListControl();
		treeList->setDefaultItemHeight( 18 );

		scrollbarManager->setTarget( treeList );

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
		child->setTextBold( true );

		TreeItem::SubItem* subItm = new TreeItem::SubItem(item);
		subItm->setCaption( "Sub item 1" );
		//subItm->setTextBold( true );
		child->addSubItem( "Sub item 2", NULL );

		child = treeList->addItem( item, "foo 1c" );
		child = treeList->addItem( item, "foo 1d" );
		child = treeList->addItem( item, "foo 1e" );
		child = treeList->addItem( item, "foo 1f" );
		child->setTextColor( Color::getColor("red") );
		subItm = new TreeItem::SubItem(item);
		subItm->setCaption( "Sub item 3" );
		//subItm->setTextColor( Color::getColor("magenta") );
		child->addSubItem( "Sub item 2", NULL );
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

		

		treeList->showColumnHeader( true );

		treeList->showHierarchyLines( true );

		treeList->ItemSelected.addHandler( new ItemEventHandler<TreeListControlsWindow>( this, &TreeListControlsWindow::onTreeItemSelected, "TreeListControlsWindow::onTreeItemSelected" ) );

		treeList->ItemStateChangeRequested.addHandler(
											new ItemEventHandler<TreeListControlsWindow>( this, &TreeListControlsWindow::onTreeItemState, "TreeListControlsWindow::onTreeItemState" ) );

		Panel* panel = new Panel();
		panel->setTransparent( true );

		treeList->setTransparent( true );

		panel->setHeight( 35 );
		add( panel, AlignBottom );

		status = new Label();
		panel->add( status, AlignClient );
		status->setCaption( "status: " );

		

		HeaderControl* header = treeList->getHeader();
		header->ColumnItemClicked.addHandler(
			new MouseEventHandler<TreeListControlsWindow>( this, &TreeListControlsWindow::headerColumnClicked, "TreeListControlsWindow::headerColumnClicked" ) );

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
		s = Format( "State item: %s, state: %d" ) % item->getCaption().c_str() % item->getState();

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
		
		bool result = Application::initRunningApplication();

		Window* mainWindow = new TreeListControlsWindow();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );
		mainWindow->show();


		return result;
	}

};


int main(int argc, char *argv[])
{
	Application* app = new TreeListControlsApplication( argc, argv );

	Application::main();

	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.8  2006/04/07 02:34:55  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.7.2.2  2005/08/25 01:48:42  ddiego
*minor update to popupmenu code
*
*Revision 1.7.2.1  2005/07/23 21:45:44  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.6.2.5  2005/06/06 02:34:05  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.6.2.4  2005/04/17 15:12:05  iamfraggle
*Replaced old-style var arg calls with new Format calls.
*
*Revision 1.6.2.3  2005/03/04 19:59:22  marcelloptr
*minor improvement to the example
*
*Revision 1.6.2.2  2005/03/04 04:42:22  ddiego
*fixed a bug in the tree list control that was not taking into account the tree item text color or text bold.
*
*Revision 1.6.2.1  2005/02/16 05:09:30  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.6  2004/12/01 04:15:36  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*

*Revision 1.5  2004/08/17 00:13:39  kiklop74
*Fixed for compilation with Borland C++
*
*Revision 1.4.2.2  2004/10/07 15:03:51  kiklop74
*Fixed building issues with bcb
*
*Revision 1.4.2.1  2004/08/21 21:06:51  ddiego
*migrated over the Resource code to the FoudationKit.
*Added support for a GraphicsResourceBundle that can get images.
*Changed the AbstractApplication class to call the System::getResourceBundle.
*Updated the various example code accordingly.
*
*Revision 1.4  2004/08/07 02:47:41  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.3.2.4  2004/04/29 03:40:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


