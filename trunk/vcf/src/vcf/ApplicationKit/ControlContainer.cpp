//ControlContainer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ControlContainer.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Containers.h"

using namespace VCF;
ControlContainer::ControlContainer( const bool& heavyWeight ):
	CustomControl( heavyWeight )
{
	setContainerDelegate( this );
	setContainer( new StandardContainer() );
	setTabStop( false );

	setBorderSize( UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) );

	init();
}

ControlContainer::~ControlContainer()
{

}

void ControlContainer::init()
{

}

double ControlContainer::getBottomBorderHeight()
{
	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			return stdContainer->getBottomBorderHeight();
		}
	}

	return -1.0;
}

void ControlContainer::setBottomBorderHeight( const double& bottomBorderHeight )
{
	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			stdContainer->setBottomBorderHeight( maxVal<double>( 0, bottomBorderHeight ) );
		}
	}
}

double ControlContainer::getTopBorderHeight()
{
	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			return stdContainer->getTopBorderHeight();
		}
	}

	return -1.0;
}

void ControlContainer::setTopBorderHeight( const double& topBorderHeight )
{
	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			stdContainer->setTopBorderHeight( maxVal<double>( 0, topBorderHeight ) );
		}
	}
}

double ControlContainer::getRightBorderWidth()
{
	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			return stdContainer->getRightBorderWidth();
		}
	}
	return -1.0;
}

void ControlContainer::setRightBorderWidth( const double& rightBorderWidth )
{
	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			stdContainer->setRightBorderWidth( maxVal<double>( 0, rightBorderWidth ) );
		}
	}
}

double ControlContainer::getLeftBorderWidth()
{
	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			return stdContainer->getLeftBorderWidth();
		}
	}
	return -1.0;
}

void ControlContainer::setLeftBorderWidth( const double& leftBorderWidth )
{
	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			stdContainer->setLeftBorderWidth( maxVal<double>( 0, leftBorderWidth ) );
		}
	}
}

double ControlContainer::getBorderSize()
{
	double result = -1;

	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			result = (stdContainer->getBottomBorderHeight() +
						stdContainer->getRightBorderWidth() +
						stdContainer->getTopBorderHeight() +
						stdContainer->getLeftBorderWidth() ) / 4.0;

			if ( (result != stdContainer->getBottomBorderHeight()) ||
					(result != stdContainer->getRightBorderWidth()) ||
					(result != stdContainer->getLeftBorderWidth()) || (result != stdContainer->getTopBorderHeight()) ) {
				result = -1;
			}
		}
	}

	return result;
}

void ControlContainer::setBorderSize( const double& borderSize )
{
	Container* container = getContainer();
	if ( NULL != container ) {
		StandardContainer* stdContainer = dynamic_cast<StandardContainer*>(container);
		if ( NULL != stdContainer ) {
			stdContainer->setBorderWidth( maxVal<double>( 0, borderSize ) );
		}
	}
}

void ControlContainer::paint( GraphicsContext* context )
{
	CustomControl::paint( context );
	paintChildren( context );
}


/**
$Id$
*/
