#ifndef _VCF_MGCCURVE2_H__
#define _VCF_MGCCURVE2_H__
//MgcCurve2.h

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


#include "vcf/GraphicsKit/MgcVector2.h"

namespace Mgc {


class MAGICFM Curve2
{
public:
    // abstract base class
    Curve2 (Real fTMin, Real fTMax);
    virtual ~Curve2 ();

    // interval on which curve parameter is defined
    Real GetMinTime () const;
    Real GetMaxTime () const;

    // position and derivatives
    virtual Vector2 GetPosition (Real fTime) const = 0;
    virtual Vector2 GetFirstDerivative (Real fTime) const = 0;
    virtual Vector2 GetSecondDerivative (Real fTime) const = 0;
    virtual Vector2 GetThirdDerivative (Real fTime) const = 0;

    // differential geometric quantities
    Real GetSpeed (Real fTime) const;
    virtual Real GetLength (Real fT0, Real fT1) const = 0;
    Real GetTotalLength () const;
    Vector2 GetTangent (Real fTime) const;
    Vector2 GetNormal (Real fTime) const;
    void GetFrame (Real fTime, Vector2& rkPosition, Vector2& rkTangent,
        Vector2& rkNormal) const;
    Real GetCurvature (Real fTime) const;

    // inverse mapping of s = Length(t) given by t = Length^{-1}(s)
    virtual Real GetTime (Real fLength, int iIterations = 32,
        Real fTolerance = 1e-06f) const = 0;

    // subdivision
    void SubdivideByTime (int iNumPoints, Vector2*& rakPoint) const;
    void SubdivideByLength (int iNumPoints, Vector2*& rakPoint) const;

    // Subdivision by variation. The pointers pkP0 and pkP1 correspond to the
    // curve points at fT0 and fT1.  If the pointer values are not null, the
    // assumption is that the caller has passed in the curve points.
    // Otherwise, the function computes the curve points.
    virtual Real GetVariation (Real fT0, Real fT1, const Vector2* pkP0 = 0,
        const Vector2* pkP1 = 0) const = 0;
    void SubdivideByVariation (Real fMinVariation, int iMaxLevel,
        int& riNumPoints, Vector2*& rakPoint) const;

protected:
    // curve parameter is t where tmin <= t <= tmax
    Real fTMin_, fTMax_;

    // subdivision
    class MAGICFM PointList
    {
    public:
        PointList (const Vector2& rkPoint, PointList* pkNext)
        {
            kPoint_ = rkPoint;
            kNext_ = pkNext;
        }

        Vector2 kPoint_;
        PointList* kNext_;
    };

    void SubdivideByVariation (Real fT0, const Vector2& rkP0, Real fT1,
        const Vector2& rkP1, Real kMinVariation, int iLevel,
        int& riNumPoints, PointList*& rpkList) const;
};

#include "vcf/GraphicsKit/MgcCurve2.inl"

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


#endif // _VCF_MGCCURVE2_H__


