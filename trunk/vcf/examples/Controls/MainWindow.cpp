//MainWindow.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"

#include "vcf/ApplicationKit/DefaultMenuItem.h"
#include "vcf/ApplicationKit/DefaultListItem.h"
#include "vcf/ApplicationKit/TitledBorder.h"
#include "vcf/ApplicationKit/EtchedBorder.h"
#include "vcf/ApplicationKit/ColorEtchedBorder.h"

#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/ApplicationKit/TextPeer.h"


#include "ControlsApplication.h"
#include "ControlsAbout.h"
#include "Spacers.h"

#include "MainWindow.h"
//#include "HorizontalLayoutContainer.h"


using namespace VCF;



MainWindow::MainWindow()
{
	this->setWidth( 600 );
	this->setHeight( 800 );

	//build main menu
	MenuBar* menuBar = new MenuBar( this );
	this->setMenuBar( menuBar );

	MenuItem* root = menuBar->getRootMenuItem();
	EventHandler* menuItemHandler = NULL;

	//add Help menu
	DefaultMenuItem* help = new DefaultMenuItem( "&Help", root, menuBar );
	DefaultMenuItem* helpAbout = new DefaultMenuItem( "About...", help, menuBar );
	menuItemHandler = new MenuItemEventHandler<MainWindow>(this, &MainWindow::onHelpAbout, "helpAbout" );
	helpAbout->MenuItemClicked += menuItemHandler;

	//add TabbedPages
	mainPages_ = new TabbedPages();
	mainPages_->setBorderWidth( 4 );
	( (StandardContainer*)mainPages_->getContainer() )->setBorderWidth( UIToolkit::getUIMetricValue(UIMetricsManager::mtContainerBorderDelta) );
	this->add( mainPages_, AlignClient );

	//add individual TabPage here.
	listBoxPage_ = mainPages_->addNewPage( "ListBoxControl" );
	makeListBoxPage();

	bordersPage_ = mainPages_->addNewPage( "Borders" );
	makeBordersPage();

	buttonsPage_ = mainPages_->addNewPage( "Buttons" );
	makeButtonsPage();

	textPage_ = mainPages_->addNewPage( "Text" );
	makeTextPage();


	treePage_ = mainPages_->addNewPage( "Tree Control" );
	makeTreePage();

	mainPagesModel_ = mainPages_->getModel();
	mainPagesModel_->setSelectedPage( listBoxPage_ );
}

MainWindow::~MainWindow()
{

}

void MainWindow::onHelpAbout( MenuItemEvent* e )
{
	ControlsAbout aboutDlg;

	aboutDlg.showModal();

}


