//ComponentInputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/VCFChar.h"
#include "vcf/ApplicationKit/ComponentInputStream.h"

#include <util/XMLUni.hpp>
#include <sax/AttributeList.hpp>
#include <framework/MemBufInputSource.hpp>
#include <util/PlatformUtils.hpp>
#include<util/XMLUniDefs.hpp>
#include <parsers/SAXParser.hpp>




using namespace VCF;
using namespace std;

ComponentInputStream::ComponentInputStream(  InputStream* inStream  )
{
	this->init();
	this->inStream_ = inStream;
	doEscapes_ = false;
}

ComponentInputStream::~ComponentInputStream()
{
	this->collectionPropertyMap_.clear();
	this->containerPropertyMap_.clear();
	this->objectPropertyMap_.clear();
}

void ComponentInputStream::init()
{
	this->component_ = NULL;
	this->currentContainer_ = NULL;
	this->prevContainer_ = NULL;
	this->inStream_ = NULL;
	objectPropertyLevel_ = 0;
	collectionPropertyLevel_ = 0;
	containerLevel_ = 0;
	currentObjectProperty_ = NULL;
	topLevelControl_ = NULL;
	topLevelComponentAlreadyExists_ = false;
}


void ComponentInputStream::seek(const unsigned long& offset, const SeekType& offsetFrom)
{

}

unsigned long ComponentInputStream::getSize()
{
	if ( NULL != inStream_ ){
		return inStream_->getSize();
	}
	return 0;
}

char* ComponentInputStream::getBuffer()
{
	return NULL;
}

void ComponentInputStream::read( char* bytesToRead, unsigned long sizeOfBytes )
{
	if ( NULL != inStream_ ){
		inStream_->read( bytesToRead, sizeOfBytes );
	}
}

void ComponentInputStream::error( const SAXParseException& e )
{
	std::cout << "\nError at (file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "): " << StrX(e.getMessage()) << endl;
}

void ComponentInputStream::fatalError( const SAXParseException& e )
{
    cout << "\nFatal Error at (file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "): " << StrX(e.getMessage()) << endl;
}

void ComponentInputStream::warning( const SAXParseException& e )
{
    cout << "\nWarning at (file " << StrX(e.getSystemId())
		 << ", line " << e.getLineNumber()
		 << ", char " << e.getColumnNumber()
         << "): " << StrX(e.getMessage()) << endl;
}

void ComponentInputStream::unparsedEntityDecl(const XMLCh* const name, const XMLCh* const publicId,
											  const XMLCh* const systemId, const XMLCh* const notationName )
{
    // Not used at this time
}


void ComponentInputStream::notationDecl( const XMLCh* const name, const XMLCh* const publicId,
										 const XMLCh* const systemId )
{
    // Not used at this time
}

void ComponentInputStream::characters(const XMLCh* const chars, const unsigned int length )
{
    // Transcode to UTF-8 for portable display
    StrX tmpXCode(chars);
    const char* tmpText = tmpXCode.localForm();

    //
    //  If we were asked to escape special chars, then do that. Else just
    //  display it as normal text.
    //
    if (doEscapes_)
    {
        for (unsigned int index = 0; index < length; index++)
        {
            switch (tmpText[index])
            {
            case chAmpersand :
                cout << "&amp;";
                break;

            case chOpenAngle :
                cout << "&lt;";
                break;

            case chCloseAngle:
                cout << "&gt;";
                break;

            case chDoubleQuote :
                cout << "&quot;";
                break;

            default:
                cout << tmpText[index];
                break;
            }
        }
    }
     else
    {
        cout << tmpText;
    }
}


void ComponentInputStream::endDocument()
{
}

