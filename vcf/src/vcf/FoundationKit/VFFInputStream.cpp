//VFFInputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/VFFInputStream.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/VFFParser.h"

using namespace VCF;

Component* VFFInputStream::rootComponent_ = NULL;
UnitTransformer* VFFInputStream::transformer = NULL;

VariantData getKeyFromIndex( const String& index, int token ) ;

static Dictionary componentConstants;

class FuncPtrHolder : public Object {
public:
	FuncPtrHolder(VFFInputStream::ComponentConstantFunc fp): funcPtr(fp){}

	VFFInputStream::ComponentConstantFunc funcPtr;
};



VFFInputStream::VFFInputStream( InputStream* stream ):
	topLevelComponent_(NULL),
	atTopLevel_(true),
	componentInputLevel_(-1),
	topLevelControlVisibility_(false),
	setDesignMode_(false),
    stream_(stream),	
    parser_(NULL),	
	deleteStream_(false)	
{
	parser_ = new VCF::VFFParser( this );
}

VFFInputStream::VFFInputStream( const VCF::String& vffString ):
	topLevelComponent_(NULL),
	atTopLevel_(true),
	componentInputLevel_(-1),
	topLevelControlVisibility_(false),
	setDesignMode_(false),
    stream_(NULL),	
    parser_(NULL),	
	deleteStream_(true)
{
	stream_ = new BasicInputStream( vffString );

	parser_ = new VCF::VFFParser( this );	
}

VFFInputStream::~VFFInputStream()
{
	delete parser_;
	parser_ = NULL;

	if ( deleteStream_ ) {
		delete stream_;
	}
}

void VFFInputStream::getOuterClassNameAndUUID( String& className, String& UUID, String& fallbackClassName )
{
	className = "";
	UUID = "";

	parser_->resetStream();

	if ( true == parser_->tokenSymbolIs( "object" ) ) {
		String currentSymbol;
		while ( (VFFParser::TO_EOF != parser_->getToken()) && (false == parser_->tokenSymbolIs( "end" )) ) {
			currentSymbol = parser_->tokenString();
			try {
				// do object
				VCFChar token = parser_->nextToken();
				switch ( token ) {
					case ':' : {
						parser_->nextToken();
						className = parser_->tokenString();
						parser_->nextToken();
						if ( parser_->getToken() == ',' ) {						
							parser_->nextToken();
							UUID = parser_->tokenString();
						}

						parser_->nextToken();
						if ( parser_->getToken() == ',' ) {
							parser_->nextToken();
							fallbackClassName = parser_->tokenString();
						}
					}
					break;
				}
			}

			catch ( BasicException& e ) {
				StringUtils::trace( e.getMessage() + "\n" );
				break;
			}
		}
	}

	parser_->resetStream();
}

void VFFInputStream::readDelegate( Component* component, VCF::Class* clazz )
{
	String currentSymbol = parser_->tokenString();

	VCFChar token = parser_->nextToken();

	//do delegate
	switch ( token ) {
		case '=' :  {
			processDelegateAsignment( token, currentSymbol, clazz );
		}
		break;

		case '.' : {
			parser_->nextToken();
			String objPropName = parser_->tokenString();
			

			Property* prop = clazz->getProperty( currentSymbol );
			VariantData* value = prop->get();
			if ( value->type == pdObject ) {
				Object* object = *value;
				if ( NULL != object ) {
					Class* objClass = object->getClass();
					if ( NULL != clazz ) {
						readDelegate( component, objClass );
					}
					else {
						StringUtils::trace( Format("Warning: no Class found for delegate property %s.")
												% currentSymbol.ansi_c_str() );
					}
				}
				else {
					throw RuntimeException( MAKE_ERROR_MSG_2("object is null - cannot access the object's delegate.") );
				}
			}
			else {
				throw RuntimeException( MAKE_ERROR_MSG_2("Property is not an object and cannot have delegates.") );
			}
		}
		break;
	}
}

void VFFInputStream::readDelegates( VCF::Component* component, VCF::Class* clazz )
{	
	if ( parser_->tokenSymbolIs( "delegates" ) ) {	

		while ( (VFFParser::TO_EOF != parser_->getToken()) && (!parser_->tokenSymbolIs( "end" )) ) {

			readDelegate( component, clazz );
		}

		parser_->nextToken();
	}	
}

