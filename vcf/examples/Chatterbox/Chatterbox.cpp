//Chatterbox.cpp


#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/FoundationKit/RTTIMacros.h"
#include "vcf/HTMLKit/HTMLKit.h"
#include "vcf/ApplicationKit/TextControl.h"

#include "vcf/NetworkKit/NetworkKit.h"
#include "vcf/NetworkKit/Socket.h"
#include "vcf/NetworkKit/IPAddress.h"
#include "vcf/FoundationKit/Dictionary.h"
#include "vcf/FoundationKit/StringTokenizer.h"
#include "vcf/FoundationKit/XMLDictOutputStream.h"
#include "vcf/FoundationKit/XMLDictInputStream.h"

#include "vcf/ApplicationKit/AdapterModels.h"


using namespace VCF;





class ChatterboxWindow : public Window {
public:
	ChatterboxWindow() {}
	virtual ~ChatterboxWindow(){};
};

_class_rtti_(ChatterboxWindow, "VCF::Window", "ChatterboxWindow")
_class_rtti_end_




class ProfilesManager : public Dialog {
public:
	ProfilesManager() {}
	virtual ~ProfilesManager(){};
};
_class_rtti_(ProfilesManager, "VCF::Dialog", "ProfilesManager")
_class_rtti_end_



class IRCReadThread : public Thread {
public:
	TCPSocket* socket;
	IRCReadThread( TCPSocket* s ) : socket(s){

	}


	AnsiString msgData;

	void doMsg() {
		
		//System::println( "-------------------------------------------------------------------------------" );

		String msg = msgData;

		StringTokenizer tok( msg, " ");

		int elementCount = 0;

		char senderNick[256];
		char senderUser[256];
		char senderHost[256];

		memset(senderNick,0,sizeof(senderNick));
		memset(senderUser,0,sizeof(senderUser));
		memset(senderHost,0,sizeof(senderHost));


		std::vector<String> params;

		int offset = 0;

		while ( tok.hasMoreElements() ) {
			String s = tok.nextElement();
			

			if ( 0 == elementCount && s[0] == ':' ) {							
				
				
				if ( tok.hasMoreElements() ) {					
					sscanf( s.ansi_c_str() + 1, "%[^!]!%[^@]@%s", senderNick, senderUser, senderHost );
					
					offset += s.size() + 1;

					s = tok.nextElement();

					params.push_back( s );

					offset += s.size() + 1;
					elementCount ++;
					continue;
				}
				
			}
			else {
				int a = 0;
				int d = 0;
				if ( 0 == d ) {
					if ( s[0] == ':' ) {
						s.erase(0,1);
						d = 1;
					}
					

					a++;

					if ( 0 == d ) {
						params.push_back( s );						
					}
					else {						
						
						params.push_back( msgData.substr(offset,msgData.size()-offset) );
						break;
					}
				}				
			}
			
			offset += s.size() + 1;
			elementCount ++;
		}

		//StringUtils::trace( "Msg:<<\n" );

		//StringUtils::trace( Format( "\tnick:%s\n") % senderNick );
		//StringUtils::trace( Format( "\tuser:%s\n") % senderUser );
		//StringUtils::trace( Format( "\thost:%s\n") % senderHost );

		

		std::vector<String>::iterator it = params.begin();
		while ( it != params.end() ) {

			//StringUtils::trace( Format( "\tparam:%s\n") % *it );

			it++;
		}


		//StringUtils::trace( ">>" );

	}

	void parseMsg( const uchar* buf, size_t size ) {
		const uchar* start = buf;
		const uchar* tmp = buf;
		while ( ((tmp-buf) < size) ) {
			if ( (*tmp == '\r') || (*tmp == '\n') ) {

				msgData.append( (const char*)start, tmp-start );
				
				doMsg();


				msgData = "";

				if ( *tmp == '\r' ) {
					tmp ++;
				}

				if ( *tmp == '\n' ) {
					tmp ++;
				}

				start = tmp;
			}
			else {
				tmp++;
			}
		}

		if ( (tmp - start) > 1 ) {
			msgData.append( (const char*)start, tmp-start );
		}

	}

	virtual bool run() {

		TCPSocketInputStream sis(*socket);

		uchar tmp[256];
		while ( canContinue() ) {
			socket->selectFor( Socket::SelectWaitForever, Socket::ssReadable );
			
			//StringUtils::trace( "\nSelect completed\n" );

			do {			
				try {
					uint64 err = sis.read( tmp, sizeof(tmp) );					

					if ( err == 0 ) {
						StringUtils::trace( "Disconnect!\n" );						
						break;
					}
					else {
						tmp[err] = 0;
						String s;
						s.append( (const char*) tmp, err );
						StringUtils::trace( s );
						parseMsg( tmp, err );
					}
				}
				catch ( BasicException& ) {
					StringUtils::trace( "Socket error!\n" );
					break;
				}
			} while( socket->pending() && socket->isReadable() ) ;


			if ( socket->isClosed() || socket->hasError() ) {
				break;
			}
		}

		StringUtils::trace( "\nRead Thread completed\n" );
		return true;
	}
};



