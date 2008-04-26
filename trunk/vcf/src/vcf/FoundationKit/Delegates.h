#ifndef _VCF_DELEGATES_H__
#define _VCF_DELEGATES_H__



/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




#ifndef _VCF_THREADED_FUNCTIONS_H__
#include "vcf/FoundationKit/ThreadedFunctions.h"
#endif 





/**
Use this macro to make sure you define a delegate named "name", and an accessor function
called get<name>, which will return a reference to the delegate.
*/
#define DELEGATE(type, name)\
	type name;\
	type& get##name() {\
		return name;\
	}\
	\




namespace VCF {


/**
\class FunctionTypeInfo Delegates.h "vcf/FoundationKit/Delegates.h"
Base class for storing function information for a delegate.
The class stores an array of std::type_info for each 
argument of the function the class is used to 
represent. This is then used to compare to FunctionTypeInfo
instance's and verify that they are the same (or not).
*/
class FOUNDATIONKIT_API FunctionTypeInfo {
public:
	typedef std::vector<const std::type_info*> TypeArray;
	
	virtual ~FunctionTypeInfo() {}

	virtual const std::type_info& getReturnType() const {
		return typeid(void);
	}

	virtual TypeArray getArgumentTypes() const {
		return TypeArray();
	};

	static void addArgumentTypeInfo( TypeArray& types, const std::type_info& ti ) {	
		types.push_back( &ti );
	}

	static bool typesMatch( const std::type_info& t1, const std::type_info& t2, bool matchExactly = false ); 

	bool operator == ( const FunctionTypeInfo& rhs ) const {
		bool result = false;

		TypeArray types = getArgumentTypes();

		TypeArray rhsTypes = rhs.getArgumentTypes();
		
		result = types.size() == rhsTypes.size();
		if ( types.size() == rhsTypes.size() ) {
			for (size_t i=0;i<types.size();i++ ) {
				result = FunctionTypeInfo::typesMatch( *(types[i]), *(rhsTypes[i]) );
				if ( !result ) {
					break;
				}
			}

			if ( result ) {
				result = FunctionTypeInfo::typesMatch( getReturnType(), rhs.getReturnType() );
			}
		}

		return result;
	}
};






class Delegate;
class ObjectWithCallbacks;

/**
\class CallBack Delegates.h "vcf/FoundationKit/Delegates.h"
Base class for a function callback. This class is used to wrap a 
C++ function pointer, either a static function, or a C++ class
member function. The class can have an optional name that may be
used to reference it for later use. A callback is attached to 
delegate. Calling the invoke function on a delegate causes the 
delegate to pass this along and call an invoke function on all 
of the callbacks registered with it. 

Note that some of the documentation here will introduce
methods that are not directly declared on the Delegate 
base class, but instead are declared and implemented in
derived classes. This specifically the case for the 
invoke(), beginInvoke(), and endInvoke() methods. 
However their usage is identical, the only difference is 
in the return type (if any) and the number of function
arguments that they take.

A callback may be associated with multiple Delegates. Because of this
the callback stores a list of delegates that it is registered with.
When the callback is deleted, it will remove it self from any 
delegates that it is still registered with at that point.

If a callback has a source, then the source will clean up the instance
of the CallBack and you don't have to worry about freeing the 
memory instance. If the callback does \em not have a source, then
it is up to the programmer to delete it. 

You cannot call the delete operator directly on a CallBack instance. 
Instead use the CallBack::free() member function to delete an instance. 

Classes that derive from CallBack are classed into 2 main categories,
functions that return some type, and functions that have a void 
return type (they return nothing). The naming convention used is that 
a procedure refers to a function with a void return type, and a function
is used to refer to something that \em does return something, e.g.
\code
void someFunction( int t );
\endcode
Note that this is \not the same as 
\code
void* someFunction( int t );
\endcode
Now we do have an actual return type ( a void pointer ).

Therefore all callback classes that wrap a procedure will be named 
ProcedureX where X indicates the number of arguments the procedure
takes. So 
\code
void foobar()
\endcode
is represented by the class Procedure and 
\code
void foobar2( const String, int, bool )
\endcode
is represented by the class Procedure3.

A callback class that wraps a function is named FunctionX where 
X is the number arguments that the function takes. For example:
\code
int foobar(char*)
\endcode
is represented by the class Function1.

Within these two groups there is a further distinction between static functions
and functions that are C++ member functions that require a "this" pointer.
Consider the following:
\code
int someFunc( int );

class MyClass {
public:
  void doit();
  static void dontDoIt();
};
\endcode

Both someFunc and MyClass::dontDoIt are considered static functions. However
MyClass::doit is a member function, and requires special treatment
according to the rules of C++ function binding.

To handle C++ member functions we also derive classes from the various
ProcedureX and FunctionX classes. These are named ClassProcedureX and
ClassFunctionX where X defines the number of arguments the 
member function takes. So the following 
\code
class MyClass {
public:
  void doit( int, bool );
  static void dontDoIt();
};
\endcode

uses the callback class ClassProcedure2 wrap MyClass::doit.

*/
class FOUNDATIONKIT_API CallBack : public Object, public FunctionTypeInfo {
public:

	typedef std::vector<CallBack*> Vector;

	CallBack():delegates_(NULL){}

	CallBack( const String& str ): name(str),delegates_(NULL){}

	CallBack( Object* source, const String& str ): name(str),delegates_(NULL){
		addToSource( source );
	}

	/**
	Deletes the instance of the callback. You must use this
	method to delete a callback, i.e.
	\code
	CallBack* cb =  //some callback...

	//delete the callback
	//(a) Right way:
	cb->free();

	//(b) wrong way
	delete cb
	\endcode
	Note that not only is the second technique (b) not allowed
	but you will get a compile error as the destructor is marked
	as protected.
	*/
	void free();


	/**
	The name of the callback. It can be anything
	you want, although the convention is the fully
	qualified C++ function name (like "SomeClass::someFunction" ).
	The name is optional and it may be an empty string.
	*/
	String getName() const {
		return name;
	}
	
	/**
	A callback may, or may not, have a 
	source. In addition, it's possible
	that the source is *not* an Object 
	based type. For this reason this 
	function is made virtual so that 
	derived classes can properly implement
	it and return a valid source point
	if possible.
	@return Object the object that "owns"
	the callback and will delete it when the
	object is deleted. This means that the
	callback;s lifetime is that of it's 
	owning object unless it's explicitly
	removed from the object and deleted.
	*/
	
	virtual Object* getSource() {
		return NULL;
	}

	/**
	Add the callback to a source. If the Object instance
	is derived from ObjectWithCallbacks, then the 
	ObjectWithCallbacks::addCallback will get called
	for you. Otherwise nothing happens. This method will
	get called automatically for you by the framework.
	@see ObjectWithCallbacks
	*/
	void addToSource( Object* source );

	friend class Delegate;
	friend class ObjectWithCallbacks;
protected:	

	

	typedef std::vector<Delegate*> DelegatesArray;
	String name;

	void addDelegate( Delegate* val ) {

		if ( NULL == delegates_ ) {
			delegates_ = new DelegatesArray();
		}

		delegates_->push_back( val );
	}

	void removeDelegate( Delegate* val ) {

		if ( NULL != delegates_ ) {
			DelegatesArray::iterator found = 
				std::find( delegates_->begin(), delegates_->end(), val );
			if ( found != delegates_->end() ) {
				delegates_->erase( found );
			}
		}		
	}

	DelegatesArray* delegates_;	

	
protected:
	virtual ~CallBack(){};
private:
	CallBack( const CallBack& rhs ); //no copies for now
	
};






/**
\class ObjectWithCallbacks Delegates.h "vcf/FoundationKit/Delegates.h"
ObjectWithCallbacks is an object that may
have 0 or more CallBacks associated with it,
and will automatically clean up these CallBacks
when it is destroyed. This simplifies handling
who has to clean up a CallBack that may have been
allocated on the heap (which they always will be).

Because the collection is a map, a CallBack may be
retrieved for future use - that is it may be reused by 
another delegate. For example:
\code
class Stuff : public ObjectWithCallbacks {
public:
	void onEvent( Event* e ) {
		
	}

};

int main() 
{
	FoundationKit::init();

	Stuff stuff;
	
	CallBack* ev = 
		new ClassProcedure1<Event*,Stuff>(&stuff,&Stuff::onEvent,"Stuff::onEvent");
	
	FoundationKit::terminate();
	return 0;
}

\endcode

This adds the new callback (ev) to the stuff instance. The callback can
then be retreived at any time:

\code
void someFunction( Stuff* stuff ) 
{
	CallBack* stuffHandler = stuff->getCallback( "Stuff::onEvent" );
	//use the stuffHandler somehow...
}
\endcode


Note that the ObjectWithCallbacks should not be created directly. Instead derive a 
new custom class using this as a base class.

*/

#define OBJECTWITHCALLBACKS_CLASSID		"2d386e10-4b81-4c71-801f-d38d2fdb8e88"

class FOUNDATIONKIT_API ObjectWithCallbacks : public Object {
public:
	
	ObjectWithCallbacks():callbacks_(NULL){}	

	virtual ~ObjectWithCallbacks();

	void addCallback( CallBack* cb );
	
	void addCallback( CallBack* cb, const String& cbName );


	void removeCallback( CallBack* cb );

