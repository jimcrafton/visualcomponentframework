//CommonFileOpenDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;

CommonFileOpenDialog::CommonFileOpenDialog( Control* owner, const String& startDir )
{
	peer_ = UIToolkit::createCommonFileOpenDialogPeer( owner );
	if ( NULL == peer_ ){
		//throw exception
	}

	if ( startDir.size() > 0 ){
		setDirectory( startDir );
	}

	setTitle( "Open" );
}

CommonFileOpenDialog::~CommonFileOpenDialog()
{
	delete peer_;
}


bool CommonFileOpenDialog::execute()
{
	return peer_->execute();
}

Enumerator<String>* CommonFileOpenDialog::getSelectedFiles()
{
	return peer_->getSelectedFiles();
}

void CommonFileOpenDialog::setFileMustExist( const bool& fileMustExist )
{
	peer_->setFileMustExist( fileMustExist );
}


/**
$Id$
*/
