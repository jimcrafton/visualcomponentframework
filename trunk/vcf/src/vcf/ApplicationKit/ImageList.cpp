//ImageList.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"

using namespace VCF;

ImageList::ImageList()
{
	init();
}

/*
ImageList::ImageList( Image* listOfImages, const unsigned long& imageWidth, const unsigned long& imageHeight )
{
	init();
}
*/



ImageList::ImageList( Component* owner ):
	Component( owner )
{
	init();
}

ImageList::ImageList( const String& name, Component* owner ):
	Component( name, owner )
{
	init();
}

ImageList::ImageList( const String& name ):
	Component( name )
{
	init();
}


ImageList::~ImageList()
{
	if ( NULL != masterImage_ ) {
		delete masterImage_;
		masterImage_ = NULL;
	}
}

void ImageList::init()
{
	imageWidth_ = 32;
	imageHeight_ = 32;
	imageCount_ = 5;
	resizeIncrement_ = 5;
	totalImageCount_ = 0;
	masterImage_ = NULL;
	changed();
}

unsigned long ImageList::getImageWidth()
{
	return imageWidth_;
}

unsigned long ImageList::getImageHeight()
{
	return imageHeight_;
}

void ImageList::setImageWidth( const unsigned long& width )
{
	imageWidth_ = 	width;
	changed();
	ImageListEvent event( this, IMAGELIST_EVENT_WIDTH_CHANGED );
	SizeChanged.fireEvent( &event );
}

void ImageList::setImageHeight( const unsigned long& height )
{
	imageHeight_ = height;
	changed();
	ImageListEvent event( this, IMAGELIST_EVENT_HEIGHT_CHANGED );
	SizeChanged.fireEvent( &event );
}

void ImageList::setTransparentColor( Color* color )
{
	transparentColor_.copy( color );
}

Color* ImageList::getTransparentColor()
{
	return &transparentColor_;
}

void ImageList::addImage( Image* newImage )
{
	if ( newImage->getHeight() != imageHeight_ ) {
		//throw exception
		return;
	}

	if ( newImage->getWidth() != imageWidth_ ) {
		//throw exception
		return;
	}

	int incr  = imageWidth_ * totalImageCount_;

	totalImageCount_++;
	if ( totalImageCount_ >= imageCount_ ) {
		//resize the master image
		imageCount_ += this->resizeIncrement_;
		this->changed();
	}

	SysPixelType* bits = masterImage_->getImageBits()->pixels_;
	bits += incr;
	SysPixelType* newImgBits = newImage->getImageBits()->pixels_;
	int scanlineWidthToCopy = newImage->getWidth();
	int scanlineWidthOfMasterImage = masterImage_->getWidth();//scanlineToCopy * imageCount_;
	for (ulong32 i=0;i<imageHeight_;i++) {
		memcpy( bits, newImgBits, scanlineWidthToCopy*sizeof(SysPixelType) );

		bits += scanlineWidthOfMasterImage;
		newImgBits += scanlineWidthToCopy;
	}

	ImageListEvent event( this, IMAGELIST_EVENT_ITEM_ADDED, newImage );
	event.setIndexOfImage( totalImageCount_-1 );
	ImageAdded.fireEvent( &event );
}

void ImageList::insertImage( const unsigned long & index, Image* newImage )
{
	if ( newImage->getHeight() != imageHeight_ ) {
		//throw exception
		return;
	}

	if ( newImage->getWidth() != imageWidth_ ) {
		//throw exception
		return;
	}

	int incr  = (imageWidth_ * sizeof(SysPixelType)) * index;
	int oldImgCount = totalImageCount_;
	int tmpSize = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * (totalImageCount_-index);
	int tmpLineIncr = (imageWidth_ * sizeof(SysPixelType)) * (totalImageCount_-index);
	int fullLineIncr = (imageWidth_ * sizeof(SysPixelType)) * totalImageCount_;

	//save off the old section of the
	//image that will have to be moved over
	char* tmpBits = new char[tmpSize];
	char* tmpBitsPtr = tmpBits;
	char* oldBits = (char*)this->masterImage_->getImageBits()->pixels_;
	oldBits += incr;
	ulong32 y = 0;
	for ( y=0;y<imageHeight_;y++) {
		memcpy( tmpBitsPtr, oldBits, tmpLineIncr );
		tmpBitsPtr += tmpLineIncr;
		oldBits += fullLineIncr;
	}

	//resize the image if neccessary
	totalImageCount_++;
	if ( totalImageCount_ >= imageCount_ ) {
		//resize the master image
		imageCount_ += this->resizeIncrement_;
		this->changed();
	}

	int moveOverIncr = (imageWidth_ * sizeof(SysPixelType)) * index+1;
	int indexIncr = (imageWidth_ * sizeof(SysPixelType)) * index;
	char* buf = (char*)masterImage_->getImageBits()->pixels_;

	char* newImgBits = (char*)newImage->getImageBits()->pixels_;
	memcpy( oldBits, newImgBits, imageHeight_ * imageWidth_ * sizeof(SysPixelType) );

	tmpBitsPtr = tmpBits;
	for ( y=0;y<imageHeight_;y++) {
		//copy back the original bits, moving over by one spot
		oldBits = buf;
		oldBits += moveOverIncr + (y * fullLineIncr);
		memcpy( oldBits, tmpBits, tmpLineIncr );

		//copy over the inserted image bits
		oldBits = buf;
		oldBits += indexIncr + (y * fullLineIncr);
		memcpy( oldBits, tmpBitsPtr, tmpLineIncr );
		tmpBitsPtr += tmpLineIncr;
	}

	delete [] tmpBits;

	ImageListEvent event( this, IMAGELIST_EVENT_ITEM_ADDED, newImage );
	event.setIndexOfImage( index );
	ImageAdded.fireEvent( &event );
}

