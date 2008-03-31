//Font.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/GraphicsKit/GraphicsKit.h"


using namespace VCF;

Font::Font():
	peer_(NULL),
	locale_(NULL),
	context_(NULL)
{
	peer_ = GraphicsToolkit::createFontPeer( "" );
	if ( NULL == peer_ ){
		throw InvalidPeer( MAKE_ERROR_MSG(NO_PEER), __LINE__ );
	}

	peer_->setFont( this );
}

Font::Font( const String& fontName ):
	peer_(NULL),
	locale_(NULL),
	context_(NULL)
{
	peer_ = GraphicsToolkit::createFontPeer( fontName );
	if ( NULL == peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	peer_->setFont( this );
}

Font::Font( const String& fontName, const double& pointSize ):
	peer_(NULL),
	locale_(NULL),
	context_(NULL)
{

	peer_ = GraphicsToolkit::createFontPeer( fontName, pointSize );
	if ( NULL == peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	peer_->setFont( this );
}

Font::Font( const Font& font ):
    Object( font ),
	peer_(NULL),
	locale_(NULL),
	context_(NULL)
{
	peer_ = GraphicsToolkit::createFontPeer( font.getName() );
	if ( NULL == peer_ ){
		throw InvalidPeer(MAKE_ERROR_MSG(NO_PEER), __LINE__);
	}

	peer_->setFont( this );

	*this = font;
}

Font::~Font()
{
	delete peer_;
}


Font& Font::operator= (const Font& rhs )
{
	setAttributes( rhs.getPointSize(), rhs.getBold(), rhs.getItalic(), rhs.getUnderlined(),
					rhs.getStrikeOut(), &rhs.color_, rhs.getName() );

	locale_ = rhs.locale_;
	context_ = rhs.context_;
	return *this;
}

void Font::setLocale( Locale* locale )
{
	locale_ = locale;
	peer_->updateLocaleSettings();

	changed( Font::fcFontLocale );
}

bool Font::isTrueType()  const

{
	return peer_->isTrueType();
}

Color* Font::getColor()
{
	return &color_;
}

void Font::setColor( Color* color )
{
	if ( NULL != color ) {
		color_ = *color;
		changed( Font::fcFontColor );
	}
}

double Font::getPointSize()  const
{
	return peer_->getPointSize();
}

void Font::setPointSize( const double& pointSize )
{
	peer_->setPointSize( pointSize );
	changed( Font::fcFontSize );
}

double Font::getPixelSize()  const
{
	return peer_->getPixelSize();
}

void Font::setPixelSize( const double& pixelSize )
{
	peer_->setPixelSize( pixelSize );
	changed( Font::fcFontSize );
}

void Font::setBold( const bool& bold )
{
	peer_->setBold( bold );
	changed( Font::fcFontBold );
}

bool Font::getBold()  const
{
	return peer_->getBold();
}

bool Font::getItalic()  const
{
	return peer_->getItalic();
}

void Font::setItalic( const bool& italic )
{
	peer_->setItalic( italic );
	changed( Font::fcFontItalic );
}

bool Font::getUnderlined()  const
{
	return peer_->getUnderlined();
}

void Font::setUnderlined( const bool& underlined )
{
	peer_->setUnderlined( underlined );
	changed( Font::fcFontUnderline );
}

bool Font::getStrikeOut()  const
{
	return peer_->getStrikeOut();
}

void Font::setStrikeOut( const bool& strikeout )
{
	peer_->setStrikeOut( strikeout );
	changed( Font::fcFontStrikeOut );
}


FontPeer* Font::getFontPeer()
{
	return peer_;
}

String Font::getName()  const
{
	return peer_->getName();
}

void Font::setName( const String& name )
{
	peer_->setName( name );
	changed( Font::fcFontName );
}

void Font::copy( Object* source )
{
	if ( NULL != source ){
		Font* srcFont = dynamic_cast<Font*>( source );
		if ( NULL != srcFont ){
			*this = *srcFont;
		}
	}
}

double Font::getAscent()  const
{
	return peer_->getAscent();
}

double Font::getDescent()  const
{
	return peer_->getDescent();
}

double Font::getHeight()  const
{
	return peer_->getAscent() + peer_->getDescent();
}

bool Font::isFixedPitch() const 
{
	return peer_->isFixedPitch();
}

void Font::setAttributes( const double& pointSize, const bool& bold, const bool& italic,
								const bool& underlined, const bool& struckOut, const Color* color, const String& name )
{

	peer_->setAttributes( pointSize, bold, italic, underlined, struckOut, name );
	if ( NULL != color ) {
		color_ = *color;
	}

	changed( Font::fcAll );
}

void Font::changed( int eventType )
{
	Event e(this, eventType);
	FontChanged( &e );
}


uint64 Font::sizeOf() const
{
	uint64 result = sizeof(Font);

	return result;
}

double Font::getTextWidth( const String& text )
{
	return peer_->getTextSize(text).width_;
}

double Font::getTextHeight( const String& text )
{
	return peer_->getTextSize(text).height_;
}

/**
$Id$
*/
