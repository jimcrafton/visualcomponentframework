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

private:
	static std::map<String,LibraryApplication*>* namedLibraryAppMap;
	static EnumeratorMapContainer<std::map<String,LibraryApplication*>, LibraryApplication*>* namedLibAppContainer;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.6.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.6  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.5.26.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.5.26.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.5  2002/03/01 05:11:24  ddiego
*added some methods for saving an applications state and doing so
*automatically if the developer wants
*
*Revision 1.4  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_LIBRARYAPPLICATION_H__


