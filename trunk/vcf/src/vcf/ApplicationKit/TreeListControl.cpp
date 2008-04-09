//TreeListControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/TreeListControl.h"
#include "vcf/ApplicationKit/TreeListModel.h"
#include "vcf/ApplicationKit/TreeItem.h"
#include "vcf/ApplicationKit/TreePeer.h"



using namespace VCF;


#define EXPANDER_SPACER		5.0




TreeListControl::TreeListControl():
	TreeControl(NULL),	
	allowLabelEditing_(false),
	currentEditColumn_(-1),
	currentEditingControl_(NULL)
{
	setTreeModel( new TreeListModel() );

	addComponent( getViewModel() );

	columnModel_ = new ColumnModel();

	CallBack* ev = 
			new ClassProcedure1<Event*,TreeListControl>( this, &TreeListControl::onEditorFocusLost, "TreeListControl::onEditorFocusLost" );

	ev = new ClassProcedure1<KeyboardEvent*,TreeListControl>( this, &TreeListControl::onEditingControlKeyPressed, "TreeListControl::onEditingControlKeyPressed" );



	ev = new ClassProcedure1<ListModelEvent*,TreeListControl>( this, &TreeListControl::onColumnItemAdded, "TreeListControl::onColumnItemAdded" );
	columnModel_->ItemAdded += ev;

	ev = new ClassProcedure1<ListModelEvent*,TreeListControl>( this, &TreeListControl::onColumnItemDeleted, "TreeListControl::onColumnItemDeleted" );
	columnModel_->ItemRemoved += ev; 
}

TreeListControl::~TreeListControl()
{

}


Rect TreeListControl::getBoundsForEdit( TreeItem* item, int column )
{
	Rect result;

	if ( column == -1 ) {
		return result;
	}


	ColumnModel* cm = getColumnModel();
/*	Enumerator<ColumnItem*>* columnItems = cm->getItems();

	result = *item->getBounds();

	int index = 0;
	while ( columnItems->hasMoreElements() ) {
		ColumnItem* col = columnItems->nextElement();
		result.right_ = result.left_ + col->getWidth();

		if ( index == column ) {

			if ( 0 == column ) {
				//adjust for state and image icons
				Rect expanderRect = getExpanderRect( item );
		
				if ( !item->isLeaf() ) {
					result.left_ = expanderRect.right_;
				}

				Rect stateRect = getStateRect( item, getCurrentIndent( item ) );

				if ( !stateRect.isEmpty() && !stateRect.isNull() ) {
					result.left_ = maxVal<>( stateRect.right_, result.left_ );
				}
			}

			//adjust for scrollers
			Scrollable* scrollable = getScrollable();
			if ( NULL != scrollable ) {
				result.offset( -scrollable->getHorizontalPosition(), -scrollable->getVerticalPosition());
				Rect clientBounds = getClientBounds();
				double w = clientBounds.getWidth();
				double h = clientBounds.getHeight();

				if ( scrollable->isVerticalScrollbarVisible() ) {
					result.right_ = minVal<>( result.right_, 
											w - scrollable->getVerticalScrollbarWidth() );
				}
				
				if ( scrollable->isHorizontalScrollbarVisible() ) {
					result.bottom_ = minVal<>( result.bottom_, 
											h - scrollable->getHorizontalScrollbarHeight() );
				}
			}

			break;
		}
		result.left_ += col->getWidth();
		index++;
	}
	*/

	return result;
}

int TreeListControl::hitTestForEditColumn( const Point& pt )
{
	int result = -1;

	TreeItem* item = NULL;//hitTest( pt );
	if ( NULL != item ) {
		if ( item->getSubItemCount() > 0 ) {

			result = 0;
				 
			ColumnModel* cm = getColumnModel();
			/*
			Enumerator<ColumnItem*>* columnItems = cm->getItems();

			Rect subItemRect = *item->getBounds();
			subItemRect.right_ = subItemRect.left_ + cm->getItemFromIndex( 0 )->getWidth();

			if ( !subItemRect.containsPt( pt ) ) {
				subItemRect.left_ += cm->getItemFromIndex( 0 )->getWidth();
				result ++;


				bool found = false;
				Enumerator<TreeSubItem*>* subItems = item->getSubItems();
				while ( columnItems->hasMoreElements() && subItems->hasMoreElements() ) {
					TreeSubItem* subItem = subItems->nextElement();
					ColumnItem* column = columnItems->nextElement();				
					
					subItemRect.right_ = subItemRect.left_ + column->getWidth();
					
					if ( subItemRect.containsPt( pt ) ) {
						found = true;
						break;
					}
					
					subItemRect.left_ += column->getWidth();
					
					result++;
				}
				
				if ( !found ) {
					result = -1;
				}
			}
			*/
		}
		else {
			result = 0;
		}
	}

	return result;
}

void TreeListControl::keyDown( KeyboardEvent* e )
{
	TreeControl::keyDown( e );

	switch( e->getVirtualCode() ) {
		case vkReturn : {

			//editCell( clickCell_, Point() );

		}
		break;
	}
}

