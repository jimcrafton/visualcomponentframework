//SciTextControl.cpp

/*
Copyright 2000-2004 The VCF Builder Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//SciTextControl.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ModelViewKit.h"

#include "vcf/ScintillaKit/ScintillaKit.h"
#include "vcf/ApplicationKit/ControlPeer.h"
#include "vcf/ScintillaKit/ScintillaPeer.h"
#include "Scintilla.h"
#include "SciLexer.h"



#include "vcf/FoundationKit/RTTIMacros.h"

using namespace VCF;




_class_rtti_(SciTextControl, "VCF::CustomControl", "SciTextControl")
_class_rtti_end_




SciTextControl::SciTextControl() : 
	Control(),
	entryMode_(SciTextControl::temInsert)
{


	

#ifdef WIN32
	
	peer_ = (ControlPeer*) new Win32ScintillaPeer( this);

#endif

	peer_->create( this );

	peer_->setControl( this );

	setVisible( true ); 

	typingTimer_ = new TimerComponent();
	addComponent( typingTimer_ );

	typingTimer_->setTimeoutInterval( 1000 );

	typingTimer_->TimerPulse += 
		new ClassProcedure1<Event*,SciTextControl>(this, &SciTextControl::onTypingTimeout, "SciTextControl::onTypingTimeout" );

	
	setKeepsReturnChar( true );
	setKeepsTabKey( true );


	SciTextModel* model = new SciTextModel();
	model->setScintillaPeer( dynamic_cast<ScintillaPeer*>(peer_) );
	addComponent( model );
	setViewModel( model );
}

SciTextControl::~SciTextControl()
{
	

}

void SciTextControl::onTypingTimeout( VCF::Event* e )
{
	stopTypingTimer();

	/*
	StringUtils::trace( "Do stuff here!\n" );
	std::vector<ContentLocation*> contents;

	while ( !contentQueue_.empty() ) {
		contents.push_back( contentQueue_.front() );

		contentQueue_.pop_front();
	}

	BasicDocument* doc = (BasicDocument*)getViewModel();
		
	VCFBuilderApplication::getApp()->processContentRangeOnDocument( doc, contents );
*/
}

void SciTextControl::onDocumentChanged( VCF::ModelEvent* e )
{
	if ( (e->getType() == TextModel::tmTextRemoved) || 
		(e->getType() == TextModel::tmTextInserted) ) {
/*	
		BasicDocument* doc = (BasicDocument*)getViewModel();

		ContentLocation* content = doc->createContentForEdit( e );

		if ( NULL != content ) {
			contentQueue_.push_back( content );
		}
		*/
	}
}


void SciTextControl::startTypingTimer()
{
	if ( typingTimer_->isActive() ) {
		typingTimer_->setActivated( false );
	}
	
	typingTimer_->setActivated( true );
}


void SciTextControl::stopTypingTimer()
{
	typingTimer_->setActivated( false );
}

SciTextModel* SciTextControl::getTextModel()
{
	return (SciTextModel*) getViewModel();
}

void SciTextControl::modelChanged( Model* oldModel, Model* newModel )
{
	

	CallBack* ev = getCallback( "SciTextControl::onDocumentChanged" );
	if ( NULL != ev && NULL != oldModel ) {
		oldModel->ModelChanged -= ev;
	}

	if ( NULL == ev ) {
		ev = new ClassProcedure1<ModelEvent*,SciTextControl>( this, &SciTextControl::onDocumentChanged, "SciTextControl::onDocumentChanged" );
	}	

	newModel->ModelChanged += ev;

	peer_->setControl( this );
}


void SciTextControl::paint( GraphicsContext * context )
{

}

void SciTextControl::setEditorStyle( const int& style, const ulong& foreColor, 
								const ulong& backColor, const ulong& size, 
								const String& fontFace, const bool& bold, 
								const bool& italic )
{
	((Win32ScintillaPeer*)peer_)->setEditorStyle( style, foreColor, backColor, size, fontFace, bold, italic );
}

void SciTextControl::setCaretPosition( const unsigned long& caretPos )
{
	((Win32ScintillaPeer*)peer_)->setCaretPosition( caretPos );
}

VCF::ulong SciTextControl::getLineFromPosition( VCF::ulong pos )
{	
	return ((Win32ScintillaPeer*)peer_)->getLineFromPosition( pos );
}

