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



_class_rtti_(ImageBits, "VCF::Object", IMAGEBITS_CLASSID)
_class_rtti_end_






};


/**
*CVS Log info
*$Log$
*Revision 1.3  2005/07/09 23:05:59  ddiego
*added missing gtk files
*
*Revision 1.2.4.1  2005/03/06 22:51:00  ddiego
*overhaul of RTTI macros. this includes changes to various examples to accommadate the new changes.
*
*Revision 1.2  2004/08/07 02:49:17  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/30 19:17:11  ddiego
*fixed some font issues. got rid of methods that are not implementable on other platforms
*
*Revision 1.1.2.2  2004/04/29 04:10:27  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:40:31  ddiego
*migration towards new directory structure
*
*Revision 1.2  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.1.2.1  2003/09/12 16:46:33  ddiego
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
*/