// begin listBoxPage_ code
void MainWindow::makeListBoxPage()
{
	double borderWidth = UIToolkit::getUIMetricValue(UIMetricsManager::mtContainerBorderDelta);

	Panel* panel1 = (Panel*)listBoxPage_->getPageComponent();

	//add a panel for ListBoxControl-related controls
	Panel* listBoxGroup = new Panel();
	( (StandardContainer*)listBoxGroup->getContainer() )->setBorderWidth( borderWidth );
	listBoxGroup->setBorder( new TitledBorder( "ListBoxControl" ) );
	listBoxGroup->setWidth( 160 );
	panel1->add( listBoxGroup, AlignLeft );

	//add a ListBoxControl
	listBox1_ = new ListBoxControl();
	listBox1_->setBorder( new Basic3DBorder( true ) );
	listBox1_->setAllowsMultiSelect( false );
	//add scrollbar to listBox1_
	ScrollbarManager* scrollbarManagerSingle = new ScrollbarManager();
	addComponent( scrollbarManagerSingle );
	scrollbarManagerSingle->setHasVerticalScrollbar( true );
	scrollbarManagerSingle->setHasHorizontalScrollbar( true );
	scrollbarManagerSingle->setTarget( listBox1_ );
	scrollbarManagerSingle->setKeepScrollbarsVisible( false, false );

	listBoxGroup->add( listBox1_, AlignClient );

	//add some items to listBox1_
	ListModel* listBoxModel = listBox1_->getListModel();
	for(int j=0; j<10; j++){
		String indx = StringUtils::toString(j);
		String capt = L"ListItem " + indx;
		listBoxModel->addItem( new DefaultListItem( listBoxModel, capt ) );
	}
	listBoxModel->addItem( new DefaultListItem( listBoxModel, "Add your own item below." ) );


	listBoxGroup->add( new VerticalSpacer( borderWidth ), AlignBottom );

	CommandButton* btnDeselect = new CommandButton();
	btnDeselect->setCaption( "Deselect all" );
	btnDeselect->setHeight( 24 );
	listBoxGroup->add( btnDeselect, AlignBottom );

	listBoxGroup->add( new VerticalSpacer( borderWidth ), AlignBottom );

	CommandButton* btnRemove = new CommandButton();
	btnRemove->setCaption( "Remove selected item" );
	btnRemove->setHeight( 24 );
	listBoxGroup->add( btnRemove, AlignBottom );

	listBoxGroup->add( new VerticalSpacer( 20 ), AlignBottom );

	//add a panel for Adding items
	Panel* listBoxAddGroup = new Panel();
	StandardContainer* lbAddContainer = new StandardContainer();
	lbAddContainer->setBorderWidth( borderWidth );
	listBoxAddGroup->setContainer( lbAddContainer );
	listBoxAddGroup->setBorder( new TitledBorder( "Add item" ) );
	//add TextControl to enter item to add
	txtCtrlAddToListBox_ = new TextControl();
	txtCtrlAddToListBox_->setHeight( 20 );
	listBoxAddGroup->add( txtCtrlAddToListBox_, AlignTop );

	listBoxAddGroup->add( new VerticalSpacer( borderWidth ), AlignTop );

	//add buttons for adding text from textCtrlSingle to listBoxSingl
	CommandButton* btnAddItem = new CommandButton();
	btnAddItem->setCaption( "Add item to ListBox" );
	btnAddItem->setHeight( 24 );
	listBoxAddGroup->add( btnAddItem, AlignTop );
	listBoxAddGroup->setHeight( 2*borderWidth + 20 + 10 + 24 + 15);
	listBoxGroup->add( listBoxAddGroup, AlignBottom );

	listBoxGroup->add( new VerticalSpacer( 20 ), AlignBottom );

	//add panel for listbox selection style
	Panel* listBoxSelGroup = new Panel();
	StandardContainer* lbSelContainer = new StandardContainer();
	lbSelContainer->setBorderWidth( borderWidth );
	listBoxSelGroup->setContainer( lbSelContainer );
	listBoxSelGroup->setBorder( new TitledBorder( "Selection style" ) );
	listBoxSelGroup->setHeight( 98 );
	listBoxGroup->add( listBoxSelGroup, AlignBottom );
	Rect bounds3 = listBoxSelGroup->getClientBounds();
	//add RadioButtonControls to selection style panel
	RadioButtonControl* rbSingleSel = new RadioButtonControl();
	rbSingleSel->setGroupID( 1 );
	rbSingleSel->setCaption("Single selection");
	rbSingleSel->setHeight( rbSingleSel->getPreferredHeight() );
	listBoxSelGroup->add( rbSingleSel, AlignTop );

	RadioButtonControl* rbMultiSel = new RadioButtonControl();
	rbMultiSel->setGroupID( 1 );
	rbMultiSel->setCaption("Multi selection");
	rbMultiSel->setHeight( rbMultiSel->getPreferredHeight() );
	listBoxSelGroup->add( rbMultiSel, AlignTop );

	RadioButtonControl* rbExtendedSel = new RadioButtonControl();
	rbExtendedSel->setGroupID( 1 );
	rbExtendedSel->setCaption("Extended selection");
	rbExtendedSel->setHeight( rbExtendedSel->getPreferredHeight() );
	listBoxSelGroup->add( rbExtendedSel, AlignTop );

	rbSingleSel->setChecked( true );

	// Event Handling for this page
	//add SelectionChanged handlers for listbox.
	listBox1_->SelectionChanged.addHandler( new ItemEventHandler<MainWindow>(this, &MainWindow::listBox1Change, "MainWindow::listBox1Change"));

	//add ButtonClicked handlers for command button.
	btnRemove->ButtonClicked.addHandler( new ButtonEventHandler<MainWindow>( this, &MainWindow::onbtnRemove, "MainWindow::onbtnRemoveClicked" ) );
	btnDeselect->ButtonClicked.addHandler( new ButtonEventHandler<MainWindow>( this, &MainWindow::onbtnDeselect, "MainWindow::onbtnDeselectClicked" ) );
	btnAddItem->ButtonClicked.addHandler( new ButtonEventHandler<MainWindow>( this, &MainWindow::onbtnAddItemClicked, "MainWindow::onbtnAddItemClicked" ) );
	rbSingleSel->ButtonClicked.addHandler( new ButtonEventHandler<MainWindow>( this, &MainWindow::onrbSingleSelClicked, "MainWindow::onrbSingleSelClicked" ) );
	rbMultiSel->ButtonClicked.addHandler( new ButtonEventHandler<MainWindow>( this, &MainWindow::onrbMultiSelClicked, "MainWindow::onrbMultiSelClicked" ) );
	rbExtendedSel->ButtonClicked.addHandler( new ButtonEventHandler<MainWindow>( this, &MainWindow::onrbExtendedSelClicked, "MainWindow::onrbExtendedSelClicked" ) );
}

