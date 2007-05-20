////ThreadMeth.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/ThreadManager.h"

#include <deque>

using namespace VCF;



class NullClassType0 {
	public:
		void m(){}
		void m(Thread*){}
};


template <typename ClassType=NullClassType0 >
class ThreadedProcedure: public Runnable {
public:	
	typedef void (ClassType::*ClassProcPtr0)();
	typedef void (ClassType::*ClassThreadProcPtr0)( Thread* thread );

	

	ThreadedProcedure( ClassType* src, ClassProcPtr0 procPtr ): 
		runningThread_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedProcedure<ClassType>* params = 
			new ThreadedProcedure<ClassType>();

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}


	ThreadedProcedure( ClassType* src, ClassThreadProcPtr0 procPtr ):
			runningThread_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure<ClassType>* params = 
			new ThreadedProcedure<ClassType>();

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}




	

	
protected:

	ThreadedProcedure():
			runningThread_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

public:
	virtual bool run() {		
		if ( NULL != instancePtr_ ) {
			if ( NULL != classThreadProcPtr_ ) {
				(instancePtr_->*classThreadProcPtr_)( runningThread_ );
			}
			else if ( NULL != classProcPtr_ ) {
				(instancePtr_->*classProcPtr_)();
			}
			else {
				return false;
			}	
			
		}
		return true;
	}

	virtual void stop(){}


	operator Thread* () {
		return runningThread_;
	}
protected:
	
	Thread* runningThread_;
	ClassProcPtr0 classProcPtr_;
	ClassThreadProcPtr0 classThreadProcPtr_;
	ClassType* instancePtr_;
};



template <>
class ThreadedProcedure<NullClassType0>: public Runnable {
public:
	typedef void (*ProcPtr0)();
	typedef void (*ProcThreadPtr0)(Thread* thread);	
	typedef NullClassType0 ClassType;	

	ThreadedProcedure( ProcPtr0 procPtr ):
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL){

		ThreadedProcedure<ClassType>* params = 
			new ThreadedProcedure<ClassType>();

		params->procPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure( ProcThreadPtr0 procPtr ): 
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL){

		ThreadedProcedure<ClassType>* params = 
			new ThreadedProcedure<ClassType>();

		params->procThreadPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}	

	
	ThreadedProcedure(): runningThread_(NULL), procPtr_(NULL), procThreadPtr_(NULL){}

public:
	virtual bool run() {		
		if ( NULL != procThreadPtr_ ) {
			(*procThreadPtr_)( runningThread_ );
		}
		else if ( NULL != procPtr_ ) {
			(*procPtr_)();
		}
		else {
			return false;
		}
		return true;
	}

	virtual void stop(){}


	operator Thread* () {
		return runningThread_;
	}
protected:
	
	Thread* runningThread_;
	ProcPtr0 procPtr_;
	ProcThreadPtr0 procThreadPtr_;	
};





template <typename ParamType1>
class NullClassType1 {
	public:
		void m(ParamType1){}
		void m(Thread*, ParamType1){}
};


template <typename ParamType1, typename ClassType=NullClassType1<ParamType1> >
class ThreadedProcedure1: public Runnable {
public:

	typedef NullClassType1<ParamType1> NullClassType;

	typedef void (*ProcPtr1)(ParamType1 p1);
	typedef void (*ProcThreadPtr1)(Thread* thread, ParamType1 p1);	

	typedef void (ClassType::*ClassProcPtr1)( ParamType1 p1 );
	typedef void (ClassType::*ClassThreadProcPtr1)( Thread* thread, ParamType1 p1 );

	

	ThreadedProcedure1( ParamType1 p1, ProcPtr1 procPtr ): param1_(p1),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure1<ParamType1,ClassType>* params = 
			new ThreadedProcedure1<ParamType1,ClassType>(p1);

		params->procPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure1( ParamType1 p1, ProcThreadPtr1 procPtr ): param1_(p1),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure1<ParamType1,ClassType>* params = 
			new ThreadedProcedure1<ParamType1,ClassType>(p1);

