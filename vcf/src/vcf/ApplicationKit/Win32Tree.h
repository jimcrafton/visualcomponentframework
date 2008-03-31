#ifndef _VCF_WIN32TREE_H__
#define _VCF_WIN32TREE_H__
//Win32Tree.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/TreePeer.h"

#ifndef _VCF_TREEMODEL_H__
#	include "vcf/ApplicationKit/TreeModel.h"
#endif // _VCF_TREEMODEL_H__

namespace VCF {

class TreeModelEvent;
class ImageListEvent;

class Win32Tree : public AbstractWin32Component, public TreePeer  {
public:
	Win32Tree( TreeControl* tree );

	virtual ~Win32Tree();

	virtual void create( Control* owningControl );
	
    virtual double getItemIndent();

    virtual void setItemIndent( const double& indent );

    virtual ImageList* getImageList();

	virtual void setStateImageList( ImageList* imageList );

    virtual void setImageList( ImageList* imageList );	

	virtual Win32Object::CreateParams createParams();

	virtual Rect getItemImageRect( const TreeModel::Key& itemKey );

	virtual Rect getItemRect( const TreeModel::Key& itemKey );

	virtual TreeModel::Key hitTest( const Point& pt );

	virtual bool getAllowLabelEditing();

	virtual void setAllowLabelEditing( const bool& allowLabelEditing );

	virtual bool handleEventMessages( UINT message, WPARAM wParam, LPARAM lParam, LRESULT& wndProcResult, WNDPROC defaultWndProc = NULL);
private:

	TreeControl* treeControl_;
	std::map<TreeModel::Key,HTREEITEM> treeItems_;
	HIMAGELIST imageListCtrl_;
	HIMAGELIST stateImageListCtrl_;
	GraphicsContext* currentCtx_;
	bool internalTreeItemMod_;
	void onImageListImageChanged( ImageListEvent* event );
	void onStateImageListImageChanged( ImageListEvent* event );

	void onControlModelChanged( Event* e );
	void onItemExpanded( ItemEvent* e );
	void onItemSelected( ItemEvent* e );
	void onTreeModelChanged( ModelEvent* event );
	void addTreeItem( TreeModel::Key key, HTREEITEM parent );
};

};


#endif // _VCF_WIN32TREE_H__

/**
$Id$
*/
