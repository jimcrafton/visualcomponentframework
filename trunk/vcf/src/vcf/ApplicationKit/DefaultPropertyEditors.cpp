//DefaultPropertyEditors.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultPropertyEditors.h"
#include "vcf/ApplicationKit/PropertyEditorManager.h"

#include "vcf/ApplicationKit/ComboBoxControl.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/CommandButton.h"
#include "vcf/ApplicationKit/DefaultListItem.h"
#include "vcf/ApplicationKit/ListBoxControl.h"
#include "vcf/ApplicationKit/Label.h"


#include "vcf/FoundationKit/VCFRTTIImpl.h"

using namespace VCF;





BoolPropertyEditor::BoolPropertyEditor()
{
	attributes_ = PropertyEditor::paHasValues;
}

BoolPropertyEditor::~BoolPropertyEditor()
{

}

std::vector<String> BoolPropertyEditor::getStringValues(){
	std::vector<String> result(2);
	result[0] = StringUtils::toString(true);
	result[1] = StringUtils::toString(false);
	return result;
}

EnumPropertyEditor::EnumPropertyEditor()
{
	attributes_ = PropertyEditor::paHasValues;
}

EnumPropertyEditor::~EnumPropertyEditor()
{

}

std::vector<String> EnumPropertyEditor::getStringValues(){
	std::vector<String> result;
	

	Enum* val = *(this->getValue());
	int current = val->get();
	int end = val->end();
	int start = val->begin();
	
	result.push_back( val->toString() );	

	int next = val->next();

	while ( next != end ) {
		result.push_back( val->toString() );
		next = val->next();		
	}
	
	val->end();

	result.push_back( val->toString() );

	return result;
}

class EnumSetItemPropertyEditor : public BoolPropertyEditor {
public:
	EnumSetItemPropertyEditor( const String& itemName, 
								const unsigned long& enumSetElement,
								const unsigned long& enumVal,
								PropertyEditor* parent ) {
		attributes_ |= PropertyEditor::paCompositeValue | PropertyEditor::paOverridePropertyName;
		propertyName_ = itemName;
		enumSetElement_ = enumSetElement;
		enumVal_ = enumVal;
		parent_ = parent;
	}

	virtual ~EnumSetItemPropertyEditor() {}

	virtual void setValueAsText( const String& textValue ) {
		BoolPropertyEditor::setValueAsText( textValue );

		enumVal_ = *parent_->getValue();

		bool val = data_;
		if ( val ) {
			enumVal_ |= enumSetElement_;
		}
		else {
			enumVal_ &= ~enumSetElement_;
		}

		VariantData enumVal = enumVal_;
		enumVal.type = pdEnumMask;
		parent_->setValue(&enumVal) ;
	}

	virtual void setValue( VariantData* value ) {
		BoolPropertyEditor::setValue( value );

		enumVal_ = *parent_->getValue();

		bool val = data_;

		if ( val ) {
			enumVal_ |= enumSetElement_;
		}
		else {
			enumVal_ &= ~enumSetElement_;
		}


		VariantData enumVal = enumVal_;
		enumVal.type = pdEnumMask;
		parent_->setValue(&enumVal) ;
	}
	
protected:
	unsigned long enumSetElement_;
	unsigned long enumVal_;
	PropertyEditor* parent_;
};


EnumSetPropertyEditor::EnumSetPropertyEditor()
{
	attributes_ = PropertyEditor::paHasSubProperties | PropertyEditor::paEditorRequestsProperty;
}

EnumSetPropertyEditor::~EnumSetPropertyEditor()
{

}

String EnumSetPropertyEditor::getValueAsText()
{
	String result;

	if ( NULL != property_ ) {
		if ( pdEnumMask == property_->getType() ) {
			EnumSetProperty* enumSetProp = (EnumSetProperty*)property_;

			std::vector<String> names;
			std::vector<unsigned long> values;

			
			if ( enumSetProp->getNameValuesAsSet( names, values ) ) {
				unsigned long val = *getValue();
				std::vector<String>::iterator it = names.begin();
				std::vector<unsigned long>::iterator it2 = values.begin();
				VariantData boolVal;

				while ( it != names.end() ) {

					if ( val & *it2 ) {
						if ( !result.empty() ) {
							result += ", ";
						}
						result += *it;
					}

					it ++;
					it2 ++;
				}
			}
		}
	}
	return result;
}

