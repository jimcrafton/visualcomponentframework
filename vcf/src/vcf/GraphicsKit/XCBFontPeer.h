#ifndef _VCF_XCBFONTPEER_H__
#define _VCF_XCBFONTPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF  {

class XCBFontPeer : public FontPeer {
public:
	XCBFontPeer( const String& fontName );

	XCBFontPeer( const String& fontName, const double& pointSize );

	virtual OSHandleID getFontHandleID();

	virtual String getName();

	virtual void setName( const String& name );

	virtual bool isTrueType();

	virtual double getPointSize();

	virtual void setPointSize( const double pointSize );

	virtual double getPixelSize();

	virtual void setPixelSize( const double pixelSize );

	virtual void setBold( const bool& bold );

	virtual bool getBold();

	virtual bool getItalic();

	virtual void setItalic( const bool& italic );

	virtual bool getUnderlined();

	virtual void setUnderlined( const bool& underlined );

	virtual bool getStrikeOut();

	virtual void setStrikeOut( const bool& strikeout );

	virtual void setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const String& name );

	virtual double getAscent();

	virtual double getDescent();

	virtual bool isFixedPitch();

	virtual void setFont( Font* font );

	String getHashcode();
	
	void internal_setIsTrueTypeFont(bool val) {
		trueTypeFont_ = val;
	}
	
	void internal_setIsFixedPitchFont(bool val) {
		fixedPitchFont_ = val;
	}
	
	void internal_setAscent(double val) {
		ascent_ = val;
	}
	
	void internal_setDescent(double val) {
		descent_ = val;
	}
protected:
	String fontName_;
	bool bold_;
	bool underlined_;
	bool italic_;
	bool strikeOut_;
	double pointSize_;
	bool trueTypeFont_;
	bool fixedPitchFont_;
	double ascent_;
	double descent_;
	
	void settingsChanged();

};

}; //end of namespace VCF

#endif // _VCF_XCBFONTPEER_H__

/**
$Id$
*/

