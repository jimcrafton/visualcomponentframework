//Combos.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/ListPeer.h"
#include "vcf/ApplicationKit/DropDownPeer.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/Win32DropDownPeer.h"
#include "vcf/ApplicationKit/DefaultListModel.h"


using namespace VCF;

class ListControl : public Control {
public:
	DELEGATE(ItemDelegate,ItemSelectionChanged);


	ListControl();

	ListModel* getListModel();

	void setListModel(ListModel * model);


	ImageList* getSmallImageList() {
		return stateImageList_;
	}

	ImageList* getLargeImageList() {
		return largeImageList_;
	}

	ImageList* getStateImageList() {
		return stateImageList_;
	}

	void setLargeImageList( ImageList* imageList );

	void setSmallImageList( ImageList* imageList );

	void setStateImageList( ImageList* imageList );		

	ListItem* addItem( const String& caption, const uint32 imageIndex=0 );

	ListItem* insertItem( const uint32& index, const String& caption, const uint32 imageIndex=0 );	


	bool itemExists( const uint32& index );
	ListItem* getItem( const uint32& index );

	void setItem( const uint32& index, ListItem* item );	

	virtual Rect getItemImageRect( const uint32& index );


	void selectItem( const uint32& index );

	Enumerator<uint32>* getSelectedItems();

	void rangeSelect( const Rect& selectionRect );

	uint32 getFocusedItem();

	uint32 getSelectedItem();

	bool allowsMultiSelect();

	void setAllowsMultiSelect( const bool& allowsMultiSelect );

	void sort( ItemSort* itemSortFunctor );

	uint32 hitTest( const Point& point );

	virtual Rect getItemRect( ListItem* item );

	virtual void insertItemSubItem( ListItem* item, const uint32& index, ListSubItem* subItem ) {}	

	virtual void removeItemSubItem( ListItem* item, ListSubItem* subItem ) {}
	
	virtual bool getItemSubItems( ListItem* item, std::vector<ListSubItem*>& subItems ) {
		return false;
	}

	virtual ListSubItem* getItemSubItem( ListItem* item, const uint32& index ) {
		return NULL;
	}
	virtual uint32 getItemSubItemIndex( ListItem* item, ListSubItem* subItem ) {return -1;}
	virtual uint32 getItemSubItemCount( ListItem* item ){return 0;}
	virtual void itemSelected( ListItem* item );

	virtual void modelChanged( Model* oldModel, Model* newModel );

	virtual void handleEvent( Event* event );	
protected:
	void onListModelContentsChanged( ListModelEvent* event );
	void onItemAdded( ListModelEvent* event );
	void onItemDeleted( ListModelEvent* event );

	virtual void removeSubItemsForItem( ListItem* item );

	ImageList* smallImageList_;
	ImageList* largeImageList_;
	ImageList* stateImageList_;
	ListItem* selectedItem_;

	Array<ListItem*> items_;
	
	ListPeer* listPeer_;
	

	bool internalModelChange_;
	bool inCallbackChange_;
};



ListControl::ListControl():
	Control(),
		listPeer_(NULL)
{
	setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_WINDOW ) );
}

ListModel* ListControl::getListModel()
{
	return (ListModel*) getViewModel();
}

void ListControl::setListModel(ListModel * model)
{
	setViewModel( model );
}

void ListControl::onListModelContentsChanged( ListModelEvent* event )
{

}

void ListControl::onItemAdded( ListModelEvent* event )
{
	if ( internalModelChange_ ) {
		return;
	}

	inCallbackChange_ = true;

	ListItem* item = new ListItem();
	addComponent( item );
	items_.push_back( item );
	item->setModel( getViewModel() );
	item->setControl( this );
	item->setIndex( event->index );	


	repaint();

	inCallbackChange_ = false;
}

void ListControl::removeSubItemsForItem( ListItem* item )
{

}

