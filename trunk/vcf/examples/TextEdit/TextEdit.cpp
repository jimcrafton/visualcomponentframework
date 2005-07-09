//TextEdit.cpp


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/TextPeer.h"


#include "TextEditDocument.h"
#include "TextEditWindow.h"
#include "FindDialog.h"
#include "ReplaceDialog.h"

#include "TextEdit.h"


using namespace VCF;



TextEdit::TextEdit( int argc, char *argv[] ) : 
	SDIDocumentBasedApplication(argc,argv) 
{

}

void TextEdit::onExit( VCF::Event* e )
{
	getMainWindow()->close();
}
	
void TextEdit::onPrint( VCF::Event* e )
{
	

	TextEditDocument* currentDoc = (TextEditDocument*)getCurrentDocument();

	CommonPrint dlg( currentDoc->getWindow() );

	

	dlg.setTitle( "Print Document " + currentDoc->getName() );

	if ( dlg.execute() ) {
		PrintSession printSession;				

		printSession.setPrintInfoHandle( dlg.getPrintInfo() );
		
		printSession.setTitle( "My Print Doc" );

		PrintContext* pc = printSession.beginPrintingDocument();

		Control* textControl = (Control*)currentDoc->getWindow()->findComponent( "EditControl" );
		TextEditPeer* textPeer = dynamic_cast<TextEditPeer*>(textControl->getPeer());
		ulong32 pageCount = textPeer->getTotalPrintablePageCount( pc );
		ulong32 page = printSession.getStartPage();
		while ( page <= pageCount ) {

			printSession.beginPage( pc );

			textPeer->print( pc, page );

			printSession.endPage( pc );

			page ++;
		}

		textPeer->finishPrinting();

		printSession.endPrintingDocument();

		pc->free();
	}

}

void TextEdit::onUpdatePrint( VCF::ActionEvent* e )
{

}

void TextEdit::onFind( VCF::Event* e )	
{
	TextEditDocument* currentDoc = (TextEditDocument*)getCurrentDocument();
	currentFindInfo_.position_ = currentDoc->getSelectionStart();
	
	if ( currentDoc->getSelectionLength() > 0 ) {			
		currentFindInfo_.searchString_ = currentDoc->getText().substr( currentFindInfo_.position_, currentDoc->getSelectionLength() );
	}
	
	FindDialog* dlg = new FindDialog();
	dlg->caseSensitive_ = currentFindInfo_.caseSensitive_;
	dlg->matchWordOnly_ = currentFindInfo_.matchWordOnly_;
	dlg->searchStrings_ = currentFindInfo_.searchStrings_;
	dlg->searchString_ = currentFindInfo_.searchString_;
	dlg->setFrameTopmost( true );
	dlg->showModal();
	dlg->free();
	
}

void TextEdit::onUpdateFind( VCF::ActionEvent* e ) 
{
	

}

void TextEdit::onReplace( VCF::Event* e )	
{
	TextEditDocument* currentDoc = (TextEditDocument*)getCurrentDocument();
	if ( NULL != currentDoc ) {
		currentReplaceInfo_.position_ = currentDoc->getSelectionStart();
		
		if ( currentDoc->getSelectionLength() > 0 ) {			
			currentReplaceInfo_.searchString_ = currentDoc->getText().substr( currentReplaceInfo_.position_, currentDoc->getSelectionLength() );
		}
	}
	
	ReplaceDialog * dlg = new ReplaceDialog();
	
	
	dlg->caseSensitive_ = currentReplaceInfo_.caseSensitive_;
	dlg->matchWordOnly_ = currentReplaceInfo_.matchWordOnly_;
	dlg->searchStrings_ = currentReplaceInfo_.searchStrings_;
	dlg->searchString_ = currentReplaceInfo_.searchString_;
	
	dlg->replaceStrings_ = currentReplaceInfo_.replaceStrings_;
	dlg->replaceString_ = currentReplaceInfo_.replaceString_;
	
	dlg->setFrameTopmost( true );
	dlg->showModal();
	dlg->free();
}

void TextEdit::onUpdateReplace( VCF::ActionEvent* e ) 
{

}

