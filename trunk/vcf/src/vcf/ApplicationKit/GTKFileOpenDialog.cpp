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
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}

void GTKFileOpenDialog::setTitle( const String& title )
{
	title_ = title;
}

gboolean GTKFileOpenDialog::onDestroyGtkFileSelector( GtkWidget *widget )
{
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
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
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
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
	StringUtils::trace(String(__FUNCTION__)+" is not implemented\n");
}


/**
$Id$
*/
