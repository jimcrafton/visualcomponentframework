//BusinessObjectValidation.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/AdapterModels.h"
#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;



class BusinessObjectValidationWindow : public Window {
public:
	BusinessObjectValidationWindow() {}
	virtual ~BusinessObjectValidationWindow(){};
};

_class_rtti_(BusinessObjectValidationWindow, "VCF::Window", "BusinessObjectValidationWindow")
_class_rtti_end_



class BusinessObject : public Object {
public:

	BusinessObject():deposit_(0.0), yearJoined_(1900){}

	String firstName() const {
		return firstName_;
	}

	void setFirstName( const String& val ) {
		firstName_ = val;
	}

	String lastName() const {
		return lastName_;
	}

	void setLastName( const String& val ) {
		lastName_ = val;
	}

	String email() const {
		return email_;
	}

	void setEmail( const String& val ) {
		email_ = val;
	}

	String workPhone() const {
		return workPhone_;
	}

	void setWorkPhone( const String& val ) {
		workPhone_ = val;
	}

	double deposit() const {
		return deposit_;
	}

	void setDeposit( const double& val ) {
		deposit_ = val;
	}

	uint32 yearJoined() const {
		return yearJoined_;
	}

	void setYearJoined( const uint32& val ) {
		yearJoined_ = val;
	}

protected:
	String firstName_;
	String lastName_;
	String email_;
	String workPhone_;
	double deposit_;
	uint32 yearJoined_;
};



_class_rtti_(BusinessObject, "VCF::Object", "BusinessObject")
	_property_( String, "firstName", firstName, setFirstName, "" )
	_property_( String, "lastName", lastName, setLastName, "" )
	_property_( String, "email", email, setEmail, "" )
	_property_( String, "workPhone", workPhone, setWorkPhone, "" )
	_property_( double, "deposit", deposit, setDeposit, "" )
	_property_( uint32, "yearJoined", yearJoined, setYearJoined, "" )
_class_rtti_end_



class BizApp : public Application {
public:
	BusinessObject* currentBO;

	BizApp( int argc, char** argv ) : Application(argc, argv) {
		currentBO = NULL;

		addCallback( new ClassProcedure1<Event*,BizApp>(this, &BizApp::newObject), "BizApp::newObject" );
		addCallback( new ClassProcedure1<Event*,BizApp>(this, &BizApp::updateNewObject), "BizApp::updateNewObject" );

		addCallback( new ClassProcedure1<Event*,BizApp>(this, &BizApp::saveObject), "BizApp::saveObject" );
		addCallback( new ClassProcedure1<Event*,BizApp>(this, &BizApp::updateSaveObject), "BizApp::updateSaveObject" );

		addCallback( new ClassProcedure1<Event*,BizApp>(this, &BizApp::deleteObject), "BizApp::deleteObject" );
		addCallback( new ClassProcedure1<Event*,BizApp>(this, &BizApp::updateDeleteObject), "BizApp::updateDeleteObject" );
		
		addCallback( new ClassProcedure1<Event*,BizApp>(this, &BizApp::updateCurrent), "BizApp::updateCurrent" );

		addCallback( new ClassProcedure1<Event*,BizApp>(this, &BizApp::validationFailed), "BizApp::validationFailed" );
		addCallback( new ClassProcedure1<Event*,BizApp>(this, &BizApp::validationOK), "BizApp::validationOK" );

		
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(BusinessObjectValidationWindow);
		REGISTER_CLASSINFO_EXTERNAL(BusinessObject);

		Window* mainWindow = Frame::createWindow( classid(BusinessObjectValidationWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

	void newObject( Event* ) {
		currentBO = new BusinessObject();
		ObjectModel* model = (ObjectModel*)findComponent( "businessObject", true );
		model->setSource( currentBO );
	}

	void deleteObject( Event* ) {
		delete currentBO;
		currentBO = NULL;
		ObjectModel* model = (ObjectModel*)findComponent( "businessObject", true );
		model->setSource( NULL );

		resetLabel( "firstName" );
		resetLabel( "lastName" );
		resetLabel( "email" );
		resetLabel( "workPhone" );
		resetLabel( "deposit" );
		resetLabel( "yearJoined" );
	}

	void saveObject( Event* ) {
		Dialog::showMessage( "Saved!\nOK, well not really, but you get the idea..." );
	}

	void updateNewObject( Event* ) {
		
	}

	void updateDeleteObject( Event* e ) {
		ActionEvent* ae = (ActionEvent*)e;
		ae->setEnabled( NULL != currentBO );
	}

	void updateSaveObject( Event* e ) {
		ActionEvent* ae = (ActionEvent*)e;
		bool enabled = false;
		if ( NULL != currentBO ) {
			ObjectModel* model = (ObjectModel*)findComponent( "businessObject", true );
			enabled = model->validate();
		}
		ae->setEnabled( enabled );
	}

	void updateCurrent( Event* e ) {
		ActionEvent* ae = (ActionEvent*)e;
		ObjectModel* model = (ObjectModel*)findComponent( "businessObject", true );		
		if ( NULL != model->getSource() ) {
			model->validate();
		}

		ae->setEnabled( NULL != model->getSource() );
	}

	void validationFailed( Event* e ) {
		ValidationErrorEvent* ve = (ValidationErrorEvent*)e;
		
		Control* c = (Control*)findComponent( ve->key.toString() + "Lbl", true );
		c->getFont()->setColor( Color::getColor("red") );
		c->repaint();
	}

	void validationOK( Event* e ) {
		ValidationEvent* ve = (ValidationEvent*)e;
		Control* c = (Control*)findComponent( ve->key.toString() + "Lbl", true );
		c->getFont()->setColor( c->getParent()->getFont()->getColor() );
		c->repaint();
	}

	void resetLabel( const String& keyName ) {
		Control* c = (Control*)findComponent( keyName + "Lbl", true );
		c->getFont()->setColor( c->getParent()->getFont()->getColor() );
		c->repaint();
	}
};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<BizApp>(argc,argv);
}


