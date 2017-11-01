#include <memory>
#include <string>
#include <functional>
#include <utility>

#include "json.hpp"

#include "MethodListing.hpp"
#include "HelperFunctions.hpp"
#include "RedditUrl.hpp"
#include "ThingTypes.hpp"

namespace redd {

// Function delgates all networking onto other.
MethodListing::MethodListing(const detail::Method& m) : extra_inputs(std::make_unique<Inputs>()) {
    setDependencyOn(m);
}


Link MethodListing::by_id(const RedditUser& user, const std::string& fullname) {
    setToken(user);
    std::string url("https://oauth.reddit.com/by_id/" + fullname);
    std::string unparsed = curl->simpleGet(url);
    nlohmann::json json;
    strToJson(unparsed, json);

    Link link;
    if (json.find("data") != json.end()) {
        if (!json["data"]["children"].empty()) {
            link = detail::ThingParser::parseLinkT3(json["data"]["children"][0]["data"]);
        }
    }
    return link;
}

PostCommentPair MethodListing::commentTree
    (const RedditUser& user, const std::string& subreddit, const std::string& id) {
    setToken(user);
    PostCommentPair tree;
    RedditUrl url("https://oauth.reddit.com/r/" + subreddit + "/comments/" + id);
    std::string unparsed = curl->simpleGet(url.url());
    nlohmann::json json;
    strToJson(unparsed, json);

    // object comes in form of an array always with size 2.
    if (json.size() != 2) {
        throw RedditError("An error has occured in parsing /r/" + subreddit + "/comments/" + id + " endpoint.");
    }
    detail::ThingParser::parsePairObject(tree, json[0], json[1]);
    return tree;
}

PostCommentPair MethodListing::random(const RedditUser& user, const std::string& s) {
    setToken(user);
    PostCommentPair random;
    std::string url("https://oauth.reddit.com/r/" + s + "/random");
    std::string unparsed = curl->simpleGet(url);
    nlohmann::json json;
    strToJson(unparsed, json);

    // object comes in form of an array always with size 2.
    if (json.size() != 2) {
        throw RedditError("An error has occured in parsing /api/random endpoint.");
    }
    detail::ThingParser::parsePairObject(random, json[0], json[1]);
    return random;
}

std::vector<Link> MethodListing::duplicates(const RedditUser& user, const std::string& id) {
    setToken(user);
    RedditUrl url("https://oauth.reddit.com/duplicates/" + id);
    std::string query_strings = inputsToString();
    if (!query_strings.empty()) {
        url.addQueryString(query_strings);
    }
    std::string unparsed = curl->simpleGet(url.url());
    nlohmann::json json;
    strToJson(unparsed, json);
    std::vector<Link> listings;

    for (auto& t3_object : json) {
        if (t3_object.find("data") != t3_object.end()) {
            for (auto& t3 : t3_object["data"]["children"]) {
                listings.push_back(detail::ThingParser::parseLinkT3(t3["data"]) );
            }
        }
    }

    listings.shrink_to_fit();
    return listings;
}

T3Listing MethodListing::hot(const RedditUser& user, const std::string& s) {
    setToken(user);
    RedditUrl url("https://oauth.reddit.com/r/" + s + "/hot");
    std::string query_strings = inputsToString();
    if (!query_strings.empty()) {
        url.addQueryString(query_strings);
    }

    T3Listing list;
    std::string unparsed = curl->simpleGet(url.url());
    nlohmann::json json;
    strToJson(unparsed, json);

    detail::ThingParser::parseT3Object(list, json);

    return list;
}

T3Listing MethodListing::_new(const RedditUser& user, const std::string& s) {
    setToken(user);
    RedditUrl url("https://oauth.reddit.com/r/" + s + "/new");
    std::string query_strings = inputsToString();
    if (!query_strings.empty()) {
        url.addQueryString(query_strings);
    }

    T3Listing list;
    std::string unparsed = curl->simpleGet(url.url());
    nlohmann::json json;
    strToJson(unparsed, json);
    detail::ThingParser::parseT3Object(list, json);

    return list;
}

T3Listing MethodListing::top(const RedditUser &user , const std::string &s) {
    setToken(user);
    RedditUrl url("https://oauth.reddit.com/r/" + s + "/top");
    std::string query_strings = inputsToString();
    if (!query_strings.empty()) {
        url.addQueryString(query_strings);
    }

    T3Listing list;
    std::string unparsed = curl->simpleGet(url.url());
    nlohmann::json json;
    strToJson(unparsed, json);
    detail::ThingParser::parseT3Object(list, json);

    return list;
}

T3Listing MethodListing::controversial(const RedditUser& user, const std::string& s) {
    setToken(user);
    RedditUrl url("https://oauth.reddit.com/r/" + s + "/controversial");
    std::string query_strings = inputsToString();
    if (!query_strings.empty()) {
        url.addQueryString(query_strings);
    }

    T3Listing list;
    std::string unparsed = curl->simpleGet(url.url());
    nlohmann::json json;
    strToJson(unparsed, json);
    detail::ThingParser::parseT3Object(list, json);

    return list;
}

T3Listing MethodListing::rising(const RedditUser& user, const std::string& s) {
    setToken(user);
    RedditUrl url("https://oauth.reddit.com/r/" + s + "/rising");
    std::string query_strings = inputsToString();
    if (!query_strings.empty()) {
        url.addQueryString(query_strings);
    }

    T3Listing list;
    std::string unparsed = curl->simpleGet(url.url());
    nlohmann::json json;
    strToJson(unparsed, json);

    detail::ThingParser::parseT3Object(list, json);

    return list;
}

// Accesses extra_inputs and accumulates a string containing
// query strings for each existing key of Inputs struct.
std::string MethodListing::inputsToString() const {
    std::string str_inputs;
    // String values
    if (!extra_inputs->after.empty())
        str_inputs.append("after=" + extra_inputs->after + "&");
    if (!extra_inputs->article.empty())
        str_inputs.append("article=" + extra_inputs->article + "&");
    if (!extra_inputs->before.empty())
        str_inputs.append("before=" + extra_inputs->before + "&");
    if (!extra_inputs->comment.empty())
        str_inputs.append("comment=" + extra_inputs->comment + "&");
    if (!extra_inputs->g.empty())
        str_inputs.append("g=" + extra_inputs->g + "&");
    if (!extra_inputs->t.empty())
        str_inputs.append("t=" + extra_inputs->t + "&");
    if (!extra_inputs->show.empty())
        str_inputs.append("show=" + extra_inputs->show + "&");
    if (!extra_inputs->sort.empty())
        str_inputs.append("sort=" + extra_inputs->sort + "&");

    // Integer Values
    if (extra_inputs->count > 0)
        str_inputs.append("count=" + std::to_string(extra_inputs->count) + "&");
    if (extra_inputs->depth > 0)
        str_inputs.append("depth=" + std::to_string(extra_inputs->depth) + "&");
    if (extra_inputs->limit > 0)
        str_inputs.append("limit=" + std::to_string(extra_inputs->limit) + "&");

    // Short Values
    if (extra_inputs->context > 0 && extra_inputs->context < 9)
        str_inputs.append("context=" + std::to_string(extra_inputs->context) + "&");
    if (extra_inputs->truncate > 0 && extra_inputs->truncate < 51)
        str_inputs.append("context=" + std::to_string(extra_inputs->truncate) + "&");

    // Boolean Values
    if (extra_inputs->showedits)
        str_inputs.append("showedits=true&");
    if (extra_inputs->showmore)
        str_inputs.append("showmore=true&");
    if (extra_inputs->sr_detail)
        str_inputs.append("sr_detail=true&");
    if (extra_inputs->threaded)
        str_inputs.append("threaded=true");

    auto iter = std::find(str_inputs.crbegin(), str_inputs.crend(), '&').base();
    if (str_inputs.end() - iter >= 3) {
        //there is a leading &
        str_inputs.erase(iter);
    }

    return str_inputs;
}

void MethodListing::setInputs(const Inputs& inputs) {
    *extra_inputs = inputs;
}

MethodListing::Inputs& MethodListing::inputs() {
    return *extra_inputs;
}

void MethodListing::resetInputs() {
    *extra_inputs = Inputs();
}






} //! redd namsepace
