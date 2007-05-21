#ifndef _DELEGATES_H__
#define _DELEGATES_H__



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


template <typename P1>
class Procedure1 : public CallBack {
public:

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

	FuncPtr staticFuncPtr;
};


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

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
};





template <typename P1>
class Delagate1 : public delegate {
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

	ClassFuncPtr classFuncPtr;
	ClassType* funcSrc;
};


template <typename ReturnType, typename P1, typename P2>
class Delagate2R : public delegate {
public:
	typedef Function2<ReturnType,P1,P2> CallbackType;
	typedef _typename_ CallbackType::FuncPtr FuncPtr;

	typedef std::vector<ReturnType> Results;

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


	Results results;
};


}; //namespace VCF

#endif //_DELEGATES_H__

