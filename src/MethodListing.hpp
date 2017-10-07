#ifndef APIMETHOD_LISTING
#define APIMETHOD_LISTING

#include <string>
#include <memory>

#include "Curl.hpp"
#include "RedditUser.hpp"
#include "Method.hpp"

namespace redd {

class MethodListing : public detail::Method {
public:
    struct Inputs; // representation of query strings user is able to input.

    struct Comment; // type prefix for T1
    struct Link;    // type prefix for T3

    /* Represention of the the structure :
     *  [ { T3 object
     *      {Link(one)}
     *    }
     *    [
     *      T1 object
     *    ]
     *  ]
     */
    struct PostCommentPair;
    struct T3Listing;

    // constructors
    explicit MethodListing() : detail::Method(), extra_inputs(std::make_unique<Inputs>()) {}
    MethodListing(const detail::Method& m);

    // functions for inputs
    void setInputs(const Inputs&);
    void resetInputs();
    Inputs& inputs();

    // *** function endpoints ***
    // missing /api/trending_subreddits

    // calls [/r/subreddit]/comments/article
    PostCommentPair commentTree(const RedditUser&, const std::string& subreddit, const std::string& id);
    // calls [/r/subreddit]/random
    PostCommentPair random(const RedditUser&, const std::string& subreddit); // this function may not work at times
    // calls /by_id/names
    Link by_id(const RedditUser&, const std::string& fullname);
    // calls /duplicates/article
    std::vector<Link> duplicates(const RedditUser&, const std::string& id); // id is not the fullname!, ex : 74pqir
    // rests calls [/r/subreddit]/new, [/r/subreddit]/hot ...
    T3Listing _new(const RedditUser&, const std::string& subreddit);
    T3Listing hot(const RedditUser&, const std::string& subreddit);
    T3Listing top(const RedditUser&, const std::string& subreddit);
    T3Listing controversial(const RedditUser&, const std::string& subreddit);
    T3Listing rising(const RedditUser&, const std::string& subreddit);
private:
    std::unique_ptr<Inputs> extra_inputs;

    Link parseLinkT3(const nlohmann::json&) const;
    Comment parseCommentT1(const nlohmann::json&) const;
    std::string inputsToString() const;
    void parseT3Object(T3Listing& dest, const nlohmann::json& json) const;
    void parsePairObject(PostCommentPair& dest, const nlohmann::json& t3, const nlohmann::json& t1) const;
    inline void setToken(const RedditUser&);
};

struct MethodListing::Inputs {
    std::string after;
    std::string article;
    std::string before;
    std::string comment;
    std::string g;
    std::string t;
    std::string show;
    std::string sort;
    int count;
    int depth;
    int limit;
    short context;
    short truncate;
    bool showedits;
    bool showmore;
    bool sr_detail;
    bool threaded;
};


struct MethodListing::Link {
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

struct MethodListing::Comment {
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

struct MethodListing::T3Listing {
    std::string after;
    std::string before;
    std::vector<Link> links;
    std::string modhash;
};

struct MethodListing::PostCommentPair {
    Link link;
    std::vector<Comment> comments;
};

// ********************
// Non Member Functions
// ********************

bool operator ==(const MethodListing::Link& lhs, const MethodListing::Link& rhs);
bool operator !=(const MethodListing::Link& lhs, const MethodListing::Link& rhs);

bool operator ==(const MethodListing::Comment& lhs, const MethodListing::Comment& rhs);
bool operator !=(const MethodListing::Comment& lhs, const MethodListing::Comment& rhs);

bool operator ==(const MethodListing::T3Listing& lhs, const MethodListing::T3Listing& rhs);
bool operator !=(const MethodListing::T3Listing& lhs, const MethodListing::T3Listing& rhs);

bool operator ==(const MethodListing::PostCommentPair& lhs, const MethodListing::PostCommentPair& rhs);
bool operator !=(const MethodListing::PostCommentPair& lhs, const MethodListing::PostCommentPair& rhs);

} //! redd namespace



#endif // APIMETHOD_LISTING
