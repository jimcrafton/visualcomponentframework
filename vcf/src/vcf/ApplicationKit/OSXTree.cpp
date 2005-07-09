//OSXTree.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"

#include "vcf/ApplicationKit/OSXControl.h"

#include "vcf/ApplicationKit/OSXTree.h"
#include "vcf/ApplicationKit/TreeControl.h"
#include "vcf/ApplicationKit/DefaultTreeItem.h"




#define OSX_TREE_CTRL_PRIMARY_COL		'PRIM'


using namespace VCF;

OSXTree::OSXTree( TreeControl* tree ):
	OSXControl( tree ),
	treeControl_( tree )	
{

}

OSXTree::~OSXTree()
{
	
}

OSStatus OSXTree::DBItemDataCallback( ControlRef browser, DataBrowserItemID item, 
										DataBrowserPropertyID property, DataBrowserItemDataRef itemData,
										Boolean setValue )
{
	OSStatus err = noErr;
	
	if ( !setValue ) {
		switch ( property ) {

			case OSX_TREE_CTRL_PRIMARY_COL : {
				//CFStringRef s = CFStringCreateWithCString( NULL, itemsText[item-BASE_ID], kCFStringEncodingMacRoman );
				//SetDataBrowserItemDataText( itemData, s );
				//CFRelease( s );
				
				TreeItem* treeItem	 = (TreeItem*)item;
				CFTextString tmp;
				tmp = treeItem->getCaption();
				SetDataBrowserItemDataText( itemData, tmp );
			}
			break;
			
			case kDataBrowserItemIsSelectableProperty : {
				err = SetDataBrowserItemDataBooleanValue( itemData, true );
			}
			break;
			
			case kDataBrowserItemIsContainerProperty : {
				TreeItem* treeItem	 = (TreeItem*)item;
				
				SetDataBrowserItemDataBooleanValue( itemData, treeItem->isLeaf() );				
			}
			break;
			
			default: {
				err = errDataBrowserPropertyNotSupported;				
			}
			break;
		}		
	}
	else {
		err = errDataBrowserPropertyNotSupported;
	}
	
	return err;
}


OSStatus OSXTree::DBItemNotificationCallback( ControlRef browser, DataBrowserItemID itemID, 
															DataBrowserItemNotification message)
{
	OSStatus status = noErr;
    switch (message)
    {
        case kDataBrowserContainerOpened: 
// 1
        {           
            /*int i, myItemsPerContainer;
            myItemsPerContainer = myTunesDatabase[itemID].songsInAlbum; 
// 2
 
            DataBrowserItemID myItems [myItemsPerContainer];
            for ( i = 0; i < myItemsPerContainer; i++) 
// 3
                        myItems[i] =  MyGetChild (itemID, i);
            status = AddDataBrowserItems (browser, itemID,
                                    myItemsPerContainer, 
                                    myItems, kTitleColumn); 
// 4
			*/
			//DataBrowserItemID item2 = BASE_ID +1;
			//status = AddDataBrowserItems( browser, BASE_ID, 1, &item2, kDataBrowserItemNoProperty );
	
			TreeItem* treeItem	 = (TreeItem*)itemID;
			OSXTree* tree = (OSXTree*) OSXControl::getControlFromControlRef( browser );
			
			tree->addChildItems( treeItem );
	
            break;  
        }   
		case kDataBrowserItemSelected : {
			SetDataBrowserSelectedItems( browser, 1, &itemID, kDataBrowserItemsAdd );
		}
		break;
		
		case kDataBrowserItemDeselected : {
			SetDataBrowserSelectedItems( browser, 1, &itemID, kDataBrowserItemsRemove );		
		}
		break;
		
    }
    return status;
}

