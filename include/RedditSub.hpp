#ifndef REDDITSUBREDDIT
#define REDDITSUBREDDIT

#include <string>
#include <vector>
#include <utility>

#include "json.hpp"

namespace redd {
    /* Interface to interact and use information from Reddit Subreddits. */
class RedditSub {
public:
    struct ExternalPost; // A way to return data from json requests, this should be changed in the future
    RedditSub(const std::string& unparsed_json);
    RedditSub(const nlohmann::json&);
    void fromStr(const std::string&);
    void fromJson(const nlohmann::json&);
    std::vector<ExternalPost> posts() const;
    bool hasData() const;
private:
   nlohmann::json redd_json;
};

struct RedditSub::ExternalPost {
    std::vector<std::pair<std::string, std::pair<int,int> > > preview; //string is the url pair is the dimensions in (w)*(h)
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
    /* All numbers return -1 if it was not found. */
    long long created_utc; // the time the post was created in utc format
    int gilded; // number of gilded recived on the post
    int downs;
    int ups;
    int num_comments;
    bool hidden;
    bool over_18;
};


bool operator ==(const RedditSub::ExternalPost&, const RedditSub::ExternalPost&);

bool operator !=(const RedditSub::ExternalPost&, const RedditSub::ExternalPost&);

}//! redd namespace


#endif // REDDITSUBREDDIT
