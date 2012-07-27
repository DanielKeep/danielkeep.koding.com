
#include <cstdlib>
#include <iostream>

// *********************************************************************** //
// *********************************************************************** //

// <cstdlib>
using std::getenv;
// <iostream>
using std::cout;
using std::endl;

// *********************************************************************** //
// *********************************************************************** //

#define REPOSITORY u8"https://github.com/DanielKeep/danielkeep.koding.com"
#define BLOB_PREFIX u8"/blob/master/"

// *********************************************************************** //
// *********************************************************************** //

int main(int argc, const char **argv)
{
    cout
        << u8"Content-Type: text/html; charset=utf-8" << endl
        << u8"X-Source-Repository: " << REPOSITORY << endl
        << endl;

    cout
        << u8"<!DOCTYPE html>" << endl
        << u8"<html>" << endl
        << u8"<body>" << endl
        << u8"<h1>Hello, World!</h1>" << endl
        << u8"<p>The <a href=\""
            << REPOSITORY BLOB_PREFIX __FILE__
            << "\">page source code</a> (possibly not live).</p>" << endl
        << u8"</body>" << endl
        << u8"</html>" << endl;

    return 0;
}
