//ThreadEvent.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
using namespace VCF;

ThreadEvent::ThreadEvent( Object* source ):
	Event( source )
{

}

ThreadEvent::ThreadEvent( Object* source, const uint32& eventType ):
	Event( source, eventType )
{

}

ThreadEvent::~ThreadEvent()
{

}


/**
$Id$
*/
