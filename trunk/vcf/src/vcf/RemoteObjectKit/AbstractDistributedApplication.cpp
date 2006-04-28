//AbstractDistributedApplication.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//AbstractDistributedApplication.h

#include "vcf/RemoteObjectKit/RemoteObjectKit.h"

using namespace VCF;
using namespace VCFNet;
using namespace VCFRemote;

String defaultUsageString = "To register or unregister this application's classes, please use the -register or -unregister arguments";


DistributedApplication* DistributedApplication::runningDistributedApp = NULL;

void DistributedApplication::distributedAppMain( const int& argc, VCF::VCFChar** argv )
{
	DistributedApplication* app = DistributedApplication::getRunningDistributedApp();

	if ( NULL != app ) {
		std::vector<String> commandLine;
		for (int i=0;i<argc;i++) {
			commandLine.push_back( String(argv[i]) );
		}

		app->processCommandLine( commandLine );

		if ( true == app->initApplication() ){
			app->notifyDistributedClassServer( true );

			app->runDistributedApp(); //execute main app code

			app->notifyDistributedClassServer( false );
		}
		else { //something went wrong - try and clean up
			app->terminateAppplication();
		}
	}
	else {
		//throw exception
	}
}

DistributedApplication* DistributedApplication::getRunningDistributedApp()
{
	return DistributedApplication::runningDistributedApp;
}

AbstractDistributedApplication::AbstractDistributedApplication()
{
	DistributedApplication::runningDistributedApp = this;

	unMarshalledArgTypes_["i"] = pdInt;
	unMarshalledArgTypes_["+i"] = pdUInt;
	unMarshalledArgTypes_["l"] = pdLong;
	unMarshalledArgTypes_["+l"] = pdULong;
	unMarshalledArgTypes_["+h"] = pdUShort;
	unMarshalledArgTypes_["h"] = pdShort;
	unMarshalledArgTypes_["c"] = pdChar;
	unMarshalledArgTypes_["d"] = pdDouble;
	unMarshalledArgTypes_["f"] = pdFloat;
	unMarshalledArgTypes_["b"] = pdBool;
	unMarshalledArgTypes_["s"] = pdString;
	unMarshalledArgTypes_["o"] = pdObject;

	instObjectContainer_.initContainer( instObjectList_ );

	appInfo_ = new AppInfo( this );
	Process p;
	appInfo_->setExecutableName( p.getName() );

	sock_.setPort( CLASS_SERVER_PORT );
	sock_.setHost( LOCAL_CLASS_SERVER );
	sock_.setAsServer( false );

	listener_ = new DistributedAppListener(this);

	onDataReceivedHandler_ =
		new SocketEventHandler<DistributedAppListener>( listener_, &DistributedAppListener::onDataReceived );

	onClientConnectedHandler_ =
		new SocketEventHandler<DistributedAppListener>( listener_, &DistributedAppListener::onClientConnected );

	onClientDisconnectedHandler_ =
		new SocketEventHandler<DistributedAppListener>( listener_, &DistributedAppListener::onClientDisconnected );


	sock_.DataReceived.addHandler( onDataReceivedHandler_ );
	sock_.ClientConnected.addHandler( onClientConnectedHandler_ );
	sock_.ClientDisconnected.addHandler( onClientDisconnectedHandler_ );

	sock_.setListeningLoop( new SocketListeningLoop(&sock_) );

	sock_.startListening();
}

AbstractDistributedApplication::~AbstractDistributedApplication()
{
	sock_.stopListening();

	sock_.DataReceived.removeHandler( onDataReceivedHandler_ );
	sock_.ClientConnected.removeHandler( onClientConnectedHandler_ );
	sock_.ClientDisconnected.removeHandler( onClientDisconnectedHandler_ );

	delete listener_;

	DistributedApplication::runningDistributedApp = NULL;
	delete appInfo_;
	appInfo_ = NULL;
}

bool AbstractDistributedApplication::initApplication()
{
	bool result = true;

	return result;
}

void AbstractDistributedApplication::processCommandLine( std::vector<VCF::String>& commandLine )
{
	std::vector<VCF::String>::iterator it = commandLine.begin();
	while ( it != commandLine.end() ) {
		processCommandLineArgument( *it );
		it ++;
	}
}

void AbstractDistributedApplication::processCommandLineArgument( const VCF::String arg )
{
	if ( arg == REGISTER_ARGUMENT ) {
		registerClasses();
	}
	else if ( arg == UNREGISTER_ARGUMENT ) {
		unRegisterClasses();
	}
}

void AbstractDistributedApplication::terminateAppplication()
{

}

bool AbstractDistributedApplication::registerClasses()
{
	bool result = false;

	return result;
}

bool AbstractDistributedApplication::unRegisterClasses()
{
	bool result = false;

	return result;
}

