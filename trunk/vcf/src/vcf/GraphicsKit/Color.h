#ifndef _VCF_COLOR_H__
#define _VCF_COLOR_H__
//Color.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


/**
* Uncomment this to activate the macro VCF_DEBUG_COLORS_COMPARISON_OPERATORS
* It is used to check if the comparison operators work right.
* This involves a certain performance penalty in debug mode. So by default it is commented !
*/
//#define VCF_DEBUG_COLORS_COMPARISON_OPERATORS


#if !defined ( _DEBUG ) && !defined( DEBUG )
#	ifdef VCF_DEBUG_COLORS_COMPARISON_OPERATORS
#	  undef VCF_DEBUG_COLORS_COMPARISON_OPERATORS
#	endif
#endif


/**
* Uses a large map collecting all the standard internet color names,
* which are 548. The standard short list has 138 names.
* Uncomment the following if you desire to use the large list.
*/
//#define VCF_LARGE_COLOR_LIST


namespace VCF {

/**
*standard system color defines
*/
#define		SYSCOLOR_SHADOW					0
#define		SYSCOLOR_FACE					1
#define		SYSCOLOR_HIGHLIGHT				2
#define		SYSCOLOR_ACTIVE_CAPTION			3
#define		SYSCOLOR_ACTIVE_BORDER			4
#define		SYSCOLOR_DESKTOP				5
#define		SYSCOLOR_CAPTION_TEXT			6
#define		SYSCOLOR_SELECTION				7
#define		SYSCOLOR_SELECTION_TEXT			8
#define		SYSCOLOR_INACTIVE_BORDER		9
#define		SYSCOLOR_INACTIVE_CAPTION		10
#define		SYSCOLOR_TOOLTIP				11
#define		SYSCOLOR_TOOLTIP_TEXT			12
#define		SYSCOLOR_MENU					13
#define		SYSCOLOR_MENU_TEXT				14
#define		SYSCOLOR_WINDOW					15
#define		SYSCOLOR_WINDOW_TEXT			16
#define		SYSCOLOR_WINDOW_FRAME			17




class Color;

/**
\class ColorSpace Color.h "vcf/GraphicsKit/Color.h"
A class for managing all the color transformations between different color spaces


ColorSpace interface

 Hue Luminosity management

	WebPages:
	\li http://www.acm.org/jgt/papers/SmithLyons96/
	\li	http://www.scottandmichelle.net/scott/code/index2.mv?codenum=045
	\note
		(google search advanced all words: hue saturation source code)


Author: Alvy Ray Smith <br>
				Microsoft <br>
				Redmond, Washington <br>
				alvys@microsoft.com <br>
				Eric Ray Lyons <br>
				Mill Valley, California <br>
				lyons@nbn.com <br>

Abstract:
	The two most common color selector models, other than RGB (Red-Green-Blue),
	are the hue-based HSV (Hue-Saturation-Value) and HSL (Hue-Saturation-Lightness) color models.
	It is shown that both of these models are flawed.
	A closely related model, HWB (Hue-Whiteness-Blackness), is introduced that avoids the flaws,
	is slightly faster to compute, and is very easy to teach to new users:
	Choose a hue. Lighten it with white. Darken it with black.
	We explain that lightening is not the opposite of darkening.


Modified, with some fixes to the algorithms, by Marcello Pietrobon

Modified, by Jim Crafton, fixed some errors due to inclusion of Win32 types
*/
class GRAPHICSKIT_API ColorSpace {
public:
	/**
	 Theoretically, hue 0 (pure red) is identical to hue 6 in these transforms. Pure
	 red always maps to 6 in this implementation. Therefore UNDEFINED can be
	 defined as 0 in situations where only unsigned numbers are desired.
	 */
	#define HUE_UNDEFINED	-1

	#define HUECRITICALMAX	( 1.0 - 1.0 / 6.0 )	// max r/g/b value is 255 ?

	/**
	HueCriticalMax is assigned ( 1.0 - 1.0 / 6.0 )
	Hue > HueCriticalMax => rgb.R > 1;
	*/
	static const double HueCriticalMax;	// = ( 1.0 - 1.0 / 6.0 )

	enum {
		RGBMax   = 0xFF,      // 255  When the max r/g/b value is 255
		HSLMax   = 0xF0,      // 240  This is what Windows' Display Properties uses: it is not too much important an exact value: see how GetLuminosity() is used for.
		RGBMax16 = 0xFFFF,    // Used when the max r/g/b value is 0xFFFF ( used for more precision )
		HSLMax16 = 0xF0F0,    // ( 0xFFFF * 240 / 255 )
	};

	enum {
		hue_undefined = HUE_UNDEFINED,
	};

	/*
	enum colormodelType {
		colormodel_RGB = 1,
		colormodel_HSV = 2,
		colormodel_HSL = 3,
		colormodel_HWB = 4
	};
	*/


	struct RGBtype {
		double R;
		double G;
		double B;
	};

	struct RGBrangetype	{
		int R;
		int G;
		int B;
	};

	struct HWBtype {
		double H;
		double W;
		double B;
	};

	struct HSVtype {
		double H;
		double S;
		double V;
	};

	struct HSLtype {
		double H;
		double S;
		double L;
	};

	struct HSLrangetype{
		int H;
		int S;
		int L;
	};


	#define MAKE_RGB(rgb, r, g, b) {rgb.R = (r); rgb.G = (g); rgb.B = (b);}
	#define MAKE_HSV(hsv, h, s, v) {hsv.H = (h); hsv.S = (s); hsv.V = (v);}
	#define MAKE_HSL(hsl, h, s, l) {hsl.H = (h); hsl.S = (s); hsl.L = (l);}
	#define MAKE_HWB(hwb, h, w, b) {hwb.H = (h); hwb.W = (w); hwb.B = (b);}

	#define SPLIT_RGB(rgb, r, g, b) r = rgb.R; g = rgb.G; b = rgb.B;
	#define SPLIT_HSV(hsv, h, s, v) h = hsv.H; s = hsv.S; v = hsv.V;
	#define SPLIT_HSL(hsl, h, s, l) h = hsl.H; s = hsl.S; l = hsl.L;
	#define SPLIT_HWB(hwb, h, w, b) h = hwb.H; w = hwb.W; b = hwb.B;



	/**
	compute the luminosity for an RGB color.
	@param color
	@return int
	*/
	static int getLuminosity( const Color& color );

	/**
	set the luminosity of a color.
	@param Color& color, the color.
	@param const int& luminosity, the desired luminosity
	expressed in a [0, ColorSpace::HSLMax] scale.
	*/
	static void setLuminosity( Color& color, const int& luminosity );

	/**
	helper function
	*/
	static double HueToColorValue(const double Hue, const double M1, const double M2);

	// the HSV-RGB Transform Pair
	static HSVtype RGBToHSV( const RGBtype& RGB );
	static RGBtype HSVToRGB( const HSVtype& HSV );

	// the HSL-RGB Transform Pair
	static RGBtype HSLToRGB (const HSLtype& hsl);
	static HSLtype RGBToHSL(const RGBtype& rgb);

	// the HWB-RGB Transform Pair
	static HWBtype RGBToHWB( const RGBtype& rgb ) ;
	static RGBtype HWBToRGB( const HWBtype& HWB ) ;



	// conversions
	static HSLtype HSLRangeToHSL (const HSLrangetype& hslRange);
	static HSLrangetype HSLToHSLRange (const HSLtype& hsl);

	static ulong32 RGBToColorLong (const RGBtype& rgb);
	static RGBtype ColorLongToRGB (const ulong32 color);

	static ulong32 HSLToColorLong (const HSLtype& hsl);
	static HSLtype ColorLongToHSL (const ulong32 color);

	static RGBrangetype RGBToRGBRange(const RGBtype& rgb);
	static RGBtype RGBRangeToRGB(const RGBrangetype& rgbRange);

	static RGBtype HSLRangeToRGB (const HSLrangetype& hslRange);
	static HSLrangetype RGBToHSLRange (const RGBtype& rgb);

	static ulong32 HSLRangeToColorLong (const HSLrangetype& hsl);
	static HSLrangetype ColorLongToHSLRange (const ulong32 color);


	// the HSV-Color conversion pair
	static Color RGBToColor (const RGBtype& rgb);
	static RGBtype ColorToRGB (const Color& color);
	static ulong32 ColorToColorLong (const Color& color);

	// the HSV-Color conversion pair
	static Color HSVToColor (const HSVtype& hsl);
	static HSVtype ColorToHSV(const Color& rgb);

	// the HSV-Color conversion Pair
	static Color HSLToColor (const HSLtype& hsl);
	static HSLtype ColorToHSL(const Color& rgb);

	// the HSV-Color conversion Pair
	static Color HWBToColor (const HWBtype& hsl);
	static HWBtype ColorToHWB(const Color& rgb);

	// usage

	static double getChanged( const double& initialVal, const double& percent );

	/**
	It is suggested to call this function with colors: 0.0/ 0.0 / 0.71428571428571

	It is suggested to call this function with grays:  0.0/ 0.0 / 0.33333333333333
	*/
	static void changeHSV ( HSVtype& hsv, const double& percentH, const double& percentS, const double& percentV );

	/**
	It is suggested to call this function with colors: 0.0/ 0.0 / -0.71428571428571

	It is suggested to call this function with grays:  0.0/ 0.0 / -0.33333333333333
	*/
	static void changeHSL ( HSLtype& hsl, const double& percentH, const double& percentS, const double& percentL );

	/**
	It is suggested to call this function with colors: 0.0/ 0.0 / 0.71428571428571

	It is suggested to call this function with grays:  0.0/ 0.0 / 0.33333333333333
	*/
	static void changeHWB ( HWBtype& hsl, const double& percentH, const double& percentW, const double& percentB );

	static HSVtype changeHSV ( const HSVtype& hsv, const double& percentH, const double& percentS, const double& percentV );
	static HSLtype changeHSL ( const HSLtype& hsl, const double& percentH, const double& percentS, const double& percentL );
	static HWBtype changeHWB ( const HWBtype& hwb, const double& percentH, const double& percentW, const double& percentB );

	/**
	Example: To draw the Titlebars of a window with a color gradient do the following:
	\code
		Color color_right = color;

		// enabled window (color)
		Color color_left = changeHSL( color_right, 0.0, 0.0, -0.71428571428571 );

		// disable window (gray)
		Color color_left = changeHSL( color_right, 0.0, 0.0, -0.33333333333333 );
		drawGradientBackground(pc, color_left, color_right);
	\endcode
	*/
	static Color changeHSV ( const Color& color, const double& percentH, const double& percentS, const double& percentV );
	static Color changeHSL ( const Color& color, const double& percentH, const double& percentS, const double& percentL );
	static Color changeHWB ( const Color& color, const double& percentH, const double& percentW, const double& percentB );

	static void		changeHue ( HSLtype& hsl, const double& deltaH );			// this one does the real work
	static HSLtype	changeHue ( const HSLtype& hsl, const double& deltaH );
	static Color	changeHue ( const Color& color, const double& deltaH );
	static RGBtype	changeHue ( const RGBtype& color, const double& deltaH );
	static ulong32	changeHue ( const ulong32& color, const double& deltaH );
};






#define COLOR_CLASSID	"AA34A97B-8294-4697-857D-398FB355EB2D"

/**
\class Color Color.h "vcf/GraphicsKit/Color.h"
The Color class is used to represent a given color with 4 values, with
each value representing a separate red, green, blue, and alpha color
component (RGBA). Each value is stored as a double with a valid range
of 0.0 to 1.0. A variety of functions a provided to convert the color
to and from other color representations, such as CMY(K), HSL,
and HSV.
*/
class GRAPHICSKIT_API Color : public VCF::Object {
public:
	friend class ColorSpace;

	/**
	this enum defines the way color is stored when compressed into a
	32/64 bit integer value. Sadly not everyone stores this the same way
	so this will indicate how the bits are arranged
	*/
	enum ColorPackScheme {
		/**
		Alpha value, Red value, Green Value, and Blue value.
		Seen in a 32 bit number as 0xAARRGGBB
		*/
		cpsARGB = 0,

		/**
		Red value, Green Value, and Blue value.
		Seen in a 32 bit number as 0x00RRGGBB
		*/
		cpsRGB,

		/**
		Alpha value, Blue value, Green Value, and Red value.
		This is the default in Win32 systems (i.e. inverted).
		Seen in a 32 bit number as 0xAABBGGRR
		*/
		cpsABGR,

		/**
		Blue value, Green Value, and Red value.
		This is the default in Win32 systems (i.e. inverted).
		Seen in a 32 bit number as 0x00BBGGRR
		*/
		cpsBGR,
	};

	/**
	An enum that indicates the color type of three double values.
	*/
	enum ColorType {
		/**
		Assuming three color values, a, b, and c, which represent
		red, green, and blue values respectively, with each value
		bounded by 0.0 to 1.0 inclusive.
		*/
		ctRGB = 0,

		/**
		Assuming three color values, a, b, and c, which represent
		Hue, Luminance, and Saturation values respectively, with each value
		bounded by 0.0 to 1.0 inclusive.
		*/
		ctHSL,

