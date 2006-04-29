#ifndef _VCF_RESOURCE_H__
#define _VCF_RESOURCE_H__
//Resource.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{
/**
\class RegistryPeer Resource.h "vcf/FoundationKit/Resource.h"
*/
class FOUNDATIONKIT_API Resource : public Object
{
public:
	/**
	*the data passed in is copied - it is assumed that someone else owns
	*it - so it is not safe to destroy.
	*/
	Resource( void* data, const uint32& size, const String& name = "" );

	virtual ~Resource();

	void* getData();

	void setData( void* data );

	String getName();

	void setName( const String& name );

	uint32 getDataSize();
private:
	String name_;
	void* data_;
	uint32 size_;
};

};


#endif // _VCF_RESOURCE_H__

/**
$Id$
*/
