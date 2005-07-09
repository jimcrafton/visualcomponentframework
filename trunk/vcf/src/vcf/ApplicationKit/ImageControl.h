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


#define IMAGEFILENAMESTRING_CLASSID		"166982EF-60DB-4476-ABF1-AD4EB82B2B08"


#define IMAGECONTROL_CLASSID			"16b4cd34-382c-4b3c-9fe9-f04b5983cd6c"


namespace VCF  {

/**
This is a typedef for a string. This typedef is then used
by the RTTI info for this class (see vcf/ApplicationKit/ApplicationKitRTTI.inl)
to "typedef" the property. So even though this is just a string, the 
proeprty type is a ImageFilenameString, which then allows us to specify
a different kind of PropertyEditor for the string.
*/
typedef String ImageFilenameString;

/**
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







/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3  2005/06/27 16:21:15  scottpearson
*AutoDelete added to ImageControl.
*
*Revision 1.2.4.6  2005/03/28 17:55:51  marcelloptr
*minor fixes
*
*Revision 1.2.4.5  2005/03/28 03:49:08  ddiego
*format changes.
*
*Revision 1.2.4.4  2005/03/27 01:35:02  scottpearson
*Toggling for AutoDelete added.
*
*Revision 1.2.4.3  2005/03/09 05:11:19  ddiego
*fixed property editor class.
*
*Revision 1.2.4.2  2005/02/28 04:51:56  ddiego
*fixed issue in handling componenent state and events when in design mode
*
*Revision 1.2.4.1  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:30  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:17  ddiego
*migration towards new directory structure
*
*Revision 1.8.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.8  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.3  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.7.4.2  2003/09/06 19:45:45  ddiego
*changes to ensure that the destroy() is properly called.
*Destructors were moved back to pbulic scope in case that was causing a bug.
*Moving them all(all teh component derived classes) to private scope causes
*a complete failure in hte VC6 compiler. Alas...
*So destructors are present, and modal dialogs can still be created on the
*stack, but almost any other component should be created on the heap, and
*gotten rid of via free() NOT using operator delete directly.
*also moved the vcs info to the end of the file for some of the headers
*This will be an ongoing process.
*
*Revision 1.7.4.1  2003/09/05 21:03:38  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.7  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.2.1  2003/03/12 03:09:35  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.5.20.2  2002/12/27 23:04:31  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.5.20.1  2002/12/02 00:38:34  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.5  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_IMAGECONTROL_H__


