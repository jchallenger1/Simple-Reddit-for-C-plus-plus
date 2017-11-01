#include <vector>
#include <string>
#include <memory>

#include "ThingTypes.hpp"
#include "MethodSearch.hpp"
#include "RedditUser.hpp"
#include "RedditUrl.hpp"


namespace redd {


std::vector<Link> MethodSearch::search(const RedditUser& user, const std::string& s) {
    setToken(user);
    RedditUrl url("http://oauth.reddit.com/r/" + s + "/search");
    std::string in = inputsToString();
    if (!in.empty()) {
        url.addQueryString(in);
    }
    std::string unparsed = curl->simpleGet(url.url());
    nlohmann::json json;
    strToJson(unparsed, json);
    std::vector<Link> links;

    if (json.find("data") != json.end()) {
        auto& child_arr = json["data"]["children"];
        for (auto it = child_arr.begin(); it != child_arr.end(); it++) {
            links.push_back(detail::ThingParser::parseLinkT3(*it));
        }
    }

    return links;

}

void MethodSearch::setInputs(const Inputs& inputs) {
    *extra_inputs = inputs;
}

void MethodSearch::resetInputs() {
    *extra_inputs = Inputs();
}

MethodSearch::Inputs& MethodSearch::inputs() {
    return *extra_inputs;
}

std::string MethodSearch::inputsToString() const {
    std::string str;
    // String values
    if (!extra_inputs->after.empty())
        str.append("after=" + extra_inputs->after + "&");
    if (!extra_inputs->before.empty())
        str.append("before=" + extra_inputs->before + "&");
    if (!extra_inputs->q.empty())
        str.append("q=" + extra_inputs->q + "&");
    if (!extra_inputs->show.empty())
        str.append("show=" + extra_inputs->show + "&");
    if (extra_inputs->sort.empty())
        str.append("sort=" + extra_inputs->sort + "&");
    if (extra_inputs->syntax.empty())
        str.append("syntax=" + extra_inputs->syntax + "&");
    if (extra_inputs->t.empty())
        str.append("t=" + extra_inputs->t + "&");
    if (extra_inputs->type.empty())
        str.append("type=" + extra_inputs->type + "&");



    // Integer values
    if (extra_inputs->count != 0)
        str.append("count=" + std::to_string(extra_inputs->count) + "&");
    if (extra_inputs->limit <= 100 && extra_inputs->limit != 0)
        str.append("limit=" + std::to_string(extra_inputs->limit) + "&");


    // Boolean values
    if (extra_inputs->restrict_sr)
        str.append("restrict_sr=true");
    if (extra_inputs->sr_detail)
        str.append("sr_detail=true");

    auto iter = std::find(str.crbegin(), str.crend(), '&').base();
    if (str.end() - iter >= 3) {
        //there is a leading &
        str.erase(iter);
    }
    return str;
}


}//! redd namespace
