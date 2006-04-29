#ifndef _VCF_DROPTARGETPEER_H__
#define _VCF_DROPTARGETPEER_H__
//DropTargetPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
*DropTargetPeer interface
*/



namespace VCF
{

class DropTarget;

class Control;

/**
\class DropTargetPeer DropTargetPeer.h "vcf/ApplicationKit/DropTargetPeer.h"
*/
class APPLICATIONKIT_API DropTargetPeer {
public:
	virtual ~DropTargetPeer(){};

	virtual void registerTarget( Control* control )=0;

	virtual void unregisterTarget( Control* control )=0;

	virtual DropTarget* getDropTarget()=0;

	virtual void setDropTarget( DropTarget* dropTarget )=0;
};

};


#endif // _VCF_DROPTARGETPEER_H__

/**
$Id$
*/
