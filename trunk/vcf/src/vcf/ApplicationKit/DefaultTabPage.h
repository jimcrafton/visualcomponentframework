#ifndef _VCF_DEFAULTTABPAGE_H__
#define _VCF_DEFAULTTABPAGE_H__
//DefaultTabPage.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/TabPage.h"


namespace VCF {

#define DEFAULTTABPAGE_CLASSID	"86F02173-3E7F-11d4-8EA7-00207811CFAB"

class APPLICATIONKIT_API DefaultTabPage : public TabPage {
public:

	DefaultTabPage( Control* component=NULL );

	virtual ~DefaultTabPage();

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

	virtual bool containsPoint( Point * pt );

    virtual unsigned long getIndex();

	virtual void setIndex( const unsigned long& index );

    virtual void* getData();

	virtual void setData( void* data );

	virtual Model* getModel();

	virtual void setModel( Model* model );

	virtual void setPageName( const String& name );

	virtual String getPageName();

	virtual Control* getPageComponent();

	virtual void setPageComponent( Control* component );

	virtual bool isSelected();

	virtual void setSelected( const bool& selected );

	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual ulong32 getPreferredHeight();

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
		return 0;
	}

	virtual void setState( const long& state ){}

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

private:
	Model* model_;
	Control* owningControl_;
	ulong32 index_;
	String pageName_;
	Control* component_;
	bool selected_;
	ulong32 preferredHeight_;
	Rect bounds_;
	long imageIndex_;
	void* data_;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/15 04:25:52  ddiego
*fixed some issues that duff had with the examples, plu added the ability to get the platforms version and name and compiler
*
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
*Revision 1.19.4.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.19  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.18.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.18  2003/08/09 02:56:42  ddiego
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
*Revision 1.17.2.1  2003/06/30 02:53:15  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.17  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.16.2.1  2003/03/12 03:09:32  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.16  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.15.8.2  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.15.8.1  2002/12/25 22:37:59  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.15  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.14.12.1  2002/07/26 04:24:29  ddiego
*added more support for properly querying modified document, and removing the
*documents from the doc tab pages, made some changes in TabbedPages to support
*this as well
*
*Revision 1.14  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTTABPAGE_H__


