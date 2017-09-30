#ifndef APIMETHOD_LISTING
#define APIMETHOD_LISTING

#include <string>
#include <memory>

#include "Curl.hpp"
#include "RedditUser.hpp"
#include "Method.hpp"

namespace redd {



class MethodListing : public detail::Method {
public:
    struct Inputs;

    struct Comment; // type prefix for T1
    struct Account; // T2
    struct Link;    // T3...
    struct Message;
    struct Subreddit;
    struct Award;

    struct Hot;

    explicit MethodListing() : detail::Method() {}
    MethodListing(const detail::Method& m);

    void setInputs(const Inputs&);
    Inputs& inputs() const;
    Hot hot(const RedditUser&, const std::string& s);
private:
    std::unique_ptr<Inputs> extraInputs;
};

struct MethodListing::Inputs {
    std::string after;
    std::string before;
    std::string count;
    std::string g;
    int limit;
    bool show;
    bool sr_detail;
};

struct MethodListing::Hot {

};

} //! redd namespace



#endif // APIMETHOD_LISTING
