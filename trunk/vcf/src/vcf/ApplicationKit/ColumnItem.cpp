/*
Copyright 2000-2008 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ColumnItem.h"
#include "vcf/ApplicationKit/ColumnModel.h"


using namespace VCF;

//ColumnItem.cpp

double ColumnItem::getWidth()
{
	return getController()->getItemWidth( this );
}

void ColumnItem::setWidth( const double& width )
{
	getController()->setItemWidth( this, width );
}

void ColumnItem::setCaptionAlignment( const TextAlignmentType& alignment )
{
	getController()->setItemTextAlignment( this, alignment );
}

TextAlignmentType ColumnItem::getCaptionAlignment()
{
	return getController()->getItemTextAlignment( this );
}


String ColumnItem::getCaption() 
{
	//control's getUseLocaleStrings() takes precedence over ours
	Control* control = getControl();
	ListModel* lm = (ListModel*) getModel();
	if ( getUseLocaleStrings() && (NULL != control) && (control->getUseLocaleStrings()) ) {
		return System::getCurrentThreadLocale()->translate( lm->getAsString( index_ ) );
	}
	return lm->getAsString( index_ );
}

void ColumnItem::setCaption( const String& caption )
{
	ListModel* lm = (ListModel*) getModel();
	VCF_ASSERT( NULL != lm );

	lm->setAsString( index_, caption, false );
}
