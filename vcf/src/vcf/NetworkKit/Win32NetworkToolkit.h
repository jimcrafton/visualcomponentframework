#ifndef _VCF_WIN32NETWORKTOOLKIT_H__
#define _VCF_WIN32NETWORKTOOLKIT_H__

//Win32NetworkToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif





namespace VCF {


	class NETWORKKIT_API Win32NetworkToolkit : public NetworkToolkit {
	public:

		Win32NetworkToolkit();

	protected:		
		virtual ~Win32NetworkToolkit();

		virtual SocketPeer* internal_createSocketPeer( int socketType );
		virtual IPAddressPeer* internal_createIPAddressPeer();
		virtual int internal_getLastError();
	};

};




#endif //_VCF_WIN32NETWORKTOOLKIT_H__