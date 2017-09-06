#include "RedditSub.hpp"

#include <vector>
#include <string>

#include "json.hpp"

namespace redd {



RedditSub::RedditSub(const std::string &unparsed_str) {
    if (!unparsed_str.empty()) {
        nlohmann::json&& a = nlohmann::json::parse(unparsed_str);
        fromJson(std::move(a));
    }
}

RedditSub::RedditSub(const nlohmann::json& parsed_json) {
    if (!parsed_json.empty()) {
        fromJson(parsed_json);
    }
}

void RedditSub::fromStr(const std::string & unparsed_str) {
    if (!unparsed_str.empty()) {
        nlohmann::json&& a = nlohmann::json::parse(unparsed_str);
        fromJson(std::move(a));
    }
}

void RedditSub::fromJson(const nlohmann::json& json_obj) {
    std::vector<RedditSub::SimplePost> return_posts;
    for (auto post_begin = json_obj["data"]["children"].begin();
        post_begin != json_obj["data"]["children"].end(); post_begin++) {
        auto index = post_begin - json_obj["data"]["children"].begin();
        return_posts[index].after = post_begin->value("after", "");
        return_posts[index].before = post_begin->value("before", "");
    }
}

std::vector<RedditSub::SimplePost> RedditSub::posts() const {

    return std::vector<RedditSub::SimplePost>();
}

bool RedditSub::hasData() const {
    return redd_json.empty();
}

}
