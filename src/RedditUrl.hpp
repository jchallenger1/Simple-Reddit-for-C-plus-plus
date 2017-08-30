#ifndef REDDITURL
#define REDDITTURL

#include <string>
#include <vector>

namespace redd {
    /* An interface to deal with various types of reddit urls and a way to process them */
    class RedditUrl {
    public:

    private:
        std::string json_url;
        std::string given_url;
        std::string base_url;
        std::vector<std::string> query_strings;
    };
}


#endif
