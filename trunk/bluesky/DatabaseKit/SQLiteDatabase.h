#ifndef _VCF_SQLITEDB_H__
#define _VCF_SQLITEDB_H__

#include "sqliteInt.h"


#define SQLITETYPE	"SQLiteType"

namespace VCF {

    class SQLiteDatabase : public Database {
    public:

        SQLiteDatabase();

        virtual ~SQLiteDatabase();

		virtual OSHandleID getHandle();

		static String errorMessageFromHandle( sqlite3* dbHandle );
		String getErrorMessage() const;
    protected:

        virtual void internal_connect();

		virtual void internal_disconnect();

        virtual int collateParams();

		sqlite3* dbHandle_;

    };

};

#endif
