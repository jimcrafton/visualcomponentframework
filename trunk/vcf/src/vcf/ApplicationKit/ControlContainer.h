#ifndef _VCF_CONTROLCONTAINER_H__
#define _VCF_CONTROLCONTAINER_H__
//ControlContainer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#define CONTROLCONTAINER_CLASSID		"708b26ee-c180-4e73-89f2-f624d5593d8e"


namespace VCF  {

/**
\class ControlContainer ControlContainer.h "vcf/ApplicationKit/ControlContainer.h"
A ControlContainer is a simple custom control that 
automatically creates a standard container as soon
as it's created. In addition it implements the 
DelegatedContainer class so you can access the more
common container methods (like adding and removing
child controls) more conviently.
*/
class APPLICATIONKIT_API ControlContainer : public VCF::CustomControl, public DelegatedContainer<ControlContainer> {
public:

	ControlContainer( const bool& heavyWeight=true );
	virtual ~ControlContainer();

	void init();

	double getBottomBorderHeight();

	void setBottomBorderHeight( const double& bottomBorderHeight );

	double getTopBorderHeight();

	void setTopBorderHeight( const double& topBorderHeight );

	double getRightBorderWidth();

	void setRightBorderWidth( const double& rightBorderWidth );

	double getLeftBorderWidth();

	void setLeftBorderWidth( const double& leftBorderWidth );

	double getBorderSize();

	void setBorderSize( const double& borderSize );

	virtual void paint( GraphicsContext* context );

protected:

};


}; //end of namespace VCF


#endif // _VCF_CONTROLCONTAINER_H__

/**
$Id$
*/
