#ifndef _VCF_RUNLOOPSOURCE_H__
#define _VCF_RUNLOOPSOURCE_H__



/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class RunLoop;

class FOUNDATIONKIT_API RunLoopSource {
public:
	virtual ~RunLoopSource(){}

	virtual void setRunLoop( RunLoop* runLoop ) = 0;

	virtual void perform() = 0;

	virtual void cancel() = 0;
};


};


#endif //_VCF_RUNLOOPSOURCE_H__

