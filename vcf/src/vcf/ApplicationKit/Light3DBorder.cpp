//Light3DBorder.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//Light3DBorder.h
#include "vcf/ApplicationKit/ApplicationKit.h"


using namespace VCF;
Light3DBorder::Light3DBorder():
	inverted_(false)
{
	
}

Light3DBorder::Light3DBorder( bool inverted ):
	inverted_(inverted)
{

}

Light3DBorder::~Light3DBorder()
{

}

void Light3DBorder::paint( Control* control, GraphicsContext* context )
{
	if ( NULL == control ){
		//throw exception
	}
	Rect bounds = control->getClientBounds(false);
	if ( !bounds.isEmpty() ){
		paint( &bounds, context );
	}
}

void Light3DBorder::paint( Rect* bounds, GraphicsContext* context )
{
	if ( NULL != bounds ){


		Color* shadow = NULL;
		if ( true == inverted_ ){
			shadow = GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
		}
		else {
			shadow = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
		}

		Color* hilight = NULL;
		if ( true == inverted_ ){
			hilight = GraphicsToolkit::getSystemColor( SYSCOLOR_SHADOW );
		}
		else {
			hilight = GraphicsToolkit::getSystemColor( SYSCOLOR_HIGHLIGHT );
		}

		Color* face = NULL;
		if ( true == inverted_ ){
			face = GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
		}
		else {
			face = GraphicsToolkit::getSystemColor( SYSCOLOR_FACE );
		}

		if ( true == inverted_ ) {
			context->rectangle( bounds->left_+1, bounds->top_+1, bounds->right_-2, bounds->bottom_-2 );
		}
		else {
			context->rectangle( bounds );
		}

		context->setColor( face );
		context->fillPath();


		context->moveTo( bounds->left_+1, bounds->bottom_-2 );
		context->lineTo( bounds->left_+1, bounds->top_+1 );
		context->lineTo( bounds->right_-2, bounds->top_+1 );

		context->setColor( hilight );

		context->strokePath();

		context->moveTo( bounds->right_-2, bounds->top_+1 );
		context->lineTo( bounds->right_-2, bounds->bottom_-2 );
		context->lineTo( bounds->left_+1, bounds->bottom_-2 );


		context->setColor( shadow );
		context->strokePath();
	}
}

Rect Light3DBorder::getClientRect( Rect* initialBounds, Control* control )
{
	Rect result = *initialBounds;

	result.inflate( -2.0, -2.0 );

	return result;
}



/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/07/15 04:27:14  ddiego
*more updates for edit nc client painting
*
*Revision 1.1.2.4  2004/07/14 21:54:41  ddiego
*attempts to fix problem with borders and drawing on common controls.
*Sort of works on editor control. There is a subtle repaint problem in painting
*damaged portions of the control.
*
*Revision 1.1.2.3  2004/07/11 18:45:34  ddiego
*some toolbar fixes, plus some other minor glithches fixed
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:18  ddiego
*migration towards new directory structure
*
*Revision 1.12  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.2.1  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.11  2003/08/09 02:56:45  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.10.2.1  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.10  2003/05/17 20:37:22  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.2  2003/04/17 04:29:50  ddiego
*updated scintilla, added gtk support for the application kit, with stubs
*for the basic peers.
*
*Revision 1.9.2.1  2003/03/12 03:12:02  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.2.2  2002/12/28 01:56:21  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.8.2.1  2002/12/27 23:04:47  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.8  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.7.10.2  2002/10/08 04:16:57  ddiego
*fixed a bug in the getClientBounds() that caused a stack overflow! DOH!
*further additions to the TemplateNewClassDlg to sync the various file names
*in the dialog to the lcass name
*
*Revision 1.7.10.1  2002/10/01 20:34:59  ddiego
*borders
*
*Revision 1.7  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.6  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


