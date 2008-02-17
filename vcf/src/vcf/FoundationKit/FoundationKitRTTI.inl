//FoundationKitRTTI.inl

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

	
/**
*A string array for the controls alignement types
*/
static String ComponentSettingScopeNames[] = { "sUser",
                                         "sLocal" };


_class_abstract_rtti_(ObjectWithCallbacks, "VCF::Object", OBJECTWITHCALLBACKS_CLASSID)
_class_rtti_end_


_class_rtti_(ComponentSetting, "VCF::Object", COMPONENTSETTING_CLASSID)
_property_( String, "name", getName, setName, "" );
_property_( String, "section", getSection, setSection, "" );
_property_( VariantData, "value", getValue, setValue, "" );
_property_enum_labeled_( ComponentSetting::Scope, "scope", getScope, setScope,
					   ComponentSetting::sUser, ComponentSetting::sLocal, 2, ComponentSettingScopeNames, "");
_class_rtti_end_

_class_abstract_rtti_(Component, "VCF::ObjectWithCallbacks", COMPONENT_CLASSID)
_property_( int32, "tag", getTag, setTag, "" )
_property_( String, "name", getName, setName, "" )
_property_obj_dictionary_(ComponentSetting,String,"settings",getSetting,assignSetting,getSettingNames,"")
_event_(ComponentDelegate, ComponentCreated );
_event_(ComponentDelegate, ComponentDestroyed );
_event_(ComponentDelegate, ComponentAdded );
_event_(ComponentDelegate, ComponentRemoved );
_event_(ComponentDelegate, ComponentLoaded );
_event_(ComponentDelegate, ComponentSaved );
_class_rtti_end_


};


/**
$Id$
*/
