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

namespace redd {

namespace detail {

class Curl {
public:
    Curl();
    ~Curl();
    std::string simplePost(const std::string& url, const redd::RedditUser&, const std::string post_fields = ""); // creates a POST request to url

    std::string simpleGet(const std::string& url); // create a HTTP get request to url
    // container and initalizer lists represent headers put
    // with the request. A single entry is in the format "Auth : 123"
    template<typename T>
    std::enable_if_t<isStrOrPtr<T>, std::string>
    simpleGet(const std::string& url, T&& str);
    template<typename C>
    std::enable_if_t<!isStrOrPtr<C>, std::string>
    simpleGet(const std::string& url, C&& cont);
    template<typename T>
    std::string simpleGet(const std::string& url, std::initializer_list<T>&& list);
    template<typename Iter>
    std::string simpleGet(const std::string& url, const Iter&, const Iter&);


    std::string curlErrors() const; // returns errors from curl in a string
    void emptyErrors(); // removes all errors in the curl_error object
private:
    static size_t writeToString(void* buffer, size_t size, size_t nmemb, std::string* userp); // writes bytes to string
    static size_t writeToFile(void* buffer, size_t size, size_t nmemb, std::ofstream* userp); // wrties bytes to file
    template<typename T>
    void setHttpHeader(const T&, curl_slist*&);

    CURL* curl;// managed curl object
    char curl_error[CURL_ERROR_SIZE]; // buffer representing errors given from curl

};


// *** Templates *** //
template<typename C>
std::enable_if_t<!isStrOrPtr<C>, std::string>
Curl::simpleGet(const std::string& url, C&& cont) {
    static_assert(IsStrOrPtr<typename C::value_type>,
                  "Underlying type of container must be of type std::string or const char*");
    return simpleGet(url, std::begin(std::forward<C>(cont)), std::end(std::forward<C>(cont)));
}

template<typename T>
std::string Curl::simpleGet(const std::string& url, std::initializer_list<T>&& list) {
    static_assert(IsStrOrPtr<typename T::value_type>,
                  "Underlying type of container must be of type std::string or const char*");
    return simpleGet(url, std::begin(std::forward<T>(list)), std::end(std::forward<T>(list)));
}

template<typename Iter>
std::string Curl::simpleGet(const std::string& url, const Iter& begin, const Iter& end) {
    using val_t = typename std::iterator_traits<Iter>::value_type;
    static_assert(IsStrOrPtr< val_t >,
                   "Underlying type of container must be of type std::string or const char*");

    curl_slist* headers = nullptr;
    while (begin != end) {
        setHttpHeader(*begin, headers);
    }
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    return simpleGet(url);
}

template<typename T>
std::enable_if_t<isStrOrPtr<T>, std::string>
Curl::simpleGet(const std::string& url, T&& str) {
    // no need to check type, already known from SFINAE.
    curl_slist* headers = nullptr;
    setHttpHeader(str, headers);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    return simpleGet(url);
}

template<typename T>
void Curl::setHttpHeader(const T& item, curl_slist*& header) {
    if (isStr<T>) {
        if (std::find(item.cbegin(), item.cend(), ':') == item.cend()) {
            throw std::runtime_error("Header must have a \':\' in the format \"Auth : 123 \"");
        }
        header = curl_slist_append(headers, begin.c_str());
    }
    else {
        auto ptr = strchr(item, ':');
        if (ptr == nullptr || ptr == NULL) {
            throw std::runtime_error("Header must have a \':\' in the format \"Auth : 123 \"");
        }
        header = curl_slist_append(header, item);
    }
}


} //! detail namespace

} //! redd namespace


#endif