void MainWindow::onrbSingleSelClicked( VCF::ButtonEvent* ) {
	listBox1_->deselectAllItems();
	listBox1_->setAllowsMultiSelect( false );
}

void MainWindow::onrbMultiSelClicked( VCF::ButtonEvent* ) {
	listBox1_->setAllowsMultiSelect( true );
	listBox1_->setAllowsExtendedSelect( false );
}

void MainWindow::onrbExtendedSelClicked( VCF::ButtonEvent* ) {
	listBox1_->setAllowsExtendedSelect( true );
}

void MainWindow::listBox1Change( VCF::ItemEvent* ) {

}

void MainWindow::onbtnRemove( VCF::ButtonEvent* ) {
	ListModel* LBCModel = (ListModel*)(listBox1_->getListModel());
	Enumerator<ListItem*>* items= LBCModel->getItems();
	int i = 0;
	i = LBCModel->getCount();

	// we reverse iterate here so you don't screw iterators.
	items->reset( true );// set iterator to .end()
	while ( true == items->hasMoreElements( true ) ) {
		ListItem* item = items->prevElement();
		if ( true == item->isSelected() ) {
			listBox1_->eraseFromSelectedItems( item );
			item->setSelected(false);
			LBCModel->deleteItem( item );
		}
	}

}

void MainWindow::onbtnDeselect( VCF::ButtonEvent* ) {
	listBox1_->deselectAllItems();
}

void MainWindow::onbtnAddItemClicked( VCF::ButtonEvent* ) {
	if(listBox1_ != NULL){
		ListModel* LBCModel = (ListModel*)(listBox1_->getListModel());
		TextModel* txtModel = txtCtrlAddToListBox_->getTextModel();
		String text = txtModel->getText();
		LBCModel->addItem( new DefaultListItem( LBCModel, text ) );
	}
}
// end of listBoxPage code




