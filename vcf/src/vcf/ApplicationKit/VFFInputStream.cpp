//VFFInputStream.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/VFFInputStream.h"

using namespace VCF;


VFFInputStream::VFFInputStream( InputStream* stream ):
	componentInputLevel_(-1),
	parser_(NULL),
	stream_(stream),
	atTopLevel_(true),
	topLevelComponent_(NULL),
	topLevelControlVisibility_(false),
	setDesignMode_(false)
{
	parser_ = new VCF::Parser( this );
}


VFFInputStream::~VFFInputStream()
{
	delete parser_;
	parser_ = NULL;
}

void VFFInputStream::getOuterClassNameAndUUID( String& className, String& UUID, String& fallbackClassName )
{
	className = "";
	UUID = "";

	parser_->resetStream();

	if ( true == parser_->tokenSymbolIs( "object" ) ) {
		String currentSymbol;
		while ( (TO_EOF != parser_->getToken()) && (false == parser_->tokenSymbolIs( "end" )) ) {
			currentSymbol = parser_->tokenString();
			try {
				// do object
				VCFChar token = parser_->nextToken();
				switch ( token ) {
					case ':' : {
						parser_->nextToken();
						className = parser_->tokenString();
						parser_->nextToken();
						parser_->checkToken( ',' );
						parser_->nextToken();
						UUID = parser_->tokenString();

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

		while ( (TO_EOF != parser_->getToken()) && (!parser_->tokenSymbolIs( "end" )) ) {
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
			EventProperty* eventProperty = clazz->getEvent ( currentSymbol );

			if ( NULL != eventProperty ) {

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
							prop->set( value );

							if ( 0 == componentInputLevel_ ) {
								if ( (prop->getName() == "visible") ||
									(prop->getDisplayName() == "visible") ) {
									topLevelControlVisibility_ = *prop->get();
								}
							}
						}
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

					processAsignmentTokens( newToken, objPropName, clazz );
				}
			}
			else {
				processAsignmentTokens( newToken, objPropName, clazz );
			}
		}
		break;

		case '[' : {

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

		Control* control = dynamic_cast<Control*>(component);
		if ( NULL != control ) {
			control->setVisible( false );
		}
		
		component->loading();
	}

	readObject( component, VFFInputStream::ufCreateChildren );// | VFFInputStream::ufCreateChildrenIfNoInstance );

	assignDeferredProperties(component);
	
	componentInputLevel_ = -1;

	component->loaded();

	Control* control = dynamic_cast<Control*>(component);
	if ( NULL != control ) {
		control->setVisible( topLevelControlVisibility_ );
	}
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

	String s;
	Control* control = NULL;
	Class* clazz = NULL;
	Container* controlContainer = NULL;
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
			parser_->nextToken();
			parser_->checkToken( ',' );
			parser_->nextToken();
			String classID = parser_->tokenString();

			String fallbackClassName;
			
			bool skipNextToken = false;
			parser_->nextToken();
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
					control = dynamic_cast<Control*>(result);
					if ( NULL != control ) {
						controlContainer = control->getContainer();
					}
				}
				else {
					parser_->error( "Unable to instantiate an object of type \"" + className + "\"" );
				}
			}
			else if ( (flags & VFFInputStream::ufCreateChildrenIfNoInstance) && (NULL != componentInstance) ) {
				
				if ( componentInstance != topLevelComponent_ ) {					
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
					result = childComponent;
					controlContainer = NULL;
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
					control = dynamic_cast<Control*>(result);
					if ( NULL != control ) {
						controlContainer = control->getContainer();
					}
				}
				else {
					parser_->error( "Unable to instantiate an object of type \"" + className + "\"" );
				}

			}
			else if ( (flags & VFFInputStream::ufFindSubComponent) && (NULL != componentInstance) ) {
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

				if ( NULL != childComponent ) {
					clazz = childComponent->getClass();
					if ( clazz->getID() != classID ) {
						parser_->error( MAKE_ERROR_MSG_2("ClassID of passed in component doesn't match ClassID encountered in parsing stream") );
					}
					control = dynamic_cast<Control*>(childComponent);
					if ( NULL != control ) {
						controlContainer = control->getContainer();
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
					if ( (clazz->getID() != classID) && (topLevelComponent_ != componentInstance) ) {
						parser_->error( MAKE_ERROR_MSG_2("ClassID of passed in component doesn't match ClassID encountered in parsing stream") );
					}
					control = dynamic_cast<Control*>(componentInstance);
					if ( NULL != control ) {
						controlContainer = control->getContainer();
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


		//read in properties, sub objects, and delegates

		while ( (TO_EOF != parser_->getToken()) && (!parser_->tokenSymbolIs( "end" )) ) {
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
							processAsignmentTokens( token, currentSymbol, clazz );
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
									field->set( &VariantData(newComponent) );
								}
							}
							
							
							//see if we need to add it as a control or component
							Control* newControl = dynamic_cast<Control*>(newComponent);
							if ( (NULL != newControl) && (NULL != controlContainer) ) {
								controlContainer->add( newControl, newControl->getAlignment() );
							}
							else {
								result->addComponent( newComponent );
							}
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

		Control* control = dynamic_cast<Control*>(component);
		if ( NULL != control ) {
			control->setVisible( false );
		}

		component->loading();
	}

	readObject( component, 0 );
	
	assignDeferredProperties(component);	

	componentInputLevel_ = -1;
	
	component->loaded();

	Control* control = dynamic_cast<Control*>(component);
	if ( NULL != control ) {
		control->setVisible( topLevelControlVisibility_ );
	}
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
		Control* control = dynamic_cast<Control*>(result);
		if ( NULL != control ) {
			control->setVisible( topLevelControlVisibility_ );
		}
	}

	return result;
}

void VFFInputStream::hexToBin( const String& hexString, Persistable* persistableObject )
{
	long hexSize = hexString.size();
	long binSize = hexSize / 2;
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
	BasicInputStream bis( (char*)binBuffer, (hexSize / 2) * sizeof(VCFChar) );
	persistableObject->loadFromStream( &bis );
	delete [] binBuffer;
}



/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:26  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.4  2005/10/09 04:32:44  ddiego
*added some minor fixes in component persistence for vcf builder.
*
*Revision 1.3.2.3  2005/09/18 22:54:47  ddiego
*fixed some minor bugs in vffinput stream and parser class.
*
*Revision 1.3.2.2  2005/09/16 01:12:01  ddiego
*fixed bug in component loaded function.
*
*Revision 1.3.2.1  2005/08/15 03:10:51  ddiego
*minor updates to vff in out streaming.
*
*Revision 1.3  2005/07/09 23:14:57  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.2.4.1  2005/04/09 17:20:36  marcelloptr
*bugfix [ 1179853 ] memory fixes around memset. Documentation. DocumentManager::saveAs and DocumentManager::reload
*
*Revision 1.2  2004/08/07 02:49:10  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/06/06 07:05:31  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/05/06 02:56:35  ddiego
*checking in OSX updates
*
*Revision 1.1.2.2  2004/04/29 03:43:15  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:20  ddiego
*migration towards new directory structure
*
*Revision 1.17.2.1  2004/04/21 02:17:26  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.17  2004/04/03 15:48:48  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.13.2.4  2004/03/21 00:39:24  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.13.2.3  2004/01/18 04:52:46  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.13.2.2  2004/01/16 04:30:47  ddiego
*some more minor mods to menus and the Component class. Added some utility
*methods for determining the state of a component, and added two new
*delegates for firing events when the component is loaded and saved,
*as well as value changes for the COmponentState enum so that some of
*the values of the component state can be OR'd together.
*
*Revision 1.13.2.1  2004/01/11 19:57:54  ddiego
*implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
*plus created a new include/rtti and src/rtti directories and moved the
*various rtti related code to the appropriate directories
*
*Revision 1.13  2003/12/18 05:16:02  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.2.1  2003/08/18 19:52:39  ddiego
*changed the Container from being a class you derive from to a separate
*intance that is created and assigned dynamically to any Control.
*
*Revision 1.12  2003/08/09 02:56:46  ddiego
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
*Revision 1.11.2.1  2003/07/24 04:10:45  ddiego
*added fixes for the following tasks:
*Task #82279 ApplicationKit: add static methods to singleton objects
*Task #82277 FoundationKit: add static methods to singleton objects
*this required a bunch of changes in terms of getting rid of older style code
*
*Revision 1.11  2003/05/17 20:37:25  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.10.2.1  2003/03/12 03:12:16  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.10  2003/02/26 04:30:47  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.9.8.3  2003/01/08 00:19:51  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.9.8.2  2002/12/28 01:56:22  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9.8.1  2002/12/27 23:04:48  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.9  2002/09/12 03:26:05  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.8.6.2  2002/09/05 04:31:46  ddiego
*fixed hte bug in hte VCFInputStream, nested class instances will now
*read in correctly.
*Also added code to properly update the name manager whenever a new form is
*loaded up to prevent name collision within ina a form class. Fixed
*a bit of selection code in the TreeControl class as well.
*
*Revision 1.8.6.1  2002/09/03 05:05:13  ddiego
*fixed some more bugs in getting form building to work again. It now works
*but of course there are new issues, namely reading in nested properties
*in a form file where the properties are objects like:
*font.color.red, so this needs to be fixed in hte VFFInputStream file
*also need to have hte form saved properly
*still miscellaneous crashes but getting closer to an alpha tes state
*
*Revision 1.8  2002/05/09 03:10:44  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.7.4.2  2002/04/27 15:52:23  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.7.4.1  2002/04/08 20:55:30  zzack
*changed include style
*
*Revision 1.7  2002/01/24 01:46:49  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


