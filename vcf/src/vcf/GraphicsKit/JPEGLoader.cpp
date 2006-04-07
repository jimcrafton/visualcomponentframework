//JPEGLoader.cpp

#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/GraphicsKitPrivate.h"
#include "vcf/GraphicsKit/JPEGLoader.h"




extern "C" {
#define XMD_H
#undef FAR
#include <setjmp.h>
#include "thirdparty/common/LibJPEG/jpeglib.h"
}

// ----------------------------------------------------------

#define INPUT_BUF_SIZE  4096	/* choose an efficiently fread'able size */
#define OUTPUT_BUF_SIZE 4096    /* choose an efficiently fwrite'able size */

typedef struct my_error_mgr * my_error_ptr;

// ----------------------------------------------------------
//   Constants + headers
// ----------------------------------------------------------

METHODDEF(void)
jpeg_error_exit (j_common_ptr cinfo) 
{
	(*cinfo->err->output_message)(cinfo);

	jpeg_destroy(cinfo);

	throw VCF::RuntimeException(MAKE_ERROR_MSG_2("Error in JPEG library."));
}

METHODDEF(void)
jpeg_output_message (j_common_ptr cinfo) 
{
	char buffer[JMSG_LENGTH_MAX];

	(*cinfo->err->format_message)(cinfo, buffer);
}

//===========================================================
/*
 * jdatasrc.c
 *
 * Copyright (C) 1994-1996, Thomas G. Lane.
 * This file is part of the Independent JPEG Group's software.
 * For conditions of distribution and use, see the accompanying README file.
 *
 * This file contains decompression data source routines for the case of
 * reading JPEG data from a file (or any stdio stream).  While these routines
 * are sufficient for most applications, some will want to use a different
 * source manager.
 * IMPORTANT: we assume that fread() will correctly transcribe an array of
 * JOCTETs from 8-bit-wide elements on external storage.  If char is wider
 * than 8 bits on your machine, you may need to do some tweaking.
 */

#include "thirdparty/common/LibJPEG/jinclude.h"
#include "thirdparty/common/LibJPEG/jpeglib.h"
#include "thirdparty/common/LibJPEG/jerror.h"

// Expanded data source object for stdio input --------------

struct my_error_mgr {
	struct jpeg_error_mgr pub;	/* "public" fields */

	jmp_buf setjmp_buffer;	/* for return to caller */
};

// ----------------------------------------------------------

struct JPEGLoaderInput {
	struct jpeg_source_mgr pub;	//public fields

	VCF::InputStream* inStream;		//source stream 

	JOCTET * buffer;		// start of buffer
	boolean start_of_file;	// have we gotten any data yet? 
};


struct JPEGLoaderOutput {
	struct jpeg_destination_mgr pub;	//public fields

	VCF::OutputStream* outStream;		//destination stream

	JOCTET * buffer;		//start of buffer 
};


METHODDEF(void)
init_source (j_decompress_ptr cinfo) {
	JPEGLoaderInput* src = (JPEGLoaderInput*) cinfo->src;

	/* We reset the empty-input-file flag for each image,
 	 * but we don't clear the input buffer.
	 * This is correct behavior for reading a series of images from one source.
	*/

	src->start_of_file = TRUE;
}


METHODDEF(void)
init_destination (j_compress_ptr cinfo) {
	JPEGLoaderOutput* dest = (JPEGLoaderOutput*) cinfo->dest;

	dest->buffer = (JOCTET *)
	  (*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE,
				  OUTPUT_BUF_SIZE * SIZEOF(JOCTET));

	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;
}


// ----------------------------------------------------------

