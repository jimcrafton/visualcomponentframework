//SQLiteDataSet.h

#ifndef _VCF_SQLITEDATASET_H__
#define _VCF_SQLITEDATASET_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



namespace VCF {
	class SQLiteDataSet : public DataSet {
	public:

	protected:
        virtual void internal_open();

        virtual void internal_close();

		virtual void internal_initFieldDefinitions();

		virtual void internal_first();
		
		virtual GetResultType getRecord();

		virtual void internal_next();

		virtual void clearRecordData();
	};
};

#endif //_VCF_SQLITEDATASET_H__

