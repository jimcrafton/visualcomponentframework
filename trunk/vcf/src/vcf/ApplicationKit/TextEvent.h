#ifndef _VCF_TEXTEVENT_H__
#define _VCF_TEXTEVENT_H__
//TextEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_TEXTMODEL_H__
#	include "vcf/ApplicationKit/TextModel.h"
#endif // _VCF_TEXTMODEL_H__

namespace VCF {


/**
\class TextEvent TextEvent.h "vcf/ApplicationKit/TextEvent.h"
*/
class APPLICATIONKIT_API TextEvent : public ModelEvent {
public:
	TextEvent( Object * source):
		ModelEvent( source,0 ),
		selectionStart_(-1),
		selectionLength_(0),
		changeStart_(0),
		changeLength_(0) {}



	TextEvent( Object * source, const String& changedText ) :
		ModelEvent( source,0 ),
		changeText_(changedText),
		selectionStart_(-1),
		selectionLength_(0),
		changeStart_(0),
		changeLength_(0) {}


	TextEvent( Object * source, int selectionStart, ulong32 selectionLength ):
		ModelEvent(source,0),
		selectionStart_(selectionStart),
		selectionLength_(selectionLength),
		changeStart_(0),
		changeLength_(0){}

	TextEvent( Object * source, ulong32 type, const String& changedText, ulong32 changeStart, ulong32 changeLength ):
		ModelEvent(source, type),
		selectionStart_(-1),
		selectionLength_(0),
		changeStart_(changeStart),
		changeLength_(changeLength){

		changeText_ = changedText;
	}

	TextEvent( Object * source, ulong32 type, const String& replacedText, 
				const String& changedText, ulong32 replaceStart, ulong32 replaceLength ):
		ModelEvent(source, type),
		changeText_(changedText),
		originalText_(replacedText),
		selectionStart_(-1),
		selectionLength_(0),
		changeStart_(replaceStart),
		changeLength_(replaceLength){}

		

	TextEvent( const TextEvent& rhs ):ModelEvent(rhs),
		selectionStart_(-1),selectionLength_(0),
		changeStart_(0),
		changeLength_(0){
		*this = rhs;
	}

	virtual ~TextEvent() {}

	TextEvent& operator= ( const TextEvent& rhs ) {
		ModelEvent::operator =( rhs );

		changeText_ = rhs.changeText_;
		originalText_ = rhs.originalText_;
		selectionStart_ = rhs.selectionStart_;
		selectionLength_ = rhs.selectionLength_;

		changeStart_ = rhs.changeStart_;
		changeLength_ = rhs.changeLength_;

		return *this;
	}

    String getChangeText() {
		return changeText_;
	}

	String getOriginalText() {
		return originalText_;
	}

	/**
	*returns the text model associated with this event. May
	*return null if the source of the event was not a TextModel
	*/
	TextModel* getTextModel() {
		return dynamic_cast<TextModel*>(this->getSource() );
	}

	virtual Object* clone( bool deep=false ) {
		return new TextEvent(*this);
	}

	/**
	Returns the current position of the selection. A return 
	value of -1 indicates no current selection. In this case
	the getSelectionLength() will also return 0.
	*/
	int getSelectionStart() const {
		return selectionStart_;
	}

	/**
	Returns the number of characters in the selection
	*/
	ulong32 getSelectionLength() const {
		return selectionLength_;
	}

	/**
	returns the start of the change
	*/
	ulong32 getChangeStart() const {
		return changeStart_;
	}

	/**
	returns the length of the change
	*/
	ulong32 getChangeLength() const {
		return changeLength_;
	}


private:
	String changeText_;
	String originalText_;
	int selectionStart_;
	ulong32 selectionLength_;

	ulong32 changeStart_;
	ulong32 changeLength_;
};





/**
*TextModelEventHandler
*handles the following:
*onTextChanged
*/
template <class SOURCE_TYPE>
class TextModelEventHandler : public EventHandlerInstance<SOURCE_TYPE,TextEvent> {
public:
	TextModelEventHandler( SOURCE_TYPE* source,
		_typename_ EventHandlerInstance<SOURCE_TYPE,TextEvent>::OnEventHandlerMethod handlerMethod,
		const String& handlerName="") :
			EventHandlerInstance<SOURCE_TYPE,TextEvent>( source, handlerMethod, handlerName ) {

	}

};


};


/**
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:25  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.1  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.4  2005/07/09 23:14:55  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.4  2005/05/22 04:05:43  ddiego
*more text edit fixes.
*
*Revision 1.3.2.3  2005/05/18 03:19:17  ddiego
*more text edit changes, fixes some subtle bugs in doc and win32 edit peer.
*
*Revision 1.3.2.2  2005/05/16 00:05:06  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.1  2005/05/02 02:31:42  ddiego
*minor text updates.
*
*Revision 1.3  2004/12/01 04:31:38  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/21 23:41:24  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
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
*Revision 1.10.4.1  2004/04/26 21:58:37  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.9.2.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.9  2003/08/09 02:56:43  ddiego
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
*Revision 1.8.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.8  2003/05/17 20:37:08  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.3  2003/03/23 03:23:47  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.2  2003/03/13 05:07:25  ddiego
*added some more documentation, and implemented the clone() method in all of the
*core event classes for the FoundationKit, GraphicsKit, and ApplicationKit.
*
*Revision 1.7.2.1  2003/03/12 03:09:58  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.14.3  2003/01/08 04:25:56  marcelloptr
*ColorNames static map and Color::s_ now use String instead than String* - VCF_LARGE_COLOR_LIST introduced
*
*Revision 1.6.14.2  2003/01/08 00:19:43  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6.14.1  2002/12/25 22:38:00  ddiego
*more stupid fixes to get rid of the damn gcc no newline warning...grrr...
*
*Revision 1.6  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/04/27 15:52:17  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.5  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_TEXTEVENT_H__


