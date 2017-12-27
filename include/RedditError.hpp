#ifndef REDDITERROR_HPP
#define REDDITERROR_HPP

#include <iostream>
#include <exception>
#include <string>

namespace redd {

class RedditError : public std::runtime_error {
public:

    explicit RedditError(const std::string& a = "", const std::string& b = "", const std::string& c = "") :
 std::runtime_error(a), curl_msg(b), server_msg(c) {}


    std::string curl_what() const noexcept { return curl_msg; }
    std::string server_what() const noexcept { return server_msg; }
private:
    std::string curl_msg;
    std::string server_msg;
};

std::ostream& operator<<(std::ostream& os, const RedditError& err);

}//! redd namespace


#endif // REDDITERROR_HPP
