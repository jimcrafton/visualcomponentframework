//OpenGLControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/OpenGLKit/OpenGLKit.h"
#include "vcf/OpenGLKit/VCFOpenGL.h"
using namespace VCF;

OpenGLControl::OpenGLControl():
	CustomControl( true )
{
	delete this->context_;
	context_ = NULL;
	context_ = new OpenGLControlContext( this );

	setDoubleBuffered( false );
}

OpenGLControl::~OpenGLControl()
{

}

void OpenGLControl::paint(GraphicsContext * context)
{
//	Do NOT call CustomControl::paint because it results in flashing, possibly due to the
//	CustomControl clearing the space with the color, and then the OpenGLControl reclearing it.
//	CustomControl::paint( context );

	// These initialize the context, if necesary (check is in initGL), and then make it current
	OpenGLControlContext* glCtx = dynamic_cast<OpenGLControlContext*>(context_);
	if ( NULL != glCtx ){
		glCtx->initGL();
		glCtx->makeCurrent();
	}
}

void OpenGLControl::swapBuffers(){
	OpenGLControlContext* glCtx = dynamic_cast<OpenGLControlContext*>(context_);
	if ( NULL != glCtx ){
		glCtx->swapBuffers();
	}
}

void OpenGLControl::afterCreate( ComponentEvent* event )
{
	CustomControl::afterCreate( event );
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:19  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.7  2004/07/21 20:18:39  pallindo
*Removed some unused files, and cleaned up the interface to the OpenGLControl
*
*Revision 1.1.2.6  2004/07/06 06:45:02  pallindo
*Forgot to remove the reference to aux
*
*Revision 1.1.2.5  2004/06/06 07:05:34  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.4  2004/06/04 15:39:51  thrysoee
*Rollback accidental commit of Linux/freeglut changes
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
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.8  2003/05/17 20:37:49  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.1  2003/03/12 03:13:17  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.14.1  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.5  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


