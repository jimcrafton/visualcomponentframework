//DefaultColumnItem.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//DefaultColumnItem.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultColumnItem.h"
#include "vcf/ApplicationKit/DefaultColumnModel.h"


using namespace VCF;




DefaultColumnItem::DefaultColumnItem()
{
	index_ = 0;
	data_ = NULL;
	model_ = NULL;
	width_ = 100.0;
	imageIndex_ = -1;
	textAlignment_ = taTextLeft;
	tag_ = -1;
}

DefaultColumnItem::~DefaultColumnItem()
{

}

bool DefaultColumnItem::containsPoint( Point * pt )
{
	return false;
}

unsigned long DefaultColumnItem::getIndex()
{
	return index_;
}

void DefaultColumnItem::setIndex( const unsigned long& index )
{
	index_ = index;
}

void DefaultColumnItem::setImageIndex( const long& imageIndex )
{
	imageIndex_ = imageIndex;
}

void DefaultColumnItem::setData( void* data )
{
	data_ = data;

	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}

void DefaultColumnItem::setCaption( const String& caption )
{
	caption_ = caption;
	ItemEvent event( this, ITEM_EVENT_TEXT_CHANGED );
	ItemChanged.fireEvent( &event );
}

Model* DefaultColumnItem::getModel()
{
	return model_;
}

void DefaultColumnItem::setModel( Model* model )
{
	model_ = dynamic_cast<ColumnModel*>( model );
}

void DefaultColumnItem::paint( GraphicsContext* context, Rect* paintRect )
{
	bounds_ = *paintRect;
	ItemEvent event( this, context );
	ItemPaint.fireEvent( &event );
}

bool DefaultColumnItem::isSelected()
{
	return selected_;
}

void DefaultColumnItem::setSelected( const bool& selected )
{
	selected_ = selected;

	ItemEvent event( this, ITEM_EVENT_SELECTED );
	ItemChanged.fireEvent( &event );
}

void DefaultColumnItem::setCaptionAlignment( const TextAlignmentType& alignment )
{
	textAlignment_ = alignment;
	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}

void DefaultColumnItem::setWidth( const double& width )
{
	width_ = width;
	ItemEvent event( this, ITEM_EVENT_CHANGED );
	ItemChanged.fireEvent( &event );
}


void DefaultColumnItem::setBounds( Rect* bounds )
{
	bounds_ = *bounds;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
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
*Revision 1.10.2.1  2003/06/30 02:53:16  ddiego
*Allow getting the selected filter from a CommonFileDialog
*Added a quitCurrentEventLoop to the UIToolkit to allow programatic
*termination of a program if there is no main window specified
*added a getTag method to the Item class
*
*Revision 1.10  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.9.2.1  2003/03/12 03:13:05  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.9  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.8.14.2  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.8.14.1  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.2  2002/04/27 15:52:44  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.7.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.7  2002/03/03 18:33:44  ddiego
*fixed some display errors in the TreeListControl and added support for ImagLists to
*the HeaderControl
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