		params->procThreadPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure1( ClassType* src, ParamType1 p1, ClassProcPtr1 procPtr ): param1_(p1),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedProcedure1<ParamType1,ClassType>* params = 
			new ThreadedProcedure1<ParamType1,ClassType>(p1);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}


	ThreadedProcedure1( ClassType* src, ParamType1 p1, ClassThreadProcPtr1 procPtr ): param1_(p1),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure1<ParamType1,ClassType>* params = 
			new ThreadedProcedure1<ParamType1,ClassType>(p1);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}




	

	
protected:

	ThreadedProcedure1( ParamType1 p1 ): param1_(p1),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

public:
	virtual bool run() {


		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != procThreadPtr_ ) {
				(*procThreadPtr_)( runningThread_, param1_ );
			}
			else if ( NULL != procPtr_ ) {
				(*procPtr_)( param1_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadProcPtr_ ) {
					(instancePtr_->*classThreadProcPtr_)( runningThread_, param1_ );
				}
				else if ( NULL != classProcPtr_ ) {
					(instancePtr_->*classProcPtr_)( param1_ );
				}
				else {
					return false;
				}	
				
			}
		}
		

		return true;
	}

	virtual void stop(){}


	operator Thread* () {
		return runningThread_;
	}
protected:
	
	ParamType1 param1_;
	Thread* runningThread_;
	ProcPtr1 procPtr_;
	ProcThreadPtr1 procThreadPtr_;
	ClassProcPtr1 classProcPtr_;
	ClassThreadProcPtr1 classThreadProcPtr_;
	ClassType* instancePtr_;
};






template <
	typename ParamType1, 
	typename ParamType2
	>
class NullClassType2 {
	public:
		void m(ParamType1, ParamType2){}
		void m(Thread*, ParamType1, ParamType2){}
};


template <
	typename ParamType1, 
	typename ParamType2, 
	typename ClassType=NullClassType2<ParamType1,ParamType2> 
	>
class ThreadedProcedure2: public Runnable {
public:

	typedef NullClassType2<ParamType1,ParamType2> NullClassType;

	typedef void (*ProcPtr2)(ParamType1 p1,ParamType2 p2);
	typedef void (*ProcThreadPtr2)(Thread* thread, ParamType1 p1, ParamType2 p2);	

	typedef void (ClassType::*ClassProcPtr2)(ParamType1 p1,ParamType2 p2);
	typedef void (ClassType::*ClassThreadProcPtr2)(Thread* thread, ParamType1 p1, ParamType2 p2);


	ThreadedProcedure2( ParamType1 p1, ParamType2 p2, ProcPtr2 procPtr ): param1_(p1), param2_(p2),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure2<ParamType1,ParamType2,ClassType>* params = 
			new ThreadedProcedure2<ParamType1,ParamType2,ClassType>(p1,p2);

		params->procPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure2( ParamType1 p1, ParamType2 p2, ProcThreadPtr2 procPtr ): param1_(p1), param2_(p2),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure2<ParamType1,ParamType2,ClassType>* params = 
			new ThreadedProcedure2<ParamType1,ParamType2,ClassType>(p1,p2);

		params->procThreadPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure2( ClassType* src, ParamType1 p1, ParamType2 p2, ClassProcPtr2 procPtr ): param1_(p1), param2_(p2),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedProcedure2<ParamType1,ParamType2,ClassType>* params = 
			new ThreadedProcedure2<ParamType1,ParamType2,ClassType>(p1,p2);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}


	ThreadedProcedure2( ClassType* src, ParamType1 p1, ParamType2 p2, ClassThreadProcPtr2 procPtr ): param1_(p1),param2_(p2),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure2<ParamType1,ParamType2,ClassType>* params = 
			new ThreadedProcedure2<ParamType1,ParamType2,ClassType>(p1,p2);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	virtual bool run() {
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != procThreadPtr_ ) {
				(*procThreadPtr_)( runningThread_, param1_, param2_ );
			}
			else if ( NULL != procPtr_ ) {
				(*procPtr_)( param1_, param2_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadProcPtr_ ) {
					(instancePtr_->*classThreadProcPtr_)( runningThread_, param1_, param2_ );
				}
				else if ( NULL != classProcPtr_ ) {
					(instancePtr_->*classProcPtr_)( param1_, param2_ );
				}
				else {
					return false;
				}	
				
			}
		}
		

		return true;
	}

	virtual void stop(){}


	operator Thread* () {
		return runningThread_;
	}


