//QuickTimeMovie.h
#include "ApplicationKit.h"
#include "QuickTimeMovie.h"

using namespace VCF;


QuickTimeMovie::QuickTimeMovie():
	m_qtMovie(NULL),
	m_displayControl(NULL),
	m_isMovieOpen(false),
	m_aspectRatio(1.0),
	playState_(psStopped)
{
	memset( &m_currentTime, 0, sizeof(TimeRecord) );	
}

QuickTimeMovie::QuickTimeMovie( VCF::Control* displayControl ):	
	m_qtMovie(NULL),
	m_displayControl(displayControl),
	m_isMovieOpen(false),
	m_aspectRatio(1.0),
	playState_(psStopped)
{
	memset( &m_currentTime, 0, sizeof(TimeRecord) );
	if ( NULL == m_displayControl ) {
		throw RuntimeException ("Display Control for the Quicktime movie is NULL");
	}

	HWND hwnd = (HWND) m_displayControl->getPeer()->getHandleID();
	CreatePortAssociation( hwnd, NULL, 0L);	
}

QuickTimeMovie::QuickTimeMovie( VCF::Control* displayControl, const String& filename ):
	m_qtMovie(NULL),
	m_displayControl(displayControl),
	m_isMovieOpen(false),
	m_aspectRatio(1.0),
	playState_(psStopped)
{
	memset( &m_currentTime, 0, sizeof(TimeRecord) );
	if ( NULL == m_displayControl ) {
		throw RuntimeException ("Display Control for the Quicktime movie is NULL");
	}

	if ( filename.empty() ) {
		throw RuntimeException ("Invalid filename for the Quicktime movie");
	}
	open( filename );
}


QuickTimeMovie::~QuickTimeMovie()
{
	close();

	HWND hwnd = (HWND) m_displayControl->getPeer()->getHandleID();

	DestroyPortAssociation( (CGrafPtr)GetNativeWindowPort( hwnd ) );
}

void QuickTimeMovie::setDisplayControl( VCF::Control* displayControl )
{
	if ( NULL != m_displayControl ) {
		HWND hwnd = (HWND) m_displayControl->getPeer()->getHandleID();
		
		DestroyPortAssociation( (CGrafPtr)GetNativeWindowPort( hwnd ) );
	}

	m_displayControl = displayControl;

	if ( NULL == m_displayControl ) {
		throw RuntimeException ("Display Control for the Quicktime movie is NULL");
	}

	HWND hwnd = (HWND) m_displayControl->getPeer()->getHandleID();
	CreatePortAssociation( hwnd, NULL, 0L);	
}

bool QuickTimeMovie::open( const String& filename )
{
	bool result = false;

	close();

	if ( ! filename.empty() )  {
		OSErr				err;
		short				theFile = 0;
		long				controllerFlags = 0L;
		FSSpec				sfFile;
		short				movieResFile;
		char				theFullPath[255];
		memset( theFullPath, 0, 255 );
		// make a copy of our full path name
		m_filename = filename;
		int size = minVal<int>(254, m_filename.size() );
		m_filename.copy( theFullPath, size );

		// convert theFullPath to pstring
		c2pstr((char*)theFullPath);

		// Make a FSSpec with a pascal string filename
		FSMakeFSSpec(0,0L, (const unsigned char*)theFullPath, &sfFile);

		// Set the port	
		HWND hwnd = (HWND) m_displayControl->getPeer()->getHandleID();
		SetGWorld( (CGrafPtr)GetNativeWindowPort( (void *)hwnd ), nil );

		err = OpenMovieFile( &sfFile, &movieResFile, fsRdPerm);

		if (err == noErr) {
			// Get the Movie from the file
			err = NewMovieFromFile( &m_qtMovie, movieResFile, 
									nil, 
									nil, 
									newMovieActive, /* flags */
									nil);
		
			// Close the movie file
			CloseMovieFile(movieResFile);

			if (err == noErr)	{			
			   	
				m_isMovieOpen = true;
				
				result = true;

				p2cstr((unsigned char*)theFullPath);

				SetMovieGWorld ( m_qtMovie, (CGrafPtr)GetNativeWindowPort((void *) hwnd ), nil );    				
				
				m_originalBounds = getBounds();//initialize the bounds

				if ( m_originalBounds.getWidth() > m_originalBounds.getHeight() ) {
					m_aspectRatio = m_originalBounds.getWidth() / m_originalBounds.getHeight();
				}
				else {
					m_aspectRatio = m_originalBounds.getHeight() / m_originalBounds.getWidth();
				}

			} 
			else {
				theFullPath[0] = '\0'; 
			}
				
		} 
		else {
			theFullPath[0] = '\0';
		}
	}

	return result;
}

void QuickTimeMovie::reset()
{
	TimeRecord time = {0};
	time.base = GetMovieTimeBase( m_qtMovie );
	SetMovieTime ( m_qtMovie, &time );
	memset( &m_currentTime, 0, sizeof(TimeRecord) );

	playState_ = psPlaying;
}

void QuickTimeMovie::play()
{
	SetMovieTime ( m_qtMovie, &m_currentTime );
	StartMovie( m_qtMovie );	
	playState_ = psPlaying;
}

void QuickTimeMovie::stop()
{
	StopMovie( m_qtMovie );
	reset();
	playState_ = psStopped;
}

void QuickTimeMovie::pause()
{
	StopMovie( m_qtMovie );
	GetMovieTime ( m_qtMovie, &m_currentTime );
	playState_ = psPaused;
}

bool QuickTimeMovie::isOpen()
{
	return m_isMovieOpen;
}

