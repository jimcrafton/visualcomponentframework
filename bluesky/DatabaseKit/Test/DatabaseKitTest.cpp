#include <iostream>
#include "DatabaseKit.h"

using namespace VCF;

int main(int argc, char **argv)
{
    DatabaseKit::init(argc, argv);
    Database *database = DatabaseToolkit::createDatabase(dtFirebird);
    database->setDatabaseName("MMSSERVER:platterlog");
    database->setParam("Username", "SYSDBA");
    database->setParam("Password", "masterkey");

    DataSet* dataset = DatabaseToolkit::createDataSet(dtFirebird);
    dataset->setDatabase(database);

    dataset->getSelectSQL()->add("SELECT * FROM TABLE");
    dataset->getSelectSQL()->add("WHERE CONDITION = VALUE");

    dataset->free();
    database->free();

    DatabaseKit::terminate();
}
