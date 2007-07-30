//ClassServerInstance.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/RemoteObjectKit/RemoteObjectKit.h"

using namespace VCF;
using namespace VCFNet;
using namespace VCFRemote;

ClassServerInstance::ClassServerInstance()
{
	newInstanceProxy_ = NULL;

	CallBack* sh =
		new ClassProcedure1<SocketEvent*,ClassServerInstance>( this, &ClassServerInstance::onDataReceived, "SocketHandler" );

}

ClassServerInstance::~ClassServerInstance()
{

}

Proxy* ClassServerInstance::createInstance( const VCF::String& className )
{
	Proxy* result = NULL;
	newInstanceProxy_ = NULL;

	classSvrReturned_ = false;


	Object* newObjInstance = NULL;
	try {
		newObjInstance = ClassRegistry::createNewInstance( className );
	}
	catch ( BasicException& e ) {
		System::print( e.getMessage() );
	}


	if ( NULL != newObjInstance ) {
		result = new Proxy( newObjInstance );
	}
	else { //we have to look elsewhere, first on this machine, then on the network
		Socket sock( LOCAL_CLASS_SERVER, CLASS_SERVER_PORT );
		CallBack* socketHandler = getEventHandler( "SocketHandler" );
		sock.DataReceived.add( socketHandler );
		try {
			sock.setListeningLoop( new SocketListeningLoop(&sock) );

			sock.startListening();

			BasicOutputStream stream;

			int msgType = CLASS_SVR_MSG_NEW_INST;
			stream << msgType << className;
			sock.send( stream.getBuffer(), stream.getSize() );

			System::sleep( 20 );//HACK ALERT !!!! this seems to need to be here
			              //to let the threaded listener for the socket to
						  //get started perhaps there is a better way ?????


			sock.checkForPendingData( VCFNET_INFINITEWAIT );
			result = newInstanceProxy_;
			if ( result == NULL ) {
				//throw exception!!!
			}
		}
		catch( ... ) {

		}
	}

	return result;
}

Proxy* ClassServerInstance::createInstanceByClassID( const VCF::String& classID )
{
	Proxy* result = NULL;

	Object* newObjInstance = NULL;
	newObjInstance = ClassRegistry::createNewInstanceFromClassID( classID );

	if ( NULL != newObjInstance ) {
		result = new Proxy( newObjInstance );
	}
	else { //we have to look elsewhere, first on this machine, then on the network

	}

	return result;
}

void ClassServerInstance::onDataReceived( VCFNet::SocketEvent* event )
{
	this->classSvrReturned_ = true;
	data_ = event->getSocketData();
	printf( "ClassServerInstance::onDataReceived() Data received, size is %d bytes\n", event->getDataSize() );

	BasicInputStream bis(event->getSocketData(), event->getDataSize() );

	newInstanceProxy_ = NULL;
	int msgType = 0;
	bis >> msgType;
	switch ( msgType ) {
		case CLASS_SVR_MSG_NEW_PROXY : {
			String classID;
			bis >> classID;
			newInstanceProxy_ = new Proxy();
			bis >> static_cast<Persistable*>(newInstanceProxy_);
		}
		break;
	}

}

VCF::VariantData* ClassServerInstance::invoke( VCF::OutputStream* marshalledData )
{
	VCF::VariantData* result = NULL;

	Socket sock( LOCAL_CLASS_SERVER, CLASS_SERVER_PORT );
	CallBack* socketHandler = getEventHandler( "SocketHandler" );
	sock.DataReceived.add( socketHandler );

	try {
		sock.startListening();
		System::sleep( 20 );//HACK ALERT !!!! this seems to need to be here
		//to let the threaded listener for the socket to
						  //get started perhaps there is a better way ?????
		BasicOutputStream stream;

		System::print( "Sending invoke request ot server...\n" );

		int msgType = CLASS_SVR_MSG_PROXY_INVOKE;
		stream << msgType;
		stream.write( (unsigned char*)marshalledData->getBuffer(), marshalledData->getSize() );
		sock.send( stream.getBuffer(), stream.getSize() );
		sock.checkForPendingData( VCFNET_INFINITEWAIT );

	}
	catch( ... ) {

	}

	return result;
}


/**
$Id$
*/
