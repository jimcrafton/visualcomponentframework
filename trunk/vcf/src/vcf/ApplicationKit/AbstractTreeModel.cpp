//AbstractTreeModel.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AbstractTreeModel.h"


using namespace VCF;

AbstractTreeModel::AbstractTreeModel()
{
	init();
}

AbstractTreeModel::~AbstractTreeModel()
{
	std::vector<TreeItem*>::iterator it = rootNodes_.begin();
	while ( it != rootNodes_.end() ) {
		TreeItem* rootItem = *it;
		if ( NULL != rootItem ) {
			//rootItem->clearChildren();
			delete rootItem;
		}
		rootItem = NULL;
		it ++;
	}
	rootNodes_.clear();
}

void AbstractTreeModel::init()
{
	treeItemContainer_.initContainer( rootNodes_ );
}

void AbstractTreeModel::empty()
{
	std::vector<TreeItem*>::iterator it = rootNodes_.begin();
	while ( it != rootNodes_.end() ) {
		TreeItem* rootItem = *it;
		if ( NULL != rootItem ) {
			rootItem->clearChildren();
			delete rootItem;
		}
		rootItem = NULL;
		it ++;
	}
	rootNodes_.clear();
}

void AbstractTreeModel::insertNodeItem(TreeItem * node, TreeItem * nodeToInsertAfter)
{
}

void AbstractTreeModel::deleteNodeItem(TreeItem * nodeToDelete)
{
}

void AbstractTreeModel::addNodeItem( TreeItem * node, TreeItem * nodeParent )
{
}

void AbstractTreeModel::sort()
{

}

void AbstractTreeModel::onItemPaint( ItemEvent* event )
{

}

void AbstractTreeModel::onItemChanged( ItemEvent* event )
{
	if ( NULL != event ){
		switch ( event->getType() ){
			case ITEM_EVENT_TEXT_CHANGED:{

			}
			break;
		}
	}
}

void AbstractTreeModel::onItemSelected( ItemEvent* event )
{

}

void AbstractTreeModel::onItemAdded( ItemEvent* event )
{

}


void AbstractTreeModel::onItemDeleted( ItemEvent* event )
{

}

Enumerator<TreeItem*>* AbstractTreeModel::getRootItems()
{
	return treeItemContainer_.getEnumerator();
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/10/05 03:15:23  kiklop74
*Additional changes in tree model
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
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/22 04:18:58  ddiego
*fixed bug 995642 delete LoalePeer in Locale, and added some miscellaneous changes to the QTPlayer. Also fixing (not finished yet) a bug that
*prevents the TreePeer from being properly notified when the tree model's
*item is deleted.
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.18  2003/08/09 02:56:44  ddiego
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
*Revision 1.17.2.1  2003/08/01 00:49:26  ddiego
*added a fix for popup windows that also fixed a problem with the
*ComboBoxControl drop down list disapearing.
*
*Revision 1.17  2003/05/17 20:37:46  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.16.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.16.2.1  2003/03/12 03:12:58  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.16  2003/02/26 04:30:54  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.15.14.2  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.15.14.1  2003/01/08 00:19:57  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.15  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.14.4.2  2002/04/27 15:52:39  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.14.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.14  2002/03/01 01:02:53  ddiego
*fixes bug [ 524006 ] TreeListControl crash
*makes some changes to model classes to utilize event types better
*
*Revision 1.13  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


