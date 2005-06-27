//ImageControl.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//ImageControl.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ImageControl.h"
#include "vcf/ApplicationKit/DefaultPropertyEditors.h"
#include "vcf/ApplicationKit/CommandButton.h"

using namespace VCF;


ImageControl::ImageControl():
	CustomControl( false )
{
	image_ = NULL;
	transparent_ = false;
	filename_ = "";
	setTabStop(false);
	autoDelete_ = true;
}

ImageControl::~ImageControl()
{
	if ( (NULL != image_) && autoDelete_ ) {
		delete image_;
	}

}

Image* ImageControl::getImage()
{
	return image_;
}

void ImageControl::setImage( Image* image )
{
	if ( (NULL != image_) && autoDelete_ ) {
		delete image_;
		image_ = NULL;
	}

	image_ = image;

	if ( NULL != image_ ) {
		image_->setIsTransparent( transparent_ );
	}
}

bool ImageControl::getTransparent()
{
	return transparent_;
}

void ImageControl::setTransparent( const bool& transparent )
{
	transparent_ = transparent;
	if ( NULL != image_ ) {
		image_->setIsTransparent( transparent_ );
	}
}

ImageFilenameString& ImageControl::getFilename()
{
	return filename_;
}

void ImageControl::setFilename( const ImageFilenameString& filename )
{
	filename_ = filename;
	if ( (NULL != image_) && autoDelete_ ) {
		delete image_;
		image_ = NULL;
	}

	image_ = GraphicsToolkit::createImage( filename_ );
}

void ImageControl::paint( GraphicsContext* context )
{
	CustomControl::paint( context );
	if ( NULL != image_ ) {

		Rect clientRect = getClientBounds();

		double w = clientRect.getWidth();
		double h = clientRect.getHeight();
		if ( (w < image_->getWidth()) && (h < image_->getHeight()) ) {
			context->drawPartialImage( clientRect.left_, clientRect.top_, &Rect(0, 0, w, h ), image_ );
		}
		else {
			context->drawImage( clientRect.left_ + ( (w/2.0) - (image_->getWidth()/2.0) ),
								clientRect.top_ + ( (h/2.0) - (image_->getHeight()/2.0) ), image_  );
		}
	}
}




ImageFilenamePropertyEditor::ImageFilenamePropertyEditor()
{

}

ImageFilenamePropertyEditor::~ImageFilenamePropertyEditor()
{

}

Control* ImageFilenamePropertyEditor::getCustomEditor()
{
	return new ModalPropertyEditorControl<ImageFilenamePropertyEditor>(
			&ImageFilenamePropertyEditor::showFilenameEditor, this->getValue(), this );
}

void ImageFilenamePropertyEditor::showFilenameEditor( VariantData* data )
{
	CommonFileOpen dlg;

	ImageFilenameString& obj = *((ImageFilenameString*)(Object*)*data);

	String s = obj;
	dlg.setFileName( s );
	if ( true == dlg.execute() ) {
		s = dlg.getFileName();
		obj = s;
	}
}




ImagePropertyEditor::ImagePropertyEditor()
{

}

ImagePropertyEditor::~ImagePropertyEditor()
{

}

Control* ImagePropertyEditor::getCustomEditor()
{
	return new ModalPropertyEditorControl<ImagePropertyEditor>(
			&ImagePropertyEditor::showImageEditor, this->getValue(), this );
}

void ImagePropertyEditor::showImageEditor( VariantData* data )
{
	Image* image = (Image*)(Object*)(*data);

	Dialog* dlg = new Dialog();
	dlg->setBounds( &Rect( 0, 0, 410, 520 ) );
	CommandButton* okBtn = new CommandButton();
	okBtn->setBounds( &Rect(240, 460, 320, 485) );
	okBtn->setCaption( "OK" );
	dlg->add( okBtn );

	CommandButton* cancelBtn = new CommandButton();
	cancelBtn->setBounds( &Rect(330, 460, 400, 485) );
	cancelBtn->setCaption( "Cancel" );
	dlg->add( cancelBtn );
	dlg->showModal();
	dlg->free();
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/06/27 16:21:15  scottpearson
*AutoDelete added to ImageControl.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/11 18:45:34  ddiego
*some toolbar fixes, plus some other minor glithches fixed
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.13  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.12.2.1  2004/01/24 16:56:19  ddiego
*general check in
*
*Revision 1.12  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.11.2.2  2003/09/12 00:09:18  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.11.2.1  2003/09/05 21:03:21  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
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
*Revision 1.10.2.1  2003/07/24 04:10:44  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.10  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.9.2.1  2003/03/12 03:13:13  ddiego
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
*Revision 1.8.8.2  2003/01/08 00:20:00  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.8.8.1  2002/12/25 22:06:35  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.8  2002/09/12 03:26:06  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.7.6.1  2002/07/14 05:40:02  ddiego
**** empty log message ***
*
*Revision 1.7  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.2  2002/04/27 15:52:51  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.6.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


