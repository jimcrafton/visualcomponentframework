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


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:12  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.3.8.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.3  2003/05/17 20:37:14  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.2.10.2  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.2.10.1  2003/03/12 03:11:41  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.2  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.2.1  2002/08/10 05:48:23  ddiego
*added basic support to the X11COntext for drawing lines, rectangles, and ellipses
*Bezier curves are more complex and will have to be done by hand as X has no
*convenient way to do this
*
*/


#endif // _VCF_X11VCFUTILS_H__


