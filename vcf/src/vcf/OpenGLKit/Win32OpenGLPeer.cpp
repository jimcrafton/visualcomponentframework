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

Win32OpenGLPeer::Win32OpenGLPeer( GraphicsContext* glContext, OpenGLControl* owningControl )
{
	this->glContext_ = glContext;
	this->owningControl_ = owningControl;
	isInitialized_ = false;
}

Win32OpenGLPeer::~Win32OpenGLPeer()
{
	if ( NULL != glContext_ ){
		// We don't need the DC to release the rendering context
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( hrc_ );
	}
}

void Win32OpenGLPeer::initGL()
{
	if ( true == isInitialized_ ){
		return;
	}
	if ( NULL != glContext_ ){
		Win32Context* win32Ctx = dynamic_cast<Win32Context*>(glContext_->getPeer());
		VCF_ASSERT( NULL != win32Ctx );
		if ( NULL == win32Ctx ){
			throw BasicException("Win32OpenGLPeer error: cannot get context peer",__LINE__);		//throw exception for release mode -- this is a bad error!
		}

		win32Ctx->checkHandle();

		/**
		JC  - I commented these out. The problem is that this is always called from a Control::paint
		method, which is turn is called when a WM_PAINT message occurs. Calling GetDC at this point
		I am almost 100% sure is not a good thing. Plus we do not properly clean up (by following
		it with a ReleaseDC() call. using the checkHandle() and releaseHandle() calls will
		do all of this automatically.
		*/
		//HWND hwnd = (HWND)(owningControl_->getPeer()->getHandleID());
		//HDC dc = ::GetDC(hwnd);

		HDC dc = (HDC)win32Ctx->getContextID();
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
				StringUtils::traceWithArgs(String("Error selecting pixelformat for GL context (" __FILE__ ":%d):\n")+errmsg,__LINE__);
				VCF_ASSERT(pixelformat != 0);
				throw BasicException(errmsg);
			}

			bool setPixelSuccess = ( TRUE == ::SetPixelFormat( dc, pixelformat, &pfd ) );
			if ( !setPixelSuccess ){
				String errmsg = VCFWin32::Win32Utils::getErrorString( GetLastError() );
				StringUtils::traceWithArgs(String("Error setting pixelformat for GL context (" __FILE__ ":%d):\n")+errmsg,__LINE__);
				throw BasicException(errmsg);
			}

			hrc_ = wglCreateContext( dc );
			isInitialized_ = ( wglMakeCurrent( dc, hrc_ ) ) ? true : false;
			VCF_ASSERT(isInitialized_);
			win32Ctx->releaseHandle();
		}
	}
}

void Win32OpenGLPeer::swapBuffers()
{
	if ( NULL != glContext_ ){
		Win32Context* win32Ctx = dynamic_cast<Win32Context*>(glContext_->getPeer());
		VCF_ASSERT(NULL != win32Ctx);
		if ( NULL == win32Ctx ){
			throw BasicException("Win32OpenGLPeer error: cannot get context peer",__LINE__);		//throw exception for release mode -- this is a bad error!
		}
		win32Ctx->checkHandle();

		/**
		JC - see Win32OpenGLPeer::initGL for the reason for 
		commenting this out.
		*/
		//HWND hwnd = (HWND)(owningControl_->getPeer()->getHandleID());
		//HDC dc = ::GetDC(hwnd);

		HDC dc = (HDC)win32Ctx->getContextID();

		::SwapBuffers( dc );

		win32Ctx->releaseHandle();
	}
}

void Win32OpenGLPeer::makeCurrent()
{
	if ( NULL != glContext_ ){
		Win32Context* win32Ctx = dynamic_cast<Win32Context*>(glContext_->getPeer());
		VCF_ASSERT(NULL != win32Ctx);
		if ( NULL == win32Ctx ){
			throw BasicException("Win32OpenGLPeer error: cannot get context peer",__LINE__);		//throw exception for release mode -- this is a bad error!
		}
		win32Ctx->checkHandle();

		/**
		JC - see Win32OpenGLPeer::initGL for the reason for 
		commenting this out.
		*/
		//HWND hwnd = (HWND)(owningControl_->getPeer()->getHandleID());
		//HDC dc = ::GetDC(hwnd);

		HDC dc = (HDC)win32Ctx->getContextID();

		wglMakeCurrent( dc, hrc_ );

		win32Ctx->releaseHandle();
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:45  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/11/01 19:39:23  marcelloptr
*minor change
*
*Revision 1.2.2.2  2004/10/31 15:32:29  ddiego
*fixed a bug in the way Win32ControlContext::releaseHandle() worked that was causing a problem in Win32Font::getPointSize().
*
*Revision 1.2.2.1  2004/10/27 22:42:47  augusto_roman
*Changed Win32 peer to create GL Rendering Context (RC) based off of the Win32 window handle of the control instead of the paintDC.  Also enforced error checking. - aroman
*
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 21:13:58  ddiego
*made a few changes to the new OpenGLKit files, adjusting where the
*CVS log was put, and changed a few cases for the export-import definition
*was used. Also added the two projects to the vcfAllProject workspace
*and added the script generated VC7 and VC71 projects as well.
*
*Revision 1.1.2.1  2004/04/29 15:38:12  pallindo
*Initial attempt at an OpenGLKit
*
*Revision 1.1.2.1  2004/04/28 00:28:21  ddiego
*migration towards new directory structure
*
*Revision 1.11  2003/05/17 20:37:38  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.16.2  2003/03/23 03:23:58  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.10.16.1  2003/03/12 03:12:40  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.9.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.9  2002/01/29 04:41:43  ddiego
*fixed leak in Win32Button, plus cleaned up some other GetDC stuff and
*fixed the Tab problem in Win98.
*
*Revision 1.8  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


