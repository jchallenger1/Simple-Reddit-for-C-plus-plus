#ifndef REDDITURL
#define REDDITURL

#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>

#include "HelperFunctions.hpp"

namespace redd {

    /* An interface to deal with various types of reddit urls and a way to process them */
class RedditUrl {
public:
    RedditUrl() = delete;
    RedditUrl(const std::string& url) : given_url(url), base_url(stripUrl(url)), return_url(url) {}
    RedditUrl(const char* url) : given_url(url), base_url(stripUrl(url)), return_url(url) {}
    ~RedditUrl() = default;
    RedditUrl(const RedditUrl&) = default;

    RedditUrl& operator =(const RedditUrl&) = default;

    RedditUrl& operator +=(const std::string);
    RedditUrl& operator +=(const char*);

    RedditUrl& operator =(const std::string);
    RedditUrl& operator =(const char*);

    char& operator[](size_t index);

    std::string::iterator begin() noexcept;
    std::string::iterator end() noexcept;
    std::string::const_iterator cbegin() const noexcept;
    std::string::const_iterator cend() const noexcept;

    std::string url() const;
    std::string based_url() const;
    std::string raw_url() const;

    explicit operator std::string();

    void resetToBase(); // resets the url without query strings
    void resetToRaw(); // resets the url to

    void stripUrl();

    void addJson();

    void addQueryString(const std::string& str);

    template<typename T>
    void addQueryStrings(T&& container);

    template<typename T>
    void addQueryStrings(std::initializer_list<T>&& list);

    template<typename Iter>
    void addQueryStrings(Iter&& begin, Iter&& end);

private:
        const std::string given_url; // the url passed into the constructor
        const std::string base_url; // stripped down url to either the subreddit or the frontpage in the format ...reddit.com/r/.../ or ...reddit.com/
        std::string return_url; // the url processed by the class
        std::string stripUrl(const std::string& url) const;
};

/* Functions */
std::ostream& operator<<(std::ostream&, const RedditUrl& url);


/*  Templates */
template<typename T>
void RedditUrl::addQueryStrings(T&& container) {
    static_assert(detail::IsStrOrPtr<typename T::value_type>,
                   "Underlying type of container must be of type std::string or const char*");
    addQueryStrings(std::begin(std::forward<T>(container)), std::end(std::forward<T>(container)));
}

template<typename T>
void RedditUrl::addQueryStrings(std::initializer_list<T>&& list) {
    using list_t = std::initializer_list<T>;
    static_assert(detail::IsStrOrPtr<T>, "Underlying type of container must be of type std::string or const char*");
    addQueryStrings(std::begin(std::forward<list_t>(list)), std::end(std::forward<list_t>(list)));
}

template<typename Iter>
void RedditUrl::addQueryStrings(Iter&& begin, Iter&& end) {
    static_assert(detail::IsStrOrPtr<typename std::iterator_traits<Iter>::value_type>,
                   "Underlying type of container must be of type std::string or const char*");
    while (begin != end) {
        addQueryString(*std::forward<Iter>(begin++));
    }
}


} //! redd namespace


#endif
