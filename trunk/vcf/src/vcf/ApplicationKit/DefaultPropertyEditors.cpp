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
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:22  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.4  2005/09/17 21:37:43  ddiego
*minor update
*
*Revision 1.3.2.3  2005/09/12 03:47:04  ddiego
*more prop editor updates.
*
*Revision 1.3.2.2  2005/09/02 01:01:20  ddiego
*changed some of the common dialogs around, was using a less clear class name.
*
*Revision 1.3.2.1  2005/08/28 05:14:17  ddiego
*small changes to component editor class.
*
*Revision 1.3  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.3  2005/03/09 05:11:19  ddiego
*fixed property editor class.
*
*Revision 1.2.4.2  2005/02/21 16:20:01  ddiego
*minor changes to various things, property editors, and tree list control.
*
*Revision 1.2.4.1  2005/02/16 05:09:31  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.2  2004/08/07 02:49:07  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.19  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.18.2.1  2004/03/18 04:19:26  ddiego
*some minor stuff for tables
*
*Revision 1.18  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.17.2.2  2003/09/05 21:03:21  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.17.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.17  2003/08/09 02:56:45  ddiego
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
*Revision 1.16.2.1  2003/06/28 04:43:20  ddiego
*cleaned up the vcf/include/events directory and got rid of files, moving
*some of the various event handler template classes into the same header
*that the event handler's event is associated with
*also made some changes to properly take advantage of a Control's View, if it
*is set.
*
*Revision 1.16  2003/05/17 20:37:48  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.15.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.15.2.1  2003/03/12 03:13:07  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.15  2003/02/26 04:30:56  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.14.14.3  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.14.14.2  2003/01/08 00:19:59  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.14.14.1  2002/12/25 22:06:35  ddiego
*whole bunch of little changes to the header files used by the ApplicationKit
*to get rid of no newline warnings by gcc.
*fixes to various event handlers in the ApplicationKit to compile with gcc
*since gcc does not like a member function pointer without the "&"
*addressof operator.
*Added initial file for the X11 UIToolkit implementation
*
*Revision 1.14  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.13.4.2  2002/04/27 15:52:46  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.13.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.13  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


