//MainWindow.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/ApplicationKit/TitledBorder.h"
#include "vcf/GraphicsKit/DrawUIState.h"
#include "MainWindow.h"
#include "QTPlayerApplication.h"
#include "QTPlayerAbout.h"
#include "QuickTimeControl.h"
#include "vcf/FoundationKit/StringTokenizer.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/ApplicationKit/DefaultListItem.h"
#include "vcf/ApplicationKit/DefaultTreeItem.h"
#include "vcf/ApplicationKit/HorizontalLayoutContainer.h"


using namespace VCF;



class PlayListDictionary : public Dictionary {
public:


	virtual ~PlayListDictionary() {
		deleteAll(getEnumerator());
	}


	PlayListDictionary* addPlayList( const String& name ) {
		PlayListDictionary* result = new PlayListDictionary();

		insert( name, result );

		return result;
	}

	void removePlaylist( const String& name ) {
		remove( name );
	}

	void addMedia( const String& name, const String& fileName ) {
		insert( name, fileName );
	}

	void removeMedia( const String& name ) {
		remove( name );
	}

	void clear() {
		deleteAll(getEnumerator());
	}

	PlayListDictionary* get( const String& name ) {
		PlayListDictionary* result = NULL;
		Object* o = (*this)[name];
		if ( NULL != o ) {
			result = (PlayListDictionary*)o;
		}

		return result;
	}

protected:
	void deleteAll( Dictionary::Enumerator* items ) {
		while ( items->hasMoreElements() ) {
			Dictionary::pair item = items->nextElement();

			if ( pdObject == item.second.type ) {
				PlayListDictionary* pl = (PlayListDictionary*) (Object*)item.second;
				Dictionary::Enumerator* subItems = pl->getEnumerator();

				pl->free();
			}
		}

		Dictionary::clear();
	}
};


#define  PLAYLISTDICTIONARY_CLASSID  "1b8c4955-f290-49fb-93a8-39aae4bce3ec"

_class_rtti_( PlayListDictionary, "VCF::Object", PLAYLISTDICTIONARY_CLASSID )
_class_rtti_end_


class PlayListItem : public DefaultListItem {
public:
	PlayListItem( Control* control, const String& caption,
					ListModel* model ):
	  DefaultListItem( model, caption ),control_(control) {

	}

	virtual void paint( GraphicsContext* gc, VCF::Rect* paintRect ) {
		//DefaultListItem::paint( gc, paintRect );
		//Light3DBorder bdr;
		//bdr.paint( paintRect, gc );
		VCF::Rect tmp = *paintRect;

		VCF::Rect clientRect = control_->getClientBounds();

		tmp.right_ = clientRect.right_;

		Font oldFont = *gc->getCurrentFont();
		if ( isSelected() ) {
			gc->setColor( GraphicsToolkit::getSystemColor(SYSCOLOR_SELECTION) );
			gc->getCurrentFont()->setColor( GraphicsToolkit::getSystemColor(SYSCOLOR_SELECTION_TEXT) );
		}
		else {
			gc->getCurrentFont()->setColor( control_->getFont()->getColor() );
			if ( !(getIndex() % 2) ) {
				gc->setColor( Color::getColor( "lightsteelblue" ) );
			}
			else {
				gc->setColor( control_->getColor() );
			}
		}
		gc->rectangle( &tmp );
		gc->fillPath();

		if ( isSelected() ) {
			DrawUIState state;
			state.setFocused(true);
			gc->drawThemeSelectionRect( &tmp, state );
		}

		tmp.right_ = paintRect->right_;
		tmp.inflate( -2, -2 );
		long options = GraphicsContext::tdoCenterVertAlign | GraphicsContext::tdoLeftAlign;
		gc->textBoundedBy( &tmp, getCaption(), options );
		gc->setCurrentFont( &oldFont );
	}

	virtual bool canPaint() {
		return false;
	}

	String getID() {
		return id_;
	}

	void setID( const String& id ) {
		id_ = id;
	}

	String id_;

	Control* control_;
};



class PlayListTreeItem : public DefaultTreeItem {
public:

	PlayListTreeItem( const String& caption ) : DefaultTreeItem(caption){}


	String getID() {
		return id_;
	}

	void setID( const String& id ) {
		id_ = id;
	}

	String id_;
};


class PagedContainer : public StandardContainer {
public:

