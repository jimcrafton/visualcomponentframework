//QuickTimeControl.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "QuickTimeControl.h"
#include "QuickTimeMovie.h"



using namespace VCF;



QuickTimeControl::QuickTimeControl():
	m_currentMovie(NULL),
	m_zoomLevel(1.0),
	m_lockAspectRatio(true),
	m_allowResizing(false),
	viewState_(vsNormal)
{
	EventHandler* ev = 
			new GenericEventHandler<QuickTimeControl>( this, &QuickTimeControl::onTimer, "QuickTimeControl::onTimer" );
		
	TimerComponent* timer = new TimerComponent();
	addComponent( timer );

	timer->TimerPulse += ev;

	timer->setTimeoutInterval( 100 );
	timer->setActivated( true );

}	

QuickTimeControl::~QuickTimeControl()
{
	
}

void QuickTimeControl::beforeDestroy( VCF::ComponentEvent* event )
{
	m_currentMovie->release();
	CustomControl::beforeDestroy( event );
}

void QuickTimeControl::paint( VCF::GraphicsContext* ctx )
{
	CustomControl::paint( ctx );
	m_currentMovie->update();
}

void QuickTimeControl::afterCreate( VCF::ComponentEvent* event )
{
	CustomControl::afterCreate( event );	

	m_currentMovie = new QuickTimeMovie( this );
}

bool QuickTimeControl::open( const VCF::String filename )
{
	bool result = m_currentMovie->open( filename );

	if ( result ) {		
		
		setMovieBounds( &getBounds() );

		repaint();

		Event movieEvent( this );
		MovieChanged.fireEvent( &movieEvent );
	}
	return result;
}

void QuickTimeControl::setMovieBounds( VCF::Rect* rect )
{
	if ( (NULL != m_currentMovie) && ( m_currentMovie->isOpen() ) ) {
		VCF::Rect r = m_currentMovie->getBounds();
		
		if ( true == m_allowResizing ) {
			if ( true == m_lockAspectRatio ) {
				VCF::Rect originalBounds = m_currentMovie->getOriginalBounds();
				

				VCF::Rect clientRect(0, 0, rect->getWidth(), rect->getHeight() );

				VCF::Rect bounds;	

				double aspectRatio = m_currentMovie->getAspectRatio();


				if ( originalBounds.getWidth() > originalBounds.getHeight() ) {
					//horizontal orientation
					if ( r.getHeight() > clientRect.getHeight() ) {
						bounds.setRect( 0, 0, clientRect.getHeight()*aspectRatio, clientRect.getHeight() );
					}
					else {
						bounds.setRect( 0, 0, clientRect.getWidth(), clientRect.getWidth()/aspectRatio );
					}
				}
				else {
					//vertical orientation					

					if ( r.getWidth() > clientRect.getWidth() ) {
						bounds.setRect( 0, 0, clientRect.getWidth(), clientRect.getWidth()*aspectRatio );
					}
					else {
						bounds.setRect( 0, 0, clientRect.getHeight()/aspectRatio, clientRect.getHeight() );
					}
				}

				bounds.inflate( -5, -5 );
				

				double w = bounds.getWidth();
				double h = bounds.getHeight();

				bounds.left_ = clientRect.left_ + ((clientRect.getWidth()*0.5) - (bounds.getWidth()*0.5));
				bounds.top_ = clientRect.top_ + ((clientRect.getHeight()*0.5) - (bounds.getHeight()*0.5));

				bounds.right_ = bounds.left_ + w;
				bounds.bottom_ = bounds.top_ + h;

				

				m_currentMovie->setBounds( bounds );
			}
			else {
				VCF::Rect bounds = *rect;
				
				m_currentMovie->setBounds( bounds );
			}
		}
		else {

			VCF::Rect bounds(0, 0, rect->getWidth(), rect->getHeight() );
			
			bounds.inflate( -5, -5 );
			
			bounds.left_ = bounds.left_ + ((bounds.getWidth()*0.5) - (r.getWidth()*0.5));
			bounds.top_ = bounds.top_ + ((bounds.getHeight()*0.5) - (r.getHeight()*0.5));
			bounds.right_ = bounds.left_ + r.getWidth();
			bounds.bottom_ = bounds.top_ + r.getHeight();
			
			m_currentMovie->setBounds( bounds );
		}
		
	}
}


