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
ColorSpace
class managing all the color transformations between different color spaces

<p>ColorSpace interface
 <p>Hue Luminosity management
	<p>WebPage: <br>
			http:www.acm.org/jgt/papers/SmithLyons96/  <br>
			http:www.scottandmichelle.net/scott/code/index2.mv?codenum=045<br>
			(google search advanced all words: hue saturation source code)<br>

<p>Author: <br>
				Alvy Ray Smith <br>
				Microsoft <br>
				Redmond, Washington <br>
				alvys@microsoft.com <br>
				Eric Ray Lyons <br>
				Mill Valley, California <br>
				lyons@nbn.com <br>

<p>Abstract:
	The two most common color selector models, other than RGB (Red-Green-Blue),
	are the hue-based HSV (Hue-Saturation-Value) and HSL (Hue-Saturation-Lightness) color models.
	It is shown that both of these models are flawed.
	A closely related model, HWB (Hue-Whiteness-Blackness), is introduced that avoids the flaws,
	is slightly faster to compute, and is very easy to teach to new users:
	Choose a hue. Lighten it with white. Darken it with black.
	We explain that lightening is not the opposite of darkening.

<p>Modified, with some fixes, by Marcello Pietrobon
<p>Modified, by Jim Crafton, fixed some errors due to inclusion of Win32 types
*/
class GRAPHICSKIT_API ColorSpace {
public:
	#define HUECRITICALMAX	( 1.0 - 1.0 / 6.0 )	// max r/g/b value is 255
	#define RGBMAX			255					// max r/g/b value is 255
	#define HSLMAX			240					// This is what Windows' Display Properties uses: it is not too much important an exact value: see how GetLuminosity() is used for.

	/**
	 Theoretically, hue 0 (pure red) is identical to hue 6 in these transforms. Pure
	 red always maps to 6 in this implementation. Therefore UNDEFINED can be
	 defined as 0 in situations where only unsigned numbers are desired.
	 */
	#define HUE_UNDEFINED	-1
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


	static const double HueCriticalMax;	// = ( 1.0 - 1.0 / 6.0 )	- Hue > HueCriticalMax => rgb.R > 1;
	//Used by GetLuminosity()
	static const int	RGBMax;			// This is what Windows in the Display Properties dialog uses in the ColorPicker tool.
	static const int	HSLMax;			// max r/g/b value is 255 in Windows

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


	/**
	compute the luminosity for an RGB color.
	@param color
	@return int
	*/
	static int getLuminosity( const Color& color );

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

	// suggested with colors: 0.0/ 0.0 / 0.71428571428571
	// suggested with grays:  0.0/ 0.0 / 0.33333333333333
	static void changeHSV ( HSVtype& hsv, const double& percentH, const double& percentS, const double& percentV );

	// suggested with colors: 0.0/ 0.0 / -0.71428571428571
	// suggested with grays:  0.0/ 0.0 / -0.33333333333333
	static void changeHSL ( HSLtype& hls, const double& percentH, const double& percentS, const double& percentL );

	// suggested with colors: 0.0/ 0.0 / 0.71428571428571
	// suggested with grays:  0.0/ 0.0 / 0.33333333333333
	static void changeHWB ( HWBtype& hls, const double& percentH, const double& percentW, const double& percentB );

	static HSVtype changeHSV ( const HSVtype& hsv, const double& percentH, const double& percentS, const double& percentV );
	static HSLtype changeHSL ( const HSLtype& hsl, const double& percentH, const double& percentS, const double& percentL );
	static HWBtype changeHWB ( const HWBtype& hwb, const double& percentH, const double& percentW, const double& percentB );

	/**
	Example: To draw the Titlebars of a window with a color gradient do the following:
	<pre>
		Color color_right = color;

		// enabled window (color)
		Color color_left = changeHSL( color_right, 0.0, 0.0, -0.71428571428571 );

		// disable window (gray)
		Color color_left = changeHSL( color_right, 0.0, 0.0, -0.33333333333333 );
		drawGradientBackground(pc, color_left, color_right);
	</pre>
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
Color class documentation
*/
class GRAPHICSKIT_API Color : public VCF::Object {

