#ifndef _VCF_COMPONENT_H__
#define _VCF_COMPONENT_H__
//Component.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/* Generated by Together */



namespace VCF {


class InvalidPeer;
class Dictionary;


#define COMPONENT_CLASSID		"ED88C09B-26AB-11d4-B539-00C04F0196DA"


#define COMPONENTSETTING_CLASSID		"e3cae872-1024-416d-b3a6-f9e9abbd2b8c"

/**
A component setting is a special "value" that may be added 
to a component's settings to be stored when the program 
shuts down, and initialized with the program starts up.

The settings stores it's value in the form of a VariantData
value, which typically is some value that is mapped to a 
property of the component. 

The setting's value has a scope that indicates whether it is 
stored only for the current user account, or stored on the 
local machine (globally). The default scope is user level.
For systems that are single user only (like devices that run
Windows CE), the scope is ignored.

The name of the setting is used to identify the setting's value
to the component where the setting is used. Typically it is the
name of a property, but it doesn't have to be. If it is \em not
the name of a property, then a custom settings loaded method 
needs to be written.
*/
class ComponentSetting : public Object {
public:
	enum Scope {
		sUser = 0,
		sLocal = 1
	};

	ComponentSetting() : scope(ComponentSetting::sUser) {}


	ComponentSetting( const String& n, const VariantData& v ) : 
		name(n), value(v) {}

	ComponentSetting( const String& n, const String& s, const VariantData& v ) : 
		name(n), section(s), value(v) {}


	Scope scope;
	String name;
	String section;
	VariantData value;


	//property getter and setters

	Scope getScope() {
		return scope;
	}

	void setScope( const Scope& val ) {
		scope = val;
	}

	String getName() {
		return name;
	}

	void setName( const String& val ) {
		name = val;
	}

	String getSection() {
		return section;
	}

	void setSection( const String& val ) {
		section = val;
	}

	VariantData getValue() {
		return value;
	}

	void setValue( const VariantData& val ) {
		value = val;
	}
};



/**
\class Component Component.h "vcf/FoundationKit/Component.h"
The base class for all objects within the Visual Component Framework
that wish to manipulated dynamically within the an IDE. All UI controls
are descended from this class.
<p>
Some of the services that are provided are as follows:
<ul>
<li>provides methods for registering components into logical
 	groups, that can then be displayed with an IDE
<li>provides the ability to own other components
<li>the ability to be manipulated by the IDE UI designer
<li>methods for uniquely identifying each instance, either
	by name or by a numerical tag.
</ul>
</p>
<p>
The component itself is a <b>non</b> visual object, thus it can be used
as a base class for a wide variety of things, in addition to serving as
a base class for UI controls. The Component by itself is an abstract class
and should never be created by itself, instead you should be created derived
instances of classes derived from Component.
*
@delegates
  @del Component::ComponentCreated
  @del Component::ComponentDeleted
  @del Component::ComponentAdded
  @del Component::ComponentRemoved
  @del Component::ComponentLoaded
  @del Component::ComponentSaved
*/
class FOUNDATIONKIT_API Component : public ObjectWithCallbacks { //, public Persistable{
protected:
	/**
	The constructor and destructor is hidden - this is an abstract class and should NEVER
	be instantiated directly
	*/
	Component();

	Component( Component* owner );

	Component( const String& name, Component* owner );

	Component( const String& name );

	/**
	This is protected - you should call free, or release to destroy the component
	*/
	virtual ~Component();

	/**
	called by the free() method. Should be overriden
	and any clean up code performed here
	*/
	virtual void destroy();
public:

	/**
	Call this method to free up the memory of the class
	for heap based objects. Use this instead of calling the 
	operator delete. For example:
	\code
	Component*  m = //get some component
	m->free();
	\endcode
	This will ensure that the destroy() method is called 
	\em before calling operator delete which allows a 
	deriving class to override the destroy methods and safely
	call virtual methods from within it.
	*/
	void free();


	enum ComponentEvents{
		COMPONENT_CREATED = 0,
		COMPONENT_DESTROYED,
		COMPONENT_NEEDS_UPDATING,
		COMPONENT_ADDED,
		COMPONENT_REMOVED,
		COMPONENT_LOADED,
		COMPONENT_SAVED,
		COMPONENT_EVENTS_LAST
	};


