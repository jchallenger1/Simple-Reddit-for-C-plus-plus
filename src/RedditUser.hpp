#ifndef REDDITUSER
#define REDDITUSER

#include <string>

#include "HelperFunctions.hpp"

namespace redd {

class RedditUser {
    friend bool operator==(const RedditUser& lhs, const RedditUser& rhs);
public:
    RedditUser(const std::string& user ="", const std::string& pass = "", const std::string& ID = "", const std::string& secret = "")
        : username(user),password(pass),client_ID(ID),client_secret(secret) {}

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

private:
    std::string username;
    std::string password;
    std::string client_ID;
    std::string client_secret;
    std::string access_token;

};

bool operator==(const RedditUser& lhs, const RedditUser& rhs);
bool operator!=(const RedditUser& lhs, const RedditUser& rhs);


}//! redd namepsace


#endif