	CallBack* getCallback( const String& name ) const ;	
protected:
	std::map<String,CallBack*>* callbacks_;
};



class ThreadPool;



/**
\class Delegate Delegates.h "vcf/FoundationKit/Delegates.h"
A delegate can be thought of as a function pointer on steroids. 
A delegate stores a collection of callbacks, or function pointers, 
and when you "invoke" the delegate, the delegate passes the function 
arguments to each of it's callbacks. It is essentially the same idea
as .Net's multicast delegate. Therefore \em all delegates in the VCF 
can have multiple "outputs" or callbacks.

Like a function a delegate has a function signature and takes 0 
or more arguments and may or may not return a value. The delegate 
derives from FunctionTypeInfo so that it can store information 
about it's function signature. This is used to make sure that 
any added callbacks actually match the function signature of 
the delegate. For instance, if you had a delegate with a function
signature of 
\code
void (delegate)(int, double)
\endcode
and tried to add a callback with a function signature of 
\code
void (callback)(double,int)
\endcode
the result would be the throwing of an exception since the 
signature's do not match.

A delegate may have 0 or more callbacks associated with it,
and when the delegate is destroyed it removes all it's callbacks.
When a callback is removed from the delegate, the delegate
makes sure the callback removes the delegate from the callbacks's 
internal list as well. In other words, both the callback and the
delegate keep references to each other, and both need to be cleaned
up when a callback is removed from a delegate.

A delegate is invoked by calling the invoke method and 
passing in the appropriate arguments. This in turn will
iteratate through all the callbacks registered with the 
delegate and invoke each callback's bound function pointer.
The invoke usage looks something like this:
\code
//define function..
bool duhDoIt( const String& str, double d );

//define a delegate with a bool return value and two 
//function arguments:
Delegate2R<bool,const String&,double> myDelegate;

//add the static function pointer to delegate
myDelegate += duhDoIt; 

//invoke the delegate
myDelegate.invoke("Hola", 120.456);

\endcode
This will call the duhDoIt() function and pass in "Hola" and
120.456 as arguments to the function. You can use the operator()
shorthand if you prefer:
\code
//invoke the delegate
myDelegate("Hola", 120.456);
\endcode

it will call invoke() for you.

Note that once invoke() is called, it will block
until all the callbacks have been called and 
completed. If you have a lengthy operation in a 
callback then this may take a while. This leads
us to wanting some sort of asynchronous invocation
mode.

You can invoke a delegate asynchronously by using the
beginInvoke() method as well as the
AsyncResult class. You start the async invocation out
by calling beingInvoke(), passing in the delegate's
function arguments, and an optional callback
that is triggered once all the callbacks have 
completed. The beginInvoke() call will return 
immediately and give you a new AsyncResult instance
which is now your responsibility to delete. 

With the AsyncResult instance you can call it's wait() method
to block until all of the callbacks have finished executing.
For example
\code
void myFunc( int i );

Delegate1<int> d2;
d2 += doit;

AsyncResult* ar = d2.beginInvoke( 10, NULL );
ar->wait();//block till we're done
delete ar;
\endcode


There is static ThreadPool for Delegates to use when they are 
operating in asynchronous mode. The lifetime of the thread pool
is managed by the framework and created and deleted automatically.

Like the CallBack class, delegates may be broken down into
two categories, those that do not return any value
and those that do. For delegates that do not return anything
the derived classes are named DelegateX where X is the 
number of arguments that the delegate function takes. 
For delegates that do return a value the classes are named
DelegateRX where where X is the number of arguments that 
the delegate function takes and the R indicates that the 
delegate has a return type.

@see DelegateR
*/
class FOUNDATIONKIT_API Delegate : public FunctionTypeInfo {
public:
	Delegate(): functions(NULL), runCallbacksAsync_(false) {}

	virtual ~Delegate() {
		clear();

		if ( NULL != functions ) {
			delete functions;
		}
	}	

	Delegate& operator=( const Delegate& rhs ) {
		if ( NULL == rhs.functions ) {
			clear();
		}
		else {
			checkHandlers();
			*functions = *rhs.functions;
		}

		runCallbacksAsync_ = rhs.runCallbacksAsync_;
		return *this;
	}


	/**
	Returns whether or not the delegate has any callbacks.
	*/
	bool empty() const {
		bool result = true;
		if ( NULL != functions ) {
			result = functions->empty();
		}
		return result;
	}

	/**
	Returns the number of callbacks currently associated with this
	delegate.
	*/
	size_t size() const {
		size_t result = 0;
		if ( NULL != functions ) {
			result = functions->size();
		}
		return result;
	}


	/**
	cleans out all callbacks from the delegate. Note that
	this does \em not delete the callback.
	*/
	void clear() {
		if ( NULL != functions ) {
			CallBack::Vector::iterator it = functions->begin();
			while ( !functions->empty() ) {
				CallBack* cb = *it;
				remove( cb );				
				it = functions->begin();
			}

			VCF_ASSERT( functions->empty() );
			functions->clear();
		}
	}


	/**
	Adds a callback to a delegate. If the callback
	function signature does not match the
	delegate function signature then the callback is
	not added and the function throws a RuntimeException.
	*/
	void add( CallBack* callback ) {
		VCF_ASSERT( NULL != callback );

		checkHandlers();

		CallBack::Vector::iterator found = 
			std::find( functions->begin(), functions->end(), callback );

		if ( found == functions->end() ) {
			//verify signatures match
			if ( *this == *callback ) {
				callback->addDelegate( this );
				functions->push_back( callback );
			}
			else {
				throw RuntimeException( "Unable to add callback to Delegate, function signatures do not match." );
			}
		}
	}

	/**
	Removes a callback from a delegate. This does \em not
	delete the callback.
	*/
	void remove( CallBack* callback ) {
		VCF_ASSERT( NULL != callback );

		if ( NULL != functions ) {
			CallBack::Vector::iterator found = 
				std::find( functions->begin(), functions->end(), callback );
			
			if ( found != functions->end() ) {
				callback->removeDelegate( this );
				functions->erase( found );
			}
		}
	}


	/**
	@see remove
	*/
	Delegate& operator -=( CallBack* callback ) {
		remove( callback );
		return *this;
	}


	/**
	Returns the callback at the specific index. If the
	delegate has no callbacks, or if the index is out of bounds
	then an exception is thrown.
	*/
	const CallBack& at( const uint32& index ) const {
		if ( NULL == functions ) {
			throw RuntimeException( "No callbacks assigned to this delegate." );
		}
		return *functions->at( index );
	}


	/**
	Tells the delegate whether the callbacks should be invoked 
	in a synchronous manner or asynchronously. This is only
	relevant when you invoke a delagate in async mode. When this 
	happens, and the thread pool determines that it's time to 
	invoke the delegate's various callbacks it has a choice:
	1) to invoke each callback, blocking until the callback 
	returns
	or
	2) to post each \em callback to the delegate thread pool 
	for asynchronous execution.
	If the delegate is set to run callbacks asynchronously
	then option 2 is used, otherwise option 1 is performed.
	The default is option 1.	
	*/
	void setRunCallbacksAsynchronously( bool val ) {
		runCallbacksAsync_ = val;
	}
	

	/**
	This allows you to retreive a copy of the callbacks registered with this 
	delegate.
	@param CallBack::Vector a reference to a std::vector<CallBack*>
	that will be filled with the callbacks registered with this
	delegate.
	@return bool returns true if the callbacks were successfully copied over.
	Otherwise returns false. A delegate with no callbacks will also return 
	false.
	*/
	bool getCallbacks( CallBack::Vector& val ) {
		if ( NULL != functions ) {
			val = *functions;
		}

		return !val.empty();
	}




	/**
	Initializes the thread pool used by delegates for 
	asynchronous callback invocation. This is called by the 
	framework.
	*/
	static void initThreadPool();

	/**
	Terminates the thread pool used by delegates for 
	asynchronous callback invocation. This is called by the 
	framework.
	*/
	static void terminateThreadPool();

	/**
	Get's the current trhead pool used by delegates for 
	asynchronous callback invocation.
	*/
	static ThreadPool* getThreadPool();
protected:
	CallBack::Vector* functions;

	inline void checkHandlers() {
		if ( NULL == functions ) {
			functions = new CallBack::Vector();
		}
	}

	bool runCallbacksAsync_;

	static ThreadPool* delegateThreadPool;
};




class AsyncResult;

/**
\class AsyncReturns Delegates.h "vcf/FoundationKit/Delegates.h"
Interface class used for async delegate execution. It is
used to indicate that a function call (by a callback)
completed. The implemenation for delegates that have
no return type is a no-op. For delegates do have a return
type, the implementation is to store the return value
in the delegate's results cache.
@see DelegateR
*/
class FOUNDATIONKIT_API AsyncReturns {
public:
	virtual ~AsyncReturns(){};

	virtual void functionFinished( AsyncResult*, Runnable* runnable ) = 0;
};


/**
\class Procedure1 Delegates.h "vcf/FoundationKit/Delegates.h"
Represents a callback for a static function with one function 
argument of type P1 and no return type. 
*/
template <typename P1>
class Procedure1 : public CallBack {
public:

	typedef Procedure1<AsyncResult*> AsyncCallback;

	

	typedef void (*FuncPtr)(P1);


	Procedure1():staticFuncPtr(NULL){}

	Procedure1(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	Procedure1( const String& str ): CallBack(str),staticFuncPtr(NULL){}


	Procedure1( Object* source, const String& str ): CallBack(source,str),staticFuncPtr(NULL){}


	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );

		return result;
	}

	virtual void invoke( P1 p1 ) {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)( p1 );
		}
	}
	

	virtual void beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of Delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
protected:
	virtual ~Procedure1(){}
private:
	Procedure1( const Procedure1<P1>& rhs );
};


/**
\class AsyncResult Delegates.h "vcf/FoundationKit/Delegates.h"
This class is used to manage invoking a delegate's callbacks
asynchronously. You don't need to create an instance of
it, instead the framework will hand you a new instance 
when you call beginInvoke on a delegate.
*/
class FOUNDATIONKIT_API AsyncResult : public Object, public Waitable {
public:
	typedef Procedure1<AsyncResult*> AsyncCallback;
	typedef std::pair<AsyncReturns*,Runnable*>  CallbackWork;


	AsyncResult(AsyncCallback* callback, bool runCallbacksAsync): completed_(false), 
					runCallbacksAsync_(runCallbacksAsync),
					resultWait_(&resultWaitMtx_), 
					callback_(callback) {}


	virtual ~AsyncResult(){}


	class AsyncTask : public Runnable {
	public:

		AsyncTask( AsyncResult* res, AsyncReturns* returnObject, Runnable* internalRunnable ):
			res_(res),returnObject_(returnObject),internalRunnable_(internalRunnable) {	}


		virtual ~AsyncTask(){}

