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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.7.8.1  2004/04/26 21:58:46  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/05/17 20:37:16  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.16.1  2003/03/12 03:11:48  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.5  2002/02/27 04:16:11  ddiego
*add sub items to TreeItem class for teh tree list control
*added fixes to the RemoteObject stuff
*
*Revision 1.4  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_DISTRIBUTEDCLASSREGISTRY_H__


