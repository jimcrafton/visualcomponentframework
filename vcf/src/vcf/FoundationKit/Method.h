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
\class Method Method.h "vcf/FoundationKit/Method.h"
Base class for dynamic method invocation
Methods are dynamically invokable and can support
querying for argument types
querying is done throught the getArgumentType() method
and will only work if the argTypes_ string has bee set appropriately.
This string consists of a series of characters each of which
are interpreted as a special code for the primitive type.
The code table is as follows:

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
	virtual VariantData invoke( VariantData** arguments,
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
	uint32 getArgCount(){
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

	virtual void setSource( const Object* source ) = 0;

	/**
	returns the argument type for the specified argument
	*@param uint32 a zero based index representing a particular
	argument. For a method declared like this void someMethod( bool, int )
	then an index of 0 would represent the frist argument (bool), and
	index 1 would represnt the second argument(int).
	*@return PropertyDescriptorType the argument type
	*/
	PropertyDescriptorType getArgumentType( const uint32& argumentIndex ){
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
				else if ( 'i' == next ){
					result = pdUInt;
				}
				else if ( 'h' == next ){
					result = pdUShort;
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
	uint32 argCount_;
	bool hasReturnValue_;
	String name_;
};




}; //end of namespace VCF


#endif // _VCF_METHOD_H__

/**
$Id$
*/
