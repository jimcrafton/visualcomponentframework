#ifndef _VCF_TRANSACTION_H__
#define _VCF_TRANSACTION_H__

/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

    class DATABASEKIT_API Transaction : public Object {
    public:
        Transaction();

        virtual ~Transaction();

        void startTransaction();

        void commit( bool retaining );

        void rollback( bool retaining );

        bool inTransaction();

        void addDatabase( Database* database );

        virtual OSHandleID getHandle() = 0;
    protected:
        virtual void internalStartTransaction() = 0;

        virtual void internalCommit( bool retaining ) = 0;

        virtual void internalRollback( bool retaining ) = 0;

        virtual bool internalInTransaction() = 0;

        Database* db_;
        bool inTransaction_;
    private:
    };

};

#endif
