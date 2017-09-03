#ifndef REDDITCLIENT
#define REDDITCLIENT

#include <string>

#include "json.hpp"

#include "Curl.hpp"
#include "HelperFunctions.hpp"
#include "RedditUser.hpp"
#include "RedditError.hpp"
#include "RedditSub.hpp"
#include "RedditUrl.hpp"

namespace redd {


/* Class to interact with the Reddit Api
* without the need of authentication.
*/
class RedditSimpleClient {
public:

    std::string requestToken(const redd::RedditUser& user);
    template<typename T>
    RedditSub subreddit(T&& url);
    RedditSub subreddit(const RedditUrl url);
private:
    Curl curl;
    template<typename T>
    void parseStr(T&& str, nlohmann::json&) const;
};

template<typename T>
RedditSub RedditSimpleClient::subreddit(T&& a) {
    static_assert(IsStrOrPtr<T>, "Object must be of type const char* or std::string");
    subreddit(RedditSub(std::forward<T>(a)));
}

template<typename T>
void RedditSimpleClient::parseStr(const T&& str, nlohmann::json& json_obj) const {
    try {
        json_obj = nlohmann::json::parse(std::forward<T>(str));
    }
    catch(const std::exception& err) {
        throw RedditError("A problem occured when parsing, Json Error:|" + err.what() + "|");
    }
}





#endif // REDDITCLIENT
