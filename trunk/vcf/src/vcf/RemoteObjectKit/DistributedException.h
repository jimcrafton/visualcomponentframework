#ifndef _VCF_DISTRIBUTEDEXCEPTION_H__
#define _VCF_DISTRIBUTEDEXCEPTION_H__
//DistributedException.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCFRemote  {

/**
*Class DistributedException documentation
*/
class REMOTEKIT_API DistributedException : public VCF::BasicException {
public:
	DistributedException();

	virtual ~DistributedException() throw();

protected:

private:
};


}; //end of namespace VCFRemote


#endif // _VCF_DISTRIBUTEDEXCEPTION_H__

/**
$Id$
*/