	friend class ColorSpace;
public:


	/**
	this enum defines the way color is stored when compressed into a
	32/64 bit integer value. Sadly not everyone stores this the same way
	so this will indicate how the bits are arranged
	*/
	enum ColorFormat {
		/**
		Alpha value, Red value, Green Value, and Blue value.
		Seen in a 32 bit number as 0xAARRGGBB
		*/
		cfARGB = 0,

		/**
		Alpha value, Blue value, Green Value, and Red value.
		This is the default in Win32 systems
		Seen in a 32 bit number as 0xAABBGGRR
		*/
		cfABGR
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
		ctHLS,

		/**
		Assuming three color values, a, b, and c, which represent
		Hue, Saturation, and Value values respectively, with each value
		bounded by 0.0 to 1.0 inclusive.
		*/
		ctHSV,

		ctYUV,
		ctLab,
		ctCMY
	};

	Color();

	Color( const Color& color );	// copy ctor

	/**
	This will initialize a color based on three double values, the meaning of which
	depends on the type.
	@param ColorType indicates what the val1, val2, and val3 components represent. By default it is
	set to ctRGB, which means that val1, val2, and val3, represent red, green, and blue color values
	*/
	Color( const double & val1, const double & val2, const double & val3, ColorType type= ctRGB );

	Color( const double & c, const double & m, const double & y, const double & k );

	Color( const unsigned char & r, const unsigned char & g, const unsigned char & b );

	Color( const unsigned long & color, ColorFormat cf=cfABGR );

	Color( const String& colorName );

	virtual ~Color(){};

	double getRed() const;

	double getGreen() const;

	double getBlue() const;

	void setRed( const double& red );

	void setGreen( const double& green );

	void setBlue( const double& blue );

	void getRGB(unsigned char & r, unsigned char & g, unsigned char & b) const;
	void getRGB(double & r, double & g, double & b) const;
	unsigned long getRGB( ColorFormat cf=cfABGR ) const;

	void setRGB( const unsigned char & r, const unsigned char & g, const unsigned char & b);
	void setRGB( const double & r, const double & g, const double & b);
	void setRGB( const unsigned long& rgb, ColorFormat cf=cfABGR );

	void getHSV(double & h, double & s, double & v) const;
	void setHSV( const double & h, const double & s, const double & v);

	void getHLS(double & h, double & l, double & s) const;
	void setHLS( const double & h, const double & l, const double & s);

	void getCMYK(double & c, double & m, double & y, double & k) const;
	void setCMYK( const double & c, const double & m, const double & y, const double & k);

	void getLab() const;
	void setLab();

	void getYUV() const;
	void setYUV();

	virtual void copy( const Color* source );

	virtual void copy( const Color& source );

	Color& operator=( const Color* clr ){
		copy( clr );
		return *this;
	};

	Color& operator=( const Color& clr ){
		copy( clr );
		return *this;
	};

	bool operator==( const Color& clr ) const {
		//return (clr.b_ == b_) && (clr.g_ == g_) && (clr.r_ == r_);
		return isEqual( &clr );
	}

	bool operator!=( const Color& clr ) const {
		return ! isEqual( &clr );
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
						(r_ < clr.r_) ? true : false;	// whow !
		#ifdef VCF_DEBUG_COLORS_COMPARISON_OPERATORS
			// this compare is less precise: so we can have rgb1==rgb2
			bool result2 = ( getRGB() < clr.getRGB() ) ;
			unsigned char r, g, b, r2, g2, b2;
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
						(r_ > clr.r_) ? true : false;	// whow !
		#ifdef VCF_DEBUG_COLORS_COMPARISON_OPERATORS
			// this compare is less precise: so we can have rgb1==rgb2
			bool result2 = ( getRGB() > clr.getRGB() ) ;
			unsigned char r, g, b, r2, g2, b2;
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
			result = (color->b_ == b_) && (color->g_ == g_) && (color->r_ == r_);
		}
		return result;
	};

