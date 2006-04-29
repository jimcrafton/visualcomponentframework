#ifndef _VCF_DEFAULTPROPERTYEDITORS_H__
#define _VCF_DEFAULTPROPERTYEDITORS_H__
//DefaultPropertyEditors.h

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




namespace VCF {


/**
\class IntegerPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API IntegerPropertyEditor : public AbstractPropertyEditor {
public:
	IntegerPropertyEditor(){};

	virtual ~IntegerPropertyEditor(){};

private:

};

/**
\class DoublePropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API DoublePropertyEditor : public AbstractPropertyEditor {
public:
	DoublePropertyEditor(){};

	virtual ~DoublePropertyEditor(){};

private:

};

/**
\class StringPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API StringPropertyEditor : public AbstractPropertyEditor {
public:
	StringPropertyEditor(){};

	virtual ~StringPropertyEditor(){};

private:

};


/**
\class BoolPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API BoolPropertyEditor : public AbstractPropertyEditor {
public:
	BoolPropertyEditor();

	virtual ~BoolPropertyEditor();

	virtual std::vector<String> getStringValues();
};


/**
\class EnumPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API EnumPropertyEditor : public AbstractPropertyEditor{
public:
	EnumPropertyEditor();

	virtual ~EnumPropertyEditor();	

	virtual std::vector<String> getStringValues();
};



/**
\class EnumSetPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API EnumSetPropertyEditor : public AbstractPropertyEditor{
public:
	EnumSetPropertyEditor();

	virtual ~EnumSetPropertyEditor();
	
	virtual std::vector<PropertyEditor*> getSubProperties();

	virtual String getValueAsText();
};


/**
\class CursorPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API CursorPropertyEditor : public AbstractPropertyEditor{
public:
	CursorPropertyEditor();

	virtual ~CursorPropertyEditor();
	
	virtual std::vector<String> getStringValues();

	virtual void setValueAsText( const String& textValue );

	virtual String getValueAsText();
};


/**
\class ColorPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API ColorPropertyEditor : public AbstractPropertyEditor {
public:
	ColorPropertyEditor();

	virtual ~ColorPropertyEditor();

	virtual void paintValue( VariantData* value, GraphicsContext* context, const Rect& bounds, const DrawUIState& state );

	virtual std::vector<String> getStringValues();

	virtual void edit();

	virtual bool sort( const String& strVal1, const String& strVal2 );

	//takes a value as text - try and look up the text color value
	//in our color list
	virtual void setValueAsText( const String& textValue );	
};



/**
\class FontPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API FontPropertyEditor : public AbstractPropertyEditor {
public:
	FontPropertyEditor();

	virtual ~FontPropertyEditor();

	virtual void paintValue( VariantData* value, GraphicsContext* context, const Rect& bounds, const DrawUIState& state );

	virtual void edit();

	virtual std::vector<PropertyEditor*> getSubProperties();

};


/**
\class DefaultMenuItemPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API DefaultMenuItemPropertyEditor : public AbstractPropertyEditor {
public:
	DefaultMenuItemPropertyEditor();

	virtual ~DefaultMenuItemPropertyEditor();

};


/**
\class DefaultListModelPropertyEditor DefaultPropertyEditors.h "vcf/ApplicationKit/DefaultPropertyEditors.h"
*/
class APPLICATIONKIT_API DefaultListModelPropertyEditor : public AbstractPropertyEditor {
public:
	DefaultListModelPropertyEditor();

	virtual ~DefaultListModelPropertyEditor();
};








};


#endif // _VCF_DEFAULTPROPERTYEDITORS_H__

/**
$Id$
*/
