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
\class Delegate Delegate.h "vcf/FoundationKit/Delegate.h"
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
		VCF_ASSERT( NULL != handler );

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
		VCF_ASSERT( NULL != handler );

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

				EventHandler* handler = *it;
				
				VCF_ASSERT( NULL != handler );

				handler->invoke( event );

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
			VCF_ASSERT( NULL != result );
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

	/**
	This allows you to retreive a copy of the handlers registered with this 
	delegate.
	@param EventHandler::Vector a reference to a std::vector<EventHandler*>
	that will be filled with the event handlers registered with this
	delegate.
	@return bool returns true if the handlers were successfully copied over.
	Otherwise returns false. A delegate with no handlers will also return 
	false.
	*/
	inline bool getEventHandlers( EventHandler::Vector& handlers ) {
		if ( NULL != handlers_ ) {
			handlers = *handlers_;
		}

		return !handlers.empty();
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


#endif // _VCF_DELEGATE_H__

/**
$Id$
*/