	virtual String toString(){
		char tmp[256];
		memset( tmp, 0, 256 );
		sprintf( tmp, "#%02X%02X%02X", (int)(r_*255.0), (int)(g_*255.0), (int)(b_*255.0) );
		return String(tmp);
	};

	void changeHSV ( const double& percentH, const double& percentS, const double& percentV );

	void changeHSL ( const double& percentH, const double& percentS, const double& percentL );

	void changeHWB ( const double& percentH, const double& percentW, const double& percentB );

	void changeHue ( const double& deltaH );

	/**
	compute the luminosity as an RGB color.
	*/
	int getLuminosity() const ;

	void getInvertedRGB(unsigned char & r, unsigned char & g, unsigned char & b) const;

	void getInvertedRGB(double & r, double & g, double & b) const;

	unsigned long getInvertedRGB( ColorFormat cf=cfABGR ) const;

	void brighter();

	void darker();

	/**
	change the color to its complement
	*/
	void invert();

	/**
	change the color to its complement
	*/
	Color& inverted();

	/**
	calc the complement of the color
	*/
	Color getInverted() const ;

	static Color* getColor( const int& gray );

	static Color* getColor( const String& colorName );

	static Color* getColorMatch( const Color& color );

	static Color getColorContrast( const Color& clrRef, double deltaL = 0.3 );

	static const String getColorNameFromMap( const Color& color );

	static void createColorMap();

	/**
	Helper function: generate a String with the internal representation of the color in hexadecimal format.
	@param bool true if an inverted scheme is desired, as it is in the Intel architecture.
	       Example: the scheme 0x00RRGGBB would appear as BBGGRR00 with Intel architecture.
	*/
	static String Color::getHexCode( const Color& color, const unsigned char & r, const unsigned char & g, const unsigned char & b, const bool& inverted=false );

private:
	double r_;
	double g_;
	double b_;


	/**

	Some notes for the future programmer.

	<p>
	Note: The choice of using the const  qualifier for s_ makes difficult to add a new color
	( it is not a const pointer though ).
	</p>
	<p>
	To check if a color has a name you need to use some constructor.
	</p>
	<p>
	Example:
	<pre>
	Color( (VCF::uchar)r, (VCF::uchar)g, (VCF::uchar)b) )
	</pre>
	</p>

	<p>
	We have some difficulties only if we have to add a new color. And the only way to
	avoid these difficulties is to declare s_ without the 'const' qualifier,
	which would cause worse problems though.
	</p>
	<p>
	Usage : <br>
	To add a new color, check if the color already exists with a name:

	<pre>
	Color cTmp = Color( (String*)NULL, (VCF::uchar)r, (VCF::uchar)g, (VCF::uchar)b) );
	</pre>
	or
	<pre>
	Color cTmp = Color( (String*)NULL, (VCF::uchar)r, (VCF::uchar)g, (VCF::uchar)b) );
	</pre>
	Then:

	<pre>
	String* s = getColorNameFromMap(cTmp);
	if (s == GraphicsToolkit::unknownColorName) {
		//allocate the memory for the colorName, then:
		String* newColorName = new String("newColorName");
		Color color = Color ( newColorName, cTmp );
	} else {
		//Color color = Color ( s, cTmp ); or
		Color color = cTmp;
	}
	</pre>

	Maybe I will think something better if you'll have to continuously add new colors:
	but in this case it is probably better to just use:
	<pre>
	Color cTmp = Color( (String*)NULL, (VCF::uchar)r, (VCF::uchar)g, (VCF::uchar)b) );
	</pre>
	*/

};


///////////////////////////////////////////////////////////////////////////////
// inlines

inline Color::Color() {
	r_ = 0.0;
	g_ = 0.0;
	b_ = 0.0;
}

inline Color::Color( const Color& color ) {
	b_ = color.b_;
	g_ = color.g_;
	r_ = color.r_;
}