void OSXTree::create( Control* owningControl )
{
	::Rect r;
	r.left = 0;
	r.top = 0;
	r.right = 0;
	r.bottom = 0;
	
	OSStatus err;
	if ( noErr == CreateDataBrowserControl( NULL, &r, kDataBrowserListView, &hiView_ ) ) {
		DataBrowserCallbacks callbacks;
		callbacks.version = kDataBrowserLatestCallbacks;
		err = InitDataBrowserCallbacks( &callbacks ); 	
		callbacks.u.v1.itemDataCallback = OSXTree::DBItemDataCallback;
		callbacks.u.v1.itemNotificationCallback = OSXTree::DBItemNotificationCallback;
		
		err = SetDataBrowserCallbacks( hiView_, &callbacks );
		
		
		//create initial column (DataBrowser doesn't work without at least one column
		DataBrowserListViewColumnDesc col;
		col.propertyDesc.propertyID = OSX_TREE_CTRL_PRIMARY_COL;
		col.propertyDesc.propertyType =  kDataBrowserTextType;
		col.propertyDesc.propertyFlags =  kDataBrowserListViewSelectionColumn;
		
		col.headerBtnDesc.version = kDataBrowserListViewLatestHeaderDesc;
		col.headerBtnDesc.minimumWidth = 10;
		col.headerBtnDesc.maximumWidth = 200;
		col.headerBtnDesc.titleOffset = 0;
		col.headerBtnDesc.titleString = NULL;
		col.headerBtnDesc.initialOrder = kDataBrowserOrderIncreasing;
		col.headerBtnDesc.btnFontStyle.flags = 0;
		col.headerBtnDesc.btnFontStyle.font = 0;
		col.headerBtnDesc.btnFontStyle.size = 0;
		col.headerBtnDesc.btnFontStyle.style = 0;
		col.headerBtnDesc.btnFontStyle.mode = 0;
		col.headerBtnDesc.btnFontStyle.just = 0;
		
		col.headerBtnDesc.btnContentInfo.contentType = kControlContentTextOnly;
		
		AddDataBrowserListViewColumn( hiView_, &col, 0 );
	
		SetDataBrowserListViewDisclosureColumn( hiView_, OSX_TREE_CTRL_PRIMARY_COL, true );
		
		SetDataBrowserSelectionFlags( hiView_, kDataBrowserSelectOnlyOne | kDataBrowserResetSelection );
		
		
		OSXControl* thisPtr = this;
		SetControlProperty( hiView_, 
							VCF_PROPERTY_CREATOR, 
							VCF_PROPERTY_CONTROL_VAL, 
							sizeof(thisPtr), 
							&thisPtr );
							
		err = OSXControl::installStdControlHandler();
							
		if ( err != noErr ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("InstallEventHandler failed for OSXTree!") );
		}
							
	}
	else {
		throw RuntimeException( MAKE_ERROR_MSG_2("CreateDataBrowserControl failed to create view!") );
	}
	
}


TreeModel* OSXTree::getTreeModel()
{
	return NULL;
}

void OSXTree::setTreeModel( TreeModel* model )
{

}

double OSXTree::getItemIndent()
{
	return 0;
}

void OSXTree::setItemIndent( const double& indent )
{
	
}

ImageList* OSXTree::getImageList()
{
	return NULL;
}

void OSXTree::setImageList( ImageList* imageList )
{

	if ( imageList != NULL ) {
		

		EventHandler* imgListHandler = getEventHandler( "OSXTree::onImageListImageChanged" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ImageListEventHandler<OSXTree>(this, &OSXTree::onImageListImageChanged, "OSXTree::onImageListImageChanged" );

		}
		imageList->SizeChanged.addHandler( imgListHandler );
		imageList->ImageAdded.addHandler( imgListHandler );
		imageList->ImageDeleted.addHandler( imgListHandler );
	}
}


void OSXTree::addItem( TreeItem* item )
{
	
}

void OSXTree::clear()
{
	
}


void OSXTree::onImageListImageChanged( ImageListEvent* event )
{
	ulong32 index = event->getIndexOfImage();
	ImageList* imageList = (ImageList*)event->getSource();
	setImageList( imageList );
}

VCF::Rect OSXTree::getItemImageRect( TreeItem* item )
{
	VCF::Rect result;

	return result;
}

void OSXTree::onStateImageListImageChanged( ImageListEvent* event )
{
	ImageList* imageList = (ImageList*)event->getSource();
	setStateImageList( imageList );
}