		virtual bool run() {

			internalRunnable_->run();

			returnObject_->functionFinished( res_, internalRunnable_ );

			res_->internal_removeRunnable( internalRunnable_ );
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


	void doWork();

	/**
	This function will wait till the async result is completed.
	The result is "finished" when all the callbacks for the delegate
	that created it are done executing. This method will
	block indefinitely until all the callbacks are done.
	*/
	virtual WaitResult wait() {
		{
			Lock l(runnableMtx_);
			if ( completed_ || internalRunnables_.empty() ) {
				return wrWaitFinished;
			}
		}
		return resultWait_.wait();
	}

	/**
	This function will attempt to wait till the async result is completed.
	The result is "finished" when all the callbacks for the delegate
	that created it are done executing. This method will
	block for the passed in number of milliseconds or 
	until all the callbacks are done whichever happens first.
	*/
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

	/**
	A flag that indicates whether or not the delegate's callbacks have 
	finished executing.	
	@return bool a result of true means the callbacks are done, otherwise 
	it returns false.
	*/
	bool isCompleted() const {
		return completed_;
	}

	void internal_addRunnable( AsyncReturns* returnObject, Runnable* internalRunnable ) {
		internalRunnables_.push_back(CallbackWork(returnObject,internalRunnable));
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
				if ( found->second == val ) {
					internalRunnables_.erase( found );
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

/**
\class ClassProcedure1 Delegates.h "vcf/FoundationKit/Delegates.h"
A class member function. The callback takes one argument of type P1 
for a class type of ClassType. 
*/
template <typename P1, typename ClassType >
class ClassProcedure1 : public Procedure1<P1> {
public:
	typedef void (ClassType::*ClassFuncPtr)(P1);


	ClassProcedure1():
		Procedure1<P1>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure1(ClassType* src, ClassFuncPtr funcPtr):
		Procedure1<P1>(),classFuncPtr(funcPtr),funcSrc(src){}


	ClassProcedure1(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure1<P1>(s), classFuncPtr(funcPtr),funcSrc(src){

		Object* obj = getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}

	}


	virtual Object* getSource() {
		return dynamic_cast<Object*>(funcSrc);
	}



	virtual void invoke( P1 p1 ) {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)( p1 );
		}
	}

	virtual void beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassProcedure1(){}
private:
	ClassProcedure1( const ClassProcedure1<P1, ClassType>& rhs );
};



/**
\class Delegate1 Delegates.h "vcf/FoundationKit/Delegates.h"
A delegate that takes one argument of type P1.
*/
template < typename P1>
class Delegate1 : public Delegate, AsyncReturns {
public:
	typedef void (*FuncPtr)(P1);	
	typedef Procedure1<P1> ProcedureType;

	Delegate1(): Delegate() {}

	virtual ~Delegate1(){}

	Delegate1<P1>& operator+= ( FuncPtr rhs ) {
		ProcedureType* cb = new ProcedureType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate1<P1>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );

		return result;
	}
	


	void operator() ( P1 p1 ) {
		invoke( p1 );
	}

	void invoke( P1 p1 ) {
		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->invoke( p1 );

			++it;
		}
	}

	
	AsyncResult* beginInvoke( P1 p1, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->beginInvoke( p1, result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

protected:
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};






/**
\class Procedure Delegates.h "vcf/FoundationKit/Delegates.h"
A callback that takes no arguments. 
*/
class FOUNDATIONKIT_API Procedure : public CallBack {
public:

	typedef void (*FuncPtr)();


	Procedure():staticFuncPtr(NULL){}

	Procedure(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	Procedure( const String& str ): CallBack(str),staticFuncPtr(NULL){}

	Procedure( Object* source, const String& str ): CallBack(source,str),staticFuncPtr(NULL){}


	virtual TypeArray getArgumentTypes() const {
		TypeArray result;
		return result;
	}

	virtual void invoke() {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)();
		}
	}
	

	virtual void beginInvoke( AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of Delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
//protected: //JC - I uncommented this out for Obirsoy to look into a compile fix in Win32RunLoopPeer.cpp
//protected:
	virtual ~Procedure(){}
private:
	

	Procedure( const Procedure& rhs );
};


/**
\class ClassProcedure Delegates.h "vcf/FoundationKit/Delegates.h"
A class method that takes no arguments. The callback class
is of type ClassType.
*/
template <typename ClassType >
class ClassProcedure : public Procedure {
public:
	typedef void (ClassType::*ClassFuncPtr)();


	ClassProcedure():
		Procedure(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure(ClassType* src, ClassFuncPtr funcPtr):
		Procedure(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassProcedure(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure(s), classFuncPtr(funcPtr),funcSrc(src){
		
		Object* obj = getSource();	
		if ( NULL != obj ) {
			addToSource( obj );
		}
	}
	


	virtual Object* getSource() {
		return dynamic_cast<Object*>(funcSrc);
	}


	virtual void invoke() {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)();
		}
	}

	virtual void beginInvoke( AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassProcedure(){}
private:
	ClassProcedure( const ClassProcedure<ClassType>& rhs );
};



/**
\class Delegate0 Delegates.h "vcf/FoundationKit/Delegates.h"
A delegate that takes no arguments.
*/
class FOUNDATIONKIT_API Delegate0 : public Delegate, AsyncReturns {
public:
	typedef void (*FuncPtr)();	
	typedef Procedure ProcedureType;

	Delegate0(): Delegate() {}

	virtual ~Delegate0(){}

	Delegate0& operator+= ( FuncPtr rhs ) {
		ProcedureType* cb = new ProcedureType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate0& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;
		return result;
	}
	


	void operator() () {
		invoke();
	}

	void invoke() {
		std::vector<CallBack*> tmp;

		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->invoke();

			++it;
		}
	}

	
	AsyncResult* beginInvoke( AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->beginInvoke( result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

protected:
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};





template <typename P1, typename P2>
class Procedure2 : public CallBack {
public:
	typedef void (*FuncPtr)(P1,P2);


	Procedure2():staticFuncPtr(NULL){}

	Procedure2(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	Procedure2( const String& str ): CallBack(str),staticFuncPtr(NULL){}

	Procedure2( Object* source, const String& str ): CallBack(source,str),staticFuncPtr(NULL){}


	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );

		return result;
	}

	virtual void invoke( P1 p1, P2 p2 ) {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)( p1, p2 );
		}
	}
	

	virtual void beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of Delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
protected:
	virtual ~Procedure2(){}
private:
	Procedure2( const Procedure2<P1,P2>& rhs );
};


template <typename P1, typename P2, typename ClassType >
class ClassProcedure2 : public Procedure2<P1, P2> {
public:
	typedef void (ClassType::*ClassFuncPtr)(P1,P2);


	ClassProcedure2():
		Procedure2<P1, P2>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure2(ClassType* src, ClassFuncPtr funcPtr):
		Procedure2<P1, P2>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassProcedure2(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure2<P1, P2>(s), classFuncPtr(funcPtr),funcSrc(src){
		
		Object* obj = getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}


	virtual Object* getSource() {
		return dynamic_cast<Object*>(funcSrc);
	}



	virtual void invoke( P1 p1, P2 p2 ) {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)( p1, p2 );
		}
	}

	virtual void beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassProcedure2(){}
private:
	ClassProcedure2( const ClassProcedure2<P1, P2, ClassType>& rhs );
};





template < typename P1, typename P2 >
class Delegate2 : public Delegate, AsyncReturns {
public:
	typedef void (*FuncPtr)(P1,P2);	
	typedef Procedure2<P1,P2> ProcedureType;

	Delegate2(): Delegate() {}

	virtual ~Delegate2(){}

	Delegate2<P1,P2>& operator+= ( FuncPtr rhs ) {
		ProcedureType* cb = new ProcedureType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate2<P1,P2>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );

		return result;
	}

	void operator() ( P1 p1, P2 p2 ) {
		invoke( p1, p2 );
	}

	void invoke( P1 p1, P2 p2 ) {
		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->invoke( p1, p2 );

			++it;
		}
	}

	
	AsyncResult* beginInvoke( P1 p1, P2 p2, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->beginInvoke( p1, p2, result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

protected:
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};








template <typename P1, typename P2, typename P3>
class Procedure3 : public CallBack {
public:

	typedef void (*FuncPtr)(P1,P2,P3);


	Procedure3():staticFuncPtr(NULL){}

	Procedure3(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	Procedure3( const String& str ): CallBack(str),staticFuncPtr(NULL){}

	Procedure3( Object* source, const String& str ): CallBack(source,str),staticFuncPtr(NULL){}


	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );

		return result;
	}

	virtual void invoke( P1 p1, P2 p2, P3 p3 ) {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)( p1, p2, p3 );
		}
	}
	

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of Delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
protected:
	virtual ~Procedure3(){}
private:
	Procedure3( const Procedure3<P1,P2,P3>& rhs );
};


template <typename P1, typename P2, typename P3, typename ClassType >
class ClassProcedure3 : public Procedure3<P1, P2, P3> {
public:
	typedef void (ClassType::*ClassFuncPtr)(P1,P2,P3);


	ClassProcedure3():
		Procedure3<P1, P2, P3>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure3(ClassType* src, ClassFuncPtr funcPtr):
		Procedure3<P1, P2, P3>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassProcedure3(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure3<P1, P2, P3>(s), classFuncPtr(funcPtr),funcSrc(src){
		
		Object* obj = getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}


	virtual Object* getSource() {
		return dynamic_cast<Object*>(funcSrc);
	}



	virtual void invoke( P1 p1, P2 p2, P3 p3 ) {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)( p1, p2, p3 );
		}
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassProcedure3(){}
private:
	ClassProcedure3( const ClassProcedure3<P1, P2, P3, ClassType>& rhs );
};





template < typename P1, typename P2, typename P3 >
class Delegate3 : public Delegate, AsyncReturns {
public:
	typedef void (*FuncPtr)(P1,P2,P3);	
	typedef Procedure3<P1,P2,P3> ProcedureType;

	Delegate3(): Delegate() {}

	virtual ~Delegate3(){}

	Delegate3<P1,P2,P3>& operator+= ( FuncPtr rhs ) {
		ProcedureType* cb = new ProcedureType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate3<P1,P2,P3>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );

		return result;
	}

	void operator() ( P1 p1, P2 p2, P3 p3 ) {
		invoke( p1, p2, p3 );
	}

	void invoke( P1 p1, P2 p2, P3 p3 ) {
		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->invoke( p1, p2, p3 );

			++it;
		}
	}

	
	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->beginInvoke( p1, p2, p3, result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

protected:
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};











template <typename P1, typename P2, typename P3, typename P4>
class Procedure4 : public CallBack {
public:

	typedef void (*FuncPtr)(P1,P2,P3,P4);


	Procedure4():staticFuncPtr(NULL){}

	Procedure4(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	Procedure4( const String& str ): CallBack(str),staticFuncPtr(NULL){}

	Procedure4( Object* source, const String& str ): CallBack(source,str),staticFuncPtr(NULL){}


	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );

		return result;
	}

	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4 ) {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)( p1, p2, p3, p4 );
		}
	}
	

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of Delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
protected:
	virtual ~Procedure4(){}
private:
	Procedure4( const Procedure4<P1,P2,P3,P4>& rhs );
};


template <typename P1, typename P2, typename P3, typename P4, typename ClassType>
class ClassProcedure4 : public Procedure4<P1, P2, P3, P4> {
public:
	typedef void (ClassType::*ClassFuncPtr)(P1,P2,P3,P4);


	ClassProcedure4():
		Procedure4<P1,P2,P3,P4>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure4(ClassType* src, ClassFuncPtr funcPtr):
		Procedure4<P1,P2,P3,P4>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassProcedure4(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure4<P1,P2,P3,P4>(s), classFuncPtr(funcPtr),funcSrc(src){
		
		Object* obj = getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}


	virtual Object* getSource() {
		return dynamic_cast<Object*>(funcSrc);
	}



	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4 ) {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)( p1, p2, p3, p4 );
		}
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassProcedure4(){}
private:
	ClassProcedure4( const ClassProcedure4<P1, P2, P3, P4, ClassType>& rhs );
};





template < typename P1, typename P2, typename P3, typename P4>
class Delegate4 : public Delegate, AsyncReturns {
public:
	typedef void (*FuncPtr)(P1,P2,P3,P4);	
	typedef Procedure4<P1,P2,P3,P4> ProcedureType;

	Delegate4(): Delegate() {}

	virtual ~Delegate4(){}

