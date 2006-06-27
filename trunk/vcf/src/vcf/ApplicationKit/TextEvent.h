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


	TextEvent( Object * source, int selectionStart, uint32 selectionLength ):
		ModelEvent(source,0),
		selectionStart_(selectionStart),
		selectionLength_(selectionLength),
		changeStart_(0),
		changeLength_(0){}

	TextEvent( Object * source, uint32 type, const String& changedText, uint32 changeStart, uint32 changeLength ):
		ModelEvent(source, type),
		selectionStart_(-1),
		selectionLength_(0),
		changeStart_(changeStart),
		changeLength_(changeLength){

		changeText_ = changedText;
	}

	TextEvent( Object * source, uint32 type, const String& replacedText, 
				const String& changedText, uint32 replaceStart, uint32 replaceLength ):
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
	uint32 getSelectionLength() const {
		return selectionLength_;
	}

	/**
	returns the start of the change
	*/
	uint32 getChangeStart() const {
		return changeStart_;
	}

	/**
	returns the length of the change
	*/
	uint32 getChangeLength() const {
		return changeLength_;
	}


private:
	String changeText_;
	String originalText_;
	int selectionStart_;
	uint32 selectionLength_;

	uint32 changeStart_;
	uint32 changeLength_;
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


#endif // _VCF_TEXTEVENT_H__

/**
$Id$
*/
