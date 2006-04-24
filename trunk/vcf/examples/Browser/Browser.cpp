//Browser.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/DefaultTreeItem.h"
#include "vcf/HTMLKit/HTMLKit.h"


namespace VCF {


	class URLCombo : public ComboBoxControl {
	public:
		DELEGATE(URLChanged);

		URLCombo(){
			edit_->KeyPressed += 
				new KeyboardEventHandler<URLCombo>( this, &URLCombo::onCBEditReturnKeyPressed, "URLCombo::onCBEditReturnKeyPressed" );
		}

		void onCBEditReturnKeyPressed( KeyboardEvent* event ) {
			if ( vkReturn == event->getVirtualCode() ) {
				Event e(this);
				URLChanged.fireEvent( &e );
			}
		}
	};



	class ActionManager : public Component {
	public:
		ActionManager( Component* owner ) : Component(owner){}
		ActionManager(){}
		virtual ~ActionManager(){}

		Action* addAction( const String& name ) {
			Action* action = new Action(this);
			action->setName( name );			
			return action;
		}

		void addTarget( const String& actionName, Component* component ) {
			Action* action = (Action*) findComponent( actionName );
			if ( NULL == action ) {
				action = addAction( actionName );
			}
			action->addTarget(component) ;
		}

		Action* getAction( const String& action ) {
			return (Action*) findComponent( action );
		}

		void addPerformed( const String& actionName, EventHandler* ev ) {
			Action* action = (Action*) findComponent( actionName );
			if ( NULL == action ) {
				action = addAction( actionName );
			}

			action->Performed += ev;
		}

		void addUpdate( const String& actionName, EventHandler* ev ) {
			Action* action = (Action*) findComponent( actionName );
			if ( NULL == action ) {
				action = addAction( actionName );
			}

			action->Update += ev;
		}
	};

};

using namespace VCF;



class CustomHTMLUI : public Window {
public:
	CustomHTMLUI() {
		browser = new HTMLBrowserControl();

		setCaption( "Custom HTML UI" );

		browser->URLLoaded += 
			new GenericEventHandler<CustomHTMLUI>(this,&CustomHTMLUI::onURLLoaded, "CustomHTMLUI::onURLLoaded" );

		browser->BeforePopupMenu += 
			new GenericEventHandler<CustomHTMLUI>(this,&CustomHTMLUI::onPopupMenu, "CustomHTMLUI::onPopupMenu" );

		add( browser, AlignClient );

		browser->setAllowsScrollbars(false);
		browser->setAllowsTextSelection(false);
		browser->setAllowDefaultContextMenu(false);
		
		

		String resHTML = System::findResourceDirectory() + "customUI.html";

		browser->setCurrentURL( resHTML );

		PopupMenu* contextMenu = new PopupMenu(this);
		MenuItem* root = contextMenu->getRootMenuItem();
		DefaultMenuItem* pmItem1 = new DefaultMenuItem( "Hello", root,contextMenu );
		DefaultMenuItem* pmItem2 = new DefaultMenuItem( "There!", root,contextMenu );

		browser->setPopupMenu( contextMenu );
	}

	HTMLBrowserControl* browser;
protected:
	void onURLLoaded( Event* e ) {
		//add callbacks for various UI elements here

		browser->setElementClickedEventHandler( "ClickMe", 
			new GenericEventHandler<CustomHTMLUI>(this,&CustomHTMLUI::onElementClicked, "CustomHTMLUI::onElementClicked" ) ); 

		browser->setElementClickedEventHandler( "DoItBtn", 
			new GenericEventHandler<CustomHTMLUI>(this,&CustomHTMLUI::onButtonClicked, "CustomHTMLUI::onButtonClicked" ) ); 		

	}

	void onElementClicked( Event* e ) {
		HTMLElementEvent* htmElementEv = (HTMLElementEvent*)e;

		Dialog::showMessage( "Element \"" + htmElementEv->elementID + "\" clicked!" );
	}


	void onButtonClicked( Event* e ) {
		static bool theWeatherIsSunny = false;

		if ( theWeatherIsSunny ) {
			browser->setElementHTMLText( "weatherValue", "Sunny<img src=\"mostly_sunny.gif\">" );
		}
		else {
			browser->setElementHTMLText( "weatherValue", "Maybe Rainy<img src=\"chance_of_rain.gif\">" );
		}

		theWeatherIsSunny = !theWeatherIsSunny;
	}

	void onPopupMenu( Event* e ) {
		ControlPopupMenuMenuEvent* popupMenuEvent = (ControlPopupMenuMenuEvent*)e;

		String id = browser->getActiveElementID();

		if ( id == "ctxMenuPara" ) {
			MenuItem* item = popupMenuEvent->popupMenu->getRootMenuItem()->getChildAt(0);
			item->setCaption( id );
		}
		else {MenuItem* item = popupMenuEvent->popupMenu->getRootMenuItem()->getChildAt(0);
			item->setCaption( "Hello" );
		}
	}
};

