#include <string>
#include <regex>
#include <exception>
#include <iostream>
#include <algorithm>

#include "RedditUrl.hpp"
#include "RedditError.hpp"

namespace redd {



RedditUrl& RedditUrl::operator +=(const std::string str) {
    return_url += str;
    return *this;
}

RedditUrl& RedditUrl::operator +=(const char* str) {
    return_url += str;
    return *this;
}

RedditUrl& RedditUrl::operator =(const std::string str) {
    return_url = str;
    return *this;
}

RedditUrl& RedditUrl::operator =(const char* str) {
    return_url = str;
    return *this;
}

char& RedditUrl::operator[](size_t index) {
    if (index > return_url.size()) {
        throw std::out_of_range("Subscript operator is out of range");
    }
    return return_url[index];
}

std::string::iterator RedditUrl::begin() noexcept {
    return return_url.begin();
}
std::string::iterator RedditUrl::end() noexcept {
    return return_url.end();
}

std::string::const_iterator RedditUrl::cbegin() const noexcept {
    return return_url.cbegin();
}

std::string::const_iterator RedditUrl::cend() const noexcept {
    return return_url.cend();
}


std::string RedditUrl::stripUrl(const std::string &url) const {
    std::string pattern("(https://)?(www.)?reddit.com(/r/.+?/)?");
    std::regex reg(pattern);
    std::smatch sm;
    bool found = std::regex_search(url, sm, reg);
    if (!found) {
        throw RedditError("An error occured in getting the base url, url recieved = \"" + url + "\"");
    }
    return sm.str();
}

std::string RedditUrl::url() const {
    return return_url;
}

std::string RedditUrl::based_url() const {
    return base_url;
}

std::string RedditUrl::raw_url() const {
    return given_url;
}

RedditUrl::operator std::string() {
    return return_url;
}

void RedditUrl::stripUrl() {
    return_url = stripUrl(return_url);
}

void RedditUrl::resetToBase() {
    return_url = base_url;
}

void RedditUrl::resetToRaw() {
    return_url = given_url;
}

void RedditUrl::addJson() {// add .json onto the url at end of the url in format /r/.../.json?...
    bool has_json = std::regex_search(return_url, std::regex("\\.json")); // make sure json isn't already there.
    if (!has_json) {
        auto ques_mark = std::find(return_url.begin(), return_url.end(), '?');
        auto end_slash = std::find(return_url.rbegin(), return_url.rend(), '/').base();
        std::string json(".json");
        if (ques_mark == return_url.cend()) { // there are no query strings present
            if (end_slash != return_url.cend()-1) {
                return_url.append("/");
            }
            return_url.append(json);
        }
        else { //there are query strings present
            return_url.insert(ques_mark, json.cbegin(), json.cend());
        }
    }
}


void RedditUrl::addQueryString(const std::string& str) {
    /* Make sure there is a slash at the end. */
    if (std::find(return_url.begin(), return_url.end(), '/') == return_url.end()) {
        return_url += "/";
    }
    return_url += str;
}


std::ostream& operator<<(std::ostream& os, const RedditUrl& url) {
    os << url.url() << std::flush;
    return os;
}


}//! redd namespace
