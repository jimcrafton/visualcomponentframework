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

class FOUNDATIONKIT_API PackageInfo : public Object {
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
					long linkageFlags,
					const String& author="", const String& company="",
					const String& copyright="", const String& additionalInfo="");


	/**
	returns the name of the package (VPL)
	*/
	String getPackageName() {
		return packageName_;
	}

	/**
	returns the package UUID, that is, the unique string id for the package.
	*/
	String getPackageUUID() {
		return packageUUID_;
	}

	/**
	*The name of the author of the package
	*/
	String getAuthor() {
		return author_;
	}

	/**
	*the copyright, if any, for the package
	*/
	String getCopyright() {
		return copyright_;
	}

	/**
	*The name of the company responsible for the package
	*/
	String getCompany() {
		return company_;
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
	String packageName_;
	String packageUUID_;
	String author_;
	String copyright_;
	String company_;
	String additionalInfo_;
	String staticLibName_;
	String sharedLibName_;
	long linkageFlags_;

	std::vector<String> requiredStaticLibs_;
	EnumeratorContainer<std::vector<String>,String> reqStaticLibsContainer_;

	std::vector<String> requiredSharedLibs_;
	EnumeratorContainer<std::vector<String>,String> reqSharedLibsContainer_;

	std::vector<String> supportedPlatforms_;
	EnumeratorContainer<std::vector<String>,String> supportedPlatformsContainer_;
};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.3.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.2.2.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.2.2.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.2  2003/08/09 02:56:42  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.1  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*/


#endif // _VCF_PACKAGEINFO_H__


