//SystemToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;



SystemToolkit* SystemToolkit::create()
{

	if ( NULL == SystemToolkit::systemToolkitInstance ) {
#if defined(VCF_WIN) && !defined(VCF_DOTNET)
		SystemToolkit::systemToolkitInstance = new Win32SystemToolkit();
#elif defined(VCF_DOTNET)
		SystemToolkit::systemToolkitInstance = new DotNetSystemToolkit();
#elif defined(VCF_POSIX)
		SystemToolkit::systemToolkitInstance = new LinuxSystemToolkit();
#elif defined(VCF_OSX)
		SystemToolkit::systemToolkitInstance = new OSXSystemToolkit();
#endif
		if ( NULL == SystemToolkit::systemToolkitInstance ) {
			throw InvalidPointerException( MAKE_ERROR_MSG_2(String("No Toolkit instantiated!")) );
		}
		SystemToolkit::systemToolkitInstance->init();
	}

	return SystemToolkit::systemToolkitInstance;
}

void SystemToolkit::terminate()
{
	SystemToolkit::systemToolkitInstance->free();
}


SystemToolkit::SystemToolkit()
{

}

SystemToolkit::~SystemToolkit()
{
	std::multimap<uint32,AcceleratorKey*>::iterator it = acceleratorMap_.begin();
	while ( it != acceleratorMap_.end() ) {
		delete it->second;
		it ++;
	}
	acceleratorMap_.clear();

}

ProcessPeer* SystemToolkit::createProcessPeer( Process* process )
{
	return SystemToolkit::getSystemToolkit()->internal_createProcessPeer( process );
}

ProcessIORedirectionPeer* SystemToolkit::createProcessIORedirectionPeer( ProcessWithRedirectedIO* process )
{
	return SystemToolkit::getSystemToolkit()->internal_createProcessIORedirectionPeer(process);
}

ThreadPeer* SystemToolkit::createThreadPeer( Thread* thread, bool mainThread )
{
	return SystemToolkit::getSystemToolkit()->internal_createThreadPeer(thread,mainThread);
}

RunLoopPeer* SystemToolkit::createRunLoopPeer( RunLoop* runLoop )
{
	return SystemToolkit::getSystemToolkit()->internal_createRunLoopPeer(runLoop);
}

ThreadManagerPeer* SystemToolkit::createThreadManagerPeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createThreadManagerPeer();
}


SystemPeer* SystemToolkit::createSystemPeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createSystemPeer();
}

SemaphorePeer* SystemToolkit::createSemaphorePeer( int32 initialCount, int32 maxCount )
{
	return SystemToolkit::getSystemToolkit()->internal_createSemaphorePeer(initialCount,maxCount);
}

RegistryPeer* SystemToolkit::createRegistryPeer( Registry* registry )
{
	return SystemToolkit::getSystemToolkit()->internal_createRegistryPeer(registry);
}

MutexPeer* SystemToolkit::createMutexPeer( Mutex* mutex )
{
	return SystemToolkit::getSystemToolkit()->internal_createMutexPeer(mutex);
}

ConditionPeer* SystemToolkit::createConditionPeer( Condition* condition )
{
	return SystemToolkit::getSystemToolkit()->internal_createConditionPeer(condition);
}

LibraryPeer* SystemToolkit::createLibraryPeer( Library* library )
{
	return SystemToolkit::getSystemToolkit()->internal_createLibraryPeer(library);
}

FilePeer* SystemToolkit::createFilePeer( File* file )
{
	return SystemToolkit::getSystemToolkit()->internal_createFilePeer( file );
}

FileStreamPeer* SystemToolkit::createFileStreamPeer( const String& filename, const FileStreamAccessType& accessType )
{
	return SystemToolkit::getSystemToolkit()->internal_createFileStreamPeer(filename,accessType);
}

FileStreamPeer* SystemToolkit::createFileStreamPeer( File* file )
{
	return SystemToolkit::getSystemToolkit()->internal_createFileStreamPeer(file);
}

LocalePeer* SystemToolkit::createLocalePeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createLocalePeer();
}

ResourceBundlePeer* SystemToolkit::createResourceBundlePeer()
{
	return SystemToolkit::getSystemToolkit()->internal_createResourceBundlePeer();
}

AcceleratorKey* SystemToolkit::getAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src )
{
	return SystemToolkit::getSystemToolkit()->internal_getAccelerator( keyCode, modifierMask, src );
}

