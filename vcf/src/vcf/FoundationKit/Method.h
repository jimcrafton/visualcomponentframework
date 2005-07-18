#ifndef _VCF_METHOD_H__
#define _VCF_METHOD_H__
//Method.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


/**
Base class for dynamic method invocation
Methods are dynamically invokable and can support
querying for argument types
querying is done throught the getArgumentType() method
and will only work if the argTypes_ string has bee set appropriately.
This string consists of a series of characters each of which
are interpreted as a special code for the primitive type.
The code table is as follows:
\par
\code
	  code	|	primitive type
	----------------------------
	  "i"   |		integer
	  "l"	|		long
	  "h"	|		short
	  "+l"	|		unsigned long
	  "f"	|		float
	  "c"	|		char
	  "d"	|		double
	  "o"	|		Object*
	  "b"	|		bool
	  "s"	|		String or String&
	  "e"	|		Enum*

\endcode
\par
To create an instance of a Method object use one of the template
based classes described below.
*/
class FOUNDATIONKIT_API Method  {

public:
	Method(){
		argCount_ = 0;
		hasReturnValue_ = false;
	};

	virtual ~Method(){};

	/**
	makes a copy of the method. Implemented in the templated
	derived classes.
	*/

	/**
	invoke the method on the source object
	We don't need the number of elements in the arguments[] because
	argCount_ should be set and we can use these. If this is not the
	case then the programmer has screwed up somewhere !
	the source argument may be NULL, in this case the
	implementing code should Assumes setSource() has already been called
	this would have gotten set when the class or interface
	the method belonged to was retreived from the Object in question
	*/
	virtual VariantData* invoke( VariantData** arguments,
								 Object* source=NULL ) = 0;

	/**
	returns the name of the method
	*/
	String getName(){
		return name_;
	}

	/**
	sets the name of the method
	*/
	void setName( const String& name ){
		name_ = name;
	}

	/**
	returns the numbers of arguments required to invoke
	the method.
	*/
	ulong32 getArgCount(){
		return argCount_;
	}

	/**
	specifies whether or not the method has a return
	value
	*@return bool true if the method has a return value
	otherwise false
	*/
	bool hasReturnValue(){
		return hasReturnValue_;
	}

	/**
	returns the bound source of the method - may return NULL if
	no source has been set
	*/
	virtual Object* getSource() = 0;

	/**
	sets the source of the object
	*/
	virtual void setSource( Object* source ) = 0;

	/**
	returns the argument type for the specified argument
	*@param ulong32 a zero based index representing a particular
	argument. For a method declared like this void someMethod( bool, int )
	then an index of 0 would represent the frist argument (bool), and
	index 1 would represnt the second argument(int).
	*@return PropertyDescriptorType the argument type
	*/
	PropertyDescriptorType getArgumentType( const ulong32& argumentIndex ){
		PropertyDescriptorType result = pdUndefined;
		char ch = argTypes_[argumentIndex];

		switch ( ch ){
			case 'i' :{
				result = pdInt;
			}
			break;

			case 'l' :{
				result = pdLong;
			}
			break;

			case 'h' :{
				result = pdShort;
			}
			break;

			case '+' :{
				VCFChar next = argTypes_.at(argumentIndex+1);
				if ( 'l' == next ){
					result = pdULong;
				}
			}
			break;

			case 'f' :{
				result = pdFloat;
			}
			break;

			case 'c' :{
				result = pdChar;
			}
			break;

			case 'd' :{
				result = pdDouble;
			}
			break;

			case 'o' :{
				result = pdObject;
			}
			break;

			case 'b' :{
				result = pdBool;
			}
			break;

			case 'e' :{
				result = pdEnum;
			}
			break;

			case 's' :{
				result = pdString;
			}
			break;
		}
		return result;
	}

	virtual Method* clone() = 0;
protected:
	String argTypes_;
	ulong32 argCount_;
	bool hasReturnValue_;
	String name_;
};




}; //end of namespace VCF


/**
CVS Log info
*$Log$
*Revision 1.3  2005/07/18 03:54:19  ddiego
*documentation updates.
*
Revision 1.2  2004/08/07 02:49:13  ddiego
merged in the devmain-0-6-5 branch to stable
*
Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
changed macros, text reformatting, copyright sections
*
Revision 1.1.2.2  2004/04/29 04:07:08  marcelloptr
reformatting of source files: macros and csvlog and copyright sections
*
Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
migration towards new directory structure
*
Revision 1.4.2.1  2004/04/26 21:58:47  marcelloptr
changes for dir reorganization: _VCF_MACRO_H__
*
Revision 1.4  2004/04/03 17:57:15  ddiego
more merge changes - rtti code that was in the dev
branch apparently didn't make it over to the stable branch.
*
Revision 1.1.2.2  2004/02/15 20:24:01  ddiego
intial Locales implementation is now checked in. This adds several new classes, namely:
The LocalePeer, which is the OS generic peer for interfacing with teh OS for lcoale support
The Locale class which provides locale support for the vcf
The Win32LocalePeer which provides a basic Win32 implementation for locale support
The UnicodeString class, which is a near identical class to the std::string class and provides a wrapper around a std::basic_string<wchar_t>. This also adds support for translating to and from ansi strings, and supporting text encoding via a TextEncoder class.
The TextCodec class which allows for custom text codec for encoding or decoding text.
The MessageLoader class which is used to provide localized string translation
The StringsMessageLoader which provides a basic implementation of string loading and translation that is compatible with Apples .strings resource files.
*
Revision 1.1.2.1  2004/01/11 19:57:54  ddiego
implemented the following tasks:
*79267	Change Class class to NOT inherit from Object
*79268	Change Property class to NOT inherit from Object
*79269	Change ClassRegistry class to NOT inherit from Object
*79270	Change Method class to NOT inherit from Object
*91983	Add a Field class for rtti
plus created a new include/rtti and src/rtti directories and moved the
various rtti related code to the appropriate directories
*
Revision 1.12  2003/12/18 05:15:57  ddiego
merge from devmain-0-6-2 branch into the stable branch
*
Revision 1.11.4.2  2003/11/02 02:54:34  ddiego
made some small changes to the method RTTI registration code.
*
Revision 1.11.4.1  2003/10/23 04:24:50  ddiego
more musical chairs with headers again, in yet another attempt to make
them more efficent to speed up compiles.
Removed all teh template RTTI classes and put them all in one header
called VCFRTTIImpl.h. This should help compile speeds a bit.
The next step is to look at some of the event classes and remove ones
that aren't really neccessary - I'd estimate that 50% of the current
event classes are unneccessary and can be removed.
*
Revision 1.11  2003/05/17 20:37:03  ddiego
this is the checkin for the 0.6.1 release - represents the merge over from
the devmain-0-6-0 branch plus a few minor bug fixes
*
Revision 1.10.22.1  2003/03/12 03:09:37  ddiego
switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
Also changed all vcf builder files to accomadate this.
Changes were made to the Stream classes to NOT multiple inheritance and to
be a little more correct. Changes include breaking the FileStream into two
distinct classes, one for input and one for output.
*
Revision 1.10  2002/01/24 01:46:47  ddiego
added a cvs "log" comment to the top of all files in vcf/src and vcf/include
to facilitate change tracking
*
*/


#endif // _VCF_METHOD_H__