protected:

	ThreadedProcedure2( ParamType1 p1, ParamType2 p2 ): param1_(p1), param2_(p2),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

	
	ParamType1 param1_;
	ParamType2 param2_;
	Thread* runningThread_;
	ProcPtr2 procPtr_;
	ProcThreadPtr2 procThreadPtr_;
	ClassProcPtr2 classProcPtr_;
	ClassThreadProcPtr2 classThreadProcPtr_;
	ClassType* instancePtr_;
};









template <
	typename ParamType1, 
	typename ParamType2, 
	typename ParamType3
	>
class NullClassType3 {
	public:
		void m(ParamType1, ParamType2, ParamType3){}
		void m(Thread*, ParamType1, ParamType2, ParamType3){}
};


template <
	typename ParamType1, 
	typename ParamType2, 
	typename ParamType3, 
	typename ClassType=NullClassType3<ParamType1,ParamType2,ParamType3> 
	>
class ThreadedProcedure3: public Runnable {
public:

	typedef NullClassType3<ParamType1,ParamType2,ParamType3> NullClassType;

	typedef void (*ProcPtr3)(ParamType1 p1,ParamType2 p2,ParamType3 p3);
	typedef void (*ProcThreadPtr3)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3);	

	typedef void (ClassType::*ClassProcPtr3)(ParamType1 p1,ParamType2 p2, ParamType3 p3);
	typedef void (ClassType::*ClassThreadProcPtr3)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3);

	

	ThreadedProcedure3( ParamType1 p1, ParamType2 p2, ParamType3 p3, ProcPtr3 procPtr ): param1_(p1), param2_(p2), param3_(p3),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure3<ParamType1,ParamType2,ParamType3,ClassType>* params = 
			new ThreadedProcedure3<ParamType1,ParamType2,ParamType3,ClassType>(p1,p2,p3);

		params->procPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure3( ParamType1 p1, ParamType2 p2, ParamType3 p3, ProcThreadPtr3 procPtr ): param1_(p1), param2_(p2), param3_(p3),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure3<ParamType1,ParamType2,ParamType3,ClassType>* params = 
			new ThreadedProcedure3<ParamType1,ParamType2,ParamType3,ClassType>(p1,p2,p3);

		params->procThreadPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure3( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ClassProcPtr3 procPtr ): param1_(p1), param2_(p2), param3_(p3),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedProcedure3<ParamType1,ParamType2,ParamType3,ClassType>* params = 
			new ThreadedProcedure3<ParamType1,ParamType2,ParamType3,ClassType>(p1,p2,p3);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}


	ThreadedProcedure3( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ClassThreadProcPtr3 procPtr ): param1_(p1),param2_(p2),param3_(p3),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure3<ParamType1,ParamType2,ParamType3,ClassType>* params = 
			new ThreadedProcedure3<ParamType1,ParamType2,ParamType3,ClassType>(p1,p2,p3);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	virtual bool run() {
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != procThreadPtr_ ) {
				(*procThreadPtr_)( runningThread_, param1_, param2_, param3_ );
			}
			else if ( NULL != procPtr_ ) {
				(*procPtr_)( param1_, param2_, param3_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadProcPtr_ ) {
					(instancePtr_->*classThreadProcPtr_)( runningThread_, param1_, param2_, param3_ );
				}
				else if ( NULL != classProcPtr_ ) {
					(instancePtr_->*classProcPtr_)( param1_, param2_, param3_ );
				}
				else {
					return false;
				}	
				
			}
		}
		

		return true;
	}

	virtual void stop(){}


	operator Thread* () {
		return runningThread_;
	}


protected:

	ThreadedProcedure3( ParamType1 p1, ParamType2 p2, ParamType3 p3 ): param1_(p1), param2_(p2), param3_(p3),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

	
	ParamType1 param1_;
	ParamType2 param2_;
	ParamType3 param3_;
	Thread* runningThread_;
	ProcPtr3 procPtr_;
	ProcThreadPtr3 procThreadPtr_;
	ClassProcPtr3 classProcPtr_;
	ClassThreadProcPtr3 classThreadProcPtr_;
	ClassType* instancePtr_;
};









