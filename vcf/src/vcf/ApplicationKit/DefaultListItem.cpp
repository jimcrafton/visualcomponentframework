//DefaultListItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultListItem.h"
#include "vcf/ApplicationKit/ListModel.h"


using namespace VCF;



DefaultListItem::DefaultListItem()
{
	init();
}

DefaultListItem::DefaultListItem( ListModel* model )
{
	init();
	model_ = dynamic_cast<Model*>(model);
}

DefaultListItem::DefaultListItem( ListModel* model, const String& caption )
{
	init();
	model_ = dynamic_cast<Model*>(model);
	caption_ = caption;
}

DefaultListItem::~DefaultListItem()
{
	std::vector<SubItem*>::iterator it = subItems_.begin();
	while ( it != subItems_.end() ) {
		SubItem* subItem = *it;

		delete subItem;
		subItem = NULL;

		it ++;
	}
}

void DefaultListItem::init()
{
	state_ = Item::idsNone;
	tag_ = -1;
	model_ = NULL;
	owningControl_ = NULL;
	imageIndex_ = 0;
	data_ = NULL;
	index_ = 0;
	model_ = NULL;
	selected_ = false;

	bounds_.setRect( 0.0, 0.0, 0.0, 0.0 );

	subItemsContainer_.initContainer( subItems_ );

}

bool DefaultListItem::containsPoint( Point * pt )
{
	return bounds_.containsPt( pt );
}

unsigned long DefaultListItem::getIndex()
{
	return index_;
}

void DefaultListItem::setIndex( const unsigned long& index )
{
	index_ = index;
}

void* DefaultListItem::getData()
{
	return data_;
}

void DefaultListItem::setData( void* data )
{
	data_ = data;
}

String DefaultListItem::getCaption()
{
	if ( getUseLocaleStrings() ) {
		return System::getCurrentThreadLocale()->translate( caption_ );
	}
	return caption_;
}

void DefaultListItem::setCaption( const String& caption )
{
	caption_ = caption;
	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged.fireEvent( &event );
}

Model* DefaultListItem::getModel()
{
	return this->model_;
}

void DefaultListItem::setModel( Model* model )
{
	model_ = model;
}

void DefaultListItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;

	ItemEvent event( this, context );
	ItemPaint.fireEvent( &event );
}

bool DefaultListItem::isSelected()
{
	return selected_;
}

void DefaultListItem::setSelected( const bool& selected )
{
	selected_ = selected;
	ItemEvent event( this, ITEM_EVENT_SELECTED );
	ItemSelected.fireEvent( &event );
}

void DefaultListItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}

void DefaultListItem::addSubItem( const String& caption, void* data )
{
	ListItem::SubItem* newSubItem = new ListItem::SubItem( this );
	newSubItem->setCaption( caption );
	newSubItem->setData( data );
	addSubItem( newSubItem );
}

void DefaultListItem::addSubItem( ListItem::SubItem* subItem )
{
	subItems_.push_back( subItem );

	ItemEvent event( this, LISTITEM_EVENT_SUBTITEM_ADDED );
	SubItemAdded.fireEvent( &event );
}

void DefaultListItem::removeSubItem( const ulong32& index )
{
	std::vector<SubItem*>::iterator found = subItems_.begin() + index;
	if ( found != subItems_.end() ) {
		SubItem* subItem = *found;
		ItemEvent event( this, LISTITEM_EVENT_SUBTITEM_DELETED );
		SubItemDeleted.fireEvent( &event );

		subItems_.erase( found );

		delete subItem;
		subItem = NULL;
	}
}


Enumerator<ListItem::SubItem*>* DefaultListItem::getSubItems()
{
	return subItemsContainer_.getEnumerator();
}

ListItem::SubItem* DefaultListItem::getSubItem( const ulong32& index )
{
    ListItem::SubItem* result = NULL;
    if ( index < subItems_.size() ) {
        result = subItems_[index];
    }
	return result;
}

ulong32 DefaultListItem::getSubItemCount()
{
	return subItems_.size();
}

void DefaultListItem::subItemChanged( ListItem::SubItem* item )
{
	ItemEvent event( this, LISTITEM_EVENT_SUBTITEM_CHANGED );
	SubItemChanged.fireEvent( &event );
}

void DefaultListItem::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
}


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/03/20 04:29:21  ddiego
*added ability to set image lists for list box control.
*
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/09 18:48:04  ddiego
*added locale translation support for most classes
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.21  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.20.2.1  2003/08/26 21:41:17  ddiego
*miscellanesous stuff, minor bugs
*
*Revision 1.20  2003/08/09 02:56:45  ddiego
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
*Revision 1.19.2.1  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.19  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.18.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.18.2.1  2003/03/12 03:13:06  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.18  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.17.14.4  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.17.14.3  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.17.14.2  2002/12/27 23:05:00  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.17.14.1  2002/12/02 00:38:36  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.17  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.16.4.2  2002/04/27 15:52:45  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.16.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.16  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


