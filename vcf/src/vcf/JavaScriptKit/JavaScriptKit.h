#ifndef _JAVASCRIPTKIT_H__
#define _JAVASCRIPTKIT_H__
//JavaScriptKit.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/**
Notes for mozilla based JS Engine

The newer version of the JSAPI engine from mozilla 
had some changes that intially would not compile 
on VC6. The VC6 compiler apparently is being dropped
due to the addition of cairo support (supposedly cairo
won't compile on VC6, which makes little sense but oh 
well, that's life with OSS projects) so the author
of the new change probably never bothered to compile
under VC6. The changes below should fix the problem,
unless new code later on introduces something else.

I'm including this here so that if someon at a later
dat jsu tblindly overwrite the JSAPI code to update 
it, we know what to fix.

fix in jsutils.h, line 72

#if _MSC_VER <= 1200 
//Jim C - added this to allow for compiling with VC6
#define JS_STATIC_ASSERT(condition)                                           \
    typedef int js_static_assert_line_##__LINE__ [(condition) ? 1 : -1]
#else
#define JS_STATIC_ASSERT(condition)                                           \
    JS_STATIC_ASSERT_IMPL(condition, __LINE__)
#define JS_STATIC_ASSERT_IMPL(condition, line)                                \
    JS_STATIC_ASSERT_IMPL2(condition, line)
#define JS_STATIC_ASSERT_IMPL2(condition, line)                               \
    typedef int js_static_assert_line_##line [(condition) ? 1 : -1]
#endif


*/




#if _MSC_VER > 1000
#   pragma once
#endif

/**
Handle the extension based on the compiler
*/
# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1400)
#     define _LIB_CPLVERNUM "vc80"
#   elif (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#		endif
#  ifdef __BORLANDC__
#     define _LIB_CPLVERNUM "bcc"
#  endif
# endif


#ifdef _DEBUG
	#define JSKIT_LIBDLL	"JavaScriptKit_"_LIB_CPLVERNUM"_d.lib"
	#define JSKIT_LIBS	"JavaScriptKit_"_LIB_CPLVERNUM"_sd.lib"
#else
	#define JSKIT_LIBDLL	"JavaScriptKit_"_LIB_CPLVERNUM".lib"
	#define JSKIT_LIBS	"JavaScriptKit_"_LIB_CPLVERNUM"_s.lib"
#endif



//auto link stuff
#if defined(_MSC_VER) || defined(__BORLANDC__)
	#ifdef USE_JAVASCRIPTKIT_DLL
		#pragma message( "linking to " JSKIT_LIBDLL )
		#define JAVASCRIPTKIT_DLL
		// using dynamic link library		
		#pragma comment(lib, JSKIT_LIBDLL)
	#elif defined USE_JAVASCRIPTKIT_LIB
		#pragma message( "linking to " JSKIT_LIBS )
		// using statically linked library
		#pragma comment(lib, JSKIT_LIBS)
	#endif

#endif //VCF_MSC





//this sets up a "dependencies" set of defines
//if you are using the regex kit, then it only makes 
//sense that you are ALSO using the FoundationKit.
//the following takes care of defining these for you.

#ifdef USE_JAVASCRIPTKIT_DLL
# 	ifndef JAVASCRIPTKIT_DLL
#		define JAVASCRIPTKIT_DLL
# 	endif
# 	ifndef USE_FOUNDATIONKIT_DLL
#		define USE_FOUNDATIONKIT_DLL
# 	endif
#elif defined (USE_JAVASCRIPTKIT_LIB)
//#		define ONIG_EXTERN extern
# 	ifndef USE_FOUNDATIONKIT_LIB
#		define USE_FOUNDATIONKIT_LIB
# 	endif
#endif



//export crap
#ifdef JAVASCRIPTKIT_DLL
	#if defined(JAVASCRIPTKIT_EXPORTS)
		#define JAVASCRIPTKIT_API __declspec(dllexport)
	#else
		#define JAVASCRIPTKIT_API __declspec(dllimport)
	#endif
#else
	#define JAVASCRIPTKIT_API
#endif //DATABASEKIT_DLL



#include "vcf/FoundationKit/FoundationKit.h"


#if defined(VCF_WIN)
	#ifndef XP_WIN
		#define XP_WIN
	#endif
#elif defined(VCF_POSIX)
	#define XP_UNIX
#endif



/* include the JS engine API header */
#include "vcf/JavaScriptKit/js-impl/jsapi.h"
#include "vcf/JavaScriptKit/js-impl/jscntxt.h"



namespace VCF {
	class JSEventHandler;




	class JAVASCRIPTKIT_API JavaScriptKit {
	public:

		static void init( int argc, char **argv );
		static void terminate();
	};





	class JAVASCRIPTKIT_API JavaScriptEvent : public Event {
	public:
		JavaScriptEvent( Object* source, unsigned int eventType, const String& msg ):Event(source,eventType),message(msg){}

		JavaScriptEvent( Object* source, unsigned int eventType ):Event(source,eventType){}

		JavaScriptEvent():Event(NULL,0){}

		String message;
	};

	class JAVASCRIPTKIT_API JavaScriptEngine : public Object {
	public:
		class JAVASCRIPTKIT_API ObjectInstanceEntry {
		public:
			ObjectInstanceEntry() : instance_(NULL), releasable_(true) {

			}

			Object* instance_;
			bool releasable_;
		};

		class JAVASCRIPTKIT_API ClassEntry {
		public:
			ClassEntry(): m_vcfClass(NULL), m_jsClass(NULL),
						m_props(NULL),
							m_propCount(0),
							m_methods(NULL),
							m_methodCount(0){				
				
			};
			
			ClassEntry ( Class* clazz, JSClass* jsClass, 
							JSPropertySpec* props, const ulong& propCount,
							JSFunctionSpec* methods, const ulong& methodCount ):
							m_vcfClass(clazz), 
							m_jsClass(jsClass),
							m_props(props),
							m_propCount(propCount),
							m_methods(methods),
							m_methodCount(methodCount)
							{

			}

			ClassEntry( const ClassEntry& val ) {
				*this = val;
			}

			ClassEntry& operator= ( const ClassEntry& val ) {
				m_vcfClass = val.m_vcfClass;
				m_jsClass = val.m_jsClass;
				m_props = val.m_props;
				m_propCount = val.m_propCount;
				m_methods = val.m_methods;
				m_methodCount = val.m_methodCount;
				return *this;
			}

			Class* m_vcfClass;
			JSClass* m_jsClass;

			//array of JSPropertySpec
			JSPropertySpec* m_props;
			ulong m_propCount;

			//array of JSFunctionSpec
			JSFunctionSpec* m_methods;
			ulong m_methodCount;
		};

		JavaScriptEngine();

		virtual ~JavaScriptEngine();


		DELEGATE(ScriptExecuting);

		DELEGATE(ErrorOccurred);


		void executeScript( const String& script );

		void executeScriptFromFile( const String& fileName );

		void updateFromClassRegistry();

		/**
		defines a globals instance of an object
		*/
		void defineGlobalObject( Object* object );

		static JavaScriptEngine& engine();

		static void initialize();
		static void terminate();

		static void invokeEventhandler( Event* e, JSFunction* function, const VCF::String& functionName );
	protected:

		void internal_executeScript( const String& script, const String& fileName );

		typedef std::map<String,ClassEntry> ClassMap;
		typedef std::map<JSObject*,ObjectInstanceEntry> InstanceMap;
		typedef std::map<JSObject*,Delegate*> DelegateMap;
		typedef std::multimap<Delegate*,EventHandler*> EventHandlerMap;
		typedef std::pair<EventHandlerMap::iterator, EventHandlerMap::iterator> EventHandlerMapRange;

		JSVersion m_version;	
		JSRuntime* m_runTime;
		JSContext* m_context;
		JSObject* m_global;
		JSClass* m_globalClass;
		JSClass* globalDelegateClass_;
		ClassEntry globalEventClass_;

		ClassMap m_jsClassMap;
		InstanceMap m_jsObjectInstances;
		DelegateMap jsDelegateInstances_;
		EventHandlerMap jsEventHandlers_;

		std::vector<char*> names_;

		static JavaScriptEngine* singleton;

		static JSBool methodCall(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);

		static JSBool getObjProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp);
		static JSBool setObjProperty(JSContext *cx, JSObject *obj, jsval id, jsval *vp);

		static JSBool enumerate(JSContext *cx, JSObject *obj);
		static JSBool resolve(JSContext *cx, JSObject *obj, jsval id);
		static void finalize(JSContext *cx, JSObject *obj);		
		static JSBool constructor(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval) ;

		bool assignJSValToVariant( jsval* vp, VariantData* vd );
		bool assignVariantToJSVal( VariantData* vd, jsval* vp );

		static void rawErrorReporter(JSContext* cx, const char* message, JSErrorReport* report );

		void initVCFGlobalClasses();

		JSObject* newObjectFromVCFEvent( VCF::Event* e );
	};	
};


/**
$Id: JavaScriptKit.h
*/



#endif // _JAVASCRIPTKIT_H__


