// RegEnVar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define SYSENV_KEY		"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment"
#define USERENV_KEY		"Environment"

#define PATH_VAR		"Path"


using namespace std;

bool regUserEnvVar( const string& name, const string& val )
{
	bool result = false;

	if ( !name.empty() && !val.empty() ) {
		HKEY key = NULL;
		
		if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_CURRENT_USER, USERENV_KEY, 0, KEY_ALL_ACCESS, &key ) ) {
			DWORD type = REG_SZ;
			if ( val.find( "%" ) != string::npos ) {
				type = REG_EXPAND_SZ;
			}
			
			if ( ERROR_SUCCESS == RegSetValueEx( key, name.c_str(), 0, type, (CONST BYTE *)val.c_str(), val.size() ) ) {
				result = true;
			}

			RegCloseKey( key );
		}
	}
	return result;
}

bool removeUserEnvVar( const string& name )
{
	bool result = false;

	if ( !name.empty() ) {
		HKEY key = NULL;
		
		if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_CURRENT_USER, USERENV_KEY, 0, KEY_ALL_ACCESS, &key ) ) {
			if ( ERROR_SUCCESS == RegDeleteValue( key, name.c_str() ) ) {
				result = true;
			}			

			RegCloseKey( key );
		}
	}
	return result;
}


bool addToUserPath( const string& val ) 
{
	bool result = false;

	HKEY key = NULL;
	if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_CURRENT_USER, USERENV_KEY, 0, KEY_ALL_ACCESS, &key ) ) {
		DWORD type = REG_EXPAND_SZ;
		char pathVal[1024];
		DWORD pathSz = 1024;

		if ( ERROR_SUCCESS == RegQueryValueEx( key, PATH_VAR, 0, &type, (LPBYTE)&pathVal[0], &pathSz ) ) {
			pathVal[pathSz] = 0;

			string name = PATH_VAR;
			string newVal = val + ";" ;
			newVal += pathVal;

			result = regUserEnvVar( name, newVal );
		}
		RegCloseKey( key );
	}

	return result;
}

bool removeFromUserPath( const string& val ) 
{
	bool result = false;

	HKEY key = NULL;
	if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_CURRENT_USER, USERENV_KEY, 0, KEY_ALL_ACCESS, &key ) ) {
		DWORD type = REG_EXPAND_SZ;
		char pathVal[1024];
		DWORD pathSz = 1024;

		if ( ERROR_SUCCESS == RegQueryValueEx( key, PATH_VAR, 0, &type, (LPBYTE)&pathVal[0], &pathSz ) ) {
			pathVal[pathSz] = 0;

			string name = PATH_VAR;
			string newVal = pathVal;
			
			string searchFor = val + ";";
		
			int pos = newVal.find( searchFor );
			while ( pos != string::npos ) {
				newVal.erase( pos, pos + searchFor.size() );

				pos = newVal.find( searchFor );
			}

			result = regUserEnvVar( name, newVal );
		}
		RegCloseKey( key );
	}

	return result;
}


bool regSystemEnvVar( const string& name, const string& val )
{
	bool result = false;

	if ( !name.empty() && !val.empty() ) {
		HKEY key = NULL;
		
		if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE, SYSENV_KEY, 0, KEY_ALL_ACCESS, &key ) ) {
			DWORD type = REG_SZ;
			if ( val.find( "%" ) != string::npos ) {
				type = REG_EXPAND_SZ;
			}
			
			if ( ERROR_SUCCESS == RegSetValueEx( key, name.c_str(), 0, type, (CONST BYTE *)val.c_str(), val.size() ) ) {
				result = true;
			}

			RegCloseKey( key );
		}
	}
	return result;
}

bool removeSystemEnvVar( const string& name )
{
	bool result = false;

	if ( !name.empty() ) {
		HKEY key = NULL;
		
		if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE, SYSENV_KEY, 0, KEY_ALL_ACCESS, &key ) ) {
			if ( ERROR_SUCCESS == RegDeleteValue( key, name.c_str() ) ) {
				result = true;
			}			

			RegCloseKey( key );
		}
	}
	return result;
}