// begin bordersPage code
void MainWindow::makeBordersPage()
{
	double borderWidth = UIToolkit::getUIMetricValue(UIMetricsManager::mtContainerBorderDelta);

	Panel* pagePanel = (Panel*)bordersPage_->getPageComponent();

	// 2 panels, just to aid in layout.
	Panel* leftPanel = new Panel();
	leftPanel->setWidth( 200 );
	leftPanel->setBorder( NULL );
	Panel* rightPanel = new Panel();
	rightPanel->setBorder( NULL );

	pagePanel->add( leftPanel, AlignLeft );
	pagePanel->add( new HorizontalSpacer( 8 ), AlignLeft );
	pagePanel->add( rightPanel, AlignClient );

	// 4 panels with TitledBorders, in which the panels with various border types/styles will reside.
	Panel* basic3DBorderTitledPanel = new Panel();
	TitledBorder* titledBorder1 = new TitledBorder( "Basic3DBorder" );
	( (StandardContainer*)basic3DBorderTitledPanel->getContainer() )->setBorderWidth( 16 );
	basic3DBorderTitledPanel->setBorder( titledBorder1 );
	basic3DBorderTitledPanel->setHeight( 200 );
	leftPanel->add( basic3DBorderTitledPanel, AlignTop );
	leftPanel->add( new VerticalSpacer( 8 ), AlignTop );

	Panel* light3DBorderTitledPanel = new Panel();
	TitledBorder* titledBorder2 = new TitledBorder( "Light3DBorder" );
	( (StandardContainer*)light3DBorderTitledPanel->getContainer() )->setBorderWidth( 16 );
	light3DBorderTitledPanel->setBorder( titledBorder2 );
	leftPanel->add( light3DBorderTitledPanel, AlignClient );

	Panel* etchedBorderTitledPanel = new Panel();
	TitledBorder* titledBorder3 = new TitledBorder( "EtchedBorder" );
	( (StandardContainer*)etchedBorderTitledPanel->getContainer() )->setBorderWidth( 16 );
	etchedBorderTitledPanel->setBorder( titledBorder3 );
	etchedBorderTitledPanel->setHeight( 200 );
	rightPanel->add( etchedBorderTitledPanel, AlignTop );
	rightPanel->add( new VerticalSpacer( 8 ), AlignTop );

	Panel* colorEtchedBorderTitledPanel = new Panel();
	TitledBorder* titledBorder4 = new TitledBorder( "ColorEtchedBorder" );
	( (StandardContainer*)colorEtchedBorderTitledPanel->getContainer() )->setBorderWidth( 16 );
	colorEtchedBorderTitledPanel->setBorder( titledBorder4 );
	rightPanel->add( colorEtchedBorderTitledPanel, AlignClient );

	// now add the panels with specific border types/styles
	basic3DBorderPanel_ = new Panel();
	basic3DBorderTitledPanel->add( basic3DBorderPanel_, AlignClient );

	light3DBorderPanel_ = new Panel();
	light3DBorderTitledPanel->add( light3DBorderPanel_, AlignClient );

	etchedBorderPanel_ = new Panel();
	etchedBorderTitledPanel->add( etchedBorderPanel_, AlignClient );

	colorEtchedBorderPanel_ = new Panel();
	colorEtchedBorderTitledPanel->add( colorEtchedBorderPanel_, AlignClient );

	//set the borders
	basic3DBorderPanel_->setBorder( new Basic3DBorder( false ) );
	light3DBorderPanel_->setBorder( new Light3DBorder( false ) );
	etchedBorderPanel_->setBorder( new EtchedBorder( GraphicsContext::etAllSides, GraphicsContext::etEtched ) );
	colorEtchedBorderPanel_->setBorder( new ColorEtchedBorder() );
	( (ColorEtchedBorder*)colorEtchedBorderPanel_->getBorder() )->setEdgeStyle( GraphicsContext::etEtched );
	( (ColorEtchedBorder*)colorEtchedBorderPanel_->getBorder() )->setHighlight( Color::getColor( "white" ) );
	( (ColorEtchedBorder*)colorEtchedBorderPanel_->getBorder() )->setShadow( Color::getColor( "blue" ) );
}
// end bordersPage code



