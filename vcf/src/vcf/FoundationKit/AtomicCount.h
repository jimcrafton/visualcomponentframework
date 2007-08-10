#ifndef _VCF_ATOMICOUNT_H__
#define _VCF_ATOMICOUNT_H__

//AtomicCount.h

/*
Copyright 2000-2007 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include <thirdparty/common/boost/detail/atomic_count.hpp>

namespace VCF {
	typedef boost::detail::atomic_count AtomicCount;
};

#endif //_VCF_ATOMICOUNT_H__

/**
$Id$
*/

