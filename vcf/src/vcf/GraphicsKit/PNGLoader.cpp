//PNGLoader.cpp

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/PNGLoader.h"


// ----------------------------------------------------------

#define PNG_ASSEMBLER_CODE_SUPPORTED
#define PNG_BYTES_TO_CHECK 8

// ----------------------------------------------------------

#include "thirdparty/common/LibPNG/png.h"


static VCF::InputStream* pngInStream = NULL;
static VCF::OutputStream* pngOutStream = NULL;


static void
error_handler(struct png_struct_def *, const char *error) {
	throw VCF::RuntimeException( MAKE_ERROR_MSG_2(VCF::String(error)) );
}

// warnings disabled for now

static void
warning_handler(struct png_struct_def *, const char *warning) {
}


static void
pngLoader_ReadProc( png_struct *, png_byte* data, png_size_t size) {
	pngInStream->read( data, size );
}

static void
pngLoader_WriteProc( png_struct *, png_byte *data, png_size_t size) {
	pngOutStream->write( data, size );
}

static void
pngLoader_FlushProc(png_structp png_ptr) {
	// empty flush implementation
}

using namespace VCF;

PNGLoader::PNGLoader()
{

}

PNGLoader::~PNGLoader()
{

}

Image* PNGLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	png_structp png_ptr;
	png_infop info_ptr;
	png_uint_32 width, height;
	png_colorp png_palette;
	int bpp, color_type, palette_entries;
	
	png_bytepp  row_pointers = NULL;
	
	FileInputStream fis(fileName);

	pngInStream = &fis;

	
	unsigned char png_check[PNG_BYTES_TO_CHECK];

	fis.read( png_check, PNG_BYTES_TO_CHECK );

	if ( png_sig_cmp(png_check, (png_size_t)0, PNG_BYTES_TO_CHECK) != 0) {
		return result;
	}
		
	//valid PNG file

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, (png_voidp)error_handler, error_handler, warning_handler);

	if (NULL == png_ptr ) {
		return result;
	}

	// create the info structure
	info_ptr = png_create_info_struct(png_ptr);

	if ( NULL == info_ptr) {
		png_destroy_read_struct(&png_ptr, (png_infopp)NULL, (png_infopp)NULL);				
		return result;
	}

	// init the IO
	
	png_set_read_fn(png_ptr, info_ptr, pngLoader_ReadProc);
	
	if (setjmp(png_jmpbuf(png_ptr))) {
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return result;
	}

	// Because we have already read the signature...
	
	png_set_sig_bytes(png_ptr, PNG_BYTES_TO_CHECK);
	
	// read the IHDR chunk
	
	png_read_info(png_ptr, info_ptr);
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bpp, &color_type, NULL, NULL, NULL);
	
	// DIB's don't support >8 bits per sample
	// => tell libpng to strip 16 bit/color files down to 8 bits/color
	
	if (bpp == 16) {
		png_set_strip_16(png_ptr);
		bpp = 8;
	}
	
	// Set some additional flags

	switch(color_type) {
		case PNG_COLOR_TYPE_RGB:
		case PNG_COLOR_TYPE_RGB_ALPHA:
			// Flip the RGB pixels to BGR (or RGBA to BGRA)

			png_set_bgr(png_ptr);
			break;

		case PNG_COLOR_TYPE_PALETTE:
			// Expand palette images to the full 8 bits from 2 or 4 bits/pixel

			if ((bpp == 2) || (bpp == 4)) {
				png_set_packing(png_ptr);
				bpp = 8;
			}					

			break;

		case PNG_COLOR_TYPE_GRAY:
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			// Expand grayscale images to the full 8 bits from 2 or 4 bits/pixel

			if ((bpp == 2) || (bpp == 4)) {
				png_set_expand(png_ptr);
				bpp = 8;
			}

			break;

		default:
			throw RuntimeException( MAKE_ERROR_MSG_2("PNG format not supported"));
	}

	// Set the background color to draw transparent and alpha images over.
	// It is possible to set the red, green, and blue components directly
	// for paletted images instead of supplying a palette index.  Note that
	// even if the PNG file supplies a background, you are not required to
	// use it - you should use the (solid) application background if it has one.
	
	if (color_type != PNG_COLOR_TYPE_RGB_ALPHA) {
		png_color_16 my_background= { 0, 255, 255, 255, 0 };
		png_color_16 *image_background;
		
		if (png_get_bKGD(png_ptr, info_ptr, &image_background))
			png_set_background(png_ptr, image_background, PNG_BACKGROUND_GAMMA_FILE, 1, 1.0);
		else
			png_set_background(png_ptr, &my_background, PNG_BACKGROUND_GAMMA_SCREEN, 0, 1.0);
	}

	// if this image has transparency, store the trns values
	
