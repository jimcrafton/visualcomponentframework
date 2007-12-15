#ifndef _VCF_ATOMICOUNT_H__
#define _VCF_ATOMICOUNT_H__

//AtomicCount.h

/*
Copyright 2000-2007 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

namespace VCF {

    class AtomicCount {    
    public:
        explicit AtomicCount( long v );

        long operator++();
        long operator--();
        operator long() const;
    
    private:
        AtomicCount(AtomicCount const &);
        AtomicCount & operator=(AtomicCount const &);

#ifdef VCF_GCC
        long InterlockedIncrement(volatile long *value); 
        long InterlockedDecrement(volatile long *value);        
#endif

    private:
        long value_;
    };

    inline
    AtomicCount::AtomicCount(long v)
        : value_(v)
    {
    }

    inline
    long 
    AtomicCount::operator++()
    {
        return InterlockedIncrement(&value_);
    }

    inline
    long 
    AtomicCount::operator--()
    {
        return InterlockedDecrement(&value_);
    }

    inline
    AtomicCount::operator long() const
    {
        return static_cast<long const volatile &>( value_ );
    }

#if defined(VCF_GCC)
    inline
    long
    AtomicCount::InterlockedIncrement(volatile long *value)
    {
        return ++value_;
        //return __sync_add_and_fetch(&value, 1);
        //return __gnu_cxx::__atomic_add( &value_, 1 );
    }

    inline
    long
    AtomicCount::InterlockedDecrement(volatile long *value)
    {
        return --value_;
        //return __sync_add_and_fetch(&value, -1);
        //return __gnu_cxx::__exchange_and_add(&value_, -1) - 1;
    }
#endif    
}

#endif //_VCF_ATOMICOUNT_H__

/**
$Id$
*/

