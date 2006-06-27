#ifndef _VCF_ETCHEDBORDER_H__
#define _VCF_ETCHEDBORDER_H__
//EtchedBorder.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define ETCHEDBORDER_CLASSID		"341D8D4C-B861-4b4d-AEC4-A6911AF67DFF"

namespace VCF {
	/**
	\class EtchedBorder EtchedBorder.h "vcf/ApplicationKit/EtchedBorder.h"
	*/
	class APPLICATIONKIT_API EtchedBorder : public Border {
	public:

		EtchedBorder();

		EtchedBorder( int32 sidesToPaint, int32 style );

		EtchedBorder( Component* owner );

		virtual ~EtchedBorder(){};

		virtual void paint( Control* control, GraphicsContext* context );

		virtual void paint( Rect* bounds, GraphicsContext* context );

		virtual Rect getClientRect( Rect* initialBounds, Control* control );

		void setSidesToPaint( const int32& sidesToPaint ) {
			sidesToPaint_ = sidesToPaint;
		}

		int32 getSidesToPaint() {
			return sidesToPaint_;
		}

		int32 getEdgeStyle() {
			return style_;
		}

		void setEdgeStyle( const int32& val ) {
			style_ = val;
		}
	protected:
		int32 sidesToPaint_;
		int32 style_;
	};
};


#endif // _VCF_ETCHEDBORDER_H__

/**
$Id$
*/
