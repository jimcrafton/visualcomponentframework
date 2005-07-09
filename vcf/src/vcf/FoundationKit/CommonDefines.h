#ifndef _VCF_COMMONDEFINES_H__
#define _VCF_COMMONDEFINES_H__
//CommonDefines.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

/**
*Standard types for representing
*property data
*/
enum PropertyDescriptorType{
	pdUndefined = 0,
	pdInt,
	pdLong,
	pdShort,
	pdULong,
	pdFloat,
	pdChar,
	pdDouble,
	pdObject,
	pdBool,
	pdString,
	pdEnum,
	pdInterface,
	pdEnumMask,
	pdUInt    ,
	pdLong64  ,
	pdULong64 ,
	pdDateTime,
	pdDateTimeSpan,
	pdLast,
};

/**
*the controls alignment type
*/
enum AlignmentType{
    AlignNone=0,
    AlignTop,
    AlignLeft,
    AlignRight,
    AlignBottom,
    AlignClient
};

/**
*A string array for the controls alignement types
*/
static String AlignmentTypeNames[] = { "AlignNone",
                                         "AlignTop",
										 "AlignLeft",
										 "AlignRight",
										 "AlignBottom",
										 "AlignClient" };


/**
*An enum of anchor types for a control,
*may be masked together
*/
enum AnchorType {
	AnchorNone = 0,
	AnchorTop = 1,
	AnchorLeft = 2,
	AnchorBottom = 4,
	AnchorRight = 8
};

/**
*an array of Anchor type names
*/
static String AnchorTypeNames[] = { "AnchorNone",
                                         "AnchorTop",
										 "AnchorLeft",
										 "AnchorBottom",
										 "AnchorRight" };

static unsigned long AnchorTypeValues[] = { AnchorNone,
                                         AnchorTop,
										 AnchorLeft,
										 AnchorBottom,
										 AnchorRight };

/**
*An enum of icon styles for list views
*/
enum IconStyleType {
	isLargeIcon=0,
	isSmallIcon,
	isList,
	isDetails
};

/**
*An enum of icon alignment types for list views
*/
enum IconAlignType {
	iaNone=0,
	iaTop,
	iaLeft,
	iaAutoArrange
};

static String IconStyleTypeNames[] = { "isLargeIcon",
                                         "isSmallIcon",
										 "isList",
										 "isDetails" };

static String IconAlignTypeNames[] = { "iaNone",
                                         "iaTop",
										 "iaLeft",
										 "iaAutoArrange" };


enum TextAlignmentType {
	taTextLeft = 0,
	taTextCenter,
	taTextRight
};

static String TextAlignmentTypeNames[] = { "taTextLeft",
                                         "taTextCenter",
										 "taTextRight" };


/**
*Mouse button masks
*/
enum MouseButtomMasks{
	mbmUndefined = 0,
	mbmLeftButton = 1,
	mbmMiddleButton = 2,
	mbmRightButton = 4
};

/**
*Keyboard masks
*/

enum KeyboardMasks{
	kmUndefined = 0,
	kmAlt = 1,
	kmShift = 2,
	kmCtrl = 4
};


//conversion defines
#define INT_STR_CONVERSION            "%d "
#define UINT_STR_CONVERSION           "%u "
#define LONG_STR_CONVERSION           "%ld "
#define ULONG_STR_CONVERSION          "%lu "
#define CHAR_STR_CONVERSION           "%c "
#define SHORT_STR_CONVERSION          "%hd "
#define USHORT_STR_CONVERSION         "%hu "
#define FLOAT_STR_CONVERSION          "%.5f "
#define DOUBLE_STR_CONVERSION         "%.5f "
#define BOOL_STR_CONVERSION_TRUE      "true "
#define BOOL_STR_CONVERSION_FALSE     "false "

#define STR_INT_CONVERSION            "%d"
#define STR_UINT_CONVERSION           "%u"
#define STR_LONG_CONVERSION           "%ld"
#define STR_ULONG_CONVERSION          "%lu"
#define STR_CHAR_CONVERSION           "%c"
#define STR_SHORT_CONVERSION          "%hd"
#define STR_USHORT_CONVERSION         "%hu"
#define STR_FLOAT_CONVERSION          "%f"
#define STR_DOUBLE_CONVERSION         "%lf"
#define STR_BOOL_CONVERSION_TRUE      "true"
#define STR_BOOL_CONVERSION_FALSE     "false"


#define W_INT_STR_CONVERSION          L"%d "
#define W_UINT_STR_CONVERSION         L"%u "
#define W_LONG_STR_CONVERSION         L"%ld "
#define W_ULONG_STR_CONVERSION        L"%lu "
#define W_CHAR_STR_CONVERSION         L"%c "
#define W_SHORT_STR_CONVERSION        L"%hd "
#define W_USHORT_STR_CONVERSION       L"%hu "
#define W_FLOAT_STR_CONVERSION        L"%.5f "
#define W_DOUBLE_STR_CONVERSION       L"%.5f "
#define W_BOOL_STR_CONVERSION_TRUE    L"true "
#define W_BOOL_STR_CONVERSION_FALSE   L"false "

