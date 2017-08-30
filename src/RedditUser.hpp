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

        template<typename T>
        void setUser(T&& str);

        template<typename T>
        void setPass(T&& str);

        template<typename T>
        void setID(T&& str);

        template<typename T>
        void setSecret(T&& str);

        template<typename T>
        void setToken(T&& str);

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



    template<typename T>
    void redd::RedditUser::setUser(T&& username_str) {
        static_assert(redd::IsStrOrPtr<T>, "Object must be of type const char* or std::string");
        username = std::forward<T>(username_str);
    }

    template<typename T>
    void redd::RedditUser::setPass(T&& pass_str) {
        static_assert(redd::IsStrOrPtr<T>, "Object must be of type const char* or std::string");
        password = std::forward<T>(pass_str);
    }

    template<typename T>
    void redd::RedditUser::setID(T&& ID_str) {
        static_assert(redd::IsStrOrPtr<T>, "Object must be of type const char* or std::string");
        client_ID = std::forward<T>(ID_str);
    }

    template<typename T>
    void redd::RedditUser::setSecret(T&& secret_str) {
        static_assert(redd::IsStrOrPtr<T>, "Object must be of type const char* or std::string");
        client_secret = std::forward<T>(secret_str);
    }

    template<typename T>
    void redd::RedditUser::setToken(T&& secret_str) {
        static_assert(redd::IsStrOrPtr<T>, "Object must be of type const char* or std::string");
        access_token = std::forward<T>(secret_str);
    }


}
#endif
