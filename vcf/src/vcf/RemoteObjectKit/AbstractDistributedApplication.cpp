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
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:51  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.3  2006/02/23 01:41:58  ddiego
*some minor changes to teh variantdata class, added support for specific char* and WideChar* cosntructor and for unsigned short types.
*
*Revision 1.2.6.2  2006/01/02 13:26:14  kiklop74
*Fixed compilation issue with BDS 2006
*
*Revision 1.2.6.1  2005/11/02 04:38:23  obirsoy
*changes required for vc80 support.
*
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:31:55  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.16  2004/04/03 15:48:49  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.14.4.1  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.15  2004/02/16 20:38:17  ddiego
*applied patch from Bobby Ward for further fixes for VC71 compiling
*
*Revision 1.14  2003/08/09 02:56:46  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.13  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.2  2003/03/23 04:06:34  marcelloptr
*minor fixes
*
*Revision 1.12.2.1  2003/03/12 03:13:31  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.8.1  2003/01/08 00:20:03  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.11  2002/09/12 03:26:07  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.10.6.1  2002/07/02 05:35:11  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.10  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.9  2002/02/28 05:08:34  ddiego
*added tests for remote objects, plus another subtle fix for BasicInputStream
*for seek positioning
*
*Revision 1.8  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


