#ifndef _VCF_DATABASEKIT_H__
#define _VCF_DATABASEKIT_H__

/**
    Copyright The VCF Project
*/

#include "DatabaseToolkit.h"
#include "Database.h"
#include "FBDatabase.h"
#include "DatabaseError.h"
#include "SQLiteDatabase.h"
#include "DataSet.h"
#include "FBDataSet.h"
#include "Transaction.h"
#include "FBTransaction.h"
#include "StringList.h"

namespace VCF {

    class DatabaseKit {
    public:
        static void init( int argc, char **argv );

        static void terminate();
    };

};

#endif
