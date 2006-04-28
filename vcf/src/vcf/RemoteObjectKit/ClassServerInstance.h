#ifndef _VCF_CLASSSERVERINSTANCE_H__
#define _VCF_CLASSSERVERINSTANCE_H__
//ClassServerInstance.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// what should this be good for?
// absolutely nothing!
/*namespace VCFNet {
	class SocketEvent;
}*/

namespace VCFRemote {

class Proxy;

class REMOTEKIT_API ClassServerInstance : public VCF::ObjectWithEvents {

public:
	ClassServerInstance();

	virtual ~ClassServerInstance();

	Proxy* createInstance( const VCF::String& className );

	Proxy* createInstanceByClassID( const VCF::String& classID );

	VCF::VariantData* invoke( VCF::OutputStream* marshalledData );

	void onDataReceived( VCFNet::SocketEvent* event );
private:
	bool classSvrReturned_;
	char* data_;
	Proxy* newInstanceProxy_;
};

}; //end of namespace VCFRemote


#endif // _VCF_CLASSSERVERINSTANCE_H__

/**
$Id$
*/
