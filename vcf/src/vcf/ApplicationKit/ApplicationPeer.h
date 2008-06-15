#ifndef _VCF_APPLICATIONPEER_H__
#define _VCF_APPLICATIONPEER_H__
//ApplicationPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class AbstractApplication;

class ResourceBundle;

/**

\class ApplicationPeer ApplicationPeer.h "vcf/ApplicationKit/ApplicationPeer.h"
*System neutral interface describing an application.
*
*@version 1.0
@author Jim Crafton
*/
class APPLICATIONKIT_API ApplicationPeer : Interface{
public:
	virtual ~ApplicationPeer(){};

	/**
	*initializes the application Peer. Any window specific system stuff can
	*go in the implementation here.
	*/
	virtual bool initApp()=0;

	/**
	*terminates the application Peer
	*/
	virtual void terminateApp() = 0;

	/**
	*get the Application instance associated with the
	*application implmenter
	*/
	virtual AbstractApplication* getApplication() = 0;

	/**
	*set the Application instance ot be associated with the
	*application implmenter
	*/
	virtual void setApplication( AbstractApplication* application ) = 0;	

	/**
	*returns the fully qualified file name
	*for the application, i.e. "C:\Stuff\My App\Foo.exe"
	*/
	virtual String getFileName() = 0;

	/**
	*returns an identifier that is specific to the OS that uniquely identifies this
	*Application. Under Win32 this corresponds to the hInstance that is used in
	*an application or in-process DLL.
	*/
	virtual OSHandleID getHandleID()  = 0;

	virtual void setHandleID( OSHandleID handleID ) = 0;	
	
	/**
	Indicates that the application peer should do the rest of 
	the clean up. Used on OSX.
	*/
	virtual bool shouldPerformCleanup() = 0;
};


};


#endif // _VCF_APPLICATIONPEER_H__

/**
$Id$
*/