void VFFInputStream::processDelegateAsignment( const VCF::VCFChar& token, const VCF::String& currentSymbol, VCF::Class* clazz )
{
	VCFChar assignmentToken = parser_->nextToken();
	String value = parser_->tokenString();

	switch ( assignmentToken ) {
		case '[': {
			DelegateProperty* delegateProperty = clazz->getDelegate ( currentSymbol );

			if ( NULL != delegateProperty ) {

				parser_->nextToken();

				std::vector<String> callbacks;

				while ( ']' != parser_->getToken() ) {
					value = "";
					while ( (',' != parser_->getToken()) && (']' != parser_->getToken()) ) {
						value += parser_->tokenString();
						parser_->nextToken();
					}

					if ( parser_->getToken() == ',' ) {
						parser_->nextToken();
					}

					int pos = value.find( "@" );
					String functionSrcID = value.substr(0,pos);
					String functionPtr = value.substr(pos+1,value.size()-(pos+1));

					callbacks.push_back( value );
				}

				if ( !callbacks.empty() ) {
					DeferredDelegateSetter* delegateSetter = new DeferredDelegateSetter();
					delegateSetter->callbackIds = callbacks;
					delegateSetter->delegateName = currentSymbol;
					delegateSetter->source = delegateProperty->getSource();
					deferredDelegates_.push_back( delegateSetter );
				}
			}
		}
		break;

		default : {
			//throw exception
			throw RuntimeException( MAKE_ERROR_MSG_2("Invalid delegate assignment syntax") );
		}
		break;
	}
}



void VFFInputStream::processAsignmentTokens( const VCFChar& token, const String& currentSymbol, const VariantData& key, Class* clazz )
{
	switch ( token ) {
		case '=' : {
			VCFChar assignmentToken = parser_->nextToken();
			String value = parser_->tokenString();
			int valToken = parser_->getToken();

			switch ( assignmentToken ) {
				default : {
					Property* prop = clazz->getProperty( currentSymbol );
					if ( NULL != prop ) {
						VCF_ASSERT( prop->isCollection() );

						if ( prop->isCollection() ) {

							VariantData varVal;
							varVal.type = prop->getType();
							if ( prop->getType() == pdVariant ) {
								//try and guess type from context
								switch ( valToken ) {
									case VFFParser::TO_STRING: {
										varVal.type = pdString;
									}
									break;

									case VFFParser::TO_INTEGER: {
										varVal.type = pdInt;
									}
									break;

									case VFFParser::TO_FLOAT: {
										varVal.type = pdDouble;
									}
									break;

									default : {
										if ( value == "true" || value == "false" ) {
											varVal.type = pdBool;
										}
									}
									break;
								}
							}

							
							if ( (pdObject == prop->getType() || pdVariant == prop->getType()) && ('@' == value[0]) ) {
								value.erase( 0, 1 );
								if ( !value.empty() ) {
									//need to adjust this for arrays/collections!
									deferredProperties_.push_back( new DeferredPropertySetter( value, prop->getName(), prop->getSource(), key ) );
								}
							}
							else {
								String newVal;							
								if ( VFFInputStream::getComponentConstant( value, newVal ) ) {
									value = newVal;
								}

								if (valToken == VFFParser::TO_INTEGER ||
									valToken == VFFParser::TO_FLOAT ) {
									value = transform( value );
								}

								//note: need to be able to set value
								//from a string!!
								//also, we need to inform the 
								//collection property that it
								//needs to not only set the property
								//to the specified key, but also 
								//fill in any blank entries, if 
								//neccessary.


								varVal.setFromString( value );

								prop->setAtKey( key, &varVal );
							}
						}
					}
				}
				break;
				case '[': {
					Property* prop = clazz->getProperty( currentSymbol );					
					if ( NULL != prop ) {
						VCF_ASSERT( prop->isCollection() );

						if ( prop->isCollection() ) {
							String value;
							while ( ']' != parser_->nextToken() ) {
								value += parser_->tokenString();
							}
							prop->setAtKey( key, value );
						}
					}
				}
				break;

				case '{': {					
					String binValue = parser_->binHexToString();
					parser_->nextToken();
					parser_->checkToken( '}' );
					Property* prop = clazz->getProperty( currentSymbol );
					if ( NULL != prop ) {
						VCF_ASSERT( prop->isCollection() );

						if ( prop->isCollection() ) {
							VariantData* value = prop->getAtKey( key );
							if ( value->type == pdObject ) {
								Object* obj = *value;
								if ( NULL != obj ) {
									Persistable* persistable = dynamic_cast<Persistable*>(obj);
									if ( NULL != persistable ) {
										hexToBin( binValue, persistable );
									}
								}
							}
						}
					}
				}
				break;
			}
			parser_->nextToken();
		}
		break;

		case '.' : {
			//we are at the property name so currentSymbol
			//will be the name of the proeprty we are examining
			//calling nextToken will take us to the
			parser_->nextToken();

			String objPropName = parser_->tokenString();
			VCFChar newToken = parser_->nextToken();

			Property* prop = clazz->getProperty( currentSymbol );
			
			VCF_ASSERT( prop->isCollection() );
			if ( prop->isCollection() ) {

				if ( prop->getType() != pdObject &&
					(prop->getType() != pdVariant) ) {
					throw RuntimeException("Attempting to assign values to a value that is not an object");
				}

				VariantData* value = NULL;
				try {
					value = prop->getAtKey( key );					
				}
				catch(...) {
					value = NULL;
					//create a new instance.

					String objClassName = prop->getTypeClassName();
					Object* obj = ClassRegistry::createNewInstance( objClassName );
					
					VariantData tmp(obj);
					prop->setAtKey( key, &tmp );

					value = prop->getAtKey( key );
				}

				if ( NULL == value ) {
					throw RuntimeException("No value is available for the collection \"" + currentSymbol + "\" at key [" + key + "]" );
				}

				VCF_ASSERT( value->type == pdObject );

				if ( value->type == pdObject ) {
					Object* object = *value;
					if ( NULL != object ) {
						clazz = object->getClass();
						
						processAsignmentTokens( newToken, objPropName, clazz );
					}
				}
			}
		}
		break;

		case '[' : {
			parser_->nextToken();
			String index = parser_->tokenString();
			VCFChar indexToken = parser_->getToken();
			parser_->nextToken();
			parser_->checkToken( ']' );		

			VCFChar token = parser_->nextToken();
			switch ( token ) {
				//properties
				case '=' : case '.' : case '[' : {
					VariantData key = getKeyFromIndex( index, indexToken );

					processAsignmentTokens( token, currentSymbol, key, clazz );
				}
				break;

				default : {
					parser_->errorStr( "Value expected for array item assignment" );
				}
				break;
			}
		}
		break;

		default : {
			parser_->errorStr( "Object type expected" );
		}
		break;
	}
}

