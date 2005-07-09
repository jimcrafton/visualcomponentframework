#ifndef _VCF_CONTAINERS_H__
#define _VCF_CONTAINERS_H__
//Containers.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_ABSTRACTCONTAINER_H__
#include "vcf/ApplicationKit/AbstractContainer.h"
#endif // _VCF_ABSTRACTCONTAINER_H__


namespace VCF {



#define STANDARDCONTAINER_CLASSID		"a1236d3c-6c40-4f25-b0a1-39065a9d8f0a"

/**
*Basic implementation of a container
*handles basic alignment,layout of child components.
*/

class APPLICATIONKIT_API StandardContainer : public AbstractContainer {
public:

	StandardContainer();

	StandardContainer( Component* owner );


	virtual void resizeChildren( Control* control );

	double getBottomBorderHeight() {
		return bottomBorderHeight_;
	}

	void setBottomBorderHeight( const double& bottomBorderHeight );

	double getTopBorderHeight() {
		return topBorderHeight_;
	}

	void setTopBorderHeight( const double& topBorderHeight );

	double getRightBorderWidth() {
		return rightBorderWidth_;
	}

	void setRightBorderWidth( const double& rightBorderWidth );

	double getLeftBorderWidth() {
		return leftBorderWidth_;
	}

	void setLeftBorderWidth( const double& leftBorderWidth );

	void setBorderWidth ( const double& borderWidth );

	void calcAlignmentList( const AlignmentType& alignment, std::vector< Control* >& alignmentList );
	Control* getControlWithAlignment( const AlignmentType& alignment, const bool& first = true );
	Control* getControlInAlignmentList( const AlignmentType& alignment, const bool& first = true );

protected:
	double bottomBorderHeight_;
	double topBorderHeight_;
	double rightBorderWidth_;
	double leftBorderWidth_;

	bool insertBefore( Control* initialControl, const bool& controlJustAdded, Control* c1, Control* c2, const AlignmentType& alignment, Rect* bounds );
	void doPosition( Control* component, const AlignmentType& alignment, Rect* rect );
	void doAlign( Control* initialControl, const bool& controlJustAdded, const AlignmentType& alignment, Rect* rect );
	bool alignWork();
	bool anchorWork();
	void doAnchors( Control* control, const bool& controlJustAdded, Rect* bounds );

	void alignFixed( Control* initialControl, const bool& controlJustAdded, const AlignmentType& alignment, Rect* rect );
};




class APPLICATIONKIT_API DesignTimeContainer : public  StandardContainer  {
public:
	DesignTimeContainer(){};

	DesignTimeContainer( Component* owner ):StandardContainer(owner){}

	virtual void resizeChildren( Control* control );
protected:
	void resizeChildrenUsingBounds(  Control* control, Rect* bounds );
};



};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/03/06 22:50:58  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/08 15:08:05  ddiego
*made the change to the StandardContainer name - the
*old StandardContainer is now called DesignTimeContainer and
*the old FixedStandardContainer is now renamed to StandardContainer.
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.2.2.1  2003/12/22 21:55:49  marcelloptr
*minor changes
*
*Revision 1.2  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.6  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.1.2.5  2003/10/15 04:02:27  ddiego
*added some more support for persisting the dependency info
*
*Revision 1.1.2.4  2003/10/12 06:34:29  ddiego
*added some fixes to standard container layout algorithms - thisstill needs
*to be tested, but it looks like it may fix some outstanding issues
*with the layout logic
*
*Revision 1.1.2.3  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.1.2.2  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.1.2.1  2003/08/18 19:52:32  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*/


#endif // _VCF_CONTAINERS_H__


