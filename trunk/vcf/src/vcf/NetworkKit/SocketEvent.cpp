//SocketEvent.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/NetworkKit/NetworkKit.h"

using namespace VCF;
using namespace VCFNet;

SocketEvent::SocketEvent( Object * source, Socket* sender,
						 char* data, const int& dataSize ):
	Event( source )
{
	sender_ = sender;
	data_ = data;
	dataSize_ = dataSize;
}

SocketEvent::~SocketEvent()
{

}


/**
$Id$
*/
