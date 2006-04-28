#ifndef _VCF_DISTRIBUTEDCLASSREGISTRY_H__
#define _VCF_DISTRIBUTEDCLASSREGISTRY_H__
//DistributedClassRegistry.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFRemote  {

class ClassRegistryEntry;


/**
*Class DistributedClassRegistry documentation
*/
class REMOTEKIT_API DistributedClassRegistry : public VCF::Object {
public:
	DistributedClassRegistry();

	virtual ~DistributedClassRegistry();

	static DistributedClassRegistry* create();

	static DistributedClassRegistry* getDistributedClassRegistry();

	/**
	*this is called in the start up of an application or VPL to register
	*the application and it's classes as distributed and available for
	*remote creation
	*/
	bool registerClass( VCF::Class* classToRegister, const VCF::String& serverName,
		                const VCF::String& userID,
						const bool& inProcessServer, const bool& isServerRemote );

	bool registerClass( const VCF::String& classID,
		                const VCF::String& userID,
						const VCF::String& localServerPath,
						const bool& inProcess,
						const bool& remote,
						const VCF::String& remoteServerPath );

	bool unRegisterClass( const VCF::String& classID );

	VCF::Enumerator<ClassRegistryEntry*>* getRegisteredEntries();

	/**
	*attempts to find a ClassRegistryEntry, assumes the name
	*param is either a valid userID or classID
	*returns NULL if nothing is found, or a valid ClassRegistryEntry pointer
	*if successful
	*/
	ClassRegistryEntry* findEntry( const VCF::String& name );
protected:
	static DistributedClassRegistry* distributedClassRegistryInstance;
private:
	VCF::String registryEntryFile_;
	std::map<VCF::String,ClassRegistryEntry*> regEntriesMap_;//keyed by classID
	std::map<VCF::String,ClassRegistryEntry*> regEntriesMap2_;//keyed by userID
	VCF::EnumeratorMapContainer<std::map<VCF::String,ClassRegistryEntry*>,ClassRegistryEntry*> regEntriesContainer_;
};


}; //end of namespace VCFRemote


#endif // _VCF_DISTRIBUTEDCLASSREGISTRY_H__

/**
$Id$
*/
