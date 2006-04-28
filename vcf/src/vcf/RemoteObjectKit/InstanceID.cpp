//InstanceID.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/RemoteObjectKit/RemoteObjectKit.h"


using namespace VCF;
using namespace VCFRemote;
using namespace VCFNet;

InstanceID::InstanceID()
{
	Process thisProcess;
	machineName_ = NetToolkit::getDefaultNetToolkit()->getLocalMachineName();
	processID_ = thisProcess.getID();
	threadID_ = thisProcess.getThreadID();
	memAddress_ = 0;
}

InstanceID::InstanceID( const int& memAddress )
{
	Process thisProcess;
	machineName_ = NetToolkit::getDefaultNetToolkit()->getLocalMachineName();
	processID_ = thisProcess.getID();
	threadID_ = thisProcess.getThreadID();
	memAddress_ = memAddress;
}

InstanceID::InstanceID( const VCF::String& machineName, const int& processID,
					     const int& threadID, const int& memAddress )
{
	this->machineName_ = machineName;
	processID_ = processID;
	threadID_ = threadID;
	memAddress_ = memAddress;
}

void InstanceID::saveToStream( VCF::OutputStream * stream )
{
	stream->write( machineName_ );
	stream->write( processID_ );
	stream->write( threadID_ );
	stream->write( memAddress_ );
}

void InstanceID::loadFromStream( VCF::InputStream * stream )
{
	stream->read( machineName_ );
	stream->read( processID_ );
	stream->read( threadID_ );
	stream->read( memAddress_ );
}


/**
$Id$
*/
