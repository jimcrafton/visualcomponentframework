#ifndef _VCF_MGCBEZIERCURVE2_H__
#define _VCF_MGCBEZIERCURVE2_H__
//MgcBezierCurve2.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


// Magic Software, Inc.
// http://www.magic-software.com
// Copyright (c) 2000-2002.  All Rights Reserved
//
// Source code from Magic Software is supplied under the terms of a license
// agreement and may not be copied or disclosed except in accordance with the
// terms of that agreement.  The various license agreements may be found at
// the Magic Software web site.  This file is subject to the license
//
// FREE SOURCE CODE
// http://www.magic-software.com/License/free.pdf


#include "vcf/GraphicsKit/MgcSingleCurve2.h"

namespace Mgc {


class MAGICFM BezierCurve2 : public SingleCurve2
{
public:
    // Construction and destruction.  BezierCurve2 accepts responsibility for
    // deleting the input array.
    BezierCurve2 (int iDegree, Vector2* akCtrlPoint);
    virtual ~BezierCurve2 ();

    int GetDegree () const;
    const Vector2* GetControlPoints () const;

    virtual Vector2 GetPosition (Real fTime) const;
    virtual Vector2 GetFirstDerivative (Real fTime) const;
    virtual Vector2 GetSecondDerivative (Real fTime) const;
    virtual Vector2 GetThirdDerivative (Real fTime) const;

    virtual Real GetVariation (Real fT0, Real fT1, const Vector2* pkP0 = 0,
        const Vector2* pkP1 = 0) const;

protected:
    int iDegree_;
    int iNumCtrlPoints_;
    Vector2* akCtrlPoint_;
    Vector2* akDer1CtrlPoint_;
    Vector2* akDer2CtrlPoint_;
    Vector2* akDer3CtrlPoint_;
    Real** aafChoose_;

    // variation support
    int iTwoDegree_;
    int iTwoDegreePlusOne_;
    Real* afSigma_;
    Real* afRecip_;
    Real* afPowT0_;
    Real* afPowOmT0_;
    Real* afPowT1_;
    Real* afPowOmT1_;
};

#include "vcf/GraphicsKit/MgcBezierCurve2.inl"

} // namespace Mgc


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_MGCBEZIERCURVE2_H__


