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
			return stdContainer->getRightBorderWidth();
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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.8  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.2  2003/09/12 00:09:18  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.7.4.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.7  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.2.1  2003/03/12 03:13:04  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.2.3  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.5.2.2  2002/12/27 23:05:00  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.5.2.1  2002/12/25 22:06:34  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.5  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.4.16.1  2002/10/01 20:34:59  ddiego
*borders
*
*Revision 1.4  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


