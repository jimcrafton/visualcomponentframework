#ifndef _VCF_WHATSTHISHELPEVENT_H__
#define _VCF_WHATSTHISHELPEVENT_H__
//WhatsThisHelpEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

#define WHAT_THIS_EVENT_TYPE	CUSTOM_EVENT_TYPES + 12


/**
\class WhatsThisHelpEvent WhatsThisHelpEvent.h "vcf/ApplicationKit/WhatsThisHelpEvent.h"  
*/
class WhatsThisHelpEvent : public Event {
public:
	WhatsThisHelpEvent( Object* source ):
	  Event( source, WHAT_THIS_EVENT_TYPE ) {

	}

	WhatsThisHelpEvent( const WhatsThisHelpEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~WhatsThisHelpEvent(){};

	WhatsThisHelpEvent& operator= ( const WhatsThisHelpEvent& rhs ) {
		Event::operator =( rhs );

		helpString = rhs.helpString;

		return *this;
	}


	String helpString;

	
	virtual Object* clone( bool deep=false ) {
		return new WhatsThisHelpEvent(*this);
	}


};





/**
*WhatsThisHelpEventHandler
*handles the following:
*onControlHelpRequested
*/
template <class SOURCE_TYPE>
class WhatsThisHelpEventHandler : public EventHandlerInstance<SOURCE_TYPE,WhatsThisHelpEvent>  {
public:
	WhatsThisHelpEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,WhatsThisHelpEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,WhatsThisHelpEvent>( source, handlerMethod, handlerName ) {

	}

};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.3  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.2.6.2  2006/02/23 05:54:23  ddiego
*some html help integration fixes and new features. context sensitive help is finished now.
*
*Revision 1.2.6.1  2005/09/07 20:24:48  ddiego
*added some more help support.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:37  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.4.2.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.4  2003/08/09 02:56:43  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.3.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.3  2003/05/17 20:37:08  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.22.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.2.22.1  2003/03/12 03:09:58  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_WHATSTHISHELPEVENT_H__


