#ifndef _VCF_COMPOSITION_H__
#define _VCF_COMPOSITION_H__
//Composition.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */



namespace VCF{
/** A Composition is a collection of graphics elements that can rendered as a group to some graphics context.
 *   Rendering to the context requires getting a bitmap to use and then rendering the composition contents to the bitmap.
 *    Once this is done the bitmap contents are rendered to the compositions graphics context.
 * @interface */
class GRAPHICSKIT_API Composition {
public:

    virtual void addElement() = 0;

    virtual void render() = 0;

    virtual void removeElement() = 0;
};

}


#endif // _VCF_COMPOSITION_H__

/**
$Id$
*/
