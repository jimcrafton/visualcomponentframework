#ifndef _VCF_SCROLLBARMANAGER_H__
#define _VCF_SCROLLBARMANAGER_H__
//ScrollbarManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define SCROLLBARMANAGER_CLASSID		"9dac628d-a522-4a59-b255-8f825b78681d"


namespace VCF  {

/**
*The ScrollbarManager represents a component used for managing
*scrolbars for a target control.
*The target control is specified and then a Scrollable instance is associated
*with the target. The manager componenent also exposes the Scrollable object's
*properties, allowing the developer to work with them at design time as well
*as programmatically.
*/
class APPLICATIONKIT_API ScrollbarManager : public Component {
public:

	/**
	@delegate VerticalScrolling
	@event ScrollEvent
	*/
	DELEGATE(VerticalScrolling)

	/**
	@delegate HorizontalScrolling
	@event ScrollEvent
	*/
	DELEGATE(HorizontalScrolling)

	ScrollbarManager();

	ScrollbarManager( Component* owner );

	ScrollbarManager( const String& name, Component* owner );

	ScrollbarManager( const String& name );

	Control* getTarget() {
		return target_;
	}

	void setTarget( Control* target );

	virtual void afterCreate( ComponentEvent* event );

	void setHasVerticalScrollbar( const bool& hasVerticalScrollbar );

	void setHasHorizontalScrollbar( const bool& hasHorizontalScrollbar );

	bool hasVerticalScrollBar();

	bool hasHorizontalScrollBar();	

	double getVirtualViewHeight();

	double getVirtualViewWidth();

	void setVirtualViewHeight( const double& virtualViewHeight );

	void setVirtualViewWidth( const double& virtualViewWidth );

	void setVirtualViewSize( const double& virtualViewWidth, const double& virtualViewHeight );

	virtual void setVirtualViewHorzStep( const double& step );

	virtual void setVirtualViewVertStep( const double& step );

	virtual double getVirtualViewHorzStep();

	virtual double getVirtualViewVertStep();

	void setVerticalPosition( const double& vertPosition );

	void setHorizontalPosition( const double& horzPosition );

	double getVerticalPosition();

	double getHorizontalPosition();

	double getVerticalTopScrollSpace();

	double getVerticalBottomScrollSpace();

	void setVerticalTopScrollSpace( const double& topScrollSpace );

	void setVerticalBottomScrollSpace( const double& bottomScrollSpace );

	double getHorizontalLeftScrollSpace();

	double getHorizontalRightScrollSpace();

	void setHorizontalLeftScrollSpace( const double& leftScrollSpace );

	void setHorizontalRightScrollSpace( const double& rightScrollSpace );

	void setKeepScrollbarsVisible( const bool& horzVisible, const bool& vertVisible );
	bool getKeepHorzScrollbarVisible();
	bool getKeepVertScrollbarVisible();

protected:
	Scrollable* scrollable_;
	Control* target_;

	virtual ~ScrollbarManager();
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.4  2004/09/21 22:27:09  marcelloptr
*added setVirtualViewStep functions for the scrollbars and other minor changes
*
*Revision 1.2.2.3  2004/09/21 05:49:23  dougtinkham
*removed updateVirtualViewSize
*
*Revision 1.2.2.2  2004/09/19 19:54:45  marcelloptr
*scrollbars transitory changes
*
*Revision 1.2.2.1  2004/09/14 21:10:55  dougtinkham
*added updateVirtualViewSize member
*
*Revision 1.2  2004/08/07 02:49:09  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/26 21:58:21  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.3.2.1  2004/03/01 05:58:54  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.3  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.4.4  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.2.4.3  2003/10/13 04:00:24  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.2.4.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2.4.1  2003/09/05 21:03:39  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.2  2003/05/17 20:37:04  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.1.22.1  2003/03/12 03:09:43  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.1  2002/03/01 01:56:20  ddiego
*added files for [ 524137 ] ScrollComponent for adding scrolling
*plus CVS log info
*
*/


#endif // _VCF_SCROLLBARMANAGER_H__


