#ifndef _DELEGATES_H__
#define _DELEGATES_H__

#ifndef _THREADPOOL_H__
#include "ThreadPool.h"
#endif


namespace VCF {




class CallBack {
public:
	virtual ~CallBack(){
		argumentTypes.clear();
	}

	String name;

	uint32 getArgumentCount() const {
		return argumentTypes.size();
	}

	const std::type_info& getArgumentTypeInfo( const uint32& index ) const {
		return *argumentTypes.at( index );
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(void);
	}

	static void addArgumentTypeInfo( CallBack& cb, const std::type_info& ti ) {	
		cb.argumentTypes.push_back( &ti );
	}
	
protected:
	std::vector<const std::type_info*> argumentTypes;
};








class delegate {
public:

	static ThreadPool* delegateThreadPool;

	static void initThreadPool() {
		if ( NULL == delegateThreadPool ) {
			delegateThreadPool = new ThreadPool(3);
			delegateThreadPool->start();
		}
	}

	static void terminateThreadPool() {
		if ( NULL != delegateThreadPool ) {
			delegateThreadPool->stop();

			delete delegateThreadPool;
		}
	}


	static ThreadPool* getThreadPool() {
		if ( NULL == delegateThreadPool ) {
			delegate::initThreadPool();
		}
		return delegateThreadPool;
	}


	~delegate() {
		clear();
	}

	bool empty() const {
		return functions.empty();
	}

	size_t size() const {
		return functions.size();
	}


	void clear() {
		std::vector<CallBack*>::iterator it = functions.begin();
		while ( it != functions.end() ) {
			delete *it;
			++it;
		}

		functions.clear();
	}


	void add( CallBack* callback ) {
		std::vector<CallBack*>::iterator found = 
			std::find( functions.begin(), functions.end(), callback );

		if ( found == functions.end() ) {
			functions.push_back( callback );
		}
	}

	void remove( CallBack* callback ) {
		std::vector<CallBack*>::iterator found = 
			std::find( functions.begin(), functions.end(), callback );

		if ( found != functions.end() ) {
			functions.erase( found );
		}
	}

	const CallBack& at( const uint32& index ) const {
		return *functions.at( index );
	}


	std::vector<CallBack*> functions;
};




class AsyncResult;


class AsyncReturns {
public:
	virtual ~AsyncReturns(){};

	virtual void functionFinished( AsyncResult*, Runnable* runnable ) = 0;
};



template <typename P1>
class Procedure1 : public CallBack {
public:

	typedef Procedure1<AsyncResult*> AsyncCallback;

	virtual ~Procedure1(){}

	typedef void (*FuncPtr)(P1);


	Procedure1():staticFuncPtr(NULL){
		CallBack::addArgumentTypeInfo(*this, typeid(P1) );
	}

	Procedure1(FuncPtr funcPtr):staticFuncPtr(funcPtr){
		CallBack::addArgumentTypeInfo(*this, typeid(P1) );
	}



	virtual void invoke( P1 p1 ) {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)( p1 );
		}
	}


	virtual void beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
};



class AsyncResult : public Object, public Waitable {
public:
	typedef Procedure1<AsyncResult*> AsyncCallback;

	typedef std::pair<AsyncReturns*,Runnable*>  CallbackWork;

	//AsyncResult(Runnable* internalRunnable, AsyncCallback* callback ): completed_(false), 
	//				resultWait_(&resultWaitMtx_), 
	//				callback_(callback),
	//				runCallbacksAsync_(false){
	//	internalRunnables_.push_back(internalRunnable);
	//}

	AsyncResult(AsyncCallback* callback): completed_(false), 
					resultWait_(&resultWaitMtx_), 
					callback_(callback),
					runCallbacksAsync_(false) {}


	virtual ~AsyncResult(){}


	class AsyncTask : public Runnable {
	public:

		AsyncTask( AsyncResult* res, AsyncReturns* returnObject, Runnable* internalRunnable ):
			res_(res),returnObject_(returnObject),internalRunnable_(internalRunnable) {	}


		virtual ~AsyncTask(){}

