
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
	//StringUtils:: //JC -  I commented this out because I want to see all the un-inplemented functions for now.
	#ifdef _DEBUG
	AnsiString s = funcName + " is not implemented.\n";
	printf(s.c_str());
	#endif
}

/**
$Id$
*/

