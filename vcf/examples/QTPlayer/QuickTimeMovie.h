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

	typedef Rect QTRect;

	enum {
		DefaultTimeOutVal = 5000
	};

	
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
		return m_qtMovie;
	}

	const Movie getMovie() const {
		return m_qtMovie;
	}

	operator Movie& () {
		return m_qtMovie;
	}

	operator const Movie& () const {
		return m_qtMovie;
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
		return m_aspectRatio;
	}

	VCF::Rect getOriginalBounds() {
		return m_originalBounds;
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
protected:
	TimeRecord m_currentTime;
	Movie m_qtMovie;
	VCF::Control* m_displayControl;
	bool m_isMovieOpen;
	VCF::String m_filename;
	VCF::Rect m_originalBounds;
	
	PlayState playState_;

	double m_aspectRatio;
	void redrawMovie();

};


#endif //_QUICKTIMEMOVIE_H__


