#include "RedditSub.hpp"

#include <vector>

namespace redd {



RedditSub::RedditSub(const std::string &unparsed_json) {

}

RedditSub::RedditSub(const nlohmann::basic_json &) {
    this->
}

void RedditSub::parseStr(const string & unparsed_json) {

}

RedditSub::SimplePost RedditSub::parseSimpleJson(const nlohmann::basic_json& json_obj) {
    std::vector<RedditSub::SimplePost> return_posts;
    for (auto post_begin = json_obj["data"]["children"].begin();
        post_begin != json_obj["data"]["children"].end(); post_begin++) {

    }
}

bool RedditSub::hasData() const {
    return this->posts.empty();
}

}