		/**
		Assuming three color values, a, b, and c, which represent
		Hue, Saturation, and Value values respectively, with each value
		bounded by 0.0 to 1.0 inclusive.
		*/
		ctHSV,

		ctHWB,

		ctYUV,
		ctLab,
		ctCMY
	};

	/**
	the factor used when ranging the color components with integers.
	*/
	enum MaxFactor {
		xFF = 0xFF,
		xFFFF = 0xFFFF,
	};


	/**
	default ctor
	*/
	Color();

	/**
	the copy ctor
	*/
	Color( const Color& color );

	/**
	Initializes a color based on the double values (type: double) of its three components
	in a specified color coordinates sytem. The values, in double (4 bytes), are directly translated
	into the internal color components (in double).
	Usage: Color color = Color( 1.0, 1.0, 0.5 );  Color color2 = Color( color.getRed(), color.getGreen(), color.getBlue() );
	@param ColorType indicates the coordinates used in the color space. By default
	the RGB (red, green, and blue) system is used.
	@see ColorType
	*/
	Color( const double& val1, const double& val2, const double& val3, ColorType type=ctRGB );

	Color( const double& val1, const double& val2, const double& val3, const double& a, ColorType type=ctRGB );

	/**
	Initializes a color based on the integer values (called range values) of its three components
	in a specified color coordinates sytem. The values are divided by 0xFF (255 - 1 byte) before being
	translated into the internal color components (in double). This conversion introduces a 'discreteness'
	in the color values that can be perceived by the human eye when drawing a a color gradient.
	Usage: Color color = Color( (uint8)255, 255, 128 );
	@param ColorType indicates the coordinates used in the color space. By default
	the RGB (red, green, and blue) system is used.
	@see ColorType
	*/
	Color( const uint8& val1, const uint8& val2, const uint8& val3, ColorType type=ctRGB );

	Color( const uint8& val1, const uint8& val2, const uint8& val3, const uint8& a, ColorType type=ctRGB );

	/**
	Initializes a color based on the values (type: unsigned short) of its three components
	in a specified color coordinates sytem. The values are divided by 0xFFFF (65535 - 2 bytes)
	before being translated into the internal color components (in double).
	Usage: Color color = Color( (uint16)0xFFFF, 0xFFFF, 0x7FFF );
	@param ColorType indicates the coordinates system used in the color space. By default
	the RGB (red, green, and blue) system is used.
	@see ColorType
	*/
	Color( const uint16& val1, const uint16& val2, const uint16& val3, ColorType type=ctRGB );

	Color( const uint16& val1, const uint16& val2, const uint16& val3, const uint16& a, ColorType type=ctRGB );

	/**
	initializes a color from its components in the 4 color space. ( not implemented yet )
	*/
	//Color( const double& c, const double& m, const double& y, const double& k );

	/**
	this is a constructor helping us in the conversion from an uint32 ( as in COLORREF )
	into which the color components have been packed (4 x 8bits).
	Under Win32 it is necessary to specify the cpsABGR parameter.
	@param the system used to pack the color components.
	@see ColorFormat
	*/
//	Color( const uint32& color, const ColorPackScheme& cps=cpsRGB );

	/**
	this is a constructor helping us in the conversion from an ulong32 ( as in COLORREF )
	into which the color components have been packed (4 x 8bits).
	Under Win32 it is necessary to specify the cpsABGR parameter.
	@param the system used to pack the color components.
	@see ColorFormat
	*/
	Color( const ulong32& color, const ColorPackScheme& cps=cpsRGB );

	/**
	this is a constructor halping us in the conversion from an ulong64 ( similarly as in COLORREF)
	into which the color components have been packed (4 x 16bits).
	Under Win32 it is necessary to specify the cpsABGR parameter.
	@param the system used to pack the color components.
	@see ColorFormat
	*/
	Color( const ulong64& color, const ColorPackScheme& cps=cpsRGB );

	/**
	extract a color from its color name. An internal map is used for this.
	*/
	Color( const String& colorName );

	virtual ~Color(){};

	double getRed() const;

	double getGreen() const;

	double getBlue() const;

	double getAlpha() const;

	void setRed( const double& red );

	void setGreen( const double& green );

	void setBlue( const double& blue );

	void setAlpha( const double& alpha );

	/**
	gets the color components of a color.
	*/
	void getRGB(double& r, double& g, double& b) const;

	void getRGBA(double& r, double& g, double& b, double& a) const;

	void getRGB8(uint8& r, uint8& g, uint8& b) const;

	void getRGBA8(uint8& r, uint8& g, uint8& b, uint8& a) const;

	void getRGB16(uint16& r, uint16& g, uint16& b) const;

	void getRGBA16(uint16& r, uint16& g, uint16& b, uint16& a) const;

	/**
	packs into a uint32 integer the color components using 8bits for each component.
	*/
	uint32 getRGBPack8( const ColorPackScheme& cps=cpsRGB ) const;

	/**
	packs into a ulong64 integer the color components using 16bits for each component.
	*/
	ulong64 getRGBPack16( const ColorPackScheme& cps=cpsRGB ) const;

	/**
	same as getRGBPack8, but with the parameter cpsABGR specified.
	introduced to make life easier to win32 users and less confusing.
	*/
	uint32 getColorRef32() const;

	/**
	same as getRGBPack16, but with the parameter cpsABGR specified.
	introduced to make life easier to win32 users and less confusing.
	*/
	ulong64 getColorRef64() const;

	/**
	sets the color starting from the known color components.
	*/
	void setRGB( const double& r, const double& g, const double& b);
	void setRGBA( const double& r, const double& g, const double& b, const double& a);

	void setRGB8( const uint8& r, const uint8& g, const uint8& b);
	void setRGBA8( const uint8& r, const uint8& g, const uint8& b, const uint8& a);
	void setRGB16( const uint16& r, const uint16& g, const uint16& b);
	void setRGBA16( const uint16& r, const uint16& g, const uint16& b, const uint16& a);

	/**
	sets the color starting from the known color components
	that have been packed into a single uint32 integer (4 x 8bits).
	*/
	Color& setRGBPack8( const uint32& rgb, const ColorPackScheme& cps=cpsRGB );

	/**
	sets the color starting from the known color components
	that have been packed into a single ulong64 integer (4 x 16bits).
	*/
	Color& setRGBPack16( const ulong64& rgb, const ColorPackScheme& cps=cpsRGB );

	/**
	same as setRGBPack8, but with the parameter cpsABGR specified.
	Introduced to make life easier to win32 users and less confusing.
	*/
	Color& setColorRef32( const uint32& rgb );

	/**
	same as setRGBPack16, but with the parameter cpsABGR specified.
	Introduced to make life easier to win32 users and less confusing.
	*/
	Color& setColorRef64( const ulong64& rgb );

	void getHSV(double& h, double& s, double& v) const;
	void setHSV( const double& h, const double& s, const double& v);

	void getHSL(double& h, double& l, double& s) const;
	void setHSL( const double& h, const double& l, const double& s);

	void getCMYK(double& c, double& m, double& y, double& k) const;
	void setCMYK( const double& c, const double& m, const double& y, const double& k);

	void getLab() const;
	void setLab();

	void getYUV() const;
	void setYUV();

	virtual void copyColor( const Color* source );

	virtual void copyColor( const Color& source );

	virtual void copy( Object* source ) {
		copyColor( (Color*) source );
	}

	Color& operator=( const Color* clr ){
		copyColor( clr );
		return *this;
	};

	Color& operator=( const Color& clr ){
		copyColor( clr );
		return *this;
	};

	bool operator==( const Color& clr ) const {
		return (clr.b_ == b_) && (clr.g_ == g_) && (clr.r_ == r_) && (clr.a_ == a_);
	}

	bool operator!=( const Color& clr ) const {
		return (clr.b_ != b_) || (clr.g_ != g_) || (clr.r_ != r_) || (clr.a_ != a_);
	}

	// this operator is necessary for Map<Color, something>
	bool operator< ( const Color& clr ) const {
		/**
		windows stores its color format in the following scheme 0x00BBGGRR:
		so b is more important (because in the intel architecture the
		rightmost byte is the most important)
		*/

		bool result =	(b_ < clr.b_) ? true :
						(clr.b_ < b_) ? false :
						(g_ < clr.g_) ? true :
						(clr.g_ < g_) ? false :
						(r_ < clr.r_) ? true :
						(clr.r_ < r_) ? false :
						(a_ < clr.a_) ? true : false;	// whow !

		#ifdef VCF_DEBUG_COLORS_COMPARISON_OPERATORS
			// this compare is less precise: so we can have rgb1==rgb2
			bool result2 = ( getRGB() < clr.getRGB() ) ;
			uint8 r, g, b, r2, g2, b2;
			getRGB(r, g, b);
			clr.getRGB(r2, g2, b2);
			VCF_ASSERT2( result2 == result || ( b==b2 || ( g!=g2 || r!=r2) ), L"different result for rounding reasons" );
		#endif
		return result;
	}

	bool operator<= ( const Color& clr ) const {
		bool result = false;

		return ( *this < clr ) || (*this == clr);
		return result;
	}

	bool operator> ( const Color& clr ) const {

		/**
		windows stores its color format in the following scheme 0x00BBGGRR:
		so b is more important (because in the intel architecture the
		rightmost byte is the most important)
		*/
		bool result =	(b_ > clr.b_) ? true :
						(clr.b_ > b_) ? false :
						(g_ > clr.g_) ? true :
						(clr.g_ > g_) ? false :
						(r_ > clr.r_) ? true :
						(clr.r_ > r_) ? false :
						(a_ > clr.a_) ? true : false;	// whow !
		#ifdef VCF_DEBUG_COLORS_COMPARISON_OPERATORS
			// this compare is less precise: so we can have rgb1==rgb2
			bool result2 = ( getRGB() > clr.getRGB() ) ;
			uint8 r, g, b, r2, g2, b2;
			getRGB(r, g, b);
			clr.getRGB(r2, g2, b2);
			VCF_ASSERT2( result2 == result || ( b==b2 || ( g!=g2 || r!=r2) ), L"different result for rounding reasons" );
		#endif
		return result;
	}

	bool operator>= ( const Color& clr ) const {
		bool result = false;
		return ( *this > clr ) || (*this == clr);
		return result;
	}

	virtual bool isEqual( const Color* color ) const {
		bool result = false;
		if ( NULL != color ){
			result = (color->b_ == b_) && (color->g_ == g_) && (color->r_ == r_) && (color->a_ == a_);
		}
		return result;
	};

	/**
	overrides the Object's base class member function.
	gives a string representation of the color in a simple format.
	*/
	virtual String toString(){
		return Format("#%02X%02X%02X") % (int)(r_*xFF+0.5) % (int)(g_*xFF+0.5) % (int)(b_*xFF+0.5);
	};

	/**
	generates a String with the internal representation of the color
	in hexadecimal format with 8bits per component.
	@param const ColorPackScheme& cps. With a value of cpsABGR we use an inverted scheme,
	as it is in the Intel architecture. The default is not inverted.
	       Example: the scheme 0x00RRGGBB would appear as BBGGRR00 with Intel architecture.
	@param const ColorType& ct. The color space used to extract the components. The default is ctRGB,
	the RGB color space.
	*/
	String toHexCode8 ( const ColorPackScheme& cps=cpsRGB, const ColorType& ct=ctRGB );
	String toHexCode16( const ColorPackScheme& cps=cpsRGB, const ColorType& ct=ctRGB );

	void changeHSV ( const double& percentH, const double& percentS, const double& percentV );

	void changeHSL ( const double& percentH, const double& percentS, const double& percentL );

	void changeHWB ( const double& percentH, const double& percentW, const double& percentB );

	void changeHue ( const double& deltaH );

	/**
	compute the luminosity as an RGB color.
	*/
	int getLuminosity() const ;

	/**
	set the luminosity of a color.
	@param const int& luminosity, the desired luminosity
	expressed in a [0, ColorSpace::HSLMax] scale.
	*/
	void setLuminosity( const int& luminosity );

	/**
	change the color to its complement (inverted)
	@return Color& the color itself.
	*/
	Color& invert();

	/**
	compute the complement of the color
	@return Color& the computed color.
	*/
	Color getInverted() const ;

	/**
	compute the inverted color of a color, given its components.
	*/
	void getInvertedRGB(double& r, double& g, double& b) const;

	/**
	compute the inverted components of a color, given its components in 8 bit.
	*/
	void getInvertedRGB8(uint8& r, uint8& g, uint8& b) const;

	/**
	compute the inverted components of a color, given its components in 16 bit.
	*/
	void getInvertedRGB16(uint16& r, uint16& g, uint16& b) const;

	/**
	makes the color brighter
	@return Color& the color itself.
	*/
	Color& brighter();

	/**
	makes the color brighter
	@return Color& the color itself.
	*/
	Color& darker();

	virtual Object* clone( bool deep ) {
		return new Color(*this);
	}

	/**
	gets a gray color from the map of internet colors.
	@param const int& gray, a gray value between 0 (black) and 255 (white)
	@return Color* a pointer to the color in the map.
	*/
	static Color* getColor( const int& gray );

	/**
	gets a color from the map of internet colors.
	@param const String& colorName the name of the color.
	@return Color* a pointer to the color in the map.
	*/
	static Color* getColor( const String& colorName );

