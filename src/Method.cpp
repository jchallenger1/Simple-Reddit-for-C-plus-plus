#include <memory>
#include <string>

#include "json.hpp"

#include "Method.hpp"
#include "Curl.hpp"
#include "HelperFunctions.hpp"
#include "RedditError.hpp"

namespace redd {

namespace detail {

Method::Method(Method &m)  {
    setDependencyOn(m);
}

Method::~Method() {}

// Delgates and shares all networking work to other.
void Method::setDependencyOn(const Method &other) & {
    auto ptr = other.wkptr.lock();
    if (ptr) {
        curl = other.curl;
        wkptr = other.curl;
    }
    else {
        throw std::runtime_error("Method type's curl pointer does not exist.");
    }
}

void Method::createNewHandle() & {
    curl = std::make_shared<detail::Curl>();
    wkptr = curl;
}

// Function checks if the json recieved is successful and throws otherwise.
// Is done through finding three keys on all non-successful jsons.
void Method::checkJsonErrors(const nlohmann::json &json) const {
    std::string server_error;
    std::string temp;
    int num;
    if (json.find("error") != json.end()) {
        setIfNotNull(num, json, "error", 0);
        server_error += "Error : " + std::to_string(num) + " ";
    }
    if (json.find("message") != json.end()) {
        setIfNotNull(temp, json, "message", "unkown message");
        server_error += temp + " ";
    }
    if (json.find("error_desc") != json.end()) {
        setIfNotNull(temp, json, "error_desc", "unkown error description");
        server_error += temp + " ";
    }
    if (!server_error.empty()) {
        throw RedditError("The server replied with an error", curl->curlErrors(), server_error);
    }
}


void Method::strToJson(const std::string& src, nlohmann::json& dest) const {
    try {
        dest = nlohmann::json::parse(src);
    } catch(const std::exception& err) {
        const std::string& what = err.what();
        throw RedditError("A problem occured when parsing, Json Error:|" + what + "|");
    }
    checkJsonErrors(dest);
}

}//! detail namespace

}//! redd namespace
