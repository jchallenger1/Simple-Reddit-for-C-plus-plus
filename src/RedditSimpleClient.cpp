#include <string>

#include "json.hpp"

#include "RedditError.hpp"
#include "Curl.hpp"


std::string redd::RedditSimpleClient::requestToken(const redd::RedditUser& user) {
    curl.emptyErrors(); // make sure the errors are from this session
    std::string post_fields("grant_type=password&username=" + user.user() + "&password=" + user.pass());
    std::string token = curl.simplePost("https://www.reddit.com/api/v1/access_token", user, post_fields);
    nlohmann::json json_obj;
    try {
        json_obj = nlohmann::json::parse(token);
    }
    catch(const std::exception& err) {
        throw RedditError("A problem occured when parsing, Json Error:|" + err.what() + "|");
    }

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