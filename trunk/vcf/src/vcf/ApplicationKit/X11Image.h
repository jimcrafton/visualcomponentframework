#ifndef _VCF_X11IMAGE_H__
#define _VCF_X11IMAGE_H__
//X11Image.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class GRAPHICSKIT_API X11Image : public AbstractImage
{
public:
	X11Image();

	X11Image( const String& fileName );

	X11Image( const unsigned long& width, const unsigned long& height );

	X11Image( GraphicsContext* context, Rect* rect );


	virtual ~X11Image();

	void init();

	virtual void setWidth( const unsigned long & width );

	virtual void setHeight( const unsigned long & height );

	Imlib_Image getXImage() {
		return ximage_;
	}

	Pixmap getPixMap() {
		return x11ImagePixmap_;
	}

	Pixmap getAlphaMaskPixMap() {
		return x11AlphaMask_;
	}

	void updateImageDataFromImageBits();

	virtual ImageBits* getImageBits();
protected:
	void loadFromFile( const String& fileName );


	void saveToFile( const String& fileName );

	Imlib_Image ximage_;

	Pixmap x11ImagePixmap_;
	Pixmap x11AlphaMask_;

	void createBitmap();
};


class GRAPHICSKIT_API XPMLoader : public Object, public ImageLoader {
public:
	XPMLoader();

	virtual ~XPMLoader();

	virtual Image* loadImageFromFile( const String& fileName );


	virtual void saveImageToFile( const String& fileName, Image* image );

	virtual bool canSaveImage(){
		return true;
	}
private:

};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:11  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:16  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.4.8.1  2004/04/26 21:58:44  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2003/05/17 20:37:13  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.2  2003/03/23 03:23:51  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.1  2003/03/12 03:11:40  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:41  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.8.4  2002/12/20 03:29:33  ddiego
*continued more work in integrating imlib2 into the X11Image class. getting
*a little better hand of how to debug with CLI gdb ! Close to having this
*work, and tehn we can work on Fonts !
*
*Revision 1.2.8.3  2002/12/19 05:32:30  ddiego
*initial integration of imlib2 into the GraphicsKit.
*
*Revision 1.2.8.2  2002/12/14 23:29:48  ddiego
*partial image support no in
*
*Revision 1.2.8.1  2002/12/14 01:50:37  ddiego
*more code in X11Image
*
*Revision 1.2  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.1.2.1  2002/08/06 02:57:36  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*
*/


#endif // _VCF_X11IMAGE_H__


