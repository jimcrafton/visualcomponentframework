#ifndef _VCF_ABSTRACTDISTRIBUTEDAPPLICATION_H__
#define _VCF_ABSTRACTDISTRIBUTEDAPPLICATION_H__
//AbstractDistributedApplication.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define REGISTER_ARGUMENT			"-register"
#define UNREGISTER_ARGUMENT			"-unregister"

namespace VCFRemote  {

/**
*Interface for distributed applications
*also provides a statice method for the main entry
*point into a distributed app. This is implemented and must not
*be overridden
*/
class REMOTEKIT_API DistributedApplication {
public:
	virtual ~DistributedApplication(){};

	/**
	*Allows you to initialize your application's data.
	*This gets called after the processCommandLine
	*@return bool return false to indicate the initialization
	*routines failed - the app will then attempt to close down
	*nicely by calling terminateAppplication(), and then exiting.
	*/
	virtual bool initApplication() = 0;

	/**
	*notifies the Distributed Class Server we are starting up
	*or shutting down, depending on the value of startup
	*@param bool startup - true, we are starting up, false, we are
	*shutting down
	*/
	virtual bool notifyDistributedClassServer( const bool& startup ) = 0;

	virtual void processCommandLine( std::vector<VCF::String>& commandLine ) = 0;

	/**
	*this is where the app terminates. Do pre-destructor clean up here
	*/
	virtual void terminateAppplication() = 0;

	/**
	*register all classes with the Distributed CLass Server here
	*/
	virtual bool registerClasses() = 0;

	/**
	*unregister all classes with the Distributed CLass Server here
	*/
	virtual bool unRegisterClasses() = 0;

	virtual VCF::String getUsageString() = 0;

	/**
	*the apps main execution point. Any code you would have put in your
	*main(...) function, you should put in here
	*/
	virtual void runDistributedApp() = 0;

	virtual VCF::Enumerator<VCF::Object*>* getInstantiatedObjects() = 0;

	static void distributedAppMain( const int& argc, VCF::VCFChar** argv );

	static DistributedApplication* getRunningDistributedApp();
protected:
	static DistributedApplication* runningDistributedApp;
};

/**
*A small object that can be passed around from app to app
*that includes information about the app. Inforamtion
*currently included is the name of the app executable.
*There is also a pointer to a DistributedApplication for
*future used. If this is NULL, that means the AppInfo object
*was "reconstituted" from a stream somewhere outside of
*the application process that it represents
*/
class REMOTEKIT_API AppInfo: public VCF::Object, public VCF::Persistable {
public:
	AppInfo( DistributedApplication* distributedApp = NULL );

	virtual ~AppInfo();

	virtual void saveToStream( VCF::OutputStream * stream );

	virtual void loadFromStream( VCF::InputStream * stream );

	void setExecutableName( const VCF::String& name ) {
		appName_ = name;
	}

	VCF::String getExecutableName() {
		return appName_;
	}
private:
	VCF::String appName_;
	DistributedApplication* distributedApp_;
};

/**
*Class AbstractDistributedApplication documentation
*/
class REMOTEKIT_API AbstractDistributedApplication : public DistributedApplication{
public:

	class DistributedAppListener : public VCF::ObjectWithCallbacks {
	public:
		DistributedAppListener( AbstractDistributedApplication* distributedApp=NULL ){
			distributedApp_ = distributedApp;
		}

		virtual ~DistributedAppListener(){};

		virtual void onDataReceived( VCFNet::SocketEvent* event ){
			if ( NULL != distributedApp_ ) {
				distributedApp_->onDataReceived( event );
			}
		}

		virtual void onClientConnected( VCFNet::SocketEvent* event ){
			if ( NULL != distributedApp_ ) {
				distributedApp_->onClientConnected( event );
			}
		}

		virtual void onClientDisconnected( VCFNet::SocketEvent* event ){
			if ( NULL != distributedApp_ ) {
				distributedApp_->onClientDisconnected( event );
			}
		}
	private:
		AbstractDistributedApplication* distributedApp_;
	};

	virtual ~AbstractDistributedApplication();

	virtual bool initApplication();

	virtual bool notifyDistributedClassServer( const bool& startup );

	/**
	*processes the command line. calls processCommandLineArgument()
	*for each arument in the commandLine
	*/
	virtual void processCommandLine( std::vector<VCF::String>& commandLine );

	/**
	*processes a command line argument. The default implementation searches for
	*the presence of -register or -unregister in the arg and
	*calls the registerClasses() or unRegisterClasses() accordingly.
	*/
	virtual void processCommandLineArgument( const VCF::String arg );

	virtual VCF::Enumerator<VCF::Object*>* getInstantiatedObjects();

	virtual void terminateAppplication();

	virtual bool registerClasses();

	virtual bool unRegisterClasses();

	virtual VCF::String getUsageString();

	virtual void runDistributedApp();

	virtual void onDataReceived( VCFNet::SocketEvent* event );

	virtual void onClientConnected( VCFNet::SocketEvent* event );

	virtual void onClientDisconnected( VCFNet::SocketEvent* event );
protected:
	/**
	*protected constructor to prevent instantiation outside
	*of a deriving class
	*/
	AbstractDistributedApplication();

	VCFNet::Socket sock_;

	AppInfo* appInfo_;
	std::map<int,VCF::Object*> instObjectList_; //keyed by mem address
	std::map<VCF::String,int> unMarshalledArgTypes_;
	VCF::EnumeratorMapContainer<std::map<int,VCF::Object*>,VCF::Object*> instObjectContainer_;
private:
	VCF::CallBack* onDataReceivedHandler_;
	VCF::CallBack* onClientConnectedHandler_;
	VCF::CallBack* onClientDisconnectedHandler_;
	DistributedAppListener* listener_;
};



}; //end of namespace VCFRemote


#endif // _VCF_ABSTRACTDISTRIBUTEDAPPLICATION_H__

/**
$Id$
*/
