#ifndef REDDITERROR_HPP
#define REDDITERROR_HPP

#include <iostream>
#include <exception>
#include <string>

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

std::ostream& operator<<(std::ostream& os, const RedditError& err);

}//! redd namespace


#endif // REDDITERROR_HPP