void MainWindow::makeButtonsPage()
{
	HorizontalLayoutContainer* container = new HorizontalLayoutContainer();
	container->setColumnWidth( 0, 200 );
	//container->setEqualizeHeights(true);
	//container->setAverageHeights(true);
	container->setKeepControlsWidth( false );

	buttonsPage_->getPageComponent()->setContainer( container );



	Label* label = NULL;

	RadioButtonControl* radioBtn = new RadioButtonControl();

	label = new Label();
	label->setCaption( radioBtn->getClassName() + "(s):" );
	container->add( label );


	Panel* panel = new Panel();
	panel->setBorder( NULL );
	panel->setBounds( 0, 0, 500, 30 );
	container->add( panel );


	radioBtn->setCaption("yes");
	radioBtn->setBounds( 1, 1, radioBtn->getPreferredWidth(), radioBtn->getPreferredHeight() );
	panel->add( radioBtn );

	radioBtn = new RadioButtonControl();
	radioBtn->setCaption("no");
	radioBtn->setBounds( 1 + radioBtn->getPreferredWidth() + 7.0, 1, radioBtn->getPreferredWidth(), radioBtn->getPreferredHeight() );
	panel->add( radioBtn );




	CommandButton* btn1 = new CommandButton();

	label = new Label();
	label->setCaption( btn1->getClassName() + ":" );
	container->add( label );

	btn1->setCaption(  "Button 1" );
	container->add( btn1 );

	EventHandler* btnHandler = new ButtonEventHandler<MainWindow>( this, &MainWindow::onButtonClicked, "MainWindow::onButtonClicked" );
	btn1->ButtonClicked.addHandler( btnHandler );



	CommandButton* btn2 = new CommandButton();

	label = new Label();
	label->setCaption( btn2->getClassName() + " Disabled:" );
	container->add( label );

	btn2->setCaption(  "Button 2" );
	btn2->setEnabled( false );
	container->add( btn2 );
	btn2->ButtonClicked.addHandler( btnHandler );




	PushButton* btn3 = new PushButton();

	label = new Label();
	label->setCaption( btn3->getClassName() + ":" );
	container->add( label );

	btn3->setCaption(  "Button 3" );
	container->add( btn3 );



	PushButton* btn4 = new PushButton();

	label = new Label();
	label->setCaption( btn4->getClassName()  + " Disabled:" );
	container->add( label );

	btn4->setCaption(  "Button 4" );
	btn4->setEnabled( false );
	container->add( btn4 );



	/**
	image list for the PushButton
	*/
	ImageList* il = new ImageList();
	il->setImageHeight( 16 );
	il->setImageWidth( 16 );
	il->setTransparentColor( &Color( 1.0, 0.0, 1.0) );
	addComponent( il );


	GraphicsResourceBundle* resBundle = Application::getRunningInstance()->getResourceBundle();
	Image* img = resBundle->getImage( "bmp1" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "bmp2" );
	il->addImage( img );
	delete img;

	int indexImgSaveUp = il->getImageCount();
	img = resBundle->getImage( "iconSaveUp" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "iconSaveDown" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "iconSaveDisabled" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "iconSaveFocus" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "iconSaveFocusDown" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "iconSaveHighlight" );
	il->addImage( img );
	delete img;


	// for images of different size we need a different ImageList
	resBundle = Application::getRunningInstance()->getResourceBundle();
	img = resBundle->getImage( "bmpLong" );

	ImageList* il2 = new ImageList();
	il2->setImageHeight( img->getHeight() );
	il2->setImageWidth( img->getWidth() );
	il2->setTransparentColor( &Color( 0.0, 1.0, 0.0) );
	addComponent( il2 );

	il2->addImage( img );
	delete img;




	PushButton* btn5 = new PushButton();

	label = new Label();
	label->setCaption( btn5->getClassName() + " (left):" );
	container->add( label );

	btn5->setCaption(  "Button (left)" );
	btn5->setImageList( il );
	btn5->setBtnImageIndex( 0 );
	btn5->setCaptionAlignment( PushButton::bcaLeft );
	container->add( btn5 );





	PushButton* btn6 = new PushButton();

	label = new Label();
	label->setCaption( btn6->getClassName()  + " (right - disabled):" );
	container->add( label );

	btn6->setCaption(  "Button (right)" );
	btn6->setEnabled( false );
	btn6->setImageList( il );
	btn6->setBtnImageIndex( 1 );
	btn6->setCaptionAlignment( PushButton::bcaRight );
	container->add( btn6 );




	PushButton* btn7 = new PushButton();

	label = new Label();
	label->setCaption( btn7->getClassName() + " (top):" );
	container->add( label );

	btn7->setCaption(  "Button (top)" );
	btn7->setImageList( il );
	btn7->setBtnImageIndex( 0 );
	btn7->setCaptionAlignment( PushButton::bcaTop );
	container->add( btn7 );


	PushButton* btn8 = new PushButton();

	label = new Label();
	label->setCaption( btn8->getClassName()  + " (bottom):" );
	container->add( label );

	btn8->setCaption(  "Button (bottom)" );
	btn8->setHeight( 80 );
	btn8->setImageList( il );
	btn8->setBtnImageIndex( 0 );
	btn8->setCaptionAlignment( PushButton::bcaBottom );
	container->add( btn8 );


	PushButton* btn9 = new PushButton();

	label = new Label();
	label->setCaption( btn9->getClassName() + " (center):" );
	container->add( label );

	btn9->setCaption(  "Button (center)" );
	btn9->setImageList( il );
	btn9->setBtnImageIndex( 1 );
	container->add( btn9 );





	PushButton* btn10 = new PushButton();

	label = new Label();
	label->setCaption( btn10->getClassName() + " (caption):" );
	container->add( label );

	btn10->setCaption(  "Button (caption)" );
	//btn10->setImageList( il );
	//btn10->setBtnImageIndex( 1 );
	container->add( btn10 );



	PushButton* btn11 = new PushButton();

	label = new Label();
	label->setCaption( btn11->getClassName()  + " (image only):" );
	container->add( label );

	btn11->setShowCaption( false );
	btn11->setCaption(  "Button (image only)" );
	btn11->setImageList( il2 );
	btn11->setBtnImageIndex( 0 );
	container->add( btn11 );




	PushButton* btn = new PushButton();

	label = new Label();
	label->setCaption( btn->getClassName()  + " (images):" );
	container->add( label );

	panel = new Panel();
	panel->setBorder( NULL );
	panel->setBounds( 0, 0, 500, 30 );
	container->add( panel );

	Size btnSize;
	double x = 0, y = 1;
	double w = il->getImageWidth() + 10;
	double h = il->getImageHeight() + 10;
	double sep = 7.0;

	btn->setBounds( x, y, w, h );
	btn->setCaption( "Button (all state images)" );
	btn->setShowCaption( false );
	btn->setToolTipText( "Button (all state images)" );
	btn->setImageList( il );
	btn->setBtnImageIndex( indexImgSaveUp+0, PushButton::bisUp );
	btn->setBtnImageIndex( indexImgSaveUp+1, PushButton::bisDown );
	btn->setBtnImageIndex( indexImgSaveUp+2, PushButton::bisDisable );
	btn->setBtnImageIndex( indexImgSaveUp+3, PushButton::bisFocus );
	btn->setBtnImageIndex( indexImgSaveUp+4, PushButton::bisFocusDown );
	btn->setBtnImageIndex( indexImgSaveUp+5, PushButton::bisHighlight );
	btnSize = btn->calcMinimumSize();
	btn->setBounds( x, y, btnSize.width_, btnSize.height_ );
	panel->add( btn );
	x += btnSize.width_ + sep;


	btn = new PushButton();
	btn->setBounds( x, y, w, h );
	btn->setCaption( "Button (all state images but not Highlight)" );
	btn->setShowCaption( false );
	btn->setToolTipText( "Button (all state images)" );
	btn->setImageList( il );
	btn->setBtnImageIndex( indexImgSaveUp+0, PushButton::bisUp );
	btn->setBtnImageIndex( indexImgSaveUp+1, PushButton::bisDown );
	btn->setBtnImageIndex( indexImgSaveUp+2, PushButton::bisDisable );
	btn->setBtnImageIndex( indexImgSaveUp+3, PushButton::bisFocus );
	btn->setBtnImageIndex( indexImgSaveUp+4, PushButton::bisFocusDown );
	btnSize = btn->calcMinimumSize();
	btn->setBounds( x, y, btnSize.width_, btnSize.height_ );
	panel->add( btn );
	x += btnSize.width_ + sep;


	btn = new PushButton();
	btn->setBounds( w*1 + sep*1, 1, w, h );
	btn->setCaption( "Button (only Up/Disable images)" );
	btn->setShowCaption( false );
	btn->setToolTipText( "Button (only Up/Disable images)" );
	btn->setEnabled( false );
	btn->setImageList( il );
	btn->setBtnImageIndex( indexImgSaveUp+0 );
	btn->setBtnImageIndex( indexImgSaveUp+2, PushButton::bisDisable );
	btnSize = btn->calcMinimumSize();
	btn->setBounds( x, y, btnSize.width_, btnSize.height_ );
	panel->add( btn );
	x += btnSize.width_ + sep;


	btn = new PushButton();
	btn->setBounds( w*2 + sep*2, 1, w, h );
	btn->setCaption( "Button (only Up image)" );
	btn->setShowCaption( false );
	btn->setToolTipText( "Button (only Up image)" );
	btn->setImageList( il );
	btn->setBtnImageIndex( indexImgSaveUp+0 );
	btnSize = btn->calcMinimumSize();
	btn->setBounds( x, y, btnSize.width_, btnSize.height_ );
	panel->add( btn );
	x += btnSize.width_ + sep;





	PushButton* toggle = new PushButton();

	label = new Label();
	label->setCaption( toggle->getClassName()  + " (images - toggled):" );
	container->add( label );

	panel = new Panel();
	panel->setBorder( NULL );
	panel->setBounds( 0, 0, 500, 30 );
	container->add( panel );

	//Size btnSize;
	x = 0, y = 1;
	w = il->getImageWidth() + 10;
	h = il->getImageHeight() + 10;
	sep = 7.0;

	//toggle = new PushButton();
	toggle->setToggled( true );
	toggle->setBounds( x, y, w, h );
	toggle->setCaption( "Toggled (all state images)" );
	toggle->setShowCaption( false );
	toggle->setToolTipText( "Toggled (all state images)" );
	toggle->setImageList( il );
	toggle->setBtnImageIndex( indexImgSaveUp+0, PushButton::bisUp );
	toggle->setBtnImageIndex( indexImgSaveUp+1, PushButton::bisDown );
	toggle->setBtnImageIndex( indexImgSaveUp+2, PushButton::bisDisable );
	toggle->setBtnImageIndex( indexImgSaveUp+3, PushButton::bisFocus );
	toggle->setBtnImageIndex( indexImgSaveUp+4, PushButton::bisFocusDown );
	toggle->setBtnImageIndex( indexImgSaveUp+5, PushButton::bisHighlight );
	btnSize = toggle->calcMinimumSize();
	toggle->setBounds( x, y, btnSize.width_, btnSize.height_ );
	panel->add( toggle );
	x += btnSize.width_ + sep;


	toggle = new PushButton();
	toggle->setToggled( true );
	toggle->setBounds( x, y, w, h );
	toggle->setCaption( "Toggled (all state images but not Highlight)" );
	toggle->setShowCaption( false );
	toggle->setToolTipText( "Toggled (all state images but not Highlight)" );
	toggle->setImageList( il );
	toggle->setBtnImageIndex( indexImgSaveUp+0, PushButton::bisUp );
	toggle->setBtnImageIndex( indexImgSaveUp+1, PushButton::bisDown );
	toggle->setBtnImageIndex( indexImgSaveUp+2, PushButton::bisDisable );
	toggle->setBtnImageIndex( indexImgSaveUp+3, PushButton::bisFocus );
	toggle->setBtnImageIndex( indexImgSaveUp+4, PushButton::bisFocusDown );
	btnSize = toggle->calcMinimumSize();
	toggle->setBounds( x, y, btnSize.width_, btnSize.height_ );
	panel->add( toggle );
	x += btnSize.width_ + sep;


	toggle = new PushButton();
	toggle->setToggled( true );
	toggle->setBounds( w*1 + sep*1, 1, w, h );
	toggle->setCaption( "Toggled (only Up/Disable images)" );
	toggle->setShowCaption( false );
	toggle->setEnabled( false );
	toggle->setToolTipText( "Toggled (only Up/Disable images)" );
	toggle->setImageList( il );
	toggle->setBtnImageIndex( indexImgSaveUp+0 );
	toggle->setBtnImageIndex( indexImgSaveUp+2, PushButton::bisDisable );
	btnSize = toggle->calcMinimumSize();
	toggle->setBounds( x, y, btnSize.width_, btnSize.height_ );
	panel->add( toggle );
	x += btnSize.width_ + sep;


	toggle = new PushButton();
	toggle->setToggled( true );
	toggle->setBounds( w*2 + sep*2, 1, w, h );
	toggle->setCaption( "Toggled (only Up image)" );
	toggle->setShowCaption( false );
	toggle->setToolTipText( "Toggled (only Up image)" );
	toggle->setImageList( il );
	toggle->setBtnImageIndex( indexImgSaveUp+0 );
	btnSize = toggle->calcMinimumSize();
	toggle->setBounds( x, y, btnSize.width_, btnSize.height_ );
	panel->add( toggle );
	x += btnSize.width_ + sep;


}

