#ifndef _VCF_OSXLIBRARYPEER_H__
#define _VCF_OSXLIBRARYPEER_H__
//OSXLibraryPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

class OSXLibraryPeer : public LibraryPeer {

public:
	OSXLibraryPeer();

	virtual ~OSXLibraryPeer();

	virtual void load( const String& libraryFilename );

	virtual void* getFunction( const String& functionName );

	virtual void unload();

	virtual OSHandleID getHandleID();
protected:
	/**
	This is either a pointer that dlopen() returned
	or a CFBundleRef
	*/
	void* libHandle_;
	bool handleIsBundle_; 

};

}; //end of namespace VCF


#endif // _VCF_OSXLIBRARYPEER_H__

/**
$Id$
*/
