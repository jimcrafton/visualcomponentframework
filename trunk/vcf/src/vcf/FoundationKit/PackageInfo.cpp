//PackageInfo.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;

PackageInfo::PackageInfo( const String& packageName, const String& packageUUID,
							const String& staticLibName, const String& sharedLibName,
							int32 linkageFlags,
							const String& author, const String& company,
							const String& copyright, const String& additionalInfo):
	ProgramInfo(packageName,"",author,copyright,company,additionalInfo,"","","","")
{	
	packageUUID_ = packageUUID;	
	additionalInfo_ = additionalInfo;
	staticLibName_ = staticLibName;
	sharedLibName_ = sharedLibName;
	linkageFlags_ = linkageFlags;
}

Enumerator<String>* PackageInfo::getRequiredStaticLibs()
{
	return requiredStaticLibs_.getEnumerator();
}

void PackageInfo::addRequiredStaticLib( const String& libName )
{
	requiredStaticLibs_.push_back( libName );
}

void PackageInfo::removeRequiredStaticLib( const String& libName )
{
	std::vector<String>::iterator found =
		std::find( requiredStaticLibs_.begin(), requiredStaticLibs_.end(), libName );
	if ( found != requiredStaticLibs_.end() ) {
		requiredStaticLibs_.erase( found );
	}
}

void PackageInfo::removeAllRequiredStaticLibs()
{
	requiredStaticLibs_.clear();
}

Enumerator<String>* PackageInfo::getRequiredSharedLibs()
{
	return requiredSharedLibs_.getEnumerator();
}

void PackageInfo::addRequiredSharedLib( const String& libName )
{
	requiredSharedLibs_.push_back( libName );
}

void PackageInfo::removeRequiredSharedLib( const String& libName )
{
	std::vector<String>::iterator found =
		std::find( requiredSharedLibs_.begin(), requiredSharedLibs_.end(), libName );
	if ( found != requiredSharedLibs_.end() ) {
		requiredSharedLibs_.erase( found );
	}
}

void PackageInfo::removeAllRequiredSharedLibs()
{
	requiredSharedLibs_.clear();
}

Enumerator<String>* PackageInfo::getSupportedPlatforms()
{
	return supportedPlatforms_.getEnumerator();
}

void PackageInfo::addSupportedPlatform( const String& platform )
{
	supportedPlatforms_.push_back( platform );
}

void PackageInfo::removeSupportedPlatform( const String& platform )
{
	std::vector<String>::iterator found =
		std::find( supportedPlatforms_.begin(), supportedPlatforms_.end(), platform );
	if ( found != supportedPlatforms_.end() ) {
		supportedPlatforms_.erase( found );
	}
}

void PackageInfo::removeAllSupportedPlatforms()
{
	supportedPlatforms_.clear();
}



PackageManager* PackageManager::pkgMgrInstance = NULL;


void PackageManager::init()
{
	PackageManager::pkgMgrInstance = new PackageManager();
}

void PackageManager::terminate()
{
	delete PackageManager::pkgMgrInstance;
}

Enumerator<PackageInfo*>* PackageManager::getPackages()
{
	return PackageManager::pkgMgrInstance->packages_.getEnumerator();
}

void PackageManager::registerPackage( PackageInfo* package )
{
	std::vector<PackageInfo*>::iterator found = 
		std::find( PackageManager::pkgMgrInstance->packages_.begin(), 
					PackageManager::pkgMgrInstance->packages_.end(), package );

	if ( found == PackageManager::pkgMgrInstance->packages_.end() ) {
		PackageManager::pkgMgrInstance->packages_.push_back( package );
	}
}

void PackageManager::removePackage( PackageInfo* package )
{
	std::vector<PackageInfo*>::iterator found = 
		std::find( PackageManager::pkgMgrInstance->packages_.begin(), 
					PackageManager::pkgMgrInstance->packages_.end(), package );

	if ( found != PackageManager::pkgMgrInstance->packages_.end() ) {
		delete *found;

		PackageManager::pkgMgrInstance->packages_.erase( found );		
	}
}

PackageManager* PackageManager::getPackageManager()
{
	return PackageManager::pkgMgrInstance;
}

PackageManager::PackageManager()
{
	
}

PackageManager::~PackageManager()
{
	std::vector<PackageInfo*>::iterator it = packages_.begin();
	while ( it != packages_.end() ) {
		delete *it;
		it ++;
	}
	packages_.clear();
}


/**
$Id$
*/