		virtual bool run() {

			internalRunnable_->run();

			returnObject_->functionFinished( res_, internalRunnable_ );

			res_->internal_removeRunnable( this );
			return true;
		}

		virtual void stop(){}

		AsyncResult* res_;
		AsyncReturns* returnObject_;
		Runnable* internalRunnable_;
	};

	class Task : public Runnable {
	public:

		Task( AsyncResult* res ):res_(res) {

		}

		virtual ~Task(){}

		virtual bool run() {

			res_->internal_run();

			return true;
		}

		virtual void stop(){}

		AsyncResult* res_;
	};

	friend class Task;
	friend class AsyncTask;


	void doWork() {
		if ( runCallbacksAsync_ ) {
			std::vector<CallbackWork>::iterator it = internalRunnables_.begin();
			while ( it != internalRunnables_.end() ) {
				delegate::getThreadPool()->postWork( new AsyncTask(this,(*it).first, (*it).second) );
				++it;
			}
		}
		else {
			delegate::getThreadPool()->postWork( new Task(this) );
		}
	}

	virtual WaitResult wait() {
		{
			Lock l(runnableMtx_);
			if ( completed_ || internalRunnables_.empty() ) {
				return wrWaitFinished;
			}
		}
		return resultWait_.wait();
	}

	virtual WaitResult wait( uint32 milliseconds ) {
		{
			Lock l(runnableMtx_);
			if ( completed_ || internalRunnables_.empty() ) {
				return wrWaitFinished;
			}
		}
		
		return resultWait_.wait( milliseconds );
	}

	virtual OSHandleID getPeerHandleID() {
		return resultWait_.getPeerHandleID();
	}


	void internal_run();

	bool isCompleted() const {
		return completed_;
	}

	void* getUserData() const;

	void internal_addRunnable( AsyncReturns* returnObject, Runnable* internalRunnable ) {
		internalRunnables_.push_back(CallbackWork(returnObject,internalRunnable));
	}
	
	void setRunCallbacksAsynchronously( bool val ) {
		runCallbacksAsync_ = val;
	}
protected:
	bool completed_;
	bool runCallbacksAsync_;
	Condition resultWait_;
	Mutex resultWaitMtx_;

	Mutex runnableMtx_;

	

	std::vector<CallbackWork> internalRunnables_;
	AsyncCallback* callback_;

	void internal_removeRunnable( Runnable* val ) {
		bool done = false;
		{
			Lock l(runnableMtx_);
			
			std::vector<CallbackWork>::iterator found = 
				internalRunnables_.begin();
			while ( found != internalRunnables_.end() ) {
				if ( found->second = val ) {
					internalRunnables_.erase( found );
					delete val;
					break;
				}
				++ found;
			}

			done = internalRunnables_.empty();
		}

		if ( done ) {
			completed_ = true;
			resultWait_.broadcast();

			if ( NULL != callback_ ) {
				callback_->invoke( this );
			}
		}
	}
};


typedef Procedure1<AsyncResult*> AsyncCallback;


template <typename P1, typename ClassType=NullClassType1<P1> >
class ClassProcedure1 : public Procedure1<P1> {
public:
	typedef void (ClassType::*ClassFuncPtr)(P1);


	ClassProcedure1():
		Procedure1<P1>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure1(ClassType* src, ClassFuncPtr funcPtr):
		Procedure1<P1>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassProcedure1(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure1<P1>(),classFuncPtr(funcPtr),funcSrc(src){
		name = s;
	}



	virtual void invoke( P1 p1 ) {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)( p1 );
		}
	}

	virtual void beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
};





template <typename P1>
class Delagate1 : public delegate, public AsyncReturns {
public:
	typedef void (*FuncPtr)(P1);	
	typedef Procedure1<P1> CallbackType;

	Delagate1<P1>& operator+= ( FuncPtr rhs ) {
		CallbackType* cb = new CallbackType(rhs);
		add( cb );
		return *this;
	}
	
