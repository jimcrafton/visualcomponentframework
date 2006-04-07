#ifndef _VCF_OSXGRAPHICSTOOLKIT_H__
#define _VCF_OSXGRAPHICSTOOLKIT_H__
//OSXGraphicsToolkit.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


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

	virtual ContextPeer* internal_createContextPeer( const unsigned long& width, const unsigned long& height );

	virtual ContextPeer* internal_createContextPeer( OSHandleID contextID );

	virtual FontPeer* internal_createFontPeer( const String& fontName );

	virtual FontPeer* internal_createFontPeer( const String& fontName, const double& pointSize );

	virtual Image* internal_createImage( const unsigned long& width, const unsigned long& height, const Image::ImageType& imageType );

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


/**
*CVS Log info
*$Log$
*Revision 1.6  2006/04/07 02:35:41  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.5.2.2  2006/02/22 01:26:22  ddiego
*mac osx updates.
*
*Revision 1.5.2.1  2005/11/10 02:02:39  ddiego
*updated the osx build so that it
*compiles again on xcode 1.5. this applies to the foundationkit and graphicskit.
*
*Revision 1.5  2005/07/09 23:06:01  ddiego
*added missing gtk files
*
*Revision 1.4  2005/01/08 20:52:48  ddiego
*fixed some glitches in osx impl.
*
*Revision 1.3.2.1  2005/05/08 19:55:32  ddiego
*osx updates, not yet functional.
*
*Revision 1.3  2004/12/01 04:31:44  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/22 13:22:01  ddiego
*removed mgc code for drawing vector shapes. Unneccessary since agg does this just fine.
*
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.7  2004/07/27 04:26:05  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.6.2.1  2004/06/15 04:04:38  ddiego
*revamped osx theme drawing API
*
*Revision 1.1.2.6  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.5  2004/05/06 03:01:29  ddiego
*checking in OSX updates
*
*Revision 1.1.2.4  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.2  2004/02/24 01:42:43  ddiego
*initial OSX ApplicationKit port checkin
*
*Revision 1.1.2.1  2004/02/21 03:27:06  ddiego
*updates for OSX porting
*
*/


#endif // _VCF_OSXGRAPHICSTOOLKIT_H__


