//Component.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/VFFInputStream.h"


static long ComponentTagID = 0;

using namespace VCF;

Component::Component():
	owner_(NULL),
	componentState_(Component::csUnknown),
	tag_(ComponentTagID),
	action_(NULL),
	useLocaleStrings_(true)
{
	ComponentTagID++;
	componentContainer_.initContainer( components_ );

	setCreated();
}

Component::Component( Component* owner ):
	owner_(NULL),
	componentState_(Component::csUnknown),
	tag_(ComponentTagID),
	action_(NULL),
	useLocaleStrings_(true)
{
	ComponentTagID++;
	componentContainer_.initContainer( components_ );

	setCreated();

	owner->addComponent( this );
}

Component::Component( const String& name, Component* owner ):
	owner_(NULL),
	componentState_(Component::csUnknown),
	tag_(ComponentTagID),
	action_(NULL),
	useLocaleStrings_(true)
{
	ComponentTagID++;
	componentContainer_.initContainer( components_ );

	setCreated();

	setName( name );
	owner->addComponent( this );
}

Component::Component( const String& name ):
	owner_(NULL),
	componentState_(Component::csUnknown),
	tag_(ComponentTagID),
	action_(NULL),
	useLocaleStrings_(true)
{
	ComponentTagID++;
	componentContainer_.initContainer( components_ );

	setCreated();

	setName( name );
}



Component::~Component()
{

}

void Component::destroy()
{
	if ( !(Component::csDestroying & componentState_) ) {
		VCF::ComponentEvent e( this, Component::COMPONENT_DESTROYED );
		handleEvent( &e );
	}

	Action* action = getAction();
	if ( NULL != action ) {
		action->removeTarget( this );
	
		removeFromUpdateList();	
	}

	std::vector<Component*>::iterator componentIter = components_.begin();
	while ( componentIter != components_.end() ){
		Component* component = *componentIter;
		component->release();
		component = NULL;
		componentIter++;
	}
	components_.clear();	

	ObjectWithEvents::destroy();
}

String Component::getName()
{
	return name_;
}

void Component::setName( const String& name )
{
	name_ = name;
}

void Component::handleEvent( Event* event )
{
	if ( NULL != event ){
		unsigned long eventType = event->getType();

		switch ( eventType ){

			case Component::COMPONENT_CREATED:{
				setNormal();

				ComponentEvent* componentEvent = (ComponentEvent*)event;

				afterCreate( componentEvent);
				ComponentCreated.fireEvent( componentEvent );
			}
			break;

			case Component::COMPONENT_DESTROYED:{
				ComponentEvent* componentEvent = (ComponentEvent*)event;
				beforeDestroy( componentEvent );
				ComponentDestroyed.fireEvent( componentEvent );
			}
			break;

			case Component::COMPONENT_NEEDS_UPDATING : {
				updateAction();
			}
			break;				
		}
	}
}

void Component::beforeDestroy( ComponentEvent* event )
{
	setComponentState( Component::csDestroying );
}


ulong32 Component::getComponentState()
{
	return componentState_;
}

void Component::setComponentState( const ulong32& componentState )
{
	//check for design mode here since we have async creation handling 
	//at the moment
	bool designing = isDesigning();

	componentState_ = componentState;
	
	if ( !(componentState & Component::csDesigning) ) {
		if ( designing ) {
			componentState_ |= Component::csDesigning;
		}
		else {
			componentState_ &= ~Component::csDesigning;
		}
	}

	std::vector<Component*>::iterator it = components_.begin();
	while ( it != components_.end() ){
		Component* child = *it;
		child->setComponentState( componentState_ );
		it ++;
	}
}

void Component::addComponent( Component* component )
{
	//prevent adding duplicates
	std::vector<Component*>::iterator found  = std::find( components_.begin(), components_.end(), component );
	if ( found == components_.end() ){
		if ( NULL != component->owner_ ) {
			component->owner_->removeComponent( component );
		}
		component->owner_ = this;
		components_.push_back( component );

		ComponentEvent e(this,Component::COMPONENT_ADDED);
		e.setChildComponent( component );
		ComponentAdded.fireEvent( &e );
	}
}

void Component::removeComponent( Component* component )
{
	std::vector<Component*>::iterator found  = std::find( components_.begin(), components_.end(), component );
	if ( found != components_.end() ){
		ComponentEvent e(this,Component::COMPONENT_REMOVED);
		e.setChildComponent( component );
		ComponentRemoved.fireEvent( &e );

		(*found)->owner_ = NULL;
		components_.erase( found );
	}
}

