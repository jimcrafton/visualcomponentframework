#ifndef _VCF_COLUMNMODELEVENT_H__
#define _VCF_COLUMNMODELEVENT_H__
//ColumnModelEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class ColumnItem;

#define COLUMN_MODEL_CONST				1900

#define COLUMN_MODEL_CONTENTS_DELETED		CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 1
#define COLUMN_MODEL_ITEM_CHANGED			CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 2
#define COLUMN_MODEL_ITEM_ADDED				CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 3
#define COLUMN_MODEL_ITEM_DELETED			CUSTOM_EVENT_TYPES + COLUMN_MODEL_CONST + 4


/**
\class ColumnModelEvent ColumnModelEvent.h "vcf/ApplicationKit/ColumnModelEvent.h"
*Class ColumnModelEvent documentation
*/
class ColumnModelEvent : public Event {
public:

	
	ColumnModelEvent( Object* source ):
	  Event( source ), columnItem_(NULL){ }

	ColumnModelEvent( Object* source, const unsigned long& eventType ):
	  Event( source, eventType ), columnItem_(NULL){}

	ColumnModelEvent( Object* source, ColumnItem* item ):
		Event( source ), columnItem_(item){}


	ColumnModelEvent( Object* source, const unsigned long& eventType, ColumnItem* item ):
		Event( source, eventType ), columnItem_(item){}


	virtual ~ColumnModelEvent(){}
	
	ColumnItem* getColumnItem() {
		return columnItem_;
	}
	
	void setColumnItem( ColumnItem* item ) {
		columnItem_ = item;
	}

	ColumnModelEvent( const ColumnModelEvent& rhs ):Event(rhs) {
		*this = rhs;
	}


	ColumnModelEvent& operator=( const ColumnModelEvent& rhs ) {
		Event::operator =( rhs );
		columnItem_ = rhs.columnItem_;

		return *this;
	}
	
	virtual Object* clone( bool deep=false ) {
		return new ColumnModelEvent(*this);
	}
protected:
	ColumnItem* columnItem_;
};

/**
\class ColumnModelEventHandler ColumnModelEvent.h "vcf/ApplicationKit/ColumnModelEvent.h"
*/
template <class SOURCE_TYPE> class ColumnModelEventHandler : public EventHandlerInstance<SOURCE_TYPE,ColumnModelEvent> {
public:
	ColumnModelEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,ColumnModelEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,ColumnModelEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~ColumnModelEventHandler(){};
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:22  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.2.6.1  2006/02/17 05:23:05  ddiego
*fixed some bugs, and added support for minmax in window resizing, as well as some fancier control over tooltips.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
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
*Revision 1.2.22.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.2.22.1  2003/03/12 03:09:50  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COLUMNMODELEVENT_H__