void ComponentInputStream::endElement( const XMLCh* const name )
{
    cout << "</" << StrX(name) << ">";
	String tokenName = StrX(name).localForm();
	switch ( getTokenFromString( tokenName ) ){
		case COMP_TOKEN_UNKNOWN:{

		}
		break;

		case COMP_TOKEN_OBJECT:{

		}
		break;

		case COMP_TOKEN_CHILDREN:{
			this->containerPropertyMap_.erase( containerLevel_ );
			containerLevel_ --;
			std::map<int,Container*>::iterator found = containerPropertyMap_.find( containerLevel_ );
			if ( found != containerPropertyMap_.end() ){
				currentContainer_ = found->second;
			}
		}
		break;

		case COMP_TOKEN_PROPERTY:{

		}
		break;

		case COMP_TOKEN_OBJECT_PROPERTY:{
			this->objectPropertyMap_.erase( objectPropertyLevel_ );
			currentObjectProperty_ = NULL;
			objectPropertyLevel_ --;
			std::map<int,Object*>::iterator found = objectPropertyMap_.find( objectPropertyLevel_ );
			if ( found != objectPropertyMap_.end() ){
				currentObjectProperty_ = found->second;
			}
		}
		break;

		case COMP_TOKEN_CLASSID:{

		}
		break;
	}
}

void ComponentInputStream::ignorableWhitespace( const XMLCh* const chars, const unsigned int length )
{

}

void ComponentInputStream::processingInstruction(const XMLCh* const target, const XMLCh* const data )
{

}

void ComponentInputStream::startDocument()
{

}

void ComponentInputStream::loadProperties( Object* object, AttributeList&  attributes )
{
	String propertyName = "";
	String propValue = "";
	Property* property = NULL;
	Class* clazz = NULL;
	clazz = object->getClass();
	if ( NULL != clazz ){
		int index = 0;
		unsigned int propCount = attributes.getLength();
		while ( index < propCount ) {
			propertyName = StrX( attributes.getValue(index) ).localForm();
			if ( clazz->hasProperty( propertyName ) ){
				property = clazz->getProperty( propertyName );
				if ( NULL != property ){
					propValue = StrX( attributes.getValue(index+1) ).localForm();
					if ( true == property->isCollection() ){
						ClassRegistry* registry = ClassRegistry::getClassRegistry();
						VariantData itemVal;
						Object* item = NULL;
						if ( NULL != registry ){
							registry->createNewInstance( propValue, &item );
							itemVal = item;
						}
						if ( NULL != item ){
							property->add( &itemVal );
							objectPropertyLevel_ ++;
							this->objectPropertyMap_[ objectPropertyLevel_ ] = item;
						}
					}
					else if ( PROP_OBJECT != property->getType() ){
						if ( false == property->isReadOnly() ){
							property->set( propValue );
						}
					}
					else {
						if ( 0 != stricmp( "null", propValue.c_str() ) ){ // now we have a class name
							VariantData* objVal = property->get();
							if ( NULL != objVal ){
								this->currentObjectProperty_ = *objVal;
								if ( NULL == currentObjectProperty_ ){//go ahead and create one
									ClassRegistry* registry = ClassRegistry::getClassRegistry();
									if ( NULL != registry ){
										registry->createNewInstance( propValue, &currentObjectProperty_ );
										*objVal = currentObjectProperty_;
										property->set( objVal );
									}
								}
								objectPropertyLevel_ ++;
								this->objectPropertyMap_[ objectPropertyLevel_ ] = currentObjectProperty_;
								this->currentPropertyClassName_ = propValue;
							}
						}
					}
				}
			}
			index += 2;
		}
	}
	else{

		//throw exception
	}
}

