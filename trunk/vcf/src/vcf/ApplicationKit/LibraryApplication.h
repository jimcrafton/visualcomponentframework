#ifndef _VCF_LIBRARYAPPLICATION_H__
#define _VCF_LIBRARYAPPLICATION_H__
//LibraryApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif








namespace VCF  {

/**
\class LibraryApplication LibraryApplication.h "vcf/ApplicationKit/LibraryApplication.h"
*Class LibraryApplication documentation
*/
class APPLICATIONKIT_API LibraryApplication : public AbstractApplication {
public:
	LibraryApplication();

	virtual ~LibraryApplication();

	virtual bool initRunningApplication(){
		return true;
	}

	virtual void terminateRunningApplication(){};

	virtual void setName( const String& name );

	virtual GraphicsResourceBundle* getResourceBundle();


	static GraphicsResourceBundle* getResourceBundle( const String& libName );
	/**
	*returns the library's resource bundle, which
	*contains all the library's resources, such as
	*images, strings, or form files, or other custom
	*data.
	*@return GraphicsResourceBundle* the library's resource bundle
	*@see GraphicsResourceBundle
	*/
	//GraphicsResourceBundle* getResourceBundle();

	/**
	*gets a collection of named libraries that have been registered
	*/
	static Enumerator<LibraryApplication*>* getRegisteredLibraries();

	static void registerLibrary( LibraryApplication* libraryApp );

	static void unRegisterLibrary( LibraryApplication* libraryApp );

	static LibraryApplication* getRegisteredLibraryApplication( const String& libName );

	static void load( LibraryApplication* libraryApp );

	static void unload( LibraryApplication* libraryApp );

	static void initLibraryRegistrar();

	static void clearLibraryRegistrar();
protected:
	
	GraphicsResourceBundle* resourceBundle_;
	static Map<String,LibraryApplication*> namedLibraryAppMap;
};


}; //end of namespace VCF


#endif // _VCF_LIBRARYAPPLICATION_H__

/**
$Id$
*/
