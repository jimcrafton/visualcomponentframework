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


#endif // _VCF_TOOLBARDOCK_H__

/**
$Id$
*/
