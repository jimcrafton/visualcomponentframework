//MgcVector2.inl

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

//----------------------------------------------------------------------------
inline Vector2::Vector2 ()
{
    // For efficiency in construction of large arrays of vectors, the
    // default constructor does not initialize the vector.
}
//----------------------------------------------------------------------------
inline Real& Vector2::operator[] (int i) const
{
    return ((Real*)this)[i];
}
//----------------------------------------------------------------------------
inline Vector2::operator Real* ()
{
    return (Real*)this;
}
//----------------------------------------------------------------------------
inline Real Vector2::SquaredLength () const
{
    return x*x + y*y;
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


