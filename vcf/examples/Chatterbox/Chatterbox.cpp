//Chatterbox.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/ApplicationKit/TextControl.h"


using namespace VCF;



class ChatterboxWindow : public Window {
public:
	ChatterboxWindow() {}
	virtual ~ChatterboxWindow(){};
};

_class_rtti_(ChatterboxWindow, "VCF::Window", "ChatterboxWindow")
_class_rtti_end_





class Chatterbox : public Application {
public:
	String currentUser;

	Chatterbox( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );

		addCallback( new ClassProcedure1<KeyboardEvent*,Chatterbox>(this, &Chatterbox::userEnteredText), "Chatterbox::userEnteredText" );
		addCallback( new ClassProcedure1<Event*,Chatterbox>(this, &Chatterbox::onTestBtn), "Chatterbox::onTestBtn" );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(ChatterboxWindow);


		currentUser = System::getUserName();


		Window* mainWindow = Frame::createWindow( classid(ChatterboxWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		
		return result;
	}

	void addUserMessageDiv( HTMLElement* contentDiv, const String& message ) {
		String div = "<div ";
		div += " >";

		div += "<span class=\"user\">" + currentUser + ":</span>";
		div += "<span class=\"userMessage\">";

		div += message;

		div += "</span>";


		div += "</div>";

		String inner = contentDiv->getInnerHTML();
		inner += div;

		contentDiv->setInnerHTML( inner );
	}

	void addExternalUserMessageDiv( HTMLElement* contentDiv, const String& user, const String& message ) {
		String div = "<div ";
		div += " >";

		div += "<span class=\"externalUser\">" + user + ":</span>";
		div += "<span class=\"externalUserMessage\">";

		div += message;

		div += "</span>";


		div += "</div>";

		String inner = contentDiv->getInnerHTML();
		inner += div;

		contentDiv->setInnerHTML( inner );
	}

	void addUserMessage( const String& message ) {
		HTMLBrowserControl* browser = (HTMLBrowserControl*)findComponent( "chatterView", true );


		HTMLElementCollection all = browser->getDocument().getAll();
		for (long i=0;i<all.getLength();i++ ) {
			HTMLElement* element = all.item(i);
			if ( element->getID() == "content" ) {
				addUserMessageDiv( element, message );
			}
		}
	}


	void userEnteredText( KeyboardEvent* e ) {
		if ( vkEnter == e->virtualKeyCode && !(e->hasShiftKey()) ) {
			TextControl* tc = (TextControl*)findComponent( "chatBox", true );
			addUserMessage( tc->getText() );
			tc->setText( "" );
		}
	}

	void onTestBtn(Event*) {
		HTMLBrowserControl* browser = (HTMLBrowserControl*)findComponent( "chatterView", true );


		HTMLElementCollection all = browser->getDocument().getAll();
		for (long i=0;i<all.getLength();i++ ) {
			HTMLElement* element = all.item(i);
			if ( element->getID() == "content" ) {
				addExternalUserMessageDiv( element, "foo", "blah blah blah....." );
			}
		}

		
	}
};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Chatterbox>(argc,argv);
}