	Delagate1<P1>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}


	void invoke( P1 p1 ) {
		std::vector<CallBack*>::iterator it = functions.begin();
		while ( it != functions.end() ) {
			CallBack* cb = *it;
			CallbackType* callBack = (CallbackType*)cb;

			callBack->invoke( p1 );

			++it;
		}
	}

	
	AsyncResult* beginInvoke( P1 p1, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback);

		std::vector<CallBack*>::iterator it = functions.begin();
		while ( it != functions.end() ) {
			CallBack* cb = *it;
			CallbackType* callBack = (CallbackType*)cb;

			callBack->beginInvoke( p1, result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};






template <typename ReturnType, typename P1, typename P2>
class Function2 : public CallBack {
public:
	typedef ReturnType (*FuncPtr)(P1,P2);


	virtual ~Function2(){}

	Function2():staticFuncPtr(NULL){
		CallBack::addArgumentTypeInfo(*this, typeid(P1) );
		CallBack::addArgumentTypeInfo(*this, typeid(P2) );
	}

	Function2(FuncPtr funcPtr):staticFuncPtr(funcPtr){
		CallBack::addArgumentTypeInfo(*this, typeid(P1) );
		CallBack::addArgumentTypeInfo(*this, typeid(P2) );
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual ReturnType invoke( P1 p1, P2 p2 ) {
		ReturnType result = ReturnType();
		if ( NULL != staticFuncPtr ) {
			result = (*staticFuncPtr)( p1, p2 );
		}
		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	FuncPtr staticFuncPtr;
};


template <typename ReturnType, 
		typename P1, 
		typename P2, 
		typename ClassType=NullReturnClassType2<ReturnType,P1,P2> 
		>
class ClassFunction2 : public Function2<ReturnType,P1,P2> {
public:
	typedef ReturnType (ClassType::*ClassFuncPtr)(P1,P2);


	ClassFunction2():
		Function2<ReturnType,P1,P2>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassFunction2(ClassType* src, ClassFuncPtr funcPtr):
		Function2<ReturnType,P1,P2>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassFunction2(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Function2<ReturnType,P1,P2>(),classFuncPtr(funcPtr),funcSrc(src){
		name = s;
	}



	virtual ReturnType invoke( P1 p1, P2 p2 ) {
		ReturnType result = ReturnType();

		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			result = (funcSrc->*classFuncPtr)( p1, p2 );
		}

		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );
	
	

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
};

template <typename ReturnType>
class ResultsCache {
public:
	typedef std::vector<ReturnType> Results;
	typedef std::map<AsyncResult*,Results*> CacheMap;

	ResultsCache():cache_(NULL){}

	~ResultsCache(){		
		Lock l(asyncResultsMtx_);
		if ( NULL != cache_ ) {				
			CacheMap::iterator it = cache_->begin();
			while ( it != cache_->end() ) {
				delete it->second;
				++it;
			}
			delete cache_;
		}		
	}
	
	void addResult( ReturnType result, AsyncResult* asyncRes ) {
		
		Lock l(asyncResultsMtx_);

		if ( NULL == cache_ ) {
			cache_ = new CacheMap();
		}

		Results* results = NULL;
		CacheMap::iterator found = cache_->find( asyncRes );
		if ( found == cache_->end() ) {
			results = new Results();
			cache_->insert( CacheMap::value_type(asyncRes,results) );
		}
		else {
			results = found->second;
		}
		
		results->push_back( result );	
	}


	ReturnType getLastResult( AsyncResult* asyncResult )  {
		ReturnType result = ReturnType();

		Results* results = getResults( asyncResult );
		{
			Lock l(asyncResultsMtx_);
			if ( NULL != results ) {
				if ( !results->empty() ) {
					result = results->back();
				}
			}
		}

		return result;
	}

	Results* getResults( AsyncResult* asyncResult ) {
		Results* result = NULL;

		Lock l(asyncResultsMtx_);
		
		if ( NULL != cache_ ) {
			
			CacheMap::iterator found = cache_->find( asyncResult );
			if ( found != cache_->end() ) {
				result = found->second;
			}
		}

		return result;
	}
protected:
	Mutex asyncResultsMtx_;
	CacheMap* cache_;
};	

template <typename ReturnType, typename P1, typename P2>
class Delagate2R : public delegate, public AsyncReturns {
public:
	typedef Function2<ReturnType,P1,P2> CallbackType;
	typedef _typename_ CallbackType::FuncPtr FuncPtr;

	typedef std::vector<ReturnType> Results;


	Delagate2R(){}

	virtual ~Delagate2R(){}

	Delagate2R<ReturnType,P1,P2>& operator+= ( FuncPtr rhs ) {
		CallbackType* cb = new CallbackType(rhs);
		add( cb );
		return *this;
	}
	
	Delagate2R<ReturnType,P1,P2>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}


	ReturnType invoke( P1 p1, P2 p2 ) {
		ReturnType result = ReturnType();

		results.clear();

		if ( !functions.empty() ) {
			
			size_t i = 0;
			results.resize( functions.size() );
			
			std::vector<CallBack*>::iterator it = functions.begin();
			while ( it != functions.end() ) {
				CallBack* cb = *it;
				CallbackType* callBack = (CallbackType*)cb;
				
				results[i] = callBack->invoke( p1, p2 );

				++i;
				++it;
			}

			result = results.back();
		}

		return result;
	}


	AsyncResult* beginInvoke( P1 p1, P2 p2, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback);

		std::vector<CallBack*>::iterator it = functions.begin();
		while ( it != functions.end() ) {
			CallBack* cb = *it;
			CallbackType* callBack = (CallbackType*)cb;

			callBack->beginInvoke( p1, p2, result, callback, this );			

			++it;
		}

		result->doWork();

		return result;
	}


	ReturnType endInvoke( AsyncResult* asyncResult );

	Results endInvokeWithResults( AsyncResult* asyncResult );
	

	virtual void functionFinished( AsyncResult*, Runnable* runnable );

	Results results;
protected:
	ResultsCache<ReturnType> resultsCache_;
};


template <typename P1>
inline void Procedure1<P1>::beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedProcedure1<P1> proc(p1, staticFuncPtr);

		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename P1, typename ClassType>
inline void ClassProcedure1<P1,ClassType>::beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedProcedure1<P1,ClassType> proc(funcSrc, p1, classFuncPtr);
	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

inline void AsyncResult::internal_run()
{

	VCF_ASSERT( !internalRunnables_.empty() );

	std::vector<CallbackWork>::iterator it = internalRunnables_.begin();
	while ( it != internalRunnables_.end() ) {
		CallbackWork& cw = *it;
		cw.second->run();
		cw.first->functionFinished( this, cw.second );
		++it;
	}


	completed_ = true;
	resultWait_.broadcast();


	if ( NULL != callback_ ) {
		callback_->invoke( this );
	}
}

template <typename P1>
inline void Delagate1<P1>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}





