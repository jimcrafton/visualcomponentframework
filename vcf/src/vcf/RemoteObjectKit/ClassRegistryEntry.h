#ifndef _VCF_CLASSREGISTRYENTRY_H__
#define _VCF_CLASSREGISTRYENTRY_H__
//ClassRegistryEntry.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFRemote  {

/**
*A Class Registry entry contains the neccessary information to create a class
*from a server, either locally (more often than not), or remotely, if the
*remote class has been cached for faster lookup.
*/
class REMOTEKIT_API ClassRegistryEntry : public VCF::Object, public VCF::Persistable {
public:
	ClassRegistryEntry();

	ClassRegistryEntry( const VCF::String& classID,
		                const VCF::String& userID,
						const VCF::String& localServerPath,
						const bool& inProcess,
						const bool& remote,
						const VCF::String& remoteServerPath );

	virtual ~ClassRegistryEntry();

	/**
     * returns the string value of the UUID that associates the entry
	 *with a particular class
     */
	VCF::String getClassID() {
		return classID_;
	}

	/**
     * the user ID is a short hand for the ClassID, such as "MyApp.Foo"
     */
	VCF::String getUserID() {
		return userID_;
	}

	/**
     * the fully qualified file name to the local server for the class.
     */
	VCF::String getLocalServerPath() {
		return localServerPath_;
	}

	/**
     * is the server in process, i.e. a DLL or SO, as opposed to a
	 *self executing file.
     */
	bool isInProcess() {
		return inProcess_;
	}

	/**
     * is the server remote. False by default. A remote server is a
	 *server whose executable code resides a another machine.
     */
	bool isRemote() {
		return isRemote_;
	}

	/**
     * a fully qualified URL that describes the name of a machine
	 *(or IP address ?) and the path to the server on that machine.
	 *This is only valid if the isRemote_ member is true, which
	 *automatically means inProcess_ is false.
     */
	VCF::String getRemoteServerPath()  {
		return remoteServerPath_;
	}

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( VCF::OutputStream * stream );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( VCF::InputStream * stream );

	virtual VCF::String toString();
protected:

private:
	/**
     * this member variable represents the string value of the UUID
	 *that associates the entry with a particular class
     */
	VCF::String classID_;
	/**
     * the user ID is a short hand for the ClassID, such as "MyApp.Foo"
     */
    VCF::String userID_;

    /**
     * the fully qualified file name to the local server for the class.
     */
    VCF::String localServerPath_;

    /**
     * is the server in process, i.e. a DLL or SO, as opposed to a self
	 *executing file.
     */
    bool inProcess_;

    /**
     * is the server remote. False by default
     */
    bool isRemote_;

    /**
     * a fully qualified URL that describes the name of a machine (or IP address ?)
	 *and the path to the server on that machine. This is only valid if the
	 *isRemote_ member is true, which automatically means inProcess_ is false.
     */
    VCF::String remoteServerPath_;
};


}; //end of namespace VCFRemote


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.5.8.1  2004/04/26 21:58:46  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/05/17 20:37:16  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.4.16.1  2003/03/12 03:11:48  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.4  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.3  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_CLASSREGISTRYENTRY_H__


