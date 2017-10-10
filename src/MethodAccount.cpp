#include <string>
#include <vector>

#include "json.hpp"

#include "MethodAccount.hpp"
#include "RedditUser.hpp"
#include "RedditError.hpp"

namespace redd {

MethodAccount::MethodAccount(const Method& m){
    setDependencyOn(m);
}

MethodAccount::Me MethodAccount::me(const RedditUser& user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    MethodAccount::Me return_me;
    curl->setHttpHeader("Authorization: bearer " + user.token());
    std::string unparsed = curl->simpleGet("https://oauth.reddit.com/api/v1/me");
    nlohmann::json json;
    strToJson(unparsed, json);
    using detail::setIfNotNull;

    // Strings
    setIfNotNull(return_me.id, json, "id", "");
    setIfNotNull(return_me.name, json, "name", "");
    setIfNotNull(return_me.oauth_client_id, json, "oauth_client_id", "");

    // Intergrals
    setIfNotNull(return_me.created, json, "created", static_cast<long long>(-1));
    setIfNotNull(return_me.created_utc, json, "created_utc", static_cast<long long>(-1));
    setIfNotNull(return_me.comment_karma, json, "comment_karma", -1);
    // gold_creddits in the json api could be a typo, this could be changed in the future
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

MethodAccount::Friends MethodAccount::friends(const RedditUser& user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    MethodAccount::Friends friend_entry;
    curl->setHttpHeader("Authorization: bearer " + user.token());
    std::string unparsed = curl->simpleGet("https://oauth.reddit.com/prefs/friends");
    nlohmann::json json;
    strToJson(unparsed, json);

    using detail::setIfNotNull;
    for (const auto& lists : json) {
        if (lists.find("data") != lists.end()) {
            if (lists["data"].find("children") != lists["data"].end()) {
                for (auto per = lists["data"]["children"].begin();
                     per != lists["data"]["children"].end(); per++) {
                    MethodAccount::Person single;
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


MethodAccount::Blocked MethodAccount::blocked(const RedditUser& user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    MethodAccount::Blocked block_entry;
    curl->setHttpHeader("Authorization: bearer " + user.token());
    std::string unparsed = curl->simpleGet("https://oauth.reddit.com/prefs/blocked");
    nlohmann::json json;
    strToJson(unparsed, json);

    using detail::setIfNotNull;
    if (json.find("data") != json.end()) {
        if (json["data"].find("children") != json["data"].end()) {
            for (auto per = json["data"]["children"].begin();
                 per != json["data"]["children"].end(); per++ ) {
                MethodAccount::Person single;
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

MethodAccount::Trusted MethodAccount::trusted(const RedditUser& user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    MethodAccount::Trusted trust_entry;
    curl->setHttpHeader("Authorization: bearer " + user.token());
    std::string unparsed = curl->simpleGet("https://oauth.reddit.com/prefs/trusted");
    nlohmann::json json;
    strToJson(unparsed, json);

    using detail::setIfNotNull;
    if (json.find("data") != json.end()) {
        if (json["data"].find("children") != json["data"].end()) {
            for (auto per = json["data"]["children"].begin();
                 per != json["data"]["children"].end(); per++ ) {
                MethodAccount::Person single;
                setIfNotNull(single.date, *per, "date", static_cast<long long>(-1));
                setIfNotNull(single.id, *per, "id", "");
                setIfNotNull(single.name, *per, "name", "");
                trust_entry.people.push_back(single);
            }
        }
    }
    trust_entry.size = trust_entry.people.size();
    return trust_entry;
}

MethodAccount::Messaging MethodAccount::messaging(const RedditUser& user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    MethodAccount::Messaging message_entry;
    curl->setHttpHeader("Authorization: bearer " + user.token());
    std::string unparsed = curl->simpleGet("https://oauth.reddit.com/prefs/messaging");
    nlohmann::json json;
    strToJson(unparsed, json);

    using detail::setIfNotNull;
    for (const auto& lists : json) {
        if (lists.find("data") != lists.end()) {
            if (lists["data"].find("children") != lists["data"].end()) {
                for (auto per = lists["data"]["children"].begin();
                     per != lists["data"]["children"].end(); per++) {
                    MethodAccount::Person single;
                    setIfNotNull(single.date, *per, "date", static_cast<long long>(-1));
                    setIfNotNull(single.id, *per, "id", "");
                    setIfNotNull(single.name, *per, "name", "");
                    message_entry.people.push_back(single);
                }
            }
        }
    }
    message_entry.size = message_entry.people.size();
    return message_entry;
}

MethodAccount::MeKarma MethodAccount::karma(const RedditUser& user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    MethodAccount::MeKarma karma_entry;
    curl->setHttpHeader("Authorization: bearer " + user.token());
    std::string unparsed = curl->simpleGet("https://oauth.reddit.com/api/v1/me/karma");
    nlohmann::json json;
    strToJson(unparsed, json);

    using detail::setIfNotNull;
    if (json.find("data") != json.end()) {
        for (auto iter = json["data"].begin(); iter != json["data"].end(); iter++) {
            MethodAccount::Karma single;
            setIfNotNull(single.sr, *iter, "sr", "");
            setIfNotNull(single.comment_karma, *iter, "comment_karma", -1);
            setIfNotNull(single.link_karma, *iter, "link_karma", -1);
            karma_entry.karmas.push_back(single);
        }
    }
    karma_entry.size = karma_entry.karmas.size();
    return karma_entry;
}

MethodAccount::MePrefs MethodAccount::prefs(const RedditUser & user) {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    MethodAccount::MePrefs pref;
    curl->setHttpHeader("Authorization: bearer " + user.token());
    std::string unparsed = curl->simpleGet("https://oauth.reddit.com/api/v1/me/prefs");
    nlohmann::json json;
    strToJson(unparsed, json);

    using detail::setIfNotNull;
    // String types
    setIfNotNull(pref.lang, json, "lang", "");
    setIfNotNull(pref.media, json, "media", "");
    setIfNotNull(pref.default_comment_sort, json, "default_comment_sort", "");
    setIfNotNull(pref.accept_pms, json, "accept_pms", "");
    // Intergral types
    setIfNotNull(pref.numsites, json, "numsites", -1);
    setIfNotNull(pref.num_comments, json, "num_comments", -1);
    setIfNotNull(pref.min_link_score, json, "min_link_score", -1);

    //Boolean types
    setIfNotNull(pref.activity_relevant_ads, json, "activity_relevant_ads", false);
    setIfNotNull(pref.allow_clicktracking, json, "allow_clicktracking", false);
    setIfNotNull(pref.clickgadget, json, "clickgadget", false);
    setIfNotNull(pref.collapse_read_messages, json, "collapse_read_messages", false);
    setIfNotNull(pref.domain_details, json, "domain_details", false);
    setIfNotNull(pref.email_digests, json, "email_digests", false);
    setIfNotNull(pref.email_messages, json, "email_messages", false);
    setIfNotNull(pref.enable_default_themes, json, "enable_default_themes", false);
    setIfNotNull(pref.hide_abusive_comments, json, "hide_abusive_comments", false);
    setIfNotNull(pref.hide_ads, json, "hide_ads", false);
    setIfNotNull(pref.hide_downs, json, "hide_downs", false);
    setIfNotNull(pref.hide_locationbar, json, "hide_locationbar", false);
    setIfNotNull(pref.hide_ups, json, "hide_ups", false);
    setIfNotNull(pref.ignore_suggested_sort, json, "ignore_suggested_sort", false);
    setIfNotNull(pref.label_nsfw, json, "label_nsfw", false);
    setIfNotNull(pref.mark_messages_read, json, "mark_messages_read", false);
    setIfNotNull(pref.monitor_mentions, json, "monitor_mentions", false);
    setIfNotNull(pref.no_profanity, json, "no_profanity", false);
    setIfNotNull(pref.over_18, json, "over_18", false);
    setIfNotNull(pref.private_feeds, json, "private_feeds", false);
    setIfNotNull(pref.public_votes, json, "public_votes", false);
    setIfNotNull(pref.search_include_over_18, json, "search_include_over_18", false);
    setIfNotNull(pref.show_flair, json, "show_flair", false);
    setIfNotNull(pref.show_link_flair, json, "show_link_flair", false);
    setIfNotNull(pref.show_snoovatar, json, "show_snoovatar", false);
    setIfNotNull(pref.show_stylesheets, json, "show_stylesheets", false);
    setIfNotNull(pref.show_trending, json, "show_trending", false);
    setIfNotNull(pref.threaded_messages, json, "threaded_messages", false);
    setIfNotNull(pref.use_global_defaults, json, "use_global_defaults", false);

    return pref;
}

}//! redd namespace

