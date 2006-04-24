//QuickTimeMovie.h

#ifndef _QUICKTIMEMOVIE_H__
#define _QUICKTIMEMOVIE_H__

#include "QTML.h"
#include "Movies.h"
#include "TextUtils.h"


#define QUICKTIMEMOVIE_CLASSID	"0A593B99-7765-4c32-8365-4B82F08E3EA9"


/**
*Class QuickTimeMovie documentation
*/
class QuickTimeMovie : public VCF::ObjectWithEvents { 
public:

	//BEGIN_CLASSINFO(QuickTimeMovie, "QuickTimeMovie", "VCF::ObjectWithEvents", QUICKTIMEMOVIE_CLASSID)
	//EVENT("VCF::GenericEventHandler", "VCF::Event", "MovieFrameChanged" );
	//END_CLASSINFO(QuickTimeMovie)

	DELEGATE(MovieFrameChanged);
	DELEGATE(MovieOpened);

	typedef Rect QTRect;

	enum {
		DefaultTimeOutVal = 5000
	};

	typedef std::pair<VCF::String,VCF::String> MovieMetaInfo;
	
	enum PlayState {
		psPlaying = 0,
		psStopped,
		psPaused
	};

	QuickTimeMovie();

	QuickTimeMovie( VCF::Control* displayControl );

	QuickTimeMovie( VCF::Control* displayControl, const VCF::String& filename );

	virtual ~QuickTimeMovie();

	bool open( const VCF::String& filename );

	void reset();

	void play();

	void stop();

	void pause();

	bool isOpen();

	bool close();

	Movie getMovie() {
		return qtMovie_;
	}

	const Movie getMovie() const {
		return qtMovie_;
	}

	operator Movie& () {
		return qtMovie_;
	}

	operator const Movie& () const {
		return qtMovie_;
	}

	void movieTask( const long& timeout=QuickTimeMovie::DefaultTimeOutVal );

	VCF::Rect getBounds();

	void setBounds( const VCF::Rect& bounds );

	void setBounds( const double& x, const double& y, const double& width, const double& height );

	TimeRecord getCurrentTime();
	double getCurrentTimeValue();

	void setCurrentTime( TimeRecord* time );

	void setCurrentTime( const TimeRecord& time );

	void update();

	double getDuration();

	void setDisplayControl( VCF::Control* displayControl );

	double getAspectRatio() {
		return aspectRatio_;
	}

	VCF::Rect getOriginalBounds() {
		return originalBounds_;
	}

	
	bool isPlaying() {
		return playState_ == psPlaying;
	}

	bool isStopped() {
		return playState_ == psStopped;
	}

	bool isPaused() {
		return playState_ == psPaused;
	}

	bool hasMovieTrack();

	void nextFrame();
	void previousFrame();

	void getMovieMetaInfo( std::vector<MovieMetaInfo>& infoList );

	VCF::String getTitle() const {
		return title_;
	}

	VCF::String getFileName() const {
		return filename_;
	}
protected:
	TimeRecord currentTime_;
	Movie qtMovie_;
	VCF::Control* displayControl_;
	bool isMovieOpen_;
	VCF::String filename_;
	VCF::String title_;
	VCF::Rect originalBounds_;
	
	PlayState playState_;

	double aspectRatio_;
	void redrawMovie();

	void setTitle();

};


#endif //_QUICKTIMEMOVIE_H__


