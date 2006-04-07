//QuickTimeMovie.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "QuickTimeMovie.h"

using namespace VCF;


QuickTimeMovie::QuickTimeMovie():
	qtMovie_(NULL),
	displayControl_(NULL),
	isMovieOpen_(false),
	aspectRatio_(1.0),
	playState_(psStopped)
{
	memset( &currentTime_, 0, sizeof(TimeRecord) );
}

QuickTimeMovie::QuickTimeMovie( VCF::Control* displayControl ):
	qtMovie_(NULL),
	displayControl_(displayControl),
	isMovieOpen_(false),
	aspectRatio_(1.0),
	playState_(psStopped)
{
	memset( &currentTime_, 0, sizeof(TimeRecord) );
	if ( NULL == displayControl_ ) {
		throw RuntimeException ("Display Control for the Quicktime movie is NULL");
	}

	HWND hwnd = (HWND) displayControl_->getPeer()->getHandleID();
	CreatePortAssociation( hwnd, NULL, 0L);
}

QuickTimeMovie::QuickTimeMovie( VCF::Control* displayControl, const String& filename ):
	qtMovie_(NULL),
	displayControl_(displayControl),
	isMovieOpen_(false),
	aspectRatio_(1.0),
	playState_(psStopped)
{
	memset( &currentTime_, 0, sizeof(TimeRecord) );
	if ( NULL == displayControl_ ) {
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

	if ( NULL != displayControl_ ) {
		HWND hwnd = (HWND) displayControl_->getPeer()->getHandleID();

		DestroyPortAssociation( (CGrafPtr)GetNativeWindowPort( hwnd ) );
	}
}

void QuickTimeMovie::setDisplayControl( VCF::Control* displayControl )
{
	if ( NULL != displayControl_ ) {
		HWND hwnd = (HWND) displayControl_->getPeer()->getHandleID();

		DestroyPortAssociation( (CGrafPtr)GetNativeWindowPort( hwnd ) );
	}

	displayControl_ = displayControl;

	if ( NULL == displayControl_ ) {
		throw RuntimeException ("Display Control for the Quicktime movie is NULL");
	}

	HWND hwnd = (HWND) displayControl_->getPeer()->getHandleID();
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
		filename_ = filename;
		int size = minVal<int>(254, filename_.size() );
		filename_.copy( theFullPath, size );

		// convert theFullPath to pstring
		c2pstr((char*)theFullPath);

		// Make a FSSpec with a pascal string filename
		FSMakeFSSpec(0,0L, (const unsigned char*)theFullPath, &sfFile);

		// Set the port
		HWND hwnd = NULL;
		if ( NULL != displayControl_ ) {
			hwnd = (HWND) displayControl_->getPeer()->getHandleID();
			SetGWorld( (CGrafPtr)GetNativeWindowPort( (void *)hwnd ), nil );
		}

		err = OpenMovieFile( &sfFile, &movieResFile, fsRdPerm);

		if (err == noErr) {
			// Get the Movie from the file
			err = NewMovieFromFile( &qtMovie_, movieResFile, 
									nil, 
									nil, 
									newMovieActive, /* flags */
									nil);

			// Close the movie file
			CloseMovieFile(movieResFile);

			if (err == noErr)	{

				isMovieOpen_ = true;

				result = true;

				p2cstr((unsigned char*)theFullPath);

				if ( NULL != displayControl_ ) {
					SetMovieGWorld ( qtMovie_, (CGrafPtr)GetNativeWindowPort((void *) hwnd ), nil );
				}
				originalBounds_ = getBounds();//initialize the bounds

				if ( originalBounds_.getWidth() > originalBounds_.getHeight() ) {
					aspectRatio_ = originalBounds_.getWidth() / originalBounds_.getHeight();
				}
				else {
					aspectRatio_ = originalBounds_.getHeight() / originalBounds_.getWidth();
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

	if ( result ) {
		setTitle();

		Event movieEvent( this );
		MovieOpened.fireEvent( &movieEvent );
	}
	return result;
}

void QuickTimeMovie::reset()
{
	TimeRecord time = {0};
	time.base = GetMovieTimeBase( qtMovie_ );
	SetMovieTime ( qtMovie_, &time );
	memset( &currentTime_, 0, sizeof(TimeRecord) );

	playState_ = psPlaying;
}

void QuickTimeMovie::play()
{
	SetMovieTime ( qtMovie_, &currentTime_ );
	StartMovie( qtMovie_ );
	playState_ = psPlaying;
}

void QuickTimeMovie::stop()
{
	StopMovie( qtMovie_ );
	reset();
	playState_ = psStopped;
}

void QuickTimeMovie::pause()
{
	StopMovie( qtMovie_ );
	GetMovieTime ( qtMovie_, &currentTime_ );
	playState_ = psPaused;
}

bool QuickTimeMovie::isOpen()
{
	return isMovieOpen_;
}

bool QuickTimeMovie::close()
{
	filename_ = "";
	memset( &currentTime_, 0, sizeof(TimeRecord) );

	aspectRatio_ = 1.0;
	originalBounds_.setRect(0,0,0,0);

	bool result = false;


	isMovieOpen_ = false;

	if ( NULL != qtMovie_ ) {
		DisposeMovie( qtMovie_ );
		result = true;
	}

	qtMovie_ = NULL;
	playState_ = psStopped;

	return result;
}


void QuickTimeMovie::movieTask( const long& timeout )
{
	if ( (NULL != qtMovie_) && (NULL != displayControl_) ) {
		MoviesTask ( qtMovie_, timeout );

		Event movieEvent( this );
		MovieFrameChanged.fireEvent( &movieEvent ); 
	}
}

VCF::Rect QuickTimeMovie::getBounds()
{
	VCF::Rect result;

	QuickTimeMovie::QTRect r;
	GetMovieBox( qtMovie_, &r );

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

	SetMovieBox( qtMovie_, &r );
}

void QuickTimeMovie::setBounds( const double& x, const double& y, const double& width, const double& height )
{
	VCF::Rect rect( x, y, x + width, y + height );
	setBounds( rect );
}

TimeRecord QuickTimeMovie::getCurrentTime()
{
	GetMovieTime ( qtMovie_, &currentTime_ );

	return currentTime_;
}

void QuickTimeMovie::setCurrentTime( TimeRecord* time )
{
	memcpy( &currentTime_, time, sizeof(TimeRecord) );
	currentTime_.base = GetMovieTimeBase( qtMovie_ );
	SetMovieTime ( qtMovie_, &currentTime_ );
}

void QuickTimeMovie::setCurrentTime( const TimeRecord& time )
{
	memcpy( &currentTime_, &time, sizeof(TimeRecord) );
	currentTime_.base = GetMovieTimeBase( qtMovie_ );
	SetMovieTime ( qtMovie_, &currentTime_ );
}

void QuickTimeMovie::update()
{
	if ( NULL != qtMovie_ ) {
		UpdateMovie( qtMovie_ );
	}
}

void QuickTimeMovie::redrawMovie()
{
	OSErr 		err = noErr;
	QuickTimeMovie::QTRect		movieRect;
	RgnHandle	clipRegion = NULL;


	if ( qtMovie_ == NULL ) goto bail;

	clipRegion = NewRgn();
	if ( clipRegion == NULL ) goto bail;

	GetClip( clipRegion );
	GetMovieBox( qtMovie_, &movieRect ); 
	ClipRect( &movieRect );

	UpdateMovie( qtMovie_ );
	MoviesTask( qtMovie_, 0 );

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

	result = (double) GetMovieDuration( qtMovie_ );

	return result;
}

double QuickTimeMovie::getCurrentTimeValue()
{
	double result = -1.0;

	return result;
}

bool QuickTimeMovie::hasMovieTrack()
{
	ulong32 count = GetMovieTrackCount( qtMovie_ );


	for (ulong32 index = 1; index <= count; index++) {
		Track track = GetMovieIndTrack(qtMovie_, index);

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
	currentTime = GetMovieTime(qtMovie_, NULL);

	unsigned long f = 1 << 16;
	GetMovieNextInterestingTime(qtMovie_, flags, 1, types, currentTime, f, &nextTime, NULL);


	if ( (nextTime < 0) || (nextTime > GetMovieDuration(qtMovie_)) ) {
		return ;
	}

	SetMovieTimeValue(qtMovie_, nextTime);

	UpdateMovie(qtMovie_);

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
	currentTime = GetMovieTime(qtMovie_, NULL);

	long f = 1 << 16;

	GetMovieNextInterestingTime(qtMovie_, flags, 1, types, currentTime, -f, &prevTime, NULL);


	if ( (prevTime < 0) || (prevTime > GetMovieDuration(qtMovie_)) ) {
		return ;
	}

	SetMovieTimeValue(qtMovie_, prevTime);

	UpdateMovie(qtMovie_);

	movieTask();
}

void QuickTimeMovie::getMovieMetaInfo( std::vector<QuickTimeMovie::MovieMetaInfo>& infoList )
{

	if ( NULL == qtMovie_ ) {
		return;
	}



	UserData data = GetMovieUserData( qtMovie_ );

	OSType udType;
	Handle hData = NULL;
	hData = NewHandle(0);
	udType = GetNextUserDataType(data, 0);

	int count = 0;
	do {
		if(0 != udType) {
			count = CountUserDataType(data, udType);
			for(int i = 1; i <= count; i++) {
				unsigned char c = (udType>>24);
				if( c == 0xA9  ) {
					GetUserDataText(data, hData, udType, i, langEnglish);
					int sz = GetHandleSize(hData);
					if ( sz > 0 ) {
						char tmp[256];
						memset( tmp,0,256);
						memcpy( tmp,*hData,min(255,sz) );
						String s = tmp;

						MovieMetaInfo info;

						info.second = s;

						switch( udType ) {
							case kUserDataTextAuthor : {
								info.first = L"Author";
							}
							break;

							case kUserDataTextComment : {
								info.first = L"Comments";
							}
							break;

							case kUserDataTextCopyright : {
								info.first = L"Copyright";
							}
							break;

							case kUserDataTextCreationDate : {
								info.first = L"Created on";
							}
							break;

							case kUserDataTextDescription : {
								info.first = L"Description";
							}
							break;

							case kUserDataTextDirector : {
								info.first = L"Director";
							}
							break;

							case kUserDataTextDisclaimer : {
								info.first = L"Disclaimer";
							}
							break;

							case kUserDataTextFullName : {
								info.first = L"Full name";
							}
							break;

							case kUserDataTextInformation : {
								info.first = L"Information";
							}
							break;

							case kUserDataTextKeywords : {
								info.first = L"Keywords";
							}
							break;

							case kUserDataTextMake : {
								info.first = L"Make";
							}
							break;

							case kUserDataTextModel : {
								info.first = L"Model";
							}
							break;

							case kUserDataTextOriginalFormat : {
								info.first = L"Orginal Format";
							}
							break;

							case kUserDataTextOriginalSource : {
								info.first = L"Orginal Source";
							}
							break;

							case kUserDataTextPerformers : {
								info.first = L"Performers";
							}
							break;

							case kUserDataTextProducer : {
								info.first = L"Producer";
							}
							break;

							case kUserDataTextProduct : {
								info.first = L"Product";
							}
							break;

							case kUserDataTextSoftware : {
								info.first = L"Software";
							}
							break;

							case kUserDataTextWarning : {
								info.first = L"Warning";
							}
							break;

							case kUserDataTextWriter : {
								info.first = L"Writer";
							}
							break;

							case kUserDataTextChapter : {
								info.first = L"Chapter";
							}
							break;
						}

						infoList.push_back(info);
					}
				}
			}
		}

		udType = GetNextUserDataType(data, udType);
	} while(0 != udType);

	DisposeHandle(hData);




	MovieMetaInfo movieInfo;


	movieInfo.first = L"Source";
	movieInfo.second = filename_;
	infoList.push_back(movieInfo);


	movieInfo.first = L"Size";


	VCF::Rect bounds = getBounds();
	movieInfo.second = Format( L"%d x %d pixels" ) % (int)bounds.getWidth() % (int)bounds.getHeight();

	infoList.push_back(movieInfo);

	movieInfo.first = L"Duration";

	double scale = GetMovieTimeScale( qtMovie_ );
	double seconds = getDuration()/scale;//time.value.lo / scale;


	int i_seconds = seconds;
	int hours = i_seconds / 3600;
	i_seconds = i_seconds - (hours*3600);
	int minutes = i_seconds / 60;
	i_seconds = i_seconds - (minutes*60);

	movieInfo.second = Format( "%02d:%02d:%02d" ) % hours % minutes % i_seconds;
	infoList.push_back(movieInfo);



	movieInfo.first = L"Movie FPS";
	movieInfo.second = Format( "%0.2f" ) % (scale/100.0);
	infoList.push_back(movieInfo);


	uint32 dataSize = GetMovieDataSize ( qtMovie_, 0, getDuration() );

	movieInfo.first = L"Data Size";

	movieInfo.second = System::getCurrentThreadLocale()->toString( dataSize ) + " bytes";
	infoList.push_back(movieInfo);

}

void QuickTimeMovie::setTitle()
{
	FilePath fp = filename_;
	title_ = fp.getBaseName();

	UserData data = GetMovieUserData( qtMovie_ );

	OSType udType;
	Handle hData = NULL;
	hData = NewHandle(0);
	udType = GetNextUserDataType(data, 0);

	bool titleFound = false;
	int count = 0;
	do {
		if( (0 != udType) && !titleFound  ) {
			count = CountUserDataType(data, udType);
			for(int i = 1; i <= count; i++) {
				unsigned char c = (udType>>24);
				if( c == 0xA9  ) {
					GetUserDataText(data, hData, udType, i, langEnglish);
					int sz = GetHandleSize(hData);
					if ( (sz > 0)  && (kUserDataTextFullName == udType) ) {
						char tmp[256];
						memset( tmp,0,256);
						memcpy( tmp,*hData,min(255,sz) );
						title_ = tmp;
						titleFound = true;
						break;
					}
				}
			}
		}

		udType = GetNextUserDataType(data, udType);
	} while(0 != udType);

	DisposeHandle(hData);

}


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:34:39  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.1  2005/07/23 21:45:40  ddiego
*merged in marcellos changes from the 0-6-7 dev branch.
*
*Revision 1.3.4.3  2005/05/05 14:19:52  marcelloptr
*standard VCF formatting
*
*/


