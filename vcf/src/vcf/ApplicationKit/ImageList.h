#ifndef _VCF_IMAGELIST_H__
#define _VCF_IMAGELIST_H__
//ImageList.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


#define IMAGELIST_CLASSID				"2EA88629-682F-4b01-BB6F-9990BCF67DD6"

class Image;

class GraphicsContext;

/**
\class ImageList ImageList.h "vcf/ApplicationKit/ImageList.h"
An image list is a collection of images.
The image list is used by controls like the TreeControl, ListViewControl, and
others. The collection of images is implemented by storing them on one single
image.
@delegates
	@del ImageList::SizeChanged
	@del ImageList::ImageAdded
	@del ImageList::ImageDeleted
*/
class APPLICATIONKIT_API ImageList : public Component{
public:


	ImageList();

	ImageList( Component* owner );

	ImageList( const String& name, Component* owner );

	ImageList( const String& name );

	/**
	*Creates a new imagelist from a Image and the
	*appropriate width and height.
	*/
	//ImageList( Image* listOfImages, const unsigned long& imageWidth, const unsigned long& imageHeight );

	virtual ~ImageList();

	void init();

	/**
	@delegate SizeChanged is fired when the size of teh image list changes. This
	happens whenever the setImageWidth() or setImageHeight() methods are called.
	@event ImageListEvent
	@eventtype IMAGELIST_EVENT_WIDTH_CHANGED
	@eventtype IMAGELIST_EVENT_HEIGHT_CHANGED
	@see setImageWidth
	@see setImageHeight
	*/
	DELEGATE(SizeChanged)

	/**
	@delegate ImageAdded this is fired when a new image is added.
	@event ImageListEvent
	@eventtype IMAGELIST_EVENT_ITEM_ADDED
	@see addImage
	@see insertImage
	*/
	DELEGATE(ImageAdded)

	/**
	@delegate ImageDeleted this is fired after an image has been removed from the image list.
	@event ImageListEvent
	@eventtype IMAGELIST_EVENT_ITEM_DELETED
	@see deleteImage
	*/
	DELEGATE(ImageDeleted)

	/**
	*returns the width of each image in the list, <b><i>NOT</i></b>
	*the width of the list itself. All images in the list
	*will have the same width and height.
	*/
	unsigned long getImageWidth();

	/**
	*returns the height of an image in the list.
	*All images in the list will have the same width and height.
	*/
	unsigned long getImageHeight();

	void setImageWidth( const unsigned long& width );

	void setImageHeight( const unsigned long& height );

	void setTransparentColor( Color* color );

	Color* getTransparentColor();

	void addImage( Image* newImage );

	void insertImage( const unsigned long & index, Image* newImage );

	void deleteImage( const unsigned long & index );

	virtual void draw( GraphicsContext* context, const unsigned long& index, Point* pt );

	/**
	*Draws the image within the bounds specified in bounds. Where the bounds->left_ and top_
	*represent the upper left and top coords. If the boudns width or height is less than the
	*images, then clipping occurs
	*/
	virtual void draw( GraphicsContext* context, const unsigned long& index, Rect* bounds );

	void copyImage( Image* imageToCopyTo, const unsigned long& index );

	void setResizeIncrement( const ulong32& resizeIncrement ) {
		resizeIncrement_ = resizeIncrement;
	}

	virtual void afterCreate( ComponentEvent* event );

	uint32 getImageCount() {
		return totalImageCount_;
	}

	Image* getMasterImage() {
		return masterImage_;
	}

private:
	void changed();

private:
	unsigned long imageWidth_;
	unsigned long imageHeight_;
	Color transparentColor_;

	/**
	*this represents the number of images the masterImage_
	*can hold
	*/
	uint32 imageCount_;

	/**
	*this represents the number of images actually
	*displayed within the masterImage_
	*/
	uint32 totalImageCount_;
	Image* masterImage_;
	ulong32 resizeIncrement_;
};


}; // namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.2  2006/03/14 02:25:47  ddiego
*large amounts of source docs updated.
*
*Revision 1.3.2.1  2006/03/12 22:42:07  ddiego
*more doc updates - specific to graphicskit.
*
*Revision 1.3  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/06/26 01:27:53  marcelloptr
*added images to a PushButton
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
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
*Revision 1.11.4.1  2004/04/26 21:58:40  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.11  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.10.4.6  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.10.4.5  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.10.4.4  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.10.4.3  2003/09/21 04:15:35  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.10.4.2  2003/09/12 16:46:33  ddiego
*finished adding header changes to improve compile speed (at least
*with MS VC++) and to get rid of some of the clutter that the RTTI macros
*add.
*But Where'd the RTTI info go!?!?
*Have no fear it's still there! It is now located in three .inl files, one
*for each kit. Each kit will consolidate it's RTTI decls in the following
*files:
*FoundationKit:
*  vcf/include/FoundationKitRTTI.inl
*GraphicsKit:
*  vcf/include/GraphicsKitRTTI.inl
*ApplicationKit:
*  vcf/include/ApplicationKitRTTI.inl
*
*Please alter these files as neeccessary to add/subtract/alter the various
*RTTI info. Each kit is also responsible for registering any of the class
*in the ClassRegistry.
*A side effect of this is that I had to alter the memory allocation for the
*VC6 build for the Application it went from /Zm120 to /Zm150. I find this
*pretty lame but I don't know what else to do. Hopefully this will improve
*compile times when using the Appkit in other programs.
*
*Revision 1.10.4.1  2003/09/12 00:09:33  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.10  2003/05/17 20:37:10  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.2  2003/03/23 03:23:48  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.2.1  2003/03/12 03:10:25  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.20.2  2003/02/24 05:42:18  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.8.20.1  2002/12/25 22:06:27  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.8  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_IMAGELIST_H__


