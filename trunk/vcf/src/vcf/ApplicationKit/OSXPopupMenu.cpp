//OSXPopupMenu.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXPopupMenu.h"
#include "vcf/ApplicationKit/MenuItemPeer.h"
#include "vcf/ApplicationKit/OSXMenuItem.h"



using namespace VCF;

OSXPopupMenu::OSXPopupMenu( PopupMenu* popupMenu )
{
	control_ = NULL;
	popupMenu_ = popupMenu;
}

OSXPopupMenu::~OSXPopupMenu()
{

}

void OSXPopupMenu::setControl( Control* control )
{
	control_ = control;
}



MenuItem* OSXPopupMenu::popup( Point* pt )
{
	MenuItem* result = NULL;
	if ( (NULL != control_) && (NULL != pt) ){
		MenuItem* rooItem = popupMenu_->getRootMenuItem();
		if  ( NULL != rooItem )  {
			
		}
	}
	
	return result;
}


/**
$Id$
*/
