//ControlEvent.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"



using namespace VCF;


ControlEvent::ControlEvent( Object* source ):
	Event( source )
{
	//this->init();
}


ControlEvent::ControlEvent( Object* source, const ulong32& eventType ):
	Event( source, eventType )
{
	this->init();
}

ControlEvent::ControlEvent( Object* source, const Size& newSize ):
	Event( source, Control::CONTROL_SIZED ){

	init();
	newSize_ = newSize;
};

/**
*use this constructor for creating COMPONENT_EVENT_POSITIONED events
*/
ControlEvent::ControlEvent( Object* source, const Point& newPosition ):
	Event( source, Control::CONTROL_POSITIONED ){

	init();
	newPosition_ = newPosition;
};

/**
*use this constructor for creating COMPONENT_EVENT_PARENT_CHANGED events
*/
ControlEvent::ControlEvent( Object* source, Control* newParent ):
	Event( source, Control::CONTROL_PARENT_CHANGED ){

	init();
	newParent_ = newParent;
};

ControlEvent::~ControlEvent()
{

}


void ControlEvent::init()
{
	this->newParent_ = NULL;
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
*Revision 1.8  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.1  2003/10/28 20:23:26  ddiego
*minor header changes
*
*Revision 1.7  2003/05/17 20:37:18  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.22.3  2003/03/23 06:46:01  marcelloptr
*minor fixes
*
*Revision 1.6.22.2  2003/03/23 03:23:54  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.22.1  2003/03/12 03:11:55  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.5  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


