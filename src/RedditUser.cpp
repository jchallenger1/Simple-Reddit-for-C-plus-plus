#include "RedditUser.hpp"

void redd::RedditUser::setUser(const char* str) {
    username = str;
}

void redd::RedditUser::setUser(const std::string& str) {
    username = str;
}

void redd::RedditUser::setUser(const std::string&& str) {
    setUser(str);
}


void redd::RedditUser::setPass(const char* str) {
    password = str;
}

void redd::RedditUser::setPass(const std::string& str) {
    password = str;
}

void redd::RedditUser::setPass(const std::string&& str) {
    setPass(str);
}


void redd::RedditUser::setID(const char* str) {
    client_ID = str;
}

void redd::RedditUser::setID(const std::string& str) {
    client_ID = str;
}

void redd::RedditUser::setID(const std::string&& str) {
    setID(str);
}


void redd::RedditUser::setSecret(const char* str) {
    client_secret = str;
}

void redd::RedditUser::setSecret(const std::string& str) {
    client_secret = str;
}

void redd::RedditUser::setSecret(const std::string&& str) {
    setSecret(str);
}


void redd::RedditUser::setToken(const char* str) {
    access_token = str;
}

void redd::RedditUser::setToken(const std::string& str) {
    access_token = str;
}

void redd::RedditUser::setToken(const std::string&& str) {
    setToken(str);
}


std::string redd::RedditUser::user() const {
    return username;
}

std::string redd::RedditUser::pass() const {
    return password;
}

std::string redd::RedditUser::ID() const {
    return client_ID;
}

std::string redd::RedditUser::secret() const {
    return client_secret;
}

std::string redd::RedditUser::token() const {
    return access_token;
}

bool redd::RedditUser::isFilled() const {
    return !username.empty() && !password.empty() &&
            !client_ID.empty()&& !client_secret.empty();
}

bool redd::RedditUser::isComplete() const {
    return isFilled() && !access_token.empty();
}

bool redd::operator==(const RedditUser& lhs, const RedditUser& rhs) {
    return  lhs.password == rhs.password && lhs.client_secret == rhs.client_secret &&
            lhs.username == rhs.username && lhs.client_ID == rhs.client_ID;
}

bool redd::operator!=(const RedditUser& lhs, const RedditUser& rhs) {
    return !(lhs == rhs);
}
