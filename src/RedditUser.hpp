#ifndef REDDITUSER
#define REDDITUSER

#include <string>
#include <chrono>

#include "HelperFunctions.hpp"

namespace redd {

class RedditUser {
    friend bool operator==(const RedditUser& lhs, const RedditUser& rhs);
public:
    explicit RedditUser(const std::string& user ="", const std::string& pass = "", const std::string& ID = "", const std::string& secret = "")
        : username(user),password(pass),client_ID(ID),client_secret(secret),
    time_token(std::chrono::system_clock::now()) {}

    void setUser(const std::string& str);

    void setPass(const std::string& str);

    void setID(const std::string& str);

    void setSecret(const std::string& str);

    void setToken(const std::string& str);

    operator bool() { return isComplete(); }


    bool isFilled() const;
    bool isComplete() const;

    std::string user() const;
    std::string pass() const;
    std::string ID() const;
    std::string secret() const;
    std::string token() const;

    // access_token is only valid for 1 hour, function determines if an hour has passed.
    template<typename DurationT = std::chrono::seconds>
    typename DurationT::rep timeLeft() const;
private:
    std::string username;
    std::string password;
    std::string client_ID;
    std::string client_secret;
    std::string access_token;
    std::chrono::time_point<std::chrono::system_clock> time_token;
};

bool operator==(const RedditUser& lhs, const RedditUser& rhs);
bool operator!=(const RedditUser& lhs, const RedditUser& rhs);

template<typename DurationT>
typename DurationT::rep RedditUser::timeLeft() const {
    auto g = std::chrono::duration_cast<DurationT>(time_token - std::chrono::system_clock::now());
    return g.count();
}



}//! redd namepsace


#endif
