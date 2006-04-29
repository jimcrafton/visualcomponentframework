#ifndef _VCF_DATATYPENOTSUPPORTEDEXCEPTION_H__
#define _VCF_DATATYPENOTSUPPORTEDEXCEPTION_H__
//DataTypeNotSupportedException.h

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
\class DataTypeNotSupportedException DataTypeNotSupportedException.h "vcf/ApplicationKit/DataTypeNotSupportedException.h"
*/
class APPLICATIONKIT_API DataTypeNotSupportedException : public BasicException {
public:
    DataTypeNotSupportedException(): BasicException("Data Type is not supported"){}

    DataTypeNotSupportedException( const String& message ): BasicException(message) {}
};

};


#endif // _VCF_DATATYPENOTSUPPORTEDEXCEPTION_H__

/**
$Id$
*/
