//JavaScriptKit.cpp

/*
Copyright 2000-2004 The VCF Builder Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "JavaScriptKit.h"


using namespace VCF;


void JavaScriptKit::init( int argc, char **argv )
{
	JavaScriptEngine::initialize();
}

void JavaScriptKit::terminate()
{
	JavaScriptEngine::terminate();
}


String convertClassNameToJSClassName( const String& className ) 
{
	String result = className;

	int pos = result.find( "::" );
	if ( pos != String.npos ) {
		String namespaceStr = result.substr( 0, pos );
		if ( namespaceStr == "VCF" ) {
			result.erase( 0, pos+1 );
		}
	}

	pos = result.find( ':' );
	while ( pos != String::npos ) {
		result.erase( pos, 1 );
		pos = result.find( ':' );
	}

	return result;
}

JavaScriptEngine* JavaScriptEngine::singleton = NULL;

JavaScriptEngine::JavaScriptEngine():
	m_runTime(NULL),
	m_context(NULL),
	m_global(NULL),
	m_globalClass(NULL)
{
		
	m_globalClass = (JSClass*)malloc(sizeof(JSClass));
	memset( m_globalClass, 0, sizeof(JSClass) );

	m_globalClass->name = "global";
	m_globalClass->flags = 0;
	m_globalClass->addProperty = JS_PropertyStub;
	m_globalClass->delProperty = JS_PropertyStub;
	m_globalClass->getProperty = JS_PropertyStub;
	m_globalClass->setProperty = JS_PropertyStub;
	m_globalClass->enumerate = JS_EnumerateStub;
	m_globalClass->resolve = JS_ResolveStub;
	m_globalClass->convert = JS_ConvertStub;
	m_globalClass->finalize = JS_FinalizeStub;

	/* initialize the JS run time, and return result in rt */
	m_runTime = JS_NewRuntime(0x100000);
	
	/* if rt does not have a value, end the program here */
	if (NULL == m_runTime) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "JavaScript runtime is NULL - could not be allocated" ) );
	}

	/* establish a context */
	m_context = JS_NewContext(m_runTime, 0x1000);
	
	/* if cx does not have a value, end the program here */
	if (m_context == NULL) {
		throw RuntimeException( MAKE_ERROR_MSG_2( "JavaScript context is NULL - could not be allocated by runtime engine" ) );
	}	
	
	/* initialize the built-in JS objects and the global object */
	m_global = JS_NewObject(m_context, m_globalClass, NULL, NULL); 
    
	int builtins = JS_InitStandardClasses(m_context, m_global);

	


	JS_SetErrorReporter( m_context, JavaScriptEngine::rawErrorReporter );

	JavaScriptEngine::singleton = this;
}


JavaScriptEngine::~JavaScriptEngine()
{
	JS_DestroyContext(m_context);

	/* Before exiting the application, free the JS run time */
	JS_DestroyRuntime(m_runTime);

	std::map<String,ClassEntry>::iterator it = m_jsClassMap.begin();
	while ( it != m_jsClassMap.end() ) {
		ClassEntry& ce = it->second;
		::free( ce.m_jsClass );

		if ( ce.m_propCount ) {
			::free( ce.m_props );
		}

		if ( ce.m_methodCount ) {
			::free( ce.m_methods );
		}
		
		it ++;
	}

	std::vector<char*>::iterator it2 = names_.begin();
	while ( it2 != names_.end() ) {
		delete [] *it2;
		it2 ++;
	}
	::free(m_globalClass);

	::free( globalDelegateClass_ );


	EventHandlerMap::iterator it3 = jsEventHandlers_.begin();
	while ( it3 != jsEventHandlers_.end() ) {
		it3->second->free();
		it3 ++;
	}
}

