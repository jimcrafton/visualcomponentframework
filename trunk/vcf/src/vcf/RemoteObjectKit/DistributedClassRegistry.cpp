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
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:31:56  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.8  2003/05/17 20:37:51  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.3  2003/03/23 04:06:34  marcelloptr
*minor fixes
*
*Revision 1.7.2.2  2003/03/23 03:24:02  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.1  2003/03/12 03:13:33  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.14.1  2003/01/08 00:20:04  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.2  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.5.4.1  2002/03/20 21:56:57  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.5  2002/02/27 04:16:12  ddiego
*add sub items to TreeItem class for teh tree list control
*added fixes to the RemoteObject stuff
*
*Revision 1.4  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


