//MgcBezierCurve2.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


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

#include "vcf/GraphicsKit/MgcBezierCurve2.h"

using namespace Mgc;

//----------------------------------------------------------------------------
BezierCurve2::BezierCurve2 (int iDegree, Vector2* akCtrlPoint)
    :
    SingleCurve2(0.0f,1.0f)
{
    assert( iDegree >= 2 );

    int i, j;

    iDegree_ = iDegree;
    iNumCtrlPoints_ = iDegree_ + 1;
    akCtrlPoint_ = akCtrlPoint;

    // compute first-order differences
    akDer1CtrlPoint_ = new Vector2[iNumCtrlPoints_-1];
    for (i = 0; i < iNumCtrlPoints_-1; i++)
        akDer1CtrlPoint_[i] = akCtrlPoint_[i+1] - akCtrlPoint_[i];

    // compute second-order differences
    akDer2CtrlPoint_ = new Vector2[iNumCtrlPoints_-2];
    for (i = 0; i < iNumCtrlPoints_-2; i++)
        akDer2CtrlPoint_[i] = akDer1CtrlPoint_[i+1] - akDer1CtrlPoint_[i];

    // compute third-order differences
    if ( iDegree >= 3 )
    {
        akDer3CtrlPoint_ = new Vector2[iNumCtrlPoints_-3];
        for (i = 0; i < iNumCtrlPoints_-3; i++)
        {
            akDer3CtrlPoint_[i] = akDer2CtrlPoint_[i+1] -
                akDer2CtrlPoint_[i];
        }
    }
    else
    {
        akDer3CtrlPoint_ = NULL;
    }

    // Compute combinatorial values Choose(N,K), store in aafChoose_[N][K].
    // The values aafChoose_[r][c] are invalid for r < c (use only the
    // entries for r >= c).
    aafChoose_ = new Real*[iNumCtrlPoints_];
    aafChoose_[0] = new Real[iNumCtrlPoints_*iNumCtrlPoints_];
    for (i = 1; i < iNumCtrlPoints_; i++)
        aafChoose_[i] = &aafChoose_[0][i*iNumCtrlPoints_];

    aafChoose_[0][0] = 1.0f;
    aafChoose_[1][0] = 1.0f;
    aafChoose_[1][1] = 1.0f;
    for (i = 2; i <= iDegree_; i++)
    {
        aafChoose_[i][0] = 1.0f;
        aafChoose_[i][i] = 1.0f;
        for (j = 1; j < i; j++)
            aafChoose_[i][j] = aafChoose_[i-1][j-1] + aafChoose_[i-1][j];
    }

    // variation support
    iTwoDegree_ = 2*iDegree_;
    iTwoDegreePlusOne_ = iTwoDegree_ + 1;
    afSigma_ = new Real[iTwoDegreePlusOne_];
    afRecip_ = new Real[iTwoDegreePlusOne_];
    for (i = 0; i <= iTwoDegree_; i++)
    {
        afSigma_[i] = 0.0f;
        int iHalf = ( i % 2 ? (i+1)/2 : i/2 );
        int iStart = ( i <= iDegree_ ? 0 : i - iDegree_ );
        Real fDot, fProd;
        for (j = iStart; j < iHalf; j++)
        {
            fDot = akCtrlPoint_[j].Dot(akCtrlPoint_[i-j]);
            fProd = aafChoose_[iDegree_][j]*aafChoose_[iDegree_][i-j];
            afSigma_[i] += fDot*fProd;
        }
        afSigma_[i] *= 2.0f;

        if ( (i % 2) == 0 )
        {
            fDot = akCtrlPoint_[iHalf].Dot(akCtrlPoint_[iHalf]);
            fProd = aafChoose_[iDegree_][iHalf];
            fProd *= fProd;
            afSigma_[i] += fDot*fProd;
        }

        afRecip_[i] = 1.0f/Real(iTwoDegreePlusOne_-i);
    }

    int iTDp2 = iTwoDegreePlusOne_+1;
    afPowT0_ = new Real[iTDp2];
    afPowT0_[0] = 1.0f;
    afPowT1_ = new Real[iTDp2];
    afPowT1_[0] = 1.0f;

    afPowOmT0_ = new Real[iTDp2];
    afPowOmT0_[0] = 1.0f;
    afPowOmT1_ = new Real[iTDp2];
    afPowOmT1_[0] = 1.0f;
}
//----------------------------------------------------------------------------
BezierCurve2::~BezierCurve2 ()
{
    delete[] afPowOmT1_;
    delete[] afPowOmT0_;
    delete[] afPowT1_;
    delete[] afPowT0_;
    delete[] afSigma_;
    delete[] afRecip_;

    delete[] aafChoose_[0];
    delete[] aafChoose_;
    delete[] akDer3CtrlPoint_;
    delete[] akDer2CtrlPoint_;
    delete[] akDer1CtrlPoint_;
    delete[] akCtrlPoint_;
}
//----------------------------------------------------------------------------
Vector2 BezierCurve2::GetPosition (Real fTime) const
{
    assert( 0.0f <= fTime && fTime <= 1.0f );

    Real fOmTime = 1.0f - fTime;
    Real fPowTime = fTime;
    Vector2 kResult = fOmTime*akCtrlPoint_[0];

    for (int i = 1; i < iDegree_; i++)
    {
        Real fCoeff = aafChoose_[iDegree_][i]*fPowTime;
        kResult = (kResult+fCoeff*akCtrlPoint_[i])*fOmTime;
        fPowTime *= fTime;
    }

    kResult += fPowTime*akCtrlPoint_[iDegree_];

    return kResult;
}
//----------------------------------------------------------------------------
Vector2 BezierCurve2::GetFirstDerivative (Real fTime) const
{
    assert( 0.0f <= fTime && fTime <= 1.0f );

    Real fOmTime = 1.0f - fTime;
    Real fPowTime = fTime;
    Vector2 kResult = fOmTime*akDer1CtrlPoint_[0];

    int iDegreeM1 = iDegree_ - 1;
    for (int i = 1; i < iDegreeM1; i++)
    {
        Real fCoeff = aafChoose_[iDegreeM1][i]*fPowTime;
        kResult = (kResult+fCoeff*akDer1CtrlPoint_[i])*fOmTime;
        fPowTime *= fTime;
    }

    kResult += fPowTime*akDer1CtrlPoint_[iDegreeM1];
    kResult *= Real(iDegree_);

    return kResult;
}
//----------------------------------------------------------------------------
Vector2 BezierCurve2::GetSecondDerivative (Real fTime) const
{
    assert( 0.0f <= fTime && fTime <= 1.0f );

    Real fOmTime = 1.0f - fTime;
    Real fPowTime = fTime;
    Vector2 kResult = fOmTime*akDer2CtrlPoint_[0];

    int iDegreeM2 = iDegree_ - 2;
    for (int i = 1; i < iDegreeM2; i++)
    {
        Real fCoeff = aafChoose_[iDegreeM2][i]*fPowTime;
        kResult = (kResult+fCoeff*akDer2CtrlPoint_[i])*fOmTime;
        fPowTime *= fTime;
    }

    kResult += fPowTime*akDer2CtrlPoint_[iDegreeM2];
    kResult *= Real(iDegree_*(iDegree_-1));

    return kResult;
}
//----------------------------------------------------------------------------
Vector2 BezierCurve2::GetThirdDerivative (Real fTime) const
{
    assert( 0.0f <= fTime && fTime <= 1.0f );

    if ( iDegree_ < 3 )
        return Vector2::ZERO;

    Real fOmTime = 1.0f - fTime;
    Real fPowTime = fTime;
    Vector2 kResult = fOmTime*akDer3CtrlPoint_[0];

    int iDegreeM3 = iDegree_ - 3;
    for (int i = 1; i < iDegreeM3; i++)
    {
        Real fCoeff = aafChoose_[iDegreeM3][i]*fPowTime;
        kResult = (kResult+fCoeff*akDer3CtrlPoint_[i])*fOmTime;
        fPowTime *= fTime;
    }

    kResult += fPowTime*akDer3CtrlPoint_[iDegreeM3];
    kResult *= Real(iDegree_*(iDegree_-1)*(iDegree_-2));

    return kResult;
}
//----------------------------------------------------------------------------
Real BezierCurve2::GetVariation (Real fT0, Real fT1,
    const Vector2* pkP0, const Vector2* pkP1) const
{
    int i, j, k;

    Vector2 kP0, kP1;
    if ( !pkP0 )
    {
        kP0 = GetPosition(fT0);
        pkP0 = &kP0;
    }
    if ( !pkP1 )
    {
        kP1 = GetPosition(fT1);
        pkP1 = &kP1;
    }

    // compute powers of t0, t1, 1-t0, 1-t1
    Real fOmT0 = 1.0f - fT0;
    Real fOmT1 = 1.0f - fT1;
    for (i = 1, j = 0; i <= iTwoDegreePlusOne_; i++, j++)
    {
        afPowT0_[i] = fT0*afPowT0_[j];
        afPowT1_[i] = fT1*afPowT1_[j];
        afPowOmT0_[i] = fOmT0*afPowOmT0_[j];
        afPowOmT1_[i] = fOmT1*afPowOmT1_[j];
    }

    // line segment is L(t) = P0 + ((t-t0)/(t1-t0))*(P1-P0)

    // var1 = integral(Dot(L,L))
    static const Real s_fOneThird = 1.0f/3.0f;
    Real fDT = fT1 - fT0;
    Real fP0P0 = pkP0->Dot(*pkP0);
    Real fP0P1 = pkP0->Dot(*pkP1);
    Real fP1P1 = pkP1->Dot(*pkP1);
    Real fVar1 = s_fOneThird*fDT*(fP0P0 + fP0P1 + fP1P1);

    // var2 = integral(Dot(X,P0))
    // var3 = integral(Dot(X,P1-P0)*(t-t0)/(t1-t0))
    Real fVar2 = 0.0f;
    Real fVar3 = 0.0f;
    Vector2 kDir = *pkP1 - *pkP0;
    Real fIint = 0.0f;
    int iDp2 = iDegree_+2, iDm1 = iDegree_-1;
    Real fJint = (afPowOmT0_[iDp2] - afPowOmT1_[iDp2])*afRecip_[iDm1];
    Real fProd0, fProd1, fDot;
    for (i = 0, j = iDegree_, k = iDegree_+1; i <= iDegree_; i++, j++, k--)
    {
        // compute I[i]
        fProd0 = afPowT0_[i]*afPowOmT0_[k];
        fProd1 = afPowT1_[i]*afPowOmT1_[k];
        fIint = (fProd0 - fProd1 + i*fIint)*afRecip_[j];

        // compute J[i]
        fProd0 = afPowT0_[i+1]*afPowOmT0_[k];
        fProd1 = afPowT1_[i+1]*afPowOmT1_[k];
        fJint = (fProd0 - fProd1 + (i+1)*fJint)*afRecip_[j];

        // update partial variations
        fDot = pkP0->Dot(akCtrlPoint_[i]);
        fProd0 = aafChoose_[iDegree_][i]*fDot;
        fVar2 += fProd0*fIint;
        fDot = kDir.Dot(akCtrlPoint_[i]);
        fProd0 = aafChoose_[iDegree_][i]*fDot;
        fVar3 += fProd0*(fJint - fT0*fIint);
    }
    fVar3 /= fDT;

    // var4 = integral(Dot(X,X))
    Real fVar4 = 0.0f;
    Real fKint = 0.0f;
    for (i = 0, j = iTwoDegreePlusOne_; i <= iTwoDegree_; i++, j--)
    {
        // compute K[i]
        fProd0 = afPowT0_[i]*afPowOmT0_[j];
        fProd1 = afPowT1_[i]*afPowOmT1_[j];
        fKint = (fProd0 - fProd1 + i*fKint)*afRecip_[i];

        // update partial variation
        fVar4 += afSigma_[i]*fKint;
    }

    Real fVar = fVar1 - 2.0f*(fVar2 + fVar3) + fVar4;
    return fVar;
}
//----------------------------------------------------------------------------


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