void JavaScriptEngine::initVCFGlobalClasses()
{
	globalDelegateClass_ = (JSClass*)malloc( sizeof(JSClass) );
	memset( globalDelegateClass_, 0 , sizeof(JSClass) );

	char* className = new char[255];

	memset(className,0,255);
	String tmp = "Delegate";
	tmp.copy( className, tmp.size() );
	globalDelegateClass_->name = className;
	names_.push_back( className );

	globalDelegateClass_->flags = JSCLASS_HAS_PRIVATE;
	globalDelegateClass_->addProperty =	JS_PropertyStub;
	globalDelegateClass_->delProperty =	JS_PropertyStub;
	globalDelegateClass_->enumerate =	JS_EnumerateStub;
	globalDelegateClass_->resolve =		JavaScriptEngine::resolve;
	globalDelegateClass_->convert =		JS_ConvertStub;
	globalDelegateClass_->finalize =	JavaScriptEngine::finalize;
	globalDelegateClass_->getProperty =	JavaScriptEngine::getObjProperty;
	globalDelegateClass_->setProperty =	JavaScriptEngine::setObjProperty;
	
	
	JSPropertySpec* jsClassProperties = (JSPropertySpec*)malloc(sizeof(JSPropertySpec) * 1);
	memset( jsClassProperties, 0, sizeof(JSPropertySpec) * 1 );
	
	JSFunctionSpec* jsClassMethods = (JSFunctionSpec*)malloc( sizeof(JSFunctionSpec) * 1 );
	memset( jsClassMethods, 0, sizeof(JSFunctionSpec) * 1 );

	JS_InitClass(m_context,     // context
							m_global,        // global object
							NULL,  // parent proto 
							globalDelegateClass_,      // JSClass
							JavaScriptEngine::constructor,            // JSNative ctor
							0,             // ctor args
							jsClassProperties,  // proto props
							jsClassMethods,     // proto funcs
							NULL,        // ctor props (static)
							NULL);    





	globalEventClass_.m_jsClass = (JSClass*)malloc( sizeof(JSClass) );
	memset( globalEventClass_.m_jsClass, 0 , sizeof(JSClass) );

	className = new char[255];
	memset(className,0,255);
	tmp = "VCFEvent";
	tmp.copy( className, tmp.size() );
	globalEventClass_.m_jsClass->name = className;
	names_.push_back( className );

	globalEventClass_.m_jsClass->flags = JSCLASS_HAS_PRIVATE;
	globalEventClass_.m_jsClass->addProperty =	JS_PropertyStub;
	globalEventClass_.m_jsClass->delProperty =	JS_PropertyStub;
	globalEventClass_.m_jsClass->enumerate =	JS_EnumerateStub;
	globalEventClass_.m_jsClass->resolve =		JS_ResolveStub;
	globalEventClass_.m_jsClass->convert =		JS_ConvertStub;
	globalEventClass_.m_jsClass->finalize =	JS_FinalizeStub;
	globalEventClass_.m_jsClass->getProperty =	JavaScriptEngine::getObjProperty;
	globalEventClass_.m_jsClass->setProperty =	JS_PropertyStub; //event's are read only for now

	//source,time,type,
	
	globalEventClass_.m_propCount = 4;
	globalEventClass_.m_props = (JSPropertySpec*)malloc(sizeof(JSPropertySpec) * globalEventClass_.m_propCount);
	memset( globalEventClass_.m_props, 0, sizeof(JSPropertySpec) * globalEventClass_.m_propCount );

	for (int i=0;i<globalEventClass_.m_propCount-1;i++) {
		char* propName = new char[255];
		memset(propName,0,255);

		switch( i ) {
			case 0 : {
				tmp = "source";
			}
			break;

			case 1 : {
				tmp = "time";
			}
			break;

			case 2 : {
				tmp = "type";
			}
			break;
		}

		
		tmp.copy( propName, tmp.size() );
		names_.push_back( propName );
		
		globalEventClass_.m_props[i].name = propName;
		globalEventClass_.m_props[i].tinyid = i;
	}
	globalEventClass_.m_methodCount = 1;
	globalEventClass_.m_methods = (JSFunctionSpec*)malloc( sizeof(JSFunctionSpec) * globalEventClass_.m_methodCount );
	memset( globalEventClass_.m_methods, 0, sizeof(JSFunctionSpec) * globalEventClass_.m_methodCount );

	JS_InitClass(m_context,     // context
							m_global,        // global object
							NULL,  // parent proto 
							globalEventClass_.m_jsClass,      // JSClass
							JavaScriptEngine::constructor,            // JSNative ctor
							0,             // ctor args
							globalEventClass_.m_props,  // proto props
							globalEventClass_.m_methods,     // proto funcs
							NULL,        // ctor props (static)
							NULL);    
}

