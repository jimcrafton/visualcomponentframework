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

		DELEGATE(LoggedIn);

        Database();

        virtual ~Database();

        void connect();

        void disconnect();

        void setParam( const String& param, VariantData value );

        VariantData getParam ( const String& );

        bool getConnected();

        void setConnected( bool connected );

        void setDatabaseName( const String& databaseName );

		String getDatabaseName();        

		bool isSQLBased();

		uint32 getDataSetCount();

		bool getKeepsConnection();

		void setKeepsConnection( bool val );

		bool getNeedsLoginPrompt();

		void setNeedsLoginPrompt( bool val );

		bool isTransactionStarted();

		void closeDatasets();

		Locale* getLocale();

		void setLocale( Locale* val );

		virtual void flushSchemaCache( const String& tableName ) = 0;

		virtual OSHandleID getHandle() = 0;

		virtual void setHandle( OSHandleID handle ) = 0;

		virtual void rollback() = 0;

		virtual void startTransaction() = 0;

		virtual void commit() = 0;
    protected:

        virtual void internal_connect() = 0;

        virtual void internal_disconnect() = 0;

        virtual int collateParams() = 0;

		std::map<String, VariantData> params_;
        bool connected_;
		bool sqlBased_;
		bool keepsConnection_;
		bool needsLoginPrompt_;
		bool transactionStarted_;
        String databaseName_;
        Transaction* tr_;
		Locale locale_;
    };

};

#endif
