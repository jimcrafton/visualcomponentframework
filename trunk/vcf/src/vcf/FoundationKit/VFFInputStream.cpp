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

VariantData getKeyFromIndex( const String& index, int token ) ;

static Dictionary componentConstants;

class FuncPtrHolder : public Object {
public:
	FuncPtrHolder(VFFInputStream::ComponentConstantFunc fp): funcPtr(fp){}

	VFFInputStream::ComponentConstantFunc funcPtr;
};



VFFInputStream::VFFInputStream( InputStream* stream ):
    stream_(stream),	
    parser_(NULL),
	topLevelComponent_(NULL),
	deleteStream_(false),
	atTopLevel_(true),
    componentInputLevel_(-1),
	topLevelControlVisibility_(false),
	setDesignMode_(false)	
{
	parser_ = new VCF::VFFParser( this );
}

VFFInputStream::VFFInputStream( const VCF::String& vffString ):
	componentInputLevel_(-1),
	parser_(NULL),
	stream_(NULL),
	deleteStream_(true),
	atTopLevel_(true),
	topLevelComponent_(NULL),
	topLevelControlVisibility_(false),
	setDesignMode_(false)	
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

void VFFInputStream::readDelegates( VCF::Component* component, VCF::Class* clazz )
{	
	if ( parser_->tokenSymbolIs( "delegates" ) ) {	

		while ( (VFFParser::TO_EOF != parser_->getToken()) && (!parser_->tokenSymbolIs( "end" )) ) {
			String currentSymbol = parser_->tokenString();

			VCFChar token = parser_->nextToken();

			//do delegate
			switch ( token ) {
				case '=' :  {
					processDelegateAsignment( token, currentSymbol, clazz );
				}
				break;				
			}

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

							
							if ( (pdObject == prop->getType()) && ('@' == value[0]) ) {
								value.erase( 0, 1 );
								if ( !value.empty() ) {
									//need to adjust this for arrays/collections!
									//deferredProperties_.push_back( new DeferredPropertySetter( value, prop->getName(), prop->getSource() ) );
								}
							}
							else {
								String newVal;							
								if ( VFFInputStream::getComponentConstant( value, newVal ) ) {
									value = newVal;
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

								prop->setAtKey( key, &varVal, true );
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
							prop->setAtKey( key, value, true );
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

				if ( prop->getType() != pdObject ) {
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
					prop->setAtKey( key, &tmp, true );

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
						if ( (pdObject == prop->getType()) && ('@' == value[0]) ) {
							//OK our value is actually a component name so we are
							//going to store it in a list for later, because we may not
							//have an existing instance of the component yet. To store
							//this successfully we need the name of the property to set,
							//the actualy object instance that we are going to set the
							//property on, and the name of the component to try and retreive
							//once we get to that point.
							
							value.erase( 0, 1 );
							if ( !value.empty() ) {
								deferredProperties_.push_back( new DeferredPropertySetter( value, prop->getName(), prop->getSource() ) );
							}
						}
						else {
							String newVal;							
							if ( VFFInputStream::getComponentConstant( value, newVal ) ) {
								value = newVal;
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

		/*
		Control* control = dynamic_cast<Control*>(component);
		if ( NULL != control ) {
			control->setVisible( false );
		}
		*/
		
		component->preLoading();

		component->loading();
	}

	readObject( component, VFFInputStream::ufCreateChildren );// | VFFInputStream::ufCreateChildrenIfNoInstance );

	assignDeferredProperties(component);
	
	componentInputLevel_ = -1;

	component->loaded();

	component->postLoaded( topLevelControlVisibility_ );
	/*
	Control* control = dynamic_cast<Control*>(component);
	if ( NULL != control ) {
		control->setVisible( topLevelControlVisibility_ );
	}
	*/
}

void VFFInputStream::assignDeferredProperties( Component* component )
{
	if ( -1 == componentInputLevel_ ) {
		std::vector<DeferredPropertySetter*>::iterator it = deferredProperties_.begin();
		while ( it != deferredProperties_.end() ) {
			DeferredPropertySetter* dps = *it;
			Class* clazz = dps->source_->getClass();
			Property* prop = clazz->getProperty( dps->propertyName_ );
			if ( NULL != prop ) {
				Component* foundComponent = NULL;
				if ( true == component->bindVariable( &foundComponent, dps->propertyVal_ ) ) {
					VariantData data;
					data = foundComponent;
					prop->set( &data );
				}
			}
			delete dps;
			dps = NULL;
			it ++;
		}
		deferredProperties_.clear();
	}
}

Object* VFFInputStream::createClassInstance( const String& className, const String& classID, const String& fallbackClassName )
{
	Object* result = NULL;

	try {
		result = ClassRegistry::createNewInstance( className );
	}
	catch (BasicException&) {
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

	
	if ( parser_->tokenSymbolIs( "object" ) ) {
		String currentSymbol;
		String objectName;

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
					//control = dynamic_cast<Control*>(result);
					//if ( NULL != control ) {
					//	controlContainer = control->getContainer();
					//}
				}
				else {
					parser_->error( "Unable to instantiate an object of type \"" + className + "\"" );
				}
			}
			else if ( (flags & VFFInputStream::ufCreateChildrenIfNoInstance) && (NULL != componentInstance) ) {
				
				if ( componentInstance != topLevelComponent_ ) {					
					/*
					Control* control = dynamic_cast<Control*>( componentInstance );
					if ( NULL != control ) {
						controlContainer = control->getContainer();
					}
					
					
					if ( NULL != controlContainer ) {
						childComponent = controlContainer->findControl( currentSymbol );
					}
					if ( childComponent == NULL ) {
						childComponent = componentInstance->findComponent( currentSymbol );
					}
					*/

					childComponent = componentInstance->findComponent( currentSymbol );

					result = childComponent;
					//controlContainer = NULL;
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
//					control = dynamic_cast<Control*>(result);
//					if ( NULL != control ) {
//						controlContainer = control->getContainer();
//					}
				}
				else {
					parser_->error( "Unable to instantiate an object of type \"" + className + "\"" );
				}

			}
			else if ( (flags & VFFInputStream::ufFindSubComponent) && (NULL != componentInstance) ) {
				/*
				Control* control = dynamic_cast<Control*>( componentInstance );
				if ( NULL != control ) {
					controlContainer = control->getContainer();
				}
				
				
				if ( NULL != controlContainer ) {
					childComponent = controlContainer->findControl( currentSymbol );
				}
				if ( childComponent == NULL ) {
					childComponent = componentInstance->findComponent( currentSymbol );
				}
				controlContainer = NULL;
				*/

				childComponent = componentInstance->findComponent( currentSymbol );

				if ( NULL != childComponent ) {
					clazz = childComponent->getClass();
					if ( clazz->getID() != classID ) {
						parser_->error( MAKE_ERROR_MSG_2("ClassID of passed in component doesn't match ClassID encountered in parsing stream") );
					}
					//control = dynamic_cast<Control*>(childComponent);
					//if ( NULL != control ) {
					//	controlContainer = control->getContainer();
					//}
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
					if ( (clazz->getID() != classID) && (topLevelComponent_ != componentInstance) ) {
						parser_->error( MAKE_ERROR_MSG_2("ClassID of passed in component doesn't match ClassID encountered in parsing stream") );
					}
					//control = dynamic_cast<Control*>(componentInstance);
					//if ( NULL != control ) {
					//	controlContainer = control->getContainer();
					//}
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
							catch ( BasicException& ) {
								StringUtils::trace( String("Error processing assignment for ") + currentSymbol + "\n" );
							}
						}
						break;
					}
				}

				while ( parser_->tokenSymbolIs( "object" ) ) {

					Component* newComponent = NULL;

					if ( flags & VFFInputStream::ufCreateChildren &&
						!(flags & VFFInputStream::ufCreateChildrenIfNoInstance) ) {
						newComponent = readNewComponent();
					}
					else if ( flags & VFFInputStream::ufCreateChildrenIfNoInstance ) {
						newComponent = readObject( componentInstance, flags );
					}
					else if ( flags & VFFInputStream::ufFindSubComponent ) {
						readObject( childComponent, VFFInputStream::ufFindSubComponent );
					}
					else {
						readObject( componentInstance, VFFInputStream::ufFindSubComponent );
					}

					if ( (flags & VFFInputStream::ufCreateChildren) ||
						(flags & VFFInputStream::ufCreateChildrenIfNoInstance)  ) {
						if ( NULL != newComponent ) {
							//see if we can assign the component to a field
							//in the parent control
							
							Class* componentClass = topLevelComponent_->getClass();
							if ( NULL != componentClass ) {
								Field* field = componentClass->getField( newComponent->getName() );
								if ( NULL != field ) {
                                    VariantData vd(newComponent);
									field->set( &vd );
								}
							}
							
							result->addNewComponent( newComponent );
						}
					}
					
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
	
	assignDeferredProperties(component);	

	componentInputLevel_ = -1;
	
	component->loaded();

	component->postLoaded( topLevelControlVisibility_ );
}

Component* VFFInputStream::readNewComponent()
{
	Component* result = NULL;	
	
	result = readObject( NULL, VFFInputStream::ufCreateComponent | VFFInputStream::ufCreateChildren );


	assignDeferredProperties( result );

	if ( NULL != result ) {
		result->loaded();
	}	

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

	return result;
}

void VFFInputStream::internal_clearComponentConstants()
{
	componentConstants.clear();
}
/**
$Id$
*/