	/**
	The ComponentState enum represents the current
	state of the component. Some states will prevent
	the Component from responding to events, for example,
	a Control with it state set to CS_DESIGNING, will <b><i>not</i></b>
	respond to certain UI events, while a Control with it's
	state set to CS_DESTROYING, will not respond to any
	pending UI events.
	*/
	enum ComponentState {
		csUnknown=0,
		/**
		csLoading and csReading are mutually exclusive - you can't be read AND writing at the
		same time
		*/
		csLoading = 0x1000,
		csSaving = 0x2000,
		csCreated = 1,
		csDesigning = 0x100,
		csNormal = 3,
		csDestroying = 4,
		csUsesLocaleStrings = 0x10000,
	};

	/**
	generic handler method for events. All UI events
	are sent here and then dispatched accordingly to a
	more specific event handler. If an Application class
	is present, then it is given a chance to "see" the event
	first before delegating it to the Component.
	<p>
	All events are dispatched by their type so it is important
	to correctly identify the event objects type if you would
	like it to be dispatched correctly.
	The method will call the appropriate component method,
	like afterCreate(), beforeDestroy(), etc.
	@param Event based on the value returned by Event::getType(),
	*/
	virtual void handleEvent( Event* event );

	/**
	@delegate ComponentCreated this is called when the component is created. This
	may be <i>after</i> the call to operator new to create the component instance.
	@event ComponentEvent
	@eventtype Component::COMPONENT_CREATED
	*/
	DELEGATE(ComponentDelegate,ComponentCreated)

	/**
	@delegate ComponentDeleted this is fired when the component is being destroyed.
	Handlers attached to this delegate may safely call virtual methods of the component
	as the component's destructor has not yet been called.
	@event ComponentEvent
	@eventtype Component::COMPONENT_DESTROYED
	*/
	DELEGATE(ComponentDelegate,ComponentDestroyed)

	/**
	@delegate ComponentAdded this is fired when a new child component is added
	to this component.
	@event ComponentEvent
	@eventtype Component::COMPONENT_ADDED
	*/
	DELEGATE(ComponentDelegate,ComponentAdded)

	/**
	@delegate ComponentRemoved this is fired when child component is removed
	from this component.
	@event ComponentEvent
	@eventtype Component::COMPONENT_REMOVED
	*/
	DELEGATE(ComponentDelegate,ComponentRemoved)

	/**
	@delegate ComponentLoaded this is fired when child component is done being
	loaded from some InputStream.
	@event ComponentEvent
	@eventtype Component::COMPONENT_LOADED
	*/
	DELEGATE(ComponentDelegate,ComponentLoaded)

	/**
	@delegate ComponentSaved this is fired when child component is removed
	from this component.
	@event ComponentEvent
	@eventtype Component::COMPONENT_SAVED
	*/
	DELEGATE(ComponentDelegate,ComponentSaved)


	/**
	This is called to make sure the csLoading bit is set in the component
	state. Called by streams that read in a component object.
	*/
	void loading();

	/**
	This is called to make sure the csSaving bit is set in the component
	state. Called by streams that write out a component object
	*/
	void saving();

	/**
	Fires an event to the ComponentLoaded delegate. The csLoading bit is removed
	from the component's state.	
	*/
	void loaded();

	/**
	Fires an event to the ComponentSaved delegate. The csSaving bit is removed
	from the component's state.
	*/
	void saved();

	/**
	The name of the component. While technically the name
	can be any character sequence, it is preferred if the
	name follow C++ variable name rules, i.e. must start
	with a character of [a..z] or [A..Z], followed by any
	sequence of characters in the set [a..z,A..Z,0..9,_].
	The name of the component should be unique.
	@return String the name of the component.
	*/
	virtual String getName() ;

	/**
	sets the name of the component. For naming conventions/rules
	please see getName().
	*/
	virtual void setName( const String& name );

	/**
	called just prior to completely destroying the component
	and it's associated memory.
	*/
	virtual void beforeDestroy( ComponentEvent* event );

	/**
	after the component has been created/instantiated
	the afterCreate() method is called. Special initializations
	may then happen here.
	*/
	virtual void afterCreate( ComponentEvent* event );


	/**
	Called when loading the component.
	Control's will re-implement this and set their visible state to false.
	*/
	virtual void preLoading() {}

	/**
	Called after the component is done loading.
	Control's will re-implement this and set their visible state to
	whatever the value of the visible parameter is.
	*/
	virtual void postLoaded( const bool& visible ) {}

	/**
	returns the current state of the component.
	Some states will prevent the Component from responding
	to events, for example, a Control with it's state set to
	CS_DESIGNING, will <b><i>not</i></b> respond to certain
	UI events, while a Control with it's state set to
	CS_DESTROYING, will not respond to any pending UI events.
	*/
	uint32 getComponentState() const;

