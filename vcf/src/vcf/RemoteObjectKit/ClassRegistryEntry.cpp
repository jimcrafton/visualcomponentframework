//ClassRegistryEntry.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ClassRegistryEntry.h


#include "vcf/RemoteObjectKit/RemoteObjectKit.h"

using namespace VCF;

using namespace VCFRemote;

ClassRegistryEntry::ClassRegistryEntry()
{
	classID_ = "";
	userID_ = "";
	localServerPath_ = "";
	inProcess_ = false;
	isRemote_ = false;
	remoteServerPath_ = "";
}

ClassRegistryEntry::ClassRegistryEntry( const VCF::String& classID,
		                const VCF::String& userID,
						const VCF::String& localServerPath,
						const bool& inProcess,
						const bool& remote,
						const VCF::String& remoteServerPath )
{
	classID_ = classID;
	userID_ = userID;
	localServerPath_ = localServerPath;
	inProcess_ = inProcess;
	isRemote_ = remote;
	remoteServerPath_ = remoteServerPath;
}

ClassRegistryEntry::~ClassRegistryEntry()
{

}

void ClassRegistryEntry::saveToStream( OutputStream * stream )
{
	stream->write( classID_ );
	stream->write( userID_ );
	stream->write( localServerPath_ );
	stream->write( inProcess_ );
	stream->write( isRemote_ );
	stream->write( remoteServerPath_ );
}

void ClassRegistryEntry::loadFromStream( InputStream * stream )
{
	stream->read( classID_ );
	stream->read( userID_ );
	stream->read( localServerPath_ );
	stream->read( inProcess_ );
	stream->read( isRemote_ );
	stream->read( remoteServerPath_ );
}

VCF::String ClassRegistryEntry::toString()
{
	return "classID = " + classID_ + "\nLocal Server Path = " + localServerPath_;
}


/**
$Id$
*/
