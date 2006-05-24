#include "DatabaseKit.h"

using namespace VCF;

FBDatabase::FBDatabase()
    : Database(), db_(NULL)
{
    tr_ = new FBTransaction();
}

FBDatabase::~FBDatabase()
{
}

void FBDatabase::internalConnect()
{
    if (collateParams() == 0) {
        throw DatabaseError("No params");
    }

    char *dbHost = (char*)databaseName_.ansi_c_str();

    if (isc_attach_database( status_, strlen(dbHost), dbHost,
        &db_, dpb_length_, dpb_buffer_ )) {
        throw DatabaseError( errorMessageFromCode( status_ ) );
    }

    connected_ = true;
}

int FBDatabase::collateParams()
{
    int paramCount = 0;

    dpb_ = dpb_buffer_;
    *dpb_++ = isc_dpb_version1;
    *dpb_++ = isc_dpb_num_buffers;
    *dpb_++ = 1;
    *dpb_++ = 90;

    if (params_.count("Username")) {
        String userStr = getParam( "Username" ).toString();
        char* username = (char*)userStr.ansi_c_str();

        *dpb_++ = isc_dpb_user_name;
		*dpb_++ = strlen( username );
        strcpy( dpb_, username );
        dpb_ += strlen( username );

        paramCount++;
    }

    if (params_.count( "Password" )) {
        String passStr = getParam("Password").toString();
        char* password = (char*)passStr.ansi_c_str();

        *dpb_++ = isc_dpb_password;
		*dpb_++ = strlen( password );
        strcpy( dpb_, password );
        dpb_ += strlen( password );

        paramCount++;
    }

    dpb_length_ = dpb_ - dpb_buffer_;

    return paramCount;
}

String FBDatabase::errorMessageFromCode( ISC_STATUS* status )
{
    char errMsg[1024];
    long sqlcode = isc_sqlcode( status );
    isc_sql_interprete(sqlcode, errMsg, 1024);

    return String( errMsg );
}

void FBDatabase::internalDisconnect()
{
    //stop all transactions

    if ( isc_detach_database( status_, &db_ ) > 0 ) {
        throw DatabaseError( errorMessageFromCode( status_ ) );
    }

}

OSHandleID FBDatabase::getHandle()
{
    return static_cast<void*>( db_ );
}
