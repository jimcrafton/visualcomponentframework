//DefaultTreeItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultTreeItem.h"
#include "vcf/ApplicationKit/TreeModel.h"

using namespace VCF;

DefaultTreeItem::DefaultTreeItem():
	treeModel_(NULL)
{
	init();
}

DefaultTreeItem::DefaultTreeItem( const String& caption ):
	treeModel_(NULL)
{
	init();
	caption_ = caption;
}

DefaultTreeItem::DefaultTreeItem( const String& caption, Control* owningControl, TreeModel* model ):
	treeModel_(NULL)
{
	init();
	owningControl_ = owningControl;
	treeModel_ = dynamic_cast<Model*>(model);
	setCaption( caption );
}

DefaultTreeItem::~DefaultTreeItem()
{
	std::vector<TreeItem::SubItem*>::iterator subIt = subItems_.begin();
	while ( subIt != subItems_.end() ) {
		(*subIt)->release();
		subIt++;
	}
	subItems_.clear();

	std::vector<TreeItem*>::iterator it = childNodeItems_.begin();
	while ( it != childNodeItems_.end() ){
		delete *it;
		it++;
	}
	childNodeItems_.clear();
}

void DefaultTreeItem::init()
{
	imageIndex_ = 0;
	isExpanded_ = false;
	tag_ = -1;
	selectedImageIndex_ = -1;
	expandedImageIndex_ = -1;
	stateImageIndex_ = -1;

	selected_ = false;

	state_ = Item::idsNone;

	bounds_.setRect(0.0,0.0,0.0,0.0);
	owningControl_ = NULL;
	caption_ = "";
	childNodeItems_.clear();
	parent_ = NULL;
	textBold_ = false;
	TextColor_.setRGB( 0.0, 0.0, 0.0 );
	userData_ = NULL;
	enumContainer_.initContainer( childNodeItems_ );

	enumSubItemsContainer_.initContainer( subItems_ );

}

bool DefaultTreeItem::containsPoint( Point * pt )
{
	return bounds_.containsPt( pt );
}


unsigned long DefaultTreeItem::getIndex()
{
	return index_;
}

void DefaultTreeItem::setIndex( const unsigned long& index )
{
	index_ = index;
}

void* DefaultTreeItem::getData()
{
	return userData_;
}

void DefaultTreeItem::setData( void* data )
{
	userData_ = data;
	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}

Color* DefaultTreeItem::getTextColor()
{
	return &TextColor_;
}

void DefaultTreeItem::setTextColor(Color* color)
{
	TextColor_ = *color;
	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}

void DefaultTreeItem::setTextBold(const bool& bold)
{
	textBold_ = bold;
	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}

bool DefaultTreeItem::getTextBold()
{
	return textBold_;
}

bool DefaultTreeItem::isRoot()
{
	return ( NULL == parent_ );
}

bool DefaultTreeItem::isLeaf()
{
	return  childNodeItems_.empty();
}

TreeItem* DefaultTreeItem::getParent()
{
	return parent_;
}

void DefaultTreeItem::setParent( TreeItem* parent )
{
	parent_ = parent;
	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}

TreeItem* DefaultTreeItem::getNextChildNodeItem()
{
	if ( NULL != parent_ ) {
		DefaultTreeItem* dtParent = dynamic_cast<DefaultTreeItem*>(parent_);
		if ( NULL != dtParent ) {
			std::vector<TreeItem*>::iterator it = std::find( dtParent->childNodeItems_.begin(),
															 dtParent->childNodeItems_.end(),
															 this );

			it ++;
			if ( it != dtParent->childNodeItems_.end() ) {
				return *it;
			}
		}
	}
	return NULL;
}

TreeItem* DefaultTreeItem::getPrevChildNodeItem()
{
	if ( NULL != parent_ ) {
		DefaultTreeItem* dtParent = dynamic_cast<DefaultTreeItem*>(parent_);
		if ( (NULL != dtParent) && (index_ > 0) ) {
			std::vector<TreeItem*>::iterator it = std::find( dtParent->childNodeItems_.begin(),
															 dtParent->childNodeItems_.end(),
															 this );
			it --;

			if ( (it != dtParent->childNodeItems_.end()) && ( it >= dtParent->childNodeItems_.begin() ) ) {
				return *it;
			}
		}
	}
	return NULL;
}

String DefaultTreeItem::getCaption()
{
	return caption_;
}

