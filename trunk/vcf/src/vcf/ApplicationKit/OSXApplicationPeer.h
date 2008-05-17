#ifndef _VCF_OSXAPPLICATIONPEER_H__
#define _VCF_OSXAPPLICATIONPEER_H__
//OSXApplicationPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

/**

*/
class OSXApplicationPeer : public Object, public ApplicationPeer  {
public:
	OSXApplicationPeer();

	virtual ~OSXApplicationPeer();

	virtual bool initApp();

	virtual void terminateApp();

	virtual VCF::AbstractApplication* getApplication() {
		return app_;
	}

	virtual void setApplication( VCF::AbstractApplication* application );

	virtual ResourceBundle* getResourceBundle();

	virtual String getFileName();

	virtual OSHandleID getHandleID();

	virtual void setHandleID( OSHandleID handleID );
protected:
	VCF::AbstractApplication* app_;
	NSApplication* appInstance_;
};

}; //end of namespace VCF


#endif // _VCF_OSXAPPLICATIONPEER_H__

/**
$Id$
*/
