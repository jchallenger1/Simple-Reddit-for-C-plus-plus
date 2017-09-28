#ifndef APIMETHOD_LISTING
#define APIMETHOD_LISTING

#include <string>
#include <memory>

#include "Curl.hpp"
#include "RedditUser.hpp"

namespace redd {



class MethodListing {
public:
    struct Inputs;

    struct Comment; // type prefix for T1
    struct Account; // T2
    struct Link;    // T3...
    struct Message;
    struct Subreddit;
    struct Award;

    struct Hot;

    MethodListing() : extraInputs(std::make_unique<Inputs>()) {}
    MethodListing(const MethodListing&);
    MethodListing& operator =(const MethodListing&);
    //void setInputs(const Inputs&);
    //Inputs& inputs() const;
    //Hot hot(const RedditUser&,const std::string& s);
private:
    std::unique_ptr<Inputs> extraInputs;
    detail::Curl curl;
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



} //! redd namespace



#endif // APIMETHOD_LISTING