#define W_STR_INT_CONVERSION          L"%d"
#define W_STR_UINT_CONVERSION         L"%u"
#define W_STR_LONG_CONVERSION         L"%ld"
#define W_STR_ULONG_CONVERSION        L"%lu"
#define W_STR_CHAR_CONVERSION         L"%c"
#define W_STR_SHORT_CONVERSION        L"%hd"
#define W_STR_USHORT_CONVERSION       L"%hu"
#define W_STR_FLOAT_CONVERSION        L"%f"
#define W_STR_DOUBLE_CONVERSION       L"%lf"
#define W_STR_BOOL_CONVERSION_TRUE    L"true"
#define W_STR_BOOL_CONVERSION_FALSE   L"false"



enum VirtualKeyCode{
	vkUndefined = 0,
	vkF1 = 200,
	vkF2,
	vkF3,
	vkF4,
	vkF5,
	vkF6,
	vkF7,
	vkF8,
	vkF9,
	vkF10,
	vkF11,
	vkF12,
	vkUpArrow,
	vkDownArrow,
	vkLeftArrow,
	vkRightArrow,
	vkPgUp,
	vkPgDown,
	vkHome,
	vkEnd,
	vkInsert,
	vkDelete,
	vkBackSpace,
	vkNumber0,
	vkNumber1,
	vkNumber2,
	vkNumber3,
	vkNumber4,
	vkNumber5,
	vkNumber6,
	vkNumber7,
	vkNumber8,
	vkNumber9,
	vkLetterA,
	vkLetterB,
	vkLetterC,
	vkLetterD,
	vkLetterE,
	vkLetterF,
	vkLetterG,
	vkLetterH,
	vkLetterI,
	vkLetterJ,
	vkLetterK,
	vkLetterL,
	vkLetterM,
	vkLetterN,
	vkLetterO,
	vkLetterP,
	vkLetterQ,
	vkLetterR,
	vkLetterS,
	vkLetterT,
	vkLetterU,
	vkLetterV,
	vkLetterW,
	vkLetterX,
	vkLetterY,
	vkLetterZ,
	vkSpaceBar,
	vkReturn,
	vkAlt,
	vkShift,
	vkCtrl,
	vkTab,
	vkEscape,
	vkLeftApostrophe,			//`
	vkTilde,					//~
	vkExclamation,				//!
	vkCommercialAt,				//@
	vkNumberSign,				//#
	vkDollarSign,				//$
	vkPercent,					//%
	vkCircumflex,				//^
	vkAmpersand,				//&
	vkAsterix,					//*
	vkOpenParen,				//(
	vkCloseParen,				//)
	vkHyphen,					//-
	vkUnderbar,					//_
	vkEqualsSign,				//=
	vkPlusSign,					//+
	vkUprightBar,				//|
	vkBackSlash,				/* \   */
	vkOpenBracket,				//[
	vkOpenBrace,				//{
	vkCloseBracket,				//]
	vkCloseBrace,				//}
	vkSemiColon,
	vkColon,
	vkSingleQuote,
	vkDoubleQuote,
	vkComma,
	vkLessThan,
	vkPeriod,
	vkGreaterThan,
	vkForwardSlash,
	vkQuestionMark,
	//miscellaneous
	vkPrintScreen,
	vkScrollLock,
	vkPause,
	vkCapsLock,
	//substitutions
	vkMinusSign = vkHyphen,
	vkDivideSign = vkForwardSlash,
	vkMultiplySign = vkAsterix,
	vkEnter = vkReturn
};


};//end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.4  2005/07/09 23:15:02  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.3.2.2  2005/06/09 06:13:09  marcelloptr
*simpler and more useful use of Color class with ctor and getters/setters
*
*Revision 1.3.2.1  2005/02/16 05:09:32  ddiego
*bunch o bug fixes and enhancements to the property editor and treelist control.
*
*Revision 1.3  2004/12/01 04:31:40  ddiego
*merged over devmain-0-6-6 code. Marcello did a kick ass job
*of fixing a nasty bug (1074768VCF application slows down modal dialogs.)
*that he found. Many, many thanks for this Marcello.
*
*Revision 1.2.2.2  2004/08/31 08:52:57  marcelloptr
*added some property descriptor types
*
*Revision 1.2.2.1  2004/08/11 04:37:26  marcelloptr
*minor fix on macro for string to double conversion
*
*Revision 1.2  2004/08/07 02:49:13  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/26 03:30:39  marcelloptr
*minor fix string to double conversion
*
*Revision 1.1.2.3  2004/07/21 02:06:53  marcelloptr
*BugFix 985136 cast to (int) and ulong64 and other conversion issues
*The fromStringAs... functions now throw an exception in case of some errors
*
*Revision 1.1.2.2  2004/04/29 04:07:06  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:39  ddiego
*migration towards new directory structure
*
*Revision 1.14.2.2  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.14.2.1  2004/04/21 02:17:07  ddiego
*checking in change to FoundationKit, GraphicsKit and Application
*Kit to support unicode in Win32
*
*Revision 1.14  2004/01/20 01:54:55  ddiego
*merged some more changes from dev branch, primarily changes to
*teh RTTI API so that we now process enum sets correctly (i.e. a long
*that is a mask made of enum values).
*
*Revision 1.13.2.1  2004/01/18 04:52:45  ddiego
*Added a new EnumSet class that handles manipulating unsigned longs
*as a mask of bits. Adds support for reading in the enum value names and
*ORing them together to form the complete mask value. Also made
*mods to the VFFOutput and VFFInput stream classes so that that the []
*property is correctly read and written
*
*Revision 1.13  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.12.26.1  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.12  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COMMONDEFINES_H__


