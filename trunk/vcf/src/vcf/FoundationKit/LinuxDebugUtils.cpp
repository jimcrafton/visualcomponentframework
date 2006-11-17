
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/FoundationKitPrivate.h"

using namespace VCF;

	
void LinuxDebugUtils::FunctionNotImplemented(const String& funcName)
{
	StringUtils::trace(funcName + " is not implemented.\n");
}

/**
$Id$
*/

