//RegExGUI.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/ApplicationKit/ControlsKit.h"
#include "vcf/RegExKit/RegExKit.h"
#include "vcf/ApplicationKit/MessageDialog.h"

using namespace VCF;



class RegExGUIWindow : public Window {
public:
	RegExGUIWindow() {
		setCaption( "RegExGUI" );		
	}

	virtual ~RegExGUIWindow(){};

};

_class_rtti_(RegExGUIWindow, "VCF::Window", "RegExGUIWindow")
_class_rtti_end_




class RegExGUIApplication : public Application {
public:

	RegExGUIApplication( int argc, char** argv ) : Application(argc, argv),
		host("", search, ONIG_SYNTAX_RUBY), lastExpression("") {

		addCallback( new ClassProcedure1<Event*,RegExGUIApplication>
			(this, &RegExGUIApplication::findNext), "RegExGUIApplication::findNext" );

		addCallback( new ClassProcedure1<Event*,RegExGUIApplication>
			(this, &RegExGUIApplication::findPrev), "RegExGUIApplication::findPrev" );

		addCallback( new ClassProcedure1<KeyboardEvent*,RegExGUIApplication>
			(this, &RegExGUIApplication::onKeyDown), "RegExGUIApplication::onKeyDown" );

		addCallback( new ClassProcedure1<Event*,RegExGUIApplication>
			(this, &RegExGUIApplication::reset), "RegExGUIApplication::reset" );
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(RegExGUIWindow);

		Window* mainWindow = Frame::createWindow( classid(RegExGUIWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();
		supplyText();
		
		return result;
	}

	void supplyText() {
		ResourceBundle* bundle = System::getResourceBundle();
		Resource* res = bundle->getResource("Search.txt");
		search = String((char*)(res->getData()), res->getDataSize());
//		search = "Nothing to see here - move along";
		MultilineTextControl* data = dynamic_cast<MultilineTextControl*>
			(findComponent("data", true));
		data->setText(search);
		host.setRangeAsString(search); 
	}

	void findNext(Event* e) {
		TextControl* edt1 = dynamic_cast<TextControl*>(findComponent("edt1", true));
		String text = edt1->getText();
		if (text == lastExpression) {
			if (it != host.end()) {
				++it;
			}
		} else {
			host.changeSearchExpression(text);
			lastExpression = text;
			it = host.begin();
		}
		if (it != host.end()) {
			showMatch(it);
		} else {
			endSearch();
		}
	}

	void findPrev(Event* e) {
		TextControl* edt1 = dynamic_cast<TextControl*>(findComponent("edt1", true));
		String text = edt1->getText();
		if (text == lastExpression) {
			if (it != host.rend().base()) {
				--it;
			}
		} else {
			host.changeSearchExpression(text);
			lastExpression = text;
			it = host.rbegin().base();
		}
		if (it != host.rend().base()) {
			showMatch(Regex::ReverseIterator(it));
		} else {
			endSearch(true);
		}
	}

	void onKeyDown(KeyboardEvent* e) {
		VCFChar pressed = e->getKeyValue();
		if (pressed == '\r') {
			findNext(e);
		}
	}

	void reset(Event* e) {
		TextControl* edt1 = dynamic_cast<TextControl*>(findComponent("edt1", true));
		edt1->setText("");
		edt1->repaint();
		lastExpression = "";
		host.changeSearchExpression("");
		CommandButton* btn;
		btn = dynamic_cast<CommandButton*>(findComponent("nextbtn", true));
		btn->setEnabled(true);
		btn = dynamic_cast<CommandButton*>(findComponent("prevbtn", true));
		btn->setEnabled(true);
	}

	void showMatch(const Regex::Iterator& it) {
		MultilineTextControl* data = dynamic_cast<MultilineTextControl*>(findComponent("data", true));
		data->setSelectionMark(it->getPosAsOffset(), it->getText().length());
		CommandButton* btn;
		btn = dynamic_cast<CommandButton*>(findComponent("nextbtn", true));
		btn->setEnabled(true);
		btn = dynamic_cast<CommandButton*>(findComponent("prevbtn", true));
		btn->setEnabled(true);
	}

	void showMatch(const Regex::ReverseIterator& rit) {
		MultilineTextControl* data = dynamic_cast<MultilineTextControl*>(findComponent("data", true));
		data->setSelectionMark(rit->getPosAsOffset(), rit->getText().length());
		CommandButton* btn;
		btn = dynamic_cast<CommandButton*>(findComponent("nextbtn", true));
		btn->setEnabled(true);
		btn = dynamic_cast<CommandButton*>(findComponent("prevbtn", true));
		btn->setEnabled(true);
	}

	void endSearch(bool backwards=false) {
		MultilineTextControl* data = dynamic_cast<MultilineTextControl*>(findComponent("data", true));
		data->setSelectionMark(0,0);
		MessageDialog end;
		end.setMessage("End of text");
		end.setInformation("There are no more matches for this expression");
		end.addActionButton("OK", UIToolkit::mrOK, true);
		end.showModal();
		CommandButton* btn;
		if (!backwards) {
			btn = dynamic_cast<CommandButton*>(findComponent("nextbtn", true));
		} else {
			btn = dynamic_cast<CommandButton*>(findComponent("prevbtn", true));
		}
		btn->setEnabled(false);
	}

private:
	Regex::Ascii host;
	Regex::Iterator it;
	String search;
	String lastExpression;

};


int main(int argc, char *argv[])
{
	Application* app = new RegExGUIApplication( argc, argv );

	Application::main();
	
	return 0;
}


