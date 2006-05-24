#include "DatabaseKit.h"

using namespace VCF;

Transaction::Transaction()
{
    inTransaction_ = false;
}

Transaction::~Transaction()
{
}

void Transaction::startTransaction()
{
    internalStartTransaction();
}

void Transaction::commit( bool retaining )
{
    internalCommit( retaining );
}

void Transaction::rollback( bool retaining )
{
    internalRollback( retaining );
}

bool Transaction::inTransaction()
{
    return internalInTransaction();
}

void Transaction::addDatabase( Database* database )
{
    if ( db_ != database ) {
        rollback( false );
        db_ = database;
    }
}
