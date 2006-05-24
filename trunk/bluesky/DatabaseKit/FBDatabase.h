#ifndef _VCF_FBDATABASE_H__
#define _VCF_FBDATABASE_H__

#include "DatabaseKit.h"
#include "ibase.h"

namespace VCF {

    class FBDatabase : public Database {
    public:
        FBDatabase();

        virtual ~FBDatabase();

        static String errorMessageFromCode( ISC_STATUS* status );

        virtual OSHandleID getHandle();
    protected:
        virtual void internalConnect();

        virtual void internalDisconnect();

        virtual int collateParams();
    private:
        isc_db_handle db_;
        char dpb_buffer_[256];
        char *dpb_;
        short dpb_length_;
        ISC_STATUS status_[20];

    };

};

#endif
