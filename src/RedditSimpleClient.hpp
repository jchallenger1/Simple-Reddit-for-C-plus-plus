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
    RedditSub subreddit(const RedditUrl& url);
    //std::string subreddit(const RedditUrl& url, const std::string& (item to search for))

private:
    Curl curl;
    void parseStr(const std::string& str, nlohmann::json&) const;
};





}//! redd namespace


#endif // REDDITCLIENT
