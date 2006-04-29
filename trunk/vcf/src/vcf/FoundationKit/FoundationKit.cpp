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


#include "vcf/FoundationKit/RTTIMacros.h"

#include "vcf/FoundationKit/FoundationKitRTTI.inl"

//#include "utils/Dictionary.h"

using namespace VCF;



SystemToolkit* SystemToolkit::systemToolkitInstance = NULL;

System* System::systemInstance = NULL;

ClassRegistry* ClassRegistry::registryInstance_ = NULL;

static CommandLine foundationKitCommandLine;

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
			REGISTER_CLASSINFO_EXTERNAL( ObjectWithEvents );
		}
		catch ( BasicException& e ) {
			StringUtils::trace( "exception attempting to register basic objects, error: " +
			e.getMessage() + "\n" );
			throw e;
		}

	}
}

void FoundationKit::terminate()
{
	TextCodec::internal_freeAllRegisteredCodecs();

	MessageLoader::internal_freeAllRegisteredMessageLoaders();

	System::terminate();

	ClassRegistry::terminate();

	SystemToolkit::terminate();

	ThreadManager::terminate();

	PackageManager::terminate();

#ifdef _VCF_DEBUG_NEW
	Mutex* mutex = Object::accessMutex_;
	Object::accessMutex_ = NULL;
	mutex->free();
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

		throw FoundationKit::Assertion( L"Assertion failure: " + failureMessage );
	}
}


/**
$Id$
*/
