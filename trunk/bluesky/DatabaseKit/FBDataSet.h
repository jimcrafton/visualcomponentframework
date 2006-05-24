#ifndef _VCF_FBDATASET_H__
#define _VCF_FBDATASET_H__

namespace VCF {

    class FBDataSet : public DataSet {
    public:
        FBDataSet();

        virtual ~FBDataSet();

        void prepare();
    protected:
        virtual void internalOpen();

        virtual void internalClose();
    private:
        void initStatement();

        void execQuery();

        void initInSQLDA();

        void initOutSQLDA();

        void allocSQLDA( XSQLDA**, int );

        void describeColumns();

        ISC_STATUS status_[20];
        isc_stmt_handle st_;
        XSQLDA* out_sqlda_;
        XSQLDA* in_sqlda_;
    };

};

#endif
