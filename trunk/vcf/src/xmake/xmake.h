#ifndef _XMLMAKE_H__
#define _XMLMAKE_H__
//xmake.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if     _MSC_VER > 1000
#  pragma once
#endif

//XMLMake.h

/**
Original makedep.c dependency code: Sulyok P‚ter (C) 1994.
Altered by Jim Crafton, Feb,8,2002
*/



#ifdef WIN32



#ifdef _LIB_CPLVERNUM
#		undef _LIB_CPLVERNUM
#endif


# if defined(__INTEL_COMPILER)
#   define _LIB_CPLVERNUM "icl7"
# elif defined(__ICL)
#   define _LIB_CPLVERNUM "icl6"
# else
#   if (_MSC_VER >= 1310)
#     define _LIB_CPLVERNUM "vc71"
#   elif (_MSC_VER >= 1300)
#     define _LIB_CPLVERNUM "vc70"
#   elif (_MSC_VER >= 1200)
#		ifdef VCF_GTK
#			define _LIB_CPLVERNUM "gtk"
#		else
#			define _LIB_CPLVERNUM "vc6"
#		endif
#   elif (_MSC_VER >= 1100)
#     define _LIB_CPLVERNUM "vc5"
#		endif
#   ifdef __BORLANDC__
#   define _LIB_CPLVERNUM "bcc"
#   endif
# endif


#ifdef USE_LIBXMAKE_DLL
//	using dynamic link library
#	ifdef _DEBUG
#		pragma comment(lib, "libXmake_"_LIB_CPLVERNUM"_d.lib")
#	else
#		pragma comment(lib, "libXmake_"_LIB_CPLVERNUM".lib")
#	endif
#elif defined USE_LIBXMAKE_LIB
//	using statically linked library
#	ifdef _DEBUG
#		pragma comment(lib, "libXmake_"_LIB_CPLVERNUM"_sd.lib")
#	else
#		pragma comment(lib, "libXmake_"_LIB_CPLVERNUM"_s.lib")
#	endif
#else
//	creating the static or dynamic link library
#endif // LIBXMAKE_LIB


#endif //WIN32



// tells the compiler to shut up
#include "xmake_warnings_off.h"



#include <string>
#include <vector>
#include <map>
#include <algorithm>


// moved here so it compiles with vc7#
#ifdef WIN32
	#include <windows.h>
    #include <io.h>
    #include <stdio.h>
	#include <process.h>
#endif 


#ifndef _ENUMERATOR_H__
	#include "Enumerator.h"
#endif




namespace xmake {

typedef std::string String;

class RuntimeException {
public:
	RuntimeException( const String & s ): err_(s) {
		
	}

	String err_;
};

};

#ifndef _DEPENDENCYNODES_H__
	#include "DependencyNodes.h"
#endif

namespace xmake {

typedef std::vector<String> StringList;
typedef std::vector<String>::iterator StringListIterator;

class XMLParser;
class XMLNode;

/**
*XMLMake is a just a class witha bunch of functions to keep thigns grouped together
*/
#if defined (__BORLANDC__)
#undef MAXPATH
#endif

class XMLMake {
public:

	XMLMake();
	~XMLMake();

	enum {
		LINE_SIZE		=	256,	// Line size
		NUM_FILE_EXT		= 	6,	// Number of source file extensions
		MAX_INCLUDE_DEPTH	=	150 ,	// Maximum number of path.
		MAXPATH			=	256 // Maximal size of path.
	};

	enum NewConfig{
		ncVC6Debug = 0,
		ncVC6Release,
		ncGCCDebug,
		ncGCCRelease
	};

	enum Action{
		actNone=0,
		actBuildTarget,
		actPrintUsage,
		actListTargets,
		actListConfigs,
		actListProjects,
		actGenerateMakefile,
		actCreateNew,
		actInstall,
		actClean,
		actShowVersion
	};

	

	void initMakefile( const String& filename );

	void initMakefileFromData( const String& data );
	
	bool initFromCommandLine( int argc, char** argv );
	
	void executeMakefile();

	StringList getTargets();

	StringList getProjects();

	StringList getConfigs();

	int getReturnCode() const {
		return returnCode_;
	}		

	String getMakeFile() const {
		return makefile_;
	}


	static String getVersion();

	static String usage();

	String getCurrentDirectory();	

	void setCurrentDirectory( const String& dir );

	struct Dependency {
		Dependency() :uptodate(false),buildable(true){}

		Dependency( const Dependency& rhs ) {
			*this = rhs;
		}

		virtual ~Dependency(){}

		Dependency& operator=( const Dependency& rhs ) {
			name = rhs.name;
			output = rhs.output;
			dependsNode = rhs.dependsNode;
			commands = rhs.commands;
			tool = rhs.tool;
			config = rhs.config;
			uptodate = rhs.uptodate;
			buildable = rhs.buildable;

			return *this;
		}

		std::string name;
		std::string output;
		DependencyNode* dependsNode;
		std::vector<std::string> commands;
		std::string tool;
		std::string config;
		bool uptodate;
		bool buildable;
		
