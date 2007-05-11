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


//container properties
//that may use component contants
//when be written to a Visual Form file.
#define	CONTAINER_BOTTOMHEIGHT		"bottomborderheight"
#define	CONTAINER_TOPHEIGHT			"topborderheight"
#define	CONTAINER_LEFTWIDTH			"leftborderwidth"
#define	CONTAINER_RIGHTWIDTH		"rightborderwidth"

#define CC_WINDOW_BORDER			"WindowBorder"
#define CC_CONTAINER_BORDER			"ContainerBorder"
#define CC_CONTROL_VSPACE			"ControlVBorder"
#define CC_CONTROL_HSPACE			"ControlHBorder"
#define CC_INFO_TOPSPACE			"InfoTopBorder"
#define CC_INFO_BOTTOMSPACE			"InfoBottomBorder"


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

	virtual bool generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue );

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
