#ifndef _VCF_DATABASE_H__
#define _VCF_DATABASE_H__

#include "vcf/FoundationKit/FoundationKit.h"
#include <map>

using namespace std;

namespace VCF {

    class Transaction;

    class Database : public Object {
    public:

        Database();

        virtual ~Database();

        void connect();

        void disconnect();

        void setParam( String param, VariantData value );

        VariantData getParam ( String param );

        bool getConnected();

        void setConnected( bool connected );

        void setDatabaseName( String databaseName );

        virtual OSHandleID getHandle() = 0;
    protected:

        virtual void internalConnect() = 0;

        virtual void internalDisconnect() = 0;

        virtual int collateParams() = 0;

        map<String, VariantData> params_;
        bool connected_;
        String databaseName_;
        Transaction* tr_;

    };

};

#endif
