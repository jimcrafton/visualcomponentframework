//MainWindow.h
#include "ApplicationKit.h"
#include "ControlsKit.h"
#include "MainWindow.h"
#include "QTPlayerApplication.h"
#include "QTPlayerAbout.h"
#include "QuickTimeControl.h"
#include "utils/StringTokenizer.h"

#include "StatusBarControl.h"



using namespace VCF;



MainQTWindow::MainQTWindow():
	m_quicktimeControl(NULL),
	movieLoaded_(false)
{

	setContainer( new FixedStandardContainer() );

	//build main menu
	MenuBar* menuBar = new MenuBar();
	addComponent( menuBar );
	this->setMenuBar( menuBar );
	MenuItem* root = menuBar->getRootMenuItem();
	
	DefaultMenuItem* file = new DefaultMenuItem( "&File", root, menuBar );

	DefaultMenuItem* fileOpen = new DefaultMenuItem( "&Open...", file, menuBar );

	DefaultMenuItem* sep = new DefaultMenuItem( "", file, menuBar );
	sep->setSeparator( true );
	
	DefaultMenuItem* fileExit = new DefaultMenuItem( "E&xit", file, menuBar );


	DefaultMenuItem* movie = new DefaultMenuItem( "&Movie", root, menuBar );	
	DefaultMenuItem* moviePlay = new DefaultMenuItem( "&Play...", movie, menuBar );
	DefaultMenuItem* moviePause = new DefaultMenuItem( "&Pause...", movie, menuBar );
	DefaultMenuItem* movieReset= new DefaultMenuItem( "&Reset...", movie, menuBar );
	DefaultMenuItem* movieStop = new DefaultMenuItem( "&Stop...", movie, menuBar );	


	DefaultMenuItem* view = new DefaultMenuItem( "&View", root, menuBar );
	DefaultMenuItem* viewNormal = new DefaultMenuItem( "&Normal", view, menuBar );
	DefaultMenuItem* viewDouble = new DefaultMenuItem( "&200%", view, menuBar );
	DefaultMenuItem* viewHalf = new DefaultMenuItem( "&50%", view, menuBar );	


	sep = new DefaultMenuItem( "", view, menuBar );
	sep->setSeparator( true );
	DefaultMenuItem* viewResizable = new DefaultMenuItem( "&Resizable", view, menuBar );
	DefaultMenuItem* viewLockAspectRatio = new DefaultMenuItem( "&Lock Aspect Ratio", view, menuBar );	

	//add Help menu
	DefaultMenuItem* help = new DefaultMenuItem( "&Help", root, menuBar );
	DefaultMenuItem* helpAbout = new DefaultMenuItem( "About...", help, menuBar );	

	EventHandler* ev = new GenericEventHandler<MainQTWindow>( this, &MainQTWindow::onHelpAbout, "MainQTWindow::onHelpAbout" );
	helpAbout->addMenuItemClickedHandler( ev );
	


	EventHandler* windowClose = new WindowEventHandler<MainQTWindow>( this, MainQTWindow::onClose, "MainQTWindow::onClose" );
	FrameClose += windowClose;


	
	
	Toolbar* toolbar = new Toolbar();
	toolbar->setName( "Toolbar1" );
	toolbar->setHeight( 25 );
	add( toolbar, AlignTop );
	
	ImageList* il = new ImageList();
	il->setImageHeight( 16 );
	il->setImageWidth( 16 );
	il->setTransparentColor( &Color( 0.0, 1.0, 0.0) );
	addComponent( il );
	
	toolbar->setImageList( il );


	ResourceBundle* resBundle = Application::getRunningInstance()->getResourceBundle();
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

	/*
	img = resBundle->getImage( "fullvol" );
	il->addImage( img );
	delete img;

	img = resBundle->getImage( "mute" );
	il->addImage( img );
	delete img;
*/


	ToolbarItem* open = toolbar->addToolBarButton( "Open" );
	open->setImageIndex( 0 );

	toolbar->addToolBarButton("")->setAsSeparator();

	ToolbarItem* reset = toolbar->addToolBarButton( "Reset" );
	reset->setImageIndex( 1 );
	ToolbarItem* play = toolbar->addToolBarButton( "Play" );
	play->setImageIndex( 2 );
	play->setGrouped(true);
	play->setChecked( true );
	ToolbarItem* pause = toolbar->addToolBarButton( "Pause" );
	pause->setImageIndex( 3 );
	pause->setGrouped(true);
	pause->setChecked( true );
	ToolbarItem* stop = toolbar->addToolBarButton( "Stop" );
	stop->setImageIndex( 4 );
	stop->setGrouped(true);
	stop->setChecked( true );

	toolbar->addToolBarButton( "" )->setAsSeparator();

	ToolbarItem* viewNormalBtn = toolbar->addToolBarButton( "View Normal(100%)" );
	viewNormalBtn->setImageIndex( 5 );
	viewNormalBtn->setGrouped(true);
	viewNormalBtn->setChecked( true );

	ToolbarItem* viewDoubleBtn = toolbar->addToolBarButton( "View Double(200%)" );
	viewDoubleBtn->setImageIndex( 6 );
	viewDoubleBtn->setGrouped(true);
	viewDoubleBtn->setChecked( true );

	ToolbarItem* viewHalfBtn = toolbar->addToolBarButton( "View Half(50%)" );
	viewHalfBtn->setImageIndex( 7 );
	viewHalfBtn->setGrouped(true);
	viewHalfBtn->setChecked( true );
	
	/**
	Actions - this is where the various UI elements get hooked up
	*/


	Action* openAction = new Action();
	addComponent( openAction );
	openAction->Performed += 
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onFileOpenMovie, "MainQTWindow::onFileOpenMovie" );

	openAction->addTarget( open );
	openAction->addTarget( fileOpen );
	

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
	viewNormalAction->addTarget( viewNormalBtn );
	


	Action* viewDoubleAction = new Action();
	addComponent( viewDoubleAction );
	viewDoubleAction->Performed += 
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewDouble, "MainQTWindow::onViewDouble" );
	viewDoubleAction->Update += 
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewDouble, "MainQTWindow::updateViewDouble" );
	
	viewDoubleAction->addTarget( viewDouble );
	viewDoubleAction->addTarget( viewDoubleBtn );



	Action* viewHalfAction = new Action();
	addComponent( viewHalfAction );
	viewHalfAction->Performed += 
			new GenericEventHandler<MainQTWindow>(this, &MainQTWindow::onViewHalf, "MainQTWindow::onViewHalf" );
	viewHalfAction->Update += 
		new EventHandlerInstance<MainQTWindow,ActionEvent>(this, &MainQTWindow::updateViewHalf, "MainQTWindow::updateViewHalf" );

	viewHalfAction->addTarget( viewHalf );
	viewHalfAction->addTarget( viewHalfBtn );



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

		
		







	m_quicktimeControl = new QuickTimeControl();
	Light3DBorder* border = new Light3DBorder();
	border->setInverted( true );
	m_quicktimeControl->setBorder( border );
	EventHandler* movieChanged = getEventHandler( "MainQTWindow::onMovieChanged" );
	if ( NULL == movieChanged ) {
		movieChanged = 
			new GenericEventHandler<MainQTWindow>( this, MainQTWindow::onMovieChanged, "MainQTWindow::onMovieChanged" );
	}		
	
	m_quicktimeControl->MovieChanged += movieChanged;
	
	add( m_quicktimeControl, AlignClient );


	Panel* bottom = new Panel();
	bottom->setBorder( NULL );
	bottom->setHeight( bottom->getPreferredHeight() );
	bottom->setBorderSize( 3 );
	add( bottom, AlignBottom );

	bottom->setContainer( new FixedStandardContainer() );

	
	ImageControl* mute = new ImageControl();
	img = resBundle->getImage( "mute" );
	img->setTransparencyColor( &Color(0.0,1.0,0.0) );
	mute->setImage( img );
	mute->setTransparent( true );
	mute->setWidth( 11 );
	bottom->add( mute, AlignLeft );

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

	bottom->add( volumeControl_, AlignLeft );

	ImageControl* fullVol = new ImageControl();
	img = resBundle->getImage( "fullvol" );
	img->setTransparencyColor( &Color(0.0,1.0,0.0) );
	fullVol->setImage( img );
	fullVol->setTransparent( true );
	fullVol->setWidth( 11 );
	bottom->add( fullVol, AlignLeft );

	fullVol->MouseClicked += 
		new GenericEventHandler<MainQTWindow>( this, &MainQTWindow::onVolumeFull, "MainQTWindow::onVolumeFull" ) ;	

	

	/**
	Add accellerators
	*/
	
	addAcceleratorKey( vkSpaceBar, 
						kmUndefined, 
						new KeyboardEventHandler<MainQTWindow>( this, &MainQTWindow::onKeyHandler, "MainQTWindow::onKeyHandler" ) );

						

	addAcceleratorKey( vkUpArrow, kmUndefined, getEventHandler( "MainQTWindow::onKeyHandler" ) );
	addAcceleratorKey( vkDownArrow, kmUndefined, getEventHandler( "MainQTWindow::onKeyHandler" ) );
	addAcceleratorKey( vkLeftArrow, kmUndefined, getEventHandler( "MainQTWindow::onKeyHandler" ) );
	addAcceleratorKey( vkRightArrow, kmUndefined, getEventHandler( "MainQTWindow::onKeyHandler" ) );


	addAcceleratorKey( vkLetterO, kmCtrl, getEventHandler( "MainQTWindow::onFileOpenMovie" ) );

	
	QuickTimeScrubber* scrubber = new QuickTimeScrubber();
	scrubber->setHeight( scrubber->getPreferredHeight() );
	bottom->add( scrubber, AlignClient );
	scrubber->setQuickTimeControl( m_quicktimeControl );
	

	m_statusBar = new StatusBarControl();
	m_statusBar->setHeight( m_statusBar->getPreferredHeight() );
	add( m_statusBar, AlignBottom );

	m_statusBar->addStatusPane( 100, "" );
	m_statusBar->setStatusText( -1, "No Movie" );


	VCF::DropTarget* qtDropTarget = new VCF::DropTarget( m_quicktimeControl );
	qtDropTarget->setName( "qtDropTarget" );
	addComponent( qtDropTarget );

	qtDropTarget->DropTargetDraggingOver += 
			new VCF::DropEventHandler<MainQTWindow>( this, &MainQTWindow::onDraggingOver, "MainQTWindow::onDraggingOver" );

	qtDropTarget->DropTargetDropped += 
			new VCF::DropEventHandler<MainQTWindow>( this, &MainQTWindow::onFilesDropped, "MainQTWindow::onFilesDropped" );



}

