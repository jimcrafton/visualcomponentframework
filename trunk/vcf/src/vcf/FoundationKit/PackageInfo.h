#ifndef _VCF_PACKAGEINFO_H__
#define _VCF_PACKAGEINFO_H__
//PackageInfo.h

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
\class PackageInfo PackageInfo.h "vcf/FoundationKit/PackageInfo.h"
This class provides extra information specifically for 
shared or static libraries.
*/
class FOUNDATIONKIT_API PackageInfo : public ProgramInfo {
public:

	enum LinkageFlags{
		lfStaticLibLinkage = 0x01,
		lfSharedLibLinkage = 0x02
	};


	/**
	Creates a PackageInfo object,
	first five arguments are <i>required</i>.
	*/
	PackageInfo( const String& packageName, const String& packageUUID,
					const String& staticLibName, const String& sharedLibName,
					int32 linkageFlags,
					const String& author="", const String& company="",
					const String& copyright="", const String& additionalInfo="");


	/**
	returns the name of the package (VPL)
	*/
	String getPackageName() {
		return getProgramName();
	}

	/**
	returns the package UUID, that is, the unique string id for the package.
	*/
	String getPackageUUID() {
		return packageUUID_;
	}

	/**
	*any additional information that can be rendered as text.
	*/
	String getAdditionalInfo() {
		return additionalInfo_;
	}

	String getStaticLibName() {
		return staticLibName_;
	}

	String getSharedLibName() {
		return sharedLibName_;
	}

	Enumerator<String>* getRequiredStaticLibs();

	void addRequiredStaticLib( const String& libName );

	void removeRequiredStaticLib( const String& libName );

	void removeAllRequiredStaticLibs();

	Enumerator<String>* getRequiredSharedLibs();

	void addRequiredSharedLib( const String& libName );

	void removeRequiredSharedLib( const String& libName );

	void removeAllRequiredSharedLibs();

	bool allowsStaticLinkage() {
		return (linkageFlags_ & PackageInfo::lfStaticLibLinkage) ? true : false;
	}

	bool allowsSharedLinkage() {
		return (linkageFlags_ & PackageInfo::lfSharedLibLinkage) ? true : false;
	}

	Enumerator<String>* getSupportedPlatforms();

	void addSupportedPlatform( const String& platform );

	void removeSupportedPlatform( const String& platform );

	void removeAllSupportedPlatforms();

protected:	
	String packageUUID_;
	
	String additionalInfo_;
	String staticLibName_;
	String sharedLibName_;
	int32 linkageFlags_;

	std::vector<String> requiredStaticLibs_;
	EnumeratorContainer<std::vector<String>,String> reqStaticLibsContainer_;

	std::vector<String> requiredSharedLibs_;
	EnumeratorContainer<std::vector<String>,String> reqSharedLibsContainer_;

	std::vector<String> supportedPlatforms_;
	EnumeratorContainer<std::vector<String>,String> supportedPlatformsContainer_;
};




class FOUNDATIONKIT_API PackageManager {
public:
	static void init();
	static void terminate();

	static Enumerator<PackageInfo*>* getPackages();

	static void registerPackage( PackageInfo* package );

	static void removePackage( PackageInfo* package );

	static PackageManager* getPackageManager();
private:
	PackageManager();
	~PackageManager();

	static PackageManager* pkgMgrInstance;

	std::vector<VCF::PackageInfo*> packages_;
	VCF::EnumeratorContainer<std::vector<VCF::PackageInfo*>,VCF::PackageInfo*> packagesContainer_;

};


};


#endif // _VCF_PACKAGEINFO_H__

/**
$Id$
*/
