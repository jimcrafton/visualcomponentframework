#ifndef _VCF_DELEGATE_H__
#define _VCF_DELEGATE_H__
//Delegate.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
Use this macro to make sure you define a delegate named "name", and an accessor function
called get<name>, which will return a reference to the delegate.
*/
#define DELEGATE(name)\
	VCF::Delegate name;\
	VCF::Delegate& get##name() {\
		return name;\
	}\
	\



namespace VCF {




/**
The Delegate class is used to maintain a collection of event handlers
and fire events to them.
<p>
Delegate's have their += and -= operators overloaded as a convenienc methods
for adding or removing event handlers.
<p>
A Delegate is <b><i>not</i></b> meant to be subclassed or derived from. It maintains
a pointer to a vector of event handlers, and be default the pointer is null. A new vector
will be created the first time a handler is added.
*/
class Delegate {
public:
	Delegate() : handlers_(NULL){

	}

	~Delegate() {
		removeAllHandlers();
		delete handlers_;
	}

	Delegate( const Delegate& rhs ): handlers_(NULL) {
		*this = rhs;
	}


	inline Delegate& operator=( const Delegate& rhs ) {

		if ( NULL == rhs.handlers_ ) {
			removeAllHandlers();
		}
		else {
			checkHandlers();
			*handlers_ = *rhs.handlers_;
		}
		return *this;
	}



	/**
	This adds a new event handler to the Delegate. If this is the first time that a
	handler has been added to this Delegate the Delgate's vector of event handlers will
	be created.
	@param EventHandler the new event handler to add. The event handler will <b>only</b>
	be added if it is not already in the collection of event handlers.
	*/
	inline void addHandler( EventHandler* handler ) {
		checkHandlers();

		EventHandler::Vector::iterator found =
				std::find( handlers_->begin(), handlers_->end(), handler );

		if ( found == handlers_->end() ) {
			handlers_->push_back( handler );
		}
	}

	/**
	This removes an event handler from the Delegate
	@param EventHandler the event handler to remove
	*/
	inline void removeHandler( EventHandler* handler ) {
		if ( NULL != handlers_ ) {
			EventHandler::Vector::iterator found =
				std::find( handlers_->begin(), handlers_->end(), handler );

			if ( found != handlers_->end() ) {
				handlers_->erase( found );
			}
		}
	}

	/**
	a shortcut for adding an event handler
	*/
	inline Delegate& operator += ( EventHandler* handler ) {
		addHandler( handler );
		return *this;
	}

	/**
	a shortcut for removing an event handler
	*/
	inline Delegate& operator -= ( EventHandler* handler ) {
		removeHandler( handler );
		return *this;
	}

	/**
	This fires an event to all known event handlers in this delegate.
	If an Event is marked as consumed (i.e. the Event's consume(true) is called)
	then the iteration of handlers will stop and the method will exit, otherwise
	each handler will have it's invoke() method called once, with the event passed in.
	@param Event the event to pass to each event handler
	*/
	inline void fireEvent( Event* event ) {
		if ( NULL != handlers_ ) {
			/**
			copy the handlers_ vector so that if a call is made to the delegates
			setFirstEventHandler, or removeAllHandlers, a crash does not
			occur due to the (possibly) changed state of the handlers_ vector.
			*/
			EventHandler::Vector tmpHandlers = *handlers_;

			EventHandler::Vector::iterator it = tmpHandlers.begin();
			while ( it != tmpHandlers.end() ) {
				if ( event->isConsumed() ) {
					break;
				}

				(*it)->invoke( event );

				it ++;
			}
		}
	}

	inline void removeAllHandlers() {
		if ( NULL != handlers_ ) {
			handlers_->clear();
		}
	}


	inline EventHandler* getFirstEventHandler() {
		EventHandler* result = NULL;
		if ( (NULL != handlers_) && (!handlers_->empty()) ) {
			result = handlers_->front();
		}

		return result;
	}


	inline void setFirstEventHandler( EventHandler* handler ) {
		checkHandlers();

		EventHandler::Vector::iterator found = std::find( handlers_->begin(), handlers_->end(), handler );
		if ( found != handlers_->end() ) {
			handlers_->erase( found );
		}

		handlers_->insert( handlers_->begin(), handler );
	}

protected:
	inline void checkHandlers() {
		if ( NULL == handlers_ ) {
			handlers_ = new EventHandler::Vector();
		}
	}

	EventHandler::Vector* handlers_;
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.10.2.1  2004/04/26 21:58:36  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.8.2.2  2004/01/06 04:40:39  ddiego
*added first handler and setting the first handler to the delegate
*
*Revision 1.8.2.1  2004/01/05 05:45:17  ddiego
**** empty log message ***
*
*Revision 1.8  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.2.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.7  2003/08/09 02:56:43  ddiego
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
*Revision 1.6.2.1  2003/06/30 02:53:15  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.6  2003/05/17 20:37:07  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.2  2003/03/23 03:23:46  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5.2.1  2003/03/12 03:09:51  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.2.2  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.4.2.1  2002/12/27 23:04:33  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.4  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.3.4.1  2002/11/04 04:50:17  ddiego
*bug fixes are:
*void Win32MenuItem::clearChildren(), was passing in an incorrect index into DeleteMenu()
*fixed an issue when deleting a project from a workspace. This was crashing due to open
*documents with bad pointers. Closing a project now closes all open documents that are
*associated with the project
*Verified that the new file and new class and new form, and new project and checking the validity of
*entered data.
*Fixed a bug in Win32Dialog where the Frame::allowClose() virtual method was not being
*called.
*Fixed a bug in the Delegate class which would allow multiple additions of the same event handler.
*
*Revision 1.3  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.2.4.2  2002/07/21 05:02:50  ddiego
*added more stuff for configuration management, fixed the FilePath bug
*add a removeAllHandlers() to VCF::Delegate class
*
*Revision 1.2.4.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.2  2002/06/24 04:24:49  ddiego
*mods to VCFBuilder
*
*Revision 1.1  2002/01/29 17:59:47  ddiego
*added the new Delegate class to facilate event handling
*
*/


#endif // _VCF_DELEGATE_H__