void JavaScriptEngine::updateFromClassRegistry()
{
	
	std::vector<char*>::iterator it = names_.begin();
	while ( it != names_.end() ) {
		delete [] *it;
		it ++;
	}
	names_.clear();
	

	initVCFGlobalClasses();

	Enumerator<Class*>* classes = ClassRegistry::getClasses();
	while ( classes->hasMoreElements() ) {
		Class* clazz = classes->nextElement();

		JSClass* jsClassToReg = (JSClass*)malloc( sizeof(JSClass) );//{0};
		memset( jsClassToReg, 0 , sizeof(JSClass) );

		//this c_str() assignment below works only because
		//the std::string class is ref counted - if a different
		//string class were to be used this would have to looked at		

		char* className = new char[255];
		memset(className,0,255);
		String tmp = convertClassNameToJSClassName( clazz->getClassName() );
		tmp.copy( className, tmp.size() );

		jsClassToReg->name = className;
		names_.push_back( className );


		jsClassToReg->flags = JSCLASS_HAS_PRIVATE;

		jsClassToReg->addProperty =	JS_PropertyStub;
		jsClassToReg->delProperty =	JS_PropertyStub;
		jsClassToReg->getProperty =	JavaScriptEngine::getObjProperty;
		jsClassToReg->setProperty =	JavaScriptEngine::setObjProperty;

		jsClassToReg->enumerate =	JavaScriptEngine::enumerate;
		jsClassToReg->resolve =		JavaScriptEngine::resolve;
		jsClassToReg->convert =		JS_ConvertStub;
		jsClassToReg->finalize =	JavaScriptEngine::finalize;


		JSObject *proto = NULL;

		
		ulong pc = clazz->getPropertyCount() + 1;

		int eventCount = 0;
		Enumerator<EventProperty*>* events = clazz->getEvents();
		while ( events->hasMoreElements() ) {
			EventProperty* event = events->nextElement();
			if ( !event->isAbstract() ) {
				eventCount++;
			}
		}
		events->reset();

		pc += eventCount;


		ulong mc = clazz->getMethodCount() + 1;

		JSPropertySpec* jsClassProperties = (JSPropertySpec*)malloc(sizeof(JSPropertySpec) * pc);
		memset( jsClassProperties, 0, sizeof(JSPropertySpec) * pc );

		JSFunctionSpec* jsClassMethods = (JSFunctionSpec*)malloc( sizeof(JSFunctionSpec) * mc );

		memset( jsClassMethods, 0, sizeof(JSFunctionSpec) * mc );

		Enumerator<Property*>* props = clazz->getProperties();
		int i = 0;
		while ( props->hasMoreElements() ) {
			Property* prop = props->nextElement();
			tmp = prop->getName();
			char* propName = new char[255];
			memset(propName,0,255);
			tmp.copy( propName, tmp.size() );
			names_.push_back( propName );

			jsClassProperties[i].name = propName;
			jsClassProperties[i].tinyid = i;			

			i++;
		}

		i = 0;
		Enumerator<Method*>* methods = clazz->getMethods();
		while (	methods->hasMoreElements() ) {
			Method* method = methods->nextElement();
			tmp = method->getName();
			char* methodName = new char[255];
			memset(methodName,0,255);
			tmp.copy( methodName, tmp.size() );
			names_.push_back( methodName );

			jsClassMethods[i].name = methodName;
			jsClassMethods[i].nargs = method->getArgCount();			
			jsClassMethods[i].call = JavaScriptEngine::methodCall;
			i++;
		}		

		//set i to the last property index
		//then add teh events as properties
		//we'll treat each event as a property
		i = clazz->getPropertyCount();
		while ( events->hasMoreElements() ) {
			EventProperty* event = events->nextElement();
			if ( !event->isAbstract() ) {
				
				tmp = event->getDelegateName();
				char* delegateName = new char[255];
				memset(delegateName,0,255);
				tmp.copy( delegateName, tmp.size() );
				names_.push_back( delegateName );

				jsClassProperties[i].name = delegateName;

				jsClassProperties[i].tinyid = i;
				i++;
			}
		}



		JSClass * tmpClass =  JS_GetClass(m_global);

		ClassEntry entry(clazz, jsClassToReg, jsClassProperties, pc, jsClassMethods, mc );

		proto = JS_InitClass(m_context,     // context
							m_global,        // global object
							NULL,  // parent proto 
							jsClassToReg,      // JSClass
							JavaScriptEngine::constructor,            // JSNative ctor
							0,             // ctor args
							entry.m_props,  // proto props
							entry.m_methods,     // proto funcs
							NULL,        // ctor props (static)
							NULL);    


		m_jsClassMap[String(jsClassToReg->name)] = entry;
		

		tmpClass =  JS_GetClass(proto);
	}
}

