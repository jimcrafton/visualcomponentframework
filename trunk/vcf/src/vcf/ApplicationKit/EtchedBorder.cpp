//EtchedBorder.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/EtchedBorder.h"
#include "vcf/GraphicsKit/DrawUIState.h"

using namespace VCF;


EtchedBorder::EtchedBorder():
	sidesToPaint_(GraphicsContext::etAllSides),
	style_(GraphicsContext::etEtched)
{

}

EtchedBorder::EtchedBorder( long sidesToPaint, long style ):
	sidesToPaint_(sidesToPaint),
	style_(style)
{

}


void EtchedBorder::paint( Control* control, GraphicsContext* context )
{
	if ( NULL == control ) {
		throw InvalidPointerException( MAKE_ERROR_MSG_2( "can't paint a border on a NULL Control." ) );
	}
	paint( &control->getClientBounds(false), context );
}

void EtchedBorder::paint( Rect* bounds, GraphicsContext* context )
{
	DrawUIState state;
	state.setActive( true );
	context->drawThemeEdge( bounds, state, sidesToPaint_, style_ );
}

Rect EtchedBorder::getClientRect( Rect* initialBounds, Control* control )
{
	Rect result = *initialBounds;

	double left, top, right, bottom = 0;

	if ( (sidesToPaint_ & GraphicsContext::etLeftSide  ) != 0 ) left   = -2.0;
	if ( (sidesToPaint_ & GraphicsContext::etTopSide   ) != 0 ) top    = -2.0;
	if ( (sidesToPaint_ & GraphicsContext::etRightSide ) != 0 ) right  = -2.0;
	if ( (sidesToPaint_ & GraphicsContext::etBottomSide) != 0 ) bottom = -2.0;

	result.inflate( left, top, right, bottom );

	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:21  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/10/01 17:04:21  dougtinkham
*modified getClientRect to account for absence of border on certain sides
*
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
*Revision 1.1.2.3  2004/07/09 03:39:29  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.2.2.1  2004/06/27 18:19:15  ddiego
*more osx updates
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.5  2003/12/18 05:16:01  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.1  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.4  2003/05/17 20:37:21  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.2  2003/03/23 03:23:55  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.1  2003/03/12 03:12:00  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:46  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.2.1  2002/12/27 23:04:47  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.2  2002/11/18 00:46:09  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.1.2.2  2002/10/08 04:16:57  ddiego
*fixed a bug in the getClientBounds() that caused a stack overflow! DOH!
*further additions to the TemplateNewClassDlg to sync the various file names
*in the dialog to the lcass name
*
*Revision 1.1.2.1  2002/10/01 20:34:59  ddiego
*borders
*
*/


