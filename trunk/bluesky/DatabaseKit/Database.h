#ifndef _VCF_DATABASE_H__
#define _VCF_DATABASE_H__


/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

    class Transaction;

    class DATABASEKIT_API Database : public Object {
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

        virtual void internal_connect() = 0;

        virtual void internal_disconnect() = 0;

        virtual int collateParams() = 0;

		std::map<String, VariantData> params_;
        bool connected_;
        String databaseName_;
        Transaction* tr_;

    };

};

#endif
