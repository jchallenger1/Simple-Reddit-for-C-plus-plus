#include <string>

#include "json.hpp"

#include "RedditSimpleClient.hpp"
#include "RedditError.hpp"
#include "Curl.hpp"
#include "RedditSub.hpp"

namespace redd {

std::string RedditSimpleClient::requestToken(const RedditUser& user) {
    curl.emptyErrors(); // make sure the errors are from this session
    std::string post_fields("grant_type=password&username=" + user.user() + "&password=" + user.pass());
    std::string token = curl.simplePost("https://www.reddit.com/api/v1/access_token", user, post_fields);
    nlohmann::json json_obj;
    parseStr(token, json_obj);

    auto iter = json_obj.find("access_token");
    if (iter == json_obj.end()) {
        if (json_obj.find("message") != json_obj.end() && json_obj.find("error") != json_obj.end() ) {
            std::string ser_err(json_obj.value("error","Unkown error code") + " : " + json_obj.value("message","Unkown error message"));
            throw RedditError("The server did not provide an access token.", curl.curlErrors(), ser_err);
        }
        else {
            throw RedditError("The server did not provide an access token.", curl.curlErrors());
        }
    }
    return json_obj["access_token"];
}



RedditSub RedditSimpleClient::subreddit(const RedditUrl url) {
    curl.emptyErrors();
    url.addJson();
    std::string unparsed = curl.simpleGet(url.url());
    nlohmann::json json_obj;
    parseStr(unparsed, json_obj);
    return RedditSub();
}

} //! redd namespace