void JavaScriptEngine::executeScript( const String& script, const String& fileName )
{
	String version = JS_GetImplementationVersion();

	JavaScriptEvent event(this, 0, "JavaScript engine version: " + version );

	ScriptExecuting.fireEvent( &event );

	jsval rval; 
	int lineno = 0;
	AnsiString ansiScript = script;
	JS_EvaluateScript(m_context, m_global, ansiScript.c_str(), ansiScript.size(), 
						fileName.empty() ? NULL : fileName.ansi_c_str(), 
						lineno, 
						&rval); 	
	
}


JSBool JavaScriptEngine::methodCall(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval)
{
	JSBool result = JS_FALSE;
	JSFunction* fun = cx->fp->fun;
	const char* funcName = JS_GetFunctionName( fun );//->atom 


	//StringUtils::trace( Format( "JavaScriptEngine::methodCall()\n\tobj: %p\n\t funcName: %s\n\targc: %d\n" ) % obj % funcName % argc );

	JSClass* clazz = JS_GetClass( obj );

	String className = clazz->name;	

	JavaScriptEngine* eng = &JavaScriptEngine::engine();
	InstanceMap::iterator found2 = eng->m_jsObjectInstances.find( obj );

	std::map<String,JavaScriptEngine::ClassEntry>::iterator found = eng->m_jsClassMap.find( className );
	if ( (found != eng->m_jsClassMap.end()) && (found2 != eng->m_jsObjectInstances.end()) ) {
		JavaScriptEngine::ClassEntry& ce = found->second;

		JavaScriptEngine::ObjectInstanceEntry& ie = found2->second;

		Method* method = ce.m_vcfClass->getMethod( String(funcName) );
		if ( NULL != method ) {
			
			if ( method->getArgCount() == argc ) {
				VariantData** args = NULL;
				if ( argc > 0 ) {
					args = new VariantData*[argc];

					for (int i=0;i<argc;i++ ) {
						args[i] = new VariantData();
						eng->assignJSValToVariant( &argv[i], args[i] );
					}
				}

				VariantData* retVal = NULL;
				try {
					retVal = method->invoke( args, ie.instance_ );
					result = JS_TRUE;
				}
				catch ( BasicException& e ) {
					retVal = NULL;
					result = JS_FALSE;

					JS_ReportError( eng->m_context, "VCF Exception thrown: %s", e.getMessage().c_str() );
				}
				
				eng->assignVariantToJSVal( retVal, rval );
				

				for (int i=0;i<argc;i++ ) {
					delete args[i];
				}
				delete [] args;
			}
		}
	}

	return result;
}

