#include <string>
#include <stdio.h>

using namespace std;

int main( int argc, char** argv )
{
	if ( argc < 2 ) {
		printf( "Please pass in a file name !\n" );
		return 1;
	}

	FILE* f = fopen( argv[1], "rb" );
	if ( NULL != f ) {
		fseek( f, 0, SEEK_END );
		int size = ftell( f );
		fseek( f, 0, SEEK_SET );
		
		char* buf = new char[size+1];
		buf[size] = 0;
		fread( buf, 1, size, f );
		
		string s = buf;
		delete [] buf;
		fclose( f );


		int pos = s.find( "<body" );
		if ( pos != string::npos ) {
			pos = s.find( ">", pos + 1 );
			if ( pos != string::npos ) {
				s.erase( 0, pos+1 );
			}
		}

		pos = s.find( "</body" );
		if ( pos != string::npos ) {
			s.erase( pos, s.size()-pos );
		}
		
		f = fopen( argv[1], "w+" );
		fwrite( s.c_str(), 1, s.size(), f );
		fclose( f );
	}
	else {
		printf( "Couldn't open file: %s\n", argv[1] );
		return 1;
	}
	return 0;
}