String AbstractDistributedApplication::getUsageString()
{
	String result = defaultUsageString;

	return result;
}

void AbstractDistributedApplication::onDataReceived( VCFNet::SocketEvent* event )
{
	BasicInputStream bis( event->getSocketData(), event->getDataSize() );
	int msgType = 0;
	bis >> msgType;

	//System::print( "AbstractDistributedApplication::onDataReceived\n");
	switch ( msgType ) {
		case DISTRIB_APP_MSG_NEW_INST : {
			String classID;
			bis >> classID;

			Object* obj = NULL;

			obj = ClassRegistry::createNewInstanceFromClassID( classID );
			if ( NULL != obj ) {
				Socket* sock = event->getSender();

				Proxy* proxy = new Proxy();
				proxy->getInstanceID()->setMemAddress( (int)obj );
				instObjectList_[(int)obj] = obj;

				BasicOutputStream bos;
				int msg = CLASS_SVR_MSG_NEW_PROXY;
				bos << msg;
				bos << classID;
				bos << proxy;

				sock->send( bos.getBuffer(), bos.getSize() );
			}
		}
		break;

		case CLASS_SVR_MSG_PROXY_INVOKE : {
			//System::print( "Client App received invoke\n" );
			Proxy dummyProxy;
			bis >> static_cast<Persistable*>(&dummyProxy);
			String methodName;
			bis >> methodName;
			int argCount = 0;
			bis >> argCount;
			std::vector<VariantData*> argList;
			for (int i=0;i<argCount;i++){
				String argID;
				bis >> argID;
				std::map<VCF::String,int>::iterator found =
					unMarshalledArgTypes_.find(argID);
				if ( found != unMarshalledArgTypes_.end() ) {
					VariantData* arg = new VariantData();
					switch ( found->second ) {
						case pdInt : {
							int tmp;
							bis >> tmp;
							*arg = tmp;
						}
						break;
					}
					argList.push_back( arg );
				}
			}

#if (defined(__BORLANDC__) && (__BORLANDC__ < 0x0581)) || (defined(_MSC_VER) && (_MSC_VER < 1300)) || defined(STLPORT)
			VariantData** methodArgs = (VariantData**)argList.begin();
#else
			VariantData** methodArgs = (VariantData**)argList.begin().operator->();
#endif
			std::map<int,VCF::Object*>::iterator found =
				instObjectList_.find( dummyProxy.getInstanceID()->getMemAddress() );
			if ( found != instObjectList_.end() ) {
				Object* obj = found->second;
				Class* clazz = obj->getClass();
				Method* method = clazz->getMethod( methodName );
				if ( NULL != method ) {
					//System::print( "Client App found requested method, preparing to invoke...\n" );
					VariantData* result = method->invoke( methodArgs );

					Socket* sock = event->getSender();
					BasicOutputStream bos;
					VariantDataOutputStream vdos( &bos );
					int msg = CLASS_SVR_MSG_PROXY_INVOKE_RETURNED;
					vdos << msg;
					vdos << &dummyProxy;
					vdos << methodName;
					if ( NULL != result ) {
						vdos.writeVariantData( result );
					}
					else {
						vdos << String("NULL");
					}
					sock->send( vdos.getBuffer(), vdos.getSize() );
				}
			}
		}
		break;
	}
}

void AbstractDistributedApplication::onClientConnected( VCFNet::SocketEvent* event )
{

}

void AbstractDistributedApplication::onClientDisconnected( VCFNet::SocketEvent* event )
{

}

void AbstractDistributedApplication::runDistributedApp()
{
	while ( true ) {
		System::sleep( 50 );
	}
}

bool AbstractDistributedApplication::notifyDistributedClassServer( const bool& startup )
{
	bool result = false;

	if ( true == startup ) {
		BasicOutputStream bos;
		int msg = CLASS_SVR_DISTRIB_APP_STARTED;
		bos << msg;
		bos << appInfo_;
		sock_.send( bos.getBuffer(), bos.getSize() );
	}
	else {
		BasicOutputStream bos;
		int msg = CLASS_SVR_DISTRIB_APP_EXITED;
		bos << msg;
		bos << appInfo_;
		sock_.send( bos.getBuffer(), bos.getSize() );
	}
	return result;
}


Enumerator<Object*>* AbstractDistributedApplication::getInstantiatedObjects()
{
	return instObjectContainer_.getEnumerator();
}

/**
*Appinfo class implmentation
*/
AppInfo::AppInfo( DistributedApplication* distributedApp )
{
	distributedApp_ = distributedApp;
}

AppInfo::~AppInfo()
{

}

void AppInfo::saveToStream( OutputStream * stream )
{
	stream->write( appName_ );
}

void AppInfo::loadFromStream( InputStream * stream )
{
	stream->read( appName_ );
}


/**
$Id$
*/
