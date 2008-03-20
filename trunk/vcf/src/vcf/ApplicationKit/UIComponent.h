#ifndef _VCF_UICOMPONENT_H__
#define _VCF_UICOMPONENT_H__
//UIComponent.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif




#define UICOMPONENT_CLASSID		"0B2E533C-BAF6-4AF7-9393-743011B93F81"

namespace VCF {

class Action;




	/**
	\class UIComponent UIComponent.h "vcf/ApplicationKit/UIComponent.h"
	*/
	class APPLICATIONKIT_API UIComponent : public Component {
	public:

		UIComponent();
		
		UIComponent( Component* owner );
		
		UIComponent( const String& name, Component* owner );
		
		UIComponent( const String& name );
		
		/**
		This is protected - you should call free, or release to destroy the component
		*/
		virtual ~UIComponent();

		/**
		Returns the Action associated with this component. Any component
		can have an action associated with it. This allows multiple component
		components (like a menu item, and a push button) to share the same action
		and to respond in a coordinated manner to changes in state.
		*/
		Action* getAction() const {
			return action_;
		}

		/**
		Set's the action for the component.
		*/
		void setAction( Action* action );

		/**
		Calling this triggers an update event to be fired.
		The default behaviour is to see if the component has an action 
		associated with it, and then calls the action's update()
		method. 
		@return bool the method returns true if the component has an
		action and the action's update() method is called. Otherwise 
		it returns false.
		@see Action::update()
		*/
		virtual bool updateAction();

		/**
		Adds the component to the framework's update list. This list
		will be traversed periodically, during idle time, and the 
		framework will create a COMPONENT_NEEDS_UPDATING
		event and pass it to the component. The component can specialize this
		functionality by customizing the behaviour of the handleEvent() method.
		*/
		void addToUpdateList();

		/**
		Removes the component from the framework's update list.
		*/
		void removeFromUpdateList();

		virtual void handleEvent( Event* event );
	protected:
		Action* action_;

		virtual void destroy();
	};
};




#endif //_VCF_UICOMPONENT_H__