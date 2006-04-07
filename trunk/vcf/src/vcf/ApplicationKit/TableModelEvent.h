#ifndef _VCF_TABLEMODELEVENT_H__
#define _VCF_TABLEMODELEVENT_H__
//TableModelEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

#define TABLEMODEL_EVENT_CONST						2000
#define COLUMNS_DELETED					CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 1
#define COLUMNS_ADDED					CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 2
#define ROWS_DELETED						CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 3
#define ROWS_ADDED						CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 4
#define CELL_CHANGED					CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 5
#define ALL_COLUMNS_CHANGED				CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 6
#define ALL_ROWS_CHANGED				CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 7
#define ALL_ITEMS_DELETED				CUSTOM_EVENT_TYPES + TABLEMODEL_EVENT_CONST + 8

#define NO_ROW_CHANGED					-1
#define NO_COLUMN_CHANGED				-1

/**
\class TableModelEvent TableModelEvent.h "vcf/ApplicationKit/TableModelEvent.h"
*/
class APPLICATIONKIT_API TableModelEvent : public Event {
public:

	TableModelEvent( Object* source, const ulong32& eventType,
		             const int& startRow =-1, const int& rowCount=0,
					 const int& startColumn =-1, const int& columnCount =0):
		Event(source,eventType),
		startRow_(startRow),
		numberOfRowsAffected_(rowCount),
		startColumn_(startColumn),
		numberOfColumnsAffected_(columnCount){

	}

	TableModelEvent( const TableModelEvent& rhs ):Event(rhs) {
		*this = rhs;
	}
	virtual ~TableModelEvent(){};


	TableModelEvent& operator=( const TableModelEvent& rhs ) {
		Event::operator =( rhs );
		startRow_ = rhs.startRow_;
		numberOfRowsAffected_ = rhs.numberOfRowsAffected_;

		startColumn_ = rhs.startColumn_;
		numberOfColumnsAffected_ = rhs.numberOfColumnsAffected_;

		return *this;
	}


	/**
	*get the row that changed. a return of -1 means no rows
	*changed for this event
	*/
	int getStartRowThatChanged() {
		return startRow_;
	}

	int getNumberOfRowsAffected() {
		return numberOfRowsAffected_;
	}

	int getStartColumnThatChanged() {
		return startColumn_;
	}

	int getNumberOfColumnsAffected() {
		return numberOfColumnsAffected_;
	}



	virtual Object* clone( bool deep=false ) {
		return new TableModelEvent(*this);
	}
private:
	int startRow_;
	int numberOfRowsAffected_;
	int startColumn_;
	int numberOfColumnsAffected_;
};




/**
*TableModelEventHandler
*handles the following:
*onChange
*/
template <class SOURCE_TYPE>
class TableModelEventHandler : public EventHandlerInstance<SOURCE_TYPE,TableModelEvent> {
public:
	TableModelEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,TableModelEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,TableModelEvent>( source, handlerMethod, handlerName ) {

	}

	virtual ~TableModelEventHandler(){};
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:25  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:19  ddiego
*migration towards new directory structure
*
*Revision 1.10.2.1  2004/04/26 21:58:37  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.9.2.1  2004/01/29 22:26:47  ddiego
*table fixes, this still needs some more work
*
*Revision 1.9  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.8.2.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
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
*Revision 1.6.2.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.6.2.1  2003/03/12 03:09:58  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.20.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TABLEMODELEVENT_H__