bool addToSystemPath( const string& val ) 
{
	bool result = false;

	HKEY key = NULL;
	if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE, SYSENV_KEY, 0, KEY_ALL_ACCESS, &key ) ) {
		DWORD type = REG_EXPAND_SZ;
		char pathVal[1024];
		DWORD pathSz = 1024;

		if ( ERROR_SUCCESS == RegQueryValueEx( key, PATH_VAR, 0, &type, (LPBYTE)&pathVal[0], &pathSz ) ) {
			pathVal[pathSz] = 0;

			string name = PATH_VAR;
			string newVal = val + ";";
			newVal += pathVal;

			result = regSystemEnvVar( name, newVal );
		}
		RegCloseKey( key );
	}

	return result;
}

bool removeFromSystemPath( const string& val ) 
{
	bool result = false;

	HKEY key = NULL;
	if ( ERROR_SUCCESS == RegOpenKeyEx( HKEY_LOCAL_MACHINE, SYSENV_KEY, 0, KEY_ALL_ACCESS, &key ) ) {
		DWORD type = REG_EXPAND_SZ;
		char pathVal[1024];
		DWORD pathSz = 1024;

		if ( ERROR_SUCCESS == RegQueryValueEx( key, PATH_VAR, 0, &type, (LPBYTE)&pathVal[0], &pathSz ) ) {
			pathVal[pathSz] = 0;

			string name = PATH_VAR;
			string newVal = pathVal;
			
			string searchFor = val + ";";
		
			int pos = newVal.find( searchFor );
			while ( pos != string::npos ) {
				newVal.erase( pos, pos + searchFor.size() );

				pos = newVal.find( searchFor );
			}

			result = regSystemEnvVar( name, newVal );
		}
		RegCloseKey( key );
	}

	return result;
}

bool updateEnv()
{
	DWORD res = 0;
	DWORD res2 = SendMessageTimeout( HWND_BROADCAST,
										WM_SETTINGCHANGE, 
										0, 
										(LPARAM)"Environment", 
										SMTO_ABORTIFHUNG, 
										5000, &res );

	return ( res2 ) ? true : false;
}


#define USAGE \
	"Usage:\n"\
	"\t--add-sys-var <name> <val>\n"\
	"\t--del-sys-var <name>\n"\
	"\t--add-user-var <name> <val>\n"\
	"\t--del-sys-var <name>\n"\
	"\t--add-to-sys-path <val>\n"\
	"\t--del-from-sys-path <val>\n"\
	"\t--add-to-user-path <val>\n"\
	"\t--del-from-user-path <val>\n"\


int main(int argc, char* argv[])
{
	CommandLine cmdLine;

	if (cmdLine.SplitLine(argc, argv) < 1)	{
		// no switches were given on the command line, abort
		printf( USAGE );
		exit(-1);
	}

	if ( cmdLine.HasSwitch( "--add-sys-var" ) ) {

		string name = cmdLine.GetArgument("--add-sys-var", 0);
        string val = cmdLine.GetArgument("--add-sys-var", 1);

		regSystemEnvVar( name, val );
	}

	if ( cmdLine.HasSwitch( "--del-sys-var" ) ) {

		string name = cmdLine.GetArgument("--del-sys-var", 0 );

		removeSystemEnvVar( name );
	}

	

	if ( cmdLine.HasSwitch( "--add-user-var" ) ) {

		string name = cmdLine.GetArgument("--add-user-var", 0);
        string val = cmdLine.GetArgument("--add-user-var", 1);

		regUserEnvVar( name, val );
	}

	if ( cmdLine.HasSwitch( "--del-user-var" ) ) {

		string name = cmdLine.GetArgument("--del-user-var", 0 );

		removeUserEnvVar( name );
	}

	



	if ( cmdLine.HasSwitch( "--add-to-sys-path" ) ) {

		string val = cmdLine.GetArgument("--add-to-sys-path", 0 );

		addToSystemPath( val );
	}

	if ( cmdLine.HasSwitch( "--del-from-sys-path" ) ) {

		string val = cmdLine.GetArgument("--del-from-sys-path", 0 );

		removeFromSystemPath( val );
	}

	if ( cmdLine.HasSwitch( "--add-to-user-path" ) ) {

		string val = cmdLine.GetArgument("--add-to-user-path", 0 );

		addToUserPath( val );
	}

	if ( cmdLine.HasSwitch( "--del-from-user-path" ) ) {

		string val = cmdLine.GetArgument("--del-from-user-path", 0 );

		removeFromUserPath( val );
	}

	if ( !updateEnv() ) {
		printf( "Environment update failed, GetLastError(): %d\n", GetLastError() );
		exit ( -1 );
	}


	return 0;
}

