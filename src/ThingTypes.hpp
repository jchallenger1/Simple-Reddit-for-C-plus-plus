#ifndef THINGTYPES_HPP
#define THINGTYPES_HPP

#include <string>
#include <vector>

namespace redd {

struct Comment; // type prefix for T1
struct Link;    // type prefix for T3

/* Represention of the the structure :
 *  [ { T3 object
 *      {Link(only one)}
 *    }
 *    [
 *      T1 object
 *    ]
 *  ]
 */
struct PostCommentPair;
struct T3Listing;


struct Link {
    std::string author;
    std::string banned_by;
    std::string domain;
    std::string id;
    std::string link_flair_text;
    std::string name;
    std::string permalink;
    std::string selftext;
    std::string selftext_html;
    std::string subreddit;
    std::string subreddit_id;
    std::string subreddit_name_prefixed;
    std::string subreddit_type;
    std::string thumbnail;
    std::string title;
    std::string url;
    std::string whitelist_status;

    long long approved_at_utc;
    long long banned_at_utc;
    long long created_utc;
    long long edited;

    int downs;
    int gilded;
    int likes;
    int num_comments;
    int num_crossposts;
    int report_reasons;
    int score;
    int ups;
    int view_count;

    bool archived;
    bool can_gild;
    bool can_mod_post;
    bool clicked;
    bool hidden;
    bool hide_score;
    bool is_crosspostable;
    bool is_self;
    bool is_video;
    bool locked;
    bool over_18;
    bool spoiler;
    bool stickied;
    bool visted;
};

struct Comment {
    std::vector<Comment> children;

    std::string author;
    std::string banned_by;
    std::string body;
    std::string id;
    std::string link_id;
    std::string name;
    std::string parent_id;
    std::string subreddit;
    std::string subreddit_id;
    std::string subreddit_name_prefixed;
    std::string subreddit_type;

    long long banned_at_utc;
    long long created;
    long long created_utc;
    long long edited;

    int downs;
    int gilded;
    int likes;
    int num_reports;
    int score;
    int ups;

    bool archived;
    bool can_gild;
    bool can_mod_post;
    bool collapsed;
    bool is_sumbitter;
    bool saved;
    bool stickied;
};

struct T3Listing {
    std::string after;
    std::string before;
    std::vector<Link> links;
    std::string modhash;
};

struct PostCommentPair {
    Link link;
    std::vector<Comment> comments;
};


// Operators
bool operator ==(const Link& lhs, const Link& rhs);
bool operator !=(const Link& lhs, const Link& rhs);

bool operator ==(const Comment& lhs, const Comment& rhs);
bool operator !=(const Comment& lhs, const Comment& rhs);

bool operator ==(const T3Listing& lhs, const T3Listing& rhs);
bool operator !=(const T3Listing& lhs, const T3Listing& rhs);

bool operator ==(const PostCommentPair& lhs, const PostCommentPair& rhs);
bool operator !=(const PostCommentPair& lhs, const PostCommentPair& rhs);


namespace detail {
class ThingParser {
public:
    static Link parseLinkT3(const nlohmann::json&);
    static Comment parseCommentT1(const nlohmann::json&);

    //
    static void parseT3Object(T3Listing& dest, const nlohmann::json& json);
    static void parsePairObject(PostCommentPair& dest, const nlohmann::json& t3, const nlohmann::json& t1);
};

}//! detail namespace


}//! redd namespace



#endif // THINGTYPES_HPP