JSBool JavaScriptEngine::getObjProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
	String className;
	JSClass* clazz = JS_GetClass( obj );

	className = clazz->name;
	

	JavaScriptEngine* eng = &JavaScriptEngine::engine();
	InstanceMap::iterator found2 = eng->m_jsObjectInstances.find( obj );

	std::map<String,JavaScriptEngine::ClassEntry>::iterator found = eng->m_jsClassMap.find( className );
	if ( (found != eng->m_jsClassMap.end()) && (found2 != eng->m_jsObjectInstances.end()) ) {
		JavaScriptEngine::ClassEntry& ce = found->second;
		JavaScriptEngine::ObjectInstanceEntry& ie = found2->second;
		
		if ( (JSVAL_IS_INT(id)) && (ce.m_propCount > 0) ) {
			int i = JSVAL_TO_INT(id);
			
			Property* prop = ce.m_vcfClass->getProperty( String(ce.m_props[i].name) );
			if ( NULL != prop ) {
				
				prop->setSource( ie.instance_ );

				VariantData* val = prop->get();

				eng->assignVariantToJSVal( val, vp );
				
			}
			else {
				//try and get and event
				EventProperty* eventProp = ce.m_vcfClass->getEvent( String(ce.m_props[i].name) );

				//check to see if our value is actually a Function!
				
				if ( NULL != eventProp ) {
					if ( !eventProp->isAbstract() ) {
						eventProp->setSource( ie.instance_ );
						Delegate* delegateSrc = eventProp->getEventDelegate();
						if ( NULL != delegateSrc ) {

							//create a new object for hte delegate and map it to our instance
							//of the delegate
							//JSObject* obj = JS_NewObject( JavaScriptEngine::engine().m_context, 
							//								JavaScriptEngine::engine().globalDelegateClass_, 
							//								NULL, NULL );
							//JavaScriptEngine::engine().jsDelegateInstances_[obj] = delegateSrc;
							//*vp = OBJECT_TO_JSVAL(obj);
						}
					}
				}
			}
		}	
	}
	else if ( className == "VCFEvent" ){
		if ( JSVAL_IS_INT(id) ) {
			int i = JSVAL_TO_INT(id);
			Event* e = (Event*)JS_GetPrivate( cx, obj );

			String name = eng->globalEventClass_.m_props[i].name;
			VariantData vd;
			if ( name == "source" ) {
				vd = e->getSource();
			}
			else if ( name == "time" ) {
				vd = (VCF::ulong)e->getTime();
			}
			else if ( name == "type" ) {
				vd = e->getType();
			}

			eng->assignVariantToJSVal( &vd, vp );
		}
	}
	
	return JS_TRUE;
}

bool JavaScriptEngine::assignVariantToJSVal( VariantData* vd, jsval* vp )
{
	bool result = true;

	if ( NULL == vd ) {
		return false;
	}
	
	switch ( vd->type ) {
		case pdInt:{
			JS_NewNumberValue( JavaScriptEngine::engine().m_context, 0, vp);
			int i = *vd;
			*vp = INT_TO_JSVAL(i);
		}
		break;

		case pdLong:{
			JS_NewNumberValue( JavaScriptEngine::engine().m_context, 0, vp);
			long i = (long)*vd;
			*vp = INT_TO_JSVAL(i);
		}
		break;

		case pdShort:{
			JS_NewNumberValue( JavaScriptEngine::engine().m_context, 0, vp);
			int i = (short)*vd;
			*vp = INT_TO_JSVAL(i);
		}
		break;

		case pdULong:{
			JS_NewNumberValue( JavaScriptEngine::engine().m_context, 0, vp);
			int i = (unsigned long)*vd;
			*vp = INT_TO_JSVAL(i);
		}
		break;

		case pdFloat:{
			JS_NewNumberValue( JavaScriptEngine::engine().m_context, 0, vp);
			double i = (float)*vd;
			*vp = DOUBLE_TO_JSVAL(i);
		}
		break;

		case pdChar:{
			JS_NewNumberValue( JavaScriptEngine::engine().m_context, 0, vp);
			int i = (char)*vd;
			*vp = INT_TO_JSVAL(i);
		}
		break;

		case pdDouble:{
			JS_NewNumberValue( JavaScriptEngine::engine().m_context, 0, vp);
			double i = *vd;
			*vp = DOUBLE_TO_JSVAL(i);
		}
		break;

		case pdBool:{
			JS_NewNumberValue( JavaScriptEngine::engine().m_context, 0, vp);
			bool i = *vd;		
			*vp = i ? BOOLEAN_TO_JSVAL(true) : BOOLEAN_TO_JSVAL(false);
		}
		break;

		case pdObject:{				
			Object* object = *vd;
			if ( NULL != object ){
				Class* clazz = object->getClass();
				String className = convertClassNameToJSClassName( clazz->getClassName() );

				std::map<String,JavaScriptEngine::ClassEntry>::iterator found = JavaScriptEngine::engine().m_jsClassMap.find( className );
				if ( found != JavaScriptEngine::engine().m_jsClassMap.end() ) {
					ClassEntry& entry = found->second;

					JSObject* obj = JS_NewObject( JavaScriptEngine::engine().m_context, 
												entry.m_jsClass, NULL, NULL );

					ObjectInstanceEntry ie;
					ie.instance_ = object;
					ie.releasable_ = false;
					JavaScriptEngine::engine().m_jsObjectInstances[obj] = ie;
					*vp = OBJECT_TO_JSVAL(obj);
				}
			}
			else{
				//throw exception
			}
		}
		break;
		
		case pdString:{
			String s = *vd;
			AnsiString tmp = s;
			JSString* jsString = JS_NewStringCopyN( JavaScriptEngine::engine().m_context, 
											tmp.c_str(), tmp.size() );
			*vp = STRING_TO_JSVAL(jsString);
			
		}
		break;		
	}

	

	return result;
}

