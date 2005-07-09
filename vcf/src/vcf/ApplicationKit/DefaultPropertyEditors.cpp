//DefaultPropertyEditors.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/DefaultPropertyEditors.h"
#include "vcf/ApplicationKit/ComboBoxControl.h"
#include "vcf/ApplicationKit/TextControl.h"
#include "vcf/ApplicationKit/CommandButton.h"
#include "vcf/ApplicationKit/DefaultListItem.h"
#include "vcf/ApplicationKit/ListBoxControl.h"
#include "vcf/ApplicationKit/Label.h"

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
	CommonColor clrDlg;
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
	CommonFont fontDlg(NULL);
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