VariantData getKeyFromIndex( const String& index, int token ) 
{
	VariantData key;	

	switch ( token ) {
		case VFFParser::TO_STRING: {
			key = index;
		}
		break;

		case VFFParser::TO_INTEGER: {			
			try {
				int i = StringUtils::fromStringAsInt( index );
				key = i;
			}
			catch ( BasicException& ) {
				key = index;
			}
		}
		break;

		case VFFParser::TO_FLOAT: {
			try {
				double d = StringUtils::fromStringAsDouble( index );
				key = d;
			}
			catch ( BasicException& ) {
				key = index;
			}
		}
		break;

		default: {
			try {
				bool b = StringUtils::fromStringAsBool( index );
				key  = b;
			}
			catch ( BasicException& ) {
				key = index;
			}
		}
		break;
	}

	return key;
}

void VFFInputStream::processAsignmentTokens( const VCFChar& token, const String& currentSymbol, Class* clazz )
{
	switch ( token ) {
		case '=' : {
			VCFChar assignmentToken = parser_->nextToken();
			String value = parser_->tokenString();
			switch ( assignmentToken ) {
				default : {
					Property* prop = clazz->getProperty( currentSymbol );
					if ( NULL != prop ) {
						//need to be a bit smarter here
						//look at the proeprty type. If the type is
						//is pdObject, then first assume that value
						//is actually a string that represents the name of
						//variable. Search for the value, if something is
						//found then pass this into the prop->set() call.
						//If nothing is found then go for it and pass
						//in the value as is.

						bool deferredProp = false;

						if ( /*(pdObject == prop->getType()) &&*/ ('@' == value[0]) ) {
							//OK our value is actually a component name so we are
							//going to store it in a list for later, because we may not
							//have an existing instance of the component yet. To store
							//this successfully we need the name of the property to set,
							//the actualy object instance that we are going to set the
							//property on, and the name of the component to try and retreive
							//once we get to that point.
							
							value.erase( 0, 1 );
							if ( !value.empty() ) {
								deferredProp = true;
							}
							else {
								value.insert( 0, L"@" );
							}
						}

						if ( deferredProp ) {							
							deferredProperties_.push_back( new DeferredPropertySetter( value, prop->getName(), prop->getSource() ) );							
						}
						else {
							String newVal;							
							if ( VFFInputStream::getComponentConstant( value, newVal ) ) {
								value = newVal;
							}
							if (assignmentToken == VFFParser::TO_INTEGER ||
								assignmentToken == VFFParser::TO_FLOAT ) {
								value = transform( value );
							}
							
							prop->set( value );

							if ( 0 == componentInputLevel_ ) {
								if ( (prop->getName() == "visible") ||
									(prop->getDisplayName() == "visible") ) {
									topLevelControlVisibility_ = *prop->get();
								}
							}
						}
					}
					else {
						StringUtils::trace( Format("No property found named '%s'.\n") % currentSymbol.ansi_c_str() );
					}
				}
				break;
				case '[': {
					Property* prop = clazz->getProperty( currentSymbol );
					if ( NULL != prop ) {
						String value;
						while ( ']' != parser_->nextToken() ) {
							value += parser_->tokenString();
						}
						prop->set( value );
					}
					else {
						StringUtils::trace( Format("No property found named '%s'.\n") % currentSymbol.ansi_c_str() );
					}
				}
				break;

				case '{': {
					//parser_->nextToken();
					String binValue = parser_->binHexToString();
					parser_->nextToken();
					parser_->checkToken( '}' );
					Property* prop = clazz->getProperty( currentSymbol );
					if ( NULL != prop ) {
						VariantData* value = prop->get();
						if ( value->type == pdObject ) {
							Object* obj = *value;
							if ( NULL != obj ) {
								Persistable* persistable = dynamic_cast<Persistable*>(obj);
								if ( NULL != persistable ) {
									hexToBin( binValue, persistable );
								}
							}
						}
					}
					else {
						StringUtils::trace( Format("No property found named '%s'.\n") % currentSymbol.ansi_c_str() );
					}
				}
				break;
			}
			parser_->nextToken();
		}
		break;

		case '.' : {
			//we are at the property name so currentSymbol
			//will be the name of the proeprty we are examining
			//calling nextToken will take us to the
			parser_->nextToken();

			String objPropName = parser_->tokenString();
			VCFChar newToken = parser_->nextToken();

			Property* prop = clazz->getProperty( currentSymbol );
			VariantData* value = prop->get();
			if ( value->type == pdObject ) {
				Object* object = *value;
				if ( NULL != object ) {
					clazz = object->getClass();

					if ( NULL != clazz ) {
						processAsignmentTokens( newToken, objPropName, clazz );
					}
					else {
						StringUtils::trace( Format("Warning: no Class found for property %s.")
												% currentSymbol.ansi_c_str() );
					}
				}
			}
			else {
				processAsignmentTokens( newToken, objPropName, clazz );
			}
		}
		break;

		case '[' : {
			parser_->nextToken();
			String index = parser_->tokenString();

			VCFChar indexToken = parser_->getToken();

			parser_->nextToken();
			parser_->checkToken( ']' );		

			VCFChar token = parser_->nextToken();
			switch ( token ) {
				//properties
				case '=' : case '.' : case '[' : {

					//String s = currentSymbol;
					//Class* cl = clazz;

					VariantData key = getKeyFromIndex(index,indexToken);

					processAsignmentTokens( token, currentSymbol, key, clazz );
				}
				break;

				default : {
					parser_->errorStr( "Value expected for array item assignment" );
				}
				break;
			}
		}
		break;

		default : {
			parser_->errorStr( "Object type expected" );
		}
		break;
	}
}

