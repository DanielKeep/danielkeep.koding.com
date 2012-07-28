
#include "utils.h"

/*enum RequestMethod
{
    REQUEST_OPTIONS,
    REQUEST_GET,
    REQUEST_HEAD,
    REQUEST_POST,
    REQUEST_PUT,
    REQUEST_DELETE,
    REQUEST_TRACE,
    REQUEST_CONNECT,
};

struct Request
{
    RequestMethod method;
    std::string path;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> query_params;
    std::map<std::string, std::string> post_params;
    std::map<std::string, std::vector<char>> post_files;
};*/

#include <algorithm>
#include <cstdlib>
#include <stdexcept>
#include <utility>

#include "c++11.h"

// <algorithm>
using std::max;
using std::min;
// <cstdlib>
using std::getenv;
// <iostream>
using std::ostream;
// <string>
using std::string;
// <utility>
using std::pair;

// *********************************************************************** //
// *********************************************************************** //

bool starts_with(const string &haystack, const string &needle);
RequestMethod to_RequestMethod(const string &);

// *********************************************************************** //
// *********************************************************************** //

string to_string(RequestMethod v)
{
    switch(v)
    {
    case REQUEST_OPTIONS:   return "OPTIONS";
    case REQUEST_GET:       return "GET";
    case REQUEST_HEAD:      return "HEAD";
    case REQUEST_POST:      return "POST";
    case REQUEST_PUT:       return "PUT";
    case REQUEST_DELETE:    return "DELETE";
    case REQUEST_TRACE:     return "TRACE";
    case REQUEST_CONNECT:   return "CONNECT";
    default:                return "UNKNOWN";
    }
}

// *********************************************************************** //

ostream &operator<<(ostream &os, const RequestMethod v)
{
    os << to_string(v);
    return os;
}

// *********************************************************************** //

Request read_request()
{
    Request r;
    
    r.method = to_RequestMethod(getenv("REQUEST_METHOD"));
    
    {
        for(char **var = environ; *var != nullptr; ++var)
        {
            string varstr = string(*var);
            if(!starts_with(varstr, "HTTP_"))
                continue;
            
            size_t eq_idx = varstr.find('=');
            
            /* The max here takes care of the case where the index is
               npos; npos+1 = 0. */
            size_t after_eq_idx = max(eq_idx+1, eq_idx);
            string key = varstr.substr(0, eq_idx);
            string value = varstr.substr(after_eq_idx);
            
            r.headers.insert(pair<string, string>(key, value));
        }
    }
    
    {
        string request_uri = string(getenv("REQUEST_URI"));
        size_t query_start = request_uri.find('.');
        r.path = request_uri.substr(0, query_start);
        
        if(query_start != string::npos)
        {
            size_t i = query_start+1;
            while(i < request_uri.length())
            {
                size_t next_idx = min(
                    request_uri.find('&', i),
                    request_uri.find(';', i));
                size_t eq_idx = min(next_idx, request_uri.find('=', i));
                
                size_t after_next_idx = max(next_idx+1, next_idx);
                size_t after_eq_idx = max(eq_idx+1, eq_idx);
                
                string key = request_uri.substr(i, eq_idx-i);
                string value = request_uri.substr(eq_idx, next_idx-eq_idx);
                
                r.query_params.insert(pair<string, string>(key, value));
                
                i = after_next_idx;
            }
        }
    }
    
    return r;
}

// *********************************************************************** //

bool starts_with(const string &haystack, const string &needle)
{
    return (haystack.compare(0, needle.length(), needle) == 0);
}

// *********************************************************************** //

RequestMethod invalid_request_method(const string &v)
{
    throw std::runtime_error("invalid HTTP method \"" + v + "\"");
}

RequestMethod to_RequestMethod(const string &v)
{
    if(v.length() == 0)
        return invalid_request_method(v);
        
    // HACK: cheat like a bastard
    switch(v[0])
    {
        
#define REQCASE(CHAR, NAME) \
    case CHAR: \
        if(v == #NAME)  return REQUEST_ ## NAME; \
        else            return invalid_request_method(v);
            
    REQCASE('O', OPTIONS)
    REQCASE('G', GET)
    REQCASE('H', HEAD)
    REQCASE('D', DELETE)
    REQCASE('T', TRACE)
    REQCASE('C', CONNECT)
    
    // Special case since PUT and POST share the same first character.
    case 'P':
        if(v.length() == 1)
            return invalid_request_method(v);
            
        switch(v[1])
        {
        REQCASE('O', POST)
        REQCASE('U', PUT)

        default:
            return invalid_request_method(v);
        }
        break;

#undef REQCASE
    
    default:
        return invalid_request_method(v);
    }
}
