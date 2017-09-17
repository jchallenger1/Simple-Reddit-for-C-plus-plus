#include <string>
#include <cstring>
#include <fstream>
#include <exception>

#include <curl/curl.h>
#include "json.hpp"

#include "Curl.hpp"
#include "RedditError.hpp"

namespace redd {

namespace detail {

Curl::Curl() {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_error);
}

Curl::~Curl() {
    curl_easy_reset(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

std::string Curl::simplePost(const std::string& url, const RedditUser& user, const std::string post_fields) {

    std::string result;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Curl::writeToString);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_error);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
    std::string auth = user.ID() + ":" + user.secret();
    curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
    auto response = curl_easy_perform(curl);

    // if a blank page was passed, it's most likely an error, the reddit endpoint atleast returns "{}".
    if (response != CURLE_OK || result.empty()) {
        throw RedditError("Curl was not able to make the request to the server.", curl_error);
    }

    return result;
}

std::string Curl::simpleGet(const std::string &url) {
    if (url.empty()) {
        throw RedditError("Given url is empty.");
    }
    std::string result;
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &Curl::writeToString);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_error);
    auto response = curl_easy_perform(curl);

    // if a blank page was passed, it's most likely an error, the reddit endpoint atleast returns "{}".
    if (response != CURLE_OK || result.empty()) {
        throw RedditError("Curl was not able to make the request to the server.", curl_error);
    }
    return result;
}

std::string Curl::curlErrors() const {
    return curl_error;
}

void Curl::emptyErrors() {
    memset(curl_error,0,sizeof(curl_error));
}


size_t Curl::writeToFile(void *buffer, size_t size, size_t nmemb, std::ofstream *userp) {
    userp->write(reinterpret_cast<char*>(buffer), size * nmemb);
    return size * nmemb;
}

size_t Curl::writeToString(void *buffer, size_t size, size_t nmemb, std::string *userp) {
    userp->append(reinterpret_cast<char*>(buffer), size * nmemb);
    return size * nmemb;
}

} //! detail namespace

} //! redd namespace
