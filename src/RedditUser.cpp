#include "RedditUser.hpp"

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
