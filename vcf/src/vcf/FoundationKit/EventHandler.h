#ifndef _VCF_EVENTHANDLER_H__
#define _VCF_EVENTHANDLER_H__
//EventHandler.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class Delegate;


/**
\par
EventHandler's form the back bone of the event
model in the VCF. The EventHandler base class
provides a clean way to invoke the class
specific member function pointers in the
derived EventHandlerInstance template class.
\par
The EventHandler is an abstract class an cannot be created.
Instead you need to derive your own custom class from it
and implement the invoke() method. Typically you can 
just use one of the already provided class, either the 
StaticEventHandlerInstance for wrapping static (or "C" style functions),
or the various template derived classes that wrap a classes 
member function. 

*/
class FOUNDATIONKIT_API EventHandler : public VCF::Object {
public:
	typedef std::vector<EventHandler*> Vector;

	EventHandler(){};

	virtual ~EventHandler();

	/**
	*called during the events dispatch cycle
	*The implemtnation will end up calling the
	*appropriate call back method
	*/
	virtual void invoke( Event* e ) = 0;

	/**
	*adds the EventHandler to it's source object.
	*For this to work the source must be derived
	*from ObjectWithEvents. By adding the event handler
	*to the source, the handler's memory will be cleaned
	*up by the source when the source is destroyed.
	*The EventHandler may be retreived at any time
	*by calling the getEventHandler() method on the
	*source (once again, assuming the source is derived
	*from ObjectWithEvents).
	*@param Object the source to which the EventHandler
	*will be added.
	*@param String the name the EventHandler is referred to.
	*This should be a reasonably unique name.
	*/
	void addHandlerToSource( Object* source, const String& handlerName );

protected:
	
};


/**
EventHandlerInstances are used to provide a
typesafe wrapper around specific class members method pointers.
In addition, when the are created, if the source passed in is
derived from VCF::ObjectWithEvents, then the handler will be
maintained in a list by the source, and destroyed when the source
is destroyed, freeing the creator of the handler from worrying about
memory leaks.
*/
template <class SOURCE, class EVENT>
class EventHandlerInstance : public EventHandler {
public:
	typedef void (SOURCE::*OnEventHandlerMethod)( EVENT* e );

	EventHandlerInstance( SOURCE* source, OnEventHandlerMethod handlerMethod, const String& handlerName="" ) {
		source_ = source;
		handlerMethod_ = handlerMethod;

		addHandlerToSource( source, handlerName );
	}

	virtual ~EventHandlerInstance(){

	}

	virtual void invoke( Event* e ) {
		if ( (NULL != source_) && (NULL != handlerMethod_) ) {
			(source_->*handlerMethod_)( dynamic_cast<EVENT*>(e) );
		}
	}

protected:
	SOURCE* source_;
	OnEventHandlerMethod handlerMethod_;
};

/**
StaticEventHandlerInstance's are used to provide a
typesafe wrapper around a specific class's <b>static</a> function pointers,
as opposed to method pointers (which take the implicit this pointer).
In addition, when they are created, if the source passed in is
derived from VCF::ObjectWithEvents, then the handler will be
maintained in a list by the source, and destroyed when the source
is destroyed, freeing the creator of the handler from worrying about
memory leaks.
*/
template <class EVENT>
class StaticEventHandlerInstance : public EventHandler {
public:
	typedef void (*OnStaticEventHandlerMethod)( EVENT* e );

	StaticEventHandlerInstance( OnStaticEventHandlerMethod handlerMethod,
								Object* source=NULL,
								const String& handlerName="" ) {
		handlerMethod_ = handlerMethod;
		if( NULL != source ) {
			addHandlerToSource( source, handlerName );
		}
	}

	virtual ~StaticEventHandlerInstance(){

	}

	virtual void invoke( Event* e ) {
		if ( NULL != handlerMethod_ ) {
			(*handlerMethod_)( dynamic_cast<EVENT*>(e) );
		}
	}

protected:
	OnStaticEventHandlerMethod handlerMethod_;
};


/**
The GenericEventHandler class is provided as a convenience class for use when dealing with a generic
Event object.
*/
template <class SOURCE_TYPE>
class GenericEventHandler : public EventHandlerInstance<SOURCE_TYPE,Event> {
public:
	GenericEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,Event>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,Event>( source, handlerMethod, handlerName ) {

	}

	virtual ~GenericEventHandler(){};
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.5  2004/12/10 03:32:52  ddiego
*fixed a heap overwrite error in the delegate-event handler code.
*
*Revision 1.4  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.3  2004/08/08 22:09:33  ddiego
*final checkin before the 0-6-5 release
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:07  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.12.4.1  2004/04/26 21:58:36  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.4.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.11  2003/05/17 20:37:07  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.2  2003/05/15 03:01:00  ddiego
*added initial osx source( FoundationKit only),
*plus some fixes to compile under GCC 3.x compilers
*
*Revision 1.10.2.1  2003/03/12 03:09:53  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.8.1  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.9  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.8.6.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.8  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.2  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.7.4.1  2002/03/25 04:19:45  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.7  2002/01/29 17:58:43  ddiego
*deprecated the old style ADD_EVENT, and REMOVE_EVENT, et al macros
*
*Revision 1.6  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_EVENTHANDLER_H__


