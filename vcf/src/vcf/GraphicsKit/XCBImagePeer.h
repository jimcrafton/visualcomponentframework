#ifndef _VCF_XCBIMAGE_H__
#define _VCF_XCBIMAGE_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF {
    class XCBImagePeer : public AbstractImage {
    public:
        XCBImagePeer();
        XCBImagePeer( const uint32& width, const uint32& height );
        XCBImagePeer( GraphicsContext* context, Rect* rect );

        virtual ~XCBImagePeer();

        virtual void setSize( const unsigned long & width, const unsigned long & height );

        virtual void beginDrawing();

        virtual void finishedDrawing();

        const xcb_image_t* getImageData() const;

    private:
        void init();
        void createBMP();
        void createImage();
        void destroyImage();

        xcb_image_t *image_;

    };




    class XCBGrayscaleImagePeer : public AbstractImage {
    public:
        XCBGrayscaleImagePeer();
        XCBGrayscaleImagePeer( const uint32& width, const uint32& height );
        XCBGrayscaleImagePeer( GraphicsContext* context, Rect* rect );

        virtual ~XCBGrayscaleImagePeer();

        virtual void setSize( const unsigned long & width, const unsigned long & height );

        virtual void beginDrawing();

        virtual void finishedDrawing();

        const xcb_image_t* getImageData() const;

    private:
        void init();
        void createBMP();
        void createImage();
        void destroyImage();

        xcb_image_t *image_;

    };
};


#endif

