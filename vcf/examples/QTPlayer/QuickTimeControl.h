//QuickTimeControl.h

#ifndef _QUICKTIMECONTROL_H__
#define _QUICKTIMECONTROL_H__



#include "QTML.h"
#include "Movies.h"

#define QUICKTIMECONTROL_CLASSID		"a9bb58ff-fd84-4a03-ae1f-126f1bba828b"



class QuickTimeMovie;


/**
*Class QuickTimeControl documentation
*/
class QuickTimeControl : public VCF::CustomControl { 
public:

	enum ViewState {
		vsNormal=0,
		vsDouble,
		vsHalf,
		vsCustom
	};


	BEGIN_CLASSINFO(QuickTimeControl, "QuickTimeControl", "VCF::CustomControl", QUICKTIMECONTROL_CLASSID)
	//EVENT("VCF::GenericEventHandler", "VCF::Event", "MovieChanged" );
	//EVENT("VCF::GenericEventHandler", "VCF::Event", "MovieFrameChanged" );
	END_CLASSINFO(QuickTimeControl)

	DELEGATE(MovieChanged);

	DELEGATE(MovieFrameChanged);

	QuickTimeControl();

	virtual ~QuickTimeControl();

	QuickTimeMovie* getMovie() {
		return m_currentMovie;
	}

	virtual void beforeDestroy( VCF::ComponentEvent* event );

	virtual void paint( VCF::GraphicsContext* ctx );

	virtual void afterCreate( VCF::ComponentEvent* event );

	bool open( const VCF::String filename );

	virtual void setBounds( VCF::Rect* rect, const bool& anchorDeltasNeedUpdating=true );

	virtual void handleEvent( VCF::Event* e );

	bool getAllowsResizing() {
		return m_allowResizing;
	}

	void setAllowsResizing( const bool& resizing );

	bool getLockAspectRatio() {
		return m_lockAspectRatio;
	}

	void setLockAspectRatio( const bool& lockAspectRatio );

	double getZoomLevel() {
		return m_zoomLevel;
	}

	void setZoomLevel( const double& val );

	void setViewDoubleSize();
	void setViewHalfSize();
	void setViewNormalSize();

	bool isDoubleSize() {
		return viewState_  == vsDouble;
	}

	bool isHalfSize(){
		return viewState_  == vsHalf;
	}

	bool isNormalSize(){
		return viewState_  == vsNormal;
	}
	
	ViewState getViewState() {
		return viewState_;
	}
protected:
	QuickTimeMovie* m_currentMovie;
	double m_zoomLevel;
	bool m_lockAspectRatio;
	bool m_allowResizing;
	ViewState viewState_;

	void setMovieBounds( VCF::Rect* rect );

	void onTimer( VCF::Event* e );
};




#define QUICKTIMESCRUBBER_CLASSID	"43D4C0CF-A834-4b90-AC13-318A2AC4E96F"
	


class QuickTimeScrubber : public VCF::CustomControl { 
public:
	BEGIN_CLASSINFO(QuickTimeScrubber, "QuickTimeScrubber", "VCF::CustomControl", QUICKTIMESCRUBBER_CLASSID)	
	END_CLASSINFO(QuickTimeScrubber)

	QuickTimeScrubber();
	virtual ~QuickTimeScrubber();

	

	QuickTimeControl* getQuickTimeControl() {
		return m_quickTimeControl;
	}

	void setQuickTimeControl( QuickTimeControl* control );

	virtual void paint( VCF::GraphicsContext* ctx );

	double getMaxRange() {
		return m_maxRange;
	}

	double getMinRange() {
		return m_minRange;
	}

	TimeRecord getCurrentPosition() {
		return m_currentPosition;
	}

	void setMaxRange( const double& val ) ;

	void setMinRange( const double& val ) ;

	void setCurrentPosition( const TimeRecord& val ) ;
	

	virtual double getPreferredHeight() {
		return 25;
	}

	virtual void mouseDown( VCF::MouseEvent* event );

	virtual void mouseMove( VCF::MouseEvent* event );

	virtual void mouseUp( VCF::MouseEvent* event );
protected:
	QuickTimeControl* m_quickTimeControl;
	double m_maxRange;
	double m_minRange;
	bool m_scrubbing;
	TimeRecord m_currentPosition;
	void onMovieChanged( VCF::Event* movieEvent );
	void onMovieFrameChanged( VCF::Event* movieEvent );

};


#endif //_QUICKTIMECONTROL_H__


