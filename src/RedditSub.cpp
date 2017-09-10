#include "RedditSub.hpp"

#include <vector>
#include <string>

#include "json.hpp"
#include "RedditError.hpp"
#include "HelperFunctions.hpp"

namespace redd {



RedditSub::RedditSub(const std::string &unparsed_str) {
    if (!unparsed_str.empty()) {
        fromJson(nlohmann::json::parse(unparsed_str));
    }
}

RedditSub::RedditSub(const nlohmann::json& parsed_json) {
    if (!parsed_json.empty()) {
        fromJson(parsed_json);
    }
}

void RedditSub::fromStr(const std::string & unparsed_str) {
    if (!unparsed_str.empty()) {
        fromJson(nlohmann::json::parse(unparsed_str));
    }
}

void RedditSub::fromJson(const nlohmann::json& json_obj) {
    redd_json = json_obj;
}

std::vector<RedditSub::ExternalPost> RedditSub::posts() const {
    std::vector<RedditSub::ExternalPost> return_posts(redd_json["data"]["children"].size());
    for (auto post_begin = redd_json["data"]["children"].begin();
        post_begin != redd_json["data"]["children"].end(); post_begin++) {
        auto index = post_begin - redd_json["data"]["children"].begin();
       try {
            auto& obj = (*post_begin)["data"];
            // String values
            setIfNotNull(return_posts[index].after, redd_json["data"], "after", "");
            setIfNotNull(return_posts[index].author, obj, "author", "");
            setIfNotNull(return_posts[index].before, redd_json["data"], "before", "");
            setIfNotNull(return_posts[index].id, obj, "id", "");
            setIfNotNull(return_posts[index].permalink, obj, "permalink", "");
            setIfNotNull(return_posts[index].selftext, obj, "selftext", "");
            setIfNotNull(return_posts[index].subreddit, obj, "subreddit", "");
            setIfNotNull(return_posts[index].subreddit_id, obj, "subreddit_id", "");
            setIfNotNull(return_posts[index].subreddit_name_prefix, obj, "subreddit_name_prefix", "");
            setIfNotNull(return_posts[index].thumbnail, obj, "thumbnail", "");
            setIfNotNull(return_posts[index].title, obj, "title", "");
            setIfNotNull(return_posts[index].url, obj, "url", "");

            // Number values
            setIfNotNull(return_posts[index].created_utc, obj, "created_utc", static_cast<long long>(-1));
            setIfNotNull(return_posts[index].gilded, obj, "gilded", -1);
            setIfNotNull(return_posts[index].downs, obj, "downs", -1);
            setIfNotNull(return_posts[index].ups, obj, "ups", -1);
            setIfNotNull(return_posts[index].num_comments, obj, "num_comments", -1);

            //Boolean values
            setIfNotNull(return_posts[index].hidden, obj, "hidden", false);
            setIfNotNull(return_posts[index].over_18, obj, "over_18", false);

        } catch(std::exception& err) {
            const std::string& a = err.what();
            throw RedditError("Error thrown setting RedditSub object, error |" + a + "|");
        }
    }
    return return_posts;
}

bool RedditSub::hasData() const {
    return !redd_json.empty();
}


// Non member functions

bool operator ==(const RedditSub::ExternalPost& lhs, const RedditSub::ExternalPost& rhs) {
    return lhs.url == rhs.url && lhs.id == rhs.id && lhs.author == rhs.author && lhs.subreddit_id == rhs.subreddit_id;
}

bool operator !=(const RedditSub::ExternalPost& lhs, const RedditSub::ExternalPost& rhs) {
    return !(lhs == rhs);
}

} //! namespace redd
