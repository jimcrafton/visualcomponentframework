#ifndef _VCF_HASH_H__
#define _VCF_HASH_H__

namespace VCF {

/**
\class Hash Hash.h "vcf/FoundationKit/Hash.h"
*Used to calculate a 32-bit hash
*
*Hash functions based on Bob Jenkins' work:
*http://burtleburtle.net/bob/hash/doobs.html
*
*@version 1.0
*@author Aaron Oneal
*/
class FOUNDATIONKIT_API Hash32
{
public:
	/// Constructors

	// Default constructor assumes 0
	Hash32()
	{
	    key = 0;
	}

	Hash32(uint32 k)
	{
	    key = k;
	}

	/// Overloaded Operators

	operator uint32&()
	{
		return key;
	}

	/// Value accessors

	/**
	* Returns the currently calculated key
	*/
	uint32 getValue()
	{
		return key;
	}

	static inline uint32 mix(uint32 a, uint32 b, uint32 c)
	{
        a -= b; a -= c; a ^= (c>>13);
        b -= c; b -= a; b ^= (a<<8);
        c -= a; c -= b; c ^= (b>>13);
        a -= b; a -= c; a ^= (c>>12);
        b -= c; b -= a; b ^= (a<<16);
        c -= a; c -= b; c ^= (b>>5);
        a -= b; a -= c; a ^= (c>>3);
        b -= c; b -= a; b ^= (a<<10);
        c -= a; c -= b; c ^= (b>>15);
        return c;
	}

    void mix(const uint8* k, uint32 length)
	{
        register uint32 a,b,c,len;

        /* Set up the internal state */
        len = length;
        a = b = 0x9e3779b9;  /* the golden ratio; an arbitrary value */
        c = key;         /* the previous hash value */

        /*---------------------------------------- handle most of the key */
        while (len >= 12)
        {
          a += (k[0] +((uint32)k[1]<<8) +((uint32)k[2]<<16) +((uint32)k[3]<<24));
          b += (k[4] +((uint32)k[5]<<8) +((uint32)k[6]<<16) +((uint32)k[7]<<24));
          c += (k[8] +((uint32)k[9]<<8) +((uint32)k[10]<<16)+((uint32)k[11]<<24));
          c = Hash32::mix(a,b,c);
          k += 12; len -= 12;
        }

        /*------------------------------------- handle the last 11 bytes */
        c += length;
        switch(len)              /* all the case statements fall through */
        {
        case 11: c+=((uint32)k[10]<<24);
        case 10: c+=((uint32)k[9]<<16);
        case 9 : c+=((uint32)k[8]<<8);
          /* the first byte of c is reserved for the length */
        case 8 : b+=((uint32)k[7]<<24);
        case 7 : b+=((uint32)k[6]<<16);
        case 6 : b+=((uint32)k[5]<<8);
        case 5 : b+=k[4];
        case 4 : a+=((uint32)k[3]<<24);
        case 3 : a+=((uint32)k[2]<<16);
        case 2 : a+=((uint32)k[1]<<8);
        case 1 : a+=k[0];
         /* case 0: nothing left to add */
        }
        key = Hash32::mix(a,b,c);
	}

    void mix(int8 k)
    {
        mix((uint8*)&k, sizeof(k));
    }

    void mix(uint8 k)
    {
        mix((uint8*)&k, sizeof(k));
    }

    void mix(int16 k)
    {
        mix((uint8*)&k, sizeof(k));
    }

    void mix(uint16 k)
    {
        mix((uint8*)&k, sizeof(k));
    }

    void mix(int32 k)
    {
        mix((uint8*)&k, sizeof(k));
    }

    void mix(uint32 k)
    {
        mix((uint8*)&k, sizeof(k));
    }

    void mix(int64 k)
    {
        mix((uint8*)&k, sizeof(k));
    }

    void mix(uint64 k)
    {
        mix((uint8*)&k, sizeof(k));
    }

   	void mix(const String& k)
	{
	    mix((uint8*)k.c_str(), k.length() * sizeof(WideChar));
	}

    // This simple hash is in common use
	void simpleMix(const String& k)
	{
	    for(uint32 i = 0; i < k.length(); i++)
            key = 31 * key + k[i];
	}

protected:
	uint32 key;
};

}; // namespace VCF
#endif // _VCF_HASH_H__
