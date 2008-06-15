#ifndef _VCF_OSXGRAPHICSTOOLKIT_H__
#define _VCF_OSXGRAPHICSTOOLKIT_H__
//OSXGraphicsToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/
#include <Cocoa/Cocoa.h>

namespace VCF  {






/**
Utility class to faciltate the transfer from a VCF::Rect instance or HIRect instance to
OSX's ::Rect struct
*/
class OSXRect {
public:
	OSXRect(){
		rect_.left = 0;
		rect_.right = 0;
		rect_.top = 0;
		rect_.bottom = 0;
	}
	
	OSXRect( const OSXRect& rhs ){
		*this = rhs;
	}
	
	OSXRect( const ::Rect& rhs ){
		*this = rhs;
	}
	
	OSXRect( const VCF::Rect& rhs ){
		*this = rhs;
	}
	
	OSXRect( VCF::Rect* rhs ){
		*this = rhs;
	}	
	
	OSXRect( const HIRect& rhs ){
		*this = rhs;
	}
	
	OSXRect( HIRect* rhs ){
		*this = rhs;
	}
	
	int left() const {
		return rect_.left;
	}
	
	int right() const {
		return rect_.right;
	}
	
	int top() const {
		return rect_.top;
	}
	
	int bottom() const {
		return rect_.bottom;
	}
	
	int width() const {
		return rect_.right - rect_.left;
	}
	
	int height() const {
		return rect_.bottom - rect_.top;
	}
			
	operator ::Rect& () {
		return rect_;
	}
	
	operator ::Rect* () {
		return &rect_;
	}
		
	operator const ::Rect& () const {
		return rect_;
	}
	
	operator VCF::Rect () const {
		VCF::Rect result( rect_.left, rect_.top, rect_.right, rect_.bottom );
		return result;
	}
	
	operator HIRect () const {
		HIRect result;
		result.origin.x = rect_.left;
		result.origin.y = rect_.top;
		result.size.width = width();
		result.size.height = height();
		return result;
	}
	
	
	
	OSXRect& operator=( const OSXRect& rhs ) {
		rect_ = rhs.rect_;
		return *this;
	}
	
	OSXRect& operator=( const ::Rect& rhs ) {
		rect_ = rhs;
		return *this;
	}
	
	OSXRect& operator=( const VCF::Rect& rhs ) {
		rect_.left = (int)rhs.left_;
		rect_.top = (int)rhs.top_;
		rect_.right = (int)rhs.right_;
		rect_.bottom = (int)rhs.bottom_;
		return *this;
	}
	
	OSXRect& operator=( VCF::Rect* rhs ) {
		rect_.left = (int)rhs->left_;
		rect_.top = (int)rhs->top_;
		rect_.right = (int)rhs->right_;
		rect_.bottom = (int)rhs->bottom_;
		return *this;
	}
	
	OSXRect& operator=( const HIRect& rhs ) {
		rect_.left = (int)rhs.origin.x;
		rect_.top = (int)rhs.origin.y;
		rect_.right = (int)(rhs.origin.x + rhs.size.width);
		rect_.bottom = (int)(rhs.origin.y + rhs.size.height);
		return *this;
	}
	
	OSXRect& operator=( HIRect* rhs ) {
		rect_.left = (int)rhs->origin.x;
		rect_.top = (int)rhs->origin.y;
		rect_.right = (int)(rhs->origin.x + rhs->size.width);
		rect_.bottom = (int)(rhs->origin.y + rhs->size.height);
		return *this;
	}
	
	
protected:
	::Rect rect_;
};



/**
*Class OSXGraphicsToolkit documentation
*/
class OSXGraphicsToolkit : public GraphicsToolkit {
public:
	OSXGraphicsToolkit();

	virtual ~OSXGraphicsToolkit();

	virtual ContextPeer* internal_createContextPeer( const uint32& width, const uint32& height );

	virtual ContextPeer* internal_createContextPeer( OSHandleID contextID );

	virtual FontPeer* internal_createFontPeer( const String& fontName );

	virtual FontPeer* internal_createFontPeer( const String& fontName, const double& pointSize );

	virtual Image* internal_createImage( const uint32& width, const uint32& height, const Image::ImageType& imageType );

	virtual Image* internal_createImage( GraphicsContext* context, Rect* rect, const Image::ImageType& imageType );

	virtual Font* getDefaultSystemFont() {
		return systemFont_;
	}
	
	virtual PrintSessionPeer* internal_createPrintSessionPeer();

	virtual GraphicsResourceBundlePeer* internal_createGraphicsResourceBundlePeer();

	virtual double internal_getDPI( GraphicsContext* context );
	
	virtual void internal_systemSettingsChanged();
protected:
	void initSystemFont();
	void loadSystemColors();
	Font* systemFont_;

};


}; //end of namespace VCF


#endif // _VCF_OSXGRAPHICSTOOLKIT_H__

/**
$Id$
*/
