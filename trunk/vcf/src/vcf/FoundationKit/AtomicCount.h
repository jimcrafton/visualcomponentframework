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

	/**
	\class RefCounted AtomicCount.h "vcf/FoundationKit/AtomicCount.h"
	Interface for refcounting classes.  If you're not sure if a class instance can be refcounted 
	use dynamic_cast<RefCounted*>.
	*/
	class FOUNDATIONKIT_API RefCounted {
	public:
		virtual ~RefCounted(){}
		/**
		*increments the reference count of the object
		@return long the current reference count of the object
		*/
	    virtual long addRef()=0;

		/**
		decrements the reference count of the object and destroys object if count reaches 0
		*/
		virtual long release()=0;

		/**
		returns the number of outstanding references for this object
		*/
	    virtual long getRefCount() const=0;
	};

	/**
	\class RefCount AtomicCount.h "vcf/FoundationKit/AtomicCount.h"
	A template class to wrap around instances to allow refcounting.
	*/
	template <class T> class RefCount: public virtual RefCounted, public T {
	public:
		RefCount(T* target): refCount_(1)/*, subject_(target)*/{}
		~RefCount(){
//			delete subject_;
		}

/*		T operator*() {
			return &subject_;
		}

		T* operator->() {
			return subject_;
		}*/

		virtual long addRef() {
			return ++refCount_;
		}
		virtual long release() {
			if (0 == --refCount_) {
				delete this;
				return 0;
			}
			return refCount_;
		}
		virtual long getRefCount() {
			return refCount_;
		}
	private:
//		T* subject_;
		AtomicCount refCount_;
	};
}

#endif //_VCF_ATOMICOUNT_H__

/**
$Id$
*/

