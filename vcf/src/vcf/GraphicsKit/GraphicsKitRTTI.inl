//GraphicsKitRTTI.inl

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

BEGIN_CLASSINFO(Color, "VCF::Color", "VCF::Object", COLOR_CLASSID)
PROPERTY( double, "red", Color::getRed, Color::setRed, pdDouble )
PROPERTY( double, "green", Color::getGreen, Color::setGreen, pdDouble )
PROPERTY( double, "blue", Color::getBlue, Color::setBlue, pdDouble )
END_CLASSINFO(Color)



BEGIN_CLASSINFO(Rect, "VCF::Rect", "VCF::Object", RECT_CLASSID)
PROPERTY( double, "left", Rect::_getLeft, Rect::setLeft, pdDouble );
PROPERTY( double, "top", Rect::_getTop, Rect::setTop, pdDouble )
PROPERTY( double, "right", Rect::_getRight, Rect::setRight, pdDouble )
PROPERTY( double, "bottom", Rect::_getBottom, Rect::setBottom, pdDouble )
READONLY_PROPERTY( double, "width", Rect::_getWidth, pdDouble )
READONLY_PROPERTY( double, "height", Rect::_getHeight, pdDouble )
END_CLASSINFO(Rect)




BEGIN_CLASSINFO(Font, "VCF::Font", "VCF::Object", FONT_CLASSID)
PROPERTY( String, "name", Font::getName, Font::setName, pdString )
PROPERTY( bool, "bold", Font::getBold, Font::setBold, pdBool )
PROPERTY( bool, "italic", Font::getItalic, Font::setItalic, pdBool )
PROPERTY( bool, "underlined", Font::getUnderlined, Font::setUnderlined, pdBool )
PROPERTY( bool, "strikeout", Font::getStrikeOut, Font::setStrikeOut, pdBool )
PROPERTY( double, "pointSize", Font::getPointSize, Font::setPointSize, pdDouble )
OBJECT_PROPERTY( Color, "color", Font::getColor, Font::setColor );
END_CLASSINFO(Font)



BEGIN_CLASSINFO(ImageBits, "VCF::ImageBits", "VCF::Object", IMAGEBITS_CLASSID)
END_CLASSINFO(ImageBits)






};


/**
*CVS Log info
*$Log$
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