void ComponentInputStream::startElement(const XMLCh* const name, AttributeList&  attributes )
{
	String tokenName = StrX(name).localForm();

	unsigned int index = 0;
	switch ( getTokenFromString( tokenName ) ){
		case COMP_TOKEN_UNKNOWN:{

		}
		break;

		/**
		*Object token is found. The class name needs to be pulled off and then
		*the class instantiated
		*/
		case COMP_TOKEN_OBJECT:{
			ClassRegistry* registry = ClassRegistry::getClassRegistry();
			if ( NULL != registry ){
				bool topLevelComp = (NULL == component_) ? true : false;

				String className = StrX( attributes.getValue(index) ).localForm();
				//this should only be true once
				if ( (true == this->topLevelComponentAlreadyExists_) && (NULL == component_) ){
					//can't compare classnames here have ot assume that the topLevelControl_
					//passed into the readControl() method is OK and matches the className
					component_ = topLevelControl_;
				}
				else{
					registry->createNewInstance( className, &component_ );
					if ( topLevelComp ){
						topLevelControl_ = dynamic_cast<Control*>( component_ );
					}
				}
				std::map<int,Container*>::iterator it = containerPropertyMap_.find( containerLevel_ );
				if ( it != containerPropertyMap_.end() ){
					it->second->add( (Control*)component_ );
				}
			}
			else {
				//throw exception !
			}
		}
		break;

		case COMP_TOKEN_CHILDREN:{
			Container* tmp = component_->getContainer();
			if ( NULL != tmp ){//means this component_ is a container
				containerLevel_ ++;
				this->containerPropertyMap_[ containerLevel_ ] = tmp;
			}
		}
		break;

		case COMP_TOKEN_PROPERTY:{
			unsigned int propCount = attributes.getLength();
			/**
			*we two cases  - either we are editing the component ( component_!=NULL ) or
			*we are editing a property of the Component (currentObjectProperty_!=NULL)
			*/

			if ( (NULL != component_) && (NULL == currentObjectProperty_) ){
				loadProperties( component_, attributes );
			}
			else {
				std::map<int,Object*>::iterator it = objectPropertyMap_.find( objectPropertyLevel_ );
				if ( it != objectPropertyMap_.end() ){
					currentObjectProperty_ = it->second;
					loadProperties( currentObjectProperty_, attributes );

				}
			}
		}
		break;

		case COMP_TOKEN_OBJECT_PROPERTY:{

		}
		break;

		case COMP_TOKEN_CLASSID:{

		}
		break;
	}
}

long ComponentInputStream::getTokenFromString( const String& string )
{
	long result = COMP_TOKEN_UNKNOWN;

	if ( 0 == _stricmp( COMP_OBJECT, string.c_str() ) ){
		result = COMP_TOKEN_OBJECT;
	}
	else if ( 0 == _stricmp( COMP_CLASS, string.c_str() ) ){
		result = COMP_TOKEN_CLASS;
	}
	else if ( 0 == _stricmp( COMP_PROPERTY, string.c_str() ) ){
		result = COMP_TOKEN_PROPERTY;
	}
	else if ( 0 == _stricmp( COMP_NAME, string.c_str() ) ){
		result = COMP_TOKEN_NAME;
	}
	else if ( 0 == _stricmp( COMP_VALUE, string.c_str() ) ){
		result = COMP_TOKEN_VALUE;
	}
	else if ( 0 == _stricmp( COMP_CHILDREN, string.c_str() ) ){
		result = COMP_TOKEN_CHILDREN;
	}
	else if ( 0 == _stricmp( COMP_OBJECT_PROPERTY, string.c_str() ) ){
		result = COMP_TOKEN_OBJECT_PROPERTY;
	}
	else if ( 0 == _stricmp( COMP_CLASSID, string.c_str() ) ){
		result = COMP_TOKEN_CLASSID;
	}
	else if ( 0 == _stricmp( COMP_COMPONENTS, string.c_str() ) ){
		result = COMP_TOKEN_COMPONENTS;
	}

	return result;
}

void ComponentInputStream::readControl( Control** controlToReadInto )
{
	topLevelComponentAlreadyExists_ = (*controlToReadInto != NULL) ? true : false;

	if ( true == topLevelComponentAlreadyExists_ ){
		topLevelControl_ = *controlToReadInto;
	}

	unsigned long size = this->getSize();
	char* bufData = NULL;
	try {
		XMLPlatformUtils::Initialize();
		bufData = new char[size];
		memset( bufData, 0, size );
		this->read( bufData, size );
		MemBufInputSource* buf = new MemBufInputSource( (const XMLByte*)bufData, size, "MEM_BUF", false );

		SAXParser parser;
		parser.setValidationScheme( SAXParser::Val_Auto );
		parser.setDoNamespaces(false);

		parser.setDocumentHandler( this );
		parser.setErrorHandler( this );

		parser.parse( *buf );

		XMLPlatformUtils::Terminate();
	}
	catch (const XMLException& toCatch){
		String s = StrX(toCatch.getMessage()).localForm();
		throw BasicException( "XML Error message: " +  s );
	}
	delete [] bufData;

	if ( NULL != topLevelControl_ ){
		*controlToReadInto = topLevelControl_;
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
*Revision 1.10  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.1  2003/08/18 19:52:38  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.9  2003/05/17 20:37:24  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.2  2003/03/23 03:23:56  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.8.2.1  2003/03/12 03:12:09  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:47  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.20.1  2003/01/08 00:19:51  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


