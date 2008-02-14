#ifndef _VCF_IMAGECONTROL_H__
#define _VCF_IMAGECONTROL_H__
//ImageControl.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_ABSTRACTPROPERTYEDITOR_H__
#include "vcf/ApplicationKit/AbstractPropertyEditor.h"
#endif 

#define IMAGEFILENAMESTRING_CLASSID		"166982EF-60DB-4476-ABF1-AD4EB82B2B08"


#define IMAGECONTROL_CLASSID			"16b4cd34-382c-4b3c-9fe9-f04b5983cd6c"

#define IMAGECOMPONENT_CLASSID			"a95da66a-c1fb-4a38-a052-f66b95b55969"

namespace VCF  {



/**
This is a typedef for a string. This typedef is then used
by the RTTI info for this class (see vcf/ApplicationKit/ApplicationKitRTTI.inl)
to "typedef" the property. So even though this is just a string, the 
property type is a ImageFilenameString, which then allows us to specify
a different kind of PropertyEditor for the string.
*/
typedef String ImageFilenameString;






/**
\class ImageComponent ImageControl.h "vcf/ApplicationKit/ImageControl.h"

*/
class APPLICATIONKIT_API ImageComponent : public UIComponent {
public:

	DELEGATE(EventDelegate,ImageChanged);

	ImageComponent();

	virtual ~ImageComponent();

	Image* getImage() {
		return image_;
	}

	ImageFilenameString getFilename();

	void setFilename( const ImageFilenameString& filename );

	bool getTransparent();

	void setTransparent( const bool& transparent );
protected:
	Image* image_;
	ImageFilenameString filename_;
};




/**
\class ImageControl ImageControl.h "vcf/ApplicationKit/ImageControl.h"
*Class ImageControl documentation
*/
class APPLICATIONKIT_API ImageControl : public VCF::CustomControl {
public:

	ImageControl();
	virtual ~ImageControl();

	Image* getImage();

	void setImage( Image* image );

	bool getTransparent();

	void setTransparent( const bool& transparent );

	ImageFilenameString getFilename();

	void setFilename( const ImageFilenameString& filename );

	virtual void paint( GraphicsContext* context );
	
	void setAutoDelete( const bool& autoDelete ) {
		autoDelete_ = autoDelete;
	}
	
	bool getAutoDelete() {
		return autoDelete_;
	}


protected:


private:
	Image* image_;
	bool transparent_;
	ImageFilenameString filename_;
	bool autoDelete_;
};


class APPLICATIONKIT_API ImageFilenamePropertyEditor : public AbstractPropertyEditor {
public:
	ImageFilenamePropertyEditor();

	virtual ~ImageFilenamePropertyEditor();

	virtual void edit();

};

class APPLICATIONKIT_API ImagePropertyEditor : public AbstractPropertyEditor {
public:
	ImagePropertyEditor();

	virtual ~ImagePropertyEditor();
	
	void edit();
private:

};

}; //end of namespace VCF


#endif // _VCF_IMAGECONTROL_H__

/**
$Id$
*/
