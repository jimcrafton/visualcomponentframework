#ifndef _VCF_DATABASETOOLKIT_H__
#define _VCF_DATABASETOOLKIT_H__

#include "DatabaseKit.h"

namespace VCF {

    class Database;
    class DataSet;

    enum DatabaseType {
        dtFirebird
    };

    class DatabaseToolkit {
    public:
        static void create();
        static void destroy();

        static Database* createDatabase( DatabaseType type );

        static DataSet* createDataSet( DatabaseType type );
    protected:
        DatabaseToolkit(){};
        virtual ~DatabaseToolkit(){};

        static DatabaseToolkit* Instance;
    };

};

#endif