template <typename ReturnType, typename P1, typename P2>
inline void Function2<ReturnType,P1,P2>::beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedFunction2<ReturnType,P1,P2> proc(p1, p2, staticFuncPtr);

		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}


template <typename ReturnType, typename P1, typename P2, typename ClassType>
inline void ClassFunction2<ReturnType,P1,P2,ClassType>::beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedFunction2<ReturnType,P1,P2,ClassType> proc(funcSrc, p1, p2, classFuncPtr);
	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename ReturnType, typename P1, typename P2>
inline void Delagate2R<ReturnType,P1,P2>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	ThreadedFunction2<ReturnType,P1,P2>* funcParams = (ThreadedFunction2<ReturnType,P1,P2>*)runnable;

	ReturnType ret = funcParams->returnValue();

	resultsCache_.addResult( ret, res );
}

template <typename ReturnType, typename P1, typename P2>
inline ReturnType Delagate2R<ReturnType,P1,P2>::endInvoke( AsyncResult* asyncResult )
{
	ReturnType result = resultsCache_.getLastResult( asyncResult );

	return result;
}

template <typename ReturnType, typename P1, typename P2>
inline Delagate2R<ReturnType,P1,P2>::Results Delagate2R<ReturnType,P1,P2>::endInvokeWithResults( AsyncResult* asyncResult )
{
	Results result;

	Results* res = resultsCache_.getResults();
	
	if ( NULL != res ) {
		result = *res;
	}
	

	return result;
}
	

}; //namespace VCF

#endif //_DELEGATES_H__

