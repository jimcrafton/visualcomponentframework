#ifndef _VCF_THREADED_FUNCTIONS_H__
#define _VCF_THREADED_FUNCTIONS_H__


/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

class Thread;

class NullClassType0 {
	public:
		void m(){}
		void m(Thread*){}
};


template <typename ClassType=NullClassType0 >
class ThreadedProcedure: public Runnable {
public:	
	typedef void (ClassType::*ClassProcPtr)();
	typedef void (ClassType::*ClassThreadProcPtr)( Thread* thread );
	typedef ThreadedProcedure<ClassType> BaseClass;
	

	ThreadedProcedure( ClassType* src, ClassProcPtr procPtr ): 			
			internalParams_(NULL),
			runningThread_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass();

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;	
		internalParams_ = params;
	}


	ThreadedProcedure( ClassType* src, ClassThreadProcPtr procPtr ):	
			internalParams_(NULL),
			runningThread_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass();

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;
		internalParams_ = params;		
	}
			
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

	
	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}
protected:

	ThreadedProcedure():
			internalParams_(NULL),
			runningThread_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){	}


	Runnable* internalParams_;
	Thread* runningThread_;
	ClassProcPtr classProcPtr_;
	ClassThreadProcPtr classThreadProcPtr_;
	ClassType* instancePtr_;
};



template <>
class ThreadedProcedure<NullClassType0>: public Runnable {
public:
	typedef void (*ProcPtr)();
	typedef void (*ProcThreadPtr)(Thread* thread);	
	typedef NullClassType0 ClassType;
	typedef ThreadedProcedure<ClassType> BaseClass;

	ThreadedProcedure( ProcPtr procPtr ):
			internalParams_(NULL),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL){

		BaseClass* params = 
			new BaseClass();

		params->procPtr_ = procPtr;

		internalParams_ = params;
	}

	ThreadedProcedure( ProcThreadPtr procPtr ): 
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL){

		BaseClass* params = 
			new BaseClass();

		params->procThreadPtr_ = procPtr;

		internalParams_ = params;		
	}	

	
	ThreadedProcedure(): runningThread_(NULL), procPtr_(NULL), procThreadPtr_(NULL){}


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


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}
protected:
	Runnable* internalParams_;
	Thread* runningThread_;
	ProcPtr procPtr_;
	ProcThreadPtr procThreadPtr_;	
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

	typedef void (*ProcPtr)(ParamType1 p1);
	typedef void (*ProcThreadPtr)(Thread* thread, ParamType1 p1);	

	typedef void (ClassType::*ClassProcPtr)( ParamType1 p1 );
	typedef void (ClassType::*ClassThreadProcPtr)( Thread* thread, ParamType1 p1 );

	typedef ThreadedProcedure1<ParamType1,ClassType> BaseClass;

	ThreadedProcedure1( ParamType1 p1, ProcPtr procPtr ): param1_(p1),
			internalParams_(NULL), runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1);

		params->procPtr_ = procPtr;

		internalParams_ = params;		
	}

	ThreadedProcedure1( ParamType1 p1, ProcThreadPtr procPtr ): param1_(p1),
			internalParams_(NULL), runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1);

		params->procThreadPtr_ = procPtr;

		internalParams_ = params;	
	}

	ThreadedProcedure1( ClassType* src, ParamType1 p1, ClassProcPtr procPtr ): param1_(p1),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;	
	}


	ThreadedProcedure1( ClassType* src, ParamType1 p1, ClassThreadProcPtr procPtr ): param1_(p1),
			internalParams_(NULL),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;		
	}




	
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


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}

	
protected:

	ThreadedProcedure1( ParamType1 p1 ): param1_(p1),
			internalParams_(NULL),
			runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

	
	ParamType1 param1_;
	Runnable* internalParams_;
	Thread* runningThread_;
	ProcPtr procPtr_;
	ProcThreadPtr procThreadPtr_;
	ClassProcPtr classProcPtr_;
	ClassThreadProcPtr classThreadProcPtr_;
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

	typedef void (*ProcPtr)(ParamType1 p1,ParamType2 p2);
	typedef void (*ProcThreadPtr)(Thread* thread, ParamType1 p1, ParamType2 p2);	

	typedef void (ClassType::*ClassProcPtr)(ParamType1 p1,ParamType2 p2);
	typedef void (ClassType::*ClassThreadProcPtr)(Thread* thread, ParamType1 p1, ParamType2 p2);

	typedef ThreadedProcedure2<ParamType1,ParamType2,ClassType> BaseClass;

	ThreadedProcedure2( ParamType1 p1, ParamType2 p2, ProcPtr procPtr ): param1_(p1), param2_(p2),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = new BaseClass(p1,p2);

		params->procPtr_ = procPtr;

		internalParams_ = params;	
	}

	ThreadedProcedure2( ParamType1 p1, ParamType2 p2, ProcThreadPtr procPtr ): param1_(p1), param2_(p2),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2);

		params->procThreadPtr_ = procPtr;

		internalParams_ = params;
	}

	ThreadedProcedure2( ClassType* src, ParamType1 p1, ParamType2 p2, ClassProcPtr procPtr ): param1_(p1), param2_(p2),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedProcedure2( ClassType* src, ParamType1 p1, ParamType2 p2, ClassThreadProcPtr procPtr ): param1_(p1),param2_(p2),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
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


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}


