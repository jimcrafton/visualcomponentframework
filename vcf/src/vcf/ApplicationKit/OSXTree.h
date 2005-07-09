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
										
	static OSStatus DBItemNotificationCallback( ControlRef browser, DataBrowserItemID itemID, 
															DataBrowserItemNotification message);

};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.4  2005/07/07 23:28:58  ddiego
*last osx checkins before release - not complete :(
*
*Revision 1.1.2.3  2005/06/29 03:46:13  ddiego
*more osx tree and list coding.
*
*Revision 1.1.2.2  2005/06/28 04:03:36  ddiego
*osx text edit mods and started on osx tree peer.
*
*Revision 1.1.2.1  2005/06/22 03:59:30  ddiego
*added osx stub classes for peers
*
*Revision 1.3.2.1  2005/02/16 05:09:32  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/06 18:33:43  ddiego
*fixed some more transparent drawing issues
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/23 04:20:56  ddiego
*more checkins
*
*Revision 1.1.2.4  2004/07/16 05:07:18  ddiego
*added support for editing labels on a tree control
*
*Revision 1.1.2.3  2004/07/14 04:56:02  ddiego
*fixed Win32 bugs. Got rid of flicker in the common control
*wrappers and toolbar. tracking down combo box display bugs.
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.19.4.2  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.19  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.18.2.2  2003/09/17 21:23:24  ddiego
*added adjustmnents to win32 tree peer and drop target
*
*Revision 1.18.2.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
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
*Revision 1.17.2.1  2003/05/27 04:45:32  ddiego
*doing some code cleanup to fix some bugs in the way dialogs and popups
*work in Win32 port. Cleaned up the ControlPeer and DialogPeer interfaces
*a bit.
*
*Revision 1.17  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.16.2.2  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.16.2.1  2003/03/12 03:11:37  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.16  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.15.14.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.15  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.14.4.1  2002/04/27 15:52:20  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.14  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_OSXTREE_H__