VCF::ulong SciTextControl::getColumnFromPosition( VCF::ulong pos )
{
	return ((Win32ScintillaPeer*)peer_)->getColumnFromPosition( pos );
}
/*
void SciTextControl::readPreferences( Preferences* preferences )
{
	std::map<int,String> styles;
	
	styles[STYLE_DEFAULT]= "Default" ;

	TextDocument* tm = this->getTextModel();
	String language;
	if ( NULL != tm ) {
		language = tm->getLexerID();
	}
	
	if ( !language.empty() ) {
		if ( language == TD_LANG_CPP ) {
			styles[SCE_C_DEFAULT]= "Default" ;
			
			styles[SCE_C_IDENTIFIER]= "Default" ;	
			
			styles[SCE_C_COMMENT] = "Comment";
			styles[SCE_C_COMMENTDOC] = "Comment";
			styles[SCE_C_COMMENTLINEDOC] = "Comment";
			styles[SCE_C_COMMENTLINE] = "Comment";
			
			styles[SCE_C_NUMBER] = "Number";
			styles[SCE_C_STRING] = "String";
			styles[SCE_C_CHARACTER] = "Character";
			styles[SCE_C_PREPROCESSOR] = "Pre Processor";
			styles[SCE_C_OPERATOR] = "Operator";
			styles[SCE_C_WORD] = "Identifier";
			styles[SCE_C_REGEX] = "Regular Expression";
		}
		else if ( language == TD_LANG_PYTHON ) {
			styles[SCE_P_DEFAULT]= "Default" ;			
			styles[SCE_P_IDENTIFIER]= "Default" ;	
			styles[SCE_P_DEFNAME]= "Default" ;			
			
			styles[SCE_P_COMMENTBLOCK] = "Comment";			
			styles[SCE_P_COMMENTLINE] = "Comment";
			
			styles[SCE_P_NUMBER] = "Number";
			styles[SCE_P_STRING] = "String";
			styles[SCE_P_CHARACTER] = "Character";
			
			styles[SCE_P_OPERATOR] = "Operator";
			
			styles[SCE_P_WORD] = "Identifier";			
		}
		else if ( (language == TD_LANG_HTML) || (language == TD_LANG_XML) ) {
			styles[SCE_H_DEFAULT]= "Default" ;
			
			styles[SCE_H_ATTRIBUTE]= "Default" ;	
			styles[SCE_H_ATTRIBUTE]= "Default" ;

			styles[SCE_H_SGML_DEFAULT]= "Default" ;
			
			
			styles[SCE_H_COMMENT] = "Comment";
			styles[SCE_H_XCCOMMENT] = "Comment";
			styles[SCE_H_SGML_COMMENT] = "Comment";
			
			
			styles[SCE_H_NUMBER] = "Number";
			styles[SCE_H_DOUBLESTRING] = "String";
			styles[SCE_H_SINGLESTRING] = "String";
			styles[SCE_H_CDATA] = "String";
			

			styles[SCE_H_SGML_DOUBLESTRING] = "String";
			styles[SCE_H_SGML_SIMPLESTRING] = "String";

						
			styles[SCE_H_TAG] = "Identifier";
			styles[SCE_H_ENTITY] = "Identifier";
			styles[SCE_H_SGML_ENTITY] = "Identifier";
			styles[SCE_H_SGML_SPECIAL] = "Identifier";
			

			styles[SCE_H_XMLSTART] = "Identifier";
			styles[SCE_H_XMLSTART] = "Identifier";

			styles[SCE_H_SGML_COMMAND] = "Identifier";		
			
			
			//styles[SCE_C_REGEX] = "Regular Expression";
		}
		else if ( language == TD_LANG_PERL ) {
			styles[SCE_PL_DEFAULT]= "Default" ;			
			styles[SCE_PL_ERROR]= "Default" ;	
			styles[SCE_PL_POD]= "Default" ;	
			styles[SCE_PL_IDENTIFIER]= "Default" ;	
			styles[SCE_PL_SYMBOLTABLE]= "Default" ;	
			
			
			styles[SCE_PL_COMMENTLINE] = "Comment";			
			styles[SCE_P_COMMENTLINE] = "Comment";
			
			styles[SCE_PL_NUMBER] = "Number";
			styles[SCE_PL_STRING] = "String";
			styles[SCE_PL_CHARACTER] = "Character";
			
			styles[SCE_PL_PUNCTUATION] = "Operator";
			styles[SCE_PL_OPERATOR] = "Operator";

			styles[SCE_PL_SCALAR] = "Operator";
			styles[SCE_PL_ARRAY] = "Operator";
			styles[SCE_PL_HASH] = "Operator";
			styles[SCE_PL_HASH] = "Operator";
			
			styles[SCE_PL_WORD] = "Identifier";	

			
			styles[SCE_PL_PREPROCESSOR] = "Pre Processor";
			styles[SCE_PL_REGEX] = "Regular Expression";
			styles[SCE_PL_REGSUBST] = "Regular Expression";

			
		}
		else if ( language == TD_LANG_SQL ) {
			styles[SCE_C_DEFAULT]= "Default" ;
			
			styles[SCE_C_IDENTIFIER]= "Default" ;	
			
			styles[SCE_C_COMMENT] = "Comment";
			styles[SCE_C_COMMENTDOC] = "Comment";
			styles[SCE_C_COMMENTLINEDOC] = "Comment";
			styles[SCE_C_COMMENTLINE] = "Comment";
			
			styles[SCE_C_NUMBER] = "Number";
			styles[SCE_C_STRING] = "String";
			styles[SCE_C_CHARACTER] = "Character";
			styles[SCE_C_PREPROCESSOR] = "Pre Processor";
			styles[SCE_C_OPERATOR] = "Operator";
			styles[SCE_C_WORD] = "Identifier";
			styles[SCE_C_REGEX] = "Regular Expression";
		}
		else if ( language == TD_LANG_VB ) {
			styles[SCE_B_DEFAULT]= "Default" ;			
			styles[SCE_B_IDENTIFIER]= "Default" ;	
			
			
			styles[SCE_B_COMMENT] = "Comment";
			
			styles[SCE_B_NUMBER] = "Number";
			styles[SCE_B_STRING] = "String";
			styles[SCE_B_DATE] = "Number";
			
			styles[SCE_B_OPERATOR] = "Operator";		
			
			styles[SCE_B_KEYWORD] = "Identifier";
			
			styles[SCE_B_PREPROCESSOR] = "Pre Processor";
			
		}
		else if ( language == TD_LANG_LATEX ) {
			styles[SCE_L_DEFAULT]= "Default" ;			
			styles[SCE_B_IDENTIFIER]= "Default";
			
			styles[SCE_L_COMMENT] = "Comment";
			
			styles[SCE_L_MATH] = "Identifier";
			styles[SCE_L_TAG] = "Identifier";
			styles[SCE_L_COMMAND] = "Identifier";
		}
		else if ( language == TD_LANG_LUA ) {
			styles[SCE_LUA_DEFAULT]= "Default" ;
			
			styles[SCE_LUA_IDENTIFIER]= "Default" ;	
			
			styles[SCE_LUA_COMMENT] = "Comment";
			styles[SCE_LUA_COMMENTLINE] = "Comment";
			styles[SCE_LUA_COMMENTDOC] = "Comment";
			
			styles[SCE_LUA_NUMBER] = "Number";
			styles[SCE_LUA_STRING] = "String";
			styles[SCE_LUA_LITERALSTRING] = "String";
			
			styles[SCE_LUA_CHARACTER] = "Character";

			styles[SCE_LUA_PREPROCESSOR] = "Pre Processor";

			styles[SCE_LUA_OPERATOR] = "Operator";

			styles[SCE_LUA_WORD] = "Identifier";
		}
		else if ( language == TD_LANG_PASCAL ) {
			styles[SCE_C_DEFAULT]= "Default" ;
			
			styles[SCE_C_IDENTIFIER]= "Default" ;	
			
			styles[SCE_C_COMMENT] = "Comment";
			styles[SCE_C_COMMENTDOC] = "Comment";
			styles[SCE_C_COMMENTLINEDOC] = "Comment";
			styles[SCE_C_COMMENTLINE] = "Comment";
			
			styles[SCE_C_NUMBER] = "Number";
			styles[SCE_C_STRING] = "String";
			styles[SCE_C_CHARACTER] = "Character";
			styles[SCE_C_PREPROCESSOR] = "Pre Processor";
			styles[SCE_C_OPERATOR] = "Operator";
			styles[SCE_C_WORD] = "Identifier";
			styles[SCE_C_REGEX] = "Regular Expression";
		}
		else if ( language == TD_LANG_ADA ) {
			styles[SCE_ADA_DEFAULT]= "Default" ;
			styles[SCE_ADA_DELIMITER]= "Default" ;	
			styles[SCE_ADA_IDENTIFIER]= "Default" ;	
			
			
			styles[SCE_ADA_COMMENTLINE] = "Comment";
			
			
			styles[SCE_ADA_NUMBER] = "Number";
			styles[SCE_ADA_STRING] = "String";
			styles[SCE_LUA_LITERALSTRING] = "String";
			
			styles[SCE_ADA_CHARACTER] = "Character";
			
			styles[SCE_ADA_WORD] = "Identifier";
		}
		else if ( language == TD_LANG_LISP ) {
			styles[SCE_LISP_DEFAULT]= "Default" ;
			styles[SCE_LISP_IDENTIFIER]= "Default" ;	
			
			styles[SCE_LISP_COMMENT] = "Comment";
			
			styles[SCE_LISP_NUMBER] = "Number";
			styles[SCE_LISP_STRING] = "String";

			styles[SCE_LISP_OPERATOR] = "Operator";			
			
			styles[SCE_LISP_KEYWORD] = "Identifier";
			
		}
		else if ( language == TD_LANG_RUBY ) {
			
		}
		else if ( language == TD_LANG_EIFFEL ) {
			styles[SCE_EIFFEL_DEFAULT]= "Default" ;
			styles[SCE_EIFFEL_IDENTIFIER]= "Default" ;	
			
			styles[SCE_EIFFEL_COMMENTLINE] = "Comment";
			
			styles[SCE_EIFFEL_NUMBER] = "Number";
			styles[SCE_EIFFEL_STRING] = "String";

			styles[SCE_EIFFEL_CHARACTER] = "Character";
			

			styles[SCE_EIFFEL_OPERATOR] = "Operator";			
			
			styles[SCE_EIFFEL_WORD] = "Identifier";
		}
		else if ( language == TD_LANG_TCL ) {
			
		}
		else if ( language == TD_LANG_ASP ) {
			
		}
		else if ( language == TD_LANG_PHP ) {
			styles[SCE_H_DEFAULT]= "Default" ;
			
			styles[SCE_H_ATTRIBUTE]= "Default" ;	
			styles[SCE_H_ATTRIBUTE]= "Default" ;

			styles[SCE_H_SGML_DEFAULT]= "Default" ;
			styles[SCE_HPHP_DEFAULT]= "Default" ;
			
			styles[SCE_HPHP_VARIABLE]= "Default" ;
			
			
			
			styles[SCE_H_COMMENT] = "Comment";
			styles[SCE_H_XCCOMMENT] = "Comment";
			styles[SCE_H_SGML_COMMENT] = "Comment";
			styles[SCE_HPHP_COMMENT] = "Comment";
			styles[SCE_HPHP_COMMENTLINE] = "Comment";
			
			
			styles[SCE_H_NUMBER] = "Number";
			styles[SCE_HPHP_NUMBER] = "Number";
			
			styles[SCE_H_DOUBLESTRING] = "String";
			styles[SCE_H_SINGLESTRING] = "String";
			styles[SCE_HPHP_HSTRING] = "String";
			styles[SCE_HPHP_SIMPLESTRING] = "String";
			
			styles[SCE_HPHP_HSTRING_VARIABLE] = "String";
			


			styles[SCE_H_SGML_DOUBLESTRING] = "String";
			styles[SCE_H_SGML_SIMPLESTRING] = "String";		

			styles[SCE_HPHP_OPERATOR] = "Operator";		
			

			styles[SCE_H_TAG] = "Identifier";
			styles[SCE_H_ENTITY] = "Identifier";
			styles[SCE_H_SGML_ENTITY] = "Identifier";
			

			styles[SCE_H_XMLSTART] = "Identifier";
			styles[SCE_H_XMLSTART] = "Identifier";

			styles[SCE_H_SGML_COMMAND] = "Identifier";
			styles[SCE_HPHP_WORD] = "Identifier";

			
		}
		else if ( language == TD_LANG_FORTRAN ) {
			styles[SCE_F_DEFAULT]= "Default" ;
			styles[SCE_F_IDENTIFIER]= "Default" ;	
			
			styles[SCE_F_COMMENT] = "Comment";
			
			styles[SCE_F_NUMBER] = "Number";
			styles[SCE_F_STRING1] = "String";
			styles[SCE_F_STRING2] = "String";

			styles[SCE_EIFFEL_CHARACTER] = "Character";
			

			styles[SCE_F_OPERATOR] = "Operator";
			styles[SCE_F_OPERATOR2] = "Operator";
			
			
			styles[SCE_F_WORD] = "Identifier";
			styles[SCE_F_WORD2] = "Identifier";
			styles[SCE_F_WORD3] = "Identifier";

			styles[SCE_F_PREPROCESSOR] = "Pre Processor";


			
		}
		else if ( language == TD_LANG_CSS ) {
			styles[SCE_CSS_DEFAULT]= "Default" ;
			styles[SCE_CSS_CLASS]= "Default" ;	
			styles[SCE_CSS_PSEUDOCLASS]= "Default" ;
			styles[SCE_CSS_IDENTIFIER]= "Default" ;
			styles[SCE_CSS_UNKNOWN_IDENTIFIER]= "Default" ;
			
			styles[SCE_CSS_VALUE]= "Default" ;
			styles[SCE_CSS_ID]= "Default" ;
			
			
			
			
			
			styles[SCE_CSS_COMMENT] = "Comment";
			styles[SCE_CSS_UNKNOWN_PSEUDOCLASS]= "Comment" ;
			
			styles[SCE_F_NUMBER] = "Number";
			styles[SCE_F_STRING1] = "String";
			styles[SCE_F_STRING2] = "String";

			styles[SCE_EIFFEL_CHARACTER] = "Character";
			

			styles[SCE_CSS_OPERATOR] = "Operator";
			styles[SCE_F_OPERATOR2] = "Operator";
			
			
			styles[SCE_CSS_TAG] = "Identifier";
			styles[SCE_CSS_IMPORTANT] = "Identifier";
			styles[SCE_CSS_DIRECTIVE] = "Identifier";
		}
	}

	for ( std::map<int,String>::iterator it=styles.begin();it!=styles.end();it++ ) {
		
		Color backColor;
		backColor.setRed( preferences->readDouble( it->second + ".backcolor.red", 255.0 )/255.0 );
		backColor.setGreen( preferences->readDouble( it->second + ".backcolor.green", 255.0 )/255.0 );
		backColor.setBlue( preferences->readDouble( it->second + ".backcolor.blue", 255.0 )/255.0 );

		Color foreColor;
		foreColor.setRed( preferences->readDouble( it->second + ".forecolor.red", 0.0 )/255.0 );
		foreColor.setGreen( preferences->readDouble( it->second + ".forecolor.green", 0.0 )/255.0 );
		foreColor.setBlue( preferences->readDouble( it->second + ".forecolor.blue", 0.0 )/255.0 );

		bool bold = preferences->readBool( it->second + ".bold", false );
		bool italic = preferences->readBool( it->second + ".italic", false );

		long fontSize = preferences->readLong( it->second + ".fontsize", 11 );
		
		String fontName = preferences->readString( it->second + ".fontname", "Courier New" );

		setEditorStyle( it->first, foreColor.getColorRef32(), backColor.getColorRef32(), fontSize, 
						fontName, bold, italic );


		
		//this will attempt to use the right Scintilla styles 
		//for the editor based on the language of the TextDocument
	}


	Win32ScintillaPeer* scintillaPeer = (Win32ScintillaPeer*)peer_;

	bool autoIndent = preferences->readBool( "AutoIndent", true );
	scintillaPeer->setIndentMaintain( autoIndent );

	scintillaPeer->sendScintillaMessage( SCI_SETTABWIDTH, preferences->readLong( "TabSize", 4 ), 0 );
	scintillaPeer->sendScintillaMessage( SCI_SETINDENT, preferences->readLong( "IndentSize", 4 ), 0 );

	scintillaPeer->sendScintillaMessage( SCI_SETINDENTATIONGUIDES, 
														preferences->readBool( "ViewIndentationGuides", true ), 0 );


	bool viewWS = preferences->readBool( "ViewWhiteSpace", false );
	scintillaPeer->sendScintillaMessage( SCI_SETVIEWWS, viewWS ? SCWS_VISIBLEALWAYS : SCWS_INVISIBLE );

	scintillaPeer->sendScintillaMessage( SCI_SETVIEWEOL, preferences->readBool( "ViewEndOfLine", false ) );
}
*/

