//ComponentOutputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Control.h"
#include "vcf/ApplicationKit/ComponentOutputStream.h"

using namespace VCF;


ComponentOutputStream::ComponentOutputStream( OutputStream* outStream )
{
	this->outStream_ = outStream;
	needsDTD_ = true;
}

ComponentOutputStream::~ComponentOutputStream()
{

}

void ComponentOutputStream::seek(const unsigned long& offset, const SeekType& offsetFrom)
{
	if ( NULL != this->outStream_ ){
		this->outStream_->seek( offset, offsetFrom );
	}
}

unsigned long ComponentOutputStream::getSize()
{
	if ( NULL != this->outStream_ ){
		return this->outStream_->getSize();
	}

	return 0;
}

char* ComponentOutputStream::getBuffer()
{
	if ( NULL != this->outStream_ ){
		return this->outStream_->getBuffer();
	}
	else{
		return NULL;
	}
}

void ComponentOutputStream::write( char* bytesToWrite, unsigned long sizeOfBytes )
{
	if ( NULL != this->outStream_ ){
		this->outStream_->write( bytesToWrite, sizeOfBytes );
	}
}

void ComponentOutputStream::write( const short& val )
{
	if ( NULL != this->outStream_ ){
		this->outStream_->write( val );
	}
}

void ComponentOutputStream::write( const long& val )
{
	if ( NULL != this->outStream_ ){
		this->outStream_->write( val );
	}
}

void ComponentOutputStream::write( const int& val )
{
	if ( NULL != this->outStream_ ){
		this->outStream_->write( val );
	}
}

void ComponentOutputStream::write( const bool& val )
{
	if ( NULL != this->outStream_ ){
		this->outStream_->write( val );
	}
}

void ComponentOutputStream::write( const char& val )
{
	if ( NULL != this->outStream_ ){
		this->outStream_->write( val );
	}
}

void ComponentOutputStream::write( const float& val )
	{
	if ( NULL != this->outStream_ ){
		this->outStream_->write( val );
	}
}

void ComponentOutputStream::write( const double& val )
{
	if ( NULL != this->outStream_ ){
		this->outStream_->write( val );
	}
}

void ComponentOutputStream::write( const String& val )
{
	if ( NULL != this->outStream_ ){
		String tmp = val + "\n";
		this->outStream_->write( tmp );
	}
}

void ComponentOutputStream::writeComponent( Component* component )
{
	if ( NULL != component ){
		Class* clazz = component->getClass();
		Control* parent = NULL;

		if ( true == needsDTD_ ){
			//dump the DTD
			String hdr = "<?xml version=\"1.0\" standalone=\"no\"?>";
			this->write( hdr );
			ComponentDTD dtd;
			this->write( dtd.toString() );
		}

		needsDTD_ = false;

		if ( NULL != clazz ){
			String tmp = "";
			String strVal = "";
			String propName = "";
			Enumerator<Property*>* props = clazz->getProperties();
			tmp = "<object class=\"" + component->getClassName() + "\" classID=\"" + clazz->getID() + "\">";
			this->write( tmp );

			if ( NULL != props ){
				while ( props->hasMoreElements() ){
					Property* prop = props->nextElement();
					writeProperty( prop, component );
				}
			}//NULL != props
			//now check for children
			Container* container = NULL;
			Control* control = dynamic_cast<Control*>( component );
			if ( NULL != control ) {
				container = control->getContainer();
			}
			if ( NULL != container ){

				Enumerator<Control*>* children = container->getChildren();
				if ( NULL != children ){
					tmp = "<children>";
					this->write( tmp );

					while ( children->hasMoreElements() ){
						Control* child = children->nextElement();
						if ( NULL != child ){
							this->writeComponent( child );
						}
					}

					tmp = "</children>";
					this->write( tmp );
				}
			}

			//now check for Components
			Enumerator<Component*>* components = component->getComponents();
			if ( NULL != components ) {
				tmp = "<components>";
				this->write( tmp );
				while ( true == components->hasMoreElements() ) {
					Component* comp = components->nextElement();
					if ( NULL != comp ) {
						writeComponent( comp );
					}
				}
				tmp = "</components>";
				this->write( tmp );
			}
			tmp = "</object>";
			this->write( tmp );
		}//NULL != clazz
	}
}

void ComponentOutputStream::writePropertyValue( const String& propName, VariantData* value )
{
	String tmp = "";
	if ( NULL != value ){
		tmp = "\t<property name=\"" + propName + "\" ";
		String strVal = "null";
		if ( PROP_OBJECT != value->type ){
			strVal = value->toString();
			tmp += "value=\"" + strVal + "\"/>";
			this->write( tmp );
		}
		else {
			Object* object = *value;
			if ( NULL != object ){
				strVal = object->getClassName();
				tmp += "value=\"" + strVal + "\">";
				this->write( tmp );
				Class* objectClass = object->getClass();
				if ( NULL != objectClass ){
					Enumerator<Property*>* objectProps = objectClass->getProperties();
					tmp = "\t<objectProperty>";
					this->write( tmp );
					if ( NULL != objectProps ){
						while ( objectProps->hasMoreElements() ){
							Property* objectProp = objectProps->nextElement();
							writeProperty( objectProp, object );
						}
					}
					tmp = "\t</objectProperty>";
					this->write( tmp );
				}
				else{
					tmp = "\t<objectProperty></objectProperty>";
					this->write( tmp );
				}
				tmp = "</property>";
				this->write( tmp );
			}
			else {
				tmp += "value=\"null\"/>";
				this->write( tmp );
			}
		}
	}
	else{
		tmp = "\t<property name=\"" + propName + " \"null\"";
		this->write( tmp );
	}
}

void ComponentOutputStream::writeProperty( Property* property, Object* source )
{
	if ( NULL != property ){
		String tmp = "";
		String propName = property->getName();
		if ( true == property->isCollection() ){
			property->startCollection( source );
			while ( property->hasMoreElements( source ) ){
				VariantData* collectionVal = property->nextElement( source );
				writePropertyValue( propName, collectionVal );
			}
		}
		else {
			VariantData* val = property->get();
			this->writePropertyValue( propName, val );
		}
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.8  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.7.4.1  2003/08/18 19:52:39  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.7  2003/05/17 20:37:24  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.6.22.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.6.22.1  2003/03/12 03:12:09  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.6  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


