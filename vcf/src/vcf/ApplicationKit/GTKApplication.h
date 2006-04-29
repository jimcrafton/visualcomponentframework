#ifndef _VCF_GTKAPPLICATION_H__
#define _VCF_GTKAPPLICATION_H__
//GTKApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF {

/**

*/
class GTKApplication : public Object, public ApplicationPeer  {
public:
	GTKApplication();

	virtual ~GTKApplication();

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
	long handleID_;
};

}; //end of namespace VCF


#endif // _VCF_GTKAPPLICATION_H__

/**
$Id$
*/
