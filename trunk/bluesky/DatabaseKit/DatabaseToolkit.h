#ifndef _VCF_DATABASETOOLKIT_H__
#define _VCF_DATABASETOOLKIT_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#include "DatabaseKit.h"


namespace VCF {

    class Database;
    class DataSet;

    enum DatabaseType {
        dtFirebird
    };

    class DATABASEKIT_API DatabaseToolkit {
    public:
        static void create();
        static void destroy();

        static Database* createDatabase( const String& type );

        static DataSet* createDataSet( const String& type );
    protected:
        DatabaseToolkit(){};
        virtual ~DatabaseToolkit(){};

        static DatabaseToolkit* Instance;
    };

};

#endif
