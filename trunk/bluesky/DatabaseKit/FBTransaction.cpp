#include "DatabaseKit.h"

using namespace VCF;

FBTransaction::FBTransaction()
{
    tr_ = NULL;
}

FBTransaction::~FBTransaction()
{
}

void FBTransaction::internalStartTransaction()
{
    isc_db_handle dbHandle = static_cast<isc_db_handle>(db_->getHandle());

    //will need to change this when implementing transaction parameters
    if (isc_start_transaction( status_, &tr_, 1, &dbHandle, 0, NULL) != 0) {
        throw DatabaseError(FBDatabase::errorMessageFromCode(status_));
    }

    inTransaction_ = true;
}

void FBTransaction::internalCommit( bool retaining )
{
    if ( retaining ) {

        if (isc_commit_retaining( status_, &tr_ ) != 0) {
            throw DatabaseError(FBDatabase::errorMessageFromCode(status_));
        }

    } else {

        if (isc_commit_transaction( status_, &tr_ ) != 0) {
            throw DatabaseError(FBDatabase::errorMessageFromCode(status_));
        }

    }

    inTransaction_ = false;
}

void FBTransaction::internalRollback( bool retaining )
{
    if ( retaining ) {

        if (isc_rollback_retaining( status_, &tr_ ) != 0) {
            throw DatabaseError(FBDatabase::errorMessageFromCode(status_));
        }

    } else {

        if (isc_rollback_transaction( status_, &tr_ ) != 0) {
            throw DatabaseError(FBDatabase::errorMessageFromCode(status_));
        }

    }

    inTransaction_ = false;
}

bool FBTransaction::internalInTransaction()
{
    return inTransaction_;
}

OSHandleID FBTransaction::getHandle()
{
    return static_cast<OSHandleID>( tr_ );
}