protected:

	ThreadedProcedure2( ParamType1 p1, ParamType2 p2 ): param1_(p1), param2_(p2),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

	
	ParamType1 param1_;
	ParamType2 param2_;
	Runnable* internalParams_;
	Thread* runningThread_;
	ProcPtr procPtr_;
	ProcThreadPtr procThreadPtr_;
	ClassProcPtr classProcPtr_;
	ClassThreadProcPtr classThreadProcPtr_;
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

	typedef void (*ProcPtr)(ParamType1 p1,ParamType2 p2,ParamType3 p3);
	typedef void (*ProcThreadPtr)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3);	

	typedef void (ClassType::*ClassProcPtr)(ParamType1 p1,ParamType2 p2, ParamType3 p3);
	typedef void (ClassType::*ClassThreadProcPtr)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3);

	typedef ThreadedProcedure3<ParamType1,ParamType2,ParamType3,ClassType> BaseClass;
	

	ThreadedProcedure3( ParamType1 p1, ParamType2 p2, ParamType3 p3, ProcPtr procPtr ): param1_(p1), param2_(p2), param3_(p3),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3);

		params->procPtr_ = procPtr;

		internalParams_ = params;
	}

	ThreadedProcedure3( ParamType1 p1, ParamType2 p2, ParamType3 p3, ProcThreadPtr procPtr ): param1_(p1), param2_(p2), param3_(p3),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3);

		params->procThreadPtr_ = procPtr;

		internalParams_ = params;
	}

	ThreadedProcedure3( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ClassProcPtr procPtr ): param1_(p1), param2_(p2), param3_(p3),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedProcedure3( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ClassThreadProcPtr procPtr ): param1_(p1),param2_(p2),param3_(p3),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
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


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}