template <
	typename ParamType1, 
	typename ParamType2, 
	typename ParamType3,
	typename ParamType4
	>
class NullClassType4 {
	public:
		void m(ParamType1, ParamType2, ParamType3,ParamType4){}
		void m(Thread*, ParamType1, ParamType2, ParamType3,ParamType4){}
};


template <
	typename ParamType1, 
	typename ParamType2, 
	typename ParamType3, 
	typename ParamType4, 
	typename ClassType=NullClassType4<ParamType1,ParamType2,ParamType3,ParamType4> 
	>
class ThreadedProcedure4: public Runnable {
public:

	typedef NullClassType4<ParamType1,ParamType2,ParamType3,ParamType4> NullClassType;

	typedef void (*ProcPtr4)(ParamType1 p1,ParamType2 p2,ParamType3 p3,ParamType4 p4);
	typedef void (*ProcThreadPtr4)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4);	

	typedef void (ClassType::*ClassProcPtr4)(ParamType1 p1,ParamType2 p2, ParamType3 p3, ParamType4 p4);
	typedef void (ClassType::*ClassThreadProcPtr4)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4);

	

	ThreadedProcedure4( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ProcPtr4 procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ClassType>* params = 
			new ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ClassType>(p1,p2,p3,p4);

		params->procPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure4( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4,ProcThreadPtr4 procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ClassType>* params = 
			new ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ClassType>(p1,p2,p3,p4);

		params->procThreadPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure4( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ClassProcPtr4 procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ClassType>* params = 
			new ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ClassType>(p1,p2,p3,p4);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}


	ThreadedProcedure4( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ClassThreadProcPtr4 procPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ClassType>* params = 
			new ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ClassType>(p1,p2,p3,p4);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	virtual bool run() {
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != procThreadPtr_ ) {
				(*procThreadPtr_)( runningThread_, param1_, param2_, param3_, param4_ );
			}
			else if ( NULL != procPtr_ ) {
				(*procPtr_)( param1_, param2_, param3_, param4_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadProcPtr_ ) {
					(instancePtr_->*classThreadProcPtr_)( runningThread_, param1_, param2_, param3_, param4_ );
				}
				else if ( NULL != classProcPtr_ ) {
					(instancePtr_->*classProcPtr_)( param1_, param2_, param3_, param4_ );
				}
				else {
					return false;
				}	
				
			}
		}
		

		return true;
	}

	virtual void stop(){}


	operator Thread* () {
		return runningThread_;
	}


protected:

	ThreadedProcedure4( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4 ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

	
	ParamType1 param1_;
	ParamType2 param2_;
	ParamType3 param3_;
	ParamType4 param4_;
	Thread* runningThread_;
	ProcPtr4 procPtr_;
	ProcThreadPtr4 procThreadPtr_;
	ClassProcPtr4 classProcPtr_;
	ClassThreadProcPtr4 classThreadProcPtr_;
	ClassType* instancePtr_;
};








template <
	typename ParamType1, 
	typename ParamType2, 
	typename ParamType3,
	typename ParamType4,
	typename ParamType5
	>
class NullClassType5 {
	public:
		void m(ParamType1, ParamType2, ParamType3,ParamType4,ParamType5){}
		void m(Thread*, ParamType1, ParamType2, ParamType3,ParamType4,ParamType5){}
};


template <
	typename ParamType1, 
	typename ParamType2, 
	typename ParamType3, 
	typename ParamType4, 
	typename ParamType5, 
	typename ClassType=NullClassType5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5> 
	>
class ThreadedProcedure5: public Runnable {
public:

	typedef NullClassType5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5> NullClassType;

	typedef void (*ProcPtr5)(ParamType1 p1,ParamType2 p2,ParamType3 p3,ParamType4 p4, ParamType5 p5);
	typedef void (*ProcThreadPtr5)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4, ParamType5 p5);	

	typedef void (ClassType::*ClassProcPtr5)(ParamType1 p1,ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5);
	typedef void (ClassType::*ClassThreadProcPtr5)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5);

	

	ThreadedProcedure5( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ProcPtr5 procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType>* params = 
			new ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType>(p1,p2,p3,p4,p5);

		params->procPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure5( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4,ParamType5 p5,ProcThreadPtr5 procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType>* params = 
			new ThreadedProcedure5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType>(p1,p2,p3,p4,p5);

		params->procThreadPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure5( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ClassProcPtr5 procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedProcedure5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType>* params = 
			new ThreadedProcedure5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType>(p1,p2,p3,p4,p5);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}


	ThreadedProcedure5( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ClassThreadProcPtr5 procPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType>* params = 
			new ThreadedProcedure5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType>(p1,p2,p3,p4,p5);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	virtual bool run() {
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != procThreadPtr_ ) {
				(*procThreadPtr_)( runningThread_, param1_, param2_, param3_, param4_, param5_ );
			}
			else if ( NULL != procPtr_ ) {
				(*procPtr_)( param1_, param2_, param3_, param4_, param5_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadProcPtr_ ) {
					(instancePtr_->*classThreadProcPtr_)( runningThread_, param1_, param2_, param3_, param4_, param5_ );
				}
				else if ( NULL != classProcPtr_ ) {
					(instancePtr_->*classProcPtr_)( param1_, param2_, param3_, param4_, param5_ );
				}
				else {
					return false;
				}	
				
			}
		}
		

		return true;
	}

	virtual void stop(){}


	operator Thread* () {
		return runningThread_;
	}


protected:

	ThreadedProcedure5( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5 ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),param5_(p5),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

	
	ParamType1 param1_;
	ParamType2 param2_;
	ParamType3 param3_;
	ParamType4 param4_;
	ParamType5 param5_;
	Thread* runningThread_;
	ProcPtr5 procPtr_;
	ProcThreadPtr5 procThreadPtr_;
	ClassProcPtr5 classProcPtr_;
	ClassThreadProcPtr5 classThreadProcPtr_;
	ClassType* instancePtr_;
};