void SciTextControl::gotoLineNumber( VCF::ulong linNumber )
{
	// this will not move the caret to the first lines of the document if it is already 
	// visible in the page, unless we set:
	//((Win32ScintillaPeer*)peer_)->sendScintillaMessage( SCI_SETYCARETPOLICY, CARET_STRICT );
	((Win32ScintillaPeer*)peer_)->sendScintillaMessage( SCI_GOTOLINE, linNumber );
}

void SciTextControl::setEntryMode( TextEntryMode val )
{
	entryMode_ = val;

	Application* app = Application::getRunningInstance();
	if ( NULL != app ) {
		EventHandler* ev = new ClassProcedure1<Event*,Component>( app->getMainWindow(), &Component::handleEvent );
		UIToolkit::postEvent( ev, new Event(this, SciTextControl::teTextEntryModeChanged) );
	}
}

void SciTextControl::handleEvent( Event* e )
{
	Control::handleEvent( e );
	//if ( e->getType() == VCFBuilderApplication::PreferencesChangedEvent ) {		
		//Preferences* prefs = VCFBuilderApplication::getApp() ->createReadablePreferencesForText();
		//readPreferences( prefs );
		//delete prefs;
	//}
}


SciTextModel::SciTextModel():
	TextModel(),
		sciPeer_(NULL),
		braceCharacters_("[](){}")
{
	
}

