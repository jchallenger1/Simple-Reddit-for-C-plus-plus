#include <string>
#include <iostream>

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
        std::string server_errors;
        std::string message, error, error_desc;
        detail::setIfNotNull(message, json_obj, "message", "unkown message");
        detail::setIfNotNull(error, json_obj, "error", "unkown error");
        detail::setIfNotNull(error_desc, json_obj, "error_description", "unkown error description");
        server_errors = message + " " + error + " " + error_desc;
        throw RedditError("The server did not provide an access token.",
                          curl.curlErrors(), server_errors);
    }
    return json_obj["access_token"];
}



RedditSub RedditSimpleClient::subreddit(const std::string& url) {
    curl.emptyErrors(); // ensure errors are from this function
    RedditUrl scoped_url(url);
    scoped_url.addJson();
    std::string unparsed = curl.simpleGet(scoped_url.url());
    nlohmann::json json_obj;
    parseStr(unparsed, json_obj);
    return RedditSub(json_obj);
}


void RedditSimpleClient::parseStr(const std::string& str, nlohmann::json& json_obj) const {
    try {
        json_obj = nlohmann::json::parse(str);
    }
    catch(const std::exception& err) {
        const std::string& what = err.what();
        throw RedditError("A problem occured when parsing, Json Error:|" + what + "|");
    }
}

} //! redd namespace
