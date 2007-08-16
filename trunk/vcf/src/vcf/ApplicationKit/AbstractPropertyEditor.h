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

#ifndef _VCF_PROPERTYEDITOR_H__
#include "vcf/ApplicationKit/PropertyEditor.h"
#endif 


namespace VCF {
/**
\class AbstractPropertyEditor AbstractPropertyEditor.h "vcf/ApplicationKit/AbstractPropertyEditor.h"
*/
class APPLICATIONKIT_API AbstractPropertyEditor : public ObjectWithCallbacks, public PropertyEditor {
public:
	AbstractPropertyEditor() : property_(NULL), attributes_(0),rootDesignerComponent_(NULL) {

	}

	virtual ~AbstractPropertyEditor(){}

	virtual void setProperty( Property* property ) {
		property_ = property;
	}

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
			VCF_ASSERT( pdUndefined != data_.type );
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

	virtual String getPropertyDescription() {
		return propertyDescription_;
	}

	virtual String getPropertyName() {
		return propertyName_;
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
	Property* property_;
	int attributes_;
	VariantData data_;
	String propertyType_;
	String propertyDescription_;
	String propertyName_;
	Component* rootDesignerComponent_;
private:

};




}; //end of namespace VCF


#endif // _VCF_ABSTRACTPROPERTYEDITOR_H__

/**
$Id$
*/
