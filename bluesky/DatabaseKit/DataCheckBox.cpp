//DataCheckBox.cpp



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "DatabaseUIKit.h"
#include "DataCheckBox.h"
#include "DataLink.h"



using namespace VCF;

DataCheckBox::DataCheckBox(): CheckBoxControl(), dataLink_(NULL)
{
	dataLink_ = new FieldDataLink();

	dataLink_->DataChange +=
		new ClassProcedure1<Event*, DataCheckBox>(this,&DataCheckBox::onDataLinkDataChanged,"DataCheckBox::onDataLinkDataChanged");
}

DataCheckBox::~DataCheckBox() {
	dataLink_->free();
}

void DataCheckBox::setDataSource( DataSource* val ) {
	dataLink_->setDataSource( val );
}

void DataCheckBox::setFieldName( const String& name ) {
	dataLink_->setFieldName( name );
}

DataField* DataCheckBox::getField() {
	return dataLink_->getField();
}

void DataCheckBox::onDataLinkDataChanged( Event* e ) {
	setChecked( getField()->getAsBoolean() );
}