void ImageList::deleteImage( const unsigned long & index )
{
	int incr  = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * index;

	int oldImgCount = totalImageCount_;

	int tmpSize = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * (oldImgCount-(index+1));
	//save off the old section of the
	//image that will have to be moved over
	char* tmpBits = new char[tmpSize];
	char* oldBits = (char*)this->masterImage_->getImageBits()->pixels_;
	oldBits += incr;
	memcpy( tmpBits, oldBits, tmpSize );

	totalImageCount_--;
	//resize the image if neccessary
	if ( (totalImageCount_ % imageCount_) == resizeIncrement_ ) {
		//resize the master image
		imageCount_ -= this->resizeIncrement_;
		this->changed();
	}
	//copy back the original bits, moving over by one spot
	int moveOverIncr = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * index;
	oldBits = (char*)this->masterImage_->getImageBits()->pixels_;
	oldBits += moveOverIncr;
	memcpy( oldBits, tmpBits, tmpSize );
	delete [] tmpBits;

	ImageListEvent event( this, IMAGELIST_EVENT_ITEM_DELETED );
	event.setIndexOfImage( index );
	ImageAdded.fireEvent( &event );
}

void ImageList::draw( GraphicsContext* context, const unsigned long& index, Point* pt )
{
	if ( index >= totalImageCount_ ) {
		return;
	}

	Rect bounds( index * imageWidth_, 0, index * imageWidth_ + imageWidth_, imageHeight_ );
	masterImage_->setIsTransparent( true );
	masterImage_->setTransparencyColor( &transparentColor_ );
	context->drawPartialImage( pt->x_, pt->y_, &bounds, masterImage_ );
}

void ImageList::draw( GraphicsContext* context, const unsigned long& index, Rect* bounds )
{
	if ( index >= totalImageCount_ ) {
		return;
	}

	double w = minVal<double>( bounds->getWidth(), imageWidth_ );
	double h = minVal<double>( bounds->getHeight(), imageHeight_ );
	Rect tmpBounds( index * imageWidth_, 0, index * imageWidth_ + w, h );
	masterImage_->setIsTransparent( true );
	masterImage_->setTransparencyColor( &transparentColor_ );
	//context->drawImage( bounds->left_, bounds->top_, masterImage_ );
	context->drawPartialImage( bounds->left_, bounds->top_, &tmpBounds, masterImage_ );
}

void ImageList::copyImage( Image* imageToCopyTo, const unsigned long& index )
{
	int incr  = (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) * index;
	char* buf = (char*)masterImage_->getImageBits()->pixels_;
	buf += incr;
	char* copyBuf = (char*)imageToCopyTo->getImageBits()->pixels_;
	memcpy( copyBuf, buf, (imageHeight_ * imageWidth_ * sizeof(SysPixelType)) );
}

void ImageList::changed()
{
	Image* oldImage = masterImage_;


	masterImage_ = GraphicsToolkit::createImage( imageWidth_ * imageCount_, imageHeight_ );
	if ( NULL == masterImage_ ) {
		throw InvalidImage( "Toolkit couldn't create Image" );
	}

	if ( NULL != oldImage ) {
		SysPixelType* oldBits = oldImage->getImageBits()->pixels_;
		long oldWidth = oldImage->getWidth();
		long oldHeight = oldImage->getHeight();
		SysPixelType* newBits = masterImage_->getImageBits()->pixels_;
		long newWidth = masterImage_->getWidth();

		uint32 size = minVal<uint32>( oldWidth,newWidth );

		for ( ulong32 i=0;i<imageHeight_;i++ ){
			if ( i < oldHeight ) {
				memcpy( newBits, oldBits, size * sizeof(SysPixelType) );
				oldBits +=  oldWidth;
				newBits += newWidth;
			}
			else {
				break;
			}
		}

		delete oldImage;
		oldImage = NULL;
	}
}

void ImageList::afterCreate( ComponentEvent* event )
{

}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 18:42:25  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.17  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.16.2.1  2003/12/13 15:56:09  ddiego
**** empty log message ***
*
*Revision 1.16  2003/08/09 02:56:45  ddiego
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
*Revision 1.15.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.15  2003/05/17 20:37:22  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.14.2.3  2003/04/07 03:39:31  ddiego
*did some documentation work, and got everything to compile cleanly with some
*of the new additions, particularly the chnages inteh Image/ImageBits classes.
*
*Revision 1.14.2.2  2003/03/23 03:23:55  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.14.2.1  2003/03/12 03:12:02  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.14  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.13.14.3  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.13.14.2  2003/01/08 00:19:50  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.13.14.1  2002/12/25 22:06:31  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.13  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.12.4.2  2002/04/27 15:52:23  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.12.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.12  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


