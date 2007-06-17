//VFFOutputStream.cpp

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/VFFOutputStream.h"

using namespace VCF;


VFFOutputStream::VFFOutputStream( OutputStream* stream ) :
	stream_(stream),
	tabLevel_(0),
	saveUnNamedComponents_(false),
	writeComponentClassID_(true)
{
		
}

String VFFOutputStream::getTabString()
{
	String result = "";
	for ( int i=0;i<tabLevel_;i++) {
		result += "\t";
	}
	return result;
}

String VFFOutputStream::binToHex( Persistable* persistableObject )
{
	String result = "";

	BasicOutputStream bos;
	bos << persistableObject;

	char* buffer = bos.getBuffer();
	char* tmpBuffer = buffer;
	int64 size = 0;//bos.getSize();
	int64 bufSize = bos.getSize();
//	int64 inc =  sizeof( char );
	VCFChar hexBytes[3];
	memset( hexBytes, 0, 3*sizeof(VCFChar) );
	//this is slow, we might want to figure out a better way !
	while ( size < bufSize ) {
		uchar hexVal = *((uchar*)tmpBuffer);
        /*
	#ifdef VCF_POSIX
		swprintf( hexBytes, sizeof(hexBytes), L"%02X", hexVal );
	#else
		swprintf( hexBytes, L"%02X", hexVal );
	#endif
    */
		result += StringUtils::toStringFromHexNumber(hexVal);// hexBytes;
		tmpBuffer++;
		size +=sizeof( char );
	}
	size = result.size();
	return result;
}

void VFFOutputStream::writeObject( Component* component, Object* object, const String& objectPropertyName )
{
	String s;
	String tabString;
	String propertyStrValue;
	String propertyName;

	Persistable* persistable = dynamic_cast<Persistable*>(object);
	if ( NULL != persistable ) {
		String hexString = binToHex( persistable );
		tabString = getTabString();
		tabLevel_ ++;
		String tabString2 = getTabString();
		s = tabString + objectPropertyName + " = {\n" + tabString2 + hexString + "\n" + tabString + "}\n";
		tabLevel_ --;
		stream_->write( s );
	}
	else { //write out the properties
		Class* clazz = object->getClass();
		if ( NULL != clazz ) {
			Enumerator<Property*>* props = clazz->getProperties();
			if ( NULL != props ) {
				tabString = getTabString();
				while ( true == props->hasMoreElements() ) {
					Property* prop = props->nextElement();
					if ( NULL != prop ) {
						VariantData* value = prop->get();
						if ( pdObject == value->type ) {
							Object* obj = (Object*)(*value);
							if ( NULL != obj ) {
								writeObject( component, obj, objectPropertyName + "." + prop->getName() );
							}
							else {
								s = tabString + prop->getName() + " = null\n";
								stream_->write( s );
							}
						}
						else if ( pdString == value->type ) {
							propertyName = objectPropertyName + "." + prop->getName();
							if ( !component->generatePropertyValue( propertyName, prop, value, propertyStrValue ) ) {
								propertyStrValue = value->toString();
							}
							s = tabString + propertyName + " = '" + propertyStrValue + "'\n";
							stream_->write( s );
						}
						else if ( pdEnumMask == value->type ) {
							propertyName = objectPropertyName + "." + prop->getName();

							if ( !component->generatePropertyValue( propertyName, prop, value, propertyStrValue ) ) {
								propertyStrValue = prop->toString();
							}

							s = tabString + propertyName + " = [" + propertyStrValue + "]\n";
							stream_->write( s );
						}
						else {
							propertyName = objectPropertyName + "." + prop->getName();

							if ( !component->generatePropertyValue( propertyName, prop, value, propertyStrValue ) ) {
								propertyStrValue = value->toString();
							}

							s = tabString + propertyName + " = " + propertyStrValue + "\n";
							stream_->write( s );
						}
					}
				}
			}
		}
	}
}

void VFFOutputStream::getComponentHeader( Component* component, String& className, String& classID, String& fallBackClassName )
{
	Class* clazz = component->getClass();
	className = clazz->getClassName();
	classID = clazz->getID();
	fallBackClassName = "";
}

void VFFOutputStream::writeProperty( Component* component, Property* property )
{
	String tabString = getTabString();
	String s;
	String propertyStrValue;

	String propertyName = property->getName();

	VariantData* value = property->get();
	switch ( value->type ) {
		case pdObject : {
			Object* obj = (Object*)(*value);
			if ( NULL != obj ) {
				Component* subComponent = dynamic_cast<Component*>(obj);
				if ( NULL != subComponent ) {
					//this is a reference to a component -
					//we don't want to write it out here otherwise
					//it will be written out twice
					if ( subComponent->getName().empty() ) {
						StringUtils::trace( Format("Warning - property '%s' references an un-named component of type '%s'\n")
							% propertyName % subComponent->getClassName() );
					}
					else {
						s  = tabString + propertyName + " = @" + subComponent->getName() + "\n";
						stream_->write( s );
					}
				}
				else {
					writeObject( component, obj, propertyName );
				}
			}
			else {
				s = tabString + propertyName + " = null\n";
				stream_->write( s );
			}
		}
		break;

		case pdString : {
			if ( !component->generatePropertyValue( propertyName, property, value, propertyStrValue ) ) {
				propertyStrValue = value->toString();
			}
			
			s = tabString + propertyName + " = '" + propertyStrValue + "'\n";
			stream_->write( s );
		}
		break;

		case pdEnumMask : {
			if ( !component->generatePropertyValue( propertyName, property, value, propertyStrValue ) ) {
				propertyStrValue = property->toString();
			}

			s = tabString + propertyName + " = [" + propertyStrValue + "]\n";
			stream_->write( s );
		}
		break;

		default : {
			
			if ( !component->generatePropertyValue( propertyName, property, value, propertyStrValue ) ) {
				propertyStrValue = value->toString();
			}

			s = tabString + propertyName + " = " + propertyStrValue + "\n";
			stream_->write( s );
		}
		break;
	}
}