void ListControl::onItemDeleted( ListModelEvent* event )
{
	inCallbackChange_ = true;
	Array<ListItem*>::iterator found = items_.begin();

	while ( found != items_.end() ) {
		ListItem* item = *found;
		if ( item->getIndex() == event->index ) {
			break;
		}
		++found;
	}

	if ( found != items_.end() ) {				
		Array<ListItem*>::iterator it = items_.begin();		
		while ( it != items_.end() ) {
			ListItem* item = *it;
			if ( item->getIndex() > event->index ) {
				item->setIndex( item->getIndex() - 1 );
			}
			
			++it;
		}
		
		ListItem* item = *found;
		
		removeSubItemsForItem( item );

		items_.erase( found );
		
		removeComponent( item );
		item->free();
	}
	inCallbackChange_ = false;
}

void ListControl::modelChanged( Model* oldModel, Model* newModel )
{
	ListModel* lm = (ListModel*)oldModel;

	if ( NULL != lm ) {
		CallBack* ev = getCallback( "ListControl::onItemAdded" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onItemAdded, "ListControl::onItemAdded" );
		}
		
		lm->ItemAdded -= ev;

		ev = getCallback( "ListControl::onItemDeleted" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onItemDeleted, "ListControl::onItemDeleted" );
		}

		lm->ItemRemoved -= ev;

		ev = getCallback( "ListControl::onListModelContentsChanged" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onListModelContentsChanged, "ListControl::onListModelContentsChanged" );
		}

		lm->ModelChanged -= ev;
	}

	lm = dynamic_cast<ListModel*>( newModel );
	VCF_ASSERT( lm != NULL );


	if ( NULL != lm ) {
		CallBack* ev = getCallback( "ListControl::onItemAdded" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onItemAdded, "ListControl::onItemAdded" );
		}
		
		lm->ItemAdded += ev;

		ev = getCallback( "ListControl::onItemDeleted" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onItemDeleted, "ListControl::onItemDeleted" );
		}

		lm->ItemRemoved += ev;

		ev = getCallback( "ListControl::onListModelContentsChanged" );
		if ( NULL == ev ) {
			ev = new ClassProcedure1<ListModelEvent*,ListControl>( this, &ListControl::onListModelContentsChanged, "ListControl::onListModelContentsChanged" );
		}

		lm->ModelChanged += ev;
	}
}

void ListControl::handleEvent( Event* event )
{
	Control::handleEvent( event );
	switch ( event->getType() ) {
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)event;
			Component* child = ev->getChildComponent();
			ListItem* item = dynamic_cast<ListItem*>(child);
			if ( NULL != item ) {
				
				if ( !inCallbackChange_ ) {				
					internalModelChange_ = true;
					ListModel* lm = getListModel();
					lm->add( "" );
					
					items_.push_back( item );
					item->setModel( getViewModel() );
					item->setControl( this );
					item->setIndex( lm->getCount()-1 );	
					
					internalModelChange_ = false;
				}
			}
		}
		break;

		case Component::COMPONENT_REMOVED : {
			
		}
		break;
	}
}

Rect ListControl::getItemRect( ListItem* item )
{
	return listPeer_->getItemRect( item->getIndex() ) ;
}

void ListControl::itemSelected( ListItem* item )
{
	if ( item->isSelected() ) {
		listPeer_->selectItem( item->getIndex() );
	}
	else {
		listPeer_->selectItem( ListModel::InvalidIndex );
	}
}

void ListControl::setLargeImageList( ImageList* imageList )
{
	this->largeImageList_ = imageList;
	listPeer_->setLargeImageList( imageList );
}

void ListControl::setSmallImageList( ImageList* imageList )
{
	this->smallImageList_ = imageList;
	listPeer_->setSmallImageList( imageList );
}

void ListControl::setStateImageList( ImageList* imageList )
{
	stateImageList_ = imageList;
}

ListItem* ListControl::addItem( const String& caption, const uint32 imageIndex )
{
	ListModel* lm = getListModel();

	return insertItem( lm->getCount(), caption, imageIndex );
}