	void showPage( Control* control ) {
		if ( !pages_.empty() ) {
			std::deque<Control*>::iterator found = std::find( pages_.begin(), pages_.end(), control );

			if ( found != pages_.end() ) {
				pages_.erase( found );
				pages_.push_back( control );
			}


			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	void first() {
		if ( !pages_.empty() ) {
			//resort the pages_
			Control* control = controls_.front();

			while ( control != pages_.front() ) {
				Control* tmp = pages_.front();
				pages_.pop_front();
				pages_.push_back( tmp );
			}


			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	void last() {
		if ( !pages_.empty() ) {
			Control* control = controls_.back();

			while ( control != pages_.front() ) {
				Control* tmp = pages_.front();
				pages_.pop_front();
				pages_.push_back( tmp );
			}

			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	void next() {
		if ( !pages_.empty() ) {
			Control* control = pages_.front();
			pages_.pop_front();
			pages_.push_back( control );

			control = pages_.front();

			std::deque<Control*>::iterator it = pages_.begin();
			while ( it != pages_.end() ) {
				if ( *it != control ) {
					(*it)->setVisible( false );
				}
				it ++;
			}

			control->setVisible( true );
		}
	}

	virtual void resizeChildren( Control* control ) {
		//controlContainer_ is the control that this container is attached to
		VCF::Rect clientBounds = controlContainer_->getClientBounds();

		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		clientBounds.setRect( clientBounds.left_ + leftBorderWidth_,
								clientBounds.top_ + topBorderHeight_,
								clientBounds.right_ - rightBorderWidth_,
								clientBounds.bottom_ - bottomBorderHeight_ );



		bool controlJustAdded = false;
		if ( NULL != control ) {
			//we may have to position this separately - if it is the first time it
			//has been added then it will not be in the child control list
			//search for the control
			std::vector<Control*>::iterator found = std::find( controls_.begin(), controls_.end(), control );

			//if found equals the controls_.end, then control has not been added yet, and this is the first time
			//this control has been positioned for this container
			controlJustAdded = ( found == controls_.end() );
		}


		if ( controlJustAdded ) {
			control->setBounds( &clientBounds );
			pages_.push_back( control );
		}
		else {
			//note: we could have used the containers vector - this would be ever so slightly faster,
			//but this is a bit cleaner for the sake of an example.
			Enumerator<Control*>* children = AbstractContainer::getChildren();

			while ( children->hasMoreElements() ) {
				Control* child = children->nextElement();
				if ( child->getVisible() ) {
					child->setBounds( &clientBounds );
				}
			}
		}
	}

protected:
	std::deque<Control*> pages_;
};





/*
class HorizontalLayoutContainer : public StandardContainer {
public:

	HorizontalLayoutContainer() {

		setBorderWidth( UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stContainerBorderDelta) );

		setNumberOfColumns(2);

		setColumnWidth( 0, 100 );

		setColumnWidth( 1, 100 );

		setColumnTweenWidth( 0, UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlHorizontalSpacing) );


		setMaxRowHeight( UIToolkit::getUIMetricsManager()->getDefaultHeightFor( UIMetricsManager::htLabelHeight ) );

		setRowSpacerHeight( UIToolkit::getUIMetricsManager()->getPreferredSpacingFor(UIMetricsManager::stControlVerticalSpacing) );
	}

	void setNumberOfColumns( int numColumns ) {
		columns_.clear();
		columnTweens_.clear();

		columns_.resize( numColumns, 0.0 );

		columnTweens_.resize( numColumns-1, 0.0 );
	}

	void setColumnWidth( int index, double width ) {
		columns_[index] = width;
	}

	void setColumnTweenWidth( int index, double width ) {
		columnTweens_[index] = width;
	}

	void setMaxRowHeight( double val ) {
		maxRowHeight_ = val;
	}



	virtual void resizeChildren( Control* control ) {
		VCF::Rect clientBounds = controlContainer_->getClientBounds();

		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		clientBounds.setRect( clientBounds.left_ + leftBorderWidth_,
			clientBounds.top_ + topBorderHeight_,
			clientBounds.right_ - rightBorderWidth_,
			clientBounds.bottom_ - bottomBorderHeight_ );


		std::vector<Control*>::iterator it = controls_.begin();

		int colCount = columns_.size();
		int tweenCount = columnTweens_.size();

		int col = 0;
		int tween = 0;
		VCF::Rect cell = clientBounds;
		cell.right_ = cell.left_ + columns_[col];

		cell.bottom_ = cell.top_ + maxRowHeight_;

		while ( it != controls_.end() ) {

			Control* control = *it;


			if ( col == (colCount-1) ) {
				cell.right_ = clientBounds.right_;
			}


			control->setBounds( &cell );


			col ++;



			if ( col >= colCount ) {
				col = 0;
				tween = 0;

				cell.offset( 0, maxRowHeight_ + rowSpacerHeight_ );

				cell.left_ = clientBounds.left_;

				cell.right_ = cell.left_ + columns_[col];

			}
			else {
				cell.offset( cell.getWidth() + columnTweens_[tween], 0 );
				tween ++;
			}


			it ++;
		}
	}


	void setRowSpacerHeight( double val ) {
		rowSpacerHeight_ = val;
	}

	std::vector<double> columns_;
	std::vector<double> columnTweens_;

	double maxRowHeight_;
	double rowSpacerHeight_;
};
*/


class MediaInfoPanel : public Panel {
public:
	MediaInfoPanel() {
		setHeight( 200 );

		HorizontalLayoutContainer* container = new HorizontalLayoutContainer();
		container->setNumberOfColumns( 2 );
		container->setColumnWidth( 0, 75 );
		container->setRowSpacerHeight( 0 );

		Font font;
		font.setName( "Tahoma" );
		font.setPointSize( 10 );
		container->setMaxRowHeight( font.getHeight() * 1.25 );

		setContainer( container );
	}

	void setMovie( QuickTimeMovie* movie ) {
		Container* container = getContainer();
		while ( container->getChildCount() > 0 ) {
			Control* child = container->getControlAtIndex( 0 );

			container->remove(child);
			removeComponent( child );
			child->free();
		}

		if ( NULL != movie ) {
			std::vector<QuickTimeMovie::MovieMetaInfo> infoList;
			movie->getMovieMetaInfo( infoList );

			std::vector<QuickTimeMovie::MovieMetaInfo>::iterator it = infoList.begin();
			while ( it != infoList.end() ) {
				QuickTimeMovie::MovieMetaInfo& info = *it;

				Label* l = new Label();
				l->getFont()->setName( "Tahoma" );
				l->getFont()->setPointSize( 10 );
				l->getFont()->setBold( true );
				l->setCaption( info.first );
				l->setToolTipText( info.first );
				container->add( l );

				l = new Label();
				l->getFont()->setName( "Tahoma" );
				l->getFont()->setPointSize( 10 );
				l->setCaption( info.second );
				l->setToolTipText( info.second );
				l->setUseLocaleStrings( false );
				container->add( l );

				it ++;
			}
		}

		container->resizeChildren(NULL);
		repaint();
	}
};




MainQTWindow::MainQTWindow():
	quicktimeControl_(NULL),
	movieLoaded_(false),
	playListDict_(NULL)
{
	REGISTER_CLASSINFO_EXTERNAL(PlayListDictionary);

	playListDict_ = new PlayListDictionary();

	FilePath fp;
	fp = Application::getRunningInstance()->getFileName();
	playlistFile_ = fp.getPathName(true) + "playlist.db";

	buildUI();

	loadPlaylist();
}

MainQTWindow::~MainQTWindow()
{
	savePlaylist();

	playListDict_->free();
}

void MainQTWindow::buildUI()
{
	//build main menu
	MenuBar* menuBar = new MenuBar();
	addComponent( menuBar );
	this->setMenuBar( menuBar );
	MenuItem* root = menuBar->getRootMenuItem();

	DefaultMenuItem* file = new DefaultMenuItem( "&File", root, menuBar );

	DefaultMenuItem* fileOpen = new DefaultMenuItem( "&Open...", file, menuBar );
	DefaultMenuItem* fileClose = new DefaultMenuItem( "&Close", file, menuBar );

	DefaultMenuItem* sep = new DefaultMenuItem( "", file, menuBar );
	sep->setSeparator( true );

	DefaultMenuItem* fileAddToPlaylist = new DefaultMenuItem( "&Add to Playlist...", file, menuBar );

	sep = new DefaultMenuItem( "", file, menuBar );
	sep->setSeparator( true );

	DefaultMenuItem* fileExit = new DefaultMenuItem( "E&xit", file, menuBar );


	DefaultMenuItem* movie = new DefaultMenuItem( "&Movie", root, menuBar );
	DefaultMenuItem* moviePlay = new DefaultMenuItem( "&Play", movie, menuBar );
	DefaultMenuItem* moviePause = new DefaultMenuItem( "&Pause", movie, menuBar );
	DefaultMenuItem* movieReset= new DefaultMenuItem( "&Reset", movie, menuBar );
	DefaultMenuItem* movieStop = new DefaultMenuItem( "&Stop", movie, menuBar );

	sep = new DefaultMenuItem( "", movie, menuBar );
	sep->setSeparator( true );

	DefaultMenuItem* movieCreatePlaylist = new DefaultMenuItem( "Create Playlist", movie, menuBar );
	DefaultMenuItem* movieAddToPlaylist = new DefaultMenuItem( "Add to Playlist", movie, menuBar );




	DefaultMenuItem* view = new DefaultMenuItem( "&View", root, menuBar );
	DefaultMenuItem* viewNormal = new DefaultMenuItem( "&Normal", view, menuBar );
	DefaultMenuItem* viewDouble = new DefaultMenuItem( "&200%", view, menuBar );
	DefaultMenuItem* viewHalf = new DefaultMenuItem( "&50%", view, menuBar );





	sep = new DefaultMenuItem( "", view, menuBar );
	sep->setSeparator( true );
	DefaultMenuItem* viewResizable = new DefaultMenuItem( "&Resizeable", view, menuBar );
	DefaultMenuItem* viewLockAspectRatio = new DefaultMenuItem( "&Lock Aspect Ratio", view, menuBar );

	sep = new DefaultMenuItem( "", view, menuBar );
	sep->setSeparator( true );

	DefaultMenuItem* viewSideBar = new DefaultMenuItem( "&Playlist", view, menuBar );

	DefaultMenuItem* viewMediaInfo = new DefaultMenuItem( "&Media Info", view, menuBar );
	DefaultMenuItem* viewSearch = new DefaultMenuItem( "&Search", view, menuBar );
	DefaultMenuItem* viewPlayControls = new DefaultMenuItem( "&Play Controls", view, menuBar );
	DefaultMenuItem* viewPlaylist = new DefaultMenuItem( "&Playlist", view, menuBar );



	//add Help menu
	DefaultMenuItem* help = new DefaultMenuItem( "&Help", root, menuBar );
	DefaultMenuItem* helpAbout = new DefaultMenuItem( "About...", help, menuBar );

	EventHandler* ev = new GenericEventHandler<MainQTWindow>( this, &MainQTWindow::onHelpAbout, "MainQTWindow::onHelpAbout" );
	helpAbout->MenuItemClicked += ev;




	EventHandler* windowClose = new WindowEventHandler<MainQTWindow>( this, MainQTWindow::onClose, "MainQTWindow::onClose" );
	FrameClose += windowClose;




	ImageList* il = new ImageList();
	il->setImageHeight( 16 );
	il->setImageWidth( 16 );
	il->setTransparentColor( &Color( 0.0, 1.0, 0.0) );
	addComponent( il );

	GraphicsResourceBundle* resBundle = Application::getRunningInstance()->getResourceBundle();
	Image* img = resBundle->getImage( "open" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "reset" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "play" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "pause" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "stop" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "viewnormal" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "view200" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "view50" );
	il->addImage( img );
	delete img;





	mediaBar_ = new Panel();
	mediaBar_->setBorder( NULL );
	mediaBar_->setHeight( 45 );
	add( mediaBar_, AlignTop );



	playPanel_ = new Panel() ;
	playPanel_->setWidth( 200 );
	playPanel_->setBorder( NULL );

	mediaBar_->add( playPanel_, AlignLeft );






	Toolbar* toolbar = new Toolbar();
	toolbar->setName( "Toolbar1" );
	toolbar->setEnableAutoResize( false );

	toolbar->setWidth( il->getImageWidth() * 5 );
	toolbar->setHeight( il->getImageHeight() * 1.5 );
	toolbar->setImageList( il );


	playPanel_->add( toolbar, AlignTop );



	ImageControl* mute = new ImageControl();
	img = resBundle->getImage( "mute" );
	img->setTransparencyColor( &Color(0.0,1.0,0.0) );
	mute->setImage( img );
	mute->setTransparent( true );
	mute->setWidth( 11 );
	playPanel_->add( mute, AlignLeft );

	mute->MouseClicked +=
		new GenericEventHandler<MainQTWindow>( this, &MainQTWindow::onVolumeMute, "MainQTWindow::onVolumeMute" ) ;


	volumeControl_ = new VCF::SliderControl();
	volumeControl_->setTickMarkStyle( SliderControl::tmsBottomRight );
	//volumeControl_->setHasTickMarks( false );
	volumeControl_->setMinValue( 0.0 );
	volumeControl_->setMaxValue( 100.0 );
	volumeControl_->setWidth( 100 );
	volumeControl_->setPosition( 100 );
	volumeControl_->PositionChanged +=
		new GenericEventHandler<MainQTWindow>( this, &MainQTWindow::onVolumeChanged, "MainQTWindow::onVolumeChanged" ) ;




	playPanel_->add( volumeControl_, AlignClient );

	ImageControl* fullVol = new ImageControl();
	img = resBundle->getImage( "fullvol" );
	img->setTransparencyColor( &Color(0.0,1.0,0.0) );
	fullVol->setImage( img );
	fullVol->setTransparent( true );
	fullVol->setWidth( 11 );
	playPanel_->add( fullVol, AlignRight );

	fullVol->MouseClicked +=
		new GenericEventHandler<MainQTWindow>( this, &MainQTWindow::onVolumeFull, "MainQTWindow::onVolumeFull" ) ;




	Label* spacer = new Label();
	spacer->setWidth( 40 );
	spacer->setCaption( "" );
	mediaBar_->add( spacer, AlignLeft );




	Panel* currentMediaPanel = new Panel() ;
	currentMediaPanel->setBorder( NULL );
	mediaBar_->add( currentMediaPanel, AlignClient );

	QuickTimeScrubber* scrubber = new QuickTimeScrubber();
	scrubber->setHeight( scrubber->getPreferredHeight() );
	currentMediaPanel->add( scrubber, AlignBottom );


	mediaLabel_ = new Label();

	mediaLabel_->setWordWrap( true );
	mediaLabel_->setTextAlignment( taTextCenter );
	mediaLabel_->setVerticalAlignment( tvaTextCenter );
	mediaLabel_->setCaption( Application::getRunningInstance()->getName() + "\nNothing playing");
	mediaLabel_->setColor( &Color((unsigned char)214,(unsigned char)219,(unsigned char)191) );
	mediaLabel_->setTransparent( false );
	mediaLabel_->setUseColorForBackground( true );
	mediaLabel_->getFont()->setName( "Tahoma" );


	Light3DBorder* bdr = new Light3DBorder();
	bdr->setInverted( true );
	mediaLabel_->setBorder( bdr );
	currentMediaPanel->add( mediaLabel_, AlignClient );

	mediaLabel_->getFont()->setPixelSize( mediaLabel_->getHeight() * 0.45 );







	spacer = new Label();
	spacer->setWidth( 40 );
	spacer->setCaption( "" );
	mediaBar_->add( spacer, AlignRight );



	searchPanel_ = new Panel();

	searchPanel_->setBorder( NULL );
	searchPanel_->setWidth( 200 );
	mediaBar_->add( searchPanel_, AlignRight );



	ImageControl* searchIcon = new ImageControl();
	img = resBundle->getImage( "search" );
	img->setTransparencyColor( &Color(0.0,1.0,0.0) );
	searchIcon->setImage( img );
	searchIcon->setTransparent( true );

	searchIcon->MouseClicked += new GenericEventHandler<MainQTWindow>( this,	&MainQTWindow::onSearchIconClick, "MainQTWindow::onSearchIconClick" );

	searchIcon->setBounds( 1, 1, 17, 17 );

	searchPanel_->add( searchIcon );

	PopupMenu* pm = new PopupMenu();
	this->addComponent( pm );
	MenuItem* pmRoot = pm->getRootMenuItem();

	DefaultMenuItem* pmItem = new DefaultMenuItem( "Edit/Create a search Catalog...", pmRoot,pm );

	pmItem->MenuItemClicked += new GenericEventHandler<MainQTWindow>(this,&MainQTWindow::onEditCreateSearchCatalog, "MainQTWindow::onEditCreateSearchCatalog" );

	searchIcon->setPopupMenu( pm );


	TextControl* searchText = new TextControl();
	searchText->setBounds( searchIcon->getRight() + 1, 1, 100, searchIcon->getPreferredHeight() );
	searchPanel_->add( searchText );

	searchText->KeyUp += new KeyboardEventHandler<MainQTWindow>( this, &MainQTWindow::onSearchTextEntered, "MainQTWindow::onSearchTextEntered" );




	ToolbarItem* open = toolbar->addToolBarButton( "Open" );
	open->setTooltip( "Open" );
	open->setImageIndex( 0 );

	toolbar->addToolBarButton("")->setAsSeparator();

	ToolbarItem* reset = toolbar->addToolBarButton( "Reset" );
	reset->setTooltip( "Reset" );
	reset->setImageIndex( 1 );
	ToolbarItem* play = toolbar->addToolBarButton( "Play" );
	play->setTooltip( "Play" );
	play->setImageIndex( 2 );
	play->setGrouped(true);
	play->setChecked( true );
	ToolbarItem* pause = toolbar->addToolBarButton( "Pause" );
	pause->setImageIndex( 3 );
	pause->setTooltip( "Pause" );
	pause->setGrouped(true);
	pause->setChecked( true );
	ToolbarItem* stop = toolbar->addToolBarButton( "Stop" );
	stop->setImageIndex( 4 );
	stop->setTooltip( "Stop" );
	stop->setGrouped(true);
	stop->setChecked( true );




	/**
	Actions - this is where the various UI elements get hooked up
	*/


	Action* openAction = new Action();
	addComponent( openAction );
	openAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onFileOpenMovie, "MainQTWindow::onFileOpenMovie" );

	openAction->addTarget( open );
	openAction->addTarget( fileOpen );


	Action* fileAddToPlaylistAction = new Action();
	addComponent( fileAddToPlaylistAction );
	fileAddToPlaylistAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onAddToFilesPlaylist, "MainQTWindow::onAddToFilesPlaylist" );
	fileAddToPlaylistAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateAddToFilesPlaylist, "MainQTWindow::updateAddToFilesPlaylist" );

	fileAddToPlaylistAction->addTarget( fileAddToPlaylist );




	Action* fileCloseAction = new Action(this);
	fileCloseAction->Performed +=
		new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onFileCloseMovie, "MainQTWindow::onFileCloseMovie" );
	fileCloseAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateFileCloseMovie, "MainQTWindow::updateFileCloseMovie" );

	fileCloseAction->addTarget( fileClose );


	Action* resetAction = new Action();
	addComponent( resetAction );
	resetAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onMovieReset, "MainQTWindow::onMovieReset" );
	resetAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateReset, "MainQTWindow::updateReset" );

	resetAction->addTarget( reset );
	resetAction->addTarget( movieReset );

	Action* playAction = new Action();
	addComponent( playAction );
	playAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onMoviePlay, "MainQTWindow::onMoviePlay" );
	playAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updatePlay, "MainQTWindow::updatePlay" );


	playAction->addTarget( play );
	playAction->addTarget( moviePlay );


	Action* pauseAction = new Action();
	addComponent( pauseAction );
	pauseAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onMoviePause, "MainQTWindow::onMoviePause" );
	pauseAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updatePause, "MainQTWindow::updatePause" );

	pauseAction->addTarget( pause );
	pauseAction->addTarget( moviePause );


	Action* stopAction = new Action();
	addComponent( stopAction );
	stopAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onMovieStop, "MainQTWindow::onMovieStop" );
	stopAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateStop, "MainQTWindow::updateStop" );


	stopAction->addTarget( stop );
	stopAction->addTarget( movieStop );


	Action* createPlaylistAction = new Action(this);
	createPlaylistAction->Performed +=
		new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onCreatePlaylist, "MainQTWindow::onCreatePlaylist" );
	createPlaylistAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateCreatePlaylist, "MainQTWindow::updateCreatePlaylist" );


	createPlaylistAction->addTarget( movieCreatePlaylist );


	Action* addToPlaylistAction = new Action(this);
	addToPlaylistAction->Performed +=
		new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onAddToPlaylist, "MainQTWindow::onAddToPlaylist" );
	addToPlaylistAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateAddToPlaylist, "MainQTWindow::updateAddToPlaylist" );


	addToPlaylistAction->addTarget( movieAddToPlaylist );





	Action* exitAction = new Action();
	addComponent( exitAction );
	exitAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onFileExit, "MainQTWindow::onFileExit" );

	exitAction->addTarget( fileExit );


	Action* viewNormalAction = new Action();
	addComponent( viewNormalAction );
	viewNormalAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewNormal, "MainQTWindow::onViewNormal" );
	viewNormalAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewNormal, "MainQTWindow::updateViewNormal" );


	viewNormalAction->addTarget( viewNormal );



	Action* viewDoubleAction = new Action();
	addComponent( viewDoubleAction );
	viewDoubleAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewDouble, "MainQTWindow::onViewDouble" );
	viewDoubleAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewDouble, "MainQTWindow::updateViewDouble" );

	viewDoubleAction->addTarget( viewDouble );



	Action* viewHalfAction = new Action();
	addComponent( viewHalfAction );
	viewHalfAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewHalf, "MainQTWindow::onViewHalf" );
	viewHalfAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewHalf, "MainQTWindow::updateViewHalf" );

	viewHalfAction->addTarget( viewHalf );



	Action* viewLockAspectRatioAction = new Action();
	addComponent( viewLockAspectRatioAction );
	viewLockAspectRatioAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewLockAspectRatio, "MainQTWindow::onViewLockAspectRatio" );
	viewLockAspectRatioAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewLock, "MainQTWindow::updateViewLock" );

	viewLockAspectRatioAction->addTarget( viewLockAspectRatio );



	Action* viewAllowResizeAction = new Action();
	addComponent( viewAllowResizeAction );
	viewAllowResizeAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewAllowResize, "MainQTWindow::onViewAllowResize" );
	viewAllowResizeAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewAllowResize, "MainQTWindow::updateViewAllowResize" );

	viewAllowResizeAction->addTarget( viewResizable );



	Action* viewSideBarAction = new Action();
	addComponent( viewSideBarAction );
	viewSideBarAction->Performed +=
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewSideBar, "MainQTWindow::onViewSideBar" );
	viewSideBarAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewSideBar, "MainQTWindow::updateViewSideBar" );

	viewSideBarAction->addTarget( viewSideBar );

	Action* viewMediaInfoAction = new Action(this);
	viewMediaInfoAction->Performed +=
		new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewMediaInfo, "MainQTWindow::onViewMediaInfo" );
	viewMediaInfoAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewMediaInfo, "MainQTWindow::updateViewMediaInfo" );

	viewMediaInfoAction->addTarget( viewMediaInfo );



	Action* viewSearchAction = new Action(this);
	viewSearchAction->Performed +=
		new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewSearch, "MainQTWindow::onViewSearch" );
	viewSearchAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewSearch, "MainQTWindow::updateViewSearch" );

	viewSearchAction->addTarget( viewSearch );

	Action* viewPlayControlsAction = new Action(this);
	viewPlayControlsAction->Performed +=
		new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewPlayControls, "MainQTWindow::onViewPlayControls" );
	viewPlayControlsAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewPlayControls, "MainQTWindow::updateViewPlayControls" );

	viewPlayControlsAction->addTarget( viewPlayControls );

	Action* viewPlaylistAction = new Action(this);
	viewPlaylistAction->Performed +=
		new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewPlaylist, "MainQTWindow::onViewPlaylist" );
	viewPlaylistAction->Update +=
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewPlaylist, "MainQTWindow::updateViewPlaylist" );

	viewPlaylistAction->addTarget( viewPlaylist );




	mainViewPanel_ = new Panel();
	mainViewPanel_->setBorder( NULL );

	mainViewPanel_->setContainer( new PagedContainer() );
	add( mainViewPanel_, AlignClient );


	quicktimeControl_ = new QuickTimeControl();
	Light3DBorder* border = new Light3DBorder();
	border->setInverted( true );
	quicktimeControl_->setBorder( border );
	EventHandler* movieChanged = getEventHandler( "MainQTWindow::onMovieChanged" );
	if ( NULL == movieChanged ) {
		movieChanged =
			new GenericEventHandler<MainQTWindow>( this, MainQTWindow::onMovieChanged, "MainQTWindow::onMovieChanged" );
	}

	quicktimeControl_->MovieChanged += movieChanged;

	mainViewPanel_->add( quicktimeControl_ );

	scrubber->setQuickTimeControl( quicktimeControl_ );





	playListCtrl_ = new ListViewControl();
	playListCtrl_->setIconStyle( isDetails );
	playListCtrl_->addHeaderColumn( "Song/Movie Name", 80 );
	playListCtrl_->addHeaderColumn( "Duration", 80 );
	playListCtrl_->addHeaderColumn( "Movie Size", 80 );
	playListCtrl_->addHeaderColumn( "Data Size", 80 );

	playListCtrl_->MouseDoubleClicked +=
		new GenericEventHandler<MainQTWindow>( this, &MainQTWindow::onPlaylistViewDblClick, "MainQTWindow::onPlaylistViewDblClick" );

	playListCtrl_->KeyUp +=
		new KeyboardEventHandler<MainQTWindow>( this, &MainQTWindow::onPlayListCtrlKeyPressed, "MainQTWindow::onPlayListCtrlKeyPressed" );


	ListModel* lm = playListCtrl_->getListModel();

	mainViewPanel_->add( playListCtrl_ );


	ImageList* playlistIL = new ImageList();
	playlistIL->setImageHeight( 32 );
	playlistIL->setImageWidth( 32 );
	playlistIL->setTransparentColor( &Color( 0.0, 1.0, 0.0) );
	addComponent( playlistIL );

	img = resBundle->getImage( "movies" );
	playlistIL->addImage( img );
	delete img;


	playListCtrl_->setSmallImageList( playlistIL );



	PagedContainer* container = (PagedContainer*)mainViewPanel_->getContainer();

	container->showPage( quicktimeControl_ );



	/**
	Add accellerators
	*/

	addAcceleratorKey( vkSpaceBar,
						kmCtrl,
						new KeyboardEventHandler<MainQTWindow>( this, &MainQTWindow::onKeyHandler, "MainQTWindow::onKeyHandler" ) );



	addAcceleratorKey( vkUpArrow, kmCtrl, getEventHandler( "MainQTWindow::onKeyHandler" ) );
	addAcceleratorKey( vkDownArrow, kmCtrl, getEventHandler( "MainQTWindow::onKeyHandler" ) );
	addAcceleratorKey( vkLeftArrow, kmCtrl, getEventHandler( "MainQTWindow::onKeyHandler" ) );
	addAcceleratorKey( vkRightArrow, kmCtrl, getEventHandler( "MainQTWindow::onKeyHandler" ) );


	openAction->setAcceleratorKey( vkLetterO, kmCtrl );
	stopAction->setAcceleratorKey( vkEscape, kmUndefined );
	fileCloseAction->setAcceleratorKey( vkLetterC, kmCtrl | kmShift );



	VCF::DropTarget* qtDropTarget = new VCF::DropTarget( quicktimeControl_ );
	qtDropTarget->setName( "qtDropTarget" );
	addComponent( qtDropTarget );

	qtDropTarget->DropTargetDraggingOver +=
			new VCF::DropEventHandler<MainQTWindow>( this, &MainQTWindow::onDraggingOver, "MainQTWindow::onDraggingOver" );

	qtDropTarget->DropTargetDropped +=
			new VCF::DropEventHandler<MainQTWindow>( this, &MainQTWindow::onFilesDropped, "MainQTWindow::onFilesDropped" );



	sideBar_ = new Panel();
	sideBar_->setWidth( 200 );
	sideBar_->setBorder( NULL );
	sideBar_->setBorderSize( 5 );
	add( sideBar_, AlignLeft );


	Splitter* splitter = new Splitter();
	add( splitter, AlignLeft );

	Label* playlistLabel = new Label();
	playlistLabel->setHeight( playlistLabel->getPreferredHeight() );

	playlistLabel->setCaption( L"Playlist" );
	sideBar_->add( playlistLabel, AlignTop );


	playListTree_ = new TreeControl();
	playListTree_->setVisible( true );
	playListTree_->setAllowLabelEditing( true );

	playListTree_->ItemSelected +=
		new GenericEventHandler<MainQTWindow>( this, &MainQTWindow::onPlaylistItemSelected,"MainQTWindow::onPlaylistItemSelected" );

	playListTree_->KeyUp +=
		new KeyboardEventHandler<MainQTWindow>( this, &MainQTWindow::onPlayListTreeKeyPressed, "MainQTWindow::onPlayListTreeKeyPressed" );

	sideBar_->add( playListTree_, AlignClient );


	VCF::DropTarget* playlistDropTarget = new VCF::DropTarget( playListTree_ );
	playlistDropTarget->setName( "playlistDropTarget" );
	addComponent( playlistDropTarget );

	playlistDropTarget->DropTargetDraggingOver +=
			new VCF::DropEventHandler<MainQTWindow>( this, &MainQTWindow::onPlaylistDraggingOver, "MainQTWindow::onPlaylistDraggingOver" );

	playlistDropTarget->DropTargetDropped +=
			new VCF::DropEventHandler<MainQTWindow>( this, &MainQTWindow::onPlaylistFilesDropped, "MainQTWindow::onPlaylistFilesDropped" );


	ImageList* playlistFolderIL = new ImageList();
	playlistFolderIL->setImageHeight( 32 );
	playlistFolderIL->setImageWidth( 32 );
	playlistFolderIL->setTransparentColor( &Color( 0.0, 1.0, 0.0) );
	addComponent( playlistFolderIL );

	img = resBundle->getImage( "movies-playlist" );
	playlistFolderIL->addImage( img );
	delete img;


	playListTree_->setImageList( playlistFolderIL );





	TreeModel* model = playListTree_->getTreeModel();



	TitledBorder* tb = new TitledBorder();
	tb->setCaption( "Media Info" );
	mediaInfo_ = new MediaInfoPanel();
	mediaInfo_->setBorder( tb );
	sideBar_->add( mediaInfo_, AlignBottom );
}



