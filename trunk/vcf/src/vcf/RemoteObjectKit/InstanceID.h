#ifndef _VCF_INSTANCEID_H__
#define _VCF_INSTANCEID_H__
//InstanceID.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFRemote {

class REMOTEKIT_API InstanceID : public VCF::Object, public VCF::Persistable {

public:
	InstanceID();

	InstanceID( const int& memAddress );

	InstanceID( const VCF::String& machineName, const int& processID,
		        const int& threadID, const int& memAddress );

	virtual ~InstanceID(){};

	virtual VCF::String toString(){
		return 	machineName_ + "." + VCF::StringUtils::toString(processID_) + "." +
			    VCF::StringUtils::toString(threadID_) + "@" +
				VCF::StringUtils::toString(memAddress_);
	}

	VCF::String getMachinName() {
		return machineName_;
	}

	void setMachineName( const VCF::String& machineName ) {
		machineName_ = machineName;
	}

	int getProcessID() {
		return processID_;
	}

	void setProcessID( const int& processID ) {
		processID_ = processID;
	}

	int getThreadID() {
		return processID_;
	}

	void setThreadID( const int& threadID ) {
		threadID_ = threadID;
	}

	int getMemAddress() {
		return memAddress_;
	}

	void setMemAddress( const int& memAddress ) {
		memAddress_ = memAddress;
	}

	virtual void saveToStream( VCF::OutputStream * stream );

	virtual void loadFromStream( VCF::InputStream * stream );
private:
	VCF::String machineName_;
	VCF::uint32 IPAddress_;
    int processID_;
    int threadID_;
    int memAddress_;
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
*Revision 1.8.4.1  2004/04/26 21:58:46  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.1  2003/08/23 11:16:18  marcelloptr
*forgotten namespace in front of StringUtils
*
*Revision 1.7  2003/05/17 20:37:16  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.1  2003/03/12 03:11:48  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:42  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.14.1  2003/01/08 00:19:48  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.5  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.4  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_INSTANCEID_H__


