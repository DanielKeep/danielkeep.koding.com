
#include "c++11.h"

#include <climits>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "index.t.h"

// *********************************************************************** //
// *********************************************************************** //

// <cstdlib>
using std::getenv;
// <iostream>
using std::cin;
using std::cout;
using std::endl;
// <string>
using std::string;
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
    
    string request_method;
    string query;
    string environ;
    string content;
};

// *********************************************************************** //
// *********************************************************************** //

string mkstring(const char *);
int string_to_int(const string &, int base = 0);

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
    
    targs.request_method = mkstring(getenv("REQUEST_METHOD"));
    targs.query = mkstring(getenv("QUERY_STRING"));
    
    if(targs.request_method == "POST")
    {
        int content_length = string_to_int(getenv("CONTENT_LENGTH"));
        vector<char> post(content_length);
        cin.read(&post[0], content_length);
        targs.content = string(post.begin(), post.end());
    }
    
    for(char **p = environ; *p != nullptr; ++p)
    {
        targs.environ += "<li><tt>" + string(*p) + "</tt></li>\n";
    }
    
    cout
        << u8"Content-Type: text/html; charset=utf-8" << endl
        << u8"X-Source-Repository: " << REPOSITORY << endl
        << endl;

    expand_index(cout, targs);

    return 0;
}

// *********************************************************************** //

string mkstring(const char *ptr)
{
    if(ptr == nullptr)
        return string();
    else
        return string(ptr);
}

// *********************************************************************** //

int string_to_int(const string &str, int base)
{
    const char *s = str.c_str();
    char *end;
    int i;
    long  l;
    
    errno = 0;
    l = strtol(s, &end, base);
    
    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX)
    {
        throw std::overflow_error(
            string("overflow in converting \"")
            + str + string("\" to int"));
    }
    
    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN)
    {
        throw std::underflow_error(
            string("underflow in converting \"")
            + str + string("\" to int"));
    }
    
    if (*s == '\0' || *end != '\0')
    {
        throw std::runtime_error(
            string("cannot convert \"")
            + str + string("\" to int"));
    }
    
    i = l;
    return i;
}