	Delegate4<P1,P2,P3,P4>& operator+= ( FuncPtr rhs ) {
		ProcedureType* cb = new ProcedureType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate4<P1,P2,P3,P4>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );

		return result;
	}

	void operator() ( P1 p1, P2 p2, P3 p3, P4 p4 ) {
		invoke( p1, p2, p3, p4 );
	}

	void invoke( P1 p1, P2 p2, P3 p3, P4 p4 ) {
		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->invoke( p1, p2, p3, p4 );

			++it;
		}
	}

	
	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->beginInvoke( p1, p2, p3, p4, result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

protected:
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};











template <typename P1, typename P2, typename P3, typename P4, typename P5>
class Procedure5 : public CallBack {
public:

	typedef void (*FuncPtr)(P1,P2,P3,P4,P5);


	Procedure5():staticFuncPtr(NULL){}

	Procedure5(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	Procedure5( const String& str ): CallBack(str),staticFuncPtr(NULL){}

	Procedure5( Object* source, const String& str ): CallBack(source,str),staticFuncPtr(NULL){}


	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );

		return result;
	}

	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)( p1, p2, p3, p4, p5 );
		}
	}
	

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of Delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
protected:
	virtual ~Procedure5(){}
private:
	Procedure5( const Procedure5<P1,P2,P3,P4,P5>& rhs );
};


template <typename P1, typename P2, typename P3, typename P4, typename P5, typename ClassType>
class ClassProcedure5 : public Procedure5<P1, P2, P3, P4, P5> {
public:
	typedef void (ClassType::*ClassFuncPtr)(P1,P2,P3,P4,P5);


	ClassProcedure5():
		Procedure5<P1,P2,P3,P4,P5>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure5(ClassType* src, ClassFuncPtr funcPtr):
		Procedure5<P1,P2,P3,P4,P5>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassProcedure5(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure5<P1,P2,P3,P4,P5>(s), classFuncPtr(funcPtr),funcSrc(src){
		
		Object* obj = getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}


	virtual Object* getSource() {
		return dynamic_cast<Object*>(funcSrc);
	}



	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)( p1, p2, p3, p4, p5 );
		}
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassProcedure5(){}
private:
	ClassProcedure5( const ClassProcedure5<P1, P2, P3, P4, P5, ClassType>& rhs );
};





template < typename P1, typename P2, typename P3, typename P4, typename P5>
class Delegate5 : public Delegate, AsyncReturns {
public:
	typedef void (*FuncPtr)(P1,P2,P3,P4,P5);	
	typedef Procedure5<P1,P2,P3,P4,P5> ProcedureType;

	Delegate5(): Delegate() {}

	virtual ~Delegate5(){}

	Delegate5<P1,P2,P3,P4,P5>& operator+= ( FuncPtr rhs ) {
		ProcedureType* cb = new ProcedureType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate5<P1,P2,P3,P4,P5>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );

		return result;
	}

	void operator() ( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) {
		invoke( p1, p2, p3, p4, p5 );
	}

	void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) {
		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->invoke( p1, p2, p3, p4, p5 );

			++it;
		}
	}

	
	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->beginInvoke( p1, p2, p3, p4, p5, result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

protected:
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};















template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Procedure6 : public CallBack {
public:

	typedef void (*FuncPtr)(P1,P2,P3,P4,P5,P6);


	Procedure6():staticFuncPtr(NULL){}

	Procedure6(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	Procedure6( const String& str ): CallBack(str),staticFuncPtr(NULL){}

	Procedure6( Object* source, const String& str ): CallBack(source,str),staticFuncPtr(NULL){}


	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P6) );

		return result;
	}

	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)( p1, p2, p3, p4, p5, p6 );
		}
	}
	

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of Delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
protected:
	virtual ~Procedure6(){}
private:
	Procedure6( const Procedure6<P1,P2,P3,P4,P5,P6>& rhs );
};


template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename ClassType>
class ClassProcedure6 : public Procedure6<P1, P2, P3, P4, P5, P6> {
public:
	typedef void (ClassType::*ClassFuncPtr)(P1,P2,P3,P4,P5,P6);


	ClassProcedure6():
		Procedure6<P1,P2,P3,P4,P5,P6>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure6(ClassType* src, ClassFuncPtr funcPtr):
		Procedure6<P1,P2,P3,P4,P5,P6>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassProcedure6(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure6<P1,P2,P3,P4,P5,P6>(s), classFuncPtr(funcPtr),funcSrc(src){
		
		Object* obj = getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}


	virtual Object* getSource() {
		return dynamic_cast<Object*>(funcSrc);
	}



	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)( p1, p2, p3, p4, p5, p6 );
		}
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassProcedure6(){}
private:
	ClassProcedure6( const ClassProcedure6<P1, P2, P3, P4, P5, P6, ClassType>& rhs );
};





template < typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
class Delegate6 : public Delegate, AsyncReturns {
public:
	typedef void (*FuncPtr)(P1,P2,P3,P4,P5,P6);	
	typedef Procedure6<P1,P2,P3,P4,P5,P6> ProcedureType;

	Delegate6(): Delegate() {}

	virtual ~Delegate6(){}

	Delegate6<P1,P2,P3,P4,P5,P6>& operator+= ( FuncPtr rhs ) {
		ProcedureType* cb = new ProcedureType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate6<P1,P2,P3,P4,P5,P6>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P6) );

		return result;
	}

	void operator() ( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) {
		invoke( p1, p2, p3, p4, p5, p6 );
	}

	void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) {
		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->invoke( p1, p2, p3, p4, p5, p6 );

			++it;
		}
	}

	
	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->beginInvoke( p1, p2, p3, p4, p5, p6, result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

protected:
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};







template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
class Procedure7 : public CallBack {
public:

	typedef void (*FuncPtr)(P1,P2,P3,P4,P5,P6,P7);


	Procedure7():staticFuncPtr(NULL){}

	Procedure7(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	Procedure7( const String& str ): CallBack(str),staticFuncPtr(NULL){}

	Procedure7( Object* source, const String& str ): CallBack(source,str),staticFuncPtr(NULL){}


	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P6) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P7) );

		return result;
	}

	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)( p1, p2, p3, p4, p5, p6, p7 );
		}
	}
	

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of Delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
protected:
	virtual ~Procedure7(){}
private:
	Procedure7( const Procedure7<P1,P2,P3,P4,P5,P6,P7>& rhs );
};


template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename ClassType>
class ClassProcedure7 : public Procedure7<P1, P2, P3, P4, P5, P6,P7> {
public:
	typedef void (ClassType::*ClassFuncPtr)(P1,P2,P3,P4,P5,P6,P7);


	ClassProcedure7():
		Procedure7<P1,P2,P3,P4,P5,P6,P7>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure7(ClassType* src, ClassFuncPtr funcPtr):
		Procedure7<P1,P2,P3,P4,P5,P6,P7>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassProcedure7(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure7<P1,P2,P3,P4,P5,P6,P7>(s), classFuncPtr(funcPtr),funcSrc(src){
		
		Object* obj = getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}


	virtual Object* getSource() {
		return dynamic_cast<Object*>(funcSrc);
	}



	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)( p1, p2, p3, p4, p5, p6, p7 );
		}
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassProcedure7(){}
private:
	ClassProcedure7( const ClassProcedure7<P1, P2, P3, P4, P5, P6, P7, ClassType>& rhs );
};





template < typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
class Delegate7 : public Delegate, AsyncReturns {
public:
	typedef void (*FuncPtr)(P1,P2,P3,P4,P5,P6,P7);	
	typedef Procedure7<P1,P2,P3,P4,P5,P6,P7> ProcedureType;

	Delegate7(): Delegate() {}

	virtual ~Delegate7(){}

	Delegate7<P1,P2,P3,P4,P5,P6,P7>& operator+= ( FuncPtr rhs ) {
		ProcedureType* cb = new ProcedureType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate7<P1,P2,P3,P4,P5,P6,P7>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P6) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P7) );

		return result;
	}

	void operator() ( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) {
		invoke( p1, p2, p3, p4, p5, p6, p7 );
	}

	void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7 ) {
		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->invoke( p1, p2, p3, p4, p5, p6, p7 );

			++it;
		}
	}

	
	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->beginInvoke( p1, p2, p3, p4, p5, p6, p7, result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

protected:
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};














template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
class Procedure8 : public CallBack {
public:

	typedef void (*FuncPtr)(P1,P2,P3,P4,P5,P6,P7,P8);


	Procedure8():staticFuncPtr(NULL){}

	Procedure8(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	Procedure8( const String& str ): CallBack(str),staticFuncPtr(NULL){}

	Procedure8( Object* source, const String& str ): CallBack(source,str),staticFuncPtr(NULL){}


	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P6) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P7) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P8) );

		return result;
	}

	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) {
		if ( NULL != staticFuncPtr ) {
			(*staticFuncPtr)( p1, p2, p3, p4, p5, p6, p7, p8 );
		}
	}
	

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	//no results return for this type of Delegate
	virtual void endInvoke( AsyncResult* ) {}

	FuncPtr staticFuncPtr;
protected:
	virtual ~Procedure8(){}
private:
	Procedure8( const Procedure8<P1,P2,P3,P4,P5,P6,P7,P8>& rhs );
};


template <typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename ClassType>
class ClassProcedure8 : public Procedure8<P1, P2, P3, P4, P5, P6,P7,P8> {
public:
	typedef void (ClassType::*ClassFuncPtr)(P1,P2,P3,P4,P5,P6,P7,P8);


	ClassProcedure8():
		Procedure8<P1,P2,P3,P4,P5,P6,P7,P8>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassProcedure8(ClassType* src, ClassFuncPtr funcPtr):
		Procedure8<P1,P2,P3,P4,P5,P6,P7,P8>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassProcedure8(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Procedure8<P1,P2,P3,P4,P5,P6,P7,P8>(s), classFuncPtr(funcPtr),funcSrc(src){
		
		Object* obj = getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}


	virtual Object* getSource() {
		return dynamic_cast<Object*>(funcSrc);
	}



	virtual void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) {
		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			(funcSrc->*classFuncPtr)( p1, p2, p3, p4, p5, p6, p7, p8 );
		}
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassProcedure8(){}
private:
	ClassProcedure8( const ClassProcedure8<P1, P2, P3, P4, P5, P6, P7, P8, ClassType>& rhs );
};





template < typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
class Delegate8 : public Delegate, AsyncReturns {
public:
	typedef void (*FuncPtr)(P1,P2,P3,P4,P5,P6,P7,P8);	
	typedef Procedure8<P1,P2,P3,P4,P5,P6,P7,P8> ProcedureType;

	Delegate8(): Delegate() {}

	virtual ~Delegate8(){}

