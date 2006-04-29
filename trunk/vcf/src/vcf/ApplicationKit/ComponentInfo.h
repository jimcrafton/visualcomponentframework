#ifndef _VCF_COMPONENTINFO_H__
#define _VCF_COMPONENTINFO_H__
//ComponentInfo.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Image;

/**
*ComponentInfo represents special data regarding a component's class.
*This information is generally used by development tools to aid in things
*like autogenerating code, for example.
*/
class APPLICATIONKIT_API ComponentInfo : public Object {
public :
	ComponentInfo( const String& componentUUID, const String& author="", const String& company="",
					const String& copyright="", const String& additionalInfo="",
					const String& packageName="", const String& packageUUID="",
					Image* componentImage=NULL );

	virtual ~ComponentInfo();

	/**
	*The name of the author of the component class
	*/
	String getAuthor() {
		return author_;
	}

	/**
	*the copyright, if any, for the components source code
	*/
	String getCopyright() {
		return copyright_;
	}

	/**
	*The name of the company responsible for the component
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

	/**
	*the UUID that represents the corresponding component class.
	*This UUID is guaranteed to be able to create a valid instance
	*of the component at runtime.
	*/
	String getComponentUUID() {
		return componentUUID_;
	}

	/**
	returns the name of the package (VPL) that this component belongs to
	*/
	String getPackageName() {
		return packageName_;
	}

	/**
	returns the package UUID, that is, the unique string id for the package
	that this component belongs to. The package anme and package UUID
	<b>must</b> refer to the same package!
	*/
	String getPackageUUID() {
		return packageUUID_;
	}

	/**
	*an image that represents the component. This image must have
	*dimensions of 25 pixels wide by 25 pixel high.
	*@return Image a pointer to the image representing the component. May
	*be NULL if no image exists. In this case a default image will be used.
	*/
	Image* getComponentImage() {
		return componentImage_;
	}

	/**
	*returns an enumeration of all the headers
	*that are required to successfully compile an implementation file
	*that uses this component.
	*/
	Enumerator<String>* getRequiredHeaders();

	/**
	*returns an enumeration of all the C++ namespaces
	*that are required to successfully compile an implementation file
	*that uses this component.
	*/
	Enumerator<String>* getRequiredNamespaces();

	void addHeader( const String& header );

	void removeHeader( const String& header );

	void removeAllHeaders();

	void addNamespace( const String& aNamespace );

	void removeNamespace( const String& aNamespace );

	void removeAllNamespaces();


protected:
	String author_;
	String copyright_;
	String company_;
	String additionalInfo_;
	String componentUUID_;
	String packageName_;
	String packageUUID_;
	Image* componentImage_;


	std::vector<String> requiredHeaders_;
	EnumeratorContainer<std::vector<String>,String> reqHeadersContainer_;

	std::vector<String> requiredNamespaces_;
	EnumeratorContainer<std::vector<String>,String> reqNamespacesContainer_;
};


};


#endif // _VCF_COMPONENTINFO_H__

/**
$Id$
*/
