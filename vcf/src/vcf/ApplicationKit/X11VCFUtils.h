#ifndef _VCF_X11VCFUTILS_H__
#define _VCF_X11VCFUTILS_H__
//X11VCFUtils.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

	/**
	Used as a placeholder for both a Window and
	GC, as both are required for most X graphics calls
	*/
	class X11GraphicsDevice {
	public:
		X11GraphicsDevice() : gc_(0), drawable_((Drawable)0), display_(NULL) {
			
		}

		X11GraphicsDevice( GC gc ) : gc_(gc), drawable_((Drawable)0), display_(NULL) {

		}

		X11GraphicsDevice( Drawable drawable ) : gc_(0), drawable_(drawable) , display_(NULL){

		}

		X11GraphicsDevice( GC gc, Drawable drawable, Display* display=NULL ) : gc_(gc), drawable_(drawable), display_(display) {

		}

		X11GraphicsDevice( const X11GraphicsDevice& xgd ) : gc_(0), drawable_((Drawable)0), display_(NULL) {
			*this = xgd;
		}


		inline X11GraphicsDevice& operator= ( const X11GraphicsDevice& xgd ) {
			gc_ = xgd.gc_;
			drawable_ = xgd.drawable_;
			display_ =  xgd.display_;
			return *this;
		}

		inline operator GC () const {
			return gc_;
		}

		inline operator Drawable () const {
			return drawable_;
		}


		inline GC getGC() const {
			return gc_;
		}

		inline void setGC( GC gc ) {
			gc_ = gc;
		}

		inline Drawable getDrawable() const {
			return drawable_;
		}

		inline void setDrawable( Drawable drawable ) {
			drawable_ = drawable;
		}

		inline Display* getDisplay() {
			return display_;	
		}

		inline void setDisplay( Display* display ) {
			display_ = display;
		}
	protected:
		GC gc_;
		Drawable drawable_;
		Display* display_;
	};

};


#endif // _VCF_X11VCFUTILS_H__

/**
$Id$
*/
