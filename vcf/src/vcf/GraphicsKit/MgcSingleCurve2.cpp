//MgcSingleCurve2.cpp

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

#include "vcf/GraphicsKit/MgcIntegrate.h"
#include "vcf/GraphicsKit/MgcSingleCurve2.h"

using namespace Mgc;

//----------------------------------------------------------------------------
SingleCurve2::SingleCurve2 (Real fTMin, Real fTMax)
    :
    Curve2(fTMin,fTMax)
{
}
//----------------------------------------------------------------------------
Real SingleCurve2::GetSpeedWithData (Real fTime, void* pvData)
{
    return ((Curve2*)pvData)->GetSpeed(fTime);
}
//----------------------------------------------------------------------------
Real SingleCurve2::GetLength (Real fT0, Real fT1) const
{
    assert( fTMin_ <= fT0 && fT0 <= fTMax_ );
    assert( fTMin_ <= fT1 && fT1 <= fTMax_ );
    assert( fT0 <= fT1 );

    return Integrate::RombergIntegral(fT0,fT1,GetSpeedWithData,(void*)this);
}
//----------------------------------------------------------------------------
Real SingleCurve2::GetTime (Real fLength, int iIterations,
    Real fTolerance) const
{
    if ( fLength <= 0.0f )
        return fTMin_;

    if ( fLength >= GetTotalLength() )
        return fTMax_;

    // initial guess for Newton's method
    Real fRatio = fLength/GetTotalLength();
    Real fOmRatio = 1.0f - fRatio;
    Real fTime = fOmRatio*fTMin_ + fRatio*fTMax_;

    for (int i = 0; i < iIterations; i++)
    {
        Real fDifference = GetLength(fTMin_,fTime) - fLength;
        if ( Math::FAbs(fDifference) < fTolerance )
            return fTime;

        fTime -= fDifference/GetSpeed(fTime);
    }

    // Newton's method failed.  If this happens, increase iterations or
    // tolerance or integration accuracy.
    return Math::MAX_REAL;
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