	/**
	queries the component state to check if it's
	set to csNormal or not.
	@return bool true if component state is csNormal, otherwise false
	*/
	bool isNormal() const ;

	/**
	queries the component state to check if it's
	set to csDestroying or not.
	@return bool true if component state is csDestroying, otherwise false
	*/
	bool isDestroying() const ;

	/**
	queries the component state to check if it's csLoading bit is set or not.
	@return bool true if component state includes csLoading, otherwise false
	*/
	bool isLoading() const ;

	/**
	queries the component state to check if it's csSaving bit is set or not.
	@return bool true if component state includes csSaving otherwise false
	*/
	bool isSaving() const ;

	/**
	queries the component state to check if it's csDesigning bit is set or not.
	@return bool true if component state includes csDesigning otherwise false
	*/
	bool isDesigning() const ;

	/**
	queries the component state to check if it's
	set to csCreated or not.
	@return bool true if component state is csCreated, otherwise false
	*/
	bool isCreated() const;




	/**
	Sets the component's state
	*/
	void setComponentState( const uint32& componentState );

	/**
	convenience fundtions for setting the component state
	*/
	void setCreated();
	void setNormal();
	void setDestroying();
	void setDesigning( const bool& designing );

	/**
	adds a component to this component. Components may contain
	one or more child, or owned, components. When the component is destroyed,
	all owned components are destroyed as well. This is entirely independent
	from the Container interface's add() method. This provides a convenient
	way to clean up memory of components added on the heap. For
	example, a Window may have a popup menu that is created during initialization.
	By adding the popup menu (which is derived from Component), the popup
	menu will be destroyed automatically for you once the Window is
	destroyed. The implementation checks to prevent multiple adds of the
	same component instance in the internal list.
	*/
	virtual void addComponent( Component* component );

	/**
	Adds a brand new child component instance to this component. By
	default this simply calls addComponent(). 
	Re-implemented in the Control class to also handle
	adding to the control's container as well.
	Used by the VFFInputStream class when loading 
	component's up.
	*/
	virtual void addNewComponent( Component* component );

	/**
	removes the component.
	*/
	virtual void removeComponent( Component* component );

	void removeFromOwner( const bool& freeInstance=true );

	/**
	returns an enumeration of all the component's that this
	component currently owns.
	*/
	virtual Enumerator<Component*>* getComponents();

	/**
	returns the number of components owned by this component
	*/
	virtual uint32 getComponentCount() const;

	/**
	finds a particular component as specified by the componentName
	parameter within the list of owned components.
	@param String the name of the component to look for
	@return Component a pointer to the Component with a matching
	name to componentName. If no match is found or the component has
	no owned components, the return value is NULL.
	*/
	virtual Component* findComponent( const String& componentName, const bool& recursive=false );


	virtual bool generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue );

	/**
	Used to bind a variable to a component by attempting to bind the variable
	passed in to the component in the variablePtr parameter to the component
	instance with the same name as the variableName parameter. This functions
	looks at all the owned components first, then checks to see if the Container
	interface is supported, and if so, it checks all the child controls of the
	container.
	@param Component* a pointer to a Component pointer variable
	@param String the name of the component to find
	@return bool true if the component is found, otherwise false
	*/
	virtual bool bindVariable( Component** variablePtr, const String& variableName );

	/**
	returns the Component's tag value. A Tag is borrowed from the
	NeXTStep idea of tags. A unique number is automatically associated
	with the component when it is created, but can be changed by the programmer.
	The following info is lifted directly from the NeXTSTEP docs.
	"Tags are integers that you use in your code to identify objects.
	They offer a convenient alternative to such methods of object identification
	as fetching an object's title.  (What if the object't title changes while the
	application is running, or the object has no title?)"
	@return int32 the tag value of the Component
	*/
	int32 getTag() {
		return tag_;
	}

	/**
	Sets the tag value
	@param int32 - represents the new value of the component's tag will be set to.
	*/
	void setTag( const int32& tag ) {
		tag_ = tag;
	}

	/**
	\p
	Returns the owner of the component. The owner (you could
	also think of this as the component's "parent") is responsible
	for destroying the component when the owner is destroyed.
	@see addComponent()
	*/
	Component* getOwner() const {
		return owner_;
	}	

