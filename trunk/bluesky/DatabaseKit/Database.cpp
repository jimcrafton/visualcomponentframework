#include "DatabaseKit.h"

using namespace VCF;

Database::Database()
    : Object(), 
	connected_(false),
	sqlBased_(true),
	keepsConnection_(true),
	needsLoginPrompt_(false),
	transactionStarted_(false),
	locale_("en", "US")
{
	setLocale( System::getCurrentThreadLocale() );
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

void Database::setParam( const String& param, VariantData value )
{
    params_[param] = value;
}

VariantData Database::getParam ( const String& param )
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

		connected_ = connected;

        if (connected) {
            internal_connect();
        } 
		else {
            internal_disconnect();
        }
    }
}

void Database::setDatabaseName( const String& databaseName )
{
    databaseName_ = databaseName;
}

String Database::getDatabaseName()
{
	return databaseName_;
}

bool Database::isSQLBased()
{
	return sqlBased_;
}

uint32 Database::getDataSetCount()
{
	return 0;
}	

bool Database::getKeepsConnection()
{
	return keepsConnection_;
}

void Database::setKeepsConnection( bool val )
{
	keepsConnection_ = val;
}

bool Database::getNeedsLoginPrompt()
{
	return needsLoginPrompt_;
}

void Database::setNeedsLoginPrompt( bool val )
{
	needsLoginPrompt_ = val;
}

void Database::closeDatasets()
{

}

Locale* Database::getLocale()
{
	return &locale_;
}

void Database::setLocale( Locale* val )
{
	locale_ = *val;
}

bool Database::isTransactionStarted()
{
	return transactionStarted_;
}