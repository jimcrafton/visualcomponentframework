//SQLiteDataSet.cpp
#include "DatabaseKit.h"
#include "SQLiteDataSet.h"
#include "SQLiteDatabase.h"



using namespace VCF;


void SQLiteDataSet::internalOpen()
{

}

void SQLiteDataSet::internalClose()
{

}

void SQLiteDataSet::internal_initFieldDefinitions()
{
	SQLiteDatabase* db = (SQLiteDatabase*) this->db_;

	sqlite3* dbHandle = (sqlite3*) db->getHandle();

	//size_t colCount = 
}