protected:

	ThreadedProcedure3( ParamType1 p1, ParamType2 p2, ParamType3 p3 ): param1_(p1), param2_(p2), param3_(p3),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){
	}

	
	ParamType1 param1_;
	ParamType2 param2_;
	ParamType3 param3_;
	Runnable* internalParams_;
	Thread* runningThread_;
	ProcPtr procPtr_;
	ProcThreadPtr procThreadPtr_;
	ClassProcPtr classProcPtr_;
	ClassThreadProcPtr classThreadProcPtr_;
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

	typedef void (*ProcPtr)(ParamType1 p1,ParamType2 p2,ParamType3 p3,ParamType4 p4);
	typedef void (*ProcThreadPtr)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4);	

	typedef void (ClassType::*ClassProcPtr)(ParamType1 p1,ParamType2 p2, ParamType3 p3, ParamType4 p4);
	typedef void (ClassType::*ClassThreadProcPtr)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4);

	typedef ThreadedProcedure4<ParamType1,ParamType2,ParamType3,ParamType4,ClassType> BaseClass;

	ThreadedProcedure4( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ProcPtr procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4);

		params->procPtr_ = procPtr;

		internalParams_ = params;
	}

	ThreadedProcedure4( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4,ProcThreadPtr procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4);

		params->procThreadPtr_ = procPtr;

		internalParams_ = params;
		
	}

	ThreadedProcedure4( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ClassProcPtr procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedProcedure4( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ClassThreadProcPtr procPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;		
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


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}


protected:

	ThreadedProcedure4( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4 ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),
			internalParams_(NULL),runningThread_(NULL),
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
	Runnable* internalParams_;
	Thread* runningThread_;
	ProcPtr procPtr_;
	ProcThreadPtr procThreadPtr_;
	ClassProcPtr classProcPtr_;
	ClassThreadProcPtr classThreadProcPtr_;
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

	typedef void (*ProcPtr)(ParamType1 p1,ParamType2 p2,ParamType3 p3,ParamType4 p4, ParamType5 p5);
	typedef void (*ProcThreadPtr)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4, ParamType5 p5);	

	typedef void (ClassType::*ClassProcPtr)(ParamType1 p1,ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5);
	typedef void (ClassType::*ClassThreadProcPtr)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5);

	typedef ThreadedProcedure5<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType> BaseClass;

	ThreadedProcedure5( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ProcPtr procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5);

		params->procPtr_ = procPtr;

		internalParams_ = params;
	}

	ThreadedProcedure5( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4,ParamType5 p5,ProcThreadPtr procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5);

		params->procThreadPtr_ = procPtr;

		internalParams_ = params;
	}

	ThreadedProcedure5( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ProcThreadPtr procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedProcedure5( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ClassThreadProcPtr procPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
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


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}


protected:

	ThreadedProcedure5( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5 ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),param5_(p5),
			internalParams_(NULL),runningThread_(NULL),
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
	Runnable* internalParams_;
	Thread* runningThread_;
	ProcPtr procPtr_;
	ProcThreadPtr procThreadPtr_;
	ClassProcPtr classProcPtr_;
	ClassThreadProcPtr classThreadProcPtr_;
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

	typedef void (*ProcPtr)(ParamType1 p1,ParamType2 p2,ParamType3 p3,ParamType4 p4, ParamType5 p5, ParamType6 p6);
	typedef void (*ProcThreadPtr)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4, ParamType5 p5, ParamType6 p6);	

	typedef void (ClassType::*ClassProcPtr)(ParamType1 p1,ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6);
	typedef void (ClassType::*ClassThreadProcPtr)(Thread* thread, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6);

	typedef ThreadedProcedure6<ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType> BaseClass;

	ThreadedProcedure6( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6, ProcPtr procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),param6_(p6),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5,p6);

		params->procPtr_ = procPtr;

		internalParams_ = params;
	}

	ThreadedProcedure6( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4,ParamType5 p5,ParamType6 p6,ProcThreadPtr procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),param6_(p6),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5,p6);

		params->procThreadPtr_ = procPtr;

		internalParams_ = params;
	}

	ThreadedProcedure6( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6, ClassProcPtr procPtr ): param1_(p1), param2_(p2), param3_(p3), param4_(p4), param5_(p5),param6_(p6),
		internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5);

		params->classProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedProcedure6( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ClassThreadProcPtr procPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),param6_(p6),
			internalParams_(NULL),runningThread_(NULL),
			procPtr_(NULL),
			procThreadPtr_(NULL),
			classProcPtr_(NULL),
			classThreadProcPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5,p6);

		params->classThreadProcPtr_ = procPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
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


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}


protected:

	ThreadedProcedure6( ParamType1 p1, ParamType2 p2, ParamType3 p3, ParamType4 p4, ParamType5 p5, ParamType6 p6 ): param1_(p1), param2_(p2), param3_(p3), param4_(p4),param5_(p5),param6_(p6),
			internalParams_(NULL),runningThread_(NULL),
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
	Runnable* internalParams_;
	Thread* runningThread_;
	ProcPtr procPtr_;
	ProcThreadPtr procThreadPtr_;
	ClassProcPtr classProcPtr_;
	ClassThreadProcPtr classThreadProcPtr_;
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

	typedef ThreadedFunction<ReturnType,ClassType> BaseClass;

	typedef NullReturnClassType0<ReturnType> NullClassType;

	ThreadedFunction( FuncPtr funcPtr ): 
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(true);

		params->funcPtr_ = funcPtr;

		internalParams_ = params;
	}

	ThreadedFunction( FuncThreadPtr funcPtr ): 
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(true);

		params->classFuncPtr_ = funcPtr;

		internalParams_ = params;
	}



	ThreadedFunction( ClassType* src, ClassFuncPtr funcPtr ): 
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(true);

		params->classFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedFunction( ClassType* src, ClassThreadFuncPtr funcPtr ):
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(true);

		params->classThreadFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}
	
	virtual bool run() {	
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != threadFuncPtr_ ) {
				returnVal_ = (*threadFuncPtr_)( runningThread_ );
			}
			else if ( NULL != funcPtr_ ) {
				returnVal_ = (*funcPtr_)();
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classThreadFuncPtr_)( runningThread_ );
				}
				else if ( NULL != classFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classFuncPtr_)();
				}
				else {
					return false;
				}	
				
			}
		}
		return true;
	}

	virtual void stop(){}


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}

	ReturnType returnValue() {
		return returnVal_;
	}