bool SystemToolkit::findMatchingAccelerators( AcceleratorKey* key, std::vector<AcceleratorKey*>& matchingAccelerators )
{
	return SystemToolkit::getSystemToolkit()->internal_findMatchingAccelerators( key, matchingAccelerators );
}

void SystemToolkit::registerAccelerator( AcceleratorKey* accelerator )
{
	SystemToolkit::getSystemToolkit()->internal_registerAccelerator( accelerator );
}

void SystemToolkit::removeAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src )
{
	SystemToolkit::getSystemToolkit()->internal_removeAccelerator( keyCode, modifierMask, src );
}

void SystemToolkit::addToUpdateList( Component* component )
{
	SystemToolkit::getSystemToolkit()->internal_addToUpdateList( component );
}

void SystemToolkit::removeFromUpdateList( Component* component )
{
	SystemToolkit::getSystemToolkit()->internal_removeFromUpdateList( component );
}

void SystemToolkit::updateComponents()
{
	SystemToolkit::getSystemToolkit()->internal_updateComponents();
}

void SystemToolkit::removeAcceleratorKeysForControl( Object* control )
{
	SystemToolkit::getSystemToolkit()->internal_removeAcceleratorKeysForControl(control);
}

void SystemToolkit::removeAcceleratorKeysForMenuItem( Object* menuItem )
{
	SystemToolkit::getSystemToolkit()->internal_removeAcceleratorKeysForMenuItem(menuItem);
}

void SystemToolkit::removeAcceleratorKeysForObject( Object* src )
{
	SystemToolkit::getSystemToolkit()->internal_removeAcceleratorKeysForObject(src);
}


AcceleratorKey* SystemToolkit::internal_getAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src )
{
	AcceleratorKey* result = NULL;

	AcceleratorKey::Value key( modifierMask, keyCode );


	typedef std::multimap<uint32,AcceleratorKey*>::iterator AccelMapIter;
	std::pair<AccelMapIter, AccelMapIter> range = acceleratorMap_.equal_range( key );

	std::multimap<uint32,AcceleratorKey*>::iterator it = range.first;
	while ( it != range.second ) {
		AcceleratorKey* accel = it->second;

		if ( (src == accel->getAssociatedControl()) || 
				(src == accel->getAssociatedMenuItem()) || 
				(src == accel->getAssociatedObject()) ) {

			result = accel;
			break;
		}

		it ++;
	}

	return result;
}

bool SystemToolkit::internal_findMatchingAccelerators( AcceleratorKey* key, std::vector<AcceleratorKey*>& matchingAccelerators )
{
	matchingAccelerators.clear();

	AcceleratorKey::Value keyVal;
	keyVal = key;

	typedef std::multimap<uint32,AcceleratorKey*>::iterator AccelMapIter;
	std::pair<AccelMapIter, AccelMapIter> range = acceleratorMap_.equal_range( keyVal );

	std::multimap<uint32,AcceleratorKey*>::iterator it = range.first;
	while ( it != range.second ) {
		AcceleratorKey* accel = it->second;

		// we don't need to put in the list the accelerator (key) to which all the others are matching.
		if ( (accel->getEventHandler() == key->getEventHandler()) && 
				(accel != key) ) {
			matchingAccelerators.push_back( accel );
		}

		it ++;
	}

	return !matchingAccelerators.empty();
}

void SystemToolkit::internal_removeAccelerator( const VirtualKeyCode& keyCode, const uint32& modifierMask, Object* src )
{

	AcceleratorKey::Value key( modifierMask, keyCode );

	typedef std::multimap<uint32,AcceleratorKey*>::iterator AccelMapIter;

	std::pair<AccelMapIter, AccelMapIter> range = acceleratorMap_.equal_range( key );	

	std::vector<AccelMapIter> removeAccels;

	AccelMapIter it = range.first;
	while ( it != range.second ) {
		AcceleratorKey* accel = it->second;
		if ( (accel->getAssociatedControl() == src) || 
			(accel->getAssociatedMenuItem() == src) ||
			(accel->getAssociatedObject() == src) ) {
			accel->release();
			removeAccels.push_back( it );
		}

		it ++;
	}

	std::vector<AccelMapIter>::iterator it2 = removeAccels.begin();
	while ( it2 != removeAccels.end() ) {
		acceleratorMap_.erase( *it2 );
		it2 ++;
	}
}


