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

	OSXImage( const unsigned long& width, const unsigned long& height );

	OSXImage( GraphicsContext* context, Rect* rect );

    virtual ~OSXImage();

	void init();

	virtual void setSize( const unsigned long & width, const unsigned long & height );

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

};



};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:18  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/27 04:26:05  ddiego
*updated devmain-0-6-5 branch with osx changes
*
*Revision 1.1.2.4.2.1  2004/06/20 00:36:11  ddiego
*finished the new theme API updates
*
*Revision 1.1.2.4  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.2.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.2  2004/04/03 15:48:42  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.1.2.2  2004/02/23 05:51:42  ddiego
*basic GraphicsKit implementation done for OSX
*
*Revision 1.1.2.1  2004/02/21 03:27:06  ddiego
*updates for OSX porting
*
*
*/


#endif // _VCF_OSXIMAGE_H__