void Component::removeFromOwner( const bool& freeInstance )
{
	Component* owner = getOwner();
	if ( NULL != owner ) {
		owner->removeComponent( this );
		if ( freeInstance ) {
			free();
		}
	}	
}

Enumerator<Component*>* Component::getComponents()
{
	return componentContainer_.getEnumerator();
}

unsigned long Component::getComponentCount()
{
	return components_.size();
}

Component* Component::findComponent( const String& componentName, const bool& recursive )
{
	Component* result = NULL;
	//this is very slow !! for the moment !
	std::vector<Component*>::iterator it = components_.begin();
	while ( it != components_.end() ){
		Component* child = *it;
		if ( child->getName() == componentName ){
			result = child;
			break;
		}
		else if (recursive) {
			//call the child component's findComponent
			result = child->findComponent( componentName, recursive );
			if ( NULL != result ) {
				break;
			}
		}
		++ it;
	}

	return result;
}

void Component::afterCreate( ComponentEvent* event )
{

}


/**
*this is a recursive funtion to try and bind a variable name with a particular
*component. This is potentially a fairly expensize operation, because we have to
*recursively search through all the components of the starting component, and
*then through all of it's child controls if the component is a Control Container.
*/
bool Component::bindVariable( Component** variablePtr, const String& variableName )
{
	*variablePtr = NULL;

	bool result = (variableName == getName());
	if ( true == result ) {
		*variablePtr = this;
	}
	if ( false == result ) {
		/**
		*search components first
		*if that fails then try controls - if we are a container
		*/
		Enumerator<Component*>* components = getComponents();
		while ( true == components->hasMoreElements() ) {
			Component* component = components->nextElement();
			if ( variableName == component->getName() ) {
				*variablePtr = component;
				result = true;
			}
			else {
				result = component->bindVariable( variablePtr, variableName );
			}
			if ( true == result ) {
				break;
			}
		}

		if ( false == result ) {
			Control* control = dynamic_cast<Control*>(this);
			if ( NULL != control ) {
				Container* container = control->getContainer();
				if ( NULL != container ){
					//need to do a recursive search until we find a match or run out of
					//components to look for
					Enumerator<Control*>* controls = container->getChildren();
					while ( true == controls->hasMoreElements() ) {
						Control* control = controls->nextElement();
						if ( variableName == control->getName() ) {
							result = true;
							*variablePtr = control;
						}
						else {
							result = control->bindVariable( variablePtr, variableName );
						}
						if ( true == result ) {
							break;
						}
					}
				}
			}
		}
	}
	return result;
}

bool Component::registerComponent( const String& componentClassName, const String& category )
{
	bool result = false;

	Class* componentClass = ClassRegistry::getClass( componentClassName );
	if ( NULL != componentClass ){
		std::map<String,std::vector<Class*>*>::iterator found = registeredComponentMap->find( category );
		std::vector<Class*>* categoryList = NULL;
		if ( found == registeredComponentMap->end() ){
			categoryList = new std::vector<Class*>();
			registeredCategory->push_back( category );
		}
		else {
			categoryList = found->second;
		}
		if ( NULL != categoryList ){
			categoryList->push_back( componentClass );
			(*Component::registeredComponentMap)[category] = categoryList;
			result = true;
		}
	}

	return result;
}

Enumerator<Class*>* Component::getComponentClassesForCategory( const String& category )
{
	Enumerator<Class*>* result = NULL;
	//registeredCompContainer
	std::map<String,std::vector<Class*>*>::iterator found = registeredComponentMap->find( category );
	if ( found != registeredComponentMap->end() ){
		std::vector<Class*>* categoryList = found->second;
		if ( NULL != categoryList ){
			registeredCompContainer->initContainer( *categoryList );
			result = registeredCompContainer->getEnumerator();
		}
	}
	return result;
}

Enumerator<String>* Component::getRegisteredComponentCategories()
{
	registeredCategoryContainer->initContainer( *registeredCategory );
	return registeredCategoryContainer->getEnumerator();
}

void Component::initComponentRegistrar()
{
	registeredComponentMap = new std::map<String,std::vector<Class*>*>();
	registeredCategory = new std::vector<String>();
	registeredCategoryContainer = new EnumeratorContainer<std::vector<String>,String>();
	registeredCompContainer = new EnumeratorContainer<std::vector<Class*>,Class*>();
}