	Delegate8<P1,P2,P3,P4,P5,P6,P7,P8>& operator+= ( FuncPtr rhs ) {
		ProcedureType* cb = new ProcedureType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate8<P1,P2,P3,P4,P5,P6,P7,P8>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P6) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P7) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P8) );

		return result;
	}

	void operator() ( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) {
		invoke( p1, p2, p3, p4, p5, p6, p7, p8 );
	}

	void invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8 ) {
		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->invoke( p1, p2, p3, p4, p5, p6, p7, p8 );

			++it;
		}
	}

	
	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			ProcedureType* callBack = (ProcedureType*)cb;

			callBack->beginInvoke( p1, p2, p3, p4, p5, p6, p7, p8, result, callback, this );

			++it;
		}

		result->doWork();

		return result;
	}

protected:
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};



















/**
\class ResultsCache Delegates.h "vcf/FoundationKit/Delegates.h"
A class that is uses to cache the results of callbacks that
return values. The ResultsCache may be used with delegates
that have been fired asynchronously. 
*/
template <typename ReturnType>
class ResultsCache {
public:
	typedef std::vector<ReturnType> Results;
	typedef std::map<AsyncResult*,Results*> CacheMap;

	ResultsCache():cache_(NULL){}

	~ResultsCache(){		
		Lock l(asyncResultsMtx_);
		if ( NULL != cache_ ) {				
			typename CacheMap::iterator it = cache_->begin();
			while ( it != cache_->end() ) {
				delete it->second;
				++it;
			}
			delete cache_;
		}		
	}
	
	/**
	this is called by the various implementations of callbacks that
	return a value when a function is finished. The AsyncResult
	passed in is used as a key to make sure that the results
	list that the result is added to is the correct one.
	*/
	void addResult( ReturnType result, AsyncResult* asyncRes ) {
		
		Lock l(asyncResultsMtx_);

		if ( NULL == cache_ ) {
			cache_ = new CacheMap();
		}

		Results* results = NULL;
		typename CacheMap::iterator found = cache_->find( asyncRes );
		if ( found == cache_->end() ) {
			results = new Results();
			cache_->insert( _typename_ CacheMap::value_type(asyncRes,results) );
		}
		else {
			results = found->second;
		}
		
		results->push_back( result );	
	}


	/**
	Get's the last result for a given AsyncResult instance.
	This is called to get the last result in a collection
	of possible results, for a given AsyncResult. If 
	you had a delegate that return a value with three 
	callbacks associated with it, then the result list
	would have 3 possible values in it, stored in the 
	order the callbacks were invoked. This function
	would return the \em last result put into the
	list.
	*/
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

	/**
	Gets an instance of the result collection for an
	AsyncResult instance. This may be NULL if there
	are no results. This will return \em all
	the results for the delegate that was invoked asynchronously.
	*/
	Results* getResults( AsyncResult* asyncResult ) {
		Results* result = NULL;

		Lock l(asyncResultsMtx_);
		
		if ( NULL != cache_ ) {
			
			typename CacheMap::iterator found = cache_->find( asyncResult );
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
















template <typename ReturnType>
class Function : public CallBack {
public:
	typedef ReturnType (*FuncPtr)();


	Function():staticFuncPtr(NULL){}

	Function(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		return result;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual ReturnType invoke() {
		ReturnType result = ReturnType();
		if ( NULL != staticFuncPtr ) {
			result = (*staticFuncPtr)();
		}
		return result;
	}

	virtual void beginInvoke( AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	FuncPtr staticFuncPtr;

protected:
	virtual ~Function(){}
};





template <typename ReturnType,
		typename ClassType 
		>
class ClassFunction : public Function<ReturnType> {
public:
	typedef ReturnType (ClassType::*ClassFuncPtr)();


	ClassFunction():
		Function<ReturnType>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassFunction(ClassType* src, ClassFuncPtr funcPtr):
		Function<ReturnType>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassFunction(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Function<ReturnType>(),classFuncPtr(funcPtr),funcSrc(src){
		this->name = s;

		Object* obj = this->getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}



	virtual ReturnType invoke() {
		ReturnType result = ReturnType();

		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			result = (funcSrc->*classFuncPtr)();
		}

		return result;
	}

	virtual void beginInvoke( AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );
	
	

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassFunction(){}
};



/**
\class DelegateR Delegates.h "vcf/FoundationKit/Delegates.h"
The base calss for delegates that return a value from
a function. This delegate returns a value of type 
ReturnType but has no arguments.

The delegate stores all the return values in a vector
of type ReturnType. You can access the values via the
results member variable which is marked as public.

When the invoke() method returns the results vector will
have been populated with all the return values from
the callbacks, stored in the order the callbacks were
called in. The return result for invoke() is the return
value of the last callback.

If the delegate is invoked asynchronously with beingInvoke()
then if you want to get the return value(s) you need ot 
call either endInvoke(), or endInvokeWithResults()
to get all the return values.
*/
template <typename ReturnType>
class DelegateR : public Delegate, AsyncReturns {
public:
	typedef Function<ReturnType> CallbackType;
	typedef _typename_ CallbackType::FuncPtr FuncPtr;

	typedef std::vector<ReturnType> Results;


	DelegateR(){}

	virtual ~DelegateR(){}

	DelegateR<ReturnType >& operator+= ( FuncPtr rhs ) {
		CallbackType* cb = new CallbackType(rhs);
		add( cb );
		return *this;
	}
	
	DelegateR<ReturnType>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	/**
	Returns a type_info that represents the return type defined
	by ReturnType.
	*/
	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;
		return result;
	}

	ReturnType operator() () {
		return invoke();
	}

	/**
	invokes the delegate and iterates through it's 
	list of callbacks. 
	@return ReturnType returns the return value of the 
	last callback.
	*/
	ReturnType invoke() {
		ReturnType result = ReturnType();

		results.clear();

		if ( NULL != functions ) {
			if ( !functions->empty() ) {
				
				size_t i = 0;
				results.resize( functions->size() );
				
				std::vector<CallBack*>::iterator it = functions->begin();
				while ( it != functions->end() ) {
					CallBack* cb = *it;
					CallbackType* callBack = (CallbackType*)cb;
					
					results[i] = callBack->invoke();

					++i;
					++it;
				}

				result = results.back();
			}
		}

		return result;
	}


	AsyncResult* beginInvoke( AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			CallbackType* callBack = (CallbackType*)cb;

			callBack->beginInvoke( result, callback, this );			

			++it;
		}

		result->doWork();

		return result;
	}


	/**
	Gets the result for the AsyncResult instance that was 
	returned by the previous call to beginInvoke().

	@return ReturnType returns the return value of the 
	last callback.
	*/
	ReturnType endInvoke( AsyncResult* asyncResult );

	/**
	Gets the results for the AsyncResult instance that was 
	returned by the previous call to beginInvoke().

	@return Results returns an a array of results, reprepresenting
	all the return values for each callback that was called. 
	The collection is a vector of ReturnType.
	*/
	Results endInvokeWithResults( AsyncResult* asyncResult );	

	Results results;
protected:
	ResultsCache<ReturnType> resultsCache_;
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};

















template <typename ReturnType, typename P1>
class Function1 : public CallBack {
public:
	typedef ReturnType (*FuncPtr)(P1);


	Function1():staticFuncPtr(NULL){}

	Function1(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );

		return result;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual ReturnType invoke( P1 p1 ) {
		ReturnType result = ReturnType();
		if ( NULL != staticFuncPtr ) {
			result = (*staticFuncPtr)( p1 );
		}
		return result;
	}

	virtual void beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	FuncPtr staticFuncPtr;
protected:
	virtual ~Function1(){}
};





template <typename ReturnType, 
		typename P1, 
		typename ClassType 
		>
class ClassFunction1 : public Function1<ReturnType,P1> {
public:
	typedef ReturnType (ClassType::*ClassFuncPtr)(P1);


	ClassFunction1():
		Function1<ReturnType,P1>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassFunction1(ClassType* src, ClassFuncPtr funcPtr):
		Function1<ReturnType,P1>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassFunction1(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Function1<ReturnType,P1>(),classFuncPtr(funcPtr),funcSrc(src){
		this->name = s;

		Object* obj = this->getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}



	virtual ReturnType invoke( P1 p1 ) {
		ReturnType result = ReturnType();

		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			result = (funcSrc->*classFuncPtr)( p1 );
		}

		return result;
	}

	virtual void beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );
	
	

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassFunction1(){}
};


template <typename ReturnType, typename P1>
class Delegate1R : public Delegate, AsyncReturns {
public:
	typedef Function1<ReturnType,P1> CallbackType;
	typedef _typename_ CallbackType::FuncPtr FuncPtr;

	typedef std::vector<ReturnType> Results;


	Delegate1R(){}

	virtual ~Delegate1R(){}

	Delegate1R<ReturnType,P1>& operator+= ( FuncPtr rhs ) {
		CallbackType* cb = new CallbackType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate1R<ReturnType,P1>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );

		return result;
	}


	ReturnType operator() ( P1 p1 ) {
		return invoke( p1 );
	}

	ReturnType invoke( P1 p1 ) {
		ReturnType result = ReturnType();

		results.clear();

		if ( NULL != functions ) {
			if ( !functions->empty() ) {
				
				size_t i = 0;
				results.resize( functions->size() );
				
				std::vector<CallBack*>::iterator it = functions->begin();
				while ( it != functions->end() ) {
					CallBack* cb = *it;
					CallbackType* callBack = (CallbackType*)cb;
					
					results[i] = callBack->invoke( p1 );
					
					++i;
					++it;
				}
				
				result = results.back();
			}
		}

		return result;
	}


	AsyncResult* beginInvoke( P1 p1, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {		
			CallBack* cb = *it;
			CallbackType* callBack = (CallbackType*)cb;

			callBack->beginInvoke( p1, result, callback, this );			

			++it;
		}

		result->doWork();

		return result;
	}


	ReturnType endInvoke( AsyncResult* asyncResult );

	Results endInvokeWithResults( AsyncResult* asyncResult );	

	Results results;
protected:
	ResultsCache<ReturnType> resultsCache_;
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};










template <typename ReturnType, typename P1, typename P2>
class Function2 : public CallBack {
public:
	typedef ReturnType (*FuncPtr)(P1,P2);


	Function2():staticFuncPtr(NULL){}

	Function2(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );

		return result;
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
protected:
	virtual ~Function2(){}
};





template <typename ReturnType, 
		typename P1, 
		typename P2, 
		typename ClassType 
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
		this->name = s;

		Object* obj = this->getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
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
protected:
	virtual ~ClassFunction2(){}
};


template <typename ReturnType, typename P1, typename P2>
class Delegate2R : public Delegate, AsyncReturns {
public:
	typedef Function2<ReturnType,P1,P2> CallbackType;
	typedef _typename_ CallbackType::FuncPtr FuncPtr;

	typedef std::vector<ReturnType> Results;


	Delegate2R(){}

	virtual ~Delegate2R(){}