void VFFInputStream::readNewComponentInstance( VCF::Component* component )
{
	componentInputLevel_ = -1;

	if ( NULL == topLevelComponent_ ) {
		topLevelComponent_ = component;

		component->preLoading();

		component->loading();
	}

	readObject( component, VFFInputStream::ufCreateChildren );// | VFFInputStream::ufCreateChildrenIfNoInstance );	
	
	componentInputLevel_ = -1;

	component->loaded();

	assignDeferredProperties(component);

	component->postLoaded( topLevelControlVisibility_ );	
}

void VFFInputStream::assignDeferredProperties( Component* component )
{
	if ( -1 == componentInputLevel_ ) {
		std::vector<DeferredPropertySetter*>::iterator it = deferredProperties_.begin();
		while ( it != deferredProperties_.end() ) {
			DeferredPropertySetter* dps = *it;

			Class* clazz = dps->source->getClass();

			Property* prop = clazz->getProperty( dps->propertyName );

			
			
			if ( NULL != prop ) {
				VariantData data;
				Component* foundComponent = NULL;
				

				
				String propName = dps->propertyVal;
				
				size_t nameDepth = 0;
				size_t pos = propName.find(".");
				if ( pos != String::npos ) {
					Property* valProp = NULL;
					String componentName;
					componentName = propName.substr(0,pos);
					propName.erase( 0, pos+1 );

					if ( component->bindVariable( &foundComponent, componentName ) ) {
						Class* valClass = foundComponent->getClass();						

						VariantData* propVal = NULL;
						do {							
							pos = propName.find(".");
							

							if ( pos != String::npos ) {
								valProp = valClass->getProperty( propName.substr(0,pos) );
								propVal = valProp->get();
								if ( NULL == propVal ) {
									throw RuntimeException( "Null property value" );
								}

								if ( propVal->type != pdObject ) {
									throw RuntimeException( "Invalid property value - must be an object in order to reference sub properties" );
								}

								Object* obj = *propVal;
								if ( NULL == obj ) {
									throw RuntimeException( "Invalid property value - must be a non-null object in order to reference sub properties" );
								}

								valClass = obj->getClass();
		
							}
							else {
								valProp = valClass->getProperty( propName );
								propVal = valProp->get();
							}
							
							propName.erase( 0, pos+1 );		
						}while ( pos != String::npos );

						if ( NULL == propVal ) {
							data = VariantData::null();
						}
						else {
							data = *propVal;
						}

					}
					else {
						StringUtils::trace( Format("Failed to find component %s. Unable to assign deferred property.\n") % dps->propertyVal );
					}
				}
				else {
					if ( true == component->bindVariable( &foundComponent, propName ) ) {						
						data = foundComponent;
					}
					else {
						StringUtils::trace( Format("Failed to find component %s. Unable to assign deferred property.\n") % dps->propertyVal );
					}
				}

				if ( prop->isCollection() && dps->keyValid ) {
					prop->setAtKey( dps->key, &data );
				}
				else if ( !prop->isCollection() ) {
					prop->set( &data );
				}
			}
			delete dps;
			dps = NULL;
			it ++;
		}
		deferredProperties_.clear();


		std::vector<DeferredDelegateSetter*>::iterator it2 = deferredDelegates_.begin();
		while ( it2 != deferredDelegates_.end() ) {
			DeferredDelegateSetter* dds = *it2;
			Class* clazz = dds->source->getClass();
			DelegateProperty* delegateProperty = clazz->getDelegate( dds->delegateName );
			if ( NULL != delegateProperty ) {
				std::vector<String>::iterator cbIt = dds->callbackIds.begin();
				while ( cbIt != dds->callbackIds.end() ) {
					const String& s = *cbIt;
					int pos = s.find( "@" );
					String functionSrcID = s.substr(0,pos);
					String functionPtr = s.substr(pos+1,s.size()-(pos+1));

					Component* source = 
						component->findComponent( functionSrcID, true );
					if ( NULL == source ) {
						if ( NULL != VFFInputStream::rootComponent_ ) {
							source = VFFInputStream::rootComponent_->findComponent( functionSrcID, true );
						}
					}

					if ( NULL != source ) {
						CallBack* cb = source->getCallback( functionPtr );

						if ( NULL != cb ) {
							delegateProperty->getDelegateInstance()->add( cb );
						}
					}

					++cbIt;
				}
			}
			delete dds;
			dds = NULL;
			++it2;
		}
		deferredDelegates_.clear();
	}
}