void MainWindow::onButtonClicked( ButtonEvent* e )
{
	Dialog::showMessage( "Hello world !" );
}

void MainWindow::onSingletextCtrlSelectionChanged( Event* e )
{
	TextControl* tc = (TextControl*) e->getSource();
	Label* label = (Label*)textPage_->getPageComponent()->findComponent( "SelectionStart", true );

	label->setCaption( Format("%d") % tc->getSelectionStart() );

	label = (Label*)textPage_->getPageComponent()->findComponent( "SelectionCount", true );
	label->setCaption( Format("%d") % tc->getSelectionCount() );
}

void MainWindow::makeTextPage()
{
	HorizontalLayoutContainer* container = new HorizontalLayoutContainer();
	container->setColumnWidth( 0, 200 );

	textPage_->getPageComponent()->setContainer( container );

	Label* label = new Label();

	label->setCaption( "Single Line Text:" );
	container->add( label );

	TextControl* singleTextCtrl = new TextControl();
	container->add( singleTextCtrl );

	// uncomment this to test if the formatting is correctly applied in this case too.
	//singleTextCtrl->setReadOnly( true );

	singleTextCtrl->getFont()->setName( "Courier New" );

	singleTextCtrl->getTextModel()->insertText( 0, "Hello, here's some text!" );

	Dictionary styles;
	styles [ Text::fsColor ] = Color::getColor("green");
	styles [ Text::fsBold ] = true;
	styles [ Text::fsPointSize ] = 10.0;
	styles [ Text::fsItalic ] = true;
	styles [ Text::fsStrikeout ] = true;
	styles [ Text::fsUnderlined ] = Text::utDotted;
	styles [ Text::fsFontName ] = "Arial";
	singleTextCtrl->setStyle( 7, 6, styles );



	singleTextCtrl->SelectionChanged +=
		new GenericEventHandler<MainWindow>( this, &MainWindow::onSingletextCtrlSelectionChanged, "MainWindow::onSingletextCtrlSelectionChanged" );


	label = new Label();
	label->setCaption( "Selection start:" );
	container->add( label );

	label = new Label();
	label->setName( "SelectionStart" );
	container->add( label );

	label = new Label();
	label->setCaption( "Selection count:" );
	container->add( label );

	label = new Label();
	label->setName( "SelectionCount" );
	container->add( label );


	label = new Label();

	label->setCaption( "Multi Line Text:" );
	container->add( label );


	MultilineTextControl* multiTextCtrl = new MultilineTextControl();
	multiTextCtrl->setHeight( 200 );
	container->add( multiTextCtrl );


	String text = "a\nb\nc\nd";
	int c = text.size();
	TextModel* textModel = multiTextCtrl->getTextModel();
	textModel->setText( text );
}



void MainWindow::makeTreePage()
{
	Container* container = treePage_->getPageComponent()->getContainer();

	Label* label = new Label();
	label->setWidth( 200 );
	container->add( label, AlignLeft );
	label->setWordWrap( true );

	String s = "This is a TreeControl.\n"\
				"Many neat things can be done with it. For Win32 "\
				"platforms this is a direct wrapper around the TREEVIEW "\
				"control.";
	label->setCaption( s );
	TreeControl* tc = new TreeControl();

	TreeItem* i = tc->addItem( NULL, "Item 1" );
	tc->addItem( i, "Item 1a" );
	tc->addItem( i, "Item 1b" );
	tc->addItem( i, "Item 1c" );
	tc->addItem( i, "Item 1d" );
	tc->addItem( i, "Item 1e" );
	tc->addItem( i, "Item 1f" );
	tc->addItem( i, "Item 1g" );
	tc->addItem( i, "Item 1h" );
	tc->addItem( i, "Item 1i" );

	container->add( tc, AlignClient );
}

/**
$Id$
*/
