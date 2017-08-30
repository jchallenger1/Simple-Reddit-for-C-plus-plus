#ifndef REDDITERROR_HPP
#define REDDITERROR_HPP

#include <iostream>
#include <exception>
#include <string>
#include <cstring>

namespace redd {
    class RedditError : public std::runtime_error {
    public:

        template<typename T = const char *, typename G = const char*, typename H = const char*>
        explicit RedditError(T&& a = "", G&& b = "", H&& c = "") : std::runtime_error(std::forward<T>(a)),
            curl_msg(std::forward<G>(b)), server_msg(std::forward<H>(c)) {}


        std::string curl_what() const noexcept { return curl_msg; }
        std::string server_what() const noexcept { return server_msg; }
    private:
        std::string curl_msg;
        std::string server_msg;
    };

    std::ostream& operator<<(std::ostream& os, const RedditError& err) {
        std::string user = err.what();
        std::string cur = err.curl_what();
        std::string ser = err.server_what();
        /* Print Errors with name */
        if (!user.empty()) {
            os << "User Error : " << main << (!cur.empty() || !ser.empty() ? "\n" : std::flush);
        }
        if (!cur.empty()) {
            os << "Curl Error : " << cur << (!ser.empty() ? "\n" : std::flush);
        }
        if (!ser.empty()) {
            os << "Server Error : " << ser << std::flush;
        }
        return os;
     }
}

#endif // REDDITERROR_HPP
