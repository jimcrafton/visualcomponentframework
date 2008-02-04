//GraphicsKitRTTI.inl

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

_class_rtti_(Color, "VCF::Object", COLOR_CLASSID)
_property_( double, "red", getRed, setRed, "The red component of the color, valid values are between 0.0 and 1.0." )
_property_( double, "green", getGreen, setGreen, "The green component of the color, valid values are between 0.0 and 1.0." )
_property_( double, "blue", getBlue, setBlue, "The blue component of the color, valid values are between 0.0 and 1.0." )
_class_rtti_end_


_class_rtti_(Size, "VCF::Object", SIZE_CLASSID)
_property_( double, "width", getWidth, setWidth, "The width component." )
_property_( double, "height", getHeight, setHeight, "The height component." )
_class_rtti_end_

_class_rtti_(Point, "VCF::Object", POINT_CLASSID)
_property_( double, "x", getX, setX, "The x component." )
_property_( double, "y", getY, setY, "The y component." )
_class_rtti_end_


_class_rtti_(Rect, "VCF::Object", RECT_CLASSID)
_property_( double, "left", _getLeft, setLeft, "The rectangle's left value." );
_property_( double, "top", _getTop, setTop, "The rectangle's top value." )
_property_( double, "right", _getRight, setRight, "The rectangle's right value." )
_property_( double, "bottom", _getBottom, setBottom, "The rectangle's bottom value." )
_property_ro_( double, "width", _getWidth, "The width of the rectangle as the absolute value between the left and right values." )
_property_ro_( double, "height", _getHeight, "The height of the rectangle as the absolute value between the top and bottom values." )
_class_rtti_end_




_class_rtti_(Font, "VCF::Object", FONT_CLASSID)
_property_( String, "name", getName, setName, "The font's family name like \"Arial\" or \"Times New Roman\"." )
_property_( bool, "bold", getBold, setBold, "Indicates whether or not the font is bold or not." )
_property_( bool, "italic", getItalic, setItalic, "Indicates whether or not the font is italic or not." )
_property_( bool, "underlined", getUnderlined, setUnderlined, "Indicates whether or not the font is underlined or not." )
_property_( bool, "strikeout", getStrikeOut, setStrikeOut, "Indicates whether or not the font is struckout or not." )
_property_( double, "pointSize", getPointSize, setPointSize, "The font's Point size. Takes into consideration the current graphics devices DPI." )
_property_object_( Color, "color", getColor, setColor, "The font's color." );
_class_rtti_end_



//_class_rtti_(ImageBits, "VCF::Object", IMAGEBITS_CLASSID)
//_class_rtti_end_






};


/**
$Id$
*/