Object* VFFInputStream::createClassInstance( const String& className, const String& classID, const String& fallbackClassName )
{
	Object* result = NULL;

	try {
		result = ClassRegistry::createNewInstance( className );
	}
	catch (BasicException&) {
		StringUtils::trace( Format("Exception creating class instance named: %s, trying class UUID %s") 
							% className % fallbackClassName );

		result = ClassRegistry::createNewInstance( fallbackClassName );
	}

	return result;
}

VCF::Component* VFFInputStream::readObject( VCF::Component* componentInstance, int flags )
{
	VCF::Component* result = NULL;
	
	componentInputLevel_ ++;
	
	
	Class* clazz = NULL;	
	Component* childComponent = NULL;

	String currentSymbol;
	String objectName;
	if ( parser_->tokenSymbolIs( "object" ) ) {
		

		//read in object info
		try {
			//go to object name
			parser_->nextToken();
			currentSymbol = parser_->tokenString();

			VCFChar token;

			if ( currentSymbol == ":" ) {
				currentSymbol = "";
				token = parser_->getToken();
			}
			else {
				//skip to ':' 
				token = parser_->nextToken();				
			}			
			
			parser_->checkToken( ':' );
			parser_->nextToken();

			if ( objectName.empty() ) {
				objectName = currentSymbol;
			}
			
			
			String className = parser_->tokenString();
			String classID;
			parser_->nextToken();
			if ( parser_->getToken() == ',' ) {
				parser_->nextToken();
				classID = parser_->tokenString();
				parser_->nextToken();
			}

			String fallbackClassName;
			
			bool skipNextToken = false;
			
			if ( parser_->getToken() == ',' ) {
				parser_->nextToken();
				fallbackClassName = parser_->tokenString();
			}
			else {
				skipNextToken = true;
			}

			if ( flags & VFFInputStream::ufCreateComponent ) {
				result = (Component*)createClassInstance( className, classID, fallbackClassName );
				if ( NULL == topLevelComponent_ ) {
					topLevelComponent_ = result;
				}
				
				if ( NULL != result ) {
					if ( setDesignMode_ ) {
						result->setDesigning( true );
					}
					result->loading();
					
					clazz = result->getClass();
				}
				else {
					parser_->error( "Unable to instantiate an object of type \"" + className + "\"" );
				}
			}
			else if ( (flags & VFFInputStream::ufCreateChildrenIfNoInstance) && (NULL != componentInstance) ) {
				
				if ( componentInstance != topLevelComponent_ ) {
					childComponent = componentInstance->findComponent( currentSymbol );

					result = childComponent;
				}
				else {
					result = componentInstance;
				}

				if ( NULL == result ) {
					result = (Component*)createClassInstance( className, classID, fallbackClassName );
					if ( NULL == topLevelComponent_ ) {
						topLevelComponent_ = result;
					}					
				}

				if ( NULL != result ) {
					if ( setDesignMode_ ) {
						result->setDesigning( true );
					}

					result->loading();
					
					clazz = result->getClass();
				}
				else {
					parser_->error( "Unable to instantiate an object of type \"" + className + "\"" );
				}

			}
			else if ( (flags & VFFInputStream::ufFindSubComponent) && (NULL != componentInstance) ) {
				childComponent = componentInstance->findComponent( currentSymbol );

				if ( NULL != childComponent ) {
					clazz = childComponent->getClass();
					if ( clazz->getID() != classID && !classID.empty() ) {
						parser_->error( MAKE_ERROR_MSG_2("ClassID of passed in component doesn't match ClassID encountered in parsing stream") );
					}
				}
				else {
					throw InvalidPointerException( MAKE_ERROR_MSG_2("component is NULL, can't write properties of stream to NULL component") );
				}
			}
			else {
				if ( NULL != componentInstance ) {
					result = componentInstance;
					clazz = componentInstance->getClass();
					//only validate the class name if the we are not parsing the top level component
					//which, in this case, should be a FormRootWindow class
					if ( (clazz->getID() != classID && !classID.empty()) && (topLevelComponent_ != componentInstance) ) {
						parser_->error( MAKE_ERROR_MSG_2("ClassID of passed in component doesn't match ClassID encountered in parsing stream") );
					}
				}
				else {
					throw InvalidPointerException( MAKE_ERROR_MSG_2("component is NULL, can't write properties of stream to NULL component") );
				}
			}
			
			if ( !skipNextToken ) {
				parser_->nextToken();
			}
		}
		catch ( BasicException& e ) {
			StringUtils::trace( e.getMessage() + "\n" );
			return result;
		}
	}
	else {
		if ( (flags & VFFInputStream::ufFindSubComponent) && (NULL != componentInstance) ) {
			currentSymbol = parser_->tokenString();

			childComponent = componentInstance->findComponent( currentSymbol );
			
			if ( NULL != childComponent ) {
				clazz = childComponent->getClass();
			}
			else {
				throw InvalidPointerException( MAKE_ERROR_MSG_2("component is NULL, can't write properties of stream to NULL component") );
			}
		}
		else {
			if ( NULL != componentInstance ) {
				result = componentInstance;
				clazz = componentInstance->getClass();				
			}
			else {
				throw InvalidPointerException( MAKE_ERROR_MSG_2("component is NULL, can't write properties of stream to NULL component") );
			}
		}
	}

	//read in properties, sub objects, and delegates
	while ( (VFFParser::TO_EOF != parser_->getToken()) && (!parser_->tokenSymbolIs( "end" )) ) {
		currentSymbol = parser_->tokenString();

		try {
			if ( parser_->tokenSymbolIs( "delegates" ) ) {
				//check for delegates
				readDelegates( componentInstance, clazz );
			}
			else if ( !parser_->tokenSymbolIs( "object" ) ) {
				// do object
				VCFChar token = parser_->nextToken();
				switch ( token ) {
					//properties
					case '=' : case '.' : case '[' : {
						try {
							processAsignmentTokens( token, currentSymbol, clazz );
						}
						catch ( BasicException& e ) {
							StringUtils::trace( String("Error processing assignment for ") + currentSymbol + "\n\tException: " + e.what() + "\n" );
						}
					}
					break;
				}
			}

			while ( parser_->tokenSymbolIs( "object" ) ) {

				Component* newComponent = NULL;
				Component* component = NULL;
				int readFlags = 0;

				if ( flags & VFFInputStream::ufCreateChildren &&
					!(flags & VFFInputStream::ufCreateChildrenIfNoInstance) ) {

					newComponent = createNewComponent(NULL,VFFInputStream::ufCreateComponent);
					readFlags = VFFInputStream::ufCreateChildren;

						//readNewComponent();
				}
				else if ( flags & VFFInputStream::ufCreateChildrenIfNoInstance ) {
					newComponent = createNewComponent(componentInstance,VFFInputStream::ufCreateChildrenIfNoInstance);
					readFlags = flags;
					//newComponent = readObject( componentInstance, flags );
				}
				else if ( flags & VFFInputStream::ufFindSubComponent ) {
					component = childComponent;
					readFlags = VFFInputStream::ufFindSubComponent; 

					//readObject( childComponent, VFFInputStream::ufFindSubComponent );
				}
				else {
					component = componentInstance;
					readFlags = VFFInputStream::ufFindSubComponent;
					//readObject( componentInstance, VFFInputStream::ufFindSubComponent );
				}
				
				if ( (flags & VFFInputStream::ufCreateChildren) ||
					(flags & VFFInputStream::ufCreateChildrenIfNoInstance)  ) {
					if ( NULL != newComponent ) {
						Class* componentClass = topLevelComponent_->getClass();
						if ( NULL != componentClass ) {
							Field* field = componentClass->getField( newComponent->getName() );
							if ( NULL != field ) {
                                VariantData vd(newComponent);
								field->set( &vd );
							}
						}
						
						result->addNewComponent( newComponent );
						component = newComponent;
					}
				}

				//read in props
				readObject( component, readFlags );

				parser_->nextToken();
			}
		}
		catch ( BasicException& e ) {
			StringUtils::trace( e.getMessage() + "\n" );
			break;
		}
	}

	if ( !objectName.empty() && (NULL != result) && result->getName().empty() ) {
		result->setName( objectName );
		objectName = "";
	}

	if ( NULL != componentInstance ) {
		componentInstance->loaded();
	}
	

	componentInputLevel_ --;

	return result;
}