bool QuickTimeMovie::close()
{
	m_filename = "";
	memset( &m_currentTime, 0, sizeof(TimeRecord) );

	m_aspectRatio = 1.0;
	m_originalBounds.setRect(0,0,0,0);

	bool result = false;

	
	m_isMovieOpen = false;	
		
	if ( NULL != m_qtMovie ) {
		DisposeMovie( m_qtMovie );
		result = true;
	}		
	
	m_qtMovie = NULL;
	playState_ = psStopped;

	return result;
}


void QuickTimeMovie::movieTask( const long& timeout )
{
	if ( NULL != m_qtMovie ) {
		MoviesTask ( m_qtMovie, timeout );

		Event movieEvent( this );
		MovieFrameChanged.fireEvent( &movieEvent ); 
	}
}

VCF::Rect QuickTimeMovie::getBounds()
{
	VCF::Rect result;

	QuickTimeMovie::QTRect r;
	GetMovieBox( m_qtMovie, &r );

	result.left_ = r.left;
	result.top_ = r.top;
	result.right_ = r.right;
	result.bottom_ = r.bottom;

	return result;
}

void QuickTimeMovie::setBounds( const VCF::Rect& bounds )
{
	QuickTimeMovie::QTRect r;
	r.left = bounds.left_;
	r.top = bounds.top_;
	r.right = bounds.right_;
	r.bottom = bounds.bottom_;

	SetMovieBox( m_qtMovie, &r );
}

void QuickTimeMovie::setBounds( const double& x, const double& y, const double& width, const double& height )
{
	VCF::Rect rect( x, y, x + width, y + height );
	setBounds( rect );
}

TimeRecord QuickTimeMovie::getCurrentTime()
{	
	GetMovieTime ( m_qtMovie, &m_currentTime );

	return m_currentTime;
}

void QuickTimeMovie::setCurrentTime( TimeRecord* time )
{	
	memcpy( &m_currentTime, time, sizeof(TimeRecord) );
	m_currentTime.base = GetMovieTimeBase( m_qtMovie );
	SetMovieTime ( m_qtMovie, &m_currentTime );
}

void QuickTimeMovie::setCurrentTime( const TimeRecord& time )
{
	memcpy( &m_currentTime, &time, sizeof(TimeRecord) );
	m_currentTime.base = GetMovieTimeBase( m_qtMovie );
	SetMovieTime ( m_qtMovie, &m_currentTime );
}

void QuickTimeMovie::update()
{
	if ( NULL != m_qtMovie ) {
		UpdateMovie( m_qtMovie );
	}
}

void QuickTimeMovie::redrawMovie()
{
	OSErr 		err = noErr;
	QuickTimeMovie::QTRect		movieRect;
	RgnHandle	clipRegion = NULL;
	
	
	if ( m_qtMovie == NULL ) goto bail;
	
	clipRegion = NewRgn();
	if ( clipRegion == NULL ) goto bail;
	
	GetClip( clipRegion );
	GetMovieBox( m_qtMovie, &movieRect ); 
	ClipRect( &movieRect );
	
	UpdateMovie( m_qtMovie );
	MoviesTask( m_qtMovie, 0 );
	
	SetClip(clipRegion);
	
	/* Closure. Clean up if we have handles. */
bail:	
	
	if	(clipRegion != NULL)
	{
		DisposeRgn(clipRegion);
	}
}

double QuickTimeMovie::getDuration()
{
	double result = -1.0;

	result = (double) GetMovieDuration( m_qtMovie );

	return result;
}

double QuickTimeMovie::getCurrentTimeValue()
{
	double result = -1.0;

	return result;
}

bool QuickTimeMovie::hasMovieTrack()
{
	ulong32 count = GetMovieTrackCount( m_qtMovie );		
	
	
	for (ulong32 index = 1; index <= count; index++) {
		Track track = GetMovieIndTrack(m_qtMovie, index);

		OSType dwType = 0;

		GetMediaHandlerDescription(GetTrackMedia(track), &dwType, NULL, NULL);

		if ( dwType == VideoMediaType ) {
			return true;
		}
	}
	
	return false;
}

void QuickTimeMovie::nextFrame()
{
	TimeValue  currentTime;
	TimeValue  nextTime;
	short   flags;
	OSType   types[1];
	OSErr   myErr = noErr;
	
		
	flags = nextTimeStep;         // we want the next frame in the movie's media
	types[0] = VisualMediaCharacteristic;     // we want video samples
	currentTime = GetMovieTime(m_qtMovie, NULL);
	
	unsigned long f = 1 << 16;
	GetMovieNextInterestingTime(m_qtMovie, flags, 1, types, currentTime, f, &nextTime, NULL);
	
	
	if ( (nextTime < 0) || (nextTime > GetMovieDuration(m_qtMovie)) ) {
		return ;
	}
	
	SetMovieTimeValue(m_qtMovie, nextTime);
	
	UpdateMovie(m_qtMovie);
	
	movieTask();
}

void QuickTimeMovie::previousFrame()
{
	TimeValue  currentTime;
	TimeValue  prevTime;
	short   flags;
	OSType   types[1];
	OSErr   myErr = noErr;
	
		
	flags = nextTimeStep;         // we want the next frame in the movie's media
	types[0] = VisualMediaCharacteristic;     // we want video samples
	currentTime = GetMovieTime(m_qtMovie, NULL);
	
	long f = 1 << 16;

	GetMovieNextInterestingTime(m_qtMovie, flags, 1, types, currentTime, -f, &prevTime, NULL);
	
	
	if ( (prevTime < 0) || (prevTime > GetMovieDuration(m_qtMovie)) ) {
		return ;
	}
	
	SetMovieTimeValue(m_qtMovie, prevTime);
	
	UpdateMovie(m_qtMovie);
	
	movieTask();
}
