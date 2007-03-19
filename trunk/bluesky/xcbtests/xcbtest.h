
#include <stdlib.h>
#include <stdio.h>


#include <sys/ipc.h>
#include <sys/shm.h>

extern "C" {
#include <xcb/xcb.h>
#include <xcb/xcb_atom.h>
#include <xcb/shm.h>
#include <xcb/xcb_aux.h>
#include <xcb/xcb_image.h>
#include <xcb/xcb_icccm.h>
}





#include "vcf/GraphicsKit/GraphicsKit.h"
#include "vcf/GraphicsKit/XCBContextPeer.h"


typedef void (*do_paint_func_t)( xcb_gcontext_t* the_gc, xcb_window_t* the_window, xcb_image_t* the_image );

class XcbTest {
public:
	XcbTest( do_paint_func_t funcPtr ): paintFunc_(funcPtr) {

	}

	int run() {
		const int width = 400;
		const int height = 400;
		
		xcb_screen_t   *screen;
		xcb_gcontext_t  gc1 = { 0 };
		xcb_drawable_t    pixmap;
		xcb_window_t	window;	
		int          screen_nbr;
		uint32_t       mask;
		uint32_t       values[2];
		int          	size;
		unsigned char  depth;
	
		xcb_connection_t* connection = NULL;
		connection = xcb_connect (NULL, &screen_nbr);
		
		screen = xcb_setup_roots_iterator(xcb_get_setup(connection)).data;

		gc1 = xcb_generate_id( connection );
		

		window = screen->root;
		
		mask = XCB_GC_FOREGROUND | XCB_GC_GRAPHICS_EXPOSURES;
		values[0] = screen->white_pixel;
	  	values[1] = 0;
	  	xcb_create_gc ( connection, gc1, window, mask, values);
	  	
		depth = xcb_aux_get_depth ( connection, screen );
		printf( "bit depth: %d\n", depth );

		mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	 	values[0] = screen->black_pixel;
	 	values[1] = XCB_EVENT_MASK_EXPOSURE | XCB_EVENT_MASK_STRUCTURE_NOTIFY | XCB_EVENT_MASK_BUTTON_PRESS;
	 	
		window = xcb_generate_id( connection );
		
		xcb_create_window ( connection, depth,
			   window,
			   screen->root,
			   0, 0, width, height,
			   0,
			   XCB_WINDOW_CLASS_INPUT_OUTPUT,
			   screen->root_visual,
			   mask, values);
			   
		xcb_map_window ( connection, window);
		xcb_flush ( connection );
		xcb_generic_event_t* xcbEvent;
		
		
		xcb_image_t* image = NULL;
		unsigned char* imageData = NULL;
		xcb_shm_query_version_reply_t *rep;
		xcb_shm_segment_info_t shminfo;
		 
		rep = xcb_shm_query_version_reply( connection, xcb_shm_query_version (connection), NULL );
		
		if ( NULL == rep ) {
			printf ( "SHM extension not supported!!!!\n" );
			return -1;
		}
		
		unsigned char format = 0;
	      
	    if ( rep->shared_pixmaps && (rep->major_version > 1 || rep->minor_version > 0) ) {
			format = rep->pixmap_format;
		}
			
		bool quit = false;
		xcbEvent = xcb_wait_for_event( connection );
		while (!quit && (NULL != xcbEvent) ) {
			if ( NULL != xcbEvent ) {
	      		switch ( xcbEvent->response_type )  {
	      			case XCB_CONFIGURE_NOTIFY: {
						xcb_configure_notify_event_t* confEv = (xcb_configure_notify_event_t*)xcbEvent;
						printf( "xcb_configure_notify_event_t w: %d, h: %d\n", confEv->width, confEv->height );
						
						if ( NULL != image ) {
							xcb_shm_detach( connection, shminfo.shmseg );

							xcb_image_shm_destroy( image );
							
							shmctl(shminfo.shmid, IPC_RMID, 0);
							shmdt(shminfo.shmaddr);
							xcb_flush(connection);
							image = NULL;
						}					
		
						image = xcb_image_shm_create (connection, depth, format, NULL, confEv->width, confEv->height );
						
						if ( NULL == image ) {
							printf( "xcb_image_shm_create failed, w: %d, h: %d\n", confEv->width, confEv->height );
							exit(-1);
						}				
						
						printf ("Create image summary:\n");
						printf (" * format..........: %d\n", image->format);
						printf (" * byte order......: %d\n", image->image_byte_order);
						printf (" * bitmap unit.....: %d\n", image->bitmap_format_scanline_unit);
						printf (" * bitmap order....: %d\n", image->bitmap_format_bit_order);
						printf (" * bitmap pad......: %d\n", image->bitmap_format_scanline_pad);
						printf (" * bytes per line..: %d\n", image->bytes_per_line);
						printf (" * bytes per pixel.: %d\n", image->bits_per_pixel);
						
	      
						shminfo.shmid = shmget( IPC_PRIVATE, image->bytes_per_line * image->height, IPC_CREAT|0777 );
						shminfo.shmaddr = (unsigned char*)shmat(shminfo.shmid, 0, 0);
						image->data = shminfo.shmaddr;
						
						memset( image->data, 0, image->bytes_per_line * image->height );
						
						shminfo.shmseg = xcb_generate_id(connection);
	//xcb_shm_seg_new (connection);

						xcb_shm_attach(connection, shminfo.shmseg, shminfo.shmid, 0);
						shmctl(shminfo.shmid, IPC_RMID, 0);
						
					}
					break;

			    	case XCB_EXPOSE: {
			    		xcb_expose_event_t* expEv = (xcb_expose_event_t*)xcbEvent;
			    		
			    		if ( NULL != image  ) {
			    		
			    			memset( image->data, 0xFF, image->bytes_per_line * image->height );
			    			
/*


			    			unsigned char* ptr = &image->data[ 40 * image->bytes_per_line + 
			    												(40 * (image->bits_per_pixel/8)) ] ;
			    												
			    												
			    												
			    			ptr[0] = 0;
							ptr[1] = 0;
							ptr[2] = 255;
							ptr[3] = 255;
							ptr += 4;
							ptr[0] = 0;
							ptr[1] = 0;
							ptr[2] = 255;
							ptr[3] = 255;
	*/		    			
							(*paintFunc_)( &gc1, &window, image );
			    						
			    			int ret = xcb_image_shm_put (connection, window, gc1, 
			    							image, shminfo, 
			    							expEv->x, expEv->y, 
			    							expEv->x, expEv->y, 
			    							expEv->width, expEv->height, 0);
			    							
			    			if ( 0 == ret ) {
								printf( "xcb_image_shm_put failed!!!!\n" );
							}
			    		}
				    }
				    break;
			    
	            	case XCB_BUTTON_PRESS: {
	            		printf ("Exiting...\n");
	            		quit = true;
		            }
	    	        break;            
		    	}
		    	free( xcbEvent );
		    	xcb_flush ( connection );
	        }
	        
	        xcbEvent = xcb_wait_for_event( connection );
	    }
	    
	    if ( NULL != image ) {
			xcb_shm_detach( connection, shminfo.shmseg );
			xcb_image_shm_destroy( image );
		}
	    
	    shmctl(shminfo.shmid, IPC_RMID, 0);
	    
	    xcb_disconnect ( connection );
	}
	
	do_paint_func_t paintFunc_;
};
