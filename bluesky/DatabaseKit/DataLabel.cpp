//DataLabel.cpp


/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "DatabaseUIKit.h"
#include "vcf/ApplicationKit/Label.h"
#include "DataLabel.h"
#include "DataLink.h"



using namespace VCF;

DataLabel::DataLabel(): Label(), dataLink_(NULL)
{
	dataLink_ = new FieldDataLink();

	dataLink_->DataChange +=
		new ClassProcedure1<Event*, DataLabel>(this,&DataLabel::onDataLinkDataChanged,"DataLabel::onDataLinkDataChanged");
}

DataLabel::~DataLabel() {
	dataLink_->free();
}

void DataLabel::setDataSource( DataSource* val ) {
	dataLink_->setDataSource( val );
}

void DataLabel::setFieldName( const String& name ) {
	dataLink_->setFieldName( name );
}

DataField* DataLabel::getField() {
	return dataLink_->getField();
}

void DataLabel::onDataLinkDataChanged( Event* e ) {
	setCaption( getField()->getAsString() );
}