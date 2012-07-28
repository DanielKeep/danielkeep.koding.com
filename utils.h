#ifndef UTILS_H_INCLUDED

#include <map>
#include <iostream>
#include <string>
#include <vector>

enum RequestMethod
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

std::string to_string(RequestMethod);
std::ostream &operator<<(std::ostream &, const RequestMethod);

struct Request
{
    RequestMethod method;
    std::string path;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> query_params;
    std::map<std::string, std::string> post_params;
    std::map<std::string, std::vector<char>> post_files;
};

Request read_request();

#endif//UTILS_H_INCLUDED