#ifndef _VCF_LINUXLIBRARYPEER_H__
#define _VCF_LINUXLIBRARYPEER_H__ 
//LinuxLibraryPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class LinuxLibraryPeer : public LibraryPeer
{

public:
	LinuxLibraryPeer();

	virtual ~LinuxLibraryPeer();

	virtual void load( const String& libraryFilename );

	virtual void* getFunction( const String& functionName );

	virtual void unload();

    virtual OSHandleID getHandleID();

protected:
	void* libHandle_;
};

} //end of namespace VCF


#endif // _VCF_LINUXLIBRARYPEER_H__

/**
$Id$
*/
