//GTKFileOpenDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/GTKFileOpenDialog.h"


using namespace VCF;

GTKFileOpenDialog::GTKFileOpenDialog( Control* owner ):
	owner_(owner)
{
	container_.initContainer( selectedFiles_ );
}

GTKFileOpenDialog::~GTKFileOpenDialog()
{

}


void GTKFileOpenDialog::init()
{

}

void GTKFileOpenDialog::setTitle( const String& title )
{
	title_ = title;
}

gboolean GTKFileOpenDialog::onDestroyGtkFileSelector( GtkWidget *widget )
{
	return FALSE;
}

bool GTKFileOpenDialog::execute()
{
	bool result = false;
	GtkWidget* openFileDlg = gtk_file_selection_new( title_.ansi_c_str() );

	gtk_window_set_modal (GTK_WINDOW(openFileDlg),TRUE);

	GtkFileSelection* fileSel = GTK_FILE_SELECTION( openFileDlg );

	if ( directory_.empty() ) {
		directory_ = System::getCurrentWorkingDirectory();
	}

	if ( directory_[directory_.size()-1] != FilePath::getDirectorySeparator()[0] ) {
		directory_ += FilePath::getDirectorySeparator();
	}

	FilePath fp = directory_ + fileName_;

	gtk_file_selection_set_filename( fileSel, String(fp).ansi_c_str() );

	gtk_file_selection_set_select_multiple( fileSel, allowsMultiSelect_ ? TRUE : FALSE );

	GtkWidget* parent = NULL;

	if ( owner_ != NULL ) {
		Control* parentControl =  owner_->getParent();
		Control* tmp = owner_;
		while ( parentControl != NULL ) {
			tmp = parentControl;
			parentControl = parentControl->getParent();
		}

		parent = (GtkWidget*)tmp->getPeer()->getHandleID();
		parent = gtk_widget_get_parent( parent );
	}
	else {
		Frame* frame = Frame::getActiveFrame();

		parent = (GtkWidget*)frame->getPeer()->getHandleID();
		parent = gtk_widget_get_parent( parent );
	}

	gtk_window_set_transient_for (GTK_WINDOW (openFileDlg), GTK_WINDOW (parent));

	gint res = gtk_dialog_run (GTK_DIALOG (openFileDlg));


	switch (res)  {
		case GTK_RESPONSE_YES: case GTK_RESPONSE_OK: {
			result = true;
		}
		break;
    }

	if ( result ) {
		fp = String( gtk_file_selection_get_filename(fileSel) );

		directory_ = fp.getPathName(true);
		fileName_ = fp;
	}
	else {
		fileName_ = "";
	}

	gtk_widget_destroy (openFileDlg);

	return result;
}

void GTKFileOpenDialog::addFilter( const String & description, const String & extension )
{

}

void GTKFileOpenDialog::setDirectory( const String & directory )
{
	directory_ = directory;
}

void GTKFileOpenDialog::setFileName( const String & filename )
{
	fileName_ = filename;
}

String GTKFileOpenDialog::getFileName()
{
	return fileName_;
}

String GTKFileOpenDialog::getDirectory()
{
	return directory_;
}

String GTKFileOpenDialog::getFileExtension()
{
	return selectedFileExt_;
}

uint32 GTKFileOpenDialog::getSelectedFileCount()
{
	return selectedFiles_.size();
}

Enumerator<String>* GTKFileOpenDialog::getSelectedFiles()
{
	return container_.getEnumerator();
}

void GTKFileOpenDialog::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	allowsMultiSelect_ = allowsMultiSelect;
}

void GTKFileOpenDialog::setSelectedFilter( const String& selectedFilter )
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:25  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.6  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.1  2003/10/02 04:50:52  ddiego
*changes to ensure the code compiles on linux. made a bunch of updates to
*the makefiles
*
*Revision 1.5  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.4.2.1  2003/07/14 22:52:53  ddiego
*added further GTK support. Fixed some sevent handling issues. Added the
*peer for the CommandButton, and basic text widget support (both multiline and
*single line) and the file open common dialog peer as well.
*
*/