bool JavaScriptEngine::assignJSValToVariant( jsval* vp, VariantData* vd )
{
	bool result = false;
	if ( JSVAL_IS_PRIMITIVE(*vp) ) {
		if ( JSVAL_IS_BOOLEAN(*vp) ) {
			JSBool boolVal = 0.0;
			JSBool res = JS_ValueToBoolean( m_context, *vp, &boolVal );
			if ( res ) {
				*vd = (boolVal) ? true : false;	
				result = true;
			}
		}
		else if ( JSVAL_IS_DOUBLE(*vp) ) {
			jsdouble dbl = 0.0;
			JSBool res = JS_ValueToNumber( m_context, *vp, &dbl );
			if ( res ) {
				*vd = (double)dbl;	
				result = true;
			}
		}
		else if ( JSVAL_IS_INT(*vp) ) {
			long i32 = 0;
			JSBool res = JS_ValueToInt32( m_context, *vp, &i32 );
			if ( res ) {
				*vd = i32;	
				result = true;
			}
		}
		else if ( JSVAL_IS_STRING(*vp) ) {
			JSString* s = JS_ValueToString( m_context, *vp );
			const char* bytes = JS_GetStringBytes(s);
			*vd = String(bytes);
			result = true;
		}		
		else { //its a JSOBJECT!
		
		}
	}

	return result;
}



class JSEngineEventHandler : public EventHandler {
public:
	JSEngineEventHandler(): function_(NULL) {

	}

	virtual void invoke( Event* e ) {
		JavaScriptEngine::invokeEventhandler( e, function_, functionName_ );		
	}

	JSFunction* function_;
	String functionName_;
};

void JavaScriptEngine::invokeEventhandler( Event* e, JSFunction* function, const VCF::String& functionName )
{
	JavaScriptEngine* eng = &JavaScriptEngine::engine();
	
	JSObject* obj =  eng->newObjectFromVCFEvent( e );
	jsval returnVal;
	jsval arg[1];

	arg[0] = OBJECT_TO_JSVAL(obj);
	
	
	if ( NULL != function ) {
		JS_CallFunction( eng->m_context, 
			JS_GetFunctionObject(function), 
			function,
			1,
			&arg[0],
			&returnVal );
		
		
	}
	else {
		JS_CallFunctionName( eng->m_context, 
			eng->m_context->globalObject, 
			functionName.ansi_c_str(),
			1,
			&arg[0],
			&returnVal );
	}
}