void VFFInputStream::readComponentInstance( Component* component )
{
	componentInputLevel_ = -1;
	if ( NULL == topLevelComponent_ ) {
		topLevelComponent_ = component;	

		component->preLoading();
		component->loading();
	}

	readObject( component, 0 );
	
	component->loaded();

	assignDeferredProperties(component);	

	componentInputLevel_ = -1;

	component->postLoaded( topLevelControlVisibility_ );
}

Component* VFFInputStream::createNewComponent(Component* componentInstance, int flags)
{
	Component* result = NULL;

	if ( parser_->tokenSymbolIs( "object" ) ) {
		parser_->savePosition();

		String currentSymbol;
		String objectName;		
		try {
			//go to object name
			parser_->nextToken();
			currentSymbol = parser_->tokenString();

			VCFChar token;

			if ( currentSymbol == ":" ) {
				currentSymbol = "";
				token = parser_->getToken();
			}
			else {
				//skip to ':' 
				token = parser_->nextToken();				
			}			
			
			parser_->checkToken( ':' );
			parser_->nextToken();

			if ( objectName.empty() ) {
				objectName = currentSymbol;
			}
			
			
			String className = parser_->tokenString();
			String classID;
			parser_->nextToken();
			if ( parser_->getToken() == ',' ) {
				parser_->nextToken();
				classID = parser_->tokenString();
				parser_->nextToken();
			}

			String fallbackClassName;
			bool skipNextToken = false;			
			
			if ( parser_->getToken() == ',' ) {
				parser_->nextToken();
				fallbackClassName = parser_->tokenString();
			}
			else {
				skipNextToken = true;
			}
			
			if ( flags & VFFInputStream::ufCreateComponent ) {
				result = (Component*)createClassInstance( className, classID, fallbackClassName );
				
				if ( NULL == topLevelComponent_ ) {
					topLevelComponent_ = result;
				}
			}
			else if ( (flags & VFFInputStream::ufCreateChildrenIfNoInstance) && (NULL != componentInstance) ) {
				if ( componentInstance != topLevelComponent_ ) {
					result = componentInstance->findComponent( currentSymbol );
				}
				else {
					result = componentInstance;
				}

				if ( NULL == result ) {
					result = (Component*)createClassInstance( className, classID, fallbackClassName );
					if ( NULL == topLevelComponent_ ) {
						topLevelComponent_ = result;
					}					
				}
			}

			if ( NULL != result ) {
				if ( setDesignMode_ ) {
					result->setDesigning( true );
				}
				result->loading();
				
				result->setName( objectName );				
			}
			else {
				parser_->error( "Unable to instantiate an object of type \"" + className + "\"" );
			}

			if ( !skipNextToken ) {
				parser_->nextToken();
			}
		}
		catch ( BasicException& e ) {
			StringUtils::trace( e.getMessage() + "\n" );
			parser_->restorePosition();
			return result;
		}

		parser_->restorePosition();
	}
	return result;
}

