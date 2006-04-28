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


#endif // _VCF_INSTANCEID_H__

/**
$Id$
*/