bool TextEdit::initRunningApplication()
{

	REGISTER_CLASSINFO( TextEditDocument );
	//REGISTER_CLASSINFO( TextEditView );
	REGISTER_CLASSINFO( TextEditWindow );

	bool result = SDIDocumentBasedApplication::initRunningApplication();	
	if ( result ) {

		//Add our custom actions here

		Action*	printAction = new Action();
		printAction->setName("EditFind");
		printAction->Performed += 
			new GenericEventHandler<TextEdit>( this, &TextEdit::onPrint, "TextEdit::onPrint" );
		
		printAction->Update += 
			new EventHandlerInstance<TextEdit,ActionEvent>( this, &TextEdit::onUpdatePrint,"TextEdit::onUpdatePrint" );
		
		addAction( TextEdit::atFilePrint, printAction );


		Action*	findAction = new Action();
		findAction->setName("EditFind");
		findAction->Performed += 
			new GenericEventHandler<TextEdit>( this, &TextEdit::onFind, "TextEdit::onFind" );
		
		findAction->Update += 
			new EventHandlerInstance<TextEdit,ActionEvent>( this, &TextEdit::onUpdateFind,"TextEdit::onUpdateFind" );
		
		addAction( TextEdit::atEditFind, findAction );
		
		Action*	replaceAction = new Action();
		replaceAction->setName("EditReplace");
		replaceAction->Performed += 
			new GenericEventHandler<TextEdit>( this, &TextEdit::onReplace, "TextEdit::onReplace" );
		
		replaceAction->Update += 
			new EventHandlerInstance<TextEdit,ActionEvent>( this, &TextEdit::onUpdateReplace,"TextEdit::onUpdateReplace" );
		
		addAction( TextEdit::atEditReplace, replaceAction );

		/**
		add additional menu items	
		*/
		
		MenuItem* root = MenuManager::getMainMenu()->getRootMenuItem();
		MenuItem* edit = root->findChildNamedSimilarTo( "edit" );
		ulong32 editCount = edit->getChildCount();
		
		
		MenuItem* find = new DefaultMenuItem( "&Find..." );	
		find->setAcceleratorKey( vkLetterF, kmCtrl );
		findAction->addTarget( find ); 
		
		DefaultMenuItem* replace = new DefaultMenuItem( "&Replace..." );	
		replace->setAcceleratorKey( vkLetterH, kmCtrl );
		replaceAction->addTarget( replace ); 
		
		

		DefaultMenuItem* sep = new DefaultMenuItem( "" );
		sep->setSeparator( true );
		
		//why -2? Becasue we want to be above the preferences item and the separator 
		//directly above it
		edit->insertChild( editCount-2, sep );
		editCount ++;
		
		edit->insertChild( editCount-2, find );
		editCount ++;		
		
		edit->insertChild( editCount-2, replace );
		editCount ++;
		
		
		MenuItem* file = root->findChildNamedSimilarTo( "file" );

		sep = new DefaultMenuItem( "" );
		sep->setSeparator( true );
		file->addChild( sep );

		DefaultMenuItem* fileExit = new DefaultMenuItem( "E&xit" );	
		fileExit->MenuItemClicked += 
				new GenericEventHandler<TextEdit>( this, &TextEdit::onExit, "TextEdit::onExit" );

		file->addChild( fileExit );

		

		newDefaultDocument();
		
		DocumentManager* docMgr = DocumentManager::getDocumentManager();
		docMgr->DocumentInitialized += 
			new GenericEventHandler<TextEdit>( this, &TextEdit::onDocInitialized, "TextEdit::onDocInitialized" );
		
	}
	return result;
}

void TextEdit::terminateRunningApplication() 
{
	SDIDocumentBasedApplication::terminateRunningApplication();

	
}

void TextEdit::onDocInitialized( Event* e ) 
{
	Document* doc = (Document*)e->getSource();		

}



int main(int argc, char *argv[])
{
	Application* app = new TextEdit( argc, argv );

	Application::main();
	
	return 0;
}



/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:45  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.2.3  2005/06/06 02:34:05  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.2.2.2  2005/05/05 12:42:25  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.2.2.1  2005/05/04 20:47:20  marcelloptr
*standard file formatting and cvs log section added
*
*/


