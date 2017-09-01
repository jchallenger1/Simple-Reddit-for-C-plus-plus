#ifndef REDDITCLIENT
#define REDDITCLIENT

#include <string>

#include "json.hpp"

#include "Curl.hpp"
#include "HelperFunctions.hpp"
#include "RedditUser.hpp"
#include "RedditError.hpp"
#include "RedditSub.hpp"


namespace redd {


/* Class to interact with the Reddit Api
* without the need of authentication.
*/
class RedditSimpleClient {
public:

    std::string requestToken(const redd::RedditUser& user);
    RedditSub subreddit();
private:
    Curl curl;
};

}





#endif // REDDITCLIENT
