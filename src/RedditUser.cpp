#include <string>
#include "RedditUser.hpp"


namespace redd {



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
