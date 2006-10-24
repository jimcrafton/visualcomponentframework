#include "DatabaseKit.h"

using namespace VCF;

Database::Database()
    : Object(), connected_(false)
{
}

Database::~Database()
{
    /*if ( connected_ ) {
        internalDisconnect();
    }*/
}

void Database::connect()
{
    setConnected( true );
}

void Database::disconnect()
{
    setConnected( false );
}

void Database::setParam( String param, VariantData value )
{
    params_[param] = value;
}

VariantData Database::getParam ( String param )
{
    return params_[param];
}

bool Database::getConnected()
{
    return connected_;
}

void Database::setConnected( bool connected )
{
    if (connected != getConnected()) {

        if (connected) {
            internal_connect();
        } else {
            internal_disconnect();
        }

    }
}

void Database::setDatabaseName( String databaseName )
{
    databaseName_ = databaseName;
}
