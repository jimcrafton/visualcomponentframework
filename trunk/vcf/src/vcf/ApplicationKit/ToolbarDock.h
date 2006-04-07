#ifndef _VCF_TOOLBARDOCK_H__
#define _VCF_TOOLBARDOCK_H__
//ToolbarDock.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

enum ToolbarDockSide {
	tdsTop=0,
	tdsLeft,
	tdsRight,
	tdsBottom
};

static String ToolbarDockSideNames[] = { "tdsTop",
                                         "tdsLeft",
										 "tdsRight",
										 "tdsBottom" };

enum ToolbarBackgroundStyle {
	tbksNone=0,
	tbksTile,
	tbksStretch
};


static String ToolbarBackgroundStyleNames[] = { "tbksNone",
											"tbksTile",
											"tbksStretch" };


#define DEFAULT_TOOLBAR_HEIGHT			25

class Toolbar;

#define TOOLBARDOCK_CLASSID			"54AE13E1-113D-4dcf-90F9-18FBBF713179"

/**
*A toolbar dock represents a rectangular child window that may hold o or more toolbars.
These toolbars may be attached to any of the four sides of the parent Window that
holds them.
*/
class APPLICATIONKIT_API ToolbarDock : public CustomControl, public DelegatedContainer<ToolbarDock> {
public:

	ToolbarDock();
	virtual ~ToolbarDock();

	ToolbarDockSide getDockSide();

	void setDockSide( const ToolbarDockSide& dockSide );

	Image* getBackground();

	void setBackground( Image* background );

	ToolbarBackgroundStyle getBackgroundStyle();

	void setBackgroundStyle( const ToolbarBackgroundStyle& backgroundStyle );

	bool isUsingBackground();

	void setUsingBackground( const bool& usingBackground );

	bool allowsDragging();

	void setAllowsDragging( const bool& allowsDrag );

	virtual void paint( GraphicsContext* context );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	void addToolbar( Toolbar* toolbar );

protected:

	/**
	*add overriden to prevent the adding of non-Toolbar Controls - this is
	*the only type if control the ToolbarDock will allow - anythign will
	*cause an exception to be thrown
	*/
	virtual void add( Control * child );

	virtual void add( Control * child, const AlignmentType& alignment );

	virtual void remove( Control* child );

	ToolbarDockSide dockSide_;
	ToolbarBackgroundStyle backgroundStyle_;
	Image* backgroundImage_;
	bool isUsingBackground_;
	bool allowsDockDragging_;
	std::vector<Toolbar*> toolbars_;
	double originalHeightWidth_; //used for either the original height or width depending on the dockSide_
	Toolbar* findToolbar( Point* pt );

	void recalcToolbarLayout();


};


/**
\class DockManager ToolbarDock.h "vcf/ApplicationKit/ToolbarDock.h"
*DockManager class uses to manage ToolbarDock's and floating toolbars
*/
class DockManager : public VCF::Object {
public:
	static DockManager* create();

	DockManager();

	virtual ~DockManager();

	static DockManager* getDockManager() {
		return dockManagerInstance;
	}

	void addDock( ToolbarDock* dock ) {
		docks_.push_back( dock );
	}

	void removeDock( ToolbarDock* dock );

	/**
	*@param Point point is in Screen coordinates
	*/
	ToolbarDock* findDock( Point* point );

	void addFloatingToolbar( Toolbar* toolbar );

	void removeFloatingToolbar( Toolbar* toolbar );
protected:
	std::vector<ToolbarDock*> docks_;
	std::vector<Toolbar*> floatingToolbars_;
	static DockManager* dockManagerInstance;


};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:25  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.13.4.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.13  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.4.4  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.12.4.3  2003/09/06 19:45:45  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.12.4.2  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.12.4.1  2003/08/18 19:52:32  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.12  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.1  2003/03/12 03:09:47  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.14.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.10  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/04/27 15:42:59  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.9  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TOOLBARDOCK_H__


