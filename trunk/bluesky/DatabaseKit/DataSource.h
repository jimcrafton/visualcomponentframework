

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

	class DATABASEKIT_API DataSource : public Component {
	public:

		typedef std::vector<DataLink*> DataLinkArray;

		DELEGATE(EventDelegate,StateChanged);
		DELEGATE(EventDelegate,DataChanged);
		DELEGATE(EventDelegate,UpdatedData);

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

		void addDataLink( DataLink* val );

		void removeDataLink( DataLink* val );

		void handleDataEvent( Event* e );

		size_t getDataLinkCount() {
			return dataLinks_.size();
		}

		DataLink* getDataLink( size_t pos ) {
			DataLink* result = NULL;
			if ( pos < dataLinks_.size() ) {
				result = dataLinks_[pos];
			}
			return result;
		}
	protected:
		DataSet* dataSet_;
		bool enabled_;
		DataSetState state_;

		

		DataLinkArray dataLinks_;

		void notifyDataLinks( Event* e );

		virtual void destroy();		
		
	};
};


#endif //_VCF_DATASOURCE_H__