void SystemToolkit::internal_registerAccelerator( AcceleratorKey* accelerator )
{
	AcceleratorKey::Value key;
	key = accelerator;	


	typedef std::multimap<uint32,AcceleratorKey*>::iterator AccelMapIter;
	std::pair<AccelMapIter, AccelMapIter> range = acceleratorMap_.equal_range( key );

	std::multimap<uint32,AcceleratorKey*>::iterator it = range.first;
	while ( it != range.second ) {
		AcceleratorKey* accel = it->second;

		if ( (accelerator->getAssociatedControl() == accel->getAssociatedControl()) && 
				(accelerator->getAssociatedMenuItem() == accel->getAssociatedMenuItem()) && 
				(accelerator->getAssociatedObject() == accel->getAssociatedObject()) ) {

			accel->free();
			//remove old entry!
			acceleratorMap_.erase( it );
			break;
		}

		it ++;
	}

	std::pair<uint32,AcceleratorKey*> item(key,accelerator);
	acceleratorMap_.insert( item );
}


void SystemToolkit::internal_addToUpdateList( Component* component )
{
	std::vector<Component*>::iterator found = std::find( componentsToUpdate_.begin(), componentsToUpdate_.end(), component );
	if ( found == componentsToUpdate_.end() ) {
		componentsToUpdate_.push_back( component );
	}
}

void SystemToolkit::internal_removeFromUpdateList( Component* component )
{
	std::vector<Component*>::iterator found = std::find( componentsToUpdate_.begin(), componentsToUpdate_.end(), component );
	if ( found != componentsToUpdate_.end() ) {
		componentsToUpdate_.erase( found );
	}
}

void SystemToolkit::internal_updateComponents()
{
	std::vector<Component*>::iterator it = componentsToUpdate_.begin();
	while ( it != componentsToUpdate_.end() ) {
		Component* component = *it;
		Event updateEvent( this, Component::COMPONENT_NEEDS_UPDATING );
		component->handleEvent( &updateEvent );
		it ++;
	}
}



void SystemToolkit::internal_removeAcceleratorKeysForControl( Object* control )
{
	typedef std::multimap<uint32,AcceleratorKey*>::iterator accel_iter;

	std::vector<accel_iter> removeAccels;

	accel_iter it = acceleratorMap_.begin();

	while ( it != acceleratorMap_.end() ) {
		AcceleratorKey* accel = it->second;
		if ( accel->getAssociatedControl() == control ) {
			accel->release();
			removeAccels.push_back( it );
		}
		it ++;
	}

	std::vector<accel_iter>::iterator it2 = removeAccels.begin();
	while ( it2 != removeAccels.end() ) {
		acceleratorMap_.erase( *it2 );
		it2 ++;
	}
}

void SystemToolkit::internal_removeAcceleratorKeysForMenuItem( Object* menuItem )
{
	typedef std::multimap<uint32,AcceleratorKey*>::iterator accel_iter;

	std::vector<accel_iter> removeAccels;

	accel_iter it = acceleratorMap_.begin();

	while ( it != acceleratorMap_.end() ) {
		AcceleratorKey* accel = it->second;
		if ( accel->getAssociatedMenuItem() == menuItem ) {
			accel->release();
			removeAccels.push_back( it );
		}
		it ++;
	}

	std::vector<accel_iter>::iterator it2 = removeAccels.begin();
	while ( it2 != removeAccels.end() ) {
		acceleratorMap_.erase( *it2 );
		it2 ++;
	}
}

void SystemToolkit::internal_removeAcceleratorKeysForObject( Object* src )
{
	typedef std::multimap<uint32,AcceleratorKey*>::iterator accel_iter;

	std::vector<accel_iter> removeAccels;

	accel_iter it = acceleratorMap_.begin();

	while ( it != acceleratorMap_.end() ) {
		AcceleratorKey* accel = it->second;
		if ( accel->getAssociatedObject() == src ) {
			accel->release();
			removeAccels.push_back( it );
		}
		it ++;
	}

	std::vector<accel_iter>::iterator it2 = removeAccels.begin();
	while ( it2 != removeAccels.end() ) {
		acceleratorMap_.erase( *it2 );
		it2 ++;
	}
}


/**
$Id$
*/
