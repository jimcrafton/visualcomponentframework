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
	comboBoxHandler_ =
		new ItemEventHandler<BoolPropertyEditor>( this, &BoolPropertyEditor::onSelectionChange, "ComboBoxAdapter" );

}

BoolPropertyEditor::~BoolPropertyEditor()
{

}

Control* BoolPropertyEditor::getCustomEditor()
{
	combo_ = new ComboBoxControl();
	combo_->SelectionChanged.addHandler( comboBoxHandler_ );

	ListModel* lm = combo_->getListModel();
	if ( NULL != lm ){
		lm->addItem( new DefaultListItem( lm, "true" ) );
		lm->addItem( new DefaultListItem( lm, "false" ) );
	}

	bool val = *(this->getValue());
	ulong32 selectedIndex = (val) ? 0 : 1;
	combo_->setSelectedItemIndex( selectedIndex );

	return 	combo_;
}

void BoolPropertyEditor::onSelectionChange( ItemEvent* event )
{
	ListItem* item = (ListItem*)event->getSource();
	if ( NULL != item ){
		ulong32 selectedIndex = item->getIndex();
		this->data_ = (selectedIndex == 0) ? true : false;
	}

}

EnumPropertyEditor::EnumPropertyEditor()
{
	comboBoxHandler_ =
		new ItemEventHandler<EnumPropertyEditor>( this, &EnumPropertyEditor::onSelectionChange, "ComboBoxAdapter" );

}

EnumPropertyEditor::~EnumPropertyEditor()
{

}

Control* EnumPropertyEditor::getCustomEditor()
{
	combo_ = new ComboBoxControl();
	combo_->SelectionChanged.addHandler( comboBoxHandler_ );

	ListModel* lm = combo_->getListModel();

	Enum* val = *(this->getValue());

	int current = val->get();

	int end = val->end();
	int start = val->begin();
	String s1 = val->toString();
	int next = val->next();
	String s2 = val->toString();
	if ( NULL != lm ){
		lm->addItem( new DefaultListItem( lm, s1 ) );
		lm->addItem( new DefaultListItem( lm, s2 ) );
		while ( next != end ) {
			next = val->next();
			lm->addItem( new DefaultListItem( lm, val->toString() ) );
		}
	}

	combo_->setSelectedItemIndex( current );

	return 	combo_;
}

void EnumPropertyEditor::onSelectionChange( ItemEvent* event )
{
	ListItem* item = (ListItem*)event->getSource();
	if ( NULL != item ){
		ulong32 selectedIndex = item->getIndex();
		Enum* val = data_;
		val->set( selectedIndex );

		this->data_ = val;
	}
}



class ColorPanel : public Panel {
public:
	ColorPanel(){

	}

	virtual ~ColorPanel(){

	}

};


ColorPropertyEditor::ColorPropertyEditor()
{

}

ColorPropertyEditor::~ColorPropertyEditor()
{

}

