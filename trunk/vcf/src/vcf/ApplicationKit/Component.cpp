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
*CVS Log info
*$Log$
*Revision 1.5  2006/04/07 02:35:22  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.4.2.5  2006/03/28 04:12:48  ddiego
*tweaked some function names for the update process.
*
*Revision 1.4.2.4  2006/03/28 04:10:17  ddiego
*tweaked some function names for the update process.
*
*Revision 1.4.2.3  2005/09/16 01:12:01  ddiego
*fixed bug in component loaded function.
*
*Revision 1.4.2.2  2005/08/27 04:49:35  ddiego
*menu fixes.
*
*Revision 1.4.2.1  2005/08/24 05:03:21  ddiego
*better component loading and creation functions.
*
*Revision 1.4  2005/07/09 23:14:52  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.4  2005/06/06 02:34:05  ddiego
*menu changes to better support win32 and osx.
*
*Revision 1.3.2.3  2005/05/15 23:17:37  ddiego
*fixes for better accelerator handling, and various fixes in hwo the text model works.
*
*Revision 1.3.2.2  2005/05/05 12:42:26  ddiego
*this adds initial support for run loops,
*fixes to some bugs in the win32 control peers, some fixes to the win32 edit
*changes to teh etxt model so that notification of text change is more
*appropriate.
*
*Revision 1.3.2.1  2005/02/28 04:51:55  ddiego
*fixed issue in handling componenent state and events when in design mode
*
*Revision 1.3  2004/12/01 04:31:20  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.1  2004/09/21 23:41:23  ddiego
*made some big changes to how the base list, tree, text, table, and tab models are laid out. They are not just plain interfaces. The actual
*concrete implementations of them now derive from BOTH Model and the specific
*tree, table, etc model interface.
*Also made some fixes to the way the text input is handled for a text control.
*We now process on a character by character basis and modify the model one
*character at a time. Previously we were just using brute force and setting
*the whole models text. This is more efficent, though its also more complex.
*
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/09 03:39:28  ddiego
*merged in changes from the OSX branch for new theming API. Added
*support for controlling the use of locale translated strings in components.
*
*Revision 1.1.2.5  2004/07/01 04:02:17  ddiego
*minor stuff
*
*Revision 1.1.2.4  2004/06/05 02:57:09  ddiego
*fixed a syntax mistake that tinkham pointed out.The problem was that the findComponent() method was incorrectly declared.
*
*Revision 1.1.2.3  2004/05/16 02:39:00  ddiego
*OSX code updates
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.28  2004/04/03 15:48:44  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.27  2004/01/20 01:54:56  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.25.2.3  2004/03/28 00:46:22  ddiego
*added VisualFormFiles, fixed some code in the DocumentManager
*class, and changed code over to create an Application class on the
*heap instead of on the stack. This fixes a problem with static object
*destrcutor order when using VC71. Also updated the project wizards
*for vc6. Still need to update docs.
*
*Revision 1.25.2.2  2004/01/16 04:30:46  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.25.2.1  2004/01/15 05:35:04  ddiego
*making some minor changes so that nested menu components get handled
*correctly and added from a VFF file
*
*Revision 1.25  2003/12/18 05:16:00  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.24.2.7  2003/12/13 15:56:08  ddiego
**** empty log message ***
*
*Revision 1.24.2.6  2003/12/08 05:05:28  ddiego
*added a bunch more documentation to classes, and added support for new doc
*keywords (@delegates, @del, @delegate, @event, and @eventtype). This
*makes it easier to see at a glance what events a class fires off.
*Added finishing touches for the Action implementation and have a partially
*complete example for this checked in.
*
*Revision 1.24.2.5  2003/12/02 05:50:05  ddiego
*added preliminary support for teh Action class. This will make it easier
*to hook up complimentary UI elements (such as a "copy" menu item, and a
*"copy" toolbar item) and have tehm respond to update and actions via a
*single source.
*Got rid of the old toolbar button and separator class. Merged in Marcellos
*new fixes for the Container and Splitter classes.
*Some misc fixes to the Toolbar, groups and checks now work correctly.
*
*Revision 1.24.2.4  2003/09/05 21:03:21  ddiego
*moved the various control destructor's to protected scope
*migrated code into destroy() overridden methods
*----------------------------------------------------------------------
*
*Revision 1.24.2.3  2003/09/03 01:41:39  ddiego
*some minor fixes
*
*Revision 1.24.2.2  2003/09/02 02:11:13  ddiego
*fixed some glitches in drag drop. also cleaned up the drag drop event
*classes. Began some fixes to the html browser implementation on Win32
*
*Revision 1.24.2.1  2003/08/18 19:52:37  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.24  2003/08/09 02:56:45  ddiego
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
*Revision 1.23.2.1  2003/07/24 04:10:43  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.23  2003/05/17 20:37:47  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.22.2.2  2003/03/23 03:24:00  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.22.2.1  2003/03/12 03:13:03  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.22  2003/02/26 04:30:55  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.21.14.2  2003/02/24 05:42:19  ddiego
*moved the code for the VariantData calss into it's own header
*migrated to the new event style using Delegates instead of relying on
*the ugly macros that we were using before - same functionality though
*made sure everything still works and compiles, including neccessary
*changes in the VCF Builder so that it creates code in the new style
*This changes to teh new style of using Delegates completes task 58837
*
*Revision 1.21.14.1  2003/01/08 00:19:58  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.21  2002/05/09 03:10:45  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.20.4.1  2002/04/27 15:52:41  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.20  2002/02/20 04:07:59  ddiego
*consolidated event handling code a bit
*introduced a virtual handleEvent() method to Component
*clean up some of the event constants, so they are now localized in the
*appropriate control classes.
*
*Revision 1.19  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