void TreeListControl::mouseDown( MouseEvent* event )
{
	TreeControl::mouseDown( event );

	finishEditing();

//	draggingSelectionRect_ = false;
//	Point pt = *event->getPoint();
//	draggingSelectedItems_.clear();	

	if ( event->hasLeftButton() ) {
//		allowMultipleSelection_ = (event->hasControlKey()  || event->hasShiftKey() );
		//setAllowsMultipleSelection(  );

//		if ( allowMultipleSelection_ ) {
//			multiSelectionChange( event );
//		}
//		else {
//			singleSelectionChange( event );
//		}
	}	
}




/*
bool TreeListControl::getAllowLabelEditing()
{
	return allowLabelEditing_;
}

void TreeListControl::setAllowLabelEditing( const bool& allowLabelEditing )
{
	allowLabelEditing_ = allowLabelEditing;
}


void TreeListControl::showColumnHeader( const bool& show )
{
	
}


double TreeListControl::getColumnWidth( const uint32& index )
{
	return result;
}

void TreeListControl::setColumnWidth( const uint32& index, const double& width )
{
	
}
*/

void TreeListControl::onEditingControlKeyPressed( KeyboardEvent* event ) 
{
	switch ( event->getVirtualCode() ) {
		case vkEscape : {
			cancelEditing();
		}
		break;

		case vkReturn : {
			event->setConsumed( true );
			finishEditing();
		}
		break;

		case vkDownArrow : case vkUpArrow : {
			setFocused(); // this will kill the edit
			
			
			KeyboardEvent* event2 =
				new KeyboardEvent( this, event->getType(),
				event->getRepeatCount(),
				event->getKeyMask(),
				event->getKeyValue(),
				event->getVirtualCode() );
			
			handleEvent( event2 );
			
			delete event2;	
			
			TreeItem* item = getSelectedItem();
			if ( NULL != item ) {
				editItem( item, NULL );
			}
		}
		break;
	}
}

bool TreeListControl::finishEditingFromFocusLoss( Control* lostFocusCtrl, Control* currentFocusedCtrl )
{
	bool result = true;
	Control* parent = currentFocusedCtrl->getParent();
	while ( NULL != parent ) {
		if ( currentEditingControl_ == parent ) {
			//skip function, we don't need to do anything
			//at all!
			result = false; 
			break;
		}
		parent = parent->getParent();
	}

	return result;
}

void TreeListControl::onEditorFocusLost( Event* e ) 
{
	Control* control = (Control*)e->getSource();

	//check to see if we have lost focus because
	//we have clicked on a child control of the 
	//currentEditingControl_
	Control* currentFocused = Control::getCurrentFocusedControl();

	if ( finishEditingFromFocusLoss( control, currentFocused ) ) {
		finishEditing();
	}	
}

void TreeListControl::postFinishedEditing( Event* e ) 
{		
	Control* editControl = (Control*) e->getUserData();

	//remove( editControl );
	removeComponent( editControl );
	editControl->free();
	repaint();		
}

void TreeListControl::cancelEditing() 
{
	finishEditing( false );
}

void TreeListControl::finishEditing( bool applyEdit ) 
{
	if ( NULL == currentEditingControl_ ) {
		return;
	}

	if ( applyEdit ) {
		
		TreeItem* item = getSelectedItem();
		finishEditingItem( item, currentEditingControl_ );
		
	}

	EventHandler* ev = (EventHandler*)getCallback( "TreeListControl::postFinishedEditing" );
	if ( NULL == ev ) {
		ev = 
			new ClassProcedure1<Event*,TreeListControl>( this, &TreeListControl::postFinishedEditing, "TreeListControl::postFinishedEditing" );
	}

	Event* e = new Event( this );
	e->setUserData( currentEditingControl_ );
	UIToolkit::postEvent( ev, e, false );
	currentEditingControl_ = NULL;
}

void TreeListControl::editItem( TreeItem* item, Point* point ) {
	if ( NULL != currentEditingControl_ ) {
		finishEditing();
	}
	currentEditingControl_ = NULL;
	
	if ( NULL != point ) {
		currentEditColumn_ = hitTestForEditColumn( *point );			
	}
	
	Rect bounds = getBoundsForEdit( item, currentEditColumn_ );
	
	if ( currentEditColumn_ != -1 ) {
		Control* editor = createEditor( item, currentEditColumn_ );
		
		if ( NULL != editor ) {			
			editor->setBounds( &bounds );
			CallBack* ev = getCallback( "TreeListControl::onEditorFocusLost" );
			editor->FocusLost += ev;

			ev = getCallback( "TreeListControl::onEditingControlKeyPressed" );
			editor->KeyDown += ev;
			
//			add( editor );

			editor->setVisible( true );
			editor->setFocused();	
			
			currentEditingControl_ = editor;
		}
	}		
}



