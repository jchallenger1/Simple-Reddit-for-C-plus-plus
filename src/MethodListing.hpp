#ifndef APIMETHOD_LISTING
#define APIMETHOD_LISTING

#include <string>
#include <memory>

#include "Curl.hpp"
#include "RedditUser.hpp"
#include "Method.hpp"

namespace redd {

/*
 * In this class currently, there are many structs and functions that
 * do similar work making a lot unneccesary. However the class should first get all
 * listing api methods working before working on connecting them together.
 */

class MethodListing : public detail::Method {
public:
    struct Inputs;

    struct Comment; // type prefix for T1
    struct Account; // T2
    struct Link;    // T3...
    struct Message;
    struct Subreddit;
    struct Award;

    struct Hot;
    struct New;
    struct Random;
    struct Top;
    struct Controversial;


    explicit MethodListing()
        : detail::Method(), extra_inputs(std::make_unique<Inputs>()) {}
    MethodListing(const detail::Method& m);


    void setInputs(const Inputs&);
    void resetInputs();
    Inputs& inputs();

    New _new(const RedditUser&, const std::string& s);
    Hot hot(const RedditUser&, const std::string& s);
    Random random(const RedditUser&, const std::string&);
    Top top(const RedditUser&, const std::string& s);
    Controversial controversial(const RedditUser&, const std::string& s);
private:
    std::unique_ptr<Inputs> extra_inputs;

    Link parseLinkT3(const nlohmann::json&) const;
    Comment parseCommentT1(const nlohmann::json&) const;
    std::string inputsToString() const;
};

struct MethodListing::Inputs {
    std::string after;
    std::string before;
    std::string g;
    std::string t;
    std::string show;
    int count;
    int limit;
    bool sr_detail;
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

struct MethodListing::Hot {
    std::string after;
    std::string before;
    std::vector<Link> links;
    std::string modhash;
};

struct MethodListing::New {
    std::string after;
    std::string before;
    std::vector<Link> links;
    std::string modhash;
};

struct MethodListing::Random {
    Link link;
    std::vector<Comment> comments;
};

struct MethodListing::Top {
    std::string after;
    std::string before;
    std::vector<Link> links;
    std::string modhash;
};

struct MethodListing::Controversial {
    std::string after;
    std::string before;
    std::vector<Link> links;
    std::string modhash;
};

} //! redd namespace



#endif // APIMETHOD_LISTING
