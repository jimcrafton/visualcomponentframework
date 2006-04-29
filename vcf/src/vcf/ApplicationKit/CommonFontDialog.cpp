//CommonFontDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"



using namespace VCF;

CommonFontDialog::CommonFontDialog( Control* owner )
{
	peer_ = UIToolkit::createCommonFontDialogPeer( owner );
	if ( NULL == peer_ ){
		//throw exception
	}


}

CommonFontDialog::~CommonFontDialog()
{
	if ( NULL != peer_ ){
		delete peer_;
	}
	peer_ = NULL;
}

bool CommonFontDialog::execute()
{
	return peer_->execute();
}

Font* CommonFontDialog::getSelectedFont()
{
	return peer_->getSelectedFont();
}

void CommonFontDialog::setSelectedFont( Font* selectedFont )
{
	peer_->setSelectedFont( selectedFont );
}


/**
$Id$
*/