void DefaultTreeItem::setCaption( const String& caption )
{
	caption_ = caption;

	changed( ITEM_EVENT_TEXT_CHANGED );
}

Enumerator<TreeItem*>* DefaultTreeItem::getChildren()
{
	return enumContainer_.getEnumerator();
}

void DefaultTreeItem::addChild( TreeItem* child )
{
//	StringUtils::trace( "Adding child " + child->getCaption() + "\n" );
	childNodeItems_.push_back( child );
	child->setParent( this );
	ItemEvent event( this, ITEM_EVENT_ADDED );
	ItemAdded.fireEvent( &event );
}

void DefaultTreeItem::insertChild( const unsigned long& index, TreeItem* child )
{
	std::vector<TreeItem*>::iterator it = childNodeItems_.begin();
	childNodeItems_.insert( it + index, child );
	child->setParent( this );
	ItemEvent event( this, ITEM_EVENT_ADDED );
	ItemAdded.fireEvent( &event );
	it = childNodeItems_.begin() + index;
	int i = index;
	while ( it != childNodeItems_.end() ) {
		TreeItem* item = *it;
		item->setIndex( i );
		it ++;
		i++;
	}
}

void DefaultTreeItem::deleteChild( TreeItem* child )
{
	std::vector<TreeItem*>::iterator found = std::find( childNodeItems_.begin(), childNodeItems_.end(), child );
	if ( found != childNodeItems_.end() ) {
		int index = found - childNodeItems_.begin();
		TreeItem* item = *found;
		ItemEvent event( child, ITEM_EVENT_DELETED );
		ItemDeleted.fireEvent( &event );
		delete item;
		item = NULL;
		childNodeItems_.erase ( found );
		int i = index;
		std::vector<TreeItem*>::iterator it = childNodeItems_.begin() + index;
		while ( it != childNodeItems_.end() ) {
			item = *it;
			item->setIndex( i );
			it ++;
			i ++;
		}
	}
}

void DefaultTreeItem::deleteChildAtIndex( const unsigned long& index )
{
	std::vector<TreeItem*>::iterator found =  childNodeItems_.begin() + index;
	if ( found != childNodeItems_.end() ) {
		TreeItem* item = *found;
		ItemEvent event( item, ITEM_EVENT_DELETED );
		ItemDeleted.fireEvent( &event );
		childNodeItems_.erase ( found );
		delete item;
		item = NULL;
		int i = index;
		std::vector<TreeItem*>::iterator it = childNodeItems_.begin() + index;
		while ( it != childNodeItems_.end() ) {
			item = *it;
			item->setIndex( i );
			it ++;
			i ++;
		}
	}
}

void DefaultTreeItem::clearChildren()
{
	for (std::vector<TreeItem*>::iterator it = childNodeItems_.begin(); it != childNodeItems_.end(); it ++ ){
		TreeItem* item = *it;
		item->clearChildren();
		ItemEvent deleteEvent( item, ITEM_EVENT_DELETED );
		ItemDeleted.fireEvent( &deleteEvent );
		delete item;
	}
	childNodeItems_.clear();

	ItemEvent event( this );
	ItemChanged.fireEvent( &event );
}

Model* DefaultTreeItem::getModel()
{
	return treeModel_;
}

void DefaultTreeItem::setModel( Model* model )
{
	treeModel_ = model;
	for (std::vector<TreeItem*>::iterator it = childNodeItems_.begin(); it != childNodeItems_.end(); it ++ ){
		(*it)->setModel( model );
	}
}

void DefaultTreeItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;

	ItemEvent event( this, context );
	ItemPaint.fireEvent( &event );
}

bool DefaultTreeItem::isSelected()
{
	return selected_;
}

void DefaultTreeItem::setSelected( const bool& selected )
{
	selected_ = selected;
	ItemEvent event( this, ITEM_EVENT_SELECTED );
	ItemSelected.fireEvent( &event );
}

void DefaultTreeItem::expand( const bool& isExpanded )
{
	isExpanded_ = isExpanded;
	changed( DefaultTreeItem::teItemExpanded );
}

ulong32 DefaultTreeItem::getLevel()
{
	ulong32 result = 0;

	if ( false == isRoot() ) {
		TreeItem* parent = getParent();
		if ( NULL != parent ) {
			result = parent->getLevel();
			result ++;
		}
	}
	return result;
}