String SciTextModel::getText( const uint32& index, const uint32& count )
{
	return sciPeer_->getText( index, count );
}

String SciTextModel::getText()
{
	return sciPeer_->getText( 0, -1 );
}

uint32 SciTextModel::getSize()
{
	return sciPeer_->getTextLength();
}

void SciTextModel::doSetText( const String& text )
{
	sciPeer_->insertText( -1, text );
}

void SciTextModel::doInsertText( const uint32& index, const String& text )
{
	sciPeer_->insertText( index, text );
}

void SciTextModel::doReplaceText( const uint32& index, const uint32& count, const String& text )
{
	sciPeer_->removeText( index, count );
	sciPeer_->insertText( index, text );
}

void SciTextModel::doRemoveText( const uint32& index, const uint32& count )
{
	sciPeer_->removeText( index, count );
}

bool SciTextModel::find( FindInfo& findInfo ) 
{
	return false;
}

bool SciTextModel::findAll( FindInfo& findInfo, std::vector<FoundEntry>& foundEntries )
{
	return false;
}

bool SciTextModel::replace( ReplaceInfo& replaceInfo )
{
	return false;
}

bool SciTextModel::replaceAll( ReplaceInfo& replaceInfo )
{
	return false;
}


void SciTextModel::setSelectionRange( const long pos, const VCF::ulong length  )
{
	sciPeer_->setSelectionMark( pos, length );
}

long SciTextModel::getSelectionStart()
{
	return sciPeer_->getSelectionStart();
}

uint32 SciTextModel::getSelectionLength()
{
	return sciPeer_->getSelectionCount();
}


String SciTextModel::getSelection()
{
	return sciPeer_->getText( sciPeer_->getSelectionStart(), sciPeer_->getSelectionCount() );
}

void SciTextModel::setSelection( const String& selectionText )
{
	uint32 selStart, selLen;
	selStart = sciPeer_->getSelectionStart();
	selLen = sciPeer_->getSelectionCount();

	sciPeer_->removeText( selStart, selLen );
	sciPeer_->insertText( selStart, selectionText );

	sciPeer_->setSelectionMark( selStart, selectionText.size() );
}

void ScintillaKit::init( int argc, char** argv )
{
	REGISTER_CLASSINFO_EXTERNAL(SciTextControl)
}

void ScintillaKit::terminate()
{

}


