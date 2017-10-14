#include "report/report.h"
#include "parsers/parsers.h"

#include <iostream>
#include <iomanip>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;
using namespace dreport;

int main( int argc, char **argv )
{

    path p = ".";
    if (argc > 1) {
        p = argv[1];
    }

    Report r;
    r.run(p);
}
