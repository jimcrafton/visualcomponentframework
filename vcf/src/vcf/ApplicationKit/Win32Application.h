#ifndef _VCF_WIN32APPLICATION_H__
#define _VCF_WIN32APPLICATION_H__
//Win32Application.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Win32Application




namespace VCF
{

class Win32ResourceBundle;

class Win32Application : public Object, public ApplicationPeer
{
public:
	Win32Application();
	virtual ~Win32Application();

	virtual bool initApp();

	virtual void terminateApp();

	virtual VCF::AbstractApplication* getApplication();

	virtual void setApplication( VCF::AbstractApplication* application );

	virtual String getFileName();

	virtual OSHandleID getHandleID();

	virtual void setHandleID( OSHandleID handleID );	
private:
	VCF::AbstractApplication* app_;
	HINSTANCE instanceHandle_;
	Win32ResourceBundle* resBundle_;
};

};


#endif // _VCF_WIN32APPLICATION_H__

/**
$Id$
*/
