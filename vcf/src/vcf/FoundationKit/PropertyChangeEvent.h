#ifndef _VCF_PROPERTYCHANGEEVENT_H__
#define _VCF_PROPERTYCHANGEEVENT_H__
//PropertyChangeEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class VariantData;

/**
*Property change event's are used whenever a propertys value changes
*/
class FOUNDATIONKIT_API PropertyChangeEvent : public Event
{
public:
	PropertyChangeEvent( Object * source, VariantData* changeValue, VariantData* originalValue );

	PropertyChangeEvent( const PropertyChangeEvent& rhs ) :Event(rhs) {
		*this = rhs;
	}

	virtual ~PropertyChangeEvent();

	PropertyChangeEvent& operator=( const PropertyChangeEvent& rhs ) {
		Event::operator =( rhs );

		changeValue_ = rhs.changeValue_;
		originalValue_ = rhs.originalValue_;

		return *this;
	}
	/**
	*returns the VariantData that represents the new value
	*/
	VariantData* getChangeValue();

	/**
	*returns a VariantData that represents the original value
	*before the change
	*/
	VariantData* getOriginalValue();

	virtual Object* clone( bool deep=false ) {
		return new PropertyChangeEvent(*this);
	}

private:
	VariantData* changeValue_;
	VariantData* originalValue_;
};




/**
*Classes implmenting this interface <b><i>MUST</i></b> throw PropertyChangeException
*if they do not want the change to be processed.
*/
template <class SOURCE_TYPE>
class PropertyChangeEventHandler : public EventHandlerInstance<SOURCE_TYPE,PropertyChangeEvent> {
public:
	PropertyChangeEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,PropertyChangeEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,PropertyChangeEvent>( source, handlerMethod, handlerName ) {

	}
};


};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.9.4.1  2004/04/26 21:58:37  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.9  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.2.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.8  2003/08/09 02:56:43  ddiego
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
*Revision 1.7.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.7  2003/05/17 20:37:08  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.22.4  2003/03/23 06:46:01  marcelloptr
*minor fixes
*
*Revision 1.6.22.3  2003/03/23 03:23:47  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.22.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.6.22.1  2003/03/12 03:09:57  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_PROPERTYCHANGEEVENT_H__