void TreeListControl::handleEvent( Event* event )
{
	TreeControl::handleEvent( event );
	switch ( event->getType() ) {
		case Component::COMPONENT_ADDED : {
			ComponentEvent* ev = (ComponentEvent*)event;
			Component* child = ev->getChildComponent();
			ColumnItem* columnItem = dynamic_cast<ColumnItem*>(child);
			if ( !inCallbackChange_ && (NULL != columnItem) ) {
				controlChangeToModel_ = true;
				
				ColumnModel* cm = getColumnModel();
				VCF_ASSERT(cm != NULL);
				
				if ( NULL != cm ) {
					columnItem->setControl( this );
					columnItem->setModel( cm );
					
					
					cm->add("");
					
					columnItem->setIndex( cm->getCount()-1 );
					columnItems_.insert( columnItems_.begin() + columnItem->getIndex(), columnItem );	
				}
				
				controlChangeToModel_ = false;
			}
		}
		break;

		case Component::COMPONENT_REMOVED : {
			
		}
		break;

	}
}



ColumnItem* TreeListControl::getColumnItem( const uint32& index )
{
	ColumnItem* result = NULL;
	
	if ( index < columnItems_.size() ) {
		result = columnItems_[index];
	}
	
	return result;
}

void TreeListControl::insertItemSubItem( TreeItem* item, const uint32& index, TreeSubItem* subItem ) {
	uint32 count = getItemSubItemCount(item);	
	
	if ( count == index ) {
		SubItemPair val(item,subItem);
		subItems_.insert( val );
	}
	else {
		SubItemIteratorPair res = subItems_.equal_range( item );
		SubItemMap::iterator r1 = res.first;
		SubItemMap::iterator r2 = res.second;
		
		std::vector<TreeSubItem*> items;
		while ( res.first != res.second ) {
			items.push_back(res.first->second);
			++res.first;
		}
		
		items.insert( items.begin() + index, subItem );
		
		std::vector<TreeSubItem*>::iterator it = items.begin();
		while ( it != items.end() ) {
			SubItemPair val(item,*it);
			subItems_.insert( val );
			++it;
		}
	}
}

void TreeListControl::removeItemSubItem( TreeItem* item, TreeSubItem* subItem ) {
	SubItemIteratorPair res = subItems_.equal_range( item );
	while ( res.first != res.second ) {
		if ( res.first->second == subItem ) {
			subItems_.erase( res.first );
			break;
		}
		++res.first;
	}
}

bool TreeListControl::getItemSubItems( TreeItem* item, std::vector<TreeSubItem*>& subItems ) {
	SubItemIteratorPair res = subItems_.equal_range( item );
	
	while ( res.first != res.second ) {
		subItems.push_back(res.first->second);
		++res.first;
	}

	return !subItems.empty();
}

TreeSubItem* TreeListControl::getItemSubItem( TreeItem* item, const uint32& index ) {
	TreeSubItem* result = NULL;
	
	SubItemIteratorPair res = subItems_.equal_range( item );
	
	uint32 si = 0;
	while ( res.first != res.second ) {
		if ( si == index ) {			
			result = res.first->second;
			break;
		}
		si ++;
		++res.first;
	}
	
	return result;
}

uint32 TreeListControl::getItemSubItemCount( TreeItem* item ) {
	uint32 result = 0;
	SubItemIteratorPair res = subItems_.equal_range( item );
	
	while ( res.first != res.second ) {
		result ++;
		++res.first;
	}
	return result;
}

bool TreeListControl::subItemExists( const TreeModel::Key& key, const uint32& subItemIndex ) {
	bool result = false;
	
	if ( itemExists( key ) ) {
		TreeItem* item = getItemFromKey( key );
		SubItemIteratorPair res = subItems_.equal_range( item );
		
		uint32 si = 0;
		while ( res.first != res.second ) {
			if ( si == subItemIndex ) {			
				result = true;
				break;
			}
			si ++;
			++res.first;
		}
	}
	
	return result;
}


double TreeListControl::getItemWidth( ColumnItem* item ) 
{
	return treePeer_->getColumnWidth( item->getIndex() );
}

void TreeListControl::setItemWidth( ColumnItem* item, const double& val ) 
{
	treePeer_->setColumnWidth( item->getIndex(), val );
}

TextAlignmentType TreeListControl::getItemTextAlignment( ColumnItem* item ) 
{
	return treePeer_->getColumnTextAlignment( item->getIndex() );
}

void TreeListControl::setItemTextAlignment( ColumnItem* item, const TextAlignmentType& val ) 
{
	treePeer_->setColumnTextAlignment( item->getIndex(), val );
}

void TreeListControl::onColumnItemAdded( ListModelEvent* event )
{
	if ( controlChangeToModel_ ) {
		return;
	}
	
	inCallbackChange_ = true;
	ColumnItem* item = new ColumnItem();
	item->setControl( this );
	item->setModel( getColumnModel() );
	item->setIndex( event->index );
	addComponent( item );
	columnItems_.insert( columnItems_.begin() + event->index, item );
	
	inCallbackChange_ = false;
}

void TreeListControl::onColumnItemDeleted( ListModelEvent* event )
{
	inCallbackChange_ = true;
	
	ColumnItem* item = this->getColumnItem( event->index );
	
	columnItems_.erase( columnItems_.begin() + event->index );
	
	removeComponent( item );
	
	item->free();
	
	inCallbackChange_ = false;
}

/**
$Id$
*/
