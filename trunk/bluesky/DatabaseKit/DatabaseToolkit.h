#ifndef _VCF_DATABASETOOLKIT_H__
#define _VCF_DATABASETOOLKIT_H__



/**
Copyright 2000-2006 The VCF Project
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif



#include "DatabaseKit.h"


namespace VCF {

    class Database;
    class DataSet;
	class DataSetPeer;

    

	/**
	\class DatabaseToolkit DatabaseToolkit.h "vcf/DatabaseKit/DatabaseToolkit.h"
	The DatabaseToolkit class creates specific instances of various
	peer interfaces. These peer interfaces are used by other concrete 
	classes (such as the DataSet) in their implementation.
	*/
    class DATABASEKIT_API DatabaseToolkit {
    public:
        static void create();
        static void destroy();

        static Database* createDatabase( const String& type );

		static DataSetPeer* createDataSetPeer( const String& type );
    protected:
        DatabaseToolkit(){};
        virtual ~DatabaseToolkit(){};

        static DatabaseToolkit* Instance;
    };

};

#endif