Component* VFFInputStream::readNewComponent()
{
	Component* result = NULL;	
	
	result = readObject( NULL, VFFInputStream::ufCreateComponent | VFFInputStream::ufCreateChildren );	

	if ( NULL != result ) {
		result->loaded();
	}	

	assignDeferredProperties( result );

	if ( -1 == componentInputLevel_ ) {
		result->postLoaded(topLevelControlVisibility_);
	}

	return result;
}

void VFFInputStream::hexToBin( const String& hexString, Persistable* persistableObject )
{
	int32 hexSize = hexString.size();
	int32 binSize = hexSize / 2;
	VCFChar* binBuffer = new VCFChar[binSize];

	const VCFChar* hexStringBuf = hexString.c_str();

	memset( binBuffer, 0, binSize*sizeof(VCFChar) );
	VCFChar tmpHexBuf[3];
	memset( tmpHexBuf, 0, 3*sizeof(VCFChar) );
	VCFChar* tmpBinBuffer = binBuffer;

	//THis is Icky code !!!!
	while ( binSize > 0 ) {

		tmpHexBuf[0] = hexStringBuf[0];
		tmpHexBuf[1] = hexStringBuf[1];
		uchar hex = '\0';
        hex = StringUtils::fromStringAsHexNumber( tmpHexBuf );

        //swscanf( tmpHexBuf, L"%X", &hex );

		*tmpBinBuffer = hex;
		hexStringBuf += 2;
		binSize --;
		tmpBinBuffer ++;
	}
	BasicInputStream bis( (const uchar*)binBuffer, (hexSize / 2) * sizeof(VCFChar) );
	persistableObject->loadFromStream( &bis );
	delete [] binBuffer;
}