template <
	typename ParamType1, 
	typename ParamType2, 
	typename ParamType3,
	typename ParamType4,
	typename ParamType5,
	typename ParamType6 
	>
class NullClassType6 {
	public:
		void m(ParamType1, ParamType2, ParamType3,ParamType4,ParamType5,ParamType6){}
		void m(Thread*, ParamType1, ParamType2, ParamType3,ParamType4,ParamType5,ParamType6){}
};


template <
	typename ParamType1, 
	typename ParamType2, 
	typename ParamType3, 
	typename ParamType4, 
	typename ParamType5, 
	typename ParamType6, 
	typename ClassType=NullClassType6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6> 
	>
class ThreadedProcedure6: public Runnable {
public:

	typedef NullClassType6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6> NullClassType;

	typedef void (*ProcPtr6)(ParamType1 p1,ParamType2 p2,ParamType3 p3,ParamType4 p4, ParamType5 p5, ParamType6 p6);
	typedef void (*ProcThreadPtr6)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4, ParamType5 p5, ParamType6 p6);	

	typedef void (ClassType::*ClassProcPtr6)(ParamType1 p1,ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6);
	typedef void (ClassType::*ClassThreadProcPtr6)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6);

	

	ThreadedProcedure6( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6, ProcPtr6 procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),param6_(p6),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType>* params = 
			new ThreadedProcedure6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType>(p1,p2,p3,p4,p5,p6);

		params->procPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure6( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4,ParamType5 p5,ParamType6 p6,ProcThreadPtr6 procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),param6_(p6),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType>* params = 
			new ThreadedProcedure6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType>(p1,p2,p3,p4,p5,p6);

		params->procThreadPtr_ = procPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedProcedure6( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6, ClassProcPtr6 procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),param6_(p6),
		runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedProcedure6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType>* params = 
			new ThreadedProcedure6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType>(p1,p2,p3,p4,p5);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}


	ThreadedProcedure6( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ClassThreadProcPtr6 procPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),param6_(p6),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		ThreadedProcedure6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType>* params = 
			new ThreadedProcedure6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType>(p1,p2,p3,p4,p5,p6);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	virtual bool run() {
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != procThreadPtr_ ) {
				(*procThreadPtr_)( runningThread_, param1_, param2_, param3_, param4_, param5_, param6_ );
			}
			else if ( NULL != procPtr_ ) {
				(*procPtr_)( param1_, param2_, param3_, param4_, param5_, param6_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadProcPtr_ ) {
					(instancePtr_->*classThreadProcPtr_)( runningThread_, param1_, param2_, param3_, param4_, param5_, param6_ );
				}
				else if ( NULL != classProcPtr_ ) {
					(instancePtr_->*classProcPtr_)( param1_, param2_, param3_, param4_, param5_, param6_ );
				}
				else {
					return false;
				}	
				
			}
		}
		

		return true;
	}

	virtual void stop(){}


	operator Thread* () {
		return runningThread_;
	}


