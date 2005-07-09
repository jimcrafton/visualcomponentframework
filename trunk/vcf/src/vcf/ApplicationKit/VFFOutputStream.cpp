//VFFOutputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/VFFOutputStream.h"

using namespace VCF;

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
	long size = 0;//bos.getSize();
	long bufSize = bos.getSize();
	long inc =  sizeof( char );
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

void VFFOutputStream::writeObject( Object* object, const String& objectPropertyName )
{
	String s;
	String tabString;

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
								writeObject( obj, objectPropertyName + "." + prop->getName() );
							}
							else {
								s = tabString + prop->getName() + " = null\n";
								stream_->write( s );
							}
						}
						else if ( pdString == value->type ) {
							s = tabString + objectPropertyName + "." + prop->getName() + " = '" + value->toString() + "'\n";
							stream_->write( s );
						}
						else if ( pdEnumMask == value->type ) {
							s = tabString + objectPropertyName + "." + prop->getName() + " = [" + prop->toString() + "]\n";
							stream_->write( s );
						}
						else {
							s = tabString + objectPropertyName + "." + prop->getName() + " = " + value->toString() + "\n";
							stream_->write( s );
						}
					}
				}
			}
		}
	}
}

void VFFOutputStream::writeComponent( Component* component )
{
	Class* clazz = component->getClass();
	String tabString = getTabString();
	if ( NULL != clazz ) {
		String className = clazz->getClassName();
		String s = tabString + "object " + component->getName() + " : " + className + ", \'" + clazz->getID() + "\'\n";
		stream_->write( s );
		Enumerator<Property*>* props = clazz->getProperties();
		if ( NULL != props ) {
			tabLevel_ ++;
			tabString = getTabString();
			while ( true == props->hasMoreElements() ) {
				Property* prop = props->nextElement();
				if ( NULL != prop ) {
					VariantData* value = prop->get();
					if ( pdObject == prop->getType() ) {
						Object* obj = (Object*)(*value);
						if ( NULL != obj ) {
							Component* subComponent = dynamic_cast<Component*>(obj);
							if ( NULL != subComponent ) {
								//this is a reference to a component -
								//we don't want to write it out here other wise
								//it will be written out twice
								s  = tabString + prop->getName() + " = @" + subComponent->getName() + "\n";
								stream_->write( s );
							}
							else {
								writeObject( obj, prop->getName() );
							}
						}
						else {
							s = tabString + prop->getName() + " = null\n";
							stream_->write( s );
						}
					}
					else if ( pdString == value->type ) {
						s = tabString + prop->getName() + " = '" + value->toString() + "'\n";
						stream_->write( s );
					}
					else if ( pdEnumMask == value->type ) {
						s = tabString + prop->getName() + " = [" + prop->toString() + "]\n";
						stream_->write( s );
					}
					else {
						s = tabString + prop->getName() + " = " + value->toString() + "\n";
						stream_->write( s );
					}
				}
			}
			tabLevel_ --;
		}
		Container* container = NULL;
		Control* control = dynamic_cast<Control*>( component );
		if ( NULL != control ) {
			container = control->getContainer();
		}

		if ( NULL != container ) {
			Enumerator<Control*>* children = container->getChildren();
			if ( NULL != children ) {
				tabLevel_ ++;
				while ( true == children->hasMoreElements() ) {
					Control* child = children->nextElement();
					writeComponent( child );
				}
				tabLevel_ --;
			}
		}

		Enumerator<Component*>* components = component->getComponents();
		if ( NULL != components ) {
			tabLevel_ ++;
			while ( true == components->hasMoreElements() ) {
				Component* childComponent = components->nextElement();
				writeComponent( childComponent );
			}
			tabLevel_ --;
		}

		tabString = getTabString();
		s = tabString + "end\n";
		stream_->write( s );
	}
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:14:57  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/04/09 17:20:36  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/05/06 02:56:36  ddiego
*checking in OSX updates
*
*Revision 1.1.2.3  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.2  2004/04/28 18:42:25  ddiego
*migrating over changes for unicode strings.
*This contains fixes for the linux port and changes to the Makefiles
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.11.2.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.11  2004/04/03 15:48:49  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.9.2.2  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.9.2.1  2004/01/18 04:52:46  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.9  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.8.4.1  2003/08/18 19:52:39  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.8  2003/05/17 20:37:25  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.1  2003/03/12 03:12:16  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:47  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.8.2  2003/01/08 00:19:51  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6.8.1  2002/12/27 23:04:50  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.5.6.1  2002/09/03 05:05:13  ddiego
*fixed some more bugs in getting form building to work again. It now works
*but of course there are new issues, namely reading in nested properties
*in a form file where the properties are objects like:
*font.color.red, so this needs to be fixed in hte VFFInputStream file
*also need to have hte form saved properly
*still miscellaneous crashes but getting closer to an alpha tes state
*
*Revision 1.5  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.4.4.2  2002/04/27 15:52:23  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.4.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.4  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


