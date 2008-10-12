#ifndef _VCF_SMARTPTR_H__
#define _VCF_SMARTPTR_H__

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#if _MSC_VER > 1000
#   pragma once
#endif

#include "thirdparty/common/boost/smart_ptr.hpp"

namespace VCF  {

    template<typename T>
    struct SmartPtr {
        typedef boost::shared_ptr<T> Shared;
        typedef boost::scoped_ptr<T> Scoped;
        typedef boost::weak_ptr<T>   Weak;

        static void Deleter(T* obj) {
            obj->free();
        }

        static
        Shared New() {
            return Shared(new T, &SmartPtr::Deleter);
        }

        static
        Shared New(T *obj) {
            return Shared(obj, &SmartPtr::Deleter);
        }
    };

    using boost::static_pointer_cast;
    using boost::const_pointer_cast;
    using boost::dynamic_pointer_cast;
    using boost::get_pointer;
    using boost::get_deleter;
}





#define SHARED_PTR(ClassT) \
typedef VCF::SmartPtr<ClassT>::Shared ClassT##Ptr;

template <typename T>
_typename_ VCF::SmartPtr<T>::Shared _new( T* obj ) 
{
	return VCF::SmartPtr<T>::Shared(obj, &VCF::SmartPtr<T>::Deleter);
}


template <typename T>
_typename_ VCF::SmartPtr<T>::Shared _new() 
{
	return VCF::SmartPtr<T>::Shared( new T(), &VCF::SmartPtr<T>::Deleter);
}



#endif // _VCF_SMARTPTR_H__

/**
$Id$
*/
