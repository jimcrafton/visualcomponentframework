#ifndef _VCF_GRAYSCALEIMAGE_H__
#define _VCF_GRAYSCALEIMAGE_H__

//GrayScaleImage.h


namespace VCF {
/**
\class GrayScaleImage GrayScaleImage.h "vcf/GraphicsKit/GrayScaleImage.h"
*/
	class GrayScaleImage : public AbstractImage {
	public:

		GrayScaleImage( const bool& needsMemAlloc=true );

		virtual ~GrayScaleImage();

		virtual void setSize( const uint32 & width, const uint32 & height );

		virtual ImageBits* getImageBits() {
			return NULL;
		}

	};

};
#endif //_VCF_GRAYSCALEIMAGE_H__

/**
$Id$
*/
