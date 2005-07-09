//EventHandler.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

EventHandler::~EventHandler()
{
	
}
	

void EventHandler::addHandlerToSource( Object* source, const String& handlerName )
{
	ObjectWithEvents* objEventOwner = dynamic_cast<ObjectWithEvents*>(source);

	if ( NULL != objEventOwner ) {
		if ( !handlerName.empty() ) {
			objEventOwner->addEventHandler( handlerName, this );
		}
	}
	else {
		//StringUtils::traceWithArgs( "this event handler does not have a source object (class Name: %s) that can clean up it's memory. \nExpect memory leaks from this!\n",
		//							source->getClassName().c_str() );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.6  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.5  2005/01/02 03:04:22  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.3.2.1  2004/12/10 21:14:01  ddiego
*fixed bug 1082362 App Icons do not appear.
*
*Revision 1.4  2004/12/10 03:32:52  ddiego
*fixed a heap overwrite error in the delegate-event handler code.
*
*Revision 1.3  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.7  2003/05/17 20:37:18  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.10.2  2003/03/23 06:46:01  marcelloptr
*minor fixes
*
*Revision 1.6.10.1  2003/03/23 03:23:54  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.5.6.2  2002/09/10 04:07:48  ddiego
*misc fixes plus now posting the TableControl::finishEditing as a event
*
*Revision 1.5.6.1  2002/08/31 05:44:52  ddiego
**** empty log message ***
*
*Revision 1.5  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.1  2002/03/20 21:56:56  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.4  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


