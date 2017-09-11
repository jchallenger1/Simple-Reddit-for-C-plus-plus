#include <iostream>
#include <exception>
#include <string>

#include "RedditError.hpp"

namespace redd {

std::ostream& operator<<(std::ostream& os, const RedditError& err) {
    std::string user = err.what();
    std::string cur = err.curl_what();
    std::string ser = err.server_what();
        /* Print Errors with name */
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


