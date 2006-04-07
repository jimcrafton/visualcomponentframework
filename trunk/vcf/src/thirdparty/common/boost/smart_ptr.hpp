//
//  smart_ptr.hpp
//
//  For convenience, this header includes the rest of the smart
//  pointer library headers.
//
//  Copyright (c) 2003 Peter Dimov  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  http://www.boost.org/libs/smart_ptr/smart_ptr.htm
//

#include <thirdparty/common/boost/config.hpp>

#include <thirdparty/common/boost/scoped_ptr.hpp>
#include <thirdparty/common/boost/scoped_array.hpp>
#include <thirdparty/common/boost/shared_ptr.hpp>
#include <thirdparty/common/boost/shared_array.hpp>

#if !defined(BOOST_NO_MEMBER_TEMPLATES) || defined(BOOST_MSVC6_MEMBER_TEMPLATES)
# include <thirdparty/common/boost/weak_ptr.hpp>
# include <thirdparty/common/boost/intrusive_ptr.hpp>
# include <thirdparty/common/boost/enable_shared_from_this.hpp>
#endif
