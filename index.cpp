
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

int main(int argc, const char **argv)
{
    cout << u8"Content-Type: text/html; charset=utf-8" << endl;
    cout << endl;
    cout
        << u8"<!DOCTYPE html>" << endl
        << u8"<html>" << endl
        << u8"<body><h1>Hello, World!</h1></body>" << endl
        << u8"</html>" << endl;

    return 0;
}
