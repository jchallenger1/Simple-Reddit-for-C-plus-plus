#ifndef APIMETHOD_REDDITACCOUNT
#define APIMETHOD_REDDITACCOUNT

#include <string>

#include "Curl.hpp"
#include "RedditUser.hpp"

namespace redd {

class RedditAccount {
public:
    struct Me; //           return information for /api/v1/me
    struct MeBlocked; //    for /api/v1/me/blocked
    struct MeFriends; //    /api/v1/me/friends
    struct MeKarma; //      /api/v1/me/karma
    struct MePrefs; //      /api/v1/me/prefs
    struct MeTrophies; //   /prefs/karma

    struct Blocked; //      /prefs/blocked
    struct Friends; //      /prefs/friends
    struct Messaging; //    /prefs/messaging
    struct Trusted; //      /prefs/trusted

    RedditAccount::Me acc_me(const RedditUser&) const;
private:
    detail::Curl curl;
};

struct RedditAccount::Me {
    std::string id;
    std::string name;
    std::string oauth_client_id;

    long long created;
    long long created_utc;

    int comment_karma;
    int gold_creddits;// <-- is not a typo.
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

}//! redd namespace

#endif
