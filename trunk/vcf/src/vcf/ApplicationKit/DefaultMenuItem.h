#ifndef _VCF_DEFAULTMENUITEM_H__
#define _VCF_DEFAULTMENUITEM_H__
//DefaultMenuItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class MenuItemPeer;

#define DEFAULTMENUITEM_CLASSID		"15307228-7207-44c8-8b22-4d5575648ae8"


class APPLICATIONKIT_API DefaultMenuItem : public MenuItem {

public:
	DefaultMenuItem();

	DefaultMenuItem( const String& caption, MenuItem* parent=NULL, Menu* menuOwner=NULL );

	virtual ~DefaultMenuItem();

	void init();

	DELEGATE(ItemPaint);
	DELEGATE(ItemChanged);
	DELEGATE(ItemSelected);
	DELEGATE(ItemAdded);
	DELEGATE(ItemDeleted);

	virtual void addItemPaintHandler( EventHandler* handler ){
		ItemPaint +=  handler;
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

	DELEGATE(MenuItemClicked);
	DELEGATE(MenuItemUpdate);

	virtual void addMenuItemClickedHandler( EventHandler* handler ) {
		MenuItemClicked += handler;
	}

	virtual void removeMenuItemClickedHandler( EventHandler* handler ) {
		MenuItemClicked -= handler;
	}

	virtual void addMenuItemUpdateHandler( EventHandler* handler ) {
		MenuItemUpdate += handler;
	}

	virtual void removeMenuItemUpdateHandler( EventHandler* handler ) {
		MenuItemUpdate -= handler;
	}


	virtual bool containsPoint( Point * pt );

    virtual unsigned long getIndex();

	virtual void setIndex( const unsigned long& index );

    virtual void* getData();

	virtual void setData( void* data );

	virtual Model* getModel();

	virtual void setModel( Model* model );

	virtual void paint( GraphicsContext* context, Rect* paintRect );

	virtual bool isSelected();

	virtual void setSelected( const bool& selected );

	virtual Enumerator<MenuItem*>* getChildren();

	virtual void addChild( MenuItem* child );

	virtual void insertChild( const unsigned long& index, MenuItem* child );

	virtual void deleteChild( MenuItem* child );

	virtual void deleteChild( const unsigned long& index );

	virtual void clearChildren();

	virtual bool isChecked();

	virtual void setChecked( const bool& checked );

	virtual bool hasParent();

	virtual bool hasChildren();

	virtual unsigned long getChildCount();

	virtual Menu* getMenuOwner();

	virtual void setMenuOwner( Menu* menuOwner );

	virtual MenuItem* getParent();

	virtual void setParent( MenuItem* parent );

	virtual MenuItem* getChildAt( const unsigned long& index );

	virtual MenuItem* findChildNamedSimilarTo( const String& name );

	virtual MenuItem* findChildNamed( const String& name );

	virtual bool isEnabled();

	virtual void setEnabled( const bool& enabled );

	virtual bool isVisible();

	virtual void setVisible( const bool& visible );

	virtual bool getRadioItem();

	virtual void setRadioItem( const bool& value );

	virtual void setCaption( const String& caption );

	virtual String getCaption();

	virtual MenuItemPeer* getPeer();

	virtual bool isSeparator();

	virtual void setSeparator( const bool& separator );

	virtual void click();

	virtual void update();

	virtual Rect* getBounds() {
		return &bounds_;
	}

	virtual Control* getControl() {
		return NULL;
	}


	virtual void setControl( Control* control ) {}


	virtual long getImageIndex() {
		return imageIndex_;
	}

	virtual void setImageIndex( const long& imageIndex );

	virtual bool canPaint() {
		return false;
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

	virtual void setAcceleratorKey( const VirtualKeyCode& keyCode, const ulong32& modifierMask );

	virtual void addAcceleratorKey( AcceleratorKey* accelerator );

	virtual AcceleratorKey* getAccelerator() {
		return currentAccelerator_;
	}
	
	virtual Object* clone(bool deep=false);

	virtual void handleEvent( Event* event );
protected:
	void onAccelerator( KeyboardEvent* e );

protected:
	MenuItemPeer* Peer_;
	std::vector<MenuItem*> menuItems_;
	EnumeratorContainer<std::vector<MenuItem*>, MenuItem*> container_;
	String caption_;
	bool visible_;
	ulong32 index_;
	bool selected_;
	void* data_;
	Menu* menuOwner_;
	bool separator_;
	MenuItem* parent_;
	bool radioItem_;
	long imageIndex_;
	bool isEnabled_;
	Rect bounds_;
	AcceleratorKey* currentAccelerator_;

};





class APPLICATIONKIT_API SeparatorMenuItem : public DefaultMenuItem {
public:
	SeparatorMenuItem( MenuItem* parent, Menu* menuOwner=NULL ) :
		DefaultMenuItem( "", parent, menuOwner_) {
		setSeparator( true );
	}
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
*Revision 1.2.2.2  2004/11/18 06:45:44  ddiego
*updated toolbar btn bug, and added text edit sample.
*
*Revision 1.2.2.1  2004/09/07 00:49:12  ddiego
*minor fixes in printg code in graphics kit, and added a 2 ways to print in the printing example.
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
*Revision 1.25.2.1  2004/04/26 21:58:19  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.25  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.23.2.1  2004/01/15 05:35:04  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.23  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.22.2.4  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.22.2.3  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.22.2.2  2003/10/17 21:22:54  ddiego
*added menu item child count function
*fixed a selection glitch in tree list control
*
*Revision 1.22.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.22  2003/08/09 02:56:42  ddiego
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
*Revision 1.21.2.3  2003/07/16 04:58:47  ddiego
*added some changes to the fil and stroke classes to allow changing whether
*they use anti-aliasing or not. Also implemented Matrix2D::invert(),
*plus properly implemented clone() on the DefaultMenuItem class.
*
*Revision 1.21.2.2  2003/06/30 02:53:15  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.21.2.1  2003/06/27 03:10:58  ddiego
*got rid of some redundant junk in the Clipboard and DataObject
*classes. Instead of a rather dippy use of the DataType calss, we now simply
*use pure mime-types to identify the various "flavours" of data.
*
*Revision 1.21  2003/05/17 20:37:02  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.20.2.3  2003/03/25 20:23:46  marcelloptr
*AbstractTextModel::appendText() fixed
*
*Revision 1.20.2.2  2003/03/23 03:23:45  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.20.2.1  2003/03/12 03:09:30  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.20  2003/02/26 04:30:37  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.19.2.3  2003/02/24 05:42:17  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.19.2.2  2002/12/27 23:04:31  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.19.2.1  2002/12/25 22:06:18  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.19  2002/11/18 00:46:07  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.18.10.1  2002/09/27 23:38:35  ddiego
*added support for geting various layout information
*added support for drawing various graphics UI primitives like scroll buttons
*tabs, tab pages, etc, partially to have this support in place for use
*in MacOSX.
*Also added scrolling buttons to TabbedPages, this fixes task 56652 in the
*ApplicationKit list
*
*Revision 1.18  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.17.4.1  2002/04/27 15:42:04  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.17  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DEFAULTMENUITEM_H__


