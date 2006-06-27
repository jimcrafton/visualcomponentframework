#ifndef _VCF_TITLEDBORDER_H__
#define _VCF_TITLEDBORDER_H__
//TitledBorder.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#define TITLEDBORDER_CLASSID		"5CD916D3-39BE-4c22-8FEB-6358073104AD"



namespace VCF {

	/**
	\class TitledBorder TitledBorder.h "vcf/ApplicationKit/TitledBorder.h"
	*/
	class APPLICATIONKIT_API TitledBorder : public Border {
	public:

		TitledBorder();
		
		TitledBorder(const String& title);
		TitledBorder(const String& title, int32 sidesToPaint);
		TitledBorder(const String& title, int32 sidesToPaint, const Font& font);

		TitledBorder( Component* owner );

		virtual ~TitledBorder(){};

		virtual void paint( Control* control, GraphicsContext* context );

		virtual void paint( Rect* bounds, GraphicsContext* context );

		virtual Rect getClientRect( Rect* initialBounds, Control* control );

		String getCaption() {
			return caption_;
		}

		void setCaption( const String& val ) {
			caption_ = val;
		}

		Font* getFont() {
			return &font_;
		}

		void setFont( Font* val ) {
			if ( NULL != val ) {
				font_ = *val;
			}
		}

		void setSidesToPaint( const int32& sidesToPaint ) {
			sidesToPaint_ = sidesToPaint;
		}

		int32 getSidesToPaint() {
			return sidesToPaint_;
		}
	protected:
		String caption_;
		int32 sidesToPaint_;
		Font font_;		
	};
};


#endif // _VCF_TITLEDBORDER_H__

/**
$Id$
*/
