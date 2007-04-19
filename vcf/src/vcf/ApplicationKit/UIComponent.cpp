//UIComponent.cpp

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationPeer.h"


using namespace VCF;


UIComponent::UIComponent():	
	Component(),
	action_(NULL)
{
	
}

UIComponent::UIComponent( Component* owner ):
	Component(owner),
	action_(NULL)
{
	
}

UIComponent::UIComponent( const String& name, Component* owner ):
	Component(name, owner),
	action_(NULL)
{
	
}

UIComponent::UIComponent( const String& name ):
	Component(name),
	action_(NULL)
{
	
}



UIComponent::~UIComponent()
{
	
}


void UIComponent::destroy()
{
	Action* action = getAction();
	if ( NULL != action ) {
		action->removeTarget( this );
	
		removeFromUpdateList();	
	}

	Component::destroy();
}


void UIComponent::setAction( Action* action )
{
	action_ = action;

	if ( NULL == action_ ) {
		removeFromUpdateList();
	}
	else {
		addToUpdateList();
	}
}

bool UIComponent::updateAction()
{
	Action* action = getAction();
	if ( NULL != action ) {
		action->update();
		return true;
	}

	return false;
}

void UIComponent::addToUpdateList()
{
	UIToolkit::addToUpdateList( this );
}

void UIComponent::removeFromUpdateList()
{
	UIToolkit::removeFromUpdateList( this );
}


void UIComponent::handleEvent( Event* event )
{
	Component::handleEvent( event );

	if ( NULL != event ){
		uint32 eventType = event->getType();

		switch ( eventType ) {
			case Component::COMPONENT_NEEDS_UPDATING : {
				updateAction();
			}
			break;
		}
	}
}