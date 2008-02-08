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
	// if ( autoDelete == false ) the ImageControl does not owns the image anymore
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

ImageFilenameString ImageControl::getFilename()
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
		if ( (w < image_->getWidth()) || (h < image_->getHeight()) ) {
			context->drawPartialImage(	maxVal<int>(clientRect.left_,clientRect.left_ + ( (w/2.0) - (image_->getWidth()/2.0) )),
										maxVal<int>(clientRect.top_,clientRect.top_ + ( (h/2.0) - (image_->getHeight()/2.0) )),
										&Rect(0, 0, minVal<int>(w,image_->getWidth()), minVal<int>(h,image_->getHeight() )), image_ );
		}
		else {
			context->drawImage( clientRect.left_ + ( (w/2.0) - (image_->getWidth()/2.0) ),
								clientRect.top_ + ( (h/2.0) - (image_->getHeight()/2.0) ), image_  );
		}
	}
}



ImageFilenamePropertyEditor::ImageFilenamePropertyEditor()
{
	attributes_ = PropertyEditor::paUsesModalDialogForEditing;
}

ImageFilenamePropertyEditor::~ImageFilenamePropertyEditor()
{

}


void ImageFilenamePropertyEditor::edit()
{
	CommonFileOpenDialog dlg;

	ImageFilenameString fileName = *getValue();

	
	dlg.setFileName( fileName );
	if ( true == dlg.execute() ) {
		fileName = dlg.getFileName();		
		VariantData data = fileName;
		setValue( &data );
	}
}




ImagePropertyEditor::ImagePropertyEditor()
{
	attributes_ = PropertyEditor::paUsesModalDialogForEditing;
}

ImagePropertyEditor::~ImagePropertyEditor()
{

}

void ImagePropertyEditor::edit()
{
	
}


ImageComponent::ImageComponent():
	UIComponent(),
	image_(NULL)
{
	delete image_;
}

ImageComponent::~ImageComponent()
{

}


ImageFilenameString ImageComponent::getFilename()
{
	if ( NULL == image_ ) {
		return "";
	}

	return filename_;
}


void ImageComponent::setFilename( const ImageFilenameString& filename )
{
	if ( filename_ != filename ) {
		filename_ = filename;
		if ( NULL != image_ ) {
			delete image_;
			image_ = NULL;
			filename_ = "";
		}
		
		if ( !filename_.empty() ) {
			image_ = GraphicsToolkit::createImage( filename_ );
		}
	}
}

bool ImageComponent::getTransparent()
{
	if ( NULL == image_ ) {
		return false;
	}

	return image_->isTransparent();
}

void ImageComponent::setTransparent( const bool& transparent )
{
	if ( NULL != image_ ) {
		image_->setIsTransparent( transparent );
	}
}

/**
$Id$
*/

