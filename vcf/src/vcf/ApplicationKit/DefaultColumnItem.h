#ifndef _VCF_DEFAULTCOLUMNITEM_H__
#define _VCF_DEFAULTCOLUMNITEM_H__
//DefaultColumnItem.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_COLUMNITEM_H__
#	include "vcf/ApplicationKit/ColumnItem.h"
#endif // _VCF_COLUMNITEM_H__


namespace VCF  {

class Image;
class ColumnModel;
class Control;


#define DEFAULTCOLUMNITEM_CLASSID		"5003340e-98c7-46ac-a27c-1d38dfdd8aa7"

/**
\class DefaultColumnItem DefaultColumnItem.h "vcf/ApplicationKit/DefaultColumnItem.h"
Class DefaultColumnItem documentation

*/
class APPLICATIONKIT_API DefaultColumnItem : public ColumnItem {
public:

	DefaultColumnItem();

	virtual ~DefaultColumnItem();

	virtual String getCaption();

	virtual void setCaption( const String& caption );

	virtual double getWidth() {
		return width_;
	}

	virtual void setWidth( const double& width );

	virtual void setCaptionAlignment( const TextAlignmentType& alignment );

	virtual TextAlignmentType getCaptionAlignment() {
		return textAlignment_;
	}

	virtual void paint( GraphicsContext* context, Rect* paintRect );

protected:
	String caption_;
	bool selected_;
	double width_;
	TextAlignmentType textAlignment_;
};


}; //end of namespace VCF


#endif // _VCF_DEFAULTCOLUMNITEM_H__

/**
$Id$
*/
