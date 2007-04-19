//FoundationKitRTTI.inl

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {


_class_rtti_(ObjectWithEvents, "VCF::Object", OBJECTWITHEVENTS_CLASSID)
_event_( "VCF::NotifyEventHandler",VCF::NotifyEvent, Notified )
_class_rtti_end_

_class_abstract_rtti_(Component, "VCF::Object", COMPONENT_CLASSID)
_property_( int32, "tag", getTag, setTag, "" );
_property_( String, "name", getName, setName, "" );
_event_("VCF::ComponentEventHandler", VCF::ComponentEvent, ComponentCreated );
_event_("VCF::ComponentEventHandler", VCF::ComponentEvent, ComponentDestroyed );
_event_("VCF::ComponentEventHandler", VCF::ComponentEvent, ComponentAdded );
_event_("VCF::ComponentEventHandler", VCF::ComponentEvent, ComponentRemoved );
_event_("VCF::ComponentEventHandler", VCF::ComponentEvent, ComponentLoaded );
_event_("VCF::ComponentEventHandler", VCF::ComponentEvent, ComponentSaved );
_class_rtti_end_


};


/**
$Id$
*/
