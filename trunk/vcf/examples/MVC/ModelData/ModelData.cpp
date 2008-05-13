//ModelData.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/SimpleListModel.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/FoundationKit/Dictionary.h"


using namespace VCF;

class Person : public Model {
public:
	virtual bool isEmpty() {
		return attributes.empty();
	}

	virtual VariantData getValue( const VariantData& key=VariantData::null() ) 	{
		String strKey = key;
		return attributes[ strKey ];
	}

	virtual void setValue( const VariantData& value, const VariantData& key=VariantData::null() )  {
		String strKey = key;
		attributes[ strKey ] = value;
		ModelEvent e( this, Model::MODEL_CHANGED );
		changed( &e );
	}

	uint32 getAge() const {
		return attributes["Age"];
	}

	String getFirstName() const {
		return attributes["FirstName"];
	}

	String getLastName() const {
		return attributes["LastName"];
	}

	String getZIPCode() const {
		return attributes["ZIPCode"];
	}

	String getAddress() const {
		return attributes["Address"];
	}

	String getState() const {
		return attributes["State"];
	}

	String getCountry() const {
		return attributes["Country"];
	}

	String getPhoneNumber() const {
		return attributes["PhoneNumber"];
	}

	void setAge( const uint32& val ) {
		attributes["Age"] = val;
		ModelEvent e( this, Model::MODEL_CHANGED );
		changed( &e );
	}

	void setFirstName( const String& val ) {
		attributes["FirstName"] = val;
		ModelEvent e( this, Model::MODEL_CHANGED );
		changed( &e );
	}

	void setLastName( const String& val ) {
		attributes["LastName"] = val;
		ModelEvent e( this, Model::MODEL_CHANGED );
		changed( &e );
	}

	void setZIPCode( const String& val ) {
		attributes["ZIPCode"] = val;
		ModelEvent e( this, Model::MODEL_CHANGED );
		changed( &e );
	}

	void setAddress( const String& val ) {
		attributes["Address"] = val;
		ModelEvent e( this, Model::MODEL_CHANGED );
		changed( &e );
	}

	void setState( const String& val ) {
		attributes["State"] = val;
		ModelEvent e( this, Model::MODEL_CHANGED );
		changed( &e );
	}

	void setCountry( const String& val ) {
		attributes["Country"] = val;
		ModelEvent e( this, Model::MODEL_CHANGED );
		changed( &e );
	}

	void setPhoneNumber( const String& val ) {
		attributes["PhoneNumber"] = val;
		ModelEvent e( this, Model::MODEL_CHANGED );
		changed( &e );
	}

protected:
	Dictionary attributes;
};

_class_rtti_(Person, "VCF::Model", "Person")
_property_( uint32, "age", getAge, setAge, "" );
_property_( String, "firstName", getFirstName, setFirstName, "" );
_property_( String, "lastName", getLastName, setLastName, "" );
_property_( String, "zipCode", getZIPCode, setZIPCode, "" );
_property_( String, "address", getAddress, setAddress, "" );
_property_( String, "state", getState, setState, "" );
_property_( String, "country", getCountry, setCountry, "" );
_property_( String, "phoneNumber", getPhoneNumber, setPhoneNumber, "" );
_class_rtti_end_






class ModelDataWindow : public Window {
public:
	ModelDataWindow() {}
	virtual ~ModelDataWindow(){};
};

_class_rtti_(ModelDataWindow, "VCF::Window", "ModelDataWindow")
_class_rtti_end_







class ModelDataApp : public Application {
public:

	ModelDataApp( int argc, char** argv ) : Application(argc, argv) {
		addCallback( new ClassProcedure1<Event*,ModelDataApp>(this, &ModelDataApp::clickMe), "ModelDataApp::clickMe" );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(ModelDataWindow);
		REGISTER_CLASSINFO_EXTERNAL(Person);

		Window* mainWindow = Frame::createWindow( classid(ModelDataWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

	void clickMe( Event* ) {
		Person* person = (Person*)findComponent( "joeBobSnake", true );

		person->setAge( person->getAge() + 1 );
	}	

};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<ModelDataApp>(argc,argv);
}


