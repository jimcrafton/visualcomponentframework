#ifndef _VCF_ABSTRACTSCROLLABLE_H__
#define _VCF_ABSTRACTSCROLLABLE_H__
//AbstractScrollable.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class ScrollPeer;

/**
*Class AbstractScrollable documentation.
*This class represents a basic implementation for
*controls that would like to be "scrollable".
*@see Scrollable
*@version 1.0
*@author Jim Crafton
*/
class APPLICATIONKIT_API AbstractScrollable : public Scrollable {
public:
	class ControlResizeHandler : public ObjectWithEvents {
	public:
		ControlResizeHandler( AbstractScrollable* scrollable );

		virtual ~ControlResizeHandler();

		void controlResized( ControlEvent* event );

	private:
		  AbstractScrollable* scrollable_;
	};

	AbstractScrollable();

	virtual ~AbstractScrollable();

	friend class ControlResizeHandler;

	virtual void setHasVerticalScrollbar( const bool& hasVerticalScrollbar ) {
		hasVertScrollbar_ = hasVerticalScrollbar;
		recalcScrollPositions();
	}

	virtual void setHasHorizontalScrollbar( const bool& hasHorizontalScrollbar ) {
		hasHorzScrollbar_ = hasHorizontalScrollbar;
		recalcScrollPositions();
	}

	virtual bool hasVerticalScrollBar() {
		return hasVertScrollbar_;
	}

	virtual bool hasHorizontalScrollBar() {
		return hasHorzScrollbar_;
	}	

	virtual void setVirtualViewSize( const double& width, const double& height );

	virtual void setVirtualViewHeight( const double& virtualViewHeight ) {
		setVirtualViewSize( getVirtualViewWidth(), virtualViewHeight );
	}

	virtual double getVirtualViewHeight() {
		return virtualViewHeight_;
	}

	virtual void setVirtualViewWidth( const double& virtualViewWidth ) {
		setVirtualViewSize( virtualViewWidth, getVirtualViewHeight() );
	}

	virtual double getVirtualViewWidth() {
		return virtualViewWidth_;
	}

	virtual void setVirtualViewHorzStep( const double& step ) {
		virtualViewHorzStep_ = step;
	}

	virtual void setVirtualViewVertStep( const double& step ) {
		virtualViewVertStep_ = step;
	}

	virtual double getVirtualViewHorzStep() {
		return virtualViewHorzStep_;
	}

	virtual double getVirtualViewVertStep() {
		return virtualViewVertStep_;
	}

	virtual bool isVerticalScrollbarVisible();
		
	virtual bool isHorizontalScrollbarVisible();

	virtual void recalcScrollPositions();

	virtual Control* getScrollableControl() {
		return scrollableControl_;
	}

	virtual void setScrollableControl( Control* scrollableControl );

	virtual void setVerticalPosition( const double& vertPosition );

	virtual void setHorizontalPosition( const double& horzPosition );

	virtual double getVerticalPosition() {
		return vertPosition_;
	}

	virtual double getHorizontalPosition() {
		return horzPosition_;
	}

	virtual double getVerticalTopScrollSpace() {
		return topScrollSpace_;
	}

	virtual double getVerticalBottomScrollSpace() {
		return bottomScrollSpace_;
	}

	virtual void setVerticalTopScrollSpace( const double& topScrollSpace );

	virtual void setVerticalBottomScrollSpace( const double& bottomScrollSpace );

	virtual double getHorizontalLeftScrollSpace() {
		return leftScrollSpace_;
	}

	virtual double getHorizontalRightScrollSpace() {
		return rightScrollSpace_;
	}

	virtual void setHorizontalLeftScrollSpace( const double& leftScrollSpace );

	virtual void setHorizontalRightScrollSpace( const double& rightScrollSpace );

	virtual double getHorizontalScrollbarHeight();

	virtual double getVerticalScrollbarWidth();

	virtual void getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds=NULL, Rect* rightBounds=NULL );

	virtual void getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds=NULL, Rect* bottomBounds=NULL );

	virtual void setKeepScrollbarsVisible( const bool& horzVisible, const bool& vertVisible );
	virtual bool getKeepHorzScrollbarVisible();
	virtual bool getKeepVertScrollbarVisible();

	virtual void setDiscreteScroll( const bool& horzDiscrete, const bool& vertDiscrete );
	virtual bool getDiscreteHorzScroll();
	virtual bool getDiscreteVertScroll();

	void setVerticalScrollingDelegate( Delegate* delegate ) {
		vertDelegate_ = delegate;
	}

	void setHorizontalScrollingDelegate( Delegate* delegate ) {
		horzDelegate_ = delegate;
	}

	Delegate* getVerticalScrollingDelegate() {
		return vertDelegate_;
	}

	Delegate* getHorizontalScrollingDelegate() {
		return horzDelegate_;
	}
protected:

	void onControlResized( ControlEvent* event );

	ControlResizeHandler* resizeHandler_;

	ScrollPeer* scrollPeer_;
	Control* scrollableControl_;
	double virtualViewHorzStep_;
	double virtualViewVertStep_;
	double virtualViewHeight_;
	double virtualViewWidth_;	
	bool hasHorzScrollbar_;
	bool hasVertScrollbar_;
	double vertPosition_;
	double horzPosition_;
	double topScrollSpace_;
	double bottomScrollSpace_;
	double leftScrollSpace_;
	double rightScrollSpace_;
	bool keepHorzScrollbarVisible_;
	bool keepVertScrollbarVisible_;
	bool discreteHorzScroll_;
	bool discreteVertScroll_;
	Delegate* vertDelegate_;
	Delegate* horzDelegate_;

};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:50  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2005/01/15 00:52:38  marcelloptr
*bugfix [ 1099910 ] plus other improvements of the scrolling
*
*Revision 1.3  2004/12/01 04:31:19  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.5  2004/09/21 22:27:09  marcelloptr
*added setVirtualViewStep functions for the scrollbars and other minor changes
*
*Revision 1.2.2.4  2004/09/21 05:44:36  dougtinkham
*removed updateVirtualViewSize, added isVerticalScrollbarVisible, isHorizontalScrollbarVisible
*
*Revision 1.2.2.3  2004/09/19 19:54:45  marcelloptr
*scrollbars transitory changes
*
*Revision 1.2.2.2  2004/09/13 06:09:15  dougtinkham
*onControlResized now checks if updateVirtualViewSize should be called
*
*Revision 1.2.2.1  2004/09/10 22:30:15  dougtinkham
*added updateVirtualViewSize member fct
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.10.2.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2004/04/03 15:48:39  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.9.2.1  2004/03/01 05:58:54  ddiego
*and even MORE updates to the TableControl. Most of the core functionality from Chris Maunder's CGridCtrl has been migrated over, and is functional. Item editing and item dragging is still not done. Had to make a minor change to the AbstractScroallable class to allow it have vertical and/or horizontal delegate's set in order to notify them of position changes. This was needed by the TableControl to properly update the top left non fixed cell calculation. The performance is kind of slow ( :) ) in debug mode, but quite snappy in release.
*
*Revision 1.9  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.4.4  2003/10/13 04:00:16  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.8.4.3  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.8.4.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.8.4.1  2003/09/08 05:23:35  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.8  2003/05/17 20:36:59  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.22.1  2003/03/12 03:09:12  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2002/02/14 05:04:45  ddiego
*documentation...
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTSCROLLABLE_H__


