//MainWindow.h

#ifndef _MAINWINDOW_H__
#define _MAINWINDOW_H__


class QuickTimeMovie;
class QuickTimeControl;

namespace VCF {
	class StatusBarControl;
	class DropTargetEvent;
	class SliderControl;
};


/**
*Class MainQTWindow documentation
*/
class MainQTWindow : public VCF::Window { 
public:
	MainQTWindow();

	virtual ~MainQTWindow();	

protected:
	void onFileOpenMovie( VCF::Event* e );

	void onFileExit( VCF::Event* e );
	void onHelpAbout( VCF::Event* e );

	void onMoviePlay( VCF::Event* e );
	void onMovieReset( VCF::Event* e );
	void onMovieStop( VCF::Event* e );
	void onMoviePause( VCF::Event* e );

	void onViewNormal( VCF::Event* e );
	void onViewDouble( VCF::Event* e );
	void onViewHalf( VCF::Event* e );

	void onViewLockAspectRatio( VCF::Event* e );
	void onViewAllowResize( VCF::Event* e );	

	void onClose( VCF::WindowEvent* event );
	void onMovieChanged( VCF::Event* movieEvent );
	void onMovieFrameChanged( VCF::Event* movieEvent );

	void onDraggingOver( VCF::DropTargetEvent* e );
	void onFilesDropped( VCF::DropTargetEvent* e );

	void updatePlay( VCF::ActionEvent* e );
	void updateReset( VCF::ActionEvent* e );
	void updateStop( VCF::ActionEvent* e );
	void updatePause( VCF::ActionEvent* e );

	void updateViewNormal( VCF::ActionEvent* e );
	void updateViewDouble( VCF::ActionEvent* e );
	void updateViewHalf( VCF::ActionEvent* e );

	void updateViewLock( VCF::ActionEvent* e );
	void updateViewAllowResize( VCF::ActionEvent* e );

	void onVolumeChanged( VCF::Event* event );
	void onVolumeMute( VCF::Event* event );
	void onVolumeFull( VCF::Event* event );

	void onKeyHandler( VCF::KeyboardEvent* event );

	QuickTimeControl* m_quicktimeControl;
	VCF::StatusBarControl* m_statusBar;
	VCF::SliderControl* volumeControl_;
	bool movieLoaded_;
};


#endif //_MAINWINDOW_H__


