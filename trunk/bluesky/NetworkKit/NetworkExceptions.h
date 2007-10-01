#ifndef _VCF_NETWORKEXCEPTIONS_H__
#define _VCF_NETWORKEXCEPTIONS_H__


//NetworkExceptions.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

	
namespace VCF  {

	enum NetworkErrors {		
		neInProgress = 1,
		neAlreadyInprogress,
		neNotSocket,
		neDestAddrRequested,
		neMsgTooLong,
		neWrongProtocol,
		neBadProtocolOpt,
		neProtocolNotSupp,
		neSockTypeNotSupp,
		neOperationNotSupp,
		neProtoFamilyNotSupp,
		neAddrFamilyNotSupp,
		neAddrInUse,
		neAddrNotAvailable,
		neNetworkDown,
		neNetworkUnreachable,
		neNetworkReset,
		neConnectionAborted,
		neConnectionReset,
		neNoBufferSpaceAvail,
		neSockAlreadyConnected,
		neSockNotConnected,
		neSockShutdown,
		neConnectionTimedOut,
		neConectionRefused,
		neTooManySymLinks,
		neNameTooLong,
		neHostDown,
		neHostUnreachable,
		neTooManyProcesses,



	};


	/**
	Base class for all exceptions in the NetworkKit
	*/
	class NETWORKKIT_API NetworkException : public BasicException {
	public:		
		NetworkException( const String & message );

		NetworkException();
			
		NetworkException( const String & message, int lineNumber );
			
		virtual ~NetworkException() throw() {};

		/**
		Returns one of the standard error codes that this exception 
		represents. The value will be one of the value in the NetworkErrors
		enumeration.

		@see NetworkErrors
		*/
		int errorCode() const {
			return errorCode_;
		}
	protected:
		int errorCode_;
	};



	class NETWORKKIT_API SocketException : public NetworkException {
	public:		
		SocketException( const String & message ):NetworkException(message){}

		SocketException():NetworkException(){}
			
		SocketException( const String & message, int lineNumber ):NetworkException(message,lineNumber){}
			
		virtual ~SocketException() throw() {};		
	};


	class NETWORKKIT_API SocketReadException : public NetworkException {
	public:		
		SocketReadException( const String & message ):NetworkException(message){}

		SocketReadException():NetworkException(){}
			
		SocketReadException( const String & message, int lineNumber ):NetworkException(message,lineNumber){}
			
		virtual ~SocketReadException() throw() {};		
	};


	class NETWORKKIT_API SocketWriteException : public NetworkException {
	public:		
		SocketWriteException( const String & message ):NetworkException(message){}

		SocketWriteException():NetworkException(){}
			
		SocketWriteException( const String & message, int lineNumber ):NetworkException(message,lineNumber){}
			
		virtual ~SocketWriteException() throw() {};		
	};
};



#endif //_VCF_NETWORKEXCEPTIONS_H__
