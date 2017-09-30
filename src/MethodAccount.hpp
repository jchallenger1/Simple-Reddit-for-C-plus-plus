#ifndef APIMETHOD_ACCOUNT
#define APIMETHOD_ACCOUNT

#include <string>
#include <vector>

#include "Curl.hpp"
#include "RedditUser.hpp"
#include "Method.hpp"

namespace redd {

class MethodAccount : public detail::Method {
public:
    struct Me; //           return information for /api/v1/me
    struct MeKarma; //      /api/v1/me/karma
    struct MePrefs; //      /api/v1/me/prefs
    struct MeTrophies; //   /api/v1/me/trophies  *NO IMPLEMENTATION*

    struct Blocked; //      /prefs/blocked and /api/v1/me/blocked (they are the same)
    struct Friends; //      /prefs/friends and /api/v1/me/friends (they are the same)
    struct Messaging; //    /prefs/messaging
    struct Trusted; //      /prefs/trusted

    struct Person; // struct to represent data returned from /pref/blocked(/friends) and /me/blocked(/friends);
    struct Karma; // represent return from /api/ve/me/karma.

    explicit MethodAccount() : detail::Method() {}
    MethodAccount(const Method& m);

    Me me(const RedditUser&); // method to return /api/v1/me
    Friends friends(const RedditUser&); // /prefs/friends & /api/v1/me/friends
    Blocked blocked(const RedditUser&); // /prefs/blocked & /api/v1/me/blocked
    Trusted trusted(const RedditUser&); // /prefs/trusted
    Messaging messaging(const RedditUser&); // /prefs/messaging
    MeKarma karma(const RedditUser&); // /api/v1/me/karma
    MePrefs prefs(const RedditUser&); // api/v1/me/prefs
};

struct MethodAccount::Me {
    std::string id;
    std::string name;
    std::string oauth_client_id;

    long long created;
    long long created_utc;

    int comment_karma;
    int gold_credits;
    int inbox_count;
    int link_karma;

    bool has_mail;
    bool has_subscribed;
    bool has_verified_email;
    bool hide_from_robots;
    bool in_beta;
    bool is_employee;
    bool is_gold;
    bool is_mod;
    bool is_suspended;
    bool over_18;
    bool pref_no_profanity;

};

struct MethodAccount::MePrefs {
    std::string lang;
    std::string media;
    std::string default_comment_sort;
    std::string accept_pms;

    int numsites;
    int num_comments;
    int min_link_score;

    bool activity_relevant_ads;
    bool allow_clicktracking;
    bool clickgadget;
    bool collapse_read_messages;
    bool domain_details;
    bool email_digests;
    bool email_messages;
    bool enable_default_themes;
    bool hide_abusive_comments;
    bool hide_ads;
    bool hide_downs;
    bool hide_locationbar;
    bool hide_ups;
    bool ignore_suggested_sort;
    bool label_nsfw;
    bool mark_messages_read;
    bool monitor_mentions;
    bool no_profanity;
    bool over_18;
    bool private_feeds;
    bool public_votes;
    bool search_include_over_18;
    bool show_flair;
    bool show_link_flair;
    bool show_snoovatar;
    bool show_stylesheets;
    bool show_trending;
    bool threaded_messages;
    bool use_global_defaults;
};

struct MethodAccount::MeKarma {
    std::vector<MethodAccount::Karma> karmas;
    int size;
};

struct MethodAccount::Karma {
    std::string sr;
    int comment_karma;
    int link_karma;
};

struct MethodAccount::Messaging {
    std::vector<MethodAccount::Person> people;
    int size;
};

struct MethodAccount::Trusted {
    std::vector<MethodAccount::Person> people;
    int size;
};

struct MethodAccount::Friends {
    std::vector<MethodAccount::Person> people;
    int size;
};

struct MethodAccount::Blocked {
    std::vector<MethodAccount::Person> people;
    int size;
};

struct MethodAccount::Person {
    long long date;
    std::string id;
    std::string name;
};


}//! redd namespace

#endif
