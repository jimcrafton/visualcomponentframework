//Action.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Action.h"
#include "vcf/ApplicationKit/ActionEvent.h"


using namespace VCF;


Action::Action()
{
	targetsContainer_.initContainer(targets_);
}

Action::Action( Component* owner ):
	Component(owner)
{
	targetsContainer_.initContainer(targets_);
}

Action::Action( const String& name, Component* owner ):
	Component(name, owner)
{
	targetsContainer_.initContainer(targets_);
}

Action::Action( const String& name ):
	Component(name)
{
	targetsContainer_.initContainer(targets_);
}

Action::~Action()
{

}


void Action::update()
{
	ActionEvent event( this, Action::UpdateEvent );

	Update.fireEvent( &event );


	std::vector<Component*>::iterator it = targets_.begin();

	while ( it != targets_.end() ) {
		(*it)->handleEvent( &event );
		it ++;
	}
}

void Action::perform( Event* event )
{
	if ( NULL != event ) {
		Performed.fireEvent( event );
	}
	else {
		ActionEvent e( this, Action::ActionPerformedEvent );
		Performed.fireEvent( &e );
	}
}

void Action::addTarget( Component* target )
{
	std::vector<Component*>::iterator found = std::find( targets_.begin(), targets_.end(), target );
	//don't allow duplicate entries
	if ( found == targets_.end() ) {
		targets_.push_back( target );
		target->setAction( this );
	}
}

void Action::removeTarget( Component* target )
{
	std::vector<Component*>::iterator found = std::find( targets_.begin(), targets_.end(), target );

	if ( found != targets_.end() ) {
		targets_.erase( found );
	}
}

Enumerator<Component*>* Action::getTargets()
{
	return targetsContainer_.getEnumerator();
}

unsigned long Action::getTargetCount()
{
	return targets_.size();
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.2  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.1.2.1  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*/


