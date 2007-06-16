#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadPool.h"

using namespace VCF;


ThreadPool* Delegate::delegateThreadPool = NULL;


void Delegate::initThreadPool() 
{
	if ( NULL == delegateThreadPool ) {
		delegateThreadPool = new ThreadPool(3);
		delegateThreadPool->start();
	}
}

void Delegate::terminateThreadPool() 
{
	if ( NULL != delegateThreadPool ) {
		delegateThreadPool->stop();

		delete delegateThreadPool;
	}
}


ThreadPool* Delegate::getThreadPool() 
{
	if ( NULL == delegateThreadPool ) {
		Delegate::initThreadPool();
	}
	return delegateThreadPool;
}



void AsyncResult::doWork() 
{
	{
		Lock l(runnableMtx_);
		if ( internalRunnables_.empty() ) {
			completed_ = true;
			resultWait_.broadcast();
			return;
		}
	}

	{
		Lock l(runnableMtx_);
		completed_ = false;
	}

	if ( runCallbacksAsync_ ) {
		std::vector<CallbackWork>::iterator it = internalRunnables_.begin();
		while ( it != internalRunnables_.end() ) {
			Delegate::getThreadPool()->postWork( new AsyncTask(this,(*it).first, (*it).second) );
			++it;
		}
	}
	else {
		Delegate::getThreadPool()->postWork( new Task(this) );
	}
}




void ObjectWithCallbacks::addCallback( CallBack* cb )
 {
	VCF_ASSERT( cb->getSource() == this );

	if ( cb->getSource() != this ) {
		throw RuntimeException( "callback cannot be added to this object because it's source is either not set or note set to this instance." );
	}

	if ( NULL == callbacks_ ) {
		callbacks_ = new std::map<String,CallBack*>();
	}

	std::map<String,CallBack*>::iterator found = 
		callbacks_->find( cb->getName() );
	if ( found == callbacks_->end() ) {
		(*callbacks_)[ cb->getName() ] = cb;
	}
	else {
		throw RuntimeException( "Callback already exists with the name." + cb->getName() );
	}
}

CallBack* ObjectWithCallbacks::getCallback( const String& name ) {
	CallBack* result = NULL;

	if ( NULL != callbacks_ ) {
		std::map<String,CallBack*>::iterator found = 
			callbacks_->find( name );
		if ( found != callbacks_->end() ) {
			result = found->second;
		}
	}
	return result;
}

void ObjectWithCallbacks::removeCallback( CallBack* cb )
{
	if ( NULL != callbacks_ ) {
		std::map<String,CallBack*>::iterator found = 
			callbacks_->find( cb->getName() );
		if ( found != callbacks_->end() ) {
			if ( found->second == cb ) {
				callbacks_->erase( found );
			}
		}
	}
}

ObjectWithCallbacks::~ObjectWithCallbacks()
{
	if ( NULL != callbacks_ ) {
		size_t cbSize = callbacks_->size();
		while ( cbSize > 0 ) {
			
			std::map<String,CallBack*>::iterator it = 
				callbacks_->begin();
			
			CallBack* cb = it->second;
			cb->free();
			
			cbSize --;
		}

		delete callbacks_;
	}
}

void CallBack::addToSource( Object* source )
{
	VCF_ASSERT( NULL != source );
	
	if ( NULL != source ) {
		ObjectWithCallbacks* objCB = dynamic_cast<ObjectWithCallbacks*>( source );
		
		if ( NULL != objCB ) {
			objCB->addCallback( this );
		}
	}
}

void CallBack::destroy()
{
	delegate_->remove( this );

	Object* src = getSource();

	if ( NULL != src ) {
		ObjectWithCallbacks* objCB = dynamic_cast<ObjectWithCallbacks*>( src );

		
		if ( NULL != objCB ) {
			objCB->removeCallback( this );
		}
	}
}