/*
 * Fill the input buffer --- called whenever buffer is emptied.
 *
 * In typical applications, this should read fresh data into the buffer
 * (ignoring the current state of next_input_byte & bytes_in_buffer),
 * reset the pointer & count to the start of the buffer, and return TRUE
 * indicating that the buffer has been reloaded.  It is not necessary to
 * fill the buffer entirely, only to obtain at least one more byte.
 *
 * There is no such thing as an EOF return.  If the end of the file has been
 * reached, the routine has a choice of ERREXIT() or inserting fake data into
 * the buffer.  In most cases, generating a warning message and inserting a
 * fake EOI marker is the best course of action --- this will allow the
 * decompressor to output however much of the image is there.  However,
 * the resulting error message is misleading if the real problem is an empty
 * input file, so we handle that case specially.
 *
 * In applications that need to be able to suspend compression due to input
 * not being available yet, a FALSE return indicates that no more data can be
 * obtained right now, but more may be forthcoming later.  In this situation,
 * the decompressor will return to its caller (with an indication of the
 * number of scanlines it has read, if any).  The application should resume
 * decompression after it has loaded more data into the input buffer.  Note
 * that there are substantial restrictions on the use of suspension --- see
 * the documentation.
 *
 * When suspending, the decompressor will back up to a convenient restart point
 * (typically the start of the current MCU). next_input_byte & bytes_in_buffer
 * indicate where the restart point will be if the current call returns FALSE.
 * Data beyond this point must be rescanned after resumption, so move it to
 * the front of the buffer rather than discarding it.
 */

METHODDEF(boolean)
fill_input_buffer (j_decompress_ptr cinfo) {
	JPEGLoaderInput* src = (JPEGLoaderInput*) cinfo->src;

	
	size_t nbytes = src->inStream->read( src->buffer, INPUT_BUF_SIZE );

		//src->m_io->read_proc(src->buffer, 1, INPUT_BUF_SIZE, src->infile);

	if (nbytes <= 0) {
		if (src->start_of_file)	/* Treat empty input file as fatal error */
			ERREXIT(cinfo, JERR_INPUT_EMPTY);

		WARNMS(cinfo, JWRN_JPEG_EOF);

		/* Insert a fake EOI marker */

		src->buffer[0] = (JOCTET) 0xFF;
		src->buffer[1] = (JOCTET) JPEG_EOI;

		nbytes = 2;
	}

	src->pub.next_input_byte = src->buffer;
	src->pub.bytes_in_buffer = nbytes;
	src->start_of_file = FALSE;

	return TRUE;
}

METHODDEF(boolean)
empty_output_buffer (j_compress_ptr cinfo) {
	JPEGLoaderOutput* dest = (JPEGLoaderOutput*) cinfo->dest;

	//if (dest->m_io->write_proc(dest->buffer, 1, OUTPUT_BUF_SIZE, dest->outfile) != OUTPUT_BUF_SIZE)
	//	ERREXIT(cinfo, JERR_FILE_WRITE);

	try {
		dest->outStream->write( dest->buffer, OUTPUT_BUF_SIZE );
	}
	catch ( ... ) {
		ERREXIT(cinfo, JERR_FILE_WRITE);
	}


	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;

	return TRUE;
}

/*
 * Skip data --- used to skip over a potentially large amount of
 * uninteresting data (such as an APPn marker).
 *
 * Writers of suspendable-input applications must note that skip_input_data
 * is not granted the right to give a suspension return.  If the skip extends
 * beyond the data currently in the buffer, the buffer can be marked empty so
 * that the next read will cause a fill_input_buffer call that can suspend.
 * Arranging for additional bytes to be discarded before reloading the input
 * buffer is the application writer's problem.
 */

METHODDEF(void)
skip_input_data (j_decompress_ptr cinfo, long num_bytes) {
	JPEGLoaderInput* src = (JPEGLoaderInput*) cinfo->src;

	/* Just a dumb implementation for now.  Could use fseek() except
     * it doesn't work on pipes.  Not clear that being smart is worth
	 * any trouble anyway --- large skips are infrequent.
	*/

	if (num_bytes > 0) {
		while (num_bytes > (long) src->pub.bytes_in_buffer) {
		  num_bytes -= (long) src->pub.bytes_in_buffer;

		  (void) fill_input_buffer(cinfo);

		  /* note we assume that fill_input_buffer will never return FALSE,
		   * so suspension need not be handled.
		   */
		}

		src->pub.next_input_byte += (size_t) num_bytes;
		src->pub.bytes_in_buffer -= (size_t) num_bytes;
	}
}

