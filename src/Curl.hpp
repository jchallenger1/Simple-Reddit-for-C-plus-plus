#ifndef CURLCLASS
#define CURLCLASS

#include <string>
#include <fstream>

#include <curl/curl.h>
#include "RedditUser.hpp"

namespace redd {

class Curl {
public:
    Curl();
    ~Curl();
    std::string simplePost(const std::string& url, const redd::RedditUser&, const std::string post_fields = ""); // creates a POST request to url
    std::string simpleGet(const std::string& url); // create a HTTP get request to url
    std::string curlErrors() const; // returns errors from curl in a string
    void emptyErrors(); // removes all errors in the curl_error object
private:
    static size_t writeToString(void* buffer, size_t size, size_t nmemb, std::string* userp); // writes bytes to string
    static size_t writeToFile(void* buffer, size_t size, size_t nmemb, std::ofstream* userp); // wrties bytes to file

    CURL* curl;// managed curl object
    char curl_error[CURL_ERROR_SIZE]; // buffer representing errors given from curl

};

}


#endif

