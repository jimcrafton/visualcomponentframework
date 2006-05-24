#ifndef _VCF_SQLITEDB_H__
#define _VCF_SQLITEDB_H__

//#include "sqlite3.h"

namespace VCF {

    class SQLiteDatabase : public Database {
    public:

        SQLiteDatabase();

        virtual ~SQLiteDatabase();

    protected:

        virtual void internalConnect();

    private:

        //sqlite3* db_;

    };

};

#endif
