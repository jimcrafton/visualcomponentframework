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
	/**
	\class FrameEvent FrameEvent.h "vcf/ApplicationKit/FrameEvent.h"
	*/
	class APPLICATIONKIT_API FrameEvent : public Event {
	public:
		FrameEvent( Object* source ) : Event(source),okToClose_(true) {};

		FrameEvent( Object* source, const uint32& eventType ):Event(source, eventType),okToClose_(true) {};

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

	/**

	*/
	typedef Delegate1<FrameEvent*> FrameDelegate; 
	typedef FrameDelegate::ProcedureType FrameHandler;
};


#endif // _VCF_FRAMEEVENT_H__

/**
$Id$
*/