/*
 * Terminate source --- called by jpeg_finish_decompress
 * after all data has been read.  Often a no-op.
 *
 * NB: *not* called by jpeg_abort or jpeg_destroy; surrounding
 * application must deal with any cleanup that should happen even
 * for error exit.
 */

METHODDEF(void)
term_source (j_decompress_ptr cinfo) {
  /* no work necessary here */
}

METHODDEF(void)
term_destination (j_compress_ptr cinfo) {
	JPEGLoaderOutput* dest = (JPEGLoaderOutput*) cinfo->dest;

	size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;

	/* Write any data remaining in the buffer */

	if (datacount > 0) {
		if ( dest->outStream->write( dest->buffer, datacount ) != datacount ) {
			ERREXIT(cinfo, JERR_FILE_WRITE);
		}
	}
}



using namespace VCF;

JPEGLoader::JPEGLoader()
{

}

JPEGLoader::~JPEGLoader()
{

}

Image* JPEGLoader::loadImageFromFile( const String& fileName )
{
	Image* result = NULL;

	JPEGLoaderInput* src;


	FileInputStream fis(fileName);

	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	// Step 1: allocate and initialize JPEG decompression object

	cinfo.err = jpeg_std_error(&jerr);

	jerr.error_exit     = jpeg_error_exit;
	jerr.output_message = jpeg_output_message;
	
	jpeg_create_decompress(&cinfo);


	// allocate memory for the buffer. is released automatically in the end

	if (cinfo.src == NULL) {
		cinfo.src = (struct jpeg_source_mgr *) (*cinfo.mem->alloc_small)
			((j_common_ptr) &cinfo, JPOOL_PERMANENT, SIZEOF(JPEGLoaderInput));

		src = (JPEGLoaderInput*) cinfo.src;

		src->buffer = (JOCTET *) (*cinfo.mem->alloc_small)
			((j_common_ptr) &cinfo, JPOOL_PERMANENT, INPUT_BUF_SIZE * SIZEOF(JOCTET));
	}

	// initialize the jpeg pointer struct with pointers to functions
	
	src = (JPEGLoaderInput*) cinfo.src;
	src->pub.init_source = init_source;
	src->pub.fill_input_buffer = fill_input_buffer;
	src->pub.skip_input_data = skip_input_data;
	src->pub.resync_to_restart = jpeg_resync_to_restart; /* use default method */
	src->pub.term_source = term_source;
	
	src->inStream = &fis;

	src->pub.bytes_in_buffer = 0; /* forces fill_input_buffer on first read */
	src->pub.next_input_byte = NULL; /* until buffer loaded */


	//now we're ready to start reading...

	// Step 3: read handle parameters with jpeg_read_header()

	jpeg_read_header(&cinfo, TRUE);
	
	
	/*
	// Step 4a: set parameters for decompression
	cinfo.dct_method          = JDCT_IFAST;
	cinfo.do_fancy_upsampling = FALSE;
	}
	*/

	if (cinfo.num_components == 1) {
		//gray scale image - not quite yet...	
	}
	else {

	}

	// Step 5: start decompressor

	jpeg_start_decompress(&cinfo);

	// Step 6: while (scan lines remain to be read) jpeg_read_scanlines(...);
	
	result = GraphicsToolkit::createImage( cinfo.output_width, cinfo.output_height );

	unsigned char* tmpBuffer = new unsigned char[ cinfo.output_width * cinfo.out_color_components ];
	unsigned char* tmpBufPtr = tmpBuffer;

	SysPixelType* pix = result->getImageBits()->pixels_;
		 
	while (cinfo.output_scanline < cinfo.output_height) {
		JSAMPROW b = (JSAMPROW) tmpBufPtr;
			//freeimage.get_scanline_proc(dib, cinfo.output_height - cinfo.output_scanline - 1);
		
		jpeg_read_scanlines(&cinfo, &b, 1);

		for ( unsigned int x=0;x<cinfo.output_width;x++ ) {
			pix[x].r = pix[x].g = pix[x].b = tmpBufPtr[(x * cinfo.out_color_components)];
			for (int channel=0;channel<cinfo.out_color_components;channel++ ) {				
				switch ( channel ) {
					case 0 : {
						pix[x].b = tmpBufPtr[(x * cinfo.out_color_components) + channel];
					}
					break;

					case 1 : {
						pix[x].g = tmpBufPtr[(x * cinfo.out_color_components) + channel];
					}
					break;

					case 2 : {
						pix[x].r = tmpBufPtr[(x * cinfo.out_color_components) + channel];
					}
					break;
				}
			}
		}
		
		pix += cinfo.output_width;
	}
	
	delete [] tmpBuffer;

	// Step 7: finish decompression 
	
	jpeg_finish_decompress(&cinfo);
	
	// Step 8: release JPEG decompression object
	
	jpeg_destroy_decompress(&cinfo);

	return result;
}

