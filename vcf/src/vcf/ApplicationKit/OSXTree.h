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

	virtual TreeModel* getTreeModel();

	virtual void setTreeModel( TreeModel* model );

    virtual double getItemIndent();

    virtual void setItemIndent( const double& indent );

    virtual ImageList* getImageList();

	virtual void setStateImageList( ImageList* imageList );

    virtual void setImageList( ImageList* imageList );

	virtual void addItem( TreeItem* item );

	virtual void clear();

	virtual Rect getItemImageRect( TreeItem* item );
	
	virtual Rect getItemRect( TreeItem* item );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );

	virtual OSStatus handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent );
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