std::vector<PropertyEditor*> EnumSetPropertyEditor::getSubProperties()
{
	std::vector<PropertyEditor*> result;	
	
	if ( NULL != property_ ) {
		if ( pdEnumMask == property_->getType() ) {
			EnumSetProperty* enumSetProp = (EnumSetProperty*)property_;

			std::vector<String> names;
			std::vector<unsigned long> values;

			
			if ( enumSetProp->getNameValuesAsSet( names, values ) ) {
				unsigned long val = *getValue();

				std::vector<String>::iterator it = names.begin();
				std::vector<unsigned long>::iterator it2 = values.begin();
				VariantData boolVal;

				while ( it != names.end() ) {
					PropertyEditor* editor = 
						new EnumSetItemPropertyEditor( *it, *it2, val, this );
					
					boolVal = (val & *it2) ? true : false;

					editor->setValue( &boolVal );
					editor->setRootDesignerComponent( getRootDesignerComponent() );

					result.push_back( editor );
					it ++;
					it2 ++;
				}
			}
		}
	}

	return result;
}

static String cursorNames[] = { "Cursor::SCT_DEFAULT",
		"Cursor::SCT_CROSSHAIRS",
		"Cursor::SCT_SPLIT_VERT",
		"Cursor::SCT_SPLIT_HORZ",
		"Cursor::SCT_SIZE_HORZ",
		"Cursor::SCT_SIZE_VERT",
		"Cursor::SCT_SIZE_NE_SW",
		"Cursor::SCT_SIZE_NW_SE",
		"Cursor::SCT_TEXT",
		"Cursor::SCT_HELP",
		"Cursor::SCT_NOWAYHOSER",
		"Cursor::SCT_WAITING",
		"Cursor::SCT_POINTING_HAND",
		"Cursor::SCT_WAIT" };

CursorPropertyEditor::CursorPropertyEditor()
{
	attributes_ = PropertyEditor::paHasValues;
}

CursorPropertyEditor::~CursorPropertyEditor()
{

}

std::vector<String> CursorPropertyEditor::getStringValues()
{
	std::vector<String> result( sizeof(cursorNames)/sizeof(String) );

	for (int i=0;i<result.size();i++ ) {
		result[i] = cursorNames[i];
	}
	

	return result;
}

void CursorPropertyEditor::setValueAsText( const String& textValue )
{
	data_ = (long)(Cursor::SCT_DEFAULT);

	int len = sizeof(cursorNames)/sizeof(String);
	for (int i=0;i<len;i++ ) {
		if ( cursorNames[i] == textValue ) {

			data_ = (long)(Cursor::SCT_DEFAULT) + i;
			break;
		}
	}
}

String CursorPropertyEditor::getValueAsText()
{
	String result;

	long val = data_;
	val = val - (long)(Cursor::SCT_DEFAULT);
	if ( (val >=0) && (val < sizeof(cursorNames)/sizeof(String)) ) {
		result = cursorNames[val];
	}

	return result;
}


ColorPropertyEditor::ColorPropertyEditor()
{
	attributes_ = PropertyEditor::paHasValues | PropertyEditor::paUsesModalDialogForEditing | 
					PropertyEditor::paNeedsCustomPaint | PropertyEditor::paSortValues |
					PropertyEditor::paValueNeedsDuplicating;
}

ColorPropertyEditor::~ColorPropertyEditor()
{

}

void ColorPropertyEditor::paintValue( VariantData* value, GraphicsContext* context, const Rect& bounds, const DrawUIState& state )
{
	Color* c = (Color*)(Object*)(*value);
	Color* oldColor = context->getColor();

	Rect innerBds = bounds;

	innerBds.inflate( -2, -2 );
	context->setColor( Color::getColor("black") );
	context->rectangle( &innerBds );
	context->strokePath();

	innerBds.inflate( -3, -3 );
	context->setColor( c );
	context->rectangle( &innerBds );
	context->fillPath();
	context->setColor( oldColor );
}