void JPEGLoader::saveImageToFile( const String& fileName, Image* image )
{

	struct jpeg_compress_struct cinfo;
	struct jpeg_error_mgr jerr;

	FileOutputStream fos(fileName);

	// Step 1: allocate and initialize JPEG compression object
	
	cinfo.err = jpeg_std_error(&jerr);
	
	jerr.error_exit     = jpeg_error_exit;
	jerr.output_message = jpeg_output_message;
	
	/* Now we can initialize the JPEG compression object. */
	
	jpeg_create_compress(&cinfo);
	
	/* Step 2: specify data destination (eg, a file) */
	
	JPEGLoaderOutput* dest;

	if (cinfo.dest == NULL) {
		cinfo.dest = (struct jpeg_destination_mgr *)(*cinfo.mem->alloc_small)
			((j_common_ptr) &cinfo, JPOOL_PERMANENT, SIZEOF(JPEGLoaderOutput));
	}

	dest = (JPEGLoaderOutput*) cinfo.dest;
	dest->pub.init_destination = init_destination;
	dest->pub.empty_output_buffer = empty_output_buffer;
	dest->pub.term_destination = term_destination;
	
	dest->outStream = &fos;

	
	/* Step 3: set parameters for compression */											    
	
	cinfo.image_width = image->getWidth();
	cinfo.image_height = image->getHeight();

	switch( image->getType() ) {
		case Image::itGrayscale :
			cinfo.in_color_space = JCS_GRAYSCALE;
			cinfo.input_components = 1;
		break;

		case Image::itColor :
			cinfo.in_color_space = JCS_RGB;
			cinfo.input_components = 3;
		break;
	}

	jpeg_set_defaults(&cinfo);

	// Set JFIF density parameters from the DIB data


	cinfo.X_density = (short)118.1102; //this assumes a pixels per meter of 11,811.02, or 300 per inch
	cinfo.Y_density = (short)118.1102;
	cinfo.density_unit = 2;	// dots / cm

	int quality = 75; //this is the default quality level that freeimage uses.

	jpeg_set_quality(&cinfo, quality, TRUE); /* limit to baseline-JPEG values */

	/* Step 5: Start compressor */
	
	jpeg_start_compress(&cinfo, TRUE);

	unsigned char* tmpBuffer = new unsigned char[ cinfo.image_width * cinfo.input_components ];	

	SysPixelType* pix = image->getImageBits()->pixels_;

	while (cinfo.next_scanline < cinfo.image_height) {

		for ( unsigned int x=0;x<cinfo.image_width;x++ ) {
			tmpBuffer[(x * cinfo.input_components)] = pix[x].r; 

			for (int channel=0;channel<cinfo.input_components;channel++ ) {				
				switch ( channel ) {
					case 0 : {
						tmpBuffer[(x * cinfo.input_components) + channel] = pix[x].b;
					}
					break;

					case 1 : {
						tmpBuffer[(x * cinfo.input_components) + channel] = pix[x].g;
					}
					break;

					case 2 : {
						tmpBuffer[(x * cinfo.input_components) + channel] = pix[x].r;
					}
					break;
				}
			}
		}

		JSAMPROW b = tmpBuffer;


		jpeg_write_scanlines(&cinfo, &b, 1);

		pix += cinfo.image_width;
	}

	delete [] tmpBuffer;

	/* Step 7: Finish compression */
	
	jpeg_finish_compress(&cinfo);
	
	/* Step 8: release JPEG compression object */
	
	jpeg_destroy_compress(&cinfo);
}



