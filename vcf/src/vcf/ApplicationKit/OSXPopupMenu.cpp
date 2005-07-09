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



void OSXPopupMenu::popup( Point* pt )
{
	if ( (NULL != control_) && (NULL != pt) ){
		MenuItem* rooItem = popupMenu_->getRootMenuItem();
		if  ( NULL != rooItem )  {
			
		}
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:54  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.1  2005/06/22 03:59:30  ddiego
*added osx stub classes for peers
*
*/