void ColorPropertyEditor::paintValue( GraphicsContext* context, const Rect& bounds )
{
	Color* c = (Color*)(Object*)(*(this->getValue()));
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

Control* ColorPropertyEditor::getCustomEditor()
{
	return new ModalPropertyEditorControl<ColorPropertyEditor>(
			&ColorPropertyEditor::showColorEditor, this->getValue(), this );
}

void ColorPropertyEditor::showColorEditor( VariantData* data )
{
	CommonColor clrDlg;
	Color* c = (Color*)(Object*)(*(this->getValue()));
	clrDlg.setSelectedColor( c );
	if ( true == clrDlg.execute() ){
		VariantData data;
		c->copy( clrDlg.getSelectedColor() );
		data = c;
		this->setValue( &data );
	}
}

FontPropertyEditor::FontPropertyEditor()
{

}

FontPropertyEditor::~FontPropertyEditor()
{

}

void FontPropertyEditor::paintValue( GraphicsContext* context, const Rect& bounds )
{
	Font* f = (Font*)(Object*)(*(this->getValue()));
	Font* oldFont = context->getCurrentFont();
	Color* oldColor = context->getColor();
	Rect innerBds = bounds;

	innerBds.inflate( -2, -2 );
	context->setColor( Color::getColor("black") );
	context->rectangle( &innerBds );
	context->strokePath();

	context->setColor( oldColor );

	innerBds.inflate( -3, 0 );
	//context->setCurrentFont( f );
	context->textAt( innerBds.left_ + 2, innerBds.top_, "ABC" );

	context->setCurrentFont( oldFont );
}

Control* FontPropertyEditor::getCustomEditor()
{
	return new ModalPropertyEditorControl<FontPropertyEditor>(
			&FontPropertyEditor::showFontEditor, this->getValue(), this );
}

void FontPropertyEditor::showFontEditor( VariantData* data )
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

DefaultMenuItemPropertyEditor::DefaultMenuItemPropertyEditor()
{

}

DefaultMenuItemPropertyEditor::~DefaultMenuItemPropertyEditor()
{

}

Control* DefaultMenuItemPropertyEditor::getCustomEditor()
{
	return new ModalPropertyEditorControl<DefaultMenuItemPropertyEditor>(
			&DefaultMenuItemPropertyEditor::showDefaultMenuItemEditor, this->getValue(), this );
}

void DefaultMenuItemPropertyEditor::showDefaultMenuItemEditor( VariantData* data )
{
	Dialog::showMessage( "DefaultMenuItemPropertyEditor::showDefaultMenuItemEditor( VariantData* data )" );
}

DefaultListModelPropertyEditor::DefaultListModelPropertyEditor()
{

}

DefaultListModelPropertyEditor::~DefaultListModelPropertyEditor()
{

}

Control* DefaultListModelPropertyEditor::getCustomEditor()
{
	return new ModalPropertyEditorControl<DefaultListModelPropertyEditor>(
			&DefaultListModelPropertyEditor::showDefaultListModelEditor, this->getValue(), this );
}


void DefaultListModelPropertyEditor::showDefaultListModelEditor( VariantData* data )
{
	Dialog* d = new Dialog();

	d->setBounds( &Rect(400,400,750,650) );

	Panel* contents = new Panel();

	Panel* bottom = new Panel();
	bottom->setBounds( &Rect(0,0,10,30) );
	d->add( bottom, AlignBottom );
	d->add( contents, AlignClient );
	contents->setBorder( NULL );
	bottom->setBorder( NULL );

	CommandButton* okBtn = new CommandButton();
	okBtn->setBounds( &Rect(160,4,240,26) );
	okBtn->setCaption( "OK" );
	okBtn->setCommandType( BC_OK );

	CommandButton* cancelBtn = new CommandButton();
	cancelBtn->setBounds( &Rect(252,4,332,26) );
	cancelBtn->setCaption( "Cancel" );
	cancelBtn->setCommandType( BC_CANCEL );
	bottom->add( okBtn );
	bottom->add( cancelBtn );

	d->setCaption( "Edit List Model" );

	Rect r = contents->getBounds();
	r.inflate( -5,-5 );

	ListBoxControl* lbc = new ListBoxControl();
	lbc->setBounds( &Rect( 5, 5, 120, r.bottom_ ) );
	contents->add( lbc );

	ListModel* lm = lbc->getListModel();

	Label* l = new Label();
	TextControl* tc = new TextControl();
	Rect dlgRect = d->getBounds();
	tc->setBounds( &Rect( dlgRect.getWidth() - 120, 10, dlgRect.getWidth() - 5, 35 ) );
	l->setBounds( &Rect( tc->getLeft() - 80, 10, tc->getLeft(), 35 ) );
	l->setCaption( "Item Caption" );
	contents->add( l );
	contents->add( tc );

	CommandButton* addBtn = new CommandButton();
	Rect tcRect = tc->getBounds();
	addBtn->setBounds( &Rect( tc->getLeft(), tcRect.getBottom() + 10, tc->getLeft() + 80, tcRect.getBottom() + 35 ) );
	addBtn->setCaption( "Add Item" );

	tcRect = addBtn->getBounds();
	CommandButton* removeBtn = new CommandButton();
	removeBtn->setBounds( &Rect( tc->getLeft(), tcRect.getBottom() + 10, tc->getLeft() + 80, tcRect.getBottom() + 35 ) );
	removeBtn->setCaption( "Remove Item" );

	contents->add( addBtn );
	contents->add( removeBtn );

	d->showModal();

	d->free();
	d = NULL;
}


/**
*CVS Log info
*$Log$
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