ListItem* ListControl::insertItem( const uint32& index, const String& caption, const uint32 imageIndex )
{
	ListItem* result = NULL;
	ListModel* lm = getListModel();
	lm->insert( index, caption );

	result = getItem(index);

	return result;
}

bool ListControl::itemExists( const uint32& index )
{
	if ( index < items_.size() ) {		
		return true;
	}
	return false;
}

ListItem* ListControl::getItem( const uint32& index )
{
	ListItem* result = NULL;

	if ( index < items_.size() ) {
		result = items_[index];
	}

	return result;
}

void ListControl::setItem( const uint32& index, ListItem* item )
{
	if ( index < items_.size() ) {
		inCallbackChange_ = true;
		ListItem* oldItem = items_[index];
		
		items_[index] = item;
		
		if ( NULL == item->getOwner() ) {
			addComponent( item );
		}

		item->setControl( this );
		item->setModel( getViewModel() );
		item->setIndex( oldItem->getIndex() );



		//free up sub items
		removeSubItemsForItem( oldItem );

		removeComponent( oldItem );
		oldItem->free();

		repaint();
		inCallbackChange_ = false;
	}
}

Rect ListControl::getItemImageRect( const uint32& index )
{
	return listPeer_->getItemImageRect( index );
}

void ListControl::selectItem( const uint32& index )
{
	listPeer_->selectItem( index );
}

Enumerator<uint32>* ListControl::getSelectedItems()
{
	return listPeer_->getSelectedItems();
}

void ListControl::rangeSelect( const Rect& selectionRect )
{
	listPeer_->rangeSelect( selectionRect );
}

uint32 ListControl::getFocusedItem()
{
	return listPeer_->getFocusedItem();
}

uint32 ListControl::getSelectedItem()
{
	return listPeer_->getSelectedItem();
}

bool ListControl::allowsMultiSelect()
{
	return listPeer_->allowsMultiSelect();
}

void ListControl::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	listPeer_->setAllowsMultiSelect( allowsMultiSelect );
}

void ListControl::sort( ItemSort* itemSortFunctor )
{
	
}

uint32 ListControl::hitTest( const Point& point )
{
	return listPeer_->hitTest( point );
}




class MyCombo : public ListControl {
public:
	MyCombo(): ListControl(),dropDownPeer_(NULL) { 
		dropDownPeer_ = new Win32DropDownPeer();

		listPeer_ = dynamic_cast<ListPeer*>( dropDownPeer_ );
		peer_ = dynamic_cast<ControlPeer*>( dropDownPeer_ );

		peer_->create(this);

		setViewModel( new DefaultListModel() );
	}

	virtual void paint( GraphicsContext* context ) {
		Rect innerBounds = getClientBounds( false );	

		context->setColor( getColor() );
		
		context->rectangle( &innerBounds );
		
		context->fillPath();
	}

	DropDownPeer* dropDownPeer_;
};




class CombosApplication : public Application {
public:
	CombosApplication( int argc, char** argv ): Application(argc, argv) {	}

	virtual bool initRunningApplication();
};

class MainWindow : public Window {
public:
	MainWindow(CombosApplication* app);
	virtual ~MainWindow() {	}

	void onSetComboItemCount( ButtonEvent* event );
	void setComboItemCount();

	void onSetDropDownCount( ButtonEvent* event );
	void setDropDownCount();

	void onSetDropDownWidth( ButtonEvent* event );
	void setDropDownWidth();

	void onSetDropDownExtendFullScreen( ButtonEvent* event );
	void updateDropDownExtendFullScreen();

	void onSetDiscreteScroll( ButtonEvent* event );
	void updateDiscreteScroll();

public:
	VCF::TextControl* edic_;
	VCF::TextControl* eddc_;
	VCF::TextControl* eddw_;
	ComboBoxControl* cb_;
	CheckBoxControl* chkDropDownExtendFullScreen_;
	CheckBoxControl* chkDiscreteScroll_;
	int itemCount_;
	int dropDownCount_;
	int dropDownWidth_;
	bool dropDownExtendFullScreen_;
	bool discreteScroll_;
};

