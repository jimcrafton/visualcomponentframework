#ifndef _VCF_TREECONTROL_H__
#define _VCF_TREECONTROL_H__
//TreeControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */




#ifndef _VCF_TREEMODEL_H__
#	include "vcf/ApplicationKit/TreeModel.h"
#endif // _VCF_TREEMODEL_H__

#ifndef _VCF_TREEITEM_H__
#	include "vcf/ApplicationKit/TreeItem.h"
#endif // _VCF_TREEITEM_H__

#ifndef _VCF_TREEMODELEVENT_H__
#	include "vcf/ApplicationKit/TreeModelEvent.h"
#endif // _VCF_TREEMODELEVENT_H__




namespace VCF {


class TreePeer;
class TreeItem;
class ImageList;

class ModelEvent;


#define TREECONTROL_CLASSID			"ED88C09C-26AB-11d4-B539-00C04F0196DA"

#define TREEITEM_SELECTED	CUSTOM_EVENT_TYPES + ITEM_CONST + 20
#define TREEITEM_EXPANDED	CUSTOM_EVENT_TYPES + ITEM_CONST + 21

/**
\class TreeControl TreeControl.h "vcf/ApplicationKit/TreeControl.h" 
*/
class APPLICATIONKIT_API TreeControl : public VCF::Control {
public:

	TreeControl();
	virtual ~TreeControl();


	enum TreeControlEvents {
		ITEM_STATECHANGE_REQUESTED = CUSTOM_EVENT_TYPES + ITEM_CONST + 10
	};

	DELEGATE(ItemDelegate,ItemSelected);
	DELEGATE(ItemDelegate,ItemStateChangeRequested);
	DELEGATE(ItemDelegate,ItemExpanded);

	virtual void handleEvent( Event* event );

	double getItemIndent();

	void setItemIndent( const double& indent );

	void setTreeModel(TreeModel * model);

	TreeModel* getTreeModel();

	ImageList* getImageList();

	ImageList* getStateImageList();

	void setImageList( ImageList* imageList );

	void setStateImageList( ImageList* imageList );

	virtual void paint( GraphicsContext * context );

	void init();

	TreeItem* findItem( Point* pt );

	void addItem( TreeItem* parent, TreeItem* item );

	TreeItem* addItem( TreeItem* parent, const String& caption=L"", const uint32 imageIndex=0 );

	void removeItem( TreeItem* item );

	TreeItem* getSelectedItem();

	Rect getItemImageRect( TreeItem* item );

	Rect getItemRect( TreeItem* item );

	bool getAllowLabelEditing();

	void setAllowLabelEditing( const bool& allowLabelEditing );
protected:
	TreeItem* hitTestForItem( Point* pt, TreeItem* item );

	void onTreeItemPaint( ItemEvent* event );

	void onTreeRootNodeChanged( TreeModelEvent* event );

	void onTreeNodeAdded( TreeModelEvent* event );

	void onTreeNodeDeleted( TreeModelEvent* event );

	void onModelEmptied( ModelEvent* event );


	TreePeer * treePeer_;
	ImageList* imageList_;
	ImageList* stateImageList_;
	TreeModel* treeModel_;
	TreeItem* currentSelectedItem_;


};

}; //namespace VCF


#endif // _VCF_TREECONTROL_H__

/**
$Id$
*/