void QuickTimeControl::setViewDoubleSize()
{
	VCF::Rect r = getMovie()->getOriginalBounds();

	r.inflate( r.getWidth()/2.0, r.getHeight()/2.0 );

	VCF::Rect bounds = getClientBounds();
			
	bounds.inflate( -5, -5 );
			
	bounds.left_ = bounds.left_ + ((bounds.getWidth()*0.5) - (r.getWidth()*0.5));
	bounds.top_ = bounds.top_ + ((bounds.getHeight()*0.5) - (r.getHeight()*0.5));
	bounds.right_ = bounds.left_ + r.getWidth();
	bounds.bottom_ = bounds.top_ + r.getHeight();
			
	getMovie()->setBounds( bounds );	
	
	viewState_  = vsDouble;
	repaint();
}

void QuickTimeControl::setViewHalfSize()
{
	VCF::Rect r = getMovie()->getOriginalBounds();

	r.inflate( -r.getWidth()/4.0, -r.getHeight()/4.0 );	

	VCF::Rect bounds = getClientBounds();
			
	bounds.inflate( -5, -5 );
			
	bounds.left_ = bounds.left_ + ((bounds.getWidth()*0.5) - (r.getWidth()*0.5));
	bounds.top_ = bounds.top_ + ((bounds.getHeight()*0.5) - (r.getHeight()*0.5));
	bounds.right_ = bounds.left_ + r.getWidth();
	bounds.bottom_ = bounds.top_ + r.getHeight();
			
	getMovie()->setBounds( bounds );

	viewState_  = vsHalf;
	repaint();
}

void QuickTimeControl::setViewNormalSize()
{	
	VCF::Rect r = getMovie()->getOriginalBounds();

	VCF::Rect bounds = getClientBounds();
			
	bounds.inflate( -5, -5 );
			
	bounds.left_ = bounds.left_ + ((bounds.getWidth()*0.5) - (r.getWidth()*0.5));
	bounds.top_ = bounds.top_ + ((bounds.getHeight()*0.5) - (r.getHeight()*0.5));
	bounds.right_ = bounds.left_ + r.getWidth();
	bounds.bottom_ = bounds.top_ + r.getHeight();
			
	getMovie()->setBounds( bounds );

	viewState_  = vsNormal;
	
	repaint();
}

void QuickTimeControl::setBounds( VCF::Rect* rect, const bool& anchorDeltasNeedUpdating )
{
	CustomControl::setBounds( rect, anchorDeltasNeedUpdating );

	setMovieBounds( rect );	
}

void QuickTimeControl::handleEvent( VCF::Event* e )
{
	CustomControl::handleEvent( e );

	if ( (NULL != m_currentMovie) && ( m_currentMovie->isOpen() ) ) {
		//m_currentMovie->movieTask();
	}
}

void QuickTimeControl::setAllowsResizing( const bool& resizing )
{
	m_allowResizing = resizing;
}

void QuickTimeControl::setLockAspectRatio( const bool& lockAspectRatio )
{
	m_lockAspectRatio = lockAspectRatio;
}

void QuickTimeControl::setZoomLevel( const double& val )
{
	m_zoomLevel = val;
}

void QuickTimeControl::onTimer( VCF::Event* e )
{
	getMovie()->movieTask();
}






//QuickTimeScrubber

QuickTimeScrubber::QuickTimeScrubber():
	quickTimeControl_(NULL),
	maxRange_(1.0),
	minRange_(0.0),
	scrubbing_(false)
{
	memset( &currentPosition_, 0, sizeof(currentPosition_) );
}

QuickTimeScrubber::~QuickTimeScrubber()
{

}

void QuickTimeScrubber::onMovieChanged( Event* movieEvent )
{
	minRange_ = 0.0;
	maxRange_ = quickTimeControl_->getMovie()->getDuration();
	memset( &currentPosition_, 0, sizeof(currentPosition_) );
	
	EventHandler* movieFrameChanged = getEventHandler( "QuickTimeScrubber::onMovieFrameChanged" );
	if ( NULL == movieFrameChanged ) {
		movieFrameChanged = 
			new GenericEventHandler<QuickTimeScrubber>( this, QuickTimeScrubber::onMovieFrameChanged, "QuickTimeScrubber::onMovieFrameChanged" );
	}
	
	QuickTimeMovie* movie = quickTimeControl_->getMovie();
	if ( NULL != movie ) {
		movie->MovieFrameChanged += movieFrameChanged;
	}
	
	repaint();
}

void QuickTimeScrubber::onMovieFrameChanged( Event* movieEvent )
{
	QuickTimeMovie* movie = (QuickTimeMovie*) movieEvent->getSource();

	TimeRecord time = movie->getCurrentTime();
	currentPosition_ = time;

	repaint();
}