MainWindow::MainWindow(CombosApplication* app)
{
	setBounds( &Rect( 100.0, 100.0, 480.0, 450.0 ) );

	Panel* p = new Panel();
	add( p , AlignClient );

	itemCount_ = 10;
	dropDownExtendFullScreen_ = false;
	discreteScroll_ = true; // for a combo and any listbox it should be true by default 

	cb_ = new ComboBoxControl();
	cb_->setBounds( &Rect(250, 50, 350, cb_->getPreferredHeight()) );
	//cb->addItem( "Item 1" );
	cb_->setVisible( true );
	cb_->setComboBoxStyle( cbsDropDownWithEdit );
	cb_->setDropDownCount( 200 );
	add( cb_ );




	MyCombo* combo = new MyCombo();
	combo->setBounds( &Rect(250, 100, 350, cb_->getPreferredHeight()) );
	add( combo );

	combo->dropDownPeer_->setDropDownCount( 6 );
	combo->setAnchor( AnchorLeft | AnchorRight );
	//combo->dropDownPeer_->enableEditBox( false );

	combo->getListModel()->add( "Item 1" );
	combo->getListModel()->add( "Item 2" );
	combo->getListModel()->add( "Item 3" );
	combo->getListModel()->add( "Item 4" );
	combo->getListModel()->add( "Item 5" );
	combo->getListModel()->add( "Item 6" );
	combo->getListModel()->add( "Item 7" );
	combo->getListModel()->add( "Item 8" );
	combo->getListModel()->add( "Item 9" );
	combo->getListModel()->add( "Item A" );
	combo->getListModel()->add( "Item B" );
	combo->getListModel()->add( "Item C" );
	combo->getListModel()->add( "Item D" );






	VCF::CommandButton* btn;
	CallBack* bh;

	eddc_ = new TextControl();
	eddc_->setBounds( 25, 20, 45, eddc_->getPreferredHeight() );
	eddc_->setVisible( true );
	eddc_->setToolTipText( "dropdown count for the combo" );
	add( eddc_ );

	btn = new CommandButton();





	btn->setCaption( "Set DropDown Count" );
	btn->setBounds ( 100, 20, btn->getPreferredWidth(), btn->getPreferredHeight() );	
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetDropDownCount, "MainWindow::onSetDropDownCount" );
	btn->ButtonClicked += bh;
	add( btn );


	edic_ = new TextControl();
	edic_->setBounds( 25, 75, 45, edic_->getPreferredHeight() );
	edic_->setVisible( true );
	edic_->setToolTipText( "number of items in the combo" );
	add( edic_ );

	btn = new CommandButton();

	btn->setCaption( "Set Items count" );
	btn->setBounds ( 100, 75, btn->getPreferredWidth(), btn->getPreferredHeight() );	
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetComboItemCount, "MainWindow::onSetComboItemCount" );
	btn->ButtonClicked += bh;
	add( btn );


	eddw_ = new TextControl();
	eddw_->setBounds( 25, 125, 45, eddw_->getPreferredHeight() );
	eddw_->setVisible( true );
	eddw_->setToolTipText( "dropdown width for the combo" );
	add( eddw_ );

	btn = new CommandButton();

	btn->setCaption( "Set DropDown Width" );
	btn->setBounds ( 100, 125, btn->getPreferredWidth(), btn->getPreferredHeight() );
	
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetDropDownWidth, "MainWindow::onSetDropDownWidth" );
	btn->ButtonClicked += bh;
	add( btn );


	chkDropDownExtendFullScreen_ = new CheckBoxControl();
	chkDropDownExtendFullScreen_->setCaption( "DropDown List Extend to full screen" );
	chkDropDownExtendFullScreen_->setToolTipText( "allow the dropdown list of the combo to extend to the full screen" );
	chkDropDownExtendFullScreen_->setBounds ( &Rect(25, 175, 225, 200) );
	chkDropDownExtendFullScreen_->setTabStop( true );
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetDropDownExtendFullScreen, "MainWindow::onSetDropDownExtendFullScreen" );
	chkDropDownExtendFullScreen_->ButtonClicked += bh;
	add( chkDropDownExtendFullScreen_ );


	chkDiscreteScroll_ = new CheckBoxControl();
	chkDiscreteScroll_->setCaption( "Scrolling by discrete amounts" );
	chkDiscreteScroll_->setToolTipText( "allow the dropdown list of the combo to be scrolled only by discrete quantities" );
	chkDiscreteScroll_->setBounds ( &Rect(25, 215, 225, 240) );
	chkDiscreteScroll_->setTabStop( true );
	bh = new ClassProcedure1<ButtonEvent*,MainWindow>( this, &MainWindow::onSetDiscreteScroll, "MainWindow::onSetDiscreteScroll" );
	chkDiscreteScroll_->ButtonClicked += bh;
	add( chkDiscreteScroll_ );
}

