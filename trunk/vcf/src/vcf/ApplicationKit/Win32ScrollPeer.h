#ifndef _VCF_WIN32SCROLLPEER_H__
#define _VCF_WIN32SCROLLPEER_H__
//Win32ScrollPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/ScrollPeer.h"


namespace VCF  {

/**
*Class Win32ScrollPeer documentation
*/
class Win32ScrollPeer : public Object, public ScrollPeer {
public:
	Win32ScrollPeer( Control* scrollableControl=NULL );

	virtual ~Win32ScrollPeer();

	virtual void scrollTo( const double& xPosition, const double& yPosition );

	virtual void getAdjustedPositions( double& xPosition, double& yPosition );

	virtual bool isVerticalScrollbarVisible();

	virtual bool isHorizontalScrollbarVisible();	

	virtual void recalcScrollPositions( Scrollable* scrollable );

	virtual Control* getScrollableControl() {
		return scrollableControl_;
	}

	virtual void setScrollableControl( Control* scrollableControl );

	virtual double getHorizontalScrollbarHeight();

	virtual double getVerticalScrollbarWidth();

	static Control* getScrollableControlFromHWnd( HWND scrollhWnd );

	virtual void getHorizontalScrollRects( Rect* scrollBounds, Rect* leftBounds=NULL, Rect* rightBounds=NULL );
	virtual void getVerticalScrollRects( Rect* scrollBounds, Rect* topBounds=NULL, Rect* bottomBounds=NULL );
protected:
	static std::map<HWND,Control*> hScrollBarMap;
	void removeScrollBarsFromMap();
	void addScrollBarsToMap();
	Control* scrollableControl_;
	Control* scrollCorner_;
	HWND vScrollHWnd_;
	HWND hScrollHWnd_;	

	bool isVertSBVisible_;//move to AbstractScrollable
	bool isHorzSBVisible_;//move to AbstractScrollable
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:39  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/09/21 05:41:25  dougtinkham
*modified recalcScrollPositions, removed updateVirtualViewSize
*
*Revision 1.2.2.1  2004/09/19 19:54:45  marcelloptr
*scrollbars transitory changes
*
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.11.2.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.10.2.2  2004/03/26 18:37:58  marcelloptr
*very minor fixes
*
*Revision 1.10.2.1  2004/03/21 20:25:40  marcelloptr
*Scrollable automatically calculates the scroll given the line where to go
*
*Revision 1.10  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.3  2003/10/13 04:02:32  ddiego
*fixed some issues with calculating the view bounds if scrollbar
*are present as well as adding some functions to get teh bounds of
*left/right and top/bottom spaces that can surround a scrollbar.
*
*Revision 1.9.4.2  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9.4.1  2003/09/08 05:23:35  ddiego
*additions to scrolling to determine the correct width/height of scroll
*bars
*fixed problem in text model with inserting text
*optimized ListBoxControl, performs much much better now
*
*Revision 1.9  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/12 03:11:29  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:40  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.14.1  2003/01/08 00:19:47  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/04/27 15:52:20  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WIN32SCROLLPEER_H__


