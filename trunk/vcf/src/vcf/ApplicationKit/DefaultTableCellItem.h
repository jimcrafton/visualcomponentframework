#ifndef _VCF_DEFAULTTABLECELLITEM_H__
#define _VCF_DEFAULTTABLECELLITEM_H__
//DefaultTableCellItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_TABLECELLITEM_H__
#	include "vcf/ApplicationKit/TableCellItem.h"
#endif // _VCF_TABLECELLITEM_H__


namespace VCF {

class BasicTableItemEditor;

#define DEFAULTTABLECELLITEM_CLASSID	"53EA0BA6-7068-11d4-8F12-00207811CFAB"

class APPLICATIONKIT_API DefaultTableCellItem : public TableCellItem {
public:

	DefaultTableCellItem();

	virtual ~DefaultTableCellItem();

	virtual bool containsPoint( Point * pt );



	DELEGATE(ItemPaint);
	DELEGATE(ItemChanged);
	DELEGATE(ItemSelected);
	DELEGATE(ItemAdded);
	DELEGATE(ItemDeleted);

	virtual void addItemPaintHandler( EventHandler* handler ){
		ItemPaint += handler;
	}

	virtual void addItemChangedHandler( EventHandler* handler ){
		ItemChanged += handler;
	}

	virtual void addItemSelectedHandler( EventHandler* handler ){
		ItemSelected += handler;
	}

	virtual void addItemAddedHandler( EventHandler* handler ){
		ItemAdded += handler;
	}

	virtual void addItemDeletedHandler( EventHandler* handler ){
		ItemDeleted += handler;
	}

	virtual void removeItemPaintHandler( EventHandler* handler ){
		ItemPaint -= handler;
	}

	virtual void removeItemChangedHandler( EventHandler* handler ){
		ItemChanged -= handler;
	}

	virtual void removeItemSelectedHandler( EventHandler* handler ){
		ItemSelected -= handler;
	}

	virtual void removeItemAddedHandler( EventHandler* handler ){
		ItemAdded -= handler;
	}

	virtual void removeItemDeletedHandler( EventHandler* handler ){
		ItemDeleted -= handler;
	}


    virtual unsigned long getIndex() {
		return -1;
	}

	virtual void setIndex( const unsigned long& index ) {}

    virtual void* getData();

	virtual void setData( void* data );

	virtual Model* getModel();

	virtual void setModel( Model* model );

	virtual void paint( GraphicsContext* context, Rect* paintRect );



	virtual TableItemEditor* createItemEditor();


	virtual bool isSelected() {
		return (state_ & TableCellItem::tisSelected) ? true : false;
	}

	virtual bool isReadonly() {
		return (state_ & TableCellItem::tisReadonly) ? true : false;
	}

	virtual bool isFixed() {
		return (state_ & TableCellItem::tcsFixed) ? true : false;
	}

	virtual bool isFocused() {
		return (state_ & TableCellItem::tcsFocused) ? true : false;
	}

	virtual bool isDropHighlighted() {
		return (state_ & TableCellItem::tcsDropHighlighted) ? true : false;
	}

	virtual bool isEditable() {
		return !isReadonly();
	}

	virtual void setSelected( const bool& val );

	virtual void setReadonly( const bool& val );

	virtual void setFocused( const bool& val );

	virtual void setDropHighlighted( const bool& val );

	virtual void setFixed( const bool& val );


	virtual String getCaption();

	virtual void setCaption( const String& caption );

	virtual Rect* getBounds() {
		return &bounds_;
	}

	virtual Control* getControl() {
		return owningControl_;
	}


	virtual void setControl( Control* control ) {
		owningControl_ = control;
	}

	virtual long getImageIndex() {
		return imageIndex_;
	}

	virtual void setImageIndex( const long& imageIndex );

	virtual bool canPaint() {
		return true;
	}

	virtual long getState(){
		return state_;
	}

	virtual void setState( const long& state ) {
		state_ = state;
	}

	virtual void setBounds( Rect* bounds );

	/**
	*not supported
	*/
	virtual long getStateImageIndex(){
		return -1;
	};

	/**
	*not supported
	*/
	virtual void setStateImageIndex( const long& index ){}

	virtual long getTag() {
		return tag_;
	}

	virtual void setTag( const long& tag ) {
		tag_ = tag;
	}
private:
	void init();
	Control* owningControl_;
	Rect bounds_;
	void* data_;
	Model* model_;
	long state_;
	String caption_;
	long imageIndex_;
	long tag_;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.21.2.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.21  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.20.2.2  2004/01/30 22:08:08  ddiego
*more fixes to the table model and table control
*
*Revision 1.20.2.1  2004/01/30 05:08:14  ddiego
*added more rearrangements for the table control
*
*Revision 1.20  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.19.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.19  2003/08/09 02:56:42  ddiego
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
*Revision 1.18.2.1  2003/06/30 02:53:15  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.18  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.17.2.1  2003/03/12 03:09:32  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.17  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.16.14.2  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.16.14.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.16  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.15.4.2  2002/04/27 15:42:09  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.15.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.15  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTTABLECELLITEM_H__


