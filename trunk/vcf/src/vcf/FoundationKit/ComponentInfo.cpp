//ComponentInfo.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"


using namespace VCF;

class VCF::Image
{
};


ComponentInfo::ComponentInfo( const String& componentUUID, const String& author, const String& company,
			  const String& copyright, const String& additionalInfo,
			  const String& packageName, const String& packageUUID,
			  Image* componentImage )
{
	author_ = author;
	copyright_ = copyright;
	company_ = company;
	additionalInfo_ = additionalInfo;
	componentUUID_ = componentUUID;
	componentImage_ = componentImage;
	packageName_ = packageName;
	packageUUID_ = packageUUID;

	reqNamespacesContainer_.initContainer( requiredNamespaces_ );
	reqHeadersContainer_.initContainer( requiredHeaders_ );
}

ComponentInfo::~ComponentInfo()
{
	if ( NULL != componentImage_ ) {
		delete componentImage_;
	}
}

Enumerator<String>* ComponentInfo::getRequiredHeaders()
{
	return reqHeadersContainer_.getEnumerator();
}

Enumerator<String>* ComponentInfo::getRequiredNamespaces()
{
	return reqNamespacesContainer_.getEnumerator();
}

void ComponentInfo::addHeader( const String& header )
{
	requiredHeaders_.push_back( header );
}

void ComponentInfo::removeHeader( const String& header )
{
	std::vector<String>::iterator found = std::find( requiredHeaders_.begin(), requiredHeaders_.end(), header );
	if ( found != requiredHeaders_.end() ) {
		requiredHeaders_.erase( found );
	}
}

void ComponentInfo::removeAllHeaders()
{
	requiredHeaders_.clear();
}

void ComponentInfo::addNamespace( const String& aNamespace )
{
	requiredNamespaces_.push_back( aNamespace );
}

void ComponentInfo::removeNamespace( const String& aNamespace )
{
	std::vector<String>::iterator found = std::find( requiredNamespaces_.begin(), requiredNamespaces_.end(), aNamespace );
	if ( found != requiredNamespaces_.end() ) {
		requiredNamespaces_.erase( found );
	}
}

void ComponentInfo::removeAllNamespaces()
{
	requiredNamespaces_.clear();
}


/**
$Id$
*/