void ColorPropertyEditor::setValueAsText( const String& textValue )
{
	//AbstractPropertyEditor::data_
	Color* color = Color::getColor(textValue);
	if ( NULL != color ) {
		Color* valColor = (Color*) (Object*)data_;
		if ( NULL != valColor ) {
			*valColor = *color;
		}
	}
	else {
		AbstractPropertyEditor::setValueAsText( textValue );
	}
}


void ColorPropertyEditor::edit()
{
	CommonColorDialog clrDlg;
	Color* c = (Color*)(Object*)(*(this->getValue()));
	clrDlg.setSelectedColor( c );
	if ( clrDlg.execute() ) {
		VariantData data;
		*c = *clrDlg.getSelectedColor();
		data = c;
		setValue( &data );
	}
}

bool ColorPropertyEditor::sort( const String& strVal1, const String& strVal2 )
{
	return strVal1 > strVal2;
}

std::vector<String> ColorPropertyEditor::getStringValues()
{
	int count = ColorNames::uniqueColorLast-ColorNames::uniqueColorFirst;
	std::vector<String> result(count);

	for ( int i=ColorNames::uniqueColorFirst;i<ColorNames::uniqueColorLast;i++ ) {
		result[i-ColorNames::uniqueColorFirst] = ColorNames::at( (ColorNames::ColorID)i );
	}

	return result;
}


FontPropertyEditor::FontPropertyEditor()
{
	//later on it would be nice to be able to get the list of system fonts here
	attributes_ = PropertyEditor::paUsesModalDialogForEditing | 
					PropertyEditor::paNeedsCustomPaint |
					PropertyEditor::paHasSubProperties;
}

FontPropertyEditor::~FontPropertyEditor()
{

}

void FontPropertyEditor::paintValue( VariantData* value, GraphicsContext* context, const Rect& bounds, const DrawUIState& state )
{
	int gcs = context->saveState();

	Font* f = (Font*)(Object*)(*value);
	Font fontCopy = *f;
	fontCopy.setPixelSize( 10 );
	
	Rect innerBds = bounds;

	innerBds.inflate( -2, -2 );
	context->setColor( Color::getColor("black") );
	context->rectangle( &innerBds );
	context->strokePath();

	innerBds.inflate( -3, 0 );
	context->setCurrentFont( &fontCopy );
	context->textAt( innerBds.left_ + 2, innerBds.top_, "ABC" );

	context->restoreState(gcs);
}


void FontPropertyEditor::edit()
{
	CommonFontDialog fontDlg(NULL);
	Font* f = (Font*)(Object*)(*(this->getValue()));
	fontDlg.setSelectedFont( f );
	if ( true == fontDlg.execute() ){
		VariantData data;
		f->copy( fontDlg.getSelectedFont() );
		data = f;
		this->setValue( &data );
	}
}

std::vector<PropertyEditor*> FontPropertyEditor::getSubProperties()
{
	std::vector<PropertyEditor*> result;

	Class* fontClass = ClassRegistry::getClass( "VCF::Font" );
	
	if ( NULL != fontClass ) {
		Enumerator<Property*>* properties = fontClass->getProperties();

		while ( properties->hasMoreElements() ) {
			Property* property = properties->nextElement();
			Object* obj = *getValue();
			property->setSource( obj );

			PropertyEditor* editor = PropertyEditorManager::createEditor( property->getTypeClassName () );
			if ( NULL != editor ) {
				result.push_back( editor );
			}
		}
	}

	return result;
}

DefaultMenuItemPropertyEditor::DefaultMenuItemPropertyEditor()
{

}

DefaultMenuItemPropertyEditor::~DefaultMenuItemPropertyEditor()
{

}

DefaultListModelPropertyEditor::DefaultListModelPropertyEditor()
{

}

DefaultListModelPropertyEditor::~DefaultListModelPropertyEditor()
{

}


/**
$Id$
*/