	Delegate2R<ReturnType,P1,P2>& operator+= ( FuncPtr rhs ) {
		CallbackType* cb = new CallbackType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate2R<ReturnType,P1,P2>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );

		return result;
	}


	ReturnType operator() ( P1 p1, P2 p2 ) {
		return invoke( p1, p2 );
	}

	ReturnType invoke( P1 p1, P2 p2 ) {
		ReturnType result = ReturnType();

		results.clear();

		if ( NULL != functions ) {
			if ( !functions->empty() ) {
				
				size_t i = 0;
				results.resize( functions->size() );
				
				std::vector<CallBack*>::iterator it = functions->begin();
				while ( it != functions->end() ) {
					CallBack* cb = *it;
					CallbackType* callBack = (CallbackType*)cb;
					
					results[i] = callBack->invoke( p1, p2 );
					
					++i;
					++it;
				}
				
				result = results.back();
			}
		}

		return result;
	}


	AsyncResult* beginInvoke( P1 p1, P2 p2, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
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

	Results results;
protected:
	ResultsCache<ReturnType> resultsCache_;
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};

















template <typename ReturnType, typename P1, typename P2, typename P3>
class Function3 : public CallBack {
public:
	typedef ReturnType (*FuncPtr)(P1,P2,P3);


	Function3():staticFuncPtr(NULL){}

	Function3(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );

		return result;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual ReturnType invoke( P1 p1, P2 p2, P3 p3 ) {
		ReturnType result = ReturnType();
		if ( NULL != staticFuncPtr ) {
			result = (*staticFuncPtr)( p1, p2, p3 );
		}
		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	FuncPtr staticFuncPtr;
protected:
	virtual ~Function3(){}
};





template <typename ReturnType, 
		typename P1, 
		typename P2, 
		typename P3, 
		typename ClassType 
		>
class ClassFunction3 : public Function3<ReturnType,P1,P2,P3> {
public:
	typedef ReturnType (ClassType::*ClassFuncPtr)(P1,P2,P3);


	ClassFunction3():
		Function3<ReturnType,P1,P2,P3>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassFunction3(ClassType* src, ClassFuncPtr funcPtr):
		Function3<ReturnType,P1,P2,P3>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassFunction3(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Function3<ReturnType,P1,P2,P3>(),classFuncPtr(funcPtr),funcSrc(src){
		this->name = s;

		Object* obj = this->getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}



	virtual ReturnType invoke( P1 p1, P2 p2, P3 p3 ) {
		ReturnType result = ReturnType();

		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			result = (funcSrc->*classFuncPtr)( p1, p2, p3 );
		}

		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );
	
	

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassFunction3(){}
};


template <typename ReturnType, typename P1, typename P2, typename P3>
class Delegate3R : public Delegate, AsyncReturns {
public:
	typedef Function3<ReturnType,P1,P2,P3> CallbackType;
	typedef _typename_ CallbackType::FuncPtr FuncPtr;

	typedef std::vector<ReturnType> Results;


	Delegate3R(){}

	virtual ~Delegate3R(){}

	Delegate3R<ReturnType,P1,P2,P3>& operator+= ( FuncPtr rhs ) {
		CallbackType* cb = new CallbackType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate3R<ReturnType,P1,P2,P3>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );

		return result;
	}

	ReturnType operator() ( P1 p1, P2 p2, P3 p3 ) {
		return invoke(p1,p2,p3);
	}

	ReturnType invoke( P1 p1, P2 p2, P3 p3 ) {
		ReturnType result = ReturnType();

		results.clear();

		if ( NULL != functions ) {
			if ( !functions->empty() ) {
				
				size_t i = 0;
				results.resize( functions->size() );
				
				std::vector<CallBack*>::iterator it = functions->begin();
				while ( it != functions->end() ) {
					CallBack* cb = *it;
					CallbackType* callBack = (CallbackType*)cb;
					
					results[i] = callBack->invoke( p1, p2, p3 );
					
					++i;
					++it;
				}
				
				result = results.back();
			}
		}

		return result;
	}


	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			CallbackType* callBack = (CallbackType*)cb;

			callBack->beginInvoke( p1, p2, p3, result, callback, this );			

			++it;
		}

		result->doWork();

		return result;
	}


	ReturnType endInvoke( AsyncResult* asyncResult );

	Results endInvokeWithResults( AsyncResult* asyncResult );	

	Results results;
protected:
	ResultsCache<ReturnType> resultsCache_;
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};






















template <typename ReturnType, typename P1, typename P2, typename P3, typename P4>
class Function4 : public CallBack {
public:
	typedef ReturnType (*FuncPtr)(P1,P2,P3,P4);


	Function4():staticFuncPtr(NULL){}

	Function4(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );

		return result;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual ReturnType invoke( P1 p1, P2 p2, P3 p3, P4 p4 ) {
		ReturnType result = ReturnType();
		if ( NULL != staticFuncPtr ) {
			result = (*staticFuncPtr)( p1, p2, p3, p4 );
		}
		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	FuncPtr staticFuncPtr;
protected:
	virtual ~Function4(){}
};





template <typename ReturnType, 
		typename P1, 
		typename P2, 
		typename P3, 
		typename P4, 
		typename ClassType 
		>
class ClassFunction4 : public Function4<ReturnType,P1,P2,P3,P4> {
public:
	typedef ReturnType (ClassType::*ClassFuncPtr)(P1,P2,P3,P4);


	ClassFunction4():
		Function4<ReturnType,P1,P2,P3,P4>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassFunction4(ClassType* src, ClassFuncPtr funcPtr):
		Function4<ReturnType,P1,P2,P3,P4>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassFunction4(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Function4<ReturnType,P1,P2,P3,P4>(),classFuncPtr(funcPtr),funcSrc(src){
		this->name = s;

		Object* obj = this->getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}



	virtual ReturnType invoke( P1 p1, P2 p2, P3 p3, P4 p4 ) {
		ReturnType result = ReturnType();

		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			result = (funcSrc->*classFuncPtr)( p1, p2, p3, p4 );
		}

		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );
	
	

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassFunction4(){}
};


template <typename ReturnType, typename P1, typename P2, typename P3, typename P4>
class Delegate4R : public Delegate, AsyncReturns {
public:
	typedef Function4<ReturnType,P1,P2,P3,P4> CallbackType;
	typedef _typename_ CallbackType::FuncPtr FuncPtr;

	typedef std::vector<ReturnType> Results;


	Delegate4R(){}

	virtual ~Delegate4R(){}

	Delegate4R<ReturnType,P1,P2,P3,P4>& operator+= ( FuncPtr rhs ) {
		CallbackType* cb = new CallbackType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate4R<ReturnType,P1,P2,P3,P4>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );

		return result;
	}

	ReturnType operator() ( P1 p1, P2 p2, P3 p3, P4 p4 ) {
		return invoke(p1,p2,p3,p4);
	}

	ReturnType invoke( P1 p1, P2 p2, P3 p3, P4 p4 ) {
		ReturnType result = ReturnType();

		results.clear();

		if ( NULL != functions ) {
			if ( !functions->empty() ) {
				
				size_t i = 0;
				results.resize( functions->size() );
				
				std::vector<CallBack*>::iterator it = functions->begin();
				while ( it != functions->end() ) {
					CallBack* cb = *it;
					CallbackType* callBack = (CallbackType*)cb;
					
					results[i] = callBack->invoke( p1, p2, p3, p4 );
					
					++i;
					++it;
				}
				
				result = results.back();
			}
		}

		return result;
	}


	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			CallbackType* callBack = (CallbackType*)cb;

			callBack->beginInvoke( p1, p2, p3, p4, result, callback, this );			

			++it;
		}

		result->doWork();

		return result;
	}


	ReturnType endInvoke( AsyncResult* asyncResult );

	Results endInvokeWithResults( AsyncResult* asyncResult );	

	Results results;
protected:
	ResultsCache<ReturnType> resultsCache_;
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};
















template <typename ReturnType, 
			typename P1, 
			typename P2, 
			typename P3, 
			typename P4,
			typename P5>
class Function5 : public CallBack {
public:
	typedef ReturnType (*FuncPtr)(P1,P2,P3,P4,P5);


	Function5():staticFuncPtr(NULL){}

	Function5(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );

		return result;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual ReturnType invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) {
		ReturnType result = ReturnType();
		if ( NULL != staticFuncPtr ) {
			result = (*staticFuncPtr)( p1, p2, p3, p4, p5 );
		}
		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	FuncPtr staticFuncPtr;
protected:
	virtual ~Function5(){}
};





template <typename ReturnType, 
		typename P1, 
		typename P2, 
		typename P3, 
		typename P4, 
		typename P5, 
		typename ClassType 
		>
class ClassFunction5 : public Function5<ReturnType,P1,P2,P3,P4,P5> {
public:
	typedef ReturnType (ClassType::*ClassFuncPtr)(P1,P2,P3,P4,P5);


	ClassFunction5():
		Function5<ReturnType,P1,P2,P3,P4,P5>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassFunction5(ClassType* src, ClassFuncPtr funcPtr):
		Function5<ReturnType,P1,P2,P3,P4,P5>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassFunction5(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Function5<ReturnType,P1,P2,P3,P4,P5>(),classFuncPtr(funcPtr),funcSrc(src){
		this->name = s;

		Object* obj = this->getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}



	virtual ReturnType invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) {
		ReturnType result = ReturnType();

		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			result = (funcSrc->*classFuncPtr)( p1, p2, p3, p4, p5 );
		}

		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );
	
	

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassFunction5(){}
};


template <typename ReturnType, 
			typename P1, 
			typename P2, 
			typename P3, 
			typename P4,
			typename P5>
class Delegate5R : public Delegate, AsyncReturns {
public:
	typedef Function5<ReturnType,P1,P2,P3,P4,P5> CallbackType;
	typedef _typename_ CallbackType::FuncPtr FuncPtr;

	typedef std::vector<ReturnType> Results;


	Delegate5R(){}

	virtual ~Delegate5R(){}

	Delegate5R<ReturnType,P1,P2,P3,P4,P5>& operator+= ( FuncPtr rhs ) {
		CallbackType* cb = new CallbackType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate5R<ReturnType,P1,P2,P3,P4,P5>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );

		return result;
	}

	ReturnType operator() ( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) {
		return invoke(p1,p2,p3,p4,p5);
	}

	ReturnType invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5 ) {
		ReturnType result = ReturnType();

		results.clear();

		if ( NULL != functions ) {
			if ( !functions->empty() ) {
				
				size_t i = 0;
				results.resize( functions->size() );
				
				std::vector<CallBack*>::iterator it = functions->begin();
				while ( it != functions->end() ) {
					CallBack* cb = *it;
					CallbackType* callBack = (CallbackType*)cb;
					
					results[i] = callBack->invoke( p1, p2, p3, p4, p5 );
					
					++i;
					++it;
				}
				
				result = results.back();
			}
		}

		return result;
	}


	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncCallback* callback ) {
		AsyncResult* result = NULL;

	
		result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			CallbackType* callBack = (CallbackType*)cb;

			callBack->beginInvoke( p1, p2, p3, p4, p5, result, callback, this );			

			++it;
		}

		result->doWork();
			

		return result;
	}


	ReturnType endInvoke( AsyncResult* asyncResult );

	Results endInvokeWithResults( AsyncResult* asyncResult );	

	Results results;