protected:
	ThreadedFunction(bool):
			returnVal_(ReturnType()),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){
	}

	ReturnType returnVal_;
	Runnable* internalParams_;
	Thread* runningThread_;
	FuncPtr funcPtr_;
	FuncThreadPtr threadFuncPtr_;
	ClassFuncPtr classFuncPtr_;
	ClassThreadFuncPtr classThreadFuncPtr_;
	ClassType* instancePtr_;
};




template <typename ReturnType, 
		typename ParamType1>
class NullReturnClassType1 {
public:
	ReturnType m(ParamType1){ return ReturnType(); }
	ReturnType m(Thread*,ParamType1){ return ReturnType(); }
};

template <typename ReturnType, 
			typename ParamType1,
			typename ClassType=NullReturnClassType1<ReturnType,ParamType1> >
class ThreadedFunction1: public Runnable {
public:	
	typedef NullReturnClassType1<ReturnType,ParamType1> NullClassType;
	typedef ReturnType (*FuncPtr)(ParamType1);
	typedef ReturnType (*FuncThreadPtr)(Thread*,ParamType1);	

	typedef ReturnType (ClassType::*ClassFuncPtr)(ParamType1);
	typedef ReturnType (ClassType::*ClassThreadFuncPtr)( Thread*, ParamType1 );

	typedef ThreadedFunction1<ReturnType,ParamType1,ClassType> BaseClass;

	ThreadedFunction1( ParamType1 p1, FuncPtr funcPtr ): param1_(p1),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1);

		params->funcPtr_ = funcPtr;

		internalParams_ = params;
	}

	ThreadedFunction1( ParamType1 p1, FuncThreadPtr funcPtr ): param1_(p1),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1);

		params->classFuncPtr_ = funcPtr;

		internalParams_ = params;
	}



	ThreadedFunction1( ClassType* src, ParamType1 p1, ClassFuncPtr funcPtr ): param1_(p1),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1);

		params->classFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedFunction1( ClassType* src, ParamType1 p1, ClassThreadFuncPtr funcPtr ):param1_(p1),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1);

		params->classThreadFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}
	
	virtual bool run() {		
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != threadFuncPtr_ ) {
				returnVal_ = (*threadFuncPtr_)( runningThread_, param1_ );
			}
			else if ( NULL != funcPtr_ ) {
				returnVal_ = (*funcPtr_)( param1_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classThreadFuncPtr_)( runningThread_, param1_ );
				}
				else if ( NULL != classFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classFuncPtr_)( param1_ );
				}
				else {
					return false;
				}	
				
			}
		}
		return true;
	}

	virtual void stop(){}


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}

	ReturnType returnValue() {
		return returnVal_;
	}
protected:
	ThreadedFunction1(ParamType1 p1):returnVal_(ReturnType()),param1_(p1),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){
	}

	ReturnType returnVal_;
	ParamType1 param1_;

	Runnable* internalParams_;
	Thread* runningThread_;
	FuncPtr funcPtr_;
	FuncThreadPtr threadFuncPtr_;
	ClassFuncPtr classFuncPtr_;
	ClassThreadFuncPtr classThreadFuncPtr_;
	ClassType* instancePtr_;
};





template <typename ReturnType, 
		typename ParamType1,
		typename ParamType2>
class NullReturnClassType2 {
public:
	ReturnType m(ParamType1,ParamType2){ return ReturnType(); }
	ReturnType m(Thread*,ParamType1,ParamType2){ return ReturnType(); }
};

template <typename ReturnType, 
			typename ParamType1,
			typename ParamType2,
			typename ClassType=NullReturnClassType2<ReturnType,ParamType1,ParamType2> >
class ThreadedFunction2: public Runnable {
public:	
	typedef NullReturnClassType2<ReturnType,ParamType1,ParamType2> NullClassType;
	typedef ReturnType (*FuncPtr)(ParamType1,ParamType2);
	typedef ReturnType (*FuncThreadPtr)(Thread*,ParamType1,ParamType2);	