JSObject* JavaScriptEngine::newObjectFromVCFEvent( VCF::Event* e )
{
	JSObject* result = NULL;

	result = JS_NewObject( JavaScriptEngine::engine().m_context, 
												JavaScriptEngine::engine().globalEventClass_.m_jsClass, 
												NULL, NULL );

	JS_SetPrivate( JavaScriptEngine::engine().m_context, result, (void*)e );

	return result;
}

JSBool JavaScriptEngine::setObjProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp)
{
	String className;
	JSClass* clazz = JS_GetClass( obj );

	className = clazz->name;	

	JavaScriptEngine* eng = &JavaScriptEngine::engine();
	InstanceMap::iterator found2 = eng->m_jsObjectInstances.find( obj );

	std::map<String,JavaScriptEngine::ClassEntry>::iterator found = eng->m_jsClassMap.find( className );
	if ( (found != eng->m_jsClassMap.end()) && (found2 != eng->m_jsObjectInstances.end()) ) {
		JavaScriptEngine::ClassEntry& ce = found->second;
		JavaScriptEngine::ObjectInstanceEntry& ie = found2->second;

		if ( (JSVAL_IS_INT(id)) && (ce.m_propCount > 0) ) {
			int i = JSVAL_TO_INT(id);
			
			Property* prop = ce.m_vcfClass->getProperty( String(ce.m_props[i].name) );
			if ( NULL != prop ) {
				
				prop->setSource( ie.instance_ );

				VariantData val;
				if ( eng->assignJSValToVariant( vp, &val ) ) {
					prop->set( &val );
				}								
			}
			else {
				EventProperty* eventProp = ce.m_vcfClass->getEvent( String(ce.m_props[i].name) );
				if ( NULL != eventProp ) {
					if ( !eventProp->isAbstract() ) {
						eventProp->setSource( ie.instance_ );
						Delegate* delegateSrc = eventProp->getEventDelegate();
						if ( NULL != delegateSrc ) {

							String name = Format( "%sEventHandler" ) % eventProp->getDelegateName();

							JSEngineEventHandler* eventHandler = new JSEngineEventHandler();
							


							//check to see if our value is actually a String!
							JSType type = JS_TypeOfValue( cx, *vp );
							if ( JSTYPE_FUNCTION == type ) {					
								
								//add event handler for function name
								eventHandler->function_ = JS_ValueToFunction( cx, *vp );
								
							}
							else if ( JSTYPE_STRING == type ) {					
								JSString* s = JS_ValueToString( cx, *vp );
								const char* bytes = JS_GetStringBytes(s);
								eventHandler->functionName_ = String(bytes);

								//add event handler for function name
								
								
							}

							delegateSrc->addHandler( eventHandler );

							EventHandlerMap::value_type val(delegateSrc,eventHandler);
							eng->jsEventHandlers_.insert( val );
						}
					}
				}
			}			
		}
	}
	return JS_TRUE;
}

JSBool JavaScriptEngine::enumerate(JSContext *cx, JSObject *obj)
{
	
	return JS_TRUE;
}

JSBool JavaScriptEngine::resolve(JSContext *cx, JSObject *obj, jsval id)
{
	
	String className;
	JSClass* clazz = JS_GetClass( obj );

	className = clazz->name;

	JavaScriptEngine* eng = &JavaScriptEngine::engine();

	InstanceMap::iterator found = eng->m_jsObjectInstances.find(obj);
	if ( found != eng->m_jsObjectInstances.end() ) {
		Object* vcfObj = found->second.instance_;
		if ( found->second.releasable_ ) {
			ulong res = vcfObj->addRef();
			StringUtils::trace( Format( "refcount: %d Object::toString(): %s\n" ) % res % vcfObj->toString() );
		}		
	}
	
	return JS_TRUE;
}

