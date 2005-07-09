#ifndef _VCF_ABSTRACTPROPERTYEDITOR_H__
#define _VCF_ABSTRACTPROPERTYEDITOR_H__
//AbstractPropertyEditor.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

class APPLICATIONKIT_API AbstractPropertyEditor : public ObjectWithEvents, public PropertyEditor {
public:
	AbstractPropertyEditor() : attributes_(0),rootDesignerComponent_(NULL) {

	}

	virtual ~AbstractPropertyEditor(){}

	virtual int getAttributes() {
		return attributes_;
	}

	virtual Control* createEditingControl() {
		return NULL;	
	}

	virtual void edit(){}

	virtual void paintValue( VariantData* value, GraphicsContext* context, const Rect& bounds, const DrawUIState& state ) {}

	virtual VariantData* getValue() {
		return &data_;
	}

	virtual void setValue( VariantData* value ) {
		if ( valueNeedsDuplicating() ) {
			//don't simply set the pointer value, actually 
			//copy it's value from the value variant to our
			//data_ variant
			VCF_ASSERT( (pdObject == data_.type) || (pdUndefined == data_.type) );

			Object* obj = data_;
			Object* obj2 = *value;
			if ( (NULL == obj) && (NULL != obj2) ) {
				data_ = obj2->clone();
			}
			else if ( NULL != obj ) {
				obj->copy( *value );
			}
		}
		else {
			data_ = *value;
		}
	}

	virtual String getValueAsText() {
		return data_.toString();
	}

	virtual void setValueAsText( const String& textValue ) {
		data_.setFromString( textValue );
	}

	virtual std::vector<String> getStringValues(){
		std::vector<String> result;
		return result;
	}

	virtual std::vector<PropertyEditor*> getSubProperties(){
		std::vector<PropertyEditor*> result;
		return result;
	}

	bool sort( const String& strVal1, const String& strVal2 ) {
		return false;
	}

	virtual bool equalTo( PropertyEditor* editor ) {
		if ( NULL == editor ) {
			return false;
		}

		return (typeid(*this) == typeid(*editor)) ? true : false;
	}

	virtual String getPropertyType() {
		return propertyType_;
	}

	virtual void internal_setPropertyType( const String& type ) {
		propertyType_ = type;
	}

	virtual Component* getRootDesignerComponent() {
		return rootDesignerComponent_;
	}

	virtual void setRootDesignerComponent( Component* rootDesigner ) {
		rootDesignerComponent_ = rootDesigner;
	}
protected:
	int attributes_;
	VariantData data_;
	String propertyType_;
	Component* rootDesignerComponent_;
private:

};




}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:50  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/03/11 04:28:21  ddiego
*added some minor modifications to the PropertyEditor interface.
*
*Revision 1.2.4.2  2005/03/09 05:11:19  ddiego
*fixed property editor class.
*
*Revision 1.2.4.1  2005/02/16 05:09:30  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:13  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.4.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.4  2003/05/17 20:36:59  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.2.2  2003/03/23 03:23:44  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.3.2.1  2003/03/12 03:09:12  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.2.14.1  2002/12/25 22:06:13  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.2  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.1.2.1  2002/04/27 15:41:43  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*/


#endif // _VCF_ABSTRACTPROPERTYEDITOR_H__