	typedef ReturnType (ClassType::*ClassFuncPtr)(ParamType1,ParamType2);
	typedef ReturnType (ClassType::*ClassThreadFuncPtr)( Thread*, ParamType1,ParamType2 );

	typedef ThreadedFunction2<ReturnType,ParamType1,ParamType2,ClassType> BaseClass;

	ThreadedFunction2( ParamType1 p1, ParamType2 p2, FuncPtr funcPtr ): param1_(p1),param2_(p2),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2);

		params->funcPtr_ = funcPtr;

		internalParams_ = params;
	}

	ThreadedFunction2( ParamType1 p1, ParamType2 p2, FuncThreadPtr funcPtr ): param1_(p1),param2_(p2),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2);

		params->classFuncPtr_ = funcPtr;

		internalParams_ = params;
	}



	ThreadedFunction2( ClassType* src, ParamType1 p1, ParamType2 p2, ClassFuncPtr funcPtr ): param1_(p1),param2_(p2),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2);

		params->classFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedFunction2( ClassType* src, ParamType1 p1, ParamType2 p2, ClassThreadFuncPtr funcPtr ):param1_(p1),param2_(p2),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2);

		params->classThreadFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}
	
	virtual bool run() {		
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != threadFuncPtr_ ) {
				returnVal_ = (*threadFuncPtr_)( runningThread_, param1_, param2_ );
			}
			else if ( NULL != funcPtr_ ) {
				returnVal_ = (*funcPtr_)( param1_, param2_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classThreadFuncPtr_)( runningThread_, param1_, param2_ );
				}
				else if ( NULL != classFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classFuncPtr_)( param1_, param2_ );
				}
				else {
					return false;
				}	
				
			}
		}
		return true;
	}

	virtual void stop(){}


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}

	ReturnType returnValue() {
		return returnVal_;
	}
protected:
	ThreadedFunction2(ParamType1 p1,ParamType2 p2):returnVal_(ReturnType()),param1_(p1),param2_(p2),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){
	}

	ReturnType returnVal_;
	ParamType1 param1_;
	ParamType2 param2_;

	Runnable* internalParams_;
	Thread* runningThread_;
	FuncPtr funcPtr_;
	FuncThreadPtr threadFuncPtr_;
	ClassFuncPtr classFuncPtr_;
	ClassThreadFuncPtr classThreadFuncPtr_;
	ClassType* instancePtr_;
};






template <typename ReturnType, 
		typename ParamType1,
		typename ParamType2,
		typename ParamType3>
class NullReturnClassType3 {
public:
	ReturnType m(ParamType1,ParamType2,ParamType3){ return ReturnType(); }
	ReturnType m(Thread*,ParamType1,ParamType2,ParamType3){ return ReturnType(); }
};

template <typename ReturnType, 
			typename ParamType1,
			typename ParamType2,
			typename ParamType3,
			typename ClassType=NullReturnClassType3<ReturnType,ParamType1,ParamType2,ParamType3> >
class ThreadedFunction3: public Runnable {
public:	
	typedef NullReturnClassType3<ReturnType,ParamType1,ParamType2,ParamType3> NullClassType;
	typedef ReturnType (*FuncPtr)(ParamType1,ParamType2,ParamType3);
	typedef ReturnType (*FuncThreadPtr)(Thread*,ParamType1,ParamType2,ParamType3);	

	typedef ReturnType (ClassType::*ClassFuncPtr)(ParamType1,ParamType2,ParamType3);
	typedef ReturnType (ClassType::*ClassThreadFuncPtr)( Thread*, ParamType1,ParamType2,ParamType3 );

	typedef ThreadedFunction3<ReturnType,ParamType1,ParamType2,ParamType3,ClassType> BaseClass;

	ThreadedFunction3( ParamType1 p1, ParamType2 p2, ParamType3 p3, FuncPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3);

		params->funcPtr_ = funcPtr;

