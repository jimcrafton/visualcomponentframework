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
    };

    using boost::static_pointer_cast;
    using boost::const_pointer_cast;
    using boost::dynamic_pointer_cast;
    using boost::get_pointer;
    using boost::get_deleter;
}

#endif // _VCF_SMARTPTR_H__