void Component::clearRegistedComponents()
{
	std::map<String,std::vector<Class*>*>::iterator it = registeredComponentMap->begin();
	while ( it != registeredComponentMap->end() ){
		std::vector<Class*>* compList = it->second;
		delete compList;
		compList = NULL;
		it++;
	}
	registeredComponentMap->clear();

	registeredCategory->clear();

	delete registeredCategoryContainer;
	registeredCategoryContainer = NULL;

	delete registeredCompContainer;
	registeredCompContainer = NULL;

	delete registeredComponentMap;
	registeredComponentMap = NULL;

	delete registeredCategory;
	registeredCategory = NULL;
}

void Component::setAction( Action* action )
{
	action_ = action;

	if ( NULL == action_ ) {
		removeFromUpdateList();
	}
	else {
		addToUpdateList();
	}
}

bool Component::updateAction()
{
	Action* action = getAction();
	if ( NULL != action ) {
		action->update();
		return true;
	}

	return false;
}

void Component::addToUpdateList()
{
	UIToolkit::addToUpdateList( this );
}

void Component::removeFromUpdateList()
{
	UIToolkit::removeFromUpdateList( this );
}

void Component::loading()
{
	componentState_ |= Component::csLoading;
}

void Component::saving()
{
	componentState_ |= Component::csSaving;
}

void Component::loaded()
{
	if ( componentState_ & Component::csLoading ) {
		componentState_ &= ~Component::csLoading;
		ComponentEvent e( this, Component::COMPONENT_LOADED );
		ComponentLoaded.fireEvent( &e );
	}
}

void Component::saved()
{
	if ( componentState_ & Component::csSaving ) {
		componentState_ &= ~Component::csSaving;
		ComponentEvent e( this, Component::COMPONENT_SAVED );
		ComponentSaved.fireEvent( &e );
	}
}

bool Component::isNormal() const
{
	return (Component::csNormal & componentState_) ? true : false;
}

bool Component::isDestroying() const
{
	return (Component::csDestroying & componentState_) ? true : false;
}

bool Component::isLoading() const
{
	return (Component::csLoading & componentState_) ? true : false;
}

bool Component::isSaving() const
{
	return (Component::csSaving & componentState_) ? true : false;
}

bool Component::isDesigning() const
{
	return (Component::csDesigning & componentState_) ? true : false;
}

bool Component::isCreated() const
{
	return (Component::csCreated & componentState_) ? true : false;
}

void Component::setCreated()
{
	setComponentState( Component::csCreated );
}

void Component::setNormal()
{
	setComponentState( Component::csNormal );
}

void Component::setDestroying()
{
	setComponentState( Component::csDestroying );
}

void Component::setDesigning( const bool& designing )
{
	if ( designing ) {
		setComponentState( componentState_ | Component::csDesigning );
	}
	else {
		setComponentState( componentState_ & ~Component::csDesigning );
	}
}


void Component::setUseLocaleStrings( const bool& val )
{
	useLocaleStrings_ = val;
	std::vector<Component*>::iterator componentIter = components_.begin();
	while ( componentIter != components_.end() ){
		Component* component = *componentIter;
		component->setUseLocaleStrings( val );
		componentIter++;
	}
}


void Component::initComponent( Component* instance, Class* clazz, Class* rootClazz, ResourceBundle* resBundle ) 
{
	if ( (clazz->getID() == COMPONENT_CLASSID) || (clazz == rootClazz) ) {
		return;
	}

	Component::initComponent( instance, clazz->getSuperClass(), rootClazz, resBundle );

	String resourceName;
	ResourceBundle* bundle = resBundle;
	if ( NULL == bundle ) {
		bundle = System::getResourceBundle();
	}

	String vffContents;

	resourceName = clazz->getClassName();

	vffContents = bundle->getVFF(resourceName);
		
	if ( !vffContents.empty() ) {
		BasicInputStream bis( vffContents );
		VFFInputStream vis( &bis );
		vis.readNewComponentInstance( instance );
	}
}


Component* Component::createComponentFromResources( Class* clazz, Class* rootClazz, ResourceBundle* resBundle )
{
	Component* result = NULL;
	
	VCF_ASSERT( clazz != NULL );

	try {
		Object* newObject = clazz->createInstance();

		result = dynamic_cast<Component*>(newObject);

		if ( NULL != result ) {
			Component::initComponent( result, clazz, rootClazz );
			
			result->loaded();
		}
		else {
			newObject->free();
		}
	}
	catch ( BasicException& ) {

	}

	return result;
}


/**
$Id$
*/
