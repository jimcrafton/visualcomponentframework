#ifndef _VCF_DATACHECKBOX_H__
#define _VCF_DATACHECKBOX_H__

/**
Copyright 2000-2007 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_CHECKBOXCONTROL_H__
	#include "vcf/ApplicationKit/CheckBoxControl.h"
#endif 





namespace VCF {

class DataSource;
class DataField;
class FieldDataLink;


#define DATACHECKBOX_CLASSID		"330d4fa8-af50-49de-a864-790ca23a7b81"

class DATABASEUIKIT_API DataCheckBox : public CheckBoxControl {
public:
	DataCheckBox();
	virtual ~DataCheckBox();

	void setDataSource( DataSource* val );

	void setFieldName( const String& name );
	DataField* getField();

protected:
	FieldDataLink* dataLink_;

	void onDataLinkDataChanged( Event* e );
};




};

#endif //_VCF_DATACHECKBOX_H__