class Chatterbox : public Application {
public:
	String currentUser;

	TCPSocket* ircConnection;
	IRCReadThread* currentIRCThread;
	Dictionary userProfiles;



	Chatterbox( int argc, char** argv ) : Application(argc, argv) {
		HTMLKit::init( argc, argv );
		NetworkKit::init(  argc, argv );

		ircConnection = NULL;
		currentIRCThread = NULL;

		addCallback( new ClassProcedure1<KeyboardEvent*,Chatterbox>(this, &Chatterbox::userEnteredText), "Chatterbox::userEnteredText" );
		addCallback( new ClassProcedure1<Event*,Chatterbox>(this, &Chatterbox::onTestBtn), "Chatterbox::onTestBtn" );

		addCallback( new ClassProcedure1<Event*,Chatterbox>(this, &Chatterbox::editProfiles), "Chatterbox::editProfiles" );
		
	}

	virtual bool initRunningApplication(){
		bool result = Application::initRunningApplication();
		REGISTER_CLASSINFO_EXTERNAL(ChatterboxWindow);
		REGISTER_CLASSINFO_EXTERNAL(ProfilesManager);
		


		currentUser = System::getUserName();


		Window* mainWindow = Frame::createWindow( classid(ChatterboxWindow) );
		setMainWindow(mainWindow);
		mainWindow->show();


		readUserProfiles();


		addProfile( "jim", "Jim C", "jimc" );

		connectToServer( "irc.freenode.net", 6667, "ddiego" );
		
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
		div += "class=\"externalUser\"";
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


	void connectToServer( const String& host, int port, const String& nick ) {
		
		if ( NULL != ircConnection ) {
			delete ircConnection;
		}
		
		if ( currentIRCThread != NULL ) {			
			currentIRCThread->stop();
		}

		currentIRCThread = NULL;


		ircConnection = new TCPSocket();

		ircConnection->connect( host, port );


		currentIRCThread = new IRCReadThread(ircConnection);
		currentIRCThread->start();



		AnsiString msg;
		msg = (String)(Format( "USER %s %s %s :%s" ) % nick % "b" % "c" % "Odysseus");
		msg += " \r\n";

		TCPSocketOutputStream sos(*ircConnection);
		sos.write( (const uchar*)msg.c_str(), msg.size() );

		msg = (String)(Format( "NICK %s" ) % "Unknown[1]");
		msg += " \r\n";
		sos.write( (const uchar*)msg.c_str(), msg.size() );

		msg = (String)(Format( "join %s" ) % "#vcf");
		msg += " \r\n";
		sos.write( (const uchar*)msg.c_str(), msg.size() );

	}


	void readUserProfiles() {
		String profilePath = System::getCommonDirectory( System::cdUserProgramData ) + "/" + getName() + "/profileData.xml";
		File profile(profilePath,File::ofRead);		

		FileInputStream* fs = profile.getInputStream();
		if ( NULL != fs ) {
			
			XMLDictInputStream xis(fs);
			
			userProfiles.clear();
			
			//read in the dictionary from the stream
			xis >> &userProfiles;

			delete fs;
		}


		//userProfiles
	}

	void saveUserProfiles() {
		String profilePath = System::getCommonDirectory( System::cdUserProgramData ) + "/" + getName() + "/"; 
		File profile;
		profile.create( profilePath );

		profile.create( profilePath + "profileData.xml", File::ofWrite );

		OutputStream* fs = profile.getOutputStream();

		XMLDictOutputStream xos(fs);

		xos << &userProfiles;


		delete fs;
	}

	void addProfile( const String& userName, const String& realName, const String& nickName )  {
		Dictionary* profile = new Dictionary();
		(*profile)["userName"] = userName;
		(*profile)["realName"] = realName;
		(*profile)["nickName"] = nickName;

		userProfiles[userName] = profile;
	}

	void editProfiles( Event* ) {
		ProfilesManager* dlg = (ProfilesManager*) Frame::createDialog( classid(ProfilesManager) );

		DictionaryListModel* m = (DictionaryListModel*)dlg->findComponent( "profiles" );

		

		m->setDictionary( &userProfiles );

		dlg->showModal();

		delete dlg;
	}
};


int main(int argc, char *argv[])
{
	return ApplicationKitMain<Chatterbox>(argc,argv);
}


