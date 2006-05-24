#include <iostream>
#include "../DatabaseKit.h"

using namespace VCF;

int main(int argc, char **argv)
{
    DatabaseKit::init(argc, argv);
    Database *database = DatabaseToolkit::createDatabase(dtFirebird);
    database->setDatabaseName("MMSSERVER:platterlog");
    database->setParam("Username", "SYSDBA");
    database->setParam("Password", "masterkey");

    try {
        database->connect();
    } catch (DatabaseError &E) {
        System::println(E.getMessage());
        return 0;
    }

    System::println("connected");


    try {
        database->disconnect();
    } catch (DatabaseError &E) {
        System::println(E.getMessage());
        return 0;
    }

    System::println("disconnected");

    database->free();

    DatabaseKit::terminate();
}
