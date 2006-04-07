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

	EventHandler* sh =
		new SocketEventHandler<ClassServerInstance>( this, &ClassServerInstance::onDataReceived, "SocketHandler" );

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
		EventHandler* socketHandler = getEventHandler( "SocketHandler" );
		sock.DataReceived.addHandler( socketHandler );
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
	EventHandler* socketHandler = getEventHandler( "SocketHandler" );
	sock.DataReceived.addHandler( socketHandler );

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
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:51  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/09/23 05:30:33  kdmix
*The first parameter of the OutputStream.write() method is const unsigned char* now.
*
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:31:56  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.12  2003/08/09 02:56:46  ddiego
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
*Revision 1.11  2003/05/17 20:37:50  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.3  2003/03/23 04:06:34  marcelloptr
*minor fixes
*
*Revision 1.10.2.2  2003/03/23 03:24:01  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.2.1  2003/03/12 03:13:32  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.14.1  2003/01/08 00:20:03  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.8  2002/02/28 05:08:34  ddiego
*added tests for remote objects, plus another subtle fix for BasicInputStream
*for seek positioning
*
*Revision 1.7  2002/02/27 04:16:12  ddiego
*add sub items to TreeItem class for teh tree list control
*added fixes to the RemoteObject stuff
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


