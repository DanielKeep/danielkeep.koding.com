
#include "c++11.h"

#include <cstdlib>
#include <iostream>
#include <vector>

#include "index.t.h"

// *********************************************************************** //
// *********************************************************************** //

// <cstdlib>
using std::getenv;
// <iostream>
using std::cout;
using std::endl;
// <vector>
using std::vector;

// *********************************************************************** //
// *********************************************************************** //

#define REPOSITORY u8"https://github.com/DanielKeep/danielkeep.koding.com"
#define BLOB_PREFIX u8"/blob/master/"

// *********************************************************************** //
// *********************************************************************** //

struct TemplateArgs
{
    vector<int> numbers;
};

// *********************************************************************** //
// *********************************************************************** //

int main(int argc, const char **argv)
{
    TemplateArgs targs;
    
    targs.numbers.push_back(1);
    targs.numbers.push_back(1);
    targs.numbers.push_back(2);
    targs.numbers.push_back(3);
    targs.numbers.push_back(5);
    targs.numbers.push_back(8);
    
    cout
        << u8"Content-Type: text/html; charset=utf-8" << endl
        << u8"X-Source-Repository: " << REPOSITORY << endl
        << endl;

    expand_index(cout, targs);

    return 0;
}
