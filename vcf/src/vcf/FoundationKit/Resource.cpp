//Resource.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"


using namespace VCF;

Resource::Resource( void* data, const uint32& size, const String& name )
{
	data_ = new char[size];
	memset( data_, 0, size*sizeof(char) );
	memcpy( data_, data, size*sizeof(char) );
	size_ = size;
	name_ = name;
}

Resource::~Resource()
{
	char* tmp = (char*)data_;
	delete tmp;
}

void* Resource::getData()
{
	return data_;
}

String Resource::getName()
{
	return name_;
}

void Resource::setName( const String& name )
{
	name_ = name;
}

uint32 Resource::getDataSize()
{
	return size_;
}


/**
$Id$
*/
