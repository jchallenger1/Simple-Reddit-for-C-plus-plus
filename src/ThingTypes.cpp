#include <vector>

#include "json.hpp"

#include "ThingTypes.hpp"
#include "HelperFunctions.hpp"
#include "RedditError.hpp"

namespace redd {





// Operators
bool operator ==(const Link& lhs, const Link& rhs) {
    return lhs.author == rhs.author && lhs.id == rhs.id && lhs.name == rhs.name &&
            lhs.subreddit_id == rhs.subreddit_id && lhs.title == rhs.title && rhs.url == lhs.url &&
            lhs.created_utc == rhs.created_utc && lhs.score == rhs.score;
}

bool operator !=(const Link& lhs, const Link& rhs) {
    return !(lhs == rhs);
}

bool operator ==(const Comment& lhs, const Comment& rhs) {
    return lhs.children.size() == rhs.children.size() && lhs.author == rhs.author && lhs.id == rhs.id &&
            lhs.link_id == rhs.link_id && lhs.parent_id == rhs.parent_id &&
            lhs.subreddit_id == rhs.subreddit_id && lhs.created_utc == rhs.created_utc;
}

bool operator !=(const Comment& lhs, const Comment& rhs) {
    return !(lhs == rhs);
}

bool operator ==(const T3Listing& lhs, const T3Listing& rhs) {
    return lhs.after == rhs.after && lhs.before == rhs.before
            && lhs.links == rhs.links && lhs.modhash == rhs.modhash;
}

bool operator !=(const T3Listing& lhs, const T3Listing& rhs) {
    return !(lhs == rhs);
}

bool operator ==(const PostCommentPair& lhs, const PostCommentPair& rhs) {
    return lhs.link == rhs.link && lhs.comments == rhs.comments;
}

bool operator !=(const PostCommentPair& lhs, const PostCommentPair& rhs) {
    return !(lhs == rhs);
}




//****************
namespace detail {
//****************

void ThingParser::parseT3Object(T3Listing& dest, const nlohmann::json& json) {
    using detail::setIfNotNull;
    if (json.find("data") != json.end()) {
        setIfNotNull(dest.after, json["data"], "after", "");
        setIfNotNull(dest.before, json["data"], "before", "");
        setIfNotNull(dest.modhash, json["data"], "modhash", "");
        if (json["data"].find("children") != json["data"].end()) {
            for (auto it = json["data"]["children"].begin(); it != json["data"]["children"].end(); it++) {
                dest.links.push_back(parseLinkT3((*it)["data"]));
            }
        }
    }
    dest.links.shrink_to_fit();
}

Comment ThingParser::parseCommentT1(const nlohmann::json& json_obj) {
    Comment comment;
    using detail::setIfNotNull;

    setIfNotNull(comment.author, json_obj, "author", "");
    setIfNotNull(comment.banned_by, json_obj, "banned_by", "");
    setIfNotNull(comment.body, json_obj, "body", "");
    setIfNotNull(comment.id, json_obj, "id", "");
    setIfNotNull(comment.link_id, json_obj, "link_id", "");
    setIfNotNull(comment.name, json_obj, "name", "");
    setIfNotNull(comment.parent_id, json_obj, "parent_id", "");
    setIfNotNull(comment.subreddit, json_obj, "subreddit", "");
    setIfNotNull(comment.subreddit_id, json_obj, "subreddit_id", "");
    setIfNotNull(comment.subreddit_name_prefixed, json_obj, "subreddit_name_prefixed", "");
    setIfNotNull(comment.subreddit_type, json_obj, "subreddit_type", "");

    setIfNotNull(comment.banned_at_utc, json_obj, "banned_at_utc", static_cast<long long>(-1));
    setIfNotNull(comment.created, json_obj, "created", static_cast<long long>(-1));
    setIfNotNull(comment.created_utc, json_obj, "created_utc", static_cast<long long>(-1));
    setIfNotNull(comment.edited, json_obj, "edited", static_cast<long long>(-1));
    auto iter = json_obj.find("edited");
    if (iter != json_obj.end()) {
        if (iter->is_number() && !iter->is_null()) {
            setIfNotNull(comment.edited, json_obj, "edited", static_cast<long long>(-1));
        }
    }

    setIfNotNull(comment.downs, json_obj, "downs", -1);
    setIfNotNull(comment.gilded, json_obj, "gilded", -1);
    setIfNotNull(comment.likes, json_obj, "likes", -1);
    setIfNotNull(comment.num_reports, json_obj, "num_reports", -1);
    setIfNotNull(comment.score, json_obj, "score", -1);
    setIfNotNull(comment.ups, json_obj, "ups", -1);

    setIfNotNull(comment.archived, json_obj, "archived", false);
    setIfNotNull(comment.can_gild, json_obj, "can_gild", false);
    setIfNotNull(comment.can_mod_post, json_obj, "can_mod_post", false);
    setIfNotNull(comment.collapsed, json_obj, "collapsed", false);
    setIfNotNull(comment.is_sumbitter, json_obj, "is_sumbitter", false);
    setIfNotNull(comment.saved, json_obj, "saved", false);
    setIfNotNull(comment.stickied, json_obj, "stickied", false);

    if (json_obj.find("replies")!= json_obj.end()) {
        if (json_obj["replies"].find("data") != json_obj["replies"].end()) {
            auto child_array = json_obj["replies"]["data"].find("children");
            if (child_array != json_obj["replies"]["data"].end()) {
                for (auto& child : *child_array) {
                    comment.children.push_back(parseCommentT1(child["data"]));
                }
            }
        }
    }

    return comment;
}

Link ThingParser::parseLinkT3(const nlohmann::json& json_obj) {
    Link link;
    using detail::setIfNotNull;

    setIfNotNull(link.author, json_obj, "author", "");
    setIfNotNull(link.banned_by, json_obj, "banned_by", "");
    setIfNotNull(link.domain, json_obj, "domain", "");
    setIfNotNull(link.id, json_obj, "id", "");
    setIfNotNull(link.link_flair_text, json_obj, "link_flair_text", "");
    setIfNotNull(link.name, json_obj, "name", "");
    setIfNotNull(link.permalink, json_obj, "permalink", "");
    setIfNotNull(link.selftext, json_obj, "selftext", "");
    setIfNotNull(link.selftext_html, json_obj, "selftext_html", "");
    setIfNotNull(link.subreddit, json_obj, "subreddit", "");
    setIfNotNull(link.subreddit_id, json_obj, "subreddit_id", "");
    setIfNotNull(link.subreddit_name_prefixed, json_obj, "subreddit_name_prefixed", "");
    setIfNotNull(link.subreddit_type, json_obj, "subreddit_type", "");
    setIfNotNull(link.thumbnail, json_obj, "thumbnail", "");
    setIfNotNull(link.title, json_obj, "title", "");
    setIfNotNull(link.url, json_obj, "url", "");
    setIfNotNull(link.whitelist_status, json_obj, "whitelist_status", "");

    setIfNotNull(link.approved_at_utc, json_obj, "approved_at_utc", static_cast<long long>(-1));
    setIfNotNull(link.banned_at_utc, json_obj, "banned_at_utc", static_cast<long long>(-1));
    setIfNotNull(link.created_utc, json_obj, "created_utc", static_cast<long long>(-1));

    /* In the api, if it hasn't been edited it returns the value 'false' and not null for the key 'edited'
     * We must first check if the type is a number to set it to the variable.
     */
    auto iter = json_obj.find("edited");
    if (iter != json_obj.end()) {
        if (iter->is_number() && !iter->is_null()) {
            setIfNotNull(link.edited, json_obj, "edited", static_cast<long long>(-1));
        }
    }



    setIfNotNull(link.downs, json_obj, "downs", -1);
    setIfNotNull(link.gilded, json_obj, "gilded", -1);
    setIfNotNull(link.likes, json_obj, "likes", -1);
    setIfNotNull(link.num_comments, json_obj, "num_comments", -1);
    setIfNotNull(link.num_crossposts, json_obj, "num_crossposts", -1);
    setIfNotNull(link.report_reasons, json_obj, "report_reasons", -1);
    setIfNotNull(link.score, json_obj, "score", -1);
    setIfNotNull(link.ups, json_obj, "ups", -1);
    setIfNotNull(link.view_count, json_obj, "view_count", -1);

    setIfNotNull(link.archived, json_obj, "archived", false);
    setIfNotNull(link.can_gild, json_obj, "can_gild", false);
    setIfNotNull(link.can_mod_post, json_obj, "can_mod_post", false);
    setIfNotNull(link.clicked, json_obj, "clicked", false);
    setIfNotNull(link.hidden, json_obj, "hidden", false);
    setIfNotNull(link.hide_score, json_obj, "hide_score", false);
    setIfNotNull(link.is_crosspostable, json_obj, "is_crosspostable", false);
    setIfNotNull(link.is_self, json_obj, "is_self", false);
    setIfNotNull(link.is_video, json_obj, "is_video", false);
    setIfNotNull(link.locked, json_obj, "locked", false);
    setIfNotNull(link.over_18, json_obj, "over_18", false);
    setIfNotNull(link.spoiler, json_obj, "spoiler", false);
    setIfNotNull(link.stickied, json_obj, "stickied", false);
    setIfNotNull(link.visted, json_obj, "visted", false);

    return link;
}

void ThingParser::parsePairObject(PostCommentPair& dest, const nlohmann::json& t3, const nlohmann::json& t1) {
    if (t3.find("data") != t3.end()) {
        if (t3["data"]["children"].size() != 1) {// there is always only one t3 object.
            throw RedditError("An error has occured parsing, no T3 object found.");
        }
        else {
            dest.link = parseLinkT3(t3["data"]["children"][0]["data"]);
        }
    }
    if (t1.find("data") != t1.end()) {
        for (auto& t1_obj : t1["data"]["children"]) {
            dest.comments.push_back(parseCommentT1(t1_obj["data"]));
        }
    }
    dest.comments.shrink_to_fit();
}



}//! detail namespace

}//! redd namespace
