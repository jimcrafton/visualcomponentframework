 

//#include <windows.h>
//#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/GraphicsKit/GraphicsKit.h"


typedef struct tagDEBUGHELPER
{
	DWORD dwVersion;
	BOOL (WINAPI *ReadDebuggeeMemory)( struct tagDEBUGHELPER *pThis, DWORD dwAddr, DWORD nWant, VOID* pWhere, DWORD *nGot );
	// from here only when dwVersion >= 0x20000
	DWORDLONG (WINAPI *GetRealAddress)( struct tagDEBUGHELPER *pThis );
	BOOL (WINAPI *ReadDebuggeeMemoryEx)( struct tagDEBUGHELPER *pThis, DWORDLONG qwAddr, DWORD nWant, VOID* pWhere, DWORD *nGot );
	int (WINAPI *GetProcessorType)( struct tagDEBUGHELPER *pThis );
} DEBUGHELPER;

inline DWORDLONG GetAddress( DEBUGHELPER *pHelper, DWORD address )
{
	return (( pHelper->dwVersion < 0x20000) ? address: pHelper->GetRealAddress(pHelper));
}

inline bool ReadMem( DEBUGHELPER *pHelper, DWORDLONG dwlAddress, size_t size, void *mem )
{
	DWORD nGot;
	if( pHelper->dwVersion < 0x20000)
	{
		if( pHelper->ReadDebuggeeMemory( pHelper, (DWORD)dwlAddress, size, mem, &nGot) != S_OK )
			return false;
	}
	else
	{
		//this is a part for VS NET
		if (pHelper->ReadDebuggeeMemoryEx(pHelper, dwlAddress, size, mem, &nGot)!=S_OK)
			return false;
	}

	return nGot == size;
}
template< typename T>
inline bool ReadMem(DEBUGHELPER *pHelper, DWORDLONG dwlAddress, T *mem)
{
	return ReadMem(pHelper, dwlAddress, sizeof(T), (void *)mem);
}


///////////////////////////////////////////////////////////////////////////////
// exports


extern "C" {
	__declspec(dllexport) HRESULT WINAPI VCF_DateTimeEvaluate( DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t maxlen, DWORD reserved );
}

extern "C" {
	__declspec(dllexport) HRESULT WINAPI VCF_DateTimeSpanEvaluate( DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t maxlen, DWORD reserved );
}

extern "C" {
	__declspec(dllexport) HRESULT WINAPI VCF_ColorEvaluate( DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t maxlen, DWORD reserved );
}


using namespace VCF;
static int VCF_ColorEvaluate_GraphicsKit_init = 0;


HRESULT WINAPI VCF_DateTimeEvaluate( DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t maxlen, DWORD reserved )
{
	DWORDLONG address = GetAddress( pHelper, dwAddress);

	DateTime dt;

	if( !ReadMem( pHelper, address, &dt ) ) {
		return E_FAIL;
	}

	char tmp[256];

	try {

		unsigned long year, month, day, hour, minute, second, millsecond;
		dt.get( &year, &month, &day, &hour, &minute, &second, &millsecond );

		wsprintf( tmp, "%04lu-%02lu-%02lu %02lu:%02lu:%02lu.%04lu", year, month, day, hour, minute, second, millsecond );

	} 
	catch ( ... ) {
		strcpy( tmp, "???*" );
	}

	strcpy( pResult, tmp );

	return S_OK;
}

HRESULT WINAPI VCF_DateTimeSpanEvaluate( DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t maxlen, DWORD reserved )
{
	DWORDLONG address = GetAddress( pHelper, dwAddress);

	DateTimeSpan dts;
	if( !ReadMem( pHelper, address, &dts) ) {
		return E_FAIL;
	}

	char tmp[256];

	try {

		unsigned long year       = dts.getYears();
		unsigned long month      = dts.getMonths();
		unsigned long day        = dts.getDays();
		unsigned long hour       = dts.getHours();
		unsigned long minute     = dts.getMinutes();
		unsigned long second     = dts.getSeconds();
		unsigned long millsecond = dts.getMilliseconds();

		wsprintf( tmp, "%04lu-%02lu-%02lu %02lu:%02lu:%02lu.%04lu", year, month, day, hour, minute, second, millsecond );

	} 
	catch ( ... ) {
		strcpy( tmp, "???*" );
	}

	strcpy( pResult, tmp );

	return S_OK;
}

