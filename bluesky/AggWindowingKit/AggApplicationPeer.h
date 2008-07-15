#ifndef _VCF_AGGAPPLICATIONPEER_H__
#define _VCF_AGGAPPLICATIONPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class AggApplicationPeer : public ApplicationPeer {
public:
    AggApplicationPeer();
    virtual ~AggApplicationPeer();

	virtual bool initApp();

	virtual void terminateApp();

	virtual AbstractApplication* getApplication();

	virtual void setApplication( AbstractApplication* application );

	virtual String getFileName();

	virtual OSHandleID getHandleID();

	virtual void setHandleID( OSHandleID handleID );

	virtual bool shouldPerformCleanup() {
		return false;
	}

protected:
    AbstractApplication* app_;
};

};

#endif // _VCF_AGGAPPLICATIONPEER_H__

/**
$Id$
*/

