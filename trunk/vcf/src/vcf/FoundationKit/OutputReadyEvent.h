#ifndef _VCF_OUTPUTREADYEVENT_H__
#define _VCF_OUTPUTREADYEVENT_H__
//OutputReadyEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {
/**
\class OutputReadyEvent OutputReadyEvent.h "vcf/FoundationKit/OutputReadyEvent.h"
*/
class FOUNDATIONKIT_API OutputReadyEvent : public Event {
public:
	OutputReadyEvent( Object* source, const String& outputData ):
	  Event(source),outputData_(outputData){};


	OutputReadyEvent( const OutputReadyEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	OutputReadyEvent& operator=( const OutputReadyEvent& rhs ) {
		Event::operator =( rhs );
		outputData_ = rhs.outputData_;

		return *this;
	}

	String getOutputData() {
		return outputData_;
	}

	virtual Object* clone( bool deep=false ) {
		return new OutputReadyEvent(*this);
	}
protected:
	String outputData_;
};


template <class SOURCE_TYPE> class OutputReadyEventHandler : public EventHandlerInstance<SOURCE_TYPE,OutputReadyEvent> {
public:
	OutputReadyEventHandler( SOURCE_TYPE* source,
							_typename_ EventHandlerInstance<SOURCE_TYPE,OutputReadyEvent>::OnEventHandlerMethod handlerMethod,
							const String& handlerName="") :
		EventHandlerInstance<SOURCE_TYPE,OutputReadyEvent>( source,
															handlerMethod,
															handlerName ) {};

};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:35  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/12 22:01:40  ddiego
*doc updates.
*
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.6.4.1  2004/04/26 21:58:37  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.2.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.5  2003/08/09 02:56:43  ddiego
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
*Revision 1.4.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.4  2003/05/17 20:37:08  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.3  2003/05/15 03:01:00  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.3.2.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.3.2.1  2003/03/12 03:09:57  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.1  2002/12/27 23:04:34  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.2  2002/09/17 21:32:59  ddiego
*added the build menus for building files and projects
*
*Revision 1.1.2.1  2002/09/17 18:48:34  ddiego
*added support in the VCF FoundationKit for redirecting io in a process
*
*/


#endif // _VCF_OUTPUTREADYEVENT_H__


