//Socket.cpp

#include "NetworkKit.h"
#include "Socket.h"
#include "NetworkToolkit.h"
#include "vcf/FoundationKit/Dictionary.h"


const VCF::String VCF::Socket::soBlocking = "soBlocking"; 
const VCF::String VCF::Socket::soBroadcast = "soBroadcast";
const VCF::String VCF::Socket::soDontLinger = "soDontLinger";
const VCF::String VCF::Socket::soDontRoute = "soDontRoute";
const VCF::String VCF::Socket::soKeepAlive = "soKeepAlive";
const VCF::String VCF::Socket::soRecvBuffer = "soRecvBuffer";
const VCF::String VCF::Socket::soReuseAddress = "soReuseAddress";
const VCF::String VCF::Socket::soSendBuffer = "soSendBuffer";



using namespace VCF;



Socket::Socket():
	peer_(NULL),
	type_(Socket::stStream),
	state_(0)
{
	peer_ = NetworkToolkit::createSocketPeer();

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	peer_->setPeerOwner( this );

	if ( 0 != peer_->create( type_ ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed to create socket instance.") );
	}
}


Socket::Socket(const SocketType& socketType):
	peer_(NULL),
	type_(socketType),
	state_(0)
{
	peer_ = NetworkToolkit::createSocketPeer();

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	peer_->setPeerOwner( this );

	if ( 0 != peer_->create( type_ ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed to create socket instance.") );
	}
}

Socket::Socket( unsigned short port ):
	peer_(NULL),
	type_(Socket::stStream),
	state_(0)
{
	peer_ = NetworkToolkit::createSocketPeer();

	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	peer_->setPeerOwner( this );

	open();

	listen( port );
}

Socket::Socket( const String& host, unsigned short port ):
	peer_(NULL),
	type_(Socket::stStream),
	state_(0)
{
	peer_ = NetworkToolkit::createSocketPeer();
	
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("Unable to create socket peer.") );
	}

	peer_->setPeerOwner( this );

	open();

	connect( host, port );
}

Socket::Socket( SocketPeer* peer ):
	peer_(peer),
	type_(Socket::stStream),
	state_(0)
{
	if ( NULL == peer_ ) {
		throw InvalidPeer( MAKE_ERROR_MSG_2("NULL peer instance passed in to Socket constructor.") );
	}

	peer_->setPeerOwner( this );
}

Socket::~Socket()
{
	close();
	peer_->setPeerOwner( NULL );
	delete peer_;
}

void Socket::open()
{
	close();
	
	if ( 0 != peer_->create( type_ ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed to create socket instance.") );
	}

	state_ = Socket::ssOpen;
}

void Socket::close()
{
	state_ = Socket::ssClosed;
	if ( 0 != peer_->close() ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Attempt to close peer failed.") );
	}
}

void Socket::connect( const String& host, unsigned short port )
{
	if ( 0 != peer_->connect( host, port ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed connect.") );
	}

	state_ |= Socket::ssConnected;
}

void Socket::listen( unsigned short port )
{
	if ( 0 != peer_->listen( port ) ) {
		throw RuntimeException( MAKE_ERROR_MSG_2("Peer failed listen.") );
	}

	state_ |= Socket::ssListening;
}

Socket* Socket::accept()
{
	Socket* result = NULL;

	SocketPeer* newSockPeer = peer_->accept();
	if ( NULL != newSockPeer ) {
		result = new Socket( newSockPeer );

		SocketEvent e(this,Socket::seClientConnected);
		e.socket = result;
		ClientConnected( &e );
	}

	return result;
}

bool Socket::validateOptions( Dictionary& options )
{
	bool result = true;

	Dictionary::Enumerator* enumerator = options.getEnumerator();

	static std::map<String,String> validOptionTypes;
	if ( validOptionTypes.empty() ) {
		validOptionTypes[Socket::soBlocking] = Socket::soBlocking;
		validOptionTypes[Socket::soBroadcast] = Socket::soBroadcast;
		validOptionTypes[Socket::soDontLinger] = Socket::soDontLinger;
		validOptionTypes[Socket::soDontRoute] = Socket::soDontRoute;
		validOptionTypes[Socket::soKeepAlive] = Socket::soKeepAlive;
		validOptionTypes[Socket::soRecvBuffer] = Socket::soRecvBuffer;
		validOptionTypes[Socket::soReuseAddress] = Socket::soReuseAddress;
		validOptionTypes[Socket::soSendBuffer] = Socket::soSendBuffer;
	}


	while ( enumerator->hasMoreElements() ) {
		Dictionary::pair element = enumerator->nextElement();
		if ( validOptionTypes.find( element.first ) == validOptionTypes.end() ) {
			result = false;
			break;	
		}
	}

	return result;
}


void Socket::setOptions( Dictionary& options )
{
	if ( Socket::validateOptions( options ) ) {
		peer_->setOptions( options );
	}
	else {
		throw RuntimeException( MAKE_ERROR_MSG_2("Invalid option (or options) passed to socket - no options set.") );
	}
}

Dictionary Socket::getOptions()
{
	return peer_->getOptions();
}

String Socket::getHostName()
{
	return peer_->getHostName();
}

String Socket::getHostIPAddress()
{
	return peer_->getHostIPAddress();
}

unsigned short Socket::getPort()
{
	return peer_->getPort();
}


bool Socket::pending() const
{
	peer_->select( Socket::SelectNoWait, NULL, NULL, NULL ); 

	return isReadable() || isWriteable();
}


bool Socket::wouldOperationBlock()
{
	return peer_->wouldOperationBlock();
}










SocketInputStream::SocketInputStream( Socket& socket ):
	totalBytesRecvd_(0),
	socket_(&socket)
{

}


uint64 SocketInputStream::read( unsigned char* bytesToRead, uint64 sizeOfBytes )
{
	uint64 bytesRead = 0;

	int err = socket_->getPeer()->recv( bytesToRead, sizeOfBytes );
	if ( err >= 0 ) {
		bytesRead = err;
	}
	else if (!socket_->wouldOperationBlock()) { //the operation flat out failed

		throw NetworkException( MAKE_ERROR_MSG_2("Socket peer's recv() failed.") );
	}
	
	totalBytesRecvd_ += bytesRead;

	return bytesRead;
}



SocketOutputStream::SocketOutputStream( Socket& socket ):
	totalBytesWritten_(0),
	socket_(&socket)
{

}

uint64 SocketOutputStream::write( const unsigned char* bytesToWrite, uint64 sizeOfBytes )
{
	uint64 bytesWritten = 0;

	int err = socket_->getPeer()->send( bytesToWrite, sizeOfBytes );

	if ( err >= 0 ) {
		bytesWritten = err;
	}
	else if (!socket_->wouldOperationBlock()) { //the operation flat out failed

		throw NetworkException( MAKE_ERROR_MSG_2("Socket peer's send() failed.") );
	}

	totalBytesWritten_ += bytesWritten;

	return bytesWritten;
}