		internalParams_ = params;
	}

	ThreadedFunction3( ParamType1 p1, ParamType2 p2, ParamType3 p3, FuncThreadPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3);

		params->classFuncPtr_ = funcPtr;

		internalParams_ = params;
	}



	ThreadedFunction3( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ClassFuncPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3);

		params->classFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedFunction3( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3, ClassThreadFuncPtr funcPtr ):param1_(p1),param2_(p2),param3_(p3),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3);

		params->classThreadFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}
	
	virtual bool run() {		
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != threadFuncPtr_ ) {
				returnVal_ = (*threadFuncPtr_)( runningThread_, param1_, param2_, param3_ );
			}
			else if ( NULL != funcPtr_ ) {
				returnVal_ = (*funcPtr_)( param1_, param2_, param3_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classThreadFuncPtr_)( runningThread_, param1_, param2_, param3_ );
				}
				else if ( NULL != classFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classFuncPtr_)( param1_, param2_, param3_ );
				}
				else {
					return false;
				}	
				
			}
		}
		return true;
	}

	virtual void stop(){}


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}

	ReturnType returnValue() {
		return returnVal_;
	}

protected:
	ThreadedFunction3(ParamType1 p1,ParamType2 p2,ParamType3 p3):returnVal_(ReturnType()),param1_(p1),param2_(p2),param3_(p3),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){
	}

	ReturnType returnVal_;
	ParamType1 param1_;
	ParamType2 param2_;
	ParamType3 param3_;

	Runnable* internalParams_;
	Thread* runningThread_;
	FuncPtr funcPtr_;
	FuncThreadPtr threadFuncPtr_;
	ClassFuncPtr classFuncPtr_;
	ClassThreadFuncPtr classThreadFuncPtr_;
	ClassType* instancePtr_;
};







template <typename ReturnType, 
		typename ParamType1,
		typename ParamType2,
		typename ParamType3,
		typename ParamType4>
class NullReturnClassType4 {
public:
	ReturnType m(ParamType1,ParamType2,ParamType3,ParamType4){ return ReturnType(); }
	ReturnType m(Thread*,ParamType1,ParamType2,ParamType3,ParamType4){ return ReturnType(); }
};

template <typename ReturnType, 
			typename ParamType1,
			typename ParamType2,
			typename ParamType3,
			typename ParamType4,
			typename ClassType=NullReturnClassType4<ReturnType,ParamType1,ParamType2,ParamType3,ParamType4> >
class ThreadedFunction4: public Runnable {
public:	
	typedef NullReturnClassType4<ReturnType,ParamType1,ParamType2,ParamType3,ParamType4> NullClassType;
	typedef ReturnType (*FuncPtr)(ParamType1,ParamType2,ParamType3,ParamType4);
	typedef ReturnType (*FuncThreadPtr)(Thread*,ParamType1,ParamType2,ParamType3,ParamType4);

	typedef ReturnType (ClassType::*ClassFuncPtr)(ParamType1,ParamType2,ParamType3,ParamType4);
	typedef ReturnType (ClassType::*ClassThreadFuncPtr)(Thread*,ParamType1,ParamType2,ParamType3,ParamType4);

	typedef ThreadedFunction4<ReturnType,ParamType1,ParamType2,ParamType3,ParamType4,ClassType> BaseClass;

	ThreadedFunction4( ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4, FuncPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4);

		params->funcPtr_ = funcPtr;

		internalParams_ = params;
	}

	ThreadedFunction4( ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4, FuncThreadPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4);

		params->classFuncPtr_ = funcPtr;

		internalParams_ = params;
	}



	ThreadedFunction4( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4, ClassFuncPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4);

		params->classFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedFunction4( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4, ClassThreadFuncPtr funcPtr ):param1_(p1),param2_(p2),param3_(p3),param4_(p4),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4);

		params->classThreadFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}
	
	virtual bool run() {		
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != threadFuncPtr_ ) {
				returnVal_ = (*threadFuncPtr_)( runningThread_, param1_, param2_, param3_, param4_ );
			}
			else if ( NULL != funcPtr_ ) {
				returnVal_ = (*funcPtr_)( param1_, param2_, param3_, param4_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classThreadFuncPtr_)( runningThread_, param1_, param2_, param3_, param4_ );
				}
				else if ( NULL != classFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classFuncPtr_)( param1_, param2_, param3_, param4_ );
				}
				else {
					return false;
				}	
				
			}
		}
		return true;
	}

	virtual void stop(){}


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}

	ReturnType returnValue() {
		return returnVal_;
	}

