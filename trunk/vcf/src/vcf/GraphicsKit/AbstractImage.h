#ifndef _VCF_ABSTRACTIMAGE_H__
#define _VCF_ABSTRACTIMAGE_H__
//AbstractImage.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

class ImageBits;
class GraphicsContext;

/**
AbstractImage represents a base implementation of the Image interface. It implements
common functions, such as getWidth, etc, but still requires actually image class to be
derived from it. It also provides basic support for ImageSizeChangedHandlers, so derived classes
do not have to baother with it. See Image for more information on what the functions do.

@version 1.0
@author Jim Crafton
@see Image
@delegates
	@del AbstractImage::ImageSizeChanged
*/
class GRAPHICSKIT_API AbstractImage : public Image , public Object, public Persistable {
public:

	AbstractImage( const bool& needsMemAlloc=true );

	virtual ~AbstractImage();


	virtual void setSize( const unsigned long & width, const unsigned long & height );

    virtual unsigned long getWidth();

    virtual unsigned long getHeight();

	/**
	@delegate ImageSizeChanged this is fired when the image's dimensions are changed
	by calling setSize().
	@event ImageEvent
	@eventtype IMAGE_EVENT_WIDTH_CHANGED
	@eventtype IMAGE_EVENT_HEIGHT_CHANGED
	@see setSize()
	*/
    DELEGATE(ImageSizeChanged);

	/**
	*This macro creates a method for adding a listener to the AbstractImage's ImageSizeChangedHandler events
	*/
	virtual void addImageSizeChangedHandler( EventHandler* handler ) {
		ImageSizeChanged += handler;
	}

	/**
	*This macro creates a method for removing a listener to the AbstractImage's ImageSizeChangedHandler events
	*/
	virtual void removeImageSizeChangedHandler( EventHandler* handler ) {
		ImageSizeChanged -= handler;
	}

    virtual GraphicsContext* getImageContext();

	virtual ImageBits* getImageBits();

	/**
	*returns the color that is used to blend with the contents of
	*a GraphicsContext when the Image is drawn. Only used when the
	*Image is set to Transparent
	*/
	virtual Color* getTransparencyColor() {
		return &transparencyColor_;
	}

	virtual void setTransparencyColor( Color* transparencyColor ) {
		transparencyColor_ = *transparencyColor;
	}

	/**
	*Indicates whether or not the Image is using a transparent
	*color.
	*@return bool if this is true then the Image is transparent
	*and the contents of the underlying GraphicsContext will show through
	*wherever a pixel in the image is found that is the transparency color
	*/
	virtual bool isTransparent() {
		return isTransparent_;
	}

	virtual void setIsTransparent( const bool& transparent ) {
		isTransparent_ = transparent;
	}

	/**
	*Write the object to the specified output stream
	*/
    virtual void saveToStream( OutputStream * stream );

	/**
	**Read the object from the specified input stream
	*/
    virtual void loadFromStream( InputStream * stream );

	virtual Image::ImageType getType() const ;

	virtual Image::ImageChannelSize getChannelSize() const;

	virtual Image::ImageChannelType getChannelType() const ;

	virtual Image::PixelLayoutOrder getPixelLayoutOrder() const ;
protected:
	ImageBits* imageBits_;
	int height_;
    int width_;
	GraphicsContext * context_;
	Color transparencyColor_;
	bool isTransparent_;

	/**
	Implementer note: flags_ needs to be intialized in the constructor of the
	platform implementation of the Image class. For Win32 an example might be:
	<pre>
	ImageBits::Traits::setChannelType( flags_, ImageBits::Traits::getTraitsChannelType() );
	ImageBits::Traits::setChannelSize( flags_, ImageBits::Traits::getTraitsChannelSize() );
	ImageBits::Traits::setImageType( flags_, ImageBits::Traits::getTraitsImageType() );
	ImageBits::Traits::setPixelLayoutOrder( flags_, Image::ploBGRA );
	</pre>
	*/
	ImageDescriptor flags_;

};

};


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/02 04:11:10  ddiego
*removed some old, extraneous files from graphics kit dir.
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 04:10:26  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:30  ddiego
*migration towards new directory structure
*
*Revision 1.14.4.1  2004/04/26 21:58:38  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.14  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.13.2.2  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.13.2.1  2003/10/28 04:06:10  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.13  2003/08/09 02:56:43  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.12.2.1  2003/06/16 03:09:39  ddiego
*beginning to add support for AGG into the VCF GraphicsKit
*added some missing files
*added some changes to the new version of xmake
*
*Revision 1.12  2003/05/17 20:37:08  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.11.2.3  2003/04/07 03:39:30  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
*
*Revision 1.11.2.2  2003/03/23 03:23:47  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.11.2.1  2003/03/12 03:10:07  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.11  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.10.8.1  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.10  2002/09/12 03:26:03  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.9.12.1  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.9  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTIMAGE_H__