void QuickTimeScrubber::setQuickTimeControl( QuickTimeControl* control )
{		
	quickTimeControl_ = control;

	if ( NULL != quickTimeControl_ ) {
		EventHandler* movieChanged = getEventHandler( "QuickTimeScrubber::onMovieChanged" );
		if ( NULL == movieChanged ) {
			movieChanged = 
				new GenericEventHandler<QuickTimeScrubber>( this, QuickTimeScrubber::onMovieChanged, "QuickTimeScrubber::onMovieChanged" );
		}		

		quickTimeControl_->MovieChanged += movieChanged;
	}
	
}

void QuickTimeScrubber::paint( VCF::GraphicsContext* ctx )
{
	CustomControl::paint( ctx );

	Color* black = Color::getColor( "black" );

	VCF::Rect r = getClientBounds();
	r.inflate( -5, -5 );

	ctx->rectangle( &r );
	ctx->setColor( black );
	ctx->strokePath();

	std::vector<VCF::Point> pts;
	pts.resize( 3 );
	
	double dx = maxRange_ - minRange_;
	double pos = r.left_ + ((r.getWidth()/dx) * currentPosition_.value.lo);

	ctx->moveTo( pos, r.top_ );
	ctx->lineTo( pos, r.bottom_ );
	ctx->strokePath();

	pts[0].x_ = pos - 5;
	pts[0].y_ = r.top_-3;
	pts[1].x_ = pos + 5;
	pts[1].y_ = r.top_-3;
	pts[2].x_ = pos;
	pts[2].y_ = r.top_+3;

	ctx->setColor( black );//GraphicsToolkit::getDefaultGraphicsToolkit()->getSystemColor( SYSCOLOR_FACE ) );
	
	ctx->polyline( pts );
	
	ctx->fillPath();
	
	ctx->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW ) );	
	ctx->moveTo( pts[1].x_, pts[1].y_ );
	ctx->lineTo( pts[0].x_-1, pts[0].y_ );
	ctx->lineTo( pts[2].x_, pts[2].y_ );
	ctx->strokePath();
	
	ctx->setColor( GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT ) );	
	ctx->moveTo( pts[2].x_, pts[2].y_ );
	ctx->lineTo( pts[1].x_+2, pts[1].y_-1 );
	ctx->strokePath();
	
}

void QuickTimeScrubber::setMaxRange( const double& val )
{
	maxRange_ = val;
	repaint();
}

void QuickTimeScrubber::setMinRange( const double& val )
{
	minRange_ = val;
	repaint();
}

void QuickTimeScrubber::setCurrentPosition( const TimeRecord& val )
{
	currentPosition_ = val;
	repaint();
	if ( this->quickTimeControl_ ) {
		
		quickTimeControl_->getMovie()->setCurrentTime( val );
	}
}

void QuickTimeScrubber::mouseDown( MouseEvent* event )
{
	CustomControl::mouseDown( event );
	scrubbing_ = false;
	if ( event->hasLeftButton() ) {
		VCF::Rect r = getClientBounds();
		r.inflate( -5, -5 );	
		
		scrubbing_ = true;
		keepMouseEvents();
		quickTimeControl_->getMovie()->pause();
		
		TimeRecord time = currentPosition_;
		time.value.lo =  maxVal<unsigned long>( 0, ((event->getPoint()->x_ - r.left_) / r.getWidth()) * (maxRange_-minRange_) );
		time.value.lo = minVal<unsigned long>( time.value.lo, maxRange_ );

		setCurrentPosition( time );
		
	}
}

void QuickTimeScrubber::mouseMove( MouseEvent* event )
{
	CustomControl::mouseMove( event );
	if ( event->hasLeftButton() && scrubbing_ ) {
		VCF::Rect r = getClientBounds();
		r.inflate( -5, -5 );	
		
		TimeRecord time = currentPosition_;			
		time.value.lo =  maxVal<unsigned long>( 0, ((event->getPoint()->x_ - r.left_) / r.getWidth()) * (maxRange_-minRange_) );
		time.value.lo = minVal<unsigned long>( time.value.lo, maxRange_ );
		setCurrentPosition( time );		
	}
}	

void QuickTimeScrubber::mouseUp( VCF::MouseEvent* event )
{
	CustomControl::mouseUp( event );
	
	releaseMouseEvents();
	if ( event->hasLeftButton() && scrubbing_ ) {
		VCF::Rect r = getClientBounds();
		r.inflate( -5, -5 );	
		
		TimeRecord time = currentPosition_;			
		time.value.lo =  maxVal<unsigned long>( 0, ((event->getPoint()->x_ - r.left_) / r.getWidth()) * (maxRange_-minRange_) );
		time.value.lo = minVal<unsigned long>( time.value.lo, maxRange_ );
		setCurrentPosition( time );		
	}

	scrubbing_ = false;
}


