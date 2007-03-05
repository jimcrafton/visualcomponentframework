//PopupWindow.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/PopupWindowPeer.h"
#include "vcf/ApplicationKit/WindowPeer.h"
#include "vcf/ApplicationKit/PopupWindow.h"


using namespace VCF;


PopupWindow::PopupWindow():
	popupPeer_(NULL),
	windowPeer_(NULL)
{

	popupPeer_ = UIToolkit::createPopupWindowPeer( this, NULL );

	peer_ = dynamic_cast<ControlPeer*>(popupPeer_);

	windowPeer_ = dynamic_cast<WindowPeer*>(popupPeer_);
}

PopupWindow::~PopupWindow()
{

}

void PopupWindow::showModal()
{
	popupPeer_->showModal();
}

void PopupWindow::showAsSheet( Window* owningWindow )
{
	popupPeer_->showAsSheet( owningWindow );
}

void PopupWindow::show()
{
	popupPeer_->show();
}