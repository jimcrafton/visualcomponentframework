//MainWindow.h

#ifndef _MAINWINDOW_H__
#define _MAINWINDOW_H__


class QuickTimeMovie;
class QuickTimeControl;

namespace VCF {
	class StatusBarControl;
	class DropTargetEvent;
	class SliderControl;
	class Panel;
	class TreeControl;
	class Label;
	class ListViewControl;
	class Dictionary;
};

class PlayListDictionary;


/**
*Class MainQTWindow documentation
*/
class MainQTWindow : public VCF::Window { 
public:
	MainQTWindow();

	virtual ~MainQTWindow();	

protected:
	void onFileOpenMovie( VCF::Event* e );
	void onFileCloseMovie( VCF::Event* e );
	void updateFileCloseMovie( VCF::ActionEvent* e );

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

	void onViewSideBar(  VCF::Event* event );
	void updateViewSideBar( VCF::ActionEvent* e );

	void onViewMediaInfo(  VCF::Event* event );
	void updateViewMediaInfo( VCF::ActionEvent* e );

	void onViewSearch(  VCF::Event* event );
	void updateViewSearch( VCF::ActionEvent* e );

	void onViewPlayControls(  VCF::Event* event );
	void updateViewPlayControls( VCF::ActionEvent* e );

	void onViewPlaylist(  VCF::Event* event );
	void updateViewPlaylist( VCF::ActionEvent* e );

	void onSearchIconClick( VCF::Event* e );
	void onSearchTextEntered( VCF::KeyboardEvent* e );

	
	void onPlaylistViewDblClick( VCF::Event* e );

	void onPlaylistItemSelected( VCF::Event* e );	

	void onCreatePlaylist(  VCF::Event* event );
	void updateCreatePlaylist( VCF::ActionEvent* e );

	void onAddToPlaylist(  VCF::Event* event );
	void updateAddToPlaylist( VCF::ActionEvent* e );

	void onPlaylistDraggingOver( VCF::DropTargetEvent* e );
	void onPlaylistFilesDropped( VCF::DropTargetEvent* e );

	void onAddToFilesPlaylist(  VCF::Event* event );
	void updateAddToFilesPlaylist( VCF::ActionEvent* e );

	void addFileNameToPlaylist( const VCF::String& fileName );

	void onPlaylistItemChanged( VCF::ItemEvent* event );

	void onPlayListCtrlKeyPressed( VCF::KeyboardEvent* e );
	void onPlayListTreeKeyPressed( VCF::KeyboardEvent* e );

	void onEditCreateSearchCatalog(  VCF::Event* event );
	void onCreateSearchCatalogThreadDone(  VCF::Event* event );

	QuickTimeControl* quicktimeControl_;
	VCF::SliderControl* volumeControl_;

	VCF::Panel* playPanel_;
	VCF::Panel* searchPanel_;

	VCF::Panel* sideBar_;
	VCF::TreeControl* playListTree_;
	VCF::Panel* mediaInfo_;

	VCF::Panel* mediaBar_;
	VCF::Label* mediaLabel_;

	VCF::Panel* mainViewPanel_;
	
	VCF::ListViewControl* playListCtrl_;

	PlayListDictionary* playListDict_;

	VCF::String playlistFile_;

	void buildUI();

	void loadPlaylist();
	void savePlaylist();
	bool movieLoaded_;
};


#endif //_MAINWINDOW_H__


