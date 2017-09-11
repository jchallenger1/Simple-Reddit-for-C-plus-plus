#include <string>
#include "RedditUser.hpp"


namespace redd {


void RedditUser::setUser(const std::string& str) {
    username = str;
}

void RedditUser::setPass(const std::string& str) {
    password = str;
}

void RedditUser::setID(const std::string& str) {
    client_ID = str;
}

void RedditUser::setSecret(const std::string& str) {
    client_secret = str;
}

void RedditUser::setToken(const std::string& str) {
    // every hour the user must get another token.
    time_token = std::chrono::system_clock::now() + std::chrono::hours(1);
    access_token = str;
}


std::string RedditUser::user() const {
    return username;
}

std::string RedditUser::pass() const {
    return password;
}

std::string RedditUser::ID() const {
    return client_ID;
}

std::string RedditUser::secret() const {
    return client_secret;
}

std::string RedditUser::token() const {
    return access_token;
}

bool RedditUser::isFilled() const {
    return !username.empty() && !password.empty() &&
            !client_ID.empty()&& !client_secret.empty();
}

bool RedditUser::isComplete() const {
    return isFilled() && !access_token.empty();
}

bool operator==(const RedditUser& lhs, const RedditUser& rhs) {
    return  lhs.password == rhs.password && lhs.client_secret == rhs.client_secret &&
            lhs.username == rhs.username && lhs.client_ID == rhs.client_ID;
}

bool operator!=(const RedditUser& lhs, const RedditUser& rhs) {
    return !(lhs == rhs);
}

}//! redd namespace