		bool partOfConfig( const String& aConfig ) {
			String tmp = config;
			std::vector<std::string> configs;
			
			int pos = tmp.find( ";" );
			while ( pos != String::npos ) {
				configs.push_back( tmp.substr( 0, pos ) );
				tmp.erase( 0, pos+1);
				pos = tmp.find( ";" );
			}
			if ( !tmp.empty() ) {
				configs.push_back( tmp );
			}
			
			return std::find( configs.begin(), configs.end(), aConfig ) != configs.end();
		}
	};
	

	struct Target : public Dependency{	
		std::string project;
		std::vector<Dependency> dependencies;
		Target(){}

		Target( const Target& rhs ) {
			*this = rhs;
		}

		Target& operator=( const Target& rhs ) {
			Dependency::operator=( rhs );

			project = rhs.project;
			dependencies = rhs.dependencies;			

			return *this;
		}
	};

	struct Project : public Dependency{
		std::vector<Target> targets;
		std::vector<Dependency> dependantProjects;
	};
	
	struct Tool { 
		std::string name;
		std::string id;
		std::string type;
		std::string flags;
		std::vector<std::string> commands;
		
		bool hasType( const String& aType ) {
			String tmp = type;
			std::vector<std::string> types;
			
			int pos = tmp.find( ";" );
			while ( pos != String::npos ) {
				types.push_back( tmp.substr( 0, pos ) );
				tmp.erase( 0, pos+1);
				pos = tmp.find( ";" );
			}
			if ( !tmp.empty() ) {
				types.push_back( tmp );
			}
			
			return std::find( types.begin(), types.end(), aType ) != types.end();
		}
	};

	struct Config {
		std::string name;
		std::vector<Tool> tools;
		std::vector<String> includes;
	};
protected:

	friend class XMakeUtils;


	//this is the list of include directories
	StringList includeDirectories_;
	String configToBuild_;	
	String makefile_;
	Enumerator<XMLNode*>* parsedNodes_;	
	String projectToBuild_;	
	String generateFileType_;
	String generateOutputFileName_;	
	bool printDebug_;	
	bool verbose_;	
	NewConfig configType_;
	Action action_;	
	
	String fileListing_;

	typedef std::map<std::string,Target> TargetMap;
	typedef std::map<std::string,Project> ProjectMap;
	typedef std::map<std::string,Config> ConfigMap;

	typedef std::map<String,StringList> IncludeMap;

	ProjectMap projects_;
	TargetMap targets_;
	ConfigMap configs_;
	Config defaultConfig_;

	IncludeMap includesMap_;
	
	DependencyNode::Vector sortedDependencies_;
	
	std::string masterContents_;
	std::string firstTarget_;
	std::string defaultConfigName_;
	
	typedef std::map<std::string,std::string> VariableMap;
	VariableMap variableList_;
	
	std::map<String,String> automaticVariablesMap_;
	
	DependencyNode::Vector dependencyList_;
	DependencyGraph dependsGraph_;

	int returnCode_;	

	void debugWithArgs( String text,... );

	void debug( const String& text );	

	bool moveFile( const String& src, const String& dest );

	bool fileExists( const String& filename );

	bool implicitDependenciesChanged( const String& filename, const String& outputFilename );

	void checkUptodateStatus( DependencyNode::Vector& sortedDependencies );

	void parseMakeFile();

	void applyCurrentConfiguration( DependencyNode::Vector& sortedDependencies );

	void replaceAutomaticVariables( DependencyNode::Vector& sortedDependencies );

	void replaceAutomaticVariablesFor( String& s, Target& target, Dependency* dependency );

	void buildSortedDependencyList( DependencyNode::Vector& sortedDependencies );

	void buildDependencies( Target& target );

	void buildDependencies( Project& target );

	void replaceWithVariables( String& s );

	void getVariablePos( const String s, String& varName, int& pos, int& length );

	void readMakeFile( const String& fileName, int pos=0 );

	String openFile( const String& filename );

	Tool findToolByID( const String& id, Config& config );

	Tool findToolForType( const String& type, Config& config );

	void makeDependFiles( String name, StringList& dependsList, long& dependencyCount );
	
	void searchIncludeFile( const String& name, long& dependencyCount, StringList& dependsList );
	
	const char* nextWhiteSpace( const char *s );
	
	const char* nextNonWhiteSpace( const char *s );	

	int exec( const String& commandLine, const String& currentDirectory );

	bool deleteFile( const String& filename );	

	bool fileNewerThan( const String& f1, const String& f2 );	
	
	void error( const String& errMessage );		

	String getEnvironmentVariableValue( const String& variableName );

	
	
	int findLastStringIn( const String& src, const String& searchFor );	

	bool verifyFileName( const String& filename, const bool& autoBuildDir );

	void applyConfig( Dependency& dependency );
	
	void buildTarget();

	void printUsage();

	void listTargets();

	void listConfigs();

	void listProjects();

	void generateMakefile();

	void createNew();

	void install();

	void clean();

	void showVersion();

	bool targetUptodate( const String name );
};

};//namespace xmake;


/**
*CVS Log info
*$Log$
*Revision 1.5  2005/07/09 23:15:18  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.1  2004/12/21 01:25:17  marcelloptr
*added cvs log section
*
*/


#endif  //_XMLMAKE_H__



