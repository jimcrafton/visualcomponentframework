#ifndef _VCF_SERVERSOCKETEVENT_H__
#define _VCF_SERVERSOCKETEVENT_H__
//ServerSocketEvent.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFNet
{

class NETKIT_API ServerSocketEvent : public VCF::Event
{
public:
	ServerSocketEvent( VCF::Object* source );

	virtual ~ServerSocketEvent();

private:



};

};


#endif // _VCF_SERVERSOCKETEVENT_H__

/**
$Id$
*/
