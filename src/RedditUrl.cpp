#include <string>
#include <regex>
#include <exception>
#include <iostream>

#include "RedditUrl.hpp"
#include "RedditError.hpp"

redd::RedditUrl& redd::RedditUrl::operator +=(const std::string str) {
    return_url += str;
}

redd::RedditUrl& redd::RedditUrl::operator +=(const char* str) {
    return_url += str;
}

redd::RedditUrl& redd::RedditUrl::operator =(const std::string str) {
    return_url = str;
}

redd::RedditUrl& redd::RedditUrl::operator =(const char* str) {
    return_url = str;
}

char& redd::RedditUrl::operator[](size_t index) {
    if (index > return_url.size()) {
        throw std::out_of_range("Subscript operator is out of range");
    }
    return return_url[index];
}

std::string::iterator redd::RedditUrl::begin() noexcept {
    return return_url.begin();
}
std::string::iterator redd::RedditUrl::end() noexcept {
    return return_url.end();
}

std::string::const_iterator redd::RedditUrl::cbegin() const noexcept {
    return return_url.cbegin();
}

std::string::const_iterator redd::RedditUrl::cend() const noexcept {
    return return_url.cend();
}


std::string redd::RedditUrl::stripUrl(const string &url) const {
    std::string pattern("(https://)?(www.)?reddit.com(/r/.+?(?:/))");
    std::regex reg(pattern);
    std::smatch sm;
    bool found = std::regex_search(url, sm, reg);
    if (!found) {
        throw RedditError("An error occured in getting the base url, url recieved = \"" + url + "\"");
    }
    return sm.str();
}

std::string redd::RedditUrl::url() const {
    return return_url;
}

std::string redd::RedditUrl::based_url() const {
    return base_url;
}

std::string redd::RedditUrl::raw_url() const {
    return given_url;
}

bool redd::RedditUrl::isSubreddit() const {
/* TODO */
}

void redd::RedditUrl::stripUrl() {
    return_url = stripUrl(return_url);
}

void redd::RedditUrl::resetToBase() {
    return_url = base_url;
}

void redd::RedditUrl::resetToRaw() {
    return_url = given_url;
}

void redd::RedditUrl::addJson() {

}


std::ostream& operator<<(std::ostream& os, const redd::RedditUrl& url) {
    os << url.url() << std::flush;
    return os;
}
