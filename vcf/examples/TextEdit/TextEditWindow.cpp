//TextEditWindow.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "TextEditWindow.h"
#include "TextEditDocument.h"
#include "TextEdit.h"

using namespace VCF;



TextEditWindow::TextEditWindow():
	docSelectionChanging_(false)
{
	DocumentManager* docMgr = DocumentManager::getDocumentManager();
	docMgr->DocumentInitialized += new GenericEventHandler<TextEditWindow>( this, 
																			&TextEditWindow::onDocInitialized,
																			"TextEditWindow::onDocInitialized" );

	MultilineTextControl* tc = new MultilineTextControl();
	tc->setName( "EditControl" );
	add( tc, AlignClient );

	tc->setKeepTabbingCharacters( true );
	setTabStop( false );

	tc->SelectionChanged += 
		new GenericEventHandler<TextEditWindow>( this, &TextEditWindow::onSelectionChanged, "TextEditWindow::onSelectionChanged" );


	tc->disableStandardAccelerators();

	initMenus();

	initToolbar();

}

TextEditWindow::~TextEditWindow()
{

}

void TextEditWindow::initToolbar() 
{
	Toolbar* tb = new Toolbar();
	tb->setName( "Toolbar1" );
	tb->setHeight( 25 );

	add( tb, AlignTop );
	
	ImageList* il = new ImageList();
	il->setImageHeight( 19 );
	il->setImageWidth( 19 );
	il->setTransparentColor( &Color( 0.0, 1.0, 0.0) );
	addComponent( il );
	
	tb->setImageList( il );
	

	GraphicsResourceBundle* resBundle = Application::getRunningInstance()->getResourceBundle();
	Image* img = resBundle->getImage( "new.bmp" );
	il->addImage( img );
	delete img;
	
	img = resBundle->getImage( "open.bmp" );
	il->addImage( img );
	delete img;
	
	img = resBundle->getImage( "save.bmp" );
	il->addImage( img );
	delete img;
	
	img = resBundle->getImage( "cut.bmp" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "copy.bmp" );
	il->addImage( img );
	delete img;
	
	img = resBundle->getImage( "paste.bmp" );
	il->addImage( img );
	delete img;
	
	img = resBundle->getImage( "undo.bmp" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "redo.bmp" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "find.bmp" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "replace.bmp" );
	il->addImage( img );
	delete img;
	
	img = resBundle->getImage( "print.bmp" );
	il->addImage( img );
	delete img;

	DocumentManager* docMgr = DocumentManager::getDocumentManager();

	ToolbarItem* newItem = tb->addToolBarButton( "New" );
	newItem->setTooltip( "New Text Document" );
	
	docMgr->getAction( DocumentManager::atFileNew )->addTarget( newItem );

	tb->addToolBarButton( "" )->setAsSeparator();

	ToolbarItem* openItem = tb->addToolBarButton( "Open" );
	openItem->setImageIndex( 1 );
	
	openItem->setTooltip( "Open from file" );
	docMgr->getAction( DocumentManager::atFileOpen )->addTarget( openItem );

	ToolbarItem* saveItem = tb->addToolBarButton( "Save" );
	saveItem->setImageIndex( 2 );
	saveItem->setTooltip( "Save to file" );
	docMgr->getAction( DocumentManager::atFileSave )->addTarget( saveItem );
	
	tb->addToolBarButton( "" )->setAsSeparator();

	
	ToolbarItem* printItem = tb->addToolBarButton( "Print" );
	printItem->setImageIndex( 10 );
	printItem->setTooltip( "Print Document" );
	docMgr->getAction( TextEdit::atFilePrint )->addTarget( printItem );

	
	tb->addToolBarButton( "" )->setAsSeparator();

	
	ToolbarItem* cutItem = tb->addToolBarButton( "Cut" );
	cutItem->setImageIndex( 3 );
	cutItem->setTooltip( "Cut" );
	docMgr->getAction( DocumentManager::atEditCut )->addTarget( cutItem );

	
	ToolbarItem* copyItem = tb->addToolBarButton( "Copy" );
	copyItem->setImageIndex( 4 );
	copyItem->setTooltip( "Copy" );
	docMgr->getAction( DocumentManager::atEditCopy )->addTarget( copyItem );

	
	ToolbarItem* pasteItem = tb->addToolBarButton( "Paste" );
	pasteItem->setImageIndex( 5 );
	pasteItem->setTooltip( "Paste" );
	docMgr->getAction( DocumentManager::atEditPaste )->addTarget( pasteItem );

	
	tb->addToolBarButton( "" )->setAsSeparator();


	ToolbarItem* undoItem = tb->addToolBarButton( "Undo" );
	
	undoItem->setImageIndex( 6 );
	
	undoItem->setTooltip( "Undo" );
	
	docMgr->getAction( DocumentManager::atEditUndo )->addTarget( undoItem );

	
	ToolbarItem* redoItem = tb->addToolBarButton( "Redo" );
	redoItem->setImageIndex( 7 );
	redoItem->setTooltip( "Redo" );
	docMgr->getAction( DocumentManager::atEditRedo )->addTarget( redoItem );

	tb->addToolBarButton( "" )->setAsSeparator();


	ToolbarItem* findItem = tb->addToolBarButton( "Find" );
	findItem->setImageIndex( 8 );
	findItem->setTooltip( "Find text in document" );
	docMgr->getAction( TextEdit::atEditFind )->addTarget( findItem );

	ToolbarItem* replaceItem = tb->addToolBarButton( "Replace" );
	replaceItem->setImageIndex( 9 );
	replaceItem->setTooltip( "Replace text in document" );
	docMgr->getAction( TextEdit::atEditReplace )->addTarget( replaceItem );
}