protected:
	ThreadedFunction4(ParamType1 p1,ParamType2 p2,ParamType3 p3,ParamType4 p4):returnVal_(ReturnType()),param1_(p1),param2_(p2),param3_(p3),param4_(p4),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){
	}

	ReturnType returnVal_;
	ParamType1 param1_;
	ParamType2 param2_;
	ParamType3 param3_;
	ParamType4 param4_;

	Runnable* internalParams_;
	Thread* runningThread_;
	FuncPtr funcPtr_;
	FuncThreadPtr threadFuncPtr_;
	ClassFuncPtr classFuncPtr_;
	ClassThreadFuncPtr classThreadFuncPtr_;
	ClassType* instancePtr_;
};








template <typename ReturnType, 
		typename ParamType1,
		typename ParamType2,
		typename ParamType3,
		typename ParamType4,
		typename ParamType5>
class NullReturnClassType5 {
public:
	ReturnType m(ParamType1,ParamType2,ParamType3,ParamType4,ParamType5){ return ReturnType(); }
	ReturnType m(Thread*,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5){ return ReturnType(); }
};

template <typename ReturnType, 
			typename ParamType1,
			typename ParamType2,
			typename ParamType3,
			typename ParamType4,
			typename ParamType5,
			typename ClassType=NullReturnClassType5<ReturnType,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5> >
class ThreadedFunction5: public Runnable {
public:	
	typedef NullReturnClassType5<ReturnType,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5> NullClassType;
	typedef ReturnType (*FuncPtr)(ParamType1,ParamType2,ParamType3,ParamType4,ParamType5);
	typedef ReturnType (*FuncThreadPtr)(Thread*,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5);

	typedef ReturnType (ClassType::*ClassFuncPtr)(ParamType1,ParamType2,ParamType3,ParamType4,ParamType5);
	typedef ReturnType (ClassType::*ClassThreadFuncPtr)(Thread*,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5);

	typedef ThreadedFunction5<ReturnType,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ClassType> BaseClass;

	ThreadedFunction5( ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4,ParamType5 p5, FuncPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5);

		params->funcPtr_ = funcPtr;

		internalParams_ = params;
	}

	ThreadedFunction5( ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4,ParamType5 p5, FuncThreadPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5);

		params->classFuncPtr_ = funcPtr;

		internalParams_ = params;
	}



	ThreadedFunction5( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4,ParamType5 p5, ClassFuncPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5);

		params->classFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedFunction5( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4,ParamType5 p5, ClassThreadFuncPtr funcPtr ):param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5);

		params->classThreadFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}
	
	virtual bool run() {		
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != threadFuncPtr_ ) {
				returnVal_ = (*threadFuncPtr_)( runningThread_, param1_, param2_, param3_, param4_, param5_ );
			}
			else if ( NULL != funcPtr_ ) {
				returnVal_ = (*funcPtr_)( param1_, param2_, param3_, param4_, param5_ );
			}
			else {
				return false;
			}			
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classThreadFuncPtr_)( runningThread_, param1_, param2_, param3_, param4_, param5_ );
				}
				else if ( NULL != classFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classFuncPtr_)( param1_, param2_, param3_, param4_, param5_ );
				}
				else {
					return false;
				}	
				
			}
		}
		return true;
	}

	virtual void stop(){}


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}

	ReturnType returnValue() {
		return returnVal_;
	}
protected:
	ThreadedFunction5(ParamType1 p1,ParamType2 p2,ParamType3 p3,ParamType4 p4,ParamType5 p5):returnVal_(ReturnType()),param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){
	}

	ReturnType returnVal_;
	ParamType1 param1_;
	ParamType2 param2_;
	ParamType3 param3_;
	ParamType4 param4_;
	ParamType5 param5_;

	Runnable* internalParams_;
	Thread* runningThread_;
	FuncPtr funcPtr_;
	FuncThreadPtr threadFuncPtr_;
	ClassFuncPtr classFuncPtr_;
	ClassThreadFuncPtr classThreadFuncPtr_;
	ClassType* instancePtr_;
};








template <typename ReturnType, 
		typename ParamType1,
		typename ParamType2,
		typename ParamType3,
		typename ParamType4,
		typename ParamType5,
		typename ParamType6>
class NullReturnClassType6 {
public:
	ReturnType m(ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6){ return ReturnType(); }
	ReturnType m(Thread*,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6){ return ReturnType(); }
};

template <typename ReturnType, 
			typename ParamType1,
			typename ParamType2,
			typename ParamType3,
			typename ParamType4,
			typename ParamType5,
			typename ParamType6,
			typename ClassType=NullReturnClassType6<ReturnType,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6> >