//	png_bytep trans               = NULL;
//	int num_trans                 = 0;
//	png_color_16p trans_values    = NULL;
//	png_uint_32 transparent_value = png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, &trans_values);


	// unlike the example in the libpng documentation, we have *no* idea where
	// this file may have come from--so if it doesn't have a file gamma, don't
	// do any correction ("do no harm")
	
	double gamma = 0;
	double screen_gamma = 2.2;
	
	if (png_get_gAMA(png_ptr, info_ptr, &gamma))
		png_set_gamma(png_ptr, screen_gamma, gamma);

	// All transformations have been registered; now update info_ptr data

	png_read_update_info(png_ptr, info_ptr);

	// Create a DIB and write the bitmap header
	// set up the DIB palette, if needed

	unsigned char* imageData = NULL;

	

	switch (color_type) {
		case PNG_COLOR_TYPE_RGB:
			png_set_invert_alpha(png_ptr);

			result = GraphicsToolkit::createImage( width, height );

			imageData = new unsigned char[ height * (width * png_ptr->channels) ];

			break;

		case PNG_COLOR_TYPE_RGB_ALPHA :
			result = GraphicsToolkit::createImage( width, height );

			imageData = new unsigned char[ height * (width * png_ptr->channels) ];

			break;

		case PNG_COLOR_TYPE_PALETTE :

			result = GraphicsToolkit::createImage( width, height );			

			png_get_PLTE(png_ptr,info_ptr, &png_palette,&palette_entries);

			imageData = new unsigned char[ height * (width * png_ptr->channels) ];

			// store the palette
/*
			for (i = 0; i < palette_entries; i++) {
				palette[i].rgbRed   = png_palette[i].red;
				palette[i].rgbGreen = png_palette[i].green;
				palette[i].rgbBlue  = png_palette[i].blue;
			}
*/
			// store the transparency table

			//if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
			//	freeimage.set_transparency_table_proc(dib, (BYTE *)trans, num_trans);					

			break;

		case PNG_COLOR_TYPE_GRAY:
		case PNG_COLOR_TYPE_GRAY_ALPHA:
			imageData = new unsigned char[ height * (width * png_ptr->channels) ];

			/*
			dib = freeimage.allocate_proc(width, height, bpp, 0, 0, 0);

			palette = freeimage.get_palette_proc(dib);
			palette_entries = 1 << bpp;

			for (i = 0; i < palette_entries; i++) {
				palette[i].rgbRed   =
				palette[i].rgbGreen =
				palette[i].rgbBlue  = (i * 255) / (palette_entries - 1);
			}

			// store the transparency table

			if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
				freeimage.set_transparency_table_proc(dib, (BYTE *)trans, num_trans);
			*/	
			break;
	}


	// set the individual row_pointers to point at the correct offsets
	
	row_pointers = (png_bytepp)malloc(height * sizeof(png_bytep));
	
	if (!row_pointers) {
		
		//if (palette)
		//	png_free(png_ptr, palette);				
		
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);		
		
		::free(row_pointers);
		return NULL;
	}

	// read in the bitmap bits via the pointer table
	
	
	for (png_uint_32 k = 0; k < height; k++) {				
		//row_pointers[height - 1 - k] = &imageData[ (height - 1 - k) * (width * png_ptr->channels) ];// freeimage.get_scanline_proc(dib, k);		
		row_pointers[k] = &imageData[ (k) * (width * png_ptr->channels) ];
	}
	
	png_read_image(png_ptr, row_pointers);
		
	// cleanup
	
	if (row_pointers) {
		::free(row_pointers);
	}
	
	png_read_end(png_ptr, info_ptr);
	
	SysPixelType* pix = result->getImageBits()->pixels_;

	unsigned int index = 0;
	unsigned int pixIndex = 0;
	for (unsigned int y=0;y<height;y++ ) {		
		for ( unsigned int x=0;x<width;x++ ) {
			pixIndex = y*width + x;
			index = y * (width * png_ptr->channels) + (x * png_ptr->channels);

			pix[pixIndex].r = pix[pixIndex].g = pix[pixIndex].b = imageData[index];

			for (int channel=0;channel<png_ptr->channels;channel++ ) {				
				switch ( channel ) {
					case 0 : {
						pix[pixIndex].b = imageData[index + channel];
					}
					break;

					case 1 : {
						pix[pixIndex].g = imageData[index + channel];
					}
					break;

					case 2 : {
						pix[pixIndex].r = imageData[index + channel];
					}
					break;
				}
			}
		}	
	}

	delete [] imageData;

	if (png_ptr)
		png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp)NULL);

	return result;
}

