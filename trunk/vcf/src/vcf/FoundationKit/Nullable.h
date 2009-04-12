#ifndef _VCF_NULLABLE_H__
#define _VCF_NULLABLE_H__

namespace VCF {

/**
\class Nullable Nullable.h "vcf/FoundationKit/Nullable.h"
*Nullable representation of a value type.
*Can also be compared to NULL using the == and != operators.
*
*@version 1.0
*@author Aaron Oneal
*/
template<typename T> class FOUNDATIONKIT_API Nullable
{
public:
	/// Constructors

	// Default constructor assumes NULL
	Nullable()
	{
		isNull = true;
	}

	// This handles the NULL case
	Nullable(void* p)
	{
		if(p != NULL)
			throw new VCF::RuntimeException("You cannot specify a non-null pointer");
		isNull = true;
	}

	Nullable(const T& t)
	{
		isNull = false;
		value = t;
	}

	// Copy constructor
	Nullable(const Nullable& n)
	{
		isNull = n.isNull;
		if(!isNull)
			value = n.value;
	}

	/// Overloaded Operators

	operator T&()
	{
		if(isNull)
			throw new VCF::RuntimeException ("Object does not have a value");
		else
			return value;
	}

	void operator =(void* p)
	{
		if(p != NULL)
			throw new VCF::RuntimeException ("You cannot assign a non-null pointer");
		isNull = true;
	}

	const T operator =(const T& t)
	{
		isNull = false;
		return (value = t);
	}

	void operator =(const VCF::VariantData& n)
	{
		isNull = n.isNull();
		if(!isNull)
			value = (const T&)n;
	}

	T& operator*()
	{
		return value;
	}

	bool operator ==(const T& t)
	{
		if(isNull)
			return false;

		return value == t;
	}

	bool operator ==(void* p)
	{
		if(p == NULL)
		{
			if(isNull)
				return true;
		}
		return false;
	}

	bool operator !=(void* p)
	{
		return !operator ==(p);
	}

	/// Value accessors

	/**
	* Determines whether the object has a value
	*/
	virtual bool hasValue() const
	{
		return !isNull;
	}

	/**
	* Returns a reference to the stored value and throws a RuntimeException if there is none.
	*/
	virtual T& getValue()
	{
		if(hasValue())
			return value;
		else
			throw new VCF::RuntimeException("Object does not have a value");
	}

	/**
	* Returns a copy of the stored value, or the default value if one is not present.
	*/
	virtual T getValueOrDefault(const T& defaultValue)
	{
		if(hasValue())
			return value;
		else
			return defaultValue;
	}

protected:
	T value;
	bool isNull;
};

}; // namespace VCF
#endif // _VCF_OPTIONAL_H__
