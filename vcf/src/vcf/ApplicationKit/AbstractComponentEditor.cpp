//AbstractComponentEditor.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//AbstractComponentEditor.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AbstractComponentEditor.h"

using namespace VCF;


AbstractComponentEditor::AbstractComponentEditor():
	defaultCommandIndex_(-1),
	component_(NULL)
{
	
}

AbstractComponentEditor::~AbstractComponentEditor()
{

}

void AbstractComponentEditor::initialize()
{
	if ( NULL != component_ ) {
		component_->setComponentState( Component::csDesigning );
	}
}


Command* AbstractComponentEditor::createCommand( const ulong32& index )
{
	return NULL;
}

void AbstractComponentEditor::setComponent( Component* component )
{
	component_ = component;
}

void AbstractComponentEditor::copy()
{
	
}

ulong32 AbstractComponentEditor::getCommandCount()
{
	return attributes_.size();
}

void AbstractComponentEditor::setCommandCount( ulong32 val )
{
	attributes_.clear();
	attributes_.resize( val, ComponentEditor::caUsesModalDialogForEditing );

	parentIndices_.clear();
	parentIndices_.resize( val, -1 );	
}

int AbstractComponentEditor::getCommandParentIndex( const ulong32& index )
{
	return parentIndices_[index];
}

void AbstractComponentEditor::setParentIndex( const ulong32& index, const int& parentIndex )
{
	parentIndices_[index] = parentIndex;
}

int AbstractComponentEditor::getAttributes( const ulong32& index )
{
	return attributes_[index];
}

void AbstractComponentEditor::setAttributes( const ulong32& index, const int& attribute )
{
	attributes_[index] = attribute;
}


/**
*AbstractControlEditor
*/

AbstractControlEditor::AbstractControlEditor()
{

}

AbstractControlEditor::~AbstractControlEditor()
{

}

bool AbstractControlEditor::isParentValid( Control* parent )
{
	return true;
}

Control* AbstractControlEditor::getControl()
{
	return dynamic_cast<Control*>( getComponent() );
}

void AbstractControlEditor::setControl( Control* control )
{
	setComponent( control );
}

void AbstractControlEditor::mouseDown( MouseEvent* event )
{

}

void AbstractControlEditor::mouseMove( MouseEvent* event )
{

}

void AbstractControlEditor::mouseUp( MouseEvent* event )
{

}

void AbstractControlEditor::mouseDblClick( MouseEvent* event )
{

}


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:21  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/08/28 05:14:17  ddiego
*small changes to component editor class.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:12  ddiego
*migration towards new directory structure
*
*Revision 1.8  2004/04/03 15:48:43  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.7  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.6.6.1  2004/01/16 04:30:46  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.6  2003/05/17 20:37:43  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.2.2  2003/03/23 03:23:59  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.5.2.1  2003/03/12 03:12:53  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2003/02/26 04:30:53  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.4.14.1  2003/01/08 00:19:56  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.4  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.3.4.2  2002/04/27 15:52:36  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.3.4.1  2002/04/08 20:55:31  zzack
*changed include style
*
*Revision 1.3  2002/02/14 05:04:52  ddiego
*documentation...
*
*Revision 1.2  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


