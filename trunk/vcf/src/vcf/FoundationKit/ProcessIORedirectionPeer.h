#ifndef _VCF_PROCESSIOREDIRECTIONPEER_H__
#define _VCF_PROCESSIOREDIRECTIONPEER_H__
//ProcessIORedirectionPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class ProcessWithRedirectedIO;
/**
\class ProcessIORedirectionPeer ProcessIORedirectionPeer.h "vcf/FoundationKit/ProcessIORedirectionPeer.h"
This defines the interface for a redirecting process input/ouput.
At this time only output redirection is supported. In other words
the process is created such that the normal output to stdout is captured
and an event is fired whenever there is output data ready to be consumed,
(i.e. an "OutputReady" event so to speak).
*/
class FOUNDATIONKIT_API ProcessIORedirectionPeer : public ProcessPeer {
public:
	virtual ~ProcessIORedirectionPeer(){};
	
	/**
	sets the peer's ProcessWithRedirectedIO process instance. When an
	OutputReady event occurs, the ProcessWithRedirectedIO instance is what
	will be used as the source of the event, <i><b>not</b></i> the peer itself.
	*/
	virtual void setProcess( ProcessWithRedirectedIO* process ) = 0;
};

};


#endif // _VCF_PROCESSIOREDIRECTIONPEER_H__

/**
$Id$
*/
