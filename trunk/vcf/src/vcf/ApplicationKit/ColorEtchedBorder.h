#ifndef _VCF_COLORETCHEDBORDER_H__
#define _VCF_COLORETCHEDBORDER_H__
//ColorEtchedBorder.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_ETCHEDBORDER_H__
#	include "vcf/ApplicationKit/EtchedBorder.h"
#endif // _VCF_ETCHEDBORDER_H__


#define COLORETCHEDBORDER_CLASSID		"BA2F53FC-C3B8-4958-A7BA-89458FDF57A5"

namespace VCF {
	/**
	\class ColorEtchedBorder ColorEtchedBorder.h "vcf/ApplicationKit/ColorEtchedBorder.h"
	*/
	class APPLICATIONKIT_API ColorEtchedBorder : public EtchedBorder {
	public:

		ColorEtchedBorder();

		ColorEtchedBorder( Component* owner );

		virtual ~ColorEtchedBorder(){};

		virtual void paint( Control* control, GraphicsContext* context );

		virtual void paint( Rect* bounds, GraphicsContext* context );

		virtual Rect getClientRect( Rect* initialBounds, Control* control );

		Color* getHighlight() {
			return &highlight_;
		}

		void setHighlight( Color* val ) {
			highlight_ = *val;
		}

		Color* getShadow() {
			return &shadow_;
		}

		void setShadow( Color* val ) {
			shadow_ = *val;
		}
	protected:
		Color highlight_;
		Color shadow_;
	};
};


#endif // _VCF_COLORETCHEDBORDER_H__

/**
$Id$
*/
