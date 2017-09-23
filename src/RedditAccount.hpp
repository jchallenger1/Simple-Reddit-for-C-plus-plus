#ifndef APIMETHOD_REDDITACCOUNT
#define APIMETHOD_REDDITACCOUNT

#include <string>
#include <vector>

#include "Curl.hpp"
#include "RedditUser.hpp"

namespace redd {

class RedditAccount {
public:
    struct Me; //     *      return information for /api/v1/me
    struct MeKarma; //      /api/v1/me/karma
    struct MePrefs; //      /api/v1/me/prefs
    struct MeTrophies; //   /prefs/karma

    struct Blocked; //   *   /prefs/blocked and /api/v1/me/blocked (they are the same)
    struct Friends; //   *   /prefs/friends and /api/v1/me/friends (they are the same)
    struct Messaging; //    /prefs/messaging
    struct Trusted; //      /prefs/trusted

    struct Person; // struct to represent data returned from /pref/blocked(/friends) and /me/blocked(/friends);

    Me me(const RedditUser&); // method to return /api/v1/me

    Friends friends(const RedditUser&); // /prefs/friends & /api/v1/me/friends
    Blocked blocked(const RedditUser&); // /prefs/blocked & /api/v1/me/blocked
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

struct RedditAccount::Friends {
    std::vector<RedditAccount::Person> people;
    int size;
};

struct RedditAccount::Blocked {
    std::vector<RedditAccount::Person> people;
    int size;
};

struct RedditAccount::Person {
    long long date;
    std::string id;
    std::string name;
};


}//! redd namespace

#endif
