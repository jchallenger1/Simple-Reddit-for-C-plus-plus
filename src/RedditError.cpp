#include <iostream>
#include <exception>
#include <string>

#include "RedditError.hpp"

namespace redd {

// Print Errors from all sources separated by newlines.
std::ostream& operator<<(std::ostream& os, const RedditError& err) {
    const std::string& user = err.what();
    const std::string& cur = err.curl_what();
    const std::string& ser = err.server_what();
    if (!user.empty()) {
        os << "User Error : " << user;
        if (!cur.empty() || !ser.empty()) {
            os << "\n";
        }
    }
    if (!cur.empty()) {
        os << "Curl Error : " << cur;
        if (!ser.empty()) {
            os << "\n";
        }
    }
    if (!ser.empty()) {
        os << "Server Error : " << ser;
    }
    os << std::flush;
    return os;
}

} //! redd namespace