void TextEditWindow::initMenus()
{
	MenuBar* menuBar = new MenuBar();
	setMenuBar( menuBar );
	addComponent( menuBar );

	MenuItem* file = new DefaultMenuItem( "&File", menuBar->getRootMenuItem(), menuBar );
	

	MenuItem* view = new DefaultMenuItem( "&View", menuBar->getRootMenuItem(), menuBar );
	MenuItem* viewToolbar = new DefaultMenuItem( "&Toolbar", view, menuBar );

	viewToolbar->MenuItemClicked += 
						new MenuItemEventHandler<TextEditWindow>( this, &TextEditWindow::viewToolbarClicked, "TextEditWindow::viewToolbarClicked" );	

	viewToolbar->MenuItemUpdate += 
						new MenuItemEventHandler<TextEditWindow>( this, &TextEditWindow::updateViewToolbar, "TextEditWindow::updateViewToolbar" );

	
	MenuItem* help = new DefaultMenuItem( "&Help", menuBar->getRootMenuItem(), menuBar );
	MenuItem* helpAbout = new DefaultMenuItem( "&About...", help, menuBar );	
}

void TextEditWindow::viewToolbarClicked( VCF::MenuItemEvent* e )
{

}

void TextEditWindow::updateViewToolbar( VCF::MenuItemEvent* e )
{

}

/**
* This will get called each time a new document is created, after it has been 
* intialized by the DocumentManager.
*
* The TextEditWindow acts as a sort of "Controller" between the document
*   and the edit control, so that when the document's selection changes the text
*   control's selection is updated, and when the text control changes it's selection
*   the document is correspondingly updated.
*/
void TextEditWindow::onDocInitialized( VCF::Event* e )
{	
	//initialization code can go here

	MultilineTextControl* tc = (MultilineTextControl*) findComponent( "EditControl" );
	TextEditDocument* doc = (TextEditDocument*)e->getSource();

	tc->setTextModel( doc );
	doc->addView( tc );

	EventHandler* evh = getEventHandler( "TextEditWindow::onModelChanged" );
	if ( NULL == evh ) {
		evh = new GenericEventHandler<TextEditWindow>( this, &TextEditWindow::onModelChanged, "TextEditWindow::onModelChanged" );
	}

	doc->addModelHandler( evh );

	tc->setFocused();


	
}

void TextEditWindow::onModelChanged( VCF::Event* e )
{
	if ( e->getType() == TextEditDocument::teTextSelectionChanged ) {
		docSelectionChanging_ = true;
		MultilineTextControl* tc = (MultilineTextControl*) findComponent( "EditControl" );
		TextEditDocument* doc = (TextEditDocument*)e->getSource();

		tc->setSelectionMark( doc->getSelectionStart(), doc->getSelectionLength() );

		docSelectionChanging_ = false;
	}
}

void TextEditWindow::onSelectionChanged( VCF::Event* e )
{
	if ( !docSelectionChanging_ ) {
		TextEvent* te = (TextEvent*) e;
		
		int start = te->getSelectionStart();
		
		MultilineTextControl* tc = (MultilineTextControl*)e->getSource();
		TextEditDocument* doc = (TextEditDocument*)tc->getViewModel();
		
		doc->setSelectionRange( start, te->getSelectionLength() );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:34:47  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.1  2005/07/23 21:45:43  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.2.2.7  2005/06/06 02:34:05  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.2.2.6  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.2.2.5  2005/05/05 12:42:25  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.2.2.4  2005/05/04 20:58:54  marcelloptr
*standard file formatting and cvs log section added. More documentation.
*
*/



