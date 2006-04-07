//MainWindow.h

#ifndef _MAINWINDOW_H__
#define _MAINWINDOW_H__



/**
*Class MainWindow documentation
*/
class MainWindow : public VCF::Window { 
public:
	MainWindow();

	virtual ~MainWindow();
[!if FILE_MENU]
	void onFileOpenProject( VCF::MenuItemEvent* e );

	void onFileSaveProject( VCF::MenuItemEvent* e );
[!endif]

	void onFileExit( VCF::MenuItemEvent* e );

[!if UNDO_REDO]
	void onEditUndo( VCF::MenuItemEvent* e );

	void onEditUndoUpdate( VCF::MenuItemEvent* e );

	void onEditRedo( VCF::MenuItemEvent* e );

	void onEditRedoUpdate( VCF::MenuItemEvent* e );
[!endif]
[!if HELP_MENU]
	void onHelpAbout( VCF::MenuItemEvent* e );
[!endif]
protected:

private:
};


#endif //_MAINWINDOW_H__


