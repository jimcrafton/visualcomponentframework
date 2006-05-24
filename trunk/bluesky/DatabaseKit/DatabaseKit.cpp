#include "DatabaseKit.h"

using namespace VCF;

void DatabaseKit::init( int argc, char **argv )
{
    DatabaseToolkit::create();
}

void DatabaseKit::terminate()
{
    DatabaseToolkit::destroy();
}
