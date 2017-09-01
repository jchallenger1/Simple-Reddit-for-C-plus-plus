#include <string>
#include <regex>
#include <exception>
#include <iostream>

#include "RedditUrl.hpp"
#include "RedditError.hpp"

namespace redd {



RedditUrl& RedditUrl::operator +=(const std::string str) {
    return_url += str;
}

RedditUrl& RedditUrl::operator +=(const char* str) {
    return_url += str;
}

RedditUrl& RedditUrl::operator =(const std::string str) {
    return_url = str;
}

RedditUrl& RedditUrl::operator =(const char* str) {
    return_url = str;
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


std::string RedditUrl::stripUrl(const string &url) const {
    std::string pattern("(https://)?(www.)?reddit.com(/r/.+?(?:/))");
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

bool RedditUrl::isSubreddit() const {
/* TODO */
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

void RedditUrl::addJson() {

}


std::ostream& operator<<(std::ostream& os, const RedditUrl& url) {
    os << url.url() << std::flush;
    return os;
}


}
