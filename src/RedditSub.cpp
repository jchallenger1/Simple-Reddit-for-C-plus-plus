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
            using detail::setIfNotNull;
            setIfNotNull(return_posts[index].after, redd_json["data"], "after", "");
            setIfNotNull(return_posts[index].author, obj, "author", "");
            setIfNotNull(return_posts[index].before, redd_json["data"], "before", "");//
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
            // type must be long long, the number from the object is be too big for smaller data types.
            setIfNotNull(return_posts[index].created_utc, obj, "created_utc", static_cast<long long>(-1));
            setIfNotNull(return_posts[index].gilded, obj, "gilded", -1);
            setIfNotNull(return_posts[index].downs, obj, "downs", -1);
            setIfNotNull(return_posts[index].ups, obj, "ups", -1);
            setIfNotNull(return_posts[index].num_comments, obj, "num_comments", -1);

            // Boolean values
            setIfNotNull(return_posts[index].hidden, obj, "hidden", false);
            setIfNotNull(return_posts[index].over_18, obj, "over_18", false);

            // get the previews
            auto& previews = return_posts[index].preview;
            previews.reserve(10);
            if (obj.find("preview") != obj.end()) {
                if (obj["preview"].find("images") != obj["preview"].end()) {
                    if (!obj["preview"]["images"].empty()) {
                        auto& images = obj["preview"]["images"][0];
                        if (!images.empty() && images.find("source") != images.end()) {
                            // add the main source preview
                            auto& source = images["source"];
                            std::string url; int width; int height;
                            setIfNotNull(url, source, "url", "");
                            setIfNotNull(width, source, "width", -1);
                            setIfNotNull(height, source, "height", -1);
                            previews.push_back(std::make_pair(url, std::make_pair(width, height)));
                        }
                        if (images.find("resolutions") != images.end()) {
                            // add the non main previews
                            for (auto res_iter = images["resolutions"].begin();
                                 res_iter != images["resolutions"].end(); res_iter++) {
                                std::string url; int width; int height;
                                setIfNotNull(url, *res_iter, "url", "");
                                setIfNotNull(width, *res_iter, "width", -1);
                                setIfNotNull(height, *res_iter, "height", -1);
                                previews.push_back(std::make_pair(url, std::make_pair(width, height)));
                            }
                        }
                    }
                }
            }

        } catch(std::exception& err) {
            const std::string& a = err.what();
            throw RedditError("Error thrown setting RedditSub object, error : |" + a + "|");
        }
    }
    return return_posts;
}

bool RedditSub::hasData() const {
    return !redd_json.empty();
}



bool operator ==(const RedditSub::ExternalPost& lhs, const RedditSub::ExternalPost& rhs) {
    return lhs.url == rhs.url && lhs.id == rhs.id && lhs.author == rhs.author && lhs.subreddit_id == rhs.subreddit_id;
}

bool operator !=(const RedditSub::ExternalPost& lhs, const RedditSub::ExternalPost& rhs) {
    return !(lhs == rhs);
}

} //! redd namespace
