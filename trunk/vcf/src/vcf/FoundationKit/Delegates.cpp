#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadPool.h"

using namespace VCF;


ThreadPool* Delegate::delegateThreadPool = NULL;

struct TypeFind {
	String find_;
public:
	TypeFind( String s):find_(s){}

	bool operator() ( const String& s ) const {
		
		bool result = true;

		if ( s != find_ ) {
			if ( s != (find_ + " *") ) {
				if ( s != (find_ + " &") ) {
					if ( s != ("const " + find_ + " *") ) {
						if ( s != ("const " + find_ + " &") ) {
							result = false;
						}
					}
				}
			}
		}

		return result;
	}
};

bool FunctionTypeInfo::typesMatch( const std::type_info& t1, const std::type_info& t2, bool matchExactly )
{
	bool result = false;

	if ( matchExactly ) {
		result = (t1 == t2) ? true : false;
	}
	else {
		/**
		ultimately what we would like to happen
		here is to match "loosely". In otehr words
		if class B derives from class A, and t1 is of
		type A and t2 is of type B, then the match
		would succeed because of the inheritance
		relationship. At the moment the only way to 
		do this would be to look up the class name in
		the ClassRegistry, but this could easily fail 
		for classes that are not registered with the
		VCF RTTI mechanisms. So for now, we just
		do an "exact" match again :(
		*/	


		String n1 = StringUtils::toString( t1 );
		String n2 = StringUtils::toString( t2 );

		static std::vector<String> primitives;
		if ( primitives.empty() ) {
			primitives.resize(19);
			primitives[0] = "void";
			primitives[1] = "wchar_t";
			primitives[2] = "bool";
			primitives[3] = "char";
			primitives[4] = "signed char";
			primitives[5] = "unsigned char";
			primitives[6] = "short";
			primitives[7] = "unsigned short";
			primitives[8] = "int";
			primitives[9] = "unsigned int";
			primitives[10] = "long";
			primitives[11] = "unsigned long";
			primitives[12] = "long long";
			primitives[13] = "unsigned long long";
			primitives[14] = "float";
			primitives[15] = "double";
			primitives[16] = "long double";
		}

		if ( n1 != n2 ) {
			if ( primitives.end() == std::find_if( primitives.begin(), primitives.end(), TypeFind(n1) ) &&
				primitives.end() == std::find_if( primitives.begin(), primitives.end(), TypeFind(n2) ) ) {

				result = true;
			}
		}
		else {
			result = true;
		}
		
	}

	return result;
}

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
