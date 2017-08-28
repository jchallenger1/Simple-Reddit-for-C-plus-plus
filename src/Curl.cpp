#include <string>
#include <cstring>
#include <fstream>
#include <exception>

#include <curl/curl.h>
#include "json.hpp"

#include "Curl.hpp"
#include "RedditError.hpp"

redd::Curl::Curl() {
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_error);
}

redd::Curl::~Curl() {
    curl_easy_reset(curl);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

std::string redd::Curl::requestToken(redd::RedditUser& user) {
    if (!user.isFilled()) {
        throw RedditError("User must have Username, Password, Client ID and Client Secret.");
    }
    std::string result;
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.reddit.com/api/v1/access_token");
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &redd::Curl::writeToString);
    std::string post_field("grant_type=password&username=" + user.user() + "&password=" + user.pass());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_field.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
    std::string auth = user.ID() + ":" + user.secret();
    curl_easy_setopt(curl, CURLOPT_USERPWD, auth.c_str());
    auto response = curl_easy_perform(curl);

    if (response != CURLE_OK || result.empty()) {
        throw RedditError("Curl was not able to make the request to the server.", curl_error);
    }

    nlohmann::json json_obj = nlohmann::json::parse(result);
    auto iter = json_obj.find("access_token");
    if (iter == json_obj.end()) {
        if (json_obj.find("message") != json_obj.end() && json_obj.find("error") != json_obj.end() ) {
            throw RedditError("The server did not provide an access token.", curl_error, json_obj["error"] + " : " + json_obj["message"]);
        }
        else {
            throw RedditError("The server did not provide an access token.", curl_error);
        }
    }
    return json_obj["access_token"];
}

void redd::Curl::emptyErrors() {
    memset(curl_error,0,sizeof(curl_error));
}


size_t redd::Curl::writeToFile(void *buffer, size_t size, size_t nmemb, std::ofstream *userp) {
    userp->write(reinterpret_cast<char*>(buffer), size * nmemb);
    return size * nmemb;
}

size_t redd::Curl::writeToString(void *buffer, size_t size, size_t nmemb, std::string *userp) {
    userp->append(reinterpret_cast<char*>(buffer), size * nmemb);
    return size * nmemb;
}