protected:

	ThreadedProcedure6( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6 ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),param5_(p5),param6_(p6),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

	
	ParamType1 param1_;
	ParamType2 param2_;
	ParamType3 param3_;
	ParamType4 param4_;
	ParamType5 param5_;
	ParamType6 param6_;
	Thread* runningThread_;
	ProcPtr6 procPtr_;
	ProcThreadPtr6 procThreadPtr_;
	ClassProcPtr6 classProcPtr_;
	ClassThreadProcPtr6 classThreadProcPtr_;
	ClassType* instancePtr_;
};







///////////////////////////////////////////////////////////////////////////////
template <typename ReturnType>
class NullReturnClassType0 {
public:
	ReturnType m(){ return ReturnType(); }
	ReturnType m(Thread*){ return ReturnType(); }
};

template <typename ReturnType, typename ClassType=NullReturnClassType0<ReturnType> >
class ThreadedFunction: public Runnable {
public:	
	typedef ReturnType (*FuncPtr)();
	typedef ReturnType (*FuncThreadPtr)(Thread* thread);	

	typedef ReturnType (ClassType::*ClassFuncPtr)();
	typedef ReturnType (ClassType::*ClassThreadFuncPtr)( Thread* thread );


	ThreadedFunction( FuncPtr funcPtr ): 
		runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedFunction<ReturnType,ClassType>* params = 
			new ThreadedFunction<ReturnType,ClassType>(true);

		params->funcPtr_ = funcPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}

	ThreadedFunction( FuncThreadPtr funcPtr ): 
		runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedFunction<ReturnType,ClassType>* params = 
			new ThreadedFunction<ReturnType,ClassType>(true);

		params->classFuncPtr_ = funcPtr;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}



	ThreadedFunction( ClassType* src, ClassFuncPtr funcPtr ): 
		runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		ThreadedFunction<ReturnType,ClassType>* params = 
			new ThreadedFunction<ReturnType,ClassType>(true);

		params->classFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}


	ThreadedFunction( ClassType* src, ClassThreadFuncPtr funcPtr ):
			runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){

		ThreadedFunction<ReturnType,ClassType>* params = 
			new ThreadedFunction<ReturnType,ClassType>(true);

		params->classThreadFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		runningThread_ = new Thread( params, true, true );
		params->runningThread_ = runningThread_;

		runningThread_->start();
	}
	


protected:
	ThreadedFunction(bool):
			runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){
	}

	


public:
	virtual bool run() {		
		if ( NULL != instancePtr_ ) {
			if ( NULL != classThreadFuncPtr_ ) {
				(instancePtr_->*classThreadFuncPtr_)( runningThread_ );
			}
			else if ( NULL != classFuncPtr_ ) {
				(instancePtr_->*classFuncPtr_)();
			}
			else {
				return false;
			}	
			
		}
		return true;
	}

	virtual void stop(){}


	operator Thread* () {
		return runningThread_;
	}
protected:
	
	Thread* runningThread_;
	FuncPtr funcPtr_;
	FuncThreadPtr threadFuncPtr_;
	ClassFuncPtr classFuncPtr_;
	ClassThreadFuncPtr classThreadFuncPtr_;
	ClassType* instancePtr_;
};










#include "ThreadPool.h"

#include "Delegates.h"



void doit( int i ) {
	printf( "Hello from doit! i: %d\n", i );
}




void doit2( Thread* th, int i ) {
	printf( "Hello from doit2! i: %d, th: %p, tid: 0x%04x \n", i, th, th->getThreadID() );

}

class Snarfy {
public:
	void thisBlows( int g ) {
		printf( "Hello from thisBlows! i: %d, this ptr: %p\n", g, this );
	}
};