void MainQTWindow::onViewSideBar(  VCF::Event* event )
{
	sideBar_->setVisible( !sideBar_->getVisible() );
}

void MainQTWindow::updateViewSideBar( VCF::ActionEvent* e )
{
	e->setChecked( sideBar_->getVisible() );
}

void MainQTWindow::onDraggingOver( VCF::DropTargetEvent* e )
{
	DataObject* dataObj = e->getDataObject();
	if ( dataObj->isTypeSupported( FILE_DATA_TYPE ) ) {
		e->setActionType( daCopy );
	}
	else {
		e->setActionType( daNone );
	}
}

void MainQTWindow::onFilesDropped( VCF::DropTargetEvent* e )
{
	DataObject* dataObj = e->getDataObject();
	if ( dataObj->isTypeSupported( FILE_DATA_TYPE ) ) {
		//create a basic output stream to write the data to
		BasicOutputStream stream;

		//write the data in the data object to the stream
		if ( dataObj->saveToStream( FILE_DATA_TYPE, &stream ) ) {
			//create a string from the output streams data
			String fileNames;
			fileNames.append( (VCF::WideChar*)stream.getBuffer(), stream.getSize()/sizeof(VCF::WideChar) );

			//create a string tokenizer, with the delimeter set to '\n'
			StringTokenizer tok( fileNames, "\n");

			//enumerate through all the file names - open the first for now

			if ( tok.hasMoreElements() ) {
				movieLoaded_ = false;
				if ( !quicktimeControl_->open( tok.nextElement() ) ) {
					((MediaInfoPanel*)mediaInfo_)->setMovie( NULL );
				}
			}
		}
	}
}

