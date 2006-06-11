#ifndef _VCF_XCBAPPLICATIONPEER_H__
#define _VCF_XCBAPPLICATIONPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF
{

class XCBApplicationPeer : public ApplicationPeer {
public:

	virtual bool initApp();

	virtual void terminateApp();

	virtual AbstractApplication* getApplication();

	virtual void setApplication( AbstractApplication* application );

	virtual String getFileName();

	virtual OSHandleID getHandleID();

	virtual void setHandleID( OSHandleID handleID );

};

};

#endif // _VCF_XCBAPPLICATIONPEER_H__

/**
$Id$
*/