	/**
	Allows the user to control whether or not the component should 
	attempt to translate the text of a specific component. This is typically 
	used in derived control classes paint() methods, which would check this value
	before calling System::getCurrentThreadLocale()->translate() to 
	translate the text to a specific locale sensitive value. Setting this
	value will also set it for any child components.
	@param bool A boolean value that indicates whether or not a  
	lookup should be made based on the current thread's locale to
	translate any text that needs displaying. A value of true means the
	lookup should take place, a value of false means the lookup should be 
	ignored.
	@see Locale
	@see System::getCurrentThreadLocale
	*/
	void setUseLocaleStrings( const bool& val );

	/**
	Returns a value indicating whether or not the component will attempt 
	to translate any text using the current thread's locale. By
	default, this is true.
	@return bool A boolean value that indicates whether or not a  
	lookup will be made based on the current thread's locale to
	translate any text that needs displaying. A value of true means the
	lookup will take place, a value of false means the lookup will be 
	ignored.

	*/
	bool getUseLocaleStrings() const ;


	
	/**
	Returns the dictionary that holds this component's settings. 
	May return NULL. The default value for a component's settings is
	NULL, so if no settings have been assigned this will definitely
	return NULL.
	*/
	Dictionary* getSettings() const;

	uint32 getSettingNames( std::vector<String>& names );

	/**
	Returns a specific setting specified by the name argument. The 
	name is the key that is used to store the setting in the component's
	settings dictionary. This name may be completely different from the
	setting's value name.
	@see ComponentSetting
	*/
	ComponentSetting* getSetting( const String& name ) const;

	/**
	Assigns a setting to the component's settings dictionary. If the
	setting already exists it's value is modified, otherwise a new setting
	is created. Returns the setting that was modified or created.
	@param String the name setting's key in the dictionary
	@param String the value name of the setting
	@param the value of the setting
	*/
	ComponentSetting* assignSetting( const String& settingName, const String& valueName,
										const VariantData& v );

	/**
	Assigns a setting to the component's settings dictionary. If the
	setting already exists it's value is modified, otherwise a new setting
	is created. Returns the setting that was modified or created. This version
	uses the component's property to get the initial value for the setting. 
	Therefore the value name needs to be a valid component property name.
	@param String the name setting's key in the dictionary
	@param String the value name of the setting. This \em must be a valid,
	existing property name that belongs to the component's Class.
	@see Class
	@see Property
	*/
	ComponentSetting* assignSetting( const String& settingName, const String& valueName );


	void setSetting( const String& settingName, ComponentSetting* setting );	


	virtual void initializeSettings( const bool& recursive );

	virtual void storeSettings( const bool& recursive );



	/**
	registers a component in the system component map. The map is organized into
	a series of keys called categories, with 1 or more entries in each category.
	The UIToolkit registers the default ApplicationKit components, and other developers may
	use this to extend the list with their own components.
	*/
	static bool registerComponent( const String& componentClassName, const String& category );

	/**
	Used by IDE's to list the various Component classes for a given category. Each Class pointer
	that is contained in the Enumerator guarantees the ability to create an instance
	of the component it represents.
	*/
	static Enumerator<Class*>* getComponentClassesForCategory( const String& category );

	/**
	returns a list of all the known, registered, component categories. These in turn
	may be used to gather the classes for each category with a call to the getComponentClassesForCategory()
	static method.
	@see Component::getComponentClassesForCategory()
	*/
	static Enumerator<String>* getRegisteredComponentCategories();

	/**
	*
	*/
	static void initComponentRegistrar();

	/**
	*
	*
	*/
	static void clearRegistedComponents();


	/**
	Takes a valid component instance and initializes it from a VFF file that
	is assumed to be present in the programs resource bundle.
	*/
	static void initComponent( Component* instance, Class* clazz, Class* rootClazz, ResourceBundle* resBundle=NULL );

	static void initComponent( Component* instance, Class* clazz, ResourceBundle* resBundle=NULL );

	static Component* createComponentFromResources( Class* clazz, Class* rootClazz, ResourceBundle* resBundle=NULL );

protected:
	Component* owner_;
	uint32 componentState_;
	String name_;
	int32 tag_;	
	std::vector<Component*> components_;
	EnumeratorContainer<std::vector<Component*>, Component*> componentContainer_;

	mutable Dictionary* settings_;

	/**
	a map of component classes to categories
	*/
	static std::map<String,std::vector<Class*>*>* registeredComponentMap;
	static std::vector<String>* registeredCategory;
	static EnumeratorContainer<std::vector<String>,String>* registeredCategoryContainer;
	static EnumeratorContainer<std::vector<Class*>,Class*>* registeredCompContainer;


	virtual void getAppNameAndKey( String& appName, String& key );

};


}; // namespace VCF


#endif // _VCF_COMPONENT_H__

/**
$Id$
*/