void DefaultTreeItem::setControl( Control* control )
{
	owningControl_ = control;
	std::vector<TreeItem*>::iterator it = childNodeItems_.begin();
	while ( it != childNodeItems_.end() ){
		TreeItem* item = *it;
		item->setControl( owningControl_ );
		it++;
	}
}

void DefaultTreeItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
}

void DefaultTreeItem::setSelectedImageIndex( const long& selectedImageIndex )
{
	selectedImageIndex_ = selectedImageIndex;
	changed( ITEM_EVENT_CHANGED );
}

void DefaultTreeItem::setExpandedImageIndex( const long& expandedImageIndex )
{
	expandedImageIndex_ = expandedImageIndex;
	changed( ITEM_EVENT_CHANGED );
}

void DefaultTreeItem::setState( const long& state )
{
	state_ = state;
	//ItemEvent event( this, ITEM_EVENT_CHANGED );
	//ItemChanged( &event );
}

void DefaultTreeItem::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
}

void DefaultTreeItem::setStateImageIndex( const long& index )
{
	stateImageIndex_ = index;
	changed( ITEM_EVENT_CHANGED );
}

void DefaultTreeItem::addSubItem( const String& caption, void* data )
{
	SubItem* subItem = new SubItem(this);
	subItems_.push_back( subItem );
	subItem->setCaption( caption );

	changed( ITEM_EVENT_CHANGED );
}

void DefaultTreeItem::addSubItem( TreeItem::SubItem* subItem )
{
	subItems_.push_back( subItem );

	changed( ITEM_EVENT_CHANGED );
}

void DefaultTreeItem::removeSubItem( const ulong32& index )
{
	std::vector<SubItem*>::iterator found = subItems_.begin() + index;
	if ( found != subItems_.end() ) {
		changed( ITEM_EVENT_CHANGED );

		subItems_.erase( found );
	}
}

TreeItem::SubItem* DefaultTreeItem::getSubItem( const ulong32& index )
{
	SubItem* result = NULL;
	if ( index < subItems_.size() ) {
		result = subItems_[index];
	}
	return result;
}

void DefaultTreeItem::subItemChanged( TreeItem::SubItem* item )
{

}

void DefaultTreeItem::changed( const ulong32& eventType )
{
	if ( NULL != treeModel_ ) {
		treeModel_->updateAllViews();
	}
	else {

		//throw InvalidPointerException( MAKE_ERROR_MSG_2("This tree item has no model!") );
	}
	ItemEvent event( this, eventType );
	ItemChanged.fireEvent( &event );
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2.2.1  2004/09/09 04:42:04  ddiego
*fixed some custom draw bugs in win32 tree control. updated
*advanced ui example.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.32  2004/04/03 16:09:31  ddiego
*Found some more merge issues that needing resolving.
*
*Revision 1.31  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.30.2.3  2003/09/22 01:48:04  ddiego
*some minor additions ot teh DropTarget to allow it to have multiple
*control targets
*also a few other misc fixes
*
*Revision 1.30.2.2  2003/09/17 21:22:55  ddiego
*added adjustmnents to win32 tree peer and drop target
*
*Revision 1.30.2.1  2003/09/15 02:52:36  ddiego
*miscellaneous changes
*
*Revision 1.30  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.29.2.1  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.29  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.28.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.28.2.1  2003/03/12 03:13:10  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.28  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.27.14.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.27.14.3  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.27.14.2  2002/12/27 23:05:01  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.27.14.1  2002/12/02 00:38:36  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.27  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.26  2002/03/21 00:47:49  ddiego
*fixes bug [ 532600 ] new VCF::DefaultTreeItem - this was due to the
*changes in updating policy with the ApplicationKit and the TreeListControl
*also fixes the missing file in the static ApplicationKit
*
*Revision 1.25  2002/03/20 02:46:54  ddiego
*fixes an issue with with changes to an items state not correctly being reflected in the
*TreeListControl
*Also makes another adjustment to the scroll positioning when collapsing nodes
*
*Revision 1.24.4.2  2002/04/27 15:52:47  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.24.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.24  2002/03/17 00:19:50  ddiego
*added support for selecting multiple items with the shift key
*
*Revision 1.23  2002/03/07 00:26:53  ddiego
*fixed memory leak of allocated subitems in DefaultTreeItem
*
*Revision 1.22  2002/02/27 04:16:12  ddiego
*add sub items to TreeItem class for teh tree list control
*added fixes to the RemoteObject stuff
*
*Revision 1.21  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


