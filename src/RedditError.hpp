#ifndef REDDITERROR_HPP
#define REDDITERROR_HPP

#include <exception>
#include <string>

class RedditError : public std::runtime_error {
public:

    template<typename T, typename G, typename H>
    explicit RedditError(T&& a, G&& b, H&& c) : std::runtime_error(std::forward<T>(a)),
        curl_msg(std::forward<G>(b)), server_msg(std::forward<H>(c)) {}

    template<typename T, typename G>
    explicit RedditError(T&& a, G&& b) : std::runtime_error(std::forward<T>(a)),
        curl_msg(std::forward<G>(b)){}

    template<typename T>
    explicit RedditError(T&& a) : std::runtime_error(std::forward<T>(a)) {}

    const char* curl_what() const { return curl_msg.c_str(); }
    const char* server_what() const { return server_msg.c_str(); }
private:
    std::string curl_msg;
    std::string server_msg;
};


#endif // REDDITERROR_HPP
