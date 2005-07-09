//ObjectWithEvents.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ObjectWithEvents.h

#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;


ObjectWithEvents::ObjectWithEvents()
{

}

ObjectWithEvents::~ObjectWithEvents()
{
	//destroy all the event handlers

	std::map<String,EventHandler*>::iterator it = eventHandlers_.begin();
	while ( it != eventHandlers_.end() ){
		EventHandler* ev = it->second;

		ev->free();
		//delete it->second;

		it++;
	}
	eventHandlers_.clear();

	std::vector<EventHandler::Vector*>::iterator handlerIt = masterHandlerList_.begin();
	while ( handlerIt != masterHandlerList_.end() ) {
		EventHandler::Vector* list = *handlerIt;
		delete list;
		list = NULL;
		handlerIt ++;
	}
	masterHandlerList_.clear();

}

void ObjectWithEvents::addEventHandler( const String& handlerName, EventHandler* handler )
{
	eventHandlers_[handlerName] = handler;
}

EventHandler* ObjectWithEvents::getEventHandler( const String& handlerName )
{
	EventHandler* result = NULL;

	std::map<String,EventHandler*>::iterator found = eventHandlers_.find( handlerName );
	if ( found != eventHandlers_.end() ){
		result = found->second;
	}
	return result;
}

void ObjectWithEvents::addEventHandlerList( EventHandler::Vector* eventHandlerList )
{
	masterHandlerList_.push_back( eventHandlerList );
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:15:04  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/05/15 23:17:39  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.7  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.5  2004/05/31 13:20:57  ddiego
*more osx updates
*
*Revision 1.1.2.4  2004/05/18 02:07:32  ddiego
*fixed a bug in StringUtils format and trace  - from osx side
*
*Revision 1.1.2.3  2004/05/16 02:39:09  ddiego
*OSX code updates
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.8  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.1  2003/03/12 03:13:17  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.14.1  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.6  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/03/20 21:53:02  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.5  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