	/**
	gets a color from the map with the closest match a given color.
	@param const Color& color the given color.
	@return Color* a pointer to the color in the map.
	*/
	static Color* getColorMatch( const Color& color );

	/**
	gets the name of the color from the map with the closest match a given color.
	@param const Color& color the given color.
	@return const String the name of the matching color in the map. The name
	is equal to ColorNames::unknownColorName() if not found.
	*/
	static const String getColorNameFromMap( const Color& color );

	/**
	creates the map of internet colors.
	*/
	static void createColorMap();

	/**
	computes a color with increased contrast.
	@param const Color& color the given color.
	@param double deltaL, the assigned fractional increase in luminosity.
	@return Color the computed color.
	*/
	static Color getColorContrast( const Color& color, double deltaL = 0.3 );

private:
	/**
	Red component. Valid range is from 0.0 to 1.0
	*/
	double r_;

	/**
	Green component. Valid range is from 0.0 to 1.0
	*/
	double g_;

	/**
	Blue component. Valid range is from 0.0 to 1.0
	*/
	double b_;

	/**
	Alpha component. Valid range is from 0.0 to 1.0. 0.0 is completely
	transparent, and 1.0 is completely opaque.
	*/
	double a_;

};


///////////////////////////////////////////////////////////////////////////////
// inlines

inline Color::Color(): Object() {
	r_ = 0.0;
	g_ = 0.0;
	b_ = 0.0;
	a_ = 1.0;
}

inline Color::Color( const Color& color ) : Object() {
	b_ = color.b_;
	g_ = color.g_;
	r_ = color.r_;
	a_ = color.a_;;
}

inline Color::Color( const double& val1, const double& val2, const double& val3, ColorType type ): Object() {
	a_ = 1.0;
	switch ( type ) {
		case ctRGB : {
			r_ = val1;
			g_ = val2;
			b_ = val3;
		}
		break;

		case ctHSL : {
			ColorSpace::HSLtype hsl;
			hsl.H = val1;
			hsl.L = val2;
			hsl.S = val3;

			ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB( hsl );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;

		case ctHSV : {
			ColorSpace::HSVtype hsv;
			hsv.H = val1;
			hsv.S = val2;
			hsv.V = val3;

			ColorSpace::RGBtype rgb = ColorSpace::HSVToRGB( hsv );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;
	case ctHWB:
	case ctYUV:
	case ctLab:
	case ctCMY:
	default:
		VCF_ASSERT(false);
		break;
	}
}


inline Color::Color( const double& val1, const double& val2, const double& val3, const double& a, ColorType type ): Object() {
	a_ = a;
	switch ( type ) {
		case ctRGB : {
			r_ = val1;
			g_ = val2;
			b_ = val3;
		}
		break;

		case ctHSL : {
			ColorSpace::HSLtype hsl;
			hsl.H = val1;
			hsl.L = val2;
			hsl.S = val3;

			ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB( hsl );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;

		case ctHSV : {
			ColorSpace::HSVtype hsv;
			hsv.H = val1;
			hsv.S = val2;
			hsv.V = val3;

			ColorSpace::RGBtype rgb = ColorSpace::HSVToRGB( hsv );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;
	case ctHWB:
	case ctYUV:
	case ctLab:
	case ctCMY:
	default:
		VCF_ASSERT(false);
		break;

	}
}

inline Color::Color( const uint8& val1, const uint8& val2, const uint8& val3, ColorType type ): Object() {
	a_ = 1.0;
	switch ( type ) {
		case ctRGB : {
			r_ = (double)val1 / xFF;
			g_ = (double)val2 / xFF;
			b_ = (double)val3 / xFF;
		}
		break;

		case ctHSL : {
			ColorSpace::HSLtype hsl;
			hsl.H = (double)val1 / xFF;
			hsl.L = (double)val2 / xFF;
			hsl.S = (double)val3 / xFF;

			ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB( hsl );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;

		case ctHSV : {
			ColorSpace::HSVtype hsv;
			hsv.H = (double)val1 / xFF;
			hsv.S = (double)val2 / xFF;
			hsv.V = (double)val3 / xFF;

			ColorSpace::RGBtype rgb = ColorSpace::HSVToRGB( hsv );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;
	case ctHWB:
	case ctYUV:
	case ctLab:
	case ctCMY:
	default:
		VCF_ASSERT(false);
		break;

	}
}

inline Color::Color( const uint8& val1, const uint8& val2, const uint8& val3, const uint8& a, ColorType type ): Object() {
	a_ = (double)a / xFF;
	switch ( type ) {
		case ctRGB : {
			r_ = (double)val1 / xFF;
			g_ = (double)val2 / xFF;
			b_ = (double)val3 / xFF;
		}
		break;

		case ctHSL : {
			ColorSpace::HSLtype hsl;
			hsl.H = (double)val1 / xFF;
			hsl.L = (double)val2 / xFF;
			hsl.S = (double)val3 / xFF;

			ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB( hsl );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;

		case ctHSV : {
			ColorSpace::HSVtype hsv;
			hsv.H = (double)val1 / xFF;
			hsv.S = (double)val2 / xFF;
			hsv.V = (double)val3 / xFF;

			ColorSpace::RGBtype rgb = ColorSpace::HSVToRGB( hsv );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;
	case ctHWB:
	case ctYUV:
	case ctLab:
	case ctCMY:
	default:
		VCF_ASSERT(false);
		break;

	}
}

inline Color::Color( const uint16& val1, const uint16& val2, const uint16& val3, ColorType type ): Object() {
	a_ = 1.0;
	switch ( type ) {
		case ctRGB : {
			r_ = (double)val1 / xFFFF;
			g_ = (double)val2 / xFFFF;
			b_ = (double)val3 / xFFFF;
		}
		break;

		case ctHSL : {
			ColorSpace::HSLtype hsl;
			hsl.H = (double)val1 / xFFFF;
			hsl.L = (double)val2 / xFFFF;
			hsl.S = (double)val3 / xFFFF;

			ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB( hsl );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;

		case ctHSV : {
			ColorSpace::HSVtype hsv;
			hsv.H = (double)val1 / xFFFF;
			hsv.S = (double)val2 / xFFFF;
			hsv.V = (double)val3 / xFFFF;

			ColorSpace::RGBtype rgb = ColorSpace::HSVToRGB( hsv );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;
	case ctHWB:
	case ctYUV:
	case ctLab:
	case ctCMY:
	default:
		VCF_ASSERT(false);
		break;

	}
}

inline Color::Color( const uint16& val1, const uint16& val2, const uint16& val3, const uint16& a, ColorType type ): Object() {
	a_ = (double)a / xFFFF;
	switch ( type ) {
		case ctRGB : {
			r_ = (double)val1 / xFFFF;
			g_ = (double)val2 / xFFFF;
			b_ = (double)val3 / xFFFF;
		}
		break;

		case ctHSL : {
			ColorSpace::HSLtype hsl;
			hsl.H = (double)val1 / xFFFF;
			hsl.L = (double)val2 / xFFFF;
			hsl.S = (double)val3 / xFFFF;

			ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB( hsl );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;

		case ctHSV : {
			ColorSpace::HSVtype hsv;
			hsv.H = (double)val1 / xFFFF;
			hsv.S = (double)val2 / xFFFF;
			hsv.V = (double)val3 / xFFFF;

			ColorSpace::RGBtype rgb = ColorSpace::HSVToRGB( hsv );

			r_ = rgb.R;
			g_ = rgb.G;
			b_ = rgb.B;
		}
		break;
	default:
		VCF_ASSERT(false);
		break;

	}
}

//inline Color::Color( const double& c, const double& m, const double& y, const double& k ) {
//	throw NotImplementedException();
//}

inline Color::Color(const ulong32& rgb, const ColorPackScheme& cps ): Object() {
	a_ = 1.0;
	setRGBPack8( rgb, cps );
}


inline Color::Color(const ulong64& rgb, const ColorPackScheme& cps ): Object() {
	a_ = 1.0;
	setRGBPack16( rgb, cps );
}


inline double Color::getRed() const {
	return r_;
}

inline double Color::getGreen() const {
	return g_;
}

inline double Color::getBlue() const {
	return b_;
}

inline double Color::getAlpha() const {
	return a_;
}

inline void Color::setRed( const double& red ) {
	r_ = red;
}

inline void Color::setGreen( const double& green ) {
	g_ = green;
}

inline void Color::setBlue( const double& blue ) {
	b_ = blue;
}

inline void Color::setAlpha( const double& alpha ) {
	a_ = alpha;
}

inline void Color::getRGB( double& r, double& g, double& b ) const {
	r = r_;
	g = g_;
	b = b_;
}

inline void Color::getRGBA( double& r, double& g, double& b, double& a ) const {
	r = r_;
	g = g_;
	b = b_;
	a = a_;
}

inline void Color::getRGB8( uint8& r, uint8& g, uint8& b ) const {
	r = (uint8)(r_ * xFF + 0.5);
	g = (uint8)(g_ * xFF + 0.5);
	b = (uint8)(b_ * xFF + 0.5);
}

inline void Color::getRGBA8( uint8& r, uint8& g, uint8& b, uint8& a ) const {
	r = (uint8)(r_ * xFF + 0.5);
	g = (uint8)(g_ * xFF + 0.5);
	b = (uint8)(b_ * xFF + 0.5);
	a = (uint8)(a_ * xFF + 0.5);
}

inline void Color::getRGB16( uint16& r, uint16& g, uint16& b ) const {
	r = (uint16)(r_ * xFFFF + 0.5);
	g = (uint16)(g_ * xFFFF + 0.5);
	b = (uint16)(b_ * xFFFF + 0.5);
}

inline void Color::getRGBA16( uint16& r, uint16& g, uint16& b, uint16& a ) const {
	r = (uint16)(r_ * xFFFF + 0.5);
	g = (uint16)(g_ * xFFFF + 0.5);
	b = (uint16)(b_ * xFFFF + 0.5);
	a = (uint16)(a_ * xFFFF + 0.5);
}

inline uint32 Color::getRGBPack8( const ColorPackScheme& cps ) const {
	uint32 rgba = 0;

	switch ( cps ) {
		case cpsRGB : {
			((uint8*)(&rgba))[2] = (uint8)(r_ * xFF + 0.5);
			((uint8*)(&rgba))[1] = (uint8)(g_ * xFF + 0.5);
			((uint8*)(&rgba))[0] = (uint8)(b_ * xFF + 0.5);
		}
		break;

		case cpsBGR : {
			((uint8*)(&rgba))[0] = (uint8)(r_ * xFF + 0.5);
			((uint8*)(&rgba))[1] = (uint8)(g_ * xFF + 0.5);
			((uint8*)(&rgba))[2] = (uint8)(b_ * xFF + 0.5);
		}
		break;

		case cpsARGB : {
			((uint8*)(&rgba))[2] = (uint8)(r_ * xFF + 0.5);
			((uint8*)(&rgba))[1] = (uint8)(g_ * xFF + 0.5);
			((uint8*)(&rgba))[0] = (uint8)(b_ * xFF + 0.5);
			((uint8*)(&rgba))[3] = (uint8)(a_ * xFF + 0.5);
		}
		break;

		case cpsABGR : {
			((uint8*)(&rgba))[0] = (uint8)(r_ * xFF + 0.5);
			((uint8*)(&rgba))[1] = (uint8)(g_ * xFF + 0.5);
			((uint8*)(&rgba))[2] = (uint8)(b_ * xFF + 0.5);
			((uint8*)(&rgba))[3] = (uint8)(a_ * xFF + 0.5);
		}
		break;
	}

	return rgba;
}

inline ulong64 Color::getRGBPack16( const ColorPackScheme& cps ) const {
	ulong64 rgb;

	switch ( cps ) {
		case cpsARGB : {
			((uint16*)(&rgb))[2] = (uint16)(r_ * xFFFF + 0.5);
			((uint16*)(&rgb))[1] = (uint16)(g_ * xFFFF + 0.5);
			((uint16*)(&rgb))[0] = (uint16)(b_ * xFFFF + 0.5);
			((uint16*)(&rgb))[3] = (uint16)(a_ * xFFFF + 0.5);
		}
		break;

		case cpsRGB : {
			((uint16*)(&rgb))[2] = (uint16)(r_ * xFFFF + 0.5);
			((uint16*)(&rgb))[1] = (uint16)(g_ * xFFFF + 0.5);
			((uint16*)(&rgb))[0] = (uint16)(b_ * xFFFF + 0.5);
		}
		break;

		case cpsBGR : {
			((uint16*)(&rgb))[0] = (uint16)(r_ * xFFFF + 0.5);
			((uint16*)(&rgb))[1] = (uint16)(g_ * xFFFF + 0.5);
			((uint16*)(&rgb))[2] = (uint16)(b_ * xFFFF + 0.5);
		}
		break;

		case cpsABGR : {
			((uint16*)(&rgb))[0] = (uint16)(r_ * xFFFF + 0.5);
			((uint16*)(&rgb))[1] = (uint16)(g_ * xFFFF + 0.5);
			((uint16*)(&rgb))[2] = (uint16)(b_ * xFFFF + 0.5);
			((uint16*)(&rgb))[3] = (uint16)(a_ * xFFFF + 0.5);
		}
		break;
	}

	return rgb;
}

inline uint32 Color::getColorRef32() const {
	return getRGBPack8( cpsBGR );
}

inline ulong64 Color::getColorRef64() const {
	return getRGBPack16( cpsBGR );
}

inline void Color::setRGB( const double& r, const double& g, const double& b) {
	r_ = r;
	g_ = g;
	b_ = b;
}

inline void Color::setRGBA( const double& r, const double& g, const double& b, const double& a) {
	r_ = r;
	g_ = g;
	b_ = b;
	a_ = a;
}

inline void Color::setRGB8( const uint8& r, const uint8& g, const uint8& b ) {
	r_ = ((double)r) / xFF;
	g_ = ((double)g) / xFF;
	b_ = ((double)b) / xFF;
}

inline void Color::setRGBA8( const uint8& r, const uint8& g, const uint8& b, const uint8& a ) {
	r_ = ((double)r) / xFF;
	g_ = ((double)g) / xFF;
	b_ = ((double)b) / xFF;
	a_ = ((double)a) / xFF;
}

inline void Color::setRGB16( const uint16& r, const uint16& g, const uint16& b ) {
	r_ = ((double)r) / xFFFF;
	g_ = ((double)g) / xFFFF;
	b_ = ((double)b) / xFFFF;
}

inline void Color::setRGBA16( const uint16& r, const uint16& g, const uint16& b, const uint16& a ) {
	r_ = ((double)r) / xFFFF;
	g_ = ((double)g) / xFFFF;
	b_ = ((double)b) / xFFFF;
	a_ = ((double)a) / xFFFF;
}

inline Color& Color::setRGBPack8( const uint32& rgb, const ColorPackScheme& cps ) {
	switch ( cps ) {
		case cpsRGB : {
			r_ = (double)((uint8*)&rgb)[2] / xFF;
			g_ = (double)((uint8*)&rgb)[1] / xFF;
			b_ = (double)((uint8*)&rgb)[0] / xFF;
		}
		break;

		case cpsBGR : {
			r_ = (double)((uint8*)&rgb)[0] / xFF;
			g_ = (double)((uint8*)&rgb)[1] / xFF;
			b_ = (double)((uint8*)&rgb)[2] / xFF;
		}
		break;

		case cpsARGB : {
			r_ = (double)((uint8*)&rgb)[2] / xFF;
			g_ = (double)((uint8*)&rgb)[1] / xFF;
			b_ = (double)((uint8*)&rgb)[0] / xFF;

			a_ = (double)((uint8*)&rgb)[3] / xFF;
		}
		break;

		case cpsABGR : {
			r_ = (double)((uint8*)&rgb)[0] / xFF;
			g_ = (double)((uint8*)&rgb)[1] / xFF;
			b_ = (double)((uint8*)&rgb)[2] / xFF;

			a_ = (double)((uint8*)&rgb)[3] / xFF;
		}
		break;
	}

	return *this;
}

inline Color& Color::setRGBPack16( const ulong64& rgb, const ColorPackScheme& cps ) {
	switch ( cps ) {
		case cpsRGB : {
			r_ = (double)((uint16*)&rgb)[2] / xFFFF;
			g_ = (double)((uint16*)&rgb)[1] / xFFFF;
			b_ = (double)((uint16*)&rgb)[0] / xFFFF;
		}
		break;

		case cpsBGR : {
			r_ = (double)((uint16*)&rgb)[0] / xFFFF;
			g_ = (double)((uint16*)&rgb)[1] / xFFFF;
			b_ = (double)((uint16*)&rgb)[2] / xFFFF;
		}
		break;

		case cpsARGB : {
			r_ = (double)((uint16*)&rgb)[2] / xFFFF;
			g_ = (double)((uint16*)&rgb)[1] / xFFFF;
			b_ = (double)((uint16*)&rgb)[0] / xFFFF;

			a_ = (double)((uint16*)&rgb)[3] / xFFFF;
		}
		break;

		case cpsABGR : {
			r_ = (double)((uint16*)&rgb)[0] / xFFFF;
			g_ = (double)((uint16*)&rgb)[1] / xFFFF;
			b_ = (double)((uint16*)&rgb)[2] / xFFFF;

			a_ = (double)((uint16*)&rgb)[3] / xFFFF;
		}
		break;
	}

	return *this;
}

inline Color& Color::setColorRef32( const uint32& rgb ) {
	return setRGBPack8( rgb, cpsBGR );
}

inline Color& Color::setColorRef64( const ulong64& rgb ) {
	return setRGBPack16( rgb, cpsBGR );
}


inline void Color::getHSV( double& h, double& s, double& v ) const {
	ColorSpace::HSVtype hsv;
	ColorSpace::RGBtype rgb;
	rgb.R = r_;
	rgb.G = g_;
	rgb.B = b_;

	hsv = ColorSpace::RGBToHSV( rgb );

	h = hsv.H;
	s = hsv.S;
	v = hsv.V;
}

inline void Color::setHSV( const double& h, const double& s, const double& v ) {
	ColorSpace::HSVtype hsv;
	hsv.H = h;
	hsv.S = s;
	hsv.V = v;

	ColorSpace::RGBtype rgb = ColorSpace::HSVToRGB( hsv );

	r_ = rgb.R;
	g_ = rgb.G;
	b_ = rgb.B;
}

inline void Color::getHSL( double& h, double& l, double& s ) const {
	ColorSpace::HSLtype hsl;
	ColorSpace::RGBtype rgb;
	rgb.R = r_;
	rgb.G = g_;
	rgb.B = b_;

	hsl = ColorSpace::RGBToHSL( rgb );

	h = hsl.H;
	l = hsl.L;
	s = hsl.S;
}

inline void Color::setHSL( const double& h, const double& l, const double& s ) {
	ColorSpace::HSLtype hsl;
	hsl.H = h;
	hsl.L = l;
	hsl.S = s;

	ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB( hsl );

	r_ = rgb.R;
	g_ = rgb.G;
	b_ = rgb.B;
}

inline void Color::getCMYK( double& c, double& m, double& y, double& k ) const {
	throw NotImplementedException();
}

inline void Color::setCMYK( const double& c, const double& m, const double& y, const double& k ) {
	throw NotImplementedException();
}

inline void Color::getLab() const {
	throw NotImplementedException();
}

inline void Color::setLab() {
	throw NotImplementedException();
}

inline void Color::getYUV() const {
	throw NotImplementedException();
}

inline void Color::setYUV() {
	throw NotImplementedException();
}


inline void Color::copyColor( const Color* color ) {
	if ( NULL != color ){
		r_ = color->r_;
		g_ = color->g_;
		b_ = color->b_;
		a_ = color->a_;
	}
}

inline void Color::copyColor( const Color& color ) {
	r_ = color.r_;
	g_ = color.g_;
	b_ = color.b_;
	a_ = color.a_;
}

inline void Color::changeHSV ( const double& percentH, const double& percentS, const double& percentV ) {
	ColorSpace::changeHWB( *this, percentH, percentS, percentV );
}

inline void Color::changeHSL ( const double& percentH, const double& percentS, const double& percentL ) {
	ColorSpace::changeHWB( *this, percentH, percentS, percentL );
}

inline void Color::changeHWB ( const double& percentH, const double& percentW, const double& percentB ) {
	ColorSpace::changeHWB( *this, percentH, percentW, percentB );
}

inline void Color::changeHue ( const double& deltaH ) {
	ColorSpace::changeHue( *this, deltaH );
}

inline int Color::getLuminosity() const {
	return ColorSpace::getLuminosity( *this );
}

inline void Color::setLuminosity( const int& luminosity ) {
	ColorSpace::setLuminosity( *this, luminosity );
}

inline Color& Color::invert() {
	// change the color to its complement
	r_ =  ( 1.0 - r_ );
	g_ =  ( 1.0 - g_ );
	b_ =  ( 1.0 - b_ );

	return *this;
}

inline Color Color::getInverted() const {
	// get the complement color
	Color color;
	color.r_ =  ( 1.0 - r_ );
	color.g_ =  ( 1.0 - g_ );
	color.b_ =  ( 1.0 - b_ );

	return color;
}

inline void Color::getInvertedRGB( double& r, double& g, double& b ) const {
	r =  ( 1.0 - r_ );
	g =  ( 1.0 - g_ );
	b =  ( 1.0 - b_ );
}

inline void Color::getInvertedRGB8( uint8& r, uint8& g, uint8& b ) const {
	r = (uint8)( (1.0 - r_ ) * xFF + 0.5);
	g = (uint8)( (1.0 - g_ ) * xFF + 0.5);
	b = (uint8)( (1.0 - b_ ) * xFF + 0.5);
}

inline void Color::getInvertedRGB16( uint16& r, uint16& g, uint16& b ) const {
	r = (uint16)( (1.0 - r_ ) * xFFFF + 0.5);
	g = (uint16)( (1.0 - g_ ) * xFFFF + 0.5);
	b = (uint16)( (1.0 - b_ ) * xFFFF + 0.5);
}





///////////////////////////////////////////////////////////////////////////////
// class ColorNames


/**
\class ColorNames Color.h "vcf/GraphicsKit/Color.h"
struct with all color names not included by VCF:
they are essentially grays
we need to instantiate it somewhere: unfortunately non-integer constant have no external
linkage otherwise ColorName would be replaced by a namespace with the same String
constants and put in the VCF library
*/
class GRAPHICSKIT_API ColorNames {
public:

	enum ColorID  {				//		NAMES					RGB (0x00RRGGBB)
#ifdef  VCF_LARGE_COLOR_LIST
			// long list ( 548 names )

			//from http://www.winvideo.net/colori.htm

			//shades of gray
			//color name r/g/b hex bg/fg color sample
			black                   ,   //  0;0;0           // 0x00000000
			grey                    ,   //  190;190;190     // 0x00BEBEBE
			dimgray                 ,   //  105;105;105     // 0x00696969   // frequently mispelled as dimgrey
			lightgray               ,   //  211;211;211     // 0x00D3D3D3
			lightslategrey          ,   //  119;136;153     // 0x00778899
			slategray               ,   //  112;128;144     // 0x00708090
			slategray1              ,   //  198;226;255     // 0x00C6E2FF
			slategray2              ,   //  185;211;238     // 0x00B9D3EE
			slategray3              ,   //  159;182;205     // 0x009FB6CD
			slategray4              ,   //  108;123;139     // 0x006C7B8B
			slategrey               ,   //  112;128;144     // 0x00708090
			grey0                   ,   //  0;0;0           // 0x00000000
			grey1                   ,   //  3;3;3           // 0x00030303
			grey2                   ,   //  5;5;5           // 0x00050505
			grey3                   ,   //  8;8;8           // 0x00080808
			grey4                   ,   //  10;10;10        // 0x000A0A0A
			grey5                   ,   //  13;13;13        // 0x000D0D0D
			grey6                   ,   //  15;15;15        // 0x000F0F0F
			grey7                   ,   //  18;18;18        // 0x00121212
			grey8                   ,   //  20;20;20        // 0x00141414
			grey98                  ,   //  23;23;23        // 0x00171717
			grey10                  ,   //  26;26;26        // 0x001A1A1A
			grey11                  ,   //  28;28;28        // 0x001C1C1C
			grey12                  ,   //  31;31;31        // 0x001F1F1F
			grey13                  ,   //  33;33;33        // 0x00212121
			grey14                  ,   //  36;36;36        // 0x00242424
			grey15                  ,   //  38;38;38        // 0x00262626
			grey16                  ,   //  41;41;41        // 0x00292929
			grey17                  ,   //  43;43;43        // 0x002B2B2B
			grey18                  ,   //  46;46;46        // 0x002E2E2E
			grey19                  ,   //  48;48;48        // 0x00303030
			grey20                  ,   //  51;51;51        // 0x00333333
			grey21                  ,   //  54;54;54        // 0x00363636
			grey22                  ,   //  56;56;56        // 0x00383838
			grey23                  ,   //  59;59;59        // 0x003B3B3B
			grey24                  ,   //  61;61;61        // 0x003D3D3D
			grey25                  ,   //  64;64;64        // 0x00404040
			grey26                  ,   //  66;66;66        // 0x00424242
			grey27                  ,   //  69;69;69        // 0x00454545
			grey28                  ,   //  71;71;71        // 0x00474747
			grey29                  ,   //  74;74;74        // 0x004A4A4A
			grey30                  ,   //  77;77;77        // 0x004D4D4D
			grey31                  ,   //  79;79;79        // 0x004F4F4F
			grey32                  ,   //  82;82;82        // 0x00525252
			grey33                  ,   //  84;84;84        // 0x00545454
			grey34                  ,   //  87;87;87        // 0x00575757
			grey35                  ,   //  89;89;89        // 0x00595959
			grey36                  ,   //  92;92;92        // 0x005C5C5C
			grey37                  ,   //  94;94;94        // 0x005E5E5E
			grey38                  ,   //  97;97;97        // 0x00616161
			grey39                  ,   //  99;99;99        // 0x00636363
			grey40                  ,   //  102;102;102     // 0x00666666
			grey41                  ,   //  105;105;105     // 0x00696969
			grey42                  ,   //  107;107;107     // 0x006B6B6B
			grey43                  ,   //  110;110;110     // 0x006E6E6E
			grey44                  ,   //  112;112;112     // 0x00707070
			grey45                  ,   //  115;115;115     // 0x00737373
			grey46                  ,   //  117;117;117     // 0x00757575
			grey47                  ,   //  120;120;120     // 0x00787878
			grey48                  ,   //  122;122;122     // 0x007A7A7A
			grey49                  ,   //  125;125;125     // 0x007D7D7D
			grey50                  ,   //  127;127;127     // 0x007F7F7F
			grey51                  ,   //  130;130;130     // 0x00828282
			grey52                  ,   //  133;133;133     // 0x00858585
			grey53                  ,   //  135;135;135     // 0x00878787
			grey54                  ,   //  138;138;138     // 0x008A8A8A
			grey55                  ,   //  140;140;140     // 0x008C8C8C
			grey56                  ,   //  143;143;143     // 0x008F8F8F
			grey57                  ,   //  145;145;145     // 0x00919191
			grey58                  ,   //  148;148;148     // 0x00949494
			grey59                  ,   //  150;150;150     // 0x00969696
			grey60                  ,   //  153;153;153     // 0x00999999
			grey61                  ,   //  156;156;156     // 0x009C9C9C
			grey62                  ,   //  158;158;158     // 0x009E9E9E
			grey63                  ,   //  161;161;161     // 0x00A1A1A1
			grey64                  ,   //  163;163;163     // 0x00A3A3A3
			grey65                  ,   //  166;166;166     // 0x00A6A6A6
			grey66                  ,   //  168;168;168     // 0x00A8A8A8
			grey67                  ,   //  171;171;171     // 0x00ABABAB
			grey68                  ,   //  173;173;173     // 0x00ADADAD
			grey69                  ,   //  176;176;176     // 0x00B0B0B0
			grey70                  ,   //  179;179;179     // 0x00B3B3B3
			grey71                  ,   //  181;181;181     // 0x00B5B5B5
			grey72                  ,   //  184;184;184     // 0x00B8B8B8
			grey73                  ,   //  186;186;186     // 0x00BABABA
			grey74                  ,   //  189;189;189     // 0x00BDBDBD
			grey75                  ,   //  191;191;191     // 0x00BFBFBF
			grey76                  ,   //  194;194;194     // 0x00C2C2C2
			grey77                  ,   //  196;196;196     // 0x00C4C4C4
			grey78                  ,   //  199;199;199     // 0x00C7C7C7
			grey79                  ,   //  201;201;201     // 0x00C9C9C9
			grey80                  ,   //  204;204;204     // 0x00CCCCCC
			grey81                  ,   //  207;207;207     // 0x00CFCFCF
			grey82                  ,   //  209;209;209     // 0x00D1D1D1
			grey83                  ,   //  212;212;212     // 0x00D4D4D4
			grey84                  ,   //  214;214;214     // 0x00D6D6D6
			grey85                  ,   //  217;217;217     // 0x00D9D9D9
			grey86                  ,   //  219;219;219     // 0x00DBDBDB
			grey87                  ,   //  222;222;222     // 0x00DEDEDE
			grey88                  ,   //  224;224;224     // 0x00E0E0E0
			grey89                  ,   //  227;227;227     // 0x00E3E3E3
			grey90                  ,   //  229;229;229     // 0x00E5E5E5
			grey91                  ,   //  232;232;232     // 0x00E8E8E8
			grey92                  ,   //  235;235;235     // 0x00EBEBEB
			grey93                  ,   //  237;237;237     // 0x00EDEDED
			grey94                  ,   //  240;240;240     // 0x00F0F0F0
			grey95                  ,   //  242;242;242     // 0x00F2F2F2
			grey96                  ,   //  245;245;245     // 0x00F5F5F5
			grey97                  ,   //  247;247;247     // 0x00F7F7F7
			grey98                  ,   //  250;250;250     // 0x00FAFAFA
			grey99                  ,   //  252;252;252     // 0x00FCFCFC
			grey100                 ,   //  255;255;255     // 0x00FFFFFF

			//shades of blue
			//color name r/g/b hex bg/fg color sample
			aliceblue               ,   //  240;248;255     // 0x00F0F8FF
			blueviolet              ,   //  138;43;226      // 0x008A2BE2
			cadetblue               ,   //  95;158;160      // 0x005F9EA0
			cadetblue1              ,   //  152;245;255     // 0x0098F5FF
			cadetblue2              ,   //  142;229;238     // 0x008EE5EE
			cadetblue3              ,   //  122;197;205     // 0x007AC5CD
			cadetblue4              ,   //  83;134;139      // 0x0053868B
			cornflowerblue          ,   //  100;149;237     // 0x006495ED
			darkslateblue           ,   //  72;61;139       // 0x00483D8B
			darkturquoise           ,   //  0;206;209       // 0x0000CED1
			deepskyblue             ,   //  0;191;255       // 0x0000BFFF
			deepskyblue1            ,   //  0;191;255       // 0x0000BFFF
			deepskyblue2            ,   //  0;178;238       // 0x0000B2EE
			deepskyblue3            ,   //  0;154;205       // 0x00009ACD
			deepskyblue4            ,   //  0;104;139       // 0x0000688B
			dodgerblue              ,   //  30;144;255      // 0x001E90FF
			dodgerblue1             ,   //  30;144;255      // 0x001E90FF
			dodgerblue2             ,   //  28;134;238      // 0x001C86EE
			dodgerblue3             ,   //  24;116;205      // 0x001874CD
			dodgerblue4             ,   //  16;78;139       // 0x00104E8B
			lightblue               ,   //  173;216;230     // 0x00ADD8E6
			lightblue1              ,   //  191;239;255     // 0x00BFEFFF
			lightblue2              ,   //  178;223;238     // 0x00B2DFEE
			lightblue3              ,   //  154;192;205     // 0x009AC0CD
			lightblue4              ,   //  104;131;139     // 0x0068838B
			lightcyan               ,   //  224;255;255     // 0x00E0FFFF
			lightcyan1              ,   //  224;255;255     // 0x00E0FFFF
			lightcyan2              ,   //  209;238;238     // 0x00D1EEEE
			lightcyan3              ,   //  180;205;205     // 0x00B4CDCD
			lightcyan4              ,   //  122;139;139     // 0x007A8B8B
			lightskyblue            ,   //  135;206;250     // 0x0087CEFA
			lightskyblue1           ,   //  176;226;255     // 0x00B0E2FF
			lightskyblue2           ,   //  164;211;238     // 0x00A4D3EE
			lightskyblue3           ,   //  141;182;205     // 0x008DB6CD
			lightskyblue4           ,   //  96;123;139      // 0x00607B8B
			lightslateblue          ,   //  132;112;255     // 0x008470FF
			lightsteelblue          ,   //  176;196;222     // 0x00B0C4DE
			lightsteelblue1         ,   //  202;225;255     // 0x00CAE1FF
			lightsteelblue2         ,   //  188;210;238     // 0x00BCD2EE
			lightsteelblue3         ,   //  162;181;205     // 0x00A2B5CD
			lightsteelblue4         ,   //  110;123;139     // 0x006E7B8B
			mediumaquamarine        ,   //  102;205;170     // 0x0066CDAA
			mediumblue              ,   //  0;0;205         // 0x000000CD
			mediumslateblue         ,   //  123;104;238     // 0x007B68EE
			mediumturquoise         ,   //  72;209;204      // 0x0048D1CC
			midnightblue            ,   //  25;25;112       // 0x00191970
			navyblue                ,   //  0;0;128         // 0x00000080
			paleturquoise           ,   //  175;238;238     // 0x00AFEEEE
			paleturquoise1          ,   //  187;255;255     // 0x00BBFFFF
			paleturquoise2          ,   //  174;238;238     // 0x00AEEEEE
			paleturquoise3          ,   //  150;205;205     // 0x0096CDCD
			paleturquoise4          ,   //  102;139;139     // 0x00668B8B
			powderblue              ,   //  176;224;230     // 0x00B0E0E6
			royalblue               ,   //  65;105;225      // 0x004169E1
			royalblue1              ,   //  72;118;255      // 0x004876FF
			royalblue2              ,   //  67;110;238      // 0x00436EEE
			royalblue3              ,   //  58;95;205       // 0x003A5FCD
			royalblue4              ,   //  39;64;139       // 0x0027408B
			royalblue5              ,   //  00;34;102       // 0x00002266
			skyblue                 ,   //  135;206;235     // 0x0087CEEB
			skyblue1                ,   //  135;206;255     // 0x0087CEFF
			skyblue2                ,   //  126;192;238     // 0x007EC0EE
			skyblue3                ,   //  108;166;205     // 0x006CA6CD
			skyblue4                ,   //  74;112;139      // 0x004A708B
			slateblue               ,   //  106;90;205      // 0x006A5ACD
			slateblue1              ,   //  131;111;255     // 0x00836FFF
			slateblue2              ,   //  122;103;238     // 0x007A67EE
			slateblue3              ,   //  105;89;205      // 0x006959CD
			slateblue4              ,   //  71;60;139       // 0x00473C8B
			steelblue               ,   //  70;130;180      // 0x004682B4
			steelblue1              ,   //  99;184;255      // 0x0063B8FF
			steelblue2              ,   //  92;172;238      // 0x005CACEE
			steelblue3              ,   //  79;148;205      // 0x004F94CD
			steelblue4              ,   //  54;100;139      // 0x0036648B
			aquamarine              ,   //  127;255;212     // 0x007FFFD4
			aquamarine1             ,   //  127;255;212     // 0x007FFFD4
			aquamarine2             ,   //  118;238;198     // 0x0076EEC6
			aquamarine3             ,   //  102;205;170     // 0x0066CDAA
			aquamarine4             ,   //  69;139;116      // 0x00458B74
			azure                   ,   //  240;255;255     // 0x00F0FFFF
			azure1                  ,   //  240;255;255     // 0x00F0FFFF
			azure2                  ,   //  224;238;238     // 0x00E0EEEE
			azure3                  ,   //  193;205;205     // 0x00C1CDCD
			azure4                  ,   //  131;139;139     // 0x00838B8B
			blue                    ,   //  0;0;255         // 0x000000FF
			blue1                   ,   //  0;0;255         // 0x000000FF
			blue2                   ,   //  0;0;238         // 0x000000EE
			blue3                   ,   //  0;0;205         // 0x000000CD
			blue4                   ,   //  0;0;139         // 0x0000008B
			cyan                    ,   //  0;255;255       // 0x0000FFFF
			cyan1                   ,   //  0;255;255       // 0x0000FFFF
			cyan2                   ,   //  0;238;238       // 0x0000EEEE
			cyan3                   ,   //  0;205;205       // 0x0000CDCD
			cyan4                   ,   //  0;139;139       // 0x00008B8B
			navy                    ,   //  0;0;128         // 0x00000080
			turquoise               ,   //  64;224;208      // 0x0040E0D0
			turquoise1              ,   //  0;245;255       // 0x0000F5FF
			turquoise2              ,   //  0;229;238       // 0x0000E5EE
			turquoise3              ,   //  0;197;205       // 0x0000C5CD
			turquoise4              ,   //  0;134;139       // 0x0000868B
			darkslategray           ,   //  47;79;79        // 0x002F4F4F
			darkslategray1          ,   //  151;255;255     // 0x0097FFFF
			darkslategray2          ,   //  141;238;238     // 0x008DEEEE
			darkslategray3          ,   //  121;205;205     // 0x0079CDCD
			darkslategray4          ,   //  82;139;139      // 0x00528B8B

			//shades of brown
			//color name r/g/b hex bg/fg color sample
			rosybrown               ,   //  188;143;143     // 0x00BC8F8F
			rosybrown1              ,   //  255;193;193     // 0x00FFC1C1
			rosybrown2              ,   //  238;180;180     // 0x00EEB4B4
			rosybrown3              ,   //  205;155;155     // 0x00CD9B9B
			rosybrown4              ,   //  139;105;105     // 0x008B6969
			saddlebrown             ,   //  139;69;19       // 0x008B4513
			sandybrown              ,   //  244;164;96      // 0x00F4A460
			beige                   ,   //  245;245;220     // 0x00F5F5DC
			brown                   ,   //  165;42;42       // 0x00A52A2A
			brown1                  ,   //  255;64;64       // 0x00FF4040
			brown2                  ,   //  238;59;59       // 0x00EE3B3B
			brown3                  ,   //  205;51;51       // 0x00CD3333
			brown4                  ,   //  139;35;35       // 0x008B2323
			burlywood               ,   //  222;184;135     // 0x00DEB887
			burlywood1              ,   //  255;211;155     // 0x00FFD39B
			burlywood2              ,   //  238;197;145     // 0x00EEC591
			burlywood3              ,   //  205;170;125     // 0x00CDAA7D
			burlywood4              ,   //  139;115;85      // 0x008B7355
			chocolate               ,   //  210;105;30      // 0x00D2691E
			chocolate1              ,   //  255;127;36      // 0x00FF7F24
			chocolate2              ,   //  238;118;33      // 0x00EE7621
			chocolate3              ,   //  205;102;29      // 0x00CD661D
			chocolate4              ,   //  139;69;19       // 0x008B4513
			peru                    ,   //  205;133;63      // 0x00CD853F
			tan                     ,   //  210;180;140     // 0x00D2B48C
			tan1                    ,   //  255;165;79      // 0x00FFA54F
			tan2                    ,   //  238;154;73      // 0x00EE9A49
			tan3                    ,   //  205;133;63      // 0x00CD853F
			tan4                    ,   //  139;90;43       // 0x008B5A2B

			//shades of green
			//color name r/g/b hex bg/fg color sample
			darkgreen               ,   //  0;100;0 006400
			darkkhaki               ,   //  189;183;107     // 0x00BDB76B
			darkolivegreen          ,   //  85;107;47       // 0x00556B2F
			darkolivegreen1         ,   //  202;255;112     // 0x00CAFF70
			darkolivegreen2         ,   //  188;238;104     // 0x00BCEE68
			darkolivegreen3         ,   //  162;205;90      // 0x00A2CD5A
			darkolivegreen4         ,   //  110;139;61      // 0x006E8B3D
			darkseagreen            ,   //  143;188;143     // 0x008FBC8F
			darkseagreen1           ,   //  193;255;193     // 0x00C1FFC1
			darkseagreen2           ,   //  180;238;180     // 0x00B4EEB4
			darkseagreen3           ,   //  155;205;155     // 0x009BCD9B
			darkseagreen4           ,   //  105;139;105     // 0x00698B69
			forestgreen             ,   //  34;139;34       // 0x00228B22
			greenyellow             ,   //  173;255;47      // 0x00ADFF2F
			lawngreen               ,   //  124;252;0       // 0x007CFC00
			lightseagreen           ,   //  32;178;170      // 0x0020B2AA
			limegreen               ,   //  50;205;50       // 0x0032CD32
			mediumseagreen          ,   //  60;179;113      // 0x003CB371
			mediumspringgreen       ,   //  0;250;154       // 0x0000FA9A
			mintcream               ,   //  245;255;250     // 0x00F5FFFA
			olivedrab               ,   //  107;142;35      // 0x006B8E23
			olivedrab1              ,   //  192;255;62      // 0x00C0FF3E
			olivedrab2              ,   //  179;238;58      // 0x00B3EE3A
			olivedrab3              ,   //  154;205;50      // 0x009ACD32
			olivedrab4              ,   //  105;139;34      // 0x00698B22
			palegreen               ,   //  152;251;152     // 0x0098FB98
			palegreen1              ,   //  154;255;154     // 0x009AFF9A
			palegreen2              ,   //  144;238;144     // 0x0090EE90
			palegreen3              ,   //  124;205;124     // 0x007CCD7C
			palegreen4              ,   //  84;139;84       // 0x00548B54
			seagreen                ,   //  46;139;87       // 0x002E8B57
			seagreen1               ,   //  84;255;159      // 0x0054FF9F
			seagreen2               ,   //  78;238;148      // 0x004EEE94
			seagreen3               ,   //  67;205;128      // 0x0043CD80
			seagreen4               ,   //  46;139;87       // 0x002E8B57
			springgreen             ,   //  0;255;127       // 0x0000FF7F
			springgreen1            ,   //  0;255;127       // 0x0000FF7F
			springgreen2            ,   //  0;238;118       // 0x0000EE76
			springgreen3            ,   //  0;205;102       // 0x0000CD66
			springgreen4            ,   //  0;139;69        // 0x00008B45
			yellowgreen             ,   //  154;205;50      // 0x009ACD32
			chartreuse              ,   //  127;255;0       // 0x007FFF00
			chartreuse1             ,   //  127;255;0       // 0x007FFF00
			chartreuse2             ,   //  118;238;0       // 0x0076EE00
			chartreuse3             ,   //  102;205;0       // 0x0066CD00
			chartreuse4             ,   //  69;139;0        // 0x00458B00
			green                   ,   //  0;255;0         // 0x0000FF00
			green1                  ,   //  0;255;0         // 0x0000FF00
			green2                  ,   //  0;238;0         // 0x0000EE00
			green3                  ,   //  0;205;0         // 0x0000CD00
			green4                  ,   //  0;139;0         // 0x00008B00
			khaki                   ,   //  240;230;140     // 0x00F0E68C
			khaki1                  ,   //  255;246;143     // 0x00FFF68F
			khaki2                  ,   //  238;230;133     // 0x00EEE685
			khaki3                  ,   //  205;198;115     // 0x00CDC673
			khaki4                  ,   //  139;134;78      // 0x008B864E

			//shades of orange
			//color name r/g/b hex bg/fg color sample
			darkorange              ,   //  255;140;0       // 0x00FF8C00
			darkorange1             ,   //  255;127;0       // 0x00FF7F00
			darkorange2             ,   //  238;118;0       // 0x00EE7600
			darkorange3             ,   //  205;102;0       // 0x00CD6600
			darkorange4             ,   //  139;69;0        // 0x008B4500
			darksalmon              ,   //  233;150;122     // 0x00E9967A
			lightcoral              ,   //  240;128;128     // 0x00F08080
			lightsalmon             ,   //  255;160;122     // 0x00FFA07A
			lightsalmon1            ,   //  255;160;122     // 0x00FFA07A
			lightsalmon2            ,   //  238;149;114     // 0x00EE9572
			lightsalmon3            ,   //  205;129;98      // 0x00CD8162
			lightsalmon4            ,   //  139;87;66       // 0x008B5742
			peachpuff               ,   //  255;218;185     // 0x00FFDAB9
			peachpuff1              ,   //  255;218;185     // 0x00FFDAB9
			peachpuff2              ,   //  238;203;173     // 0x00EECBAD
			peachpuff3              ,   //  205;175;149     // 0x00CDAF95
			peachpuff4              ,   //  139;119;101     // 0x008B7765
			bisque                  ,   //  255;228;196     // 0x00FFE4C4
			bisque1                 ,   //  255;228;196     // 0x00FFE4C4
			bisque2                 ,   //  238;213;183     // 0x00EED5B7
			bisque3                 ,   //  205;183;158     // 0x00CDB79E
			bisque4                 ,   //  139;125;107     // 0x008B7D6B
			coral                   ,   //  255;127;80      // 0x00FF7F50
			coral1                  ,   //  255;114;86      // 0x00FF7256
			coral2                  ,   //  238;106;80      // 0x00EE6A50
			coral3                  ,   //  205;91;69       // 0x00CD5B45
			coral4                  ,   //  139;62;47       // 0x008B3E2F
			honeydew                ,   //  240;255;240     // 0x00F0FFF0
			honeydew1               ,   //  240;255;240     // 0x00F0FFF0
			honeydew2               ,   //  224;238;224     // 0x00E0EEE0
			honeydew3               ,   //  193;205;193     // 0x00C1CDC1
			honeydew4               ,   //  131;139;131     // 0x00838B83
			orange                  ,   //  255;165;0       // 0x00FFA500
			orange1                 ,   //  255;165;0       // 0x00FFA500
			orange2                 ,   //  238;154;0       // 0x00EE9A00
			orange3                 ,   //  205;133;0       // 0x00CD8500
			orange4                 ,   //  139;90;0        // 0x008B5A00
			salmon                  ,   //  250;128;114     // 0x00FA8072
			salmon1                 ,   //  255;140;105     // 0x00FF8C69
			salmon2                 ,   //  238;130;98      // 0x00EE8262
			salmon3                 ,   //  205;112;84      // 0x00CD7054
			salmon4                 ,   //  139;76;57       // 0x008B4C39
			sienna                  ,   //  160;82;45       // 0x00A0522D
			sienna1                 ,   //  255;130;71      // 0x00FF8247
			sienna2                 ,   //  238;121;66      // 0x00EE7942
			sienna3                 ,   //  205;104;57      // 0x00CD6839
			sienna4                 ,   //  139;71;38       // 0x008B4726

			//shades of red
			//color name r/g/b hex bg/fg color sample
			deeppink                ,   //  255;20;147      // 0x00FF1493
			deeppink1               ,   //  255;20;147      // 0x00FF1493
			deeppink2               ,   //  238;18;137      // 0x00EE1289
			deeppink3               ,   //  205;16;118      // 0x00CD1076
			deeppink4               ,   //  139;10;80       // 0x008B0A50
			hotpink                 ,   //  255;105;180     // 0x00FF69B4
			hotpink1                ,   //  255;110;180     // 0x00FF6EB4
			hotpink2                ,   //  238;106;167     // 0x00EE6AA7
			hotpink3                ,   //  205;96;144      // 0x00CD6090
			hotpink4                ,   //  139;58;98       // 0x008B3A62
			indianred               ,   //  205;92;92       // 0x00CD5C5C
			indianred1              ,   //  255;106;106     // 0x00FF6A6A
			indianred2              ,   //  238;99;99       // 0x00EE6363
			indianred3              ,   //  205;85;85       // 0x00CD5555
			indianred4              ,   //  139;58;58       // 0x008B3A3A
			lightpink               ,   //  255;182;193     // 0x00FFB6C1
			lightpink1              ,   //  255;174;185     // 0x00FFAEB9
			lightpink2              ,   //  238;162;173     // 0x00EEA2AD
			lightpink3              ,   //  205;140;149     // 0x00CD8C95
			lightpink4              ,   //  139;95;101      // 0x008B5F65
			mediumvioletred         ,   //  199;21;133      // 0x00C71585
			mistyrose               ,   //  255;228;225     // 0x00FFE4E1
			mistyrose1              ,   //  255;228;225     // 0x00FFE4E1
			mistyrose2              ,   //  238;213;210     // 0x00EED5D2
			mistyrose3              ,   //  205;183;181     // 0x00CDB7B5
			mistyrose4              ,   //  139;125;123     // 0x008B7D7B
			orangered               ,   //  255;69;0        // 0x00FF4500
			orangered1              ,   //  255;69;0        // 0x00FF4500
			orangered2              ,   //  238;64;0        // 0x00EE4000
			orangered3              ,   //  205;55;0        // 0x00CD3700
			orangered4              ,   //  139;37;0        // 0x008B2500
			palevioletred           ,   //  219;112;147     // 0x00DB7093
			palevioletred1          ,   //  255;130;171     // 0x00FF82AB
			palevioletred2          ,   //  238;121;159     // 0x00EE799F
			palevioletred3          ,   //  205;104;137     // 0x00CD6889
			palevioletred4          ,   //  139;71;93       // 0x008B475D
			violetred               ,   //  208;32;144      // 0x00D02090
			violetred1              ,   //  255;62;150      // 0x00FF3E96
			violetred2              ,   //  238;58;140      // 0x00EE3A8C
			violetred3              ,   //  205;50;120      // 0x00CD3278
			violetred4              ,   //  139;34;82       // 0x008B2252
			firebrick               ,   //  178;34;34       // 0x00B22222
			firebrick1              ,   //  255;48;48       // 0x00FF3030
			firebrick2              ,   //  238;44;44       // 0x00EE2C2C
			firebrick3              ,   //  205;38;38       // 0x00CD2626
			firebrick4              ,   //  139;26;26       // 0x008B1A1A
			pink                    ,   //  255;192;203     // 0x00FFC0CB
			pink1                   ,   //  255;181;197     // 0x00FFB5C5
			pink2                   ,   //  238;169;184     // 0x00EEA9B8
			pink3                   ,   //  205;145;158     // 0x00CD919E
			pink4                   ,   //  139;99;108      // 0x008B636C
			red                     ,   //  255;0;0         // 0x00FF0000
			red1                    ,   //  255;0;0         // 0x00FF0000
			red2                    ,   //  238;0;0         // 0x00EE0000
			red3                    ,   //  205;0;0         // 0x00CD0000
			red4                    ,   //  139;0;0         // 0x008B0000
			tomato                  ,   //  255;99;71       // 0x00FF6347
			tomato1                 ,   //  255;99;71       // 0x00FF6347
			tomato2                 ,   //  238;92;66       // 0x00EE5C42
			tomato3                 ,   //  205;79;57       // 0x00CD4F39
			tomato4                 ,   //  139;54;38       // 0x008B3626

			//shades of violet
			//color name r/g/b hex bg/fg color sample
			darkorchid              ,   //  153;50;204      // 0x009932CC
			darkorchid1             ,   //  191;62;255      // 0x00BF3EFF
			darkorchid2             ,   //  178;58;238      // 0x00B23AEE
			darkorchid3             ,   //  154;50;205      // 0x009A32CD
			darkorchid4             ,   //  104;34;139      // 0x0068228B
			darkviolet              ,   //  148;0;211       // 0x009400D3
			lavenderblush           ,   //  255;240;245     // 0x00FFF0F5
			lavenderblush1          ,   //  255;240;245     // 0x00FFF0F5
			lavenderblush2          ,   //  238;224;229     // 0x00EEE0E5
			lavenderblush3          ,   //  205;193;197     // 0x00CDC1C5
			lavenderblush4          ,   //  139;131;134     // 0x008B8386
			mediumorchid            ,   //  186;85;211      // 0x00BA55D3
			mediumorchid1           ,   //  224;102;255     // 0x00E066FF
			mediumorchid2           ,   //  209;95;238      // 0x00D15FEE
			mediumorchid3           ,   //  180;82;205      // 0x00B452CD
			mediumorchid4           ,   //  122;55;139      // 0x007A378B
			mediumpurple            ,   //  147;112;219     // 0x009370DB
			mediumpurple1           ,   //  171;130;255     // 0x00AB82FF
			mediumpurple2           ,   //  159;121;238     // 0x009F79EE
			mediumpurple3           ,   //  137;104;205     // 0x008968CD
			mediumpurple4           ,   //  93;71;139       // 0x005D478B
			lavender                ,   //  230;230;250     // 0x00E6E6FA
			magenta                 ,   //  255;0;255       // 0x00FF00FF
			magenta1                ,   //  255;0;255       // 0x00FF00FF
			magenta2                ,   //  238;0;238       // 0x00EE00EE
			magenta3                ,   //  205;0;205       // 0x00CD00CD
			magenta4                ,   //  139;0;139       // 0x008B008B
			maroon                  ,   //  176;48;96       // 0x00B03060
			maroon1                 ,   //  255;52;179      // 0x00FF34B3
			maroon2                 ,   //  238;48;167      // 0x00EE30A7
			maroon3                 ,   //  205;41;144      // 0x00CD2990
			maroon4                 ,   //  139;28;98       // 0x008B1C62
			orchid                  ,   //  218;112;214     // 0x00DA70D6
			orchid1                 ,   //  255;131;250     // 0x00FF83FA
			orchid2                 ,   //  238;122;233     // 0x00EE7AE9
			orchid3                 ,   //  205;105;201     // 0x00CD69C9
			orchid4                 ,   //  139;71;137      // 0x008B4789
			plum                    ,   //  221;160;221     // 0x00DDA0DD
			plum1                   ,   //  255;187;255     // 0x00FFBBFF
			plum2                   ,   //  238;174;238     // 0x00EEAEEE
			plum3                   ,   //  205;150;205     // 0x00CD96CD
			plum4                   ,   //  139;102;139     // 0x008B668B
			purple                  ,   //  160;32;240      // 0x00A020F0
			purple1                 ,   //  155;48;255      // 0x009B30FF
			purple2                 ,   //  145;44;238      // 0x00912CEE
			purple3                 ,   //  125;38;205      // 0x007D26CD
			purple4                 ,   //  85;26;139       // 0x00551A8B
			thistle                 ,   //  216;191;216     // 0x00D8BFD8
			thistle1                ,   //  255;225;255     // 0x00FFE1FF
			thistle2                ,   //  238;210;238     // 0x00EED2EE
			thistle3                ,   //  205;181;205     // 0x00CDB5CD
			thistle4                ,   //  139;123;139     // 0x008B7B8B
			violet                  ,   //  238;130;238     // 0x00EE82EE

			//shades of white
			//color name r/g/b hex bg/fg color sample
			antiquewhite            ,   //  250;235;215     // 0x00FAEBD7
			antiquewhite1           ,   //  255;239;219     // 0x00FFEFDB
			antiquewhite2           ,   //  238;223;204     // 0x00EEDFCC
			antiquewhite3           ,   //  205;192;176     // 0x00CDC0B0
			antiquewhite4           ,   //  139;131;120     // 0x008B8378
			floralwhite             ,   //  255;250;240     // 0x00FFFAF0
			ghostwhite              ,   //  248;248;255     // 0x00F8F8FF
			navajowhite             ,   //  255;222;173     // 0x00FFDEAD
			navajowhite1            ,   //  255;222;173     // 0x00FFDEAD
			navajowhite2            ,   //  238;207;161     // 0x00EECFA1
			navajowhite3            ,   //  205;179;139     // 0x00CDB38B
			navajowhite4            ,   //  139;121;94      // 0x008B795E
			oldlace                 ,   //  253;245;230     // 0x00FDF5E6
			whitesmoke              ,   //  245;245;245     // 0x00F5F5F5
			gainsboro               ,   //  220;220;220     // 0x00DCDCDC
			ivory                   ,   //  255;255;240     // 0x00FFFFF0
			ivory1                  ,   //  255;255;240     // 0x00FFFFF0
			ivory2                  ,   //  238;238;224     // 0x00EEEEE0
			ivory3                  ,   //  205;205;193     // 0x00CDCDC1
			ivory4                  ,   //  139;139;131     // 0x008B8B83
			linen                   ,   //  250;240;230     // 0x00FAF0E6
			seashell                ,   //  255;245;238     // 0x00FFF5EE
			seashell1               ,   //  255;245;238     // 0x00FFF5EE
			seashell2               ,   //  238;229;222     // 0x00EEE5DE
			seashell3               ,   //  205;197;191     // 0x00CDC5BF
			seashell4               ,   //  139;134;130     // 0x008B8682
			snow                    ,   //  255;250;250     // 0x00FFFAFA
			snow1                   ,   //  255;250;250     // 0x00FFFAFA
			snow2                   ,   //  238;233;233     // 0x00EEE9E9
			snow3                   ,   //  205;201;201     // 0x00CDC9C9
			snow4                   ,   //  139;137;137     // 0x008B8989
			wheat                   ,   //  245;222;179     // 0x00F5DEB3
			wheat1                  ,   //  255;231;186     // 0x00FFE7BA
			wheat2                  ,   //  238;216;174     // 0x00EED8AE
			wheat3                  ,   //  205;186;150     // 0x00CDBA96
			wheat4                  ,   //  139;126;102     // 0x008B7E66
			white                   ,   //  255;255;255     // 0x00FFFFFF

			//shades of yellow
			//color name r/g/b hex bg/fg color sample
			blanchedalmond          ,   //  255;235;205     // 0x00FFEBCD
			darkgoldenrod           ,   //  184;134;11      // 0x00B8860B
			darkgoldenrod1          ,   //  255;185;15      // 0x00FFB90F
			darkgoldenrod2          ,   //  238;173;14      // 0x00EEAD0E
			darkgoldenrod3          ,   //  205;149;12      // 0x00CD950C
			darkgoldenrod4          ,   //  139;101;8       // 0x008B6508
			lemonchiffon            ,   //  255;250;205     // 0x00FFFACD
			lemonchiffon1           ,   //  255;250;205     // 0x00FFFACD
			lemonchiffon2           ,   //  238;233;191     // 0x00EEE9BF
			lemonchiffon3           ,   //  205;201;165     // 0x00CDC9A5
			lemonchiffon4           ,   //  139;137;112     // 0x008B8970
			lightgoldenrod          ,   //  238;221;130     // 0x00EEDD82
			lightgoldenrod1         ,   //  255;236;139     // 0x00FFEC8B
			lightgoldenrod2         ,   //  238;220;130     // 0x00EEDC82
			lightgoldenrod3         ,   //  205;190;112     // 0x00CDBE70
			lightgoldenrod4         ,   //  139;129;76      // 0x008B814C
			lightgoldenrodyellow    ,   //  250;250;210     // 0x00FAFAD2
			lightyellow             ,   //  255;255;224     // 0x00FFFFE0
			lightyellow1            ,   //  255;255;224     // 0x00FFFFE0
			lightyellow2            ,   //  238;238;209     // 0x00EEEED1
			lightyellow3            ,   //  205;205;180     // 0x00CDCDB4
			lightyellow4            ,   //  139;139;122     // 0x008B8B7A
			palegoldenrod           ,   //  238;232;170     // 0x00EEE8AA
			papayawhip              ,   //  255;239;213     // 0x00FFEFD5
			cornsilk                ,   //  255;248;220     // 0x00FFF8DC
			cornsilk1               ,   //  255;248;220     // 0x00FFF8DC
			cornsilk2               ,   //  238;232;205     // 0x00EEE8CD
			cornsilk3               ,   //  205;200;177     // 0x00CDC8B1
			cornsilk4               ,   //  139;136;120     // 0x008B8878
			gold                    ,   //  255;215;0       // 0x00FFD700
			gold1                   ,   //  255;215;0       // 0x00FFD700
			gold2                   ,   //  238;201;0       // 0x00EEC900
			gold3                   ,   //  205;173;0       // 0x00CDAD00
			gold4                   ,   //  139;117;0       // 0x008B7500
			goldenrod               ,   //  218;165;32      // 0x00DAA520
			goldenrod1              ,   //  255;193;37      // 0x00FFC125
			goldenrod2              ,   //  238;180;34      // 0x00EEB422
			goldenrod3              ,   //  205;155;29      // 0x00CD9B1D
			goldenrod4              ,   //  139;105;20      // 0x008B6914
			moccasin                ,   //  255;228;181     // 0x00FFE4B5
			yellow                  ,   //  255;255;0       // 0x00FFFF00
			yellow1                 ,   //  255;255;0       // 0x00FFFF00
			yellow2                 ,   //  238;238;0       // 0x00EEEE00
			yellow3                 ,   //  205;205;0       // 0x00CDCD00
			yellow4                 ,   //  139;139;0       // 0x008B8B00

			//metal rgb according to netscape
			//color name r/g/b hex bg/fg color sample
			copper                  ,   //  184;115;51      // 0x00B87333
			gold                    ,   //  205;127;50      // 0x00CD7F32
			silver                  ,   //  230;232;250     // 0x00E6E8FA

	#else
			// short list ( 138 names )

			black = 0            ,  //  = "black";                  // 0x00000000
			dimgray              ,  //  = "dimgray";                // 0x00696969
			gray                 ,  //  = "gray";                   // 0x00808080
			darkgray             ,  //  = "darkgray";               // 0x00A9A9A9
			silver               ,  //  = "silver";                 // 0x00C0C0C0
			lightgray            ,  //  = "lightgray";              // 0x00D3D3D3
			gainsboro            ,  //  = "gainsboro";              // 0x00DCDCDC
			whitesmoke           ,  //  = "whitesmoke";             // 0x00F5F5F5
			white                ,  //  = "white";                  // 0x00FFFFFF
			snow                 ,  //  = "snow";                   // 0x00FFFAFA
			rosybrown            ,  //  = "rosybrown";              // 0x00BC8F8F
			lightcoral           ,  //  = "lightcoral";             // 0x00F08080
			indianred            ,  //  = "indianred";              // 0x00CD5C5C
			brown                ,  //  = "brown";                  // 0x00A52A2A
			firebrick            ,  //  = "firebrick";              // 0x00B22222
			maroon               ,  //  = "maroon";                 // 0x00800000
			darkred              ,  //  = "darkred";                // 0x008B0000
			red                  ,  //  = "red";                    // 0x00FF0000
			mistyrose            ,  //  = "mistyrose";              // 0x00FFE4E1
			salmon               ,  //  = "salmon";                 // 0x00FA8072
			tomato               ,  //  = "tomato";                 // 0x00FF6347
			darksalmon           ,  //  = "darksalmon";             // 0x00E9967A
			coral                ,  //  = "coral";                  // 0x00FF7F50
			orangered            ,  //  = "orangered";              // 0x00FF4500
			lightsalmon          ,  //  = "lightsalmon";            // 0x00FFA07A
			sienna               ,  //  = "sienna";                 // 0x00A0522D
			seashell             ,  //  = "seashell";               // 0x00FFF5EE
			saddlebrown          ,  //  = "saddlebrown";            // 0x008B4513
			chocolate            ,  //  = "chocolate";              // 0x00D2691E
			sandybrown           ,  //  = "sandybrown";             // 0x00F4A460
			peachpuff            ,  //  = "peachpuff";              // 0x00FFDAB9
			linen                ,  //  = "linen";                  // 0x00FAF0E6
			peru                 ,  //  = "peru";                   // 0x00CD853F
			bisque               ,  //  = "bisque";                 // 0x00FFE4C4
			burlywood            ,  //  = "burlywood";              // 0x00DEB887
			darkorange           ,  //  = "darkorange";             // 0x00FF8C00
			antiquewhite         ,  //  = "antiquewhite";           // 0x00FAEBD7
			tan                  ,  //  = "tan";                    // 0x00D2B48C
			blanchedalmond       ,  //  = "blanchedalmond";         // 0x00FFEBCD
			navajowhite          ,  //  = "navajowhite";            // 0x00FFDEAD
			papayawhip           ,  //  = "papayawhip";             // 0x00FFEFD5
			moccasin             ,  //  = "moccasin";               // 0x00FFE4B5
			oldlace              ,  //  = "oldlace";                // 0x00FDF5E6
			wheat                ,  //  = "wheat";                  // 0x00F5DEB3
			floralwhite          ,  //  = "floralwhite";            // 0x00FFFAF0
			orange               ,  //  = "orange";                 // 0x00FFA500
			darkgoldenrod        ,  //  = "darkgoldenrod";          // 0x00B8860B
			goldenrod            ,  //  = "goldenrod";              // 0x00DAA520
			cornsilk             ,  //  = "cornsilk";               // 0x00FFF8DC
			gold                 ,  //  = "gold";                   // 0x00FFD700
			lemonchiffon         ,  //  = "lemonchiffon";           // 0x00FFFACD
			khaki                ,  //  = "khaki";                  // 0x00F0E68C
			palegoldenrod        ,  //  = "palegoldenrod";          // 0x00EEE8AA
			darkkhaki            ,  //  = "darkkhaki";              // 0x00BDB76B
			ivory                ,  //  = "ivory";                  // 0x00FFFFF0
			beige                ,  //  = "beige";                  // 0x00F5F5DC
			lightyellow          ,  //  = "lightyellow";            // 0x00FFFFE0
			lightgoldenrodyellow ,  //  = "lightgoldenrodyellow";   // 0x00FAFAD2
			olive                ,  //  = "olive";                  // 0x00808000
			yellow               ,  //  = "yellow";                 // 0x00FFFF00
			olivedrab            ,  //  = "olivedrab";              // 0x006B8E23
			yellowgreen          ,  //  = "yellowgreen";            // 0x009ACD32
			darkolivegreen       ,  //  = "darkolivegreen";         // 0x00556B2F
			greenyellow          ,  //  = "greenyellow";            // 0x00ADFF2F
			chartreuse           ,  //  = "chartreuse";             // 0x007FFF00
			lawngreen            ,  //  = "lawngreen";              // 0x007CFC00
			honeydew             ,  //  = "honeydew";               // 0x00F0FFF0
			darkseagreen         ,  //  = "darkseagreen";           // 0x008FBC8B
			lightgreen           ,  //  = "lightgreen";             // 0x0090EE90
			palegreen            ,  //  = "palegreen";              // 0x0098FB98
			forestgreen          ,  //  = "forestgreen";            // 0x00228B22
			limegreen            ,  //  = "limegreen";              // 0x0032CD32
			darkgreen            ,  //  = "darkgreen";              // 0x00006400
			green                ,  //  = "green";                  // 0x00008000
			lime                 ,  //  = "lime";                   // 0x0000FF00
			seagreen             ,  //  = "seagreen";               // 0x002E8B57
			mediumseagreen       ,  //  = "mediumseagreen";         // 0x003CB371
			mintcream            ,  //  = "mintcream";              // 0x00F5FFFA
			springgreen          ,  //  = "springgreen";            // 0x0000FF7F
			mediumspringgreen    ,  //  = "mediumspringgreen";      // 0x0000FA9A
			mediumaquamarine     ,  //  = "mediumaquamarine";       // 0x0066CDAA
			aquamarine           ,  //  = "aquamarine";             // 0x007FFFD4
			darkturquoise        ,  //  = "darkturquoise";          // 0x0000CED1   // right place ?
			turquoise            ,  //  = "turquoise";              // 0x0040E0D0
			lightseagreen        ,  //  = "lightseagreen";          // 0x0020B2AA
			mediumturquoise      ,  //  = "mediumturquoise";        // 0x0048D1CC
			azure                ,  //  = "azure";                  // 0x00F0FFFF
			lightcyan            ,  //  = "lightcyan";              // 0x00E0FFFF
			paleturquoise        ,  //  = "paleturquoise";          // 0x00AFEEEE
			darkslategray        ,  //  = "darkslategray";          // 0x002F4F4F
			teal                 ,  //  = "teal";                   // 0x00008080
			darkcyan             ,  //  = "darkcyan";               // 0x00008B8B
			cyan                 ,  //  = "cyan";                   // 0x0000FFFF
			cadetblue            ,  //  = "cadetblue";              // 0x005F9EA0
			powderblue           ,  //  = "powderblue";             // 0x00B0E0E6
			lightblue            ,  //  = "lightblue";              // 0x00ADD8E6
			deepskyblue          ,  //  = "deepskyblue";            // 0x0000BFFF
			skyblue              ,  //  = "skyblue";                // 0x0087CEEB
			lightskyblue         ,  //  = "lightskyblue";           // 0x0087CEFA
			aliceblue            ,  //  = "aliceblue";              // 0x00F0F8FF
			steelblue            ,  //  = "steelblue";              // 0x004682B4
			slategray            ,  //  = "slategray";              // 0x00708090
			lightslategray       ,  //  = "lightslategray";         // 0x00778899
			dodgerblue           ,  //  = "dodgerblue";             // 0x001E90FF
			lightsteelblue       ,  //  = "lightsteelblue";         // 0x00B0C4DE
			cornflowerblue       ,  //  = "cornflowerblue";         // 0x006495ED
			royalblue            ,  //  = "royalblue";              // 0x004169E1
			ghostwhite           ,  //  = "ghostwhite";             // 0x00F8F8FF
			lavender             ,  //  = "lavender";               // 0x00E6E6FA
			midnightblue         ,  //  = "midnightblue";           // 0x00191970
			navy                 ,  //  = "navy";                   // 0x00000080
			darkblue             ,  //  = "darkblue";               // 0x0000008B
			mediumblue           ,  //  = "mediumblue";             // 0x000000CD
			blue                 ,  //  = "blue";                   // 0x000000FF
			slateblue            ,  //  = "slateblue";              // 0x006A5ACD
			darkslateblue        ,  //  = "darkslateblue";          // 0x00483D8B
			mediumslateblue      ,  //  = "mediumslateblue";        // 0x007B68EE
			mediumpurple         ,  //  = "mediumpurple";           // 0x009370DB
			blueviolet           ,  //  = "blueviolet";             // 0x008A2BE2
			indigo               ,  //  = "indigo";                 // 0x004B0082
			darkorchid           ,  //  = "darkorchid";             // 0x009932CC
			darkviolet           ,  //  = "darkviolet";             // 0x009400D3
			mediumorchid         ,  //  = "mediumorchid";           // 0x00BA55D3
			thistle              ,  //  = "thistle";                // 0x00D8BFD8
			plum                 ,  //  = "plum";                   // 0x00DDA0DD
			violet               ,  //  = "violet";                 // 0x00EE82EE
			purple               ,  //  = "purple";                 // 0x00800080
			darkmagenta          ,  //  = "darkmagenta";            // 0x008B008B
			magenta              ,  //  = "magenta";                // 0x00FF00FF
			orchid               ,  //  = "orchid";                 // 0x00DA70D6
			mediumvioletred      ,  //  = "mediumvioletred";        // 0x00C71585
			deeppink             ,  //  = "deeppink";               // 0x00FF1493
			hotpink              ,  //  = "hotpink";                // 0x00FF69B4
			lavenderblush        ,  //  = "lavenderblush";          // 0x00FFF0F5
			palevioletred        ,  //  = "palevioletred";          // 0x00DB7093
			pink                 ,  //  = "pink";                   // 0x00FFC0CB
			crimson              ,  //  = "crimson";                // 0x00DC143C
			lightpink            ,  //  = "lightpink";              // 0x00FFB6C1
	#endif  // VCF_LARGE_COLOR_LIST

		/**
		double colornames
		*/
		aqua                 ,  //  = "aqua";           // 0x0000FFFF = cyan
		fuchsia              ,  //  = "fuchsia";        // 0x00FF00FF = magenta

		/**
		useful tags
		*/
		transparent          ,  //  = "transparent";    // 0xFF000000
		defaultcolor         ,  //  = "default";        // 0x02000000 ( appears as black )
		unknown              ,  //  = "unknown";        // 0x01000000 ( appears as black )
	};

	enum {
		/**
		take the last item from the ColorID enumeration and add 1
		to indicate the number of unique color names
		*/
		uniqueColorFirst = black,
		uniqueColorLast = lightpink,
		numUniqueColorNames = uniqueColorLast +1,
		numColorNames = unknown +1,
	};

	static String at( ColorID colorID );

	static Enumerator<String>* getColorIDs();

	static String unknownColorName();

protected:
	static String unknownColorName_;
	static std::map<ColorID, String> nameMap;
	static EnumeratorMapContainer<std::map<ColorID, String>, String > nameMapContainer;

	/**
	GraphicsToolkit will have this as a member variable, which will
	construct an instance of this, and in turn initialize all the colors
	*/
	friend class GraphicsToolkit;

	/**
	protected because we don't want people to create instances of this
	The constructor will initialize the nameMap with all the correct color strings
	*/
	ColorNames();

	/**
	made non virtual because we don't want people to derive from this either
	*/
	~ColorNames() {}
};








///////////////////////////////////////////////////////////////////////////////
// class ColorSpace

/**
inline implementation for ColorSpace class
*/

// the RGB-Color conversion pair
inline Color ColorSpace::RGBToColor (const ColorSpace::RGBtype& rgb) {
	Color color;
	color.r_ = rgb.R;
	color.g_ = rgb.G;
	color.b_ = rgb.B;
	return color;
}

inline ColorSpace::RGBtype ColorSpace::ColorToRGB (const Color& color) {
	RGBtype rgb;
	rgb.R = color.r_;
	rgb.G = color.g_;
	rgb.B = color.b_;
	return rgb;
}

inline ulong32 ColorSpace::ColorToColorLong (const Color& color) {
	RGBtype rgb = ColorSpace::ColorToRGB ( color );
	return ColorSpace::RGBToColorLong ( rgb );
}


// the HSV-Color conversion pair
inline Color ColorSpace::HSVToColor (const HSVtype& hsv) {
	RGBtype rgb = ColorSpace::HSVToRGB (hsv);
	return ColorSpace::RGBToColor( rgb );
}

inline ColorSpace::HSVtype ColorSpace::ColorToHSV(const Color& color) {
	ColorSpace::RGBtype rgb = ColorSpace::ColorToRGB( color );
	return ColorSpace::RGBToHSV ( rgb );
}

// the HSL-Color conversion Pair
inline Color ColorSpace::HSLToColor (const HSLtype& hsl) {
	ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB (hsl);
	return ColorSpace::RGBToColor( rgb );
}

inline ColorSpace::HSLtype ColorSpace::ColorToHSL(const Color& color) {
	RGBtype rgb = ColorSpace::ColorToRGB( color );
	return ColorSpace::RGBToHSL ( rgb );
}

// the HWB-Color conversion Pair
inline Color ColorSpace::HWBToColor (const HWBtype& hsl) {
	RGBtype rgb = ColorSpace::HWBToRGB (hsl);
	return ColorSpace::RGBToColor( rgb );
}

inline ColorSpace::HWBtype ColorSpace::ColorToHWB(const Color& color) {
	RGBtype rgb = ColorSpace::ColorToRGB( color );
	return ColorSpace::RGBToHWB ( rgb );
}

//////////////////////////////
// saturation ( ColorSpace )

inline ColorSpace::HSVtype ColorSpace::changeHSV ( const HSVtype& hsv, const double& percentH, const double& percentS, const double& percentV ) {
	HSVtype _hsv = hsv;
	ColorSpace::changeHSV ( _hsv, percentH, percentS, percentV );
	return _hsv;
}

inline ColorSpace::HSLtype ColorSpace::changeHSL ( const HSLtype& hsl, const double& percentH, const double& percentS, const double& percentL ) {
	HSLtype _hsl = hsl;
	ColorSpace::changeHSL ( _hsl, percentH, percentS, percentL );
	return _hsl;
}

inline ColorSpace::HWBtype ColorSpace::changeHWB ( const HWBtype& hwb, const double& percentH, const double& percentW, const double& percentB ) {
	HWBtype _hwb = hwb;
	ColorSpace::changeHWB ( _hwb, percentH, percentW, percentB );
	return _hwb;
}

//////////////////////////////
// saturation ( Color )

inline Color ColorSpace::changeHSV ( const Color& color, const double& percentH, const double& percentS, const double& percentV ) {
	HSVtype _hsv = ColorSpace::ColorToHSV( color );
	ColorSpace::changeHSV ( _hsv, percentH, percentS, percentV );
	return HSVToColor ( _hsv );
}

inline Color ColorSpace::changeHSL ( const Color& color, const double& percentH, const double& percentS, const double& percentL ) {
	HSLtype _hsl = ColorSpace::ColorToHSL( color );
	ColorSpace::changeHSL ( _hsl, percentH, percentS, percentL );
	return ColorSpace::HSLToColor ( _hsl );
}

inline Color ColorSpace::changeHWB ( const Color& color, const double& percentH, const double& percentW, const double& percentB ) {
	HWBtype _hwb = ColorSpace::ColorToHWB( color );
	ColorSpace::changeHWB ( _hwb, percentH, percentW, percentB );
	return ColorSpace::HWBToColor ( _hwb );
}

//////////////////////////////
// Hue

inline ColorSpace::HSLtype ColorSpace::changeHue( const HSLtype& hsl, const double& deltaH ) {
	HSLtype _hsl = hsl;
	ColorSpace::changeHue( _hsl, deltaH );
	return _hsl;
}

inline Color ColorSpace::changeHue ( const Color& color, const double& deltaH ) {
	HSLtype hsl = ColorSpace::ColorToHSL(color);
	ColorSpace::changeHue( hsl, deltaH );
	return ColorSpace::HSLToColor( hsl );
}

inline ColorSpace::RGBtype ColorSpace::changeHue( const RGBtype& color, const double& deltaH ) {
	HSLtype hsl = ColorSpace::RGBToHSL(color);

	ColorSpace::changeHue( hsl, deltaH );
	RGBtype clr = ColorSpace::HSLToRGB( hsl );

	return clr;
}

inline ulong32 ColorSpace::changeHue( const ulong32& color, const double& deltaH ) {
	RGBtype rgb = ColorSpace::ColorLongToRGB(color);

	HSLtype hsl = ColorSpace::RGBToHSL(rgb);
	ColorSpace::changeHue( hsl, deltaH );

	rgb = ColorSpace::HSLToRGB(hsl);
	ulong32 color2 = ColorSpace::RGBToColorLong (rgb);

	return color2;
}



}; // namespace VCF


#endif // _VCF_COLOR_H__

/**
$Id$
*/
