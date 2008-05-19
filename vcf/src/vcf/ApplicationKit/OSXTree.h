#ifndef _VCF_OSXTREE_H__
#define _VCF_OSXTREE_H__
//OSXTree.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/




#include "vcf/ApplicationKit/TreePeer.h"

#ifndef _VCF_TREEMODEL_H__
#	include "vcf/ApplicationKit/TreeModel.h"
#endif // _VCF_TREEMODEL_H__

namespace VCF {

class TreeModelEvent;
class ImageListEvent;

class OSXTree : public OSXControl, public TreePeer  {
public:
	OSXTree( TreeControl* tree );

	virtual ~OSXTree();

	virtual void create( Control* owningControl );

	virtual double getItemIndent();

    virtual void setItemIndent( const double& indent );

	virtual void setStateImageList( ImageList* imageList );

    virtual void setImageList( ImageList* imageList );	

	virtual void setHeaderImageList( ImageList* imageList );

	virtual Rect getItemImageRect( const TreeModel::Key& itemKey );

	virtual Rect getItemRect( const TreeModel::Key& itemKey );

	virtual TreeModel::Key hitTest( const Point& pt );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );

	virtual void enableHeader( const bool& val );

	virtual void setColumnWidth( const uint32& index, const double& width, ColumnAutosizeType type );

	virtual double getColumnWidth( const uint32& index );

	virtual TextAlignmentType getColumnTextAlignment( const uint32& index );

	virtual void setColumnTextAlignment( const uint32& index, const TextAlignmentType& val );

	virtual void setDisplayOptions( uint32 displayOptions );

protected:
	
	TreeControl* treeControl_;

	void onImageListImageChanged( ImageListEvent* event );
	void onStateImageListImageChanged( ImageListEvent* event );
	void onControlModelChanged( Event* e );
	void onTreeNodeDeleted( TreeModelEvent* event );
	
	void addChildItems( TreeItem* parent );
	
	static OSStatus DBItemDataCallback( ControlRef browser, DataBrowserItemID item, 
										DataBrowserPropertyID property, DataBrowserItemDataRef itemData,
										Boolean setValue );
										
	static void DBItemNotificationCallback( ControlRef browser, DataBrowserItemID itemID, 
															DataBrowserItemNotification message);

};

};


#endif // _VCF_OSXTREE_H__

/**
$Id$
*/
