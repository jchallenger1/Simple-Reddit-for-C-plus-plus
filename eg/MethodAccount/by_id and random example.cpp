#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

#include "RedditUser.hpp"
#include "RedditError.hpp"
#include "MethodListing.hpp"
#include "ThingTypes.hpp"

using namespace redd;

// Example of MethodListing::random and MethodListing::by_id
// Function uses the interface of [/r/subreddit]/random and /by_id/names
// Example will :
// Get a random post from the all subreddit
// Return information of a post based on an id.

int main() {
    // Get the user token, expires in 1 hr
    RedditUser user("Username","Password","clientID","clientSecret");
	MethodListing listing;
    try {
        user.setToken(listing.requestToken(user));
    } catch(RedditError& err) {
        std::cerr << err << std::endl;
    }

    std::string id;
    ThingTypes::PostCommentPair pair = listing.random(user, "all");
    // print random's body text.
    std::cout << pair.link.selftext << std::endl;

    // get the t3's fullname.
    id = pair.link.name;
    MethodListing::Link post = listing.by_id(user, id);

    std::cout << std::boolalpha;

    std::cout << (post == pair.link) << std::endl; // true

    return 0;
}
