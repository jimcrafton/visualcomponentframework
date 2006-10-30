

#ifndef _VCF_DATASOURCE_H__
#define _VCF_DATASOURCE_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "DataSet.h"


namespace VCF {

	class DataLink;

	class DataSource : public Object {
	public:

		DELEGATE(StateChanged);
		DELEGATE(DataChanged);
		DELEGATE(UpdatedData);

		DataSource();		

		DataSet* getDataSet() {
			return dataSet_;
		}

		void setDataSet( DataSet* val );

		bool isEnabled() {
			return enabled_;
		}

		void setEnabled( bool val );

		DataSetState getState() {
			return state_;
		}

		void setState( DataSetState val );

		void updateState();

		void edit();
	protected:
		DataSet* dataSet_;
		bool enabled_;
		DataSetState state_;



		virtual void destroy();		
		
	};
};


#endif //_VCF_DATASOURCE_H__