class BrowserApp : public Application {
public:

	BrowserApp( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );
	}
	

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		
		



		Window* mainWindow = new Window();
		setMainWindow(mainWindow);
		mainWindow->setBounds( 100.0, 100.0, 500.0, 500.0 );

		browser = new HTMLBrowserControl();
		browser->setDoubleBuffered( false );
		mainWindow->add( browser, AlignClient );

		browser->StatusChanged += 
			new GenericEventHandler<BrowserApp>(this,&BrowserApp::onHTMLStatusChanged, "BrowserApp::onHTMLStatusChanged" );

		browser->URLLoaded += 
			new GenericEventHandler<BrowserApp>(this,&BrowserApp::onURLLoaded, "BrowserApp::onURLLoaded" );

		browser->URLLoadingBegun += 
			new GenericEventHandler<BrowserApp>(this,&BrowserApp::onURLLoadingBegun, "BrowserApp::onURLLoadingBegun" );





		Toolbar* tb = new Toolbar();
		tb->setName( "Toolbar1" );
		tb->setHeight( 25 );
		mainWindow->add( tb, AlignTop );


		ImageList* il = new ImageList(mainWindow);
		il->setImageHeight( 17 );
		il->setImageWidth( 17 );
		il->setTransparentColor( &Color( (uchar)212, (uchar)208, (uchar)200 ) );		

		tb->setImageList( il );

		GraphicsResourceBundle* resBundle = getResourceBundle();
		Image* img = resBundle->getImage( "back.png" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "forward.png" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "refresh.png" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "home.png" );
		il->addImage( img );
		delete img;

		img = resBundle->getImage( "go.png" );
		il->addImage( img );
		delete img;


		ToolbarItem* item = tb->addToolBarButton( "back" );
		item->setImageIndex(0);
		item->setTooltip( "Go back one page" );

		item = tb->addToolBarButton( "forward" );
		item->setImageIndex(1);
		item->setTooltip( "Go forward one page" );

		

		item = tb->addToolBarButton( "refresh" );
		item->setImageIndex(2);
		item->setTooltip( "Reload current page" );

		item = tb->addToolBarButton( "home" );
		item->setImageIndex(3);
		item->setTooltip( "Load home page" );


		item = tb->addToolBarButton( "url" );
		item->setEnabled( false );

		urlBox = new URLCombo();
		urlBox->setWidth( 250 );
		urlBox->setComboBoxStyle( cbsDropDownWithEdit );
		urlBox->URLChanged += 
			new GenericEventHandler<BrowserApp>(this,&BrowserApp::urlChanged,"BrowserApp::urlChanged");

		item->setItemControl( urlBox );		
		

		item = tb->addToolBarButton( "go" );
		item->setImageIndex(4);
		item->setTooltip( "Load URL" );


		tb->addToolBarButton( "" )->setAsSeparator();


		allowPopupsBtn = new CheckBoxControl();
		allowPopupsBtn->setWidth( 100 );
		allowPopupsBtn->setCaption( "Allow Popups" );		
		allowPopupsBtn->setChecked( browser->getAllowsPopupWindows() );

		allowPopupsBtn->ButtonClicked += 
			new GenericEventHandler<BrowserApp>(this,&BrowserApp::onAllowPopupsChecked, "BrowserApp::onAllowPopupsChecked" );

		

		item = tb->addToolBarButton( "popups" );
		item->setEnabled( false );
		item->setItemControl( allowPopupsBtn );		


		tb->addToolBarButton( "" )->setAsSeparator();

		editDocument = new CheckBoxControl();
		editDocument->setWidth( 200 );
		editDocument->setCaption( "Edit current document" );		
		editDocument->setChecked( false );

		editDocument->ButtonClicked += 
			new GenericEventHandler<BrowserApp>(this,&BrowserApp::onEditCurrentDocChecked, "BrowserApp::onEditCurrentDocChecked" );

		

		item = tb->addToolBarButton( "editDoc" );
		item->setEnabled( false );
		item->setItemControl( editDocument );	

		

		statusLabel = new Label();
		statusLabel->setCaption( "Enter URL" );

		Panel* statPane = new Panel();
		statPane->setBorder( NULL );
		statPane->setHeight( statusLabel->getPreferredHeight() + 5 );
		statPane->add( statusLabel, AlignClient );
		
		mainWindow->add( statPane, AlignBottom );



		TreeControl* treeCtrl = new TreeControl();
		treeCtrl->setWidth( 100 );
		mainWindow->add( treeCtrl, AlignLeft );
		Splitter* splitter = new Splitter();
		mainWindow->add( splitter, AlignLeft );
		
		documentTree = treeCtrl->getTreeModel();



		mgr = new ActionManager(mainWindow);




		MenuBar* menuBar = new MenuBar(mainWindow);
		mainWindow->setMenuBar( menuBar );
		MenuItem* root = menuBar->getRootMenuItem();
		DefaultMenuItem* app = new DefaultMenuItem( "Browser App", root, menuBar );

		DefaultMenuItem* appEVDemo = new DefaultMenuItem( "Event Handler Demo...", app, menuBar );
		

		mgr->addTarget( "appEVDemo", appEVDemo );
		mgr->addPerformed( "appEVDemo", new GenericEventHandler<BrowserApp>(this, &BrowserApp::doEventHandlerDemo, "BrowserApp::doEventHandlerDemo" ) );




		
		


		//hook up actions
		ToolbarModel* tbModel = tb->getToolbarModel();

		mgr->addTarget( "back", tbModel->getItemAtIndex(0) );
		mgr->addPerformed( "back", new GenericEventHandler<BrowserApp>(this, &BrowserApp::back, "BrowserApp::back" ) );

		
		mgr->addTarget( "forward", tbModel->getItemAtIndex(1) );
		mgr->addPerformed( "forward", 
			new GenericEventHandler<BrowserApp>(this, &BrowserApp::forward, "BrowserApp::forward" ) );

		mgr->addTarget( "refresh", tbModel->getItemAtIndex(2) );
		mgr->addPerformed( "refresh", 
			new GenericEventHandler<BrowserApp>(this, &BrowserApp::refresh, "BrowserApp::refresh" ) );

		mgr->addTarget( "home", tbModel->getItemAtIndex(3) );
		mgr->addPerformed( "home", 
			new GenericEventHandler<BrowserApp>(this, &BrowserApp::home, "BrowserApp::home" ) );

		mgr->addTarget( "go", tbModel->getItemAtIndex(5) );
		mgr->addPerformed( "go", 
			new GenericEventHandler<BrowserApp>(this, &BrowserApp::go, "BrowserApp::go" ) );



		browser->setCurrentURL( "http://vcf-online.org" );

		mainWindow->setCaption( "Browser" );

		mainWindow->show();
		
		return result;
	}

