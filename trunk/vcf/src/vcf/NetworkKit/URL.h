#ifndef _VCF_URL_H__
#define _VCF_URL_H__
//URL.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFNet
{

class NETKIT_API URL : public VCF::Object
{
public:
	URL();

	virtual ~URL();

};


};


#endif // _VCF_URL_H__

/**
$Id$
*/
