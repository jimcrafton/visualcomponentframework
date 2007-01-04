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
	pdNull = -1,
	pdUndefined = 0,
	pdInt,
	pdLong,
	pdShort,
	pdUShort,
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
	pdInt64  ,
	pdUInt64 ,
	pdDateTime,
	pdDateTimeSpan,
	pdLast,
};



/**
This enum is a mapping of virtual keys on a keyboard 
to a standard value.
*/
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



};//end of namespace VCF


#endif // _VCF_COMMONDEFINES_H__

/**
$Id$
*/
