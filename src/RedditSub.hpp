#ifndef REDDITSUBREDDIT
#define REDDITSUBREDDIT

#include <string>
#include <vector>

#include "json.hpp"

namespace redd {
    /* Interface to interact and use information from Reddit Subreddits. */
class RedditSub {
public:
    struct SimplePost; // A way to return data from json requests, this should be changed in the future
    RedditSub(const std::string& unparsed_json);
    RedditSub(const nlohmann::basic_json&);
    RedditSub(const RedditSub::SimpleSub&);
    std::vector<SimpleSub> posts;
    bool hasData() const;
private:
    void parseStr(const string&);
    void parseSimpleJson(const nlohmann::basic_json&);
};

struct RedditSub::SimplePost {
    std::vector<std::pair<std::string, std::pair<int,int> > > preview; //string is the url pair is the dimensions
    std::string after; // the id of the next pair of posts
    std::string author; // the id of the author
    std::string before; // the id of the previous pair of posts
    std::string id; // id of the post
    std::string permalink; // url of the post's comment section or post page
    std::string selftext; // text in the post
    std::string subreddit; // name of the subreddit
    std::string subreddit_id; // id of the subreddit
    std::string subreddit_name_prefix; // the name of the subreddit with a prefix
    std::string thumbnail; // the url of the thumbnail
    std::string title; // title of the post
    std::string url; // the url where the post redirects to
    unsigned long created_utc; // the time the post was created in utc format
    unsigned int gilded; // number of gilded recived on the post
    int downs;
    int ups;
    int num_comments;
    bool hidden;
    bool over_18;
};

}//! redd namespace


#endif // REDDITSUBREDDIT
