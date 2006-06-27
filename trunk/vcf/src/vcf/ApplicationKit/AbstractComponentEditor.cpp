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


Command* AbstractComponentEditor::createCommand( const uint32& index )
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

uint32 AbstractComponentEditor::getCommandCount()
{
	return attributes_.size();
}

void AbstractComponentEditor::setCommandCount( uint32 val )
{
	attributes_.clear();
	attributes_.resize( val, ComponentEditor::caUsesModalDialogForEditing );

	parentIndices_.clear();
	parentIndices_.resize( val, -1 );	
}

int AbstractComponentEditor::getCommandParentIndex( const uint32& index )
{
	return parentIndices_[index];
}

void AbstractComponentEditor::setParentIndex( const uint32& index, const int& parentIndex )
{
	parentIndices_[index] = parentIndex;
}

int AbstractComponentEditor::getAttributes( const uint32& index )
{
	return attributes_[index];
}

void AbstractComponentEditor::setAttributes( const uint32& index, const int& attribute )
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
$Id$
*/
