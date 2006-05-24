#include "DatabaseKit.h"

using namespace VCF;

FBDataSet::FBDataSet()
    : DataSet()
{
}

FBDataSet::~FBDataSet()
{
}

void FBDataSet::internalOpen()
{
    prepare();
}

void FBDataSet::internalClose()
{
}

void FBDataSet::prepare()
{
    initStatement();

    isc_tr_handle tr = static_cast<isc_tr_handle>( tr_->getHandle() );

    char* sql = (char*)selectSQL_->getText().ansi_c_str();

    if ( isc_dsql_prepare( status_, &tr, &st_ , 0, sql, 1, NULL ) ) {
        throw DatabaseError( FBDatabase::errorMessageFromCode( status_ ) );
    }

    describeColumns();
    initInSQLDA();
    initOutSQLDA();
}

void FBDataSet::execQuery()
{
    prepare();

    isc_tr_handle tr = static_cast<isc_tr_handle>( tr_->getHandle() );

    if ( isc_dsql_execute( status_, &tr, &st_, 1, NULL ) ) {
        throw DatabaseError( FBDatabase::errorMessageFromCode( status_ ) );
    }
}

void FBDataSet::initStatement()
{
    isc_db_handle db = static_cast<isc_db_handle>( db_->getHandle() );
    st_ = NULL;

    if ( isc_dsql_allocate_statement( status_, &db, &st_ ) ) {
        throw DatabaseError( FBDatabase::errorMessageFromCode( status_ ) );
    }
}

void FBDataSet::initInSQLDA()
{
    allocSQLDA( &in_sqlda_, params_.size() );

    if ( isc_dsql_describe_bind( status_, &st_, 1, in_sqlda_ ) ) {
        throw DatabaseError( FBDatabase::errorMessageFromCode( status_ ) );
    }

    //allocSqlvar(&in_sqlda, nparam);

    //if (param_list) fillSqlvar(&in_sqlda, nparam, param_list);
}

void FBDataSet::initOutSQLDA()
{
    allocSQLDA( &out_sqlda_, columnCount );

    if ( isc_dsql_describe( status_, &st_, 1, out_sqlda_ ) ) {
        throw DatabaseError( FBDatabase::errorMessageFromCode( status_ ) );
    }

    //allocSqlvar(&out_sqlda, ncol);
}

void FBDataSet::allocSQLDA( XSQLDA** xsqlda, int count )
{
    ::free( xsqlda );

    *xsqlda = (XSQLDA*)malloc( XSQLDA_LENGTH( count ) );
    (*xsqlda)->version = 1;
    (*xsqlda)->sqln = count;
}

void FBDataSet::describeColumns()
{
    XSQLDA* xsqlda = (XSQLDA*)malloc( XSQLDA_LENGTH( 0 ) );
    xsqlda->version = 1;
    xsqlda->sqln = 0;

    if ( isc_dsql_describe( status_, &st_, 1, xsqlda) ) {
        ::free( xsqlda );
        throw DatabaseError( FBDatabase::errorMessageFromCode( status_ ) );
    }

    columnCount = xsqlda->sqld;

    ::free( xsqlda );
}
