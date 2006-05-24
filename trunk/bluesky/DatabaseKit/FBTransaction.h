#ifndef _VCF_FBTRANSACTION_H__
#define _VCF_FBTRANSACTION_H__

#include "ibase.h"

namespace VCF {

    class FBTransaction : public Transaction {
    public:
        FBTransaction();

        virtual ~FBTransaction();

        void addDatabase( Database* database );

        virtual OSHandleID getHandle();
    protected:
        virtual void internalStartTransaction();

        virtual void internalCommit( bool retaining );

        virtual void internalRollback( bool retaining );

        virtual bool internalInTransaction();
    private:
        isc_tr_handle tr_;
        ISC_STATUS status_[20];
    };

};

#endif