class Swanky {
public:
	void doit( double& d, const String& s ) {
		printf( "Hello from Swanky::doit! d: %0.3f, s: %s, this ptr: %p\n", 
					d, s.ansi_c_str(), this );
	}


	void doit2( Thread* th, double& d, const String& s ) {
		printf( "Hello from Swanky::doit! d: %0.3f, s: %s, this ptr: %p\n", 
					d, s.ansi_c_str(), this );

		for (int i=0;i<10;i++) {
			th->sleep(1000);
		}
	}

	void doit3() {
		printf( "Hello from Swanky::doit3! this ptr: %p\n", this );
	}
};



void abc(int,double,char)
{

}

void abc2(int, const String&,double,char,bool,Object*)
{

}

void abc3(){

}


int abc4()
{
	return 100;
}

class FooBar {
public:	
	int duh()
	{
		return 100;
	}
};

bool duhDoIt( const String& str, double d )
{
	bool result = true;
	printf( "duhDoIt() %s, %0.5f, returning %d\n", str.ansi_c_str(), d, result );
	return result;
}


class Blooper : public Object {
public:

	bool stuffIt( const String& str, double d )
	{
		bool result = false;
		printf( "Blooper::stuffIt() %s, %0.5f, returning %d\n", str.ansi_c_str(), d, result );
		return result;
	}

};


class RunThis : public Runnable {
public:
	RunThis(){
		printf( "Creating RunThis %p\n", this );
	}

	virtual ~RunThis() {
		printf( "Deleting RunThis %p\n", this );
	}

	virtual bool run() {

		Thread* th = ThreadManager::getCurrentThread();

		printf( "RunThis %p on thread %p id 0x%04x\n", this, th, th->getThreadID() );
		th->sleep(3000);
		return true;
	}

	virtual void stop(){}
};




int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	Snarfy sn;
	/*

	Thread* th = ThreadedProcedure1<int>(10,doit);

	th->wait();

	th = ThreadedProcedure1<int>(231,doit2);

	th->wait();
	
	
	

	th = ThreadedProcedure1<int,Snarfy>(&sn,38112,&Snarfy::thisBlows);
	th->wait();



	String s = "hello";
	Swanky sk;

	double d = 0.0332;
	
	th = ThreadedProcedure2<double&,const String&,Swanky>(&sk,d,s,&Swanky::doit2);
	th->wait();


	printf( "Bye!\n");


	ThreadedProcedure3<int,double,char>(10,200.0,'a',abc);


	
	ThreadedProcedure6<int, const String&,double,char,bool,Object*>(10,s,200.0,'a',true,th,abc2);
	
	ThreadedProcedure<Swanky>(&sk, &Swanky::doit3);

	ThreadedProcedure<>(abc3);



	
	ThreadedProcedure<> g(abc3);


	FooBar fb;
	ThreadedFunction<int,FooBar>(&fb, &FooBar::duh);



	ThreadedFunction<int> h(abc4);
	
*/

	Delagate1<int> d2;
	d2 += doit;


	
	d2 += new ClassProcedure1<int,Snarfy>(&sn,&Snarfy::thisBlows,"Snarfy::thisBlows");

	d2.invoke(10);

	String s = d2.at( 0 ).getReturnType().name();


	Delagate2R<bool,const String&,double> d3;

	d3 += duhDoIt;


	Blooper bl;

	d3 += new ClassFunction2<bool,const String&,double,Blooper>(&bl,&Blooper::stuffIt);

	s = d3.at( 1 ).getReturnType().name();
	uint32 ac = d3.at( 1 ).getArgumentCount();
	s = d3.at( 1 ).getArgumentTypeInfo(0).name();
	s = d3.at( 1 ).getArgumentTypeInfo(1).name();

	bool result = d3.invoke("Hola", 120.456);
	printf( "d2 result: %d\n", result );
	for ( int i=0;i<d3.results.size();i++ ) {
		printf( "d2 results[%d]: %d\n", i, (int)d3.results[i] );
	}
	
	{
		ThreadPool pool(3);
		pool.start();
		
		pool.postWork( new RunThis() );
		pool.postWork( new RunThis() );
		pool.postWork( new RunThis() );
		pool.postWork( new RunThis() );
		
		
		pool.wait(  );
		pool.stop();
	}

	FoundationKit::terminate();
	return 0;
}


