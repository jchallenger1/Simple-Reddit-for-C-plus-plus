#ifndef APIMETHOD_LISTING
#define APIMETHOD_LISTING

#include <string>
#include <memory>

#include "Curl.hpp"
#include "RedditUser.hpp"
#include "Method.hpp"
#include "ThingTypes.hpp"

namespace redd {

class MethodListing : public detail::Method {
public:
    struct Inputs; // representation of query strings user is able to input.

    // constructors
    explicit MethodListing() : detail::Method(), extra_inputs(std::make_unique<Inputs>()) {}
    MethodListing(const detail::Method& m);

    // functions for inputs
    void setInputs(const Inputs&);
    void resetInputs();
    Inputs& inputs();

    // *** function endpoints ***
    // missing /api/trending_subreddits

    // calls [/r/subreddit]/comments/article
    PostCommentPair commentTree(const RedditUser&, const std::string& subreddit, const std::string& id);
    // calls [/r/subreddit]/random
    PostCommentPair random(const RedditUser&, const std::string& subreddit); // this function may not work at times
    // calls /by_id/names
    Link by_id(const RedditUser&, const std::string& fullname);
    // calls /duplicates/article
    std::vector<Link> duplicates(const RedditUser&, const std::string& id); // id is not the fullname!, ex : 74pqir
    // rests calls [/r/subreddit]/new, [/r/subreddit]/hot ...
    T3Listing _new(const RedditUser&, const std::string& subreddit);
    T3Listing hot(const RedditUser&, const std::string& subreddit);
    T3Listing top(const RedditUser&, const std::string& subreddit);
    T3Listing controversial(const RedditUser&, const std::string& subreddit);
    T3Listing rising(const RedditUser&, const std::string& subreddit);
private:
    std::unique_ptr<Inputs> extra_inputs;

    std::string inputsToString() const;
    inline void setToken(const RedditUser&);
};

struct MethodListing::Inputs {
    std::string after;
    std::string article;
    std::string before;
    std::string comment;
    std::string g;
    std::string t;
    std::string show;
    std::string sort;
    int count;
    int depth;
    int limit;
    short context;
    short truncate;
    bool showedits;
    bool showmore;
    bool sr_detail;
    bool threaded;
};


} //! redd namespace



#endif // APIMETHOD_LISTING
