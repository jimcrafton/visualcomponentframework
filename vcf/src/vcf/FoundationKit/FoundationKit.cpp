//FoundationKit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/MessageLoader.h"
#include "vcf/FoundationKit/TextCodec.h"
#include "vcf/FoundationKit/StringsMessageLoader.h"
#include "vcf/FoundationKit/ThreadManager.h"
#include "vcf/FoundationKit/VFFInputStream.h"


#include "vcf/FoundationKit/RTTIMacros.h"

#include "vcf/FoundationKit/FoundationKitRTTI.inl"

//#include "utils/Dictionary.h"

namespace VCF
{



SystemToolkit* SystemToolkit::systemToolkitInstance = NULL;

System* System::systemInstance = NULL;

ClassRegistry* ClassRegistry::registryInstance_ = NULL;


std::map<String,std::vector<Class*>*>* Component::registeredComponentMap = NULL;

EnumeratorContainer<std::vector<Class*>,Class*>* Component::registeredCompContainer = NULL;

EnumeratorContainer<std::vector<String>,String>* Component::registeredCategoryContainer = NULL;

std::vector<String>* Component::registeredCategory = NULL;

std::vector<InitializationFunc>* initializerFunctions = NULL;
std::vector<FinalizationFunc>* finalizerFunctions = NULL;


static CommandLine foundationKitCommandLine;



void FoundationKit::internal_addInitializer( InitializationFunc funcPtr )
{
	if ( NULL == initializerFunctions ) {
		initializerFunctions = new std::vector<InitializationFunc>();
	}

	std::vector<InitializationFunc>::iterator found =
		std::find( initializerFunctions->begin(), initializerFunctions->end(), funcPtr );
	if ( found == initializerFunctions->end() ) {
		initializerFunctions->push_back( funcPtr );
	}

}

void FoundationKit::internal_addFinalizer( FinalizationFunc funcPtr )
{
	if ( NULL == finalizerFunctions ) {
		finalizerFunctions = new std::vector<FinalizationFunc>();
	}

	std::vector<FinalizationFunc>::iterator found =
		std::find( finalizerFunctions->begin(), finalizerFunctions->end(), funcPtr );
	if ( found == finalizerFunctions->end() ) {
		finalizerFunctions->push_back( funcPtr );
	}
}


void FoundationKit::init( int argc, char** argv )
{
	try {
		foundationKitCommandLine.splitLine( argc, argv );

		SystemToolkit::create();

#ifdef _VCF_DEBUG_NEW
		Object::accessMutex_ = NULL;
		Object::accessMutex_ = new Mutex();
		if ( NULL == Object::accessMutex_ ) {
			throw RuntimeException( MAKE_ERROR_MSG_2("access mutex is NULL!") );
		}
#endif
		System::create();

		ClassRegistry::create();


		MessageLoader::registerMessageLoader( "text/strings", new StringsMessageLoader() );

		ThreadManager::create();

		PackageManager::init();

	}
	catch ( BasicException& e ) {
		StringUtils::trace( "unknown exception occurred during FoundationKit::init()\n\terror is: " +
												e.getMessage() + "\n" );
		throw e;
	}
	catch ( ... ) {
		StringUtils::trace( "unknown exception occurred during FoundationKit::init()\n" );
		throw BasicException("unknown exception occurred during FoundationKit::init()");
	}

	{
		try {
			REGISTER_CLASSINFO_EXTERNAL( ObjectWithCallbacks );
			REGISTER_CLASSINFO_EXTERNAL( ComponentSetting );
			REGISTER_CLASSINFO_EXTERNAL( Component );
		}
		catch ( BasicException& e ) {
			StringUtils::trace( "exception attempting to register basic objects, error: " +
			e.getMessage() + "\n" );
			throw e;
		}

	}


	//call initializers!

	if ( NULL != initializerFunctions ) {
		std::vector<InitializationFunc>::iterator it = initializerFunctions->begin();
		while ( it != initializerFunctions->end() ) {
			InitializationFunc funcPtr = *it;

			(*funcPtr)();

			it ++;
		}
	}
}

void FoundationKit::terminate()
{
	//call finalizers!

	if ( NULL != finalizerFunctions ) {
		std::vector<FinalizationFunc>::iterator it = finalizerFunctions->begin();
		while ( it != finalizerFunctions->end() ) {
			FinalizationFunc funcPtr = *it;

			(*funcPtr)();

			it ++;
		}

		delete finalizerFunctions;
	}

	Delegate::terminateThreadPool();


	TextCodec::internal_freeAllRegisteredCodecs();

	MessageLoader::internal_freeAllRegisteredMessageLoaders();

	ClassRegistry::terminate();

	SystemToolkit::terminate();

	ThreadManager::terminate();

	PackageManager::terminate();

	VFFInputStream::internal_clearComponentConstants();

	System::terminate();

#ifdef _VCF_DEBUG_NEW
	Mutex* mutex = Object::accessMutex_;
	Object::accessMutex_ = NULL;
	delete mutex;
#endif

#ifdef _DEBUG
	Object::dumpDebugInfo();
#endif



}



const CommandLine& FoundationKit::getCommandLine()
{
	return foundationKitCommandLine;
}

void FoundationKit::assertCondition( bool condition, const String& failureMessage )
{
	if ( !condition ) {

		throw FoundationKit::Assertion( L"Assertion failure:\n" + failureMessage );
	}
}

} // namespace VCF

/**
$Id$
*/
