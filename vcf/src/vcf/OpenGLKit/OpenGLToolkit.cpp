//OpenGLToolkit.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/OpenGLToolkit.h"

#ifdef WIN32
#	include "vcf/OpenGLKit/Win32OpenGLPeer.h"
#endif

using namespace VCF;

OpenGLPeer *OpenGLToolkit::createOpenGLPeer(GraphicsContext *context, OpenGLControl* owningControl){
#ifdef WIN32
	return new Win32OpenGLPeer(context,owningControl);
#else
	throw BasicException("OpenGLToolkit::createOpenGLPeer: Unsupported on this platform");
#endif
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:45  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/27 22:42:47  augusto_roman
*Changed Win32 peer to create GL Rendering Context (RC) based off of the Win32 window handle of the control instead of the paintDC.  Also enforced error checking. - aroman
*
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*/