MainQTWindow::~MainQTWindow()
{
	
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
			fileNames.append( stream.getBuffer(), stream.getSize() );
			
			//create a string tokenizer, with the delimeter set to '\n'
			StringTokenizer tok( fileNames, "\n");

			//enumerate through all the file names - open the first for now
			
			if ( tok.hasMoreElements() ) {				
				
				if ( m_quicktimeControl->open( tok.nextElement() ) ) {	
					
					m_quicktimeControl->getMovie()->play();
				}
			}
		}
	}
}

void MainQTWindow::onFileOpenMovie( Event* e )
{
	
	CommonFileOpen openDlg( this );	
	openDlg.addFilter( "Quicktime Movie", "*.mov" );
	openDlg.addFilter( "MPEG movies", "*.mpg;*.mpeg" );
	openDlg.addFilter( "AVI movies", "*.avi" );
	openDlg.addFilter( "Soundtracks", "*.mp3;*.wav;*.au;*.aac;*.mid" );
	openDlg.addFilter( "All Files", "*.*" );
	if ( true == openDlg.execute() ) {
		if ( m_quicktimeControl->open( openDlg.getFileName() ) ) {	
			
			movieLoaded_ = true;

			short vol = (volumeControl_->getPosition()/100.0) * 255.0;
			
			QuickTimeMovie& movie = *m_quicktimeControl->getMovie();	

			::SetMovieVolume( movie, vol );
			
			m_statusBar->setStatusText( 0, "Movie Opened" );

			onMoviePlay( NULL );			
		}
		else {
			
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
	m_quicktimeControl->getMovie()->play();
	
	m_statusBar->setStatusText( 0, m_quicktimeControl->getMovie()->hasMovieTrack() ? "Movie Playing" : "Audio Playing" );
}

void MainQTWindow::onMovieReset( VCF::Event* e )
{
	m_quicktimeControl->getMovie()->reset();
	m_statusBar->setStatusText( 0, m_quicktimeControl->getMovie()->hasMovieTrack() ? "Movie Reset" : "Audio Reset" );
}

void MainQTWindow::onMovieStop( VCF::Event* e )
{
	m_quicktimeControl->getMovie()->stop();
	m_statusBar->setStatusText( 0, m_quicktimeControl->getMovie()->hasMovieTrack() ? "Movie Stopped" : "Audio Stopped" );
}

void MainQTWindow::onMoviePause( VCF::Event* e )
{
	m_quicktimeControl->getMovie()->pause();
	m_statusBar->setStatusText( 0, m_quicktimeControl->getMovie()->hasMovieTrack() ? "Movie Paused" : "Audio Paused" );
}

void MainQTWindow::onMovieChanged( Event* movieEvent )
{
	EventHandler* movieFrameChanged = getEventHandler( "MainQTWindow::onMovieFrameChanged" );
	if ( NULL == movieFrameChanged ) {
		movieFrameChanged = 
			new GenericEventHandler<MainQTWindow>( this, MainQTWindow::onMovieFrameChanged, "MainQTWindow::onMovieFrameChanged" );
	}
	
	QuickTimeMovie* movie = m_quicktimeControl->getMovie();
	if ( NULL != movie ) {
		movie->MovieFrameChanged += movieFrameChanged;
	}
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

	String s = StringUtils::format( "%02d:%02d:%02d Volume: %d %%", hours, minutes, i_seconds, volume );	
	m_statusBar->setStatusText( -1, s );	
}

void MainQTWindow::onClose( VCF::WindowEvent* event )
{
	QuickTimeMovie* movie = m_quicktimeControl->getMovie();
	if ( NULL != movie ) {
		movie->stop();
		movie->close();
	}
}

void MainQTWindow::onViewNormal( VCF::Event* e )
{
	StringUtils::traceWithArgs( "zoom: %0.2f\n", m_quicktimeControl->getZoomLevel() );
	
	m_quicktimeControl->setViewNormalSize();
}

void MainQTWindow::onViewDouble( VCF::Event* e )
{
	m_quicktimeControl->setViewDoubleSize();
}

void MainQTWindow::onViewHalf( VCF::Event* e )
{
	m_quicktimeControl->setViewHalfSize();
}

void MainQTWindow::onViewLockAspectRatio( VCF::Event* e )
{
	m_quicktimeControl->setLockAspectRatio( !m_quicktimeControl->getLockAspectRatio() );
}

void MainQTWindow::onViewAllowResize( VCF::Event* e )
{
	m_quicktimeControl->setAllowsResizing( !m_quicktimeControl->getAllowsResizing() );
}

void MainQTWindow::updatePlay( VCF::ActionEvent* e )
{
	e->setEnabled( movieLoaded_ );

	QuickTimeMovie* movie = m_quicktimeControl->getMovie();

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
	QuickTimeMovie* movie = m_quicktimeControl->getMovie();

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

	QuickTimeMovie* movie = m_quicktimeControl->getMovie();

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
	if ( m_quicktimeControl->isNormalSize() ) {
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
	if ( m_quicktimeControl->isDoubleSize() ) {
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
	if ( m_quicktimeControl->isHalfSize() ) {
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
	e->setChecked( m_quicktimeControl->getLockAspectRatio() );
}

void MainQTWindow::updateViewAllowResize( VCF::ActionEvent* e )
{
	e->setEnabled( movieLoaded_ );
	e->setChecked( m_quicktimeControl->getAllowsResizing() );
}

void MainQTWindow::onVolumeChanged( VCF::Event* event )
{
	short vol = (volumeControl_->getPosition()/100.0) * 255.0;

	QuickTimeMovie& movie = *m_quicktimeControl->getMovie();	

	::SetMovieVolume( movie, vol );

	vol = ::GetMovieVolume( movie ) * 100;

	String s = StringUtils::format( "Volume: %d %%", vol/255 );	
	m_statusBar->setStatusText( -1, s );
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
	QuickTimeMovie& movie = *m_quicktimeControl->getMovie();	

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




