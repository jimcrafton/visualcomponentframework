#ifndef _VCF_SIMPLELISTMODEL_H__
#define _VCF_SIMPLELISTMODEL_H__
//SimpleListModel.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_LISTMODEL_H__
#	include "vcf/ApplicationKit/ListModel.h"
#endif // _VCF_LISTMODEL_H__





namespace VCF{

#define SIMPLELISTMODEL_CLASSID			"56c4d2a3-603e-4bc1-9357-5e392a9b8617"

/**
\class SimpleListModel SimpleListModel.h "vcf/ApplicationKit/SimpleListModel.h"
*/
class APPLICATIONKIT_API SimpleListModel : public ListModel {
public:

	SimpleListModel();

	virtual ~SimpleListModel();


	virtual void empty();
	virtual VariantData get( const uint32& index );	
	virtual uint32 getIndexOf( const VariantData& item );
	virtual bool getItems( std::vector<VariantData>& items );
	virtual Enumerator<VariantData>* getItems();
	virtual bool getRange( const uint32& start, const uint32& end, std::vector<VariantData>& items );
	virtual uint32 getCount();

	virtual void copy( Object* source );
protected:
	Array<VariantData> data_;
	virtual bool doInsert( const uint32 & index, const VariantData& item );	
	virtual bool doRemove( const uint32 & index );
	virtual bool doSet( const uint32& index, const VariantData& item );
};

};


#endif // _VCF_SIMPLELISTMODEL_H__

/**
$Id: SimpleListModel.h 3300 2007-12-11 22:46:34Z ddiego $
*/