void OSXTree::setStateImageList( ImageList* imageList )
{
	if ( imageList != NULL ) {	
		EventHandler* imgListHandler = getEventHandler( "OSXTree::onStateImageListImageChanged" );
		if ( NULL == imgListHandler ) {
			imgListHandler =
				new ImageListEventHandler<OSXTree>(this, &OSXTree::onStateImageListImageChanged, "OSXTree::onStateImageListImageChanged" );

		}
		imageList->SizeChanged.addHandler( imgListHandler );
		imageList->ImageAdded.addHandler( imgListHandler );
		imageList->ImageDeleted.addHandler( imgListHandler );
	}
}

bool OSXTree::getAllowLabelEditing()
{
	return false;
}

void OSXTree::setAllowLabelEditing( const bool& allowLabelEditing )
{
	
}

void OSXTree::onControlModelChanged( Event* e )
{
	EventHandler* ev = getEventHandler( "OSXTree::onTreeNodeDeleted" );

	if ( NULL == ev ) {
		ev = new TreeModelEventHandler<OSXTree>( this,
													&OSXTree::onTreeNodeDeleted,
													"OSXTree::onTreeNodeDeleted" );
	}
	
	
	treeControl_->getTreeModel()->addTreeNodeDeletedHandler( ev );
	
	addChildItems( NULL );
}

void OSXTree::onTreeNodeDeleted( TreeModelEvent* event )
{
	TreeItem* item = event->getTreeItem();
	if ( NULL != item ){
		DataBrowserItemID dbParentItem = (DataBrowserItemID)item->getParent();
		DataBrowserItemID dbItem = (DataBrowserItemID)item;
		
		RemoveDataBrowserItems( hiView_, dbParentItem, 1, &dbItem, kDataBrowserItemNoProperty );
	}
}

void OSXTree::addChildItems( TreeItem* parent )
{
	if ( NULL == parent ) {
		//start from the tree model!!!
		
 		TreeModel* treeModel = treeControl_->getTreeModel();
 		Enumerator<TreeItem*>* rootItems = treeModel->getRootItems();		
		while ( rootItems->hasMoreElements() ) {
			TreeItem* item = rootItems->nextElement();
			DataBrowserItemID dbItem = (DataBrowserItemID)item;
			AddDataBrowserItems( hiView_, kDataBrowserNoItem, 1, 
										&dbItem, kDataBrowserItemNoProperty );	
										
			addChildItems( item );
		}
	}
	else {
		uint32 count = parent->getChildCount();
		if ( count > 0 ) {
			Enumerator<TreeItem*>* children = parent->getChildren();
			while ( children->hasMoreElements() ) {
				TreeItem* child = children->nextElement();
				
				//use the child's pointer address as the item ID
				DataBrowserItemID dbItem = (DataBrowserItemID)child;
				
				AddDataBrowserItems( hiView_, (DataBrowserItemID)parent, 1, 
										&dbItem, kDataBrowserItemNoProperty );	
				
				addChildItems( child );
			}
		}
	}
}

OSStatus OSXTree::handleOSXEvent( EventHandlerCallRef nextHandler, EventRef theEvent )
{
	OSStatus result = eventNotHandledErr;
	
    UInt32 whatHappened = GetEventKind (theEvent);
	TCarbonEvent event( theEvent );
	
	switch ( GetEventClass( theEvent ) )  {				 
		case kEventClassControl : {
			switch( whatHappened ) {
				case kEventControlDraw : {
					result = CallNextEventHandler( nextHandler, theEvent );
				}
				break;
				
				default : {
					result = OSXControl::handleOSXEvent( nextHandler, theEvent );
				}	
				break;
			}
		}
		break;
		
		default : {
			result = OSXControl::handleOSXEvent( nextHandler, theEvent );
		}	
		break;
	}
	
	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.5  2005/07/07 23:28:58  ddiego
*last osx checkins before release - not complete :(
*
*Revision 1.1.2.4  2005/06/29 03:46:13  ddiego
*more osx tree and list coding.
*
*Revision 1.1.2.3  2005/06/28 04:03:36  ddiego
*osx text edit mods and started on osx tree peer.
*
*Revision 1.1.2.2  2005/06/23 01:26:55  ddiego
*build updates
*
*Revision 1.1.2.1  2005/06/22 03:59:30  ddiego
*added osx stub classes for peers
*
*/