protected:
	ResultsCache<ReturnType> resultsCache_;
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};




















template <typename ReturnType, 
			typename P1, 
			typename P2, 
			typename P3, 
			typename P4,
			typename P5,
			typename P6>
class Function6 : public CallBack {
public:
	typedef ReturnType (*FuncPtr)(P1,P2,P3,P4,P5,P6);


	Function6():staticFuncPtr(NULL){}

	Function6(FuncPtr funcPtr):staticFuncPtr(funcPtr){}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P6) );

		return result;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual ReturnType invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) {
		ReturnType result = ReturnType();
		if ( NULL != staticFuncPtr ) {
			result = (*staticFuncPtr)( p1, p2, p3, p4, p5, p6 );
		}
		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );

	FuncPtr staticFuncPtr;
protected:
	virtual ~Function6(){}
};





template <typename ReturnType, 
		typename P1, 
		typename P2, 
		typename P3, 
		typename P4, 
		typename P5, 
		typename P6, 
		typename ClassType 
		>
class ClassFunction6 : public Function6<ReturnType,P1,P2,P3,P4,P5,P6> {
public:
	typedef ReturnType (ClassType::*ClassFuncPtr)(P1,P2,P3,P4,P5,P6);


	ClassFunction6():
		Function6<ReturnType,P1,P2,P3,P4,P5,P6>(),classFuncPtr(NULL),funcSrc(NULL){}
	
	ClassFunction6(ClassType* src, ClassFuncPtr funcPtr):
		Function6<ReturnType,P1,P2,P3,P4,P5,P6>(),classFuncPtr(funcPtr),funcSrc(src){}

	ClassFunction6(ClassType* src, ClassFuncPtr funcPtr, const String& s):
		Function6<ReturnType,P1,P2,P3,P4,P5,P6>(),classFuncPtr(funcPtr),funcSrc(src){
		this->name = s;

		Object* obj = this->getSource();	
		if ( NULL != obj ) {
			this->addToSource( obj );
		}
	}



	virtual ReturnType invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) {
		ReturnType result = ReturnType();

		if ( NULL != classFuncPtr && NULL != funcSrc ) {
			result = (funcSrc->*classFuncPtr)( p1, p2, p3, p4, p5, p6 );
		}

		return result;
	}

	virtual void beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject );
	
	

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
protected:
	virtual ~ClassFunction6(){}
};


template <typename ReturnType, 
			typename P1, 
			typename P2, 
			typename P3, 
			typename P4,
			typename P5,
			typename P6>
class Delegate6R : public Delegate, AsyncReturns {
public:
	typedef Function6<ReturnType,P1,P2,P3,P4,P5,P6> CallbackType;
	typedef _typename_ CallbackType::FuncPtr FuncPtr;

	typedef std::vector<ReturnType> Results;


	Delegate6R(){}

	virtual ~Delegate6R(){}

	Delegate6R<ReturnType,P1,P2,P3,P4,P5,P6>& operator+= ( FuncPtr rhs ) {
		CallbackType* cb = new CallbackType(rhs);
		add( cb );
		return *this;
	}
	
	Delegate6R<ReturnType,P1,P2,P3,P4,P5,P6>& operator+= ( CallBack* rhs ) {		
		add( rhs );
		return *this;
	}

	virtual const std::type_info& getReturnType() const {
		return typeid(ReturnType);
	}

	virtual TypeArray getArgumentTypes() const {
		TypeArray result;

		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P1) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P2) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P3) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P4) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P5) );
		FunctionTypeInfo::addArgumentTypeInfo( result, typeid(P6) );

		return result;
	}

	ReturnType operator() ( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) {
		return invoke(p1,p2,p3,p4,p5,p6);
	}

	ReturnType invoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6 ) {
		ReturnType result = ReturnType();

		results.clear();

		if ( NULL != functions ) {
			if ( !functions->empty() ) {
				
				size_t i = 0;
				results.resize( functions->size() );
				
				std::vector<CallBack*>::iterator it = functions->begin();
				while ( it != functions->end() ) {
					CallBack* cb = *it;
					CallbackType* callBack = (CallbackType*)cb;
					
					results[i] = callBack->invoke( p1, p2, p3, p4, p5, p6 );
					
					++i;
					++it;
				}
				
				result = results.back();
			}
		}

		return result;
	}


	AsyncResult* beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncCallback* callback ) {
		AsyncResult* result = new AsyncResult(callback,runCallbacksAsync_);

		std::vector<CallBack*> tmp;
		getCallbacks(tmp);

		std::vector<CallBack*>::iterator it = tmp.begin();
		while ( it != tmp.end() ) {
			CallBack* cb = *it;
			CallbackType* callBack = (CallbackType*)cb;

			callBack->beginInvoke( p1, p2, p3, p4, p5, p6, result, callback, this );			

			++it;
		}

		result->doWork();

		return result;
	}


	ReturnType endInvoke( AsyncResult* asyncResult );

	Results endInvokeWithResults( AsyncResult* asyncResult );	

	Results results;
protected:
	ResultsCache<ReturnType> resultsCache_;
	virtual void functionFinished( AsyncResult*, Runnable* runnable );
};