void VFFOutputStream::writeComponent( Component* component )
{
	if ( !saveUnNamedComponents_ && (component->getName().empty()) ) {
		return;
	}

	Class* clazz = component->getClass();
	String tabString = getTabString();
	if ( NULL != clazz ) {
		String className;// = clazz->getClassName();
		String classID;
		String fallBackClassName;

		getComponentHeader( component, className, classID, fallBackClassName );

		String s = tabString + "object " + component->getName() + " : " + className;
		if ( writeComponentClassID_ ) {
			s += ", \'" + classID + "\'";
		}

		if ( !fallBackClassName.empty() ) {
			s += ", " + fallBackClassName;
		}

		s += "\n";

		stream_->write( s );
		Enumerator<Property*>* props = clazz->getProperties();
		if ( NULL != props ) {
			tabLevel_ ++;
			while ( true == props->hasMoreElements() ) {
				Property* prop = props->nextElement();
				if ( NULL != prop ) {
					writeProperty( component, prop );
				}
			}
			tabLevel_ --;
		}
//		Container* container = NULL;
//		Control* control = dynamic_cast<Control*>( component );
//		if ( NULL != control ) {
//			container = control->getContainer();
//		}

		//std::vector<Component*> componentsAlreadyWritten;
		//std::vector<Component*>::iterator found;

		/*
		if ( NULL != container ) {
			Enumerator<Control*>* children = container->getChildren();
			if ( NULL != children ) {
				tabLevel_ ++;
				while ( true == children->hasMoreElements() ) {
					Control* child = children->nextElement();
					writeComponent( child );
					componentsAlreadyWritten.push_back( child );
				}
				tabLevel_ --;
			}
		}
*/
		Enumerator<Component*>* components = component->getComponents();
		if ( NULL != components ) {
			tabLevel_ ++;
			while ( true == components->hasMoreElements() ) {
				Component* childComponent = components->nextElement();
				//found = std::find( componentsAlreadyWritten.begin(), componentsAlreadyWritten.end(), childComponent );
				//if ( found == componentsAlreadyWritten.end() ) {
					writeComponent( childComponent );
				//}
			}
			tabLevel_ --;
		}


		//write out the events for the components
		writeEvents( component );


		tabString = getTabString();
		s = tabString + "end\n";
		stream_->write( s );
	}	
}

/**
This is used to generate a string that has the 
event handler source name, if possible, followed by an "@"
character, followed by the name of the event handler.
If the name of the source can't be determined, then a 
empty string is returned.
*/
String VFFOutputStream::generateEventHandlerString( EventProperty* eventProperty, EventHandler* handler )
{
	String result;

	Object* source = handler->getSource();
	if ( NULL != source ) {
		//check if it's a component??
		Component* componentSrc = dynamic_cast<Component*>( source );
		if ( NULL != componentSrc ) {
			String srcName = componentSrc->getName();
			String handlerName = handler->getName();
			if ( !srcName.empty() && !handlerName.empty() ) {
				result = srcName + "@" + handlerName;
			}
		}
	}	

	return result;
}

void VFFOutputStream::writeEvents( Component* component )
{
	Class* clazz = component->getClass();
	tabLevel_ ++;
	String tabString = getTabString();
	if ( NULL != clazz ) {
		String s;

		Enumerator<EventProperty*>* events = clazz->getEvents();
		

		bool needsDelegateSection = events->hasMoreElements();

		if ( needsDelegateSection ) {
			s = tabString + "delegates \n";
			stream_->write( s );
		}

		tabLevel_ ++;
		tabString = getTabString();

		tabLevel_ ++;
		String tabString2 = getTabString();

		while ( events->hasMoreElements() ) {
			EventProperty* eventProp = events->nextElement();
			Delegate* eventDelegate = eventProp->getEventDelegate(component);

			if ( NULL != eventDelegate ) {
				EventHandler::Vector handlers;
				String delegateStr;

				if ( eventDelegate->getCallbacks( handlers ) ) {
					
					EventHandler::Vector::iterator it = handlers.begin();
					
					while ( it != handlers.end() ) {
						EventHandler* ev = *it;
						String evStr = generateEventHandlerString( eventProp, ev );

						if ( !evStr.empty() ) {
							if ( it > handlers.begin() ) {
								delegateStr += ", ";
							}
							delegateStr += evStr;
						}
						
						it ++;
					}

					//make sure we don't end up with "[]" an empty set
					if ( !delegateStr.empty() ) {
						s = tabString + eventProp->getDelegateName() + " = [\n";
						s += tabString2 + delegateStr +  "]\n";
						stream_->write( s );
					}
					
					
				}
			}
		}

		tabLevel_ --;

		tabLevel_ --;
		tabString = getTabString();

		if ( needsDelegateSection ) {
			s = tabString + "end\n";
			stream_->write( s );
		}
		
	}

	tabLevel_ --;
}


/**
$Id$
*/