inline Color::Color( const double & val1, const double & val2, const double & val3, ColorType type ) {
	switch ( type ) {
		case ctRGB : {
			r_ = val1;
			g_ = val2;
			b_ = val3;
		}
		break;

		case ctHLS : {
			ColorSpace::HSLtype hls;
			hls.H = val1;
			hls.L = val2;
			hls.S = val3;

			ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB( hls );

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
	}
}

inline Color::Color( const double & c, const double & m, const double & y, const double & k ) {
	throw NotImplementedException();
}

inline Color::Color( const unsigned char & r, const unsigned char & g, const unsigned char & b ) {
	r_ = ((double)r) / 255.0;
	g_ = ((double)g) / 255.0;
	b_ = ((double)b) / 255.0;
}

inline Color::Color(const unsigned long & color, ColorFormat cf ) {
	switch ( cf ) {
		case cfARGB : {
			r_ = ((unsigned char*)&color)[2] / 255.0;
			g_ = ((unsigned char*)&color)[1] / 255.0;
			b_ = ((unsigned char*)&color)[0] / 255.0;
		}
		break;

		case cfABGR : {
			r_ = ((unsigned char*)&color)[0] / 255.0;
			g_ = ((unsigned char*)&color)[1] / 255.0;
			b_ = ((unsigned char*)&color)[2] / 255.0;
		}
		break;
	}
}

inline Color::Color( const String& colorName ) {
	( *this ) = (* GraphicsToolkit::getColorFromColormap( colorName ) );
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

inline void Color::setRed( const double& red ) {
	r_ = red;
}

inline void Color::setGreen( const double& green ) {
	g_ = green;
}

inline void Color::setBlue( const double& blue ) {
	b_ = blue;
}

inline void Color::getRGB( unsigned char & r, unsigned char & g, unsigned char & b ) const {
	r = (unsigned char)(r_ * 255 + 0.5);
	g = (unsigned char)(g_ * 255 + 0.5);
	b = (unsigned char)(b_ * 255 + 0.5);
}

inline void Color::getRGB( double & r, double & g, double & b ) const {
	r = r_;
	g = g_;
	b = b_;
}

inline unsigned long Color::getRGB( ColorFormat cf ) const {
	unsigned long rgb = 0;

	switch ( cf ) {
		case cfARGB : {
			((unsigned char*)(&rgb))[2] = (unsigned char)(r_ * 255 + 0.5);
			((unsigned char*)(&rgb))[1] = (unsigned char)(g_ * 255 + 0.5);
			((unsigned char*)(&rgb))[0] = (unsigned char)(b_ * 255 + 0.5);
		}
		break;

		case cfABGR : {
			((unsigned char*)(&rgb))[0] = (unsigned char)(r_ * 255 + 0.5);
			((unsigned char*)(&rgb))[1] = (unsigned char)(g_ * 255 + 0.5);
			((unsigned char*)(&rgb))[2] = (unsigned char)(b_ * 255 + 0.5);
		}
		break;
	}

	return rgb;
}

inline void Color::setRGB( const unsigned char & r, const unsigned char & g, const unsigned char & b ) {
	r_ = ((double)r) / 255.0;
	g_ = ((double)g) / 255.0;
	b_ = ((double)b) / 255.0;
}

inline void Color::setRGB( const double & r, const double & g, const double & b) {
	r_ = r;
	g_ = g;
	b_ = b;
}

inline void Color::setRGB( const unsigned long& rgb, ColorFormat cf ) {
	switch ( cf ) {
		case cfARGB : {
			r_ = ((unsigned char*)&rgb)[2] / 255.0;
			g_ = ((unsigned char*)&rgb)[1] / 255.0;
			b_ = ((unsigned char*)&rgb)[0] / 255.0;
		}
		break;

		case cfABGR : {
			r_ = ((unsigned char*)&rgb)[0] / 255.0;
			g_ = ((unsigned char*)&rgb)[1] / 255.0;
			b_ = ((unsigned char*)&rgb)[2] / 255.0;
		}
		break;
	}
}


inline void Color::getHSV( double & h, double & s, double & v ) const {
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

inline void Color::setHSV( const double & h, const double & s, const double & v ) {
	ColorSpace::HSVtype hsv;
	hsv.H = h;
	hsv.S = s;
	hsv.V = v;

	ColorSpace::RGBtype rgb = ColorSpace::HSVToRGB( hsv );

	r_ = rgb.R;
	g_ = rgb.G;
	b_ = rgb.B;
}

inline void Color::getHLS( double & h, double & l, double & s ) const {
	ColorSpace::HSLtype hls;
	ColorSpace::RGBtype rgb;
	rgb.R = r_;
	rgb.G = g_;
	rgb.B = b_;

	hls = ColorSpace::RGBToHSL( rgb );

	h = hls.H;
	l = hls.L;
	s = hls.S;
}

inline void Color::setHLS( const double & h, const double & l, const double & s ) {
	ColorSpace::HSLtype hls;
	hls.H = h;
	hls.L = l;
	hls.S = s;

	ColorSpace::RGBtype rgb = ColorSpace::HSLToRGB( hls );

	r_ = rgb.R;
	g_ = rgb.G;
	b_ = rgb.B;
}

inline void Color::getCMYK( double & c, double & m, double & y, double & k ) const {
	throw NotImplementedException();
}

inline void Color::setCMYK( const double & c, const double & m, const double & y, const double & k ) {
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


inline void Color::copy( const Color* color ) {
	if ( NULL != color ){
		r_ = color->getRed();
		g_ = color->getGreen();
		b_ = color->getBlue();
	}
}

inline void Color::copy( const Color& color ) {
	r_ = color.getRed();
	g_ = color.getGreen();
	b_ = color.getBlue();
}


inline int Color::getLuminosity() const {
	unsigned char r, g, b;
	getRGB (r, g, b);
	int rgbMax = maxVal<>( maxVal<>(r,g), b);
	int rgbMin = minVal<>( minVal<>(r,g), b);
	return (int) (double) (((rgbMax+rgbMin) * ColorSpace::HSLMax) + ColorSpace::RGBMax ) / (2 * ColorSpace::RGBMax);
}

inline void Color::getInvertedRGB( unsigned char & r, unsigned char & g, unsigned char & b ) const {
	r = (unsigned char)( (1.0 - r_ ) * 255 + 0.5);
	g = (unsigned char)( (1.0 - g_ ) * 255 + 0.5);
	b = (unsigned char)( (1.0 - b_ ) * 255 + 0.5);
}

inline void Color::getInvertedRGB( double & r, double & g, double & b ) const {
	r =  ( 1.0 - r_ );
	g =  ( 1.0 - g_ );
	b =  ( 1.0 - b_ );
}

inline unsigned long Color::getInvertedRGB( ColorFormat cf ) const {
	unsigned long rgb = 0;

	switch ( cf ) {
		case cfARGB : {
			((unsigned char*)(&rgb))[2] = (unsigned char)( (1.0 - r_ ) * 255 + 0.5);
			((unsigned char*)(&rgb))[1] = (unsigned char)( (1.0 - g_ ) * 255 + 0.5);
			((unsigned char*)(&rgb))[0] = (unsigned char)( (1.0 - b_ ) * 255 + 0.5);
		}
		break;

		case cfABGR : {
			((unsigned char*)(&rgb))[0] = (unsigned char)( (1.0 - r_ ) * 255 + 0.5);
			((unsigned char*)(&rgb))[1] = (unsigned char)( (1.0 - g_ ) * 255 + 0.5);
			((unsigned char*)(&rgb))[2] = (unsigned char)( (1.0 - b_ ) * 255 + 0.5);
		}
		break;
	}

	return rgb;
}

inline void Color::brighter() {
	throw NotImplementedException();
}


inline void Color::darker() {
	throw NotImplementedException();
}

inline void Color::invert() {
	// change the color to its complement
	r_ =  ( 1.0 - r_ );
	g_ =  ( 1.0 - g_ );
	b_ =  ( 1.0 - b_ );
}

inline Color Color::getInverted() const {
	// get the complement color
	Color color;
	color.r_ =  ( 1.0 - r_ );
	color.g_ =  ( 1.0 - g_ );
	color.b_ =  ( 1.0 - b_ );

	return color;
}

inline Color* Color::getColor( const int& gray ) {
	return GraphicsToolkit::getColorFromColormap( gray );
}

inline Color* Color::getColor( const String& colorName ) {
	return GraphicsToolkit::getColorFromColormap( colorName );
}

inline Color* Color::getColorMatch( const Color& color ) {
	return GraphicsToolkit::getColorMatchFromColormap( color );
}

inline Color Color::getColorContrast( const Color& clrRef, double deltaL/*=0.3*/ ) {
	return GraphicsToolkit::getColorContrast( clrRef, deltaL );
}

inline const String Color::getColorNameFromMap( const Color& color ) {
	return GraphicsToolkit::getColorNameFromMap( color );
}






///////////////////////////////////////////////////////////////////////////////
// class ColorNames


/**
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

	static String unknownColor();
protected:
	static String unknownColorName;
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

	//made non virtual because we don't want people to derive from this either
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

inline String Color::getHexCode( const Color& color, const unsigned char & r, const unsigned char & g, const unsigned char & b, const bool& inverted/*=false*/ ) {

	// Remark:
	//   scheme: 0x00RRGGBB ( it would appear as BB GG RR 00 with Intel architecture ) so it should be:
	//   code = StringUtils::format( L"%02x%02x%02x", cb, cg, cr ); if we want to see as it would appear with Intel architecture

	String code = "";

	unsigned char cr, cg, cb;
	cr = (unsigned char)(r * 255 + 0.5);
	cg = (unsigned char)(g * 255 + 0.5);
	cb = (unsigned char)(b * 255 + 0.5);

	unsigned long rgb = 0;

	if ( !inverted ) {
		//((unsigned char*)(&rgb))[2] = cr;
		//((unsigned char*)(&rgb))[1] = cg;
		//((unsigned char*)(&rgb))[0] = cb;
		code = StringUtils::format( L"%02X%02X%02X", cr, cg, cb );
	} else {
		//((unsigned char*)(&rgb))[0] = cr;
		//((unsigned char*)(&rgb))[1] = cg;
		//((unsigned char*)(&rgb))[2] = cb;
		code = StringUtils::format( L"%02X%02X%02X", cr, cg, cb );
	}

	return code;
}



}; // namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/12/01 04:31:42  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.3  2004/11/10 19:09:48  marcelloptr
*fixed documentation for doxygen
*
*Revision 1.2.2.2  2004/10/11 12:19:17  marcelloptr
*added missed function
*
*Revision 1.2.2.1  2004/08/27 19:55:45  marcelloptr
*Color changes
*
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.5  2004/06/25 19:52:48  marcelloptr
*adjusted macros and other changes for better performance
*
*Revision 1.1.2.3  2004/06/18 14:38:43  ddiego
*commented out the VCF_DEBUG_COLORS define for Marcello.
*
*Revision 1.1.2.2  2004/04/29 04:10:26  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.15.2.1  2004/04/26 21:58:38  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.15  2004/04/03 15:48:40  ddiego
*Merged over code from the 0-6-3 branch.
*
*Revision 1.14.2.2  2004/03/26 01:38:10  ddiego
*added Marcello's suggestion for the additional VCF_ASSERT
*macro. So we now have one which takes a single parameter, and another
*which takes 2 parameters, the assert condition, and a message.
*
*Revision 1.14.2.1  2004/01/30 22:08:08  ddiego
*more fixes to the table model and table control
*
*Revision 1.14  2003/12/18 05:15:58  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.13.4.3  2003/11/10 01:57:29  ddiego
*add a fromString methods to StingUtils
*added some minor fixes to list box control and added a SelectionChanged
*Delegate to it
*add some minor fixes ot ComboBoxControl
*added an unknownColor() method to ColorNames class
*
*Revision 1.13.4.2  2003/10/28 04:06:11  ddiego
*updated the GraphicsContext and ContextPeer classes to support
*slider control drawing. adjusted the Slider control accordingly.
*Also changed some of the GraphicsKit headers to conform to the
*current header style.
*
*Revision 1.13.4.1  2003/09/12 16:46:33  ddiego
*finished adding header changes to improve compile speed (at least
*with MS VC++) and to get rid of some of the clutter that the RTTI macros
*add.
*But Where'd the RTTI info go!?!?
*Have no fear it's still there! It is now located in three .inl files, one
*for each kit. Each kit will consolidate it's RTTI decls in the following
*files:
*FoundationKit:
*  vcf/include/FoundationKitRTTI.inl
*GraphicsKit:
*  vcf/include/GraphicsKitRTTI.inl
*ApplicationKit:
*  vcf/include/ApplicationKitRTTI.inl
*
*Please alter these files as neeccessary to add/subtract/alter the various
*RTTI info. Each kit is also responsible for registering any of the class
*in the ClassRegistry.
*A side effect of this is that I had to alter the memory allocation for the
*VC6 build for the Application it went from /Zm120 to /Zm150. I find this
*pretty lame but I don't know what else to do. Hopefully this will improve
*compile times when using the Appkit in other programs.
*
*Revision 1.13  2003/05/17 20:37:09  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.12.2.2  2003/03/23 03:23:48  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.12.2.1  2003/03/12 03:10:14  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.12  2003/02/26 04:30:39  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.11.2.8  2003/01/08 04:25:56  marcelloptr
*ColorNames static map and Color::s_ now use String instead than String* - VCF_LARGE_COLOR_LIST introduced
*
*Revision 1.11.2.7  2003/01/08 00:19:44  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.11.2.6  2002/12/31 07:01:28  ddiego
*trying to track issues with parenting in X. Made some fixes in the Color class
*and the ContextPeer class to work in gcc/X
*
*Revision 1.11.2.5  2002/12/30 21:48:00  ddiego
*miscellaneous fixes to the ColorNames class. Adjusted the way it looks up colors
*and got rid of some of the extern variables, also removed the pragma lib in the
*color.cpp file
*
*: ----------------------------------------------------------------------
*
*Revision 1.11.2.4  2002/12/30 03:59:25  ddiego
*more X11 porting code. Now have X11UIToolkit::runEventLoop partially implemented
*Can create and paint in a Window object! Woo hoo!
*Color class is crurently broken on linux, will fix pronto
*
*Revision 1.11.2.3  2002/12/30 00:24:12  ddiego
*made some minor modifications to Marcello's additions to the Color class
*Also modified the Application class to work with hooking OS Native event
*in a more general way.
*
*Revision 1.11.2.2  2002/12/28 22:51:05  marcelloptr
*Color Spaces transformations and Color Names
*
*Revision 1.11.2.1  2002/12/27 23:04:36  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.11  2002/11/18 00:46:08  ddiego
*this is the merge over of all the bug fixes and features (mostly
*VCF Builder stuff) from the devmain-0-5-8 branch
*
*Revision 1.10.4.1  2002/09/28 22:22:35  ddiego
*added some support for font info and determinging the names on the system
*
*Revision 1.10  2002/09/12 03:26:04  ddiego
*merged over the changes from the devmain-0-5-5b branch
*
*Revision 1.9.6.2  2002/08/06 02:57:35  ddiego
*added base X11 files for GraphicsKit and made sure that the GraphicsKit compiles
*under linux (GCC). There is now a new dir under build/xmake called GraphicsKit
*where the xmake build script lives. This checkin also includes the base X11
*include (as part of GraphicsKitPrivate.h), as well as linking to the X11 libs
*
*Revision 1.9.6.1  2002/07/02 05:35:10  marcelloptr
*fixes for vc6, vc7, separated builds, automatic library selection, stlport
*
*Revision 1.9  2002/05/09 03:10:43  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.8.4.1  2002/03/25 04:19:46  ddiego
*fixed some file checking problems in xmake and fixed some general
*code to be able to compile with GCC and Borland C++
*
*Revision 1.8  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COLOR_H__