class ThreadedFunction6: public Runnable {
public:	
	typedef NullReturnClassType6<ReturnType,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6> NullClassType;
	typedef ReturnType (*FuncPtr)(ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6);
	typedef ReturnType (*FuncThreadPtr)(Thread*,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6);

	typedef ReturnType (ClassType::*ClassFuncPtr)(ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6);
	typedef ReturnType (ClassType::*ClassThreadFuncPtr)(Thread*,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6);

	typedef ThreadedFunction6<ReturnType,ParamType1,ParamType2,ParamType3,ParamType4,ParamType5,ParamType6,ClassType> BaseClass;

	ThreadedFunction6( ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4,ParamType5 p5,ParamType6 p6, FuncPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),param6_(p6),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5,p6);

		params->funcPtr_ = funcPtr;

		internalParams_ = params;
	}

	ThreadedFunction6( ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4,ParamType5 p5,ParamType6 p6, FuncThreadPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),param6_(p6),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5,p6);

		params->classFuncPtr_ = funcPtr;

		internalParams_ = params;
	}



	ThreadedFunction6( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4,ParamType5 p5,ParamType6 p6, ClassFuncPtr funcPtr ): param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),param6_(p6),
		internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL) {

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5,p6);

		params->classFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}


	ThreadedFunction6( ClassType* src, ParamType1 p1, ParamType2 p2, ParamType3 p3,ParamType4 p4,ParamType5 p5,ParamType6 p6, ClassThreadFuncPtr funcPtr ):param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),param6_(p6),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){

		BaseClass* params = 
			new BaseClass(p1,p2,p3,p4,p5,p6);

		params->classThreadFuncPtr_ = funcPtr;
		params->instancePtr_ = src;

		internalParams_ = params;
	}
	
	virtual bool run() {		
		if ( typeid(ClassType) == typeid(NullClassType) ) {
			if ( NULL != threadFuncPtr_ ) {
				returnVal_ = (*threadFuncPtr_)( runningThread_, param1_, param2_, param3_, param4_, param5_, param6_ );
			}
			else if ( NULL != funcPtr_ ) {
				returnVal_ = (*funcPtr_)( param1_, param2_, param3_, param4_, param5_, param6_ );
			}
			else {
				return false;
			}
		}
		else {
			if ( NULL != instancePtr_ ) {
				if ( NULL != classThreadFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classThreadFuncPtr_)( runningThread_, param1_, param2_, param3_, param4_, param5_, param6_ );
				}
				else if ( NULL != classFuncPtr_ ) {
					returnVal_ = (instancePtr_->*classFuncPtr_)( param1_, param2_, param3_, param4_, param5_, param6_ );
				}
				else {
					return false;
				}	
				
			}
		}
		return true;
	}

	virtual void stop(){}


	Runnable* getParams() {
		return internalParams_;
	}

	Thread* invoke() {
		if ( NULL == runningThread_ ) {
			runningThread_ = new Thread( internalParams_, true, true );
			BaseClass* params = (BaseClass*)internalParams_;
			params->runningThread_ = runningThread_;

			runningThread_->start();
		}
		return runningThread_;
	}

	ReturnType returnValue() {
		return returnVal_;
	}

protected:
	ThreadedFunction6(ParamType1 p1,ParamType2 p2,ParamType3 p3,ParamType4 p4,ParamType5 p5,ParamType6 p6):returnVal_(ReturnType()),param1_(p1),param2_(p2),param3_(p3),param4_(p4),param5_(p5),param6_(p6),
			internalParams_(NULL),runningThread_(NULL),
			funcPtr_(NULL),
			threadFuncPtr_(NULL),
			classFuncPtr_(NULL),
			classThreadFuncPtr_(NULL),
			instancePtr_(NULL){
	}

	ReturnType returnVal_;
	ParamType1 param1_;
	ParamType2 param2_;
	ParamType3 param3_;
	ParamType4 param4_;
	ParamType5 param5_;
	ParamType6 param6_;

	Runnable* internalParams_;
	Thread* runningThread_;
	FuncPtr funcPtr_;
	FuncThreadPtr threadFuncPtr_;
	ClassFuncPtr classFuncPtr_;
	ClassThreadFuncPtr classThreadFuncPtr_;
	ClassType* instancePtr_;
};






};//namespace VCF

#endif //_VCF_THREADED_FUNCTIONS_H__

