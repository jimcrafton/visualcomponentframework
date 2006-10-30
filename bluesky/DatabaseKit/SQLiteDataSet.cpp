//SQLiteDataSet.cpp
#include "DatabaseKit.h"
#include "SQLiteDataSet.h"
#include "SQLiteDatabase.h"



using namespace VCF;


void SQLiteDataSet::internal_open()
{

}

void SQLiteDataSet::internal_close()
{

}

void SQLiteDataSet::internal_initFieldDefinitions()
{
	SQLiteDatabase* db = (SQLiteDatabase*) this->db_;

	sqlite3* dbHandle = (sqlite3*) db->getHandle();

	//size_t colCount = 
}

void SQLiteDataSet::internal_first()
{

}
		
GetResultType SQLiteDataSet::getRecord()
{
	GetResultType result = grFailed;

	return result;
}

void SQLiteDataSet::internal_next()
{

}

void SQLiteDataSet::clearRecordData()
{

}