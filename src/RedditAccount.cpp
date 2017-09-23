#include <string>
#include <vector>

#include "json.hpp"

#include "RedditAccount.hpp"
#include "RedditUser.hpp"
#include "RedditError.hpp"

namespace redd {


RedditAccount::Me RedditAccount::me(const RedditUser& user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    RedditAccount::Me return_me;
    curl.setHttpHeader("Authorization: bearer " + user.token());
    std::string unparsed = curl.simpleGet("https://oauth.reddit.com/api/v1/me");
    nlohmann::json json = nlohmann::json::parse(unparsed);
    using detail::setIfNotNull;

    // Strings
    setIfNotNull(return_me.id, json, "id", "");
    setIfNotNull(return_me.name, json, "name", "");
    setIfNotNull(return_me.oauth_client_id, json, "oauth_client_id", "");

    // Intergrals
    setIfNotNull(return_me.created, json, "created", static_cast<long long>(-1));
    setIfNotNull(return_me.created_utc, json, "created_utc", static_cast<long long>(-1));
    setIfNotNull(return_me.comment_karma, json, "comment_karma", -1);
    // gold_creddits in the json api is a typo, this could be changed in the future
    // to gold_credits, therefore we must check both.
    setIfNotNull(return_me.gold_credits, json, "gold_creddits", -1);
    if (return_me.gold_credits == -1) { // typo in json is fixed
        setIfNotNull(return_me.gold_credits, json, "gold_credits", -1);
    }
    setIfNotNull(return_me.inbox_count, json, "inbox_count", -1);
    setIfNotNull(return_me.link_karma, json, "link_karma", -1);

    // Booleans
    setIfNotNull(return_me.has_mail, json, "has_mail", false);
    setIfNotNull(return_me.has_subscribed, json, "has_subscribed", false);
    setIfNotNull(return_me.has_verified_email, json, "has_verified_email", false);
    setIfNotNull(return_me.hide_from_robots, json, "hide_from_robots", false);
    setIfNotNull(return_me.in_beta, json, "in_beta", false);
    setIfNotNull(return_me.is_employee, json, "is_employee", false);
    setIfNotNull(return_me.is_gold, json, "is_gold", false);
    setIfNotNull(return_me.is_mod, json, "is_mod", false);
    setIfNotNull(return_me.is_suspended, json, "is_suspended", false);
    setIfNotNull(return_me.over_18, json, "over_18", false);
    setIfNotNull(return_me.pref_no_profanity, json, "pref_no_profanity", false);

    return return_me;
}

RedditAccount::Friends RedditAccount::friends(const RedditUser& user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    RedditAccount::Friends friend_entry;
    curl.setHttpHeader("Authorization:bearer " + user.token());
    std::string unparsed = curl.simpleGet("https://oauth.reddit.com/prefs/friends");
    nlohmann::json json= nlohmann::json::parse(unparsed);


    using detail::setIfNotNull;
    for (const auto& lists : json) {
        if (lists.find("data") != lists.end()) {
            if (lists["data"].find("children") != lists["data"].end()) {
                for (auto per = lists["data"]["children"].begin();
                     per != lists["data"]["children"].end(); per++) {
                    RedditAccount::Person single;
                    setIfNotNull(single.date, *per, "date", static_cast<long long>(-1));
                    setIfNotNull(single.id, *per, "id", "");
                    setIfNotNull(single.name, *per, "name", "");
                    friend_entry.people.push_back(single);
                }
            }
        }
    }
    friend_entry.size = friend_entry.people.size();
    return friend_entry;
}


RedditAccount::Blocked RedditAccount::blocked(const RedditUser& user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    RedditAccount::Blocked block_entry;
    curl.setHttpHeader("Authorization:bearer " + user.token());
    std::string unparsed = curl.simpleGet("https://oauth.reddit.com/prefs/friends");
    nlohmann::json json= nlohmann::json::parse(unparsed);


    using detail::setIfNotNull;
    if (json.find("data") != json.end()) {
        if (json["data"].find("children") != json["data"].end()) {
            for (auto per = json["data"]["children"].begin();
                 per != json["data"]["children"].end(); per++ ) {
                RedditAccount::Person single;
                setIfNotNull(single.date, *per, "date", static_cast<long long>(-1));
                setIfNotNull(single.id, *per, "id", "");
                setIfNotNull(single.name, *per, "name", "");
                block_entry.people.push_back(single);
            }
        }
    }
    block_entry.size = block_entry.people.size();
    return block_entry;
}

}//! redd namespace