void PNGLoader::saveImageToFile( const String& fileName, Image* image )
{

	png_structp png_ptr;
	png_infop info_ptr;
	png_colorp palette = NULL;
	png_uint_32 width, height, bpp;
//	int has_alpha_channel = FALSE;
	int bit_depth;
//	int palette_entries;
	int	interlace_type;

	FileOutputStream fos(fileName);

	pngOutStream = &fos;

	// create the chunk manage structure

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, (png_voidp)error_handler, error_handler, warning_handler);
	
	if (!png_ptr)  {
		return;
	}

	// Allocate/initialize the image information data.
	
	info_ptr = png_create_info_struct(png_ptr);
	
	if (!info_ptr)  {
		png_destroy_write_struct(&png_ptr,  (png_infopp)NULL);
		return;
	}

	// Set error handling.  REQUIRED if you aren't supplying your own
	// error handling functions in the png_create_write_struct() call.
	
	if (setjmp(png_jmpbuf(png_ptr)))  {
		// If we get here, we had a problem reading the file
		
		png_destroy_write_struct(&png_ptr, &info_ptr);
		
		return;
	}

	// init the IO
	
	png_set_write_fn(png_ptr, info_ptr, pngLoader_WriteProc, pngLoader_FlushProc);
	
	// DIBs *do* support physical resolution
	
	
	png_uint_32 res_x = 0; //punt on this...maybe we need to deal with this???
	png_uint_32 res_y = 0;
	
	if ((res_x > 0) && (res_y > 0))  {
		png_set_pHYs(png_ptr, info_ptr, res_x, res_y, 1);
	}

	// Set the image information here.  Width and height are up to 2^31,
	// bit_depth is one of 1, 2, 4, 8, or 16, but valid values also depend on
	// the color_type selected. color_type is one of PNG_COLOR_TYPE_GRAY,
	// PNG_COLOR_TYPE_GRAY_ALPHA, PNG_COLOR_TYPE_PALETTE, PNG_COLOR_TYPE_RGB,
	// or PNG_COLOR_TYPE_RGB_ALPHA.  interlace is either PNG_INTERLACE_NONE or
	// PNG_INTERLACE_ADAM7, and the compression_type and filter_type MUST
	// currently be PNG_COMPRESSION_TYPE_BASE and PNG_FILTER_TYPE_BASE. REQUIRED
	
	width = image->getWidth();
	height = image->getHeight();

	switch( image->getType() ) {
		case Image::itGrayscale :
			bpp = bit_depth = 8;
		break;

		case Image::itColor :
			bpp = bit_depth = 32;
		break;
	}

	
	
	if (bit_depth == 16) {
		png_destroy_write_struct(&png_ptr, &info_ptr);
		
		throw RuntimeException( MAKE_ERROR_MSG_2("16 bit PNG's not currently supported") );
	}
	
	bit_depth = (bit_depth > 8) ? 8 : bit_depth;
	
	interlace_type = PNG_INTERLACE_NONE;	// Default value

	switch( image->getType() ) {
		case Image::itGrayscale :
			png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 
						PNG_COLOR_TYPE_GRAY, interlace_type, 
						PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

			
			//set transparency???
			//png_set_tRNS(png_ptr, info_ptr, freeimage.get_transparency_table_proc(dib), freeimage.get_transparency_count_proc(dib), NULL);

		break;

		case Image::itColor :

			/*
			if ( //do we support alpha??? ) {
				has_alpha_channel = TRUE;

				png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 
					PNG_COLOR_TYPE_RGBA, interlace_type, 
					PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

				png_set_bgr(png_ptr); // flip BGR pixels to RGB
			}
			*/

			png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 
				PNG_COLOR_TYPE_RGB, interlace_type, 
				PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

			png_set_bgr(png_ptr); // flip BGR pixels to RGB
		break;
	}

	// Optional gamma chunk is strongly suggested if you have any guess
	// as to the correct gamma of the image.
	// png_set_gAMA(png_ptr, info_ptr, gamma);

	// Write the file header information.

	png_write_info(png_ptr, info_ptr);


	// write out the image data	

	unsigned char* tmpBuffer = new unsigned char[  width * png_ptr->channels ];	

	SysPixelType* pix = image->getImageBits()->pixels_;

	switch( image->getType() ) {
		case Image::itGrayscale :
			//for (png_uint_32 k = 0; k < height; k++) {
				//png_write_row(png_ptr, freeimage.get_scanline_proc(dib, height - k - 1));
			//}
		break;

		case Image::itColor :
		break;
	}

	for (png_uint_32 k = 0; k < height; k++) {

		for ( unsigned int x=0;x<width;x++ ) {
			tmpBuffer[(x * png_ptr->channels)] = pix[x].r; 

			for (int channel=0;channel<png_ptr->channels;channel++ ) {				
				switch ( channel ) {
					case 0 : {
						tmpBuffer[(x * png_ptr->channels) + channel] = pix[x].b;
					}
					break;

					case 1 : {
						tmpBuffer[(x * png_ptr->channels) + channel] = pix[x].g;
					}
					break;

					case 2 : {
						tmpBuffer[(x * png_ptr->channels) + channel] = pix[x].r;
					}
					break;
				}
			}
		}

		png_write_row(png_ptr, tmpBuffer );

		pix += width;
	}

	delete [] tmpBuffer;


	// It is REQUIRED to call this to finish writing the rest of the file
	// Bug with png_flush
	
	png_write_end(png_ptr, info_ptr);
	
	// clean up after the write, and free any memory allocated
	
	png_destroy_write_struct(&png_ptr, &info_ptr);

	if (palette) {
		png_free(png_ptr, palette);	
	}
}
