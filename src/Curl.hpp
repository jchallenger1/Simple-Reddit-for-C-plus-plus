#ifndef CURLCLASS
#define CURLCLASS

#include <string>
#include <fstream>
#include <utility>
#include <initializer_list>
#include <cstring>
#include <type_traits>

#include <curl/curl.h>
#include "json.hpp"

#include "RedditUser.hpp"
#include "RedditError.hpp"
#include "HelperFunctions.hpp"

namespace redd {

namespace detail {

// To Do : Use Smart Pointers to manage the object.
class Curl {
public:
    Curl();
    ~Curl();
    std::string simplePost(const std::string& url, const redd::RedditUser&, const std::string post_fields = ""); // creates a POST request to url

    std::string simpleGet(const std::string& url); // create a HTTP get request to url

    template<typename T>
    void setHttpHeader(const T& str);

    template<typename C>
    void setHttpHeaders(const C& container);

    template<typename T>
    void setHttpHeaders(std::initializer_list<T>&& list);

    template<typename Iter>
    void setHttpHeaders(Iter begin, Iter end);

    void emptyHttpHeader();

    std::string curlErrors() const; // returns errors from curl in a string
    void emptyErrors(); // removes all errors in the curl_error object
private:
    static size_t writeToString(void* buffer, size_t size, size_t nmemb, std::string* userp); // writes bytes to string
    static size_t writeToFile(void* buffer, size_t size, size_t nmemb, std::ofstream* userp); // wrties bytes to file
    void appendHeader(const std::string&);
    void appendHeader(const char*);

    // reddit api requires a unique user agent.
    std::string user_agent = "OS:reddit++:v0.0.1 (by /u/Anonymous)";
    curl_slist* header_list;
    CURL* curl;// managed curl object
    char curl_error[CURL_ERROR_SIZE]; // buffer representing errors given from curl

};

template<typename C>
void Curl::setHttpHeaders(const C& container) {
    static_assert(IsStrOrPtr<typename C::value_type>,
                  "Underlying type of container must be of type std::string or const char*");
    setHttpHeaders(std::cbegin(container), std::cend(container));
}

template<typename T>
void Curl::setHttpHeaders(std::initializer_list<T>&& list) {
    using list_t = typename std::initializer_list<T>;
    static_assert(IsStrOrPtr<T>,
                  "Underlying type of initalizer list must be of type std::string or const char*");
    setHttpHeaders(std::cbegin(std::forward<list_t>(list)), std::cend(std::forward<list_t>(list)));
}

template<typename Iter>
void Curl::setHttpHeaders(Iter begin, Iter end) {
    using val_t = typename std::iterator_traits<Iter>::value_type;
    static_assert(IsStrOrPtr< val_t >,
                   "Underlying type of iterator must be of type std::string or const char*");
    while (begin != end) {
        setHttpHeader(*begin);
        begin++;
    }
}

template<typename T>
void Curl::setHttpHeader(const T& str_header) {
    static_assert(IsStrOrPtr<T>, "Type must be of std::string or const char*");
    appendHeader(str_header);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);
}


} //! detail namespace

} //! redd namespace


#endif

