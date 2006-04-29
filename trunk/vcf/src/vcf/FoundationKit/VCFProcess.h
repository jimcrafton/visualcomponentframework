#ifndef _VCF_VCFPROCESS_H__
#define _VCF_VCFPROCESS_H__
//VCFProcess.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#ifndef _VCF_WAITABLE_H__
#include "vcf/FoundationKit/Waitable.h"
#endif


namespace VCF {

class ProcessPeer;

/**
\class Process VCFProcess.h "vcf/FoundationKit/VCFProcess.h"
*/
class FOUNDATIONKIT_API Process : public Object, public Waitable {

public:
	Process();

	virtual ~Process();

	int getID();

	int getThreadID();

	/**
	The default behaviour is to just start the process, assuming the processName is a
	path to the executable. However, we are now going to get a tad fancier!
	
	If the processName is a directory, we will try and locate the 
	Info.plist/Info.xml file, read it, and, based on the info we get, 
	attempt to use this to open the binary inside.
	@param String the fully qualified file name of the process to
	create, or a directory that includes a Info.plist/Info.xml file in it
	identifying the process's ProgramInfo.
	@see System::getProgramInfoFromFileName()
	@see ProgramInfo

	@param String the command line arguments to pass to the newly created process.	
	*/
	bool createProcess( const String& processName, const String& arguments );

	String getName();

	ulong32 terminate();

	virtual WaitResult wait();

	virtual WaitResult wait( uint32 milliseconds );

	virtual OSHandleID getPeerHandleID(); 
protected:
	ProcessPeer* processPeer_;
};

}; //end of namespace VCF


#endif // _VCF_VCFPROCESS_H__

/**
$Id$
*/
