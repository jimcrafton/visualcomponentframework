#ifndef _VCF_FRAMEEVENT_H__
#define _VCF_FRAMEEVENT_H__
//FrameEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {
	class APPLICATIONKIT_API FrameEvent : public Event {
	public:
		FrameEvent( Object* source ) : Event(source),okToClose_(true) {};

		FrameEvent( Object* source, const unsigned long& eventType ):Event(source, eventType),okToClose_(true) {};

		FrameEvent( const FrameEvent& rhs ):Event(rhs) {
			*this = rhs;
		}

		virtual ~FrameEvent(){};


		FrameEvent& operator=( const FrameEvent& rhs ) {
			Event::operator =( rhs );
			okToClose_ = rhs.okToClose_;
			return *this;
		}
		/**
		*returns whether or not the window can close.
		*Windows which are in their closing methods should not close
		*if the flag has been set to false
		*/
		bool isOkToClose() {
			return okToClose_;
		}

		/**
		*sets the event okToClose_ flag
		*/
		void setOkToClose( const bool& okToClose ) {
			okToClose_ = okToClose;
			if ( false == okToClose_ ) {
				//set consumed to true so the event stops getting
				//processed by the Delegate event handling loop
				setConsumed( true );
			}
		}

		virtual Object* clone( bool deep=false ) {
			return new FrameEvent(*this);
		}

	protected:
		bool okToClose_;
	};



	template <class SOURCE_TYPE>
	class FrameEventHandler : public EventHandlerInstance<SOURCE_TYPE,FrameEvent> {
	public:
		FrameEventHandler( SOURCE_TYPE* source,
			_typename_ EventHandlerInstance<SOURCE_TYPE,FrameEvent>::OnEventHandlerMethod handlerMethod,
			const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,FrameEvent>( source, handlerMethod, handlerName ) {

		}

		virtual ~FrameEventHandler(){};

	};
};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:36  marcelloptr
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
*Revision 1.4.2.1  2003/09/12 00:09:32  ddiego
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
*Revision 1.3  2003/05/17 20:37:07  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.10.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.2.10.1  2003/03/12 03:09:54  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.2.1  2002/08/13 04:28:23  ddiego
*bugs fixed:
*[ 585085 ] Can't get at multi selected filenames - this was just a matter of exposing a function that was already available in the
*peer class
*
*features:
*58839 Add a method to query closing a Frame, this required a change that included added a new event (FrameEvent and the corresponding
*FrameEventHandler) and a method, bool Frame::allowClose()
*
*Also made fixes in the VCF Builder to now take advantage of this, so the MainWindow class will now register an event
*handler to handler the FrameClosing event, and attempt to set the current workspace to NULL. If this does not happen then
*the closing event will fail and prevent the widnow from being shutdown. Woo hoo !
*
*/


#endif // _VCF_FRAMEEVENT_H__