void VFFInputStream::registerComponentConstant( const String& name, const String& data )
{
	VCF_ASSERT( !name.empty() );

	componentConstants.setOwnsObjectValues( true );
	componentConstants[name] = data;
}

void VFFInputStream::registerComponentConstant( const String& name, ComponentConstantFunc funcPtr )
{
	VCF_ASSERT( !name.empty() );
	VCF_ASSERT( NULL != funcPtr );

	componentConstants.setOwnsObjectValues( true );

	FuncPtrHolder* holder = new FuncPtrHolder(funcPtr);	
	componentConstants[name] = holder;
}

bool VFFInputStream::getComponentConstant( const String& name, String& value )
{	
	bool result = false;
	bool resString = false;

	if ( name.size() > 4 ) {
		if ( name.substr(0,4) == "res:" ) {
			resString = true;
		}
	}

	if ( resString ) {
		//we have a reference to a resource file.
		//get the resource bundle and add it to the 
		//remaining string

		value = 
			System::findResourceDirectory( System::getCurrentThreadLocale() );

		value += name.substr(4,name.size()-4);

		if ( !File::exists(value) ) {
			//revert back, let the underlying object attempt to 
			//deal with this. This will work perfectly for 
			//images
			value = name;
		}

		result = true;
	}
	else {
		const Dictionary& d = componentConstants;
		
		VariantData tmp = d[name];
		if ( !tmp.isNull() && tmp.type != pdUndefined ) {
			
			if ( tmp.type == pdObject ) {
				FuncPtrHolder* holder = (FuncPtrHolder*)((Object*)tmp);
				
				value = (*holder->funcPtr)( name );
				result = true;
			}
			else {
				value = (String)tmp;
				result = true;
			}
		}
	}

	return result;
}

void VFFInputStream::internal_clearComponentConstants()
{
	componentConstants.clear();
}

String VFFInputStream::transform( const String& originalValue )
{
	if ( NULL != VFFInputStream::transformer ) {
		return VFFInputStream::transformer->transform( originalValue );
	}

	return originalValue;
}

/**
$Id$
*/