inline void Procedure::beginInvoke( AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedProcedure<> proc(staticFuncPtr);

		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename ClassType>
inline void ClassProcedure<ClassType>::beginInvoke( AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedProcedure<ClassType> proc(funcSrc, classFuncPtr);
	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}


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



template <typename P1,
			typename P2 >
inline void Procedure2<P1,P2>::beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedProcedure2<P1,P2> proc(p1, p2, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename P1, 
			typename P2, 
			typename ClassType>
inline void ClassProcedure2<P1,P2,ClassType>::beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedProcedure2<P1,P2,ClassType> proc(funcSrc, p1, p2, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}





template <typename P1,
			typename P2,
			typename P3 >
inline void Procedure3<P1,P2,P3>::beginInvoke( P1 p1, P2 p2, P3 p3, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedProcedure3<P1,P2,P3> proc(p1, p2, p3, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename P1, 
			typename P2, 
			typename P3,
			typename ClassType>
inline void ClassProcedure3<P1,P2,P3,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedProcedure3<P1,P2,P3,ClassType> proc(funcSrc, p1, p2, p3, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}



template <typename P1,
			typename P2,
			typename P3,
			typename P4>
inline void Procedure4<P1,P2,P3,P4>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedProcedure4<P1,P2,P3,P4> proc(p1, p2, p3, p4, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename P1, 
			typename P2, 
			typename P3,
			typename P4,
			typename ClassType>
inline void ClassProcedure4<P1,P2,P3,P4,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedProcedure4<P1,P2,P3,P4,ClassType> proc(funcSrc, p1, p2, p3, p4, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}




template <typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5>
inline void Procedure5<P1,P2,P3,P4,P5>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedProcedure5<P1,P2,P3,P4,P5> proc(p1, p2, p3, p4, p5, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename P1, 
			typename P2, 
			typename P3,
			typename P4,
			typename P5,
			typename ClassType>
inline void ClassProcedure5<P1,P2,P3,P4,P5,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedProcedure5<P1,P2,P3,P4,P5,ClassType> proc(funcSrc, p1, p2, p3, p4, p5, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}





template <typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5,
			typename P6>
inline void Procedure6<P1,P2,P3,P4,P5,P6>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedProcedure6<P1,P2,P3,P4,P5,P6> proc(p1, p2, p3, p4, p5, p6, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename P1, 
			typename P2, 
			typename P3,
			typename P4,
			typename P5,
			typename P6,
			typename ClassType>
inline void ClassProcedure6<P1,P2,P3,P4,P5,P6,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedProcedure6<P1,P2,P3,P4,P5,P6,ClassType> proc(funcSrc, p1, p2, p3, p4, p5, p6, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}



template <typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5,
			typename P6,
			typename P7>
inline void Procedure7<P1,P2,P3,P4,P5,P6,P7>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedProcedure7<P1,P2,P3,P4,P5,P6,P7> proc(p1, p2, p3, p4, p5, p6, p7, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename P1, 
			typename P2, 
			typename P3,
			typename P4,
			typename P5,
			typename P6,
			typename P7,
			typename ClassType>
inline void ClassProcedure7<P1,P2,P3,P4,P5,P6,P7,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedProcedure7<P1,P2,P3,P4,P5,P6,P7,ClassType> proc(funcSrc, p1, p2, p3, p4, p5, p6, p7, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}





template <typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5,
			typename P6,
			typename P7,
			typename P8>
inline void Procedure8<P1,P2,P3,P4,P5,P6,P7,P8>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedProcedure8<P1,P2,P3,P4,P5,P6,P7,P8> proc(p1, p2, p3, p4, p5, p6, p7, p8, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename P1, 
			typename P2, 
			typename P3,
			typename P4,
			typename P5,
			typename P6,
			typename P7,
			typename P8,
			typename ClassType>
inline void ClassProcedure8<P1,P2,P3,P4,P5,P6,P7,P8,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, P7 p7, P8 p8, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedProcedure8<P1,P2,P3,P4,P5,P6,P7,ClassType> proc(funcSrc, p1, p2, p3, p4, p5, p6, p7, p8, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}














template <typename ReturnType>
inline void Function<ReturnType>::beginInvoke( AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedFunction<ReturnType> proc(staticFuncPtr);

		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename ReturnType,typename ClassType>
inline void ClassFunction<ReturnType,ClassType>::beginInvoke( AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedFunction<ClassType> proc(funcSrc, classFuncPtr);
	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}


template <typename ReturnType,typename P1>
inline void Function1<ReturnType,P1>::beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedFunction1<ReturnType, P1> proc(p1, staticFuncPtr);

		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename ReturnType,typename P1, typename ClassType>
inline void ClassFunction1<ReturnType,P1,ClassType>::beginInvoke( P1 p1, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedFunction1<ReturnType, P1,ClassType> proc(funcSrc, p1, classFuncPtr);
	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}




template <typename ReturnType,typename P1,
			typename P2 >
inline void Function2<ReturnType,P1,P2>::beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedFunction2<ReturnType,P1,P2> proc(p1, p2, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename ReturnType,typename P1, 
			typename P2, 
			typename ClassType>
inline void ClassFunction2<ReturnType,P1,P2,ClassType>::beginInvoke( P1 p1, P2 p2, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedFunction2<ReturnType,P1,P2,ClassType> proc(funcSrc, p1, p2, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}





template <typename ReturnType,typename P1,
			typename P2,
			typename P3 >
inline void Function3<ReturnType,P1,P2,P3>::beginInvoke( P1 p1, P2 p2, P3 p3, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedFunction3<ReturnType,P1,P2,P3> proc(p1, p2, p3, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename ReturnType,typename P1, 
			typename P2, 
			typename P3,
			typename ClassType>
inline void ClassFunction3<ReturnType,P1,P2,P3,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedFunction3<ReturnType,P1,P2,P3,ClassType> proc(funcSrc, p1, p2, p3, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}



template <typename ReturnType,typename P1,
			typename P2,
			typename P3,
			typename P4>
inline void Function4<ReturnType,P1,P2,P3,P4>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedFunction4<ReturnType,P1,P2,P3,P4> proc(p1, p2, p3, p4, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename ReturnType,typename P1, 
			typename P2, 
			typename P3,
			typename P4,
			typename ClassType>
inline void ClassFunction4<ReturnType,P1,P2,P3,P4,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedFunction4<ReturnType,P1,P2,P3,P4,ClassType> proc(funcSrc, p1, p2, p3, p4, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}




template <typename ReturnType,typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5>
inline void Function5<ReturnType,P1,P2,P3,P4,P5>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedFunction5<ReturnType,P1,P2,P3,P4,P5> proc(p1, p2, p3, p4, p5, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename ReturnType,typename P1, 
			typename P2, 
			typename P3,
			typename P4,
			typename P5,
			typename ClassType>
inline void ClassFunction5<ReturnType,P1,P2,P3,P4,P5,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedFunction5<ReturnType,P1,P2,P3,P4,P5,ClassType> proc(funcSrc, p1, p2, p3, p4, p5, classFuncPtr);	
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}





template <typename ReturnType,typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5,
			typename P6>
inline void Function6<ReturnType,P1,P2,P3,P4,P5,P6>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != staticFuncPtr ) {
		ThreadedFunction6<ReturnType,P1,P2,P3,P4,P5,P6> proc(p1, p2, p3, p4, p5, p6, staticFuncPtr);		
		initialResult->internal_addRunnable( returnObject, proc.getParams() );
	}
}

template <typename ReturnType,typename P1, 
			typename P2, 
			typename P3,
			typename P4,
			typename P5,
			typename P6,
			typename ClassType>
inline void ClassFunction6<ReturnType,P1,P2,P3,P4,P5,P6,ClassType>::beginInvoke( P1 p1, P2 p2, P3 p3, P4 p4, P5 p5, P6 p6, AsyncResult* initialResult, AsyncCallback* callback, AsyncReturns* returnObject )
{
	if ( NULL != classFuncPtr && NULL != funcSrc ) {
		ThreadedFunction6<ReturnType,P1,P2,P3,P4,P5,P6,ClassType> proc(funcSrc, p1, p2, p3, p4, p5, p6, classFuncPtr);	
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



inline void Delegate0::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}


template <typename P1>
inline void Delegate1<P1>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}

template <typename P1,typename P2>
inline void Delegate2<P1,P2>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}

template <typename P1,typename P2,typename P3>
inline void Delegate3<P1,P2,P3>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}


template <typename P1,typename P2,typename P3,typename P4>
inline void Delegate4<P1,P2,P3,P4>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}


template <typename P1,typename P2,typename P3,typename P4,typename P5>
inline void Delegate5<P1,P2,P3,P4,P5>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}

template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6>
inline void Delegate6<P1,P2,P3,P4,P5,P6>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}


template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7>
inline void Delegate7<P1,P2,P3,P4,P5,P6,P7>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}

template <typename P1,typename P2,typename P3,typename P4,typename P5,typename P6,typename P7,typename P8>
inline void Delegate8<P1,P2,P3,P4,P5,P6,P7,P8>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	//no-op for procedures - they don't return values!
}






template <typename ReturnType>
inline void DelegateR<ReturnType>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	ThreadedFunction<ReturnType>* funcParams = (ThreadedFunction<ReturnType>*)runnable;

	ReturnType ret = funcParams->returnValue();

	resultsCache_.addResult( ret, res );
}

template <typename ReturnType>
inline ReturnType 
	DelegateR<ReturnType>::endInvoke( AsyncResult* asyncResult )
{
	ReturnType result = resultsCache_.getLastResult( asyncResult );

	return result;
}

template <typename ReturnType>
inline typename DelegateR<ReturnType>::Results 
	DelegateR<ReturnType>::endInvokeWithResults( AsyncResult* asyncResult )
{
	Results result;

	Results* res = resultsCache_.getResults();
	
	if ( NULL != res ) {
		result = *res;
	}	

	return result;
}





template <typename ReturnType, typename P1>
inline void Delegate1R<ReturnType,P1>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	ThreadedFunction1<ReturnType,P1>* funcParams = (ThreadedFunction1<ReturnType,P1>*)runnable;

	ReturnType ret = funcParams->returnValue();

	resultsCache_.addResult( ret, res );
}

template <typename ReturnType, 
			typename P1>
inline ReturnType 
	Delegate1R<ReturnType,P1>::endInvoke( AsyncResult* asyncResult )
{
	ReturnType result = resultsCache_.getLastResult( asyncResult );

	return result;
}

template <typename ReturnType, 
			typename P1>
inline typename Delegate1R<ReturnType,P1>::Results 
	Delegate1R<ReturnType,P1>::endInvokeWithResults( AsyncResult* asyncResult )
{
	Results result;

	Results* res = resultsCache_.getResults();
	
	if ( NULL != res ) {
		result = *res;
	}	

	return result;
}



template <typename ReturnType, typename P1, typename P2>
inline void Delegate2R<ReturnType,P1,P2>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	ThreadedFunction2<ReturnType,P1,P2>* funcParams = (ThreadedFunction2<ReturnType,P1,P2>*)runnable;

	ReturnType ret = funcParams->returnValue();

	resultsCache_.addResult( ret, res );
}

template <typename ReturnType, typename P1, typename P2>
inline ReturnType Delegate2R<ReturnType,P1,P2>::endInvoke( AsyncResult* asyncResult )
{
	ReturnType result = resultsCache_.getLastResult( asyncResult );

	return result;
}

template <typename ReturnType, typename P1, typename P2>
inline typename Delegate2R<ReturnType,P1,P2>::Results Delegate2R<ReturnType,P1,P2>::endInvokeWithResults( AsyncResult* asyncResult )
{
	Results result;

	Results* res = resultsCache_.getResults();
	
	if ( NULL != res ) {
		result = *res;
	}
	

	return result;
}







template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3>
inline void Delegate3R<ReturnType,P1,P2,P3>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	ThreadedFunction3<ReturnType,P1,P2,P3>* funcParams = 
		(ThreadedFunction3<ReturnType,P1,P2,P3>*)runnable;

	ReturnType ret = funcParams->returnValue();

	resultsCache_.addResult( ret, res );
}

template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3>
inline ReturnType 
	Delegate3R<ReturnType,P1,P2,P3>::endInvoke( AsyncResult* asyncResult )
{
	ReturnType result = resultsCache_.getLastResult( asyncResult );

	return result;
}

template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3>
inline typename Delegate3R<ReturnType,P1,P2,P3>::Results 
	Delegate3R<ReturnType,P1,P2,P3>::endInvokeWithResults( AsyncResult* asyncResult )
{
	Results result;

	Results* res = resultsCache_.getResults();
	
	if ( NULL != res ) {
		result = *res;
	}	

	return result;
}








template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3,
			typename P4>
inline void Delegate4R<ReturnType,P1,P2,P3,P4>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	ThreadedFunction4<ReturnType,P1,P2,P3,P4>* funcParams = 
		(ThreadedFunction4<ReturnType,P1,P2,P3,P4>*)runnable;

	ReturnType ret = funcParams->returnValue();

	resultsCache_.addResult( ret, res );
}

template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3,
			typename P4>
inline ReturnType 
	Delegate4R<ReturnType,P1,P2,P3,P4>::endInvoke( AsyncResult* asyncResult )
{
	ReturnType result = resultsCache_.getLastResult( asyncResult );

	return result;
}

template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3,
			typename P4>
inline typename Delegate4R<ReturnType,P1,P2,P3,P4>::Results 
	Delegate4R<ReturnType,P1,P2,P3,P4>::endInvokeWithResults( AsyncResult* asyncResult )
{
	Results result;

	Results* res = resultsCache_.getResults();
	
	if ( NULL != res ) {
		result = *res;
	}	

	return result;
}









template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5>
inline void Delegate5R<ReturnType,P1,P2,P3,P4,P5>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	ThreadedFunction5<ReturnType,P1,P2,P3,P4,P5>* funcParams = 
		(ThreadedFunction5<ReturnType,P1,P2,P3,P4,P5>*)runnable;

	ReturnType ret = funcParams->returnValue();

	resultsCache_.addResult( ret, res );
}

template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5>
inline ReturnType 
	Delegate5R<ReturnType,P1,P2,P3,P4,P5>::endInvoke( AsyncResult* asyncResult )
{
	ReturnType result = resultsCache_.getLastResult( asyncResult );

	return result;
}

template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5>
inline typename Delegate5R<ReturnType,P1,P2,P3,P4,P5>::Results 
	Delegate5R<ReturnType,P1,P2,P3,P4,P5>::endInvokeWithResults( AsyncResult* asyncResult )
{
	Results result;

	Results* res = resultsCache_.getResults();
	
	if ( NULL != res ) {
		result = *res;
	}	

	return result;
}








template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5,
			typename P6>
inline void Delegate6R<ReturnType,P1,P2,P3,P4,P5,P6>::functionFinished( AsyncResult* res, Runnable* runnable )
{
	ThreadedFunction6<ReturnType,P1,P2,P3,P4,P5,P6>* funcParams = 
		(ThreadedFunction6<ReturnType,P1,P2,P3,P4,P5,P6>*)runnable;

	ReturnType ret = funcParams->returnValue();

	resultsCache_.addResult( ret, res );
}

template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5,
			typename P6>
inline ReturnType 
	Delegate6R<ReturnType,P1,P2,P3,P4,P5,P6>::endInvoke( AsyncResult* asyncResult )
{
	ReturnType result = resultsCache_.getLastResult( asyncResult );

	return result;
}

template <typename ReturnType, 
			typename P1,
			typename P2,
			typename P3,
			typename P4,
			typename P5,
			typename P6>
inline typename Delegate6R<ReturnType,P1,P2,P3,P4,P5,P6>::Results 
	Delegate6R<ReturnType,P1,P2,P3,P4,P5,P6>::endInvokeWithResults( AsyncResult* asyncResult )
{
	Results result;

	Results* res = resultsCache_.getResults();
	
	if ( NULL != res ) {
		result = *res;
	}	

	return result;
}







}; //namespace VCF

#endif //_VCF_DELEGATES_H__