void MainWindow::onSetComboItemCount( ButtonEvent* event )
{
	setComboItemCount();
}

void MainWindow::setComboItemCount()
{
	String s;

	s = edic_->getTextModel()->getText();
	itemCount_ = StringUtils::fromStringAsInt( s );

	cb_->setSelectedItem( NULL );	// bugfix ! otherwise it crashes when emptying the model
	cb_->getViewModel()->empty(); // cb_->getListModel()->empty(); is obsolete

	for (int i=0; i < itemCount_; i++) {
		s = Format( "item %d")% (i+1);
		cb_->addItem( s );
	}
}

void MainWindow::onSetDropDownCount( ButtonEvent* event )
{
	setDropDownCount();
}

void MainWindow::setDropDownCount()
{
	String s;

	s = eddc_->getTextModel()->getText();
	dropDownCount_ = StringUtils::fromStringAsInt( s );

	cb_->setDropDownCount( dropDownCount_ );	// bugfix ! otherwise it crashes when emptying the model
}

void MainWindow::onSetDropDownWidth( ButtonEvent* event )
{
	setDropDownWidth();
}

void MainWindow::setDropDownWidth()
{
	String s;

	s = eddw_->getTextModel()->getText();
	dropDownWidth_ = StringUtils::fromStringAsInt( s );

	cb_->setDropDownWidth( dropDownWidth_ );
}

void MainWindow::onSetDropDownExtendFullScreen( ButtonEvent* event )
{
	dropDownExtendFullScreen_ = !dropDownExtendFullScreen_;
	updateDropDownExtendFullScreen();
}

void MainWindow::updateDropDownExtendFullScreen()
{
	cb_->setDropDownExtendFullScreen( dropDownExtendFullScreen_ );	// bugfix ! otherwise it crashes when emptying the model
	chkDropDownExtendFullScreen_->setChecked( dropDownExtendFullScreen_ );
}

void MainWindow::onSetDiscreteScroll( ButtonEvent* event )
{
	discreteScroll_ = !discreteScroll_;
	updateDiscreteScroll();
}

void MainWindow::updateDiscreteScroll()
{
	cb_->setDiscreteScroll( discreteScroll_ );
	chkDiscreteScroll_->setChecked( discreteScroll_ );
}

bool CombosApplication::initRunningApplication(){
	bool result = Application::initRunningApplication();
	
	MainWindow* mainWindow = new MainWindow(this);
	setMainWindow(mainWindow);
	
	mainWindow->setCaption( "Combos !" );
	mainWindow->eddc_->getTextModel()->setText( "130" );
	mainWindow->edic_->getTextModel()->setText( "135" );
	mainWindow->eddw_->getTextModel()->setText( "0" );
	ButtonEvent be( mainWindow, 0 );	// is it correct to use mask = 0 ?
	mainWindow->onSetDropDownCount( &be );
	mainWindow->onSetComboItemCount( &be );
	mainWindow->updateDropDownExtendFullScreen();
	mainWindow->updateDiscreteScroll();
	mainWindow->show();

	return result;
}

int main(int argc, char *argv[])
{
	Application* app = new CombosApplication( argc, argv );

	Application::main();
	
	return 0;
}