void MainQTWindow::onFileOpenMovie( Event* e )
{
	movieLoaded_ = false;
	CommonFileOpenDialog openDlg( this );
	openDlg.addFilter( "Quicktime Movie", "*.mov" );
	openDlg.addFilter( "MPEG movies", "*.mpg;*.mpeg" );
	openDlg.addFilter( "AVI movies", "*.avi" );
	openDlg.addFilter( "Soundtracks", "*.mp3;*.wav;*.au;*.aac;*.mid" );
	openDlg.addFilter( "All Files", "*.*" );
	if ( true == openDlg.execute() ) {
		if ( !quicktimeControl_->open( openDlg.getFileName() ) ) {
			((MediaInfoPanel*)mediaInfo_)->setMovie( NULL );
		}
	}

}

void MainQTWindow::onFileExit( Event* e )
{
	close();
}

void MainQTWindow::onHelpAbout( Event* e )
{
	QTPlayerAbout aboutDlg;

	aboutDlg.showModal();

}


void MainQTWindow::onMoviePlay( VCF::Event* e )
{
	PagedContainer* container = (PagedContainer*)mainViewPanel_->getContainer();

	container->showPage( quicktimeControl_ );

	quicktimeControl_->getMovie()->play();
}

void MainQTWindow::onMovieReset( VCF::Event* e )
{
	quicktimeControl_->getMovie()->reset();
}

