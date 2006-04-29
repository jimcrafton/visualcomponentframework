#ifndef _VCF_WIN32LIBRARYPEER_H__
#define _VCF_WIN32LIBRARYPEER_H__
//Win32LibraryPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class Win32LibraryPeer : public LibraryPeer{

public:
	Win32LibraryPeer();

	virtual ~Win32LibraryPeer();

	virtual void load( const String& libraryFilename );

	virtual void* getFunction( const String& functionName );

	virtual void unload();

	virtual OSHandleID getHandleID() {
		return (OSHandleID) libHandle_;
	}

private:
	HMODULE libHandle_;

};

}; //end of namespace VCF


#endif // _VCF_WIN32LIBRARYPEER_H__

/**
$Id$
*/