HRESULT WINAPI VCF_ColorEvaluate( DWORD dwAddress, DEBUGHELPER *pHelper, int nBase, BOOL bUniStrings, char *pResult, size_t maxlen, DWORD reserved )
{
	DWORDLONG address = GetAddress( pHelper, dwAddress);

	/**
	If the object has no pointers or virtual table, or destructor destroying something
	( i.e. it is a plain structure ) it is fine to just copy the entire structure,
	otherwise... I don't know there is no documentation !

	This doesn't work:
		char* buffer = new char[ sizeof (Color) ];
		memset( buffer, 0, sizeof (Color) );
		Color& color = reinterpret_cast<Color&>( buffer );

	This is too much pain ... and there are problems accessing private variables
		Color color;
		unsigned long offset;
		offset = &color - &color.r_;
		if( !ReadMem( pHelper, address+offset, &color.r_ ) ) {
			return E_FAIL;
		}
	*/

	Color color;
	if( !ReadMem( pHelper, address, &color ) ) {
		return E_FAIL;
	}

	/**
	be careful if a double is undefined you would get:
	"%.2lf" --> "-92559631349317831000000000000000000000000000000000000000000000.00"
	and an overflow would cause:
	  Run-Time Check Failure #2 - Stack around the variable 'color' was corrupted.
	*/
	char tmp[1024];

	try {

		if ( 0 == VCF_ColorEvaluate_GraphicsKit_init ) {
			VCF_ColorEvaluate_GraphicsKit_init ++;
			GraphicsKit::init( 0, NULL );
		}

		String name = Color::getColorNameFromMap( color );

		int luminosity = color.getLuminosity();

		ColorSpace::RGBtype rgbType    = ColorSpace::ColorToRGB( color );
		ColorSpace::RGBrangetype rgbRg = ColorSpace::RGBToRGBRange ( rgbType );
		String rgbHex                  = Color::getHexCode( color, rgbType.R, rgbType.G, rgbType.B, true );
		unsigned long rgb              = color.getRGB();

		ColorSpace::HSLtype hslType    = ColorSpace::ColorToHSL( color );
		ColorSpace::HSLrangetype hslRg = ColorSpace::HSLToHSLRange ( hslType );
		String hslHex                  = Color::getHexCode( color, hslType.H, hslType.S, hslType.L, true );

		if ( rgbType.R + rgbType.G + rgbType.B + rgbType.R + rgbType.G + rgbType.B < -1.e6 ) {
			// not initialized yet
			sprintf( tmp, "%-10s [ lum: %3d ]\n { RGB: [%3d,%3d,%3d] [%.2e,%.2e,%.2e] %s }\n { HSL: [%3d,%3d,%3d] [%.2e,%.2e,%.2e] %s }"
									, name.ansi_c_str(), luminosity
									, rgbRg.R, rgbRg.G, rgbRg.B, rgbType.R, rgbType.G, rgbType.B, rgbHex.ansi_c_str()
									, hslRg.H, hslRg.S, hslRg.L, hslType.H, hslType.S, hslType.L, hslHex.ansi_c_str() 
							);
		} else {
			sprintf( tmp, "%-10s [ lum: %3d ]\n { RGB: [%3d,%3d,%3d] [%.2lf,%.2lf,%.2lf] %s }\n { HSL: [%3d,%3d,%3d] [%.2lf,%.2lf,%.2lf] %s }"
									, name.ansi_c_str(), luminosity
									, rgbRg.R, rgbRg.G, rgbRg.B, rgbType.R, rgbType.G, rgbType.B, rgbHex.ansi_c_str()
									, hslRg.H, hslRg.S, hslRg.L, hslType.H, hslType.S, hslType.L, hslHex.ansi_c_str() 
							);
		}
	} 
	catch ( ... ) {
		strcpy( tmp, "???*" );
	}

	strcpy( pResult, tmp );

	return S_OK;
}