void MainQTWindow::onMovieStop( VCF::Event* e )
{
	quicktimeControl_->getMovie()->stop();
}

void MainQTWindow::onMoviePause( VCF::Event* e )
{
	quicktimeControl_->getMovie()->pause();
}

void MainQTWindow::onMovieChanged( Event* movieEvent )
{
	EventHandler* movieFrameChanged = getEventHandler( "MainQTWindow::onMovieFrameChanged" );
	if ( NULL == movieFrameChanged ) {
		movieFrameChanged =
			new GenericEventHandler<MainQTWindow>( this, MainQTWindow::onMovieFrameChanged, "MainQTWindow::onMovieFrameChanged" );
	}

	QuickTimeMovie* movie = quicktimeControl_->getMovie();
	if ( NULL != movie ) {
		movie->MovieFrameChanged += movieFrameChanged;
	}

	movieLoaded_ = true;

	short vol = (volumeControl_->getPosition()/100.0) * 255.0;

	((MediaInfoPanel*)mediaInfo_)->setMovie( movie );

	::SetMovieVolume( *movie, vol );

	setCaption( Application::getRunningInstance()->getName() + L" - " + movie->getTitle() );

	mediaLabel_->setCaption( movie->getTitle() + "\n00:00:00" );

	onMoviePlay( NULL );
}

