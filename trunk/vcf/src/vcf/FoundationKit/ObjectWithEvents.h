#ifndef _VCF_OBJECTWITHEVENTS_H__
#define _VCF_OBJECTWITHEVENTS_H__
//ObjectWithEvents.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define OBJECTWITHEVENTS_CLASSID		"eadd685c-e57b-49c5-b93d-00648641102a"


namespace VCF  {

class NotifyEvent;

/**
*ObjectWithEvents is an object that may
*have 0 or more EventHandlers associated with it,
*and will automatically clean up these EventHandlers
*when it is destroyed. This simplifies handling
*who has to clean up EventHandlers that have been
*allocated on the heap (which they always will be).
*/
class FOUNDATIONKIT_API ObjectWithEvents : public Object {
public:

	ObjectWithEvents();

	virtual ~ObjectWithEvents();

	/**
	*This is a utility method for adding event handlers to an object.
	*Adding a handler provides a convenient way to store the various events
	*an object may wish to listen to. Handlers still need to have their method
	*callbacks set, otherwise nothing will happen. When the object is destroyed
	*all the event handlers in this list are also destroyed.
	*/
	void addEventHandler( const String& handlerName, EventHandler* handler );

	/**
	*Finds a EventHandler handler for a given name. If the object has that
	*handler then a pointer to the is returned otherwise null
	*is returned
	*/
	EventHandler* getEventHandler( const String& handlerName );

	/**
	*Adds the vector of handlers to the master list. This list will be
	*destroyed when the destructor is called
	*/
	void addEventHandlerList( EventHandler::Vector* eventHandlerList );

	/**
	*Notifier events
	*/
	DELEGATE(Notified)

protected:
	/**
	*This map holds a list of EventHandlers that have been
	*added to the object
	*/
	std::map<String,EventHandler*> eventHandlers_;

	/**
	*this vector holds a list of vector that in turn hold a series
	*of 0 or more handlers. The idea is to conserve memory, as each
	*vector defined as a member on the stace in a class adds 16 bytes to
	*the class size, which begins to add up, since there will now
	*be a vector for each type of event method fired, as opposed to a
	*listener for the set
	*/
	std::vector<EventHandler::Vector*> masterHandlerList_;
private:
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.12.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.12  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.4.3  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.11.4.2  2003/10/04 20:14:59  ddiego
*aaddec changes to support compiling on GCC 3.3.1, which is much more
*picky than some of the previous versions.
*
*Revision 1.11.4.1  2003/09/12 16:46:33  ddiego
*finished adding header changes to improve compile speed (at least
*with MS VC++) and to get rid of some of the clutter that the RTTI macros
*add.
*But Where'd the RTTI info go!?!?
*Have no fear it's still there! It is now located in three .inl files, one
*for each kit. Each kit will consolidate it's RTTI decls in the following
*files:
*FoundationKit:
*  vcf/include/FoundationKitRTTI.inl
*GraphicsKit:
*  vcf/include/GraphicsKitRTTI.inl
*ApplicationKit:
*  vcf/include/ApplicationKitRTTI.inl
*
*Please alter these files as neeccessary to add/subtract/alter the various
*RTTI info. Each kit is also responsible for registering any of the class
*in the ClassRegistry.
*A side effect of this is that I had to alter the memory allocation for the
*VC6 build for the Application it went from /Zm120 to /Zm150. I find this
*pretty lame but I don't know what else to do. Hopefully this will improve
*compile times when using the Appkit in other programs.
*
*Revision 1.11  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.1  2003/03/12 03:09:40  ddiego
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
*Revision 1.7.4.1  2002/03/20 21:56:55  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.7  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_OBJECTWITHEVENTS_H__


