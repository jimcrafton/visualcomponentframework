//DistributedException.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//DistributedException.h
#include "vcf/RemoteObjectKit/RemoteObjectKit.h"

using namespace VCF;

using namespace VCFRemote;


DistributedException::DistributedException():
	BasicException("")
{

}

DistributedException::~DistributedException() throw()
{

}


/**
$Id$
*/
