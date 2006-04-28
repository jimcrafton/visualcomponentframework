//DistributedClassRegistry.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//DistributedClassRegistry.h

#include "vcf/RemoteObjectKit/RemoteObjectKit.h"

using namespace VCF;

using namespace VCFRemote;

#define  DISTRIB_CLASS_REG_DB		 "Software\\VCF\\Remote"
#define  DISTRIB_CLASS_DB_FILE		 "DistribClassRegDB"

DistributedClassRegistry* DistributedClassRegistry::distributedClassRegistryInstance = NULL;


DistributedClassRegistry* DistributedClassRegistry::getDistributedClassRegistry()
{
	return DistributedClassRegistry::distributedClassRegistryInstance;
}

DistributedClassRegistry* DistributedClassRegistry::create()
{
	if ( NULL == DistributedClassRegistry::distributedClassRegistryInstance ) {
		DistributedClassRegistry::distributedClassRegistryInstance = new DistributedClassRegistry();
	}

	return DistributedClassRegistry::distributedClassRegistryInstance;
}


DistributedClassRegistry::DistributedClassRegistry()
{
	registryEntryFile_ = "";

	regEntriesContainer_.initContainer( regEntriesMap_ );

	Registry reg;
	reg.setRoot( RKT_LOCAL_MACHINE );
	if ( true == reg.openKey( DISTRIB_CLASS_REG_DB, false ) )
	{
		registryEntryFile_ = reg.getStringValue( DISTRIB_CLASS_DB_FILE );
		if ( registryEntryFile_.empty() ) {
			//throw exception - class registry db file not found !!!!!
		}
	}
	else {
		//throw exception - class registry db file not found !!!!!
	}

	FileInputStream fs( registryEntryFile_ );
	int entryCount = 0;
	fs >> entryCount;
	for ( int i=0;i<entryCount;i++)
	{
		ClassRegistryEntry* entry = new ClassRegistryEntry();
		fs >> static_cast<Persistable*>(entry);
		regEntriesMap_[ entry->getClassID() ] = entry;
		regEntriesMap2_[ entry->getUserID() ] = entry;
	}
}

DistributedClassRegistry::~DistributedClassRegistry()
{
	bool okToWriteRegEntries = !(registryEntryFile_.empty());
	OutputStream* os = NULL;
	FileOutputStream* fs = NULL;
	if ( true == okToWriteRegEntries ) {
		fs = new FileOutputStream( registryEntryFile_ );
		int entryCount = regEntriesMap_.size();
		(*fs) << entryCount;
		//os = dynamic_cast<OutputStream*>( &fs );
	}
	std::map<String,ClassRegistryEntry*>::iterator it = regEntriesMap_.begin();
	while ( it != regEntriesMap_.end() ) {
		ClassRegistryEntry* entry = it->second;
		if ( true == okToWriteRegEntries ) {
			 (*fs) << entry;
		}
		delete entry;
		entry = NULL;
		it++;
	}
	if ( true == okToWriteRegEntries ) {
		delete fs;
		fs = NULL;
	}
	regEntriesMap_.clear();
	regEntriesMap2_.clear();
}

bool DistributedClassRegistry::registerClass( Class* classToRegister, const VCF::String& serverName,
												const VCF::String& userID,
												const bool& inProcessServer,
												const bool& isServerRemote )
{
	bool result = false;
	if ( NULL == classToRegister ) {
		return result;
	}


	return result;
}

bool DistributedClassRegistry::registerClass( const VCF::String& classID,
												const VCF::String& userID,
												const VCF::String& localServerPath,
												const bool& inProcess,
												const bool& remote,
												const VCF::String& remoteServerPath )
{
	bool result = false;

	ClassRegistryEntry* entry =
		new ClassRegistryEntry(  classID, userID, localServerPath, inProcess, remote, remoteServerPath );

	regEntriesMap_[classID] = entry;
	regEntriesMap2_[userID] = entry;
	result = true;
	return result;
}

VCF::Enumerator<ClassRegistryEntry*>* DistributedClassRegistry::getRegisteredEntries()
{
	return regEntriesContainer_.getEnumerator();
}

ClassRegistryEntry* DistributedClassRegistry::findEntry( const VCF::String& name )
{
	ClassRegistryEntry* result = NULL;
	/*
	*searches the classID map first, then the userID map
	*could a smarter way, perhaps read the first few charaters
	*and check the form to see if it a valid UUID ?
	*/
	std::map<VCF::String,ClassRegistryEntry*>::iterator found = regEntriesMap_.find( name );
	if ( found != regEntriesMap_.end() ) {
		result = found->second;
	}
	else {
		found = regEntriesMap2_.find( name );
		if ( found != regEntriesMap2_.end() ){
			result = found->second;
		}
	}
	return result;
}

bool DistributedClassRegistry::unRegisterClass( const VCF::String& classID )
{
	bool result = false;
	std::map<VCF::String,ClassRegistryEntry*>::iterator found = regEntriesMap_.find( classID );
	if ( found != regEntriesMap_.end() ) {
		ClassRegistryEntry* entry = found->second;
		delete entry;
		regEntriesMap_.erase( found );
		entry = NULL;
		result = true;
	}
	return result;
}


/**
$Id$
*/
