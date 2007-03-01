#ifndef _VCF_DATALABEL_H__
#define _VCF_DATALABEL_H__

/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




namespace VCF {

class DataSource;
class DataField;
class FieldDataLink;


#define DATALABEL_CLASSID		"e5c0d189-1b7a-4e33-b7c3-eb9862e6ad7a"

class DATABASEUIKIT_API DataLabel : public Label {
public:
	DataLabel();
	virtual ~DataLabel();

	void setDataSource( DataSource* val );

	void setFieldName( const String& name );
	DataField* getField();

protected:
	FieldDataLink* dataLink_;

	void onDataLinkDataChanged( Event* e );
};




};

#endif //_VCF_DATALABEL_H__

