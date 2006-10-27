#ifndef _VCF_DATASET_H__
#define _VCF_DATASET_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {

    class Database;
    class Transaction;
    class StringList;
	class FieldDefinitions;

    class DATABASEKIT_API DataSet : public Object {
    public:

        DataSet();

        virtual ~DataSet();

        void setDatabase( Database* database );

        void setTransaction( Transaction* transaction );

        void open();

        void close();

        StringList* getSelectSQL();

		void updateFieldDefs();

		virtual void initFieldDefs();
    protected:
        virtual void internalOpen() = 0;

        virtual void internalClose() = 0;

		virtual void internal_initFieldDefs() = 0;

        Database* db_;
        Transaction* tr_;
        StringList* selectSQL_;
        int columnCount;
        std::map<String, VariantData> params_;

		FieldDefinitions* fieldDefs_;

    private:
        void setActive( bool active );
    };

};

#endif