JSBool JavaScriptEngine::constructor(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) 
{
	String className;
	JSClass* clazz = JS_GetClass( obj );

	className = clazz->name;	

	JavaScriptEngine* eng = &JavaScriptEngine::engine();
	std::map<String,JavaScriptEngine::ClassEntry>::iterator found = eng->m_jsClassMap.find( className );
	if ( found != eng->m_jsClassMap.end() ) {
		StringUtils::trace( Format( "JavaScriptEngine::constructor for class: %s, argcount: %d\n\tcx->lastMessage: %s\n\tobj: %p\n" ) % 
													className % argc % cx->lastMessage % obj );	

		JavaScriptEngine::ClassEntry& ce = found->second;
		Object* vcfObj = NULL;
		vcfObj = ce.m_vcfClass->createInstance();

		if ( NULL != obj ) {
			ObjectInstanceEntry entry;
			entry.instance_ = vcfObj;

			eng->m_jsObjectInstances[obj] = entry;
		}
	}

	

	//m_jsObjectInstances

	return JS_TRUE;
}

void JavaScriptEngine::finalize(JSContext *cx, JSObject *obj)
{	
	JavaScriptEngine* eng = &JavaScriptEngine::engine();

	String className;
	JSClass* clazz = JS_GetClass( obj );

	className = clazz->name;	

	std::map<JSObject*,ObjectInstanceEntry>::iterator found = eng->m_jsObjectInstances.find(obj);
	if ( found != eng->m_jsObjectInstances.end() ) {
		//StringUtils::trace( Format( "JavaScriptEngine::finalize\n\tcx->lastMessage: %s\n\tobj: %p\n" ) % cx->lastMessage % obj );	

		ObjectInstanceEntry& entry = found->second;
		Object* vcfObj = entry.instance_;

		//check if we have to trash any event handlers
		Class* clazz = vcfObj->getClass();
		Enumerator<EventProperty*>* events = clazz->getEvents();
		while ( events->hasMoreElements() ) {
			EventProperty* e = events->nextElement();
			
			Delegate* delegate = e->getEventDelegate(vcfObj);

			EventHandlerMapRange range = eng->jsEventHandlers_.equal_range( delegate );
			EventHandlerMap::iterator it = range.first;
			while ( it != range.second ) {
				delegate->removeHandler( it->second );
				it ++;
			}
		}

		if ( entry.releasable_ ) {

			ulong res = vcfObj->release();
			if ( res ) {
				StringUtils::trace( Format( "refcount: %d Object::toString(): %s\n" ) % res % vcfObj->toString() );
			}
			else {
				eng->m_jsObjectInstances.erase( found );
				StringUtils::trace( Format( "Object %p freed and removed from map!\n" ) % vcfObj );
			}
		}		
	}
	else {
		JS_FinalizeStub( cx, obj );
	}
}


void JavaScriptEngine::initialize()
{
	JavaScriptEngine::singleton = new JavaScriptEngine();
}

void JavaScriptEngine::terminate()
{
	if ( NULL != JavaScriptEngine::singleton ) {
		JavaScriptEngine::singleton->free();
	}
}

void JavaScriptEngine::defineGlobalObject( Object* object )
{
	Class* clazz = object->getClass();
	if ( NULL != clazz ) {
		String className = convertClassNameToJSClassName( clazz->getClassName() );
		
		std::map<String,JavaScriptEngine::ClassEntry>::iterator found = m_jsClassMap.find( className );
		if ( found != m_jsClassMap.end() ) {
			JavaScriptEngine::ClassEntry& ce = found->second;

			JSObject* result = JS_DefineObject( m_context, m_global, className.ansi_c_str(), ce.m_jsClass, 0, 0 );

			ObjectInstanceEntry entry;
			entry.instance_ = object;
			entry.releasable_ = false;

			m_jsObjectInstances[result] = entry;
		}
	}
}

void JavaScriptEngine::rawErrorReporter(JSContext* cx, const char* message, JSErrorReport* report )
{
	String errMessage = Format( "JavaScript error in %s: line %d\n\t%s\n\t%s" ) %
											 report->filename %
											 (report->lineno+1) %
											 report->tokenptr %
											 message;

	JavaScriptEvent event(JavaScriptEngine::singleton, 0, errMessage );

	JavaScriptEngine::singleton->ErrorOccurred.fireEvent( &event );
}



/**
$Id: JavaScriptKit.cpp
*/


