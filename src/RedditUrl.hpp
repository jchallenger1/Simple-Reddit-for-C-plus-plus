#ifndef REDDITURL
#define REDDITURL

#include <iostream>
#include <string>
#include <vector>

namespace redd {
    /* An interface to deal with various types of reddit urls and a way to process them */
    class RedditUrl {
    public:
    RedditUrl() = delete;
    RedditUrl(const string&) : given_url(url), base_url(stripUrl(url)), return_url(url) {}
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

    bool isSubreddit() const; // determines if managed url has a subreddit embeded

    void resetToBase(); // resets the url without query strings
    void resetToRaw(); // resets the url to

    void stripUrl();

    void addJson();
    /* TODO: add implementation
     * TODO: add functionality for std::pair of a container and a string or const char of a container
    */
    template<typename T>
    void addQueryStrings(T&& container);

    template<typename Iter>
    void addQueryStrings(const Iter&& begin, const Iter&& end);




    private:
        const std::string given_url; // the url passed into the constructor
        const std::string base_url; // stripped down url to either the subreddit or the frontpage
        std::string return_url; // the url processed by the class
        std::string stripUrl(const string& url) const;
    };

    std::ostream& operator<<(std::ostream&, const RedditUrl& url);
}


#endif
