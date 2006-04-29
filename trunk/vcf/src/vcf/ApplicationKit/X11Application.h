#ifndef _VCF_X11APPLICATION_H__
#define _VCF_X11APPLICATION_H__
//X11Application.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**

*/
class X11Application : public Object, public ApplicationPeer  {
public:
	X11Application();

	virtual ~X11Application();

	virtual bool initApp( const std::vector<VCF::String>& appCmdLine );

	virtual void terminateApp();

	virtual VCF::AbstractApplication* getApplication() {
		return app_;
	}

	virtual void setApplication( VCF::AbstractApplication* application );

	virtual ResourceBundle* getResourceBundle();

	virtual String getFileName();

	virtual String getCurrentDirectory();

	virtual void setCurrentDirectory( const String& currentDirectory );

	virtual long getHandleID();

	virtual void setHandleID( const long& handleID );
protected:
	VCF::AbstractApplication* app_;
	long handleID_;
};

}; //end of namespace VCF


#endif // _VCF_X11APPLICATION_H__

/**
$Id$
*/
