//Win32OpenGLPeer.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/GraphicsKit/ContextPeer.h"
#include "vcf/GraphicsKit/Win32Context.h"
#include "vcf/OpenGLKit/Win32OpenGLPeer.h"
#include "vcf/OpenGLKit/VCFOpenGL.h"
#include "vcf/FoundationKit/Win32Peer.h"


using namespace VCF;

Win32OpenGLPeer::Win32OpenGLPeer( Control* owningControl ):
		owningControl_(owningControl),
		dc_(NULL),
		hrc_(NULL),
		isInitialized_(false)
{		
	
}

Win32OpenGLPeer::~Win32OpenGLPeer()
{
	if ( NULL != dc_ ){
		// We don't need the DC to release the rendering context
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( hrc_ );
	}
}

void Win32OpenGLPeer::initGL(GraphicsContext * context)
{
	if ( true == isInitialized_ ){
		return;
	}

	

		/**
		JC  - I commented these out. The problem is that this is always called from a Control::paint
		method, which is turn is called when a WM_PAINT message occurs. Calling GetDC at this point
		I am almost 100% sure is not a good thing. Plus we do not properly clean up (by following
		it with a ReleaseDC() call. using the checkHandle() and releaseHandle() calls will
		do all of this automatically.
		*/
		HWND hwnd = (HWND)(owningControl_->getPeer()->getHandleID());
		HDC dc = ::GetDC(hwnd);

		dc = (HDC)context->getPeer()->getContextID();
		if ( NULL != dc ){
			PIXELFORMATDESCRIPTOR pfd =
			{
				sizeof(PIXELFORMATDESCRIPTOR),  // size of this pfd
					1,                              // version number
					PFD_DRAW_TO_WINDOW |            // support window
					PFD_SUPPORT_OPENGL |          // support OpenGL
					PFD_DOUBLEBUFFER,             // double buffered
					PFD_TYPE_RGBA,                  // RGBA type
					24,                             // 24-bit color depth
					0, 0, 0, 0, 0, 0,               // color bits ignored
					0,                              // no alpha buffer
					0,                              // shift bit ignored
					0,                              // no accumulation buffer
					0, 0, 0, 0,                     // accum bits ignored
					32,                             // 32-bit z-buffer
					0,                              // no stencil buffer
					0,                              // no auxiliary buffer
					PFD_MAIN_PLANE,                 // main layer
					0,                              // reserved
					0, 0, 0                         // layer masks ignored
			};

			int pixelformat = ChoosePixelFormat( dc, &pfd );
			if ( pixelformat == 0 ){
				String errmsg = VCFWin32::Win32Utils::getErrorString( GetLastError() );
				StringUtils::trace( Format( String("Error selecting pixelformat for GL context (" __FILE__ ":%d):\n") + errmsg ) % __LINE__);
				VCF_ASSERT(pixelformat != 0);
				throw BasicException(errmsg);
			}

			bool setPixelSuccess = ( TRUE == ::SetPixelFormat( dc, pixelformat, &pfd ) );
			if ( !setPixelSuccess ){
				String errmsg = VCFWin32::Win32Utils::getErrorString( GetLastError() );
				StringUtils::trace( Format( String("Error setting pixelformat for GL context (" __FILE__ ":%d):\n") + errmsg ) % __LINE__);
				throw BasicException(errmsg);
			}

			hrc_ = wglCreateContext( dc );
			isInitialized_ = ( wglMakeCurrent( dc, hrc_ ) ) ? true : false;
			VCF_ASSERT(isInitialized_);

			ReleaseDC(hwnd,dc);
		}
}

void Win32OpenGLPeer::swapBuffers()
{
	HWND hwnd = (HWND)(owningControl_->getPeer()->getHandleID());
	HDC dc = ::GetDC(hwnd);

	if ( NULL != dc ){
		//Win32Context* win32Ctx = dynamic_cast<Win32Context*>(glContext_->getPeer());
		//VCF_ASSERT(NULL != win32Ctx);
		//if ( NULL == win32Ctx ){
		//	throw BasicException("Win32OpenGLPeer error: cannot get context peer",__LINE__);		//throw exception for release mode -- this is a bad error!
		//}
		//win32Ctx->checkHandle();

		/**
		JC - see Win32OpenGLPeer::initGL for the reason for 
		commenting this out.
		*/
		//HWND hwnd = (HWND)(owningControl_->getPeer()->getHandleID());
		//HDC dc = ::GetDC(hwnd);

		//HDC dc = (HDC)glContext_->getPeer()->getContextID();

		::SwapBuffers( dc );

		ReleaseDC(hwnd,dc);
		//win32Ctx->releaseHandle();
	}
}

void Win32OpenGLPeer::makeCurrent()
{
	HWND hwnd = (HWND)(owningControl_->getPeer()->getHandleID());
	HDC dc = ::GetDC(hwnd);
	if ( NULL != dc ){
		//Win32Context* win32Ctx = dynamic_cast<Win32Context*>(glContext_->getPeer());
		//VCF_ASSERT(NULL != win32Ctx);
		//if ( NULL == win32Ctx ){
		//	throw BasicException("Win32OpenGLPeer error: cannot get context peer",__LINE__);		//throw exception for release mode -- this is a bad error!
		//}
		//win32Ctx->checkHandle();

		/**
		JC - see Win32OpenGLPeer::initGL for the reason for 
		commenting this out.
		*/
		//HWND hwnd = (HWND)(owningControl_->getPeer()->getHandleID());
		//HDC dc = ::GetDC(hwnd);

		//HDC dc = (HDC)glContext_->getPeer()->getContextID();

		wglMakeCurrent( dc, hrc_ );

		//win32Ctx->releaseHandle();
	}
}


/**
$Id$
*/
