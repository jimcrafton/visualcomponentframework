//CommonColorDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */
#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;

CommonColorDialog::CommonColorDialog( Control* owner )
{
	peer_ = NULL;

	peer_ = UIToolkit::createCommonColorDialogPeer( owner );
	if ( NULL == peer_ ){

	}


}

CommonColorDialog::~CommonColorDialog()
{
	delete peer_;
}

bool CommonColorDialog::execute()
{
	return peer_->execute();
}

Color* CommonColorDialog::getSelectedColor()
{
	return peer_->getSelectedColor();
}

void CommonColorDialog::setSelectedColor( Color* selectedColor )
{
	peer_->setSelectedColor( selectedColor );
}


/**
$Id$
*/
