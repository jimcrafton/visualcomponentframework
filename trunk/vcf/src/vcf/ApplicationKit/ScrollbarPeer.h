#ifndef _VCF_SCROLLBARPEER_H__
#define _VCF_SCROLLBARPEER_H__
//ScrollbarPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

class APPLICATIONKIT_API ScrollbarPeer : public VCF::Interface {
public:

    virtual double getPosition() = 0;

    virtual void setPosition(const double& position ) = 0;

    virtual void setMax(const double& max ) = 0;

    virtual double getMax() = 0;

    virtual double getMin() = 0;

    virtual void setMin( const double& min ) = 0;

    virtual void getPageSize() = 0;

    virtual void setPageSize() = 0;

    virtual void getOrientation() = 0;

    virtual void setOrientation() = 0;
};

}


#endif // _VCF_SCROLLBARPEER_H__

/**
$Id$
*/
