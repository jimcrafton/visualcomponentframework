#ifndef _VCF_TREEPEER_H__
#define _VCF_TREEPEER_H__
//TreePeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#ifndef _VCF_TREEMODEL_H__
	#include "vcf/ApplicationKit/TreeModel.h"
#endif


namespace VCF{

class ImageList;
class ColumnModel;

/**
\class TreePeer TreePeer.h "vcf/ApplicationKit/TreePeer.h"  
*/

class APPLICATIONKIT_API TreePeer : public VCF::Interface {
public:
	virtual ~TreePeer(){};

    virtual double getItemIndent() = 0;

    virtual void setItemIndent( const double& indent ) = 0;

    virtual ImageList* getImageList() = 0;

    virtual void setImageList( ImageList* imageList ) = 0;

	virtual void setStateImageList( ImageList* imageList ) = 0;

	virtual Rect getItemImageRect( const TreeModel::Key& itemKey ) = 0;

	virtual Rect getItemRect( const TreeModel::Key& itemKey ) = 0;

	virtual TreeModel::Key hitTest( const Point& pt ) = 0;

	virtual bool getAllowLabelEditing() = 0;

	virtual void setAllowLabelEditing( const bool& allowLabelEditing ) = 0;

	/**
	Pass in a null column model to disable the header, 
	other wise it's enabled and made visible
	*/
	virtual void enableHeader( const bool& val ) = 0;
};

};


#endif // _VCF_TREEPEER_H__

/**
$Id$
*/
