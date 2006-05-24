#ifndef _VCF_DATASET_H__
#define _VCF_DATASET_H__

#include "vcf/FoundationKit/FoundationKit.h"

namespace VCF {

    class Database;
    class Transaction;
    class StringList;

    class DataSet : public Object {
    public:

        DataSet();

        virtual ~DataSet();

        void setDatabase( Database* database );

        void setTransaction( Transaction* transaction );

        void open();

        void close();

        StringList* getSelectSQL();
    protected:
        virtual void internalOpen() = 0;

        virtual void internalClose() = 0;

        Database* db_;
        Transaction* tr_;
        StringList* selectSQL_;
        int columnCount;
        std::map<String, VariantData> params_;
    private:
        void setActive( bool active );
    };

};

#endif
