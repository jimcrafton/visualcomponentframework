//DropDownControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DropDownControl.h"
#include "vcf/ApplicationKit/DefaultListModel.h"
#include "vcf/ApplicationKit/DropDownPeer.h"
//#include "vcf/ApplicationKit/ListControl.h"



using namespace VCF;




DropDownControl::DropDownControl(): 
	ListControl(),
	dropDownPeer_(NULL) 
{ 
	dropDownPeer_ = UIToolkit::createDropDownPeer(this);
	
	listPeer_ = dynamic_cast<ListPeer*>( dropDownPeer_ );
	peer_ = dynamic_cast<ControlPeer*>( dropDownPeer_ );
	
	peer_->create(this);
	
	setViewModel( new DefaultListModel() );
}

void DropDownControl::paint( GraphicsContext* context ) 
{
	Rect innerBounds = getClientBounds( false );	
	
	context->setColor( getColor() );
	
	context->rectangle( &innerBounds );
	
	context->fillPath();
}

void DropDownControl::setEditText( const String& text ) 
{
	dropDownPeer_->setEditText(text);
}

String DropDownControl::getEditText() 
{
	return dropDownPeer_->getEditText();
}

void DropDownControl::setDropDownWidth( const double& val ) 
{
	dropDownPeer_->setDropDownWidth(val);
}

double DropDownControl::getDropDownWidth() 
{
	return dropDownPeer_->getDropDownWidth();
}

void DropDownControl::setDropDownCount( const uint32& dropDownCount ) 
{
	dropDownPeer_->setDropDownCount(dropDownCount);
}

uint32 DropDownControl::getDropDownCount()
{
	return dropDownPeer_->getDropDownCount();
}

void DropDownControl::enableEditBox( const bool& val ) 
{
	dropDownPeer_->enableEditBox(val);
}

bool DropDownControl::editBoxEnabled() {
	return dropDownPeer_->editBoxEnabled();
}



