#ifndef _VCF_DRAGEVENT_H__
#define _VCF_DRAGEVENT_H__
//DragEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {
/**
\class DragSourceEvent DragEvent.h "vcf/ApplicationKit/DragEvent.h"
*/
class APPLICATIONKIT_API DragSourceEvent : public Event {
public:
	DragSourceEvent( Object* source, VCF::DataObject* data ):
		Event( source ){
		data_ = data;
	}

	DragSourceEvent( Object* source, VCF::DataObject* data,
		       const uint32& keyMask, const uint32& buttonMask,
			   const DragActionType& action ):
		Event( source ){
		data_ = data;
		keyMask_ = keyMask;
		buttonMask_ = buttonMask;
		action_ = action;
	}


	DragSourceEvent( const DragSourceEvent& rhs ):Event(rhs) {
		*this = rhs;
	}

	virtual ~DragSourceEvent(){};

	DragSourceEvent& operator=( const DragSourceEvent& rhs ) {
		Event::operator =( rhs );

		data_ = rhs.data_;
		keyMask_ = rhs.keyMask_;
		buttonMask_ = rhs.buttonMask_;
		action_ = rhs.action_;


		return *this;
	}

	virtual Object* clone( bool deep=false ) {
		return new DragSourceEvent(*this);
	}


	VCF::DataObject* getDataObject() {
		return data_;
	}

	uint32 getButtonMask() {
		return buttonMask_;
	}

	void setButtonMask( const uint32& buttonMask ) {
		buttonMask_ = buttonMask;
	}

    uint32 getKeyMask() {
		return keyMask_;
	}

	void setKeyMask( const uint32& keyMask ) {
		keyMask_ = keyMask;
	}

	/**
	*
	*/
	void setActionType( const DragActionType& action ) {
		action_ = action;
	}
	/**
	*get the type of action the event represents
	*/
	DragActionType getAction() {
		return action_;
	}

private:
    VCF::DataObject* data_;
	uint32 keyMask_;
    uint32 buttonMask_;
	DragActionType action_;
};

typedef Delegate1<DragSourceEvent*> DragSourceDelegate; 


}


#endif // _VCF_DRAGEVENT_H__

/**
$Id$
*/
