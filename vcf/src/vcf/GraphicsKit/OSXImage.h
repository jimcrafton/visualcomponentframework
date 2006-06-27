#ifndef _VCF_OSXIMAGE_H__
#define _VCF_OSXIMAGE_H__
//OSXImage.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF
{

class OSXImage : public AbstractImage
{
public:
	OSXImage();

	OSXImage( const uint32& width, const uint32& height );

	OSXImage( GraphicsContext* context, Rect* rect );

	OSXImage( CFURLRef url, const String& ext );
	
    virtual ~OSXImage();

	void init();

	virtual void setSize( const uint32 & width, const uint32 & height );

	virtual void beginDrawing();

	virtual void finishedDrawing();

    CGImageRef getCGImage() {
        return imageRef_;
    }
protected:

	void setAlpha( float val );
	
    void createBMP();
    GrafPtr grafPort_;
    CGImageRef imageRef_;

	void loadFromURL( CFURLRef url, const String& ext );
};



};


#endif // _VCF_OSXIMAGE_H__

/**
$Id$
*/
