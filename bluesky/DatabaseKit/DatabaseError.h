#ifndef _VCF_DATABASEERROR_H__
#define _VCF_DATABASEERROR_H__

/*
    Copyright 2000-2004 The VCF Project.
    Please see License.txt in the top level directory
    where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

	/**
	\class DatabaseError DatabaseError.h "vcf/DatabaseKit/DatabaseError.h"
	*/
    class DATABASEKIT_API DatabaseError : public BasicException {
    public:

        DatabaseError( const String &message ) :
            BasicException( message ){};

        virtual ~DatabaseError() throw() {};
    };

};

#endif
