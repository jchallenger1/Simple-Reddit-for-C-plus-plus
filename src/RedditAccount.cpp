#include <string>

#include "json.hpp"

#include "RedditAccount.hpp"
#include "RedditUser.hpp"
#include "RedditError.hpp"

namespace redd {


RedditAccount::Me acc_me(const RedditUser& user) const {
    if (!user.isComplete()) {
        throw RedditError("RedditUser must be complete");
    }
    RedditAccount::Me return_me;
    std::string unparsed = curl.simpleGet("https://oauth.reddit.com/api/v1/me", "Authorization : bearer" + user.token());
    nlohmann::json json = nlohmann::json::parse(unparsed);
    {
        /*
         * TODO : use the return_me to add the variables and return.
         * SimpleClient's parseStr should be a non member function declared in helperfunctions.hpp.
        */
    }
    return return_me;
}

}//! redd namespace