void MainQTWindow::onMovieFrameChanged( Event* movieEvent )
{
	QuickTimeMovie* movie = (QuickTimeMovie*) movieEvent->getSource();

	static double prev = 0;

	TimeRecord time = movie->getCurrentTime();

	double scale = time.scale;
	double seconds = time.value.lo / scale;

	int i_seconds = seconds;
	int hours = i_seconds / 3600;
	i_seconds = i_seconds - (hours*3600);
	int minutes = i_seconds / 60;
	i_seconds = i_seconds - (minutes*60);

	short tmp = ::GetMovieVolume( *movie ) * 100;
	int volume = tmp / 255;

	String s = Format( "%02d:%02d:%02d" ) % hours % minutes % i_seconds ;

	mediaLabel_->setCaption( movie->getTitle() + "\n" + s );
}

void MainQTWindow::onClose( VCF::WindowEvent* event )
{
	QuickTimeMovie* movie = quicktimeControl_->getMovie();
	if ( NULL != movie ) {
		movie->stop();
		movie->close();
	}
}

void MainQTWindow::onViewNormal( VCF::Event* e )
{
	quicktimeControl_->setViewNormalSize();
}

void MainQTWindow::onViewDouble( VCF::Event* e )
{
	quicktimeControl_->setViewDoubleSize();
}

void MainQTWindow::onViewHalf( VCF::Event* e )
{
	quicktimeControl_->setViewHalfSize();
}

void MainQTWindow::onViewLockAspectRatio( VCF::Event* e )
{
	quicktimeControl_->setLockAspectRatio( !quicktimeControl_->getLockAspectRatio() );
}

void MainQTWindow::onViewAllowResize( VCF::Event* e )
{
	quicktimeControl_->setAllowsResizing( !quicktimeControl_->getAllowsResizing() );
}

void MainQTWindow::updatePlay( VCF::ActionEvent* e )
{
	e->setEnabled( movieLoaded_ );

	QuickTimeMovie* movie = quicktimeControl_->getMovie();

	if ( movie->isPlaying() ) {
		e->setChecked( true );
		e->setState( e->getState() | ToolbarItem::tisPressed );
	}
	else {
		e->setChecked( false );
		e->setState( e->getState() & ~ToolbarItem::tisPressed );
	}
}

void MainQTWindow::updateReset( VCF::ActionEvent* e )
{
	e->setEnabled( movieLoaded_ );

}

void MainQTWindow::updateStop( VCF::ActionEvent* e )
{
	e->setEnabled( movieLoaded_ );
	QuickTimeMovie* movie = quicktimeControl_->getMovie();

	if ( movie->isStopped() ) {
		e->setChecked( true );
		e->setState( e->getState() | ToolbarItem::tisPressed );
	}
	else {
		e->setChecked( false );
		e->setState( e->getState() & ~ToolbarItem::tisPressed );
	}
}

void MainQTWindow::updatePause( VCF::ActionEvent* e )
{
	e->setEnabled( movieLoaded_ );

	QuickTimeMovie* movie = quicktimeControl_->getMovie();

	if ( movie->isPaused() ) {
		e->setChecked( true );
		e->setState( e->getState() | ToolbarItem::tisPressed );
	}
	else {
		e->setChecked( false );
		e->setState( e->getState() & ~ToolbarItem::tisPressed );
	}
}

void MainQTWindow::updateViewNormal( VCF::ActionEvent* e )
{
	if ( quicktimeControl_->isNormalSize() ) {
		e->setChecked( true );
		e->setState( e->getState() | ToolbarItem::tisPressed );
	}
	else {
		e->setChecked( false );
		e->setState( e->getState() & ~ToolbarItem::tisPressed );
	}

	e->setEnabled( movieLoaded_ );
}

void MainQTWindow::updateViewDouble( VCF::ActionEvent* e )
{
	if ( quicktimeControl_->isDoubleSize() ) {
		e->setChecked( true );
		e->setState( e->getState() | ToolbarItem::tisPressed );
	}
	else {
		e->setChecked( false );
		e->setState( e->getState() & ~ToolbarItem::tisPressed );
	}

	e->setEnabled( movieLoaded_ );
}

void MainQTWindow::updateViewHalf( VCF::ActionEvent* e )
{
	if ( quicktimeControl_->isHalfSize() ) {
		e->setChecked( true );
		e->setState( e->getState() | ToolbarItem::tisPressed );
	}
	else {
		e->setChecked( false );
		e->setState( e->getState() & ~ToolbarItem::tisPressed );
	}
	e->setEnabled( movieLoaded_ );
}

void MainQTWindow::updateViewLock( VCF::ActionEvent* e )
{
	e->setEnabled( movieLoaded_ );
	e->setChecked( quicktimeControl_->getLockAspectRatio() );
}

void MainQTWindow::updateViewAllowResize( VCF::ActionEvent* e )
{
	e->setEnabled( movieLoaded_ );
	e->setChecked( quicktimeControl_->getAllowsResizing() );
}

void MainQTWindow::onVolumeChanged( VCF::Event* event )
{
	short vol = (volumeControl_->getPosition()/100.0) * 255.0;

	QuickTimeMovie& movie = *quicktimeControl_->getMovie();

	::SetMovieVolume( movie, vol );

	vol = ::GetMovieVolume( movie ) * 100;
}

void MainQTWindow::onVolumeMute( VCF::Event* event )
{
	volumeControl_->setPosition( 0 );
}

void MainQTWindow::onVolumeFull( VCF::Event* event )
{
	volumeControl_->setPosition( 25500 / 100 );
}

void MainQTWindow::onKeyHandler( VCF::KeyboardEvent* event )
{
	QuickTimeMovie& movie = *quicktimeControl_->getMovie();

	switch ( event->getVirtualCode() ) {
		case vkRightArrow : {
			if ( movie.isPlaying() ){
				onMoviePause( NULL );
			}

			movie.nextFrame();
		}
		break;

		case vkLeftArrow : {
			if ( movie.isPlaying() ){
				onMoviePause( NULL );
			}

			movie.previousFrame();
		}
		break;

		case vkUpArrow : {
			volumeControl_->setPosition( minVal<int>( 100, 10 + volumeControl_->getPosition() ) );
		}
		break;

		case vkDownArrow : {
			volumeControl_->setPosition( maxVal<int>( 0, volumeControl_->getPosition() - 10 ) );
		}
		break;

		case vkSpaceBar : {
			if ( movie.isPlaying() ){
				onMoviePause( NULL );
			}
			else {
				onMoviePlay( NULL );
			}
		}
		break;
	}
}

void MainQTWindow::onViewMediaInfo(  VCF::Event* event )
{
	mediaInfo_->setVisible( !mediaInfo_->getVisible() );
}

void MainQTWindow::updateViewMediaInfo( VCF::ActionEvent* e )
{
	e->setChecked( mediaInfo_->getVisible() );
	e->setEnabled( sideBar_->getVisible() );
}

void MainQTWindow::onFileCloseMovie( VCF::Event* e )
{
	onMovieStop(NULL);
	QuickTimeMovie& movie = *quicktimeControl_->getMovie();
	movie.close();

	mediaLabel_->setCaption( Application::getRunningInstance()->getName() + "\nNothing playing");

	quicktimeControl_->repaint();

	movieLoaded_ = false;

	((MediaInfoPanel*)mediaInfo_)->setMovie( NULL );
}

void MainQTWindow::updateFileCloseMovie( VCF::ActionEvent* e )
{
	QuickTimeMovie& movie = *quicktimeControl_->getMovie();

	e->setEnabled( movie.isOpen() );
}