protected:
	HTMLBrowserControl* browser;
	URLCombo* urlBox;
	ActionManager* mgr;
	Label* statusLabel;
	CheckBoxControl* allowPopupsBtn;
	CheckBoxControl* editDocument;
	TreeModel* documentTree;

	void urlChanged( Event* ) {
		browser->setCurrentURL( urlBox->getCurrentText() );	
	}

	void go( Event* ) {
		browser->setCurrentURL( urlBox->getCurrentText() );
	}

	void back( Event* ) {
		browser->goBack();
	}

	void forward( Event* ) {
		browser->goForward();
	}

	void home( Event* ) {
		browser->goHome();
	}

	void refresh( Event* ) {
		browser->refresh();
	}

	void onHTMLStatusChanged( Event* e ) {
		HTMLEvent* htmlEvent = (HTMLEvent*)e;

		statusLabel->setCaption( htmlEvent->status );
	}

	void doEventHandlerDemo( Event* ) {
		CustomHTMLUI* window = new CustomHTMLUI();
		window->setBounds( 100, 100, 500, 500 );
		window->show();
	}


	void walkElements( HTMLElement& parent, TreeItem* treeItemParent ) {
		HTMLElementCollection children = parent.getChildren();

		long length = children.getLength();
		for (long i=0;i<length;i++ ) {
			HTMLElement* child = children.item(i);
			String s = child->getOuterText();

			String title = "<" + child->getTagName() + ">";
			if ( !s.empty() ) {
				title += " " + s.substr(0,minVal<size_t>(s.size(),25));
			}

			TreeItem* item = new DefaultTreeItem( title );

			documentTree->addNodeItem( item, treeItemParent );

			walkElements( *child, item );
		}
	}
	
	void onURLLoadingBegun( Event* e ) {
		browser->setCursorID( Cursor::SCT_WAITING );
	}

	void onURLLoaded( Event* e ) {
		browser->setCursorID( Cursor::SCT_DEFAULT );

		HTMLEvent* htmlEvent = (HTMLEvent*)e;
		urlBox->setCurrentText( htmlEvent->url );
		getMainWindow()->setCaption( browser->getTitle() + " - Browser" );

		editDocument->setChecked( false );

		//walk the DOM tree

		//first clear out the old stuff
		Model* treeModel = dynamic_cast<Model*>(documentTree);
		treeModel->empty();


		HTMLDocument doc = browser->getDocument();

		if ( !doc.null() ) {			
			HTMLElement body = doc.getBody();			
			TreeItem* item = new DefaultTreeItem( doc.getTitle() + " - Body" );
			documentTree->addNodeItem( item );
			walkElements( body, item );
		}
	}

	void onAllowPopupsChecked( Event* ) {
		browser->setAllowsPopupWindows( allowPopupsBtn->isChecked() );

	}

	void onEditCurrentDocChecked( Event* ) {
		browser->edit( editDocument->isChecked() );

	}

	
};


int main(int argc, char *argv[])
{
	Application* app = new BrowserApp( argc, argv );

	Application::main();
	
	HTMLKit::terminate();

	return 0;
}


