#ifndef _VCF_INTERFACE_H__
#define _VCF_INTERFACE_H__
//Interface.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class Interface Interface.h "vcf/FoundationKit/Interface.h"
*Base class for interfaces
*/
class FOUNDATIONKIT_API Interface {

public:
	Interface(){};

	virtual ~Interface(){};

};

}; //end of namespace VCF


#endif // _VCF_INTERFACE_H__

/**
$Id$
*/