void MainQTWindow::onViewSearch(  VCF::Event* event )
{
	searchPanel_->setVisible( !searchPanel_->getVisible() );
}

void MainQTWindow::updateViewSearch( VCF::ActionEvent* e )
{
	e->setChecked( searchPanel_->getVisible() );
}

void MainQTWindow::onViewPlayControls(  VCF::Event* event )
{
	playPanel_->setVisible( !playPanel_->getVisible() );
}

void MainQTWindow::updateViewPlayControls( VCF::ActionEvent* e )
{
	e->setChecked( playPanel_->getVisible() );
}

void MainQTWindow::onSearchIconClick( VCF::Event* e )
{
	MouseEvent* me = (MouseEvent*)e;
	if ( !me->hasLeftButton() ) {
		return;
	}


	Control* control = (Control*) e->getSource();
	PopupMenu* pm = control->getPopupMenu();

	VCF::Point pt = control->getBounds().getBottomLeft();
	pm->popup( &pt );
}

void MainQTWindow::onSearchTextEntered( VCF::KeyboardEvent* e )
{
	TextControl* textCtrl = (TextControl*)e->getSource();
	StringUtils::trace( "Searching for \"" + textCtrl->getTextModel()->getText() + "\"...\n" );
}

void MainQTWindow::onPlaylistItemSelected( VCF::Event* e )
{
	PagedContainer* container = (PagedContainer*)mainViewPanel_->getContainer();


	PlayListTreeItem* selectedItem = (PlayListTreeItem*)playListTree_->getSelectedItem();



	if ( NULL != selectedItem ) {
		ListModel* lm = playListCtrl_->getListModel();
		playListCtrl_->getViewModel()->empty();

		PlayListDictionary* list = playListDict_->get( selectedItem->getID() );
		VCF_ASSERT( NULL != list );

		String name = (*list)[ L"PlayListName" ];

		VCF_ASSERT( name == selectedItem->getCaption() );


		Dictionary::Enumerator* items = list->getEnumerator();
		while ( items->hasMoreElements() ) {
			Dictionary::pair item = items->nextElement();

			if ( pdObject == item.second.type ) {
				Dictionary& itemAsDict = *((PlayListDictionary*)(Object*)item.second);



				PlayListItem* newItem = new PlayListItem( playListCtrl_, itemAsDict[L"Title"], NULL );
				newItem->setID(item.first);

				newItem->setData( (void*)list );
				lm->addItem( newItem );

				String itemMetaInfo = itemAsDict[L"Duration"];

				if ( !itemMetaInfo.empty() ) {
					newItem->addSubItem( itemMetaInfo, NULL );
				}

				itemMetaInfo = (String)itemAsDict[L"Size"];

				if ( !itemMetaInfo.empty() ) {
					newItem->addSubItem( itemMetaInfo, NULL );
				}

				itemMetaInfo = (String)itemAsDict[L"Data Size"];

				if ( !itemMetaInfo.empty() ) {
					newItem->addSubItem( itemMetaInfo, NULL );
				}
			}
		}
	}



	container->showPage( playListCtrl_ );
}

void MainQTWindow::onPlaylistItemChanged( VCF::ItemEvent* event )
{
	PlayListTreeItem* item = (PlayListTreeItem*)event->getSource();

	//String oldName = itemMap_[item];
	PlayListDictionary* dict = playListDict_->get( item->getID() );
	if ( NULL != dict ) {

		(*dict)[L"PlayListName"] = item->getCaption();
	}

}

void MainQTWindow::onCreatePlaylist(  VCF::Event* event )
{
	TreeModel* tm = playListTree_->getTreeModel();

	PlayListTreeItem* newItem = new PlayListTreeItem( "New playlist" );

	tm->addNodeItem( newItem );
	newItem->setID( StringUtils::newUUID() );

	EventHandler* ev = this->getEventHandler( "MainQTWindow::onPlaylistItemChanged" );
	if ( NULL == ev ) {
		ev = new ItemEventHandler<MainQTWindow>( this, MainQTWindow::onPlaylistItemChanged, "MainQTWindow::onPlaylistItemChanged" );
	}
	newItem->addItemChangedHandler( ev );

	PlayListDictionary& dict = *playListDict_->addPlayList( newItem->getID() );
	dict[L"PlayListName"] = newItem->getCaption();
}

void MainQTWindow::updateCreatePlaylist( VCF::ActionEvent* e )
{

}

void MainQTWindow::onViewPlaylist(  VCF::Event* event )
{
	PagedContainer* container = (PagedContainer*)mainViewPanel_->getContainer();


	if ( playListCtrl_->getVisible() ) {
		container->showPage( quicktimeControl_ );
	}
	else {
		container->showPage( playListCtrl_ );
	}
}

void MainQTWindow::updateViewPlaylist( VCF::ActionEvent* e )
{
	e->setChecked( playListCtrl_->getVisible() );
}

void MainQTWindow::onAddToPlaylist(  VCF::Event* event )
{
	addFileNameToPlaylist( quicktimeControl_->getMovie()->getFileName() );
}

void MainQTWindow::updateAddToPlaylist( VCF::ActionEvent* e )
{
	Enumerator<TreeItem*>* items = playListTree_->getTreeModel()->getRootItems();
	e->setEnabled( items->hasMoreElements() && quicktimeControl_->getMovie()->isOpen() );
}

void MainQTWindow::onPlaylistDraggingOver( VCF::DropTargetEvent* e )
{
	DataObject* dataObj = e->getDataObject();
	if ( dataObj->isTypeSupported( FILE_DATA_TYPE ) ) {
		e->setActionType( daCopy );
	}
	else {
		e->setActionType( daNone );
	}
}

void MainQTWindow::onPlaylistFilesDropped( VCF::DropTargetEvent* e )
{
	DataObject* dataObj = e->getDataObject();
	if ( dataObj->isTypeSupported( FILE_DATA_TYPE ) ) {
		//create a basic output stream to write the data to
		BasicOutputStream stream;

		//write the data in the data object to the stream
		if ( dataObj->saveToStream( FILE_DATA_TYPE, &stream ) ) {
			//create a string from the output streams data
			String fileNames;
			fileNames.append( (VCF::WideChar*)stream.getBuffer(), stream.getSize()/sizeof(VCF::WideChar) );

			//create a string tokenizer, with the delimeter set to '\n'
			StringTokenizer tok( fileNames, "\n");

			//enumerate through all the file names - open the first for now

			while ( tok.hasMoreElements() ) {
				String fileName = tok.nextElement();

				addFileNameToPlaylist( fileName );
			}
		}
	}
}

void MainQTWindow::onAddToFilesPlaylist(  VCF::Event* event )
{
	CommonFileOpenDialog openDlg( this );
	openDlg.setAllowsMultiSelect( true );
	openDlg.addFilter( "Quicktime Movie", "*.mov" );
	openDlg.addFilter( "MPEG movies", "*.mpg;*.mpeg" );
	openDlg.addFilter( "AVI movies", "*.avi" );
	openDlg.addFilter( "Soundtracks", "*.mp3;*.wav;*.au;*.aac;*.mid" );
	openDlg.addFilter( "All Files", "*.*" );
	if ( true == openDlg.execute() ) {
		Enumerator<String>* files = openDlg.getSelectedFiles();
		while ( files->hasMoreElements() ) {
			FilePath fp;
			fp = openDlg.getDirectory();
			if ( !fp.isDirectoryName () ) {
				fp = fp.getFileName() + FilePath::getDirectorySeparator();
			}
			fp = fp.getFileName() + files->nextElement();

			addFileNameToPlaylist( fp );
		}
	}
}

void MainQTWindow::updateAddToFilesPlaylist( VCF::ActionEvent* e )
{
	Enumerator<TreeItem*>* items = playListTree_->getTreeModel()->getRootItems();
	e->setEnabled( items->hasMoreElements() );
}

