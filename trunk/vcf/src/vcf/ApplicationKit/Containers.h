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
\class StandardContainer Containers.h "vcf/ApplicationKit/Containers.h"
Basic implementation of a container
handles basic alignment,layout of child components.
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




/**
\class DesignTimeContainer Containers.h "vcf/ApplicationKit/Containers.h"
*/
class APPLICATIONKIT_API DesignTimeContainer : public  StandardContainer  {
public:
	DesignTimeContainer(){};

	DesignTimeContainer( Component* owner ):StandardContainer(owner){}

	virtual void resizeChildren( Control* control );
protected:
	void resizeChildrenUsingBounds(  Control* control, Rect* bounds );
};



};


#endif // _VCF_CONTAINERS_H__

/**
$Id$
*/