void MainQTWindow::addFileNameToPlaylist( const VCF::String& fileName )
{
	PlayListTreeItem* selectedItem = (PlayListTreeItem*)playListTree_->getSelectedItem();
	if ( NULL == selectedItem ) {
		TreeItem* first = playListTree_->getTreeModel()->getRootItems()->nextElement();
		first->setSelected( true );
		selectedItem = (PlayListTreeItem*)first;
	}


	if ( NULL != selectedItem ) {
		PlayListDictionary* list = playListDict_->get( selectedItem->getID() );
		VCF_ASSERT( NULL != list );

		VCF_ASSERT( !fileName.empty() );

		QuickTimeMovie mov;
		mov.open( fileName );

		String title = mov.getTitle();
		VCF_ASSERT( !title.empty() );


		String id = StringUtils::newUUID();
		Dictionary& dict = *list->addPlayList(id);


		dict[L"Filename"] = fileName;
		dict[L"Title"] = title;

		std::vector<QuickTimeMovie::MovieMetaInfo> infoList;
		mov.getMovieMetaInfo( infoList );

		std::vector<QuickTimeMovie::MovieMetaInfo>::iterator it = infoList.begin();
		while ( it != infoList.end() ) {
			QuickTimeMovie::MovieMetaInfo& info = *it;

			dict[ info.first ] = info.second;

			it ++;
		}

	}
}

void MainQTWindow::loadPlaylist()
{
	if ( File::exists(playlistFile_) ) {
		FileInputStream fis( playlistFile_ );
		fis >> playListDict_;

		Dictionary::Enumerator* items = playListDict_->getEnumerator();
		while ( items->hasMoreElements() ) {
			Dictionary::pair item = items->nextElement();
			if ( pdObject == item.second.type ) {

				Dictionary& dict = *((PlayListDictionary*)(Object*)item.second);

				PlayListTreeItem* newItem = new PlayListTreeItem( dict[L"PlayListName"] );

				playListTree_->getTreeModel()->addNodeItem( newItem, NULL );
				newItem->setID( item.first );


				EventHandler* ev = this->getEventHandler( "MainQTWindow::onPlaylistItemChanged" );
				if ( NULL == ev ) {
					ev = new ItemEventHandler<MainQTWindow>( this, MainQTWindow::onPlaylistItemChanged, "MainQTWindow::onPlaylistItemChanged" );
				}
				newItem->addItemChangedHandler( ev );
			}
		}
	}
}

void MainQTWindow::savePlaylist()
{
	FileOutputStream fos( playlistFile_ );
	fos << playListDict_;
}

void MainQTWindow::onPlaylistViewDblClick( VCF::Event* e )
{


	PlayListItem* item = (PlayListItem*)playListCtrl_->getSelectedItem();

	if ( NULL != item ) {
		PlayListDictionary* dict = (PlayListDictionary*)item->getData();

		PlayListDictionary* movieDict = (PlayListDictionary*)(Object*) (*dict)[ item->getID() ];

		String fileName = (*movieDict)[ L"Filename" ];

		VCF_ASSERT( !fileName.empty() );

		movieLoaded_ = false;
		if ( !quicktimeControl_->open( fileName ) ) {
			((MediaInfoPanel*)mediaInfo_)->setMovie( NULL );
		}
	}
}

void MainQTWindow::onPlayListCtrlKeyPressed( VCF::KeyboardEvent* e )
{
	if ( e->getVirtualCode() == vkDelete ) {
		ListItem* item = playListCtrl_->getSelectedItem();

		if ( NULL != item ) {

			PlayListTreeItem* selectedItem = (PlayListTreeItem*)playListTree_->getSelectedItem();

			if ( NULL != selectedItem ) {
				PlayListDictionary* list = playListDict_->get( selectedItem->getID() );
				VCF_ASSERT( NULL != list );

				PlayListItem* playListItem = (PlayListItem*)item;

				PlayListDictionary* movieInfoDict = list->get( playListItem->getID() );
				VCF_ASSERT( NULL != movieInfoDict );

				list->remove( playListItem->getID() );

				movieInfoDict->free();

			}


			playListCtrl_->getListModel()->deleteItem( item );
		}
	}
}

void MainQTWindow::onPlayListTreeKeyPressed( VCF::KeyboardEvent* e )
{
	if ( e->getVirtualCode() == vkDelete ) {
		PlayListTreeItem* selectedItem = (PlayListTreeItem*)playListTree_->getSelectedItem();

		if ( NULL != selectedItem ) {

			selectedItem->setSelected( false );

			PlayListDictionary* list = playListDict_->get( selectedItem->getID() );

			VCF_ASSERT( NULL != list );

			playListDict_->remove( selectedItem->getID() );
			list->free();

			playListTree_->getTreeModel()->deleteNodeItem( selectedItem );


			playListCtrl_->getViewModel()->empty();
		}

	}
}


class CreateCatalogThread : public Thread {
public:
	CreateCatalogThread( EventHandler* doneEventHandler, const String& catDirectory ):Thread(),
		doneEventHandler_(doneEventHandler),
		directoryToCatalog_(catDirectory){ }


	virtual bool run() {

		String catalog;

		Directory dir(directoryToCatalog_);
		Directory::Finder* finder =  dir.findFiles( "*.*" );
		if ( NULL != finder ) {
			finder->setRecursion( true );
			File* file = NULL;
			while ( finder->nextElement() ) {
				file = finder->getCurrentElement();

				catalog += file->getName() + "\n";

			}
			finder->free();

			StringUtils::trace( catalog );

			FilePath catFileName = Application::getRunningInstance()->getFileName();

			catFileName = catFileName.getPathName(true) + "SearchCatalog.db";

			File::OpenFlags flags = File::ofWrite;




			File catFile( catFileName );
			if ( File::exists( catFileName ) ) {
				flags = File::ofAppend;
				catFile.openWithRights( catFileName, flags );
			}
			else {
				catFile.create( catFileName, flags );
			}



			FileOutputStream& fs = *catFile.getOutputStream();

			fs<< catalog;

		}

		UIToolkit::postEvent( doneEventHandler_, new Event(this,0), false );

		return true;
	}


	String directoryToCatalog_;
	EventHandler* doneEventHandler_;
};

void MainQTWindow::onCreateSearchCatalogThreadDone(  VCF::Event* event )
{
	StringUtils::trace( "\n\nonCreateSearchCatalogThreadDone\n" );
	searchPanel_->setEnabled( true );
}

void MainQTWindow::onEditCreateSearchCatalog(  VCF::Event* event )
{
	CommonFileBrowseDialog browse;

	browse.setTitle( L"Select Directory to catalog" );

	if ( browse.execute() ) {

		EventHandler* ev = getEventHandler( "MainQTWindow::onCreateSearchCatalogThreadDone" );
		if ( NULL == ev ) {
			ev = new GenericEventHandler<MainQTWindow>( this, &MainQTWindow::onCreateSearchCatalogThreadDone, "MainQTWindow::onCreateSearchCatalogThreadDone" );
		}

		searchPanel_->setEnabled( false );
		CreateCatalogThread* thread = new CreateCatalogThread(ev,browse.getDirectory());
		thread->start();
	}

}



/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:34:39  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.5  2005/09/13 01:58:06  ddiego
*minor changes to dictionary class.
*
*Revision 1.5.2.4  2005/09/02 01:01:20  ddiego
*changed some of the common dialogs around, was using a less clear class name.
*
*Revision 1.5.2.3  2005/08/25 01:48:42  ddiego
*minor update to popupmenu code
*
*Revision 1.5.2.2  2005/08/01 20:02:23  marcelloptr
*rolled back a container's change
*
*Revision 1.5.2.1  2005/07/23 21:45:39  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.4.2.6  2005/07/22 00:24:39  marcelloptr
*fixed all deprecated traceWithArgs(...) and format(...) calls
*
*Revision 1.4.2.3  2005/06/25 22:47:20  marcelloptr
*[bugfix 1227549] HorizontalLayoutContainer set the heights in the wrong rows.
*AbstractContainer::add() needs to resizeChildren *after* the child control has been added.
*
*/


